/*
   File:    gropdotlink.c
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

#include "gropdotlink.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "GroPDotLink"
#include <logging/catlog.h>

struct _GroPDotLinkPrivate {
	GroPDotState *dot_state;
	CatHashSet *referred_by;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPDotLink, grop_dot_link, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPDotLink)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_dot_link_class_init(GroPDotLinkClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_dot_link_init(GroPDotLink *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	GroPDotLink *instance = GROP_DOT_LINK(object);
	GroPDotLinkPrivate *priv = grop_dot_link_get_instance_private(instance);
	cat_unref_ptr(priv->dot_state);
	cat_unref_ptr(priv->referred_by);
	G_OBJECT_CLASS(grop_dot_link_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_dot_link_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPDotLink *grop_dot_link_new(GroPDotState *dot_state) {
	GroPDotLink *result = g_object_new(GROP_TYPE_DOT_LINK, NULL);
	cat_ref_anounce(result);
	GroPDotLinkPrivate *priv = grop_dot_link_get_instance_private(result);
	priv->dot_state = cat_ref_ptr(dot_state);
	priv->referred_by = cat_hash_set_new((GHashFunc) grop_dot_state_hash, (GEqualFunc) grop_dot_state_equal);
	return result;
}

GroPDotState *grop_dot_link_get_dot_state(GroPDotLink *dot_link) {
	GroPDotLinkPrivate *priv = grop_dot_link_get_instance_private(dot_link);
	return priv->dot_state;
}

gboolean grop_dot_link_add_referred_by_state(GroPDotLink *dot_link, GroPDotState *by) {
	GroPDotLinkPrivate *priv = grop_dot_link_get_instance_private(dot_link);
	GObject *old = cat_hash_set_add(priv->referred_by, (GObject *) by);
	if (old) {
		return FALSE;
	}
	return TRUE;
}

gboolean grop_dot_link_add_referred_by_link(GroPDotLink *dot_link, GroPDotLink *by) {
	GroPDotLinkPrivate *priv = grop_dot_link_get_instance_private(dot_link);
	GroPDotLinkPrivate *priv_by = grop_dot_link_get_instance_private(by);
	return cat_hash_set_add_all(priv->referred_by, priv_by->referred_by);
}


/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	GroPDotLink *instance = GROP_DOT_LINK(self);
	GroPDotLinkPrivate *priv = grop_dot_link_get_instance_private(instance);
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);

	cat_string_wo_format(append_to, "%s[%p: %O]", iname, self, priv->dot_state);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
