package gensym.charts.annotations;

import gensym.charts.GraphChart;
import gensym.charts.annotations.graph.AnnotationBuilder;
import gensym.charts.annotations.graph.AnnotationFactory;
import gensym.charts.annotations.graph.AnnotationWithAxis;
import gensym.charts.annotations.line.LineAnnotationFactory;
import gensym.charts.annotations.line.LineAnnotation;
import gensym.charts.annotations.table.TableAnnotation;
import gensym.charts.annotations.table.TableAnnotationsFactory;
import gensym.charts.axis.MultiAxesPlot;

import org.jfree.chart.annotations.XYAnnotation;
import org.jfree.chart.annotations.XYTitleAnnotation;
import org.jfree.chart.plot.ValueMarker;
import org.jfree.chart.plot.XYPlot;
import org.jfree.ui.Layer;

/**
 * Chart annotations class
 */
public class ChartAnnotations {
    /**
     * Chart
     */
    private GraphChart chart;
    
    /**
     * Graph annotations
     */
    private AnnotationFactory graphAnnotations = new AnnotationFactory();
    
    /**
     * Graph annotation visibility flag
     */
    private boolean showGraphAnnotation = true;

    /**
     * Table annotations
     */
    private TableAnnotationsFactory tableAnnotations = null;
    
    /**
     * Current table annotation ID
     */
    private int tableAnnotationId = -1;

    /**
     * Table annotation visibility flag
     */
    private boolean showTableAnnotation = true;
    
    /**
     * Horizontal line annotations
     */
    private LineAnnotationFactory horLineAnnotations = new LineAnnotationFactory();
    
    /**
     * Line annotation visibility flag
     */
    private boolean showLineAnnotation = true;
    
    /**
     * Annotation showing flag
     */
    private boolean showAnnotations = true;

    /**
     * Constructor
     * @param chart the chart
     */
    public ChartAnnotations(GraphChart chart) {
        this.chart = chart;
        
        tableAnnotations = new TableAnnotationsFactory(chart);
    }
    
    /**
     * Returns graph annotations factory
     * @return
     */
    public AnnotationFactory getGraphAnnotations() {
        return graphAnnotations; 
    }
    
    /**
     * Returns current table annotation
     * @return the current table annotation
     */
    public TableAnnotation getCurrentTableAnnotation() {
        return tableAnnotations.get(tableAnnotationId); 
    }
    
    /**
     * Sets current annotation table
     * @param id the table id
     */
    public void setCurrentTableAnnotation(int id) {
        tableAnnotationId = id;
    }
    
    /**
     * {@inheritDoc}
     */
    public void updateTableAnnotations() {
        for (TableAnnotation table : tableAnnotations.getItems()) {
            table.update(isTableAnnotationsVisible());
        }
    }

    /**
     * Updates graph annotations
     */
    public void updateGraphAnnotations() {
        MultiAxesPlot plot = chart.getPlot();

        for (Object obj : plot.getAnnotations()) {
            XYAnnotation annotation = (XYAnnotation) obj;
            if (!(annotation instanceof XYTitleAnnotation)) {
                plot.removeAnnotation(annotation, false);
            }
        }
        
        XYPlot newPlot = plot.getPlot(0);
        if (newPlot == null) {
            newPlot = plot;
        }
        
        if (isGraphAnnotationsVisible()) {
            AnnotationBuilder builder = new AnnotationBuilder(getGraphAnnotations());
            for (AnnotationWithAxis axisAnnotation = builder.next(); axisAnnotation != null; axisAnnotation = builder.next()) {
                XYPlot axisPlot = plot.getPlot(axisAnnotation.getAxis());
                if (axisPlot != null) {
                    axisPlot.addAnnotation(axisAnnotation.getAnnotation(), false);
                } else {
                    newPlot.addAnnotation(axisAnnotation.getAnnotation(), false);
                }
            }
        }
    }
    
    /**
     * Updates horizontal line annotations
     */
    public void updateHorLineAnnotations() {
        MultiAxesPlot plot = chart.getPlot();
        plot.clearRangeMarkers();
        
        if (!isLineAnnotationsVisible()) {
            return;
        }
        
        for (LineAnnotation annotation : horLineAnnotations.getItems()) {
            ValueMarker marker = annotation.createMarker();
            
            if (marker != null && plot.getPlot(annotation.getAxis()) != null) {
                plot.getPlot(annotation.getAxis()).addRangeMarker(0, marker, Layer.FOREGROUND, false);
            }
        }
    }
    
    /**
     * Tests if graph annotations are visible
     * @return true if graph annotations are visible
     */
    public boolean isGraphAnnotationsVisible() {
        return showGraphAnnotation || isAnnotationVisible();
    }
    
    /**
     * Sets table annotation visibility
     * @param visible the visibility flag
     */
    public void setTableAnnotationsVisible(boolean visible) {
        showTableAnnotation = visible;
    }
    
    /**
     * Tests if table annotations are visible
     * @return true if table annotations are visible
     */
    public boolean isTableAnnotationsVisible() {
        return showTableAnnotation || isAnnotationVisible();
    }
    
    /**
     * Sets graph annotation visibility
     * @param visible the visibility flag
     */
    public void setGraphAnnotationsVisible(boolean visible) {
        showGraphAnnotation = visible;
    }

    /**
     * Tests if annotations are visible
     * @return true if annotations are visible
     */
    public boolean isAnnotationVisible() {
        return showAnnotations;
    }
    
    /**
     * Sets annotation visibility
     * @param visible the visibility flag
     */
    public void setAnnotationVisible(boolean visible) {
        showAnnotations = visible;
    }
    
    /**
     * Updates annotations
     */
    public void update() {
        updateGraphAnnotations();
        updateTableAnnotations();
        updateHorLineAnnotations();
    }

    /**
     * Returns horizontal line annotations
     * @return horizontal line annotations
     */
    public LineAnnotationFactory getHorizontalLineAnnotations() {
        return horLineAnnotations;
    }
    
    /**
     * Sets line annotation visibility
     * @param visible the visibility flag
     */
    public void setLineAnnotationsVisible(boolean visible) {
        showLineAnnotation = visible;
    }
    
    /**
     * Tests if line annotations are visible
     * @return true if line annotations are visible
     */
    public boolean isLineAnnotationsVisible() {
        return showLineAnnotation || isAnnotationVisible();
    }

}
