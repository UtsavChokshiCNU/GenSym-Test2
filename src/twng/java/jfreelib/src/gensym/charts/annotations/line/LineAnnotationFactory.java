package gensym.charts.annotations.line;

import java.awt.Font;
import java.util.LinkedHashMap;
import java.util.Map;

/**
 * Line annotation factory
 */
public class LineAnnotationFactory {
    /**
     * Max font size
     */
    private static final float MAX_FONT_SIZE = 14;

    /**
     * Table annotations map
     */
    private Map<Integer, LineAnnotation> annotations = new LinkedHashMap<Integer, LineAnnotation>();
    
    /**
     * Text font
     */
    private Font font = new Font("SansSerif", Font.PLAIN, (int) MAX_FONT_SIZE);
    
    /**
     * Get line annotation by ID. Make it if not present 
     * @param id the ID
     * @return the corresponding line annotation 
     */
    public LineAnnotation get(int id) {
        LineAnnotation annotation = annotations.get(id);
        
        if (annotation == null) {
            annotation = new LineAnnotation();
            annotations.put(id, annotation);
        }
        
        return annotation;
    }
    
    /**
     * Returns items
     * @return array of items
     */
    public LineAnnotation[] getItems() {
        return annotations.values().toArray(new LineAnnotation[0]);
    }

    /**
     * Returns text font
     * @return the font
     */
    public Font getFont() {
        return font;
    }
    
    /**
     * Sets text size
     * @param size the new text size
     */
    public void setTextSize(int size) {
        font = font.deriveFont(MAX_FONT_SIZE * size / 100);
    }
    
    /**
     * Clear all annotations
     */
    public void clear() {
        annotations.clear();
    }
}
