package com.gensym.nols.data;

import static org.hamcrest.CoreMatchers.allOf;
import static org.hamcrest.CoreMatchers.containsString;
import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.CoreMatchers.hasItem;
import static org.hamcrest.CoreMatchers.hasItems;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.CoreMatchers.not;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.junit.Assert.assertTrue;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class DataSeriesFileFormatTest {
	private final int nonZeroValue = 10;
	private final double aDouble = 25;
	private final double anotherDouble = 1000;

	private DataSeriesFileFormat sut;
	private double[] data;
	private Object symbolConversion;
	private SimpleDateFormat dateFormat;
	private SimpleDateFormat dateTimeFormat;
	private SimpleDateFormat timeFormat;
	private String symbol;
	private String tokensToReadDataLine;
	private String tokensToReadNonDataLine;
	private String[] subStrings;
	private Vector<Vector<Object>> symbols;

	@Before
	public void setup() {
		dateTimeFormat = new SimpleDateFormat("dd/MM/yyyy hh:mm:ss");
		dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		timeFormat = new SimpleDateFormat("hh:mm:ss");
		symbolConversion = new Double(100.0);

		sut = new DataSeriesFileFormat();
	}

	@Test
	public void test_constructorWithName_Always_SetsName() {
		// Arrange
		String name = "Data Series Name";

		// Act
		sut = new DataSeriesFileFormat(name);

		// Assert
		assertThat(sut.getName(), is(equalTo(name)));
	}

	@Test
	public void test_getComment_Always_ReturnsPreviouslySetComment() {
		// Arrange
		String comment = "New Comment";
		sut.setComment(comment);

		// Act & Assert
		assertThat(sut.getComment(), is(equalTo(comment)));
	}

	@Test
	public void test_getDateTimeFormat_Always_ReturnsPreviouslySetDateTimeFormat() {
		// Arrange
		sut.setDateTimeFormat(dateTimeFormat);

		// Act & Assert
		assertThat(sut.getDateTimeFormat(), is(equalTo(dateTimeFormat)));
	}

	@Test
	public void test_getDateFormat_Always_ReturnsPreviouslySetDateFormat() {
		// Arrange
		sut.setDateFormat(dateFormat);

		// Act & Assert
		assertThat(sut.getDateFormat(), is(equalTo(dateFormat)));
	}

	@Test
	public void test_getTimeFormat_Always_ReturnsPreviouslySetTimeFormat() {
		// Arrange
		sut.setTimeFormat(timeFormat);

		// Act & Assert
		assertThat(sut.getTimeFormat(), is(equalTo(timeFormat)));
	}

	@Test
	public void test_getSuffix_Always_ReturnsPreviouslySetSuffix() {
		// Arrange
		String suffix = "Data Series Time";
		sut.setSuffix(suffix);

		// Act & Assert
		assertThat(sut.getSuffix(), is(equalTo(suffix)));
	}

	@Test
	public void test_getSeparator_Always_ReturnsPreviouslySetSeparator() {
		// Arrange
		String separator = "|";
		sut.setSeparator(separator);

		// Act & Assert
		assertThat(sut.getSeparator(), is(equalTo(separator)));
	}

	@Test
	public void test_getColumns_Always_ReturnsPreviouslySetColumns() {
		// Arrange
		int column = 10;
		sut.setColumns(column);

		// Act & Assert
		assertThat(sut.getColumns(), is(equalTo(column)));
	}

	@Test
	public void test_getTagLine_Always_ReturnsPreviouslySetTagLine() {
		// Arrange
		int tagline = 20;
		sut.setTagLine(tagline);

		// Act & Assert
		assertThat(sut.getTagLine(), is(equalTo(tagline)));
	}

	@Test
	public void test_getNameLine_Always_ReturnsPreviouslySetNameLine() {
		// Arrange
		int nameline = 30;
		sut.setNameLine(nameline);

		// Act & Assert
		assertThat(sut.getNameLine(), is(equalTo(nameline)));
	}

	@Test
	public void test_getUnitLine_Always_ReturnsPreviouslySetUnitLine() {
		// Arrange
		int unitLine = 40;
		sut.setUnitLine(unitLine);

		// Act & Assert
		assertThat(sut.getUnitLine(), is(equalTo(unitLine)));
	}

	@Test
	public void test_getDateTimeColumn_Always_ReturnsPreviouslySetDateTimeColumn() {
		// Arrange
		int dateTimeColumn = 50;
		sut.setDateTimeColumn(dateTimeColumn);

		// Act & Assert
		assertThat(sut.getDateTimeColumn(), is(equalTo(dateTimeColumn)));
	}

	@Test
	public void test_getDateColumn_Always_ReturnsPreviouslySetDateColumn() {
		// Arrange
		int dateColumn = 60;
		sut.setDateColumn(dateColumn);

		// Act & Assert
		assertThat(sut.getDateColumn(), is(equalTo(dateColumn)));
	}

	@Test
	public void test_getTimeColumn_Always_ReturnsPreviouslySetTimeColumn() {
		// Arrange
		int timeColumn = 70;
		sut.setTimeColumn(timeColumn);

		// Act & Assert
		assertThat(sut.getTimeColumn(), is(equalTo(timeColumn)));
	}

	@Test
	public void test_getIgnoredColumns_Always_ReturnsPreviouslySetIgnoredColumns() {
		// Arrange
		int columnsCount = 5;
		int[] ignoredColumns = new int[] { -1, 1, -1, 3, -1 };
		sut.setColumns(columnsCount);
		sut.setIgnoredColumns(ignoredColumns);

		// Act
		int[] result = sut.getIgnoredColumns();

		// Assert
		assertThat(result, is(equalTo(ignoredColumns)));
	}

	@Test
	public void test_getIgnoredRows_Always_ReturnsPreviouslySetIgnoredRows() {
		// Arrange
		int[] ignoredRows = new int[] { 0, 1, 0, 1, 0 };
		sut.setIgnoredRows(ignoredRows);

		// Act
		int[] result = sut.getIgnoredRows();

		// Assert
		assertThat(result, is(equalTo(ignoredRows)));
	}

	@Test
	public void test_getSymbols_Always_ReturnsPreviouslySetSymbols() {
		// Arrange
		Vector<String> symbols = new Vector<String>();
		symbols.addElement("Symbol 1");
		sut.setSymbols(symbols);

		// Act & Assert
		assertThat(sut.getSymbols(), is(equalTo(symbols)));
	}

	@Test
	public void test_getName_Always_ReturnsPreviouslySetName() {
		// Arrange
		String name = "File Format Name";
		sut.setName(name);

		// Act & Assert
		assertThat(sut.getName(), is(equalTo(name)));
	}

	@Test
	public void test_getDecimalFormatLocalString_Always_ReturnsPreviouslySetDecimalFormatLocalString() {
		// Arrange
		String decimalFormatLocalString = "en-US";
		sut.setDecimalFormatLocalString(decimalFormatLocalString);

		// Act & Assert
		assertThat(sut.getDecimalFormatLocalString(), is(equalTo(decimalFormatLocalString)));
	}

	@Test
	public void test_getDataColumn_DateAndTimeAndDateTimeColumnsAreNotSet_ReturnsCorrectDataColumn() {
		// Arrange
		int columns = 100;
		int[] ignoredColumns = new int[] { 0, 0, 0 };
		sut.setColumns(columns);
		sut.setIgnoredColumns(ignoredColumns);

		// Act & Assert
		assertThat(sut.getDataColumn(), is(equalTo(columns - ignoredColumns.length)));
	}

	@Test
	public void test_getDataColumn_DateTimeColumnIsSet_ReturnsCorrectDataColumn() {
		// Arrange
		int columns = 100;
		int[] ignoredColumns = new int[] { 0, 0, 0 };
		sut.setColumns(columns);
		sut.setIgnoredColumns(ignoredColumns);
		sut.setDateTimeColumn(nonZeroValue);

		// Act & Assert
		assertThat(sut.getDataColumn(), is(equalTo(columns - ignoredColumns.length - 1)));
	}

	@Test
	public void test_getDataColumn_DateColumnIsSet_ReturnsCorrectDataColumn() {
		// Arrange
		int columns = 100;
		int[] ignoredColumns = new int[] { 0, 0, 0 };
		sut.setColumns(columns);
		sut.setIgnoredColumns(ignoredColumns);
		sut.setDateColumn(nonZeroValue);

		// Act & Assert
		assertThat(sut.getDataColumn(), is(equalTo(columns - ignoredColumns.length - 1)));
	}

	@Test
	public void test_getDataColumn_TimeColumnIsSet_ReturnsCorrectDataColumn() {
		// Arrange
		int columns = 100;
		int[] ignoredColumns = new int[] { 0, 0, 0 };
		sut.setColumns(columns);
		sut.setIgnoredColumns(ignoredColumns);
		sut.setTimeColumn(nonZeroValue);

		// Act & Assert
		assertThat(sut.getDataColumn(), is(equalTo(columns - ignoredColumns.length - 1)));
	}

	@Test
	public void test_getDataColumn_DateAndTimeColumnsAreSet_ReturnsCorrectDataColumn() {
		// Arrange
		int columns = 100;
		int[] ignoredColumns = new int[] { 0, 0, 0 };
		sut.setColumns(columns);
		sut.setIgnoredColumns(ignoredColumns);
		sut.setDateColumn(nonZeroValue);
		sut.setTimeColumn(nonZeroValue);

		// Act & Assert
		assertThat(sut.getDataColumn(), is(equalTo(columns - ignoredColumns.length - 2)));
	}

	@Test
	public void test_getCount_ValidStringIsPassed_ReturnsCorrectCount() {
		// Arrange
		String tokens = " A | B | C | D | E ";
		sut.setSeparator("|");

		// Act & Assert
		assertThat(sut.getCount(tokens), is(equalTo(5)));
	}

	@Test
	public void test_getCount_TwoSeparatorsArePlaced_ReturnsCountUntilBreak() {
		// Arrange
		String tokensIncludingEmptyStringBetweenTwoSeparators = " A | B |  | D | E ";
		sut.setSeparator("|");

		// Act & Assert
		assertThat(sut.getCount(tokensIncludingEmptyStringBetweenTwoSeparators), is(equalTo(3)));
	}

	@Test
	public void test_getCount_EmptyStringIsPassed_ReturnsOne() {
		// Arrange
		String emptyString = "";
		sut.setSeparator("|");

		// Act & Assert
		assertThat(sut.getCount(emptyString), is(equalTo(1)));
	}

	@Test
	public void test_getCount_OnlySeparatorIsPassed_ReturnsOne() {
		// Arrange
		String emptyDataWithOnlyOneSeparator = "|";
		sut.setSeparator("|");

		// Act & Assert
		assertThat(sut.getCount(emptyDataWithOnlyOneSeparator), is(equalTo(1)));
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_readNonDataLine_ColumnsCountIsDifferentThanTokensCount_ThrowsMathException() throws MathException {
		// Arrange
		// Tokens count: 5, columns count 4.
		String moreTokensThanColumnsCount = " A | B | C | D | E ";
		sut.setSeparator("|");
		sut.setColumns(4);
		String[] subStrings = new String[0];

		// Act
		sut.readNonDataLine(moreTokensThanColumnsCount, subStrings);
	}

	@Test
	public void test_readNonDataLine_ColumnsCountIsSameAsTokens_SubStringsContainNonData() throws MathException {
		// Arrange
		arrangeForReadNonDataLine();

		// Act
		sut.readNonDataLine(tokensToReadNonDataLine, subStrings);

		// Assert
		assertThat(Arrays.asList(subStrings), hasItems("Non Data 1", "Non Data 2"));
	}

	@Test
	public void test_readNonDataLine_ColumnsCountIsSameAsTokens_SubStringsDoNotContainData() throws MathException {
		// Arrange
		arrangeForReadNonDataLine();

		// Act
		sut.readNonDataLine(tokensToReadNonDataLine, subStrings);

		// Assert
		assertThat(Arrays.asList(subStrings),
				allOf(not(hasItem("01/01/2016 05:00")), not(hasItem("01/01/2016")), not(hasItem("05:00"))));
	}

	@Test
	public void test_readDataLine_DateTimeColumnIsSet_ReturnsCorrectMilliseconds()
			throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		sut.setDateTimeColumn(0);
		long expected = dateTimeFormat.parse("01/01/2016 05:00:30").getTime();

		// Act & Assert
		assertThat(sut.readDataLine(tokensToReadDataLine, data), is(equalTo(expected)));
	}

	@Test
	public void test_readDataLine_DateAndTimeColumnsAreSet_ReturnsCorrectMilliseconds()
			throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		sut.setDateColumn(1);
		sut.setTimeColumn(2);
		long expected = dateTimeFormat.parse("01/01/2016 05:00:30").getTime();

		// Act & Assert
		assertThat(sut.readDataLine(tokensToReadDataLine, data), is(equalTo(expected)));
	}

	@Test
	public void test_readDataLine_TokensAreMoreThanColumns_ReturnsCorrectMilliseconds()
			throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		// Tokens count: 6, columns count 5.
		String moreTokensThanColumnsCount = tokensToReadDataLine + " | 1000 ";
		sut.setDateTimeColumn(0);
		long expected = dateTimeFormat.parse("01/01/2016 05:00:30").getTime();

		// Act & Assert
		assertThat(sut.readDataLine(moreTokensThanColumnsCount, data), is(equalTo(expected)));
	}

	@Test
	public void test_readDataLine_TokensAreLessThanColumns_ReturnsCorrectMilliseconds()
			throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		// Tokens count: 3, columns count 5.
		String lessTokensThanColumnsCount = " 01/01/2016 05:00:30 | 01/01/2016 | 05:00:30";
		sut.setDateTimeColumn(0);
		long expected = dateTimeFormat.parse("01/01/2016 05:00:30").getTime();

		// Act & Assert
		assertThat(sut.readDataLine(lessTokensThanColumnsCount, data), is(equalTo(expected)));
	}

	@Test
	public void test_readDataLine_DateTimeStringIsEmpty_ReturnsMinusTwo() throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		String tokensWithEmptyDateTimeString = "  | 01/01/2016 | 05:00:30";
		sut.setDateTimeColumn(0);

		// Act & Assert
		assertThat(sut.readDataLine(tokensWithEmptyDateTimeString, data), is(equalTo(-2L)));
	}

	@Test
	public void test_readDataLine_DateStringIsEmpty_ReturnsMinusTwo() throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		String tokensWithEmptyDateString = " 01/01/2016 05:00:30 |  | 05:00:30";
		sut.setDateColumn(1);
		sut.setTimeColumn(2);

		// Act & Assert
		assertThat(sut.readDataLine(tokensWithEmptyDateString, data), is(equalTo(-2L)));
	}

	@Test
	public void test_readDataLine_TimeStringIsEmpty_ReturnsMinusTwo() throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		String tokensWithEmptyTimeString = " 01/01/2016 05:00:30 | 01/01/2016 | ";
		sut.setDateColumn(1);
		sut.setTimeColumn(2);

		// Act & Assert
		assertThat(sut.readDataLine(tokensWithEmptyTimeString, data), is(equalTo(-2L)));
	}

	@Test
	public void test_readDataLine_DateTimeStringIsInvalid_ReturnsMinusOne() throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		String tokensWithInvalidDateTimeString = " Invalid Date Time | 01/01/2016 | 05:00:30";
		sut.setDateTimeColumn(0);

		// Act & Assert
		assertThat(sut.readDataLine(tokensWithInvalidDateTimeString, data), is(equalTo(-1L)));
	}

	@Test
	public void test_readDataLine_DateStringIsInvalid_ReturnsMinusOne() throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		String tokensWithInvalidDateString = " 01/01/2016 05:00:30 | Invalid Date | 05:00:30";
		sut.setDateColumn(1);
		sut.setTimeColumn(2);

		// Act & Assert
		assertThat(sut.readDataLine(tokensWithInvalidDateString, data), is(equalTo(-1L)));
	}

	@Test
	public void test_readDataLine_TimeStringIsInvalid_ReturnsMinusOne() throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		String tokensWithInvalidTimeString = " 01/01/2016 05:00:30 | 01/01/2016 | Invalid Time";
		sut.setDateColumn(1);
		sut.setTimeColumn(2);

		// Act & Assert
		assertThat(sut.readDataLine(tokensWithInvalidTimeString, data), is(equalTo(-1L)));
	}

	@Test
	public void test_readDataLine_StringContainsDoubles_AddsDoubleValuesToData() throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		sut.setDateTimeColumn(0);

		// Act
		sut.readDataLine(tokensToReadDataLine, data);

		// Assert
		assertTrue(arrayContains(data, aDouble));
		assertTrue(arrayContains(data, anotherDouble));
	}

	@Test
	public void test_readDataLine_StringContainsDoubleFromSymbols_AddsDoubleValuesToData()
			throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		sut.setDateTimeColumn(0);
		sut.setSymbols(symbols);
		String tokensContainsDoubleFromSymbols = " 01/01/2016 05:00:30 | " + symbol;

		// Act
		sut.readDataLine(tokensContainsDoubleFromSymbols, data);

		// Assert
		assertTrue(arrayContains(data, ((Double) symbolConversion).doubleValue()));
	}

	@Test
	public void test_readDataLine_StringContainsStringFromSymbols_ReturnsMinusTwo()
			throws MathException, ParseException {
		// Arrange
		symbolConversion = "Symbol Conversion";
		arrangeForReadDataLine();
		sut.setDateTimeColumn(0);
		sut.setSymbols(symbols);
		String tokensContainsStringFromSymbols = " 01/01/2016 05:00:30 | " + symbol;

		// Act & Assert
		assertThat(sut.readDataLine(tokensContainsStringFromSymbols, data), is(equalTo(-2L)));
	}

	@Test
	public void test_readDataLine_FormatStringIsNotEnglishAndStringContainsDoubles_AddsDoubleValuesToData()
			throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();
		sut.setDecimalFormatLocalString("en-US");
		sut.setDateTimeColumn(0);

		// Act
		sut.readDataLine(tokensToReadDataLine, data);

		// Assert
		assertTrue(arrayContains(data, aDouble));
		assertTrue(arrayContains(data, anotherDouble));
	}

	@Test
	public void test_readDataLine_FormatStringIsNotEnglishAndStringContainsDoubleFromSymbols_AddsDoubleValuesToData()
			throws MathException, ParseException {
		// Arrange
		sut.setDecimalFormatLocalString("en-US");
		arrangeForReadDataLine();
		sut.setDateTimeColumn(0);
		sut.setSymbols(symbols);
		String tokensContainsDoubleFromSymbols = " 01/01/2016 05:00:30 | " + symbol;

		// Act
		sut.readDataLine(tokensContainsDoubleFromSymbols, data);

		// Assert
		assertTrue(arrayContains(data, ((Double) symbolConversion).doubleValue()));
	}

	@Test
	public void test_readDataLine_FormatStringIsNotEnglishAndStringContainsStringFromSymbols_ReturnsMinusTwo()
			throws MathException, ParseException {
		// Arrange
		sut.setDecimalFormatLocalString("en-US");
		symbolConversion = "Symbol Conversion";
		arrangeForReadDataLine();
		sut.setDateTimeColumn(0);
		sut.setSymbols(symbols);
		String tokensContainsStringFromSymbols = " 01/01/2016 05:00:30 | " + symbol;

		// Act & Assert
		assertThat(sut.readDataLine(tokensContainsStringFromSymbols, data), is(equalTo(-2L)));
	}

	@Test
	public void test_readDataLine_DateTimeAndDateAndTimeColumnsAreNotSet_ReturnsMinusTwo()
			throws MathException, ParseException {
		// Arrange
		arrangeForReadDataLine();

		// Act & Assert
		assertThat(sut.readDataLine(tokensToReadDataLine, data), is(equalTo(-2L)));
	}

	@Test
	public void test_toString_Always_ReturnsName() {
		// Arrange
		String name = "Data Series File Format";
		sut.setName(name);

		// Act & Assert
		assertThat(sut.toString(), is(equalTo(name)));
	}

	@Test
	public void test_toStringForTest_Always_ContainsSuffix() {
		// Arrange
		String suffix = "Data Series Time";
		sut.setSuffix(suffix);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("suffix: " + suffix));
	}

	@Test
	public void test_toStringForTest_Always_ContainsSeparator() {
		// Arrange
		String separator = "|";
		sut.setSeparator(separator);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("Separater: " + separator));
	}

	@Test
	public void test_toStringForTest_Always_ContainsColumn() {
		// Arrange
		int column = 10;
		sut.setColumns(column);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("Column: " + column));
	}

	@Test
	public void test_toStringForTest_Always_ContainsTagLine() {
		// Arrange
		int tagline = 20;
		sut.setTagLine(tagline);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("tagLine: " + tagline));
	}

	@Test
	public void test_toStringForTest_Always_ContainsNameLine() {
		// Arrange
		int nameline = 30;
		sut.setNameLine(nameline);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("nameLine: " + nameline));
	}

	@Test
	public void test_toStringForTest_Always_ContainsUnitLine() {
		// Arrange
		int unitline = 30;
		sut.setUnitLine(unitline);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("unitLine: " + unitline));
	}

	@Test
	public void test_toStringForTest_Always_ContainsDateTimeColumn() {
		// Arrange
		int dateTimeColumn = 50;
		sut.setDateTimeColumn(dateTimeColumn);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("dateTimeColumn: " + dateTimeColumn));
	}

	@Test
	public void test_toStringForTest_Always_ContainsDateColumn() {
		// Arrange
		int dateColumn = 60;
		sut.setDateColumn(dateColumn);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("dateColumn: " + dateColumn));
	}

	@Test
	public void test_toStringForTest_Always_ContainsTimeColumn() {
		// Arrange
		int timeColumn = 50;
		sut.setTimeColumn(timeColumn);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("timeColumn: " + timeColumn));
	}

	@Test
	public void test_toStringForTest_Always_ContainsIgnoredRows() {
		// Arrange
		int[] ignoredRows = new int[] { 0, 1, 0, 1, 0 };
		sut.setIgnoredRows(ignoredRows);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("ignoredRows:[0,1,0,1,0,]"));
	}

	@Test
	public void test_toStringForTest_Always_ContainsDateTimeFormat() {
		// Arrange
		sut.setDateTimeFormat(dateTimeFormat);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("dateTimeFormat=" + dateTimeFormat.toPattern()));
	}

	@Test
	public void test_toStringForTest_Always_ContainsDateFormat() {
		// Arrange
		sut.setDateFormat(dateFormat);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("dateFormat=dd/MM/yyyy"));
	}

	@Test
	public void test_toStringForTest_Always_ContainsTimeFormat() {
		// Arrange
		sut.setTimeFormat(timeFormat);

		// Act & Assert
		assertThat(sut.toStringForTest(), containsString("timeFormat=hh:mm"));
	}

	private void arrangeForReadNonDataLine() {
		tokensToReadNonDataLine = " 01/01/2016 05:00:30 | 01/01/2016 | 05:00:30 | Non Data 1 | Non Data 2 ";
		sut.setSeparator("|");
		sut.setDateTimeColumn(0);
		sut.setDateColumn(1);
		sut.setTimeColumn(2);
		int columnsCount = 5;
		sut.setColumns(columnsCount);

		subStrings = new String[columnsCount + 1];
	}

	private void arrangeForReadDataLine() {
		tokensToReadDataLine = " 01/01/2016 05:00:30 | 01/01/2016 | 05:00:30 | " + aDouble + " | " + anotherDouble;
		sut.setSeparator("|");
		sut.setDateTimeFormat(dateTimeFormat);
		sut.setDateFormat(dateFormat);
		sut.setTimeFormat(timeFormat);
		sut.setColumns(5);

		data = new double[5];

		symbols = new Vector<Vector<Object>>();
		symbol = "Symbol";
		Vector<Object> symbolVector = new Vector<Object>();
		symbolVector.addElement(symbol);
		symbolVector.addElement(symbolConversion);
		symbols.addElement(symbolVector);
	}

	private boolean arrayContains(double[] data, double aDouble) {
		for (double elem : data) {
			if (elem - aDouble < 0.1) {
				return true;
			}
		}

		return false;
	}
}
