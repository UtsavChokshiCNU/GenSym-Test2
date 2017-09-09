package gensym.charts.annotations.graph;

import java.awt.Font;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * Graph annotation info factory 
 */
public class AnnotationFactory {
    /**
     * Max font size
     */
    private static final float MAX_FONT_SIZE = 16;
    
    /**
     * Annotations maps
     */
    private Map<Integer, AnnotationInfo> infos = new LinkedHashMap<Integer, AnnotationInfo>();
    
    /**
     * Text font
     */
    private Font font = new Font("SansSerif", Font.PLAIN, (int) MAX_FONT_SIZE);
    
    /**
     * Is annotations movable
     */
    private boolean movable = false;
    
    /**
     * Constructor
     */
    public AnnotationFactory() {
    }
    
    /**
     * Get annotation info object by ID. Make it if not present 
     * @param id the ID
     * @return the corresponding annotation info 
     */
    public AnnotationInfo getInfo(int id) {
        AnnotationInfo info = infos.get(id);
        
        if (info == null) {
            info = new AnnotationInfo(id, this);
            infos.put(info.getId(), info);
        }
        
        return info;
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
     * Tests if annotation is movable
     * @return true if annotation is movable
     */
    public boolean isMovable() {
        return movable;
    }
    
    /**
     * Sets movable flag
     * @param movable the movable flag
     */
    public void setMovable(boolean movable) {
        this.movable = movable;
    }
    
    /**
     * Returns list of items
     * @return the item list
     */
    public List<Integer> getItems() {
        return new ArrayList<Integer>(infos.keySet());
    }
}
