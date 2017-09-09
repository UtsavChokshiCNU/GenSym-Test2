/*
 * @(#)ClassComparator.java	1.9 00/02/02
 *
 * Copyright 1997-2000 Sun Microsystems, Inc. All Rights Reserved.
 * 
 * This software is the proprietary information of Sun Microsystems, Inc.  
 * Use is subject to license terms.
 * 
 */

package com.gensym.devtools.doclets13;

import com.sun.javadoc.*;
import java.util.*;

/**
 * Comparator to be used to compare the class names.
 */
public class ClassComparator implements Comparator {

    /**
     * Compare the classnames of classes represented by two
     * {@link com.sun.javadoc.ClassDoc} objects.
     *
     * @param   o1 ClassDoc object1
     * @param   o2 ClassDoc object2
     * @return  Return the value returned by {@link java.lang.String#compareTo}
     *          method from java.lang.String class.
     */
    @Override
    public int compare(Object o1, Object o2) {
        return (((ClassDoc)o1).name())
            .compareTo(((ClassDoc)o2).name());
    }
}
