package com.gensym.newclasstools.tests;

import com.gensym.newclasstools.*;
import java.util.*;
import java.io.*;

public class ForTest implements RuntimeConstants 
{
  public static void main (String[] args) {
    try {			

      Type classType = Type.makeType("com.gensym.newclasstools.tests.TestFor");
      
      ClassInfo ci =  new ClassInfo(new ClassAccess(ACC_PUBLIC |
						    ACC_FINAL  |
						    ACC_SUPER),
				    classType,
				    Type.OBJECT_TYPE,
				    true);

      
      // *** Adding an Interface ***
      InterfaceInfo intinf = 
      new InterfaceInfo(Type.makeType("com.gensym.newclasstools.tests.TestExpressionInterface"));
      ci.add(intinf);
      // An instance method 

      FieldInfo fi = new FieldInfo(new Access(ACC_PUBLIC), "x", Type.INT_TYPE, new Value(12), false);

      ci.add(fi);

      FieldRef xRef =  new FieldRef(classType, "x", Type.INT_TYPE);

      Block b = new Block();
      
      Block inner = new Block();

      ExpressionStatement incrementer
	= new ExpressionStatement(new OperatorCall("post++",
						   new Expression [] {
	  xRef}));

      FieldRef fr = new FieldRef(Type.makeType("java.lang.System"),
				 "out",
				 Type.makeType("java.io.PrintStream"),
				 true);

      // System.out.println("FieldRef is of type " + fr.getExpressionType());
      // System.out.println("Class name is stored internally in this type as <" + fr.getExpressionType().getClassName() + ">");
      MethodCall printcall 
	= new MethodCall("println",
			 Type.makeType("java.io.PrintStream"),
			 new Type[]{Type.STRING_TYPE},
			 Type.VOID_TYPE,
			 fr,
			 new Expression[] {
	  new OperatorCall("+", 
			   new Expression[] {
	    xRef,
	      new Value(" is the current value of x.")
	      })},
	  MTH_CALL_VIRTUAL);

      inner.add(printcall);

      OperatorCall comparison = 
        new OperatorCall(">", 
        new Expression[] {
	  xRef,
	    new Value(25)});

      If maybecontinue = new If(comparison, new Continue());

      inner.add(maybecontinue);

      MethodCall printcall2
	= new MethodCall("println",
			 Type.makeType("java.io.PrintStream"),
			 new Type[]{Type.STRING_TYPE},
			 Type.VOID_TYPE,
			 fr,
			 new Expression[] {
	  new Value("x <= 25; continue ignored")
	    },
	  MTH_CALL_VIRTUAL);

      inner.add (printcall2);

      OperatorCall comparison2 = 
        new OperatorCall("<", 
        new Expression[] {
	  xRef,
	    new Value(30)});

      b.add(new For
	    (new ExpressionStatement[] {
	      new ExpressionStatement
		(new OperatorCall("=",
				  new Expression[]{xRef, new Value(16)}))},
	      comparison2,
	      new ExpressionStatement[]{incrementer},
	      inner));
    
     MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
				    "test",
				    Type.VOID_TYPE,
				    null,
				    b,
				    null,
				    null);
     ci.add(mi);
          
     System.out.println("Created the classInfo");
                  
     // ************* Output the bytes to file  *************
     FileOutputStream fileOutStream = new FileOutputStream("TestFor.class");
     fileOutStream.write(ci.getBytes(true));
     fileOutStream.close();
     System.out.println("Wrote the .class file");

     // ci.toStdout();

     //************** Load the new class into this VM ************
     Class cl = Class.forName("com.gensym.newclasstools.tests.TestFor");
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
