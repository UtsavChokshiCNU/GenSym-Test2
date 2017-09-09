
package com.gensym.util;

import java.lang.reflect.*;


/**
 * This class runs a Helper thread to do what the client wants
 * to do. Use this if you have to complete a task synchronously
 * but don't want to hold up the current thread (it may be called
 * out of the UI.
 */

public class Helper extends Thread {
  protected Object root;
  protected Method method;
  protected Object[] args;
  protected Throwable stackTraceObject = new Throwable ();

  public Helper (Object root, Method m, Object[] args) {
    this.root = root;
    this.method = m;
    this.args = args;
    stackTraceObject.fillInStackTrace ();
  }

  @Override
  public void run () {
    try {
      method.invoke (root, args);
    } catch (Exception e) {
      cleanup (e);
    }
  }

  /**
   * A method to cleanup after any exceptions that might occur
   * during the method call. Note that Errors and other
   * Throwables are not caught and forwarded. The default
   * implementation simply prints a stack trace of the
   * point of throw and for the call that spawned the Helper.
   * Subclasses should feel free to override this behaviour
   * and / or do specific cleanup tasks.
   */
  public void cleanup (Exception e) {
    // do nothing, but spit out the call trace
    Throwable t;
    if (e instanceof InvocationTargetException)
      t = ((InvocationTargetException)e).getTargetException ();
    else
      t = e;
    System.out.println ("Helper thread encountered an Exception");
    t.printStackTrace ();
    System.out.println ("Backtrace of Initiating thread:");
    stackTraceObject.printStackTrace ();
  }

}
