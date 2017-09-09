package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.powermock.api.mockito.PowerMockito.mock;

import java.util.Vector;

import org.junit.Test;
import org.mockito.Mockito;

public class DataSourceTest
{
	/**
	 * Method to test DataSource constructor for sourceName input
	 */
	@Test
	public void testDataSourceForSourceNameInput()
	{
		final String sourceName = "TestSource";
		final DataSource testObj = new DataSource(sourceName);
		assertEquals(sourceName, testObj.getName());
		assertEquals(sourceName, testObj.toString());
	}

	/**
	 * Method to test getNumberOfDataSeries, getDataSeries
	 */
	@Test
	public void testDataSeries()
	{
		final DataSource testObj = new DataSource();
		final Vector<DataSeries> series = new Vector<>();
		series.addElement(new DataSeries(1, 1));
		series.addElement(new DataSeries(2, 2));
		series.addElement(new DataSeries(3, 3));

		testObj.setDataSeries(series);
		assertEquals(3,  testObj.getNumberOfDataSeries());
		final DataSeries seriesObj = testObj.getDataSeries(1);
		assertEquals(2, seriesObj.getColumn());
		assertEquals(2, seriesObj.getRow());
	}

	/**
	 * Method to test getDataSeriesIndex, getDataSeriesName, getDataSeries
	 */
	@Test
	public void testDataSeriesName()
	{
		final DataSource testObj = new DataSource();
		final Vector<DataSeries> series = new Vector<>();

		final DataSeries series1 = new DataSeries(1, 1);
		series1.setName("Series1");

		final DataSeries series2 = new DataSeries(2, 2);
		series2.setName("Series2");

		final DataSeries series3 = new DataSeries(3, 3);
		series3.setName("Series3");

		series.addElement(series1);
		series.addElement(series2);
		series.addElement(series3);
		testObj.setDataSeries(series);

		assertEquals("Series3", testObj.getDataSeriesName(2));

		assertEquals(2, testObj.getDataSeriesIndex("Series3"));
		assertEquals(-1, testObj.getDataSeriesIndex("Series7"));

		final DataSeries seriesObj = testObj.getDataSeries("Series2");
		assertEquals(2, seriesObj.getColumn());
		assertEquals(2, seriesObj.getRow());
		assertNull(testObj.getDataSeries("Series8"));
	}

	/**
	 * Method to test addListener, removeListener & clearListener methods.
	 */
	@Test
	public void testAddListener()
	{
		final DataSource testObj = new DataSource();
		final DataSourceListener l = mock(DataSourceListener.class);
		testObj.addListener(l);
		final DataSourceListener m = mock(DataSourceListener.class);
		testObj.addListener(m);
		testObj.addListener(l);

		assertEquals(2, testObj.itsEventListeners.size());
		testObj.removeListener(l);
		assertEquals(1, testObj.itsEventListeners.size());
		assertFalse(testObj.itsEventListeners.contains(l));
		assertTrue(testObj.itsEventListeners.contains(m));
		testObj.addListener(l);
		testObj.clearListener();
		assertEquals(0, testObj.itsEventListeners.size());
	}

	@Test
	public void testInitTransient()
	{
		final Project p = new Project();

		final DataSource testObj = new DataSource();
		final Vector<DataSeries> series = new Vector<>();
		final DataSeries ds = mock(DataSeries.class);
		series.addElement(ds);
		testObj.setDataSeries(series);
		testObj.initTransient(p);
		Mockito.verify(ds).initTransient(testObj);
	}
}
