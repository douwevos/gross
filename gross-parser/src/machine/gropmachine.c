/*
   File:    gropmachine.c
   Project: gross-parser
   Author:  Douwe Vos
   Date:    Mar 16, 2017
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

#include "gropmachine.h"
#include "gropdotstate.h"
#include "gropkernel.h"
#include "gropsymbolkey.h"
#include "gropdotlink.h"
#include "gropbuildentry.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "GroPMachine"
#include <logging/catlog.h>

struct _GroPMachinePrivate {
	GroIMessageHandler *message_handler;
	GroPModel *model;

	int kernel_sequence;
	int state_sequence;

	CatHashMapWo *map;			// <Kernel, BuildEntry>
	CatHashMapWo *dot_links;	// <DotState, DotLink>

};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(GroPMachine, grop_machine, G_TYPE_OBJECT,
		G_ADD_PRIVATE(GroPMachine)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void grop_machine_class_init(GroPMachineClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void grop_machine_init(GroPMachine *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//	GroPMachine *instance = GROP_MACHINE(object);
//	GroPMachinePrivate *priv = grop_machine_get_instance_private(instance);
	G_OBJECT_CLASS(grop_machine_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(grop_machine_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


GroPMachine *grop_machine_new(GroIMessageHandler *message_handler, GroPModel *model) {
	GroPMachine *result = g_object_new(GROP_TYPE_MACHINE, NULL);
	cat_ref_anounce(result);
	GroPMachinePrivate *priv = grop_machine_get_instance_private(result);
	priv->message_handler = cat_ref_ptr(message_handler);
	priv->model = cat_ref_ptr(model);
	priv->dot_links = cat_hash_map_wo_new((GHashFunc) grop_dot_state_hash, (GEqualFunc) grop_dot_state_equal);
	priv->kernel_sequence = 0;
	priv->state_sequence = 0;
	priv->map = cat_hash_map_wo_new((GHashFunc) grop_kernel_hash, (GEqualFunc) grop_kernel_equal);
	return result;
}

gboolean l_map_forward(GroPMachine *machine, GroPBuildEntry *build_entry, GroPDotLink *main_dot_link);

void grop_machine_build(GroPMachine *machine) {
	GroPMachinePrivate *priv = grop_machine_get_instance_private(machine);
	cat_log_verbose("Calculating Nullability");
	grop_model_calculate_nullabilty(priv->model);
	cat_log_verbose("Calculating first sets");
	grop_model_calculate_first_sets(priv->model);
	cat_log_verbose("Creating states");

	GroPProduction *prod = grop_model_get_production(priv->model, 0);

	CatArrayWo *work_list = cat_array_wo_new();	// <Kernel>

	GroPKernel *dot_set = grop_kernel_new(priv->kernel_sequence++);
	GroPDotState *ds = grop_dot_state_new(prod, 0, NULL);
	GroPDotLink *start_dot_link = grop_machine_get_or_create_dot_link(machine, ds);
	cat_unref_ptr(ds);

	grop_kernel_add(dot_set, start_dot_link);
	cat_array_wo_append(work_list, (GObject *) dot_set);


	gboolean had_changes = TRUE;
	int round = 0;
	while(had_changes) {
		round++;
		had_changes = FALSE;
		cat_log_error("Creating statemachine iteration %d, nr-of-states thusfar %d", round, cat_hash_map_wo_size(priv->map));
		while(cat_array_wo_size(work_list)!=0) {

			GroPKernel *main_dot_set = NULL;
			cat_array_wo_remove_first(work_list, (GObject **) &main_dot_set);
			if (!GROP_IS_KERNEL(main_dot_set)) {
				cat_log_error("main_dot_set not a kernel:%O", main_dot_set);
				cat_stacktrace_print();
			}
			GroPBuildEntry *build_entry = (GroPBuildEntry *) cat_hash_map_wo_get(priv->map, (GObject *) main_dot_set);
			if (build_entry==NULL) {
				build_entry = grop_build_entry_new(main_dot_set, priv->state_sequence++);
				cat_hash_map_wo_put(priv->map, (GObject *) main_dot_set, (GObject *) build_entry);
			}
			cat_log_debug("--------------------------- ");
			cat_log_debug("Run state: %d  %d/work-list=%d (%d)", grop_build_entry_get_id(build_entry), cat_hash_map_wo_size(priv->map), cat_array_wo_size(work_list), round);

			CatIIterator *mds_iter = grop_kernel_iterator(main_dot_set);
			while(cat_iiterator_has_next(mds_iter)) {
				GroPDotLink *main_dot_link = (GroPDotLink *) cat_iiterator_next(mds_iter);
				had_changes |= l_map_forward(machine, build_entry, main_dot_link);
			}
			cat_unref_ptr(mds_iter);

			CatHashMapWo *build_entry_fwd_map = grop_build_entry_get_forward_map(build_entry);
			CatArrayWo *fwd_syms = cat_hash_map_wo_enlist_keys(build_entry_fwd_map, NULL);
			CatIIterator *fwds_iter = cat_array_wo_iterator(fwd_syms);
			while(cat_iiterator_has_next(fwds_iter)) {
				GroPSymbolKey *symbol = (GroPSymbolKey *) cat_iiterator_next(fwds_iter);
				GroPKernel *fwd_kernel = (GroPKernel *) cat_hash_map_wo_get(build_entry_fwd_map, symbol);
				cat_log_debug("  fwdKernel=%d, sym=%O", grop_kernel_get_id(fwd_kernel), symbol);
				if (grop_symbol_key_get_symbol(symbol)==(GroPSymbol *) grop_model_get_eof_terminal(priv->model)) {
					continue;
				}
				if (cat_hash_map_wo_get(priv->map, fwd_kernel)!=NULL) {
					GroPBuildEntry *mapped_build_entry = (GroPBuildEntry *) cat_hash_map_wo_get(priv->map, fwd_kernel);
					GroPKernel *mapped_kernel = grop_build_entry_get_kernel(mapped_build_entry);
					cat_log_debug("    mapped_kernel=%O", mapped_kernel);
					cat_hash_map_wo_put(build_entry_fwd_map, (GObject *) symbol, (GObject *) mapped_kernel);
				} else {
					cat_array_wo_append(work_list, (GObject *) fwd_kernel);
				}
			}
			cat_unref_ptr(fwds_iter);

		}

		cat_log_debug("Analyzing DotLinks for recursion");

		CatIMapIterator *miter = cat_hash_map_wo_iterator(priv->dot_links);
		gpointer key;
		GroPDotLink *dot_link;
		while(cat_imap_iterator_next(miter, &key, &dot_link)) {
			cat_log_debug("  %O", dot_link);

			GroPDotState *dl_ds = grop_dot_link_get_dot_state(dot_link);
			if (grop_dot_state_is_at_end(dl_ds)) {
				GroPProduction *dl_prod = grop_dot_state_get_production(dl_ds);
				GroPNonTerminal *lhs_nt = grop_production_get_lhs(dl_prod);
				cat_log_debug("  ꩜ Testing");
				cat_log_debug("      ⬡ %O", lhs_nt);
				CatIIterator *p_iter = grop_non_terminal_iterator(lhs_nt);
				while(cat_iiterator_has_next(p_iter)) {
					GroPProduction *lhs_prod = (GroPProduction *) cat_iiterator_next(p_iter);
					cat_log_debug("      ⬅ %O", lhs_prod);
					GroPDotState *tds = grop_dot_state_new(lhs_prod, 0, NULL);
					while(!grop_dot_state_is_at_end(tds)) {
						GroPDotState *shifted = grop_dot_state_shift_normal(tds);
						GroPSymbol *sad = grop_dot_state_get_symbol_at_dot(tds);
						cat_log_debug("       ⬌ %O    %O", tds, shifted);
						if (GROP_IS_NON_TERMINAL(sad)) {
							GroPNonTerminal *nterec = (GroPNonTerminal *) sad;
							GroPSymbolSet *firstset = grop_non_terminal_get_first_set(nterec);
							if (grop_symbol_set_contains(firstset, lhs_nt)) {
								GroPDotLink *tdotlink = cat_hash_map_wo_get(priv->dot_links, shifted);
								if (tdotlink!=NULL) {
									cat_log_debug("          Adding reference %O", grop_dot_link_get_dot_state(tdotlink));
									had_changes |= grop_dot_link_add_referred_by_state(dot_link, grop_dot_link_get_dot_state(tdotlink));
								}
							}
						}
						cat_ref_ptr(shifted);
						cat_unref_ptr(tds);
						tds = shifted;
					}
					cat_unref_ptr(tds);
				}
				cat_unref_ptr(p_iter);
			}
		}
		cat_unref_ptr(miter);

//		for(DotLink dotLink : dotLinks.values()) {
//			cat_log_debug("  %s", dotLink);
//
//		}
//
		cat_hash_map_wo_enlist_keys(priv->map, work_list);
//		workList.addAll(map.keySet());
//	}
//
//	logger.log(Level.VERBOSE, "Creating states done in "+round+" rounds");
//
//
//	ArrayList<BuildEntry> enlistedEntries = new ArrayList<BuildEntry>(map.values());
//	Collections.sort(enlistedEntries, new Comparator<BuildEntry>() {
//		@Override
//		public int compare(BuildEntry o1, BuildEntry o2) {
//			return o1.id<o2.id ? -1 : (o1.id>o2.id ? 1 : 0);
//		}
//	});
//	states = new LrarState[map.size()];
//	for(BuildEntry build_entry : enlistedEntries) {
//		states[build_entry.id] = build_entry.buildState();
//	}
//
//	map.clear();
//	for(BuildEntry b : enlistedEntries) {
//		map.put(b.kernel, b);
//	}
//
//
//
//	int bidx=-1;
//	for(BuildEntry build_entry : enlistedEntries) {
//		bidx++;
//		if (logger.isEnabled(Level.DEBUG)) {
//			cat_log_debug("");
//			build_entry.describe(System.out, dotLinks);
//		}
//
//		logger.log(Level.VERBOSE, "  Creating basic forward transitions "+bidx+"/"+map.size());
//
//		LrarState lrarState = states[build_entry.state.id];
//		for(SymbolKey sym : build_entry.forwardMap.keySet()) {
//			if (sym.isNullified) {
//				continue;
//			}
//			TransitionsForSymbol transForSym = lrarState.getOrCreateTransitionsForSymbol(sym.symbol);
//			if (sym.symbol == model.getEofTerminal()) {
//				transForSym.addTransition(new AcceptTransition());
//			} else {
//				Kernel destDotSet = build_entry.forwardMap.get(sym);
//				BuildEntry destEntry = map.get(destDotSet);
//				if (destEntry==null) {
//					for(DotState ds : destDotSet.main.keySet()) {
//						logger.log(Level.WARN, "    ds=%s", ds);
//					}
//					for(BuildEntry be : map.values()) {
//						logger.log(Level.WARN, "   be.dotset=%s", be.kernel);
//					}
//				}
//				LrarState destLrarState = states[destEntry.state.id];
//				transForSym.addTransition(new ShiftTransition("BASC", destLrarState));
//			}
//		}
//
//		logger.log(Level.VERBOSE, "  Creating reduce transitions based on linked-lists "+bidx+"/"+map.size());
//
//
//		for(DotLink dotLink : build_entry.kernel) {
//			cat_log_debug("    dotLink "+dotLink);
//
//			if (dotLink.dotState.isAtEnd()) {
//				/* This dotLink reached the end of the production. We need to insert ReduceTransitions for all symbols that follow.
//				 */
//				SymbolSet followSet = createFollowSet(dotLink, new HashSet<DotLink>());
//				for(Symbol sym : followSet) {
//					TransitionsForSymbol transForSym = lrarState.getOrCreateTransitionsForSymbol(sym);
//					transForSym.addTransition(new ReduceTransition("LL", dotLink.dotState));
//				}
//				cat_log_debug("     followSet="+followSet);
//			} else if (!dotLink.dotState.isTerminated()) {
//				DotState terminated = dotLink.dotState.createTerminated();
//				if (allowNonCloseReduce(terminated)) {
//					DotLink terminatedDotLink = getOrCreateDotLink(terminated);
//
//
//					SymbolSet followSet = createFollowSet(dotLink, new HashSet<DotLink>());
//					for(Symbol sym : followSet) {
//						TransitionsForSymbol transForSym = lrarState.getOrCreateTransitionsForSymbol(sym);
//						transForSym.addTransition(new ReduceTransition("TERM", terminatedDotLink.dotState));
//					}
//					cat_log_debug("     followSet="+followSet);
//				}
//
//			}
//		}
//
//	}
//
//
////		if (logger.isEnabled(Level.VERBOSE)) {
////			for(LrarState state : states){
////				state.describe(System.out, false, dotLinks);
////				for(DotLink dotLink : state.kernel) {
////
////					if (dotLink.dotState.isAtEnd()) {
////						/* This dotLink reached the end of the production. We need to insert ReduceTransitions for all symbols that follow.
////						 */
////						SymbolSet followSet = createFollowSet(dotLink, new HashSet<DotLink>());
////						cat_log_debug("   followSet="+followSet);
////					}
////				}
////			}
////		}
	}
}


GroPDotLink *grop_machine_get_or_create_dot_link(GroPMachine *machine, GroPDotState *dot_state) {
	GroPMachinePrivate *priv = grop_machine_get_instance_private(machine);
	GroPDotLink *dot_link = (GroPDotLink *) cat_hash_map_wo_get(priv->dot_links, dot_state);
	if (dot_link==NULL) {
		dot_link = grop_dot_link_new(dot_state);
		cat_hash_map_wo_put(priv->dot_links, (GObject *) dot_state, (GObject *) dot_link);
		cat_unref(dot_link);
	}
	return dot_link;
}


static void l_create_forward_mapping(GroPMachinePrivate *priv, CatHashMapWo *forward_map, GroPSymbolKey *symbol_at_dot, GroPDotLink *follow_dot_link) {
	GroPKernel *dot_set = (GroPKernel *) cat_hash_map_wo_get(forward_map, symbol_at_dot);
	if (dot_set==NULL) {
		dot_set = grop_kernel_new(priv->kernel_sequence++);
		cat_log_debug("new:%O", dot_set);
		cat_hash_map_wo_put(forward_map, (GObject *) symbol_at_dot, (GObject *) dot_set);
//		cat_unref(dot_set);
	}
//	cat_log_debug("                       add-shift sym=%O, dotset=%O, state=%O", symbol_at_dot, dot_set, follow_dot_link);
	cat_log_debug("kernel=%O", dot_set);
	grop_kernel_add(dot_set, follow_dot_link);
}

gboolean l_recurse_worward(GroPMachine *machine, GroPBuildEntry *build_entry, GroPDotLink *referred_link, GroPProduction *cons_prod, CatHashSet /*<Production>*/ *considered, CatStringWo *indent) {
	GroPMachinePrivate *priv = grop_machine_get_instance_private(machine);
	cat_log_debug("%O        referred_link=%O, cons_prod=%O", indent, referred_link, cons_prod);
	gboolean result = FALSE;
	GroPDotState *t_ds = grop_dot_state_new(cons_prod, 0, NULL);
	GroPDotLink *main_link = grop_machine_get_or_create_dot_link(machine, t_ds);
	cat_unref_ptr(t_ds);

	GroPDotState *shifted_referrer = grop_dot_state_shift_normal(grop_dot_link_get_dot_state(referred_link));
	if (shifted_referrer!=NULL) {
		result = grop_dot_link_add_referred_by_state(main_link, shifted_referrer);
	}

	CatArrayWo /*<DotLink>*/ *next_level = cat_array_wo_new();
	while(TRUE) {
		GroPSymbol *cons_prod_sym = grop_dot_state_get_symbol_at_dot(grop_dot_link_get_dot_state(main_link));
		cat_log_debug("%O        main-link=%O, build_entry=%O", indent, grop_dot_link_get_dot_state(main_link), build_entry);
		if (cons_prod_sym!=NULL) {

			GroPDotLink *next_dot_link = grop_machine_get_or_create_dot_link(machine, grop_dot_state_shift_normal(grop_dot_link_get_dot_state(main_link)));
			grop_dot_link_add_referred_by_link(next_dot_link, main_link);
//				next_dot_link.referredBy.add(endLink.dotState);
			GroPSymbolKey *tsk = grop_symbol_key_new(cons_prod_sym, FALSE);
			l_create_forward_mapping(priv, grop_build_entry_get_forward_map(build_entry), tsk, next_dot_link);

			if (GROP_IS_NON_TERMINAL(cons_prod_sym)) {
				cat_array_wo_append(next_level, (GObject *) main_link);
				GroPNonTerminal *cnte = (GroPNonTerminal *) cons_prod_sym;
				if (grop_non_terminal_get_nullable(cnte)==GROP_NULLABLE_TRUE) {
					GroPDotLink *next = grop_machine_get_or_create_dot_link(machine, grop_dot_state_shift_nullify(grop_dot_link_get_dot_state(main_link)));
					grop_dot_link_add_referred_by_link(next, main_link);
					main_link = next;
				} else {
					break;
				}
			} else {
				break;
			}
		} else {
			break;
		}
	}

	CatIIterator *nl_iter = cat_array_wo_iterator(next_level);
	while(cat_iiterator_has_next(nl_iter)) {
		GroPDotLink *dot_link = cat_iiterator_next(nl_iter);
		GroPSymbol *cons_prod_sym = grop_dot_state_get_symbol_at_dot(grop_dot_link_get_dot_state(dot_link));
		GroPNonTerminal *cnte = (GroPNonTerminal *) cons_prod_sym;
		CatArrayWo *prods = cat_array_wo_new();
		CatIIterator *prod_iter = grop_non_terminal_iterator(cnte);
		while(cat_iiterator_has_next(prod_iter)) {
			GroPProduction *child_prod = (GroPProduction *) cat_iiterator_next(prod_iter);
			if (cat_hash_set_add(considered, (GObject *) child_prod)==NULL) {
				cat_array_wo_append(prods, (GObject *) child_prod);
			}
		}
		cat_unref_ptr(prod_iter);

		CatStringWo *next_indent = cat_string_wo_new();
		cat_string_wo_format(indent, "%O  ", indent);
		CatIIterator *p_iter = cat_array_wo_iterator(prods);
		while(cat_iiterator_has_next(p_iter)) {
			GroPProduction *child_prod = (GroPProduction *) cat_iiterator_next(p_iter);
			l_recurse_worward(machine, build_entry, dot_link, child_prod, considered, next_indent);
		}
		cat_unref_ptr(p_iter);
		cat_unref_ptr(next_indent);


		/* remove all prods from considered */
		p_iter = cat_array_wo_iterator(prods);
		while(cat_iiterator_has_next(p_iter)) {
			GroPProduction *child_prod = (GroPProduction *) cat_iiterator_next(p_iter);
			GObject *ret = cat_hash_set_remove(considered, (GObject *) child_prod);
			cat_unref_ptr(ret);
		}
		cat_unref_ptr(p_iter);

		cat_unref_ptr(prods);
	}
	cat_unref_ptr(nl_iter);
	return result;
}


gboolean l_map_forward(GroPMachine *machine, GroPBuildEntry *build_entry, GroPDotLink *main_dot_link) {
	GroPMachinePrivate *priv = grop_machine_get_instance_private(machine);
	gboolean result = FALSE;
	GroPDotLink *head_link = main_dot_link;

	CatStringWo *indent = cat_string_wo_new_with("");
	cat_log_debug("  main_dot_link=%O", main_dot_link);
	while(head_link!=NULL) {
		cat_log_debug("    head-link=%O", head_link);
		GroPDotLink *next_link = NULL;
		GroPSymbol *symbol_at_dot = grop_dot_state_get_symbol_at_dot(grop_dot_link_get_dot_state(head_link));
		if (symbol_at_dot!=NULL) {

			GroPDotLink *head_follow_dot_link = grop_machine_get_or_create_dot_link(machine, grop_dot_state_shift_normal(grop_dot_link_get_dot_state(head_link)));
			result |= grop_dot_link_add_referred_by_link(head_follow_dot_link, head_link);
			cat_log_debug("    head_follow_dot_link=%O", head_follow_dot_link);
			GroPSymbolKey *tsk = grop_symbol_key_new(symbol_at_dot, FALSE);
			l_create_forward_mapping(priv, grop_build_entry_get_forward_map(build_entry), tsk, head_follow_dot_link);
			cat_unref_ptr(tsk);

			if (GROP_IS_NON_TERMINAL(symbol_at_dot)) {
				GroPNonTerminal *nte = (GroPNonTerminal *) symbol_at_dot;

				/* deeply recurse into the non Terminal */
				CatHashSet *considered = cat_hash_set_new((GHashFunc) grop_production_hash, (GEqualFunc) grop_production_equal);
				CatIIterator *prod_iter = grop_non_terminal_iterator(nte);
				while(cat_iiterator_has_next(prod_iter)) {
					GroPProduction *prod = (GroPProduction *) cat_iiterator_next(prod_iter);
					gboolean rec_res = l_recurse_worward(machine, build_entry, head_link, prod, considered, indent);
					result |= rec_res;
				}
				cat_unref_ptr(prod_iter);

				if (grop_non_terminal_get_nullable(nte)==GROP_NULLABLE_TRUE) {
					next_link = grop_machine_get_or_create_dot_link(machine, grop_dot_state_shift_nullify(grop_dot_link_get_dot_state(head_link)));
					gboolean link_res = grop_dot_link_add_referred_by_link(next_link, head_link);
					result |= link_res;
				}
			}
		}
		head_link = next_link;
	}
	return result;
}



/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
//	GroPMachine *instance = GROP_MACHINE(self);
//	GroPMachinePrivate *priv = grop_machine_get_instance_private(instance);
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);
	cat_string_wo_format(append_to, "%s[%p]", iname, self);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
