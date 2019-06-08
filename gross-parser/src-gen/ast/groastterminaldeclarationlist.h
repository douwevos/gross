/* This file was generated by Gross-CC on 2019.04.12 AD at 23:25:21 CEST */
#ifndef GROASTTERMINAL_DECLARATION_LIST_H_
#define GROASTTERMINAL_DECLARATION_LIST_H_

#include "groastterminaldeclaration.h"
#include "grorunfork.h"

G_BEGIN_DECLS

#define GROAST_TYPE_TERMINAL_DECLARATION_LIST              (groast_terminal_declaration_list_get_type())
#define GROAST_TERMINAL_DECLARATION_LIST(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), groast_terminal_declaration_list_get_type(), GroAstTerminalDeclarationList))
#define GROAST_TERMINAL_DECLARATION_LIST_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GROAST_TYPE_TERMINAL_DECLARATION_LIST, GroAstTerminalDeclarationListClass))
#define GROAST_IS_TERMINAL_DECLARATION_LIST(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GROAST_TYPE_TERMINAL_DECLARATION_LIST))
#define GROAST_IS_TERMINAL_DECLARATION_LIST_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GROAST_TYPE_TERMINAL_DECLARATION_LIST))
#define GROAST_TERMINAL_DECLARATION_LIST_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GROAST_TYPE_TERMINAL_DECLARATION_LIST, GroAstTerminalDeclarationListClass))


typedef struct _GroAstTerminalDeclarationList               GroAstTerminalDeclarationList;
typedef struct _GroAstTerminalDeclarationListPrivate        GroAstTerminalDeclarationListPrivate;
typedef struct _GroAstTerminalDeclarationListClass          GroAstTerminalDeclarationListClass;


struct _GroAstTerminalDeclarationList {
	GObject parent;
};

struct _GroAstTerminalDeclarationListClass {
	GObjectClass parent_class;
};


GType groast_terminal_declaration_list_get_type();

CatArrayWo *groast_terminal_declaration_list_enlist(GroAstTerminalDeclarationList *self);
GroAstTerminalDeclarationList *groast_terminal_declaration_list_new_1(GroRunIToken *tdlist, GroRunIToken *td);
GroRunIToken *groast_terminal_declaration_list_tk_td(GroAstTerminalDeclarationList *self);
GroAstTerminalDeclaration *groast_terminal_declaration_list_get_td(GroAstTerminalDeclarationList *self);
GroRunIToken *groast_terminal_declaration_list_tk_tdlist(GroAstTerminalDeclarationList *self);
GroAstTerminalDeclarationList *groast_terminal_declaration_list_get_tdlist(GroAstTerminalDeclarationList *self);

G_END_DECLS

#endif /* GROASTTERMINAL_DECLARATION_LIST_H_ */
