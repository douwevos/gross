/*
   File:    gropdotstate.c
   Project: gross-parser
   Author:  Douwe Vos
   Date:    Mar 19, 2017
   e-mail:  dmvos2000(at)yahoo.com

   Copyright (C) 2017 Douwe Vos.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "gropdotstate.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "GroPDotState"
#include <logging/catlog.h>

struct _GroPDotStatePrivate {
	GroPProduction *production;
	int dot_pos;
	CatIntArrayWo *nullified;
	gboolean is_terminated;
	GroPSymbolSet *first_set;
	GroPDotState *shifted_normal;
	GroPDotState *shifted_nullified;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPDotState, grop_dot_state, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPDotState)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_dot_state_class_init(GroPDotStateClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_dot_state_init(GroPDotState *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	GroPDotState *instance = GROP_DOT_STATE(object);
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(instance);
	cat_unref_ptr(priv->first_set);
	cat_unref_ptr(priv->nullified);
	cat_unref_ptr(priv->production);
	cat_unref_ptr(priv->shifted_normal);
	cat_unref_ptr(priv->shifted_nullified);
	G_OBJECT_CLASS(grop_dot_state_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_dot_state_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPDotState *grop_dot_state_new(GroPProduction *production, int dot_pos, CatIntArrayWo *nullified) {
	GroPDotState *result = g_object_new(GROP_TYPE_DOT_STATE, NULL);
	cat_ref_anounce(result);
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(result);
	priv->dot_pos = dot_pos;
	priv->first_set = NULL;
	priv->is_terminated = FALSE;
	priv->nullified = cat_ref_ptr(nullified);
	priv->production = cat_ref_ptr(production);
	priv->shifted_normal = NULL;
	priv->shifted_nullified = NULL;
	return result;
}

GroPSymbolSet *grop_dot_state_get_local_first_set(GroPDotState *dot_state) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);
	if (priv->first_set==NULL) {
		priv->first_set = grop_symbol_set_new();

		priv->is_terminated = FALSE;
		int idx;
		int rhs_count = grop_production_rhs_count(priv->production);
		for(idx=priv->dot_pos; idx<rhs_count; idx++) {
			GroPProductionPart *rhs_at = grop_production_rhs_at(priv->production, idx);
			GroPSymbol *symbol = grop_production_part_get_symbol(rhs_at);
			if (GROP_IS_TERMINAL(symbol)) {
				grop_symbol_set_add(priv->first_set, symbol);
				priv->is_terminated = TRUE;
				break;
			} else if (GROP_IS_NON_TERMINAL(symbol)) {
				GroPNonTerminal *nte = (GroPNonTerminal *) symbol;
				grop_symbol_set_add_all(priv->first_set, grop_non_terminal_get_first_set(nte));
				GroPNullable nt_nullable = grop_non_terminal_get_nullable(nte);
				if (nt_nullable == GROP_NULLABLE_TRUE) {
					priv->is_terminated = TRUE;
					break;
				}
			}
		}
	}
	return priv->first_set;
}

GroPProduction *grop_dot_state_get_production(GroPDotState *dot_state) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);
	return priv->production;
}


gboolean grop_dot_state_is_at_end(GroPDotState *dot_state) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);
	int rhs_count = grop_production_rhs_count(priv->production);
	return priv->dot_pos>=rhs_count;
}

gboolean grop_dot_state_is_terminated(GroPDotState *dot_state) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);
	grop_dot_state_get_local_first_set(dot_state);
	return priv->is_terminated;
}


gboolean grop_dot_state_is_left_recursive(GroPDotState *dot_state) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);

	int rhs_count = grop_production_rhs_count(priv->production);
	if (rhs_count==0) {
		return FALSE;
	}
	if (priv->nullified!=NULL) {
		return FALSE;
	}
	int idx = 0;
		GroPSymbol *left_symbol = grop_production_part_get_symbol(grop_production_rhs_at(priv->production, idx));
		GroPSymbol *lhs_symbol = (GroPSymbol *) grop_production_get_lhs(priv->production);
		if (left_symbol==lhs_symbol) {
			return TRUE;
		} else if (GROP_IS_NON_TERMINAL(left_symbol)) {
			GroPNonTerminal *nte = (GroPNonTerminal *) left_symbol;
			GroPSymbolSet *nt_first_set = grop_non_terminal_get_first_set(nte);

			if (grop_symbol_set_contains(nt_first_set, lhs_symbol)) {
				return TRUE;
			}
			if (grop_non_terminal_get_nullable(nte)!=GROP_NULLABLE_TRUE) {
				return FALSE;
			}
		} else {
			return FALSE;
		}
	return FALSE;
}


GroPDotState *grop_dot_state_shift_normal(GroPDotState *dot_state) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);

	if (priv->shifted_normal==NULL) {
		GroPDotState *sdot_state = NULL;
		if (!grop_dot_state_is_at_end(dot_state)) {
			sdot_state = grop_dot_state_new(priv->production, priv->dot_pos+1, priv->nullified);
		}
		priv->shifted_normal = sdot_state;
	}
	return priv->shifted_normal;
}



GroPDotState *grop_dot_state_shift_nullify(GroPDotState *dot_state) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);

	if (priv->shifted_nullified==NULL) {
		GroPDotState *sdot_state = NULL;
		if (!grop_dot_state_is_at_end(dot_state)) {

			CatIntArrayWo *next_nullified = NULL;
			if (priv->dot_pos<grop_production_rhs_count(priv->production)) {
				if (priv->nullified==NULL) {
					next_nullified = cat_int_array_wo_new();
				} else {
					next_nullified = cat_int_array_wo_clone(priv->nullified, CAT_CLONE_DEPTH_MAIN);
				}
				cat_int_array_wo_append(next_nullified, priv->dot_pos);
			}

			sdot_state = grop_dot_state_new(priv->production, priv->dot_pos+1, next_nullified);
			cat_unref_ptr(next_nullified);
		}
		priv->shifted_nullified = sdot_state;
	}
	return priv->shifted_nullified;
}

GroPSymbol *grop_dot_state_get_symbol_at_dot(GroPDotState *dot_state) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);

	if (grop_dot_state_is_at_end(dot_state)) {
		return NULL;
	}
	GroPProductionPart *part_at = grop_production_rhs_at(priv->production, priv->dot_pos);
	return grop_production_part_get_symbol(part_at);
}


gboolean grop_dot_state_is_nullified(GroPDotState *dot_state, int dotPos) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);
	if (priv->nullified == NULL) {
		return FALSE;
	}
	int idx;
	for(idx=0; idx<cat_int_array_wo_size(priv->nullified); idx++) {
		int s = cat_int_array_wo_get(priv->nullified, idx);
		if (s==priv->dot_pos) {
			return TRUE;
		}
	}
	return FALSE;
}

int grop_dot_state_hash(GroPDotState *dot_state) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);
	return grop_production_get_id(priv->production)*13 + priv->dot_pos*117;
}

gboolean grop_dot_state_equal(const GroPDotState *dot_state_a, const GroPDotState *dot_state_b) {
	if (dot_state_a == dot_state_b) {
		return TRUE;
	} else if ((dot_state_a==NULL) ||  (dot_state_b==NULL)) {
		return FALSE;
	}
	GroPDotStatePrivate *priv_a = grop_dot_state_get_instance_private((GroPDotState *) dot_state_a);
	GroPDotStatePrivate *priv_b = grop_dot_state_get_instance_private((GroPDotState *) dot_state_b);
	return (priv_a->dot_pos==priv_b->dot_pos) && (priv_a->production==priv_b->production) &&
			cat_int_array_wo_equal(priv_a->nullified, priv_b->nullified);
}


/********************* start CatIStringable implementation *********************/

static void l_prefix(GroPDotState *dot_state, CatStringWo *buf) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);
	cat_string_wo_append_char(buf, '[');
	int idx;
	for(idx=0; idx<priv->dot_pos; idx++) {
		GroPProductionPart *part_at = grop_production_rhs_at(priv->production, idx);
		if (idx!=0) {
			cat_string_wo_append_char(buf, ' ');
		}
		gboolean isNullified = grop_dot_state_is_nullified(dot_state, idx);
		if (isNullified) {
			cat_string_wo_append_char(buf, '~');
		}
		cat_string_wo_format(buf, "%O", part_at);
	}
}

static void l_postfix(GroPDotState *dot_state, CatStringWo *buf) {
	GroPDotStatePrivate *priv = grop_dot_state_get_instance_private(dot_state);
	int rhs_count = grop_production_rhs_count(priv->production);
	if (rhs_count==0) {
		cat_string_wo_append_chars(buf, "∅");
	}
	int idx;
	for(idx=priv->dot_pos; idx<rhs_count; idx++) {
		GroPProductionPart *part_at = grop_production_rhs_at(priv->production, idx);
		if (idx!=priv->dot_pos){
			cat_string_wo_append_char(buf, ' ');
		}
		gboolean isNullified = grop_dot_state_is_nullified(dot_state, idx);
		if (isNullified) {
			cat_string_wo_append_char(buf, '~');
		}
		cat_string_wo_format(buf, "%O", part_at);
	}
	cat_string_wo_append_chars(buf, " ⇒ ");
	cat_string_wo_append(buf, grop_symbol_get_name((GroPSymbol *) grop_production_get_lhs(priv->production)));

	if (grop_dot_state_is_left_recursive(dot_state)) {
		cat_string_wo_append_chars(buf, " (left-rec)");
	}
	cat_string_wo_append_char(buf, ']');
}

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPDotState *instance = GROP_DOT_STATE(self);
	l_prefix(instance, append_to);
	cat_string_wo_append_chars(append_to, "⚫");
	l_postfix(instance, append_to);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
