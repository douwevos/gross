/*
   File:    gropproductionpart.c
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

#include "gropproductionpart.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "GroPProductionPart"
#include <logging/catlog.h>

struct _GroPProductionPartPrivate {
	GroPSymbol *symbol;
	CatStringWo *label;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPProductionPart, grop_production_part, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPProductionPart)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_production_part_class_init(GroPProductionPartClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_production_part_init(GroPProductionPart *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	GroPProductionPart *instance = GROP_PRODUCTION_PART(object);
	GroPProductionPartPrivate *priv = grop_production_part_get_instance_private(instance);
	cat_unref_ptr(priv->label);
	cat_unref_ptr(priv->symbol);
	G_OBJECT_CLASS(grop_production_part_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_production_part_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}

GroPProductionPart *grop_production_part_new(GroPSymbol *symbol, CatStringWo *label) {
	GroPProductionPart *result = g_object_new(GROP_TYPE_PRODUCTION_PART, NULL);
	cat_ref_anounce(result);
	GroPProductionPartPrivate *priv = grop_production_part_get_instance_private(result);
	priv->symbol = cat_ref_ptr(symbol);
	priv->label = cat_ref_ptr(label);
	return result;
}

GroPSymbol *grop_production_part_get_symbol(GroPProductionPart *prod_part) {
	GroPProductionPartPrivate *priv = grop_production_part_get_instance_private(prod_part);
	return priv->symbol;
}

CatStringWo *grop_production_part_get_label(GroPProductionPart *prod_part) {
	GroPProductionPartPrivate *priv = grop_production_part_get_instance_private(prod_part);
	return priv->label;
}

int grop_production_part_hash(GroPProductionPart *prod_part){
	GroPProductionPartPrivate *priv = grop_production_part_get_instance_private(prod_part);
	return grop_symbol_hash(priv->symbol);
}

gboolean grop_production_part_equal(const GroPProductionPart *prod_part_a, const GroPProductionPart *prod_part_b) {
	if (prod_part_a==prod_part_b) {
		return TRUE;
	} else if ((prod_part_a==NULL) || (prod_part_b==NULL)) {
		return FALSE;
	}
	GroPProductionPartPrivate *priv_a = grop_production_part_get_instance_private((GroPProductionPart *) prod_part_a);
	GroPProductionPartPrivate *priv_b = grop_production_part_get_instance_private((GroPProductionPart *) prod_part_b);
	return priv_a->symbol==priv_b->symbol;
}

/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPProductionPart *instance = GROP_PRODUCTION_PART(self);
	GroPProductionPartPrivate *priv = grop_production_part_get_instance_private(instance);
	if (priv->symbol) {
		cat_string_wo_append(append_to, grop_symbol_get_name(priv->symbol));
	} else {
		cat_string_wo_format(append_to, "<nil>");
	}
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/

