package gensym.charts.tests;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FontMetrics;
import java.awt.Graphics;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JToolTip;
import javax.swing.plaf.ToolTipUI;

import gensym.charts.tooltips.MultiLineToolTip;
import gensym.charts.tooltips.MultiLineToolTipUI;

import junit.framework.TestCase;

/**
 * <p>
 * Test cases for MultiLine ToolTips functionality.
 * </p>
 */
public class ToolTipsTest extends TestCase {

    /**
     * Frame (required for test)
     */
    private JFrame frame = new JFrame("Test");
    
    /**
    * Panel (required for test)
     */
    private JPanel panel = new JPanel(new BorderLayout());
    
    /**
     * String for test
     */
    private String testStr = "test";
    
    /**
     * Button with toolTips
     */
    private JButton button = new JButton("Ok") {
        public JToolTip createToolTip() {
            MultiLineToolTip toolTip = new MultiLineToolTip();
            toolTip.setComponent(this);
            return toolTip;
        }
    };
    
    /**
     * Initializes test data
     */
    protected void setUp() {
        frame.setPreferredSize(new Dimension(100, 100));
        //Create the component that will have the initial focus.
        panel.add(button);
        frame.getContentPane().add(panel);
        frame.pack();
        button.requestFocusInWindow(); 
        frame.setVisible(true);
    }
    
    /**
     * Destroys test data 
     */
    protected void tearDown() {
    	frame.dispose();
    }
    
    /**
     * Generate multiline string
     * @param lineCount line count
     * @return multiline string
     */
    public String genMultiLinesText(int lineCount) {
    	String result = testStr;
    	for (int i = 1; i < lineCount; i++)
    		result = result + "\r\n" + testStr; 
    	return lineCount > 0 ? result : "";
    }
    
    /**
     * Calculated height of toolTip window 
     * @param metrics font metrics
     * @param lineCount line count
     * @return Dimension of toolTip window
     */
    public double expectedHeight(FontMetrics metrics, int lineCount) {
    	return (lineCount > 0 ? metrics.getHeight() * lineCount : metrics.getHeight()) + MultiLineToolTipUI.DEFAULT_TOOLTIP_MARGIN * 2;
    }
    
    /**
     * Tests multiLine ToolTipUI plugin
     */
    public void testMultiLineToolTipUI() {
        try {
            JToolTip tt = button.createToolTip();
            assertNotNull(tt);
            assertTrue(tt instanceof MultiLineToolTip);
            
            ToolTipUI ttUI = tt.getUI();
            assertNotNull(ttUI);
            assertTrue(ttUI instanceof MultiLineToolTipUI);
            
            FontMetrics metrics = tt.getFontMetrics(button.getFont());

            tt.setTipText(null);
            assertEquals(expectedHeight(metrics, 1), ttUI.getPreferredSize(tt).getHeight());
            
            tt.setTipText(genMultiLinesText(1));
            assertEquals(expectedHeight(metrics, 1), ttUI.getPreferredSize(tt).getHeight());
            
            tt.setTipText(genMultiLinesText(2));
            assertEquals(expectedHeight(metrics, 2), ttUI.getPreferredSize(tt).getHeight());
            
            tt.setTipText(genMultiLinesText(3));
            assertEquals(expectedHeight(metrics, 3), ttUI.getPreferredSize(tt).getHeight());
            
            Graphics graphics = button.getGraphics().create();
            ttUI.paint(graphics, tt);
            assertEquals(tt.getForeground(), graphics.getColor()); 
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
