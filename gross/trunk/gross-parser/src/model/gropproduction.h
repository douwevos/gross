/*
   File:    gropproduction.h
   Project: gross-parser
   Author:  Douwe Vos
   Date:    Mar 17, 2017
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

#ifndef MACHINE_GROPPRODUCTION_H_
#define MACHINE_GROPPRODUCTION_H_

#include "gropproductionpart.h"
#include "gropterminal.h"
#include "gropnonterminal.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_PRODUCTION              (grop_production_get_type())
#define GROP_PRODUCTION(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_production_get_type(), GroPProduction))
#define GROP_PRODUCTION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_PRODUCTION, GroPProductionClass))
#define GROP_IS_PRODUCTION(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_PRODUCTION))
#define GROP_IS_PRODUCTION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_PRODUCTION))
#define GROP_PRODUCTION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_PRODUCTION, GroPProductionClass))


typedef struct _GroPProduction               GroPProduction;
typedef struct _GroPProductionPrivate        GroPProductionPrivate;
typedef struct _GroPProductionClass          GroPProductionClass;


struct _GroPProduction {
	GObject parent;
};

struct _GroPProductionClass {
	GObjectClass parent_class;
};


GType grop_production_get_type();

GroPProduction *grop_production_new(CatInteger *prod_id, int offset, CatStringWo *label, GroPNonTerminal *lhs, CatArrayWo *rhs_parts, CatArrayWo *excluded_rhs_parts);

int grop_production_get_id(GroPProduction *production);

GroPNonTerminal *grop_production_get_lhs(GroPProduction *production);

GroPNullable grop_production_calculate_nullabilty(GroPProduction *production);

int grop_production_rhs_count(GroPProduction *production);
GroPProductionPart *grop_production_rhs_at(GroPProduction *production, int idx);
CatIIterator *grop_production_iterator(GroPProduction *production);

int grop_production_hash(GroPProduction *production);
gboolean grop_production_equal(const GroPProduction *production_a, const GroPProduction *production_b);

G_END_DECLS

#endif /* MACHINE_GROPPRODUCTION_H_ */
