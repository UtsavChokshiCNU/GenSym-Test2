package com.gensym.newclasstools.tests;

import com.gensym.newclasstools.*;

public class TypeTest implements RuntimeConstants {
  public static void main(String[] args) {

    System.out.println("Running simple type test");

    /*
    Type mytype = Type.makeType("foo.bar.baz");
    System.out.println("New Type " + mytype + " created");
    System.out.println("Descriptor is " + mytype.descriptor());
    */

     System.out.println("Creating Type object for [[[I");
     Type newType3 = Type.makeType(Type.INT_TYPE, 3);
     System.out.println("Type created, prints as " + newType3);

     System.out.println("Creating Type object for [[I");
     Type newType2 = Type.makeType(Type.INT_TYPE, 2);
     System.out.println("Type created, prints as " + newType2);

     System.out.println("Creating Type object for [I");
     Type newType = Type.makeType(Type.INT_TYPE, 1);
     System.out.println("Type created, prints as " + newType);

     System.out.println("Creating Type object (again) for [[[I");
     Type newType3a = Type.makeType(Type.INT_TYPE, 3);
     System.out.println("Type created, prints as " + newType3a);
     /*
     Type newType3 = Type.makeType(mytype, 3);
     System.out.println("Type created, prints as " + newType3);
     */
  }
}
