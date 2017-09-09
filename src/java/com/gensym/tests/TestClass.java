
package com.gensym.tests;

public class TestClass {

  public static void someRPC () {
    try {
      Thread.sleep (20000);
    } catch (InterruptedException ie) {
    }
  }

  
  public static int someRPCInt () {
    try {
      Thread.sleep (20000);
    } catch (InterruptedException ie) {
    }
    return 21;
  }

  
  public static int someRPC (int x) {
    try {
      Thread.sleep (20000);
    } catch (InterruptedException ie) {
    }
    return (x += 21);
  }

  public static void fooRPC () {
  }

}
