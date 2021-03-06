/* This file was generated by Gross-CC on 2019.04.12 AD at 23:25:21 CEST */
#include "groastrhsrule.h"
#include "../../src/ast/groastirhsenlistable.h"

struct _GroAstRhsRulePrivate {
	GroRunIToken *rulePartList;
	GroRunIToken *imark;
};

static void l_irhs_enlistable_iface_init(GroAstIRhsEnlistableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroAstRhsRule, groast_rhs_rule, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroAstRhsRule)
		G_IMPLEMENT_INTERFACE(GROAST_TYPE_IRHS_ENLISTABLE, l_irhs_enlistable_iface_init)
);

#define L_SAFE_UNREF_PTR(p) { void *ptr = p; p = NULL; if (ptr) { g_object_unref(ptr); } }
static G_GNUC_UNUSED void *L_SAFE_REF_PTR(void *p) { if (p) { g_object_ref(p); } return p; }

static void l_dispose(GObject *object);

static void groast_rhs_rule_class_init(GroAstRhsRuleClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
}

static void groast_rhs_rule_init(GroAstRhsRule *instance) {
}

static void l_dispose(GObject *object) {
	GroAstRhsRule *instance = GROAST_RHS_RULE(object);
	GroAstRhsRulePrivate *priv = groast_rhs_rule_get_instance_private(instance);
	L_SAFE_UNREF_PTR(priv->rulePartList);
	L_SAFE_UNREF_PTR(priv->imark);
	G_OBJECT_CLASS(groast_rhs_rule_parent_class)->dispose(object);
}

CatArrayWo *groast_rhs_rule_enlist(GroAstRhsRule *self) {
 
  
	GroAstRhsRulePrivate *priv = groast_rhs_rule_get_instance_private(self);
	if (priv->rulePartList==NULL) {
		return cat_array_wo_new();
	}
	return groast_irhs_enlistable_enlist((GroAstIRhsEnlistable *) grorun_itoken_get_value(priv->rulePartList));
  
}

GroAstRhsRule *groast_rhs_rule_new_1(GroRunIToken *rulePartList) {
	GroAstRhsRule *instance = g_object_new(GROAST_TYPE_RHS_RULE, NULL);
	GroAstRhsRulePrivate *priv = groast_rhs_rule_get_instance_private(instance);
	priv->rulePartList = L_SAFE_REF_PTR(rulePartList);
	priv->imark = NULL;
	return instance;
}

GroAstRhsRule *groast_rhs_rule_new_2(GroRunIToken *imark, GroRunIToken *rulePartList) {
	GroAstRhsRule *instance = g_object_new(GROAST_TYPE_RHS_RULE, NULL);
	GroAstRhsRulePrivate *priv = groast_rhs_rule_get_instance_private(instance);
	priv->rulePartList = L_SAFE_REF_PTR(rulePartList);
	priv->imark = L_SAFE_REF_PTR(imark);
	return instance;
}

GroRunIToken *groast_rhs_rule_tk_rulePartList(GroAstRhsRule *self) {
	GroAstRhsRulePrivate *priv = groast_rhs_rule_get_instance_private(self);
	return priv->rulePartList;
}

GroAstRhsRulePartList *groast_rhs_rule_get_rulePartList(GroAstRhsRule *self) {
	GroAstRhsRulePrivate *priv = groast_rhs_rule_get_instance_private(self);
	return priv->rulePartList==NULL ? NULL : (GroAstRhsRulePartList *) grorun_itoken_get_value(priv->rulePartList);
}

GroRunIToken *groast_rhs_rule_tk_imark(GroAstRhsRule *self) {
	GroAstRhsRulePrivate *priv = groast_rhs_rule_get_instance_private(self);
	return priv->imark;
}

CatStringWo *groast_rhs_rule_get_imark(GroAstRhsRule *self) {
	GroAstRhsRulePrivate *priv = groast_rhs_rule_get_instance_private(self);
	return priv->imark==NULL ? NULL : (CatStringWo *) grorun_itoken_get_value(priv->imark);
}


/******************** start GroAstIRhsEnlistable implementation  ********************/


static void l_irhs_enlistable_iface_init(GroAstIRhsEnlistableInterface *iface) {

  	iface->enlist = (GroAstEnlistFunc) groast_rhs_rule_enlist;
  
}

/******************** end GroAstIRhsEnlistable implementation ********************/

