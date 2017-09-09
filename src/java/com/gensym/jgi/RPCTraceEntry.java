/**
 * @undocumented
 */

/**
 * This class is for collecting RPCTrace data .
 *
 *@author FY
 */
package com.gensym.jgi;

import com.gensym.util.Symbol;

class RPCTraceEntry {
  private Symbol pName;
  private Object pArgs[];
  private long duration;
  private Exception ex;

  public RPCTraceEntry(Symbol name, Object[] args, long dtime, Exception e) {
    pName = name;
    pArgs = args;
    duration = dtime;
    ex = e;
  }

  Symbol getProcedureName() {
    return pName;
  }

  Object getProcedureArgs() {
    return pArgs;
  }

  long getDuration () {
    return duration;
  }

  Exception getStackTrace() {
    return ex;
  }

} 