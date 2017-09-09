package com.gensym.com.tests;

import com.gensym.com.JavaClass;
import com.gensym.com.Guid;

import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.classtools.RuntimeConstants;

public class TestJavaClass implements ActiveXRuntimeConstants, RuntimeConstants
{

public static void main(String[] args) {
      try {
          JavaClass testClass1  
            = new JavaClass(new Guid(),
                            "com.gensym.com.tests.InsertableCreatableTest",
                            true,
                            true,
                            false,
                            "Java Class",
                            "A big ole load a",
                            "AJSCLass.ocx");

          testClass1.addMethod(ACC_PUBLIC,10,"QueryInterface",
                              "(Lcom/gensym/com/Variant;Lcom/gensym/com/Variant;Lcom/gensym/com/Variant;)V",
                              null,
                              AX_INVOKE);

          testClass1.addMethod(ACC_PUBLIC,10,"AddRef",
                              "()J",
                              "Long",
                              AX_INVOKE);

          testClass1.addMethod(ACC_PUBLIC,10,"BackColor",
                              "(Ljava/awt/Color;)V",
                              null,
                              AX_PROPERTYSET);

          testClass1.addMethod(ACC_PUBLIC,10,"BackColor",
                              "()Ljava/awt/Color;",
                              "Color",
                              AX_PROPERTYGET);

          testClass1.toFile("InsertableCreatableTest.class",true);

          Class cl1 = Class.forName("com.gensym.com.tests.InsertableCreatableTest");
          System.out.println("Loaded the " + cl1);
          Object a1 = (Object) cl1.newInstance();
          System.out.println("New instance created " + a1);

          
          JavaClass testClass2  = new JavaClass(new Guid(),
                                               "com.gensym.com.tests.UnInsertableCreatableTest",
                                               true,
                                               false,
                                               false,
                                               "Java Class",
                                               "A big ole load a",
                                               "AJSCLass.ocx");

          testClass2.toFile("UnInsertableCreatableTest.class",true);

          Class cl2 = Class.forName("com.gensym.com.tests.UnInsertableCreatableTest");
          System.out.println("Loaded the " + cl2);
          Object a2 = (Object) cl2.newInstance();
          System.out.println("New instance created " + a2);
          

          JavaClass testClass3  = new JavaClass(new Guid(),
                                               "com.gensym.com.tests.UnInsertableUnCreatableTest",
                                               false,
                                               false,
                                               false,
                                               "Java Class",
                                               "A big ole load a",
                                               "AJSCLass.ocx");

          testClass3.toFile("UnInsertableUnCreatableTest.class",true);

          Class cl3 = Class.forName("com.gensym.com.tests.UnInsertableUnCreatableTest");
          System.out.println("Loaded the " + cl3);

          JavaClass testClass4  = new JavaClass(new Guid(),
                                               "com.gensym.com.tests.InterfaceTest",
                                               false,
                                               false,
                                               true,
                                               "Java Class",
                                               "A big ole load a",
                                               "AJSCLass.ocx");

          testClass4.toFile("InterfaceTest.class",true);

          Class cl4 = Class.forName("com.gensym.com.tests.InterfaceTest");
          System.out.println("Loaded the " + cl4);
      }
      catch (Exception e) {
          System.out.println("Class Emit failed\n");
          e.printStackTrace();

      }
  }
}
