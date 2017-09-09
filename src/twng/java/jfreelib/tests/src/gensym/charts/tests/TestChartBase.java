package gensym.charts.tests;

import gensym.charts.AbstractChart;
import gensym.charts.ChartServer;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.JFreeChartHolder;

import org.jfree.chart.JFreeChart;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

import junit.framework.TestCase;

public abstract class TestChartBase extends TestCase {

    private static int handle = 0;

    /**
     * Gets handle
     * @return handle
     */
    public int getHandle() {
        return handle;
    }

    /**
     * Initializes test data
     */
    public void setUp() {
        handle++;
    }

    /**
     * Destroys test data
     */
    public void tearDown() {
        JFreeChartHolder holder = JFreeChartHolder.getHolder(handle);
        if (holder != null) {
            holder.dispose();
        }
    }

    /**
     * Creates chart
     */
    public boolean doCreateAction(int type) {
        return doCreateAction(false, false, type);
    }

    /**
     * Creates chart
     */
    public boolean doCreateAction(boolean fail, boolean pos) {
        return doCreateAction(fail, pos, CreateChartAction.PE_GRAPH_CHART);
    }

    /**
     * Creates chart
     */
    public boolean doCreateAction(boolean fail, boolean pos, int type) {
        boolean bRet = true;
        try {
            String title = "Hello";
            int x = pos ? 100 : -1;
            int y = 200;
            int width = 300;
            int height = pos ? 400 : -400;
            runAction("CreateChart", "title", title, "type", fail ? -1 : type,
                    "x", x, "y", y, "width", width, "height", height);

        } catch (Exception e) {
            bRet = false;
        }
        return bRet;
    }

    /**
     * Gets chart by current handle
     * @return AbstractChart from holder
     */
    public AbstractChart getChart() {
        if (JFreeChartHolder.getHolder(handle) != null) {
            return JFreeChartHolder.getHolder(handle).getChart();
        }
        return null;
    }

    /**
     * Gets chart by current handle
     * @return JFreeChart from holder
     */
    public JFreeChart getJChart() {
        if (getChart() != null) {
            return getChart().getChart();
        }
        return null;
    }

    /**
     * Gets chart holder by current handle
     * @return JFreeChartHolder
     */
    public JFreeChartHolder getHolder() {
        return JFreeChartHolder.getHolder(handle);
    }

    /**
     * Runs action
     * @param name action name
     * @param parameters action parameters
     * @throws Exception
     */
    public void runAction(String name, Object... parameters) throws Exception {
        Document doc = ChartServer.makeXMLMessage(name, handle);
        ChartServer.addXMLData(doc, parameters);
        runAction(doc);
    }

    /**
     * Runs actiob defined in XML document
     * @param doc action XML
     * @throws Exception
     */
    public void runAction(Document doc) throws Exception {
        ChartServer.processXML(doc);
    }
    
    public void runActionDoubleArray(int handle, int prop, double values[]) throws Exception {
        Document doc = ChartServer.makeXMLMessage("SetDoubleArray", handle);
        ChartServer.addXMLData(doc, "property", prop, "i", 0, "j", 0);
        Element data = doc.createElement("value");
        doc.getDocumentElement().appendChild(data);
        for (double value : values) {
            ChartServer.addXMLElementData(doc, data, "item", value);
        }
        runAction(doc);
    }
}
