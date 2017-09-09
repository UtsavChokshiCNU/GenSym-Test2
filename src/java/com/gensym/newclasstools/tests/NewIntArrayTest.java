package com.gensym.newclasstools.tests;

import com.gensym.newclasstools.*;
import java.util.*;
import java.io.*;

public class NewIntArrayTest implements RuntimeConstants 
{
  public static void main (String[] args) {
    try {			

      Type classType = Type.makeType("com.gensym.newclasstools.tests.TestNewIntArray");
      
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

      Type intArray = Type.makeType(Type.INT_TYPE, 1);

      FieldInfo fi = new FieldInfo(new Access(ACC_PUBLIC), "x", intArray, null, false);

      ci.add(fi);

      FieldRef xRef =  new FieldRef(classType, "x", intArray);

      Block b = new Block();

      NewArray na = 
	new NewArray(Type.INT_TYPE,
		     (int)1, 
		     new Expression[] {new Value(5)});

      b.add(new OperatorCall("=", 
			     new Expression[] {xRef, na}));

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
	    xRef,
	      new Value(" is the current value of x.")
	      })},
	  MTH_CALL_VIRTUAL);
      
      b.add(printcall);
    
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
     FileOutputStream fileOutStream = new FileOutputStream("TestNewIntArray.class");
     fileOutStream.write(ci.getBytes(true));
     fileOutStream.close();
     System.out.println("Wrote the .class file");

     // ci.toStdout();

     //************** Load the new class into this VM ************
     Class cl = Class.forName("com.gensym.newclasstools.tests.TestNewIntArray");
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
