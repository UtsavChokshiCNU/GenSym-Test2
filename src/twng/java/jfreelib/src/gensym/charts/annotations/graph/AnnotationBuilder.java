package gensym.charts.annotations.graph;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

/**
 * Annotation builder class
 */
public class AnnotationBuilder {
    
    /** List of annotation IDs */
    private List<Integer> items = null;
    
    /** Annotation factory */
    private AnnotationFactory factory = null;

    /** List of builders */
    private List<AbstractBuilder> builders = new LinkedList<AbstractBuilder>();
    
    /** Stack of built annotations */
    private Stack<AnnotationWithAxis> annotations = new Stack<AnnotationWithAxis>();
    
    /** Current item index */
    private int currentItem = 0;
    
    /**
     * Constructor
     * @param factory the factory
     */
    public AnnotationBuilder(AnnotationFactory factory) {
        this.factory = factory;
        
        items = factory.getItems();
        Collections.sort(items);
    }
    
    /**
     * Makes and returns next annotation
     * @return next annotation
     */
    public AnnotationWithAxis next() {
        if (annotations.size() > 0) {
            return annotations.pop();
        }
        
        for (; currentItem < items.size(); ) {
            AnnotationInfo info = factory.getInfo(items.get(currentItem));
            currentItem++;
            
            AbstractBuilder builder = findBuilder(info);
            if (builder != null) {
                builder.addInfo(info);
            } else {
                builder = AnnotationBuildersFactory.createBuilder(info);
            }
            if (builder != null) {
                if (builder.isBuildFinished()) {
                    return buildAnnotation(builder);
                } else if (!builders.contains(builder)) {
                    builders.add(0, builder);
                }
            }
        }
        
        return tryToBuild();
    }
    
    /**
     * Finds builder for annotation info
     * @param info the annotation info
     * @return builder
     */
    private AbstractBuilder findBuilder(AnnotationInfo info) {
        for (AbstractBuilder builder : builders) {
            if (builder.isInfoUsed(info)) {
                return builder;
            }
        }
        
        return null;
    }
    
    /**
     * Try to build annotation by rest of builders
     * @return
     */
    private AnnotationWithAxis tryToBuild() {
        while (builders.size() > 0) {
            AnnotationWithAxis annotation = buildAnnotation(builders.get(0));
            if (annotation != null) {
                return annotation;
            }
        }
        return null;
    }
    
    /**
     * Build annotation
     * @param builder annotation builder
     * @return the built annotation
     */
    private AnnotationWithAxis buildAnnotation(AbstractBuilder builder) {
        for (AnnotationWithAxis annotation : builder.build()) {
            annotations.push(annotation);
        }
        
        builders.remove(builder);

        return annotations.size() > 0 ? annotations.pop() : null;
    }
}
