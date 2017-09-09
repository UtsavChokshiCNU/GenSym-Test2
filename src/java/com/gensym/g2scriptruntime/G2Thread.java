package com.gensym.g2scriptruntime;

import java.lang.reflect.*;

public class G2Thread extends Thread {
  Object object;
  Method method;
  Object[] args;
  long delay;
  protected Throwable stackTraceObject = new Throwable();

  public G2Thread (Object object, Method m, Object[] args, long delay)
  {
    this.object = object;
    this.method = m;
    this.args = args;
    this.delay = delay;
    stackTraceObject.fillInStackTrace ();
  }

  @Override
  public void run () 
  {  
    try {
      if (delay != 0)
	Thread.sleep(delay);
      method.invoke (object, args);
    } catch (Exception e) {
      cleanup (e);
    }
  }

  void cleanup (Exception e) {
    // do nothing, but spit out the call trace
    Throwable t;
    if (e instanceof InvocationTargetException)
      t = ((InvocationTargetException)e).getTargetException ();
    else
      t = e;
    System.out.println ("G2 thread encountered an Exception");
    t.printStackTrace ();
    System.out.println ("Backtrace of Initiating thread:");
    stackTraceObject.printStackTrace ();
  }

}
