package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class SynchronizedTest implements RuntimeConstants {


public static void main (String[] args) {	
    try {
			
        String className = "com/gensym/classtools/tests/TestSynchronized";
        // Create a ClassInfo to hold the class being created.  This class is named
        // TestProxy, it has no superior classes and it is public and final.
        ClassInfo ci =  new ClassInfo(new ClassAccess(ACC_PUBLIC |
            ACC_FINAL  |
            ACC_SUPER),
            className,
            true);
        
        // *** Adding an Interface ***
        InterfaceInfo intinf = 
			new InterfaceInfo("com/gensym/classtools/tests/TestExpressionInterface");
        ci.add(intinf);
    
      
      // An instance method 
        
        MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestSynchronized",
            "test",
            "()V");			
        Block b = new Block();

        Block bl =  new Block();
        bl.add(new VariableDeclaration("hello","I",new Value((int) 20)));

        Synchronized sync = new Synchronized(new Variable(0,
                                              "Ljava/lang/Object;"),
                                             bl);
        b.add(sync);
          

        MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
            mr,
            null,
            b);
        ci.add(mi);
        
                
        // ************* Output the bytes to file  *************
        FileOutputStream fileOutStream = new FileOutputStream("TestSynchronized.class");
        fileOutStream.write(ci.getBytes(true));
        fileOutStream.close();
	    		

        //************** Load the new class into this VM ************
        Class cl = Class.forName("com.gensym.classtools.tests.TestSynchronized");
        System.out.println("Loaded the " + cl);
        TestExpressionInterface a = (TestExpressionInterface) cl.newInstance();
        System.out.println("New instance created " + a);
        a.test();
        
    }
    catch (Exception e) {
        System.out.println("Failure " + e);
        e.printStackTrace();
    }
}   
}   
