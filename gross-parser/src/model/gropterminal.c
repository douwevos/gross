/*
   File:    gropterminal.c
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


#include "gropterminal.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "GroPTerminal"
#include <logging/catlog.h>

G_DEFINE_TYPE(GroPTerminal, grop_terminal, GROP_TYPE_SYMBOL);

static void grop_terminal_class_init(GroPTerminalClass *clazz) {
}

static void grop_terminal_init(GroPTerminal *instance) {
}


GroPTerminal *grop_terminal_new(CatStringWo *name, CatInteger *id) {
	GroPTerminal *result = g_object_new(GROP_TYPE_TERMINAL, NULL);
	cat_ref_anounce(result);
	grop_symbol_construct((GroPSymbol *) result, name, id);
	return result;
}

