package com.gensym.devtools.build;

import java.io.*;
import java.util.*;

import com.gensym.core.CmdLineArgHandler;

public class Rmic {  
  private Vector compileList = new Vector();
  private boolean verbose = false;
  
  public Rmic() {
  }

  public void setVerbose(boolean verbose) {
    this.verbose = verbose;
  }

  /**
   * Scans the directory looking for class files to be compiled.
   * The result is returned in the class variable compileList.
   */
  void scanDir(File baseDir, String files[], boolean shouldVerify) {
    for (int i = 0; i < files.length; i++) {
      File baseFile = new File(baseDir, files[i]);
      if (files[i].endsWith(".class") &&
	  !files[i].endsWith("_Stub.class") &&
	  !files[i].endsWith("_Skel.class")) {
	if (shouldCompile(baseFile)) {
	  String classname = files[i].replace(File.separatorChar, '.');
	  classname = classname.substring(0, classname.indexOf(".class"));
	  boolean shouldAdd = true;
	  if (shouldVerify) {
	    try {
	      Class testClass = Class.forName(classname);
	      // One cannot RMIC an interface
	      if (testClass.isInterface() || !isValidRmiRemote(testClass)) {
		shouldAdd = false;
	      }
	    } catch (ClassNotFoundException e) {
	      System.err.println("Unable to verify class " + classname + 
		  ". It could not be found.");
	    } catch (NoClassDefFoundError e) {
	      System.err.println("Unable to verify class " + classname + 
		  ". It is not defined.");
	    }
	  }
	  if (shouldAdd) {
	    System.out.println("Info: Adding: " + classname + " to compile list");
	    compileList.addElement(classname);
	  }
	}
      }
    }
  }

  /**
   * Determine whether the class needs to be RMI compiled. 
   * It looks at the _Stub.class and _Skel.class files' last 
   * modification date and compares it with the class' class file.
   */
  private boolean shouldCompile (File classFile) {
    long now = (new Date()).getTime();
    File stubFile = 
      new File(classFile.getAbsolutePath().substring(0,
						     classFile.getAbsolutePath().indexOf(".class")) + "_Stub.class");
    File skelFile = 
      new File(classFile.getAbsolutePath().substring(0,
						     classFile.getAbsolutePath().indexOf(".class")) + "_Skel.class");
    if (classFile.exists()) {
      if (classFile.lastModified() > now) {
	System.err.println("Warning: file modified in the future: " + classFile);
      }
      
      if (classFile.lastModified() > stubFile.lastModified()) {
	return true;
      } else if (classFile.lastModified() > skelFile.lastModified()) {
	return true;
      } else {
	return false;
      }
    }
    return true;
  }
  
  /**
   * Check to see if the class or superclasses/interfaces implement
   * java.rmi.Remote.
   */
  private boolean isValidRmiRemote (Class testClass) {
    Class rmiRemote = java.rmi.Remote.class;
        
    if (rmiRemote.equals(testClass)) {
      // This class is java.rmi.Remote
      return true;
    }
    
    Class [] interfaces = testClass.getInterfaces();
    if (interfaces != null) {
      for (int i = 0; i < interfaces.length; i++) {
	if (rmiRemote.equals(interfaces[i])) {
	  // This class directly implements java.rmi.Remote
	  return true;
	}
	if (isValidRmiRemote(interfaces[i])) {
	  return true;
	}
      }
    }
    return false;
  }

  public void compile(File baseDir, String classpath, String classname) {
    if (!baseDir.exists()) {
      System.err.println("base dir does not exist " + baseDir);
      System.exit(1);
    }

    sun.rmi.rmic.Main compiler = new sun.rmi.rmic.Main(System.out, "rmic");
    String [] args = {
      "-d", 
      baseDir.getAbsolutePath(), 
      "-classpath", 
      classpath,
      classname};

    if(verbose) { System.out.println("checking  " + classname + " needs to be compiled"); }
    if (shouldCompile(new File(baseDir, classname.replace('.', 
							  File.separatorChar) + ".class"))) {
      if(verbose) { System.out.println("compiling " + classname); }
      //System.out.println(com.gensym.core.DebugUtil.printArray(args));   
      compiler.compile(args);
    }
  }
  
  public static final void main(String [] args) {
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);
    String baseDirectory = cmdLine.getOptionValue ("-directory");
    String classpath = cmdLine.getOptionValue ("-classpath");
    String classname = cmdLine.getOptionValue ("-classname");
    boolean verbose = (cmdLine.getOptionValue("-verbose") != null) ? true : false;
    Rmic compiler = new Rmic();
    compiler.setVerbose(verbose);
    compiler.compile(new File(baseDirectory), classpath, classname);
  }
  /*
    java com.gensym.devtools.build.Rmic -directory c:\\bt\\bb1-ns-v11\\java\\ -classpath c:\bt\bb1-ns-v11\java -classname com.gensym.dhns.naming.spi.dhns.DHNSImpl
  */
}
