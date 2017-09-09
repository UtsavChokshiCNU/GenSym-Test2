package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class ReferenceTest implements RuntimeConstants {


public static void main (String[] args) {	
  try {
    
    String className = "com/gensym/classtools/tests/TestReference";
    // Create a ClassInfo to hold the class being created.  This class is named
    // TestProxy, it has no superior classes and it is public and final.
    ClassInfo ci =  new ClassInfo(new ClassAccess(ACC_PUBLIC |
      ACC_FINAL  |
      ACC_SUPER),
      className,
      true);
    
    // *** Adding an Interface ***
    InterfaceInfo intinf = new InterfaceInfo("com/gensym/classtools/tests/TestExpressionInterface");
    ci.add(intinf);
    
    
    // An instance method 
    
    MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestExpression",
      "test",
      "()V");			
    Block b = new Block();

    VariableDeclaration myvar = new VariableDeclaration("myvar", "Ljava/awt/Color;");
    b.add(myvar);    
    Variable var = myvar.getVariable();

    b.add(new OperatorCall("=", new Expression[] {var, new Value(null)}));
      
    VariableDeclaration myvar2 = new VariableDeclaration("myvar2", "Ljava/lang/String;");
    b.add(myvar2);    
    Variable var2 = myvar2.getVariable();

    b.add(new OperatorCall("=", new Expression[] {var2, new Value(null)}));

    b.add(new OperatorCall("=", new Expression[] {var2, new Value("Hello World")}));


    b.add(new Return());
    
    MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
      mr,
      null,
      b);

    ci.add(mi);
    
    // ************* Output the bytes to file  *************
    FileOutputStream fileOutStream = new FileOutputStream("TestReference.class");
    fileOutStream.write(ci.getBytes(true));
    fileOutStream.close();
    
    
    //************** Load the new class into this VM ************
    Class cl = Class.forName("com.gensym.classtools.tests.TestReference");
    System.out.println("Loaded the " + cl);
    TestExpressionInterface a = (TestExpressionInterface) cl.newInstance();
    System.out.println("New instance created " + a);
    a.test();
    
  }
  catch (Exception e) 
  {
    System.out.println("Failure " + e);
    e.printStackTrace();
  }
}
}
