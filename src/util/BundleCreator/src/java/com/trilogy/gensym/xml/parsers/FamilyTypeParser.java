package com.trilogy.gensym.xml.parsers;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import org.apache.log4j.Logger;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.trilogy.gensym.constants.XMLStringConstants;
import com.trilogy.gensym.xml.elements.FamilyType;
import com.trilogy.gensym.xml.exception.XMLParserException;
import com.trilogy.gensym.xml.parsers.CompatiblePreviousVersionsParser;
import com.trilogy.gensym.xml.parsers.G2OKComponentParser;
import com.trilogy.gensym.xml.parsers.PreviousVersionsParser;

/**
 * @author rvasyl
 *
 */
public class FamilyTypeParser extends AbstractParser{

    private static Logger logger = Logger.getLogger(FamilyTypeParser.class);
    
    private float  index;
    private float  fileSyntaxVersion;
    private String printName;
    private String directory;
    private String guid;
    private String splashScreen;
    private String licenseText;
    private String platforms;
    private List   g2Components;
    private List   bundles;
    private List   compatiblePreviousVer;
    private List   previousVer;
    
    public FamilyTypeParser () throws IOException, XMLParserException {
        g2Components = new ArrayList();
        bundles = new ArrayList();
    }
    
    /**
     * Method call all other method for correct parsing 'FamilyType' (main) tag. 
     * Returns FamilyType object. 
     * 
     * @param documentXML
     * @param prop
     * @return familyType
     * @throws XMLParserException
     * @throws IllegalArgumentException
     * @throws IOException
     */
    public FamilyType parseData(Document documentXML, Properties prop) throws XMLParserException, IllegalArgumentException, IOException {
        logger.info("Start parsing Family Type");
        parseAttributes(documentXML, prop);
        parseElements(documentXML, prop);
        logger.info("End parsing Family Type");
        return new FamilyType(index, fileSyntaxVersion, printName, directory, guid, splashScreen, 
                licenseText, platforms,  g2Components, bundles, compatiblePreviousVer, previousVer);
    }
    
    /**
     * Method parse all attributes of 'FamilyType' tag in XML file.
     * 
     * @param documentXML
     * @param prop
     */
    protected void parseAttributes(Document documentXML, Properties prop) {
        logger.debug("Start parsing AttributeData");
        Element element = documentXML.getDocumentElement();
        String sIndex = element.getAttribute(prop.getProperty(XMLStringConstants.INDEX));
        if (sIndex != null && !sIndex.equals(EMPTY_STRING))
            index = Float.parseFloat(sIndex);
        else
            index = 0;
        String sFileSyntaxVersion = element.getAttribute(prop.getProperty(XMLStringConstants.FILE_SYNTAX_VERSION));
        if (sFileSyntaxVersion != null && !sFileSyntaxVersion.equals(EMPTY_STRING))
            fileSyntaxVersion = Float.parseFloat(sFileSyntaxVersion);        
        else
            fileSyntaxVersion = 0;
        printName = element.getAttribute(prop.getProperty(XMLStringConstants.PRINT_NAME));
        directory = element.getAttribute(prop.getProperty(XMLStringConstants.DIRECTORY));
        guid = element.getAttribute(prop.getProperty(XMLStringConstants.GUID));
        splashScreen = element.getAttribute(prop.getProperty(XMLStringConstants.SPLASH_SCREEN));
        licenseText = element.getAttribute(prop.getProperty(XMLStringConstants.LICENSE_TEXT));
        platforms = element.getAttribute(prop.getProperty(XMLStringConstants.PLATFORMS));
        logger.debug("End parsing AttributeData");
    }
    
    /**
     * Method parse 'FamilyType' tag in XML file.
     * 
     * @param documentXML
     * @param prop
     * @throws XMLParserException
     */
    protected void parseElements (Document documentXML, Properties prop) throws XMLParserException {
        Element element = documentXML.getDocumentElement();
        NodeList nl = element.getChildNodes();
        Node child;
        for (int i = 0; i < nl.getLength(); i++) {
            child = nl.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.G2_OK_COMPONENTS))) {
                g2Components.add(new G2OKComponentParser().parseData(child, prop));
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.BUNDLES))) {
                bundles = new BundlesParser().parseData(child, prop); 
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.COMPARTIBLE_P_VERSIONS))){
                compatiblePreviousVer = new CompatiblePreviousVersionsParser().parseData(child, prop);
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.P_VERSIONS))){
                previousVer = new PreviousVersionsParser().parseData(child, prop);
                continue;
            }
        }
    }
}

