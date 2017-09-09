package com.trilogy.gensym.xml;

import java.io.File;
import java.io.IOException;
import java.util.Properties;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import com.trilogy.gensym.constants.FilenamesStringConstants;
import com.trilogy.gensym.propertiesloader.PropertiesLoader;
import com.trilogy.gensym.xml.elements.FamilyType;
import com.trilogy.gensym.xml.exception.XMLParserException;
import com.trilogy.gensym.xml.exception.XSDErrorHandler;
import com.trilogy.gensym.xml.parsers.FamilyTypeParser;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.apache.log4j.Logger;

/**
 * @author rvasyl
 *
 */
public class XMLParser {

    private static final Logger logger = Logger.getLogger(XMLParser.class);
    private static final String JAXP_SCHEMA_LANGUAGE = "http://java.sun.com/xml/jaxp/properties/schemaLanguage";
    private static final String JAXP_SCHEMA_SOURCE = "http://java.sun.com/xml/jaxp/properties/schemaSource";
    private static final String W3C_XML_SCHEMA = "http://www.w3.org/2001/XMLSchema"; 

    private final File xmlFile;
    private final File xsdFile;

    /**
     * Constructor for XMLParser. As input it takes path to XML file which must 
     * be parsed. Throw IllegalArgumentException if XML file or XSD file 
     * doesn't exist. 
     * 
     * @param xmlFileName
     * @throws IllegalArgumentException
     */
    public XMLParser(String xmlFileName) throws IllegalArgumentException{
        logger.info("XML filename: " + xmlFileName);
        xmlFile = new File(xmlFileName);
        if (!xmlFile.exists()) {
            throw new IllegalArgumentException("There must be passed existing XML file");
        }
        logger.info("XSD filename: " + FilenamesStringConstants.XSD_FILE_NAME);
        xsdFile = new File(FilenamesStringConstants.XSD_FILE_NAME);
        if (!xsdFile.exists()) {
            throw new IllegalArgumentException("XSD file doesn't exist");
        }
    }

    /**
     * Method call schema validating and parsing XML file, in result returns 
     * object FamilyType with content of parsed file.
     * 
     * @return familyType
     * @throws SAXException
     * @throws IOException
     * @throws ParserConfigurationException
     * @throws IllegalArgumentException
     * @throws XMLParserException
     */
    public FamilyType parseXML() throws SAXException, IOException, ParserConfigurationException, IllegalArgumentException, XMLParserException {
        Properties prop = PropertiesLoader.loadPropertyFile(FilenamesStringConstants.ATTRIBUTE_NAMES_FILE);
        DocumentBuilderFactory fact = DocumentBuilderFactory.newInstance();
        Document documentXML = validateSchema(fact);
        return new FamilyTypeParser().parseData(documentXML, prop);
    }

    /**
     * Method validate passed DocumentBuilderFactory object with XSD schema 
     * pointed in xsdFile. If schema is valid, returns Document object of 
     * passed DocumentBuilderFactory.
     * 
     * @param factory
     * @return document
     * @throws IOException
     * @throws SAXException
     * @throws ParserConfigurationException
     */
    protected Document validateSchema(DocumentBuilderFactory factory) throws IOException, SAXException, ParserConfigurationException {
        logger.info("Schema validating started.");
        factory.setNamespaceAware(true);
        factory.setValidating(true);
        factory.setAttribute(JAXP_SCHEMA_LANGUAGE, W3C_XML_SCHEMA);
        factory.setAttribute(JAXP_SCHEMA_SOURCE, xsdFile);
        DocumentBuilder parser = factory.newDocumentBuilder();
        parser.setErrorHandler(new XSDErrorHandler());
        logger.info("Schema validating complete successfully.");
        return parser.parse(xmlFile);
    }
}