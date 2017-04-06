/* This file was generated by Gross-CC on 2017.04.04 AD at 21:26:40 CEST */
#ifndef GROASTRHS_UNARY_PART_H_
#define GROASTRHS_UNARY_PART_H_

#include "../groastunaryop.h"
#include "grorunfork.h"
#include "../../src/ast/groastirhspart.h"

G_BEGIN_DECLS

#define GROAST_TYPE_RHS_UNARY_PART              (groast_rhs_unary_part_get_type())
#define GROAST_RHS_UNARY_PART(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), groast_rhs_unary_part_get_type(), GroAstRhsUnaryPart))
#define GROAST_RHS_UNARY_PART_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROAST_TYPE_RHS_UNARY_PART, GroAstRhsUnaryPartClass))
#define GROAST_IS_RHS_UNARY_PART(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROAST_TYPE_RHS_UNARY_PART))
#define GROAST_IS_RHS_UNARY_PART_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROAST_TYPE_RHS_UNARY_PART))
#define GROAST_RHS_UNARY_PART_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROAST_TYPE_RHS_UNARY_PART, GroAstRhsUnaryPartClass))


typedef struct _GroAstRhsUnaryPart               GroAstRhsUnaryPart;
typedef struct _GroAstRhsUnaryPartPrivate        GroAstRhsUnaryPartPrivate;
typedef struct _GroAstRhsUnaryPartClass          GroAstRhsUnaryPartClass;


struct _GroAstRhsUnaryPart {
	GObject parent;
};

struct _GroAstRhsUnaryPartClass {
	GObjectClass parent_class;
};


GType groast_rhs_unary_part_get_type();

GroAstRhsUnaryPart *groast_rhs_unary_part_new_1(GroRunIToken *entry, GroAstUnaryOp op);
GroRunIToken *groast_rhs_unary_part_tk_entry(GroAstRhsUnaryPart *self);
GroAstIRhsPart *groast_rhs_unary_part_get_entry(GroAstRhsUnaryPart *self);
GroAstUnaryOp groast_rhs_unary_part_get_op(GroAstRhsUnaryPart *self);

G_END_DECLS

#endif /* GROASTRHS_UNARY_PART_H_ */
