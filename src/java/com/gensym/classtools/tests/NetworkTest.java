package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class NetworkTest implements RuntimeConstants 
{
  public static void main (String[] args) {
    try {			
      String className = "com/gensym/classtools/tests/TestNetwork";
      
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
      
      MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestNetwork",
        "test",
        "()V");			
      Block b = new Block();
      
      b.add (new VariableDeclaration("x", "I", new Value(17)));

      OperatorCall comparison = 
        new OperatorCall(">", 
        new Expression[] {
	  new Variable("x", "I"),
	    new Value(25)});
        
      IfNode ifnode = new IfNode(comparison);

      MethodCall printcall 
	= new MethodCall(
            new FieldRef("java/lang/System", "out", "Ljava/io/PrintStream;", true),
	    new MethodRef("java/io/PrintStream", "println", "(Ljava/lang/String;)V"),
	    new Expression[] {
	        new OperatorCall("+", 
				 new Expression[] {
		  new Variable("x", "I"),
		  new Value(" is the current value of x.")
		    })},
            MTH_CALL_VIRTUAL);

      Block printblock = new Block();
      printblock.add(new ExpressionStatement(printcall));
      BlockNode printNode = new BlockNode(printblock);

      Expression incrementer
	= new OperatorCall("=",
			   new Expression [] {
	  new Variable("x", "I"),
	    new OperatorCall("+", new Expression [] {
	      new Variable("x", "I"),
		new Value(1)})});

      Block incrblock = new Block();
      incrblock.add(new ExpressionStatement(incrementer));
      BlockNode incrNode = new BlockNode(incrblock);

      NetworkStatement n = new NetworkStatement(printNode);
      n.add(ifnode);
      n.add(incrNode);

      printNode.setNextNode(ifnode);

      /*      
      System.out.println("if node is " + ifnode);
      System.out.println("its parent is " + ifnode.parent);
      System.out.println("its siblings are " + ifnode.parent.children);
      System.out.println("incr node is " + incrNode);
      */

      ifnode.setFinalIfTrue();
      ifnode.setNextNodeIfFalse(incrNode);
      //      ifnode.setFinalIfFalse();
      incrNode.setNextNode(printNode);

      b.add(n);
        
      //b.add(new Return());
        
    
     MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
       mr,
       null,
       b);
     ci.add(mi);
          
                  
     // ************* Output the bytes to file  *************
     FileOutputStream fileOutStream = new FileOutputStream("TestNetwork.class");
     fileOutStream.write(ci.getBytes(true));
     fileOutStream.close();
    
    
     //************** Load the new class into this VM ************
     Class cl = Class.forName("com.gensym.classtools.tests.TestNetwork");
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
