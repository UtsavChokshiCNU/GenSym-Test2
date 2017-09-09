package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.inOrder;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.spy;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Vector;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.mockito.ArgumentCaptor;
import org.mockito.InOrder;
import org.mockito.Matchers;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;
import org.powermock.api.mockito.PowerMockito;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ClassicRbfn;
import com.gensym.math.matrix.Matrix;

public class NolRbfnModelTest {
	private static final int MATRIX_X_ROWS_COUNT = 2;
	private static final int MATRIX_X_COLS_COUNT = 3;
	private static final int MATRIX_Y_ROWS_COUNT = 4;
	private static final int MATRIX_Y_COLS_COUNT = 5;

	private static final double DELTA = 0.1;
	private static final double RMSE = 300;

	private static final String DATA_WRITTEN = "Written Data";
	private static final String NORMALIZED_FACTOR_WRITTEN = "Written Normalized Factor";
	private static final String PARAMETERS_WRITTEN = "Written Parameters";
	private static final String WEIGHTS_WRITTEN = "Written Weights";
	private static final String XML_FILE_WRITTEN = "Written Xml File";

	private static final String INFILE_CONTENT = "Infile Content";
	private static final String READ_ERROR_FROM_FILE_RESPONSE = "Error Message";

	private boolean fileExists;
	private boolean readWeightsFromCorrectFile;
	private ClassicRbfn classicRbfn;
	private double[][] predictionData;
	private File infile;
	private File outfile;
	private int nout;
	private int runningParameter;
	private IOException writeRbfnForEvaluateException;
	private Matrix matrixYPred;
	private NolClassicModelTrainer trainer;
	private NolRbfnModel sut;
	private NolRbfnModel sutSpy;
	private Preprocessor preprocessor;
	private String name;
	private String[] makeRPCFileNamesResponse;
	private Vector<String> inputs;
	private Vector<long[]> inputDelays;
	private Vector<String> outputs;
	private Vector<long[]> outputDelays;
	private Vector<String> modelParametersVector;

	@Rule
	public TemporaryFolder folder = new TemporaryFolder();

	@Before
	public void setup() throws IOException, MathException {
		fileExists = true;
		makeRPCFileNamesResponse = new String[] { "Filename 1", "Filename 2" };
		nout = 2;
		predictionData = new double[][] { { 11, 12, 13 }, { 21, 22, 23 } };
		readWeightsFromCorrectFile = false;
		writeRbfnForEvaluateException = null;

		createSut();
	}

	@Test
	public void test_setNormalizedData_flagIsTrue_setsIsNormalizedData() {
		// Arrange
		// No arrangements

		// Act
		sut.setNormalizeData(true);

		// Assert
		assertTrue(sut.isNormalizeData());
	}

	@Test
	public void test_setNormalizedData_flagIsTrue_InvokesSetNormalizeDataWithTrueFlag() {
		// Arrange
		// No arrangements

		// Act
		sut.setNormalizeData(true);

		// Assert
		verify(classicRbfn).setNormalizeData(true);
	}

	@Test
	public void test_setNormalizedData_flagIsFalse_resetsIsNormalizedData() {
		// Arrange
		// No arrangements

		// Act
		sut.setNormalizeData(false);

		// Assert
		assertFalse(sut.isNormalizeData());
	}

	@Test
	public void test_setNormalizedData_flagIsFalse_InvokesSetNormalizeDataWithFalseFlag() {
		// Arrange
		// No arrangements

		// Act
		sut.setNormalizeData(false);

		// Assert
		verify(classicRbfn).setNormalizeData(false);
	}

	@Test
	public void test_prepareDataStat_always_invokesPrepareDataStat() throws MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);

		// Act
		sut.prepareDataStat(matrixX, matrixY);

		// Assert
		verify(classicRbfn).prepareDataStat(matrixX, matrixY);
	}

	@Test
	public void test_writeRbfnToFileWithMatrices_always_invokesWriteData() throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		ArgumentCaptor<BufferedWriter> bufferedWriterCaptor = ArgumentCaptor.forClass(BufferedWriter.class);
		ArgumentCaptor<Matrix> matrixXCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Matrix> matrixYCaptor = ArgumentCaptor.forClass(Matrix.class);
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeRbfnToFile(outfile.getAbsolutePath(), matrixX, matrixY);

		// Assert
		verify(classicRbfn).writeData(bufferedWriterCaptor.capture(), matrixXCaptor.capture(), matrixYCaptor.capture());
		assertEquals(matrixX, matrixXCaptor.getValue());
		assertEquals(matrixY, matrixYCaptor.getValue());
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains(DATA_WRITTEN));
	}

	@Test
	public void test_writeRbfnToFileWithMatrices_always_invokesWriteParameters() throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeRbfnToFile(outfile.getAbsolutePath(), matrixX, matrixY);

		// Assert
		verify(classicRbfn).writeParameters(Matchers.any(BufferedWriter.class));
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains(PARAMETERS_WRITTEN));
	}

	@Test
	public void test_writeRbfnToFileWithMatrices_runningParameterMethodIsZero_writesNormalClusteringMethodToFile()
			throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		outfile = folder.newFile("Outfile.tmp");
		sut.setRunningParameter(0);

		// Act
		sut.writeRbfnToFile(outfile.getAbsolutePath(), matrixX, matrixY);

		// Assert
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains("0; normal clustering method"));
	}

	@Test
	public void test_writeRbfnToFileWithMatrices_runningParameterIsNotZero_writesNormalClusteringMethodToFile()
			throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		outfile = folder.newFile("Outfile.tmp");
		runningParameter = 10;
		sut.setRunningParameter(runningParameter);

		// Act
		sut.writeRbfnToFile(outfile.getAbsolutePath(), matrixX, matrixY);

		// Assert
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains(runningParameter + "; class-separate clustering"));
	}

	@Test
	public void test_writeRbfnToFile_always_invokesWriteParameters() throws IOException {
		// Arrange
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeRbfnToFile(outfile.getAbsolutePath());

		// Assert
		verify(classicRbfn).writeParameters(Matchers.any(BufferedWriter.class));
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains(PARAMETERS_WRITTEN));
	}

	@Test
	public void test_writeRbfnToFile_always_invokesWriteWeights() throws IOException {
		// Arrange
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeRbfnToFile(outfile.getAbsolutePath());

		// Assert
		verify(classicRbfn).writeWeights(Matchers.any(BufferedWriter.class));
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains(WEIGHTS_WRITTEN));
	}

	@Test
	public void test_writeNormalizeFactorToFile_always_addsVariablesStartingWithVariablesComma() throws IOException {
		// Arrange
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeNormalizeFactorToFile(outfile.getAbsolutePath());

		// Assert
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.startsWith("Variables,"));
	}

	@Test
	public void test_writeNormalizeFactorToFile_always_addsInputVariablesWithZeroDelayWithoutDelayInParenthesis()
			throws IOException {
		// Arrange
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeNormalizeFactorToFile(outfile.getAbsolutePath());

		// Assert
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains("Input 1,"));
	}

	@Test
	public void test_writeNormalizeFactorToFile_always_addsInputVariablesWithDelaysAsDelayInParenthesis()
			throws IOException {
		// Arrange
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeNormalizeFactorToFile(outfile.getAbsolutePath());

		// Assert
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains("Input 2(1),Input 3(1),Input 3(2),Input 3(3),"));
	}

	@Test
	public void test_writeNormalizeFactorToFile_always_invokesWriteNormalizeFactorToFile() throws IOException {
		// Arrange
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeNormalizeFactorToFile(outfile.getAbsolutePath());

		// Assert
		verify(classicRbfn).writeNormalizeFactorToFile(Matchers.any(BufferedWriter.class));
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.trim().endsWith(NORMALIZED_FACTOR_WRITTEN));
	}

	@Test
	public void test_writeNormalizeFactorToFile_always_addsOutputVariablesWithoutDelays() throws IOException {
		// Arrange
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeNormalizeFactorToFile(outfile.getAbsolutePath());

		// Assert
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.trim().contains("Output 1,Output 2"));
	}

	@Test
	public void test_readRbfnFromFile_fileDoesNotExist_doesNotInvokeReadWeights() throws IOException {
		// Arrange
		fileExists = false;
		arrangeForReadRbfnFromFile();

		// Act
		sut.readRbfnFromFile(infile.getAbsolutePath());

		// Assert
		verify(classicRbfn, never()).readWeights(Matchers.any(BufferedReader.class));
	}

	@Test
	public void test_readRbfnFromFile_fileExists_invokesReadWeights() throws IOException {
		// Arrange
		arrangeForReadRbfnFromFile();

		// Act
		sut.readRbfnFromFile(infile.getAbsolutePath());

		// Assert
		verify(classicRbfn).readWeights(Matchers.any(BufferedReader.class));
		assertTrue(readWeightsFromCorrectFile);
	}

	@Test
	public void test_writeRbfnForEvaluate_always_invokesWriteData() throws IOException, MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		ArgumentCaptor<BufferedWriter> bufferedWriterCaptor = ArgumentCaptor.forClass(BufferedWriter.class);
		ArgumentCaptor<Matrix> matrixXCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Matrix> matrixYCaptor = ArgumentCaptor.forClass(Matrix.class);
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeRbfnForEvaluate(outfile.getAbsolutePath(), matrixX, matrixY);

		// Assert
		verify(classicRbfn).writeData(bufferedWriterCaptor.capture(), matrixXCaptor.capture(), matrixYCaptor.capture());
		assertEquals(matrixX, matrixXCaptor.getValue());
		assertEquals(matrixY, matrixYCaptor.getValue());
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains(DATA_WRITTEN));
	}

	@Test
	public void test_writeRbfnForEvaluate_always_invokesWriteParameters() throws IOException, MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeRbfnForEvaluate(outfile.getAbsolutePath(), matrixX, matrixY);

		// Assert
		verify(classicRbfn).writeParameters(Matchers.any(BufferedWriter.class));
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains(PARAMETERS_WRITTEN));
	}

	@Test
	public void test_writeRbfnForEvaluate_always_invokesWriteWeights() throws IOException, MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		outfile = folder.newFile("Outfile.tmp");

		// Act
		sut.writeRbfnForEvaluate(outfile.getAbsolutePath(), matrixX, matrixY);

		// Assert
		verify(classicRbfn).writeWeights(Matchers.any(BufferedWriter.class));
		File fileStream = new File(outfile.getAbsolutePath());
		String allText = readStream(fileStream);
		assertTrue(allText.contains(WEIGHTS_WRITTEN));
	}

	@Test
	public void test_evaluate_always_setsFlagBeforeInvokingMakeRPCFileNamesMethod() throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForEvaluate();

		// Act
		sutSpy.evaluate(matrixX, matrixY);

		// Assert
		InOrder inOrder = inOrder(trainer);
		inOrder.verify(trainer).setFlag(NolClassicModelTrainer.RBFNFIT);
		inOrder.verify(trainer).makeRPCfileNames();
	}

	@Test
	public void test_evaluate_always_setsInputBeforeInvokingMakeRPCFileNamesMethod() throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForEvaluate();

		// Act
		sutSpy.evaluate(matrixX, matrixY);

		// Assert
		InOrder inOrder = inOrder(trainer);
		inOrder.verify(trainer).setInput(matrixX);
		inOrder.verify(trainer).makeRPCfileNames();
	}

	@Test
	public void test_evaluate_always_setsOutputBeforeInvokingMakeRPCFileNamesMethod()
			throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForEvaluate();

		// Act
		sutSpy.evaluate(matrixX, matrixY);

		// Assert
		InOrder inOrder = inOrder(trainer);
		inOrder.verify(trainer).setOutput(matrixY);
		inOrder.verify(trainer).makeRPCfileNames();
		assertEquals(matrixX.getRows(), matrixY.getRows());
		assertEquals(nout, matrixY.getCols());
	}

	@Test
	public void test_evaluate_always_invokesWriteRbfnForEvaluate() throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForEvaluate();

		// Act
		sutSpy.evaluate(matrixX, matrixY);

		// Assert
		verify(sutSpy).writeRbfnForEvaluate(makeRPCFileNamesResponse[0], matrixX, matrixY);
	}

	@Test
	public void test_evaluate_always_invokesJfit_tester() throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForEvaluate();

		// Act
		sutSpy.evaluate(matrixX, matrixY);

		// Assert
		verify(trainer).jfit_tester(makeRPCFileNamesResponse[0], makeRPCFileNamesResponse[1]);
	}

	@Test
	public void test_evaluate_always_invokesReadPredictionFromFile() throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForEvaluate();

		// Act
		sutSpy.evaluate(matrixX, matrixY);

		// Assert
		verify(sutSpy).readPredictionFromFile(makeRPCFileNamesResponse[1], matrixY);
	}

	@Test
	public void test_evaluate_always_invokesDeleteFiles() throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForEvaluate();

		// Act
		sutSpy.evaluate(matrixX, matrixY);

		// Assert
		verify(trainer).deleteFiles(makeRPCFileNamesResponse);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_evaluate_IOExceptionIsThrown_throwsMathException() throws MathException, IOException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		writeRbfnForEvaluateException = new IOException("Failed while writing Rbfn for evaluation.");
		arrangeForEvaluate();

		// Act
		sutSpy.evaluate(matrixX, matrixY);
	}

	@Test
	public void test_readPredictionFromFile_fileDoesNotExist_DoesNotUnnormalizePrediction()
			throws IOException, MathException {
		// Arrange
		fileExists = false;
		arrangeForReadPredictionFromFile();
		sut.setNormalizeData(true);

		// Act
		sut.readPredictionFromFile(infile.getAbsolutePath(), matrixYPred);

		// Assert
		verify(classicRbfn, never()).unnormalizePrediction(Matchers.any(Matrix.class));
	}

	@Test
	public void test_readPredictionFromFile_fileExists_setsPredictionsToMatrix() throws IOException, MathException {
		// Arrange
		arrangeForReadPredictionFromFile();

		// Act
		sut.readPredictionFromFile(infile.getAbsolutePath(), matrixYPred);

		// Assert
		for (int i = 0; i < predictionData.length; i++) {
			for (int j = 0; j < predictionData[i].length; j++) {
				assertEquals(predictionData[i][j], matrixYPred.get(i, j), DELTA);
			}
		}
	}

	@Test
	public void test_readPredictionFromFile_fileExists_setsRmse() throws IOException, MathException {
		// Arrange
		arrangeForReadPredictionFromFile();

		// Act
		sut.readPredictionFromFile(infile.getAbsolutePath(), matrixYPred);

		// Assert
		assertEquals(RMSE, sut.getRMSE(), DELTA);
	}

	@Test
	public void test_readPredictionFromFile_dataIsNormalized_invokesUnnormalizePrediction()
			throws IOException, MathException {
		// Arrange
		arrangeForReadPredictionFromFile();
		sut.setNormalizeData(true);

		// Act
		sut.readPredictionFromFile(infile.getAbsolutePath(), matrixYPred);

		// Assert
		verify(classicRbfn).unnormalizePrediction(matrixYPred);
	}

	@Test
	public void test_readPredictionFromFile_dataIsUnnormalized_doesNotInvokeUnnormalizePrediction()
			throws IOException, MathException {
		// Arrange
		arrangeForReadPredictionFromFile();
		sut.setNormalizeData(false);

		// Act
		sut.readPredictionFromFile(infile.getAbsolutePath(), matrixYPred);

		// Assert
		verify(classicRbfn, never()).unnormalizePrediction(matrixYPred);
	}

	@Test
	public void test_getDescription_always_returnsModelDescription() {
		// Arrange
		// No arrangements

		// Act & Assert
		assertEquals(classicRbfn.getDescription(), sut.getDescription());
	}

	@Test
	public void test_train_always_setsTrainerFlagBeforeInvokingPrepareDataStat() throws IOException, MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForTrain(matrixX, matrixY);

		// Act
		sutSpy.train(matrixX, matrixY);

		// Assert
		InOrder inOrder = inOrder(trainer, sutSpy);
		inOrder.verify(trainer).setFlag(NolClassicModelTrainer.RBFNTRAINING);
		inOrder.verify(sutSpy).prepareDataStat(matrixX, matrixY);
	}

	@Test
	public void test_train_always_setsFlagBeforeInvokingMakeRPCFileNames() throws IOException, MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForTrain(matrixX, matrixY);

		// Act
		sutSpy.train(matrixX, matrixY);

		// Assert
		InOrder inOrder = inOrder(trainer, sutSpy);
		inOrder.verify(trainer).setFlag(NolClassicModelTrainer.RBFNTRAINING);
		inOrder.verify(trainer).makeRPCfileNames();
	}

	@Test
	public void test_train_always_invokesWriteRbfnForEvaluate() throws IOException, MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForTrain(matrixX, matrixY);

		// Act
		sutSpy.train(matrixX, matrixY);

		// Assert
		verify(sutSpy).writeRbfnToFile(makeRPCFileNamesResponse[0], matrixX, matrixY);
	}

	@Test
	public void test_train_always_invokesJrbfnTrainer() throws IOException, MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForTrain(matrixX, matrixY);

		// Act
		sutSpy.train(matrixX, matrixY);

		// Assert
		InOrder inOrder = inOrder(sutSpy, trainer);
		inOrder.verify(sutSpy).writeRbfnToFile(makeRPCFileNamesResponse[0], matrixX, matrixY);
		inOrder.verify(trainer).jrbfn_trainer(makeRPCFileNamesResponse[0], makeRPCFileNamesResponse[1]);
	}

	@Test
	public void test_train_jrbfnTrainerDoesNotReturnOne_invokesInformsListenersForError()
			throws IOException, MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForTrain(matrixX, matrixY);

		// Act
		sutSpy.train(matrixX, matrixY);

		// Assert
		verify(trainer).informListeners("error", READ_ERROR_FROM_FILE_RESPONSE);
	}

	@Test
	public void test_train_always_invokesDeleteFiles() throws IOException, MathException {
		// Arrange
		Matrix matrixX = new Matrix();
		Matrix matrixY = new Matrix();
		matrixX.redimension(MATRIX_X_ROWS_COUNT, MATRIX_X_COLS_COUNT);
		matrixY.redimension(MATRIX_Y_ROWS_COUNT, MATRIX_Y_COLS_COUNT);
		arrangeForTrain(matrixX, matrixY);

		// Act
		sutSpy.train(matrixX, matrixY);

		// Assert
		verify(trainer).deleteFiles(makeRPCFileNamesResponse);
	}

	@Test
	public void test_getParametersVector_always_returnsModelParametersVector() throws MathException {
		// Arrange
		// No arrangements

		// Act & Assert
		assertEquals(classicRbfn.getParametersVector(), sut.getParametersVector());
	}

	@Test
	public void test_setParametersVector_always_invokesModelSetParametersVector() throws MathException {
		// Arrange
		Vector<String> parametersVector = new Vector<String>();
		parametersVector.add("New Parameter 1");

		// Act
		sut.setParametersVector(parametersVector);

		// Assert
		verify(classicRbfn).setParametersVector(parametersVector);
	}

	@Test
	public void test_writeXMLFile_always_invokesWriteXMLFile() throws MathException, IOException {
		// Arrange
		File file = folder.newFile("Output.tmp");
		FileWriter fWriter = new FileWriter(file);
		BufferedWriter target = new BufferedWriter(fWriter);
		int indentNumber = 10;

		// Act
		sut.writeXMLFile(target, indentNumber);

		// Assert
		verify(classicRbfn).writeXMLFile(target, indentNumber);
		target.close();
	}

	private void createSut() throws IOException, MathException {
		arrangeClassicRbfn();

		name = "NolRbfn Model";
		outputs = new Vector<String>();
		outputDelays = new Vector<long[]>();
		inputs = new Vector<String>();
		inputDelays = new Vector<long[]>();

		// Input with only one delay of 0
		inputs.add("Input 1");
		inputDelays.add(new long[] { 0 });

		// Input with only one delay of non-zero
		inputs.add("Input 2");
		inputDelays.add(new long[] { 60000 });

		// Input with multiple non-zero delays
		inputs.add("Input 3");
		inputDelays.add(new long[] { 60000, 120000, 180000 });

		// Output with only one delay of 0
		outputs.add("Output 1");
		outputDelays.add(new long[] { 0 });

		// Output with multiple non-zero delays
		outputs.add("Output 2");
		outputDelays.add(new long[] { 240000, 300000 });

		preprocessor = mock(Preprocessor.class);

		sut = new NolRbfnModel(classicRbfn, name, outputs, inputs, outputDelays, inputDelays, preprocessor);
	}

	private void arrangeForEvaluate() throws IOException, MathException {
		sutSpy = spy(sut);
		arrangeTrainer();

		PowerMockito.doNothing().when(sutSpy).writeRbfnForEvaluate(Matchers.anyString(), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class));
		PowerMockito.doNothing().when(sutSpy).readPredictionFromFile(Matchers.anyString(), Matchers.any(Matrix.class));

		if (writeRbfnForEvaluateException != null) {
			PowerMockito.doThrow(writeRbfnForEvaluateException).when(sutSpy).writeRbfnForEvaluate(Matchers.anyString(),
					Matchers.any(Matrix.class), Matchers.any(Matrix.class));
		}
	}

	private void arrangeForReadPredictionFromFile() throws IOException {
		matrixYPred = new Matrix();
		matrixYPred.redimension(1, 10);

		infile = folder.newFile("Infile.tmp");
		FileWriter fWriter = new FileWriter(infile.getAbsolutePath());
		BufferedWriter bWriter = new BufferedWriter(fWriter);
		// Line 1 Data
		bWriter.write(" " + predictionData[0][0] + " , " + predictionData[0][1] + " , " + predictionData[0][2] + " ;");
		bWriter.newLine();
		// Line 2 Data
		bWriter.write(" " + predictionData[1][0] + " , " + predictionData[1][1] + " , " + predictionData[1][2] + " ;");
		bWriter.newLine();
		// Root mean squared error
		bWriter.write(" " + RMSE + " ;");
		bWriter.close();

		if (!fileExists) {
			infile.delete();
		}
	}

	private void arrangeForReadRbfnFromFile() throws IOException {
		infile = folder.newFile("Infile.tmp");

		FileWriter fWriter = new FileWriter(infile);
		BufferedWriter bWriter = new BufferedWriter(fWriter);
		bWriter.write(INFILE_CONTENT);
		bWriter.close();

		if (!fileExists) {
			infile.delete();
		}
	}

	private void arrangeForTrain(Matrix matrixX, Matrix matrixY) throws MathException, IOException {
		sutSpy = spy(sut);
		arrangeTrainer();

		PowerMockito.doNothing().when(sutSpy).prepareDataStat(matrixX, matrixY);
		PowerMockito.doNothing().when(sutSpy).writeRbfnToFile(Matchers.anyString(), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class));
		PowerMockito.doNothing().when(sutSpy).readRbfnFromFile(Matchers.anyString());
	}

	private void arrangeClassicRbfn() throws IOException, MathException {
		classicRbfn = mock(ClassicRbfn.class);

		PowerMockito.when(classicRbfn.getDescription()).thenReturn("ClassicRbfn Description");

		PowerMockito.when(classicRbfn.getNout()).thenReturn(nout);

		modelParametersVector = new Vector<String>();
		modelParametersVector.add("Parameter 1");

		PowerMockito.when(classicRbfn.getParametersVector()).thenReturn(modelParametersVector);

		PowerMockito.doAnswer(new Answer<Object>() {

			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {

				BufferedReader source = (BufferedReader) invocation.getArguments()[0];
				String readWeights = source.readLine();
				readWeightsFromCorrectFile = readWeights.equals(INFILE_CONTENT);
				return null;
			}
		}).when(classicRbfn).readWeights(Matchers.any(BufferedReader.class));

		PowerMockito.doAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {

				BufferedWriter source = (BufferedWriter) invocation.getArguments()[0];
				source.write(DATA_WRITTEN);
				return null;
			}
		}).when(classicRbfn).writeData(Matchers.any(BufferedWriter.class), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class));

		PowerMockito.doAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {

				BufferedWriter source = (BufferedWriter) invocation.getArguments()[0];
				source.write(NORMALIZED_FACTOR_WRITTEN);
				return null;
			}
		}).when(classicRbfn).writeNormalizeFactorToFile(Matchers.any(BufferedWriter.class));

		PowerMockito.doAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {

				BufferedWriter source = (BufferedWriter) invocation.getArguments()[0];
				source.write(PARAMETERS_WRITTEN);
				return null;
			}

		}).when(classicRbfn).writeParameters(Matchers.any(BufferedWriter.class));

		PowerMockito.doAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {

				BufferedWriter source = (BufferedWriter) invocation.getArguments()[0];
				source.write(WEIGHTS_WRITTEN);
				return null;
			}
		}).when(classicRbfn).writeWeights(Matchers.any(BufferedWriter.class));

		PowerMockito.doAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {

				BufferedWriter source = (BufferedWriter) invocation.getArguments()[0];
				source.write(XML_FILE_WRITTEN);
				return null;
			}
		}).when(classicRbfn).writeXMLFile(Matchers.any(BufferedWriter.class), Matchers.any(int.class));
	}

	private void arrangeTrainer() throws IOException {
		trainer = mock(NolClassicModelTrainer.class);
		PowerMockito.when(trainer.makeRPCfileNames()).thenReturn(makeRPCFileNamesResponse);
		PowerMockito.when(trainer.readErrorFromFile(makeRPCFileNamesResponse[1]))
				.thenReturn(READ_ERROR_FROM_FILE_RESPONSE);
		sutSpy.setTrainer(trainer);
	}

	private static String readStream(File file) throws FileNotFoundException {
		FileInputStream is = new FileInputStream(file);
		StringBuilder sb = new StringBuilder(512);
		try {
			Reader reader = new InputStreamReader(is, "UTF-8");
			int c = 0;
			while ((c = reader.read()) != -1) {
				sb.append((char) c);
			}

			reader.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		return sb.toString();
	}
}
