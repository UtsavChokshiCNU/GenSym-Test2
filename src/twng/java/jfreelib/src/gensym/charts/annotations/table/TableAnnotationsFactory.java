package gensym.charts.annotations.table;

import gensym.charts.GraphChart;

import java.util.LinkedHashMap;
import java.util.Map;

/**
 * Table annotations factory
 */
public class TableAnnotationsFactory {
    /**
     * Table annotations map
     */
    private Map<Integer, TableAnnotation> annotations = new LinkedHashMap<Integer, TableAnnotation>();
    
    /**
     * Chart
     */
    private GraphChart chart = null;
    
    /**
     * Constructor
     */
    public TableAnnotationsFactory(GraphChart chart) {
        this.chart = chart;
    }
    
    /**
     * Get table annotation by ID. Make it if not present 
     * @param id the ID
     * @return the corresponding table annotation 
     */
    public TableAnnotation get(int id) {
        TableAnnotation annotation = annotations.get(id);
        
        if (annotation == null) {
            annotation = new TableAnnotation(chart);
            annotations.put(id, annotation);
        }
        
        return annotation;
    }
    
    /**
     * Returns items
     * @return array of items
     */
    public TableAnnotation[] getItems() {
        return annotations.values().toArray(new TableAnnotation[0]);
    }
}
