package gensym.charts.tooltips;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FontMetrics;
import java.awt.Graphics;

import java.util.LinkedList;
import java.util.List;

import javax.swing.JComponent;
import javax.swing.JToolTip;
import javax.swing.SwingUtilities;
import javax.swing.plaf.metal.MetalToolTipUI;

import sun.swing.SwingUtilities2;

/**
 * MultiLine toolTip plugable UI 
 */
public class MultiLineToolTipUI extends MetalToolTipUI {
    /**
     * Default toolTip color
     */
    public static Color DEFAULT_TOOLTIP_COLOR = Color.YELLOW;

    /**
     * Default toolTip margin
     */
    public static int DEFAULT_TOOLTIP_MARGIN = 3;

    /**
     * Array of toolTip string 
     */
    private List<String> tooltips = new LinkedList<String>();

    /**
     * {@inheritDoc}
     */
    public void paint(Graphics graphics, JComponent jcomp) {
        FontMetrics metrics = graphics.getFontMetrics();
        Dimension size = jcomp.getSize();
        graphics.setColor(DEFAULT_TOOLTIP_COLOR);
        graphics.fillRect(0, 0, size.width, size.height);
        graphics.setColor(jcomp.getForeground());
        
        for (int i = 0; i < tooltips.size(); i++) {
        	graphics.drawString(tooltips.get(i), DEFAULT_TOOLTIP_MARGIN, (metrics.getHeight()) * (i + 1));
        }
    }

    /**
     * {@inheritDoc} 
     */
    public Dimension getPreferredSize(JComponent jcomp) {

        FontMetrics metrics = SwingUtilities2.getFontMetrics(jcomp, jcomp.getFont());
        JToolTip toolTip = (JToolTip) jcomp;
        String tipText = toolTip.getTipText();
        if (tipText == null) {
        	tipText = "";
        }
        
        tooltips.clear();

        tipText = tipText.replace("\r\n", "|");
        tipText = tipText.replace("\n", "|");
        
        int maxWidth = 0;
        for (String line : tipText.split("[|]")) {
            maxWidth = Math.max(maxWidth, SwingUtilities.computeStringWidth(metrics, line));
            tooltips.add(line);
        }
        int height = tooltips.size() > 0 ? metrics.getHeight() * tooltips.size() : metrics.getHeight();
        return new Dimension(maxWidth + DEFAULT_TOOLTIP_MARGIN * 2, height + DEFAULT_TOOLTIP_MARGIN * 2);
    }
}
