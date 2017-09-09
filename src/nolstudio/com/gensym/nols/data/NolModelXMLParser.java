package com.gensym.nols.data;

import java.io.*;
import org.xml.sax.*;
import org.xml.sax.helpers.DefaultHandler;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;


public class NolModelXMLParser extends DefaultHandler {
    static private Writer out;
    StringBuffer textBuffer;

    public static void main(String[] argv) {
        if (argv.length != 1) {
            System.err.println("Usage: cmd filename");
            System.exit(1);
        }

        // Use an instance of ourselves as the SAX event handler
        DefaultHandler handler = new NolModelXMLParser();

        // Use the default (non-validating) parser
        SAXParserFactory factory = SAXParserFactory.newInstance();

        try {
            // Set up output stream
            out = new OutputStreamWriter(System.out, "UTF8");

            // Parse the input
            SAXParser saxParser = factory.newSAXParser();
            saxParser.parse(new File(argv[0]), handler);
        } catch (Throwable t) {
            t.printStackTrace();
        }

        System.exit(0);
    }

    //===========================================================
    // SAX DocumentHandler methods
    //===========================================================
    @Override
    public void startDocument() throws SAXException {
        emit("<?xml version='1.0' encoding='UTF-8'?>");
        nl();
    }

    @Override
    public void endDocument() throws SAXException {
        try {
            nl();
            out.flush();
        } catch (IOException e) {
            throw new SAXException("I/O error", e);
        }
    }

    @Override
    public void startElement(String namespaceURI, String sName, // simple name
        String qName, // qualified name
        Attributes attrs) throws SAXException {
        echoText();
System.out.println("qName="+qName);

        String eName = sName; // element name

        if ("".equals(eName)) {
            eName = qName; // not namespaceAware
        }
        emit("<" + eName);

        if (attrs != null) {
 System.out.println("attrs.getLength()="+attrs.getLength());
            for (int i = 0; i < attrs.getLength(); i++) {
                String aName = attrs.getLocalName(i); // Attr name 

                if ("".equals(aName)) {
                    aName = attrs.getQName(i);
                }

                emit(" ");
                emit(aName + "=\"" + attrs.getValue(i) + "\"");
 System.out.println("aName="+aName);
 System.out.println("attrs.getValue(i)="+attrs.getValue(i));
          }
        }else{
 System.out.println("null attrs");
		}

        emit(">");
    }

    @Override
    public void endElement(String namespaceURI, String sName, // simple name
        String qName // qualified name
    ) throws SAXException {
        echoText();

        String eName = sName; // element name

        if ("".equals(eName)) {
            eName = qName; // not namespaceAware
        }

        emit("</" + eName + ">");
    }

    @Override
    public void characters(char[] buf, int offset, int len)
        throws SAXException {
        String s = new String(buf, offset, len);

        if (textBuffer == null) {
            textBuffer = new StringBuffer(s);
        } else {
            textBuffer.append(s);
        }
/*  System.out.println("s="+s);
  System.out.println("offset="+offset);
  System.out.println("len="+len);
  System.out.println("textBuffer="+textBuffer);
  System.out.println("buf="+buf);

  */
	}

	@Override
	public void processingInstruction(String target,
                           String data)
                           throws SAXException{

  System.out.println("target="+target);
  System.out.println("data="+data);

	}
    //===========================================================
    // Utility Methods ...
    //===========================================================
    private void echoText() throws SAXException {
        if (textBuffer == null) {
            return;
        }

        String s = "" + textBuffer;
        emit(s);
        textBuffer = null;
    }

    // Wrap I/O exceptions in SAX exceptions, to
    // suit handler signature requirements
    private void emit(String s) throws SAXException {
/*        try {
            out.write(s);
            out.flush();
        } catch (IOException e) {
            throw new SAXException("I/O error", e);
        }
  */
	}

    // Start a new line
    private void nl() throws SAXException {
        String lineEnd = System.getProperty("line.separator");
/*
        try {
            out.write(lineEnd);
        } catch (IOException e) {
            throw new SAXException("I/O error", e);
        }	  */
    }
}
