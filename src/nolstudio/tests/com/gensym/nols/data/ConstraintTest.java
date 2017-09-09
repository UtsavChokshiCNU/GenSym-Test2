package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class ConstraintTest
{

	/**
	 * Method to test constructor
	 */
	@Test
	public void testConstructor()
	{
		final int n = 100;
		final String name = "Constraint";
		final String s = "E";
		final double rhv = 10.0;

		final Constraint testObj = createTestObject();
		assertEquals(n, testObj.getNumber());
		assertEquals(name, testObj.getName());
		assertEquals(s, testObj.getSense());
		assertEquals(rhv, testObj.getRightHandValue(), 0);

		testObj.setRightHandValue(20.0);
		assertEquals(20.0, testObj.getRightHandValue(), 0);
	}

	/**
	 * Method to test Equals()
	 */
	@Test
	public void testEquals()
	{
		Object inputObj = new Object();
		final Constraint testObj = createTestObject();
		assertFalse(testObj.equals(inputObj));

		inputObj = new Constraint(20, "Constraint", "W", 30.0);
		assertTrue(testObj.equals(inputObj));

		inputObj = new Constraint(20, "Constraint1", "W", 30.0);
		assertFalse(testObj.equals(inputObj));
	}

	/**
	 * Method to test toString()
	 */
	@Test
	public void testToString()
	{
		final Constraint testObj = createTestObject();
		assertEquals("Constraint", testObj.toString());
	}

	/**
	 * Method to test setContent, getContent, getContentString methods.
	 */
	@Test
	public void testContent()
	{
		final Constraint testObj = createTestObject();
		final String content = "TestContent";
		testObj.setContent(content);
		assertEquals(content, testObj.getContent());
		final String contentString = "lhs[" + 100 + "] = " + content;
		assertEquals(contentString, testObj.getContentString());
	}

	/**
	 * Method to test addInnerVariable, removerInnerVariable, getInternalVarString
	 */
	@Test
	public void testInnverVariableMethods()
	{
		final Constraint testObj = new Constraint();
		final DataSeries ds = new DataSeries();
		final Variable var1 = new Variable("Var1", ds, 1);
		final Variable var2 = new Variable("Var2", ds, 2);
		final Variable var3 = new Variable("Var3", ds, 3);
		testObj.addInnerVariable(var1);
		testObj.addInnerVariable(var2);
		testObj.addInnerVariable(var3);
		final String varString = testObj.getInternalVarString();
		assertEquals("double Var1;\ndouble Var2;\ndouble Var3;\n", varString);
		testObj.removerInnerVariable(var2);
		assertEquals("double Var1;\ndouble Var3;\n", testObj.getInternalVarString());
	}

	/**
	 * Helper method to create test object of Constraint.
	 * @return
	 */
	private Constraint createTestObject()
	{
		final int n = 100;
		final String name = "Constraint";
		final String s = "E";
		final double rhv = 10.0;

		final Constraint testObj = new Constraint(n, name, s, rhv);
		return testObj;
	}

}
