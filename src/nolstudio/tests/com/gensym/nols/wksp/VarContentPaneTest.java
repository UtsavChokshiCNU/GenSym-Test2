package com.gensym.nols.wksp;

import static org.junit.Assert.assertEquals;

import java.awt.GridLayout;
import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.nols.data.NolOptimization;
import com.gensym.nols.data.NolOptimizeModel;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.wksp.NolOptimizationWKSP.BorderedTextField;
import com.gensym.nols.wksp.NolOptimizationWKSP.VarContentPane;


public class VarContentPaneTest {

	private static final long DELAY = 60000;
	private static final int NUMBER_OF_COLUMNS = 4;
	private static final String VAR1 = "var1";
	
	private VarContentPane pane;

	private VarContentPane getPane() {
		NolMainFrame frame = new NolMainFrame();
		NolOptimization optimization = new NolOptimization();
		Preprocessor prep = new Preprocessor();
		NolOptimizeModel optModel = new NolOptimizeModel(null, "",
				new Vector(), new Vector(), new Vector(), new Vector(),
				new Vector(), new Vector(), prep);
		optimization.setModel(optModel);
		optimization.putBounds(VAR1, new double[] {0, 0, 0, 0, 0, 0, 0});
		NolOptimizationWKSP wksp = new NolOptimizationWKSP(frame, optimization);
		VarContentPane pane = wksp.new VarContentPane(VAR1, 0, DELAY);
		return pane;
	}
	
	@Before
	public void setup() {
		pane = getPane();
	}
	
	@Test
	public void testDelayColumnPresence() {
		assertEquals(NUMBER_OF_COLUMNS, pane.getComponents().length);
	}
	
	@Test
	public void testDelayColumnIsSecond() {
		BorderedTextField field = (BorderedTextField) pane.getComponents()[1];
		assertEquals(Double.toString(DELAY / (1000 * 60)), field.getText());
		assertEquals(VAR1, field.getVarName());
	}
	
	@Test
	public void testLayout() {
		GridLayout layout = (GridLayout) pane.getLayout();
		assertEquals(NUMBER_OF_COLUMNS, layout.getColumns());
	}
	
	@Test
	public void testDelayValue() {
		assertEquals(DELAY, pane.getDelayValue());
	}
}
