/*
 * @(#)ClassComparator.java	1.7 98/09/21
 *
 * Copyright 1997, 1998 by Sun Microsystems, Inc.,
 * 901 San Antonio Road, Palo Alto, California, 94303, U.S.A.
 * All rights reserved.
 *
 * This software is the confidential and proprietary information
 * of Sun Microsystems, Inc. ("Confidential Information").  You
 * shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Sun.
 */

package com.gensym.devtools.doclets;

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
