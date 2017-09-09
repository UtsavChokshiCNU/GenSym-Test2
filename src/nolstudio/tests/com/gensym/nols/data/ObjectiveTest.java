package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class ObjectiveTest
{

	/**
	 * Method to test constructor with String argument
	 */
	@Test
	public void testConstructor()
	{
		final Objective testObj = new Objective("TestObject");
		assertEquals("TestObject", testObj.getName());
	}

	/**
	 * Method to test addInnerVariable, removerInnerVariable, getInternalVarString
	 */
	@Test
	public void testAddInnerVariable()
	{
		final Objective testObj = new Objective();
		final DataSeries ds = new DataSeries();
		final Variable var1 = new Variable("Var1", ds, 1);
		final Variable var2 = new Variable("Var2", ds, 2);
		final Variable var3 = new Variable("Var3", ds, 3);

		testObj.addInnerVariable(var1);
		testObj.addInnerVariable(var2);
		testObj.addInnerVariable(var3);
		testObj.addInnerVariable(var2);

		String varString = testObj.getInternalVarString();
		assertEquals("double * Var1;\ndouble * Var2;\ndouble * Var3;\n", varString);

		testObj.removerInnerVariable(var2);
		varString = testObj.getInternalVarString();
		assertEquals("double * Var1;\ndouble * Var3;\n", varString);
	}
}
