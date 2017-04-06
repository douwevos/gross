/*
   File:    gropmodelbuilder.c
   Project: gross-parser
   Author:  Douwe Vos
   Date:    Mar 20, 2017
   e-mail:  dmvos2000(at)yahoo.com

   Copyright (C) 2017 Douwe Vos.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "gropmodelbuilder.h"
#include "gropproductionpartlist.h"
#include "../../src-gen/ast/groastrhssub.h"
#include "../../src-gen/ast/groastrhssublist.h"
#include "../../src-gen/ast/groastrhsunarypart.h"
#include "../../src-gen/ast/groastsymbolpart.h"
#include "../ast/groastirhsenlistable.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "GroPModelBuilder"
#include <logging/catlog.h>

struct _GroPModelBuilderPrivate {
	GroAstSpec *specification;
	GroIMessageHandler *msg_handler;
	gboolean success;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPModelBuilder, grop_model_builder, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPModelBuilder)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_model_builder_class_init(GroPModelBuilderClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_model_builder_init(GroPModelBuilder *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//	GroPModelBuilder *instance = GROP_MODEL_BUILDER(object);
//	GroPModelBuilderPrivate *priv = grop_model_builder_get_instance_private(instance);
	G_OBJECT_CLASS(grop_model_builder_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_model_builder_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPModelBuilder *grop_model_builder_new(GroAstSpec *specification, GroIMessageHandler *msg_handler) {
	GroPModelBuilder *result = g_object_new(GROP_TYPE_MODEL_BUILDER, NULL);
	cat_ref_anounce(result);
	GroPModelBuilderPrivate *priv = grop_model_builder_get_instance_private(result);
	priv->specification = cat_ref_ptr(specification);
	priv->msg_handler = cat_ref_ptr(msg_handler);
	priv->success = TRUE;
	return result;
}

static CatArrayWo *l_handler_entries(GroPModelBuilder *builder, GroPModel *model, CatIIterator *iter, CatAtomicInteger *offset_sequence, CatStringWo *label);



GroPModel *grop_model_builder_do_build(GroPModelBuilder *builder) {
	GroPModelBuilderPrivate *priv = grop_model_builder_get_instance_private(builder);
	GroPModel *result = grop_model_new();


	cat_log_debug("hier");

	/* declare terminals */
	GroAstTerminalDeclarationList *term_decl_list = groast_spec_get_td(priv->specification);
	CatArrayWo *term_decl_enlisted = groast_terminal_declaration_list_enlist(term_decl_list);



	CatIIterator *iter = cat_array_wo_iterator(term_decl_enlisted);
	cat_unref_ptr(term_decl_enlisted);
	while(cat_iiterator_has_next(iter)) {
		GroRunIToken *tk_term_decl = GRORUN_ITOKEN(cat_iiterator_next(iter));

		GroAstTerminalDeclaration *term_decl = GROAST_TERMINAL_DECLARATION(grorun_itoken_get_value(tk_term_decl));
		cat_log_debug("term_decl=%O", term_decl);
		CatArrayWo *terms = groast_terminal_declaration_enlist(term_decl);
		CatIIterator *t_iter = cat_array_wo_iterator(terms);
		cat_unref_ptr(terms);
		while(cat_iiterator_has_next(t_iter)) {
			GroRunIToken *token = GRORUN_ITOKEN(cat_iiterator_next(t_iter));
			cat_log_debug("token=%O", token);
			CatStringWo *symbol_name = CAT_STRING_WO(grorun_itoken_get_value(token));
			if (grop_model_get_symbol_by_name(result, symbol_name)!=NULL) {
				cat_log_error("symbol_name=%O", token);
				CatStringWo *msg = cat_string_wo_new_with("Symbol was already defined");
				gro_imessage_handler_message(priv->msg_handler, msg, grorun_itoken_get_location(token));
				cat_unref_ptr(msg);
			} else {
				grop_model_addTerminal(result, symbol_name);
			}
		}
		cat_unref_ptr(t_iter);
	}
	cat_unref_ptr(iter);




	/* declare non-terminals */
	GroAstProductionDefinitionList *prod_def_list = groast_spec_get_pl(priv->specification);
	CatArrayWo *prod_def_enlisted = groast_production_definition_list_enlist(prod_def_list);
	CatIIterator *pd_iter = cat_array_wo_iterator(prod_def_enlisted);
	while(cat_iiterator_has_next(pd_iter)) {
		GroRunIToken *tk_pd = GRORUN_ITOKEN(cat_iiterator_next(pd_iter));
		GroAstProductionDefinition *prod_def = GROAST_PRODUCTION_DEFINITION(grorun_itoken_get_value(tk_pd));
		GroRunIToken *tk_lhs_name = groast_production_definition_tk_lhsName(prod_def);
		CatStringWo *lhs_name = CAT_STRING_WO(grorun_itoken_get_value(tk_lhs_name));
		cat_log_error("declaring non-term:%O", lhs_name);
		if (grop_model_get_symbol_by_name(result, lhs_name)!=NULL) {
			CatStringWo *msg = cat_string_wo_new_with("Symbol was already defined");
			gro_imessage_handler_message(priv->msg_handler, msg, grorun_itoken_get_location(tk_lhs_name));
			cat_unref_ptr(msg);
		} else {
			grop_model_add_non_terminal(result, lhs_name);
		}
	}
	cat_unref_ptr(pd_iter);



	/* create rules */
	pd_iter = cat_array_wo_iterator(prod_def_enlisted);
	cat_unref_ptr(prod_def_enlisted);
	while(cat_iiterator_has_next(pd_iter)) {
		GroRunIToken *tk_pd = GRORUN_ITOKEN(cat_iiterator_next(pd_iter));
		GroAstProductionDefinition *prod_def = GROAST_PRODUCTION_DEFINITION(grorun_itoken_get_value(tk_pd));
		GroRunIToken *tk_lhs_name = groast_production_definition_tk_lhsName(prod_def);
		CatStringWo *lhs_name = CAT_STRING_WO(grorun_itoken_get_value(tk_lhs_name));
		GroPNonTerminal *lhs_nt = grop_model_get_non_terminal_by_name(result, lhs_name);
		GroAstRhsRuleList *rule_list = groast_production_definition_get_ruleList(prod_def);


		CatAtomicInteger *ai = cat_atomic_integer_new_val(-1);
		CatArrayWo *rules = groast_rhs_rule_list_enlist(rule_list);
		CatIIterator *ru_iter = cat_array_wo_iterator(rules);
		CatArrayWo *entries = l_handler_entries(builder, result, ru_iter, ai, NULL);
		cat_array_wo_remove_first(entries, NULL);

		CatIIterator *e_iter = cat_array_wo_iterator(entries);
		while(cat_iiterator_has_next(e_iter)) {
			GroPProductionPartList *part_list = (GroPProductionPartList *) cat_iiterator_next(e_iter);
			int pp_offset = grop_production_part_list_get_offset(part_list);
			CatStringWo *pp_label = grop_production_part_list_get_label(part_list);
			CatArrayWo *pp_list = grop_production_part_list_get_list(part_list);
			CatArrayWo *pp_excluded = grop_production_part_list_get_excluded(part_list);
			grop_model_add_production_with_excl(result, pp_offset, pp_label, lhs_nt, pp_list, pp_excluded);
		}
		cat_unref_ptr(e_iter);

	}
	cat_unref_ptr(pd_iter);

	return result;
}


static void l_append_part(CatArrayWo *output_pp_arrays, GroPProductionPart *part) {
	CatIIterator *iter = cat_array_wo_iterator(output_pp_arrays);
	while(cat_iiterator_has_next(iter)) {
		GroPProductionPartList *part_list = (GroPProductionPartList *) cat_iiterator_next(iter);
		grop_production_part_list_add(part_list, part);
	}
	cat_unref_ptr(iter);
}

static GroPProductionPart *l_handle_symbol_part(GroPModelBuilder *builder, GroPModel *model, GroAstSymbolPart *sym_part) {
	CatStringWo *sym_name = groast_symbol_part_get_symName(sym_part);
	GroPSymbol *symbol = grop_model_get_symbol_by_name(model, sym_name);
	GroPProductionPart *result = NULL;

	if (symbol==NULL) {
		GroPModelBuilderPrivate *priv = grop_model_builder_get_instance_private(builder);
		priv->success = FALSE;
//		throw new RuntimeException("symbol with name "+sym_name+" not found");
	} else {
		result = grop_production_part_new(symbol, groast_symbol_part_get_label(sym_part));
	}
	return result;
}

static CatArrayWo *l_handler_entries(GroPModelBuilder *builder, GroPModel *model, CatIIterator *iter, CatAtomicInteger *offset_sequence, CatStringWo *label) {
	GroPModelBuilderPrivate *priv = grop_model_builder_get_instance_private(builder);
	CatArrayWo *output_pp_arrays = cat_array_wo_new();

	int offset = -1;
	if (offset_sequence!=NULL) {
		offset = cat_atomic_integer_increment(offset_sequence);
	}
	GroPProductionPartList *e = grop_production_part_list_new(offset, label);
	cat_array_wo_append(output_pp_arrays, (GObject *) e);
	cat_unref(e);

	while(priv->success && cat_iiterator_has_next(iter)) {
		GObject *rhs_entry = cat_iiterator_next(iter);
		if (GRORUN_IS_ITOKEN(rhs_entry)) {
			rhs_entry = grorun_itoken_get_value(rhs_entry);
		}

		if (GROAST_IS_RHS_SUB_LIST(rhs_entry)) {
			/* this is a sub list  (A B | B | C D E) */

			GroAstRhsSubList *rhs_sub_list = (GroAstRhsSubList *) rhs_entry;
			CatArrayWo *sub_parts = groast_rhs_sub_list_enlist(rhs_sub_list);
			CatIIterator *sp_iter = cat_array_wo_iterator(sub_parts);
			cat_unref_ptr(sub_parts);
			CatArrayWo *sub_pp_arrays = l_handler_entries(builder, model, sp_iter, NULL, NULL);
			cat_unref_ptr(sp_iter);
			if (sub_pp_arrays) {
				cat_array_wo_remove_first(sub_pp_arrays, NULL);
				GroPNonTerminal *sub_lhs = grop_model_add_sub_productions(model, sub_pp_arrays);
				GroPProductionPart *slpp = grop_production_part_new((GroPSymbol *) sub_lhs, NULL);
				l_append_part(output_pp_arrays, slpp);
				cat_unref_ptr(slpp);
				cat_unref_ptr(sub_pp_arrays);
			}

		} else if (GROAST_IS_RHS_UNARY_PART(rhs_entry)) {
			/* this is a unary operation  A+, (C | D)*, (F)? */
			GroAstRhsUnaryPart *rhs_unary = (GroAstRhsUnaryPart *) rhs_entry;
			GroAstIRhsPart *un_entry = groast_rhs_unary_part_get_entry(rhs_unary);
			switch(groast_rhs_unary_part_get_op(rhs_unary)) {
				case GRO_AST_UN_PLUS :
				case GRO_AST_UN_STAR : {
					/* the * operator means 0 or more repetitions */

					GroPSymbol *sym_to_rep = NULL;
					if (GROAST_IS_SYMBOL_PART(un_entry)) {
						/* This is a single symbol which will be repeated */
						CatStringWo *sym_id = groast_symbol_part_get_symName((GroAstSymbolPart *) un_entry);
						sym_to_rep = grop_model_get_symbol_by_name(model, sym_id);
						if (sym_to_rep==NULL) {

							priv->success = FALSE;
//							throw new RuntimeException("symbol with name "+symId+" not found");
							goto done;
						}
					} else if (GROAST_IS_IRHS_ENLISTABLE(un_entry)) {
						/* This is a complex sub list which is repeated. For this we will create an additional non terminal.
						 */
//							CatIIterator *sub_iter = cat_array_wo_iterator((CatArrayWo *) un_entry);
//							CatArrayWo *sub_pp_arrays = l_handle_entries(model, msg_handler, sub_iter);
//							cat_unref_ptr(sub_iter);
//							cat_array_wo_remove_first(sub_pp_arrays, NULL);
//							sym_to_rep = (GroMSymbol *) gro_model_add_sub_productions(model, sub_pp_arrays);
					}

					if (sym_to_rep!=NULL) {
						/* lets insert new rules
						 *
						 *    sub_nterm ::=
						 *    			  sub_nterm sym_to_rep
						 *    			| <sym_to_rep> (in case it is +)
						 *    			;
						 *
						 */
						GroPNonTerminal *sub_nterm = grop_model_create_sub_non_terminal(model);
						CatArrayWo *pp_one = cat_array_wo_new();
						GroPProductionPart *pa1 = grop_production_part_new((GroPSymbol *) sub_nterm, NULL);
						cat_array_wo_append(pp_one, (GObject *) pa1);
						cat_unref_ptr(pa1);
						GroPProductionPart *pa2 = grop_production_part_new((GroPSymbol *) sym_to_rep, NULL);
						cat_array_wo_append(pp_one, (GObject *) pa2);
						cat_unref_ptr(pa2);
						grop_model_add_production_with_excl(model, -1, NULL, sub_nterm, pp_one, NULL);
						cat_unref_ptr(pp_one);

						CatArrayWo *pp_two = cat_array_wo_new();
						if (groast_rhs_unary_part_get_op(rhs_unary)==GRO_AST_UN_PLUS) {
							GroPProductionPart *pa3 = grop_production_part_new((GroPSymbol *) sym_to_rep, NULL);
							cat_array_wo_append(pp_two, (GObject *) pa3);
							cat_unref_ptr(pa3);
						}
						grop_model_add_production_with_excl(model, -1, NULL, sub_nterm, pp_two, NULL);
						cat_unref_ptr(pp_two);

						GroPProductionPart *pp_res = grop_production_part_new((GroPSymbol *) sub_nterm, NULL);
						l_append_part(output_pp_arrays, pp_res);
						cat_unref_ptr(pp_res);
//						} else {
//							result = FALSE;
					}
				} break;
				case GRO_AST_UN_EXCL : {
					GroPProductionPart *psym_part = NULL;
					/* the ? operator means an optional entry */
					if (GROAST_IS_SYMBOL_PART(un_entry)) {
						GroAstSymbolPart *un_sym = (GroAstSymbolPart *) un_entry;
						/* This is a single symbol which is optional */
						CatStringWo *sym_id = groast_symbol_part_get_symName(un_sym);
						GroPSymbol *opt_sym = grop_model_get_symbol_by_name(model, sym_id);
						if (opt_sym==NULL) {
							priv->success = FALSE;
//							throw new RuntimeException("symbol with name "+symId+" not found");
							goto done;
						}
						psym_part = l_handle_symbol_part(builder, model, un_sym);


					} else if (GROAST_IS_IRHS_ENLISTABLE(un_entry)) {
						/* This is a complex sub list which is repeated. For this we will create an additional non terminal.
						 */
						CatArrayWo *enlisted = groast_irhs_enlistable_enlist((GroAstIRhsEnlistable *) un_entry);
						CatIIterator *enl_iter = cat_array_wo_iterator(enlisted);

						CatArrayWo *sub_pp_arrays = l_handler_entries(builder, model, enl_iter, NULL, NULL);
						if (sub_pp_arrays) {
							cat_array_wo_remove_first(sub_pp_arrays, NULL);
							if (cat_array_wo_size(sub_pp_arrays)==1) {
								GroPProductionPartList *sub_pp_list = (GroPProductionPartList *) cat_array_wo_get_first(sub_pp_arrays);
								psym_part = grop_production_part_list_get_single_part(sub_pp_list);
								cat_ref_ptr(psym_part);
							}

							if (psym_part==NULL) {
								GroPNonTerminal *sub_nt = grop_model_add_sub_productions(model, sub_pp_arrays);
								psym_part = grop_production_part_new((GroPSymbol *) sub_nt, NULL);
							}
						}
						cat_unref_ptr(enl_iter);
						cat_unref_ptr(enlisted);
					}

					if (psym_part) {


						int pp_count = cat_array_wo_size(output_pp_arrays);
						for(int idx=0; idx<pp_count; idx++) {
							GroPProductionPartList *production_part_list = (GroPProductionPartList *) cat_array_wo_get(output_pp_arrays, idx);
							GroPProductionPartList *duplicate = grop_production_part_list_duplicate(production_part_list);

							grop_production_part_list_add(duplicate, psym_part);
							cat_array_wo_append(output_pp_arrays, (GObject *) duplicate);
							grop_production_part_list_exclude(production_part_list, psym_part);
						}
					}


				} break;

			}
		} else if (GROAST_IS_RHS_SUB(rhs_entry)) {
			/* this is entry list in a sub list A B C */

			GroAstRhsSub *sub = (GroAstRhsSub *) rhs_entry;
			CatArrayWo *sub_enlisted = groast_rhs_sub_enlist(sub);
			CatIIterator *se_iter = cat_array_wo_iterator(sub_enlisted);
			CatArrayWo *sub_pp_arrays = l_handler_entries(builder, model, se_iter, NULL, label);
			if (sub_pp_arrays) {
				cat_array_wo_append_all(output_pp_arrays, sub_pp_arrays);
			}

//				CatIIterator *sub_iter = gro_bnf_rhs_production_part_iterator((GroBnfRhs *) rhs_entry);
//				CatArrayWo *sub_pp_arrays = l_handle_entries(model, msg_handler, sub_iter);
//				cat_unref_ptr(sub_iter);
//				cat_array_wo_append_all(output_pp_arrays, sub_pp_arrays);
//				cat_unref_ptr(sub_pp_arrays);
//
		} else if (GROAST_IS_RHS_RULE(rhs_entry)) {
			GroAstRhsRule *rule = (GroAstRhsRule *) rhs_entry;
			CatArrayWo *rl_list = groast_rhs_rule_enlist(rule);
			CatIIterator *rl_iter = cat_array_wo_iterator(rl_list);
			CatArrayWo *sub_pp_arrays = l_handler_entries(builder, model, rl_iter, offset_sequence, groast_rhs_rule_get_imark(rule));
			if (sub_pp_arrays) {
				cat_array_wo_append_all(output_pp_arrays, sub_pp_arrays);
				cat_unref_ptr(sub_pp_arrays);
			}
			cat_unref_ptr(rl_iter);
			cat_unref_ptr(rl_list);
		} else if (GROAST_IS_SYMBOL_PART(rhs_entry)) {
			GroAstSymbolPart *part = (GroAstSymbolPart *) rhs_entry;
			GroPProductionPart *psym_part = l_handle_symbol_part(builder, model, part);
			if (psym_part!=NULL) {
				l_append_part(output_pp_arrays, psym_part);
			} else {
//					result = false;
			}
			cat_unref_ptr(psym_part);
		} else {
			cat_log_error("unknown type:%O", rhs_entry);
//			throw new RuntimeException("unknown entry type:"+rhsEntry);
			priv->success = FALSE;
			goto done;
//			} else if (GRO_IS_BNF_RHS_ACTION_CODE(rhs_entry)) {
//				GroBnfRhsActionCode *code_part = (GroBnfRhsActionCode *) rhs_entry;
//				GroMProdActionPart *pact_part = gro_m_prod_action_part_new(gro_bnf_rhs_action_code_get_code(code_part));
//				l_append_part(output_pp_arrays, pact_part);
		}
	}
done:
	return output_pp_arrays;

}

/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);
	cat_string_wo_format(append_to, "%s[%p]", iname, self);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
