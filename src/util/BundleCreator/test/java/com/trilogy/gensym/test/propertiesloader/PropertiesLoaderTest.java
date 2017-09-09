package com.trilogy.gensym.test.propertiesloader;

import com.trilogy.gensym.propertiesloader.PropertiesLoader;

import junit.framework.TestCase;

public class PropertiesLoaderTest extends TestCase{
	
	public final void testLoadPropertyFileException() throws Exception {
		PropertiesLoader pl = new PropertiesLoader();
		assertNotNull(pl);
		try {
			PropertiesLoader.loadPropertyFile("WrongFileNane.properties");
			fail();
		} catch (IllegalArgumentException e) {}
	}
}
