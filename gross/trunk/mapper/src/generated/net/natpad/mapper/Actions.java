package net.natpad.mapper;
import net.natpad.gross.runtime.Symbol;
import net.natpad.gross.runtime.Terminal;
import net.natpad.gross.runtime.NonTerminal;
import net.natpad.gross.runtime.Token;
import net.natpad.gross.runtime.Fork;
import net.natpad.gross.runtime.StackEntry;
import net.natpad.gross.runtime.ParserContext;
import net.natpad.gross.runtime.ReduceLayout;

import net.natpad.mapper.model.TypeList;
import net.natpad.mapper.model.TypeDefinition;
import net.natpad.mapper.model.Block;
import net.natpad.mapper.model.FieldList;
import net.natpad.mapper.model.Field;


/* This file was generated by Gross-CC on 2017.03.07 AD at 21:14:13 CET */
public class Actions implements ParserContext.ReduceAction {

	public <T> T extract(Fork fork, ReduceLayout reduceLayout, int offset) {
		T result = null;
		StackEntry fe = fork.getEntry(reduceLayout.calculateStackOffset(offset));
		if (fe!=null) {
			result = (T) fe.lookahead.getValue();
		}
		return result;
	}

	public Object doAction(Fork fork, ReduceLayout reduceLayout, int actionId) {
		Object result = null;
		switch(actionId) {
			case 0 : { /* document ⟶ type_list:tl */
				TypeList tl = extract(fork, reduceLayout, 0);
 result = tl; 
			} break;
			case 1 : { /* type_list ⟶ type_list:tl type_def:td */
				TypeList tl = extract(fork, reduceLayout, 0);
				TypeDefinition td = extract(fork, reduceLayout, 1);
 result = new TypeList(tl, td); 
			} break;
			case 2 : { /* type_def ⟶ L_TYPE ID:id type_block:block */
				String id = extract(fork, reduceLayout, 1);
				Block block = extract(fork, reduceLayout, 2);
 result = new TypeDefinition(id, block); 
			} break;
			case 3 : { /* type_block ⟶ L_LCUBRACE type_fields:tfs L_RCUBRACE */
				FieldList tfs = extract(fork, reduceLayout, 1);
 result = new Block(tfs); 
			} break;
			case 4 : { /* type_fields ⟶ type_fields:tfs type_field:tf */
				FieldList tfs = extract(fork, reduceLayout, 0);
				Field tf = extract(fork, reduceLayout, 1);
 result = new FieldList(tfs, tf); 
			} break;
			case 5 : { /* type_field ⟶ ID:ft ID:fn SEMI */
				String ft = extract(fork, reduceLayout, 0);
				String fn = extract(fork, reduceLayout, 1);
 result = new Field(ft, fn); 
			} break;
		}
		return result;
	}
}