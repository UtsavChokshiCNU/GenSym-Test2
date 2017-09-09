package com.gensym.devtools;

import java.lang.reflect.*;

/** This class can be used to launch another class by invoking the main
 *  method.  The first command line argument is the name of the class to
 *  launch, and the rest of the arguments are passed to the launched class.
 */

public class Launcher {

  public static void main (String[] args) {

    try {

      String classToLaunch = args[0];
      Class c = Class.forName (classToLaunch);
      Class stringArrayClass = (new String[0]).getClass ();
      Method mainMethod = c.getDeclaredMethod ("main", new Class[] {stringArrayClass});
      String[] launchArgs = new String[args.length - 1];
      System.arraycopy (args, 1, launchArgs, 0, args.length - 1);
      mainMethod.invoke (null, new Object[] {launchArgs});

      } catch (Throwable ex) {
        System.out.println (ex);
        ex.printStackTrace ();

        if (ex instanceof ExceptionInInitializerError) {
          ExceptionInInitializerError eiie = (ExceptionInInitializerError) ex;

          Throwable nestedEx = eiie.getException ();
          System.out.println (nestedEx);
          nestedEx.printStackTrace ();
        }
	if (ex instanceof java.lang.reflect.InvocationTargetException) {
	  InvocationTargetException ite = (InvocationTargetException)ex;
	  Throwable nestedEx = ite.getTargetException ();
	  System.out.println (nestedEx);
	  nestedEx.printStackTrace ();
	}	  

     }
  }
}
