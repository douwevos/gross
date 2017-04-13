/* This file was generated by Gross-CC on 2017.04.04 AD at 21:26:40 CEST */
#ifndef GROASTRHS_RULE_H_
#define GROASTRHS_RULE_H_

#include <caterpillar.h>
#include "groastrhsrulepartlist.h"
#include "grorunfork.h"

G_BEGIN_DECLS

#define GROAST_TYPE_RHS_RULE              (groast_rhs_rule_get_type())
#define GROAST_RHS_RULE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), groast_rhs_rule_get_type(), GroAstRhsRule))
#define GROAST_RHS_RULE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROAST_TYPE_RHS_RULE, GroAstRhsRuleClass))
#define GROAST_IS_RHS_RULE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROAST_TYPE_RHS_RULE))
#define GROAST_IS_RHS_RULE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROAST_TYPE_RHS_RULE))
#define GROAST_RHS_RULE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROAST_TYPE_RHS_RULE, GroAstRhsRuleClass))


typedef struct _GroAstRhsRule               GroAstRhsRule;
typedef struct _GroAstRhsRulePrivate        GroAstRhsRulePrivate;
typedef struct _GroAstRhsRuleClass          GroAstRhsRuleClass;


struct _GroAstRhsRule {
	GObject parent;
};

struct _GroAstRhsRuleClass {
	GObjectClass parent_class;
};


GType groast_rhs_rule_get_type();

CatArrayWo *groast_rhs_rule_enlist(GroAstRhsRule *self);
GroAstRhsRule *groast_rhs_rule_new_1(GroRunIToken *rulePartList);
GroAstRhsRule *groast_rhs_rule_new_2(GroRunIToken *imark, GroRunIToken *rulePartList);
GroRunIToken *groast_rhs_rule_tk_rulePartList(GroAstRhsRule *self);
GroAstRhsRulePartList *groast_rhs_rule_get_rulePartList(GroAstRhsRule *self);
GroRunIToken *groast_rhs_rule_tk_imark(GroAstRhsRule *self);
CatStringWo *groast_rhs_rule_get_imark(GroAstRhsRule *self);

G_END_DECLS

#endif /* GROASTRHS_RULE_H_ */