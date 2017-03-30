/*
   File:    gropmodelbuilder.h
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

#ifndef MODEL_GROPMODELBUILDER_H_
#define MODEL_GROPMODELBUILDER_H_

#include "gropmodel.h"
#include "../groimessagehandler.h"
#include "../../src-gen/ast/groastspec.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_MODEL_BUILDER              (grop_model_builder_get_type())
#define GROP_MODEL_BUILDER(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_model_builder_get_type(), GroPModelBuilder))
#define GROP_MODEL_BUILDER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_MODEL_BUILDER, GroPModelBuilderClass))
#define GROP_IS_MODEL_BUILDER(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_MODEL_BUILDER))
#define GROP_IS_MODEL_BUILDER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_MODEL_BUILDER))
#define GROP_MODEL_BUILDER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_MODEL_BUILDER, GroPModelBuilderClass))


typedef struct _GroPModelBuilder               GroPModelBuilder;
typedef struct _GroPModelBuilderPrivate        GroPModelBuilderPrivate;
typedef struct _GroPModelBuilderClass          GroPModelBuilderClass;


struct _GroPModelBuilder {
	GObject parent;
};

struct _GroPModelBuilderClass {
	GObjectClass parent_class;
};


GType grop_model_builder_get_type();

GroPModelBuilder *grop_model_builder_new(GroAstSpec *specification, GroIMessageHandler *msg_handler);

GroPModel *grop_model_builder_do_build(GroPModelBuilder *builder);

G_END_DECLS

#endif /* MODEL_GROPMODELBUILDER_H_ */
