/*
   File:    gropterminal.h
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

#ifndef MACHINE_GROPTERMINAL_H_
#define MACHINE_GROPTERMINAL_H_

#include "gropsymbol.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_TERMINAL              (grop_terminal_get_type())
#define GROP_TERMINAL(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_terminal_get_type(), GroPTerminal))
#define GROP_TERMINAL_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_TERMINAL, GroPTerminalClass))
#define GROP_IS_TERMINAL(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_TERMINAL))
#define GROP_IS_TERMINAL_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_TERMINAL))
#define GROP_TERMINAL_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_TERMINAL, GroPTerminalClass))


typedef struct _GroPTerminal               GroPTerminal;
typedef struct _GroPTerminalClass          GroPTerminalClass;


struct _GroPTerminal {
	GroPSymbol parent;
};

struct _GroPTerminalClass {
	GroPSymbolClass parent_class;
};


GType grop_terminal_get_type();

GroPTerminal *grop_terminal_new(CatStringWo *name, CatInteger *id);

G_END_DECLS

#endif /* MACHINE_GROPTERMINAL_H_ */
