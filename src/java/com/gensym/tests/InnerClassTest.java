
package com.gensym.tests;

public class InnerClassTest {

  public static void main (String[] args) throws IllegalAccessException, InstantiationException, ClassNotFoundException {
    Class cls = Class.forName ("vkp.Slider");

    Object s = cls.newInstance ();
    System.out.println ("Created = " + s);
  }
}
