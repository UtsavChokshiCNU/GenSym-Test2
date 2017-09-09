
package com.gensym.tests;

public class FindSystemClassTest extends ClassLoader {

  public static void main (String[] args) {
    new FindSystemClassTest().runTest ();
  }

  public void runTest () {
    int numErrs = 0;
    long t0 = System.currentTimeMillis ();
    for (int i=0; i<100; i++) {
      try {
	Class c = super.findSystemClass ("junk.class.Name");
      } catch (ClassNotFoundException cnfe) {
	numErrs++;
      }
    }
    long t1 = System.currentTimeMillis ();
    System.out.println ("Time for 100 junk loads = " + (t1 - t0) + "ms with " + numErrs + " errors");

    t0 = System.currentTimeMillis ();
    for (int i=0; i<100; i++) {
      try {
	Class c = super.findSystemClass ("com.gensym.jgi.rmi.G2RMIAccessBrokerImpl");
      } catch (ClassNotFoundException cnfe) {
	numErrs++;
      }
    }
    t1 = System.currentTimeMillis ();
    System.out.println ("Time for 100 real loads = " + (t1 - t0) + "ms with " + numErrs + " errors");
  }

  @Override
  public Class loadClass (String className, boolean resolve)  throws ClassNotFoundException {
    return super.findSystemClass (className);
  }
}
