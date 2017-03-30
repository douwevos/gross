/*
   File:    gropsymbolset.h
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

#ifndef MACHINE_GROPSYMBOLSET_H_
#define MACHINE_GROPSYMBOLSET_H_

#include "../model/gropsymbol.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_SYMBOL_SET              (grop_symbol_set_get_type())
#define GROP_SYMBOL_SET(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_symbol_set_get_type(), GroPSymbolSet))
#define GROP_SYMBOL_SET_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_SYMBOL_SET, GroPSymbolSetClass))
#define GROP_IS_SYMBOL_SET(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_SYMBOL_SET))
#define GROP_IS_SYMBOL_SET_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_SYMBOL_SET))
#define GROP_SYMBOL_SET_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_SYMBOL_SET, GroPSymbolSetClass))


typedef struct _GroPSymbolSet               GroPSymbolSet;
typedef struct _GroPSymbolSetPrivate        GroPSymbolSetPrivate;
typedef struct _GroPSymbolSetClass          GroPSymbolSetClass;


struct _GroPSymbolSet {
	GObject parent;
};

struct _GroPSymbolSetClass {
	GObjectClass parent_class;
};


GType grop_symbol_set_get_type();

GroPSymbolSet *grop_symbol_set_new();

gboolean grop_symbol_set_add(GroPSymbolSet *symbol_set, GroPSymbol *sym);
gboolean grop_symbol_set_add_all(GroPSymbolSet *symbol_set, GroPSymbolSet *set_to_add);


gboolean grop_symbol_set_is_empty(const GroPSymbolSet *symbol_set);

gboolean grop_symbol_set_contains(const GroPSymbolSet *symbol_set, GroPSymbol *sym);

G_END_DECLS

#endif /* MACHINE_GROPSYMBOLSET_H_ */
