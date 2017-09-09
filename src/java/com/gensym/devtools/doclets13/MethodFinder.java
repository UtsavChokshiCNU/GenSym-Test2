/*
 * @(#)MethodFinder.java	1.3 00/02/02
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
 * This class is useful for searching a method which has documentation 
 * comment and documentation tags. The method is searched in all the 
 * superclasses and interfaces(subsequently super-interfaces also) 
 * recursively.
 */
public abstract class MethodFinder {     

  abstract boolean isCorrectMethod(MethodDoc method);
    
  public MethodDoc search(ClassDoc cd, MethodDoc method) {
    MethodDoc meth = searchInterfaces(cd, method);
    if (meth != null) {
      return meth;
    }
    ClassDoc icd = cd.superclass();        
    if (icd != null) {
      meth = Util.findMethod(icd, method);
      if (meth != null) {
	if (isCorrectMethod(meth)) {
	  return meth;
	}
      }
      return search(icd, method);
    }
    return null;
  }

  public MethodDoc searchInterfaces(ClassDoc cd, MethodDoc method) {
    ClassDoc[] iin = cd.interfaces();
    for (int i = 0; i < iin.length; i++) {
      MethodDoc meth = Util.findMethod(iin[i], method);
      if (meth != null) {
	if (isCorrectMethod(meth)) {
	  return meth;
	}
      }
    }
    for (int i = 0; i < iin.length; i++) {
      MethodDoc meth = searchInterfaces(iin[i], method);
      if (meth != null) {
	return meth;
      }
    }
    return null;
  }
}
