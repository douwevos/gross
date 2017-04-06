/*
   File:    gropsymbolkey.c
   Project: gross-parser
   Author:  Douwe Vos
   Date:    Mar 20, 2017
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

#include "gropsymbolkey.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "GroPSymbolKey"
#include <logging/catlog.h>

struct _GroPSymbolKeyPrivate {
	GroPSymbol *symbol;
	gboolean is_nullified;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPSymbolKey, grop_symbol_key, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPSymbolKey)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_symbol_key_class_init(GroPSymbolKeyClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_symbol_key_init(GroPSymbolKey *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//	GroPSymbolKey *instance = GROP_SYMBOL_KEY(object);
//	GroPSymbolKeyPrivate *priv = grop_symbol_key_get_instance_private(instance);
	G_OBJECT_CLASS(grop_symbol_key_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_symbol_key_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPSymbolKey *grop_symbol_key_new(GroPSymbol *symbol, gboolean is_nullified) {
	GroPSymbolKey *result = g_object_new(GROP_TYPE_SYMBOL_KEY, NULL);
	cat_ref_anounce(result);
	GroPSymbolKeyPrivate *priv = grop_symbol_key_get_instance_private(result);
	priv->symbol = cat_ref_ptr(symbol);
	priv->is_nullified = is_nullified;
	return result;
}

GroPSymbol *grop_symbol_key_get_symbol(GroPSymbolKey *symbol_key) {
	GroPSymbolKeyPrivate *priv = grop_symbol_key_get_instance_private(symbol_key);
	return priv->symbol;
}

int grop_symbol_key_hash(GroPSymbolKey *symbol_key) {
	GroPSymbolKeyPrivate *priv = grop_symbol_key_get_instance_private(symbol_key);
	return grop_symbol_hash(priv->symbol) + (priv->is_nullified ? 13 : 7);
}

gboolean grop_symbol_key_equal(const GroPSymbolKey *symbol_key_a, const GroPSymbolKey *symbol_key_b) {
	if (symbol_key_a == symbol_key_b) {
		return TRUE;
	} else if ((symbol_key_a==NULL) || (symbol_key_b==NULL)) {
		return FALSE;
	}
	GroPSymbolKeyPrivate *priv_a = grop_symbol_key_get_instance_private((GroPSymbolKey *) symbol_key_a);
	GroPSymbolKeyPrivate *priv_b = grop_symbol_key_get_instance_private((GroPSymbolKey *) symbol_key_b);
	return (priv_a->is_nullified==priv_b->is_nullified) && grop_symbol_equal(priv_a->symbol, priv_b->symbol);
}

/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPSymbolKey *instance = GROP_SYMBOL_KEY(self);
	GroPSymbolKeyPrivate *priv = grop_symbol_key_get_instance_private(instance);
	cat_string_wo_append_char(append_to, priv->is_nullified ? '-' : '+');
	cat_string_wo_append(append_to, grop_symbol_get_name(priv->symbol));
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
