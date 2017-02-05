/* This file was generated by Gross-CC on 2016.11.30 AD at 21:31:20 CET */
#ifndef GROASTPRODUCTION_DEFINITION_LIST_H_
#define GROASTPRODUCTION_DEFINITION_LIST_H_

#include "groastproductiondefinition.h"
#include "grorunfork.h"

G_BEGIN_DECLS

#define GROAST_TYPE_PRODUCTION_DEFINITION_LIST              (groast_production_definition_list_get_type())
#define GROAST_PRODUCTION_DEFINITION_LIST(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), groast_production_definition_list_get_type(), GroAstProductionDefinitionList))
#define GROAST_PRODUCTION_DEFINITION_LIST_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROAST_TYPE_PRODUCTION_DEFINITION_LIST, GroAstProductionDefinitionListClass))
#define GROAST_IS_PRODUCTION_DEFINITION_LIST(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROAST_TYPE_PRODUCTION_DEFINITION_LIST))
#define GROAST_IS_PRODUCTION_DEFINITION_LIST_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROAST_TYPE_PRODUCTION_DEFINITION_LIST))
#define GROAST_PRODUCTION_DEFINITION_LIST_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROAST_TYPE_PRODUCTION_DEFINITION_LIST, GroAstProductionDefinitionListClass))


typedef struct _GroAstProductionDefinitionList               GroAstProductionDefinitionList;
typedef struct _GroAstProductionDefinitionListPrivate        GroAstProductionDefinitionListPrivate;
typedef struct _GroAstProductionDefinitionListClass          GroAstProductionDefinitionListClass;


struct _GroAstProductionDefinitionList {
	GObject parent;
};

struct _GroAstProductionDefinitionListClass {
	GObjectClass parent_class;
};


GType groast_production_definition_list_get_type();

CatArrayWo *groast_production_definition_list_enlist(GroAstProductionDefinitionList *self);
GroAstProductionDefinitionList *groast_production_definition_list_new_1(GroRunIToken *plist, GroRunIToken *prod);
GroAstProductionDefinitionList *groast_production_definition_list_new_2(GroRunIToken *prod);
GroRunIToken *groast_production_definition_list_tk_plist(GroAstProductionDefinitionList *self);
GroAstProductionDefinitionList *groast_production_definition_list_get_plist(GroAstProductionDefinitionList *self);
GroRunIToken *groast_production_definition_list_tk_prod(GroAstProductionDefinitionList *self);
GroAstProductionDefinition *groast_production_definition_list_get_prod(GroAstProductionDefinitionList *self);

G_END_DECLS

#endif /* GROASTPRODUCTION_DEFINITION_LIST_H_ */