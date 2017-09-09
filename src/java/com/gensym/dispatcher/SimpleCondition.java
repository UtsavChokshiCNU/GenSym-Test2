package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.lang.reflect.*;

public class SimpleCondition extends Condition
{

  public final static int EQUAL = 0;
  public final static int GREATER_THAN_OR_EQUAL = 1;
  public final static int LESS_THAN_OR_EQUAL = 2;
  public final static int GREATER_THAN = 3;
  public final static int LESS_THAN = 4;
  public final static int NOT_EQUAL = 5;
  final static int METHOD = 6;

  private int testType;
  private Method method; 
  private Reference ref1, ref2;
  private static boolean debug = false;

  private String pprintTestType() {
    switch (testType) {
    case EQUAL: return "==";
    case GREATER_THAN_OR_EQUAL: return ">=";
    case LESS_THAN_OR_EQUAL: return "<=";
    case GREATER_THAN: return ">";
    case LESS_THAN: return "<";
    case NOT_EQUAL: return "!=";
    default: return "" + testType;
    }
  }

  private boolean eval(boolean arg1, boolean arg2) {
    switch (testType) {
    case EQUAL: return arg1 == arg2; 
    case NOT_EQUAL: return arg1 != arg2;
    default: return false;
    }
  }

  private boolean eval(int arg1, int arg2)
  {
    switch (testType) {
    case EQUAL: return arg1 == arg2; 
    case GREATER_THAN_OR_EQUAL: return arg1 >= arg2; 
    case LESS_THAN_OR_EQUAL: return arg1 <= arg2; 
    case GREATER_THAN: return arg1 > arg2; 
    case LESS_THAN: return arg1 < arg2; 
    case NOT_EQUAL: return arg1 != arg2;
    default: return false;
    }
  }

  private boolean eval(short arg1, short arg2)
  {
    switch (testType) {
    case EQUAL: return arg1 == arg2; 
    case GREATER_THAN_OR_EQUAL: return arg1 >= arg2; 
    case LESS_THAN_OR_EQUAL: return arg1 <= arg2; 
    case GREATER_THAN: return arg1 > arg2; 
    case LESS_THAN: return arg1 < arg2; 
    case NOT_EQUAL: return arg1 != arg2;
    default: return false;
    }
  }

  private boolean eval(long arg1, long arg2)
  {
    switch (testType) {
    case EQUAL: return arg1 == arg2; 
    case GREATER_THAN_OR_EQUAL: return arg1 >= arg2; 
    case LESS_THAN_OR_EQUAL: return arg1 <= arg2; 
    case GREATER_THAN: return arg1 > arg2; 
    case LESS_THAN: return arg1 < arg2; 
    case NOT_EQUAL: return arg1 != arg2;
    default: return false;
    }
  }

  private boolean eval(float arg1, float arg2)
  {
    switch (testType) {
    case EQUAL: return arg1 == arg2;
    case GREATER_THAN_OR_EQUAL: return arg1 >= arg2; 
    case LESS_THAN_OR_EQUAL: return arg1 <= arg2; 
    case GREATER_THAN: return arg1 > arg2; 
    case LESS_THAN: return arg1 < arg2;
    case NOT_EQUAL: return arg1 != arg2;
    default: return false;
    }
  }

  private boolean eval(double arg1, double arg2)
  {
    switch (testType) {
    case EQUAL: return arg1 == arg2; 
    case GREATER_THAN_OR_EQUAL: return arg1 >= arg2; 
    case LESS_THAN_OR_EQUAL: return arg1 <= arg2; 
    case GREATER_THAN: return arg1 > arg2; 
    case LESS_THAN: return arg1 < arg2; 
    case NOT_EQUAL: return arg1 != arg2;
    default: return false;
    }
  }

  private boolean eval(Byte arg1, Byte arg2)
  {
    return eval(arg1.byteValue(), arg2.byteValue());
  }
  
  private boolean eval(Character arg1, Character arg2)
  {
    return eval(arg1.charValue(), arg2.charValue());
  }

  private boolean eval(Integer arg1, Integer arg2)
  {
    return eval(arg1.intValue(), arg2.intValue());
  }
    
  private boolean eval(Boolean arg1, Boolean arg2)
  {
    return eval (arg1.booleanValue(), arg2.booleanValue());
  }

  private boolean eval(Short arg1, Short arg2)
  {
    return eval(arg1.shortValue(), arg2.shortValue());
  }

  private boolean eval(Long arg1, Long arg2)
  {
    return eval(arg1.longValue(),arg2.longValue());
  }

  private boolean eval(Float arg1, Float arg2)
  {
    return eval(arg1.floatValue(), arg2.floatValue());
  }

  private boolean eval(Double arg1, Double arg2)
  {
    return eval(arg1.doubleValue(), arg2.doubleValue());
  }

  private boolean methodEval(Object arg1, Object arg2)
       throws IllegalAccessException,
	 InvocationTargetException
  {
    if (method!= null)
      return ((Boolean)method.invoke(null, new Object[] {arg1, arg2})).booleanValue();
    return false;
  }
  
  private boolean eval(Object arg1, Object arg2,
		       Class type1, Class type2)
       throws IllegalAccessException
  {
    if (testType == METHOD) {
      try {
	return methodEval(arg1, arg2);
      } catch (InvocationTargetException ite) {
	Trace.exception (ite);
	Trace.exception (ite.getTargetException ());
	throw new RuntimeException("Invocation Target Exception in Simple Condition: " +
				   "Method: " + method +
				   ite.getTargetException());
      }
    } else {
      if (type1.isPrimitive()) {
	//boolean, byte, char, short, int, long, float, double, void
	if (type1 == type2) {// == arg1.getClass() == arg2.getClass()) {
	  if (type1 == Boolean.TYPE)
	    return eval((Boolean)arg1,(Boolean)arg2);
	  else if (type1 == Byte.TYPE)
	    return eval((Byte)arg1,(Byte) arg2);
	  else if (type1 == Character.TYPE)
	    return eval((Character)arg1,(Character)arg2);
	  else if (type1 == Short.TYPE)
	    return eval((Short)arg1,(Short)arg2);
	  else if (type1 == Integer.TYPE)
	    return eval((Integer)arg1,(Integer)arg2);
	  else if (type1 == Long.TYPE)
	    return eval((Long)arg1,(Long)arg2);
	  else if (type1 == Float.TYPE)
	    return eval((Float)arg1,(Float)arg2);
	  else if (type1 == Double.TYPE)
	    return eval((Double)arg1,(Double)arg2);
	} else {
	  if (debug)
	    System.out.println("NON EQUAL CLASS TYPES IN EVAL");
	  return false;
	}
      } else {
	switch (testType) {
	case EQUAL: return arg1 == arg2; 
	case NOT_EQUAL: return arg1 != arg2;
	default: return false;
	}
      }
    }
    return false;
  }

  public SimpleCondition(int testType,
			 Reference arg1,
			 Reference arg2)
  {
    this.testType = testType;
    this.ref1 = arg1;
    this.ref2 = arg2;
  }

  public SimpleCondition(Method staticMethod,
			 Reference arg1,
			 Reference arg2)
       throws NonStaticMethodException
  {
    if (!Modifier.isStatic(staticMethod.getModifiers()))
      throw new NonStaticMethodException(staticMethod);
    this.method = staticMethod;
    this.testType = METHOD;
    this.ref1 = arg1;
    this.ref2 = arg2;
  }

  @Override
  public boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException
  {
    if (debug)
      System.out.println("TRYING TO EVAL CONDITION " + this +" using table " + table);
    Object ref1Val = ref1.getValue(table);
    Object ref2Val = ref2.getValue(table);
    if (debug) {
      System.out.println("ref1 = " + ref1Val + " ref2 = " + ref2Val);
      System.out.println("TYPE1 = " + ref1.getType() + " TYPE2 = " + ref2.getType());
    }
    return eval(ref1Val, ref2Val,
		ref1.getType(), ref2.getType());
  }

  @Override
  public String toString()
  {
    if (method != null)
      return method.getDeclaringClass().getName() + "." +
	method.getName() +
	"\n(" + ref1 + "," + ref2 + ")";
    else
      return ref1 + pprintTestType() + ref2;
  }

  public Reference getRef2()//temp
  {
    return ref2;
  }
}
