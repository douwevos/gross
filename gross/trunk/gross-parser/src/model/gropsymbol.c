/*
   File:    gropsymbol.c
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

#include "gropsymbol.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "GroPSymbol"
#include <logging/catlog.h>

struct _GroPSymbolPrivate {
	CatStringWo *name;
	CatInteger *id;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPSymbol, grop_symbol, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPSymbol)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_symbol_class_init(GroPSymbolClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_symbol_init(GroPSymbol *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	GroPSymbol *instance = GROP_SYMBOL(object);
	GroPSymbolPrivate *priv = grop_symbol_get_instance_private(instance);
	cat_unref_ptr(priv->name);
	cat_unref_ptr(priv->id);
	G_OBJECT_CLASS(grop_symbol_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_symbol_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


void grop_symbol_construct(GroPSymbol *symbol, CatStringWo *name, CatInteger *id) {
	GroPSymbolPrivate *priv = grop_symbol_get_instance_private(symbol);
	priv->name = cat_ref_ptr(name);
	priv->id = cat_ref_ptr(id);
}

CatStringWo *grop_symbol_get_name(GroPSymbol *symbol) {
	GroPSymbolPrivate *priv = grop_symbol_get_instance_private(symbol);
	return priv->name;
}

CatInteger *grop_symbol_get_id(GroPSymbol *symbol) {
	GroPSymbolPrivate *priv = grop_symbol_get_instance_private(symbol);
	return priv->id;
}

int grop_symbol_hash(const GroPSymbol *symbol) {
	GroPSymbolPrivate *priv = grop_symbol_get_instance_private((GroPSymbol *) symbol);
	return cat_integer_value(priv->id);
}

gboolean grop_symbol_equal(const GroPSymbol *symbol_a, const GroPSymbol *symbol_b) {
	if (symbol_a == symbol_b) {
		return TRUE;
	} else if ((symbol_a == NULL) || (symbol_b == NULL)) {
		return FALSE;
	}
	GroPSymbolPrivate *priv_a = grop_symbol_get_instance_private((GroPSymbol *) symbol_a);
	GroPSymbolPrivate *priv_b = grop_symbol_get_instance_private((GroPSymbol *) symbol_b);
	return priv_a->id == priv_b->id;
}

/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPSymbol *instance = GROP_SYMBOL(self);
	GroPSymbolPrivate *priv = grop_symbol_get_instance_private(instance);
	cat_string_wo_append(append_to, priv->name);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
