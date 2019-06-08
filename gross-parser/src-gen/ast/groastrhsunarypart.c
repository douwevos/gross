/* This file was generated by Gross-CC on 2019.04.12 AD at 23:25:21 CEST */
#include "groastrhsunarypart.h"

struct _GroAstRhsUnaryPartPrivate {
	GroRunIToken *entry;
	GroAstUnaryOp op;
};


G_DEFINE_TYPE_WITH_CODE(GroAstRhsUnaryPart, groast_rhs_unary_part, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroAstRhsUnaryPart)
);

#define L_SAFE_UNREF_PTR(p) { void *ptr = p; p = NULL; if (ptr) { g_object_unref(ptr); } }
static G_GNUC_UNUSED void *L_SAFE_REF_PTR(void *p) { if (p) { g_object_ref(p); } return p; }

static void l_dispose(GObject *object);

static void groast_rhs_unary_part_class_init(GroAstRhsUnaryPartClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
}

static void groast_rhs_unary_part_init(GroAstRhsUnaryPart *instance) {
}

static void l_dispose(GObject *object) {
	GroAstRhsUnaryPart *instance = GROAST_RHS_UNARY_PART(object);
	GroAstRhsUnaryPartPrivate *priv = groast_rhs_unary_part_get_instance_private(instance);
	L_SAFE_UNREF_PTR(priv->entry);
	G_OBJECT_CLASS(groast_rhs_unary_part_parent_class)->dispose(object);
}

GroAstRhsUnaryPart *groast_rhs_unary_part_new_1(GroRunIToken *entry, GroAstUnaryOp op) {
	GroAstRhsUnaryPart *instance = g_object_new(GROAST_TYPE_RHS_UNARY_PART, NULL);
	GroAstRhsUnaryPartPrivate *priv = groast_rhs_unary_part_get_instance_private(instance);
	priv->entry = L_SAFE_REF_PTR(entry);
	priv->op = 0;
	return instance;
}

GroRunIToken *groast_rhs_unary_part_tk_entry(GroAstRhsUnaryPart *self) {
	GroAstRhsUnaryPartPrivate *priv = groast_rhs_unary_part_get_instance_private(self);
	return priv->entry;
}

GroAstIRhsPart *groast_rhs_unary_part_get_entry(GroAstRhsUnaryPart *self) {
	GroAstRhsUnaryPartPrivate *priv = groast_rhs_unary_part_get_instance_private(self);
	return priv->entry==NULL ? NULL : (GroAstIRhsPart *) grorun_itoken_get_value(priv->entry);
}

GroAstUnaryOp groast_rhs_unary_part_get_op(GroAstRhsUnaryPart *self) {
	GroAstRhsUnaryPartPrivate *priv = groast_rhs_unary_part_get_instance_private(self);
	return (GroAstUnaryOp ) priv->op;
}

