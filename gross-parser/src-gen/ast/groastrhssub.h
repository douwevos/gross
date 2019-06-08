/* This file was generated by Gross-CC on 2019.04.12 AD at 23:25:21 CEST */
#ifndef GROASTRHS_SUB_H_
#define GROASTRHS_SUB_H_

#include "grorunfork.h"
#include "../../src/ast/groastirhspart.h"

G_BEGIN_DECLS

#define GROAST_TYPE_RHS_SUB              (groast_rhs_sub_get_type())
#define GROAST_RHS_SUB(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), groast_rhs_sub_get_type(), GroAstRhsSub))
#define GROAST_RHS_SUB_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROAST_TYPE_RHS_SUB, GroAstRhsSubClass))
#define GROAST_IS_RHS_SUB(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROAST_TYPE_RHS_SUB))
#define GROAST_IS_RHS_SUB_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROAST_TYPE_RHS_SUB))
#define GROAST_RHS_SUB_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROAST_TYPE_RHS_SUB, GroAstRhsSubClass))


typedef struct _GroAstRhsSub               GroAstRhsSub;
typedef struct _GroAstRhsSubPrivate        GroAstRhsSubPrivate;
typedef struct _GroAstRhsSubClass          GroAstRhsSubClass;


struct _GroAstRhsSub {
	GObject parent;
};

struct _GroAstRhsSubClass {
	GObjectClass parent_class;
};


GType groast_rhs_sub_get_type();

CatArrayWo *groast_rhs_sub_enlist(GroAstRhsSub *self);
GroAstRhsSub *groast_rhs_sub_new_1(GroRunIToken *sub, GroRunIToken *entry);
GroAstRhsSub *groast_rhs_sub_new_2(GroRunIToken *entry);
GroRunIToken *groast_rhs_sub_tk_sub(GroAstRhsSub *self);
GroAstIRhsPart *groast_rhs_sub_get_sub(GroAstRhsSub *self);
GroRunIToken *groast_rhs_sub_tk_entry(GroAstRhsSub *self);
GroAstIRhsPart *groast_rhs_sub_get_entry(GroAstRhsSub *self);

G_END_DECLS

#endif /* GROASTRHS_SUB_H_ */
