package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class TryExpressionTest implements RuntimeConstants {

public static boolean takeException = false;

public static boolean takeException()
          throws Exception
{
  if(takeException)
    throw new Exception();

  return true;
}

public static void main (String[] args) {	
  try {			
    String className = "com/gensym/classtools/tests/TestTryExpression";
    
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
    
    MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestTryExpression",
      "test",
      "()V");			
    Block b = new Block();
    

    // Simple boolean expression test
    
    b.add(new VariableDeclaration("foo","Z",new Value(false)));
    Block block2 = new Block();
    block2.add(new If(new Variable("foo","Z"), 
      new Throw(new New("java.lang.Exception"))));
    
    
    MethodRef mr2 = new MethodRef("com/gensym/classtools/tests/TryExpressionTest",
      "takeException",
      "()Z");			

    
    MethodCall mc = new MethodCall(mr2, null, MTH_CALL_STATIC);

    TryExpression expTry = 
      new TryExpression(mc,
      new VariableDeclaration[] {
      new VariableDeclaration("e","Ljava/lang/Exception;")},
       new Expression[] { new Value(false) });
      
    b.add(new If(expTry,new StatementExpression(new OperatorCall("=", new Expression[] {new Variable("foo","Z"),
    new Value(true)}))));
    b.add(new OperatorCall("=", new Expression[] {new Variable("foo", "Z"),
        new Value(false)}));
      
    //b.toStdout();
      
    MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
      mr,
      null,
      b);
    ci.add(mi);
      
        
    // ************* Output the bytes to file  *************
    FileOutputStream fileOutStream = new FileOutputStream("TestTryExpression.class");
    fileOutStream.write(ci.getBytes(true));
    fileOutStream.close();
        
      
    //************** Load the new class into this VM ************
    Class cl = Class.forName("com.gensym.classtools.tests.TestTryExpression");
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

