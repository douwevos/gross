/*
   File:    gropsymbolset.c
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

#include "gropsymbolset.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "GroPSymbolSet"
#include <logging/catlog.h>

struct _GroPSymbolSetPrivate {
	CatHashSet *set;
	CatInteger *hash;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPSymbolSet, grop_symbol_set, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPSymbolSet)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_symbol_set_class_init(GroPSymbolSetClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_symbol_set_init(GroPSymbolSet *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	GroPSymbolSet *instance = GROP_SYMBOL_SET(object);
	GroPSymbolSetPrivate *priv = grop_symbol_set_get_instance_private(instance);
	cat_unref_ptr(priv->set);
	cat_unref_ptr(priv->hash);
	G_OBJECT_CLASS(grop_symbol_set_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_symbol_set_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPSymbolSet *grop_symbol_set_new() {
	GroPSymbolSet *result = g_object_new(GROP_TYPE_SYMBOL_SET, NULL);
	cat_ref_anounce(result);
	GroPSymbolSetPrivate *priv = grop_symbol_set_get_instance_private(result);
	priv->set = cat_hash_set_new((GHashFunc) grop_symbol_hash, (GEqualFunc) grop_symbol_equal);
	priv->hash = NULL;
	return result;
}

gboolean grop_symbol_set_add(GroPSymbolSet *symbol_set, GroPSymbol *sym) {
	GroPSymbolSetPrivate *priv = grop_symbol_set_get_instance_private(symbol_set);
	GObject *old = cat_hash_set_add(priv->set, (GObject *) sym);
	if (old) {
		cat_unref_ptr(old);
		return FALSE;
	}
	cat_unref_ptr(priv->hash);
	return TRUE;
}

gboolean grop_symbol_set_add_all(GroPSymbolSet *symbol_set, GroPSymbolSet *set_to_add) {
	if (set_to_add) {
		return FALSE;
	}
	GroPSymbolSetPrivate *priv = grop_symbol_set_get_instance_private(symbol_set);
	GroPSymbolSetPrivate *priv_b = grop_symbol_set_get_instance_private(set_to_add);
	gboolean result = cat_hash_set_add_all(priv->set, priv_b->set);
	if (result) {
		cat_unref_ptr(priv->hash);
	}
	return result;
}


gboolean grop_symbol_set_is_empty(const GroPSymbolSet *symbol_set) {
	GroPSymbolSetPrivate *priv = grop_symbol_set_get_instance_private((GroPSymbolSet *) symbol_set);
	return cat_hash_set_size(priv->set)==0;
}

gboolean grop_symbol_set_contains(const GroPSymbolSet *symbol_set, GroPSymbol *sym) {
	GroPSymbolSetPrivate *priv = grop_symbol_set_get_instance_private((GroPSymbolSet *) symbol_set);
	return cat_hash_set_get(priv->set, (GObject *) sym)!=NULL;
}


/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPSymbolSet *instance = GROP_SYMBOL_SET(self);
	GroPSymbolSetPrivate *priv = grop_symbol_set_get_instance_private(instance);

	cat_string_wo_append_unichar(append_to, 0x2e28);
	gboolean first = TRUE;
	CatIIterator *sym_iter = cat_hash_set_iterator(priv->set);
	while(cat_iiterator_has_next(sym_iter)) {
		GroPSymbol *sym = (GroPSymbol *) cat_iiterator_next(sym_iter);
		if (first) {
			first = FALSE;
		} else {
			cat_string_wo_append_char(append_to, ',');
		}
		cat_string_wo_append(append_to, grop_symbol_get_name(sym));
	}
	cat_string_wo_append_unichar(append_to, 0x2e29);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
