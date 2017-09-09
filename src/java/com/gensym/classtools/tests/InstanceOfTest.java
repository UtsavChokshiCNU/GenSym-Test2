package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class InstanceOfTest implements RuntimeConstants 
{
  public static void main (String[] args) {
    try {			
      String className = "com/gensym/classtools/tests/TestInstanceOf";
      
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
      
      MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestInstanceOf",
        "test",
        "()V");			
      Block b = new Block();
      
      OperatorCall instanceOf = 
        new OperatorCall("instanceof", 
        new Expression[] {
        new New("java.lang.Object"),
        new ClassRef("java.lang.Object")});
        
      If ifStatement = new If(instanceOf, new Return());
        
      b.add(ifStatement);
        
      //b.add(new Return());
        
    
     MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
       mr,
       null,
       b);
     ci.add(mi);
          
                  
     // ************* Output the bytes to file  *************
     FileOutputStream fileOutStream = new FileOutputStream("TestInstanceOf.class");
     fileOutStream.write(ci.getBytes(true));
     fileOutStream.close();
    
    
     //************** Load the new class into this VM ************
     Class cl = Class.forName("com.gensym.classtools.tests.TestInstanceOf");
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
