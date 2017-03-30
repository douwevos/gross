/*
   File:    gropnonterminal.h
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

#ifndef MACHINE_GROPNONTERMINAL_H_
#define MACHINE_GROPNONTERMINAL_H_

#include "gropsymbol.h"
#include "gropsymbolset.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_NON_TERMINAL              (grop_non_terminal_get_type())
#define GROP_NON_TERMINAL(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_non_terminal_get_type(), GroPNonTerminal))
#define GROP_NON_TERMINAL_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_NON_TERMINAL, GroPNonTerminalClass))
#define GROP_IS_NON_TERMINAL(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_NON_TERMINAL))
#define GROP_IS_NON_TERMINAL_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_NON_TERMINAL))
#define GROP_NON_TERMINAL_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_NON_TERMINAL, GroPNonTerminalClass))


typedef struct _GroPNonTerminal               GroPNonTerminal;
typedef struct _GroPNonTerminalPrivate        GroPNonTerminalPrivate;
typedef struct _GroPNonTerminalClass          GroPNonTerminalClass;


struct _GroPNonTerminal {
	GroPSymbol parent;
};

struct _GroPNonTerminalClass {
	GroPSymbolClass parent_class;
};

struct _GroPProduction;

GType grop_non_terminal_get_type();

GroPNonTerminal *grop_non_terminal_new(CatStringWo *name, CatInteger *id);

GroPNullable grop_non_terminal_calculate_nullabilty(GroPNonTerminal *non_term);
GroPNullable grop_non_terminal_get_nullable(GroPNonTerminal *non_term);
void grop_non_terminal_set_nullable(GroPNonTerminal *non_term, GroPNullable nullable);

gboolean grop_non_terminal_compute_first_set(GroPNonTerminal *non_term);
GroPSymbolSet *grop_non_terminal_get_first_set(GroPNonTerminal *non_term);

void grop_non_terminal_add_production(GroPNonTerminal *non_term, struct _GroPProduction *production);
CatIIterator *grop_non_terminal_iterator(GroPNonTerminal *non_term);

G_END_DECLS

#endif /* MACHINE_GROPNONTERMINAL_H_ */
