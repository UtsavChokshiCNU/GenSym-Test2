package com.gensym.nols.wksp;

import static org.junit.Assert.assertEquals;

import static org.easymock.EasyMock.expect;

import java.awt.Container;
import java.util.Vector;

import javax.swing.JLayeredPane;
import javax.swing.JPanel;
import javax.swing.JRootPane;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JViewport;

import org.easymock.EasyMock;
import org.easymock.IMocksControl;
import org.junit.Before;
import org.junit.Test;

import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.INolOptimizeModel;
import com.gensym.nols.data.NolOptimization;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.wksp.NolOptimizationWKSP.BorderedLabel;
import com.gensym.nols.wksp.NolOptimizationWKSP.BorderedTextField;
import com.gensym.nols.wksp.NolOptimizationWKSP.VarContentHeaderPane;
import com.gensym.nols.wksp.NolOptimizationWKSP.VarContentPane;

import java.lang.reflect.*;
import com.gensym.nols.wksp.NolOptimizationWKSP.BoundsTableModel;

public class NolOptimizationWKSPTest {

	private static final long DELAY = 7;
	private static final long DELAY2 = 10;
	private static final long[] DELAYS = new long[] {DELAY, DELAY2};
	private static final long[] TIMEUNITDELAYS = new long[] {3600000, 7200000};
	private static final String VAR1 = "Var1";
	private static final String VAR2 = "Var2";
	
	private Vector<VarContentPane> panes;
	private NolOptimizationWKSP wksp;
	private NolMainFrame frame;
	private NolOptimization optimization;
	private INolOptimizeModel optModel;
	private IMocksControl mocksControl;
	private Preprocessor prep;
	private Vector<String> outputVars;
	private Vector<long[]> outputDelays;
	private Vector<long[]> stateDelays;
	private Vector<String> stateVars;
	private Vector<long[]> stateInputDelays;
	private Vector<String> stateInputVars;
	private Vector<String> inputVars;
	private Vector<long[]> inputDelays;
	private Vector<String> manipulateVars;
	private int delayTimeUnit = 0;
	
	private static final class TestPreprocessor extends Preprocessor {

		private static final long serialVersionUID = 7798863374559666874L;

		@SuppressWarnings("unchecked")
		TestPreprocessor() {
			dataSeries = new Vector<DataSeries>();
			dataSeries.add(new DataSeries(0, 2));
		}
		
	}
	
	@Before
	public void setup() {
		outputVars = new Vector<String>();
		outputVars.add(VAR1);
		outputDelays = new Vector<long[]>();
		
		stateVars = new Vector<String>();
		stateDelays = new Vector<long[]>();
		
		stateInputVars = new Vector<String>();
		stateInputDelays = new Vector<long[]>();
		
		inputVars = new Vector<String>();
		inputDelays = new Vector<long[]>();
		
		manipulateVars = new Vector<String>();
		
		prep = new TestPreprocessor();

		mocksControl = EasyMock.createControl();
		optModel = mocksControl.createMock(INolOptimizeModel.class);
		EasyMock.expect(optModel.getOutputs()).andStubReturn(outputVars);
		EasyMock.expect(optModel.getOutputDelays()).andStubReturn(outputDelays);
		EasyMock.expect(optModel.getState()).andStubReturn(stateVars);
		EasyMock.expect(optModel.getStateDelays()).andStubReturn(stateDelays);
		EasyMock.expect(optModel.getStateInput()).andStubReturn(stateInputVars);
		EasyMock.expect(optModel.getStateInputDelays()).andStubReturn(stateInputDelays);
		EasyMock.expect(optModel.getManipulate()).andStubReturn(manipulateVars);
		EasyMock.expect(optModel.getExogenous()).andStubReturn(new Vector());
		EasyMock.expect(optModel.getPreprocessor()).andStubReturn(prep);
		EasyMock.expect(optModel.getName()).andStubReturn("");
		EasyMock.expect(optModel.getModel()).andStubReturn(null);
		EasyMock.expect(optModel.getStateModel()).andStubReturn(null);
		EasyMock.expect(optModel.getInputs()).andStubReturn(inputVars);
		EasyMock.expect(optModel.getInputDelays()).andStubReturn(inputDelays);
		expect(optModel.getNin()).andStubReturn(1);
	}
	
	private void finalizeSetup(int timeUnit) {
		expect(optModel.getDelayTimeUnit()).andReturn(timeUnit);
		mocksControl.replay();
		
		optimization = new NolOptimization();
		optimization.setModel(optModel);
		optimization.putBounds(VAR2, new double[7]);
		optimization.putWeights(VAR2, new double[4]);
		frame = new NolMainFrame();
		frame.getProject().addOptimizationModel(optModel);
	}
	
	private String getHeaderLabel() {
		JRootPane rootPane = (JRootPane) wksp.getComponent(0);
		JLayeredPane layeredPane = (JLayeredPane) rootPane.getComponent(1);
		JPanel panel1 = (JPanel) layeredPane.getComponent(0);
		JTabbedPane tabbedPane = (JTabbedPane) panel1.getComponent(0);
		JPanel panel2 = (JPanel) tabbedPane.getComponent(1);
		JScrollPane scrollpane = (JScrollPane) panel2.getComponent(0);
		JViewport viewport = scrollpane.getColumnHeader();
		VarContentHeaderPane headerPane = (VarContentHeaderPane) viewport.getComponent(0);
		BorderedLabel label = (BorderedLabel) headerPane.getComponent(1);
		return label.getText();
	}
	

	private void setupWorkspace(int timeUnit) {
		finalizeSetup(timeUnit);
		wksp = new NolOptimizationWKSP(frame, optimization);
		panes = wksp.getVarContentPanes();
	}
	
	@Test
	public void testDelaysInContentPanes() {
		outputDelays.add(new long[] {DELAY});
		setupWorkspace(0);
		assertEquals(1, panes.size());
		assertEquals(DELAY, panes.elementAt(0).getDelayValue());
	}

	@Test
	public void testTwoDelaysInContentPanes() {
		outputDelays.add(DELAYS);
		setupWorkspace(0);
		assertEquals(2, panes.size());
		assertEquals(DELAY, panes.elementAt(0).getDelayValue());
		assertEquals(DELAY2, panes.elementAt(1).getDelayValue());
	}
	
	@Test
	public void testNoDelaysInContentPanes() {
		setupWorkspace(0);
		assertEquals(1, panes.size());
		assertEquals(0, panes.elementAt(0).getDelayValue());
	}
	
	@Test
	public void testTwoStateDelaysInContentPanes() {
		stateVars.add(VAR1);
		stateDelays.add(DELAYS);
		setupWorkspace(0);
		assertEquals(6, panes.size());
		assertEquals(0, panes.elementAt(0).getDelayValue());
		assertEquals(DELAY, panes.elementAt(1).getDelayValue());
		assertEquals(DELAY2, panes.elementAt(2).getDelayValue());
	}

	@Test
	public void test1ManipulateInput2Delays1Output1Delay() {
		inputVars.add(VAR2);
		manipulateVars.add(VAR2);
		inputDelays.add(DELAYS);
		setupWorkspace(0);
		assertEquals(3, panes.size());
		assertEquals(0, panes.elementAt(0).getDelayValue());
		assertEquals(DELAY, panes.elementAt(1).getDelayValue());
		assertEquals(DELAY2, panes.elementAt(2).getDelayValue());
	}

	@Test
	public void test1StateInput2Delays1Output1Delay() {
		inputVars.add(VAR2);
		stateVars.add(VAR2);
		inputDelays.add(DELAYS);
		setupWorkspace(0);
		assertEquals(4, panes.size());
		assertEquals(0, panes.elementAt(0).getDelayValue());
		assertEquals(0, panes.elementAt(1).getDelayValue());
		assertEquals(DELAY, panes.elementAt(2).getDelayValue());
		assertEquals(DELAY2, panes.elementAt(3).getDelayValue());
	}
	
	@Test
	public void testInputDelaysNone() {
		inputVars.add(VAR2);
		manipulateVars.add(VAR2);
		inputDelays.add(TIMEUNITDELAYS);
		setupWorkspace(0); //Old behavior
		assertEquals("0.0", ((BorderedTextField)panes.elementAt(0).getComponent(1)).getText());
		assertEquals("3600000.0", ((BorderedTextField)panes.elementAt(1).getComponent(1)).getText());
		assertEquals("7200000.0", ((BorderedTextField)panes.elementAt(2).getComponent(1)).getText());
	}
	
	@Test
	public void testInputDelaysHour() {
		inputVars.add(VAR2);
		manipulateVars.add(VAR2);
		inputDelays.add(TIMEUNITDELAYS);
		setupWorkspace(1); //Hour
		assertEquals("0.0", ((BorderedTextField)panes.elementAt(0).getComponent(1)).getText());
		assertEquals("1.0", ((BorderedTextField)panes.elementAt(1).getComponent(1)).getText());
		assertEquals("2.0", ((BorderedTextField)panes.elementAt(2).getComponent(1)).getText());
		assertEquals("Delay(Hour)", getHeaderLabel());
	}
	
	@Test
	public void testInputDelaysMinute() {
		inputVars.add(VAR2);
		manipulateVars.add(VAR2);
		inputDelays.add(TIMEUNITDELAYS);
		setupWorkspace(2); //Minute
		assertEquals("0.0", ((BorderedTextField)panes.elementAt(0).getComponent(1)).getText());
		assertEquals("60.0", ((BorderedTextField)panes.elementAt(1).getComponent(1)).getText());
		assertEquals("120.0", ((BorderedTextField)panes.elementAt(2).getComponent(1)).getText());
		assertEquals("Delay(Minute)", getHeaderLabel());
	}
	
	@Test
	public void testInputDelaysSecond() {
		inputVars.add(VAR2);
		manipulateVars.add(VAR2);
		inputDelays.add(TIMEUNITDELAYS);
		setupWorkspace(3); //Second
		assertEquals("0.0", ((BorderedTextField)panes.elementAt(0).getComponent(1)).getText());
		assertEquals("3600.0", ((BorderedTextField)panes.elementAt(1).getComponent(1)).getText());
		assertEquals("7200.0", ((BorderedTextField)panes.elementAt(2).getComponent(1)).getText());
		assertEquals("Delay(Second)", getHeaderLabel());
		
	}
	
	@Test
	public void testgetValueAtBoundsTableModel() throws NoSuchFieldException, IllegalArgumentException, IllegalAccessException {
		setupWorkspace(0);
		Field field = wksp.getClass().getDeclaredField("boundsTableModel");
	    field.setAccessible(true);
	    BoundsTableModel boundsTableModel = (BoundsTableModel)field.get(wksp);
	    org.junit.Assert.assertNotNull("testgetValueAtBoundsTableModel error", boundsTableModel.getValueAt(0, 1));
	}
}
