/*
   File:    gropproduction.c
   Project: gross-parser
   Author:  Douwe Vos
   Date:    Mar 17, 2017
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

#include "gropproduction.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "GroPProduction"
#include <logging/catlog.h>

struct _GroPProductionPrivate {
	CatInteger *id;
	GroPNonTerminal *lhs;
	int offset;
	CatStringWo *label;
	CatArrayWo *parts;
	CatArrayWo *excluded_parts;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPProduction, grop_production, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPProduction)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_production_class_init(GroPProductionClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_production_init(GroPProduction *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	cat_stacktrace_print();
	GroPProduction *instance = GROP_PRODUCTION(object);
	GroPProductionPrivate *priv = grop_production_get_instance_private(instance);
	cat_unref_ptr(priv->excluded_parts);
	cat_unref_ptr(priv->id);
	cat_unref_ptr(priv->label);
	cat_unref_ptr(priv->lhs);
	cat_unref_ptr(priv->parts);
	G_OBJECT_CLASS(grop_production_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_production_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}

GroPProduction *grop_production_new(CatInteger *prod_id, int offset, CatStringWo *label, GroPNonTerminal *lhs, CatArrayWo *rhs_parts, CatArrayWo *excluded_rhs_parts) {
	GroPProduction *result = g_object_new(GROP_TYPE_PRODUCTION, NULL);
	cat_ref_anounce(result);
	GroPProductionPrivate *priv = grop_production_get_instance_private(result);
	cat_ref_ptr(result);
	cat_ref_ptr(result);
	cat_ref_ptr(result);
	cat_ref_ptr(result);
	priv->id = cat_ref_ptr(prod_id);
	cat_log_detail("error:%p, id=%O", result, prod_id);
	priv->offset = offset;
	priv->label = cat_ref_ptr(label);
	priv->lhs = cat_ref_ptr(lhs);
	priv->parts = cat_array_wo_clone(rhs_parts, CAT_CLONE_DEPTH_NONE);
	priv->excluded_parts = cat_array_wo_clone(excluded_rhs_parts, CAT_CLONE_DEPTH_NONE);
	return result;
}

int grop_production_get_id(GroPProduction *production) {
	GroPProductionPrivate *priv = grop_production_get_instance_private(production);
	return cat_integer_value(priv->id);
}

GroPNonTerminal *grop_production_get_lhs(GroPProduction *production) {
	GroPProductionPrivate *priv = grop_production_get_instance_private(production);
	return priv->lhs;
}

GroPNullable grop_production_calculate_nullabilty(GroPProduction *production) {
	GroPProductionPrivate *priv = grop_production_get_instance_private(production);
	GroPNullable result = GROP_NULLABLE_TRUE;
	CatIIterator *pp_iter = cat_array_wo_iterator(priv->parts);
	while(cat_iiterator_has_next(pp_iter)) {
		GroPProductionPart *pp = (GroPProductionPart *) cat_iiterator_next(pp_iter);
		GroPSymbol *pp_sym = grop_production_part_get_symbol(pp);
		if (GROP_IS_TERMINAL(pp_sym)) {
			result = GROP_NULLABLE_FALSE;
			break;
		} else if (GROP_IS_NON_TERMINAL(pp_sym)) {
			GroPNonTerminal *nte = (GroPNonTerminal *) pp_sym;
			GroPNullable nt_nullable = grop_non_terminal_get_nullable(nte);
			if (nt_nullable == GROP_NULLABLE_UNKNOWN) {
				result = GROP_NULLABLE_UNKNOWN;
			} else if (nt_nullable == GROP_NULLABLE_FALSE) {
				result = GROP_NULLABLE_FALSE;
				break;
			}
		}
	}
	cat_unref_ptr(pp_iter);
	return result;
}

int grop_production_rhs_count(GroPProduction *production) {
	GroPProductionPrivate *priv = grop_production_get_instance_private(production);
	return cat_array_wo_size(priv->parts);
}

GroPProductionPart *grop_production_rhs_at(GroPProduction *production, int idx) {
	GroPProductionPrivate *priv = grop_production_get_instance_private(production);
	return (GroPProductionPart *) cat_array_wo_get(priv->parts, idx);
}

CatIIterator *grop_production_iterator(GroPProduction *production) {
	GroPProductionPrivate *priv = grop_production_get_instance_private(production);
	return cat_array_wo_iterator(priv->parts);
}

int grop_production_hash(GroPProduction *production) {
	GroPProductionPrivate *priv = grop_production_get_instance_private(production);
	return cat_integer_value(priv->id);
}

gboolean grop_production_equal(const GroPProduction *production_a, const GroPProduction *production_b) {
	return production_a == production_b;
}


/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPProduction *instance = GROP_PRODUCTION(self);
	GroPProductionPrivate *priv = grop_production_get_instance_private(instance);

	gboolean first = TRUE;
	CatIIterator *parts_iter = cat_array_wo_iterator(priv->parts);
	while(cat_iiterator_has_next(parts_iter)) {
		if (first) {
			first = FALSE;
		} else {
			cat_string_wo_append_char(append_to, ' ');
		}
		GroPProductionPart *ppart = (GroPProductionPart *) cat_iiterator_next(parts_iter);
		GroPSymbol *pp_sym = grop_production_part_get_symbol(ppart);
		cat_string_wo_append(append_to, grop_symbol_get_name(pp_sym));
	}
	cat_unref_ptr(parts_iter);

	cat_string_wo_append_chars(append_to, "⇒");
	cat_string_wo_append(append_to, grop_symbol_get_name((GroPSymbol *) priv->lhs));
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/

