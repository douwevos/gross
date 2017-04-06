/* This file was generated by Gross-CC on 2017.04.04 AD at 21:26:40 CEST */
#ifndef GROASTPRODUCTION_DEFINITION_H_
#define GROASTPRODUCTION_DEFINITION_H_

#include <caterpillar.h>
#include "grorunfork.h"
#include "groastrhsrulelist.h"

G_BEGIN_DECLS

#define GROAST_TYPE_PRODUCTION_DEFINITION              (groast_production_definition_get_type())
#define GROAST_PRODUCTION_DEFINITION(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), groast_production_definition_get_type(), GroAstProductionDefinition))
#define GROAST_PRODUCTION_DEFINITION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROAST_TYPE_PRODUCTION_DEFINITION, GroAstProductionDefinitionClass))
#define GROAST_IS_PRODUCTION_DEFINITION(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROAST_TYPE_PRODUCTION_DEFINITION))
#define GROAST_IS_PRODUCTION_DEFINITION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROAST_TYPE_PRODUCTION_DEFINITION))
#define GROAST_PRODUCTION_DEFINITION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROAST_TYPE_PRODUCTION_DEFINITION, GroAstProductionDefinitionClass))


typedef struct _GroAstProductionDefinition               GroAstProductionDefinition;
typedef struct _GroAstProductionDefinitionPrivate        GroAstProductionDefinitionPrivate;
typedef struct _GroAstProductionDefinitionClass          GroAstProductionDefinitionClass;


struct _GroAstProductionDefinition {
	GObject parent;
};

struct _GroAstProductionDefinitionClass {
	GObjectClass parent_class;
};


GType groast_production_definition_get_type();

GroAstProductionDefinition *groast_production_definition_new_1(GroRunIToken *lhsName, GroRunIToken *ruleList);
GroRunIToken *groast_production_definition_tk_lhsName(GroAstProductionDefinition *self);
CatStringWo *groast_production_definition_get_lhsName(GroAstProductionDefinition *self);
GroRunIToken *groast_production_definition_tk_ruleList(GroAstProductionDefinition *self);
GroAstRhsRuleList *groast_production_definition_get_ruleList(GroAstProductionDefinition *self);

G_END_DECLS

#endif /* GROASTPRODUCTION_DEFINITION_H_ */
