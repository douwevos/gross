/*
   File:    gropmachine.h
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

#ifndef MACHINE_GROPMACHINE_H_
#define MACHINE_GROPMACHINE_H_

#include "gropdotstate.h"
#include "gropdotlink.h"
#include "../model/gropmodel.h"
#include "../groimessagehandler.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_MACHINE              (grop_machine_get_type())
#define GROP_MACHINE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_machine_get_type(), GroPMachine))
#define GROP_MACHINE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_MACHINE, GroPMachineClass))
#define GROP_IS_MACHINE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_MACHINE))
#define GROP_IS_MACHINE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_MACHINE))
#define GROP_MACHINE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_MACHINE, GroPMachineClass))


typedef struct _GroPMachine               GroPMachine;
typedef struct _GroPMachinePrivate        GroPMachinePrivate;
typedef struct _GroPMachineClass          GroPMachineClass;


struct _GroPMachine {
	GObject parent;
};

struct _GroPMachineClass {
	GObjectClass parent_class;
};


GType grop_machine_get_type();

GroPMachine *grop_machine_new(GroIMessageHandler *message_handler, GroPModel *model);
void grop_machine_build(GroPMachine *machine);

GroPDotLink *grop_machine_get_or_create_dot_link(GroPMachine *machine, GroPDotState *dot_state);

G_END_DECLS

#endif /* MACHINE_GROPMACHINE_H_ */
