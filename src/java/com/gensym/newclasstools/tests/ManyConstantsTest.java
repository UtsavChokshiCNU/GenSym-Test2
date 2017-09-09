package com.gensym.newclasstools.tests;

import com.gensym.newclasstools.*;
import java.util.*;
import java.io.*;

public class ManyConstantsTest implements RuntimeConstants 
{
  public static void main (String[] args) {
    try {			

      Type classType = Type.makeType("com.gensym.newclasstools.tests.TestManyConstants");
      
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

      FieldInfo fi = new FieldInfo(new Access(ACC_PUBLIC), "x", Type.STRING_TYPE, new Value("Initial Value"), false);

      ci.add(fi);

      FieldRef xRef =  new FieldRef(classType, "x", Type.STRING_TYPE);

      Block b = new Block();
      MethodCall printcall;
      Expression assign;

      FieldRef fr = new FieldRef(Type.makeType("java.lang.System"),
				 "out",
				 Type.makeType("java.io.PrintStream"),
				 true);

      for (int i = 2; i < 300; i++) {
	assign
	  = new OperatorCall("=",
			   new Expression [] {
	    xRef, 
	      new Value("Value is now " + i + " ***")});

	b.add(assign);

	printcall 
	  = new MethodCall("println",
			   Type.makeType("java.io.PrintStream"),
			   new Type[]{Type.STRING_TYPE},
			   Type.VOID_TYPE,
			   fr,
			   new Expression[] {xRef},
			   MTH_CALL_VIRTUAL);
      
	b.add(printcall);
      }

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
     FileOutputStream fileOutStream = new FileOutputStream("TestManyConstants.class");
     fileOutStream.write(ci.getBytes(true));
     fileOutStream.close();
     System.out.println("Wrote the .class file");

     // ci.toStdout();

     //************** Load the new class into this VM ************
     Class cl = Class.forName("com.gensym.newclasstools.tests.TestManyConstants");
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
