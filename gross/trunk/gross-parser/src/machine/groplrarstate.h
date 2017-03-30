/*
   File:    groplrarstate.h
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

#ifndef MACHINE_GROPLRARSTATE_H_
#define MACHINE_GROPLRARSTATE_H_

#include "gropkernel.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_LRAR_STATE              (grop_lrar_state_get_type())
#define GROP_LRAR_STATE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_lrar_state_get_type(), GroPLrarState))
#define GROP_LRAR_STATE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_LRAR_STATE, GroPLrarStateClass))
#define GROP_IS_LRAR_STATE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_LRAR_STATE))
#define GROP_IS_LRAR_STATE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_LRAR_STATE))
#define GROP_LRAR_STATE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_LRAR_STATE, GroPLrarStateClass))


typedef struct _GroPLrarState               GroPLrarState;
typedef struct _GroPLrarStatePrivate        GroPLrarStatePrivate;
typedef struct _GroPLrarStateClass          GroPLrarStateClass;


struct _GroPLrarState {
	GObject parent;
};

struct _GroPLrarStateClass {
	GObjectClass parent_class;
};


GType grop_lrar_state_get_type();

GroPLrarState *grop_lrar_state_new(GroPKernel *kernel, int id);

G_END_DECLS

#endif /* MACHINE_GROPLRARSTATE_H_ */
