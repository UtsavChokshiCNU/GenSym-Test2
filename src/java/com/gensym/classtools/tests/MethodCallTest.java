package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class MethodCallTest implements RuntimeConstants {

public long longFunc() {
    return (long) 2;
}

public int intFunc() {
    return 2;
}

public void longSinkFunc(long arg) {
}

public void intSinkFunc(int arg) {
}

public static void main (String[] args) {	
    try {
			
        String className = "com/gensym/classtools/tests/TestMethodCall";
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
        

        // *** Creating a field ***
        // Create a FieldRef to refer to the field o in this class
        FieldRef fr =  new FieldRef("com/gensym/classtools/tests/TestMethodCall",
          "o",
          "Lcom/gensym/classtools/tests/MethodCallTest;",
          true);

        // Create a FieldInfo from this object and add it to the class
        FieldInfo fi =  new FieldInfo(new Access(ACC_PRIVATE | ACC_STATIC),fr,
          new New("com/gensym/classtools/tests/MethodCallTest"));
        ci.add(fi);

        // An instance method 
        
        MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestMethodCall",
            "test",
            "()V");			
        Block b = new Block();

        // Test calling 2 byte method in value returning and non-value returning
        // contexts
        MethodRef mr2 = new MethodRef("com/gensym/classtools/tests/MethodCallTest",
            "longFunc",
            "()J");

        MethodCall mc = new MethodCall(
                            fr,
                            mr2,
                            null,
                            MTH_CALL_VIRTUAL);

        b.add(mc);

        b.add(new VariableDeclaration("result","J"));
        b.add(new OperatorCall("=", 
          new Expression[] 
        { new Variable("result","J"),
          new MethodCall(fr, mr2, null, MTH_CALL_VIRTUAL)}));

        // Test calling 1 byte method in value returning and non-value returning
        // contexts
        MethodRef mr3 = new MethodRef("com/gensym/classtools/tests/MethodCallTest",
            "intFunc",
            "()I");

        MethodCall mc2 = new MethodCall(
                            fr,
                            mr3,
                            null,
                            MTH_CALL_VIRTUAL);

        b.add(mc2);

        b.add(new VariableDeclaration("result2","I"));
        b.add(new OperatorCall("=", 
          new Expression[] 
        { new Variable("result2","I"),
          new MethodCall(fr, mr3, null, MTH_CALL_VIRTUAL)}));
        
        // Test returning from a 1 byte method to a method that
        // takes a 1 byte argument
        MethodRef mr4 = new MethodRef("com/gensym/classtools/tests/MethodCallTest",
            "intSinkFunc",
            "(I)V");

        MethodCall mc3 = new MethodCall(
                            fr,
                            mr3,
                            null,
                            MTH_CALL_VIRTUAL);

        MethodCall mc4 = new MethodCall(
                            fr,
                            mr4,
                            new Expression[] {  mc3 },
                            MTH_CALL_VIRTUAL);
        
        b.add(mc4);


        // Test returning from a 2 byte method to a method that
        // takes a 2 byte argument

        MethodRef mr5 = new MethodRef("com/gensym/classtools/tests/MethodCallTest",
            "longSinkFunc",
            "(J)V");

        MethodCall mc5 = new MethodCall(
                            fr,
                            mr2,
                            null,
                            MTH_CALL_VIRTUAL);

        MethodCall mc6 = new MethodCall(
                            fr,
                            mr5,
                            new Expression[] {  mc5 },
                            MTH_CALL_VIRTUAL);

        b.add(mc6);
        

        b.add(new Return());

        MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
            mr,
            null,
            b);
        ci.add(mi);

                
        // ************* Output the bytes to file  *************
        FileOutputStream fileOutStream = new FileOutputStream("TestMethodCall.class");
        fileOutStream.write(ci.getBytes(true));
        fileOutStream.close();
	    		

        //************** Load the new class into this VM ************
        Class cl = Class.forName("com.gensym.classtools.tests.TestMethodCall");
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
