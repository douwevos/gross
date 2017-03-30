/*
   File:    gropmodel.h
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

#ifndef MACHINE_GROPMODEL_H_
#define MACHINE_GROPMODEL_H_

#include "gropterminal.h"
#include "gropnonterminal.h"
#include "gropproduction.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_MODEL              (grop_model_get_type())
#define GROP_MODEL(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_model_get_type(), GroPModel))
#define GROP_MODEL_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_MODEL, GroPModelClass))
#define GROP_IS_MODEL(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_MODEL))
#define GROP_IS_MODEL_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_MODEL))
#define GROP_MODEL_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_MODEL, GroPModelClass))


typedef struct _GroPModel               GroPModel;
typedef struct _GroPModelPrivate        GroPModelPrivate;
typedef struct _GroPModelClass          GroPModelClass;


struct _GroPModel {
	GObject parent;
};

struct _GroPModelClass {
	GObjectClass parent_class;
};


GType grop_model_get_type();

GroPModel *grop_model_new();

GroPTerminal *grop_model_get_eof_terminal(GroPModel *model);
GroPTerminal *grop_model_get_error_terminal(GroPModel *model);

GroPSymbol *grop_model_get_symbol_by_name(GroPModel *model, CatStringWo *name);

GroPNonTerminal *grop_model_add_non_terminal(GroPModel *model, CatStringWo *name);
GroPNonTerminal *grop_model_get_non_terminal_by_name(GroPModel *model, CatStringWo *name);

GroPTerminal *grop_model_addTerminal(GroPModel *model, CatStringWo *name);

GroPProduction *grop_model_add_production(GroPModel *model, GroPNonTerminal *lhs, CatArrayWo /*<ProductionPart> */ *rhs_parts);

GroPProduction *grop_model_add_production_with_excl(GroPModel *model, int offset, CatStringWo *label, GroPNonTerminal *lhs, CatArrayWo *rhs_parts, CatArrayWo *excluded_rhs_parts);

GroPNonTerminal *grop_model_create_sub_non_terminal(GroPModel *model);

GroPNonTerminal *grop_model_add_sub_productions(GroPModel *model, CatArrayWo *sub_pp_arrays);

GroPProduction *grop_model_get_production(GroPModel *model, int index);

void grop_model_calculate_nullabilty(GroPModel *model);
void grop_model_calculate_first_sets(GroPModel *model);

CatIIterator *grop_model_terminal_iterator(GroPModel *model);
CatIIterator *grop_model_non_terminal_iterator(GroPModel *model);
CatArrayWo *grop_model_all_symbols(GroPModel *model);
CatIIterator *grop_model_productions_iterator(GroPModel *model);

G_END_DECLS

#endif /* MACHINE_GROPMODEL_H_ */
