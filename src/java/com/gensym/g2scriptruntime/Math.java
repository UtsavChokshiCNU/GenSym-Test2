package com.gensym.g2scriptruntime;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;

public class Math
{
  static Class itemClass;
  
  static
  {
    try { 
      itemClass = Class.forName("com.gensym.classes.Item");
    }
    catch (ClassNotFoundException cnfe)
      {
	itemClass = null;
      }
  }

  public static int extractIntFromNumber(Object x)
  {
    if (x instanceof Integer)
      return ((Integer)x).intValue();
    else
      throw new ArithmeticException("Quantity was not an integer");
  }

  public static double extractDoubleFromNumber(Object x)
  {
    if (!(x instanceof Number))
      throw new ArithmeticException("Quantity was not an coercible to float");
    else
      return ((Number)x).doubleValue();
  }

  public static boolean extractBooleanFromObject(Object x)
       throws G2ScriptException
  {
    if (!(x instanceof Boolean))
      throw new G2ScriptException("Non truth Value : "+x);
    else
      return ((Boolean)x).booleanValue();
  }

  public static Number add(Object x, Object y)
  {
    if (!(x instanceof Number))
      throw new ArithmeticException("Non-number received"+x);
    else if (!(y instanceof Number))
      throw new ArithmeticException("Non-number received"+y);
    else if (x instanceof Integer && y instanceof Integer)
      return ((Integer)x).intValue() + ((Integer)y).intValue();
    else 
      return ((Number)x).doubleValue() + ((Number)y).doubleValue();
  }

 
  // Subtraction

  public static Number subtract(Object x, Object y)
  {
    if (!(x instanceof Number))
      throw new ArithmeticException("Non-number received"+x);
    else if (!(y instanceof Number))
      throw new ArithmeticException("Non-number received"+y);
    else if (x instanceof Integer && y instanceof Integer)
      return ((Integer)x).intValue() - ((Integer)y).intValue();
    else 
      return ((Number)x).doubleValue() - ((Number)y).doubleValue();
  }

  // Multiplication

  public static Number multiply(Object x, Object y)
  {
    if (!(x instanceof Number))
      throw new ArithmeticException("Non-number received"+x);
    else if (!(y instanceof Number))
      throw new ArithmeticException("Non-number received"+y);
    else if (x instanceof Integer && y instanceof Integer)
      return ((Integer)x).intValue() * ((Integer)y).intValue();
    else 
      return ((Number)x).doubleValue() * ((Number)y).doubleValue();
  }
  
  public static boolean isEqual(Object x, Object y)
       throws G2ScriptException
  {
    if (itemClass != null && 
	 itemClass.isAssignableFrom(y.getClass())) // x is checked later
      throw new G2ScriptException("Bad value for = "+y);
    else if (x instanceof Number)
      {
	if (y instanceof Number)
	  return Double.compare(((Number)x).doubleValue(), ((Number)y).doubleValue()) == 0;
	else return false;
      }
    else if (x instanceof String)
      {
	if (y instanceof String)
	  {
	    int compare = ((String)x).compareTo((String)y);
	    if (compare == 0)
	      return true;
	    else 
	      return false;
	  }
	else
	  return false;
      }
    else if (x instanceof Symbol ||
	     x instanceof Boolean ||
	     x instanceof Sequence ||
	     x instanceof Structure)
      return x.equals(y);
    else 
      throw new RuntimeException("Bad value for = "+x);
  }

  public static boolean notEqual(Object x, Object y)
       throws G2ScriptException
  {
    if (itemClass != null && 
	itemClass.isAssignableFrom(y.getClass())) // x is checked later
      throw new G2ScriptException("Bad value for /= "+y);
    else if (x instanceof Number)
      {
	if (y instanceof Number)
	  return Double.compare(((Number)x).doubleValue(), ((Number)y).doubleValue()) != 0;
	else return false;
      }
    else if (x instanceof String)
      {
	if (y instanceof String)
	  {
	    int compare = ((String)x).compareTo((String)y);
	    if (compare != 0)
	      return true;
	    else 
	      return false;
	  }
	else
	  return false;
      }
    else if (x instanceof Symbol ||
	     x instanceof Boolean ||
	     x instanceof Sequence ||
	     x instanceof Structure)
      return !(x.equals(y));
    else 
      throw new RuntimeException("Bad value for /= "+x);
  }

  public static boolean less(Object x, Object y)
       throws G2ScriptException
  {
    if (x instanceof Number)
      {
	if (y instanceof Number)
	  return ((Number)x).doubleValue() < ((Number)y).doubleValue();
	else
	  throw new G2ScriptException("incompatible types for <, "+x+" and "+y);
      }
    else if (x instanceof String)
      {
	if (y instanceof String)
	  {
	    int compare = ((String)x).compareTo((String)y);
	    if (compare < 0)
	      return true;
	    else 
	      return false;
	  }
	else
	  throw new G2ScriptException("incompatible types for <, "+x+" and "+y);
      }
    else 
      throw new G2ScriptException("incompatible types for <,"+x+" and "+y);
  }

  public static boolean greater(Object x, Object y)
       throws G2ScriptException
  {
    if (x instanceof Number)
      {
	if (y instanceof Number)
	  return ((Number)x).doubleValue() > ((Number)y).doubleValue();
	else
	  throw new G2ScriptException("incompatible types for >, "+x+" and "+y);
      }
    else if (x instanceof String)
      {
	if (y instanceof String)
	  {
	    int compare = ((String)x).compareTo((String)y);
	    if (compare > 0)
	      return true;
	    else 
	      return false;
	  }
	else
	  throw new G2ScriptException("incompatible types for >, "+x+" and "+y);
      }
    else 
      throw new G2ScriptException("incompatible types for >,"+x+" and "+y);
  }

  public static boolean lessOrEqual(Object x, Object y)
       throws G2ScriptException
  {
    if (x instanceof Number)
      {
	if (y instanceof Number)
	  return ((Number)x).doubleValue() <= ((Number)y).doubleValue();
	else
	  throw new G2ScriptException("incompatible types for <=, "+x+" and "+y);
      }
    else if (x instanceof String)
      {
	if (y instanceof String)
	  {
	    int compare = ((String)x).compareTo((String)y);
	    if (compare <= 0)
	      return true;
	    else 
	      return false;
	  }
	else
	  throw new G2ScriptException("incompatible types for <=, "+x+" and "+y);
      }
    else 
      throw new G2ScriptException("incompatible types for <=,"+x+" and "+y);
  }

  public static boolean greaterOrEqual(Object x, Object y)
       throws G2ScriptException
  {
    if (x instanceof Number)
      {
	if (y instanceof Number)
	  return ((Number)x).doubleValue() >= ((Number)y).doubleValue();
	else
	  throw new G2ScriptException("incompatible types for >=, "+x+" and "+y);
      }
    else if (x instanceof String)
      {
	if (y instanceof String)
	  {
	    int compare = ((String)x).compareTo((String)y);
	    if (compare >= 0)
	      return true;
	    else 
	      return false;
	  }
	else
	  throw new G2ScriptException("incompatible types for >=, "+x+" and "+y);
      }
    else 
      throw new G2ScriptException("incompatible types for >=,"+x+" and "+y);
  }

  public static boolean and(Object x, Object y)
  {
    if (!(x instanceof Boolean))
      throw new RuntimeException("Non-Boolean received "+x);
    else if (!(y instanceof Boolean))
      throw new RuntimeException("Non-Boolean received "+y);
    else
      return ((Boolean)x).booleanValue() && ((Boolean)y).booleanValue();
  }

  public static boolean or(Object x, Object y)
  {
    if (!(x instanceof Boolean))
      throw new RuntimeException("Non-Boolean received "+x);
    else if (!(y instanceof Boolean))
      throw new RuntimeException("Non-Boolean received "+y);
    else
      return ((Boolean)x).booleanValue() || ((Boolean)y).booleanValue();
  }
}
