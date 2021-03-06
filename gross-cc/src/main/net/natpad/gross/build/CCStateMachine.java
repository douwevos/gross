package net.natpad.gross.build;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;

import net.natpad.gross.runtime.GrossLogger;
import net.natpad.gross.runtime.GrossLogger.Level;
import net.natpad.gross.runtime.State;
import net.natpad.gross.runtime.StateModel;
import net.natpad.gross.runtime.Symbol;

public class CCStateMachine {

	private static boolean LOG_ENABLED = true;
	public final CCModel model;
	public final GrossLogger logger;
	
	private int kernelSequence;
	private int stateSequence;
	
	HashMap<Kernel, BuildEntry> map = new HashMap<Kernel, BuildEntry>(); 
	
	
	HashMap<DotState, DotLink> dotLinks = new HashMap<DotState, DotLink>();
	
	private LrarState[] states;
	
	public CCStateMachine(GrossLogger logger, CCModel model) {
		this.model = model;
		this.logger = logger;
	}
	
	
	public void build() {

		logger.log(Level.VERBOSE, "Calculating Nullability");
		model.calculateNullabilty();
		logger.log(Level.VERBOSE, "Calculating first sets");
		model.calculateFirstSets();

		logger.log(Level.VERBOSE, "Creating states");

		Production prod = model.getProduction(0);

		ArrayList<Kernel> workList = new ArrayList<Kernel>();
		
		Kernel dotSet = new Kernel(kernelSequence++);
		DotLink startDotLink = getOrCreateDotLink(new DotState(prod, 0));
		dotSet.add(startDotLink);
		workList.add(dotSet);
		
		
		boolean hadChanges = true;
		int round = 0;
		while(hadChanges) {
			round++;
			hadChanges = false;
			logger.log(Level.INFO, "Creating statemachine iteration "+round+", nr-of-states thusfar "+map.size());
			while(!workList.isEmpty()) {
	
				Kernel mainDotSet = workList.remove(0);
				BuildEntry buildEntry = map.get(mainDotSet);
				if (buildEntry==null) {
					buildEntry = new BuildEntry(mainDotSet, stateSequence++);
					map.put(mainDotSet, buildEntry);
				}
				logger.log(Level.DEBUG, "--------------------------- ");
				logger.log(Level.DEBUG, "Run state: "+buildEntry.id+"  "+map.size()+"/work-list="+workList.size()+" ("+round+")");
	
				for(DotLink mainDotLink : mainDotSet) {
					hadChanges |= mapForward(buildEntry, mainDotLink);
				}
			
//				if (round==1) {
					ArrayList<SymbolKey> fwdSyms = new ArrayList<SymbolKey>(buildEntry.forwardMap.keySet());
					for(SymbolKey symbol : fwdSyms) {
						Kernel fwdKernel = buildEntry.forwardMap.get(symbol);
						if (LOG_ENABLED) {
							logger.log(Level.DEBUG, "  fwdKernel=%d, sym=%s", fwdKernel.id, symbol);
						}
						if (symbol.symbol==model.getEofTerminal()) {
							continue;
						}
						if (map.containsKey(fwdKernel)) {
							Kernel mappedKernel = map.get(fwdKernel).kernel;
							buildEntry.forwardMap.put(symbol, mappedKernel);
						} else {
							workList.add(fwdKernel);
						}
					}
//				}
			}
//			
			logger.log(Level.DEBUG, "Analyzing DotLinks for recursion");
			for(DotLink dotLink : dotLinks.values()) {
				logger.log(Level.DEBUG, "  %s", dotLink);
				
				if (dotLink.dotState.isAtPossibleEnd()) {
					NonTerminalExt lhs = dotLink.dotState.production.lhs;
					logger.log(Level.DEBUG, "  ꩜ Testing");
					logger.log(Level.DEBUG, "      ⬡ %s", lhs);

					for(Production p : lhs) {
						logger.log(Level.DEBUG, "      ⬅ %s", p);
						DotState tds = new DotState(p, 0, null);
						while(!tds.isAtEnd()) {
							DotState shifted = tds.shiftNormal();
							Symbol sad = tds.getSymbolAtDot();
							logger.log(Level.DEBUG, "       ⬌ %s", tds);
							if (sad instanceof NonTerminalExt) {
								NonTerminalExt nterec = (NonTerminalExt) sad;
								if (nterec.firstSet().contains(lhs)) {
									DotLink tdotLink = dotLinks.get(shifted);
									if (tdotLink!=null) {
										logger.log(Level.DEBUG, "          Adding reference %s", tdotLink.dotState);
										hadChanges |= dotLink.addReferredBy(tdotLink.dotState);
									}
								}
							}
							tds = shifted;
						}
					}				
				
				}
				
			}
			
			workList.addAll(map.keySet());
		}

		logger.log(Level.VERBOSE, "Creating states done in "+round+" rounds");


		ArrayList<BuildEntry> enlistedEntries = new ArrayList<BuildEntry>(map.values());
		Collections.sort(enlistedEntries, new Comparator<BuildEntry>() {
			@Override
			public int compare(BuildEntry o1, BuildEntry o2) {
				return o1.id<o2.id ? -1 : (o1.id>o2.id ? 1 : 0);
			}
		});
		states = new LrarState[map.size()];
		for(BuildEntry buildEntry : enlistedEntries) {
			states[buildEntry.id] = buildEntry.buildState();
		}
		
		map.clear();
		for(BuildEntry b : enlistedEntries) {
			map.put(b.kernel, b);
		}
		

		
		int bidx=-1;
		for(BuildEntry buildEntry : enlistedEntries) {
			bidx++;
			if (logger.isEnabled(Level.DEBUG)) {
				logger.log(Level.DEBUG, "");
				buildEntry.describe(System.out, dotLinks);
			}
			
			logger.log(Level.VERBOSE, "  Creating basic forward transitions "+bidx+"/"+map.size());

			LrarState lrarState = states[buildEntry.state.id];
			for(SymbolKey sym : buildEntry.forwardMap.keySet()) {
				if (sym.isNullified) {
					continue;
				}
				TransitionsForSymbol transForSym = lrarState.getOrCreateTransitionsForSymbol(sym.symbol);
				if (sym.symbol == model.getEofTerminal()) {
					transForSym.addTransition(new AcceptTransition());
				} else {
					Kernel destDotSet = buildEntry.forwardMap.get(sym);
					BuildEntry destEntry = map.get(destDotSet);
					if (destEntry==null) {
						for(DotState ds : destDotSet.main.keySet()) {
							logger.log(Level.WARN, "    ds=%s", ds);
						}
						for(BuildEntry be : map.values()) {
							logger.log(Level.WARN, "   be.dotset=%s", be.kernel);
						}
					}
					LrarState destLrarState = states[destEntry.state.id];
					transForSym.addTransition(new ShiftTransition("BASC", destLrarState));
				}
			}
			
			logger.log(Level.VERBOSE, "  Creating reduce transitions based on linked-lists "+bidx+"/"+map.size());

			
			for(DotLink dotLink : buildEntry.kernel) {
				logger.log(Level.DEBUG, "    dotLink "+dotLink);
				
				if (dotLink.dotState.isAtEnd()) {
					/* This dotLink reached the end of the production. We need to insert ReduceTransitions for all symbols that follow.
					 */
					SymbolSet followSet = createFollowSet(dotLink, new HashSet<DotLink>());
					for(Symbol sym : followSet) {
						TransitionsForSymbol transForSym = lrarState.getOrCreateTransitionsForSymbol(sym);
						transForSym.addTransition(new ReduceTransition("LL", dotLink.dotState));
					}
					logger.log(Level.DEBUG, "     followSet="+followSet);
				} else if (!dotLink.dotState.isTerminated()) {
					DotState terminated = dotLink.dotState.createTerminated();
					if (allowNonCloseReduce(terminated)) {
						DotLink terminatedDotLink = getOrCreateDotLink(terminated);

					
						SymbolSet followSet = createFollowSet(dotLink, new HashSet<DotLink>());
						for(Symbol sym : followSet) {
							TransitionsForSymbol transForSym = lrarState.getOrCreateTransitionsForSymbol(sym);
							transForSym.addTransition(new ReduceTransition("TERM", terminatedDotLink.dotState));
						}
						logger.log(Level.DEBUG, "     followSet="+followSet);
					}
					
				}
			}
			
		}

		
//		if (logger.isEnabled(Level.VERBOSE)) {
//			for(LrarState state : states){
//				state.describe(System.out, false, dotLinks);
//				for(DotLink dotLink : state.kernel) {
//					
//					if (dotLink.dotState.isAtEnd()) {
//						/* This dotLink reached the end of the production. We need to insert ReduceTransitions for all symbols that follow.
//						 */
//						SymbolSet followSet = createFollowSet(dotLink, new HashSet<DotLink>());
//						logger.log(Level.DEBUG, "   followSet="+followSet);
//					}
//				}
//			}
//		}
		
	}

	
	private SymbolSet createFollowSet(DotLink dotLink, HashSet<DotLink> considered) {
		if (!considered.add(dotLink)) {
			return null; 
		}
//		logger.log(Level.DEBUG, "  flw-set for dotLink "+dotLink);
		SymbolSet result = new SymbolSet();
		for(DotState referrer : dotLink) {
			DotLink referredLink = getOrCreateDotLink(referrer);
//			logger.log(Level.DETAIL, "     referredLink "+referredLink);
			SymbolSet firstSet = referredLink.dotState.getLocalFirstSet();
			result.addAll(firstSet);
			if (!referredLink.dotState.isTerminated()) {
//				logger.log(Level.DETAIL, "     not terminated");
				SymbolSet topFollowSet = createFollowSet(referredLink, considered);
				if (topFollowSet!=null) {
					result.addAll(topFollowSet);
				}
			}
			
			
		}
		return result;
	}


	/*
	 * this method check if a DotState without any of the empty replacement symbols is merely a reduction to itself.
	 * 
	 * [a -b⚫ ⇒ a] can be rewritten to [a⚫ ⇒ a] which would result in counter-productive reduction.  
	 */
	private boolean allowNonCloseReduce(DotState ncDotState) {
		if (ncDotState.nullified==null) {
			return true;
		}
		int nonEmptyCnt = 0;
		for(int idx=ncDotState.production.rhsCount()-1; idx>=0; idx--) {
			if (ncDotState.isNullified(idx)) {
				continue;
			}
			if (ncDotState.production.rhsAt(idx).symbol==ncDotState.production.lhs) {
				nonEmptyCnt++;
			} else {
				return true;
			}
		}
		
		return nonEmptyCnt!=1;
	}


	private boolean mapForward(BuildEntry buildEntry, DotLink mainDotLink) {
		boolean result = false;
		DotLink headLink = mainDotLink;
		
		logger.log(Level.DEBUG, "  mainDotLink=%s", mainDotLink);
		while(headLink!=null) {
			logger.log(Level.DEBUG, "    head-link=%s", headLink);
			DotLink nextLink = null;
			Symbol symbolAtDot = headLink.dotState.getSymbolAtDot();
			if (symbolAtDot!=null) {
				
				DotState headShiftedNormal = headLink.dotState.shiftNormal();
				DotLink headFollowDotLink = getOrCreateDotLink(headShiftedNormal);
				if (!testIt(headShiftedNormal)) {
					break;
				}
				result |= headFollowDotLink.addReferredBy(headLink);
				logger.log(Level.DEBUG, "    headFollowDotLink=%s", headFollowDotLink);
				createForwardMapping(buildEntry.forwardMap, new SymbolKey(symbolAtDot, false), headFollowDotLink);
				
				if (symbolAtDot instanceof NonTerminalExt) {
					NonTerminalExt nte = (NonTerminalExt) symbolAtDot;

					/* deeply recurse into the non Terminal */
					HashSet<Production> considered = new HashSet<Production>();
					for(Production p : nte) {
						result |= recurseForward(buildEntry, headLink, p, considered, "");
					}

					if (nte.getNullable()==Boolean.TRUE) {
						DotState shiftedNullify = headLink.dotState.shiftNullify();
						if (testIt(shiftedNullify)) {
							nextLink = getOrCreateDotLink(shiftedNullify);
							result |= nextLink.addReferredBy(headLink);
						}
					}
				}
			}
			headLink = nextLink;
		}
		return result;
	}

	
	private boolean testIt(DotState state) {
		List<Symbol> syms = state.stripNullified();
		if (syms.isEmpty()) {
			return true;
		}
		
		
		for(Production p : state.production.lhs) {
			if (state.production!=p && p.startsWith(syms)) {
				return false;
			}
		}
		
		return true;
	}


	private boolean recurseForward(BuildEntry buildEntry, DotLink referredLink, Production consProd, HashSet<Production> considered, String indent) {
		logger.log(Level.DEBUG, indent+"        referredLink=%s, consProd=%s", referredLink, consProd);
		boolean result = false;
		DotLink mainLink = getOrCreateDotLink(new DotState(consProd,0));

		DotState shiftedReferrer = referredLink.dotState.shiftNormal();
		if (shiftedReferrer!=null) {
			result = mainLink.addReferredBy(shiftedReferrer);
		}
		
		
		ArrayList<DotLink> nextLevel = new ArrayList<DotLink>();
		
		while(true) {
			Symbol consProdSym = mainLink.dotState.getSymbolAtDot();
			logger.log(Level.DEBUG, indent+"        main-link=%s", mainLink.dotState);
			if (consProdSym!=null) {
				
				DotState mainShiftedNormal = mainLink.dotState.shiftNormal();
				if (!testIt(mainShiftedNormal)) {
					break;
				}
				DotLink nextDotLink = getOrCreateDotLink(mainShiftedNormal);
				nextDotLink.addReferredBy(mainLink);
//				nextDotLink.referredBy.add(endLink.dotState);
				createForwardMapping(buildEntry.forwardMap, new SymbolKey(consProdSym, false), nextDotLink);
				
				if (consProdSym instanceof NonTerminalExt) {
					nextLevel.add(mainLink);
					NonTerminalExt cnte = (NonTerminalExt) consProdSym;
					if (cnte.getNullable()==Boolean.TRUE) {
						DotState mainShiftedNullify = mainLink.dotState.shiftNullify();
						if (!testIt(mainShiftedNullify)) {
							break;
						}
						DotLink next = getOrCreateDotLink(mainShiftedNullify);
						next.addReferredBy(mainLink);
						mainLink = next;
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


		
		for (DotLink dotLink : nextLevel) {
			Symbol consProdSym = dotLink.dotState.getSymbolAtDot();
			NonTerminalExt cnte = (NonTerminalExt) consProdSym;

			ArrayList<Production> prods = new ArrayList<Production>();
			for(Production childProd : cnte) {
				if (considered.add(childProd)) {
					prods.add(childProd);
				}
			}
			
			for(Production childProd : prods) {
				recurseForward(buildEntry, dotLink, childProd, considered, indent+"  ");
			}
			considered.removeAll(prods);
		}
		return result;
	}


	private void createForwardMapping(HashMap<SymbolKey, Kernel> forwardMap, SymbolKey symbolAtDot, DotLink followDotLink) {
		Kernel dotSet = forwardMap.get(symbolAtDot);
		if (dotSet==null) {
			dotSet = new Kernel(kernelSequence++);
			forwardMap.put(symbolAtDot, dotSet);
		}
		logger.log(Level.DEBUG, "                       add-shift sym=%s, dotset=%s, state=%s", symbolAtDot, dotSet, followDotLink);
		dotSet.add(followDotLink);
	}


//	private int compactStates() {
//		int result = -1;
//		boolean didMerge = true;
//		while(didMerge) {
//			didMerge = false;
//			for(int idx=0; idx<stateList.size(); idx++) {
//				CCState mainState = stateList.get(idx);
//				for(int subIdx=idx+1; subIdx<stateList.size(); subIdx++) {
//					CCState subState = stateList.get(subIdx);
//					
//					if (mainState.canBeMerged(subState)) {
//						logger.log(Level.DEBUG, "merging "+subState+" with "+mainState);
//						stateList.remove(subIdx);
//						mergeStates(mainState, subState);
//						subIdx--;
//						didMerge = true;
//					}
//				}
//			}
//			result++;
//		}
//		return result;
//	}
//
//
//	private void mergeStates(CCState mainState, CCState subState) {
//		mainState.dotStateList.addAll(subState.dotStateList);
//		for(int idx=0; idx<stateList.size(); idx++) {
//			CCState state = stateList.get(idx);
//			state.informMerge(mainState, subState);
//		}
//	}
//
//
//	public CCState getStateByDotState(DotState dotState) {
////		DotState relevant = dotState.getRelevant();
//		DotState relevant = dotState;
//		return stateMap.get(relevant.kernel);
//	}
//
	public LrarState getStartState() {
		return states[0];
	}

	public int stateCount() {
		return states.length;
	}
	
	public LrarState stateAt(int index) {
		return states[index];
	}
//
//
	public int indexOf(LrarState state) {
		for(int idx=states.length-1; idx>=0; idx--) {
			if (states[idx]==state) {
				return idx;
			}
		}
		return -1;
	}


	
	
	public StateModel createStateModel() {
		Collection<Symbol> allSymbols = model.allSymbols();
		Symbol symbols[] = allSymbols.toArray(new Symbol[allSymbols.size()]);
		State[] smstates = new State[states.length];
		for(int idx=0; idx<states.length; idx++) {
			State state = new State(idx);
			smstates[idx] = state;
		}

		for(int idx=0; idx<states.length; idx++) {
			LrarState ccState = states[idx];
			ccState.configureState(smstates[idx], states, smstates);
		}
		
		return new StateModel(symbols, smstates);
	}

	
	
	public DotLink getOrCreateDotLink(DotState dotState) {
		DotLink dotLink = dotLinks.get(dotState);
		if (dotLink==null) {
			dotLink = new DotLink(dotState);
			dotLinks.put(dotState, dotLink);
		}
		return dotLink;
	}
	
	

	public void dumpGlrTransitions() {
		int glrCollisionCount = 0;
		for(int stateIdx=0 ; stateIdx<stateCount(); stateIdx++) {
			LrarState state = stateAt(stateIdx);

			state.describe(System.out, false, null);
			System.out.println("--------------------------------------------------------------------");

			boolean didDescribe = false;
			Collection<TransitionsForSymbol> values = state.transitionMap.values();
			for (TransitionsForSymbol transitionsForSymbol : values) {
				if (transitionsForSymbol.unique.size()>1) {
//					if (!didDescribe) {
//						didDescribe = true;
//						state.describe(System.out, false, null);
//						System.out.println("--------------------------------------------------------------------");
//					}
					System.out.println("  Glr at state:"+stateIdx+" under symbol:"+transitionsForSymbol.symbol.name);
					ArrayList<Transition> unique = transitionsForSymbol.unique;
					for (Transition transition : unique) {
						System.out.println("    # "+transition.toString());
						glrCollisionCount++;
					}
				}
			}
		}
		
		System.out.println("GLR collision count:"+glrCollisionCount);
	}
	
}
