/*
   File:    gropproductionpartlist.h
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

#ifndef MODEL_GROPPRODUCTIONPARTLIST_H_
#define MODEL_GROPPRODUCTIONPARTLIST_H_

#include "gropproductionpart.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_PRODUCTION_PART_LIST              (grop_production_part_list_get_type())
#define GROP_PRODUCTION_PART_LIST(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_production_part_list_get_type(), GroPProductionPartList))
#define GROP_PRODUCTION_PART_LIST_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_PRODUCTION_PART_LIST, GroPProductionPartListClass))
#define GROP_IS_PRODUCTION_PART_LIST(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_PRODUCTION_PART_LIST))
#define GROP_IS_PRODUCTION_PART_LIST_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_PRODUCTION_PART_LIST))
#define GROP_PRODUCTION_PART_LIST_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_PRODUCTION_PART_LIST, GroPProductionPartListClass))


typedef struct _GroPProductionPartList               GroPProductionPartList;
typedef struct _GroPProductionPartListPrivate        GroPProductionPartListPrivate;
typedef struct _GroPProductionPartListClass          GroPProductionPartListClass;


struct _GroPProductionPartList {
	GObject parent;
};

struct _GroPProductionPartListClass {
	GObjectClass parent_class;
};


GType grop_production_part_list_get_type();

GroPProductionPartList *grop_production_part_list_new(int offset, CatStringWo *label);
GroPProductionPartList *grop_production_part_list_duplicate(GroPProductionPartList *source);

GroPProductionPart *grop_production_part_list_get_single_part(GroPProductionPartList *pp_list);

void grop_production_part_list_add(GroPProductionPartList *pp_list, GroPProductionPart *sym_part);

void grop_production_part_list_exclude(GroPProductionPartList *pp_list, GroPProductionPart *sym_part);


int grop_production_part_list_get_offset(GroPProductionPartList *pp_list);
CatStringWo *grop_production_part_list_get_label(GroPProductionPartList *pp_list);
CatArrayWo *grop_production_part_list_get_list(GroPProductionPartList *pp_list);
CatArrayWo *grop_production_part_list_get_excluded(GroPProductionPartList *pp_list);


G_END_DECLS

#endif /* MODEL_GROPPRODUCTIONPARTLIST_H_ */
