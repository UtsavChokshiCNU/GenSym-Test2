
package com.gensym.util;

import java.util.Hashtable;
import java.lang.reflect.*;


/**
 * This class utlizes the SourceCompiler class to provide methods
 * to dynamically compile, load, resolve and create new class instances.
 * It also provides generic methods to call instance and static methods
 * on an object, using reflection.
 * 
 * @version 	1.1, 29-NOV-1997
 *
 * @author M.D.Gribble
 */
public class DownLoad
{

  // Private attributes
  
  private boolean fulldebug = false;    // Java level debugging switch
  private boolean methoddebug = false;  // Java level methodname debugging siwtch

  private Dispatcher methodDispatcher = new Dispatcher();

  protected Hashtable classHashtable = new Hashtable(); // Lookup table for class loaded dynmically
  // load some known classes from G2
  {
    classHashtable.put("java.lang.Integer.TYPE", java.lang.Integer.TYPE);
    classHashtable.put("java.lang.Float.TYPE", java.lang.Float.TYPE);
    classHashtable.put("java.lang.Double.TYPE", java.lang.Double.TYPE);
    classHashtable.put("java.lang.Short.TYPE", java.lang.Short.TYPE);
    classHashtable.put("java.lang.Long.TYPE", java.lang.Long.TYPE);
    classHashtable.put("java.lang.Character.TYPE", java.lang.Character.TYPE);
    classHashtable.put("java.lang.Boolean.TYPE", java.lang.Boolean.TYPE);
    classHashtable.put("java.lang.Byte.TYPE", java.lang.Byte.TYPE);
    classHashtable.put("int", java.lang.Integer.TYPE);
    classHashtable.put("float", java.lang.Float.TYPE);
    classHashtable.put("double", java.lang.Double.TYPE);
    classHashtable.put("short", java.lang.Short.TYPE);
    classHashtable.put("long", java.lang.Long.TYPE);
    classHashtable.put("char", java.lang.Character.TYPE);
    classHashtable.put("boolean", java.lang.Boolean.TYPE);
    classHashtable.put("byte", java.lang.Byte.TYPE);
  }

  private SourceCompiler SC = new SourceCompiler();


  // Public Method allowing dynamic loading, creation and instantiation of Java Classes
  // REM JGI NATIVE CODE ACCESSES THESE METHODS
  // *********************************************************************************

  /**
   * Constructs a new DownLoad Class 
   */


  /**
   * Compile Java Class Source Text and "Load" the subsequent 
   * classs into the runtime.
   *
   * <P>This method compiles the source given as a paramater. If successfull
   * the .class file is loaded into the current runtime and resolved
   * aganist current loaded classes. As a source file can contain many
   * class definitions, a classname parameter must be specified. This 
   * specifies which class to load and resolve. This class loaded 
   * allows classes to be loaded even when they have already been part of
   * the runtime. This allows dynamic updating of class definitions.
   * However, note that class instances created from old definitions
   * will still use their original class definition.
   *
   *@param classname The class to compile in the source code
   *@param source  The Java source text
   *
   *@return If errors where found during the source compilation the
   * compiler error message is returned. The text of exceptions raised
   * is returned and the class is not loaded. If the source compiles
   * and the class loads and resolves then a empty string "" is returned
   */
  public String loadJavaClass(String stagingDir, String classname, String source)
       throws JavaClassCompilerException
  {

    if (fulldebug){
    	System.out.println(source);
    }

    try {
      SC.GenerateClass (stagingDir, classname, source);
      if (fulldebug){
    	  System.out.println ("Class File Generated");
      }
      Class newClass = SC.loadClass (stagingDir, classname);
      if (fulldebug){
    	  System.out.println ("Class " + newClass.toString() + " loaded!");
      }
      if (this.classHashtable == null)
		this.classHashtable = new Hashtable();
      this.classHashtable.put(classname, newClass);
      //if (NewClass.getClassLoader() != null)
      //System.out.println(NewClass.getClassLoader().toString());
      return "";
     }
    catch (java.io.IOException E) {
      System.out.println(E.toString());
      throw new JavaClassCompilerException(E.toString());
    }
  }

 public String loadJavaClass(String classname, String source)
       throws JavaClassCompilerException
  {
    return loadJavaClass("", classname, source);
  }

  /**
   * "Load" the class byte codes into the runtime.
   *
   * <P> This method will load class byte codes into the current runtime 
   * and resolve aganist current loaded classes. This class loaded 
   * allows classes to be loaded even when they have already part of
   * the runtime. This allows dynamic updating of class definitions.
   * However, note that class instances created from old definitions
   * will still use their orginal class definition.
   *
   *@param classname The class to compile in the source code
   *@param bytecodes  The Java byte codes for the class
   *
   *
   */
  public void loadJavaClass(String classname, byte[] class_data)
  {

      StreamClassLoader CL = new StreamClassLoader(classname, class_data);
      Class NewClass = CL.loadClass (classname, true);
      if (fulldebug){
    	  System.out.println ("Class " + NewClass.toString() + " loaded!");
      }
      if (this.classHashtable == null)
		this.classHashtable = new Hashtable();
      this.classHashtable.put(classname, NewClass);
  }

  /**
   * load a class into the downloaders Class cache. If there exits a class
   * already in the cache of the same name, then it will be replaced with the new class.
   *
   * @param clazz The class to insert into the Class cache.
   */
  public void loadClass(Class clazz) {
    if (this.classHashtable == null)
      this.classHashtable = new Hashtable();
    //System.out.println("Registered " + clazz + clazz.getClassLoader());
    this.classHashtable.put(clazz.getName(), clazz);
  }

  /**
   * Create a Java Class Instance, and return a unique handle for the object.
   *
   * <P>Thie method will create a  new instance if a class previsouly downloaded
   * using <B>loadJavaClass</B> or from the system class loader. 
   * <P>The method will lookup the constructor that matches the classes in args.
   * If no arguments can be found then NoSuchMethodException will be raised.
   * <P>If an IllegalAccessException is thrown, the class may not be declared
   * public
   * 
   *
   *@param class_name  The class of the instance to create
   *@param args The constructors parameters
   *@param parameter_types Class Object for each argm or null
   * @param argClasses  The Classes for the signature of the constructor to call
   *                    or null for classes to be read from the args
   *@return A unque handle for the object created
   */
  public Object newInstance(final String class_name, final Object args[], final Class[] argClasses)
       throws ClassNotFoundException, 
	 InstantiationException, 
	 IllegalAccessException,
	 MethodInvocationException,
	 NoSuchMethodException
  {
    Class the_class;
    Object obj;

    Class[] classes = argClasses;
    the_class = lookupClass(class_name);


    if (fulldebug){
    	System.out.println("looked up class " + the_class.hashCode());
    }
    
    // We have found the class, not lookup up the constructor 
    // based on the parameters passed in

    if (classes == null)
      classes = getArgClasses(args);

    // Get the constructure for these parameter types
    Constructor cons = null;
    try {
      try {
        cons = the_class.getConstructor(classes);

      } catch (NoSuchMethodException E) {

	// Could not find a match, use our own dispather to find an applicable method
	// from subclass o instance Class or Overridden method
	cons =  methodDispatcher.findConstructor(the_class,
						   classes);
	if (cons == null) // still no luck
	  throw E;
      }

      // call the method
      obj = cons.newInstance(args);
      
    } catch (NoSuchMethodException E)
      {
	String argstr = ",args = " ;
	// Detail which method we looked up
	for (int i=0; i<args.length; i++) 
	  argstr = argstr + "|" + args[i] + "|" ;
	throw (new NoSuchMethodException(" for Constructor (" + the_class + ")\n" + argstr));
      }
    catch (InvocationTargetException E)
      {
	// Detail which method we looked up
	throw new MethodInvocationException (E.getTargetException().toString());
      }

    return obj;
  }

  /**
   * Create a Java Class Instance, and return a unique handle for the object.
   *
   * <P>Thie method will create a  new instance if a class previsouly downloaded
   * using <B>loadJavaClass</B>, or from the system class loader.
   * <P>The method will lookup the constructor that matches the classes in the Sequence args.
   * If no arguments can be found then NoSuchMethodException will be raised.
   * <P>If an IllegalAccessException is thrown, the class may not be declared
   * public
   * 
   *
   *@param class_name  The class of the instance to create
   *@param args The constructors parameters
   *@return the created object
   */
  public Object newInstance(String class_name, Sequence args, Class[] argClasses)
       throws ClassNotFoundException, 
	 InstantiationException, 
	 IllegalAccessException,
	 MethodInvocationException,
	 NoSuchMethodException
  {
    if (args == null){
    	return null;
    }

    return newInstance(class_name, args.getContents(), argClasses);
  }

  /**
   * Create a Java Array Class Instance of a required size, and return a unique handle for the object.
   *
   * <P>Thie method will create an array instance of a class previsouly downloaded
   * using <B>loadJavaClass</B> or from the system class loader.
   * <P>The method will lookup the constructor that matches the classes in args.
   * If no arguments can be found then NoSuchMethodException will be raised.
   * <P>If an IllegalAccessException is thrown, the class may not be declared
   * public
   * 
   *
   *@param class_name  The class of the instance to create
   *@param size The size of the array
   *@return A unque handle for the object created
   */
  public Object newArrayInstance(final String class_name, final int size)
       throws ClassNotFoundException, 
	 InstantiationException, 
	 IllegalAccessException
  {
    Class the_class;

    String className = getClassName(class_name);
 
    the_class = lookupClass(className);

    if (fulldebug){
    	System.out.println("looked up class " + the_class.hashCode());
    }
    
    // Get the constructure for these parameter types
    Object array = Array.newInstance(the_class, size);
      

    return array;
  }


  public Object newArrayInstance(final String class_name, final int[] dimensionsArray) 
    throws ClassNotFoundException, 
	 InstantiationException, 
	 IllegalAccessException
  {
    Class the_class;
    Object obj;

    String className = getClassName(class_name);
    the_class = lookupClass(className);

    if (fulldebug){
    	System.out.println("looked up class " + the_class.hashCode());
    }

    // Get the constructure for these parameter types
    Object array = Array.newInstance(the_class, dimensionsArray);
      
    return array;
  }

    private String getClassName(final String class_name) {
    String className = class_name;	
      if (className.startsWith("["))
    	  className = className.substring(1);
      if (className.startsWith("L"))
    	  className = className.substring(1);
      if (class_name.endsWith(";"))
    	  className = className.substring(0, className.length() - 1);
      return className;
    }


  /**
   * Call A Method on an instance created previously by newInstance or registered
   *
   * @param instance    The object to call the method on
   * @param method_name The method to call
   * @param args        The arguments to pass to the method
   * @param argClasses  The Classes for the signature of the method to call
   *                    or null for classes to be read from the args
   */
  public Object callMethod(final Object instance, final String method_name, final Object args[], final Class[] argClasses)
       throws
	 NoSuchMethodException, 
	 IllegalAccessException, 
	 MethodInvocationException
  {

    if (methoddebug){
	System.out.println("Method callMethod " + method_name );
      }

    Class[] classes = argClasses;  
    if (classes == null)
      classes = getArgClasses(args);

    Method method;

    // Get the method for these parameter types and name
    try {

      try {
	method = instance.getClass().getMethod(method_name, classes);

      } catch (NoSuchMethodException E) {

	// Could not find a match, use our own dispather to find an applicable method
	// from subclass o instance Class or Overridden method
	method =  methodDispatcher.findInstanceMethod(method_name,
							  instance.getClass(),
							  classes);
	if (method == null) // still no luck
	  throw E;
      }

      // call the method
      Object retval = method.invoke(instance, args);

      return retval;
      
    } catch (NoSuchMethodException E) {
      // Detail which method we looked up
      String argstr = ",args = " ;
      for (int i=0; i<args.length; i++)
	argstr = argstr + "|" + args[i] + "|" ;
      throw (new NoSuchMethodException(" for method (" + instance.getClass().getName() + "." + 
				       method_name + " )\n" + argstr));
    }
    catch (InvocationTargetException E) {
      // Detail which method we looked up
      //E.getTargetException().printStackTrace();
      throw new MethodInvocationException (method_name + " caused " + E.getTargetException().toString());
    }
		
  }
  

  /** 
   * Call A Method on an instance created previously by newInstance
   * The calling arguments are send via a Sequence. All Wrapped prmitive types
   * wrapped in the arguments are unwrapped before invoking the method
   *
   * @param instance    The object to call the method on
   * @param method_name The method to call
   * @param args        The Sequence of arguments to pass to the method
   */
  public Object callMethod(Object instance, String method_name, Sequence args, Class[] argClasses)
       throws
	 NoSuchMethodException,
	 IllegalAccessException,
	 MethodInvocationException
  {

    return callMethod(instance, method_name, args.getContents(), argClasses);
  }


   /**
   * Call A Static Method on a class
   *
   * @param class_name  The class name
   * @param method_name The method to call
   * @param args        The arguments to pass to the method
   * @param argClasses  The Classes for the signature of the method to call
   *                    or null for classes to be read from the args
   */
  public Object callStaticMethod(final String class_name, final String method_name, final Object args[], final Class[] argClasses)
       throws ClassNotFoundException,
	 NoSuchMethodException, 
	 IllegalAccessException,
	 MethodInvocationException
  {
    Class the_class;

    if (methoddebug) {
      System.out.println("Method callStaticMethod " + method_name );
    }

    Class[] classes = argClasses;
    the_class = lookupClass(class_name);
    if (classes == null)
      classes = getArgClasses(args);
    try {
      Method method = null;
      try {
	method = the_class.getMethod(method_name, classes );
	
      } catch (NoSuchMethodException E) {

	// Could not find a match, use our own dispather to find an applicable method
	// from subclass o instance Class or Overridden method
	method =  methodDispatcher.findStaticMethod(method_name,
						    the_class,
						    classes);
	if (method == null) // still no luck
	  throw E;
      }

 
      // call the method
      return method.invoke(null, args);
    } catch (NoSuchMethodException E) {
      String argstr = ",args = " ;
      // Detail which method we looked up
      for (int i=0; i<args.length; i++) {
	argstr = argstr + "|" + args[i] + "|" ;
      }
      throw (new NoSuchMethodException(" for staticmethod(" + the_class.getName() + 
				       "." + method_name + ")\n" + argstr));

    }
    catch (InvocationTargetException E) {
      // Detail which method we looked up
      throw new MethodInvocationException (E.getTargetException().toString());
    }
		
  }

 /** 
   * Call A Static Method on a class created previously downloaded
   * The calling arguments are send via a Sequence. All Wrapped prmitive types
   * wrapped in the arguments are unwrapped before invoking the method
   *
   * @param handle      The handle of the object to call the method on
   * @param method_name The method to call
   * @param args        The Sequence of arguments to pass to the method
   * @param argClasses  The Classes for the signature of the method to call
   *                    or null for classes to be read from the args
   */
  public Object callStaticMethod(String class_name, String method_name, Sequence args, Class[] argClasses)
       throws ClassNotFoundException, 
	 NoSuchMethodException, 
	 IllegalAccessException, 
	 MethodInvocationException
  {
    return callStaticMethod(class_name, method_name, args.getContents(), argClasses);
  }

  private Class[] getArgClasses(Object args) {
    boolean isSeq = args instanceof Sequence;
    int argLength = (int)(isSeq ? ((Sequence)args).size() : ((Object[])args).length);
    Class argClasses[] = new Class[argLength];
    Class param_class;
      
    // Construct a list of the parameters types to call
    for (int i = 0; i < argLength; i++) {
	
      param_class = (Class)(isSeq ? ((Sequence)args).elementAt(i) : ((Object[])args)[i]).getClass();
      // Assume that we want to use primitive types
      if (param_class == Integer.class)
	param_class = Integer.TYPE;
      else if (param_class == Long.class)
	param_class = Long.TYPE;
      else if (param_class == Float.class)
	param_class = Float.TYPE;
      else if (param_class == Boolean.class)
	param_class = Boolean.TYPE;
      else if (param_class == Double.class)
	param_class = Double.TYPE;
      else if (param_class == Byte.class)
	param_class = Byte.TYPE;
      else if (param_class == Short.class)
	param_class = Short.TYPE;
      else if (param_class == Character.class)
	param_class = Character.TYPE;
	
      argClasses[i] = param_class;
    }
    return argClasses;
  }


  /**
   * Lookup up a class from teh class cache. If the class has not already been downloaded
   * then it will be loaded via the System class loader.
   *
   *@param class_name Class to lookup (must be fully quanlified for local classes)
   */
  public Class lookupClass(String class_name)
       throws ClassNotFoundException
    {
      Class the_class;

      try {
	the_class = (Class)
	  this.classHashtable.get(class_name);

	// If anyone is wondering why Class.forName is not used here to
	// look up a class, we want the last class loaded of a given
	// name, not the first (which forName returns)
      
	// No class found that was previously loaded, therefore try a local class
	if (the_class == null)
	  the_class = Class.forName(class_name);

	return the_class;

      } catch (Exception E) 
	{
	  throw (new ClassNotFoundException
		 ("Could Not find Class " + class_name + " locally or downloaded" ));
	}
    }

}
    





