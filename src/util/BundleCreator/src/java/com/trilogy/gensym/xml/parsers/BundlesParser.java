package com.trilogy.gensym.xml.parsers;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import org.apache.log4j.Logger;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.trilogy.gensym.constants.XMLStringConstants;
import com.trilogy.gensym.xml.elements.Bundle;
import com.trilogy.gensym.xml.exception.XMLParserException;

/**
 * @author rvasyl
 *
 */
public class BundlesParser extends AbstractParser{

    private static Logger logger = Logger.getLogger(BundlesParser.class);
    
    private String version;
    private String directory;
    private String bundlename;
    private String printName;
    private List   bundles;
    private List   components;

    public BundlesParser() {
        components = new ArrayList();
        bundles = new ArrayList();
    }

    /**
     * Method call all other method for correct parsing 'bundles' tag. 
     * Returns list of bundles.
     * 
     * @param bundlesNode
     * @param prop
     * @return bundles
     * @throws XMLParserException
     */
    public List parseData(Node bundlesNode, Properties prop) throws XMLParserException {
        logger.debug("Start parsing Bundles");
        parseBundles(bundlesNode, prop);
        logger.debug("End parsing Bundles");
        return bundles;
    }

    /**
     * Method parse 'bundles' tag in XML file.
     * 
     * @param bundlesNode
     * @param prop
     * @throws XMLParserException
     */
    protected void parseBundles(Node bundlesNode, Properties prop) throws XMLParserException {
        NodeList nl = bundlesNode.getChildNodes();
        Node child;
        for (int i = 0; i < nl.getLength(); i++) {
            child = nl.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.BUNDLE))) {
                parseBundle(child, prop);
                continue;
            }
        }
    }

    /**
     * Method parse 'bundle' tag in XML file.
     * 
     * @param bundlesNode
     * @param prop
     * @throws XMLParserException
     */
    protected void parseBundle(Node bundlesNode, Properties prop) throws XMLParserException {
        parseBundleAttributes(bundlesNode, prop);
        NodeList nl = bundlesNode.getChildNodes();
        Node child;
        for (int i = 0; i < nl.getLength(); i++) {
            child = nl.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.BUNDLENAME))) {
                bundlename = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.PRINT_NAME))) {
                printName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.COMPONENTS))) {
                parseComponents(child.getChildNodes(), prop);
                continue;
            }
        }
        bundles.add(new Bundle(version, directory, bundlename, printName, components));
        clearBundlesParser();
    }
    
    /**
     * Method parse all attributes of 'bundle' tag in XML file.
     * 
     * @param bundlesNode
     * @param prop
     */
    protected void parseBundleAttributes(Node bundlesNode, Properties prop) {
        NamedNodeMap nnm = bundlesNode.getAttributes();
        version = getValueFromNode(nnm.getNamedItem(prop.getProperty(XMLStringConstants.VERSION)));
        directory = getValueFromNode(nnm.getNamedItem(prop.getProperty(XMLStringConstants.DIRECTORY)));
    }

    /**
     * Method parse all components of 'bundle' tag in XML file.
     * 
     * @param componentsNode
     * @param prop
     * @throws XMLParserException
     */
    protected void parseComponents(NodeList componentsNode, Properties prop) throws XMLParserException {
        Node child;
        for (int i = 0; i < componentsNode.getLength(); i++) {
            child = componentsNode.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.COMPONENT))) {
                components.add(new ComponentsParser().parseData(child, prop));
                continue;
            }
        }
    }

    /**
     * Method clear all values before creating new bundle. 
     */
    protected void clearBundlesParser() {
        version = null;
        directory = null;
        bundlename = null;
        printName = null;
        components = new ArrayList();
    }
}
