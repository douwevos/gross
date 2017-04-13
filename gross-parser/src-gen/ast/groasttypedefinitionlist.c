/* This file was generated by Gross-CC on 2017.04.04 AD at 21:26:40 CEST */
#include "groasttypedefinitionlist.h"

struct _GroAstTypeDefinitionListPrivate {
	GroRunIToken *tdList;
	GroRunIToken *typeDef;
};


G_DEFINE_TYPE_WITH_CODE(GroAstTypeDefinitionList, groast_type_definition_list, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroAstTypeDefinitionList)
);

#define L_SAFE_UNREF_PTR(p) { void *ptr = p; p = NULL; if (ptr) { g_object_unref(ptr); } }
static G_GNUC_UNUSED void *L_SAFE_REF_PTR(void *p) { if (p) { g_object_ref(p); } return p; }

static void l_dispose(GObject *object);

static void groast_type_definition_list_class_init(GroAstTypeDefinitionListClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
}

static void groast_type_definition_list_init(GroAstTypeDefinitionList *instance) {
}

static void l_dispose(GObject *object) {
	GroAstTypeDefinitionList *instance = GROAST_TYPE_DEFINITION_LIST(object);
	GroAstTypeDefinitionListPrivate *priv = groast_type_definition_list_get_instance_private(instance);
	L_SAFE_UNREF_PTR(priv->tdList);
	L_SAFE_UNREF_PTR(priv->typeDef);
	G_OBJECT_CLASS(groast_type_definition_list_parent_class)->dispose(object);
}

CatArrayWo *groast_type_definition_list_enlist(GroAstTypeDefinitionList *self) {
 
	CatArrayWo *result = cat_array_wo_new();
	GroAstTypeDefinitionList *tdl = self;
	while(tdl) {
		GroAstTypeDefinitionListPrivate *priv = groast_type_definition_list_get_instance_private(tdl);
		cat_array_wo_append(result, (GObject *) priv->typeDef);
		if (priv->tdList==NULL) {
			break;
		}
		tdl = (GroAstTypeDefinitionList *) grorun_itoken_get_value(priv->tdList);
	}
	cat_array_wo_reverse(result);
	return result;
  
}

GroAstTypeDefinitionList *groast_type_definition_list_new_1(GroRunIToken *tdList, GroRunIToken *typeDef) {
	GroAstTypeDefinitionList *instance = g_object_new(GROAST_TYPE_TYPE_DEFINITION_LIST, NULL);
	GroAstTypeDefinitionListPrivate *priv = groast_type_definition_list_get_instance_private(instance);
	priv->tdList = L_SAFE_REF_PTR(tdList);
	priv->typeDef = L_SAFE_REF_PTR(typeDef);
	return instance;
}

GroRunIToken *groast_type_definition_list_tk_tdList(GroAstTypeDefinitionList *self) {
	GroAstTypeDefinitionListPrivate *priv = groast_type_definition_list_get_instance_private(self);
	return priv->tdList;
}

GroAstTypeDefinitionList *groast_type_definition_list_get_tdList(GroAstTypeDefinitionList *self) {
	GroAstTypeDefinitionListPrivate *priv = groast_type_definition_list_get_instance_private(self);
	return priv->tdList==NULL ? NULL : (GroAstTypeDefinitionList *) grorun_itoken_get_value(priv->tdList);
}

GroRunIToken *groast_type_definition_list_tk_typeDef(GroAstTypeDefinitionList *self) {
	GroAstTypeDefinitionListPrivate *priv = groast_type_definition_list_get_instance_private(self);
	return priv->typeDef;
}

GroAstTypeDefinition *groast_type_definition_list_get_typeDef(GroAstTypeDefinitionList *self) {
	GroAstTypeDefinitionListPrivate *priv = groast_type_definition_list_get_instance_private(self);
	return priv->typeDef==NULL ? NULL : (GroAstTypeDefinition *) grorun_itoken_get_value(priv->typeDef);
}
