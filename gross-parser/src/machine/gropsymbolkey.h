/*
   File:    gropsymbolkey.h
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

#ifndef MACHINE_GROPSYMBOLKEY_H_
#define MACHINE_GROPSYMBOLKEY_H_

#include "../model/gropsymbol.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_SYMBOL_KEY              (grop_symbol_key_get_type())
#define GROP_SYMBOL_KEY(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_symbol_key_get_type(), GroPSymbolKey))
#define GROP_SYMBOL_KEY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_SYMBOL_KEY, GroPSymbolKeyClass))
#define GROP_IS_SYMBOL_KEY(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_SYMBOL_KEY))
#define GROP_IS_SYMBOL_KEY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_SYMBOL_KEY))
#define GROP_SYMBOL_KEY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_SYMBOL_KEY, GroPSymbolKeyClass))


typedef struct _GroPSymbolKey               GroPSymbolKey;
typedef struct _GroPSymbolKeyPrivate        GroPSymbolKeyPrivate;
typedef struct _GroPSymbolKeyClass          GroPSymbolKeyClass;


struct _GroPSymbolKey {
	GObject parent;
};

struct _GroPSymbolKeyClass {
	GObjectClass parent_class;
};


GType grop_symbol_key_get_type();

GroPSymbolKey *grop_symbol_key_new(GroPSymbol *symbol, gboolean is_nullified);

GroPSymbol *grop_symbol_key_get_symbol(GroPSymbolKey *symbol_key);

int grop_symbol_key_hash(GroPSymbolKey *symbol_key);
gboolean grop_symbol_key_equal(const GroPSymbolKey *symbol_key_a, const GroPSymbolKey *symbol_key_b);

G_END_DECLS

#endif /* MACHINE_GROPSYMBOLKEY_H_ */
