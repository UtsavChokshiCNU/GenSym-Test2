package com.gensym.nols.deploy;


import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Matchers.any;
import static org.mockito.Matchers.anyInt;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.util.UUID;
import java.util.Vector;

import org.junit.Before;
import org.junit.Test;
import org.powermock.reflect.Whitebox;

import com.gensym.classes.FloatArray;
import com.gensym.classes.FloatArrayImpl;
import com.gensym.classes.IntegerArray;
import com.gensym.classes.IntegerArrayImpl;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.math.MathException;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.NolAnnModel;
import com.gensym.nols.data.NolBpnModel;
import com.gensym.nols.data.NolModel2;
import com.gensym.nols.data.NolOptimization;
import com.gensym.nols.data.NolPcaModel;
import com.gensym.nols.data.NolPlsModel;
import com.gensym.nols.data.NolRbfnModel;
import com.gensym.nols.data.NolRhoModel;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Project2;
import com.gensym.nols.data.RawDataSource;
import com.gensym.nols.data.Variable;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/**
 * Unit test for the class com.gensym.nols.deploy.NolG2Gateway
 * @author Ambarish
 *
 */
public class NolG2GatewayTest {

	private NolG2Gateway gateWay;
	private FloatArray floatArray;
	private G2Connection connection;
	private static final String TEST = "test";
	private static final String INPUT = "input";
	private static final String OUTPUT = "output";
	private static final String CLASSIFICATION = "CLASSIFICATION";
	private static final int HUNDRED = 100;
	private static final int ONE = 1;
	private static final int ZERO = 0;
	private static final String STRING_ONE = "1";
	private static final String STRING_TWO = "2";
	private static final double[] DOUBLE_ARRAY= {1.4,2.6,3.8};
	private IntegerArray intArray;
	private NolPcaModel pcaModel;
	private Preprocessor preprocessor;
	private NolModel2 nolModel;
	private RawDataSource rawSource;
	private G2ConnectionEvent event;
	private DataSeries series;
	private NolOptimization optimization;
	private Variable variable;
	private Matrix matrix;
	private Structure structure;
	private NolMainFrame frame;
	private Project2 project;
	private Sequence sequence;
	private Sequence sequenceString;
	private Sequence sequenceStructure;

	private Sequence trainingSequence;
	private Sequence modelParams;
	private Vector<String> namesList;
	private Vector<Integer> intList;
	private Vector<FloatArray> list;
	private Vector<Preprocessor> preprocessorList;
	private Vector<String> mockList;
	private NolBpnModel bpnModel;

	/**
	 * Initializer for all the test variables
	 * @throws G2AccessException
	 * @throws MathException
	 * @throws NoSuchAttributeException
	 */
	@Before
	public void initGateWay() throws G2AccessException, MathException,NoSuchAttributeException{
		connection = mock(G2Connection.class);
		frame = mock(NolMainFrame.class);
		project = mock(Project2.class);
		floatArray = new FloatArrayImpl();
		intArray = new IntegerArrayImpl();
		pcaModel = mock(NolPcaModel.class);
		preprocessor = mock(Preprocessor.class);
		nolModel = mock(NolModel2.class);
		rawSource = mock(RawDataSource.class);
		event = mock(G2ConnectionEvent.class);
		series = mock(DataSeries.class);
		optimization = mock(NolOptimization.class);
		variable = mock(Variable.class);
		matrix = new Matrix();
		structure = mock(Structure.class);
		bpnModel = mock(NolBpnModel.class);
		floatArray.setG2ArrayContents(DOUBLE_ARRAY);

		intArray.setG2ArrayContents(new int[] { 1, 2, 3 });
		sequence = new Sequence();
		sequence.add(floatArray);

		sequenceString = mock(Sequence.class);
		sequenceStructure = new Sequence();
		sequenceStructure.add(structure);

		trainingSequence = new Sequence();
		for (int i = 1; i <= 10; i++) {
			trainingSequence.add(floatArray);
		}

		modelParams = new Sequence();
		modelParams.add(TEST);
		modelParams.add(TEST);
		modelParams.add(TEST);
		modelParams.add("true");
		modelParams.add(STRING_ONE);
		modelParams.add(STRING_TWO);
		modelParams.add(sequenceStructure);
		modelParams.add(sequenceStructure);

		mockList = new Vector<String>();
		namesList = new Vector<String>();
		namesList.add(TEST);

		intList = new Vector<Integer>();
		intList.add(ONE);

		list = new Vector<FloatArray>();
		list.add(floatArray);

		preprocessorList = new Vector<Preprocessor>();
		preprocessorList.add(preprocessor);
		when(pcaModel.getInputs()).thenReturn(namesList);
		when(pcaModel.getScore()).thenReturn(matrix);
		when(pcaModel.getPreprocessor()).thenReturn(preprocessor);
		when(connection.g2GetHostName()).thenReturn(TEST);
		when(connection.g2GetPortNumberOrName()).thenReturn(TEST);
		when(event.getMessage()).thenReturn(TEST);
		when(structure.getAttributeValue(Symbol.intern("NODES"))).thenReturn(sequenceStructure);
		when(structure.getAttributeValue(Symbol.intern("DELAY"))).thenReturn(STRING_ONE);
		when(connection.callRPC(any(Symbol.class), any(String[].class), anyInt())).thenReturn(list, list, list, list,
				list, list, list, list, mockList, sequence);
		when(frame.getProject()).thenReturn(project);
		when(frame.classifyInputOutput(series)).thenReturn(new Vector[] { namesList, namesList });
		gateWay = new NolG2Gateway(connection);
		Whitebox.setInternalState(gateWay, "frame", frame);
		when(project.getPcaModelIndexByName(TEST)).thenReturn(ZERO);
		when(project.getPcaModel(ZERO)).thenReturn(pcaModel);
		when(project.getPredictiveModelIndexByName(TEST)).thenReturn(ONE);
		when(project.getPredictiveModel(ONE)).thenReturn(nolModel);
		when(project.getPredictiveModel(ZERO)).thenReturn(nolModel);
		when(project.getNumberOfPredictiveModels()).thenReturn(ONE);
		when(project.getOptimization(ZERO)).thenReturn(optimization);
		when(project.getNumberOfOptimizations()).thenReturn(ONE);
		when(project.getRawDataSource()).thenReturn(rawSource);
		when(rawSource.getNumberOfDataSeries()).thenReturn(ONE);
		when(rawSource.getDataSeriesName(ZERO)).thenReturn(TEST);
		when(rawSource.getDataSeries()).thenReturn(list);
		when(project.getPreprocessors()).thenReturn(preprocessorList);
		when(nolModel.getPreprocessor()).thenReturn(preprocessor);
		when(nolModel.getName()).thenReturn(TEST);
		when(nolModel.getMaximumInputs()).thenReturn(ONE);
		when(nolModel.getInputs()).thenReturn(intList);
		when(nolModel.getHasTimeStamps()).thenReturn(true);
		when(nolModel.getOutputs()).thenReturn(intList);
		when(bpnModel.getPreprocessor()).thenReturn(preprocessor);
		when(bpnModel.getName()).thenReturn(TEST);
		when(bpnModel.getMaximumInputs()).thenReturn(ONE);
		when(bpnModel.getInputs()).thenReturn(intList);
		when(bpnModel.getHasTimeStamps()).thenReturn(true);
		when(bpnModel.getOutputs()).thenReturn(intList);
		when(preprocessor.getVariableFromVariableName(TEST)).thenReturn(variable);
		when(nolModel.getNumberOfOutputs(ZERO)).thenReturn(ONE);
		when(bpnModel.getNumberOfOutputs(ZERO)).thenReturn(ONE);
		when(preprocessor.getOriginalVarNames(any(Vector.class))).thenReturn(namesList);
		when(preprocessor.getNumberOfDataSeries()).thenReturn(ONE);
		when(preprocessor.getName()).thenReturn(TEST);
		when(preprocessor.getDataSeriesName(ZERO)).thenReturn(TEST);
		when(preprocessor.getDataSeries(ZERO)).thenReturn(series);
		when(variable.getDataSeries()).thenReturn(series);
		when(series.getTimeStamps()).thenReturn(new long[] { 1000L, 2000L });
		when(series.getFiniteData()).thenReturn(new double[][] { DOUBLE_ARRAY });
		when(series.getVarObjects()).thenReturn(mockList);
		when(series.getHasTimeStamps()).thenReturn(true);
		when(series.getDataMatrix()).thenReturn(matrix);
		when(sequenceString.getContents()).thenReturn(new Object[] { TEST, intArray, intArray, floatArray, floatArray });
		gateWay.setDebug(true);
		gateWay.initializeLocalRPCs(connection);
	}

	/**
	 * Test method to get data set names from G2
	 * @throws G2AccessException
	 */
	@Test
	public void testGetDataSetNamesFromG2() throws G2AccessException{
		assertTrue(gateWay.getDataSetNamesFromG2().size()>ZERO);
		assertTrue(gateWay.getAllDataSetNamesFromG2().size()>ZERO);
		assertTrue(gateWay.getAllNamedDataSetNamesFromG2().size()>ZERO);
		gateWay.getDataSetFromG2("NOLS-MATRIX", TEST,true);
		gateWay.getDataSetFromG2("GNNE-DATA-SET", TEST,true);
		verify(frame,times(2)).finishAddDataSeries(any(DataSeries.class));
	}

	/**
	 * Test method for data series names
	 * @throws G2AccessException
	 */
	@Test
	public void testDataSeriesNames() throws G2AccessException{
		assertFalse(gateWay.hasDataSeriesWithSameName(TEST));
		assertTrue(gateWay.getRawDataSeriesNames(sequence).size() > ZERO);
		assertTrue(gateWay.getDataSeriesFullNames(sequence).size() > ZERO);
	}


	/**
	 * Test methods on predictive model when auto recursive
	 * @throws G2AccessException
	 */
	@Test
	public void testPredictiveModelWhenAutoRecursive() throws G2AccessException {
		when(nolModel.isAutoRecursiveModel()).thenReturn(true);
		assertEquals(gateWay.showPredictiveModelPrediction(TEST), ONE);
	}

	/**
	 * Test methods on predictive model
	 * @throws G2AccessException
	 * @throws MathException
	 */
	@Test
	public void testPredictiveModel() throws G2AccessException, MathException {
		assertTrue(gateWay.getPredictiveModelNames(sequence).size() > ZERO);
		assertTrue(gateWay.getOptimizationNames(sequence).size() > ZERO);
		assertNotNull(gateWay.setPredictiveModelParameters(sequence, TEST));
		assertTrue(((Sequence) gateWay.getPredictiveModelParameters(sequence, TEST)).size() == ZERO);
		assertEquals(gateWay.showClassicModelPrediction(TEST), ZERO);
		when(project.getBpnModel(ZERO)).thenReturn(bpnModel);
		assertEquals(gateWay.showClassicModelPrediction(TEST), ONE);

		final Sequence inputSeq = new Sequence();
		when(project.getPredictiveModelIndexByName(TEST)).thenReturn(ONE);
		final NolModel2 nolModel2 = mock(NolModel2.class);
		when(project.getPredictiveModel(ONE)).thenReturn(nolModel2);
		final Vector infors = new Vector<>();
		infors.addElement(10.1);
		infors.addElement(10.2);
		when(nolModel2.getParametersVector()).thenReturn(infors);
		final Sequence returnVal = (Sequence)gateWay.getPredictiveModelParameters(inputSeq, TEST);
		final Object[] seqContents = returnVal.getContents();
		assertEquals(10.1, seqContents[0]);
		assertEquals(10.2, seqContents[1]);
	}

	/**
	 * Test method for predictive model xml parameters
	 * @throws G2AccessException
	 * @throws MathException
	 */
	@Test
	public void testPredictiveModelXMLParameters() throws G2AccessException, MathException {
		gateWay.getPredictiveModelXMLParameters(sequence, TEST);
		assertEquals(gateWay.showPredictiveModelPrediction(TEST), ONE);
		when(nolModel.isTrained()).thenReturn(true);
		when(nolModel.getWholeParametersVector()).thenReturn(namesList);
		final Sequence result = (Sequence)gateWay.getPredictiveModelXMLParameters(sequence, TEST);
		assertEquals(result.size(),ONE);
		assertEquals(sequence, result);

		final Sequence inputSeq = new Sequence();
		when(project.getPredictiveModelIndexByName(TEST)).thenReturn(ONE);
		final NolModel2 model = mock(NolModel2.class);
		when(project.getPredictiveModel(ONE)).thenReturn(model);
		when(model.isTrained()).thenReturn(true);
		final Vector infors = new Vector<>();
		infors.addElement(10.1);
		infors.addElement(10.2);
		when(model.getWholeParametersVector()).thenReturn(infors);
		final Sequence returnVal = (Sequence)gateWay.getPredictiveModelXMLParameters(inputSeq, TEST);
		final Object[] seqContents = returnVal.getContents();
		assertEquals(10.1, seqContents[0]);
		assertEquals(10.2, seqContents[1]);
	}
	/**
	 * Test methods on predictive model with lists
	 *
	 * @throws G2AccessException, MathException
	 */
	@Test
	public void testPredictiveModelWithLists() throws G2AccessException, MathException{
		when(project.getPredictiveModelIndexByName(TEST)).thenReturn(ZERO);
		when(project.getPredictiveModel(ZERO)).thenReturn(nolModel);
		when(nolModel.getParametersVector()).thenReturn(list);
		assertTrue(((Sequence) gateWay.getPredictiveModelParameters(sequence, TEST)).size() == list.size());
	}

	/**
	 * Test methods on BPN model
	 * @throws G2AccessException
	 * @throws MathException
	 */
	@Test
	public void testBPNModel() throws G2AccessException, MathException{
		final NolBpnModel bpnModel = mock(NolBpnModel.class);
		when(project.getNumberOfBpnModels()).thenReturn(ONE);
		when(project.getBpnModel(ZERO)).thenReturn(bpnModel);
		when(bpnModel.getName()).thenReturn(TEST);
		assertTrue(gateWay.getBPNModelNames(sequence).size() > ZERO);
		assertNotNull(gateWay.setBPNModelParameters(sequenceString, TEST));
		assertTrue(((Sequence) gateWay.getBPNModelParameters(sequenceString, TEST)).size() == ZERO);

		final Sequence inputSeq = new Sequence();
		when(project.getBpnModelIndexByName(TEST)).thenReturn(ONE);
		final NolBpnModel model = mock(NolBpnModel.class);
		when(project.getBpnModel(ONE)).thenReturn(model);
		final Vector infors = new Vector<>();
		infors.addElement(10.1);
		infors.addElement(10.2);
		when(model.getParametersVector()).thenReturn(infors);
		final Sequence returnVal = (Sequence)gateWay.getBPNModelParameters(inputSeq, TEST);
		final Object[] seqContents = returnVal.getContents();
		assertEquals(10.1, seqContents[0]);
		assertEquals(10.2, seqContents[1]);
	}

	/**
	 * Test methods on RBF Model
	 * @throws G2AccessException
	 * @throws MathException
	 */
	@Test
	public void testRBFNModel() throws G2AccessException, MathException{
		final NolRbfnModel rbfnModel = mock(NolRbfnModel.class);
		when(project.getNumberOfRbfnModels()).thenReturn(ONE);
		when(project.getRbfnModel(ZERO)).thenReturn(rbfnModel);
		when(rbfnModel.getName()).thenReturn(TEST);
		assertTrue(gateWay.getRBFNModelNames(sequence).size() > ZERO);
		assertNotNull(gateWay.setRBFNModelParameters(sequenceString, TEST));
		assertTrue(((Sequence) gateWay.getRBFNModelParameters(sequenceString, TEST)).size() == ZERO);

		final Sequence inputSeq = new Sequence();
		when(project.getRbfnModelIndexByName(TEST)).thenReturn(ONE);
		final NolRbfnModel model = mock(NolRbfnModel.class);
		when(project.getRbfnModel(ONE)).thenReturn(model);
		final Vector infors = new Vector<>();
		infors.addElement(10.1);
		infors.addElement(10.2);
		when(model.getParametersVector()).thenReturn(infors);
		final Sequence returnVal = (Sequence)gateWay.getRBFNModelParameters(inputSeq, TEST);
		final Object[] seqContents = returnVal.getContents();
		assertEquals(10.1, seqContents[0]);
		assertEquals(10.2, seqContents[1]);
	}

	/**
	 * Test methods on AAN Model
	 * @throws G2AccessException
	 * @throws MathException
	 */
	@Test
	public void testAANModel() throws G2AccessException, MathException{
		final NolAnnModel nolAnnModel = mock(NolAnnModel.class);
		when(project.getNumberOfAnnModels()).thenReturn(ONE);
		when(project.getAnnModel(ZERO)).thenReturn(nolAnnModel);
		when(nolAnnModel.getName()).thenReturn(TEST);

		assertTrue(gateWay.getAANModelNames(sequence).size() > ZERO);
		assertNotNull(gateWay.setAANModelParameters(sequenceString, TEST));
		assertTrue(((Sequence) gateWay.getAANModelParameters(sequenceString, TEST)).size() == ZERO);

		final Sequence inputSeq = new Sequence();
		when(project.getAnnModelIndexByName(TEST)).thenReturn(ONE);
		when(project.getAnnModel(ONE)).thenReturn(nolAnnModel);
		final Vector infors = new Vector<>();
		infors.addElement(10.1);
		infors.addElement(10.2);
		when(nolAnnModel.getParametersVector()).thenReturn(infors);
		final Sequence returnVal = (Sequence)gateWay.getAANModelParameters(inputSeq, TEST);
		final Object[] seqContents = returnVal.getContents();
		assertEquals(10.1, seqContents[0]);
		assertEquals(10.2, seqContents[1]);
	}

	/**
	 * Test methods on RHO Model
	 * @throws G2AccessException
	 * @throws MathException
	 */
	@Test
	public void testRHOModel() throws G2AccessException, MathException{
		final NolRhoModel nolRhoModel = mock(NolRhoModel.class);
		when(project.getNumberOfRhoModels()).thenReturn(ONE);
		when(project.getRhoModel(ZERO)).thenReturn(nolRhoModel);
		when(nolRhoModel.getName()).thenReturn(TEST);
		assertTrue(gateWay.getRHOModelNames(sequence).size() > ZERO);
		assertNotNull(gateWay.setRHOModelParameters(sequenceString, TEST));
		assertTrue(((Sequence) gateWay.getRHOModelParameters(sequenceString, TEST)).size() == ZERO);

		final Sequence inputSeq = new Sequence();
		when(project.getRhoModelIndexByName(TEST)).thenReturn(ONE);
		when(project.getRhoModel(ONE)).thenReturn(nolRhoModel);
		final Vector infors = new Vector<>();
		infors.addElement(10.1);
		infors.addElement(10.2);
		when(nolRhoModel.getParametersVector()).thenReturn(infors);
		final Sequence returnVal = (Sequence)gateWay.getRHOModelParameters(inputSeq, TEST);
		final Object[] seqContents = returnVal.getContents();
		assertEquals(10.1, seqContents[0]);
		assertEquals(10.2, seqContents[1]);
	}

	/**
	 * Test methods on Pls Model
	 * @throws G2AccessException
	 * @throws MathException
	 */
	@Test
	public void testPlsModel() throws G2AccessException, MathException{
		final NolPlsModel nolPlsModel = mock(NolPlsModel.class);
		when(project.getNumberOfPlsModels()).thenReturn(ONE);
		when(project.getPlsModel(ZERO)).thenReturn(nolPlsModel);
		when(nolPlsModel.getName()).thenReturn(TEST);
		assertTrue(gateWay.getPlsModelNames(sequence).size() > ZERO);
		assertEquals(gateWay.showPlsModelPrediction(TEST), ONE);
		when(project.getPlsModelIndexByName(TEST)).thenReturn(-1);
		assertEquals(gateWay.showPlsModelPrediction(TEST), ZERO);
		assertTrue(((Sequence) gateWay.getPlsModelParameters(sequenceString, TEST)).size() == ZERO);

		final Sequence inputSeq = new Sequence();
		when(project.getPlsModelIndexByName(TEST)).thenReturn(ONE);
		final NolPlsModel model = mock(NolPlsModel.class);
		when(project.getPlsModel(ONE)).thenReturn(model);
		final Vector infors = new Vector<>();
		infors.addElement(10.1);
		infors.addElement(10.2);
		when(model.getParametersVector()).thenReturn(infors);
		final Sequence returnVal = (Sequence)gateWay.getPlsModelParameters(inputSeq, TEST);
		final Object[] seqContents = returnVal.getContents();
		assertEquals(10.1, seqContents[0]);
		assertEquals(10.2, seqContents[1]);
	}

	/**
	 * Test methods on Pca Model
	 * @throws G2AccessException
	 * @throws MathException
	 */
	@Test
	public void testPcaModel() throws G2AccessException, MathException{
		final NolPcaModel nolPcaModel = mock(NolPcaModel.class);
		when(project.getNumberOfPcaModels()).thenReturn(ONE);
		when(project.getPcaModel(ZERO)).thenReturn(nolPcaModel);
		when(nolPcaModel.getName()).thenReturn(TEST);
		assertTrue(gateWay.getPcaModelNames(sequence).size() > ZERO);
		assertNotNull(gateWay.getPcaModelData(sequenceString, TEST));
		assertTrue(((Sequence) gateWay.getPcaModelParameters(sequenceString, TEST)).size() == ZERO);

		final Sequence inputSeq = new Sequence();
		when(project.getPcaModelIndexByName(TEST)).thenReturn(ONE);
		when(project.getPcaModel(ONE)).thenReturn(pcaModel);
		final Vector infors = new Vector<>();
		infors.addElement(10.1);
		infors.addElement(10.2);
		when(pcaModel.getParametersVector()).thenReturn(infors);
		final Sequence returnVal = (Sequence)gateWay.getPcaModelParameters(inputSeq, TEST);
		final Object[] seqContents = returnVal.getContents();
		assertEquals(10.1, seqContents[0]);
		assertEquals(10.2, seqContents[1]);
	}

	/**
	 * Test methods on validate models
	 * @throws MathException
	 * @throws G2AccessException
	 */
	@Test
	public void testValidateModels() throws MathException,G2AccessException{
		assertEquals(gateWay.validatePcaModel(TEST, sequence), ONE);
		assertEquals(gateWay.validatePredictiveModel(TEST, sequence, sequence), ONE);
		assertEquals(gateWay.validatePredictiveModel(TEST, sequence, sequenceString), ZERO);
	}

	/**
	 * Test method to validate classic model
	 * @throws MathException
	 * @throws G2AccessException
	 */
	@Test
	public void testValidateClassicModel() throws MathException,G2AccessException{
		assertEquals(gateWay.validateClassicModel(TEST, sequence, sequence), ZERO);
		when(project.getBpnModelIndexByName(TEST)).thenReturn(ZERO);
		when(project.getBpnModel(ZERO)).thenReturn(bpnModel);
		assertEquals(gateWay.validateClassicModel(TEST, sequence, sequence), ONE);
		assertEquals(gateWay.validateClassicModel(TEST, sequence, sequenceString), ZERO);
	}

	/**
	 * Test method to validate pls model
	 * @throws MathException
	 * @throws G2AccessException
	 */
	@Test
	public void testValidatePlsModel() throws MathException,G2AccessException{
		final NolPlsModel plsModel = mock(NolPlsModel.class);
		assertEquals(gateWay.validatePlsModel(TEST, sequence, sequence), ZERO);
		when(project.getPlsModel(ZERO)).thenReturn(plsModel);
		when(plsModel.getName()).thenReturn(TEST);
		when(plsModel.getPreprocessor()).thenReturn(preprocessor);
		when(plsModel.getName()).thenReturn(TEST);
		when(plsModel.getMaximumInputs()).thenReturn(ONE);
		when(plsModel.getInputs()).thenReturn(intList);
		when(plsModel.getHasTimeStamps()).thenReturn(true);
		when(plsModel.getOutputs()).thenReturn(intList);
		when(plsModel.getNumberOfOutputs(ZERO)).thenReturn(ONE);
		assertEquals(gateWay.validatePlsModel(TEST, sequence, sequence), ONE);
		assertEquals(gateWay.validatePlsModel(TEST, sequence, sequenceString), ZERO);
		when(project.getPlsModelIndexByName(TEST)).thenReturn(-1);
		assertEquals(gateWay.validatePlsModel(TEST, sequence, sequence), ZERO);
	}

	/**
	 * Test method to validate AAN model
	 * @throws MathException
	 * @throws G2AccessException
	 */
	@Test
	public void testValidateAANModel() throws MathException,G2AccessException{
		final NolAnnModel annModel = mock(NolAnnModel.class);
		assertEquals(gateWay.validateAANModel(TEST, sequence), ZERO);
		when(project.getBpnModelIndexByName(TEST)).thenReturn(-1);
		when(project.getRbfnModelIndexByName(TEST)).thenReturn(-1);
		when(project.getAnnModelIndexByName(TEST)).thenReturn(ZERO);
		when(project.getAnnModel(ZERO)).thenReturn(annModel);
		when(annModel.getName()).thenReturn(TEST);
		when(annModel.getPreprocessor()).thenReturn(preprocessor);
		when(annModel.getName()).thenReturn(TEST);
		when(annModel.getMaximumInputs()).thenReturn(ONE);
		when(annModel.getInputs()).thenReturn(intList);
		when(annModel.getHasTimeStamps()).thenReturn(true);
		when(annModel.getOutputs()).thenReturn(intList);
		when(annModel.getNumberOfOutputs(ZERO)).thenReturn(ONE);
		assertEquals(gateWay.validateAANModel(TEST, sequence), ONE);
		assertEquals(gateWay.validateAANModel(TEST, sequenceString), ZERO);
	}

	/**
	 * Test method to validate classid model from name
	 * @throws G2AccessException
	 */
	@Test
	public void testValidateClassicModelFromName() throws G2AccessException {
		when(project.getBpnModelIndexByName(TEST)).thenReturn(-1);
		when(project.getRbfnModelIndexByName(TEST)).thenReturn(ZERO);
		when(project.getAnnModelIndexByName(TEST)).thenReturn(-1);
		assertEquals(gateWay.showClassicModelPrediction(TEST),ZERO);
		when(project.getRbfnModelIndexByName(TEST)).thenReturn(ZERO);
		when(project.getAnnModelIndexByName(TEST)).thenReturn(ZERO);
		when(project.getRhoModelIndexByName(TEST)).thenReturn(ZERO);
		assertEquals(gateWay.showClassicModelPrediction(TEST),ZERO);
		when(project.getRbfnModelIndexByName(TEST)).thenReturn(-1);
		when(project.getAnnModelIndexByName(TEST)).thenReturn(-1);
		assertEquals(gateWay.showClassicModelPrediction(TEST),ZERO);
		when(project.getRhoModelIndexByName(TEST)).thenReturn(-1);
		assertEquals(gateWay.showClassicModelPrediction(TEST),ZERO);
	}
	/**
	 * Test methods on export data to G2
	 * @throws MathException
	 * @throws G2AccessException
	 */
	@Test
	public void testExportDataToG2() throws MathException,G2AccessException{
		when(connection.callRPC(any(Symbol.class), any(String[].class), anyInt())).thenReturn(sequence);
		gateWay.exportDataMatrixToG2(series, TEST, TEST, true);
		assertTrue(sequence.size() > ZERO);
		gateWay.exportDataSetToG2(series, TEST, true, namesList, namesList);
		assertTrue(sequence.size() == ZERO);
		when(series.getVarObjects()).thenReturn(mockList);
		gateWay.exportDataSetToG2(series, TEST, true, namesList, namesList);
		assertTrue(sequence.size() == ZERO);
	}

	/**
	 * Test method to get data set from studio
	 * @throws MathException
	 * @throws G2AccessException
	 */
	@Test
	public void testGetDataSetFromStudio() throws MathException, G2AccessException{
		when(connection.callRPC(any(Symbol.class), any(String[].class), anyInt())).thenReturn(sequence);
		assertTrue(gateWay.getDataSetFromStudio("test.test").size() > ZERO);
		assertTrue(gateWay.getDataSetFromStudio("Rawdata.test").size() > ZERO);
		when(frame.classifyInputOutput(any(DataSeries.class))).thenReturn(new Vector[]{namesList});
		assertTrue(gateWay.getDataSetFromStudio("RawData.test").size() == sequence.size());
	}

	/**
	 * Test method to inform G2 training complete
	 * @throws G2AccessException
	 */
	@Test
	public void testInformG2TrainingComplete() throws G2AccessException{
		when(connection.callRPC(any(Symbol.class), any(String[].class), anyInt())).thenReturn(sequence);
		gateWay.informG2TrainingComplete(UUID.randomUUID().toString(), true);
		gateWay.informG2TrainingComplete(UUID.randomUUID().toString(), true, intList);
		gateWay.informG2SimpleTrainingComplete(UUID.randomUUID().toString(), true, intList);
		gateWay.informG2ErrorOccur(UUID.randomUUID().toString(), true, "error");
		verify(connection, times(6)).callRPC(any(Symbol.class), any(String[].class), anyInt());
	}

	/**
	 * Test methods for data sequence
	 * @throws G2AccessException
	 */
	@Test
	public void testDataSequence() throws G2AccessException{
		when(connection.callRPC(any(Symbol.class), any(String[].class), anyInt())).thenReturn(sequence);
		assertEquals(gateWay.getDataSequence(), sequence);
	}

	/**
	 * Test method to show chart
	 * @throws G2AccessException
	 * @throws MathException
	 * @throws NoSuchAttributeException
	 */
	@Test
	public void testShowChart()  throws G2AccessException, MathException,NoSuchAttributeException{
		assertEquals(gateWay.showLineChart(sequence), ZERO);
		assertEquals(gateWay.showProjectionChart(sequence), ZERO);
		assertEquals(gateWay.showXYChart(sequence), ZERO);
	}

	/**
	 * Test method to train predictive model
	 * @throws NoSuchAttributeException
	 * @throws G2AccessException
	 */
	@Test
	public void testTrainPredictiveModel() throws NoSuchAttributeException, G2AccessException{
		when(connection.callRPC(any(Symbol.class), any(String[].class), anyInt())).thenReturn(sequence);

		assertTrue(gateWay.trainPredictiveModel(TEST, trainingSequence, trainingSequence, HUNDRED, true, true, true).getAttributeCount() == ZERO);

		when(structure.getAttributeValue(Symbol.intern(CLASSIFICATION))).thenReturn(OUTPUT);
		assertTrue(gateWay.trainPredictiveModelFromFile(modelParams, modelParams, HUNDRED, true, true, true).getAttributeCount() > ZERO);

		when(structure.getAttributeValue(Symbol.intern(CLASSIFICATION))).thenReturn(INPUT);
		assertTrue(gateWay.trainPredictiveModelFromFile(modelParams, modelParams, HUNDRED, true, true, true).getAttributeCount() > ZERO);

		when(structure.getAttributeValue(Symbol.intern(CLASSIFICATION))).thenReturn(OUTPUT);
		assertTrue(gateWay.trainPredictiveModelFromFileWithXMLExport(modelParams, modelParams, HUNDRED, true, true, true, TEST).getAttributeCount() > ZERO);
		when(structure.getAttributeValue(Symbol.intern(CLASSIFICATION))).thenReturn(INPUT);
		assertTrue(gateWay.trainPredictiveModelFromFileWithXMLExport(modelParams, modelParams, HUNDRED, true, true, true, TEST).getAttributeCount() > ZERO);
	}

	/**
	 * Test method to calculate predictive model
	 * @throws NoSuchAttributeException
	 * @throws G2AccessException
	 */
	@Test
	public void testCalculatePredictiveModel() throws NoSuchAttributeException, G2AccessException{
		when(structure.getAttributeValue(Symbol.intern(CLASSIFICATION))).thenReturn(OUTPUT);
		assertTrue(gateWay.calculatePredictiveModelSensitivityFromFile(modelParams, modelParams).getAttributeCount() > ZERO);
		when(structure.getAttributeValue(Symbol.intern(CLASSIFICATION))).thenReturn(INPUT);
		assertTrue(gateWay.calculatePredictiveModelSensitivityFromFile(modelParams, modelParams).getAttributeCount() > ZERO);
	}

	/**
	 * Test method for sensitivity calculation
	 * @throws G2AccessException
	 */
	@Test
	public void testSensitivityCalculation() throws G2AccessException{
		when(connection.callRPC(any(Symbol.class), any(String[].class), anyInt())).thenReturn(sequence);
		gateWay.endSensitivityCalculation(TEST, matrix);
		gateWay.closeG2Connection();
		gateWay.clear();
	}
}
