package com.trilogy.gensym.test.xml.exception;

import com.trilogy.gensym.xml.exception.XMLParserException;

import junit.framework.TestCase;

public class XMLParserExceptionTest extends TestCase {
	
	public final void testCreateXMLParserExceptionArgumentString() {
		XMLParserException xmlPE = new XMLParserException("");
		assertNotNull(xmlPE);
	}
	
	public final void testCreateXMLParserExceptionArgumentException() {
		XMLParserException xmlPE = new XMLParserException(new NullPointerException());
		assertNotNull(xmlPE);
	}
	
	public final void testCreateXMLParserExceptionTwoArguments() {
		XMLParserException xmlPE = new XMLParserException(new NullPointerException(), "");
		assertNotNull(xmlPE);
	}
}
