/*
 * 	 SourceCompiler.java
 *
 *	 Description
 *      SourceCompiler compilation of java source and dynamic loading of
 *      java class files
 *
 *	 Author:
 *		V.Pillai/M.D.Gribble		Dec/96
 *
 *     
 *   Modifications:
 *
 */


/* To DO
 * 1. Delete compilation source and .class files after comiletion
 */
package com.gensym.util;


import java.io.*;

/**
 * Handles complation of java source and loading of new classes into the current executing Java VM
 *
 * @version 	1.1,  16 Sep 1997
 *
 * @author M.D.Gribble
 * @author Vikram Pillai
 */
 
public class SourceCompiler {

  private String StagingDirectory = "";
  private static boolean fulldebug = false;
  StreamClassLoader CL = new StreamClassLoader();
 
  // Note on NT, Process.waitFor on a javac process does not work, see RunCompiler
  private static String JavaCompilerName = "javac -J-Djavac.pipe.output=true ";  
  //private static String JavaCompilerName = "dir "; 

  /**
   * Compile a java source file, reporting any errors back via JavaClassCompilerException.
   * Compilation designed to work cross platform
   *
   * @param filename filename of java source file
   * @exception JavaClassCompilerException if the compilation fails, erros contained in exception
   */
  public static void Compile(String filename)
       throws JavaClassCompilerException
  {
 
 
    String compiler_output = RunCompiler.compile(JavaCompilerName, filename);

    if (compiler_output.indexOf("error") >= 0){
      throw new JavaClassCompilerException (compiler_output); 
    } else if (fulldebug){
    	System.out.println ("Compilation succeeded!");
    }

  }
	
  /** 
   * Generate a class file by compiling then loading SourceCode
   * Here we assume that there is only one class in the SourceCode
   *
   * @param ClassName  The class to load from SourceCode
   * @param sourceCode The source code to compile
   */
  public void GenerateClass (String className, String sourceCode)
	throws 
	  JavaClassCompilerException {
	  GenerateClass(StagingDirectory, className, sourceCode);

  }
			
 /** 
   * Generate a class file by compiling then loading SourceCode
   * Here we assume that there is only one class in the SourceCode
   *
   * @param ClassName  The class to load from SourceCode
   * @param sourceCode The source code to compile
   */
  public void GenerateClass (String directory, String fullClassName, String sourceCode)
	throws 
	  JavaClassCompilerException {

    int CompilerExitStatus = 0;

    // Remove any package spec
    String className = fullClassName;
    if (fullClassName.lastIndexOf(".") > -1)
      className = fullClassName.substring(fullClassName.lastIndexOf(".")+1);
 
    try
      {
	String javaFileName = directory + className + ".java";
	String classFileName = directory + className + ".class";

	// Try to open the source file and an output stream for the compiled source file
	// We can raise IOException here
	if (fulldebug) 
	  System.out.println ("Class Name is : " + className);
	FileOutputStream FOStream = new FileOutputStream (javaFileName);	
	DataOutputStream DStream = new DataOutputStream (FOStream);
      
	DStream.writeBytes (sourceCode);
	DStream.close ();

	String compiler_output = RunCompiler.compile(JavaCompilerName, javaFileName);

	if (compiler_output.indexOf("Note: sun.tools.javac.Main has been deprecated.") >= 0){
	  System.out.println (compiler_output);
    } else if (!compiler_output.equals("")){
	  throw new JavaClassCompilerException (compiler_output); 
	} else if (fulldebug){
		System.out.println ("Compilation succeeded!");
	}
      }
    catch (IOException E) 
      {
	throw new JavaClassCompilerException (E.toString()); 
      }
	
 
   
  }

  /** 
   * Load the precompiled class into the current environment
   * using our own class loader
   */
  public Class loadClass (String stagingDir, String fullClassName) 
       throws  java.io.FileNotFoundException, java.io.IOException
  {

    // Remove any package spec
    String className = fullClassName;
    if (fullClassName.lastIndexOf(".") > -1)
      className = fullClassName.substring(fullClassName.lastIndexOf(".")+1);

    String classFileName = stagingDir + className + ".class";
    StreamClassLoader classLoader = new StreamClassLoader(className, classFileName);
    if (fulldebug)
		System.out.println ("Call to load/define class : " + className + " from " + classFileName);
    return (classLoader.loadClass(className, true));
    
  }

    /** 
   * Load the precompiled class into the current environment
   * using our own class loader
   */
  public Class loadClass (String className) 
       throws  java.io.FileNotFoundException, java.io.IOException
  {
    return  loadClass(StagingDirectory, className);
  }

  
}

