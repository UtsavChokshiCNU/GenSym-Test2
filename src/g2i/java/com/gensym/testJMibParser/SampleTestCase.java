package com.gensym.testJMibParser;

import java.io.File;
import junit.framework.*;
import junit.extensions.*;

import com.gensym.JMibParser.Addition;

public class SampleTestCase extends TestCase
{
	public SampleTestCase (String name) 
	{
		super (name);
	}
	
	public static void main(String[] args) 
	{
		junit.textui.TestRunner.run(SampleTestCase.class);
	}

	public void testGetName() throws Exception 
	{
		Addition a=new Addition();
        assertEquals(11,a.add(5,6));
	}
}