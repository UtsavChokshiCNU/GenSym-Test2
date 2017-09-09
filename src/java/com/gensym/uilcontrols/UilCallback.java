package com.gensym.uilcontrols;
 
import java.io.Serializable;
import java.io.IOException;
import com.gensym.util.Symbol;
import com.gensym.message.*;
import java.lang.reflect.*;

public class UilCallback implements Serializable{

  static final long serialVersionUID = 7671596444378473134L;

  private Symbol name;
  private String[] argumentTypeNames;
  private transient Class[] argumentTypes;
  private String[] arguments;
  private int syntax;
  private String source;
  private byte[] compiledCode;
  private String staticMethodClassName;
  private transient Class staticMethodClass;
  private String staticMethodName;
  private transient Method method;
  private int callbackType;

  static final int DEFAULT_CALLBACK = 1;
  static final int STATIC_METHOD_CALLBACK = 2;
  static final int SELF_CONTAINED_CALLBACK = 3;

  private Object objectInitiatingCallback; //used for actions

 
  /** Constructor for default callbacks  */
  public UilCallback(Symbol name, Class[] argumentTypes, String[] arguments)
  {
    this.name = name;
    this.argumentTypes = argumentTypes;
    this.arguments = arguments;
    callbackType = DEFAULT_CALLBACK;
    setArgumentTypeNames();
  }

  /** Constructor for static method callbacks  */
  public UilCallback(Symbol name, 
		     Class[] argumentTypes, String[] arguments,
		     Class staticMethodClass, String staticMethodName)
  {
    this.name = name;
    this.argumentTypes = argumentTypes;
    this.arguments = arguments;
    callbackType = STATIC_METHOD_CALLBACK;
    this.staticMethodClass = staticMethodClass;
    this.staticMethodName = staticMethodName;
    setArgumentTypeNames();
    staticMethodClassName = staticMethodClass.getName();
  }

  private void setArgumentTypeNames()
  {
    argumentTypeNames = new String[argumentTypes.length];
    for (int i = 0; i<argumentTypes.length; i++)
      argumentTypeNames[i] = argumentTypes[i].getName();
  }

  private void readObject(java.io.ObjectInputStream in)
       throws IOException, ClassNotFoundException
  {
    in.defaultReadObject();
    int i,len = argumentTypeNames.length;
    argumentTypes = new Class[len];
    for (i = 0; i<len ; i++)
      argumentTypes[i] = Class.forName(argumentTypeNames[i]);
    if (staticMethodClassName != null)
      staticMethodClass = Class.forName(staticMethodClassName);
  }

  public boolean isDefaultCallback()
  {
    return (callbackType == DEFAULT_CALLBACK);
  }

  public Symbol getName()
  {
    return name;
  }

  public Object getObjectInitiatingCallback(){
    return objectInitiatingCallback;
  }

  public void setObjectInitiatingCallback(Object object){
    objectInitiatingCallback = object;
  }

  public int getCallbackType()
  {
    return callbackType;
  }

  public void setCallbackType(int callbackType)
  {
    this.callbackType = callbackType;
  }

  public Class getStaticMethodClass()
  {
    return staticMethodClass;
  }

  public void setStaticMethodClass(Class c)
  {
    staticMethodClass = c;
    staticMethodClassName = c.getName();
    method = null;
  }

  public String getStaticMethodName()
  {
    return staticMethodName;
  }

  public void setStaticMethodName(String name)
  {
    staticMethodName = name;
    method = null;
  }

  private static final Resource i18nTrace = Trace.getBundle("com.gensym.uilcontrols.TraceMessages");
  private static final MessageKey traceKey = Trace.registerMessageKey("com.gensym.uilcontrols", UilCallback.class);

  public Object doCallback(Object[] args)
       throws ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException
  {
    if (callbackType == STATIC_METHOD_CALLBACK)
      {
	trace(args);
	method = staticMethodClass.getMethod(staticMethodName,argumentTypes);
	return method.invoke(null,args);
      }
    else
      return null;
  }

  private void trace(Object[] args){
    Object traceArgs[] = new Object[args.length + 2];
    traceArgs[0] = staticMethodName;
    traceArgs[1] = staticMethodClassName;
    for (int i=0; i< args.length; i++)
      traceArgs[i+2] = args[i];
    if (args.length == 1)
      Trace.send(5, traceKey, i18nTrace, "doCallback0", traceArgs);
    else if (args.length == 2)
      Trace.send(5, traceKey, i18nTrace, "doCallback1", traceArgs);
    else if (args.length == 3)
      Trace.send(5, traceKey, i18nTrace, "doCallback2", traceArgs);
    else if (args.length == 4)
      Trace.send(5, traceKey, i18nTrace, "doCallback3", traceArgs);
    else if (args.length == 5)
      Trace.send(5, traceKey, i18nTrace, "doCallback4", traceArgs);
    else if (args.length == 6)
      Trace.send(5, traceKey, i18nTrace, "doCallback5", traceArgs);   
    else if (args.length == 7)
      Trace.send(5, traceKey, i18nTrace, "doCallback6", traceArgs);
  }

  @Override
  public String toString(){
    return (super.toString()+"[name="+name+" argumentTypes="+argumentTypes+" callbackType="+callbackType+
	    " staticMethodClassName="+staticMethodClassName+" staticMethodName="+staticMethodName+" syntax="+syntax+"]");
  }

  public static String convertCallbackNameToMethodName(Symbol callbackName){
    return com.gensym.util.G2ClassTranslator.createJavaNameFromG2Name(callbackName);
  }

}
