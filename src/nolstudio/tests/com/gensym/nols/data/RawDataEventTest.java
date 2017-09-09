package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Test;

public class RawDataEventTest
{
	/**
	 * Method to test Constructor for DataSeries Parameter
	 */
	@Test
	public void testConstructor()
	{
		final Object rawData = new Object();
		final String id = "TestId";
		final DataSeries ds = new DataSeries();
		final RawDataEvent testObj = new RawDataEvent(rawData, id, ds);

		assertEquals(ds, testObj.getDataSeries());
		assertEquals(id, testObj.getIdentifier());
		assertEquals(rawData, testObj.getRawDataSource());
	}

	/**
	 * Method to test Constructor for DataSeries Parameter
	 */
	@Test
	public void testConstructorForEvtDataParam()
	{
		final Object rawData = new Object();
		final String id = "TestId";
		final Object evtData = new Object();
		final RawDataEvent testObj = new RawDataEvent(rawData, id, evtData);

		assertEquals(evtData, testObj.getEventObject());
		assertEquals(id, testObj.getIdentifier());
		assertEquals(rawData, testObj.getRawDataSource());
	}

	/**
	 * Method to test Constructor for DataSeries Parameter
	 */
	@Test
	public void testConstructorForVectorInput()
	{
		final Object rawData = new Object();
		final String id = "TestId";
		Vector<Variable> vars = new Vector<>();
		final Variable var = new Variable();
		vars.addElement(var);
		RawDataEvent testObj = new RawDataEvent(rawData, id, vars);

		assertEquals(vars, testObj.getVarObjects());
		assertEquals(var, testObj.getVarObjects().get(0));
		assertEquals(id, testObj.getIdentifier());
		assertEquals(rawData, testObj.getRawDataSource());

		vars = new Vector<>();
		testObj = new RawDataEvent(rawData, id, vars);
		assertEquals(vars, testObj.getVarObjects());
		assertEquals(id, testObj.getIdentifier());
		assertEquals(rawData, testObj.getRawDataSource());
	}
}
