
package com.gensym.tests;

public class TestClassDefinition {

  public static void main (String[] args) throws Exception {
    Class c = Class.forName ("com.gensym.classes.ClassDefinition");
    c.getField ("staticAttributes");
  }
}
