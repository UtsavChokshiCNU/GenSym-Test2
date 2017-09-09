package com.gensym.nols.wksp;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.datafit.EnsembleModel;
import com.gensym.nols.data.NolOptimizeModel;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.main.NolMainFrame;

import static org.junit.Assert.assertEquals;

public class NolModelWKSPTest {

	private static final String MANIPULATE_VAR = "Manipulate variable";
	private static final String STATE_VAR = "State variable";
	private static final String OUTPUT_VAR = "Output variable";
	private static final String EXOGENOUS_VAR = "Exogenous variable";
	
	private Preprocessor preprocessor;
	private NolMainFrame frame;
	private Vector<String> inputs;
	private Vector<long[]> inputDelays;
	private Vector<String> outputs;
	private Vector<long[]> outputDelays;
	private Vector<String> states;
	private Vector<long[]> stateDelays;
	private Vector<String> stateInputs;
	private Vector<long[]> stateInputDelays;
	private Vector<String> manipulateInputs;
	private Vector<String> exogenous;
	private EnsembleModel ensembleModel;
	private NolOptimizeModel nolModel;
	private NolModelWKSP wksp;
	private NolModelWKSP.VarClassifyTableModel model;
	
	@Test
	public void testInitDataDisplayHeaders() {
		finishSetup();
		assertEquals(11, model.getRowCount());
		assertEquals("Variable", model.getColumnName(0));
		assertEquals("Classification", model.getColumnName(1));
		assertEquals("Delay(Minute)", model.getColumnName(2));
	}

	@Test
	public void testInitDataDisplayForManipulate() {
		finishSetup();
		assertEquals(11, model.getRowCount());
		assertEquals(MANIPULATE_VAR, model.getValueAt(9, 0));
		assertEquals("Manipulate", model.getValueAt(9, 1));
		assertEquals("2.0", model.getValueAt(9, 2));
	}

	@Test
	public void testInitDataDisplayForExogenous() {
		initExogenousData();
		finishSetup();
		assertEquals(12, model.getRowCount());
		assertEquals("Exogenous", model.getValueAt(11, 1));
	}


	private void finishSetup() {
		nolModel = new NolOptimizeModel(ensembleModel,
				ensembleModel, "TestModel", outputs, inputs, states,
				stateInputs, manipulateInputs, exogenous, outputDelays,
				inputDelays, stateDelays, stateInputDelays, preprocessor);
		wksp = new NolModelWKSP(frame, nolModel);
		model = wksp.getVarClassifyTableModel();
	}


	private void initExogenousData() {
		inputs.add(EXOGENOUS_VAR);
		exogenous.add(EXOGENOUS_VAR);
		stateInputs.add(EXOGENOUS_VAR);
		stateInputDelays.add(new long[] {0});
	}

	@Before
	public void setup() {
		preprocessor = new Preprocessor();
		frame = new NolMainFrame();
		
		inputs = new Vector<String>();
		inputs.add(MANIPULATE_VAR);
		inputs.add(STATE_VAR);
		
		inputDelays = new Vector<long[]>();
		inputDelays.add(new long[] {0, 60000});
		inputDelays.add(new long[] {0, 60000});
		
		outputs = new Vector<String>();
		outputs.add(OUTPUT_VAR);
		
		outputDelays = new Vector<long[]>();
		outputDelays.add(new long[] {0});
		
		states = new Vector<String>();
		states.add(STATE_VAR);
		
		stateDelays = new Vector<long[]>();
		stateDelays.add(new long[] {0});
		
		stateInputs = new Vector<String>();
		stateInputs.add(MANIPULATE_VAR);
		
		stateInputDelays = new Vector<long[]>();
		stateInputDelays.add(new long[] {120000, 180000});
		
		manipulateInputs = new Vector<String>();
		manipulateInputs.add(MANIPULATE_VAR);
		
		exogenous = new Vector<String>();
		
		ensembleModel = new EnsembleModel(null);
	}
}
