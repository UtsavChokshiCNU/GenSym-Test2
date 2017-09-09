package gensym.charts.properties.plotting;

import gensym.charts.GraphChart;
import gensym.charts.GraphBubbleRenderer;

import org.jfree.chart.renderer.xy.*;

/**
 * Additional class for PlottingMethodProperty & PlottingMethodsProperty
 */
public class GraphRendererFactory {
    /** Line */
    public static final int PEGPM_LINE = 0;

    /** Bar */
    public static final int PEGPM_BAR = 1;

    /** Point */
    public static final int PEGPM_POINT = 2;

    /** Area */
    public static final int PEGPM_AREA = 3;

    /** Stacked bar */
    public static final int PEGPM_BARSTACKED = 6;

    /** Points and spline */
    public static final int PEGPM_POINTSPLUSSPLINE = 15;

    /** Points and best fit curve (not supported) */
    public static final int PEGPM_POINTSPLUSBFC = 13;

    /** Ribbon */
    public static final int PEGPM_RIBBON = 22;

    /** Step */
    public static final int PEGPM_STEP = 21;

    /** Bubble */
    public static final int PEGPM_BUBBLE = 12;


    /** Graph*/
    private GraphChart graph;
    
    /**
     * Constructor
     * @param graph source graph
     */
    public GraphRendererFactory(GraphChart graph) {
        this.graph = graph;
    }
    
    /**
     * Creates renderer by Id
     * @param graph GraphChart
     * @param value value
     * @return new XYItemRenderer
     */
    public XYItemRenderer createRenderer(int id) {
        XYItemRenderer renderer = null;
        switch (id) {
            case PEGPM_LINE:
                renderer = new XYLineAndShapeRenderer();
                break;
            case PEGPM_BAR:
                ClusteredXYBarRenderer barRenderer = new ClusteredXYBarRenderer();
                barRenderer.setMargin(0.2);
                renderer = barRenderer;
                break;
            case PEGPM_POINT:
                XYLineAndShapeRenderer shapeRenderer = new XYLineAndShapeRenderer();
                for (int series = 0; series < 100; series++) {
                    shapeRenderer.setSeriesLinesVisible(series, false);
                }
                renderer = shapeRenderer;
                break;
            case PEGPM_AREA:
                break;
            case PEGPM_BARSTACKED:
                if (graph.isStackedDataAllowed()) {
                    StackedXYBarRenderer stackedRenderer = new StackedXYBarRenderer();
                    stackedRenderer.setMargin(0.2);
                    renderer = stackedRenderer;
                }
                break;

            case PEGPM_POINTSPLUSSPLINE:
            case PEGPM_POINTSPLUSBFC:
                renderer = new XYSplineRenderer(10);
                break;

            case PEGPM_RIBBON:
                if (graph.isRibbonAllowed()) {
                    renderer = new XYLine3DRenderer();
                }
                break;

            case PEGPM_STEP:
                if (graph.isStepAllowed()) {
                    renderer = new XYStepAreaRenderer();
                }
                break;

            case PEGPM_BUBBLE:
                if (graph.isBubbleAllowed()) {
                    renderer = new GraphBubbleRenderer(XYBubbleRenderer.SCALE_ON_RANGE_AXIS);
                }
                break;

            default:
                break;
        }
        return renderer;
    }
}
