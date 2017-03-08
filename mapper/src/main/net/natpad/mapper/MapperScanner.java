package net.natpad.mapper;

import java.io.IOException;
import java.io.Reader;
import java.util.HashMap;

import net.natpad.gross.runtime.Location;
import net.natpad.gross.runtime.Scanner;
import net.natpad.gross.runtime.Symbol;
import net.natpad.gross.runtime.Token;
import net.natpad.gross.runtime.TokenFactory;


public class MapperScanner implements Scanner {
    
    private final Reader input;
    private int lookahead[] = new int[5];
    private int leftColumn, rightColumn, markColumn;
    private int leftRow, rightRow, markRow;
    public TokenFactory tokenFactory;
    public Symbol[] symbols;
    private HashMap<String, Symbol> symbolMap = new HashMap<String, Symbol>();
    
    
    public MapperScanner(Reader input, TokenFactory tokenFactory, Symbol[] symbols) throws IOException {
        this.input = input;
        this.tokenFactory = tokenFactory;
        for(Symbol sym : symbols) {
            symbolMap.put(sym.name, sym);
        }
        
        for(int idx=1; idx<lookahead.length; idx++) {
            lookahead[idx] = input.read();
        }

        nextChar();
        
    }

    
    public void nextChar() throws IOException {
        System.arraycopy(lookahead, 1, lookahead, 0, lookahead.length-1);
        lookahead[lookahead.length-1] = input.read();
        leftRow = rightRow;
        leftColumn = rightColumn;
        int ch = lookahead[0];
        if (ch==0xd) {
            rightRow++;
            rightColumn=0;
            if (lookahead[1]==0xa) {
                System.arraycopy(lookahead, 1, lookahead, 0, lookahead.length-1);
                lookahead[lookahead.length-1] = input.read();
            }
        } else if (ch==0xa) {
            rightRow++;
            rightColumn=0;
            if (lookahead[1]==0xd) {
                System.arraycopy(lookahead, 1, lookahead, 0, lookahead.length-1);
                lookahead[lookahead.length-1] = input.read();
            }
        } else {
            rightColumn++;
        }
    }
    
    
    
    @Override
    public Token next() {
    	Token result = nextToken();
    	System.out.println("result="+result);
    	return result;
    }
    
    public Token nextToken()  {
        
        try {
            while(true) {
                markLocation();
                switch(lookahead[0]) {
                    case -1 : {
                        return tokenFactory.createToken(symbolMap.get("⟧"), null, null, "EOT");
                    }
                    case '{' : {
                        return createBasicToken("L_LCUBRACE", 1);
                    }
                    case '}' : {
                        return createBasicToken("L_RCUBRACE", 1);
                    }
                    case ';' : {
                        return createBasicToken("SEMI", 1);
                    }
                    default : {
                        if (Character.isAlphabetic(lookahead[0])) {
                            return scanForId();
                        }
                        nextChar();
                    }
                    
                }
            }
        } catch(IOException t) {
            t.printStackTrace();
        }
        
        return null;
    }


    private Token scanForId() throws IOException {
        StringBuilder buf = new StringBuilder();
        
        
        int row = rightRow;
        int column = rightColumn;
        while(true) {
            int ch = lookahead[0];
            if (ch==-1) {
                break;
            } else if (ch=='_' || Character.isLetterOrDigit(ch)) {
                buf.append((char) ch);
                row = rightRow;
                column = rightColumn;
                nextChar();
            } else {
            	break;
            }
        }
        
        Location location = new Location(markColumn, markRow, column, row);
		String identifier = buf.toString();
		if ("type".equals(identifier)) {
			return tokenFactory.createToken(symbolMap.get("L_TYPE"), identifier, location, "TYPE");
		}
		return tokenFactory.createToken(symbolMap.get("ID"), identifier, location, "ID");
    }


    private void markLocation() {
        markRow = leftRow;
        markColumn = leftColumn;
    }


    private Token createBasicToken(String symbolkey, int charCount) throws IOException {
        Symbol symbol = symbolMap.get(symbolkey);
        
        while(charCount>1) {
            nextChar();
        }
        Location location = new Location(markColumn, markRow, rightColumn, rightRow);
        nextChar();
        return tokenFactory.createToken(symbol, null, location , null);
    }

    
}
