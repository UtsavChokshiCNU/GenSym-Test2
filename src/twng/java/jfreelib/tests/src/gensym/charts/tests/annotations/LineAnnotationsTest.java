package gensym.charts.tests.annotations;

import gensym.charts.tests.TestChartBase;
import gensym.charts.annotations.line.*;
import gensym.charts.*;

import gensym.charts.actions.CreateChartAction;
import gensym.charts.annotations.graph.ext.XYArrowAnnotation;
import java.awt.*;
import java.util.Collection;

import org.jfree.chart.plot.ValueMarker;
import org.jfree.ui.TextAnchor;
import org.jfree.ui.RectangleAnchor;
import org.jfree.ui.Layer;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Line annotations test
 */
public class LineAnnotationsTest extends TestChartBase {

    /**
     * Tests factory
     */
    public void testFactory() {
        LineAnnotationFactory factory = new LineAnnotationFactory();

        int size = 100;
        for (int i = 0; i < size; i++) {
            factory.get(i);
        }

        assertEquals(size, factory.getItems().length);

        factory.clear();
        assertEquals(0, factory.getItems().length);

        Font oldFont = factory.getFont();
        assertNotNull(oldFont);
        factory.setTextSize(65);
        assertNotNull(factory.getFont());
        assertFalse(factory.getFont().equals(oldFont));
    }

    /**
     * Tests annotations
     */
    public void testAnnotations() {
        LineAnnotation annotation = new LineAnnotation();

        int axis = 2;
        annotation.setAxis(axis);
        assertEquals(axis, annotation.getAxis());

        Color color = Color.RED;
        annotation.setColor(color);
        assertEquals(color, annotation.getColor());

        double position = 15;
        annotation.setPosition(position);
        assertEquals(position, annotation.getPosition());

        String text = "text";
        annotation.setText(text);
        assertEquals(text, annotation.getText());

        int type = 123;
        annotation.setType(type);
        assertEquals(type, annotation.getType());

        doTestMarker(7, true);
        doTestMarker(8, true);
        doTestMarker(14, true);
        doTestMarker(15, true);

        doTestMarker(ChartLineTypes.LINE_DASHDOT, false);
        doTestMarker(ChartLineTypes.LINE_EXTRATHICKSOLID, false);

        // Additional arrow test
        XYArrowAnnotation arrow = new XYArrowAnnotation(1, 2, 3, 4);
        assertNotNull(arrow);
        assertTrue(arrow.geRightVisible());
        assertTrue(arrow.getLeftVisible());
        arrow.setLeftVisible(false);
        arrow.setRightVisible(false);
        assertFalse(arrow.geRightVisible());
        assertFalse(arrow.getLeftVisible());
    }

    /**
     * Tests marker
     * @param type line annotaation type
     * @param newType is there used new type
     */
    private void doTestMarker(int type, boolean newType) {
        LineAnnotation annotation = new LineAnnotation();

        Color color = Color.RED;
        annotation.setColor(color);

        annotation.setType(type);

        String text = "text";
        annotation.setText(text);

        ValueMarker marker = annotation.createMarker();
        assertNull(marker);
        annotation.setPosition(10);

        marker = annotation.createMarker();
        assertNotNull(marker);
        assertEquals(color, marker.getPaint());
        assertEquals(text, marker.getLabel());
        assertEquals(TextAnchor.BOTTOM_LEFT, marker.getLabelTextAnchor());
        assertEquals(RectangleAnchor.TOP_LEFT, marker.getLabelAnchor());

        annotation.setText("|r" + text);
        marker = annotation.createMarker();
        assertEquals(color, marker.getPaint());
        assertEquals(text, marker.getLabel());
        assertEquals(TextAnchor.BOTTOM_RIGHT, marker.getLabelTextAnchor());
        assertEquals(RectangleAnchor.TOP_RIGHT, marker.getLabelAnchor());

        if (newType) {
            assertNotSame(marker.getStroke(), ChartLineTypes.makeBasicStroke(type));
        } else {
            assertEquals(marker.getStroke(), ChartLineTypes.makeBasicStroke(type));
        }
    }

    /**
     * Tests properties
     */
    public void testProperties () {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertNotNull(getChart());
        assertEquals(GraphChart.class, getChart().getClass());
        GraphChart chart = (GraphChart) getChart();
        LineAnnotationFactory factory = chart.getAnnotations().getHorizontalLineAnnotations();
        chart.getAnnotations().setAnnotationVisible(true);

        try {
            // horz-line-annotation-axis
            int axis = 0;
            runAction("SetInt", "property", 3003, "i", 0, "j", 0, "value", axis);
            assertEquals(axis, factory.get(0).getAxis());

            // horz-line-annotation-color
            int bgr = 0xFFDD00;
            runAction("SetInt", "property", 3217, "i", 0, "j", 0, "value", bgr);
            assertEquals(ChartsCommon.convertBGRtoRGB(bgr), factory.get(0).getColor().getRGB() & 0xFFFFFF);

            // horz-line-annotation
            double pos = 120;
            Document doc = ChartServer.makeXMLMessage("SetDoubleArray", getHandle());
            ChartServer.addXMLData(doc, "property", 3213, "i", 0, "j", 0);
            Element data = doc.createElement("value");
            doc.getDocumentElement().appendChild(data);
            ChartServer.addXMLElementData(doc, data, "item", pos);
            runAction(doc);

            assertEquals(pos, factory.get(0).getPosition());

            // horz-line-annotation-text
            String text = "test";
            runAction("SetString", "property", 3214, "i", 0, "j", 0, "value", text);
            assertEquals(text, factory.get(0).getText());

            // horz-line-annotation-type
            int type = ChartLineTypes.LINE_EXTRATHICKSOLID;
            runAction("SetInt", "property", 3216, "i", 0, "j", 0, "value", type);
            assertEquals(type, factory.get(0).getType());

            // line-annotation-text-size
            Font oldFont = factory.getFont();
            assertNotNull(oldFont);
            runAction("SetInt", "property", 3244, "i", 0, "j", 0, "value", 50);
            assertNotNull(factory.getFont());
            assertFalse(factory.getFont().equals(oldFont));

            // update chart and test annotations
            runAction("Update");
            Collection<?> markers = chart.getChart().getXYPlot().getRangeMarkers(Layer.FOREGROUND);
            assertEquals(1, markers.size()); // one marker
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
