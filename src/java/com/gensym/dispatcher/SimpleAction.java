package com.gensym.dispatcher;

import java.lang.reflect.*;

/**
 * SimpleAction
 */

public class SimpleAction extends Action

{
  private Method method;
  private Object obj;
  private boolean isStaticMethod;
  private Reference[] args;

  SimpleAction()//for Noop
  {
  }

  public SimpleAction(String className,
		      String methodName) 
       throws ClassNotFoundException,
			NonStaticMethodException,
			NoSuchMethodException
  {
    this(Class.forName(className), methodName, null, null);
  }

  public SimpleAction(String className,
		      String methodName,
		      Reference argReference)
       throws ClassNotFoundException,
			NonStaticMethodException,
			NoSuchMethodException
  {
    this(Class.forName(className), methodName, null, new Reference[] {argReference});
  }


  public SimpleAction(String className,
		      String methodName,
		      Reference[] argReferences)
       throws ClassNotFoundException,
			NonStaticMethodException,
			NoSuchMethodException
  {
    this(Class.forName(className), methodName, null, argReferences);
  }

  public SimpleAction(String className,
		      String methodName,
		      Object obj,
		      Reference argReference)
       throws ClassNotFoundException,
			NonStaticMethodException,
			NoSuchMethodException
  {
    this(className, methodName, obj, new Reference[] {argReference});
  }

  public SimpleAction(String className,
		      String methodName,
		      Object obj,
		      Reference[] argReferences)
       throws ClassNotFoundException,
			NonStaticMethodException,
			NoSuchMethodException
  {
    this(Class.forName(className), methodName, obj, argReferences);
  }

  private static Class[] getTypes(Reference[] refs)
  {
    Class[] types = new Class[refs.length];
    for (int i=0;i<refs.length;i++) {
      types[i]=refs[i].getType();
      /*System.out.println("LOOKING FOR METHOD WITH TYPE[" + i + "] = " +
			 types[i]);*/
    }
    
    return types;
  }

  private static String pprintObjectArray(Object[] objs)
  {
    String str = "";
    for (int i=0;i<objs.length;i++) {
      str = str + objs[i].toString();
      if (i < (objs.length-1))
	str += ",";
    }
    return str;
  }
  
  private static String pprintTypes(Class[] types)
  {
    String str = "";
    for (int i=0;i<types.length;i++) {
      str = str + types[i].getName();
      if (i < (types.length-1))
	str += ",";
    }
    return str;
  }

  private static Method getMethod(Class classObject,
				  String methodName,
				  Class[] types)
       throws NoSuchMethodException
  {
    /*System.out.println("LOOKING FOR METHOD " +
      methodName + "(" + pprintTypes(types) + ")" +
      " in " + classObject);*/
    try {
      Method method = classObject.getMethod(methodName, types);
      //System.out.println("FOUND METHOD " + method);
      return method;
    } catch (NoSuchMethodException nsme) {
      /*System.out.println("NO METHOD " + 
			 methodName + "(" + pprintTypes(types) + ")" +
			 " in " + classObject);*/
      throw new NoSuchMethodException("\n"+methodName + "(" + pprintTypes(types) + ")" +
				      " in " + classObject);
    }

  }
  
  public SimpleAction(Class classObject,
		      String methodName,
		      Object obj,
		      Reference[] argReferences)
       throws NonStaticMethodException,
			NoSuchMethodException
			
  {
    this(getMethod(classObject, methodName, getTypes(argReferences)),
	 obj,
	 argReferences);
  }
  
  public SimpleAction(Method method,
		      Object obj,
		      Reference[] argReferences)
       throws NonStaticMethodException,
			IllegalArgumentException
	
  {
    this.method = method;
    this.obj = obj;
    this.args = argReferences;
    
    isStaticMethod = Modifier.isStatic(method.getModifiers());
    if (obj == null && !isStaticMethod)
      throw new NonStaticMethodException(method);
    else if (method.getParameterTypes().length != args.length)
      throw new IllegalArgumentException();

  }

  private Object[] getArgumentValues(DispatchTable table)
       throws IllegalAccessException
  {
    Object[] argValues = new Object[args.length];
    for (int i=0;i<args.length;i++) {
      argValues[i] = args[i].getValue(table);
    }
    return argValues;
  }

  @Override
  public Object invoke(DispatchTable table) 
       throws IllegalAccessException,
	 IllegalArgumentException,
	 InvocationTargetException
  {
    //System.out.println("HERE" + method);
    Object[] argumentValues = getArgumentValues(table);
    /*System.out.println("TRYING TO INVOKE " + method +
		       " on " + obj +
		       " with " + argumentValues);*/
    Object thing = obj;
    if (thing instanceof Reference)
      thing = ((Reference)thing).getValue(table);
    Object retval = null;
    try {
      retval = method.invoke(thing, argumentValues);
    } catch(InvocationTargetException ite) {
      com.gensym.message.Trace.exception (ite.getTargetException ());
      throw new InvocationTargetException(ite.getTargetException(),"\n"+thing + "." + method.getName() +
					  "(" + pprintObjectArray(argumentValues) + ")");
    } catch(IllegalArgumentException iae) {
      throw new IllegalArgumentException(thing + "." + method.getName() +
					 "(" + pprintObjectArray(argumentValues) + ")");
    }
    
    return retval;
  }

  private String pprintArgs()
  {
    if (args == null) return "";
    String str = "";
    for (int i=0;i<args.length;i++) {
      String type = args[i].getType().getName();
      str = str + "("+type+")" + " " + args[i];
      if (i < args.length-1)
	str+=",\n";
    }
    return str;
  }

  
  @Override
  public String toString()
  {
    String str = method.getName() + "(" + pprintArgs() + ")";
    if (obj != null) {
      Class declaringClass = method.getDeclaringClass();
      if (declaringClass.isInstance(obj))
	return obj.toString()+"." + str + ";";
      else
	return "(("+declaringClass.getName()+")"+obj.toString()+")." + str + ";";
    } else
      return method.getDeclaringClass().getName()+"."+str+";";
  }
  
}

