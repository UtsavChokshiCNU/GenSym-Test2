package gensym.charts.actions;

import gensym.charts.JFreeChartHolder;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.print.PageFormat;
import java.awt.print.Printable;

/**
 * Class response of printing chart
 */
public class PrintChart implements Printable {

    /** Chart frame to print */
    private JFreeChartHolder chart;

    /**
     * Constructor
     * @param chart chart frame
     */
    public PrintChart(JFreeChartHolder chart) {
        this.chart = chart;
    }

    /**
     * {@inheritDoc}
     */
    public int print(Graphics g, PageFormat pf, int pageIndex) {
        if (pageIndex != 0 && g instanceof Graphics2D) {
            return NO_SUCH_PAGE;
        }

        Graphics2D g2 = (Graphics2D) g;

        AffineTransform at = g2.getTransform();
        at.scale(pf.getWidth() / chart.getWidth(), pf.getWidth() / chart.getHeight());
        g2.setTransform(at);

        chart.printAll(g2);

        return PAGE_EXISTS;
    }
}
