package net.natpad.mapper;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;

import net.natpad.gross.runtime.DefaultLogger;
import net.natpad.gross.runtime.DefaultTokenFactory;
import net.natpad.gross.runtime.GrossLogger;
import net.natpad.gross.runtime.Parser;
import net.natpad.gross.runtime.ParserContext;
import net.natpad.gross.runtime.ParserContext.ReduceAction;
import net.natpad.gross.runtime.Scanner;
import net.natpad.gross.runtime.StateModel;
import net.natpad.gross.runtime.Symbol;
import net.natpad.gross.runtime.TokenFactory;
import net.natpad.mapper.gobject.GObject;
import net.natpad.mapper.gobject.GObject.Name;
import net.natpad.mapper.model.TypeDefinition;
import net.natpad.mapper.model.TypeList;

public class Main {

    public Main() {
    }

    public static void main(String[] args) {
        Main main = new Main();
        main.run(args);
    }

    private void run(String[] args) {
        
        GrossLogger logger = new DefaultLogger(System.out);
        Parser parser = new Parser(logger);
        TokenFactory tokenFactory = new DefaultTokenFactory();
        GrossParserTables gpt = new GrossParserTables();
        Symbol[] symbols = gpt.symbols;
        
        StateModel stateModel = new StateModel(symbols, gpt.cfgText, gpt.stateCount);
        ReduceAction actionHandler = new Actions();
        ParserContext context = new ParserContext(tokenFactory, stateModel , actionHandler);
        FileReader reader;
        try {
            reader = new FileReader("./etc/test.map");
            Scanner scanner = new MapperScanner(reader, tokenFactory, symbols);
            TypeList typeList = parser.parse(context, scanner);
            List<TypeDefinition> enlist = typeList.enlist();
            
            System.out.println("typeList="+typeList);
            
            
            File outputBase = new File("./generated/");
            outputBase.mkdirs();
            
            
            for (TypeDefinition typeDefinition : enlist) {
            	GObject obn = new GObject(new Name("Vos", typeDefinition.typename));
				//				System.out.println(typeDefinition.typename);
				GObjectExporter exporter = new GObjectExporter(obn);
				exporter.export(outputBase);
			}
            
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
}
