package com.trilogy.gensym.xml.exception;

import org.apache.log4j.Logger;
import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

/**
 * @author rvasyl
 *
 */
public class XSDErrorHandler implements ErrorHandler{

    private static Logger logger = Logger.getLogger(XSDErrorHandler.class);

    public void warning(SAXParseException e) {
        logger.warn(e.getMessage());
    }

    public void error(SAXParseException e) throws SAXException {
        logger.fatal("Error at line " + e.getLineNumber() + " in XML file:");
        throw e;
    }

    public void fatalError(SAXParseException e) throws SAXException {
        logger.fatal("Fatal error at line " + e.getLineNumber() + " in XML file:");
        throw e;
    }
}
