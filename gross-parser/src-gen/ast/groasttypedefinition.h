/* This file was generated by Gross-CC on 2017.04.04 AD at 21:26:40 CEST */
#ifndef GROASTTYPE_DEFINITION_H_
#define GROASTTYPE_DEFINITION_H_

#include <caterpillar.h>
#include "grorunfork.h"
#include "groastidlist.h"

G_BEGIN_DECLS

#define GROAST_TYPE_TYPE_DEFINITION              (groast_type_definition_get_type())
#define GROAST_TYPE_DEFINITION(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), groast_type_definition_get_type(), GroAstTypeDefinition))
#define GROAST_TYPE_DEFINITION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROAST_TYPE_TYPE_DEFINITION, GroAstTypeDefinitionClass))
#define GROAST_IS_TYPE_DEFINITION(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROAST_TYPE_TYPE_DEFINITION))
#define GROAST_IS_TYPE_DEFINITION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROAST_TYPE_TYPE_DEFINITION))
#define GROAST_TYPE_DEFINITION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROAST_TYPE_TYPE_DEFINITION, GroAstTypeDefinitionClass))


typedef struct _GroAstTypeDefinition               GroAstTypeDefinition;
typedef struct _GroAstTypeDefinitionPrivate        GroAstTypeDefinitionPrivate;
typedef struct _GroAstTypeDefinitionClass          GroAstTypeDefinitionClass;


struct _GroAstTypeDefinition {
	GObject parent;
};

struct _GroAstTypeDefinitionClass {
	GObjectClass parent_class;
};


GType groast_type_definition_get_type();

GroAstTypeDefinition *groast_type_definition_new_1(GroRunIToken *symtype, GroRunIToken *symids);
GroRunIToken *groast_type_definition_tk_symids(GroAstTypeDefinition *self);
GroAstIdList *groast_type_definition_get_symids(GroAstTypeDefinition *self);
GroRunIToken *groast_type_definition_tk_symtype(GroAstTypeDefinition *self);
CatStringWo *groast_type_definition_get_symtype(GroAstTypeDefinition *self);

G_END_DECLS

#endif /* GROASTTYPE_DEFINITION_H_ */
