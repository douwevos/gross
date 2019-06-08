/*
   File:    gropbuildentry.c
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

#include "gropbuildentry.h"
#include "gropkernel.h"
#include "groplrarstate.h"
#include "gropsymbolkey.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "GroPBuildEntry"
#include <logging/catlog.h>

struct _GroPBuildEntryPrivate {
	int id;
	GroPKernel *kernel;
	CatHashMapWo *forward_map;	// <SymbolKey, Kernel>
	CatHashMapWo *non_closed_map;	// <SymbolKey, Kernel>
	GroPLrarState *state;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPBuildEntry, grop_build_entry, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPBuildEntry)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_build_entry_class_init(GroPBuildEntryClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_build_entry_init(GroPBuildEntry *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	GroPBuildEntry *instance = GROP_BUILD_ENTRY(object);
	GroPBuildEntryPrivate *priv = grop_build_entry_get_instance_private(instance);
	cat_unref_ptr(priv->kernel);
	cat_unref_ptr(priv->forward_map);
	cat_unref_ptr(priv->non_closed_map);
	cat_unref_ptr(priv->state);
	G_OBJECT_CLASS(grop_build_entry_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_build_entry_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}

GroPBuildEntry *grop_build_entry_new(GroPKernel *main_dot_set, int id) {
	GroPBuildEntry *result = g_object_new(GROP_TYPE_BUILD_ENTRY, NULL);
	cat_ref_anounce(result);
	GroPBuildEntryPrivate *priv = grop_build_entry_get_instance_private(result);
	if (!GROP_IS_KERNEL(main_dot_set)) {
		cat_log_error("wrong here");
		cat_stacktrace_print();
	}
	priv->kernel = cat_ref_ptr(main_dot_set);
	priv->id = id;
	priv->forward_map = cat_hash_map_wo_new((GHashFunc) grop_symbol_key_hash, (GEqualFunc) grop_symbol_key_equal);
	return result;
}

GroPKernel *grop_build_entry_get_kernel(GroPBuildEntry *build_entry) {
	GroPBuildEntryPrivate *priv = grop_build_entry_get_instance_private(build_entry);
	return priv->kernel;
}


int grop_build_entry_get_id(GroPBuildEntry *build_entry) {
	GroPBuildEntryPrivate *priv = grop_build_entry_get_instance_private(build_entry);
	return priv->id;
}


CatHashMapWo *grop_build_entry_get_forward_map(GroPBuildEntry *build_entry) {
	GroPBuildEntryPrivate *priv = grop_build_entry_get_instance_private(build_entry);
	return priv->forward_map;
}


/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPBuildEntry *instance = GROP_BUILD_ENTRY(self);
	GroPBuildEntryPrivate *priv = grop_build_entry_get_instance_private(instance);
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);

	cat_string_wo_format(append_to, "%s[%p id=%d]", iname, self, priv->id);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
