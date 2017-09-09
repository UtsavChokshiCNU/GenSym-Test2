package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.mock;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.Closeable;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStreamWriter;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.charset.Charset;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.Random;
import java.util.Vector;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.mockito.Matchers;
import org.powermock.api.mockito.PowerMockito;

import com.gensym.DEBUG;
import com.gensym.math.MathException;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.dlg.ProgressEvent;
import com.gensym.nols.dlg.ProgressListener;

public class DataSeriesTest {
	private static final double DELTA = 0.01;
	private static final int ANY_INT = 2;
	private static final int ASCII_TYPE_DS = 1;
	private static final int ASCII_TYPE_CSV = 2;
	private static final int ASCII_TYPE_TXT = 3;
	private static final int ASCII_TYPE_MATRIX = 4;
	private static final int BASE_TIME_STAMP = 10000;
	private static final int BDS_FILE_FORMAT = 1;
	private static final int DATA_FIRST_COLUMN_INDEX = 1;
	private static final int DATA_FIRST_ROW_INDEX = 3;
	private static final int DS_FORMAT = 0;
	private static final int GNNE_DATA_SET_VERSION_ROW_INDEX = 0;
	private static final int GNNE_DATA_SET_SAMPLES_ROW_INDEX = 1;
	private static final int GNNE_DATA_SET_INPUT_DATA_VECTOR_ROW_INDEX = 2;
	private static final int GNNE_DATA_SET_OUTPUT_DATA_VECTOR_ROW_INDEX = 3;
	private static final int GNNE_DATA_SET_DATA_ROW_START_INDEX = 4;
	private static final int GNNE_DATA_SET_DATA_ROW_INDEX_COL_INDEX = 0;
	private static final int GNNE_DATA_SET_DATA_ROW_TIME_STAMP_COL_INDEX = 1;
	private static final int GNNE_DATA_SET_DATA_ROW_OK_COL_INDEX = 2;
	private static final int GNNE_DATA_SET_DATA_ROW_MATRIX_START_COL_INDEX = 3;
	private static final int LISTENERS_VALUE_CHANGED_INVOCATION_MAX_COUNT = 20;
	private static final int MATRIX_FILE_FORMAT = 2;
	private static final int NAME_ROW_INDEX = 1;
	private static final int NON_DATA_ROWS_COUNT = 3;
	private static final int TAG_ROW_INDEX = 0;
	private static final int TIMESTAMPS_FIRST_INDEX_ROW = 3;
	private static final int TIMESTAMPS_INTERVAL = 1000;
	private static final int TYPE_DEFAULT = 0;
	private static final int UNIT_ROW_INDEX = 2;
	private static final int VAR_STAT_DATA_ROW_START_INDEX = 1;
	private static final int VAR_STAT_VAR_NAME_INDEX = 0;
	private static final int VAR_STAT_VAR_MIN_INDEX = 1;
	private static final int VAR_STAT_VAR_MAX_INDEX = 2;
	private static final int VAR_STAT_VAR_RANGE_INDEX = 3;
	private static final int VAR_STAT_VAR_MEAN_INDEX = 4;
	private static final int VAR_STAT_VAR_MEDIAN_INDEX = 5;
	private static final int VAR_STAT_VAR_STD_DEV_INDEX = 6;
	private static final int VAR_STAT_VAR_VARIANCE_INDEX = 7;
	private static final int VAR_STAT_VAR_SKEWNESS_INDEX = 8;
	private static final int VAR_STAT_VAR_KURTOSIS_INDEX = 9;
	private static final String ANY_STRING = "Any String";
	private static final String DEFAULT_TAG_NAME = "Var";
	private static final String DEFAULT_VAR_NAME = "Var";
	private static final String COMMA_SEPARATOR = ",";
	private static final String NEW_LINE = "\n";
	private static final String TAB_SEPARATOR = "\t";
	private static final String TIME_TAG = "Time";
	private static final String TIME_UNIT = "Millisecond";
	private static final String VARIABLE_NEW_NAME_PREFIX = "varNewName";
	private static final String VARIABLE_NEW_TAG_PREFIX = "varNewTag";
	private static final String VARIABLE_NEW_UNIT_PREFIX = "varNewUnit";

	private boolean currentDebugFlag;
	private Random randomGenerator;

	@Rule
	public TemporaryFolder temporaryFolder = new TemporaryFolder();

	@Before
	public void setup() {
		currentDebugFlag = DEBUG.debugFlag;
		randomGenerator = new Random();
	}

	@After
	public void cleanup() {
		DEBUG.debugFlag = currentDebugFlag;
	}

	@Test
	public void test_Instance_isCreatedFromMatrix_initializesVariablesBasedOnMatrixColumnsCount() {
		// Arrange
		Matrix matrix = createMatrix();

		// Act
		DataSeries sut = new DataSeries(matrix);

		// Assert
		assertThatVariablesAreCreatedWithDefaultNames(sut, matrix.getCols());
	}

	@Test
	public void test_Instance_isCreatedFromMatrixAndTimeStamps_initializesVariablesBasedOnMatrixColumnsCount() {
		// Arrange
		long[] timeStamps = createTimeStamps(2);
		Matrix matrix = createMatrix();

		// Act
		DataSeries sut = new DataSeries(timeStamps, matrix);

		// Assert
		assertThatVariablesAreCreatedWithDefaultNames(sut, matrix.getCols());
	}

	@Test
	public void test_Instance_isCreatedFromMatrixAndTimeStamps_initializesTimeStamps() {
		// Arrange
		Matrix matrix = createMatrix();
		long[] timeStamps = createTimeStamps(matrix.getRows());

		// Act
		DataSeries sut = new DataSeries(timeStamps, matrix);

		// Assert
		assertTrue(sut.getHasTimeStamps());
		assertTrue(Arrays.equals(timeStamps, sut.getTimeStamps()));
	}

	@Test
	public void test_Instance_isCreatedWithZeroRows_setsMatrixDataAsNullReference() {
		// Arrange
		int rows = 0;
		int cols = 3;

		// Act
		DataSeries sut = new DataSeries(rows, cols);

		// Assert
		assertNull(sut.getDataMatrix());
	}

	@Test
	public void test_Instance_isCreatedZeroRowsButNonZeroColumns_setsVariablesBasedOnNumberOfColumns() {
		// Arrange
		int rows = 0;
		int cols = 3;

		// Act
		DataSeries sut = new DataSeries(rows, cols);

		// Assert
		assertThatVariablesAreCreatedWithDefaultNames(sut, cols);
	}

	@Test
	public void test_Instance_isCreatedNonZeroRowsAndNonZeroColumns_setsVariablesBasedOnNumberOfColumns() {
		// Arrange
		int rows = 3;
		int cols = 3;

		// Act
		DataSeries sut = new DataSeries(rows, cols);

		// Assert
		assertThatVariablesAreCreatedWithDefaultNames(sut, cols);
	}

	@Test
	public void test_setDataSource_always_setsDataSeriesDataSource() {
		// Arrange
		DataSource dataSource = createRawDataSource();
		DataSeries sut = new DataSeries();

		// Act
		sut.setDataSource(dataSource);

		// Assert
		assertEquals(dataSource, sut.getDataSource());
	}

	@Test
	public void test_getDataSource_dataSourceWasNotSet_returnsNull() {
		// Arrange
		DataSeries sut = new DataSeries();

		// Act & Assert
		assertNull(sut.getDataSource());
	}

	@Test
	public void test_setName_always_setsDataSeriesName() {
		// Arrange
		DataSeries sut = new DataSeries();
		String name = "DataSeries Name";

		// Act
		sut.setName(name);

		// Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_setComment_always_setsDataSeriesComment() {
		// Arrange
		DataSeries sut = new DataSeries();
		String comment = "DataSeries Comment";

		// Act
		sut.setComment(comment);

		// Assert
		assertEquals(comment, sut.getComment());
	}

	@Test
	public void test_setTimeStamps_dataSourceExists_setsDataSourceTimeStamps() {
		// Arrange
		DataSeries sut = new DataSeries();
		RawDataSource dataSource = createRawDataSource();
		sut.setDataSource(dataSource);

		// Act
		sut.setTimeStamps(createTimeStamps(ANY_INT));

		// Assert
		verify(dataSource).setTimeStamps(sut);
	}

	@Test
	public void test_setTimeStampsWithStartTimeAndInterval_always_setsDataSeriesTimeStamps() {
		// Arrange
		int rows = 5, cols = 3;
		DataSeries sut = new DataSeries(rows, cols);
		long startTime = 100000, interval = 10000;

		// Act
		sut.setTimeStamps(startTime, interval);

		// Assert
		assertThatTimeStampsAreSet(sut, cols, startTime, interval);
	}

	@Test
	public void test_setTimeStampsWithStartTimeAndInterval_dataSourceExists_setsDataSourceTimeStamps() {
		// Arrange
		int rows = 5, cols = 3;
		DataSeries sut = new DataSeries(rows, cols);
		long startTime = 100000, interval = 10000;
		RawDataSource dataSource = createRawDataSource();
		sut.setDataSource(dataSource);

		// Act
		sut.setTimeStamps(startTime, interval);

		// Assert
		verify(dataSource).setTimeStamps(sut);
	}

	@Test
	public void test_getRow_dataMatrixDoesNotExist_returnsZero() {
		// Arrange
		DataSeries sut = new DataSeries();
		sut.emptyDataSeries();

		// Act & Assert
		assertEquals(0, sut.getRow());
	}

	@Test
	public void test_getRow_dataMatrixExists_returnsDataMatrixRows() {
		// Arrange
		int rows = 5, cols = 3;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertEquals(rows, sut.getRow());
	}

	@Test
	public void test_getColumn_dataMatrixDoesNotExist_returnsZero() {
		// Arrange
		DataSeries sut = new DataSeries();
		sut.emptyDataSeries();

		// Act & Assert
		assertEquals(0, sut.getColumn());
	}

	@Test
	public void test_getColumn_dataMatrixExists_returnsVariableColumns() {
		// Arrange
		int rows = 5, cols = 3;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertEquals(cols, sut.getColumn());
	}

	@Test
	public void test_isEmpty_dataMatrixDoesNotExist_returnsTrue() {
		// Arrange
		int cols = 3;
		DataSeries sut = new DataSeries(0, cols);

		// Act & Assert
		assertTrue(sut.isEmpty());
	}

	@Test
	public void test_isEmpty_dataMatrixExists_returnsFalse() {
		// Arrange
		int rows = 5, cols = 3;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertFalse(sut.isEmpty());
	}

	@Test
	public void test_getCol_always_returnsDataMatrixRows() {
		// Arrange
		int rows = 5, cols = 3;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertEquals(rows, sut.getRow());
	}

	@Test
	public void test_emptyDataSeries_always_clearsData() {
		// Arrange
		int rows = 5, cols = 3;
		DataSeries sut = new DataSeries(rows, cols);

		// Act
		sut.emptyDataSeries();

		// Assert
		assertNull(sut.getDataMatrix());
	}

	@Test
	public void test_emptyDataSeries_always_setsEmptyDataFlag() {
		// Arrange
		int rows = 5, cols = 3;
		DataSeries sut = new DataSeries(rows, cols);

		// Act
		sut.emptyDataSeries();

		// Assert
		assertTrue(sut.isEmpty());
	}

	@Test
	public void test_emptyDataSeries_always_clearsTimeStamps() {
		// Arrange
		int rows = 5, cols = 3;
		DataSeries sut = new DataSeries(rows, cols);

		// Act
		sut.emptyDataSeries();

		// Assert
		assertEquals(0, sut.getTimeStamps().length);
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getVarObjects_always_returnsVarObjects() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		// Act
		Vector<Variable> varObjects = sut.getVarObjects();

		// Assert
		for (int idx = 0; idx < cols; idx++) {
			Variable variable = varObjects.get(idx);
			String expectedVariableName = "Var" + new Integer(idx + 1).toString();
			assertEquals(expectedVariableName, variable.getName());
			assertEquals(sut, variable.getDataSeries());
			assertEquals(idx, variable.getColumnIndex());
		}
	}

	@Test
	public void test_getVarIndexByName_variableExists_returnsVarIndex() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		for (int idx = 0; idx < cols; idx++) {
			// Act & Assert
			assertEquals(idx, sut.getVarIndexByName(DEFAULT_VAR_NAME + (idx + 1)));
		}
	}

	@Test
	public void test_getVarIndexByName_variableDoesNotExist_returnsMinusOne() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertEquals(-1, sut.getVarIndexByName(ANY_STRING));
	}

	@Test
	public void test_getVarIndex_variableExists_returnsVarIndex() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		for (int idx = 0; idx < cols; idx++) {
			// Act & Assert
			assertEquals(idx, sut.getVarIndex((Variable) sut.getVarObjects().get(idx)));
		}
	}

	@Test
	public void test_getVarIndex_variableDoesNotExist_returnsMinusOne() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertEquals(-1, sut.getVarIndex(new Variable()));
	}

	@Test
	public void test_getVarIndexByTag_variableExists_returnsVarIndex() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		for (int idx = 0; idx < cols; idx++) {
			// Act & Assert
			assertEquals(idx, sut.getVarIndexByTag(DEFAULT_TAG_NAME + (idx + 1)));
		}
	}

	@Test
	public void test_getVarIndexByTag_variableDoesNotExist_returnsMinusOne() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertEquals(-1, sut.getVarIndexByTag(ANY_STRING));
	}

	@Test
	public void test_getVarByName_variableExists_returnsVariable() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		for (int idx = 0; idx < cols; idx++) {
			// Act & Assert
			assertEquals(sut.getVarByIndex(idx), sut.getVarByName(DEFAULT_VAR_NAME + (idx + 1)));
		}
	}

	@Test
	public void test_getVarByName_variableDoesNotExist_returnsNullReference() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertEquals(null, sut.getVarByName(ANY_STRING));
	}

	@Test
	public void test_getVarByTag_variableExists_returnsVariable() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		for (int idx = 0; idx < cols; idx++) {
			// Act & Assert
			assertEquals(sut.getVarByIndex(idx), sut.getVarByTag(DEFAULT_TAG_NAME + (idx + 1)));
		}
	}

	@Test
	public void test_getVarByTag_variableDoesNotExist_returnsNullReference() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertEquals(null, sut.getVarByTag(ANY_STRING));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getVarByIndex_variableExists_returnsVariable() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Variable> varObjects = sut.getVarObjects();

		assertEquals(cols, varObjects.size());
		for (int idx = 0; idx < varObjects.size(); idx++) {
			// Act & Assert
			assertEquals(varObjects.get(idx), sut.getVarByIndex(idx));
		}
	}

	@Test
	public void test_getVarByIndex_variableDoesNotExist_returnsNullReference() {
		// Arrange
		int rows = ANY_INT;
		int cols = ANY_INT;
		DataSeries sut = new DataSeries(rows, cols);

		// Act & Assert
		assertEquals(null, sut.getVarByIndex(cols));
	}

	@Test
	public void test_getVarArrayByName_variableExists_returnsDataForVariableIndex() {
		// Arrange
		Matrix matrix = createMatrix();
		int existingColumns = matrix.getCols();
		DataSeries sut = new DataSeries(matrix);

		for (int idx = 0; idx < existingColumns; idx++) {
			// Act
			double[] varArray = sut.getVarArrayByName(DEFAULT_VAR_NAME + (idx + 1));

			// Assert
			for (int r = 0; r < matrix.getRows(); r++) {
				assertEquals(matrix.get(r, idx), varArray[r], DELTA);
			}
		}
	}

	@Test
	public void test_getVarArrayByName_variableDoesNotExist_returnsNullReference() {
		// Arrange
		Matrix matrix = createMatrix();
		DataSeries sut = new DataSeries(matrix);

		// Act & Assert
		assertNull(sut.getVarArrayByName(ANY_STRING));
	}

	@Test
	public void test_getVarArrayByName_dataIsEmpty_returnsNullReference() {
		// Arrange
		DataSeries sut = new DataSeries();
		sut.emptyDataSeries();

		// Act & Assert
		assertNull(sut.getVarArrayByName(ANY_STRING));
	}

	@Test
	public void test_getVarArrayByTag_variableExists_returnsDataForVariableIndex() {
		// Arrange
		Matrix matrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(matrix);
		DataSeries sut = new DataSeries(matrix);

		for (int idx = 0; idx < existingMatrix.getCols(); idx++) {
			// Act
			double[] varArray = sut.getVarArrayByTag(DEFAULT_TAG_NAME + (idx + 1));

			// Assert
			for (int r = 0; r < existingMatrix.getRows(); r++) {
				assertEquals(existingMatrix.get(r, idx), varArray[r], DELTA);
			}
		}
	}

	@Test
	public void test_getVarArrayByTag_variableDoesNotExist_returnsNullReference() {
		// Arrange
		Matrix matrix = createMatrix();
		DataSeries sut = new DataSeries(matrix);

		// Act & Assert
		assertNull(sut.getVarArrayByTag(ANY_STRING));
	}

	@Test
	public void test_getVarArrayByTag_dataIsEmpty_returnsNullReference() {
		// Arrange
		DataSeries sut = new DataSeries();
		sut.emptyDataSeries();

		// Act & Assert
		assertNull(sut.getVarArrayByTag(ANY_STRING));
	}

	@Test
	public void test_getVarArray_variableExists_returnsDataForVariableIndex() {
		// Arrange
		Matrix matrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(matrix);
		DataSeries sut = new DataSeries(matrix);

		for (int idx = 0; idx < existingMatrix.getCols(); idx++) {
			// Act
			double[] varArray = sut.getVarArray(sut.getVarByIndex(idx));

			// Assert
			for (int r = 0; r < existingMatrix.getRows(); r++) {
				assertEquals(existingMatrix.get(r, idx), varArray[r], DELTA);
			}
		}
	}

	@Test
	public void test_getVarArray_variableDoesNotExist_returnsNullReference() {
		// Arrange
		Matrix matrix = createMatrix();
		DataSeries sut = new DataSeries(matrix);

		// Act & Assert
		assertNull(sut.getVarArray(new Variable()));
	}

	@Test
	public void test_getVarArray_dataIsEmpty_returnsNullReference() {
		// Arrange
		DataSeries sut = new DataSeries();
		sut.emptyDataSeries();

		// Act & Assert
		assertNull(sut.getVarArray(new Variable()));
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setVariableParameters_indexIsLessThanZero_throwsMathException() throws MathException {
		// Arrange
		Matrix matrix = createMatrix();
		DataSeries sut = new DataSeries(matrix);

		// Act
		sut.setVariableParameters(-1, ANY_STRING, ANY_STRING, ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setVariableParameters_indexIsGreaterThanVariableObjects_throwsMathException()
			throws MathException {
		// Arrange
		Matrix matrix = createMatrix();
		DataSeries sut = new DataSeries(matrix);

		// Act
		sut.setVariableParameters(sut.getVarObjects().size() + 1, ANY_STRING, ANY_STRING, ANY_STRING);
	}

	@Test
	public void test_setVariableParameters_indexIsWithinVariablesVectorBounds_setsNameTagAndUnit()
			throws MathException {
		// Arrange
		Matrix matrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(matrix);
		DataSeries sut = new DataSeries(matrix);

		for (int idx = 0; idx < existingMatrix.getCols(); idx++) {
			String name = "variableNewName" + idx;
			String tag = "variableNewTag" + idx;
			String unit = "variableNewUnit" + idx;

			// Act
			sut.setVariableParameters(idx, tag, name, unit);

			// Assert
			Variable variable = sut.getVarByIndex(idx);
			assertEquals(name, variable.getName());
			assertEquals(tag, variable.getTag());
			assertEquals(unit, variable.getUnit());
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setColumnValues_indexIsLessThanZero_throwsMathException() throws MathException {
		// Arrange
		DataSeries sut = new DataSeries();

		// Act
		sut.setColumnValues(-1, new double[0]);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setColumnValues_indexIsGreaterThanVariableObjects_throwsMathException() throws MathException {
		// Arrange
		DataSeries sut = new DataSeries();

		// Act
		sut.setColumnValues(sut.getVarObjects().size() + 1, new double[0]);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setColumnValues_dataLengthDoesNotMatchRowDimension_throwsMathException() throws MathException {
		// Arrange
		Matrix matrix = createMatrix();
		DataSeries sut = new DataSeries(matrix);

		// Act
		sut.setColumnValues(0, new double[sut.getVarObjects().size() + 1]);
	}

	@Test
	public void test_setColumnValues_dataLengthMatchesRowDimension_setsData() throws MathException {
		// Arrange
		Matrix matrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(matrix);
		DataSeries sut = new DataSeries(matrix);

		for (int idx = 0; idx < existingMatrix.getCols(); idx++) {
			double[] data = new double[matrix.getRows()];
			for (int r = 0; r < existingMatrix.getRows(); r++) {
				data[r] = randomGenerator.nextDouble();
			}

			// Act
			sut.setColumnValues(idx, data);

			// Assert
			for (int r = 0; r < existingMatrix.getRows(); r++) {
				assertEquals(data[r], sut.getValueAt(r, idx), DELTA);
			}
		}
	}

	@Test
	public void test_setValueAt_always_setsData() throws MathException {
		// Arrange
		Matrix matrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(matrix);
		DataSeries sut = new DataSeries(matrix);

		for (int r = 0; r < existingMatrix.getRows(); r++) {
			for (int c = 0; c < existingMatrix.getRows(); c++) {
				double data = randomGenerator.nextDouble();

				// Act
				sut.setValueAt(r, c, data);

				// Assert
				assertEquals(data, sut.getValueAt(r, c), DELTA);
			}
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getVarMatrix_variableDoesNotExist_throwsMathException() throws MathException {
		// Arrange
		DataSeries sut = new DataSeries();

		// Act
		sut.getVarMatrix(new Variable(), Matlib.createMatrix());
	}

	@Test
	public void test_getVarMatrix_variableExists_setsMatrix() throws MathException {
		// Arrange
		Matrix sutMatrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(sutMatrix);
		DataSeries sut = new DataSeries(sutMatrix);
		Matrix matrix = Matlib.createMatrix();

		for (int idx = 0; idx < existingMatrix.getCols(); idx++) {
			// Act
			sut.getVarMatrix(sut.getVarByIndex(idx), matrix);

			// Assert
			for (int r = 0; r < existingMatrix.getRows(); r++) {
				assertEquals(existingMatrix.get(r, idx), matrix.get(r, 0), DELTA);
			}
		}
	}

	@Test
	public void test_addColumns_zeroColumnsAreToBeAdded_doesNotAddAnyColumns() throws MathException {
		// Arrange
		Matrix sutMatrix = createMatrix();
		int currentCols = sutMatrix.getCols();
		DataSeries sut = new DataSeries(sutMatrix);

		// Act
		sut.addColumns(0);

		// Assert
		assertEquals(currentCols, sut.getDataMatrix().getCols());
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_addColumns_negativeArgumentIsPassedForNewColumns_throwsMathException() throws MathException {
		// Arrange
		Matrix sutMatrix = createMatrix();
		DataSeries sut = new DataSeries(sutMatrix);

		// Act
		sut.addColumns(-1);
	}

	@Test
	public void test_addColumns_positiveArgumentIsPassedForNewColumns_addsEmptyDataColumnsToDataSeries()
			throws MathException {
		// Arrange
		Matrix sutMatrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(sutMatrix);
		DataSeries sut = new DataSeries(sutMatrix);
		int n = 3;

		// Act
		sut.addColumns(n);

		// Assert
		assertEquals(existingMatrix.getCols() + n, sut.getDataMatrix().getCols());
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = existingMatrix.getCols(); c < existingMatrix.getCols() + n; c++) {
				assertEquals(0.0, sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_addColumns_timeStampsAreDifferentThanDataRows_throwsException() throws MathException {
		// Arrange
		Matrix sutMatrix = createMatrix();
		DataSeries sut = new DataSeries(sutMatrix);
		sut.setTimeStamps(new long[sutMatrix.getRows() + ANY_INT]);

		// Act
		sut.addColumns(ANY_INT);
	}

	@Test
	public void test_addColumns_initiallyDataMatrixIsEmpty_doesNothing() throws MathException {
		// Arrange
		Matrix sutMatrix = Matlib.createMatrix();
		DataSeries sut = new DataSeries(sutMatrix);

		// Act
		sut.addColumns(ANY_INT);

		// Assert
		assertEquals(0, sut.getDataMatrix().getCols());
	}

	@Test
	public void test_load_fileDoesNotExist_doesNotClearVariables() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 2;
		DataSeries sut = new DataSeries(rows, cols);
		String fileName = "Data Series.ds";

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		assertThatVariablesAreCreatedWithDefaultNames(sut, cols);
	}

	@Test
	public void test_load_containsNoHeaderRows_doesNotClearVariables() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 2;
		DataSeries sut = new DataSeries(rows, cols);
		String fileName = createDsFileName(new Vector<Vector<String>>());

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		assertThatVariablesAreCreatedWithDefaultNames(sut, cols);
	}

	@Test
	public void test_load_containsValues_createsNewVariables() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 2;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, false);
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		assertThatVariablesAreCreatedWithNewNamesTagsAndUnits(sut, fileLines);
	}

	@Test
	public void test_load_variablesWithSameNamesAreFound_createsNewVariablesWithUniqueNames() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, false);
		int variableIndex = 0;
		int variableMatchingIndex = 2;
		fileLines.get(NAME_ROW_INDEX).set(variableMatchingIndex, fileLines.get(NAME_ROW_INDEX).get(variableIndex));
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		assertEquals(fileLines.get(NAME_ROW_INDEX).get(variableIndex) + "_1",
				sut.getVarByIndex(variableIndex).getName());
		assertEquals(fileLines.get(NAME_ROW_INDEX).get(variableIndex) + "_2",
				sut.getVarByIndex(variableMatchingIndex).getName());
	}

	@Test
	public void test_load_fileContainsLessVariablesNames_addsEmptyVariableNames() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols - 1, false);
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		assertEquals("", sut.getVarByIndex(cols - 1).getName());
	}

	@Test
	public void test_load_fileContainsLessTags_addsEmptyTags() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols - 1, false);
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		assertEquals("", sut.getVarByIndex(cols - 1).getTag());
	}

	@Test
	public void test_load_fileContainsLessUnits_addsEmptyUnits() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols - 1, false);
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		assertEquals("", sut.getVarByIndex(cols - 1).getUnit());
	}

	@Test
	public void test_load_fileContainsTimeStamps_addsTimestamps() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, true);
		addDataAndTimeStamps(fileLines, rows, cols, null);
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		assertTrue(sut.getHasTimeStamps());
		long[] timeStamps = sut.getTimeStamps();
		for (int idx = TIMESTAMPS_FIRST_INDEX_ROW; idx < fileLines.size(); idx++) {
			assertEquals(Long.valueOf(fileLines.get(idx).get(0)).longValue(),
					timeStamps[idx - TIMESTAMPS_FIRST_INDEX_ROW]);
		}
	}

	@Test
	public void test_load_fileContainsData_addsDataToMatrix() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(sut.getDataMatrix().getCols(), false);
		addData(fileLines, sut.getDataMatrix().getRows(), sut.getDataMatrix().getCols());
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		Matrix matrix = sut.getDataMatrix();
		for (int lineIdx = 0; lineIdx < fileLines.size() - DATA_FIRST_ROW_INDEX; lineIdx++) {
			Vector<String> line = fileLines.get(DATA_FIRST_ROW_INDEX + lineIdx);
			for (int c = 0; c < line.size(); c++) {
				assertEquals(Double.valueOf(line.get(c)).doubleValue(), matrix.get(lineIdx, c), DELTA);
			}
		}
	}

	@Test
	public void test_load_fileContainsDataWithTimestamps_addsDataToMatrix() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(true);
		int rows = sut.getDataMatrix().getRows();
		int cols = sut.getDataMatrix().getCols();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, true);
		addDataAndTimeStamps(fileLines, rows, cols, null);
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		Matrix matrix = sut.getDataMatrix();
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				assertEquals(Double.valueOf(fileLines.get(DATA_FIRST_ROW_INDEX + r).get(DATA_FIRST_COLUMN_INDEX + c))
						.doubleValue(), matrix.get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_load_dataRowsAreLessThanTwenty_informsListenersForEachNewDataRowAdded() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);

		// Adding progress listeners
		Vector<ProgressListener> listeners = new Vector<ProgressListener>();
		for (int listenerIdx = 0; listenerIdx < 3; listenerIdx++) {
			ProgressListener listener = createProgressListener();
			listeners.add(listener);
			sut.addListener(listener);
		}

		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, true);
		addDataAndTimeStamps(fileLines, rows, cols, null);
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		for (ProgressListener listener : listeners) {
			verify(listener, times(rows)).valueChanged(Matchers.any(ProgressEvent.class));
		}
	}

	@Test
	public void test_load_dataRowsAreMoreThanTwenty_informsListenersForFirstTwentyDataRowsAdded() throws IOException {
		// Arrange
		int rows = 40;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);

		// Adding progress listeners
		Vector<ProgressListener> listeners = new Vector<ProgressListener>();
		for (int listenerIdx = 0; listenerIdx < 3; listenerIdx++) {
			ProgressListener listener = createProgressListener();
			listeners.add(listener);
			sut.addListener(listener);
		}

		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, true);
		addDataAndTimeStamps(fileLines, rows, cols, null);
		String fileName = createDsFileName(fileLines);

		// Act
		sut.Load(fileName, DS_FORMAT);

		// Assert
		for (ProgressListener listener : listeners) {
			verify(listener, times(LISTENERS_VALUE_CHANGED_INVOCATION_MAX_COUNT))
					.valueChanged(Matchers.any(ProgressEvent.class));
		}
	}

	@Test
	public void test_load_fileIsBDSFileFormat_setsDataMatrix() throws IOException {
		// Arrange
		DataSeries sut = new DataSeries();
		Matrix matrix = createMatrix();
		DataSeries dataSeries = new DataSeries(matrix);
		String fileName = createDsFileName(dataSeries);

		// Act
		sut.Load(fileName, BDS_FILE_FORMAT);

		// Assert
		for (int r = 0; r < matrix.getRows(); r++) {
			for (int c = 0; c < matrix.getCols(); c++) {
				assertEquals(matrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_load_fileIsBDSFileFormat_setsTimeStamps() throws IOException {
		// Arrange
		DataSeries sut = new DataSeries();
		Matrix matrix = createMatrix();
		DataSeries dataSeries = new DataSeries(matrix);
		String fileName = createDsFileName(dataSeries);

		// Act
		sut.Load(fileName, BDS_FILE_FORMAT);

		// Assert
		for (int idx = 0; idx < dataSeries.getTimeStamps().length; idx++) {
			assertEquals(dataSeries.getTimeStamps()[idx], sut.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_load_fileIsBDSFileFormat_setsVarObjects() throws IOException {
		// Arrange
		DataSeries sut = new DataSeries();
		Matrix matrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(matrix);
		DataSeries dataSeries = new DataSeries(matrix);
		String fileName = createDsFileName(dataSeries);

		// Act
		sut.Load(fileName, BDS_FILE_FORMAT);

		// Assert
		for (int idx = 0; idx < existingMatrix.getCols(); idx++) {
			assertEquals(dataSeries.getVarByIndex(idx).getName(), sut.getVarByIndex(idx).getName());
			assertEquals(dataSeries.getVarByIndex(idx).getTag(), sut.getVarByIndex(idx).getTag());
			assertEquals(dataSeries.getVarByIndex(idx).getUnit(), sut.getVarByIndex(idx).getUnit());
		}
	}

	@Test
	public void test_load_fileIsBDSFileFormat_setsComment() throws IOException {
		// Arrange
		DataSeries sut = new DataSeries();
		Matrix matrix = createMatrix();
		DataSeries dataSeries = new DataSeries(matrix);
		String fileName = createDsFileName(dataSeries);

		// Act
		sut.Load(fileName, BDS_FILE_FORMAT);

		// Assert
		assertEquals(dataSeries.getComment(), sut.getComment());
	}

	@Test
	public void test_load_isLoadedWithMatrix_setsDataSeriesDataMatrix() throws IOException {
		// Arrange
		DataSeries sut = new DataSeries();
		Matrix matrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(matrix);
		String fileName = createMatrixFile(matrix);

		// Act
		sut.Load(fileName, MATRIX_FILE_FORMAT);

		// Assert
		for (int r = 0; r < existingMatrix.getRows(); r++) {
			for (int c = 0; c < existingMatrix.getCols(); c++) {
				assertEquals(matrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_loadFromUrl_containsValues_createsNewVariables() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 2;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, false);
		URL url = createUrl(fileLines, "DataSeries");

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		assertThatVariablesAreCreatedWithNewNamesTagsAndUnits(sut, fileLines);
	}

	@Test
	public void test_loadFromUrl_variablesWithSameTagsAreFound_createsNewVariablesWithUniqueTags() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, false);
		int variableIndex = 0;
		int variableMatchingIndex = 2;
		fileLines.get(TAG_ROW_INDEX).set(variableMatchingIndex, fileLines.get(TAG_ROW_INDEX).get(variableIndex));
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		assertEquals(fileLines.get(TAG_ROW_INDEX).get(variableIndex) + "_1",
				sut.getVarByIndex(variableIndex).getName());
		assertEquals(fileLines.get(TAG_ROW_INDEX).get(variableIndex) + "_2",
				sut.getVarByIndex(variableMatchingIndex).getName());
	}

	@Test
	public void test_loadFromUrl_fileContainsLessVariablesNames_addsEmptyVariableNames() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols - 1, false);
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		assertEquals("", sut.getVarByIndex(cols - 1).getName());
	}

	@Test
	public void test_loadFromUrl_fileContainsLessTags_addsEmptyTags() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols - 1, false);
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		assertEquals("", sut.getVarByIndex(cols - 1).getTag());
	}

	@Test
	public void test_loadFromUrl_fileContainsLessUnits_addsEmptyUnits() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols - 1, false);
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		assertEquals("", sut.getVarByIndex(cols - 1).getUnit());
	}

	@Test
	public void test_loadFromUrl_dataContainsNaN_setsDataAsNaN() throws IOException {
		// Arrange
		DataSeries sut = new DataSeries(createMatrix());

		Vector<Vector<String>> fileLines = createVariableSpecsLines(sut.getDataMatrix().getCols(), false);
		Matrix matrix = createMatrix(false);
		addData(fileLines, matrix);
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		Matrix sutMatrix = sut.getDataMatrix();
		for (int r = 0; r < matrix.getRows(); r++) {
			for (int c = 0; c < matrix.getCols(); c++) {
				assertEquals(Double.NaN, sutMatrix.get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_loadFromUrl_fileContainsTimeStamps_addsTimestamps() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, true);
		addDataAndTimeStamps(fileLines, rows, cols, null);
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		assertTrue(sut.getHasTimeStamps());
		for (int idx = TIMESTAMPS_FIRST_INDEX_ROW; idx < fileLines.size(); idx++) {
			assertEquals(Long.valueOf(fileLines.get(idx).get(0)).longValue(),
					sut.getTimeStamps()[idx - TIMESTAMPS_FIRST_INDEX_ROW]);
		}
	}

	@Test
	public void test_loadFromUrl_fileContainsData_addsDataToMatrix() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols - 1, false);
		addData(fileLines, rows, cols);
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				assertEquals(Double.valueOf(fileLines.get(DATA_FIRST_ROW_INDEX + r).get(c)).doubleValue(),
						sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_loadFromUrl_fileContainsDataWithTimestamps_addsDataToMatrix() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		int dataCols = cols - 1;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, true);
		addDataAndTimeStamps(fileLines, rows, cols, null);
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < dataCols; c++) {
				assertEquals(Double.valueOf(fileLines.get(DATA_FIRST_ROW_INDEX + r).get(c + DATA_FIRST_COLUMN_INDEX))
						.doubleValue(), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_loadFromUrl_dataRowsAreLessThanTwenty_informsListenersForEachNewDataRowAdded() throws IOException {
		// Arrange
		int rows = 3;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);

		// Adding progress listeners
		Vector<ProgressListener> listeners = new Vector<ProgressListener>();
		for (int listenerIdx = 0; listenerIdx < 3; listenerIdx++) {
			ProgressListener listener = createProgressListener();
			listeners.add(listener);
			sut.addListener(listener);
		}

		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, true);
		addDataAndTimeStamps(fileLines, rows, cols, null);
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		for (ProgressListener listener : listeners) {
			verify(listener, times(rows)).valueChanged(Matchers.any(ProgressEvent.class));
		}
	}

	@Test
	public void test_loadFromUrl_dataRowsAreMoreThanTwenty_informsListenersForFirstTwentyDataRowsAdded()
			throws IOException {
		// Arrange
		int rows = 40;
		int cols = 4;
		DataSeries sut = new DataSeries(rows, cols);
		Vector<ProgressListener> listeners = addProgressListeners(sut);

		Vector<Vector<String>> fileLines = createVariableSpecsLines(cols, true);
		addDataAndTimeStamps(fileLines, rows, cols, null);
		URL url = createUrl(fileLines);

		// Act
		sut.Load(url, DS_FORMAT);

		// Assert
		for (ProgressListener listener : listeners) {
			verify(listener, times(LISTENERS_VALUE_CHANGED_INVOCATION_MAX_COUNT))
					.valueChanged(Matchers.any(ProgressEvent.class));
		}
	}

	@Test
	public void test_loadFromUrl_isLoadedWithMatrix_setsDataSeriesDataMatrix() throws IOException {
		// Arrange
		DataSeries sut = new DataSeries();
		Matrix matrix = createMatrix();
		URL url = createUrl(matrix);

		// Act
		sut.Load(url, MATRIX_FILE_FORMAT);

		// Assert
		assertEquals(matrix.getRows(), sut.getDataMatrix().getRows());
		for (int r = 0; r < matrix.getRows(); r++) {
			for (int c = 0; c < matrix.getCols(); c++) {
				assertEquals(matrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_appendRows_sutHasTimeStampsButSourceDoesNotHaveTimeStamps_returnsFalse()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut(true);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(sut.getColumn(), false);
		String fileName = createDsFileName(fileLines);

		// Act & Assert
		assertFalse(sut.appendRows(fileName, DS_FORMAT));
	}

	@Test
	public void test_appendRows_sutDoesNotHaveAnyDataSource_returnsFalse() throws MathException {
		// Arrange
		DataSeries sut = createSut(false);
		sut.setDataSource(null);

		DataSeries sourceData = new DataSeries(createMatrix());

		// Act & Assert
		assertFalse(sut.appendRows(sourceData));
	}

	@Test
	public void test_appendRows_dataSourceIsNotInstanceOfRawDataSource_returnsFalse() {
		// Arrange
		DataSeries sut = new DataSeries(createMatrix());
		sut.setDataSource(mock(DataSource.class));

		DataSeries sourceData = new DataSeries(createMatrix());

		// Act & Assert
		assertFalse(sut.appendRows(sourceData));
	}

	@Test
	public void test_appendRows_sourceDataSeriesDoesNotContainAnyNewVariables_keepsExistingVariables()
			throws MathException {
		// Arrange
		DataSeries sut = createSut(false);
		int existingColsCount = sut.getDataMatrix().getCols();

		DataSeries sourceData = new DataSeries(createMatrix());

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		assertThatVariablesAreCreatedWithDefaultNames(sut, existingColsCount);
	}

	@Test
	public void test_appendRows_sourceDataSeriesDoesNotContainAnyNewVariables_keepsExistingDataMatrix()
			throws MathException {
		// Arrange
		DataSeries sut = createSut(false);
		Matrix existingMatrix = cloneMatrix(sut.getDataMatrix());

		DataSeries sourceData = new DataSeries(createMatrix());

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		for (int r = 0; r < existingMatrix.getRows(); r++) {
			for (int c = 0; c < existingMatrix.getCols(); c++) {
				assertEquals(existingMatrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_appendRows_sourceDataSeriesContainsNewVariables_keepsExistingVariables() throws MathException {
		// Arrange
		DataSeries sut = createSut(false);
		int existingColsCount = sut.getDataMatrix().getCols();

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setVariableParameters(1, "tag4", "name4", "unit4");

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		assertThatVariablesAreCreatedWithDefaultNames(sut, existingColsCount);
	}

	@Test
	public void test_appendRows_sourceDataSeriesContainsNewVariables_keepsExistingDataMatrix() throws MathException {
		// Arrange
		DataSeries sut = createSut(false);
		Matrix existingMatrix = cloneMatrix(sut.getDataMatrix());

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setVariableParameters(1, "tag4", "name4", "unit4");

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		for (int r = 0; r < existingMatrix.getRows(); r++) {
			for (int c = 0; c < existingMatrix.getCols(); c++) {
				assertEquals(existingMatrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_appendRows_sourceDataSeriesContainsNewVariables_addsNewVariables() throws MathException {
		// Arrange
		DataSeries sut = createSut(false);
		int existingRowsCount = sut.getDataMatrix().getRows();
		int existingColsCount = sut.getDataMatrix().getCols();

		DataSeries sourceData = new DataSeries(createMatrix());
		// Adding new variables
		int newVarsCount = 2;
		for (int idx = 0; idx < newVarsCount; idx++) {
			sourceData.setVariableParameters(idx, "tag" + (existingRowsCount + idx), "name" + (existingRowsCount + idx),
					"unit" + (existingRowsCount + idx));
		}

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		for (int idx = 0; idx < newVarsCount; idx++) {
			Variable variable = sut.getVarByIndex(existingColsCount + idx);
			assertEquals(sourceData.getVarByIndex(idx).getName(), variable.getName());
			assertEquals(sourceData.getVarByIndex(idx).getTag(), variable.getTag());
			assertEquals(sourceData.getVarByIndex(idx).getUnit(), variable.getUnit());
		}
	}

	@Test
	public void test_appendRows_sourceDataSeriesContainsNewVariables_addsNewDataAsNaN() throws MathException {
		// Arrange
		DataSeries sut = createSut(false);
		int existingRowsCount = sut.getDataMatrix().getRows();

		DataSeries sourceData = new DataSeries(createMatrix());
		// Adding new variables
		int newVarsCount = 2;
		for (int idx = 0; idx < newVarsCount; idx++) {
			sourceData.setVariableParameters(idx, "tag" + (existingRowsCount + idx), "name" + (existingRowsCount + idx),
					"unit" + (existingRowsCount + idx));
		}

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		// NaN is added at the end of existing data
		assertTrue(result);
		for (int r = existingRowsCount; r < existingRowsCount + newVarsCount; r++) {
			for (int c = 0; c < newVarsCount; c++) {
				assertEquals(Double.NaN, sut.getDataMatrix().get(r, c), DELTA);
			}
		}

		// NaN is added at the beginning of new data
		for (int r = 0; r < newVarsCount; r++) {
			for (int c = 0; c < newVarsCount; c++) {
				assertEquals(Double.NaN, sut.getDataMatrix().get(existingRowsCount + r, c), DELTA);
			}
		}
	}

	@Test
	public void test_appendRows_doesNotContainTimeStamps_invokesModifyLabelMaskForDataSeries() throws MathException {
		// Arrange
		DataSeries sut = createSut(false);

		DataSeries sourceData = new DataSeries(createMatrix());

		// Act
		sut.appendRows(sourceData);

		// Assert
		verify((RawDataSource) sut.getDataSource()).modifyLabelMaskForDataSeries(sut);
	}

	@Test
	public void test_appendRows_sourceDataFirstTimeStampIsSameAsSutLastTimeStamp_returnsFalse() throws MathException {
		// Arrange
		DataSeries sut = createSut(true);

		DataSeries sourceData = new DataSeries(createMatrix());
		long[] sourceDataTimeStamps = createTimeStamps(sourceData.getDataMatrix().getRows());
		// Setting source data first time as SUT last time stamp
		sourceDataTimeStamps[0] = sut.getTimeStamps()[sut.getTimeStamps().length - 1];
		sourceData.setTimeStamps(sourceDataTimeStamps);

		// Act & Assert
		assertFalse(sut.appendRows(sourceData));
	}

	@Test
	public void test_appendRows_sourceTimeStampsAreLaterThanSutTimeStamps_updatesDataSeriesTimeStamps()
			throws MathException {
		// Arrange
		DataSeries sut = createSut(true);
		long[] existingTimeStamps = sut.getTimeStamps();

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setTimeStamps(createNextTimeStamps(sourceData.getDataMatrix().getRows(),
				sut.getTimeStamps()[sut.getDataMatrix().getRows() - 1]));

		// Act
		sut.appendRows(sourceData);

		// Assert
		long[] timeStamps = sut.getTimeStamps();
		for (int idx = 0; idx < existingTimeStamps.length; idx++) {
			assertEquals(existingTimeStamps[idx], timeStamps[idx]);
		}

		for (int idx = 0; idx < sourceData.getTimeStamps().length; idx++) {
			assertEquals(sourceData.getTimeStamps()[idx], timeStamps[existingTimeStamps.length + idx]);
		}
	}

	@Test
	public void test_appendRows_sutTimeStampsAreLaterThanSourceTimeStamps_updatesDataSeriesTimeStamps()
			throws MathException {
		// Arrange
		DataSeries sourceData = createSut(true);

		Matrix matrix = createMatrix();
		DataSeries sut = new DataSeries(matrix);
		RawDataSource dataSource = createRawDataSource();
		sut.setDataSource(dataSource);
		sut.setTimeStamps(createNextTimeStamps(sut.getDataMatrix().getRows(),
				sourceData.getTimeStamps()[sourceData.getTimeStamps().length - 1]));
		long[] existingTimeStamps = sut.getTimeStamps();

		// Act
		sut.appendRows(sourceData);

		// Assert
		long[] timeStamps = sut.getTimeStamps();
		for (int idx = 0; idx < sourceData.getTimeStamps().length; idx++) {
			assertEquals(sourceData.getTimeStamps()[idx], timeStamps[idx]);
		}

		for (int idx = 0; idx < existingTimeStamps.length; idx++) {
			assertEquals(existingTimeStamps[idx], timeStamps[existingTimeStamps.length + idx]);
		}
	}

	@Test
	public void test_appendRows_timeStampsExistAndSourceDataSeriesDoesNotContainAnyNewVariables_keepsExistingVariables()
			throws MathException {
		// Arrange
		DataSeries sut = createSut(true);
		int existingColsCount = sut.getDataMatrix().getCols();

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setTimeStamps(createNextTimeStamps(sourceData.getDataMatrix().getRows(),
				sut.getTimeStamps()[sut.getDataMatrix().getRows() - 1]));

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		assertThatVariablesAreCreatedWithDefaultNames(sut, existingColsCount);
	}

	@Test
	public void test_appendRows_timeStampsExistAndSourceDataSeriesDoesNotContainAnyNewVariables_keepsExistingDataMatrix()
			throws MathException {
		// Arrange
		Matrix matrix = createMatrix();
		Matrix existingMatrix = cloneMatrix(matrix);
		int existingRowsCount = matrix.getRows();
		int existingColsCount = matrix.getCols();
		DataSeries sut = new DataSeries(matrix);
		sut.setDataSource(createRawDataSource());
		sut.setTimeStamps(createTimeStamps(matrix.getRows()));

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setTimeStamps(
				createNextTimeStamps(sourceData.getDataMatrix().getRows(), sut.getTimeStamps()[matrix.getRows() - 1]));

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		for (int r = 0; r < existingRowsCount; r++) {
			for (int c = 0; c < existingColsCount; c++) {
				assertEquals(existingMatrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_appendRows_timeStampsExistAndSourceDataSeriesContainsNewVariables_keepsExistingVariables()
			throws MathException {
		// Arrange
		DataSeries sut = createSut(true);
		int existingColsCount = sut.getDataMatrix().getCols();

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setVariableParameters(1, "tag4", "name4", "unit4");
		sourceData.setTimeStamps(createNextTimeStamps(sourceData.getDataMatrix().getRows(),
				sut.getTimeStamps()[sut.getDataMatrix().getRows() - 1]));

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		assertThatVariablesAreCreatedWithDefaultNames(sut, existingColsCount);
	}

	@Test
	public void test_appendRows_timeStampsExistAndSourceDataSeriesContainsNewVariables_keepsExistingDataMatrix()
			throws MathException {
		// Arrange
		DataSeries sut = createSut(true);
		Matrix existingMatrix = cloneMatrix(sut.getDataMatrix());

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setTimeStamps(createNextTimeStamps(sourceData.getDataMatrix().getRows(),
				sut.getTimeStamps()[existingMatrix.getRows() - 1]));
		sourceData.setVariableParameters(1, "tag4", "name4", "unit4");

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		for (int r = 0; r < existingMatrix.getRows(); r++) {
			for (int c = 0; c < existingMatrix.getCols(); c++) {
				assertEquals(existingMatrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_appendRows_timeStampsExistAndSourceDataSeriesContainsNewVariables_addsNewVariables()
			throws MathException {
		// Arrange
		DataSeries sut = createSut(true);
		int existingRowsCount = sut.getDataMatrix().getRows();
		int existingColsCount = sut.getDataMatrix().getCols();

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setTimeStamps(createNextTimeStamps(sourceData.getDataMatrix().getRows(),
				sut.getTimeStamps()[sut.getDataMatrix().getRows() - 1]));
		// Adding new variables
		int newVarsCount = 2;
		for (int idx = 0; idx < newVarsCount; idx++) {
			sourceData.setVariableParameters(idx, "tag" + (existingRowsCount + idx), "name" + (existingRowsCount + idx),
					"unit" + (existingRowsCount + idx));
		}

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		assertTrue(result);
		for (int idx = 0; idx < newVarsCount; idx++) {
			Variable variable = sut.getVarByIndex(existingColsCount + idx);
			assertEquals(sourceData.getVarByIndex(idx).getName(), variable.getName());
			assertEquals(sourceData.getVarByIndex(idx).getTag(), variable.getTag());
			assertEquals(sourceData.getVarByIndex(idx).getUnit(), variable.getUnit());
		}
	}

	@Test
	public void test_appendRows_timeStampsExistAndSourceDataSeriesContainsNewVariables_addsNewDataAsNaN()
			throws MathException {
		// Arrange
		DataSeries sut = createSut(true);
		int existingRowsCount = sut.getDataMatrix().getRows();

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setTimeStamps(createNextTimeStamps(sourceData.getDataMatrix().getRows(),
				sut.getTimeStamps()[sut.getDataMatrix().getRows() - 1]));
		// Adding new variables
		int newVarsCount = 2;
		for (int idx = 0; idx < newVarsCount; idx++) {
			sourceData.setVariableParameters(idx, "tag" + (existingRowsCount + idx), "name" + (existingRowsCount + idx),
					"unit" + (existingRowsCount + idx));
		}

		// Act
		boolean result = sut.appendRows(sourceData);

		// Assert
		// NaN is added at the end of existing data
		assertTrue(result);
		for (int r = existingRowsCount; r < existingRowsCount + newVarsCount; r++) {
			for (int c = 0; c < newVarsCount; c++) {
				assertEquals(Double.NaN, sut.getDataMatrix().get(r, c), DELTA);
			}
		}

		// NaN is added at the beginning of new data
		for (int r = 0; r < newVarsCount; r++) {
			for (int c = 0; c < newVarsCount; c++) {
				assertEquals(Double.NaN, sut.getDataMatrix().get(existingRowsCount + r, c), DELTA);
			}
		}
	}

	@Test
	public void test_appendRows_timeStampsExist_invokesModifyLabelMaskForDataSeries() throws MathException {
		// Arrange
		DataSeries sut = createSut(true);
		long[] existingTimeStamps = sut.getTimeStamps();

		DataSeries sourceData = new DataSeries(createMatrix());
		sourceData.setTimeStamps(createNextTimeStamps(sourceData.getDataMatrix().getRows(),
				sut.getTimeStamps()[sut.getDataMatrix().getRows() - 1]));

		// Act
		sut.appendRows(sourceData);

		// Assert
		verify((RawDataSource) sut.getDataSource()).modifyLabelMaskForDataSeries(sut, existingTimeStamps,
				sut.getTimeStamps());
	}

	@Test
	public void test_saveAscii_hasTimeStampsAndSavedAsTypeOne_containsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(true);
		setVariables(sut);

		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_DS, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		assertTrue(sut.getHasTimeStamps());
		assertEquals(test.getTimeStamps().length, sut.getTimeStamps().length);
		for (int idx = 0; idx < sut.getTimeStamps().length; idx++) {
			assertEquals(test.getTimeStamps()[idx], sut.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_saveAscii_doesNotHaveTimeStampsAndSavedAsTypeOne_doesNotContainsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(false);
		setVariables(sut);

		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_DS, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		assertFalse(sut.getHasTimeStamps());
	}

	@Test
	public void test_saveAscii_savedAsTypeOne_containsVariableTagsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_DS, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getTag(), sut.getVarByIndex(idx).getTag());
		}
	}

	@Test
	public void test_saveAscii_savedAsTypeOne_containsVariableNamesInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_DS, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getName(), sut.getVarByIndex(idx).getName());
		}
	}

	@Test
	public void test_saveAscii_savedAsTypeOne_containsVariableUnitsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_DS, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getUnit(), sut.getVarByIndex(idx).getUnit());
		}
	}

	@Test
	public void test_saveAscii_savedAsTypeOne_containsMatrixData() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_DS, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(test.getDataMatrix().get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_saveAscii_hasTimeStampsAndSavedAsTypeTwo_containsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(true);
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_CSV, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsTimeStampsInfo(sut, file, dateFormat, timeFormat, COMMA_SEPARATOR);
	}

	@Test
	public void test_saveAscii_doesNotHaveTimeStampsAndSavedAsTypeTwo_doesNotContainsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(false);
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_CSV, dateFormat,
				timeFormat);

		// Assert
		assertThatFileDoesNotContainTimeStampsInfo(sut, file);
	}

	@Test
	public void test_saveAscii_savedAsTypeTwo_containsVariableTagsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_CSV, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsVariableTagsInfo(sut, file, COMMA_SEPARATOR);
	}

	@Test
	public void test_saveAscii_savedAsTypeTwo_containsVariableNamesInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_CSV, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsVariableNamesInfo(sut, file, COMMA_SEPARATOR);
	}

	@Test
	public void test_saveAscii_savedAsTypeTwo_containsVariableUnitsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_CSV, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsVariableUnitsInfo(sut, file, COMMA_SEPARATOR);
	}

	@Test
	public void test_saveAscii_savedAsTypeTwo_containsMatrixData() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_CSV, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsDataMatrixInfo(sut, file, COMMA_SEPARATOR);
	}

	@Test
	public void test_saveAscii_hasTimeStampsAndSavedAsTypeThree_containsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(true);
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_TXT, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsTimeStampsInfo(sut, file, dateFormat, timeFormat, TAB_SEPARATOR);
	}

	@Test
	public void test_saveAscii_doesNotHaveTimeStampsAndSavedAsTypeThree_doesNotContainsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(false);
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_TXT, dateFormat,
				timeFormat);

		// Assert
		assertThatFileDoesNotContainTimeStampsInfo(sut, file);
	}

	@Test
	public void test_saveAscii_savedAsTypeThree_containsVariableTagsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_TXT, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsVariableTagsInfo(sut, file, TAB_SEPARATOR);
	}

	@Test
	public void test_saveAscii_savedAsTypeThree_containsVariableNamesInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_TXT, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsVariableNamesInfo(sut, file, TAB_SEPARATOR);
	}

	@Test
	public void test_saveAscii_savedAsTypeThree_containsVariableUnitsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_TXT, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsVariableUnitsInfo(sut, file, TAB_SEPARATOR);
	}

	@Test
	public void test_saveAscii_savedAsTypeThree_containsMatrixData() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_TXT, dateFormat,
				timeFormat);

		// Assert
		assertThatFileContainsDataMatrixInfo(sut, file, TAB_SEPARATOR);
	}

	@Test
	public void test_saveAscii_hasTimeStampsAndSavedAsDefaultType_containsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(true);
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), TYPE_DEFAULT, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		assertTrue(sut.getHasTimeStamps());
		assertEquals(test.getTimeStamps().length, sut.getTimeStamps().length);
		for (int idx = 0; idx < sut.getTimeStamps().length; idx++) {
			assertEquals(test.getTimeStamps()[idx], sut.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_saveAscii_doesNotHaveTimeStampsAndSavedAsDefaultType_doesNotContainsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(false);
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), TYPE_DEFAULT, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		assertFalse(sut.getHasTimeStamps());
	}

	@Test
	public void test_saveAscii_savedAsDefaultType_containsVariableTagsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), TYPE_DEFAULT, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getTag(), sut.getVarByIndex(idx).getTag());
		}
	}

	@Test
	public void test_saveAscii_savedAsDefaultType_containsVariableNamesInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), TYPE_DEFAULT, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getName(), sut.getVarByIndex(idx).getName());
		}
	}

	@Test
	public void test_saveAscii_savedAsDefaultType_containsVariableUnitsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), TYPE_DEFAULT, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getUnit(), sut.getVarByIndex(idx).getUnit());
		}
	}

	@Test
	public void test_saveAscii_savedAsDefaultType_containsMatrixData() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);
		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), TYPE_DEFAULT, dateFormat,
				timeFormat);

		// Assert
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(test.getDataMatrix().get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_toStringForSave_hasTimeStampsAndSavedAsTypeOne_containsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(true);
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_DS, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		assertTrue(sut.getHasTimeStamps());
		assertEquals(test.getTimeStamps().length, sut.getTimeStamps().length);
		for (int idx = 0; idx < sut.getTimeStamps().length; idx++) {
			assertEquals(test.getTimeStamps()[idx], sut.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_toStringForSave_doesNotHaveTimeStampsAndSavedAsTypeOne_doesNotContainsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(false);
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_DS, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		assertFalse(sut.getHasTimeStamps());
	}

	@Test
	public void test_toStringForSave_savedAsTypeOne_containsVariableTagsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_DS, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getTag(), sut.getVarByIndex(idx).getTag());
		}
	}

	@Test
	public void test_toStringForSave_savedAsTypeOne_containsVariableNamesInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_DS, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getName(), sut.getVarByIndex(idx).getName());
		}
	}

	@Test
	public void test_toStringForSave_savedAsTypeOne_containsVariableUnitsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_DS, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getUnit(), sut.getVarByIndex(idx).getUnit());
		}
	}

	@Test
	public void test_toStringForSave_savedAsTypeOne_containsMatrixData() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_DS, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(test.getDataMatrix().get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_toStringForSave_hasTimeStampsAndSavedAsTypeTwo_containsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(true);
		setVariables(sut);
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_CSV, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsTimeStampsInfo(sut, lines, dateFormat, timeFormat, COMMA_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_doesNotHaveTimeStampsAndSavedAsTypeTwo_doesNotContainsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(false);
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_CSV, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileDoesNotContainTimeStampsInfo(sut, lines);
	}

	@Test
	public void test_toStringForSave_savedAsTypeTwo_containsVariableTagsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_CSV, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsVariableTagsInfo(sut, lines, COMMA_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_savedAsTypeTwo_containsVariableNamesInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_CSV, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsVariableNamesInfo(sut, lines, COMMA_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_savedAsTypeTwo_containsVariableUnitsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_CSV, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsVariableUnitsInfo(sut, lines, COMMA_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_savedAsTypeTwo_containsMatrixData() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_CSV, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsDataMatrixInfo(sut, lines, COMMA_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_hasTimeStampsAndSavedAsTypeThree_containsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(true);
		setVariables(sut);
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm");

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_TXT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsTimeStampsInfo(sut, lines, dateFormat, timeFormat, TAB_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_doesNotHaveTimeStampsAndSavedAsTypeThree_doesNotContainsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(false);
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_TXT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileDoesNotContainTimeStampsInfo(sut, lines);
	}

	@Test
	public void test_toStringForSave_savedAsTypeThree_containsVariableTagsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_TXT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsVariableTagsInfo(sut, lines, TAB_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_savedAsTypeThree_containsVariableNamesInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_TXT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsVariableNamesInfo(sut, lines, TAB_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_savedAsTypeThree_containsVariableUnitsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_TXT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsVariableUnitsInfo(sut, lines, TAB_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_savedAsTypeThree_containsMatrixData() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(ASCII_TYPE_TXT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		Vector<String> lines = new Vector<String>(Arrays.asList(result.split("\\n")));
		assertThatFileContainsDataMatrixInfo(sut, lines, TAB_SEPARATOR);
	}

	@Test
	public void test_toStringForSave_hasTimeStampsAndSavedAsDefaultType_containsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(true);
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(TYPE_DEFAULT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		assertTrue(sut.getHasTimeStamps());
		assertEquals(test.getTimeStamps().length, sut.getTimeStamps().length);
		for (int idx = 0; idx < sut.getTimeStamps().length; idx++) {
			assertEquals(test.getTimeStamps()[idx], sut.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_toStringForSave_doesNotHaveTimeStampsAndSavedAsDefaultType_doesNotContainsTimeStampsInfo()
			throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut(false);
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(TYPE_DEFAULT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		assertFalse(sut.getHasTimeStamps());
	}

	@Test
	public void test_toStringForSave_savedAsDefaultType_containsVariableTagsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(TYPE_DEFAULT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getTag(), sut.getVarByIndex(idx).getTag());
		}
	}

	@Test
	public void test_toStringForSave_savedAsDefaultType_containsVariableNamesInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(TYPE_DEFAULT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getName(), sut.getVarByIndex(idx).getName());
		}
	}

	@Test
	public void test_toStringForSave_savedAsDefaultType_containsVariableUnitsInfo() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(TYPE_DEFAULT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			assertEquals(test.getVarByIndex(idx).getUnit(), sut.getVarByIndex(idx).getUnit());
		}
	}

	@Test
	public void test_toStringForSave_savedAsDefaultType_containsMatrixData() throws IOException, MathException {
		// Arrange
		DataSeries sut = createSut();
		setVariables(sut);

		// Act
		String result = sut.toStringForSave(TYPE_DEFAULT, new SimpleDateFormat("dd/MM/yyyy"),
				new SimpleDateFormat("H:mm"));

		// Assert
		File file = createFile(result);
		DataSeries test = new DataSeries();
		test.Load(file.getAbsolutePath(), DS_FORMAT);
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(test.getDataMatrix().get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_appendRows_doesNotContainDataRows_returnsFalse()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		String dsName = "DataSeries Name";

		// Act & Assert
		assertFalse(sut.appendRows(file.getAbsolutePath(), format, dsName));
	}

	@Test
	public void test_appendRows_doesNotContainTimeStamps_returnsFalse()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		String dsName = "DataSeries Name";

		// Act & Assert
		assertFalse(sut.appendRows(file.getAbsolutePath(), format, dsName));
	}

	@Test(expected = MathException.class)
	public void test_LoadViaFormat_doesNotContainDataRows_throwsMathException()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		File file = createDsFile(fileLines);
		String directory = file.getAbsolutePath().replace(file.getName(), "");

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(directory, file.getName(), format, dsName);
	}

	@Test
	public void test_LoadViaFormat_always_setsName() throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert

		assertEquals(dsName, sut.getName());
	}

	@Test
	public void test_LoadViaFormat_doesNotContainTimeStamps_setsHasTimeStampsAsFalse()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		assertFalse(sut.getHasTimeStamps());
	}

	@Test
	public void test_LoadViaFormat_doesNotContainTimeStamps_setsVariables()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		String dateFormat = "dd/MM/yyyy";

		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addDataAndTimeStamps(fileLines, matrix.getRows(), matrix.getCols(), dateFormat);
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(fileLines.get(NAME_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getName());
			assertEquals(fileLines.get(TAG_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getTag());
			assertEquals(fileLines.get(UNIT_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getUnit());
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_LoadViaFormat_timeStampIsInvalid_throwsMathException()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addDataAndTimeStamps(fileLines, matrix, null);
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), true);
		format.setDateFormat(new SimpleDateFormat("dd/MM/yyyy"));

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);
	}

	@Test
	public void test_LoadViaFormat_containsDataRows_setsData()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		for (int r = 0; r < matrix.getRows(); r++) {
			for (int c = 0; c < matrix.getCols(); c++) {
				assertEquals(sut.getDataMatrix().get(r, c), matrix.get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_LoadViaFormat_containsDataRows_setsVariables()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(fileLines.get(NAME_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getName());
			assertEquals(fileLines.get(TAG_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getTag());
			assertEquals(fileLines.get(UNIT_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getUnit());
		}
	}

	@Test
	public void test_LoadViaFormat_containsTimeStamps_setsTimeStamps()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		String dateFormat = "dd/MM/yyyy";

		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addDataAndTimeStamps(fileLines, matrix.getRows(), matrix.getCols(), dateFormat);
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), true);
		format.setDateFormat(new SimpleDateFormat(dateFormat));

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		assertTrue(sut.getHasTimeStamps());
	}

	@Test
	public void test_LoadViaFormat_formatTagLineIsNotSet_setsVariableTagsAsNames()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		format.setTagLine(-1);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(fileLines.get(NAME_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getTag());
		}
	}

	@Test
	public void test_LoadViaFormat_formatNameLineIsNotSet_setsVariableNamesAsTags()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		format.setNameLine(-1);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(fileLines.get(TAG_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getName());
		}
	}

	@Test
	public void test_LoadViaFormat_formatNameLineAndTagLineIsNotSet_setsVariableNamesAndTagsAsAutoNames()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);
		int existingVarsCount = sut.getDataMatrix().getCols();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		format.setNameLine(-1);
		format.setTagLine(-1);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(DEFAULT_VAR_NAME + (existingVarsCount + idx + 1), sut.getVarByIndex(idx).getName());
			assertEquals(DEFAULT_VAR_NAME + (existingVarsCount + idx + 1), sut.getVarByIndex(idx).getTag());
		}
	}

	@Test
	public void test_LoadViaFormat_formatNameLineAndUnitLineIsNotSet_setsVariableUnitsAsNone()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		format.setUnitLine(-1);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals("None", sut.getVarByIndex(idx).getUnit());
		}
	}

	@Test
	public void test_LoadViaFormat_dataRowsAreLessThanTwenty_invokesProgressListenerValueChangedMethodForEachDataRow()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);
		Vector<ProgressListener> listeners = addProgressListeners(sut);

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		for (ProgressListener listener : listeners) {
			verify(listener, times(sut.getDataMatrix().getRows() + NON_DATA_ROWS_COUNT))
					.valueChanged(Matchers.any(ProgressEvent.class));
		}
	}

	@Test
	public void test_LoadViaFormat_dataRowsAreTwentyOrMore_invokesProgressListenerValueChangedMethodForFirstTwentyDataRowsOnly()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);
		Vector<ProgressListener> listeners = addProgressListeners(sut);

		Matrix matrix = createMatrix(40, 4);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		File file = createDsFile(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(null, file.getAbsolutePath(), format, dsName);

		// Assert
		for (ProgressListener listener : listeners) {
			verify(listener, times(LISTENERS_VALUE_CHANGED_INVOCATION_MAX_COUNT + NON_DATA_ROWS_COUNT))
					.valueChanged(Matchers.any(ProgressEvent.class));
		}
	}

	@Test(expected = MathException.class)
	public void test_LoadViaFormatWithUrl_doesNotContainDataRows_throwsMathException()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);
	}

	@Test
	public void test_LoadViaFormatWithUrl_always_setsName() throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		assertEquals(dsName, sut.getName());
	}

	@Test
	public void test_LoadViaFormatWithUrl_doesNotContainTimeStamps_setsHasTimeStampsAsFalse()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		assertFalse(sut.getHasTimeStamps());
	}

	@Test
	public void test_LoadViaFormatWithUrl_doesNotContainTimeStamps_setsVariables()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		String dateFormat = "dd/MM/yyyy";

		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addDataAndTimeStamps(fileLines, matrix.getRows(), matrix.getCols(), dateFormat);
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(fileLines.get(NAME_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getName());
			assertEquals(fileLines.get(TAG_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getTag());
			assertEquals(fileLines.get(UNIT_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getUnit());
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_LoadViaFormatWithUrl_timeStampIsInvalid_throwsMathException()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addDataAndTimeStamps(fileLines, matrix, null);
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), true);
		format.setDateFormat(new SimpleDateFormat("dd/MM/yyyy"));

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);
	}

	@Test
	public void test_LoadViaFormatWithUrl_containsDataRows_setsData()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		for (int r = 0; r < matrix.getRows(); r++) {
			for (int c = 0; c < matrix.getCols(); c++) {
				assertEquals(sut.getDataMatrix().get(r, c), matrix.get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_LoadViaFormatWithUrl_containsDataRows_setsVariables()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(fileLines.get(NAME_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getName());
			assertEquals(fileLines.get(TAG_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getTag());
			assertEquals(fileLines.get(UNIT_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getUnit());
		}
	}

	@Test
	public void test_LoadViaFormatWithUrl_containsTimeStamps_setsTimeStamps()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		String dateFormat = "dd/MM/yyyy";

		DataSeries sut = new DataSeries();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addDataAndTimeStamps(fileLines, matrix.getRows(), matrix.getCols(), dateFormat);
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), true);
		format.setDateFormat(new SimpleDateFormat(dateFormat));

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		assertTrue(sut.getHasTimeStamps());
	}

	@Test
	public void test_LoadViaFormatWithUrl_formatTagLineIsNotSet_setsVariableTagsAsNames()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		format.setTagLine(-1);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(fileLines.get(NAME_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getTag());
		}
	}

	@Test
	public void test_LoadViaFormatWithUrl_formatNameLineIsNotSet_setsVariableNamesAsTags()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix.getRows(), matrix.getCols());
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		format.setNameLine(-1);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(fileLines.get(TAG_ROW_INDEX).get(idx), sut.getVarByIndex(idx).getName());
		}
	}

	@Test
	public void test_LoadViaFormatWithUrl_formatNameLineAndTagLineIsNotSet_setsVariableNamesAndTagsAsAutoNames()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);
		int existingVarsCount = sut.getDataMatrix().getCols();

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		format.setNameLine(-1);
		format.setTagLine(-1);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals(DEFAULT_VAR_NAME + (existingVarsCount + idx + 1), sut.getVarByIndex(idx).getName());
			assertEquals(DEFAULT_VAR_NAME + (existingVarsCount + idx + 1), sut.getVarByIndex(idx).getTag());
		}
	}

	@Test
	public void test_LoadViaFormatWithUrl_formatNameLineAndUnitLineIsNotSet_setsVariableUnitsAsNone()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);
		format.setUnitLine(-1);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		for (int idx = 0; idx < matrix.getCols(); idx++) {
			assertEquals("None", sut.getVarByIndex(idx).getUnit());
		}
	}

	@Test
	public void test_LoadViaFormatWithUrl_dataRowsAreLessThanTwenty_invokesProgressListenerValueChangedMethodForEachDataRow()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);
		Vector<ProgressListener> listeners = addProgressListeners(sut);

		Matrix matrix = createMatrix();
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		for (ProgressListener listener : listeners) {
			verify(listener, times(sut.getDataMatrix().getRows() + NON_DATA_ROWS_COUNT))
					.valueChanged(Matchers.any(ProgressEvent.class));
		}
	}

	@Test
	public void test_LoadViaFormatWithUrl_dataRowsAreTwentyOrMore_invokesProgressListenerValueChangedMethodForFirstTwentyDataRowsOnly()
			throws MathException, MalformedURLException, IOException {
		// Arrange
		DataSeries sut = createSut(false);
		Vector<ProgressListener> listeners = addProgressListeners(sut);

		Matrix matrix = createMatrix(40, 4);
		Vector<Vector<String>> fileLines = createVariableSpecsLines(matrix.getCols(), false);
		addData(fileLines, matrix);
		URL url = createUrlWithoutLeadingAndTrailingSeparators(fileLines);

		DataSeriesFileFormat format = createDataSeriesFileFormat(matrix.getCols(), false);

		String dsName = "DataSeries Name";

		// Act
		sut.LoadViaFormat(url, format, dsName);

		// Assert
		for (ProgressListener listener : listeners) {
			verify(listener, times(LISTENERS_VALUE_CHANGED_INVOCATION_MAX_COUNT + NON_DATA_ROWS_COUNT))
					.valueChanged(Matchers.any(ProgressEvent.class));
		}
	}

	@Test
	public void test_saveGNNEDataSet_always_writeVersionLineInfoToFile() throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		Vector<String> outputNames = new Vector<String>();

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals("1; Version of this save/restore protocol for data sets",
				fileLines.get(GNNE_DATA_SET_VERSION_ROW_INDEX).trim());
	}

	@Test
	public void test_saveGNNEDataSet_UsedAndOutputNamesAreEmpty_writesSamplesInfoToFile()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		Vector<String> outputNames = new Vector<String>();

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals("0 ; Number of samples in this data-set", fileLines.get(GNNE_DATA_SET_SAMPLES_ROW_INDEX).trim());
	}

	@Test
	public void test_saveGNNEDataSet_UsedAndOutputNamesAreEmpty_writesInputDataInfoToFile()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		Vector<String> outputNames = new Vector<String>();

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals("0 ; ; Length of each input data vector",
				fileLines.get(GNNE_DATA_SET_INPUT_DATA_VECTOR_ROW_INDEX).trim());
	}

	@Test
	public void test_saveGNNEDataSet_UsedAndOutputNamesAreEmpty_writesOutputDataInfoToFile()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		Vector<String> outputNames = new Vector<String>();

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals("0 ; Length of each output data vector",
				fileLines.get(GNNE_DATA_SET_OUTPUT_DATA_VECTOR_ROW_INDEX).trim());
	}

	@Test
	public void test_saveGNNEDataSet_usedNamesContainsVarNames_writesInputNumberOfColumns()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			usedNames.add(sut.getVarByIndex(idx).getName());
		}

		Vector<String> outputNames = new Vector<String>();

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals(sut.getDataMatrix().getCols() + " ; ; Length of each input data vector",
				fileLines.get(GNNE_DATA_SET_INPUT_DATA_VECTOR_ROW_INDEX).trim());
	}

	@Test
	public void test_saveGNNEDataSet_outputNamesContainsVarNames_writesOutputNumberOfColumns()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		Vector<String> outputNames = new Vector<String>();

		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			usedNames.add(sut.getVarByIndex(idx).getName());
			outputNames.add(sut.getVarByIndex(idx).getName());
		}

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals(sut.getDataMatrix().getCols() + " ; Length of each output data vector",
				fileLines.get(GNNE_DATA_SET_OUTPUT_DATA_VECTOR_ROW_INDEX).trim());
	}

	@Test
	public void test_saveGNNEDataSet_always_writesRowIndexToFile() throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		Vector<String> outputNames = new Vector<String>();

		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			usedNames.add(sut.getVarByIndex(idx).getName());
			outputNames.add(sut.getVarByIndex(idx).getName());
		}

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			String dataRow = fileLines.get(GNNE_DATA_SET_DATA_ROW_START_INDEX + idx);
			String[] dataRowContents = dataRow.split(",");
			assertEquals(idx, new Integer(dataRowContents[GNNE_DATA_SET_DATA_ROW_INDEX_COL_INDEX]).intValue());
		}
	}

	@Test
	public void test_saveGNNEDataSet_sutContainsTimeStamps_writesTimeStampsToFile() throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut(true);
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		Vector<String> outputNames = new Vector<String>();

		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			usedNames.add(sut.getVarByIndex(idx).getName());
			outputNames.add(sut.getVarByIndex(idx).getName());
		}

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			String dataRow = fileLines.get(GNNE_DATA_SET_DATA_ROW_START_INDEX + idx);
			String[] dataRowContents = dataRow.split(",");
			assertEquals((long) (sut.getTimeStamps()[idx] / 1000.0),
					Double.valueOf(dataRowContents[GNNE_DATA_SET_DATA_ROW_TIME_STAMP_COL_INDEX]).longValue());
			assertEquals("OK", dataRowContents[GNNE_DATA_SET_DATA_ROW_OK_COL_INDEX].trim());
		}
	}

	@Test
	public void test_saveGNNEDataSet_sutDoesNotContainTimeStamps_writesTimeStampsRelaventToBaseToFile()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut(false);
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		Vector<String> outputNames = new Vector<String>();

		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			usedNames.add(sut.getVarByIndex(idx).getName());
			outputNames.add(sut.getVarByIndex(idx).getName());
		}

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		for (int idx = 0; idx < sut.getDataMatrix().getRows(); idx++) {
			String dataRow = fileLines.get(GNNE_DATA_SET_DATA_ROW_START_INDEX + idx);
			String[] dataRowContents = dataRow.split(",");
			assertEquals(BASE_TIME_STAMP + (idx * 10),
					new Integer(dataRowContents[GNNE_DATA_SET_DATA_ROW_TIME_STAMP_COL_INDEX]).intValue());
			assertEquals("OK", dataRowContents[GNNE_DATA_SET_DATA_ROW_OK_COL_INDEX].trim());
		}
	}

	@Test
	public void test_saveGNNEDataSet_outputDataContainsAllVars_writesMatrixDataToFile()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut(false);
		int rows = sut.getDataMatrix().getRows();
		int cols = sut.getDataMatrix().getCols();
		File file = createEmptyFile();
		String directory = file.getAbsolutePath().replace(file.getName(), "");
		Vector<String> usedNames = new Vector<String>();
		Vector<String> outputNames = new Vector<String>();

		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			usedNames.add(sut.getVarByIndex(idx).getName());
			outputNames.add(sut.getVarByIndex(idx).getName());
		}

		// Act
		sut.saveGNNEDataSet(directory, file.getName(), usedNames, outputNames);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		for (int r = 0; r < rows; r++) {
			String dataRow = fileLines.get(GNNE_DATA_SET_DATA_ROW_START_INDEX + r);
			String[] dataRowContents = dataRow.split(",");
			for (int c = 0; c < cols; c++) {
				assertEquals(sut.getDataMatrix().get(r, c),
						Double.valueOf(dataRowContents[GNNE_DATA_SET_DATA_ROW_MATRIX_START_COL_INDEX + c].trim())
								.doubleValue(),
						DELTA);
			}
		}
	}

	@Test
	public void test_saveBinary_always_savesDataSeriesAsBinaryFile() throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();

		// Act
		sut.saveBinary(file.getAbsolutePath());

		// Assert
		DataSeries savedDataSeries = fetchDataSeries(file);
		assertNotNull(savedDataSeries);
		assertDataSeriesIsSame(sut, savedDataSeries);
	}

	@Test
	public void test_saveBinary_filenameContainsDot_savesCorrectDataSeriesNameInBinaryFile()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();
		String expectedDataSeriesName = file.getAbsolutePath().substring(0, file.getAbsolutePath().indexOf("."));

		// Act
		sut.saveBinary(file.getAbsolutePath());

		// Assert
		DataSeries savedDataSeries = fetchDataSeries(file);
		assertEquals(expectedDataSeriesName, savedDataSeries.getName());
	}

	@Test
	public void test_saveBinary_filenameDoesNotContainDot_savesCorrectDataSeriesNameInBinaryFile()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile("Data Series Binary File");

		// Act
		sut.saveBinary(file.getAbsolutePath());

		// Assert
		DataSeries savedDataSeries = fetchDataSeries(file);
		assertEquals(file.getAbsolutePath(), savedDataSeries.getName());
	}

	@Test
	public void test_saveBinary_directoryIsSpecified_savesCorrectDataSeriesNameInBinaryFile()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		String fileName = "Data Series Binary File";
		File file = createEmptyFile(fileName);

		// Act
		sut.saveBinary(file.getAbsolutePath().replace(file.getName(), ""), file.getName());

		// Assert
		DataSeries savedDataSeries = fetchDataSeries(file);
		assertEquals(fileName, savedDataSeries.getName());
	}

	@Test
	public void test_initTransient_always_setsDataSource() throws MathException {
		// Arrange
		DataSeries sut = createSut();
		RawDataSource dataSource = createRawDataSource();

		// Act
		sut.initTransient(dataSource);

		// Assert
		assertEquals(dataSource, sut.getDataSource());
	}

	@Test
	public void test_initTransient_always_setsDataSeriesOfAllVariables() throws MathException {
		// Arrange
		DataSeries sut = createSut();
		RawDataSource dataSource = createRawDataSource();
		int variablesCount = sut.getDataMatrix().getCols();

		// Act
		sut.initTransient(dataSource);

		// Assert
		for (int idx = 0; idx < variablesCount; idx++) {
			assertEquals(sut, sut.getVarByIndex(idx).getDataSeries());
			assertEquals(sut.hashCode(), sut.getVarByIndex(idx).getDataSeriesHashCode());
		}
	}

	@Test
	public void test_initTransientWithProject_dataSourceIsNotFound_doesNotUpdateDataSource() throws MathException {
		// Arrange
		DataSeries sut = createSut();
		String existingDataSourceName = sut.getDataSource().getName();
		Project project = createProject();
		Vector<Preprocessor> preprocessors = new Vector<Preprocessor>();
		preprocessors.add(createPreprocessor());
		addProjectPreprocessor(project, preprocessors);

		// Act
		sut.initTransient(project);

		// Assert
		assertEquals(existingDataSourceName, sut.getDataSource().getName());
	}

	@Test
	public void test_initTransientWithProject_dataSourceIsFound_updatesDataSource() throws MathException {
		// Arrange
		DataSeries sut = createSut();
		Preprocessor preprocessor = createPreprocessor("Preprocessor Old Name");
		sut.setDataSource(preprocessor);

		String preprocessorNewName = "Preprocessor New Name";
		updatePreprocessor(preprocessor, preprocessorNewName);

		Project project = createProject();
		Vector<Preprocessor> preprocessors = new Vector<Preprocessor>();
		preprocessors.add(createPreprocessor());
		preprocessors.add(preprocessor);
		preprocessors.add(createPreprocessor());

		addProjectPreprocessor(project, preprocessors);

		// Act
		sut.initTransient(project);

		// Assert
		assertEquals(preprocessorNewName, sut.getDataSource().getName());
	}

	@Test
	public void test_toString_always_returnsDataSeriesName() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act & Assert
		assertEquals(sut.getName(), sut.toString());
	}

	@Test
	public void test_saveAscii_dataMatrixContainsAllDataAsFinite_addsWholeMatrixDataToFile()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		int rows = sut.getDataMatrix().getRows();
		int cols = sut.getDataMatrix().getCols();

		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_MATRIX, dateFormat,
				timeFormat);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals(rows, fileLines.size());
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				assertEquals(sut.getDataMatrix().get(r, c),
						Double.valueOf(fileLines.get(r).split(",")[c]).doubleValue(), DELTA);
			}
		}
	}

	@Test
	public void test_saveAscii_dataMatrixContainsSomeDataAsNaN_skipsNaNDataRowAndAddsFiniteMatrixDataToFile()
			throws MathException, IOException {
		// Arrange
		Matrix matrix = createMatrix();
		matrix.set(0, 0, Double.NaN);
		DataSeries sut = createSut();
		int rows = matrix.getRows();
		int cols = matrix.getCols();

		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_MATRIX, dateFormat,
				timeFormat);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals(rows, fileLines.size());
		int lineIdx = 0;
		for (int r = 0; r < rows; r++) {
			if (sut.getDataMatrix().get(r, 0) == Double.NaN) {
				continue;
			}

			for (int c = 0; c < cols; c++) {
				assertEquals(sut.getDataMatrix().get(r, c),
						Double.valueOf(fileLines.get(lineIdx).split(",")[c]).doubleValue(), DELTA);
			}

			lineIdx++;
		}
	}

	@Test
	public void test_saveAscii_dataMatrixContainsSomeDataAsInfinity_skipsInfinityDataRowAndAddsFiniteMatrixDataToFile()
			throws MathException, IOException {
		// Arrange
		Matrix matrix = createMatrix();
		matrix.set(0, 0, Double.POSITIVE_INFINITY);
		DataSeries sut = createSut();
		int rows = matrix.getRows();
		int cols = matrix.getCols();

		File file = createEmptyFile();
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

		// Act
		sut.saveAscii(file.getAbsolutePath().replace(file.getName(), ""), file.getName(), ASCII_TYPE_MATRIX, dateFormat,
				timeFormat);

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals(rows, fileLines.size());
		int lineIdx = 0;
		for (int r = 0; r < rows; r++) {
			if (sut.getDataMatrix().get(r, 0) == Double.POSITIVE_INFINITY) {
				continue;
			}

			for (int c = 0; c < cols; c++) {
				assertEquals(sut.getDataMatrix().get(r, c),
						Double.valueOf(fileLines.get(lineIdx).split(",")[c]).doubleValue(), DELTA);
			}

			lineIdx++;
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_truncateColumn_requiredTruncatedColumnsCountIsZero_throwsMathException() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		sut.truncateColumn(0);
	}

	@Test
	public void test_truncateColumn_requiredTruncatedColumnsCountIsNonZero_alwaysTruncatesVariablesAndDataMatrix()
			throws MathException {
		// Arrange
		DataSeries sut = createSut();
		Matrix existingDataMatrix = cloneMatrix(sut.getDataMatrix());
		int numberOfCols = 2;

		// Act
		sut.truncateColumn(numberOfCols);

		// Assert
		assertEquals(numberOfCols, sut.getVarObjects().size());
		assertEquals(existingDataMatrix.getRows(), sut.getDataMatrix().getRows());
		assertEquals(numberOfCols, sut.getDataMatrix().getCols());
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(existingDataMatrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_truncateRow_always_truncatesDataRows() throws MathException {
		// Arrange
		DataSeries sut = createSut(createMatrix(5, 4), true);
		Matrix existingDataMatrix = cloneMatrix(sut.getDataMatrix());
		int startRow = 1;
		int endRow = 3;

		// Act
		sut.truncateRow(startRow, endRow);

		// Assert
		assertEquals(endRow - startRow + 1, sut.getDataMatrix().getRows());
		assertEquals(existingDataMatrix.getCols(), sut.getDataMatrix().getCols());
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(existingDataMatrix.get(startRow + r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_clearMemory_always_removesTimeStamps() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		sut.clearMemory();

		// Assert
		assertNull(sut.getTimeStamps());
	}

	@Test
	public void test_clearMemory_always_removesVariableObjects() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		sut.clearMemory();

		// Assert
		assertNull(sut.getVarObjects());
	}

	@Test
	public void test_clearMemory_always_clearsDataMatrix() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		sut.clearMemory();

		// Assert
		assertNull(sut.getDataMatrix().getData());
	}

	@Test
	public void test_clone_always_clonesDataMatrix() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		DataSeries cloned = (DataSeries) sut.clone();

		// Assert
		assertEquals(sut.getDataMatrix().getRows(), cloned.getDataMatrix().getRows());
		assertEquals(sut.getDataMatrix().getCols(), cloned.getDataMatrix().getCols());
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(cloned.getDataMatrix().get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_clone_always_clonesVariables() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		DataSeries cloned = (DataSeries) sut.clone();

		// Assert
		assertEquals(sut.getVarObjects().size(), cloned.getVarObjects().size());
		for (int idx = 0; idx < sut.getVarObjects().size(); idx++) {
			Variable sutVariable = (Variable) sut.getVarObjects().get(idx);
			Variable clonedVariable = (Variable) cloned.getVarObjects().get(idx);
			assertEquals(clonedVariable.getName(), sutVariable.getName());
			assertEquals(clonedVariable.getTag(), sutVariable.getTag());
			assertEquals(clonedVariable.getUnit(), sutVariable.getUnit());
		}
	}

	@Test
	public void test_clone_always_clonesTimeStamps() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		DataSeries cloned = (DataSeries) sut.clone();

		// Assert
		assertEquals(sut.getHasTimeStamps(), cloned.getHasTimeStamps());
		assertEquals(sut.getTimeStamps().length, cloned.getTimeStamps().length);
		for (int idx = 0; idx < sut.getTimeStamps().length; idx++) {
			assertEquals(sut.getTimeStamps()[idx], cloned.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_clone_always_clonesDataSource() throws MathException {
		// Arrange
		DataSeries sut = createSut();
		addProgressListeners(sut);

		// Act
		DataSeries cloned = (DataSeries) sut.clone();

		// Assert
		assertEquals(sut.getDataSource(), cloned.getDataSource());
	}

	@Test
	public void test_createScaledDataSeries_always_clonesDataMatrix() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		DataSeries scaledDataSeries = sut.createScaledDataSeries();

		// Assert
		assertEquals(sut.getDataMatrix().getRows(), scaledDataSeries.getDataMatrix().getRows());
		assertEquals(sut.getDataMatrix().getCols(), scaledDataSeries.getDataMatrix().getCols());
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(scaledDataSeries.getDataMatrix().get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_createScaledDataSeries_always_clonesVariables() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		DataSeries scaledDataSource = sut.createScaledDataSeries();

		// Assert
		assertEquals(sut.getVarObjects().size(), scaledDataSource.getVarObjects().size());
		for (int idx = 0; idx < sut.getVarObjects().size(); idx++) {
			Variable sutVariable = (Variable) sut.getVarObjects().get(idx);
			Variable clonedVariable = (Variable) scaledDataSource.getVarObjects().get(idx);
			assertEquals(clonedVariable.getName(), sutVariable.getName());
			assertEquals(clonedVariable.getTag(), sutVariable.getTag());
			assertEquals(clonedVariable.getUnit(), sutVariable.getUnit());
		}
	}

	@Test
	public void test_createScaledDataSeries_always_clonesTimeStamps() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		DataSeries scaledDataSeries = sut.createScaledDataSeries();

		// Assert
		assertEquals(sut.getHasTimeStamps(), scaledDataSeries.getHasTimeStamps());
		assertEquals(sut.getTimeStamps().length, scaledDataSeries.getTimeStamps().length);
		for (int idx = 0; idx < sut.getTimeStamps().length; idx++) {
			assertEquals(sut.getTimeStamps()[idx], scaledDataSeries.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_createScaledDataSeries_always_clonesDataSource() throws MathException {
		// Arrange
		DataSeries sut = createSut();
		addProgressListeners(sut);

		// Act
		DataSeries scaledDataSeries = sut.createScaledDataSeries();

		// Assert
		assertEquals(sut.getDataSource(), scaledDataSeries.getDataSource());
	}

	@Test
	public void test_writeVariableStatistics_always_writesStatisticsHeaderToFile() throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();

		// Act
		sut.writeVariableStatistics(file.getAbsolutePath());

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		assertEquals("Variable, MINIMUM,MAXIMUM,RANGE,MEAN,MEDIAN,STDDEV,VARIANCE,SKEWNESS,KURTOSIS", fileLines.get(0));
	}

	@Test
	public void test_writeVariableStatistics_always_writesAllVarStatisticsToFile() throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		File file = createEmptyFile();

		// Act
		sut.writeVariableStatistics(file.getAbsolutePath());

		// Assert
		Vector<String> fileLines = readLines(file.getAbsolutePath());
		for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
			String[] varStats = fileLines.get(VAR_STAT_DATA_ROW_START_INDEX + c).split(",");
			assertEquals(sut.getVarByIndex(c).getName(), varStats[VAR_STAT_VAR_NAME_INDEX]);
			assertEquals(calculateMin(sut.getDataMatrix(), c),
					Double.valueOf(varStats[VAR_STAT_VAR_MIN_INDEX].trim()).doubleValue(), DELTA);
			assertEquals(calculateMax(sut.getDataMatrix(), c),
					Double.valueOf(varStats[VAR_STAT_VAR_MAX_INDEX].trim()).doubleValue(), DELTA);
			assertEquals(calculateRange(sut.getDataMatrix(), c),
					Double.valueOf(varStats[VAR_STAT_VAR_RANGE_INDEX].trim()).doubleValue(), DELTA);
			assertEquals(calculateMean(sut.getDataMatrix(), c),
					Double.valueOf(varStats[VAR_STAT_VAR_MEAN_INDEX].trim()).doubleValue(), DELTA);
			assertEquals(calculateMedian(sut.getDataMatrix(), c),
					Double.valueOf(varStats[VAR_STAT_VAR_MEDIAN_INDEX].trim()).doubleValue(), DELTA);
			assertEquals(calculateStdDeviation(sut.getDataMatrix(), c),
					Double.valueOf(varStats[VAR_STAT_VAR_STD_DEV_INDEX].trim()).doubleValue(), DELTA);
			assertEquals(calculateVariance(sut.getDataMatrix(), c),
					Double.valueOf(varStats[VAR_STAT_VAR_VARIANCE_INDEX].trim()).doubleValue(), DELTA);
			assertEquals(calculateSkewness(sut.getDataMatrix(), c),
					Double.valueOf(varStats[VAR_STAT_VAR_SKEWNESS_INDEX].trim()).doubleValue(), DELTA);
			assertEquals(calculateKurtosis(sut.getDataMatrix(), c),
					Double.valueOf(varStats[VAR_STAT_VAR_KURTOSIS_INDEX].trim()).doubleValue(), DELTA);
		}
	}

	@Test
	public void test_resampleData_newRowsAreMoreThanExistingRows_doesNotResampleData()
			throws MathException, IOException {
		// Arrange
		DataSeries sut = createSut();
		Matrix existingMatrix = cloneMatrix(sut.getDataMatrix());
		long[] existingTimeStamps = sut.getTimeStamps().clone();
		long startTime = sut.getTimeStamps()[0];
		// Setting end time and interval such that new rows are more than
		// existing rows
		long endTime = startTime + (TIMESTAMPS_INTERVAL * (existingMatrix.getRows() + 1));

		// Act
		sut.resampleData(startTime, endTime, TIMESTAMPS_INTERVAL);

		// Assert
		for (int r = 0; r < existingMatrix.getRows(); r++) {
			assertEquals(existingTimeStamps[r], sut.getTimeStamps()[r]);

			for (int c = 0; c < existingMatrix.getCols(); c++) {
				assertEquals(existingMatrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_resampleData_newRowsAreEqualToExistingRows_resamplesTimeStamps()
			throws MathException, IOException {
		// Arrange
		int rows = 5, cols = 4;
		Matrix sutMatrix = createMatrix(rows, cols);
		DataSeries sut = createSut(cloneMatrix(sutMatrix));
		long startTime = sut.getTimeStamps()[0];
		// Setting end time and interval such that new rows are equal to
		// existing rows
		long endTime = startTime + (TIMESTAMPS_INTERVAL * (rows));
		int newRows = (int) ((endTime - startTime) / TIMESTAMPS_INTERVAL);

		// Act
		sut.resampleData(startTime, endTime, TIMESTAMPS_INTERVAL);

		// Assert
		assertEquals(newRows, sut.getTimeStamps().length);
		for (int idx = 0; idx < newRows; idx++) {
			assertEquals(startTime + TIMESTAMPS_INTERVAL * idx, sut.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_resampleData_newRowsAreEqualToExistingRows_setsSameDataForMatchingTimeStamps()
			throws MathException, IOException {
		// Arrange
		int rows = 5, cols = 4;
		Matrix sutMatrix = createMatrix(rows, cols);
		DataSeries sut = createSut(cloneMatrix(sutMatrix));
		int delayedTimeStamps = 2;
		long startTime = sut.getTimeStamps()[delayedTimeStamps];
		// Setting end time and interval such that new rows are equal to
		// existing rows
		long endTime = startTime + (TIMESTAMPS_INTERVAL * (rows));
		int newRows = (int) ((endTime - startTime) / TIMESTAMPS_INTERVAL);

		// Act
		sut.resampleData(startTime, endTime, TIMESTAMPS_INTERVAL);

		// Assert
		assertEquals(newRows, sut.getDataMatrix().getRows());
		for (int r = 0; r < sut.getDataMatrix().getRows() - delayedTimeStamps; r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(sutMatrix.get(r + delayedTimeStamps, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_resampleData_newRowsAreEqualToExistingRows_setsNaNForMissingTimeStamps()
			throws MathException, IOException {
		// Arrange
		int rows = 5, cols = 4;
		Matrix sutMatrix = createMatrix(rows, cols);
		DataSeries sut = createSut(cloneMatrix(sutMatrix));
		int delayedTimeStamps = 2;
		long startTime = sut.getTimeStamps()[delayedTimeStamps];
		// Setting end time and interval such that new rows are equal to
		// existing rows
		long endTime = startTime + (TIMESTAMPS_INTERVAL * (rows));

		// Act
		sut.resampleData(startTime, endTime, TIMESTAMPS_INTERVAL);

		// Assert
		for (int r = sut.getDataMatrix().getRows() - delayedTimeStamps; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(Double.NaN, sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_resampleData_newRowsAreEqualToExistingRows_setsNaNForTimeStampsLessThanExistingTimeStamps()
			throws MathException, IOException {
		// Arrange
		int rows = 5, cols = 4;
		Matrix sutMatrix = createMatrix(rows, cols);
		DataSeries sut = createSut(cloneMatrix(sutMatrix));
		int advancedTimeStamps = 2;
		long startTime = sut.getTimeStamps()[0] - (TIMESTAMPS_INTERVAL * advancedTimeStamps);
		// Setting end time and interval such that new rows are equal to
		// existing rows
		long endTime = startTime + (TIMESTAMPS_INTERVAL * (rows));

		// Act
		sut.resampleData(startTime, endTime, TIMESTAMPS_INTERVAL);

		// Assert
		for (int r = 0; r < advancedTimeStamps; r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(Double.NaN, sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_resampleData_newRowsAreLessThanExistingRows_resamplesTimeStamps()
			throws MathException, IOException {
		// Arrange
		int rows = 5, cols = 4;
		Matrix sutMatrix = createMatrix(rows, cols);
		DataSeries sut = createSut(cloneMatrix(sutMatrix));
		long startTime = sut.getTimeStamps()[0];
		// Setting end time and interval such that new rows are equal to
		// existing rows
		long endTime = startTime + (TIMESTAMPS_INTERVAL * (rows - 1));
		int newRows = (int) ((endTime - startTime) / TIMESTAMPS_INTERVAL);

		// Act
		sut.resampleData(startTime, endTime, TIMESTAMPS_INTERVAL);

		// Assert
		assertEquals(newRows, sut.getTimeStamps().length);
		for (int idx = 0; idx < newRows; idx++) {
			assertEquals(startTime + TIMESTAMPS_INTERVAL * idx, sut.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_resampleData_newRowsAreLessThanExistingRows_setsSameDataForMatchingTimeStamps()
			throws MathException, IOException {
		// Arrange
		int rows = 5, cols = 4;
		Matrix sutMatrix = createMatrix(rows, cols);
		DataSeries sut = createSut(cloneMatrix(sutMatrix));
		int delayedTimeStamps = 2;
		long startTime = sut.getTimeStamps()[delayedTimeStamps];
		// Setting end time and interval such that new rows are equal to
		// existing rows
		long endTime = startTime + (TIMESTAMPS_INTERVAL * (rows - 1));
		int newRows = (int) ((endTime - startTime) / TIMESTAMPS_INTERVAL);

		// Act
		sut.resampleData(startTime, endTime, TIMESTAMPS_INTERVAL);

		// Assert
		assertEquals(newRows, sut.getDataMatrix().getRows());
		for (int r = 0; r < sut.getDataMatrix().getRows() - delayedTimeStamps; r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(sutMatrix.get(r + delayedTimeStamps, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_resampleData_newRowsAreLessThanExistingRows_setsNaNForMissingTimeStamps()
			throws MathException, IOException {
		// Arrange
		int rows = 5, cols = 4;
		Matrix sutMatrix = createMatrix(rows, cols);
		DataSeries sut = createSut(cloneMatrix(sutMatrix));
		int delayedTimeStamps = 2;
		long startTime = sut.getTimeStamps()[delayedTimeStamps];
		// Setting end time and interval such that new rows are equal to
		// existing rows
		long endTime = startTime + (TIMESTAMPS_INTERVAL * (rows - 1));

		// Act
		sut.resampleData(startTime, endTime, TIMESTAMPS_INTERVAL);

		// Assert
		for (int r = sutMatrix.getRows() - delayedTimeStamps; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(Double.NaN, sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_resampleData_newRowsAreLessThanExistingRows_setsNaNForTimeStampsLessThanExistingTimeStamps()
			throws MathException, IOException {
		// Arrange
		int rows = 5, cols = 4;
		Matrix sutMatrix = createMatrix(rows, cols);
		DataSeries sut = createSut(cloneMatrix(sutMatrix));
		int advancedTimeStamps = 2;
		long startTime = sut.getTimeStamps()[0] - (TIMESTAMPS_INTERVAL * advancedTimeStamps);
		// Setting end time and interval such that new rows are equal to
		// existing rows
		long endTime = startTime + (TIMESTAMPS_INTERVAL * (rows - 1));

		// Act
		sut.resampleData(startTime, endTime, TIMESTAMPS_INTERVAL);

		// Assert
		for (int r = 0; r < advancedTimeStamps; r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(Double.NaN, sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_initializeHardBounds_always_initializedHardBoundsOfAllVariables() throws MathException {
		// Arrange
		DataSeries sut = createSut();
		updateVariableHardBounds(sut);

		// Act
		sut.initializeHardBounds();

		// Assert
		for (int idx = 0; idx < sut.getVarObjects().size(); idx++) {
			Variable variable = sut.getVarByIndex(idx);
			assertEquals(Double.NEGATIVE_INFINITY, variable.getHardLowerBound(), DELTA);
			assertEquals(Double.POSITIVE_INFINITY, variable.getHardUpperBound(), DELTA);
		}
	}

	@Test
	public void test_getFiniteData_always_returnsDataMatrixAsTwoDimensionalArray() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act
		double[][] finiteData = sut.getFiniteData();

		// Assert
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				assertEquals(finiteData[r][c], sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_hasFiniteData_dataIsFinite_returnsTrue() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act & Assert
		assertTrue(sut.hasFiniteData());
	}

	@Test
	public void test_hasFiniteData_dataIsNaN_returnsFalse() throws MathException {
		// Arrange
		Matrix matrix = createMatrix();
		for (int r = 0; r < matrix.getRows(); r++) {
			matrix.set(r, 0, Double.NaN);
		}

		DataSeries sut = createSut(matrix);

		// Act & Assert
		assertFalse(sut.hasFiniteData());
	}

	@Test
	public void test_hasFiniteData_dataIsInfinite_returnsFalse() throws MathException {
		// Arrange
		Matrix matrix = createMatrix();
		for (int r = 0; r < matrix.getRows(); r++) {
			matrix.set(r, 0, Double.POSITIVE_INFINITY);
		}

		DataSeries sut = createSut(matrix);

		// Act & Assert
		assertFalse(sut.hasFiniteData());
	}

	@Test
	public void test_setDataMatrix_matrixContainsDiffNumberOfColsThanVariables_doesNotUpdateMatrix()
			throws MathException {
		// Act
		DataSeries sut = createSut();
		Matrix sutMatrix = cloneMatrix(sut.getDataMatrix());
		Matrix newMatrix = createMatrix(ANY_INT, sut.getVarObjects().size() + 1);

		// Act
		sut.setDataMatrix(newMatrix);

		// Assert
		assertEquals(sutMatrix.getCols(), sut.getDataMatrix().getCols());
		for (int r = 0; r < sutMatrix.getRows(); r++) {
			for (int c = 0; c < sutMatrix.getCols(); c++) {
				assertEquals(sutMatrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_setDataMatrix_matrixContainsSameNumberOfColsAsVariables_updatesMatrix() throws MathException {
		// Act
		DataSeries sut = createSut();
		Matrix newMatrix = createMatrix(ANY_INT, sut.getVarObjects().size());

		// Act
		sut.setDataMatrix(newMatrix);

		// Assert
		assertEquals(newMatrix.getCols(), sut.getDataMatrix().getCols());
		for (int r = 0; r < newMatrix.getRows(); r++) {
			for (int c = 0; c < newMatrix.getCols(); c++) {
				assertEquals(newMatrix.get(r, c), sut.getDataMatrix().get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_setDataMatrix_matrixContainsSameNumberOfRowsAsTimeStamps_doesNotClearTimeStamps()
			throws MathException {
		// Act
		DataSeries sut = createSut();
		long[] existingTimeStamps = sut.getTimeStamps().clone();
		Matrix newMatrix = createMatrix(sut.getDataMatrix().getRows(), sut.getVarObjects().size());

		// Act
		sut.setDataMatrix(newMatrix);

		// Assert
		for (int idx = 0; idx < existingTimeStamps.length; idx++) {
			assertEquals(existingTimeStamps[idx], sut.getTimeStamps()[idx]);
		}
	}

	@Test
	public void test_setDataMatrix_matrixContainsDifferentNumberOfRowsThanTimeStamps_clearsTimeStamps()
			throws MathException {
		// Act
		DataSeries sut = createSut();
		Matrix newMatrix = createMatrix(sut.getDataMatrix().getRows() + 1, sut.getVarObjects().size());

		// Act
		sut.setDataMatrix(newMatrix);

		// Assert
		assertFalse(sut.getHasTimeStamps());
		assertEquals(0, sut.getTimeStamps().length);
	}

	@Test
	public void test_findRowAtTime_timeStampIsLessThanFirstTimeStamp_ReturnsMinusOne() throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act && Assert
		assertEquals(-1, sut.findRowAtTime(sut.getTimeStamps()[0] - 1));
	}

	@Test
	public void test_findRowAtTime_timeStampIsGreaterThanLastTimeStamp_ReturnsLastRowIndex() throws MathException {
		// Arrange
		DataSeries sut = createSut();
		int lastTimeStampIdx = sut.getTimeStamps().length - 1;

		// Act && Assert
		assertEquals(lastTimeStampIdx, sut.findRowAtTime(sut.getTimeStamps()[lastTimeStampIdx] + 1));
	}

	@Test
	public void test_findRowAtTime_timeStampIsBetweenExistingTimeStamps_ReturnsLowerTimeStampIndex()
			throws MathException {
		// Arrange
		DataSeries sut = createSut();

		// Act && Assert
		for (int timeStampIdx = 0; timeStampIdx < sut.getTimeStamps().length; timeStampIdx++) {
			assertEquals(timeStampIdx, sut.findRowAtTime(sut.getTimeStamps()[timeStampIdx] + 1));
		}
	}

	// -- Helper Methods --

	private Vector<ProgressListener> addProgressListeners(DataSeries sut) {
		Vector<ProgressListener> listeners = new Vector<ProgressListener>();
		for (int listenerIdx = 0; listenerIdx < 3; listenerIdx++) {
			ProgressListener listener = createProgressListener();
			listeners.add(listener);
			sut.addListener(listener);
		}

		return listeners;
	}

	private Vector<String> readLines(String fileName) throws IOException {
		Vector<String> lines = new Vector<String>();

		FileInputStream fileStream = null;
		InputStreamReader streamReader = null;
		BufferedReader reader = null;
		try {
			fileStream = new FileInputStream(fileName);
			streamReader = new InputStreamReader(fileStream, Charset.defaultCharset());
			reader = new BufferedReader(streamReader);
			String line = null;
			while ((line = reader.readLine()) != null) {
				lines.add(line);
			}
		} catch (Exception ex) {
			fail("Failed to read lines.");
		} finally {
			closeSilently(reader);
			closeSilently(streamReader);
			closeSilently(fileStream);
		}

		return lines;
	}

	private void addData(Vector<Vector<String>> fileLines, int rowsCount, int colsCount) {
		for (int idx = 0; idx < rowsCount; idx++) {
			Vector<String> line = new Vector<String>();

			for (int colIdx = 0; colIdx < colsCount; colIdx++) {
				line.add(new Double(randomGenerator.nextDouble()).toString());
			}

			fileLines.add(line);
		}
	}

	private void addData(Vector<Vector<String>> fileLines, Matrix matrix) {
		for (int r = 0; r < matrix.getRows(); r++) {
			Vector<String> line = new Vector<String>();

			for (int c = 0; c < matrix.getCols(); c++) {
				line.add(new Double(matrix.get(r, c)).toString());
			}

			fileLines.add(line);
		}
	}

	private void addDataAndTimeStamps(Vector<Vector<String>> fileLines, int rowsCount, int colsCount,
			String dateTimeFormat) {
		for (int idx = 0; idx < rowsCount; idx++) {
			Vector<String> line = new Vector<String>();

			String timeStamp = new Long(System.currentTimeMillis()).toString();
			if (dateTimeFormat != null) {
				timeStamp = new SimpleDateFormat(dateTimeFormat).format(new Date(System.currentTimeMillis()));
			}

			line.add(timeStamp);

			for (int colIdx = 0; colIdx < colsCount; colIdx++) {
				line.add(new Double(randomGenerator.nextDouble()).toString());
			}

			fileLines.add(line);
		}
	}

	private void addDataAndTimeStamps(Vector<Vector<String>> fileLines, Matrix matrix, String dateTimeFormat) {
		for (int r = 0; r < matrix.getRows(); r++) {
			Vector<String> line = new Vector<String>();

			String timeStamp = new Long(System.currentTimeMillis()).toString();
			if (dateTimeFormat != null) {
				timeStamp = new SimpleDateFormat(dateTimeFormat).format(new Date(System.currentTimeMillis()));
			}

			line.add(timeStamp);

			for (int c = 0; c < matrix.getCols(); c++) {
				line.add(new Double(matrix.get(r, c)).toString());
			}

			fileLines.add(line);
		}
	}

	private void addProjectPreprocessor(Project project, Vector<Preprocessor> preprocessors) {
		PowerMockito.when(project.getPreprocessors()).thenReturn(preprocessors);
	}

	private void assertDataSeriesIsSame(DataSeries expected, DataSeries actual) {
		assertEquals(expected.getComment(), actual.getComment());

		assertEquals(expected.getDataMatrix().getRows(), actual.getDataMatrix().getRows());
		for (int r = 0; r < expected.getDataMatrix().getRows(); r++) {
			for (int c = 0; c < expected.getDataMatrix().getCols(); c++) {
				assertEquals(expected.getDataMatrix().get(r, c), actual.getDataMatrix().get(r, c), DELTA);
			}
		}

		assertEquals(expected.getHasTimeStamps(), actual.getHasTimeStamps());
		for (int idx = 0; idx < expected.getDataMatrix().getRows(); idx++) {
			assertEquals(expected.getTimeStamps()[idx], actual.getTimeStamps()[idx]);
		}
	}

	private void assertThatFileContainsDataMatrixInfo(DataSeries sut, File file, String separator) throws IOException {
		Vector<String> lines = readLines(file.getAbsolutePath());
		assertThatFileContainsDataMatrixInfo(sut, lines, separator);
	}

	private void assertThatFileContainsDataMatrixInfo(DataSeries sut, Vector<String> lines, String separator) {
		for (int r = 0; r < sut.getDataMatrix().getRows(); r++) {
			String dataLine = lines.get(DATA_FIRST_ROW_INDEX + r);
			String data = "";
			for (int c = 0; c < sut.getDataMatrix().getCols(); c++) {
				data += sut.getDataMatrix().get(r, c);
				if (c < sut.getDataMatrix().getCols() - 1) {
					data += separator;
				}
			}

			assertTrue(dataLine.contains(data));
		}
	}

	private void assertThatFileContainsTimeStampsInfo(DataSeries sut, File file, SimpleDateFormat dateFormat,
			SimpleDateFormat timeFormat, String separator) throws IOException {
		Vector<String> lines = readLines(file.getAbsolutePath());
		assertThatFileContainsTimeStampsInfo(sut, lines, dateFormat, timeFormat, separator);
	}

	private void assertThatFileContainsTimeStampsInfo(DataSeries sut, Vector<String> lines, SimpleDateFormat dateFormat,
			SimpleDateFormat timeFormat, String separator) throws IOException {
		String tags = lines.get(TAG_ROW_INDEX);
		String names = lines.get(NAME_ROW_INDEX);
		String units = lines.get(UNIT_ROW_INDEX);
		assertTrue(tags.startsWith(TIME_TAG + separator));
		assertTrue(names.startsWith(TIME_TAG + separator));
		assertTrue(units.startsWith(dateFormat.toPattern() + " " + timeFormat.toPattern() + separator));
		for (int idx = 0; idx < sut.getTimeStamps().length; idx++) {
			String dataLine = lines.get(DATA_FIRST_ROW_INDEX + idx);
			String timeStamp = dateFormat.format(new Date(sut.getTimeStamps()[idx])) + " "
					+ timeFormat.format(new Date(sut.getTimeStamps()[idx]));
			assertTrue(dataLine.startsWith(timeStamp + separator));
		}
	}

	private void assertThatFileContainsVariableNamesInfo(DataSeries sut, File file, String separator)
			throws IOException {
		Vector<String> lines = readLines(file.getAbsolutePath());
		assertThatFileContainsVariableNamesInfo(sut, lines, separator);
	}

	private void assertThatFileContainsVariableNamesInfo(DataSeries sut, Vector<String> lines, String separator)
			throws IOException {
		String names = lines.get(NAME_ROW_INDEX);
		assertTrue(names.contains(getVariableNames(sut, separator)));
	}

	private void assertThatFileContainsVariableTagsInfo(DataSeries sut, File file, String separator)
			throws IOException {
		Vector<String> lines = readLines(file.getAbsolutePath());
		assertThatFileContainsVariableTagsInfo(sut, lines, separator);
	}

	private void assertThatFileContainsVariableTagsInfo(DataSeries sut, Vector<String> lines, String separator)
			throws IOException {
		String tags = lines.get(TAG_ROW_INDEX);
		assertTrue(tags.contains(getVariableTags(sut, separator)));
	}

	private void assertThatFileContainsVariableUnitsInfo(DataSeries sut, File file, String separator)
			throws IOException {
		Vector<String> lines = readLines(file.getAbsolutePath());
		assertThatFileContainsVariableUnitsInfo(sut, lines, separator);
	}

	private void assertThatFileContainsVariableUnitsInfo(DataSeries sut, Vector<String> lines, String separator) {
		String units = lines.get(UNIT_ROW_INDEX);
		assertTrue(units.contains(getVariableUnits(sut, separator)));
	}

	private void assertThatFileDoesNotContainTimeStampsInfo(DataSeries sut, File file) throws IOException {
		Vector<String> lines = readLines(file.getAbsolutePath());
		assertThatFileDoesNotContainTimeStampsInfo(sut, lines);
	}

	private void assertThatFileDoesNotContainTimeStampsInfo(DataSeries sut, Vector<String> lines) {
		String tags = lines.get(TAG_ROW_INDEX);
		String names = lines.get(NAME_ROW_INDEX);
		assertFalse(tags.contains(TIME_TAG));
		assertFalse(names.contains(TIME_TAG));
	}

	private void assertThatTimeStampsAreSet(DataSeries sut, int cols, long startTime, long interval) {
		long[] timeStamps = sut.getTimeStamps();
		for (int idx = 0; idx < cols; idx++) {
			assertEquals(startTime + interval * idx, timeStamps[idx]);
		}
	}

	private void assertThatVariablesAreCreatedWithDefaultNames(DataSeries sut, int cols) {
		for (int idx = 0; idx < cols; idx++) {
			Variable variable = sut.getVarByIndex(idx);
			String expectedVariableName = DEFAULT_VAR_NAME + new Integer(idx + 1).toString();
			assertEquals(expectedVariableName, variable.getName());
			assertEquals(sut, variable.getDataSeries());
			assertEquals(idx, variable.getColumnIndex());
		}
	}

	private void assertThatVariablesAreCreatedWithNewNamesTagsAndUnits(DataSeries sut,
			Vector<Vector<String>> newValues) {
		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			Variable variable = sut.getVarByIndex(idx);
			assertEquals(newValues.get(1).get(idx), variable.getName());
			assertEquals(newValues.get(0).get(idx), variable.getTag());
			assertEquals(newValues.get(2).get(idx), variable.getUnit());
		}
	}

	private double calculateKurtosis(Matrix matrix, int col) {
		double kurtosis = Double.NaN;

		if (matrix.getRows() > 0) {
			double variance = 0;
			double stdDeviation = 0;
			double err = 0;
			double skew = 0;
			kurtosis = 0;

			for (int r = 0; r < matrix.getRows(); r++) {
				if (!Double.isNaN(matrix.get(r, col))) {
					double dif = matrix.get(r, col) - calculateMean(matrix, col);
					err += Math.abs(dif);
					variance += dif * dif;
					stdDeviation += dif * dif * dif;
					skew += dif * dif * dif;
					kurtosis += dif * dif * dif * dif;
				}
			}

			err = err / matrix.getRows();
			int nn = matrix.getRows();
			if (matrix.getRows() == 1) {
				nn = 2;
			}

			variance = variance / (nn - 1);
			stdDeviation = Math.sqrt(variance);
			skew = skew / (matrix.getRows() * stdDeviation * stdDeviation * stdDeviation);
			kurtosis = kurtosis / (matrix.getRows() * stdDeviation * stdDeviation * stdDeviation * stdDeviation) - 3.0;
		}

		return kurtosis;
	}

	private double calculateMax(Matrix matrix, int col) {
		double max = Double.NEGATIVE_INFINITY;

		for (int r = 0; r < matrix.getRows(); r++) {
			if (!Double.isNaN(matrix.get(r, col))) {
				if (matrix.get(r, col) > max) {
					max = matrix.get(r, col);
				}
			}
		}

		return max;
	}

	private double calculateMean(Matrix matrix, int col) {
		double sum = calculateSum(matrix, col);
		double mean = Double.NaN;
		if (matrix.getRows() > 0) {
			mean = sum / matrix.getRows();
		}

		return mean;
	}

	private double calculateMedian(Matrix matrix, int col) {
		double[] data = new double[matrix.getRows()];

		for (int r = 0; r < matrix.getRows(); r++) {
			data[r] = matrix.get(r, col);
		}

		return DataUtilities.median(data);
	}

	private double calculateMin(Matrix matrix, int col) {
		double min = Double.POSITIVE_INFINITY;

		for (int r = 0; r < matrix.getRows(); r++) {
			if (!Double.isNaN(matrix.get(r, col))) {
				if (matrix.get(r, col) < min) {
					min = matrix.get(r, col);
				}
			}
		}

		return min;
	}

	private double calculateRange(Matrix matrix, int col) {
		return calculateMax(matrix, col) - calculateMin(matrix, col);
	}

	private double calculateSkewness(Matrix matrix, int col) {
		double skewness = Double.NaN;

		if (matrix.getRows() > 0) {
			double variance = 0;
			double stdDeviation = 0;
			double err = 0;
			skewness = 0;

			for (int r = 0; r < matrix.getRows(); r++) {
				if (!Double.isNaN(matrix.get(r, col))) {
					double dif = matrix.get(r, col) - calculateMean(matrix, col);
					err += Math.abs(dif);
					variance += dif * dif;
					stdDeviation += dif * dif * dif;
					skewness += dif * dif * dif;
				}
			}

			err = err / matrix.getRows();
			int nn = matrix.getRows();
			if (matrix.getRows() == 1) {
				nn = 2;
			}

			variance = variance / (nn - 1);
			stdDeviation = Math.sqrt(variance);
			skewness = skewness / (matrix.getRows() * stdDeviation * stdDeviation * stdDeviation);
		}

		return skewness;
	}

	private double calculateStdDeviation(Matrix matrix, int col) {
		double stdDeviation = Double.NaN;

		if (matrix.getRows() > 0) {
			double variance = 0;
			double err = 0;
			stdDeviation = 0;

			for (int r = 0; r < matrix.getRows(); r++) {
				if (!Double.isNaN(matrix.get(r, col))) {
					double dif = matrix.get(r, col) - calculateMean(matrix, col);
					err += Math.abs(dif);
					variance += dif * dif;
					stdDeviation += dif * dif * dif;
				}
			}

			err = err / matrix.getRows();
			int nn = matrix.getRows();
			if (matrix.getRows() == 1) {
				nn = 2;
			}

			variance = variance / (nn - 1);
			stdDeviation = Math.sqrt(variance);
		}

		return stdDeviation;
	}

	private double calculateSum(Matrix matrix, int col) {
		double sum = 0.0;

		for (int r = 0; r < matrix.getRows(); r++) {
			sum += matrix.get(r, col);
		}

		return sum;
	}

	private double calculateVariance(Matrix matrix, int col) {
		double variance = Double.NaN;

		if (matrix.getRows() > 0) {
			double err = 0;
			variance = 0;

			for (int r = 0; r < matrix.getRows(); r++) {
				if (!Double.isNaN(matrix.get(r, col))) {
					double dif = matrix.get(r, col) - calculateMean(matrix, col);
					err += Math.abs(dif);
					variance += dif * dif;
				}
			}

			err = err / matrix.getRows();
			int nn = matrix.getRows();
			if (matrix.getRows() == 1) {
				nn = 2;
			}

			variance = variance / (nn - 1);
		}

		return variance;
	}

	private Matrix cloneMatrix(Matrix matrix) {
		Matrix ret = Matlib.createMatrix(matrix.getRows(), matrix.getCols());

		for (int r = 0; r < matrix.getRows(); r++) {
			for (int c = 0; c < matrix.getCols(); c++) {
				ret.set(r, c, matrix.get(r, c));
			}
		}

		return ret;
	}

	private DataSeriesFileFormat createDataSeriesFileFormat(int cols, boolean addDateColumn) {
		DataSeriesFileFormat format = new DataSeriesFileFormat();

		format.setTagLine(0);
		format.setNameLine(1);
		format.setUnitLine(2);
		format.setIgnoredRows(new int[0]);
		format.setIgnoredColumns(new int[0]);
		format.setColumns(cols);
		format.setSeparator(TAB_SEPARATOR);

		if (addDateColumn) {
			format.setDateColumn(0);
		}

		return format;
	}

	private String createDsFileName(DataSeries dataSeries) throws IOException {
		File file = temporaryFolder.newFile("DataSeries.bds");

		dataSeries.setComment("Data Series Common");
		dataSeries.setTimeStamps(createTimeStamps(dataSeries.getDataMatrix().getRows()));

		FileOutputStream fos = new FileOutputStream(file);
		GZIPOutputStream gzos = new GZIPOutputStream(fos);
		ObjectOutputStream oos = null;
		try {
			oos = new ObjectOutputStream(gzos);
			VersionManagerForDataSeries versionForData = new VersionManagerForDataSeries();
			versionForData.setDataSeries(dataSeries);
			oos.writeObject(versionForData);
		} catch (Exception ex) {
			fail("Failed to create DataSeries object file.");
		} finally {
			if (oos != null) {
				oos.close();
			}
		}

		return file.getAbsolutePath();
	}

	private File createDsFile(Vector<Vector<String>> fileLines) throws IOException {
		String fileContent = getDsFileContent(fileLines);
		StringBuilder sb = new StringBuilder();

		String[] lines = fileContent.split("\\n");
		for (int idx = 0; idx < lines.length; idx++) {
			String line = lines[idx];
			if (line.startsWith(TAB_SEPARATOR)) {
				line = line.substring(1, line.length());
			}

			if (line.endsWith(TAB_SEPARATOR)) {
				line = line.substring(0, line.length() - 1);
			}

			sb.append(line);
			if (idx < lines.length - 1) {
				sb.append(NEW_LINE);
			}
		}

		return createFile(sb.toString());
	}

	private String createDsFileName(Vector<Vector<String>> fileLines) throws IOException {
		return createDsFileName(fileLines, "DataSeriesFile.ds");
	}

	private String createDsFileName(Vector<Vector<String>> fileLines, String fileName) throws IOException {
		File file = temporaryFolder.newFile(fileName);

		FileOutputStream fileStream= null;
		OutputStreamWriter streamWriter = null;
		BufferedWriter bWriter = null;
		try {
			fileStream = new FileOutputStream(file);
			streamWriter = new OutputStreamWriter(fileStream, Charset.defaultCharset());
			bWriter = new BufferedWriter(streamWriter);
			bWriter.write(getDsFileContent(fileLines));
		} catch (Exception ex) {
			fail("Failed to create DataSeries file.");
		} finally {
			closeSilently(bWriter);
			closeSilently(streamWriter);
			closeSilently(fileStream);
		}

		return file.getAbsolutePath();
	}

	private File createEmptyFile() throws IOException {
		return createEmptyFile("File.tmp");
	}

	private File createEmptyFile(String filename) throws IOException {
		return temporaryFolder.newFile(filename);
	}

	private File createFile(String content) throws IOException {
		File file = temporaryFolder.newFile("DataSeries");
		FileOutputStream fileStream= null;
		OutputStreamWriter streamWriter = null;
		BufferedWriter writer = null;
		try {
			fileStream = new FileOutputStream(file);
			streamWriter = new OutputStreamWriter(fileStream, Charset.defaultCharset());
			writer = new BufferedWriter(streamWriter);
			writer.write(content);
		} catch (Exception ex) {
			fail("Failed to create file.");
		} finally {
			closeSilently(writer);
			closeSilently(streamWriter);
			closeSilently(fileStream);
		}

		return file;
	}

	private Matrix createMatrix() {
		return createMatrix(2, 3, true);
	}

	private Matrix createMatrix(boolean isValid) {
		return createMatrix(2, 3, isValid);
	}

	private Matrix createMatrix(int rows, int cols) {
		return createMatrix(rows, cols, true);
	}

	private Matrix createMatrix(int rows, int cols, boolean isValid) {
		Matrix matrix = Matlib.createMatrix(rows, cols);

		for (int r = 0; r < matrix.getRows(); r++) {
			for (int c = 0; c < matrix.getCols(); c++) {
				if (isValid) {
					matrix.set(r, c, randomGenerator.nextDouble());
				} else {
					matrix.set(r, c, Double.NaN);
				}
			}
		}

		return matrix;
	}

	private String createMatrixFile(Matrix matrix) throws IOException {
		File file = temporaryFolder.newFile("DataSeries.matrix");

		FileOutputStream fileStream= null;
		OutputStreamWriter streamWriter = null;
		BufferedWriter writer = null;
		try {
			fileStream = new FileOutputStream(file);
			streamWriter = new OutputStreamWriter(fileStream, Charset.defaultCharset());
			writer = new BufferedWriter(streamWriter);
			writer.write(getDsFileContent(matrix));
		} catch (Exception ex) {
			fail("Failed to create Matrix file.");
		} finally {
			closeSilently(writer);
			closeSilently(streamWriter);
			closeSilently(fileStream);
		}

		return file.getAbsolutePath();
	}

	private long[] createNextTimeStamps(int length, long oldTimeStamp) {
		long[] timeStamps = new long[length];
		for (int idx = 0; idx < length; idx++) {
			timeStamps[idx] = oldTimeStamp + idx + 1;
		}
		return timeStamps;
	}

	private ProgressListener createProgressListener() {
		ProgressListener progressListener = mock(ProgressListener.class);
		return progressListener;
	}

	private Preprocessor createPreprocessor() {
		return createPreprocessor("Preprocessor Name");
	}

	private Preprocessor createPreprocessor(String name) {
		Preprocessor preprocessor = mock(Preprocessor.class);
		PowerMockito.when(preprocessor.getName()).thenReturn(name);
		PowerMockito.when(preprocessor.getItsHashCode()).thenReturn(preprocessor.hashCode());
		return preprocessor;
	}

	private Project createProject() {
		Project project = mock(Project.class);
		return project;
	}

	private RawDataSource createRawDataSource() {
		return createRawDataSource("Raw DataSource Name");
	}

	private RawDataSource createRawDataSource(String dataSourceName) {
		RawDataSource dataSource = mock(RawDataSource.class);
		PowerMockito.when(dataSource.getName()).thenReturn(dataSourceName);
		return dataSource;
	}

	private DataSeries createSut(Matrix matrix) throws MathException {
		return createSut(matrix, true);
	}

	private DataSeries createSut(Matrix matrix, boolean hasTimeStamps) throws MathException {
		DataSeries dataSeries = new DataSeries(matrix);
		dataSeries.setName("Data Series Name");
		dataSeries.setComment("Data Series Comments");

		RawDataSource dataSource = createRawDataSource();
		dataSeries.setDataSource(dataSource);

		if (hasTimeStamps) {
			dataSeries.setTimeStamps(createTimeStamps(matrix.getRows()));
		}

		return dataSeries;
	}

	private DataSeries createSut() throws MathException {
		return createSut(true);
	}

	private DataSeries createSut(boolean hasTimeStamps) throws MathException {
		Matrix matrix = createMatrix();
		return createSut(matrix, hasTimeStamps);
	}

	private long[] createTimeStamps(int length) {
		return createTimeStamps(length, System.currentTimeMillis());
	}

	private long[] createTimeStamps(int length, long base) {
		long[] timeStamps = new long[length];
		for (int idx = 0; idx < length; idx++) {
			timeStamps[idx] = base + (idx * TIMESTAMPS_INTERVAL);
		}

		return timeStamps;
	}

	private URL createUrl(Matrix matrix) throws MalformedURLException, IOException {
		return new File(createMatrixFile(matrix)).toURI().toURL();
	}

	private URL createUrl(Vector<Vector<String>> fileLines) throws MalformedURLException, IOException {
		return new File(createDsFileName(fileLines)).toURI().toURL();
	}

	private URL createUrl(Vector<Vector<String>> fileLines, String fileName) throws MalformedURLException, IOException {
		return new File(createDsFileName(fileLines, fileName)).toURI().toURL();
	}

	private URL createUrlWithoutLeadingAndTrailingSeparators(Vector<Vector<String>> fileLines) throws IOException {
		String fileContent = getDsFileContent(fileLines);
		StringBuilder sb = new StringBuilder();

		String[] lines = fileContent.split("\\n");
		for (int idx = 0; idx < lines.length; idx++) {
			String line = lines[idx];
			if (line.startsWith(TAB_SEPARATOR)) {
				line = line.substring(1, line.length());
			}

			if (line.endsWith(TAB_SEPARATOR)) {
				line = line.substring(0, line.length() - 1);
			}

			sb.append(line);
			if (idx < lines.length - 1) {
				sb.append(NEW_LINE);
			}
		}

		return createFile(sb.toString()).toURI().toURL();
	}

	private Vector<Vector<String>> createVariableSpecsLines(int varNumbers, boolean containsTimeStamps) {
		Vector<Vector<String>> fileLines = new Vector<Vector<String>>();

		fileLines.add(new Vector<String>());
		fileLines.add(new Vector<String>());
		fileLines.add(new Vector<String>());

		if (containsTimeStamps) {
			fileLines.get(NAME_ROW_INDEX).add(TIME_TAG);
			fileLines.get(TAG_ROW_INDEX).add(TIME_TAG);
			fileLines.get(UNIT_ROW_INDEX).add(TIME_UNIT);
		}

		for (int idx = 0; idx < varNumbers; idx++) {
			fileLines.get(NAME_ROW_INDEX).add(VARIABLE_NEW_NAME_PREFIX + (idx + 1));
		}

		for (int idx = 0; idx < varNumbers; idx++) {
			fileLines.get(TAG_ROW_INDEX).add(VARIABLE_NEW_TAG_PREFIX + (idx + 1));
		}

		for (int idx = 0; idx < varNumbers; idx++) {
			fileLines.get(UNIT_ROW_INDEX).add(VARIABLE_NEW_UNIT_PREFIX + (idx + 1));
		}

		return fileLines;
	}

	private DataSeries fetchDataSeries(File file) throws IOException {
		DataSeries dataSeries = null;
		FileInputStream fis = null;
		GZIPInputStream gzis = null;
		ObjectInputStream in = null;

		try {
			fis = new FileInputStream(file);
			gzis = new GZIPInputStream(fis);
			in = new ObjectInputStream(gzis);

			dataSeries = (DataSeries) in.readObject();
		} catch (Exception ex) {
			fail("Failed to fetch DataSeries object.");
		} finally {
			if (in != null) {
				in.close();
			}
		}

		return dataSeries;
	}

	private String getDsFileContent(Vector<Vector<String>> fileLines) {
		StringBuilder sb = new StringBuilder();

		// Adding header rows
		if (fileLines.size() > 0) {
			for (int lineIdx = 0; lineIdx < 3; lineIdx++) {
				Vector<String> line = fileLines.get(lineIdx);
				for (int valueIdx = 0; valueIdx < line.size(); valueIdx++) {
					sb.append(TAB_SEPARATOR);
					sb.append(line.get(valueIdx));
				}

				sb.append(TAB_SEPARATOR);
				sb.append(NEW_LINE);
			}
		}

		// Adding time stamps rows if any
		if (fileLines.size() > 3) {
			for (int lineIdx = 3; lineIdx < fileLines.size(); lineIdx++) {
				Vector<String> line = fileLines.get(lineIdx);
				for (int valueIdx = 0; valueIdx < line.size(); valueIdx++) {
					sb.append(line.get(valueIdx));

					if (valueIdx < line.size() - 1) {
						sb.append(TAB_SEPARATOR);
					}
				}

				sb.append(NEW_LINE);
			}
		}

		return sb.toString();
	}

	private String getDsFileContent(Matrix matrix) {
		StringBuilder sb = new StringBuilder();

		for (int r = 0; r < matrix.getRows(); r++) {
			for (int c = 0; c < matrix.getCols(); c++) {
				sb.append(matrix.get(r, c));
				sb.append(TAB_SEPARATOR);
			}

			sb.append(NEW_LINE);
		}

		return sb.toString();
	}
	
	private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println("NON-FATAL exception: Error while closing stream : " + e.getMessage());
      } 
    }

	private String getVariableNames(DataSeries sut, String separator) {
		StringBuilder sb = new StringBuilder();

		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			sb.append(sut.getVarByIndex(idx).getName());
			if (idx < sut.getDataMatrix().getCols() - 1) {
				sb.append(separator);
			}
		}

		return sb.toString();
	}

	private String getVariableTags(DataSeries sut, String separator) {
		StringBuilder sb = new StringBuilder();

		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			sb.append(sut.getVarByIndex(idx).getTag());
			if (idx < sut.getDataMatrix().getCols() - 1) {
				sb.append(separator);
			}
		}

		return sb.toString();
	}

	private String getVariableUnits(DataSeries sut, String separator) {
		StringBuilder sb = new StringBuilder();

		for (int idx = 0; idx < sut.getDataMatrix().getCols(); idx++) {
			sb.append(sut.getVarByIndex(idx).getUnit());
			if (idx < sut.getDataMatrix().getCols() - 1) {
				sb.append(separator);
			}
		}
		return sb.toString();
	}

	private void setVariables(DataSeries dataSeries) throws MathException {
		for (int idx = 0; idx < dataSeries.getDataMatrix().getCols(); idx++) {
			dataSeries.setVariableParameters(idx, "varTag" + (idx + 1), "varName" + (idx + 1), "varUnit" + (idx + 1));
		}
	}

	private void updatePreprocessor(Preprocessor preprocessor, String name) {
		PowerMockito.when(preprocessor.getName()).thenReturn(name);
	}

	private void updateVariableHardBounds(DataSeries sut) {
		for (int idx = 0; idx < sut.getVarObjects().size(); idx++) {
			Variable variable = sut.getVarByIndex(idx);
			variable.setHardLowerBound(randomGenerator.nextDouble());
			variable.setHardUpperBound(variable.getHardLowerBound() + 10);
		}
	}
}
