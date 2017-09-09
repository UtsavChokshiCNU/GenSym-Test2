package gensym.charts;

import gensym.charts.actions.IChartAction;

import org.jfree.chart.title.TextTitle;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.Document;

import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import java.awt.Font;
import java.io.StringWriter;

/**
 * ChartsCommon class provides common functions 
 */
public class ChartsCommon {

    /**
     * Find child elemnt by name
     * @param element parent element
     * @param elementName child element name
     * @return child element with given name
     * @throws IChartAction.ChartActionException
     */
    public static Element getChildElement(Element element, String elementName) throws IChartAction.ChartActionException {
        NodeList list = element.getElementsByTagName(elementName);
        if (list.getLength() == 1){
            return (Element) list.item(0);
        }
        else {
            throw new IChartAction.ChartActionException("Element " + elementName + " not found");
        }
    }

    /**
     * Looks for child element with specified name and returns its value
     * @param element parent element
     * @param elementName child element name
     * @return element value
     * @throws IChartAction.ChartActionException
     */
    public static String getElementValue(Element element, String elementName) throws IChartAction.ChartActionException {
        Node node = getChildElement(element, elementName).getFirstChild();
        return node == null ? "" : node.getNodeValue();
    }

    /**
     * Converts string to integer value
     * @param str string containing integer value
     * @return converted integer value
     * @throws IChartAction.ChartActionException
     */
    public static int getIntValue(String str) throws IChartAction.ChartActionException {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            throw new IChartAction.ChartActionException("Invalid int value: " + str);
        }
    }

    /**
     * Looks for child element with specified name and returns its value as integer
     * @param element parent element
     * @param elementName child element name
     * @return element integer value
     * @throws IChartAction.ChartActionException
     */
    public static int getIntValue(Element element, String elementName) throws IChartAction.ChartActionException {
        return getIntValue(getElementValue(element, elementName)); 
    }

    /**
     * Converts string to double
     * @param str string containing double value
     * @return converted double value
     * @throws IChartAction.ChartActionException
     */
    public static double getDoubleValue(String str) throws IChartAction.ChartActionException {
        try {
            return Double.parseDouble(str);
        } catch (NumberFormatException e) {
            throw new IChartAction.ChartActionException("Invalid double value: " + str);
        }
    }

    /**
     * Converts XML document to string
     * @param doc XML document
     * @return XML string
     * @throws TransformerException
     */
    public static String getStringFromXML(Document doc) throws TransformerException {
        DOMSource domSource = new DOMSource(doc);
        StringWriter xmlWriter = new StringWriter();
        StreamResult stream = new StreamResult(xmlWriter);
        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        transformer.transform(domSource, stream);

        return xmlWriter.toString();
    }
    
    /**
     * Converts color in format 0xbbggrr to format 0xrrggbb
     * @param bgr color in BGR format
     * @return color in RGB format
     */
    public static int convertBGRtoRGB(int bgr) {
        return ((bgr & 0x0000FF) << 16) | (bgr & 0x00FF00) | ((bgr & 0xFF0000) >> 16); 
    }
    
    /**
     * Creates a new font with specified style
     * @param font base font
     * @param newStyle style to be updated
     * @param add if true style is set, otherwise reset
     * @return new font with specified style
     */
    public static Font deriveFont(Font font, int newStyle, boolean add) {
        int style = font.getStyle(); 
        if (add) {
            style |= newStyle;
        } else {
            style &= ~newStyle;
        }
        return font.deriveFont(style);
    }

    /**
     * Updated title font style
     * @param title chart title
     * @param newStyle style to be updated
     * @param add if true style is set, otherwise reset
     */
    public static void updateTitleFont(TextTitle title, int newStyle, boolean add) {
        title.setFont(deriveFont(title.getFont(), newStyle, add));
    }
}
