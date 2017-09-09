package gensym.charts;

import gensym.charts.actions.IChartAction;
import gensym.charts.actions.ChartActionsFactory;

import org.xml.sax.InputSource;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

import javax.xml.parsers.*;
import javax.xml.transform.TransformerException;
import java.io.*;
import java.net.*;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Chart server class.
 * Waits for one client connection and processes requests in XML format.
 * XML has next format: "<message><action>action-name</action><handle>chart-handle</handle>action-data-tags</message>"
 */
public class ChartServer {
    /**
     * XML tags constants
     */
    private final static String MAIN_TAG = "message";
    private final static String ACTION_TAG = "action";
    private final static String HANDLE_TAG = "handle";

    /**
     * Socket writer
     */
    private static PrintWriter writer = null;

    /**
     * Parses XML string
     * @param xml XML string
     * @return XML document object
     * @throws Exception
     */
    public static Document parse(String xml) throws Exception {
        InputSource is = new InputSource();
        is.setCharacterStream(new StringReader(xml));
        DocumentBuilder builder = DocumentBuilderFactory.newInstance().newDocumentBuilder();

        try {
            return builder.parse(is);
        } catch (Exception e) {
            return null;
        }
    }

    /**
     * Makes XML message and build its header
     * @param action action name
     * @param handle chart handle
     * @return XML document representing message
     * @throws Exception
     */
    public static Document makeXMLMessage(String action, int handle) throws Exception {
        DocumentBuilder builder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document doc = builder.newDocument();

        doc.appendChild(doc.createElement("message"));

        addXMLData(doc, "handle", handle, "action", action);

        return doc;
    }

    /**
     * Adds data to XML
     * @param doc XML document
     * @param parameters XML data (element-value)
     */
    public static void addXMLData(Document doc, Object... parameters) {
        addXMLElementData(doc, doc.getDocumentElement(), parameters);
    }

    /**
     * Adds data to XML element
     * @param doc XML document
     * @param element XML element
     * @param parameters XML data (element-value)
     */
    public static void addXMLElementData(Document doc, Element element, Object... parameters) {
        Element parameter = null;
        for (Object param : parameters) {
            if (parameter == null) {
                parameter = doc.createElement(param.toString());
                element.appendChild(parameter);
            } else {
                parameter.appendChild(doc.createTextNode(param.toString()));
                parameter = null;
            }
        }
    }

    /**
     * Sends chart events to client 
     * @param name event name
     * @param parameters event parameters
     * @param handle chart handle
     */
    public static void sendChartEvent(String name, int handle, Object... parameters) {
        try {
            Document doc = makeXMLMessage("ChartEvent", handle);

            addXMLData(doc, "id", name);
            addXMLData(doc, parameters);
            sendXML(doc);
        } catch (Exception e) {
            System.out.println("Error during sending error. " + e.toString());
        }
    }

    /** 
     * Sends XML to client
     * @param doc XML document
     * @throws TransformerException
     */
    private static void sendXML(Document doc) throws TransformerException {
        String xml = ChartsCommon.getStringFromXML(doc);

        //System.out.println(xml);
        if (writer != null) {
            writer.println(xml);
        }
    }

    /**
     * Prints error to writer
     * @param message error message
     * @param handle chart handle
     */
    public static void printError(String message, int handle) {
        try {
            Document doc = makeXMLMessage("ChartError", handle);

            Element error = doc.createElement("text");
            error.appendChild(doc.createTextNode(message));
            doc.getDocumentElement().appendChild(error);

            sendXML(doc);
        } catch (Exception e) {
            System.out.println("Error during sending error. " + e.toString());
        }
    }
    /**
     * Works with client connection
     * @param client client socket
     * @throws Exception
     */
    private static void workWithClient(Socket client) throws Exception {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
            writer = new PrintWriter(client.getOutputStream(), true);

            String xml = "";
            String line;
            while ((line = in.readLine()) != null) {
                if (line.equalsIgnoreCase("") || !line.endsWith("/" + MAIN_TAG + ">")) {
                    xml += line + "\n";
                    continue;
                }
                xml += line;

                if (xml.startsWith("\n")) {
                    xml = xml.substring(1);
                }

                Document doc = parse(xml);

                if (doc == null) {
                    continue;
                }
                xml = "";

                try {
                    processXML(doc);
                } catch (IChartAction.ChartActionException e) {
                    printError(e.getMessage(), -1);
                    System.out.println("Error. " + e.toString());
                }
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    /**
     * Processes client request stored in XML format
     * @param document request XML document
     * @throws Exception
     */
    public static void processXML(Document document) throws Exception {
        Element root = document.getDocumentElement();
        if (!root.getTagName().equalsIgnoreCase(MAIN_TAG)) {
            throw new IChartAction.ChartActionException("Unknown message: " + root.getFirstChild().getNodeValue());
        }

        try {
            String actionName = ChartsCommon.getElementValue(root, ACTION_TAG);
            IChartAction action = ChartActionsFactory.makeAction(actionName);
            action.setData(root);

            int handle = ChartsCommon.getIntValue(root, HANDLE_TAG);
            JFreeChartHolder holder = JFreeChartHolder.getHolder(handle);

            if (action.isChartRequired() && holder == null) {
                throw new IChartAction.ChartActionException("Unknown handle: " + handle);
            }
            action.execute(holder);
        } catch (ChartActionsFactory.ChartActionsFactoryException e) {
            throw new IChartAction.ChartActionException(e.toString());
        }
    }

    /**
     * Server work routine
     * @param port listening port
     * @param timeout waiting timeout
     */
    public static void doWork(int port, int timeout) {
        ServerSocket server = null;
        Socket client = null;
        try {
            server = new ServerSocket(port);
            client = waitForClient(server, timeout);

            if (client != null) {
                workWithClient(client);
            }
        } catch(Exception e) {
            System.out.println("Error. " + e.toString());
        }

        try { if (server != null) server.close(); } catch (Exception ex) {}
        try { if (client != null) client.close(); } catch (Exception ex) {}
    }

    /**
     * Waits for client connection for specified time and terminate application if there are none connections.
     * @param server server cocket
     * @param ms waiting period
     * @return client socket
     * @throws IOException
     */
    private static Socket waitForClient(ServerSocket server, int ms) throws IOException {
        final ServerSocket socket = server;
        TimerTask timerTask = new TimerTask() {
            public void run() {
                String message = "Process terminating because no clients are connected.";
                System.out.println(message);
                if (socket != null) {
                    try {
                        if (!socket.isClosed()) {
                            socket.close();
                        }
                    } catch (Exception e) {
                    }
                }
            }
        };

        Timer timer = new Timer("WaitClientTimer");
        timer.schedule(timerTask, ms);
        
        Socket client = null;
        try {
            client = server.accept();
        } catch (Exception e) {
            System.out.println("Error. " + e.toString());
        }

        timer.cancel();
        return client;
    }
}
