/*
   File:    gropmodel.c
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

#include "gropmodel.h"
#include "gropproductionpart.h"
#include "gropproductionpartlist.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "GroPModel"
#include <logging/catlog.h>

struct _GroPModelPrivate {
	int sequence;
	CatHashMapWo *symbol_map;
	CatArrayWo *non_term_list;
	CatArrayWo *term_list;
	CatArrayWo *production_list;
	int sub_prod_seq;
	GroPTerminal *eof_terminal;
	GroPTerminal *error_terminal;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPModel, grop_model, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPModel)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_model_class_init(GroPModelClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_model_init(GroPModel *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	GroPModel *instance = GROP_MODEL(object);
	GroPModelPrivate *priv = grop_model_get_instance_private(instance);
	cat_unref_ptr(priv->non_term_list);
	cat_unref_ptr(priv->production_list);
	cat_unref_ptr(priv->symbol_map);
	cat_unref_ptr(priv->term_list);
	G_OBJECT_CLASS(grop_model_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_model_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPModel *grop_model_new() {
	GroPModel *result = g_object_new(GROP_TYPE_MODEL, NULL);
	cat_ref_anounce(result);
	GroPModelPrivate *priv = grop_model_get_instance_private(result);
	priv->sequence = 0;
	priv->sub_prod_seq = 0;
	priv->symbol_map = cat_hash_map_wo_new((GHashFunc) cat_integer_hash, (GEqualFunc) cat_integer_equal);
	priv->non_term_list = cat_array_wo_new();
	priv->term_list = cat_array_wo_new();
	priv->production_list = cat_array_wo_new();
	CatStringWo *tmp = cat_string_wo_new_with("⟧");
	priv->eof_terminal = grop_model_addTerminal(result, tmp);
	cat_unref_ptr(tmp);
	tmp = cat_string_wo_new_with("⊗");
	priv->error_terminal = grop_model_addTerminal(result, tmp);
	cat_unref_ptr(tmp);
	return result;
}

GroPTerminal *grop_model_get_eof_terminal(GroPModel *model) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	return priv->eof_terminal;
}

GroPTerminal *grop_model_get_error_terminal(GroPModel *model) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	return priv->error_terminal;
}

GroPSymbol *grop_model_get_symbol_by_name(GroPModel *model, CatStringWo *name) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	CatIMapIterator *iter = cat_hash_map_wo_iterator(priv->symbol_map);
	CatInteger *key;
	GroPSymbol *symbol = NULL;
	while(cat_imap_iterator_next(iter, (gpointer *) &key, (gpointer *) &symbol)) {
		if (cat_string_wo_equal(grop_symbol_get_name(symbol), name)) {
			break;
		}
	}
	cat_unref_ptr(iter);
	return symbol;
}

GroPNonTerminal *grop_model_add_non_terminal(GroPModel *model, CatStringWo *name) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	CatInteger *new_id = cat_integer_new(priv->sequence++);
	GroPNonTerminal *non_terminal = grop_non_terminal_new(name, new_id);
	cat_hash_map_wo_put(priv->symbol_map, (GObject *) new_id, (GObject *) non_terminal);
	cat_array_wo_append(priv->non_term_list, (GObject *) non_terminal);
	if (cat_array_wo_size(priv->non_term_list)==2) {
		GroPNonTerminal *nt_start = (GroPNonTerminal *) cat_array_wo_get(priv->non_term_list, 0);
		CatArrayWo *parts = cat_array_wo_new();	// <ProductionPart *>
		GroPProductionPart *p1 = grop_production_part_new((GroPSymbol *) non_terminal, NULL);
		GroPProductionPart *p2 = grop_production_part_new((GroPSymbol *) cat_array_wo_get_first(priv->term_list), NULL);
		cat_array_wo_append(parts, (GObject *) p1);
		cat_array_wo_append(parts, (GObject *) p2);
		cat_unref_ptr(p1);
		cat_unref_ptr(p2);
		grop_model_add_production(model, nt_start, parts);
		cat_unref_ptr(parts);
	}
	cat_unref_ptr(new_id);
	cat_unref(non_terminal);
	return non_terminal;
}

GroPNonTerminal *grop_model_get_non_terminal_by_name(GroPModel *model, CatStringWo *name) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	GroPNonTerminal *result = NULL;
	CatIIterator *iter = cat_array_wo_iterator(priv->non_term_list);
	while(cat_iiterator_has_next(iter)) {
		GroPNonTerminal *nt_test = (GroPNonTerminal *) cat_iiterator_next(iter);
		if (cat_string_wo_equal(grop_symbol_get_name((GroPSymbol *) nt_test), name)) {
			result = nt_test;
			break;
		}
	}
	cat_unref_ptr(iter);
	return result;
}


GroPTerminal *grop_model_addTerminal(GroPModel *model, CatStringWo *name) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	CatInteger *new_id = cat_integer_new(priv->sequence++);
	GroPTerminal *terminal = grop_terminal_new(name, new_id);
	cat_hash_map_wo_put(priv->symbol_map, (GObject *) new_id, (GObject *) terminal);
	cat_array_wo_append(priv->term_list, (GObject *) terminal);
	cat_unref(terminal);
	cat_unref_ptr(new_id);
	return terminal;
}
GroPProduction *grop_model_add_production(GroPModel *model, GroPNonTerminal *lhs, CatArrayWo /*<ProductionPart> */ *rhs_parts) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	CatInteger *prod_id = cat_integer_new(cat_array_wo_size(priv->production_list));
	GroPProduction *production = grop_production_new(prod_id, -1, NULL, lhs, rhs_parts, NULL);
	cat_array_wo_append(priv->production_list, (GObject *) production);
	grop_non_terminal_add_production(lhs, production);
	return production;
}

GroPProduction *grop_model_add_production_with_excl(GroPModel *model, int offset, CatStringWo *label, GroPNonTerminal *lhs, CatArrayWo *rhs_parts, CatArrayWo *excluded_rhs_parts) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	CatInteger *prod_id = cat_integer_new(cat_array_wo_size(priv->production_list));
	GroPProduction *production = grop_production_new(prod_id, -1, NULL, lhs, rhs_parts, excluded_rhs_parts);
	cat_array_wo_append(priv->production_list, (GObject *) production);
	grop_non_terminal_add_production(lhs, production);
	return production;
}

GroPNonTerminal *grop_model_create_sub_non_terminal(GroPModel *model) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	CatStringWo *sub_nt_name = cat_string_wo_new();
	cat_string_wo_format(sub_nt_name, "sub_list$%d", priv->sub_prod_seq++);
	GroPNonTerminal *result = grop_model_add_non_terminal(model, sub_nt_name);
	return result;
}

GroPNonTerminal *grop_model_add_sub_productions(GroPModel *model, CatArrayWo *sub_pp_arrays) {
	GroPNonTerminal *lhs = grop_model_create_sub_non_terminal(model);
	CatIIterator *iter = cat_array_wo_iterator(sub_pp_arrays);
	while(cat_iiterator_has_next(iter)) {
		GroPProductionPartList *rhs_parts = (GroPProductionPartList *) cat_iiterator_next(iter);
		CatArrayWo *rhs_parts_list = grop_production_part_list_get_list(rhs_parts);
		CatArrayWo *rhs_parts_excluded = grop_production_part_list_get_excluded(rhs_parts);
		grop_model_add_production_with_excl(model, -1, NULL, lhs, rhs_parts_list, rhs_parts_excluded);
	}
	return lhs;
}


GroPProduction *grop_model_get_production(GroPModel *model, int index) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	return (GroPProduction *) cat_array_wo_get(priv->production_list, index);
}

void grop_model_calculate_nullabilty(GroPModel *model) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	CatHashSet *finished = cat_hash_set_new((GHashFunc) grop_symbol_hash, (GEqualFunc) grop_symbol_equal); // NonTerminalExt
	while(cat_hash_set_size(finished)!=cat_array_wo_size(priv->non_term_list)) {
		int lastFinished = cat_hash_set_size(finished);
		CatIIterator *iter = cat_array_wo_iterator(priv->non_term_list);
		while(cat_iiterator_has_next(iter)) {
			GroPNonTerminal *non_term = (GroPNonTerminal *) cat_iiterator_next(iter);
			if (cat_hash_set_get(finished, (GObject *) non_term)==NULL) {
				if (grop_non_terminal_calculate_nullabilty(non_term)) {
					cat_hash_set_add(finished, (GObject *) non_term);
				}
			}
		}
		cat_unref_ptr(iter);
		if (lastFinished==cat_hash_set_size(finished)) {
			CatStringWo *buf = cat_string_wo_new();
			CatIIterator *nt_iter = cat_array_wo_iterator(priv->non_term_list);
			while(cat_iiterator_has_next(nt_iter)) {
				GroPNonTerminal *non_term = cat_iiterator_next(nt_iter);
				if (cat_hash_set_get(finished, (GObject *) non_term)==NULL) {
					cat_string_wo_format(buf, ",%O", non_term);
				}
			}
			cat_unref_ptr(nt_iter);
			cat_log_error("Not able to calculate nullability for the next non-terminals %O", buf);
			return;
		}
	}
}

void grop_model_calculate_first_sets(GroPModel *model) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	gboolean didChange = TRUE;
	while(didChange) {
		didChange = FALSE;
		CatIIterator *iter = cat_array_wo_iterator(priv->non_term_list);
		while(cat_iiterator_has_next(iter)) {
			GroPNonTerminal *non_term = (GroPNonTerminal *) cat_iiterator_next(iter);
			if (grop_non_terminal_compute_first_set(non_term)) {
				didChange = TRUE;
			}
		}
		cat_unref_ptr(iter);
	}
}


CatIIterator *grop_model_terminal_iterator(GroPModel *model) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	return cat_array_wo_iterator(priv->term_list);
}

CatIIterator *grop_model_non_terminal_iterator(GroPModel *model) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	return cat_array_wo_iterator(priv->non_term_list);
}

CatArrayWo *grop_model_all_symbols(GroPModel *model) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	return cat_hash_map_wo_enlist_values(priv->symbol_map, NULL);
}

CatIIterator *grop_model_productions_iterator(GroPModel *model) {
	GroPModelPrivate *priv = grop_model_get_instance_private(model);
	return cat_array_wo_iterator(priv->production_list);
}


/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);
	cat_string_wo_format(append_to, "%s[%p]", iname, self);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
