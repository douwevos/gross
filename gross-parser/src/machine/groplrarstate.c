/*
   File:    groplrarstate.c
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

#include "groplrarstate.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "GroPLrarState"
#include <logging/catlog.h>

struct _GroPLrarStatePrivate {
	GroPKernel *kernel;
	int id;
	CatHashMapWo *transition_map;		// <Symbol, TransitionsForSymbol>
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPLrarState, grop_lrar_state, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPLrarState)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_lrar_state_class_init(GroPLrarStateClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_lrar_state_init(GroPLrarState *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	GroPLrarState *instance = GROP_LRAR_STATE(object);
	GroPLrarStatePrivate *priv = grop_lrar_state_get_instance_private(instance);
	cat_unref_ptr(priv->kernel);
	cat_unref_ptr(priv->transition_map);
	G_OBJECT_CLASS(grop_lrar_state_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_lrar_state_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPLrarState *grop_lrar_state_new(GroPKernel *kernel, int id) {
	GroPLrarState *result = g_object_new(GROP_TYPE_LRAR_STATE, NULL);
	cat_ref_anounce(result);
	GroPLrarStatePrivate *priv = grop_lrar_state_get_instance_private(result);
	priv->id = id;
	priv->kernel = cat_ref_ptr(kernel);
	priv->transition_map = cat_hash_map_wo_new((GHashFunc) grop_symbol_hash, (GEqualFunc) grop_symbol_equal);
	return result;
}

/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPLrarState *instance = GROP_LRAR_STATE(self);
	GroPLrarStatePrivate *priv = grop_lrar_state_get_instance_private(instance);
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);

	cat_string_wo_format(append_to, "%s[%p kernel=%O]", iname, self, priv->kernel);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
