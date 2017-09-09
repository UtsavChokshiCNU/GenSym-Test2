package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.powermock.api.mockito.PowerMockito.mock;

import java.awt.Color;
import java.util.Random;

import org.junit.Test;

import com.gensym.nols.util.ColorMap;

public class VariableTest {
	private static final boolean ANY_BOOLEAN = false;
	private static final double DELTA = 0.01;
	private static final String ANY_STRING = "ANY STRING";

	private Random randomGenerator = new Random();

	@Test
	public void test_newInstanceWithoutIndex_always_setsPlotColorAsGreen() {
		// Arrange
		// No arrangements

		// Act
		Variable sut = createSut();

		// Assert
		assertEquals(Color.green, sut.getPlotColor());
	}

	@Test
	public void test_newInstanceWithDataSeries_indexIsLessThanZero_setsPlotColorAsGreen() {
		// Arrange
		// No arrangements

		// Act
		Variable sut = createSut(ANY_STRING, createDataSeries(), -1);

		// Assert
		assertEquals(Color.green, sut.getPlotColor());
	}

	@Test
	public void test_newInstanceWithDataSeries_indexIsGreaterThanOrEqualToZero_setsFromDefaultPlotColors() {
		// Arrange
		// No arrangements

		for (int index = 0; index <= ColorMap.defaultPlotColors.length * 2; index++) {
			// Act
			Variable sut = createSut(ANY_STRING, createDataSeries(), index);

			// Assert
			assertEquals(ColorMap.colors[ColorMap.defaultPlotColors[index % ColorMap.defaultPlotColors.length]],
					sut.getPlotColor());
		}
	}

	@Test
	public void test_newInstanceWithDataSeries_indexIsLessThanZero_setsPlotSymbolAsZero() {
		// Arrange
		// No arrangements

		// Act
		Variable sut = createSut(ANY_STRING, createDataSeries(), -1);

		// Assert
		assertEquals(0, sut.getPlotSymbol());
	}

	@Test
	public void test_newInstanceWithDataSeries_indexIsGreaterThanOrEqualToZero_setsPlotSymbolLessThanSevenBasedOnIndex() {
		// Arrange
		// No arrangements

		for (int index = 0; index <= ColorMap.defaultPlotColors.length * 2; index++) {
			// Act
			Variable sut = createSut(ANY_STRING, createDataSeries(), index);

			// Assert
			assertEquals(index % 7, sut.getPlotSymbol());
		}
	}

	@Test
	public void test_newInstanceWithDataSeries_always_setsDataSeries() {
		// Arrange
		DataSeries dataSeries = createDataSeries();

		// Act
		Variable sut = createSut(ANY_STRING, dataSeries, 0);

		// Assert
		assertEquals(dataSeries, sut.getDataSeries());
		assertEquals(dataSeries.hashCode(), sut.getDataSeriesHashCode());
		assertEquals(dataSeries.getDataSource(), sut.getDataSource());
	}

	@Test
	public void test_newInstanceWithDataSeries_always_setsName() {
		// Arrange
		String name = "VariableName";

		// Act
		Variable sut = createSut(name, createDataSeries(), 0);

		// Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_newInstanceWithNameTagAndUnit_indexIsGreaterThanOrEqualToZero_setsFromDefaultPlotColors() {
		// Arrange
		// No arrangements

		for (int index = 0; index <= ColorMap.defaultPlotColors.length * 2; index++) {
			// Act
			Variable sut = createSut(ANY_STRING, ANY_STRING, ANY_STRING, createDataSeries(), index);

			// Assert
			assertEquals(ColorMap.colors[ColorMap.defaultPlotColors[index % ColorMap.defaultPlotColors.length]],
					sut.getPlotColor());
		}
	}

	@Test
	public void test_newInstanceWithNameTagAndUnit_indexIsGreaterThanOrEqualToZero_setsPlotSymbolLessThanSevenBasedOnIndex() {
		// Arrange
		// No arrangements

		for (int index = 0; index <= ColorMap.defaultPlotColors.length * 2; index++) {
			// Act
			Variable sut = createSut(ANY_STRING, ANY_STRING, ANY_STRING, createDataSeries(), index);

			// Assert
			assertEquals(index % 7, sut.getPlotSymbol());
		}
	}

	@Test
	public void test_newInstanceWithNameTagAndUnit_always_setsDataSeries() {
		// Arrange
		DataSeries dataSeries = createDataSeries();

		// Act
		Variable sut = createSut(ANY_STRING, ANY_STRING, ANY_STRING, dataSeries, 0);

		// Assert
		assertEquals(dataSeries, sut.getDataSeries());
		assertEquals(dataSeries.hashCode(), sut.getDataSeriesHashCode());
		assertEquals(dataSeries.getDataSource(), sut.getDataSource());
	}

	@Test
	public void test_newInstanceWithNameTagAndUnit_always_setsTag() {
		// Arrange
		String tag = "variableTag";

		// Act
		Variable sut = createSut(tag, ANY_STRING, ANY_STRING, createDataSeries(), 0);

		// Assert
		assertEquals(tag, sut.getTag());
	}

	@Test
	public void test_newInstanceWithNameTagAndUnit_always_setsName() {
		// Arrange
		String name = "variableName";

		// Act
		Variable sut = createSut(ANY_STRING, name, ANY_STRING, createDataSeries(), 0);

		// Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_newInstanceWithNameTagAndUnit_always_setsUnit() {
		// Arrange
		String unit = "variableUnit";

		// Act
		Variable sut = createSut(ANY_STRING, ANY_STRING, unit, createDataSeries(), 0);

		// Assert
		assertEquals(unit, sut.getUnit());
	}

	@Test
	public void test_setDataSeries_always_updatesDataSeries() {
		// Arrange
		Variable sut = createSut();
		DataSeries dataSeries = createDataSeries();

		// Act
		sut.setDataSeries(dataSeries);

		// Assert
		assertEquals(dataSeries, sut.getDataSeries());
	}

	@Test
	public void test_setName_always_updatesName() {
		// Arrange
		Variable sut = createSut();
		String name = "New Name";

		// Act
		sut.setName(name);

		// Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_setTag_always_updatesTag() {
		// Arrange
		Variable sut = createSut();
		String tag = "New Tag";

		// Act
		sut.setTag(tag);

		// Assert
		assertEquals(tag, sut.getTag());
	}

	@Test
	public void test_setUnit_always_updatesUnit() {
		// Arrange
		Variable sut = createSut();
		String unit = "New Unit";

		// Act
		sut.setUnit(unit);

		// Assert
		assertEquals(unit, sut.getUnit());
	}

	@Test
	public void test_setPlotSymbol_always_updatesPlotSymbol() {
		// Arrange
		Variable sut = createSut();
		int plotSymbol = 100;

		// Act
		sut.setPlotSymbol(plotSymbol);

		// Assert
		assertEquals(plotSymbol, sut.getPlotSymbol());
	}

	@Test
	public void test_setPlotColor_always_updatesPlotColor() {
		// Arrange
		Variable sut = createSut();
		Color plotColor = Color.red;

		// Act
		sut.setPlotColor(plotColor);

		// Assert
		assertEquals(plotColor, sut.getPlotColor());
	}

	@Test
	public void test_setStatistics_always_setsStatistics() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();

		// Act
		sut.setStatistics(statistics);

		// Assert
		assertEquals(sut.getStatistics().length, statistics.length);
		for (int idx = 0; idx < statistics.length; idx++) {
			assertEquals(statistics[idx], sut.getStatistics()[idx], DELTA);
		}
	}

	@Test
	public void test_getMaxValue_always_returnsMaxValue() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[8], sut.getMaxValue(), DELTA);
	}

	@Test
	public void test_getMinValue_always_returnsMinValue() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[7], sut.getMinValue(), DELTA);
	}

	@Test
	public void test_getMeanValue_always_returnsMeanValue() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[0], sut.getMeanValue(), DELTA);
	}

	@Test
	public void test_getMedianValue_always_returnsMedianValue() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[1], sut.getMedianValue(), DELTA);
	}

	@Test
	public void test_getSum_always_returnsSum() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[9], sut.getSum(), DELTA);
	}

	@Test
	public void test_getSTD_always_returnsSTD() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[2], sut.getSTD(), DELTA);
	}

	@Test
	public void test_getVariance_always_returnsVariance() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[3], sut.getVariance(), DELTA);
	}

	@Test
	public void test_getKurt_always_returnsKurt() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[4], sut.getKurt(), DELTA);
	}

	@Test
	public void test_getSkew_always_returnsSkew() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[5], sut.getSkew(), DELTA);
	}

	@Test
	public void test_getRange_always_returnsRange() {
		// Arrange
		Variable sut = createSut();
		double[] statistics = createStatistics();
		sut.setStatistics(statistics);

		// Act & Assert
		assertEquals(statistics[6], sut.getRange(), DELTA);
	}

	@Test
	public void test_setComment_always_updatesComment() {
		// Arrange
		Variable sut = createSut();
		String comment = "New Comment";

		// Act
		sut.setComment(comment);

		// Assert
		assertEquals(comment, sut.getComment());
	}

	@Test
	public void test_setColumnIndex_always_updatesColumnIndex() {
		// Arrange
		Variable sut = createSut();
		int columnIndex = 10;

		// Act
		sut.setColumnIndex(columnIndex);

		// Assert
		assertEquals(columnIndex, sut.getColumnIndex());
	}

	@Test
	public void test_initTransient_always_updatesDataSeries() {
		// Arrange
		Variable sut = createSut();
		DataSeries dataSeries = createDataSeries();

		// Act
		sut.initTransient(dataSeries);

		// Assert
		assertEquals(dataSeries, sut.getDataSeries());
		assertEquals(dataSeries.hashCode(), sut.getDataSeriesHashCode());
	}

	@Test
	public void test_toName_always_returnsName() {
		// Arrange
		Variable sut = createSut();
		String name = "Variable Name";
		sut.setName(name);

		// Act & Assert
		assertEquals(name, sut.toString());
	}

	@Test
	public void test_toStringWithFlag_always_returnsFormattedNameTagAndUnit() {
		// Arrange
		String name = "VariableName";
		String tag = "varTag";
		String unit = "varUnit";
		int columnIndex = 4;
		Variable sut = createSut(tag, name, unit);
		sut.setColumnIndex(columnIndex);
		sut.setName(name);

		// Act & Assert
		assertEquals("Name=" + name + "  Index=" + columnIndex + "  Tag=" + tag + "  Unit = " + unit,
				sut.toString(ANY_BOOLEAN));
	}

	@Test
	public void test_setDependencyFlag_always_updatesDependencyFlag() {
		// Arrange
		Variable sut = createSut();
		int flag = 15;

		// Act
		sut.setDependencyFlag(flag);

		// Act & Assert
		assertEquals(flag, sut.getDependencyFlag());
	}

	@Test
	public void test_setInitialValue_always_updatesInitialValue() {
		// Arrange
		Variable sut = createSut();
		double initValue = 25;

		// Act
		sut.setInitialValue(initValue);

		// Act & Assert
		assertEquals(initValue, sut.getInitialValue(), DELTA);
	}

	@Test
	public void test_setHardUpperBound_always_updatesHardUpperBound() {
		// Arrange
		Variable sut = createSut();
		double hub = 99;

		// Act
		sut.setHardUpperBound(hub);

		// Act & Assert
		assertEquals(hub, sut.getHardUpperBound(), DELTA);
	}

	@Test
	public void test_setHardLowerBound_always_updatesHardLowerBound() {
		// Arrange
		Variable sut = createSut();
		double hlb = 1;

		// Act
		sut.setHardLowerBound(hlb);

		// Act & Assert
		assertEquals(hlb, sut.getHardLowerBound(), DELTA);
	}

	@Test
	public void test_setResultValue_always_updatesResultValue() {
		// Arrange
		Variable sut = createSut();
		double resultValue = 51;

		// Act
		sut.setResultValue(resultValue);

		// Act & Assert
		assertEquals(resultValue, sut.getResultValue(), DELTA);
	}

	@Test
	public void test_initializeHardBounds_always_resetsHardBounds() {
		// Arrange
		Variable sut = createSut();
		sut.setHardUpperBound(99);
		sut.setHardLowerBound(1);

		// Act
		sut.initializeHardBounds();

		// Act & Assert
		assertEquals(Double.NEGATIVE_INFINITY, sut.getHardLowerBound(), DELTA);
		assertEquals(Double.POSITIVE_INFINITY, sut.getHardUpperBound(), DELTA);
	}

	// -- Helper Methods --

	private DataSeries createDataSeries() {
		DataSeries dataSeries = new DataSeries();
		dataSeries.setDataSource(createDataSource());
		return dataSeries;
	}

	private DataSource createDataSource() {
		DataSource dataSource = mock(DataSource.class);
		return dataSource;
	}

	private double[] createStatistics() {
		double[] statistics = new double[10];

		for (int idx = 0; idx < 10; idx++) {
			statistics[idx] = randomGenerator.nextInt() + idx;
		}

		return statistics;
	}

	private Variable createSut() {
		return new Variable();
	}

	private Variable createSut(String name, DataSeries d, int index) {
		return new Variable(name, d, index);
	}

	private Variable createSut(String tag, String name, String unit) {
		return new Variable(tag, name, unit, createDataSeries(), 0);
	}

	private Variable createSut(String tag, String name, String unit, DataSeries d, int index) {
		return new Variable(tag, name, unit, d, index);
	}
}
