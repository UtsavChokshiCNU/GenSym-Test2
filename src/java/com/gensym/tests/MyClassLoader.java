
package com.gensym.tests;
public class MyClassLoader extends ClassLoader {

@Override
public Class loadClass (String name, boolean resolve) {
  return null;
  }

  class InnerClass {
    public void callOuterFindSystemClass (String className) {
      try {
	findSystemClass1 (className);
      } catch (ClassNotFoundException e) {
      }
    }
  }

  private final Class findSystemClass1 (String className) throws java.lang.ClassNotFoundException {
    return super.findSystemClass (className);
  }
}
