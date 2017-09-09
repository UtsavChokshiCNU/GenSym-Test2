/*
 * 	 StreamClassLoader.java
 *
 *	 Description
 *      Class loader for loading compiled classes from our own stream
 *
 *	 Author:
 *		V.Pillai/M.D.Gribble		Dec/96
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.util;


import java.io.*;

/**
 * Class loader for loading compiled classes from our own stream
 * Our class loader does not cache classes already loaded, so we have can have
 * Incremental Class resolution
 *
 * @version 	1.0, 01 Dec 1996
 *
 * @author M.D.Gribble
 * @author Vikram Pillai
 */

public class StreamClassLoader extends ClassLoader {

  private String className;
  private String classFileName;
  private byte[] classContents;
  private int classFileLength;
  private static Class alreadyLoadedClass = null;
  private boolean fulldebug = false;


  /**
   * Constructs a StreamClassLoader, loads contents of a class
   * from an existing byte array
   *
   * @param ClassName the class name of the class being loaded
   * @param ClassData the byte array containing the class
   */
  public StreamClassLoader (String className, byte[] classData)
  {
    super();

	  this.className = className;
	  this.classContents = classData;
	  this.classFileLength = classData.length;
  }

  /**
   * Constructs an empty StreamClassLoader, need to call readFromFile
   *
   */
  public StreamClassLoader ()
  {
    super();

	  this.className = "";
	  this.classContents = new byte[0];
	  this.classFileLength = 0;
  }

  /** 
   * Constructs a StreamClassLoader, loads contents of ClassFileName
   * into a DataInputStream
   * Exceptions, should be caught by caller
   * @param ClassName the class name of the class being loaded
   * @param ClassFileName the compiled class file
   */
  public StreamClassLoader (String className, String classFileName)
  throws FileNotFoundException, IOException{
    super();
    
    readFromFile(className, classFileName);
  }
  

  /**
   * Redefine the byte codes to be loaded, by loading the given file
   */
  public void readFromFile(String className, String classFileName)
       throws FileNotFoundException, IOException{
    this.className = className;
    this.classFileName = classFileName;

    File CFile = new File (classFileName);
    classFileLength = (int)CFile.length();
    classContents = new byte[classFileLength]; 

    //System.out.println ("Trying to open class file " + ClassFileName);
     
    DataInputStream CFStream = new DataInputStream (new FileInputStream (CFile));
    CFStream.readFully(classContents);

    //System.out.println ("Class File Read!");

  }

  /**
   * Return the class byte code array, previsously loaded
   *
   */
  public byte[] getClassData()
  {
	  return classContents;
  }


  /**
   * Defines/redefines and resolves a given Class
   * System classes can not be redefined
   * 
   * @param Classname the class to load
   * @param resolve if true make class avaliable for use 
   */
  @Override
  public Class loadClass (String className, boolean resolve) {
    //System.out.print ("Trying to load class " + ClassName + " [");
	
    // We are not allowed to redfines system classes
    // Notes: findSystemClass is used to resolve classes from the 
    // local system such as classes on the CLASSPATH. We therefore
    // do not call findSystemClass for ClassName as it may find 
    // it already loaded or on the CLASSPATH and prevent redefinition
    // i.e. it will find a previous loaded version.
    if (!className.equals(this.className)) {
      try {
	Class ExistingClass = super.findSystemClass (className);
	if (fulldebug){ 
		System.out.println ("  Returning System Class " + ExistingClass.toString());
	}
	return ExistingClass;
      } catch (ClassNotFoundException CNFE) {}
    } else {
      //Not a current loaded system class, we can define our class
	
      Class newClass;
      // Check we have not already loaded our class
      if (alreadyLoadedClass == null) {
	newClass = defineClass (null, classContents, 0, classFileLength);
	if (resolve)
	  resolveClass (newClass);
      }
      else
	newClass = alreadyLoadedClass;
    
      if (fulldebug){
    	  System.out.println("Resolved new class " + newClass.toString() + " " + newClass.hashCode());
      }
	
      return newClass;
    }
    return null; // should not reach here
  }
}

  



