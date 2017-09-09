package com.gensym.message;

/**
 * This interface can be used to mark a class that is capable of providing Trace messages as part of
 * a "process".
 */
public interface TraceableProcessObject
{

  /**
   * Get the ProcessTrace that is being used to report trace messages
   * for this TraceableProcessObject.
   * @return A possibly-null ProcessTrace.
   */
  public ProcessTrace getProcessTrace();

  /**
   * Set the ProcessTrace that will be used to report trace messages
   * for this TraceableProcessObject.
   * @param processTrace a possibly-null ProcessTrace for this TraceableProcessObject. 
   */
  public void setProcessTrace(ProcessTrace processTrace);

}
