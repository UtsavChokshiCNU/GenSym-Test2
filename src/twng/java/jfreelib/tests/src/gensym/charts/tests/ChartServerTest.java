package gensym.charts.tests;

import junit.framework.TestCase;
import gensym.charts.*;
import gensym.charts.actions.IChartAction;
import org.w3c.dom.Document;

import java.io.PrintWriter;
import java.net.Socket;

/**
 * <p>
 * Test cases for Chart runner functionality.
 * </p>
 *
 */

public class ChartServerTest extends TestCase {
    /**
     * XML header string
     */
    private static String xmlHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

    /**
     * Test for ChartServer.
     */
    public final void testChartServer() {
        assertNotNull(new ChartServer());
        String xml = xmlHeader + "<test>123</test>";

        try {
            Document doc = ChartServer.parse(xml);
            assertNotNull(doc);
            try {
                ChartServer.processXML(doc);
                fail("Exception should be thrown");
            } catch (IChartAction.ChartActionException e) {
            }

            assertNull(ChartServer.parse(xml + "<test>"));
            ChartServer.printError("test", -1);
            ChartServer.doWork(1234, 1000);
        } catch (Exception e) {
            fail("Exception during running");
        }
    }
    /**
     * Test ChartServer with client.
     */
    public final void testChartServerClient() {
        final int port = 1234;
        final int timeout = 2000;
        Thread thread = new Thread()  {
            public void run() {
                Socket socket = null;
                try {
                    sleep(timeout);
                    socket = new Socket("localhost", port);
                    PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                    out.println(xmlHeader + "\n<test>tst</test>\n\n");
                    sleep(timeout);
                }
                catch (Exception ex) {
                }
                if (socket != null) {
                    try { socket.close(); } catch (Exception e) {}
                }
           }
        };

        thread.start();
        ChartServer.doWork(1234, timeout * 2);
    }
}
