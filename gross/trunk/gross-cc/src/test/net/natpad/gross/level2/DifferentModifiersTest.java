package net.natpad.gross.level2;

import java.io.IOException;

import org.junit.Test;

import net.natpad.gross.Base;
import net.natpad.gross.build.CCStateMachine;

public class DifferentModifiersTest extends Base {
	
	@Test
	public void simpleTest() throws IOException {

		CCStateMachine stateMachine = createStateMachine(getClass().getResourceAsStream("different_modifiers.gro"));

		
	}
	
}
