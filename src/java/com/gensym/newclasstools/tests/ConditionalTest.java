package com.gensym.newclasstools.tests;

import com.gensym.newclasstools.*;
import java.util.*;
import java.io.*;

public class ConditionalTest implements RuntimeConstants 
{
  public static void main (String[] args) {
    try {			

      Type classType = Type.makeType("com.gensym.newclasstools.tests.TestConditional");
      
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

      FieldInfo fi = new FieldInfo(new Access(ACC_PUBLIC), "x", Type.INT_TYPE, new Value(17), false);

      ci.add(fi);

      FieldRef xRef =  new FieldRef(classType, "x", Type.INT_TYPE);

      Block b = new Block();

      FieldRef fr = new FieldRef(Type.makeType("java.lang.System"),
				 "out",
				 Type.makeType("java.io.PrintStream"),
				 true);

      MethodCall printcall 
	= new MethodCall("println",
			 Type.makeType("java.io.PrintStream"),
			 new Type[]{Type.STRING_TYPE},
			 Type.VOID_TYPE,
			 fr,
			 new Expression[] {
	  new OperatorCall("+", 
			   new Expression[] {
	    new OperatorCall("?:", new Expression[] {
	      new Value(true),
		new Value(3),
		new Value(5)}),
	      new Value(" is the current value of x.")
	      })},
	  MTH_CALL_VIRTUAL);
      
      b.add(printcall);

      MethodCall printcall2 
	= new MethodCall("println",
			 Type.makeType("java.io.PrintStream"),
			 new Type[]{Type.STRING_TYPE},
			 Type.VOID_TYPE,
			 fr,
			 new Expression[] {
	  new OperatorCall("+", 
			   new Expression[] {
	    new OperatorCall("==", new Expression[] {
		new Value(3),
		  xRef}),
	      new Value(" is the current value of (x == 3).")
	      })},
	  MTH_CALL_VIRTUAL);
      
      b.add(printcall2);
    
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
     FileOutputStream fileOutStream = new FileOutputStream("TestConditional.class");
     fileOutStream.write(ci.getBytes(true));
     fileOutStream.close();
     System.out.println("Wrote the .class file");

     // ci.toStdout();

     //************** Load the new class into this VM ************
     Class cl = Class.forName("com.gensym.newclasstools.tests.TestConditional");
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
