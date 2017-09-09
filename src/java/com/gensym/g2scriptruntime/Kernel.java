package com.gensym.g2scriptruntime;

import com.gensym.util.Dispatcher;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import java.lang.reflect.*;
import java.util.Enumeration;

public class Kernel
{
  static Dispatcher dispatcher = new Dispatcher();
  static volatile NamingService theNamingService = null;
  static volatile ClassManager theClassManager = null;
  static long startTime = System.currentTimeMillis();
  static volatile IconColorChangeHandler iconColorChangeHandler = null;
  static volatile ConnectionTraversalHandler connectionTraversalHandler = null;

  public static void startStatic(String className,
				 String methodName, 
				 Object[] args,
				 Number delayInSeconds,
				 int priority) // ignored
       throws ClassNotFoundException, G2ScriptException
  {
    Class c = Class.forName(className);
    Class[] argClasses = makeClassArray(args);
    Method method 
      = dispatcher.findInstanceMethod(methodName,c,argClasses);
    if (method == null)
      throw new G2ScriptException("No such method/procedure: "+methodName);
    else
      {
	G2Thread thread 
	  = new G2Thread(null,method,args,
			 (long)(delayInSeconds.doubleValue() * 1000.0));
	thread.start();
      }
  }
  
  public static void startVirtual(Object object,
				  String methodName,
				  Object[] args,
				  Number delayInSeconds,
				  int priority) // ignored
       throws G2ScriptException
  {
    Class[] argClasses = makeClassArray(args);
    Method method 
      = dispatcher.findInstanceMethod(methodName,object.getClass(),argClasses);
    if (method == null)
      throw new G2ScriptException("No such method/procedure: "+methodName);
    else
      {
	G2Thread thread
	  = new G2Thread(object,method,args,
			 (long)(delayInSeconds.doubleValue() * 1000.0));
	thread.start();
      }
  }

  public static void waitForInterval(Number delayInSeconds)
  {
    try {
      Thread.sleep((long)(delayInSeconds.doubleValue() * 1000.0));
    } catch (InterruptedException e)
      {
	// just go on for now
      }
  }

  private static Class[] makeClassArray(Object[] array)
  {
    Class[] result = new Class[array.length];
    for (int i = 0; i<array.length ; i++)
      result[i] = array[i].getClass();
    return result;
  }

  public static Sequence makeSequence(Object[] contents)
  {
    int i, len = contents.length;
    Sequence s = new Sequence(len);
    for (i=0; i<len; i++)
      s.addElement(contents[i]);
    return s;
  }

  public static Structure makeStructure(Symbol[] names, Object[] values)
  {
    return new Structure(names,values,values.length);
  }

  public static void setBaseRealTime(long newStartTime)
  {
    startTime = newStartTime;
  }

  public static double getCurrentSubsecondRealTime()
  {
    return ((double)(System.currentTimeMillis() - startTime)) / 1000.0;
  }

  public static int getCurrentRealTime()
  {
    return (int) ((System.currentTimeMillis() - startTime) / 1000);
  }

  /*
  public static void signal(Object errorObject)
       throws Exception
  {
    // the following should really test to see if errorObject is an 
    // export of G2
    if (errorObject instanceof Exception) 
                          
      throw errorObject;
    else
      throw new G2ScriptException("non error object 
  }
  */

  public static void signal(Object errorName, Object errorText)
       throws Exception
  {
    if (!(errorName instanceof Symbol))
      throw new G2ScriptException("Error Name is not a symbol "+errorName);
    else if (!(errorText instanceof String))
      throw new G2ScriptException("Error Text is not text "+errorText);
    else
      throw new G2ScriptException((Symbol)errorName, (String)errorText);
  }

  public static Symbol getExceptionSymbol(Exception e)
  {
    String name = e.getClass().getName();
    int lastIndex = name.lastIndexOf(".");
    if (lastIndex == -1) 
      lastIndex = 0;
    else
      lastIndex++;
    return createG2NameFromJavaName(name.substring(lastIndex,name.length()));
  }

  public static Symbol createG2NameFromJavaName(String java_name)
  {
    char cchar;
    char cchar_p1;
    String field_name;
    StringBuffer g2_name_buffer;
    int length = java_name.length();
    int i;

    g2_name_buffer = new StringBuffer(length);
    for (i=0; i<java_name.length(); i++)
      {
	// Look for each lower/captical compination and insert a "-"
	cchar = java_name.charAt(i);
	g2_name_buffer.append(cchar);
	if ((i+1 < length))
	    {
	      cchar_p1 = java_name.charAt(i+1);
	      
	      boolean condition1 = (Character.isLowerCase(cchar) || Character.isDigit(cchar)) && Character.isUpperCase(cchar_p1);
	      
	      // Also look for cap words before start captialized word
	      // (e.g. ThisFIELDWillWork -> This-FIELD-Will-Work)
	      boolean condition2 = (i+2 < length) && Character.isUpperCase(cchar) && Character.isUpperCase(cchar_p1)
			       					&& Character.isLowerCase(java_name.charAt(i+2));
	      if (condition1 || condition2)
	    	  g2_name_buffer.append("-");
	    }
      }
    return Symbol.intern(g2_name_buffer.toString().toUpperCase());
  }

  public static String getExceptionText(Exception e)
  {
    return e.getMessage();
  }

  public static Object getInstanceField(Object o, String fieldName)
       throws G2ScriptException, IllegalAccessException
  {
    if (o instanceof Structure)
      {
	Object result 
	  = ((Structure)o).getAttributeValue(Symbol.intern(fieldName),null);
	if (result == null)
	  throw new NullPointerException("No such attribute "+fieldName+" in "+
					 o);
	return result;
      }
    else
      {
	Class c = o.getClass();
	try {
	  Field field = c.getField(fieldName);
	  if (Modifier.isStatic(field.getModifiers()))
	    throw new G2ScriptException("No such instance attribute"+fieldName+
					" in "+o);
	  return field.get(o);
	} catch (NoSuchFieldException e)
	  {
	    throw new G2ScriptException("No such attribute "+fieldName+" in "+
					o);
	  }
      }
  }

  public static Object getStaticField(String className, String fieldName)
       throws G2ScriptException, IllegalAccessException
  {
    Class c = null;
    try {
      c = Class.forName(className);
      Field field = c.getField(fieldName);
      if (!Modifier.isStatic(field.getModifiers()))
	throw new G2ScriptException("No such static attribute"+fieldName+
				    " in "+c);
      return field.get(null);
    } 
    catch (ClassNotFoundException cnfe)
      {
	throw new G2ScriptException("No class found for "+className);
      }
    catch (NoSuchFieldException e)
      {
	throw new G2ScriptException("No such static attribute "+fieldName+" in "+
				    c);
      }
  }

  public static void setInstanceField(Object o, String fieldName, Object newValue)
       throws G2ScriptException, IllegalAccessException
  {
    if (o instanceof Structure)
      ((Structure)o).setAttributeValue(Symbol.intern(fieldName),newValue);
    else
      {
	Class c = o.getClass();
	try {
	  Field field = c.getField(fieldName);
	  if (Modifier.isStatic(field.getModifiers()))
	    throw new G2ScriptException("No such instance attribute"+fieldName+
					" in "+o);
	  field.set(o,newValue);
	} catch (NoSuchFieldException e)
	  {
	    throw new G2ScriptException("No such attribute "+fieldName+" in "+
					o);
	  }
      }
  }

  public static void setStaticField(String className, String fieldName,
				      Object newValue)
       throws G2ScriptException, IllegalAccessException
  {
    Class c = null;
    try {
      c = Class.forName(className);
      Field field = c.getField(fieldName);
      if (!Modifier.isStatic(field.getModifiers()))
	throw new G2ScriptException("No such static attribute"+fieldName+
				    " in "+c);
      field.set(null,newValue);
    } 
    catch (ClassNotFoundException cnfe)
      {
	throw new G2ScriptException("No class found for "+className);
      }
    catch (NoSuchFieldException e)
      {
	throw new G2ScriptException("No such static attribute "+fieldName+" in "+
				    c);
      }
  }

  public static Object getArrayOrSequenceElement(Object x, Object number)
       throws G2ScriptException
  {
    int index = Math.extractIntFromNumber(number);
    return getArrayOrSequenceElement(x,index);
  }

  public static Object getArrayOrSequenceElement(Object x, int index)
       throws G2ScriptException
  {
    if (x instanceof G2ArrayAccess)
      {
	Object array = ((G2ArrayAccess)x).getArray();
	Class arrayClass = array.getClass();
	Class elementClass = arrayClass.getComponentType();
	if (elementClass == java.lang.Double.TYPE)
	  return new Double(((double[])array)[index]);
	else if (elementClass == java.lang.Integer.TYPE)
	  return ((int[])array)[index];
	else
	  return ((Object[])array)[index];
      }
    else if (x instanceof Sequence)
      {
	return ((Sequence)x).elementAt(index);
      }
    else
      throw new G2ScriptException(x+" is not a sequence of an array");
  }


  public static void setArrayOrSequenceElement(Object x, Object number,
					       Object newValue)
       throws G2ScriptException
  {
    int index = Math.extractIntFromNumber(number);
    setArrayOrSequenceElement(x,index,newValue);
  }

  public static void setArrayOrSequenceElement(Object x, int index,
					       Object newValue)
       throws G2ScriptException
  {
    if (x instanceof G2ArrayAccess)
      {
	Object array = ((G2ArrayAccess)x).getArray();
	Class arrayClass = array.getClass();
	Class elementClass = arrayClass.getComponentType();
	if (elementClass == java.lang.Double.TYPE)
	  ((double[])array)[index] = Math.extractDoubleFromNumber(newValue);
	else if (elementClass == java.lang.Integer.TYPE)
	  ((int[])array)[index] = Math.extractIntFromNumber(newValue);
	else
	  ((Object[])array)[index] = newValue;
      }
    else if (x instanceof Sequence)
      {
	((Sequence)x).setElementAt(newValue,index);
      }
    else
      throw new G2ScriptException(x+" is not a sequence of an array");
  }

  public static Enumeration getAggregateEnumeration(Object aggregate)
       throws G2ScriptException
  {
    if (aggregate instanceof Sequence)
      {
	return ((Sequence)aggregate).elements();
      }
    else
      throw new G2ScriptException("cannot enumerate elements of "+aggregate);
  }

  public static void setDomain(NamingService namingService)
  {
    theNamingService = namingService;
  }

  public static Object lookupObject(String name,
				    Object callingObject)
       throws G2ScriptException
  {
    if (theNamingService == null)
      throw new G2ScriptException("No NamingService registered as domain");
    return theNamingService.lookup(name,Object.class);
  }

  public static Enumeration getClassEnumeration(String className)
       throws G2ScriptException
  {
    if (theNamingService == null)
      throw new G2ScriptException("No NamingService registered as domain");
    Class c = null;
    try {
      c = Class.forName(className);
    }
    catch (Exception e)
      {
	c = null;
      }
    if (c == null)
      throw new G2ScriptException("Unknown class "+className);
    return theNamingService.lookup(c);
  }

  public static void setExternalClassManager(ClassManager classManager)
  {
    theClassManager = classManager;
  }

  public static Class getVersionedImplementationClass(String interfaceName,
						       String defaultImplementationName,
						       Object callingObject)
       throws ClassNotFoundException
  {
    if (theClassManager != null)
      return theClassManager.getVersionedImplementationClass(interfaceName, 
							  defaultImplementationName,
							  callingObject);
    else
      return null;
  }

  public static Object newVersionedImplementionClass(String interfaceName,
						     String defaultImplementationName,
						     Object callingObject)
       throws G2ScriptException
  {
    Class classToCreate = null;
    try {
      classToCreate
	= getVersionedImplementationClass(interfaceName,defaultImplementationName,
					  callingObject);
    } catch (ClassNotFoundException e) {
      throw new G2ScriptException("Could not find Implementation Class, caused " + e.toString());
    }
    if (classToCreate == null)
      throw new G2ScriptException("No implementation class given for "+interfaceName);
    else
      {
	try {
	  return classToCreate.newInstance();
	} catch (Exception e)
	  {
	    throw new G2ScriptException("Problems instantiating implementation class "+
					classToCreate.getName()+
					" for interface "+interfaceName);
	  }
      }
  }

  public static int sequenceOrListLength(Object sequenceOrList)
       throws G2ScriptException
  {
    if (sequenceOrList instanceof Sequence)
      return ((Sequence)sequenceOrList).size();
    else
      throw new G2ScriptException("Cannot get number of elements of "+sequenceOrList);
  }

  public static void setIconRegionColor(Object object, Symbol regionName,
					Symbol colorName)
  {
    if (iconColorChangeHandler != null)
      iconColorChangeHandler.changeIconRegionColor(object,
						   regionName,
						   colorName);
  }

  public static void setIconColorChangeHandler(IconColorChangeHandler
					       changeHandler)
  {
    iconColorChangeHandler = changeHandler;
  }
       
  public static Object getUniqueConnectedObject(Object object,
			 		      String className,
					      String portName)
  {
    if (connectionTraversalHandler != null)
      return connectionTraversalHandler.getUniqueConnectedObject(object,className,portName);
    else
      return null;
  }

  public static void setConnectionTraversalHandler(ConnectionTraversalHandler
						   traversalHandler)
  {
    connectionTraversalHandler = traversalHandler;
  }

  public static Object getUniqueObjectUponWorkspace(Object workspace,
						    String subObjectClassName)
  {
    if (connectionTraversalHandler != null)
      return connectionTraversalHandler.getUniqueObjectUponWorkspace(workspace,subObjectClassName);
    else
      return null;
  }

}
