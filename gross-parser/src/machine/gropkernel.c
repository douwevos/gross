/*
   File:    gropkernel.c
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

#include "gropkernel.h"
#include "gropdotstate.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "GroPKernel"
#include <logging/catlog.h>

struct _GroPKernelPrivate {
	int id;
	CatHashMapWo *main;	// <DotState, DotLink>
	GroPSymbolSet *lookahead;
	CatInteger *hash;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPKernel, grop_kernel, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPKernel)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_kernel_class_init(GroPKernelClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_kernel_init(GroPKernel *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	GroPKernel *instance = GROP_KERNEL(object);
	GroPKernelPrivate *priv = grop_kernel_get_instance_private(instance);
	cat_unref_ptr(priv->hash);
	cat_unref_ptr(priv->lookahead);
	cat_unref_ptr(priv->main);
	G_OBJECT_CLASS(grop_kernel_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_kernel_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPKernel *grop_kernel_new(int id) {
	GroPKernel *result = g_object_new(GROP_TYPE_KERNEL, NULL);
	cat_ref_anounce(result);
	GroPKernelPrivate *priv = grop_kernel_get_instance_private(result);
	priv->id = id;
	priv->main = cat_hash_map_wo_new((GHashFunc) grop_dot_state_hash, (GEqualFunc) grop_dot_state_equal);
	priv->lookahead = NULL;
	priv->hash = NULL;
	return result;
}

int grop_kernel_get_id(GroPKernel *kernel) {
	GroPKernelPrivate *priv = grop_kernel_get_instance_private(kernel);
	return priv->id;
}


int grop_kernel_size(GroPKernel *kernel) {
	GroPKernelPrivate *priv = grop_kernel_get_instance_private(kernel);
	return cat_hash_map_wo_size(priv->main);
}


gboolean grop_kernel_add(GroPKernel *kernel, GroPDotLink *dot_link) {
	GroPKernelPrivate *priv = grop_kernel_get_instance_private(kernel);
	if (dot_link==NULL) {
		cat_log_fatal("dot link NULL");
		return FALSE;
	}

	gboolean result = FALSE;
	if (cat_hash_map_wo_put(priv->main, (GObject *) grop_dot_link_get_dot_state(dot_link), (GObject *) dot_link)) {
		cat_unref_ptr(priv->hash);
		cat_unref_ptr(priv->lookahead);
		result = TRUE;
	}
	return result;
}

CatIIterator *grop_kernel_iterator(GroPKernel *kernel) {
	GroPKernelPrivate *priv = grop_kernel_get_instance_private(kernel);
	CatArrayWo *values = cat_hash_map_wo_enlist_values(priv->main, NULL);
	CatIIterator *result = cat_array_wo_iterator(values);
	cat_unref_ptr(values);
	return result;
}


int grop_kernel_hash(GroPKernel *kernel) {
	GroPKernelPrivate *priv = grop_kernel_get_instance_private(kernel);
	if (priv->hash==NULL) {
		int val = 0;
		CatArrayWo *main_keys = cat_hash_map_wo_enlist_keys(priv->main, NULL);
		CatIIterator *ds_iter = cat_array_wo_iterator(main_keys);
		while(cat_iiterator_has_next(ds_iter)) {
			GroPDotState *dot_state = (GroPDotState *) cat_iiterator_next(ds_iter);
			val = val*273 + grop_dot_state_hash(dot_state)*12;
		}
		cat_unref_ptr(ds_iter);
		priv->hash = cat_integer_new(val);
	}
	return cat_integer_value(priv->hash);
}

gboolean grop_kernel_equal(const GroPKernel *kernel_a, const GroPKernel *kernel_b) {
	if (kernel_a==kernel_b) {
		return TRUE;
	} else if ((kernel_a==NULL) || (kernel_b==NULL)) {
		return FALSE;
	}
	GroPKernelPrivate *priv_a = grop_kernel_get_instance_private((GroPKernel *) kernel_a);
	GroPKernelPrivate *priv_b = grop_kernel_get_instance_private((GroPKernel *) kernel_b);
	if (cat_hash_map_wo_size(priv_a->main)!=cat_hash_map_wo_size(priv_b->main)) {
		return FALSE;
	}
	gboolean result = TRUE;
	CatArrayWo *keys_a = cat_hash_map_wo_enlist_keys(priv_a->main, NULL);
	CatIIterator *a_iter = cat_array_wo_iterator(keys_a);
	while(cat_iiterator_has_next(a_iter)) {
		GroPDotState *key_a = (GroPDotState *) cat_iiterator_next(a_iter);
		if (cat_hash_map_wo_get(priv_b->main, key_a)==NULL) {
			result = FALSE;
			break;
		}
	}
	cat_unref_ptr(a_iter);
	return result;
}



/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPKernel *instance = GROP_KERNEL(self);
	GroPKernelPrivate *priv = grop_kernel_get_instance_private(instance);
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);

	cat_string_wo_format(append_to, "%s[%p id=%d]", iname, self, priv->id);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
