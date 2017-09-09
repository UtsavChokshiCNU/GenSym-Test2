package gensym.charts.annotations.graph;

/**
 * Annotation text info contains info about annotation text: label and position.
 */
public class AnnotationTextInfo {
    /** Text */
    private String text;
    
    /** Text x coordinate */
    private Double x;
    
    /** Text y coordinate */
    private Double y;
    
    /**
     * Constructor
     * @param text the annotation text
     */
    public AnnotationTextInfo(String text) {
        this.text = text;
    }
    
    /**
     * Returns annotation text
     * @return the text
     */
    public String getText() {
        return text;
    }
    
    /**
     * Tests whether text coordinates are used
     * @return true if text has coordinates
     */
    public boolean isCoordinatesUsed() {
        return x != null && y != null;
    }
    
    /**
     * Returns text X position
     * @return X position
     */
    public double getX() {
        return x != null ? x : 0;
    }
    
    /**
     * Sets text X position
     * @param x X position
     */
    public void setX(double x) {
        this.x = x;
    }
    
    /**
     * Returns text Y position
     * @return Y position
     */
    public double getY() {
        return y != null ? y : 0;
    }
    
    /**
     * Sets text Y position
     * @param y Y position
     */
    public void setY(double y) {
        this.y = y;
    }

    /**
     * Parses text and returns annotation text info
     * @param text text to be parsed
     * @return annotation text info
     */
    public static AnnotationTextInfo parseText(String text) {
        if (!text.startsWith("|")) {
            return text.isEmpty() ? null : new AnnotationTextInfo(text);
        }
        String[] parts = text.split("[|]");

        String part = parts[1];
        if (part.startsWith("H") || part.startsWith("V")) {
            return parseTextCoordinates(part.substring(1), parts);
        }

        String label = "";
        if (!part.isEmpty()) {
            label = part.substring(1);
        }
        
        for (int i = 1; i < parts.length; i++) {
            if (!label.isEmpty() || i != 1) { //for "||text" issue
                label += "|";
            }
            label += parts[i];
        }
        
        return label.isEmpty() ? null : new AnnotationTextInfo(label);
    }

    /**
     * Parses text with coordinates
     * @param xText X coordinate string
     * @param parts text parts
     * @return
     */
    private static AnnotationTextInfo parseTextCoordinates(String xText, String[] parts) {
        if (parts.length < 4 || parts[parts.length - 1].isEmpty()) {
            return null;
        }
        String yText = parts.length > 2 ? parts[2] : "";
        try {
            double x = Double.parseDouble(xText);
            double y = Double.parseDouble(yText);
            String text = parts[parts.length - 1];
            
            AnnotationTextInfo info = new AnnotationTextInfo(text);
            info.setX(x);
            info.setY(y);
            return info;
            
        } catch (NumberFormatException ex) {
            return null;
        }
    }
}
