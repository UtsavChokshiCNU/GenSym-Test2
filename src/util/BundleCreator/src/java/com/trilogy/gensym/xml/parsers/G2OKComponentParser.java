package com.trilogy.gensym.xml.parsers;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import org.apache.log4j.Logger;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.trilogy.gensym.constants.XMLStringConstants;
import com.trilogy.gensym.xml.elements.G2OKComponent;
import com.trilogy.gensym.xml.exception.XMLParserException;

public class G2OKComponentParser extends AbstractParser{

    private static Logger logger = Logger.getLogger(G2OKComponentParser.class);

    private String bundleName;
    private String familyName;
    private String printName;
    private List   options;
    private List   clientList;

    public G2OKComponentParser() {
        options = new ArrayList();
        clientList = new ArrayList();
    }

    /**
     * Method call all other method for correct parsing 'g2-ok-components' tag. 
     * Returns G2OKComponent object.
     * 
     * @param g2OkComponentsNode
     * @param prop
     * @return
     * @throws XMLParserException
     */
    public G2OKComponent parseData(Node g2OkComponentsNode, Properties prop) throws XMLParserException {
        logger.debug("Start parsing G2OKComponents");
        parseG2OKComponents(g2OkComponentsNode, prop);
        logger.debug("End parsing G2OKComponents");
        return new G2OKComponent(bundleName, familyName, printName, options, clientList);
    }

    /**
     * Method parse 'g2-ok-components' tag in XML file.
     * 
     * @param g2OkComponentsNode
     * @param prop
     */
    protected void parseG2OKComponents(Node g2OkComponentsNode, Properties prop) {
        NodeList nl = g2OkComponentsNode.getChildNodes();
        Node child;
        for (int i = 0; i < nl.getLength(); i++) {
            child = nl.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.BUNDLE_NAME))) {
                bundleName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.OPTIONS))) {
                parseOptions(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.FAMILY_NAME))){
                familyName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.PRINT_NAME))) {
                printName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.N_CLIENTS_LIST))) {
                parseClientList(child.getChildNodes());
                continue;
            }
        }
    }

    /**
     * Method parse options subtag in 'g2-ok-components' tag in xml file.
     * 
     * @param node
     */
    protected void parseOptions(NodeList node) {
        for (int i = 0; i < node.getLength(); i++) {
            if (node.item(i).hasChildNodes())
                options.add(node.item(i).getFirstChild().getNodeValue());
        }
    }

    /**
     * Method parse 'n-clients-list' subtag in 'g2-ok-components' tag in xml file.
     * 
     * @param node
     */
    protected void parseClientList(NodeList node) {
        for (int i = 0; i < node.getLength(); i++) {
            if (node.item(i).hasChildNodes())
                clientList.add(new Double(Double.parseDouble(node.item(i).getFirstChild().getNodeValue())));
        }
    }
}
