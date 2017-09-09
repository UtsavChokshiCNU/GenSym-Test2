package com.trilogy.gensym.xml.exception;

/**
 * @author rvasyl
 *
 */
public class XMLParserException extends Exception{

    private static final long serialVersionUID = 1L;

    public XMLParserException(String msg) {
        super(msg);
    }

    public XMLParserException(Exception e) {
        super(e);
    }

    public XMLParserException(Exception e, String msg) {
        super(msg, e);
    }
}
