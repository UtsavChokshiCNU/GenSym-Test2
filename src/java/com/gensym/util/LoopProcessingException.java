/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   LoopProcessingException.java 
 * 
 * 
 */ 
  

package com.gensym.util;

import java.util.Vector;
import java.util.Enumeration;
import java.io.PrintWriter;

/**
 * Encapsulates the idea that, during a loop, exceptions may be being
 * thrown, but the loop wishes to continue to the next iteration and at the
 * same time, the loop wishes to remember what exceptions occured during
 * processing, and throw a single exception to indicate that error(s) occured
 * during the processing. This exception should be used to store all the
 * exceptions that occured during the processing of the loop, and thrown
 * when the loop has finished processing.
 *<p>
 * One example of its use is by clients of concrete subclasses of
 * VectorQueueManager.
 * @see com.gensym.util.VectorQueueManager
 */
public class LoopProcessingException extends RuntimeException {

  private Vector eventExceptions;
  private Vector failedEvents;
  private Vector stackTraces;

  public LoopProcessingException(Vector eventExceptions,
				  Vector stackTraces,
				  Vector failedEvents) {
    this.eventExceptions = eventExceptions;
    this.failedEvents = failedEvents;
    this.stackTraces = stackTraces;
  }

  @Override
  public void printStackTrace() {
    super.printStackTrace();
    if (eventExceptions != null) {
      System.out.println("Nested Exceptions: ");
      for (Enumeration en = eventExceptions.elements();
	   en.hasMoreElements();) {
	((Throwable)en.nextElement()).printStackTrace();
      }
    }
  }

  @Override
  public void printStackTrace(PrintWriter writer) {
    super.printStackTrace(writer);
    if (eventExceptions != null) {
      writer.println("Nested Exceptions: ");
      for (Enumeration en = eventExceptions.elements();
	   en.hasMoreElements();) {
	((Throwable)en.nextElement()).printStackTrace(writer);
      }
    }
  }

  public void printFullStackTrace(PrintWriter writer) {
    super.printStackTrace(writer);
    if (eventExceptions != null) {
      Enumeration env = failedEvents.elements();
      writer.println("Nested Exceptions: ");
      for (Enumeration en = stackTraces.elements();
	   en.hasMoreElements();) {
	writer.println("Exception Raised for Event: ");
	writer.println(env.nextElement());
	writer.println("Exception was:");
	writer.print(en.nextElement());
      }
    }
  }
}

