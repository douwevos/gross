/*
   File:    gropsymbol.h
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

#ifndef MACHINE_GROPSYMBOL_H_
#define MACHINE_GROPSYMBOL_H_

#include <caterpillar.h>

G_BEGIN_DECLS

enum _GroPNullable {
	GROP_NULLABLE_UNKNOWN,
	GROP_NULLABLE_TRUE,
	GROP_NULLABLE_FALSE
};

typedef enum _GroPNullable GroPNullable;

#define GROP_TYPE_SYMBOL              (grop_symbol_get_type())
#define GROP_SYMBOL(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_symbol_get_type(), GroPSymbol))
#define GROP_SYMBOL_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_SYMBOL, GroPSymbolClass))
#define GROP_IS_SYMBOL(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_SYMBOL))
#define GROP_IS_SYMBOL_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_SYMBOL))
#define GROP_SYMBOL_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_SYMBOL, GroPSymbolClass))


typedef struct _GroPSymbol               GroPSymbol;
typedef struct _GroPSymbolPrivate        GroPSymbolPrivate;
typedef struct _GroPSymbolClass          GroPSymbolClass;


struct _GroPSymbol {
	GObject parent;
};

struct _GroPSymbolClass {
	GObjectClass parent_class;
};


GType grop_symbol_get_type();

void grop_symbol_construct(GroPSymbol *symbol, CatStringWo *name, CatInteger *id);

CatStringWo *grop_symbol_get_name(GroPSymbol *symbol);

CatInteger *grop_symbol_get_id(GroPSymbol *symbol);

int grop_symbol_hash(const GroPSymbol *symbol);
gboolean grop_symbol_equal(const GroPSymbol *symbol_a, const GroPSymbol *symbol_b);

G_END_DECLS

#endif /* MACHINE_GROPSYMBOL_H_ */
