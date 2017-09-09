package gensym.charts.annotations.graph;

import gensym.charts.annotations.graph.ext.XYMultiLineAnnotation;
import org.jfree.ui.TextAnchor;

/**
 * Start text annotation
 * TODO: Add multiline support
 */
public class StartTextAnnotation extends AbstractBuilder {

    /** Add text annotation type */
    public static final int PEGAT_ADDTEXT = 85;

    /** Paragraph annotation type */
    public static final int PEGAT_PARAGRAPH = 86;

    /** Annotation text */
    private String text = "";

    /**
     * Constructor
     * @param info annotation info
     */
    StartTextAnnotation(AnnotationInfo info) {
        setAxis(info.getAxis());
        text += info.getText();
    }

    /**
     * {@inheritDoc}
     */
    public boolean isInfoUsed(AnnotationInfo info) {
        return info.getType() == PEGAT_ADDTEXT || info.getType() == PEGAT_PARAGRAPH;
    }
    
    /**
     * {@inheritDoc}
     */
    public void addInfo(AnnotationInfo info) {
        if (isInfoUsed(info)) {
            switch (info.getType()) {
            case PEGAT_ADDTEXT:
                text += info.getText();
                break;
                
            case PEGAT_PARAGRAPH:
                XYMultiLineAnnotation annotation =
                        new XYMultiLineAnnotation(text, info.getX(), info.getY(), 0, 0);
                if (info.getFactory().getFont() != null) {
                    annotation.setFont(info.getFactory().getFont());
                }
                
                if (info.getColor() != null) {
                    annotation.setPaint(info.getColor());
                }
                annotation.setTextAnchor(TextAnchor.BASELINE_LEFT);

                addAnnotation(annotation);
                isFinished = true;
                break;
            default:
                break;
            }
        }
    }
}
