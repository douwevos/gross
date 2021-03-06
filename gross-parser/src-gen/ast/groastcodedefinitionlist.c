/* This file was generated by Gross-CC on 2019.04.12 AD at 23:25:21 CEST */
#include "groastcodedefinitionlist.h"

struct _GroAstCodeDefinitionListPrivate {
	GroRunIToken *cdList;
	GroRunIToken *codeDef;
};


G_DEFINE_TYPE_WITH_CODE(GroAstCodeDefinitionList, groast_code_definition_list, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroAstCodeDefinitionList)
);

#define L_SAFE_UNREF_PTR(p) { void *ptr = p; p = NULL; if (ptr) { g_object_unref(ptr); } }
static G_GNUC_UNUSED void *L_SAFE_REF_PTR(void *p) { if (p) { g_object_ref(p); } return p; }

static void l_dispose(GObject *object);

static void groast_code_definition_list_class_init(GroAstCodeDefinitionListClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
}

static void groast_code_definition_list_init(GroAstCodeDefinitionList *instance) {
}

static void l_dispose(GObject *object) {
	GroAstCodeDefinitionList *instance = GROAST_CODE_DEFINITION_LIST(object);
	GroAstCodeDefinitionListPrivate *priv = groast_code_definition_list_get_instance_private(instance);
	L_SAFE_UNREF_PTR(priv->cdList);
	L_SAFE_UNREF_PTR(priv->codeDef);
	G_OBJECT_CLASS(groast_code_definition_list_parent_class)->dispose(object);
}

GroAstCodeDefinitionList *groast_code_definition_list_new_1(GroRunIToken *cdList, GroRunIToken *codeDef) {
	GroAstCodeDefinitionList *instance = g_object_new(GROAST_TYPE_CODE_DEFINITION_LIST, NULL);
	GroAstCodeDefinitionListPrivate *priv = groast_code_definition_list_get_instance_private(instance);
	priv->cdList = L_SAFE_REF_PTR(cdList);
	priv->codeDef = L_SAFE_REF_PTR(codeDef);
	return instance;
}

GroRunIToken *groast_code_definition_list_tk_cdList(GroAstCodeDefinitionList *self) {
	GroAstCodeDefinitionListPrivate *priv = groast_code_definition_list_get_instance_private(self);
	return priv->cdList;
}

GroAstCodeDefinitionList *groast_code_definition_list_get_cdList(GroAstCodeDefinitionList *self) {
	GroAstCodeDefinitionListPrivate *priv = groast_code_definition_list_get_instance_private(self);
	return priv->cdList==NULL ? NULL : (GroAstCodeDefinitionList *) grorun_itoken_get_value(priv->cdList);
}

GroRunIToken *groast_code_definition_list_tk_codeDef(GroAstCodeDefinitionList *self) {
	GroAstCodeDefinitionListPrivate *priv = groast_code_definition_list_get_instance_private(self);
	return priv->codeDef;
}

GroAstCodeDefinition *groast_code_definition_list_get_codeDef(GroAstCodeDefinitionList *self) {
	GroAstCodeDefinitionListPrivate *priv = groast_code_definition_list_get_instance_private(self);
	return priv->codeDef==NULL ? NULL : (GroAstCodeDefinition *) grorun_itoken_get_value(priv->codeDef);
}

