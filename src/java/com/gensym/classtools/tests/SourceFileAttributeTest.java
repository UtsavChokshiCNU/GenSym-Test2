package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class SourceFileAttributeTest implements RuntimeConstants {

public static void main (String[] args) {	
    try {
			
        String className = "com/gensym/classtools/tests/TestSourceFileAttribute";
        // Create a ClassInfo to hold the class being created.  This class is named
        // TestProxy, it has no superior classes and it is public and final.
        ClassInfo ci =  new ClassInfo(new ClassAccess(ACC_PUBLIC |
            ACC_FINAL  |
            ACC_SUPER),
            className,
            true);
        
        ci.add(new SourceFileAttribute("TestSourceFileAttribute.java"));
                
        // ************* Output the bytes to file  *************
        FileOutputStream fileOutStream 
          = new FileOutputStream("TestSourceFileAttribute.class");
        fileOutStream.write(ci.getBytes(true));
        fileOutStream.close();
	    		

        //************** Load the new class into this VM ************
        Class cl = Class.forName("com.gensym.classtools.tests.TestSourceFileAttribute");
        System.out.println("Loaded the " + cl);
        ClassInfo.main(new String[] {"report", "TestSourceFileAttribute.class"});
    }
    catch (Exception e) {
        System.out.println("Failure " + e);
        e.printStackTrace();
    }
}   
}   
