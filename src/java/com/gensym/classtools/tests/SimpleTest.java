package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class SimpleTest implements RuntimeConstants 
{
  public static void main (String[] args) {
    try {			

      String className = "com/gensym/classtools/tests/TestSimple";
      
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
      
      MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestSimple",
        "test",
        "()V");			

      Block b = new Block();

      FieldRef fr = new FieldRef("java.lang.System", "out", "Ljava/io/PrintStream;", true);

      MethodCall printcall 
	= new MethodCall(
			 fr,
	    new MethodRef("java/io/PrintStream", "println", "(Ljava/lang/String;)V"),
			 new Expression[] {
	  new OperatorCall("+", 
			   new Expression[] {
	    new Value(3),
	      new Value(" is a number.")})},
	  MTH_CALL_VIRTUAL);
      
      b.add(printcall);
    
     MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
       mr,
       null,
       b);
     ci.add(mi);
      
     MethodRef mr2 = new MethodRef("com/gensym/classtools/tests/TestSimple",
				   "test2",
        "()V");			

      Block b2 = new Block();

      b2.add(new VariableDeclaration("x", "I", new Value(23)));
      FieldRef fr2 = new FieldRef("java.lang.System", "out", "Ljava/io/PrintStream;", true);

      MethodCall printcall2
	= new MethodCall(
			 fr2,
	    new MethodRef("java/io/PrintStream", "println", "(Ljava/lang/String;)V"),
			 new Expression[] {
	  new OperatorCall("+", 
			   new Expression[] {
	    new Variable("x", "I"),
	      new Value(" is also a number.")})},
	  MTH_CALL_VIRTUAL);
      
      b2.add(printcall2);
    
     MethodInfo mi2 = new MethodInfo(new Access(ACC_PUBLIC),
       mr2,
       null,
       b2);
     ci.add(mi2);
          
                  
     // ************* Output the bytes to file  *************
     FileOutputStream fileOutStream = new FileOutputStream("TestSimple.class");
     fileOutStream.write(ci.getBytes(true));
     fileOutStream.close();
    
    
     //************** Load the new class into this VM ************
     Class cl = Class.forName("com.gensym.classtools.tests.TestSimple");
     System.out.println("Loaded the " + cl);
     TestExpressionInterface a = (TestExpressionInterface) cl.newInstance();
     System.out.println("New instance created " + a);
     a.test();         
   }
   catch (Exception e) 
   {
      e.printStackTrace();
   }
  } 
}
