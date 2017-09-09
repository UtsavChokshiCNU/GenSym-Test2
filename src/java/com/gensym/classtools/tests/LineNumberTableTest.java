package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class LineNumberTableTest implements RuntimeConstants {


public static void main (String[] args) {	
    try {
			
        String className = "com/gensym/classtools/tests/TestLineNumberTable";
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

        ci.add(new SourceFileAttribute("LineNumberTableRef.java"));
      
      // An instance method 
        
        MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestLineNumberTable",
            "test",
            "()V");			
        Block b = new Block();
        
        Block tryBlock = new Block();
        Throw thrw = new Throw(new New("java/lang/Exception"));
        thrw.setLineNumber(12); // See LineNumberTableRef.java
        tryBlock.add(thrw);
        
        Block catchBlock = new Block();
        Variable var = new Variable("e","Ljava/lang/Exception;");
        MethodRef mr2 = new MethodRef("java/lang/Exception","printStackTrace","()V");
        MethodCall mc = new MethodCall(var, 
                                       mr2,
                                       null,
                                       MTH_CALL_VIRTUAL);
        mc.setLineNumber(16);  // See LineNumberTableRef.java
        catchBlock.add(mc);

        b.add(new Try(tryBlock, 
                      new VariableDeclaration[] {
                        new VariableDeclaration("e","Ljava/lang/Exception;")
                        },
                      new Block[] {catchBlock}));
                        
        b.add(new Return());

        //b.toStdout();

        MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
            mr,
            null,
            b);
        ci.add(mi);
        
                
        // ************* Output the bytes to file  *************
        FileOutputStream fileOutStream = new FileOutputStream("TestLineNumberTable.class");
        fileOutStream.write(ci.getBytes(true));
        fileOutStream.close();
	    		

        //************** Load the new class into this VM ************
        Class cl = Class.forName("com.gensym.classtools.tests.TestLineNumberTable");
        System.out.println("Loaded the " + cl);
        TestExpressionInterface a = (TestExpressionInterface) cl.newInstance();
        System.out.println("New instance created " + a);
        System.out.println("EXPECT EXCEPTION AT LINE 12:");
        a.test();
    }
    catch (Exception e) {
        System.out.println("Failure " + e);
        e.printStackTrace();
    }
}   
}   
