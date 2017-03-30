/*
   File:    gropproductionpart.h
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

#ifndef MACHINE_GROPPRODUCTIONPART_H_
#define MACHINE_GROPPRODUCTIONPART_H_

#include "../model/gropsymbol.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_PRODUCTION_PART              (grop_production_part_get_type())
#define GROP_PRODUCTION_PART(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_production_part_get_type(), GroPProductionPart))
#define GROP_PRODUCTION_PART_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_PRODUCTION_PART, GroPProductionPartClass))
#define GROP_IS_PRODUCTION_PART(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_PRODUCTION_PART))
#define GROP_IS_PRODUCTION_PART_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_PRODUCTION_PART))
#define GROP_PRODUCTION_PART_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_PRODUCTION_PART, GroPProductionPartClass))


typedef struct _GroPProductionPart               GroPProductionPart;
typedef struct _GroPProductionPartPrivate        GroPProductionPartPrivate;
typedef struct _GroPProductionPartClass          GroPProductionPartClass;


struct _GroPProductionPart {
	GObject parent;
};

struct _GroPProductionPartClass {
	GObjectClass parent_class;
};


GType grop_production_part_get_type();

GroPProductionPart *grop_production_part_new(GroPSymbol *symbol, CatStringWo *label);

GroPSymbol *grop_production_part_get_symbol(GroPProductionPart *prod_part);
CatStringWo *grop_production_part_get_label(GroPProductionPart *prod_part);

int grop_production_part_hash(GroPProductionPart *prod_part);
gboolean grop_production_part_equal(const GroPProductionPart *prod_part_a, const GroPProductionPart *prod_part_b);

G_END_DECLS

#endif /* MACHINE_GROPPRODUCTIONPART_H_ */
