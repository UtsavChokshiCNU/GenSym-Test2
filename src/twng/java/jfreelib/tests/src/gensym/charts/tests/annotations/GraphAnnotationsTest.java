package gensym.charts.tests.annotations;

import gensym.charts.annotations.graph.*;
import gensym.charts.annotations.graph.ext.PlotShapeAnnotation;
import gensym.charts.annotations.graph.ext.PointerShapeBuilder;
import gensym.charts.axis.MultiAxesPlot;
import gensym.charts.properties.annotations.graph.GraphAnnotationAxisProperty;
import gensym.charts.tests.TestChartBase;
import gensym.charts.GraphChart;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.ChartsCommon;
import gensym.charts.ChartServer;
import gensym.charts.annotations.graph.ext.XYArrowAnnotation;
import gensym.charts.hatching.HatchedPaint;

import gensym.charts.annotations.graph.ext.XYMultiLineAnnotation;
import java.util.Set;
import java.util.LinkedHashSet;
import java.util.List;
import java.awt.Font;
import java.awt.Color;
import java.awt.Shape;
import java.awt.BasicStroke;
import java.awt.Paint;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

import org.jfree.chart.annotations.*;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Graph Annotations test class
 */
public class GraphAnnotationsTest extends TestChartBase {
    /**
     * Tests graph annotations
     */
    public void testAnnotationsFactory() {
        AnnotationFactory factory = new AnnotationFactory();

        int size = 100;
        for (int i = 0; i < size; i++) {
            factory.getInfo(i);
        }

        Set<Integer> ids = new LinkedHashSet<Integer>();
        for (int id : factory.getItems()) {
            assertFalse(ids.contains(id));
            assertTrue(id < size);
            ids.add(id);
        }

        factory.setMovable(true);
        assertTrue(factory.isMovable());
        factory.setMovable(false);
        assertFalse(factory.isMovable());

        Font oldFont = factory.getFont();
        assertNotNull(oldFont);
        factory.setTextSize(65);
        assertNotNull(factory.getFont());
        assertFalse(factory.getFont().equals(oldFont));
    }

    /**
     * Tests graph annotation info
     */
    public void testAnnotationInfo() {
        int id = 10;
        AnnotationFactory factory = new AnnotationFactory();
        AnnotationInfo info = factory.getInfo(id);

        assertEquals(id, info.getId());
        assertEquals(factory, info.getFactory());

        double x = 120;
        info.setX(x);
        assertEquals(x, info.getX());

        double y = 100;
        info.setY(y);
        assertEquals(y, info.getY());

        String text = "test";
        info.setText(text);
        assertEquals(text, info.getText());

        int type = 123;
        info.setType(type);
        assertEquals(type, info.getType());

        Color color = new Color(0xFF00FE);
        info.setColor(color);
        assertEquals(color, info.getColor());

        assertEquals(0, info.getAxis());
        info.setAxis(2);
        assertEquals(2, info.getAxis());
    }

    /**
     * Tests PlotShapeAnnotation
     */
    public void testPlotShapeAnnotation() {
        Shape shape = new Ellipse2D.Double(0, 0, 10, 10);
        double x = 100;
        double y = 130;
        PlotShapeAnnotation annotation = new PlotShapeAnnotation(shape, x, y);
        assertEquals(shape, annotation.getShape());
        assertEquals(annotation, new PlotShapeAnnotation(shape, x, y));
        assertFalse(annotation.equals(new PlotShapeAnnotation(shape, x + 20, y)));
        assertFalse(annotation.equals(null));

        BasicStroke stroke = new BasicStroke(5);
        annotation.setStroke(stroke);
        assertEquals(stroke, annotation.getStroke());

        Color color = new Color(0x00FECC);
        annotation.setFillPaint(color);
        assertEquals(color, annotation.getFillPaint());

        color = new Color(0x00F000);
        annotation.setOutlinePaint(color);
        assertEquals(color, annotation.getOutlinePaint());
    }

    /**
     * Tests Cross annotation
     */
    public void testCrossAnnotation() {
        doTestCross(AnnotationBuildersFactory.PEGAT_CROSS);
        doTestCross(AnnotationBuildersFactory.PEGAT_SMALLCROSS);
        doTestCross(AnnotationBuildersFactory.PEGAT_LARGECROSS);
    }
    
    /**
     * Tests cross
     * @param type cross type
     */
    private void doTestCross(int type) {
        AnnotationInfo info = new AnnotationInfo(1, new AnnotationFactory());
        info.setType(type);
        info.setX(10);
        info.setY(100);
        String text = "cross" + type;
        info.setText("|H10|10|" + text);
        Color color = new Color(0xFFFEFA);
        info.setColor(color);

        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);
        assertEquals(builder.getClass(), CrossAnnotation.class);

        assertFalse(builder.isInfoUsed(null));
        builder.addInfo(null);
        
        assertTrue(builder.isBuildFinished());
        AnnotationWithAxis[] annotations = builder.build();
        assertEquals(2, annotations.length); // text + cross
        assertTrue(annotations[0].getAnnotation() instanceof PlotShapeAnnotation);
        assertTrue(annotations[1].getAnnotation() instanceof XYMultiLineAnnotation);

        PlotShapeAnnotation cross = (PlotShapeAnnotation) annotations[0].getAnnotation();
        assertEquals(cross.getOutlinePaint(), color);

        XYMultiLineAnnotation pointer = (XYMultiLineAnnotation) annotations[1].getAnnotation();
        assertEquals(pointer.getText(), text);
        assertEquals(pointer.getPaint(), color);
        
        Rectangle2D r2d = null;
        switch (type) {
            case AnnotationBuildersFactory.PEGAT_CROSS:
                r2d = new Rectangle2D.Double(-12.0, -12.0, 24.0, 24.0);
                break;
            case AnnotationBuildersFactory.PEGAT_SMALLCROSS:
                r2d = new Rectangle2D.Double(-7.0, -7.0, 14.0, 14.0);
                break;
            case AnnotationBuildersFactory.PEGAT_LARGECROSS:
                r2d = new Rectangle2D.Double(-19.0, -19.0, 38.0, 38.0);
                break;
        }
        assertEquals(r2d, cross.getShape().getBounds2D());
    }

    /**
     * Tests Line annotation
     */
    public void testLineAnnotation() {
        doTestLine(AnnotationBuildersFactory.PEGAT_EXTRATHINSOLID);
        doTestLine(AnnotationBuildersFactory.PEGAT_THINSOLIDLINE);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMSOLIDLINE);
        doTestLine(AnnotationBuildersFactory.PEGAT_THICKSOLIDLINE);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHINSOLID);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHICKSOLID);
        doTestLine(AnnotationBuildersFactory.PEGAT_EXTRATHICKSOLID);
        doTestLine(AnnotationBuildersFactory.PEGAT_DASHLINE);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHINDASH);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMDASH);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHICKDASH);
        doTestLine(AnnotationBuildersFactory.PEGAT_THICKDASH);
        doTestLine(AnnotationBuildersFactory.PEGAT_EXTRATHICKDASH);
        doTestLine(AnnotationBuildersFactory.PEGAT_DOTLINE);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHINDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHICKDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_THICKDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_EXTRATHICKDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_DASHDOTLINE);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHINDASHDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMDASHDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHICKDASHDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_THICKDASHDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_EXTRATHICKDASHDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_DASHDOTDOTLINE);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHINDASHDOTDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMDASHDOTDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_MEDIUMTHICKDASHDOTDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_THICKDASHDOTDOT);
        doTestLine(AnnotationBuildersFactory.PEGAT_EXTRATHICKDASHDOTDOT);
    }

    /**
     * Create annotation info
     * @param type  the annotation info type
     * @param color the color of annotation
     * @param text the annotation label
     * @return annotation info
     */
    private AnnotationInfo createAnnotationInfo(int type, Color color, String text) {
        AnnotationInfo info = new AnnotationInfo(1, new AnnotationFactory());
        info.setType(type);
        info.setX(100);
        info.setY(120);
        info.setText(text);
        info.setColor(color);
        return info;
    }

    /**
     * Tests line
     * @param type line type
     */
    private void doTestLine(int type) {
        AnnotationInfo info = new AnnotationInfo(1, new AnnotationFactory());
        info.setType(type);
        info.setX(100);
        info.setY(120);
        String text = "line" + type;
        info.setText(text);
        Color color = new Color(0xFFFEFA);
        info.setColor(color);

        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);
        assertTrue(builder instanceof LineAnnotation);

        assertFalse(builder.isBuildFinished());

        // wrong data
        info.setType(AnnotationBuildersFactory.PEGAT_CROSS);
        assertFalse(builder.isInfoUsed(info));
        builder.addInfo(info);

        // next point
        info.setType(LineAnnotation.PEGAT_LINECONTINUE);
        info.setText("");
        info.setX(110);
        assertTrue(builder.isInfoUsed(info));
        builder.addInfo(info);

        // last point
        String lastText = "last" + type;
        info.setText(lastText);
        info.setColor(null);
        info.setY(150);
        builder.addInfo(info);

        assertFalse(builder.isBuildFinished());
        AnnotationWithAxis[] annotations = builder.build();
        assertEquals(annotations.length, 4); // text + line + line + text

        assertTrue(annotations[0].getAnnotation() instanceof XYMultiLineAnnotation);
        XYMultiLineAnnotation pointer = (XYMultiLineAnnotation) annotations[0].getAnnotation();
        assertEquals(pointer.getText(), text);
        assertEquals(pointer.getPaint(), color);

        assertTrue(annotations[3].getAnnotation() instanceof XYMultiLineAnnotation);
        pointer = (XYMultiLineAnnotation) annotations[3].getAnnotation();
        assertEquals(pointer.getText(), lastText);
        assertEquals(pointer.getPaint(), color);

        assertTrue(annotations[1].getAnnotation() instanceof XYLineAnnotation);
        assertTrue(annotations[2].getAnnotation() instanceof XYLineAnnotation);
    }

    /**
     * Tests all poly annotations
     */
    public void testPolyLineAndPolygon() {
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYGON);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_THIN);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_MEDIUM);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_THICK);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_DASH);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_DOT);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_DASHDOT);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_DASHDOTDOT);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_MEDIUMDASH);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_MEDIUMDOT);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_MEDIUMDASHDOT);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_MEDIUMDASHDOTDOT);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_THICKDASH);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_THICKDOT);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_THICKDASHDOT);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYLINE_THICKDASHDOTDOT);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_HORIZONTAL);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_VERTICAL);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_FDIAGONAL);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_BDIAGONAL);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_CROSS);
        testPolyAnnotation(StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_DIAGCROSS);
    }

    /**
     * Tests poly annotation
     * @param type of annotation
     */
   private final void testPolyAnnotation(int type) {
        AnnotationInfo info = new AnnotationInfo(1, new AnnotationFactory());
        info.setType(AnnotationBuildersFactory.PEGAT_STARTPOLY);
        String text = "Pointer";
        info.setText(text);
        Color color = new Color(0xFFFEFA);
        info.setColor(color);

        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);
        assertTrue(builder instanceof StartPolyAnnotation);
        assertFalse(builder.isBuildFinished());

        // next point
        info.setType(StartPolyAnnotation.PEGAT_ADDPOLYPOINT);
        info.setText("");
        info.setX(100);
        assertTrue(builder.isInfoUsed(info));
        builder.addInfo(info);
        assertFalse(builder.isBuildFinished());

        // wrong data
        info.setType(AnnotationBuildersFactory.PEGAT_CROSS);
        assertFalse(builder.isInfoUsed(info));
        builder.addInfo(info);

        // last point
        info.setType(type);
        String endText = "End";
        info.setText(endText);
        info.setY(100);
        assertTrue(builder.isInfoUsed(info));
        builder.addInfo(info);
        assertTrue(builder.isBuildFinished());

        // test
        AnnotationWithAxis[] annotations = builder.build();
        assertEquals(annotations.length, 3); // text + poly + text
        assertTrue(annotations[0].getAnnotation() instanceof XYMultiLineAnnotation);
        assertTrue(annotations[1].getAnnotation() instanceof XYPolygonAnnotation);
        assertTrue(annotations[2].getAnnotation() instanceof XYMultiLineAnnotation);

        XYMultiLineAnnotation pointer = (XYMultiLineAnnotation) annotations[0].getAnnotation();
        assertEquals(pointer.getText(), text);
        assertEquals(pointer.getPaint(), color);

        XYPolygonAnnotation poly = (XYPolygonAnnotation) annotations[1].getAnnotation();
        if (getPaint(type, color) != null) {
            assertEquals(poly.getFillPaint().getClass(), getPaint(type, color).getClass());
        }

        pointer = (XYMultiLineAnnotation) annotations[2].getAnnotation();
        assertEquals(pointer.getText(), endText);
        assertEquals(pointer.getPaint(), color);
    }

    /**
     * Gets figure paint
     * @param type of figure
     * @param color of lines
     * @return new Paint
     */
    private Paint getPaint(int type, Color color) {
        Paint paint = null;
        switch (type) {
            case StartPolyAnnotation.PEGAT_ENDPOLYGON:
                paint = color;
                break;
            case StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_HORIZONTAL:
                paint = new HatchedPaint(HatchedPaint.HORIZONTAL_LINE, color, null);
                break;
            case StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_VERTICAL:
                paint = new HatchedPaint(HatchedPaint.VERTICAL_LINE, color, null);
                break;
            case StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_FDIAGONAL:
                paint = new HatchedPaint(HatchedPaint.LU_RB_DIAGONAL_LINE, color, null);
                break;
            case StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_BDIAGONAL:
                paint = new HatchedPaint(HatchedPaint.LB_RU_DIAGONAL_LINE, color, null);
                break;
            case StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_CROSS:
                paint = new HatchedPaint(HatchedPaint.HORIZONTAL_LINE | HatchedPaint.VERTICAL_LINE, color, null);
                break;
            case StartPolyAnnotation.PEGAT_ENDPOLYGON_HATCH_DIAGCROSS:
                paint = new HatchedPaint(HatchedPaint.LU_RB_DIAGONAL_LINE | HatchedPaint.LB_RU_DIAGONAL_LINE, color, null);
                break;
        }
        return paint;
    }

    /**
     * Tests text annotation
     */
    public void testTextAnnotation() {
        AnnotationInfo info = new AnnotationInfo(1, new AnnotationFactory());
        info.setType(AnnotationBuildersFactory.PEGAT_STARTTEXT);
        String text1 = "Start";
        info.setText(text1);
        Color color = new Color(0xFFFEFA);
        info.setColor(color);

        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);
        assertEquals(builder.getClass(), StartTextAnnotation.class);
        assertFalse(builder.isBuildFinished());

        assertEquals(0, builder.build() != null ? builder.build().length : 0);

        // wrong data
        info.setType(AnnotationBuildersFactory.PEGAT_CROSS);
        assertFalse(builder.isInfoUsed(info));
        builder.addInfo(info);

        // next text
        info.setType(StartTextAnnotation.PEGAT_ADDTEXT);
        String text2 = "End";
        info.setText(text2);
        assertTrue(builder.isInfoUsed(info));
        builder.addInfo(info);
        assertFalse(builder.isBuildFinished());

        // last text
        info.setType(StartTextAnnotation.PEGAT_PARAGRAPH);
        String text3 = "--";
        info.setText(text3);
        double x = 100;
        double y = 150;
        info.setX(x);
        info.setY(y);
        color = Color.GREEN;
        info.setColor(color);
        assertTrue(builder.isInfoUsed(info));
        builder.addInfo(info);
        assertTrue(builder.isBuildFinished());

        // test
        AnnotationWithAxis[] annotations = builder.build();
        assertEquals(annotations.length, 1); // text
        assertTrue(annotations[0].getAnnotation() instanceof XYTextAnnotation);

        XYTextAnnotation annotation = (XYTextAnnotation) annotations[0].getAnnotation();
        assertEquals(annotation.getText(), text1 + text2);
        assertEquals(annotation.getPaint(), color);
        assertEquals(x, annotation.getX());
        assertEquals(y, annotation.getY());
    }

    /**
     * Tests ellipse annotation
     */
    public void testFigureAnnotation() {
        Point2D point1 = new Point2D.Double(100, 0);
        Point2D point2 = new Point2D.Double(0, 100);

        for (int type = TopLeftBottomRightAnnotation.PEGAT_RECT_THIN;
                type < TopLeftBottomRightAnnotation.PEGAT_ELLIPSE_FILL; type++) {

            doTestFigure(TopLeftBottomRightAnnotation.PEGAT_BOTTOMRIGHT, point1,
                    TopLeftBottomRightAnnotation.PEGAT_TOPLEFT, point2, type);

            doTestFigure(TopLeftBottomRightAnnotation.PEGAT_TOPLEFT, point1,
                    TopLeftBottomRightAnnotation.PEGAT_BOTTOMRIGHT, point2, type);
        }

        for (int type = TopLeftBottomRightAnnotation.PEGAT_RECT_MEDIUMDASH;
                type < TopLeftBottomRightAnnotation.PEGAT_ELLIPSE_THICKDASHDOTDOT; type++) {

            doTestFigure(TopLeftBottomRightAnnotation.PEGAT_BOTTOMRIGHT, point1,
                    TopLeftBottomRightAnnotation.PEGAT_TOPLEFT, point2, type);

            doTestFigure(TopLeftBottomRightAnnotation.PEGAT_TOPLEFT, point1,
                    TopLeftBottomRightAnnotation.PEGAT_BOTTOMRIGHT, point2, type);
        }

        for (int type = TopLeftBottomRightAnnotation.PEGAT_RECT_HATCH_HORIZONTAL;
                type < TopLeftBottomRightAnnotation.PEGAT_ELLIPSE_HATCH_DIAGCROSS; type++) {

            doTestFigure(TopLeftBottomRightAnnotation.PEGAT_BOTTOMRIGHT, point1,
                    TopLeftBottomRightAnnotation.PEGAT_TOPLEFT, point2, type);

            doTestFigure(TopLeftBottomRightAnnotation.PEGAT_TOPLEFT, point1,
                    TopLeftBottomRightAnnotation.PEGAT_BOTTOMRIGHT, point2, type);
        }

    }

    /**
     * Test ellipse
     * @param type1 first point type (TopLeftBottomRightAnnotation.PEGAT_BOTTOMRIGHT or TopLeftBottomRightAnnotation.PEGAT_TOPLEFT)
     * @param point1 first point
     * @param type2 second point type (TopLeftBottomRightAnnotation.PEGAT_BOTTOMRIGHT or TopLeftBottomRightAnnotation.PEGAT_TOPLEFT)
     * @param point2 second point
     */
    private void doTestFigure(int type1, Point2D point1, int type2, Point2D point2, int type) {
        AnnotationInfo info = new AnnotationInfo(1, new AnnotationFactory());
        info.setType(type1);
        Color color = new Color(0xFFFEFA);
        info.setColor(color);
        info.setX(point1.getX());
        info.setY(point1.getY());

        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);
        assertEquals(builder.getClass(), TopLeftBottomRightAnnotation.class);
        assertFalse(builder.isBuildFinished());

        // wrong data
        info.setType(AnnotationBuildersFactory.PEGAT_CROSS);
        assertFalse(builder.isInfoUsed(info));
        builder.addInfo(info);

        // 2nd point
        info.setType(type1);
        info.setX(point2.getX());
        info.setY(point2.getY());
        info.setType(type2);
        assertTrue(builder.isInfoUsed(info));
        builder.addInfo(info);
        assertFalse(builder.isBuildFinished());

        // last
        info.setType(type);
        String text = "test";
        info.setText(text);
        color = Color.DARK_GRAY;
        info.setColor(color);
        assertTrue(builder.isInfoUsed(info));
        builder.addInfo(info);
        assertTrue(builder.isBuildFinished());

        // test
        AnnotationWithAxis[] annotations = builder.build();
        assertEquals(annotations.length, 2); // ellipse + text
        assertTrue(annotations[0].getAnnotation() instanceof XYShapeAnnotation);
        assertTrue(annotations[1].getAnnotation() instanceof XYMultiLineAnnotation);
        XYMultiLineAnnotation pointer = (XYMultiLineAnnotation) annotations[1].getAnnotation();
        assertEquals(pointer.getText(), text);
        assertEquals(pointer.getPaint(), color);
    }

    /**
     * Tests other things
     */
    public void testOther() {
        AnnotationInfo info = createAnnotationInfo(-1, null, "Test");
        assertNull(AnnotationBuildersFactory.createBuilder(info));
    }

    /**
     * Tests graph annotation properties.
     * Creates Cross and line with text
     */
    public void testProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertNotNull(getChart());
        assertEquals(GraphChart.class, getChart().getClass());
        GraphChart chart = (GraphChart) getChart();
        AnnotationFactory factory = chart.getAnnotations().getGraphAnnotations();

        chart.getAnnotations().setAnnotationVisible(true);

        try {
            // graph-annotation-color
            int bgr = 0x00FFFE;
            runAction("SetInt", "property", 3236, "i", 0, "j", 0, "value", bgr);
            assertNotNull(factory.getInfo(0).getColor());
            assertEquals(ChartsCommon.convertBGRtoRGB(bgr), factory.getInfo(0).getColor().getRGB() & 0xFFFFFF);
            runAction("SetInt", "property", 3236, "i", 1, "j", 0, "value", bgr);
            assertNotNull(factory.getInfo(1).getColor());
            assertEquals(ChartsCommon.convertBGRtoRGB(bgr), factory.getInfo(1).getColor().getRGB() & 0xFFFFFF);

            // graph-annotmoveable
            runAction("SetInt", "property", 2324, "i", 0, "j", 0, "value", 1);
            assertTrue(factory.isMovable());
            runAction("SetInt", "property", 2324, "i", 0, "j", 0, "value", 0);
            assertFalse(factory.isMovable());

            // graph-annotation-text
            String text = "Text";
            runAction("SetString", "property", 3293, "i", 1, "j", 0, "value", text);
            assertEquals(text, factory.getInfo(1).getText());

            // graph-annotation-text-size
            Font oldFont = factory.getFont();
            assertNotNull(oldFont);
            runAction("SetInt", "property", 3242, "i", 0, "j", 0, "value", 85);
            assertNotNull(factory.getFont());
            assertFalse(factory.getFont().equals(oldFont));

            // graph-annotation-x
            double x1 = 120;
            double x2 = 100;
            Document xdoc = ChartServer.makeXMLMessage("SetDoubleArray", getHandle());
            ChartServer.addXMLData(xdoc, "property", 3291, "i", 0, "j", 0);
            Element xdata = xdoc.createElement("value");
            xdoc.getDocumentElement().appendChild(xdata);
            ChartServer.addXMLElementData(xdoc, xdata, "item", x1);
            ChartServer.addXMLElementData(xdoc, xdata, "item", x2);
            runAction(xdoc);

            assertEquals(x1, factory.getInfo(0).getX());
            assertEquals(x2, factory.getInfo(1).getX());

            // simple graph-annotation-x
            double x3 = 12;
            runAction("SetDouble", "property", 3291, "i", 2, "j", 0, "value", x3);
            assertEquals(x3, factory.getInfo(2).getX());

            // graph-annotation-y
            double y1 = 120;
            double y2 = 130;
            Document ydoc = ChartServer.makeXMLMessage("SetDoubleArray", getHandle());
            ChartServer.addXMLData(ydoc, "property", 3292, "i", 0, "j", 0);
            Element ydata = ydoc.createElement("value");
            ydoc.getDocumentElement().appendChild(ydata);
            ChartServer.addXMLElementData(ydoc, ydata, "item", y1);
            ChartServer.addXMLElementData(ydoc, ydata, "item", y2);
            runAction(ydoc);

            assertEquals(y1, factory.getInfo(0).getY());
            assertEquals(y2, factory.getInfo(1).getY());

            // simple graph-annotation-y
            double y3 = 42;
            runAction("SetDouble", "property", 3292, "i", 2, "j", 0, "value", y3);
            assertEquals(y3, factory.getInfo(2).getY());

            // graph-annotation-type
            runAction("SetInt", "property", 3246, "i", 0, "j", 0, "value", AnnotationBuildersFactory.PEGAT_CROSS);
            assertEquals(AnnotationBuildersFactory.PEGAT_CROSS, factory.getInfo(0).getType());

            runAction("SetInt", "property", 3246, "i", 1, "j", 0, "value", AnnotationBuildersFactory.PEGAT_THICKSOLIDLINE);
            assertEquals(AnnotationBuildersFactory.PEGAT_THICKSOLIDLINE, factory.getInfo(1).getType());

            runAction("SetInt", "property", 3246, "i", 2, "j", 0, "value", AnnotationBuildersFactory.PEGAT_THICKSOLIDLINE);
            assertEquals(AnnotationBuildersFactory.PEGAT_THICKSOLIDLINE, factory.getInfo(1).getType());

            runAction("SetInt", "property", 3246, "i", 2, "j", 0, "value", AnnotationBuildersFactory.PEGAT_THICKSOLIDLINE);
            assertEquals(AnnotationBuildersFactory.PEGAT_THICKSOLIDLINE, factory.getInfo(2).getType());

            runAction("SetInt", "property", 3246, "i", 3, "j", 0, "value", LineAnnotation.PEGAT_LINECONTINUE);
            assertEquals(LineAnnotation.PEGAT_LINECONTINUE, factory.getInfo(3).getType());

            runAction("SetInt", "property", 3246, "i", 3, "j", 0, "value", LineAnnotation.PEGAT_VECTOR_SMALL);
            assertEquals(LineAnnotation.PEGAT_VECTOR_SMALL, factory.getInfo(3).getType());
            runAction("Update");

            runAction("SetInt", "property", 3246, "i", 3, "j", 0, "value", LineAnnotation.PEGAT_VECTOR_MEDIUM);
            assertEquals(LineAnnotation.PEGAT_VECTOR_MEDIUM, factory.getInfo(3).getType());
            runAction("Update");

            runAction("SetInt", "property", 3246, "i", 3, "j", 0, "value", LineAnnotation.PEGAT_VECTOR_LARGE);
            assertEquals(LineAnnotation.PEGAT_VECTOR_LARGE, factory.getInfo(3).getType());
            runAction("Update");
            XYPlot plot = chart.getChart().getXYPlot();
            plot.setOrientation(PlotOrientation.HORIZONTAL);
            assertEquals(plot.getOrientation(), PlotOrientation.HORIZONTAL);

            runAction("SetInt", "property", 3246, "i", 3, "j", 0, "value", LineAnnotation.PEGAT_ARROW_SMALL);
            assertEquals(LineAnnotation.PEGAT_ARROW_SMALL, factory.getInfo(3).getType());
            runAction("Update");

            runAction("SetInt", "property", 3246, "i", 3, "j", 0, "value", LineAnnotation.PEGAT_ARROW_MEDIUM);
            assertEquals(LineAnnotation.PEGAT_ARROW_MEDIUM, factory.getInfo(3).getType());
            runAction("Update");

            runAction("SetInt", "property", 3246, "i", 3, "j", 0, "value", LineAnnotation.PEGAT_ARROW_LARGE);
            assertEquals(LineAnnotation.PEGAT_ARROW_LARGE, factory.getInfo(3).getType());
            runAction("Update");

            List<?> annotations = chart.getChart().getXYPlot().getAnnotations();
            assertEquals(annotations.size(), 3); // cross + text + line
            assertTrue(annotations.get(0) instanceof PlotShapeAnnotation);
            assertTrue(annotations.get(1) instanceof XYArrowAnnotation);
            assertTrue(annotations.get(2) instanceof XYMultiLineAnnotation);

            int firstAxis = 0;
            int secondAxis = 1;
            int multiaxesSubsetsPropertyId = 3001;
            runAction("SetInt", "property", multiaxesSubsetsPropertyId, "i", 0, "j", 0, "value", 1);
            runAction("SetInt", "property", multiaxesSubsetsPropertyId, "i", 1, "j", 0, "value", 1);

            runAction("SetInt", "property", 3002, "i", 0, "j", 0, "value", secondAxis);
            assertEquals(secondAxis, factory.getInfo(0).getAxis());

            runAction("Update");

            annotations = chart.getPlot().getPlot(firstAxis).getAnnotations();
            assertEquals(2, annotations.size()); // line + text

            assertTrue(annotations.get(0) instanceof XYArrowAnnotation);
            assertTrue(annotations.get(1) instanceof XYMultiLineAnnotation);

            annotations = chart.getPlot().getPlot(secondAxis).getAnnotations();
            assertEquals(1, annotations.size()); // cross
            assertTrue(annotations.get(0) instanceof PlotShapeAnnotation);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests pointer annotation
     */
     public void testBaseShapeAnnotation() {
        Color color = new Color(0xFFFEFA);
        String text = "Base shape annotation";
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_POINTER, color, text);

        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);
        assertTrue(builder instanceof BaseShapeAnnotation);

        assertTrue(builder.isBuildFinished());
        AnnotationWithAxis[] annotations = builder.build();
        assertEquals(annotations.length, 2); // pointer + text
        assertTrue(annotations[0].getAnnotation() instanceof PlotShapeAnnotation);
        assertTrue(annotations[1].getAnnotation() instanceof XYMultiLineAnnotation);

        PlotShapeAnnotation pointer = (PlotShapeAnnotation) annotations[0].getAnnotation();
        assertEquals(new BasicStroke(0.5f), pointer.getStroke());
        assertEquals(color, pointer.getFillPaint());
        assertEquals(color, pointer.getOutlinePaint());

        XYMultiLineAnnotation textAnnotation = (XYMultiLineAnnotation) annotations[1].getAnnotation();
        assertEquals(100.0, textAnnotation.getX());
        assertEquals(120.0, textAnnotation.getY());
        assertEquals(text, textAnnotation.getText());
        assertEquals(color, textAnnotation.getPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_DOT);
        builder = AnnotationBuildersFactory.createBuilder(info);
        assertTrue(builder instanceof BaseShapeAnnotation);
        annotations = builder.build();
        assertEquals(annotations.length, 2); // dot + text
        pointer = (PlotShapeAnnotation) annotations[0].getAnnotation();
        assertEquals(null, pointer.getFillPaint());
        assertEquals(color, pointer.getOutlinePaint());
        assertEquals(color, textAnnotation.getPaint());

        info.setColor(null);
        builder = AnnotationBuildersFactory.createBuilder(info);
        annotations = builder.build();
        pointer = (PlotShapeAnnotation) annotations[0].getAnnotation();
        assertEquals(null, pointer.getFillPaint());
        assertEquals(PlotShapeAnnotation.DEFAULT_OUTLINE_PAINT, pointer.getOutlinePaint());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;
        assertEquals(17.0, bsa.getLabelOffset(new Rectangle2D.Double(0, 2, 20, 10)));
        assertEquals(13.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));
    }

    /**
     * Tests pointer annotation
     */
  public void testPoiterAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_POINTER, color, "Pointer");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertEquals(builder.getClass(), PointerAnnotation.class);

        assertTrue(builder.isBuildFinished());
        AnnotationWithAxis[] annotations = builder.build();

        assertEquals(color, ((PlotShapeAnnotation) annotations[0].getAnnotation()).getFillPaint());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;
        int incorrectType = -100;
        assertEquals(null, bsa.createShape(incorrectType));

        assertEquals(15.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -12, 20, 10)));
        assertEquals(5.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));

        info.setType(AnnotationBuildersFactory.PEGAT_POINTER);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(-2.4692208302432412, -14.14213562373095, 16.611356453974192, 16.61135645397419),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_POINTER_VECTOR_SMALL);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(0.0, -21.213203435596423, 21.213203435596427, 21.213203435596423),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_POINTER_VECTOR_MEDIUM);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(0.0, -32.17335854398791, 32.173358543987916, 32.17335854398791),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_POINTER_VECTOR_LARGE);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(0.0, -43.13351365237939, 43.1335136523794, 43.13351365237939),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_POINTER_ARROW_SMALL);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(0.0, -21.213203435596423, 21.213203435596427, 21.213203435596423),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_POINTER_ARROW_MEDIUM);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(0.0, -32.17335854398791, 32.173358543987916, 32.17335854398791),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_POINTER_ARROW_LARGE);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(0.0, -43.13351365237939, 43.1335136523794, 43.13351365237939),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());
    }

    /**
     * Tests arrow annotation
     */
    public void testArrowAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_ARROW_N, color, "Arrow");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertTrue(builder instanceof ArrowAnnotation);

        assertTrue(builder.isBuildFinished());
        AnnotationWithAxis[] annotations = builder.build();

        assertEquals(color, ((PlotShapeAnnotation) annotations[0].getAnnotation()).getFillPaint());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;

        assertEquals(15.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -12, 20, 10)));
        assertEquals(5.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));

        int incorrectType = -100;
        assertEquals(null, bsa.createShape(incorrectType));

        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(-4.166666507720947, 0.0, 8.333333015441895, 10.0),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_ARROW_NE);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(-7.071067811865475, 0.0, 7.0710678118654755, 7.0710678118654755),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_ARROW_E);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(-10.0, -4.166666507720947, 10.0, 8.333333015441895),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_ARROW_SE);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(-7.071067811865477, -7.071067811865475, 7.071067811865477, 7.0710678118654755),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_ARROW_S);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(-4.166666507720947, -10.0, 8.333333015441895, 10.0),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_ARROW_SW);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(-1.3322676295501878E-15, -7.071067811865477, 7.0710678118654755, 7.071067811865477),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_ARROW_W);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(0.0, -4.166666507720947, 10.0, 8.333333015441895),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

        info.setType(AnnotationBuildersFactory.PEGAT_ARROW_NW);
        annotations = AnnotationBuildersFactory.createBuilder(info).build();
        assertEquals(new Rectangle2D.Double(0.0, -4.440892098500626E-16, 7.0710678118654755, 7.0710678118654755),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());

    }

    /**
     * Tests dash annotation
     */
    public void testDashAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_DASH, color, "Dash");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertEquals(builder.getClass(), DashAnnotation.class);

        assertTrue(builder.isBuildFinished());
        AnnotationWithAxis[] annotations = builder.build();

        assertEquals(null, ((PlotShapeAnnotation) annotations[0].getAnnotation()).getFillPaint());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;
        assertEquals(17.0, bsa.getLabelOffset(new Rectangle2D.Double(0, 2, 20, 10)));
        assertEquals(13.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));

        assertEquals(Rectangle2D.Double.class, ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getClass());
        assertEquals(new Rectangle2D.Double(-7.0, 0.0, 14.0, 0.05),
                    ((PlotShapeAnnotation)annotations[0].getAnnotation()).getShape().getBounds2D());
    }

    /**
     * Tests diamond annotation
     */
    public void testDiamondAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_DIAMOND, color, "Diamond");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertTrue(builder instanceof DiamondAnnotation);
        assertTrue(builder.isBuildFinished());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;

        assertEquals(17.0, bsa.getLabelOffset(new Rectangle2D.Double(0, 2, 20, 10)));
        assertEquals(13.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));

        PlotShapeAnnotation pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-12.0, -12.0, 24.0, 24.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_DIAMONDSOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-12.0, -12.0, 24.0, 24.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLDIAMOND);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-7.0, -7.0, 14.0, 14.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLDIAMONDSOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-7.0, -7.0, 14.0, 14.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGEDIAMOND);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-19.0, -19.0, 38.0, 38.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGEDIAMONDSOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-19.0, -19.0, 38.0, 38.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());
    }

    /**
     * Tests square annotation
     */
    public void testSquareAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_SQUARE, color, "Square");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertEquals(builder.getClass(), SquareAnnotation.class);
        assertTrue(builder.isBuildFinished());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;

        assertEquals(17.0, bsa.getLabelOffset(new Rectangle2D.Double(0, 2, 20, 10)));
        assertEquals(13.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));

        PlotShapeAnnotation pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-11.313708498984761, -11.313708498984761, 22.627416997969522, 22.627416997969522),
                     pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SQUARESOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-11.313708498984761, -11.313708498984761, 22.627416997969522, 22.627416997969522),
                     pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLSQUARE);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-6.3639610306789285, -6.3639610306789285, 12.727922061357857, 12.727922061357857),
                     pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLSQUARESOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-6.3639610306789285, -6.3639610306789285, 12.727922061357857, 12.727922061357857),
                     pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGESQUARE);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-18.38477631085024, -18.38477631085024, 36.76955262170048, 36.76955262170048),
                     pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGESQUARESOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-18.38477631085024, -18.38477631085024, 36.76955262170048, 36.76955262170048),
                     pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());
    }

    /**
     * Tests up-triangle annotation
     */
    public void testUpTriangleAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_UPTRIANGLE, color, "UpTriangle");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertEquals(builder.getClass(), UpTriangleAnnotation.class);
        assertTrue(builder.isBuildFinished());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;
        assertEquals(17.0, bsa.getLabelOffset(new Rectangle2D.Double(0, 2, 20, 10)));
        assertEquals(13.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));

        PlotShapeAnnotation pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-12.0, -12.0, 24.0, 24.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_UPTRIANGLESOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-12.0, -12.0, 24.0, 24.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLUPTRIANGLE);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-7.0, -7.0, 14.0, 14.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLUPTRIANGLESOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-7.0, -7.0, 14.0, 14.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGEUPTRIANGLE);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-19.0, -19.0, 38.0, 38.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGEUPTRIANGLESOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-19.0, -19.0, 38.0, 38.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());
    }

    /**
     * Tests down-triangle annotation
     */
    public void testDownTriangleAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_DOWNTRIANGLE, color, "DownTriangle");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertEquals(builder.getClass(), DownTriangleAnnotation.class);
        assertTrue(builder.isBuildFinished());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;
        assertEquals(17.0, bsa.getLabelOffset(new Rectangle2D.Double(0, 2, 20, 10)));
        assertEquals(13.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));

        PlotShapeAnnotation pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-12.0, -12.0, 24.0, 24.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_DOWNTRIANGLESOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-12.0, -12.0, 24.0, 24.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLDOWNTRIANGLE);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-7.0, -7.0, 14.0, 14.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLDOWNTRIANGLESOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-7.0, -7.0, 14.0, 14.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGEDOWNTRIANGLE);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-19.0, -19.0, 38.0, 38.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGEDOWNTRIANGLESOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-19.0, -19.0, 38.0, 38.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());
    }

    /**
     * Tests dot annotation
     */
    public void testDotAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_DOT, color, "Dot");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertEquals(builder.getClass(), DotAnnotation.class);
        assertTrue(builder.isBuildFinished());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;
        assertEquals(17.0, bsa.getLabelOffset(new Rectangle2D.Double(0, 2, 20, 10)));
        assertEquals(13.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));

        PlotShapeAnnotation pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(Ellipse2D.Double.class, pa.getShape().getClass());
        assertEquals(new Rectangle2D.Double(-11.0, -11.0, 22.0, 22.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_DOTSOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(Ellipse2D.Double.class, pa.getShape().getClass());
        assertEquals(new Rectangle2D.Double(-11.0, -11.0, 22.0, 22.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLDOT);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(Ellipse2D.Double.class, pa.getShape().getClass());
        assertEquals(new Rectangle2D.Double(-4.0, -4.0, 8.0, 8.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLDOTSOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(Ellipse2D.Double.class, pa.getShape().getClass());
        assertEquals(new Rectangle2D.Double(-4.0, -4.0, 8.0, 8.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGEDOT);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(Ellipse2D.Double.class, pa.getShape().getClass());
        assertEquals(new Rectangle2D.Double(-16.0, -16.0, 32.0, 32.0), pa.getShape().getBounds2D());
        assertEquals(null, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGEDOTSOLID);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(Ellipse2D.Double.class, pa.getShape().getClass());
        assertEquals(new Rectangle2D.Double(-16.0, -16.0, 32.0, 32.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());
    }

    /**
     * Tests plus annotation
     */
    public void testPlusAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_PLUS, color, "Plus");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertEquals(builder.getClass(), PlusAnnotation.class);
        assertTrue(builder.isBuildFinished());

        BaseShapeAnnotation bsa = (BaseShapeAnnotation)builder;
        assertEquals(17.0, bsa.getLabelOffset(new Rectangle2D.Double(0, 2, 20, 10)));
        assertEquals(13.0, bsa.getLabelOffset(new Rectangle2D.Double(0, -2, 20, 10)));

        PlotShapeAnnotation pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-12.0, -12.0, 24.0, 24.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_SMALLPLUS);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-7.0, -7.0, 14.0, 14.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());

        info.setType(AnnotationBuildersFactory.PEGAT_LARGEPLUS);
        pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(new Rectangle2D.Double(-19.0, -19.0, 38.0, 38.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());
    }

    /**
     * Tests pixel annotation
     */
    public void testPixelAnnotation() {
        Color color = new Color(0xFFFEFA);
        AnnotationInfo info = createAnnotationInfo(AnnotationBuildersFactory.PEGAT_PIXEL, color, "Pixel");
        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);

        assertTrue(builder instanceof BaseShapeAnnotation);
        assertEquals(builder.getClass(), DotAnnotation.class);
        assertTrue(builder.isBuildFinished());

        PlotShapeAnnotation pa = (PlotShapeAnnotation)AnnotationBuildersFactory.createBuilder(info).build()[0].getAnnotation();
        assertEquals(Ellipse2D.Double.class, pa.getShape().getClass());
        assertEquals(new Rectangle2D.Double(-1.0, -1.0, 2.0, 2.0), pa.getShape().getBounds2D());
        assertEquals(color, pa.getFillPaint());
    }
    
    /**
     * Tests pointer shape builder
     */
    public void testPointerShapeBuilder() {
        PointerShapeBuilder psb = new PointerShapeBuilder();
        assertNotNull(psb);

        assertEquals(100.0, psb.getLength());

        assertEquals(1.0/3.0, psb.getArrowToLengthRatio());
        
        assertEquals(Math.PI/4.0, psb.getArrowAngle());
        
        assertEquals(0.0, psb.getLineThickness());
        
        psb.setLength(80);
        assertEquals(80.0, psb.getLength());
        
        psb.setArrowToLengthRatio(1/4.0);
        assertEquals(1.0/4.0, psb.getArrowToLengthRatio());

        psb.setArrowAngle(Math.PI/3.0);
        assertEquals(Math.PI/3.0, psb.getArrowAngle());
        
        psb.setLineThickness(0.45);
        assertEquals(0.45, psb.getLineThickness());
        
        assertEquals(new Rectangle2D.Double(-20.0, -20.0, 100.0, 40.0), psb.buildPointer().getBounds2D());
        assertEquals(new Rectangle2D.Double(0.0, -0.22499999403953552, 80.0, 35.09101638197899), psb.buildVector().getBounds2D());
        assertEquals(new Rectangle2D.Double(0.0, -34.86601638793945, 80.0, 69.7320327758789), psb.buildArrow().getBounds2D());

        assertFalse(psb.buildPointer().equals(psb.buildPointer(Math.PI/2)));
        assertFalse(psb.buildVector().equals(psb.buildVector(Math.PI/2)));
        assertFalse(psb.buildArrow().equals(psb.buildArrow(Math.PI/2)));
    }
}
