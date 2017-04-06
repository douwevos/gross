/*
   File:    gropnonterminal.c
   Project: gross-parser
   Author:  Douwe Vos
   Date:    Mar 16, 2017
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

#include "gropnonterminal.h"
#include "gropproduction.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "GroPNonTerminal"
#include <logging/catlog.h>

struct _GroPNonTerminalPrivate {
	GroPNullable nullable;
	CatArrayWo *production_list;
	GroPSymbolSet *first_set;
};

G_DEFINE_TYPE_WITH_CODE(GroPNonTerminal, grop_non_terminal, GROP_TYPE_SYMBOL,
		G_ADD_PRIVATE(GroPNonTerminal)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_non_terminal_class_init(GroPNonTerminalClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_non_terminal_init(GroPNonTerminal *instance) {
}


static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//	GroPNonTerminal *instance = GROP_NON_TERMINAL(object);
//	GroPNonTerminalPrivate *priv = grop_non_terminal_get_instance_private(instance);
	G_OBJECT_CLASS(grop_non_terminal_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_non_terminal_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}
GroPNonTerminal *grop_non_terminal_new(CatStringWo *name, CatInteger *id) {
	GroPNonTerminal *result = g_object_new(GROP_TYPE_NON_TERMINAL, NULL);
	cat_ref_anounce(result);
	grop_symbol_construct((GroPSymbol *) result, name, id);
	GroPNonTerminalPrivate *priv = grop_non_terminal_get_instance_private(result);
	priv->nullable = GROP_NULLABLE_UNKNOWN;
	priv->production_list = cat_array_wo_new();
	priv->first_set = grop_symbol_set_new();
	return result;
}

void grop_non_terminal_add_production(GroPNonTerminal *non_term, struct _GroPProduction *production) {
	GroPNonTerminalPrivate *priv = grop_non_terminal_get_instance_private(non_term);
	cat_array_wo_append(priv->production_list, (GObject *) production);
	if (grop_production_rhs_count(production)==0) {
		priv->nullable = GROP_NULLABLE_TRUE;
	}
}

CatIIterator *grop_non_terminal_iterator(GroPNonTerminal *non_term) {
	GroPNonTerminalPrivate *priv = grop_non_terminal_get_instance_private(non_term);
	return cat_array_wo_iterator(priv->production_list);
}


GroPNullable grop_non_terminal_get_nullable(GroPNonTerminal *non_term) {
	GroPNonTerminalPrivate *priv = grop_non_terminal_get_instance_private(non_term);
	return priv->nullable;
}

void grop_non_terminal_set_nullable(GroPNonTerminal *non_term, GroPNullable nullable) {
	GroPNonTerminalPrivate *priv = grop_non_terminal_get_instance_private(non_term);
	priv->nullable = nullable;
}


GroPNullable grop_non_terminal_calculate_nullabilty(GroPNonTerminal *non_term) {
	GroPNonTerminalPrivate *priv = grop_non_terminal_get_instance_private(non_term);
	if (priv->nullable!=GROP_NULLABLE_UNKNOWN) {
		return priv->nullable;
	}

	priv->nullable = GROP_NULLABLE_TRUE;
	CatIIterator *prod_iter = cat_array_wo_iterator(priv->production_list);
	while(cat_iiterator_has_next(prod_iter)) {
		GroPProduction *production = (GroPProduction *) cat_iiterator_next(prod_iter);
		GroPNullable prod_nullable = grop_production_calculate_nullabilty(production);
		if (prod_nullable == GROP_NULLABLE_TRUE) {
			priv->nullable = GROP_NULLABLE_TRUE;
			break;
		} else if (prod_nullable==GROP_NULLABLE_UNKNOWN) {
			priv->nullable = GROP_NULLABLE_UNKNOWN;
		} else if (prod_nullable==GROP_NULLABLE_FALSE && priv->nullable!=GROP_NULLABLE_UNKNOWN) {
			priv->nullable = GROP_NULLABLE_FALSE;
		}
	}
	cat_unref_ptr(prod_iter);
	return priv->nullable;
}


gboolean grop_non_terminal_compute_first_set(GroPNonTerminal *non_term) {
	GroPNonTerminalPrivate *priv = grop_non_terminal_get_instance_private(non_term);
	gboolean did_change = FALSE;
	CatIIterator *prod_iter = cat_array_wo_iterator(priv->production_list);
	while(cat_iiterator_has_next(prod_iter)) {
		GroPProduction *production = (GroPProduction *) cat_iiterator_next(prod_iter);
		int rhs_count = grop_production_rhs_count(production);
		int rhs_idx;
		for(rhs_idx=0; rhs_idx<rhs_count; rhs_idx++) {
			GroPProductionPart *prod_part = grop_production_rhs_at(production, rhs_idx);
			GroPSymbol *pp_sym = grop_production_part_get_symbol(prod_part);
			cat_log_error("pp_sym=%O", pp_sym);
			if (grop_symbol_set_add(priv->first_set, pp_sym)) {
				did_change = TRUE;
			}
			if (GROP_IS_TERMINAL(pp_sym)) {
				rhs_count = 0;
			} else if (GROP_IS_NON_TERMINAL(pp_sym)) {
				GroPNonTerminal *nt = (GroPNonTerminal *) pp_sym;
				if ((nt!=non_term) && grop_symbol_set_add_all(priv->first_set, grop_non_terminal_get_first_set(nt))) {
					did_change = TRUE;
				}

				if (grop_non_terminal_get_nullable(nt) == GROP_NULLABLE_FALSE) {
					rhs_count = 0;
				}
			}
		}
	}
	cat_unref_ptr(prod_iter);

	return did_change;
}

GroPSymbolSet *grop_non_terminal_get_first_set(GroPNonTerminal *non_term) {
	GroPNonTerminalPrivate *priv = grop_non_terminal_get_instance_private(non_term);
	return priv->first_set;
}
