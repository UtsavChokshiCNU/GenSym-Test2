package com.trilogy.gensym.xml.parsers;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import org.apache.log4j.Logger;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.trilogy.gensym.constants.XMLStringConstants;
import com.trilogy.gensym.xml.elements.ComponentPart;
import com.trilogy.gensym.xml.elements.EnvironmentVariable;
import com.trilogy.gensym.xml.elements.Shortcut;
import com.trilogy.gensym.xml.exception.XMLParserException;

/**
 * @author rvasyl
 *
 */
public class ComponentPartParser extends AbstractParser{

    private static Logger logger = Logger.getLogger(ComponentPartParser.class);

    private String version;
    private String register;
    private String makeNROnly;
    private String name;
    private String printName;
    private String source;
    private String sourceSubdir;
    private List   platforms;
    private List   sourceFilename;
    private String destDir;
    private String destFilename;
    private String sourceSType;
    private String indep;
    private List   removeFromS;
    private List   envVariables;
    private List   regEntries;
    private List   shortcuts;
    private String postinstallCode;
    private List   nonPlatforms;

    public ComponentPartParser() {
        platforms = new ArrayList();
        sourceFilename = new ArrayList();
        removeFromS = new ArrayList();
        envVariables = new ArrayList();
        regEntries = new ArrayList();
        shortcuts = new ArrayList();
        nonPlatforms = new ArrayList();
    }

    /**
     * Method call all other method for correct parsing 'componentpart' tag. 
     * Returns ComponentPart object. 
     * 
     * @param cpNode
     * @param prop
     * @return
     * @throws XMLParserException
     */
    public ComponentPart parseData(Node cpNode, Properties prop) throws XMLParserException {
        logger.debug("Start parsing Component Part");
        parseCPAttributes(cpNode, prop);
        parseComponentPart(cpNode, prop);
        logger.debug("End parsing Component Part " + name);
        return new ComponentPart(version, register, makeNROnly, name, printName, source, sourceSubdir,
                platforms, sourceFilename, destDir, destFilename, sourceSType, indep, removeFromS,
                envVariables, regEntries, shortcuts, postinstallCode, nonPlatforms);
    }

    /**
     * Method parse all attributes of 'componentpart' tag in XML file.
     * 
     * @param bundlesNode
     * @param prop
     */
    protected void parseCPAttributes(Node bundlesNode, Properties prop) {
        NamedNodeMap nnm = bundlesNode.getAttributes();
        version = getValueFromNode(nnm.getNamedItem(prop.getProperty(XMLStringConstants.VERSION)));
        register = getValueFromNode(nnm.getNamedItem(prop.getProperty(XMLStringConstants.REGISTER)));
        makeNROnly = getValueFromNode(nnm.getNamedItem(prop.getProperty(XMLStringConstants.MNRO)));
    }

    /**
     * Method parse 'componentpart' tag in XML file.
     * 
     * @param bundlesNode
     * @param prop
     * @throws XMLParserException
     */
    protected void parseComponentPart(Node bundlesNode, Properties prop) throws XMLParserException {
        NodeList nl = bundlesNode.getChildNodes();
        Node child;
        for (int i = 0; i < nl.getLength(); i++) {
            child = nl.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.NAME))) {
                name = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.PRINT_NAME))) {
                printName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.SOURCE))) {
                source = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.SOURCE_SUBDIR))) {
                sourceSubdir = getValueFromItem(child.getChildNodes());
                continue;
            }if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.PLATFORMS))) {
                parsePlatforms(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.SOURCE_FILENAME))) {
                parseSrcFileNames(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.DEST_DIR))) {
                destDir = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.DEST_FILENAME))) {
                destFilename = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.SOURCE_S_TYPE))) {
                sourceSType = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.INDEP))) {
                indep = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.REMOVE_FROM_S))) {
                parseRemoveFromSource(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.ENV_VARIABLES))) {
                parseEnvVariables(child.getChildNodes(), prop);
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.REG_ENTIRES))) {
                parseRegistryEntires(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.SHORTCUTS))) {
                parseShortCuts(child.getChildNodes(), prop);
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.POSTINSTALL_CODE))) {
                postinstallCode = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.NON_PLATFORMS))) {
                parseNonPlatforms(child.getChildNodes());
                continue;
            }
        }
    }
    
    /**
     * Method parse all 'source-filename' subtag in 'componentpart' tag in xml file. 
     * 
     * @param nodeList
     */
    protected void parseSrcFileNames(NodeList nodeList) {
        parseAbstractList(nodeList, sourceFilename);
    }
    
    /**
     * Method parse all 'remove-from-source' subtag in 'source-filename' tag in xml file. 
     * 
     * @param nodeList
     */
    protected void parseRemoveFromSource(NodeList nodeList) {
        parseAbstractList(nodeList, removeFromS);
    }
    
    /**
     * Method parse all 'registry-entries' subtag in 'source-filename' tag in xml file. 
     * 
     * @param nodeList
     */
    protected void parseRegistryEntires(NodeList nodeList) {
        parseAbstractList(nodeList, regEntries);
    }
    
    /**
     * Method parse all 'platforms' subtag in 'source-filename' tag in xml file. 
     * 
     * @param nodeList
     */
    protected void parsePlatforms (NodeList nodeList) {
        parseAbstractList(nodeList, platforms);
    }
    
    /**
     *  Method parse all 'non-platforms' subtag in 'source-filename' tag in xml file.
     * 
     * @param nodeList
     */
    protected void parseNonPlatforms (NodeList nodeList) {
        parseAbstractList(nodeList, nonPlatforms);
    }
    
    /**
     * Method parse all subtags in node and add it values into abstractList.
     * 
     * @param node
     * @param abstractList
     */
    protected void parseAbstractList(NodeList node, List abstractList) {
        for (int i = 0; i < node.getLength(); i++) {
            if (node.item(i).hasChildNodes())
                abstractList.add(node.item(i).getFirstChild().getNodeValue());
        }
    }
    
    /**
     * Method parse 'environment-variables' subtag in 'source-filename' tag in xml file.
     * 
     * @param nodeList
     * @param prop
     * @throws XMLParserException
     */
    protected void parseEnvVariables(NodeList nodeList, Properties prop) throws XMLParserException {
        for (int i = 0; i < nodeList.getLength(); i++) {
            if (nodeList.item(i).getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (nodeList.item(i).getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.ENV_VARIABLE))) {
                parseEnvVariable(nodeList.item(i).getChildNodes(), prop);
                continue;
            }
        }
    }
    
    /**
     * Method parse all 'environment-variable' subtag in 'environment-variables' tag in xml file.
     * 
     * @param nodeList
     * @param prop
     * @throws XMLParserException
     */
    protected void parseEnvVariable(NodeList nodeList, Properties prop) throws XMLParserException {
        List evn = new ArrayList();
        List names = new ArrayList();    
        String value = null;
        String appOrMergue = null;
        Node child;
        for (int i = 0; i < nodeList.getLength(); i++) {
            child = nodeList.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.E_V_N))) {
                evn.add(getValueFromItem(child.getChildNodes()));
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.NAME))) {
                names.add(getValueFromItem(child.getChildNodes()));
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.VALUE))) {
                value = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.APPEND_OR_MERGE))) {
                appOrMergue = getValueFromItem(child.getChildNodes());
                continue;
            }
        }
        envVariables.add(new EnvironmentVariable(value, appOrMergue, evn, names));
    }
    
    /**
     * Method parse 'shortcuts' subtag in 'source-filename' tag in xml file.
     * 
     * @param nodeList
     * @param prop
     * @throws XMLParserException
     */
    protected void parseShortCuts(NodeList nodeList, Properties prop) throws XMLParserException {
        for (int i = 0; i < nodeList.getLength(); i++) {
            if (nodeList.item(i).getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (nodeList.item(i).getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.SHORTCUT))) {
                parseShortCut(nodeList.item(i).getChildNodes(), prop);
                continue;
            }
        }
    }
    
    /**
     * Method parse all 'shortcut' subtag in 'shortcuts' tag in xml file.
     * 
     * @param nodeList
     * @param prop
     * @throws XMLParserException
     */
    protected void parseShortCut(NodeList nodeList, Properties prop) throws XMLParserException {
        String shortcutName = null;
        String folderName = null;
        String subfolderName = null;
        String subsubfolderName = null;
        String appDisplayName = null;
        String appDirectory = null;
        String targetName = null;
        String parameters = null;
        String iconFile = null;
        float iconIndex = 0;
        String runStyle = null;
        Node child;
        for (int i = 0; i < nodeList.getLength(); i++) {
            child = nodeList.item(i);
            if (child.getNodeName().toLowerCase().equals(XMLStringConstants.TEXT_LABEL))
                continue;
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.SHORTCUT_NAME))) {
                shortcutName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.FOLDER_NAME))) {
                folderName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.SUB_FOLDER_NAME))) {
                subfolderName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.SUB_SUB_FOLDER_NAME))) {
                subsubfolderName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.APP_DISPLAY_NAME))) {
                appDisplayName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.APP_DIRECTORY))) {
                appDirectory = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.TARGET_NAME))) {
                targetName = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.PARAMETHERS))) {
                parameters = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.ICON_FILE))) {
                iconFile = getValueFromItem(child.getChildNodes());
                continue;
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.ICON_INDEX))) {
                String sIconIndex = getValueFromItem(child.getChildNodes());
                if (sIconIndex != null && !sIconIndex.equals(EMPTY_STRING))
                    iconIndex = Float.parseFloat(sIconIndex);
            }
            if (child.getNodeName().toLowerCase().equals(prop.getProperty(XMLStringConstants.RUN_STYLE))) {
                runStyle = getValueFromItem(child.getChildNodes());
            }
        }
        shortcuts.add(new Shortcut(shortcutName, folderName, subfolderName, subsubfolderName, appDisplayName, 
                appDirectory, targetName, parameters, iconFile, iconIndex, runStyle));
    }
}
