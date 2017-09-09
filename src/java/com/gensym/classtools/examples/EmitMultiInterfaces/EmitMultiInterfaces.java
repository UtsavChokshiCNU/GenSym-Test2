package com.gensym.classtools.examples.EmitMultiInterfaces;

import com.gensym.classtools.*;
import java.io.*;

/*
 *    An example use of the classtools facility to create a .class files for
 *    the following interfaces
 *    
 *    public interface ClassA { }
 *
 *    public interface ClassB { }
 *
 *    public interface ClassC extends ClassA, ClassB { }
 *
 */

public class EmitMultiInterfaces implements RuntimeConstants {

public static void main (String[] args) {	
  String packageName = "com.gensym.classtools.examples.EmitMultiInterfaces.";
  String classAName = packageName + "ClassA";
  String classBName = packageName + "ClassB";
  String classCName = packageName + "ClassC";

  
  try{
  
    ClassInfo classA =  new ClassInfo(new InterfaceAccess(ACC_INTERFACE |
      ACC_PUBLIC),
      classAName,
      false);

    ClassInfo classB =  new ClassInfo(new InterfaceAccess(ACC_INTERFACE |
      ACC_PUBLIC),
      classBName,
      false);


    ClassInfo classC =  new ClassInfo(new InterfaceAccess(ACC_INTERFACE |
      ACC_PUBLIC),
      classCName,
      new String []
    {classAName, classBName});


    // ************* Output the bytes to file  *************
    classA.toFile("ClassA.class",true);
    classB.toFile("ClassB.class",true);
    classC.toFile("ClassC.class",true);

    //  *********** Validate results by loading the emitted classes ***
    Class cl;
    cl = Class.forName(classAName);
    System.out.println("Loaded the " + cl);
    cl = Class.forName(classBName);
    System.out.println("Loaded the " + cl);
    cl = Class.forName(classCName);
    System.out.println("Loaded the " + cl);

  }
  catch (Exception e)  {
    System.out.println("Example failed" + e);
    e.printStackTrace();  
  }
}

}
