/*
   File:    gropdotlink.h
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

#ifndef MACHINE_GROPDOTLINK_H_
#define MACHINE_GROPDOTLINK_H_

#include "gropdotstate.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_DOT_LINK              (grop_dot_link_get_type())
#define GROP_DOT_LINK(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_dot_link_get_type(), GroPDotLink))
#define GROP_DOT_LINK_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_DOT_LINK, GroPDotLinkClass))
#define GROP_IS_DOT_LINK(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_DOT_LINK))
#define GROP_IS_DOT_LINK_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_DOT_LINK))
#define GROP_DOT_LINK_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_DOT_LINK, GroPDotLinkClass))


typedef struct _GroPDotLink               GroPDotLink;
typedef struct _GroPDotLinkPrivate        GroPDotLinkPrivate;
typedef struct _GroPDotLinkClass          GroPDotLinkClass;


struct _GroPDotLink {
	GObject parent;
};

struct _GroPDotLinkClass {
	GObjectClass parent_class;
};


GType grop_dot_link_get_type();

GroPDotLink *grop_dot_link_new(GroPDotState *dot_state);

GroPDotState *grop_dot_link_get_dot_state(GroPDotLink *dot_link);

gboolean grop_dot_link_add_referred_by_state(GroPDotLink *dot_link, GroPDotState *by);
gboolean grop_dot_link_add_referred_by_link(GroPDotLink *dot_link, GroPDotLink *by);

G_END_DECLS

#endif /* MACHINE_GROPDOTLINK_H_ */
