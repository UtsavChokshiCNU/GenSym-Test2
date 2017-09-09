package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class ArrayTest implements RuntimeConstants 
{
  public static void main (String[] args) {
    try {			

      String className = "com/gensym/classtools/tests/TestArray";
      
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
      
      MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestArray",
        "test",
        "()V");			

      Block b = new Block();

      b.add(new VariableDeclaration("x", "I", new Value(3)));
      b.add(new VariableDeclaration("y", "[I"));

      //      b.add(new VariableDeclaration("v", "Ljava/util/Vector;",
      //			    new New("java.util.Vector")));

      b.add(new OperatorCall("=", new Expression[] {
	new Variable("y", "[I"),
	  new NewArray("[I", new OperatorCall("+", new Expression[] {
	    new Variable("x", "I"), new Value(4)
	      }))}));
      
      b.add(new OperatorCall("=", new Expression[] {
	new ArrayRef(new Variable("y", "[I"), 
		     new OperatorCall("+", 
				      new Expression[] {
		       new Variable("x", "I"),
			 new Value(2)})),
	  new Value(12)}));

      /*
      // print length by using copyInto to make a Vector (what a kludge!)
      b.add(new MethodCall(new Variable("v", "Ljava/util/Vector;"),
			   new MethodRef("java.util.Vector", "copyInto",
					 "([Ljava/lang/Object;)V"),
			   new Expression[] {
	new Variable("y", "[I")},
	MTH_CALL_VIRTUAL));

	*/

      FieldRef fr = new FieldRef("java.lang.System", "out", "Ljava/io/PrintStream;", true);

      MethodCall printcall 
	= new MethodCall(
			 fr,
	    new MethodRef("java/io/PrintStream", "println", "(Ljava/lang/String;)V"),
			 new Expression[] {
	  new OperatorCall("+", 
			   new Expression[] {
	    new Value("Fifth element of the array (should be 12) is "),
	      new ArrayRef(new Variable("y", "[I"), new Value(5))})},
	  MTH_CALL_VIRTUAL);
      
      b.add(printcall);

      MethodCall printcall2 
	= new MethodCall(
			 fr,
	    new MethodRef("java/io/PrintStream", "println", "(Ljava/lang/String;)V"),
			 new Expression[] {
	  new OperatorCall("+", 
			   new Expression[] {
	    new Value("Length of array (should be 7) is "),
	      new MethodCall(new MethodRef("java.lang.reflect.Array", "getLength",
					   "(Ljava/lang/Object;)I"),
			     new Expression[] {new Variable("y", "[I")},
			     MTH_CALL_STATIC)})},
	  MTH_CALL_VIRTUAL);
      
      b.add(printcall2);
    
     MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
       mr,
       null,
       b);
     ci.add(mi);
                  
     // ************* Output the bytes to file  *************
     FileOutputStream fileOutStream = new FileOutputStream("TestArray.class");
     fileOutStream.write(ci.getBytes(true));
     fileOutStream.close();
    
    
     //************** Load the new class into this VM ************
     Class cl = Class.forName("com.gensym.classtools.tests.TestArray");
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
