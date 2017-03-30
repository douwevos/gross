/*
   File:    gropproductionpartlist.c
   Project: gross-parser
   Author:  Douwe Vos
   Date:    Mar 22, 2017
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

#include "gropproductionpartlist.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "GroPProductionPartList"
#include <logging/catlog.h>

struct _GroPProductionPartListPrivate {
	int offset;
	CatStringWo *label;
	CatArrayWo *list;
	CatArrayWo *excluded;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPProductionPartList, grop_production_part_list, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPProductionPartList)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_production_part_list_class_init(GroPProductionPartListClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_production_part_list_init(GroPProductionPartList *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//	GroPProductionPartList *instance = GROP_PRODUCTION_PART_LIST(object);
//	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(instance);
	G_OBJECT_CLASS(grop_production_part_list_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_production_part_list_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPProductionPartList *grop_production_part_list_new(int offset, CatStringWo *label) {
	GroPProductionPartList *result = g_object_new(GROP_TYPE_PRODUCTION_PART_LIST, NULL);
	cat_ref_anounce(result);
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(result);
	priv->offset = offset;
	priv->label = cat_ref_ptr(label);
	priv->excluded = NULL;
	priv->list = cat_array_wo_new();
	return result;
}

GroPProductionPartList *grop_production_part_list_duplicate(GroPProductionPartList *source) {
	GroPProductionPartList *result = g_object_new(GROP_TYPE_PRODUCTION_PART_LIST, NULL);
	cat_ref_anounce(result);
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(result);
	GroPProductionPartListPrivate *spriv = grop_production_part_list_get_instance_private(source);
	priv->offset = spriv->offset;
	priv->label = cat_ref_ptr(spriv->label);
	priv->list = cat_array_wo_clone(spriv->list, CAT_CLONE_DEPTH_MAIN);
	priv->excluded = cat_array_wo_clone(spriv->excluded, CAT_CLONE_DEPTH_MAIN);
	return result;
}

int grop_production_part_list_get_offset(GroPProductionPartList *pp_list) {
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(pp_list);
	return priv->offset;
}

CatStringWo *grop_production_part_list_get_label(GroPProductionPartList *pp_list) {
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(pp_list);
	return priv->label;
}

CatArrayWo *grop_production_part_list_get_list(GroPProductionPartList *pp_list) {
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(pp_list);
	return priv->list;
}

CatArrayWo *grop_production_part_list_get_excluded(GroPProductionPartList *pp_list) {
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(pp_list);
	return priv->excluded;
}


GroPProductionPart *grop_production_part_list_get_single_part(GroPProductionPartList *pp_list)  {
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(pp_list);
	if ((priv->excluded!=NULL) && (cat_array_wo_size(priv->excluded)>0)) {
		return NULL;
	}
	if (cat_array_wo_size(priv->list)!=1) {
		return NULL;
	}
	return (GroPProductionPart *) cat_array_wo_get_first(priv->list);
}


void grop_production_part_list_add(GroPProductionPartList *pp_list, GroPProductionPart *sym_part) {
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(pp_list);
	cat_array_wo_append(priv->list, (GObject *) sym_part);
}

void grop_production_part_list_exclude(GroPProductionPartList *pp_list, GroPProductionPart *sym_part) {
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(pp_list);
	if (priv->excluded==NULL) {
		priv->excluded = cat_array_wo_new();
	}
	cat_array_wo_append(priv->excluded, (GObject *) sym_part);
}



/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPProductionPartList *instance = GROP_PRODUCTION_PART_LIST(self);
	GroPProductionPartListPrivate *priv = grop_production_part_list_get_instance_private(instance);
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);

	cat_string_wo_format(append_to, "%s[%p %O]", iname, self, priv->list);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/

