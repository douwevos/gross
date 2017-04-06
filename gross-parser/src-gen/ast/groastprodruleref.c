/* This file was generated by Gross-CC on 2017.04.04 AD at 21:26:40 CEST */
#include "groastprodruleref.h"

struct _GroAstProdRuleRefPrivate {
	GroRunIToken *lhsName;
	GroRunIToken *offset;
	GroRunIToken *label;
};


G_DEFINE_TYPE_WITH_CODE(GroAstProdRuleRef, groast_prod_rule_ref, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroAstProdRuleRef)
);

#define L_SAFE_UNREF_PTR(p) { void *ptr = p; p = NULL; if (ptr) { g_object_unref(ptr); } }
static G_GNUC_UNUSED void *L_SAFE_REF_PTR(void *p) { if (p) { g_object_ref(p); } return p; }

static void l_dispose(GObject *object);

static void groast_prod_rule_ref_class_init(GroAstProdRuleRefClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
}

static void groast_prod_rule_ref_init(GroAstProdRuleRef *instance) {
}

static void l_dispose(GObject *object) {
	GroAstProdRuleRef *instance = GROAST_PROD_RULE_REF(object);
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(instance);
	L_SAFE_UNREF_PTR(priv->lhsName);
	L_SAFE_UNREF_PTR(priv->offset);
	L_SAFE_UNREF_PTR(priv->label);
	G_OBJECT_CLASS(groast_prod_rule_ref_parent_class)->dispose(object);
}

GroAstProdRuleRef *groast_prod_rule_ref_new_1(GroRunIToken *lhsName) {
	GroAstProdRuleRef *instance = g_object_new(GROAST_TYPE_PROD_RULE_REF, NULL);
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(instance);
	priv->lhsName = L_SAFE_REF_PTR(lhsName);
	priv->offset = NULL;
	priv->label = NULL;
	return instance;
}

GroAstProdRuleRef *groast_prod_rule_ref_new_2(GroRunIToken *lhsName, GroRunIToken *label) {
	GroAstProdRuleRef *instance = g_object_new(GROAST_TYPE_PROD_RULE_REF, NULL);
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(instance);
	priv->lhsName = L_SAFE_REF_PTR(lhsName);
	priv->offset = NULL;
	priv->label = L_SAFE_REF_PTR(label);
	return instance;
}

GroAstProdRuleRef *groast_prod_rule_ref_new_3(GroRunIToken *lhsName, GroRunIToken *offset) {
	GroAstProdRuleRef *instance = g_object_new(GROAST_TYPE_PROD_RULE_REF, NULL);
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(instance);
	priv->lhsName = L_SAFE_REF_PTR(lhsName);
	priv->offset = L_SAFE_REF_PTR(offset);
	priv->label = NULL;
	return instance;
}

GroRunIToken *groast_prod_rule_ref_tk_lhsName(GroAstProdRuleRef *self) {
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(self);
	return priv->lhsName;
}

CatStringWo *groast_prod_rule_ref_get_lhsName(GroAstProdRuleRef *self) {
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(self);
	return priv->lhsName==NULL ? NULL : (CatStringWo *) grorun_itoken_get_value(priv->lhsName);
}

GroRunIToken *groast_prod_rule_ref_tk_offset(GroAstProdRuleRef *self) {
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(self);
	return priv->offset;
}

CatInteger *groast_prod_rule_ref_get_offset(GroAstProdRuleRef *self) {
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(self);
	return priv->offset==NULL ? NULL : (CatInteger *) grorun_itoken_get_value(priv->offset);
}

GroRunIToken *groast_prod_rule_ref_tk_label(GroAstProdRuleRef *self) {
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(self);
	return priv->label;
}

CatStringWo *groast_prod_rule_ref_get_label(GroAstProdRuleRef *self) {
	GroAstProdRuleRefPrivate *priv = groast_prod_rule_ref_get_instance_private(self);
	return priv->label==NULL ? NULL : (CatStringWo *) grorun_itoken_get_value(priv->label);
}

