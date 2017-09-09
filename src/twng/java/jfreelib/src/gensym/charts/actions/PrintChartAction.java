package gensym.charts.actions;

import gensym.charts.*;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;
import org.w3c.dom.Element;

/**
 * Print chart action: print chart
 */
public class PrintChartAction implements IChartAction {

    /**
     * {@inheritDoc}
     */
    public void execute(JFreeChartHolder chart) throws ChartActionException {
        PrinterJob pj = PrinterJob.getPrinterJob();
        pj.setPrintable(new PrintChart(chart));

        if (pj.printDialog()) {
            try {
                pj.print();
            } catch (PrinterException e) {
                System.out.println(e);
            }
        }
    }

    /**
     * {@inheritDoc}
     */
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    /**
     * {@inheritDoc}
     */
    public String getName() {
        return "Print";
    }

    /**
     * {@inheritDoc}
     */
    public boolean isChartRequired() {
        return true;
    }

    /**
     * {@inheritDoc}
     */
    public void setData(Element data) throws ChartActionException {
    }
}
