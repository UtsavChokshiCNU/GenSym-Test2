
package com.gensym.tests;

import com.gensym.classes.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.io.*;

public class TestClassFriendAccess {

  public static void main (String[] args) throws Exception {
    File directory = new File ("/bt/vkp-sol/java/com/gensym/classes");
    String[] fileNames = directory.list (new FilenameFilter () {
      @Override
      public boolean accept (File dir, String name) {
	return name.endsWith (".java") &&
	  !(name.substring (0, name.length () - 5).endsWith ("Impl"));
      }
    });
    System.out.println ("Got files = " + fileNames);
    Sequence g2ClassNames = new Sequence (201);
    ClassFriendAccess cfa = new ClassFriendAccess ();
    for (int i=0; i<fileNames.length; i++) {
      try {
	String fileName = fileNames[i];
	String className = fileName.substring (0, fileName.length () - 5);
	className = "com.gensym.classes." + className;
	Class clazz = Class.forName (className);
	Symbol g2ClassName = (Symbol) clazz.getField ("g2ClassName").get (null);
	cfa.register (g2ClassName, clazz);
	if (g2ClassName != null)
	  g2ClassNames.addElement (g2ClassName);
      } catch (Exception e) {
	System.err.println ("Failed for " + fileNames[i]);
      }
    }
    for (int i=0; i<g2ClassNames.size (); i++) {
      Symbol g2ClassName = (Symbol) g2ClassNames.elementAt (i);
      Symbol[] sups = cfa.getDirectSuperiorClasses (g2ClassName);
      System.out.print (g2ClassName + " -> ");
      for (int j=0; j<sups.length; j++) {
	System.out.print (" ");
	System.out.print (sups[j]);
      }
      System.out.println ();
    }
  }

}
