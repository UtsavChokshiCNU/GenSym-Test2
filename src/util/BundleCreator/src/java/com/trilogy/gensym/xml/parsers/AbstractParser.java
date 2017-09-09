package com.trilogy.gensym.xml.parsers;

import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

/**
 * @author rvasyl
 *
 */
abstract public class AbstractParser {

    protected static final int VALUE_NODE_NUMBER  = 0;

    protected static final String EMPTY_STRING    = "";

    /**
     * If first item of NodeList is not equals null, returns value of this item.
     * 
     * @param listOfNodes
     * @return
     */
    protected String getValueFromItem(NodeList listOfNodes) {
        if (listOfNodes.item(VALUE_NODE_NUMBER) != null)
            return listOfNodes.item(VALUE_NODE_NUMBER).getNodeValue();
        else
            return null;
    }

    /**
     *  If Node is not equals null, returns value of this Node.
     * 
     * @param node
     * @return
     */
    protected String getValueFromNode(Node node) {
        if (node != null)
            return node.getNodeValue();
        else
            return null;
    }
}
