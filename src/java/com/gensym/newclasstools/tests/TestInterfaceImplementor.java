package com.gensym.newclasstools.tests;

import com.gensym.newclasstools.*;
import java.util.*;
import java.io.*;

public class TestInterfaceImplementor {

  // Sample usage: java com.gensym.newclasstools.tests.TestInterfaceImplementor "com.gensym.denali.eval.RuntimeEnvironment"
  public static void main (String[] args) {
    try {
      String interfaceName = args[0];

      String implementationSimpleName = interfaceName.substring(interfaceName.lastIndexOf(".") + 1)
	+ "Implementation";
      String implementationName = "com.gensym.newclasstools.tests." + implementationSimpleName;
	interfaceName.substring(interfaceName.lastIndexOf(".") + 1);
      ClassInfo implementation = new ClassInfo(interfaceName, implementationName);
      
     FileOutputStream fileOutStream = new FileOutputStream(implementationSimpleName + ".class");
     fileOutStream.write(implementation.getBytes(true));
     fileOutStream.close();
     System.out.println("Wrote the .class file");

     Class cl = Class.forName(implementationName);
     Object instance = cl.newInstance();


     System.out.println("Implementation class successfully loaded and instantiated");
    } catch (Exception e) {
      System.out.println("Something went wrong: " + e);
    }
  }
}
