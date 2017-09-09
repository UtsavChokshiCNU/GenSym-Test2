package com.trilogy.gensym.xml;

import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.apache.log4j.Logger;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import com.trilogy.gensym.constants.FilenamesStringConstants;
import com.trilogy.gensym.constants.XMLStringConstants;
import com.trilogy.gensym.xml.parsers.AbstractParser;

/**
 * @author rvasyl
 *
 */
public class PathsXMLParser extends AbstractParser{

    private final static Logger logger = Logger.getLogger(PathsXMLParser.class);

    private final static String PATH = "path";

    private final Document documentXML;
    private List paths;

    /**
     * Constructor for PathsXMLParser. As input it takes path to XML file which
     * must be parsed. Throw IllegalArgumentException if passed XML file 
     * doesn't exist. 
     * 
     * @param pathsXMLfileName
     * @throws ParserConfigurationException
     * @throws SAXException
     * @throws IOException
     * @throws URISyntaxException
     */
    public PathsXMLParser (String pathsXMLfileName) throws ParserConfigurationException, SAXException, IOException, URISyntaxException {
        paths = new ArrayList();
        DocumentBuilderFactory fact = DocumentBuilderFactory.newInstance();
          DocumentBuilder parser = fact.newDocumentBuilder();
          File pathsFile = new File(FilenamesStringConstants.PATHS_FILE);
          if (!pathsFile.exists()) {
              throw new IllegalArgumentException("XML file '" + FilenamesStringConstants.PATHS_FILE + "' with paths doesn't exist");
          }
          logger.info("XML file with paths: " + FilenamesStringConstants.PATHS_FILE);
          documentXML = parser.parse(pathsFile);
    }

    /**
     * Method parse XML file and returns list of paths (content XML file).
     * 
     * @return paths
     */
    public List getPaths () {
        logger.debug("Start parsing file with paths");
        Element element = documentXML.getDocumentElement();
        NodeList nl = element.getChildNodes();
        Node child;
        for (int i = 0; i < nl.getLength(); i++) {
            child = nl.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(PATH)) {
                paths.add(getValueFromItem(child.getChildNodes()));
                logger.debug("Adding path: " + getValueFromItem(child.getChildNodes()));
                continue;
            }
        }
        logger.debug("End parsing file with paths");
        return paths;
    }
}
