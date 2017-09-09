package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class ContinueTest implements RuntimeConstants 
{
  public static void main (String[] args) {
    try {			

      String className = "com/gensym/classtools/tests/TestContinue";
      
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
      
      MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestContinue",
        "test",
        "()V");			

      Block b = new Block();
      
      b.add (new VariableDeclaration("x", "I", new Value(17)));

      // Until variable initializers work
      b.add(new ExpressionStatement(new OperatorCall("=",
						     new Expression [] {
	new Variable("x", "I"),
	  new Value(17)})));

      Block inner = new Block();

      Expression incrementer
	= new OperatorCall("=",
			   new Expression [] {
	  new Variable("x", "I"),
	    new OperatorCall("+", new Expression [] {
	      new Variable("x", "I"),
		new Value(1)})});

      inner.add(new ExpressionStatement(incrementer));


      FieldRef fr = new FieldRef("java.lang.System", "out", "Ljava/io/PrintStream;", true);

      System.out.println("FieldRef is of type " + fr.getExpressionType());
      System.out.println("Class name is stored internally in this type as <" + fr.getExpressionType().getClassName() + ">");
      MethodCall printcall 
	= new MethodCall(
			 fr,
	    new MethodRef("java/io/PrintStream", "println", "(Ljava/lang/String;)V"),
	    new Expression[] {
	        new OperatorCall("+", 
				 new Expression[] {
		  new Variable("x", "I"),
		  new Value(" is the current value of x.")
		    })},
            MTH_CALL_VIRTUAL);

      inner.add(printcall);

      OperatorCall comparison = 
        new OperatorCall(">", 
        new Expression[] {
	  new Variable("x", "I"),
	    new Value(25)});

      If maybecontinue = new If(comparison, new Continue());

      inner.add(maybecontinue);

      MethodCall printcall2
	= new MethodCall(
            new FieldRef("java/lang/System", "out", "Ljava/io/PrintStream;", true),
	    new MethodRef("java/io/PrintStream", "println", "(Ljava/lang/String;)V"),
	    new Expression[] {
	  new Value("x <= 25; continue ignored")
		    },
            MTH_CALL_VIRTUAL);

      inner.add (printcall2);

      OperatorCall comparison2 = 
        new OperatorCall("<", 
        new Expression[] {
	  new Variable("x", "I"),
	    new Value(30)});

      b.add(new While(comparison2, inner));
    
     MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
       mr,
       null,
       b);
     ci.add(mi);
          
                  
     // ************* Output the bytes to file  *************
     FileOutputStream fileOutStream = new FileOutputStream("TestContinue.class");
     fileOutStream.write(ci.getBytes(true));
     fileOutStream.close();
    
    
     //************** Load the new class into this VM ************
     Class cl = Class.forName("com.gensym.classtools.tests.TestContinue");
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
