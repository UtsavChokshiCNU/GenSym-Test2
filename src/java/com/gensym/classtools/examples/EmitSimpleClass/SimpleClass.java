package com.gensym.classtools.examples.EmitSimpleClass;

import java.io.FileOutputStream;
import com.gensym.classtools.*;

public class SimpleClass implements RuntimeConstants {
  ClassInfo c;
	
  public SimpleClass() {
    try {
      c = new ClassInfo(new ClassAccess(ACC_PUBLIC & ACC_FINAL),
			"com/gensym/examples/OtherClass",
			true);
    }
    catch (ClassException e) { }
  }

  public static void main(String[] args) {
    try {
      SimpleClass foo = new SimpleClass();
      FileOutputStream out = new FileOutputStream("OtherClass.class");
      out.write(foo.c.getBytes(true));
      out.close();
      ClassInfo.main(new String[] {"report","OtherClass.class"});
    }
    catch (Exception e) {
      System.out.println("Simple class failed: " + e);
    }
  }

}
