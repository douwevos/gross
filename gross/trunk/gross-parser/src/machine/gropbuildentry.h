/*
   File:    gropbuildentry.h
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

#ifndef MACHINE_GROPBUILDENTRY_H_
#define MACHINE_GROPBUILDENTRY_H_

#include "gropkernel.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_BUILD_ENTRY              (grop_build_entry_get_type())
#define GROP_BUILD_ENTRY(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_build_entry_get_type(), GroPBuildEntry))
#define GROP_BUILD_ENTRY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_BUILD_ENTRY, GroPBuildEntryClass))
#define GROP_IS_BUILD_ENTRY(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_BUILD_ENTRY))
#define GROP_IS_BUILD_ENTRY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_BUILD_ENTRY))
#define GROP_BUILD_ENTRY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_BUILD_ENTRY, GroPBuildEntryClass))


typedef struct _GroPBuildEntry               GroPBuildEntry;
typedef struct _GroPBuildEntryPrivate        GroPBuildEntryPrivate;
typedef struct _GroPBuildEntryClass          GroPBuildEntryClass;


struct _GroPBuildEntry {
	GObject parent;
};

struct _GroPBuildEntryClass {
	GObjectClass parent_class;
};


GType grop_build_entry_get_type();

GroPBuildEntry *grop_build_entry_new(GroPKernel *main_dot_set, int id);

int grop_build_entry_get_id(GroPBuildEntry *build_entry);

CatHashMapWo *grop_build_entry_get_forward_map(GroPBuildEntry *build_entry);

G_END_DECLS

#endif /* MACHINE_GROPBUILDENTRY_H_ */
