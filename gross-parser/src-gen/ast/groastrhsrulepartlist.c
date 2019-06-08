/* This file was generated by Gross-CC on 2019.04.12 AD at 23:25:21 CEST */
#include "groastrhsrulepartlist.h"
#include "../../src/ast/groastirhsenlistable.h"

struct _GroAstRhsRulePartListPrivate {
	GroRunIToken *rulePart;
	GroRunIToken *rulePartList;
};

static void l_irhs_enlistable_iface_init(GroAstIRhsEnlistableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroAstRhsRulePartList, groast_rhs_rule_part_list, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroAstRhsRulePartList)
		G_IMPLEMENT_INTERFACE(GROAST_TYPE_IRHS_ENLISTABLE, l_irhs_enlistable_iface_init)
);

#define L_SAFE_UNREF_PTR(p) { void *ptr = p; p = NULL; if (ptr) { g_object_unref(ptr); } }
static G_GNUC_UNUSED void *L_SAFE_REF_PTR(void *p) { if (p) { g_object_ref(p); } return p; }

static void l_dispose(GObject *object);

static void groast_rhs_rule_part_list_class_init(GroAstRhsRulePartListClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
}

static void groast_rhs_rule_part_list_init(GroAstRhsRulePartList *instance) {
}

static void l_dispose(GObject *object) {
	GroAstRhsRulePartList *instance = GROAST_RHS_RULE_PART_LIST(object);
	GroAstRhsRulePartListPrivate *priv = groast_rhs_rule_part_list_get_instance_private(instance);
	L_SAFE_UNREF_PTR(priv->rulePart);
	L_SAFE_UNREF_PTR(priv->rulePartList);
	G_OBJECT_CLASS(groast_rhs_rule_part_list_parent_class)->dispose(object);
}

CatArrayWo *groast_rhs_rule_part_list_enlist(GroAstRhsRulePartList *self) {
 
	CatArrayWo *result = cat_array_wo_new();
	GroAstRhsRulePartList *tdl = self;
	while(tdl) {
		GroAstRhsRulePartListPrivate *priv = groast_rhs_rule_part_list_get_instance_private(tdl);
		cat_array_wo_append(result, (GObject *) priv->rulePart);
		if (priv->rulePartList==NULL) {
			break;
		}
		tdl = (GroAstRhsRulePartList *) grorun_itoken_get_value(priv->rulePartList);
	}
	cat_array_wo_reverse(result);
	return result;
  
}

GroAstRhsRulePartList *groast_rhs_rule_part_list_new_1(GroRunIToken *rulePartList, GroRunIToken *rulePart) {
	GroAstRhsRulePartList *instance = g_object_new(GROAST_TYPE_RHS_RULE_PART_LIST, NULL);
	GroAstRhsRulePartListPrivate *priv = groast_rhs_rule_part_list_get_instance_private(instance);
	priv->rulePart = L_SAFE_REF_PTR(rulePart);
	priv->rulePartList = L_SAFE_REF_PTR(rulePartList);
	return instance;
}

GroRunIToken *groast_rhs_rule_part_list_tk_rulePart(GroAstRhsRulePartList *self) {
	GroAstRhsRulePartListPrivate *priv = groast_rhs_rule_part_list_get_instance_private(self);
	return priv->rulePart;
}

GroAstIRhsPart *groast_rhs_rule_part_list_get_rulePart(GroAstRhsRulePartList *self) {
	GroAstRhsRulePartListPrivate *priv = groast_rhs_rule_part_list_get_instance_private(self);
	return priv->rulePart==NULL ? NULL : (GroAstIRhsPart *) grorun_itoken_get_value(priv->rulePart);
}

GroRunIToken *groast_rhs_rule_part_list_tk_rulePartList(GroAstRhsRulePartList *self) {
	GroAstRhsRulePartListPrivate *priv = groast_rhs_rule_part_list_get_instance_private(self);
	return priv->rulePartList;
}

GroAstRhsRulePartList *groast_rhs_rule_part_list_get_rulePartList(GroAstRhsRulePartList *self) {
	GroAstRhsRulePartListPrivate *priv = groast_rhs_rule_part_list_get_instance_private(self);
	return priv->rulePartList==NULL ? NULL : (GroAstRhsRulePartList *) grorun_itoken_get_value(priv->rulePartList);
}


/******************** start GroAstIRhsEnlistable implementation  ********************/


static void l_irhs_enlistable_iface_init(GroAstIRhsEnlistableInterface *iface) {

  	iface->enlist = (GroAstEnlistFunc) groast_rhs_rule_part_list_enlist;
  
}

/******************** end GroAstIRhsEnlistable implementation ********************/

