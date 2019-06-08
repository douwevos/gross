/* This file was generated by Gross-CC on 2019.04.12 AD at 23:25:21 CEST */
#include "groastspec.h"

struct _GroAstSpecPrivate {
	GroRunIToken *td;
	GroRunIToken *im;
	GroRunIToken *tl;
	GroRunIToken *cl;
	GroRunIToken *pl;
};


G_DEFINE_TYPE_WITH_CODE(GroAstSpec, groast_spec, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroAstSpec)
);

#define L_SAFE_UNREF_PTR(p) { void *ptr = p; p = NULL; if (ptr) { g_object_unref(ptr); } }
static G_GNUC_UNUSED void *L_SAFE_REF_PTR(void *p) { if (p) { g_object_ref(p); } return p; }

static void l_dispose(GObject *object);

static void groast_spec_class_init(GroAstSpecClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
}

static void groast_spec_init(GroAstSpec *instance) {
}

static void l_dispose(GObject *object) {
	GroAstSpec *instance = GROAST_SPEC(object);
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(instance);
	L_SAFE_UNREF_PTR(priv->td);
	L_SAFE_UNREF_PTR(priv->im);
	L_SAFE_UNREF_PTR(priv->tl);
	L_SAFE_UNREF_PTR(priv->cl);
	L_SAFE_UNREF_PTR(priv->pl);
	G_OBJECT_CLASS(groast_spec_parent_class)->dispose(object);
}

GroAstSpec *groast_spec_new_1(GroRunIToken *td, GroRunIToken *pl, GroRunIToken *im, GroRunIToken *tl, GroRunIToken *cl) {
	GroAstSpec *instance = g_object_new(GROAST_TYPE_SPEC, NULL);
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(instance);
	priv->td = L_SAFE_REF_PTR(td);
	priv->im = L_SAFE_REF_PTR(im);
	priv->tl = L_SAFE_REF_PTR(tl);
	priv->cl = L_SAFE_REF_PTR(cl);
	priv->pl = L_SAFE_REF_PTR(pl);
	return instance;
}

GroAstSpec *groast_spec_new_2(GroRunIToken *td, GroRunIToken *pl) {
	GroAstSpec *instance = g_object_new(GROAST_TYPE_SPEC, NULL);
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(instance);
	priv->td = L_SAFE_REF_PTR(td);
	priv->im = NULL;
	priv->tl = NULL;
	priv->cl = NULL;
	priv->pl = L_SAFE_REF_PTR(pl);
	return instance;
}

GroRunIToken *groast_spec_tk_td(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->td;
}

GroAstTerminalDeclarationList *groast_spec_get_td(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->td==NULL ? NULL : (GroAstTerminalDeclarationList *) grorun_itoken_get_value(priv->td);
}

GroRunIToken *groast_spec_tk_im(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->im;
}

CatStringWo *groast_spec_get_im(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->im==NULL ? NULL : (CatStringWo *) grorun_itoken_get_value(priv->im);
}

GroRunIToken *groast_spec_tk_tl(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->tl;
}

GroAstTypeDefinitionList *groast_spec_get_tl(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->tl==NULL ? NULL : (GroAstTypeDefinitionList *) grorun_itoken_get_value(priv->tl);
}

GroRunIToken *groast_spec_tk_cl(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->cl;
}

GroAstCodeDefinitionList *groast_spec_get_cl(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->cl==NULL ? NULL : (GroAstCodeDefinitionList *) grorun_itoken_get_value(priv->cl);
}

GroRunIToken *groast_spec_tk_pl(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->pl;
}

GroAstProductionDefinitionList *groast_spec_get_pl(GroAstSpec *self) {
	GroAstSpecPrivate *priv = groast_spec_get_instance_private(self);
	return priv->pl==NULL ? NULL : (GroAstProductionDefinitionList *) grorun_itoken_get_value(priv->pl);
}

