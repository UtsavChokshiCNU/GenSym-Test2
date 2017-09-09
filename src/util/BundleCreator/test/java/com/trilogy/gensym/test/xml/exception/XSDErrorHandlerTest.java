package com.trilogy.gensym.test.xml.exception;

import junit.framework.TestCase;

import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

import com.trilogy.gensym.xml.exception.XSDErrorHandler;

public class XSDErrorHandlerTest extends TestCase{
	
	XSDErrorHandler errHandler;
	
	public void setUp () throws Exception  {
		errHandler = new XSDErrorHandler();
	}
	
	public final void testWarring() {
		errHandler.warning(new SAXParseException("", "", "", 0, 0));
	}
	
	public final void testError() {
		try {
			errHandler.error(new SAXParseException("", "", "", 0, 0));
			fail();
		} catch (SAXException e) {}
	}
	
	public final void testFatalError() {
		try {
			errHandler.fatalError(new SAXParseException("", "", "", 0, 0));
			fail();
		} catch (SAXException e) {}
	}
}
