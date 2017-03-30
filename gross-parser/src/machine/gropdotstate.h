/*
   File:    gropdotstate.h
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

#ifndef MACHINE_GROPDOTSTATE_H_
#define MACHINE_GROPDOTSTATE_H_

#include "../model/gropsymbol.h"
#include "../model/gropnonterminal.h"
#include "../model/gropproduction.h"
#include "../model/gropsymbolset.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_DOT_STATE              (grop_dot_state_get_type())
#define GROP_DOT_STATE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_dot_state_get_type(), GroPDotState))
#define GROP_DOT_STATE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_DOT_STATE, GroPDotStateClass))
#define GROP_IS_DOT_STATE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_DOT_STATE))
#define GROP_IS_DOT_STATE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_DOT_STATE))
#define GROP_DOT_STATE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_DOT_STATE, GroPDotStateClass))


typedef struct _GroPDotState               GroPDotState;
typedef struct _GroPDotStatePrivate        GroPDotStatePrivate;
typedef struct _GroPDotStateClass          GroPDotStateClass;


struct _GroPDotState {
	GObject parent;
};

struct _GroPDotStateClass {
	GObjectClass parent_class;
};


GType grop_dot_state_get_type();

GroPDotState *grop_dot_state_new(GroPProduction *production, int dot_pos, CatIntArrayWo *nullified);

GroPSymbolSet *grop_dot_state_get_local_first_set(GroPDotState *dot_state);

gboolean grop_dot_state_is_at_end(GroPDotState *dot_state);
gboolean grop_dot_state_is_terminated(GroPDotState *dot_state);
gboolean grop_dot_state_is_nullified(GroPDotState *dot_state, int dotPos);
gboolean grop_dot_state_is_left_recursive(GroPDotState *dot_state);

GroPDotState *grop_dot_state_shift_normal(GroPDotState *dot_state);
GroPDotState *grop_dot_state_shift_nullify(GroPDotState *dot_state);

GroPSymbol *grop_dot_state_get_symbol_at_dot(GroPDotState *dot_state);

int grop_dot_state_hash(GroPDotState *dot_state);
gboolean grop_dot_state_equal(const GroPDotState *dot_state_a, const GroPDotState *dot_state_b);

G_END_DECLS

#endif /* MACHINE_GROPDOTSTATE_H_ */
