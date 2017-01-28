package net.natpad.ast.build.parser;
import net.natpad.gross.runtime.Symbol;
import net.natpad.gross.runtime.Terminal;
import net.natpad.gross.runtime.NonTerminal;
import net.natpad.gross.runtime.Token;
import net.natpad.gross.runtime.Fork;
import net.natpad.gross.runtime.StackEntry;
import net.natpad.gross.runtime.ParserContext;
import net.natpad.gross.runtime.ReduceLayout;


import net.natpad.gross.ast.bnf.*;



/* This file was generated by Gross-CC on 2016.11.29 AD at 11:53:23 CET */
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
			case 0 : { /* ast_lines ⟶ ast_line:ast_line */
				AstLine ast_line = extract(fork, reduceLayout, 0);
				result = new AstLines(null, ast_line); 
			} break;
			case 1 : { /* type_defs ⟶ type_defs:type_defs type_def:type_def */
				TypeDefs type_defs = extract(fork, reduceLayout, 0);
				TypeDef type_def = extract(fork, reduceLayout, 1);
				result = new TypeDefs(type_defs, type_def); 
			} break;
			case 2 : { /* rule_ref_list ⟶ rule_ref:rule_ref */
				RuleRef rule_ref = extract(fork, reduceLayout, 0);
				result = new RuleRefList(null, rule_ref); 
			} break;
			case 3 : { /* rule_ref ⟶ IDENTIFIER:lhs_name */
				String lhs_name = extract(fork, reduceLayout, 0);
				result = new RuleRef(lhs_name, null); 
			} break;
			case 4 : { /* spec ⟶ type_defs:type_defs ast_lines:ast_lines */
				TypeDefs type_defs = extract(fork, reduceLayout, 0);
				AstLines ast_lines = extract(fork, reduceLayout, 1);
				result = new AstFile(type_defs, ast_lines); 
			} break;
			case 5 : { /* rule_ref_list ⟶ rule_ref_list:rule_ref_list rule_ref:rule_ref */
				RuleRefList rule_ref_list = extract(fork, reduceLayout, 0);
				RuleRef rule_ref = extract(fork, reduceLayout, 1);
				result = new RuleRefList(rule_ref_list, rule_ref); 
			} break;
			case 6 : { /* type_description ⟶ type_def:type_def */
				TypeDef type_def = extract(fork, reduceLayout, 0);
				result = new TypeDescription(type_def); 
			} break;
			case 7 : { /* ast_lines ⟶ ast_lines:ast_lines ast_line:ast_line */
				AstLines ast_lines = extract(fork, reduceLayout, 0);
				AstLine ast_line = extract(fork, reduceLayout, 1);
				result = new AstLines(ast_lines, ast_line); 
			} break;
			case 8 : { /* type_def ⟶ TYPE STRING:description */
				String description = extract(fork, reduceLayout, 1);
				result = new TypeDef(description); 
			} break;
			case 9 : { /* ast_line ⟶ rule_ref_list:rule_ref_list fwd_type_description:description SEMI */
				RuleRefList rule_ref_list = extract(fork, reduceLayout, 0);
				ForwardTypeDescription description = extract(fork, reduceLayout, 1);
				result = new AstLine(rule_ref_list, description); 
			} break;
			case 10 : { /* ast_type_description ⟶ AST type_def:type_def opt_extends:opt_extends opt_as:opt_as body:body */
				TypeDef type_def = extract(fork, reduceLayout, 1);
				String opt_extends = extract(fork, reduceLayout, 2);
				String opt_as = extract(fork, reduceLayout, 3);
				BodyStatements body = extract(fork, reduceLayout, 4);
				result = new AstTypeDescription(type_def, opt_extends, opt_as, body); 
			} break;
			case 11 : { /* fwd_type_description ⟶ FORWARD type_def:type_def */
				TypeDef type_def = extract(fork, reduceLayout, 1);
				result = new ForwardTypeDescription(type_def); 
			} break;
			case 12 : { /* ast_line ⟶ rule_ref_list:rule_ref_list ast_type_description:description SEMI */
				RuleRefList rule_ref_list = extract(fork, reduceLayout, 0);
				AstTypeDescription description = extract(fork, reduceLayout, 1);
				result = new AstLine(rule_ref_list, description); 
			} break;
			case 13 : { /* ast_line ⟶ rule_ref_list:rule_ref_list type_description:description SEMI */
				RuleRefList rule_ref_list = extract(fork, reduceLayout, 0);
				TypeDescription description = extract(fork, reduceLayout, 1);
				result = new AstLine(rule_ref_list, description); 
			} break;
			case 14 : { /* rule_ref ⟶ IDENTIFIER:lhs_name INDEX_MARK IDENTIFIER:label */
				String lhs_name = extract(fork, reduceLayout, 0);
				String label = extract(fork, reduceLayout, 2);
				result = new RuleRef(lhs_name, label); 
			} break;
			case 15 : { /* opt_extends ⟶ EXTENDS STRING:extendsTypeName */
				String extendsTypeName = extract(fork, reduceLayout, 1);
				result = extendsTypeName; 
			} break;
			case 16 : { /* body_statements ⟶ body_statements:body_statements body_statement:body_statement */
				BodyStatements body_statements = extract(fork, reduceLayout, 0);
				BodyStatement body_statement = extract(fork, reduceLayout, 1);
				result = new BodyStatements(body_statements, body_statement); 
			} break;
			case 17 : { /* body ⟶ LCUBRACK body_statements:body_statements RCUBRACK */
				BodyStatements body_statements = extract(fork, reduceLayout, 1);
				result = body_statements; 
			} break;
			case 18 : { /* opt_as ⟶ AS name:name */
				String name = extract(fork, reduceLayout, 1);
				result = name; 
			} break;
			case 19 : { /* name ⟶ IDENTIFIER:id */
				String id = extract(fork, reduceLayout, 0);
				result = id; 
			} break;
			case 20 : { /* name ⟶ STRING:id */
				String id = extract(fork, reduceLayout, 0);
				result = id; 
			} break;
			case 21 : { /* body_statement ⟶ METHOD name:method_name opt_return:opt_return CODE_TEXT:code_text */
				String method_name = extract(fork, reduceLayout, 1);
				String opt_return = extract(fork, reduceLayout, 2);
				String code_text = extract(fork, reduceLayout, 3);
				result = new BodyMethodStatement(method_name, code_text, opt_return); 
			} break;
			case 22 : { /* body_statement ⟶ IMPLEMENT name:type_name CODE_TEXT:code_text */
				String type_name = extract(fork, reduceLayout, 1);
				String code_text = extract(fork, reduceLayout, 2);
				result = new BodyImplementStatement(type_name, code_text); 
			} break;
			case 23 : { /* opt_return ⟶ RETURN name:type_name */
				String type_name = extract(fork, reduceLayout, 1);
				result = type_name; 
			} break;
			case 24 : { /* body_statement ⟶ ARGUMENT STRING:type_name COMMA STRING:label COMMA STRING:value */
				String type_name = extract(fork, reduceLayout, 1);
				String label = extract(fork, reduceLayout, 3);
				String value = extract(fork, reduceLayout, 5);
				result = new BodyArgumentStatement(type_name, label, value); 
			} break;
		}
		return result;
	}
}
