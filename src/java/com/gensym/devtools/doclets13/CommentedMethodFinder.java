/*
 * @(#)CommentedMethodFinder.java	1.3 00/02/02
 *
 * Copyright 1998-2000 Sun Microsystems, Inc. All Rights Reserved.
 * 
 * This software is the proprietary information of Sun Microsystems, Inc.  
 * Use is subject to license terms.
 * 
 */

package com.gensym.devtools.doclets13;

import com.sun.javadoc.*;
import java.lang.*;
import java.util.*;
import java.io.*;

/**
 * Find a commented method.
 */
public class CommentedMethodFinder extends MethodFinder {
  public boolean isCorrectMethod(MethodDoc method) {
    return method.inlineTags().length > 0;
  }
}
 
