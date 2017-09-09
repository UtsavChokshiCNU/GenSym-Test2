package com.gensym.classtools.examples.MergeClassLoader;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;


/** 
* MergeClassLoader is an example use of the classtools package.
* 
* It is a class loader that will automatically merge in a specific class
* to every class that is being loaded. The class that is merged into every
* class being loaded is never actually loaded itself. 
*
* This is anticipated as being a mechanism whereby an environment can
* enforce the implementation of an interface on every class being loaded
* without any implementation work on the part of the creator of the original
* class.
* 
**/

public class MergeClassLoader extends ClassLoader {
    private Hashtable classes = new Hashtable();
	private ClassInfo mergeClassInfo;
	
	
	/** Load and parse the merge class - throw a ClassException if cannot 
	*  parse the merge class.
	*
	* @exception ClassNotFoundException
	* Cannot create a MergeClassLoader because the merge class specified
	* could not be loaded.
	*/
    public MergeClassLoader(String mergeclassname) 
	   throws ClassNotFoundException
	{
	  try {  	
	  FileInputStream fileStream = new FileInputStream(mergeclassname);
	  mergeClassInfo = new ClassInfo(fileStream);
	  
	  fileStream.close();
	  }
	  catch (Exception e) {
		  e.printStackTrace();
		  throw new ClassNotFoundException();
	  }
	}


	private byte[] parseAndMerge(String className) 
	  throws ClassNotFoundException
	{
	try {
	   FileInputStream fileStream = new FileInputStream(className);
	   ClassInfo classInfo = new ClassInfo(fileStream);
 	   
         long before = System.currentTimeMillis();
         classInfo.merge(mergeClassInfo);
       
         long after = System.currentTimeMillis();
	   System.out.println("Time for merge = " + (after - before));

         classInfo.toFile("Y2.class", false);
        
         return classInfo.getBytes(false);
	 	    }
	 catch (Exception e) {
		 e.printStackTrace();
		 throw new ClassNotFoundException();
	 }
	}


    /**
	 * @exception ClassNotFoundException
	 *     Cannot load the class specified because it cannot be found.
     */	
	@Override	
	public Class loadClass(String className) 
		throws ClassNotFoundException {
        return (loadClass(className, true));
    }


	/**
	 * @exception ClassNotFoundException
	 *     Cannot load the class specified because it cannot be found.
     */	
    @Override	
    public synchronized Class loadClass(String className, boolean resolveIt)
        throws ClassNotFoundException {
        Class result;
        byte  classData[];

        result = (Class)classes.get(className);
      
		if (result != null) {
              return result;
         }
        
		/* Check with the primordial class loader */
		
        try {
            result = super.findSystemClass(className);
            return result;
        } catch (ClassNotFoundException e) {
        }

        classData = parseAndMerge(className);
        if (classData == null) {
            throw new ClassNotFoundException();
        }

        result = defineClass(classData, 0, classData.length);
        if (result == null) {
            throw new ClassFormatError();
        }

        if (resolveIt) {
            resolveClass(result);
        }

        return result;
    }

public static void main (String[] args)
{
	try{
		MergeClassLoader mcl = new MergeClassLoader(args[0]);
		Class cl = mcl.loadClass(args[1]);
		Object o = cl.newInstance();
		System.out.println("" + o);
		System.out.println("" + ((U) o).dostuff(3,4));
	}
	catch (Exception e) {
		System.out.println("Exceptio" + e);
		e.printStackTrace();
	}
  }

}

