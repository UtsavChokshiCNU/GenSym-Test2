package com.trilogy.gensym.xml.parsers;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import org.apache.log4j.Logger;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.trilogy.gensym.constants.XMLStringConstants;
import com.trilogy.gensym.xml.elements.Component;
import com.trilogy.gensym.xml.exception.XMLParserException;

/**
 * @author rvasyl
 *
 */
public class ComponentsParser extends AbstractParser{

    private static Logger logger = Logger.getLogger(ComponentsParser.class);

    private String watermark;
    private String typical;
    private String optional;
    private float  radioButtonGI;
    private String componentname;
    private String printName;
    private List   platforms;
    private List   componentpart;

    public ComponentsParser() {
        platforms = new ArrayList();
        componentpart = new ArrayList();
    }

    /**
     * Method call all other method for correct parsing 'component' tag. 
     * Returns Component object. 
     * 
     * @param componentsNode
     * @param prop
     * @return component
     * @throws XMLParserException
     */
    public Component parseData(Node componentsNode, Properties prop) throws XMLParserException {
        logger.debug("Start parsing Component");
        parseComponentAttributes(componentsNode, prop);
        parseComponent(componentsNode, prop);
        logger.debug("End parsing Component" + printName);
        return new Component(watermark, typical, optional, radioButtonGI, componentname, printName, platforms, componentpart);
    }

    /**
     * Method parse all attributes of 'component' tag in XML file.
     * 
     * @param bundlesNode
     * @param prop
     */
    protected void parseComponentAttributes(Node bundlesNode, Properties prop) {
        NamedNodeMap nnm = bundlesNode.getAttributes();
        watermark = getValueFromNode(nnm.getNamedItem(prop.getProperty(XMLStringConstants.WATERMARK)));
        typical = getValueFromNode(nnm.getNamedItem(prop.getProperty(XMLStringConstants.TYPICAL)));
        optional = getValueFromNode(nnm.getNamedItem(prop.getProperty(XMLStringConstants.OPTIONAL)));
        String sRadioButtonGI = getValueFromNode(nnm.getNamedItem(prop.getProperty(XMLStringConstants.RBGI)));
        if (sRadioButtonGI != null && !sRadioButtonGI.equals(EMPTY_STRING))
            radioButtonGI = Float.parseFloat(sRadioButtonGI);
        else
            radioButtonGI = 0;
    }

    /**
     * Method parse 'component' tag in XML file.
     * 
     * @param bundlesNode
     * @param prop
     * @throws XMLParserException
     */
    protected void parseComponent(Node bundlesNode, Properties prop) throws XMLParserException {
        NodeList nl = bundlesNode.getChildNodes();
        Node child;
        for (int i = 0; i < nl.getLength(); i++) {
            child = nl.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.COMPONENTNAME))) {
                componentname = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.PRINT_NAME))) {
                printName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.PLATFORMS))) {
                getPlatforms(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.COMPONENTPART))) {
                componentpart.add(new ComponentPartParser().parseData(child, prop));
                continue;
            }
        }
    }

    /**
     * Method parse 'platforms' subtag in 'component' tag in xml file.
     * 
     * @param node
     */
    protected void getPlatforms(NodeList node) {
        for (int i = 0; i < node.getLength(); i++) {
            if (node.item(i).hasChildNodes())
                platforms.add(node.item(i).getFirstChild().getNodeValue());
        }
    }
}
