/*
 * @(#)ImplementedMethods.java	1.3 00/02/02
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
 * For a given class method, build an array of interface methods which it
 * implements.
 *
 * @author Atul M Dambalkar
 */
public class ImplementedMethods {

  private List methlist = new ArrayList();
  private final ClassDoc classdoc;
  private final MethodDoc method;

  public ImplementedMethods(MethodDoc method) {
    this.method = method;
    classdoc = method.containingClass(); 
  }

  /**
   * Return the array of interface methods which the method passed in the
   * constructor is implementing. The search/build order is as follows:
   * <pre>
   * 1. Search in all the immediate interfaces which this method's class is 
   *    implementing. Do it recursively for the superinterfaces as well.
   * 2. Traverse all the superclasses and search recursively in the 
   *    interfaces which those superclasses implement.
   *</pre>
   *
   * @return MethodDoc[] Array of implemented methods.
   */
  public MethodDoc[] build() {
    ClassDoc icd = classdoc;
    while (icd != null) {
      buildImplementedMethodList(icd.interfaces());
      icd = icd.superclass();
    }
    return (MethodDoc[])methlist.toArray(new MethodDoc[methlist.size()]);
  }

  /**
   * Search the method in the array of interfaces. If found check if it is 
   * not overridden by any other subinterface method which this class 
   * implements. If it is not overidden, add it in the method list.
   * Do it recursively for all the extended interfaces for each interface 
   * from the array passed.
   */ 
  private void buildImplementedMethodList(ClassDoc[] intfacs) {
    for (int i = 0; i < intfacs.length; i++) {
      MethodDoc found = Util.findMethod(intfacs[i], method);
      if (found != null) {
	removeOverriddenMethod(found);
	if (!overriddingMethodFound(found)) {
	  methlist.add(method);
	}   
      }
      ClassDoc[] iin = intfacs[i].interfaces();
      buildImplementedMethodList(iin);
    }
  }

  /**
   * Search in the already found methods' list if it contains a method which
   * is overridden by the method as parameter, remove the overridden method
   * from the method list.
   *
   * @param method Is this method overridding a method in the method list.
   */
  private void removeOverriddenMethod(MethodDoc method) {
    ClassDoc overriddenClass = method.overriddenClass();  
    if (overriddenClass != null) {
      for (int i = 0; i < methlist.size(); i++) {
	ClassDoc cd = ((MethodDoc)methlist.get(i)).containingClass();
	if (cd == overriddenClass || overriddenClass.subclassOf(cd)) {
	  methlist.remove(i);  // remove overridden method
	  return;
	}
      } 
    } 
  }

  /**
   * Search in the already found methods' list if it contains a method which
   * is overridding the method as parameter or this method itself.
   *
   * @param method Is this method overridden by a method in the method list.
   */
  private boolean overriddingMethodFound(MethodDoc method) {
    ClassDoc containingClass = method.containingClass();
    for (int i = 0; i < methlist.size(); i++) {
      ClassDoc cd = ((MethodDoc)methlist.get(i)).overriddenClass();
      if (cd == containingClass || cd.subclassOf(containingClass)) {
	return true;
      }
    }
    return false;
  }
}
