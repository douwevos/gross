/*
   File:    gropkernel.h
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

#ifndef MACHINE_GROPKERNEL_H_
#define MACHINE_GROPKERNEL_H_

#include "gropdotlink.h"
#include "../model/gropsymbolset.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define GROP_TYPE_KERNEL              (grop_kernel_get_type())
#define GROP_KERNEL(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), grop_kernel_get_type(), GroPKernel))
#define GROP_KERNEL_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROP_TYPE_KERNEL, GroPKernelClass))
#define GROP_IS_KERNEL(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROP_TYPE_KERNEL))
#define GROP_IS_KERNEL_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROP_TYPE_KERNEL))
#define GROP_KERNEL_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROP_TYPE_KERNEL, GroPKernelClass))


typedef struct _GroPKernel               GroPKernel;
typedef struct _GroPKernelPrivate        GroPKernelPrivate;
typedef struct _GroPKernelClass          GroPKernelClass;


struct _GroPKernel {
	GObject parent;
};

struct _GroPKernelClass {
	GObjectClass parent_class;
};


GType grop_kernel_get_type();

GroPKernel *grop_kernel_new(int id);

int grop_kernel_get_id(GroPKernel *kernel);

int grop_kernel_size(GroPKernel *kernel);

gboolean grop_kernel_add(GroPKernel *kernel, GroPDotLink *dot_link);

CatIIterator *grop_kernel_iterator(GroPKernel *kernel);

int grop_kernel_hash(GroPKernel *kernel);
gboolean grop_kernel_equal(const GroPKernel *kernel_a, const GroPKernel *kernel_b);

G_END_DECLS

#endif /* MACHINE_GROPKERNEL_H_ */
