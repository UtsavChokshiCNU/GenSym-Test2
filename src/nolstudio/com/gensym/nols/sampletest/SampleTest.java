package com.gensym.nols.sampletest;

import java.io.File;
import junit.framework.*;
import junit.extensions.*;

import com.gensym.nols.Addition;

public class SampleTest extends TestCase
{
  
   public SampleTest (String name) 
	{
		super (name);
	}
	
	public static void main(String[] args) 
	{
		junit.textui.TestRunner.run(SampleTest.class);

	}
	
	public void testGetName() throws Exception 
	{
	    	  Addition a=new Addition();

	            assertEquals(11,a.add(5,6));
	}
}