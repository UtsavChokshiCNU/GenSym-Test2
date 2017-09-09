package com.trilogy.gensym.xml.parsers;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import org.apache.log4j.Logger;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.trilogy.gensym.constants.XMLStringConstants;
import com.trilogy.gensym.xml.elements.Version;
import com.trilogy.gensym.xml.exception.XMLParserException;

/**
 * @author rvasyl
 *
 */
abstract public class AbstractVersionParser extends AbstractParser{

    private static Logger logger = Logger.getLogger(AbstractVersionParser.class);
    
    private final String className; 
    private List versions;

    /**
     * Class for parsing versions (it may be 'previous-versions' or 
     * 'compatible-previous-versions' tag in XML file). As input it takes
     * name of class for correct logging.
     * 
     * @param nameOfClass
     */
    public AbstractVersionParser(String nameOfClass) {
        className = nameOfClass;
        versions = new ArrayList();
    }

    /**
     * Method call all other method for correct parsing versions tag. 
     * Returns list of versions.
     * 
     * @param compatiblePVersionsNode
     * @param prop
     * @return
     * @throws XMLParserException
     */
    public List parseData(Node compatiblePVersionsNode, Properties prop) throws XMLParserException {
        logger.debug("Start parsing " + className);
        parseVersions(compatiblePVersionsNode, prop);
        logger.debug("End parsing " + className);
        return versions;
    }

    /**
     * Method parse versions tag in XML file.
     * 
     * @param compatiblePVersionsNode
     * @param prop
     */
    protected void parseVersions(Node compatiblePVersionsNode, Properties prop) {
        NodeList nl = compatiblePVersionsNode.getChildNodes();
        Node child;
        for (int i = 0; i < nl.getLength(); i++) {
            child = nl.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.VERSION))) {
                parseClientList(child.getChildNodes(), prop);
                continue;
            }
        }
    }

    /**
     * Method parse version tag in XML file. It determines versionid and 
     * versionguid values and add it to versions list.
     * 
     * @param node
     * @param prop
     */
    protected void parseClientList(NodeList node, Properties prop) {
        String versionid = null;
        String versionguid = null;
        Node child;
        for (int i = 0; i < node.getLength(); i++) {
            child = node.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.VERSIONID))) {
                versionid = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.VERSIONGUID))) {
                versionguid = getValueFromItem(child.getChildNodes());
                continue;
            }
        }
        if (versionid != null && versionguid != null) {
            versions.add(new Version(versionid, versionguid));
        }
    }
}
