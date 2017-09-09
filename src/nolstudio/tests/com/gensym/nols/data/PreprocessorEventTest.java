package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Test;

public class PreprocessorEventTest
{

	/**
	 * Method to test constructor with arguments.
	 */
	@Test
	public void testConstructor()
	{
		final Object prep = new Object();
		final String id = "TestId";
		final Vector<Object> dss = new Vector<>();
		dss.addElement(new Object());
		int flag = 0;

		PreprocessorEvent testObj = new PreprocessorEvent(prep, id, dss, flag);
		assertEquals(dss, testObj.getDataSeries());
		assertEquals(prep, testObj.getPreprocessor());
		assertEquals(id, testObj.getIdentifier());

		flag = 1;
		testObj = new PreprocessorEvent(prep, id, dss, flag);
		assertEquals(dss, testObj.getVarObjects());
	}
}
