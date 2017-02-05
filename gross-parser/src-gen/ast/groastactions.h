/* This file was generated by Gross-CC on 2016.11.30 AD at 21:31:20 CET */
#ifndef GROAST_ACTIONS_H_
#define GROAST_ACTIONS_H_

#include "groastterminaldeclaration.h"
#include "groastrhsrule.h"
#include "groasttypedefinitionlist.h"
#include "groastsymbolpart.h"
#include "groastprodruleref.h"
#include "groastcodedefinition.h"
#include <grossruntime.h>
#include "groastrhssublist.h"
#include "groastidlist.h"
#include "groasttypedefinition.h"
#include "groastspec.h"
#include "groastterminaldeclarationlist.h"
#include "groastproductiondefinition.h"
#include "groastproductiondefinitionlist.h"
#include "groastrhsrulepartlist.h"
#include "groastcodedefinitionlist.h"
#include "groastrhsrulelist.h"
#include "groastrhsunarypart.h"
#include "groastrhssub.h"

G_BEGIN_DECLS

#define GRO_TYPE_AST_ACTIONS              (gro_ast_actions_get_type())
#define GRO_AST_ACTIONS(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), gro_ast_actions_get_type(), GroAstActions))
#define GRO_AST_ACTIONS_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GRO_TYPE_AST_ACTIONS, GroAstActionsClass))
#define GRO_IS_AST_ACTIONS(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GRO_TYPE_AST_ACTIONS))
#define GRO_IS_AST_ACTIONS_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GRO_TYPE_AST_ACTIONS))
#define GRO_AST_ACTIONS_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GRO_TYPE_AST_ACTIONS, GroAstActionsClass))


typedef struct _GroAstActions               GroAstActions;
typedef struct _GroAstActionsClass          GroAstActionsClass;


struct _GroAstActions {
	GObject parent;
};

struct _GroAstActionsClass {
	GObjectClass parent_class;
};


GType gro_ast_actions_get_type();

GroAstActions *gro_ast_actions_new();

G_END_DECLS

#endif /* GROAST_ACTIONS_H_ */