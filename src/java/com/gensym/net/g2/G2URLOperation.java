
package com.gensym.net.g2;

import java.net.*;
import java.lang.reflect.*;
import com.gensym.util.Symbol;

public class G2URLOperation {

  private Method methodCall;
  private Object[] arguments;
  private Object dispatchObject;
  private boolean isGetter;
  private static final boolean urlOpDebug = false;

  G2URLOperation (Object focus, Method m, Object[] args, boolean getter) {
    dispatchObject = focus;
    methodCall = m;
    arguments = args;
    isGetter = getter;
  }

  public void setArgAtIndex (int index, Object newArg) {
    arguments[index] = newArg;
  }

  public void setArgByName (String argName, Object newArg) {
    if (urlOpDebug)
      System.out.println ("In setArgByName, isGetter = " + isGetter);
    Method m = (isGetter? G2Connection.postGetMethod : G2Connection.postSetMethod);
    if (urlOpDebug)
      System.out.println ("Hence method = " + m);
    int index = G2Connection.getIndexOfArgFromName (Symbol.intern (argName), 
						    G2Connection.getArgumentDescriptionsForMethod (m));
    setArgAtIndex (index, newArg);
  }

  public Object execute () throws IllegalAccessException, InvocationTargetException {
    if (urlOpDebug)
      System.out.println ("Executing URL fetch: dispatchObject = " + dispatchObject);
    if (urlOpDebug)
      System.out.println ("                     dispatchMethod = " + methodCall);
    return methodCall.invoke (dispatchObject, arguments);
  }

}
