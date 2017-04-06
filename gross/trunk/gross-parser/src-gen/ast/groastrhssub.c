/* This file was generated by Gross-CC on 2017.04.04 AD at 21:26:40 CEST */
#include "groastrhssub.h"
#include "../../src/ast/groastirhsenlistable.h"

struct _GroAstRhsSubPrivate {
	GroRunIToken *sub;
	GroRunIToken *entry;
};

static void l_irhs_enlistable_iface_init(GroAstIRhsEnlistableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroAstRhsSub, groast_rhs_sub, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroAstRhsSub)
		G_IMPLEMENT_INTERFACE(GROAST_TYPE_IRHS_ENLISTABLE, l_irhs_enlistable_iface_init)
);

#define L_SAFE_UNREF_PTR(p) { void *ptr = p; p = NULL; if (ptr) { g_object_unref(ptr); } }
static G_GNUC_UNUSED void *L_SAFE_REF_PTR(void *p) { if (p) { g_object_ref(p); } return p; }

static void l_dispose(GObject *object);

static void groast_rhs_sub_class_init(GroAstRhsSubClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
}

static void groast_rhs_sub_init(GroAstRhsSub *instance) {
}

static void l_dispose(GObject *object) {
	GroAstRhsSub *instance = GROAST_RHS_SUB(object);
	GroAstRhsSubPrivate *priv = groast_rhs_sub_get_instance_private(instance);
	L_SAFE_UNREF_PTR(priv->sub);
	L_SAFE_UNREF_PTR(priv->entry);
	G_OBJECT_CLASS(groast_rhs_sub_parent_class)->dispose(object);
}

CatArrayWo *groast_rhs_sub_enlist(GroAstRhsSub *self) {
 
	CatArrayWo *result = cat_array_wo_new();
	GroAstRhsSub *tdl = self;
	while(tdl) {
		GroAstRhsSubPrivate *priv = groast_rhs_sub_get_instance_private(tdl);
		cat_array_wo_append(result, (GObject *) priv->entry);
		if (priv->sub==NULL) {
			break;
		}
		tdl = (GroAstRhsSub *) grorun_itoken_get_value(priv->sub);
	}
	cat_array_wo_reverse(result);
	return result;
  
}

GroAstRhsSub *groast_rhs_sub_new_1(GroRunIToken *sub, GroRunIToken *entry) {
	GroAstRhsSub *instance = g_object_new(GROAST_TYPE_RHS_SUB, NULL);
	GroAstRhsSubPrivate *priv = groast_rhs_sub_get_instance_private(instance);
	priv->sub = L_SAFE_REF_PTR(sub);
	priv->entry = L_SAFE_REF_PTR(entry);
	return instance;
}

GroAstRhsSub *groast_rhs_sub_new_2(GroRunIToken *entry) {
	GroAstRhsSub *instance = g_object_new(GROAST_TYPE_RHS_SUB, NULL);
	GroAstRhsSubPrivate *priv = groast_rhs_sub_get_instance_private(instance);
	priv->sub = NULL;
	priv->entry = L_SAFE_REF_PTR(entry);
	return instance;
}

GroRunIToken *groast_rhs_sub_tk_sub(GroAstRhsSub *self) {
	GroAstRhsSubPrivate *priv = groast_rhs_sub_get_instance_private(self);
	return priv->sub;
}

GroAstIRhsPart *groast_rhs_sub_get_sub(GroAstRhsSub *self) {
	GroAstRhsSubPrivate *priv = groast_rhs_sub_get_instance_private(self);
	return priv->sub==NULL ? NULL : (GroAstIRhsPart *) grorun_itoken_get_value(priv->sub);
}

GroRunIToken *groast_rhs_sub_tk_entry(GroAstRhsSub *self) {
	GroAstRhsSubPrivate *priv = groast_rhs_sub_get_instance_private(self);
	return priv->entry;
}

GroAstIRhsPart *groast_rhs_sub_get_entry(GroAstRhsSub *self) {
	GroAstRhsSubPrivate *priv = groast_rhs_sub_get_instance_private(self);
	return priv->entry==NULL ? NULL : (GroAstIRhsPart *) grorun_itoken_get_value(priv->entry);
}


/******************** start GroAstIRhsEnlistable implementation  ********************/


static void l_irhs_enlistable_iface_init(GroAstIRhsEnlistableInterface *iface) {

  	iface->enlist = (GroAstEnlistFunc) groast_rhs_sub_enlist;
  
}

/******************** end GroAstIRhsEnlistable implementation ********************/

