package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class TryTest implements RuntimeConstants {


public static void main (String[] args) {	
    try {
			
        String className = "com/gensym/classtools/tests/TestTry";
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
        
        MethodRef mr = new MethodRef("com/gensym/classtools/tests/TryTest",
            "test",
            "()V");			
        Block b = new Block();
          

        /* The empty try block case */

        b.add(new Try(new Block(), 
                      new VariableDeclaration[] {
                        new VariableDeclaration("e","Ljava/lang/Exception;")
                        },
                      new Block[] {new Block()}));

        /* A single try and catch block */


        Block tryBlock1 = new Block();
        tryBlock1.add(new VariableDeclaration("try","Z",new Value(false)));
        b.add(new Try( tryBlock1,
                       new VariableDeclaration[] {
                         new VariableDeclaration("e","Ljava/lang/Exception;")
                         },
                       new Block[] {new Block()}));
       

        /* Multiple catch blocks */

        Block tryBlock2 = new Block();
        tryBlock2.add(new Throw(new New("java/lang/Exception")));
        b.add(new Try( tryBlock2,
                       new VariableDeclaration[] {
                         new VariableDeclaration("e","Ljava/lang/Exception;"),
                         new VariableDeclaration("t","Ljava/lang/Throwable;")
                         },
                       new Block[] {new Block(),
                                    new Block()}));

        /* Nested try catch statements */

        Block tryBlock3 = new Block();
        tryBlock3.add(new Throw(new New("java/lang/Exception")));
        Try innerTry = new Try( tryBlock3,
                        new VariableDeclaration[] {
                          new VariableDeclaration("e","Ljava/lang/ClassCastException;"),
                          },
                        new Block[] {new Block()});

        Block tryBlock4 = new Block();
        tryBlock4.add(innerTry);

        Try outerTry = new Try( tryBlock4,
                        new VariableDeclaration[] {
                          new VariableDeclaration("e","Ljava/lang/Exception;"),
                          },
                        new Block[] {new Block()});

        b.add(outerTry);

       
        Block tryBlock5 = new Block();
        tryBlock5.add(new VariableDeclaration("try","Z",new Value(false)));         

        Block finallyBlock1 = new Block();
        finallyBlock1.add(new VariableDeclaration("finally","Z",new Value(false)));

        b.add(new Try(tryBlock5,finallyBlock1));


        Block tryBlock6 = new Block();
        tryBlock6.add(new VariableDeclaration("try","Z",new Value(false)));         

        Block finallyBlock2 = new Block();
        finallyBlock2.add(new VariableDeclaration("finally","Z",new Value(false)));

        Block catchBlock = new Block();
        catchBlock.add(new VariableDeclaration("catch","Z",new Value(false)));         

        b.add(new Try(tryBlock6,
                      new VariableDeclaration[] {
                       new VariableDeclaration("e","Ljava/lang/Exception;")
                       },
                      new Block[] { catchBlock },
                      finallyBlock2));


        Block tryBlock7 = new Block();
        tryBlock7.add(new Throw(new New("java/lang/Exception")));         

        Block finallyBlock3 = new Block();
        finallyBlock3.add(new VariableDeclaration("finally","Z",new Value(false)));

        Block catchBlock1 = new Block();
        catchBlock1.add(new VariableDeclaration("catch","Z",new Value(false)));         

        Block catchBlock2 = new Block();
        catchBlock2.add(new VariableDeclaration("catch","Z",new Value(false)));         

        b.add(new Try(tryBlock7,
                      new VariableDeclaration[] {
                       new VariableDeclaration("e","Ljava/lang/Exception;"),
                       new VariableDeclaration("e","Ljava/lang/Throwable;")
                       },
                      new Block[] { catchBlock1, catchBlock2 },
                      finallyBlock3));

        //b.add(new Return());


        MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
            mr,
            null,
            b);
        ci.add(mi);
        
                
        // ************* Output the bytes to file  *************
        FileOutputStream fileOutStream = new FileOutputStream("TestTry.class");
        fileOutStream.write(ci.getBytes(true));
        fileOutStream.close();
	    		

        //************** Load the new class into this VM ************
        Class cl = Class.forName("com.gensym.classtools.tests.TestTry");
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
