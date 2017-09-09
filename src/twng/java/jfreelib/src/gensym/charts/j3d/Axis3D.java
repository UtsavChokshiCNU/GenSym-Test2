package gensym.charts.j3d;

import gensym.charts.axis.StringNumberFormat;

import java.awt.Graphics2D;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import org.jfree.chart.axis.AxisState;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.NumberTick;
import org.jfree.chart.axis.TickType;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.RectangleInsets;
import org.jfree.ui.TextAnchor;

public class Axis3D extends NumberAxis {

    /** Generated serial version UID */
    private static final long serialVersionUID = -3085016358739397757L;

    /** Axis label format */
    private StringNumberFormat format = new StringNumberFormat(null);

    /** Grid line showing flag */
    private boolean showGridLine = true;

    /**
     * Constructor
     */
    public Axis3D() {
        setNumberFormatOverride(format);
        
        setTickMarkInsideLength(1);
        setTickMarkOutsideLength(6);
        
        setLabelInsets(new RectangleInsets(3, 5, 3, 5));
    }

    /**
     * {@inheritDoc}
     */
    public AxisState draw(Graphics2D g2, double cursor, Rectangle2D plotArea,
            Rectangle2D dataArea, RectangleEdge edge,
            PlotRenderingInfo plotState) {
        return null;
    }
    
    /**
     * Returns ticks
     * @param g2 graphic object
     * @param start start axis point
     * @param end end axis point
     * @return ticks list
     */
    public List<NumberTick> getTicks(Graphics2D g2, Point2D start, Point2D end) {
        double x = start.getX() - end.getX();
        double y = start.getY() - end.getY();
        double d = Math.sqrt(x * x + y * y);
        Rectangle2D area = new Rectangle2D.Double(0, 0, d, d);
        List<?> ticks = refreshTicks(g2, null, area, RectangleEdge.BOTTOM);

        if (getLabelFormat().isEmpty() || getMajorTickCount(ticks) == 0)
        {
            return copyTicks(ticks);
        }

        return formatTicks(ticks, getLabelFormat());
    }

    /**
     * Copies ticks
     * @param ticks source list
     * @return copied list
     */
    protected List<NumberTick> copyTicks(List<?> ticks) {
        ArrayList<NumberTick> list = new ArrayList<NumberTick>(ticks.size());
        for (Object tick : ticks) {
            if (tick instanceof NumberTick) {
                list.add((NumberTick) tick);
            }
        }
        return list;
    }

    /**
     * Formats ticks
     * @param ticks source tick list
     * @param format string format
     * @return list of formatted ticks
     */
    protected List<NumberTick> formatTicks(List<?> ticks, StringNumberFormat format) {
        Map<Double, String> labels = format.getLabels();
        Vector<Double> values = new Vector<Double>(labels.keySet());
        Collections.sort(values);

        int count = getMajorTickCount(ticks);
        double step = values.size() / count;
        if (step < 1.0) {
            step = 1.0;
            count = values.size();
        }

        List<NumberTick> newTicks = new LinkedList<NumberTick>();
        for (int index = 0; index < count; index++) {
            int pos = (int) (step * index);
            Double val = values.get(pos);
            String label = labels.get(val);

            NumberTick tick = new NumberTick(TickType.MAJOR, val, label,
                    TextAnchor.CENTER, TextAnchor.CENTER, 0);

            newTicks.add(tick);
        }
        return newTicks;
    }
    
    /**
     * Returns tick label format
     * @return the tick label format
     */
    public StringNumberFormat getLabelFormat() {
        return format;
    }

    /**
     * Calculates count of major ticks
     * @param ticks list of ticks
     * @return count of major ticks
     */
    private int getMajorTickCount(List<?> ticks) {
        int count = 0;
        for (Object tick : ticks) {
            if (tick instanceof NumberTick) {
                NumberTick numberTick = (NumberTick) tick;
                if (numberTick.getTickType() == TickType.MAJOR) {
                    count++;
                }
            }
        }
        return count;
    }

    /**
     * Tests whether grid lines are visible
     * @return true if grid lines are visible
     */
    public boolean isGridLineVisible() {
        return showGridLine;
    }

    /**
     * Sets grid lines visibility flag
     * @param visible grid lines visibility flag
     */
    public void setGridLineVisible(boolean visible) {
        showGridLine = visible;
    }
}
