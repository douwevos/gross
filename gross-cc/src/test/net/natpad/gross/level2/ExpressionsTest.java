package net.natpad.gross.level2;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import org.junit.Test;

import net.natpad.gross.Base;
import net.natpad.gross.build.CCStateMachine;

public class ExpressionsTest extends Base {
	
	@Test
	public void simpleTest() throws IOException {

		CCStateMachine stateMachine = createStateMachine(new FileInputStream(new File("/home/superman/cpp-workspace/gross/gross-cc/src/test/net/natpad/gross/level2/expressions.gro")));

		
	}
	
}
