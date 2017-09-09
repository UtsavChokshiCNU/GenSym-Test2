package com.gensym.beaneditor;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import java.beans.EventSetDescriptor;
import java.beans.IntrospectionException;
import java.beans.Introspector;
import java.beans.PropertyDescriptor;
import java.beans.BeanInfo;
import java.lang.reflect.*;
import java.io.InputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.StringWriter;
import java.io.PrintWriter;
import com.gensym.message.Trace;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.message.Resource;
import com.gensym.classtools.*;
import com.gensym.beansruntime.Hookup;
import com.gensym.beansruntime.HookupDefinition;
import com.gensym.beansruntime.G2ClassLoader;
import com.gensym.g2script.Compiler;
import com.gensym.g2script.CompilerException;
import com.gensym.classtools.ClassInfo;
import com.gensym.classtools.ClassException;
import com.gensym.classtools.ClassAccess;
import com.gensym.classtools.RuntimeConstants;

public class HookupFactory implements RuntimeConstants
{
  private static final String pathSeparator = System.getProperty ("path.separator");
  private static Vector hookups = new Vector();
  private static final boolean debug = false;
  private static byte[] lastClassData;
  private static Hashtable hookupSources = new Hashtable();

  static final int AUTOMATIC       = 1;
  static final int JAVA            = 2;
  static final int G2SCRIPT        = 3;
  static final int AUTOMATIC_EXACT = 4;
  
  /*
   * Standard Messaging Requirements
   */
  
  static private Resource i18n =
  Resource.getBundle("com.gensym.resources.Messages",
		     Locale.getDefault());
  
  static private int GUI_LEVEL = 2;
  
  static String dirName;
  
  static {
      dirName = System.getProperty ("com.gensym.beaneditor.hookups.repository",
				    null);
      if (dirName == null){
	if (ComponentEditor.windowsPlatform)
	  dirName = java.io.File.separator+"temp";//hopefully this will be writable!
	else
	  dirName = java.io.File.separator+"tmp";
      }
      File file = new File(dirName);
      file.mkdirs();
  }

  /**
   *  If generateHookup returns null, rather than throwing an exception
   *  it implies that the user cancelled interactive hookup creation.
   *
   *  the targetMethod arg may be null if the sourceCode argument is provided
   *  and vice-versa.  If both are null an IllegalArgumentException is thrown,
   *  and the callers name and address will be taken and reported to the authorities.
   */
  
  static Object generateHookup(EventSetDescriptor esd,
			       Method listenerMethod,
			       Object sourceBean,
			       Object targetBean,
			       Object callSpecification,
			       int syntax,
			       String sourceCode,
			       String[] knownBeanNames,
			       Object[] knownBeans)
  {
    if (callSpecification == null && sourceCode == null)
      throw new IllegalArgumentException("Either targetMethod or sourceCode must be given");
    HookupSession session = new HookupSession();
    
    
    try {
      // whip up a new hookup class 
      Class hookupClass = null;
      switch (syntax)
	{
	case AUTOMATIC:
	case AUTOMATIC_EXACT:
	case G2SCRIPT:
	  ClassInfo classInfo
	    = generateHookupClassInfo(esd,listenerMethod,targetBean.getClass(),
				      callSpecification,syntax,session,sourceCode,
				      knownBeanNames,knownBeans);
	  if (classInfo == null)
	    return null; // implies no hookup by user's choice, not an exception;
	  classInfo.add(new SourceFileAttribute("Anonymous Hookup"));
	  classInfo.emit();
	  // next three lines are debugging
	  byte[] classData = classInfo.getBytes();
	  if (debug)
	    {
	      classInfo.toStdout();
	      System.out.println("emitted class is "+classData.length+" bytes");
	    }
	  String simpleClassName
	    = classInfo.getClassName().substring(classInfo.getClassName().lastIndexOf(".")+1);
	  String fileName = dirName + java.io.File.separator + simpleClassName + ".class";
	  classInfo.toFile(fileName,false);
	  
	  // Get the class-defining bytes
	  G2ClassLoader loader = G2ClassLoader.ourLoader;
	  InputStream is = new FileInputStream(fileName);
	  File classFile = new File (fileName);
	  int classFileLength = (int)classFile.length ();
	  lastClassData = new byte[classFileLength];
	  is.read (lastClassData);
	  is.close();
	  
	  // Now load the class and make hookup instance
	  hookupClass = loader.loadClass (classInfo.getClassName(), lastClassData);
	  if (debug)
	    {
	      System.out.println("loading class done");
	      System.out.flush();
	    }
	  loader.reallyResolveClass(hookupClass);
	  if (debug)
	    {
	      System.out.println("resolved class");
	      System.out.flush();
	    }
	  break;
	case JAVA:
	  hookupClass = generateJavaHookupClass(esd, listenerMethod, sourceBean, 
						targetBean, callSpecification, 
						session,
						sourceCode,
						knownBeanNames,
						knownBeans);
	  if (hookupClass == null)
	    return null;  // implies no hookup by user's choice, not an exception;
	  break;
	}
      

      // by this point the HookupSession, session should have some sourceCode in
      // it and we can place it in the per-class hashtable for hookups.
      Object tableValue = session.source;
      if (tableValue == null)
	tableValue = new Integer(3);
      hookupSources.put(hookupClass,tableValue);
      Hookup hookup = (Hookup) hookupClass.newInstance();

      if (hookup != null)
	{
	  hookup.setSource(sourceBean);
	  hookup.setTarget(targetBean);
	  hookup.setDebug(true);
	  int i,len = knownBeanNames.length;
	  for (i=0; i<len; i++)
	    try {
	    Field field = hookupClass.getField(knownBeanNames[i]);
	    field.set(hookup,knownBeans[i]);
	  } catch (Exception e)
	    {
	      Trace.exception(e);
	      throw new RuntimeException("Internal knowledge link init failure");
	    }
	  hookups.addElement(new HookupDefinition(hookupClass.getName(), lastClassData));
	  return hookup;
	}
      else
	throw new ClassNotFoundException(hookupClass.getName());
    } catch (Exception e)
      {
	System.out.println("general generate hookup exception");
	Trace.exception (e, null);
	Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
				       HookupFactory.class, i18n,
				       "cantLoadHookup", new Object[] {}));
	return null;
      }
  }
  
  /*
   * In the case where the target bean implements the listener
   * interface directly and the target method chosen is the
   * same as the source method, there is no need for an
   * adapter. This entire step can be short-circuited.
   */
  private static boolean hookupNeedsAdapter (EventSetDescriptor esd,
					     Method listenerMethod,
					     Object targetBean,
					     Method targetMethod) {
    Class c = esd.getListenerType();
    boolean match = c.isAssignableFrom (targetBean.getClass ());
    if (match)
      match = listenerMethod.getName ().equals (targetMethod.getName ());
    Class[] listenerParams = listenerMethod.getParameterTypes ();
    Class[] targetParams   = targetMethod.getParameterTypes ();
    if (match = match && (listenerParams.length == targetParams.length)) {
      for (int i=0; i<listenerParams.length; i++)
	if (!(listenerParams[i].equals (targetParams[i]))) {
	  match = false;
	  break;
	}
    }
    return (!match);
  }


  /** Gets a vector containing the names of the hookups and the bytes which
  * define them
  */
  static Vector getHookups()
  {
     return hookups;
  }

  static void addHookup (HookupDefinition hd) {
    hookups.addElement (hd);
  }

  static void removeHookupDefinitionForClass(Class c)
  {
    String className = c.getName();
    int i, size = hookups.size();
    for (i=0; i<size ; i++)
      if (((HookupDefinition)hookups.elementAt(i)).name.equals(className))
	{
	  hookups.removeElementAt(i);
	  break;
	}
  }

  static void clearHookups () {
    hookups.removeAllElements ();
  }

  // AUTOMATIC syntax support

  static String descriptorForType(Class type)
  {
    if (type == Integer.TYPE)
      return "I";
    else if (type == Long.TYPE)
      return "J";
    else if (type == Byte.TYPE)
      return "B";
    else if (type == Character.TYPE)
      return "C";
    else if (type == Short.TYPE)
      return "S";
    else if (type == Float.TYPE)
      return "F";
    else if (type == Double.TYPE)
      return "D";
    else if (type == Boolean.TYPE)
      return "Z";
    else if (type == Void.TYPE)
      return "V";
    else
      return "L"+type.getName().replace('.','/')+";";
  }
  
  static String descriptorForMethod(Method method)
  {
    String descriptor = "(";
    Class[] parameterTypes = method.getParameterTypes();
    for (int i = 0; i<parameterTypes.length ; i++)
      descriptor += descriptorForType(parameterTypes[i]);
    return descriptor + ")"+descriptorForType(method.getReturnType());
  }

  
  private static ClassInfo generateHookupClassInfo(EventSetDescriptor esd,
						   Method listenerMethod,
						   Class targetType,
						   Object callSpecification,
						   int syntax,
						   HookupSession session,
						   String sourceCodeForMethod,
						   String[] knownBeanNames,
						   Object[] knownBeans)
  {
    Method targetMethod = null;
    boolean usingHookupCall = false;
    HookupCall hookupCall = null;
    if (callSpecification != null)
      {
	if (callSpecification instanceof HookupCall)
	  {
	    targetMethod = ((HookupCall)callSpecification).method;
	    hookupCall = (HookupCall)callSpecification;
	    usingHookupCall = true;
	  }
	else
	  targetMethod = (Method)callSpecification;
      }
    
    String packageName = "com.gensym.beaneditor.hookups";
    String simpleClassName = "Hookup"+Long.toHexString((new Date()).getTime()/10);
    String className = packageName + "." + simpleClassName;
    Object hookup = null;
    Class[] targetMethodTypes = null;
    if (targetMethod != null)
      targetMethodTypes = targetMethod.getParameterTypes();
    Class[] listenerMethodTypes = listenerMethod.getParameterTypes();
    int i,j,k;
    Vector methodInfosMade = new Vector();
    
    try {
      ClassAccess access 
	= new ClassAccess(ACC_PUBLIC);
      ClassInfo c = new ClassInfo(access,
				  className,
				  "com.gensym.beansruntime.Hookup",
				  true);
      addKnownBeansAsFields(c,knownBeanNames,knownBeans);
      c.add(new InterfaceInfo(esd.getListenerType().getName()));
      // all subclasses have a protected field called target of type Object
      // which needs to be cast to the real target type.
      FieldRef targetFieldRef 
	=  new FieldRef("com.gensym.beansruntime.Hookup",
			"target","Ljava/lang/Object;");

      Block deliverBlock = new Block();
      MethodRef deliverMethodRef
	= new MethodRef(className,"deliverEvent","(Ljava/lang/Object;)V");
      int listenerArgCount = listenerMethodTypes.length;
      
      if (syntax == AUTOMATIC || syntax == AUTOMATIC_EXACT)
	{  
	  int targetArgCount = targetMethodTypes.length;
	  MethodRef targetMethodRef
	    = new MethodRef(targetType.getName(),
			    targetMethod.getName(),
			    descriptorForMethod(targetMethod));
	  if (!usingHookupCall && targetArgCount > 0 && targetArgCount != listenerArgCount)
	    throw new RuntimeException("listener and target arg count mismatch");
	  String[] deliverArgNames = new String[listenerArgCount];
	  for (int a = 0; a<listenerArgCount; a++) deliverArgNames[a] = "arg"+a;
	  Expression[] targetMethodArgs = new Expression[targetArgCount];
	  // either call a no-arg method or EVERY arg of listener
	  // method is believed to match with targetMethod
	  for (i = 0; i < targetArgCount; i++)
	    if (usingHookupCall)
	      targetMethodArgs[i] =
		hookupCall.generateArgumentCode(c,i,
						targetMethodTypes[i],deliverArgNames[0]);//need to assume 1 event arg?(cmh)
	    else
	      {
		Variable variableExpression
		  = new Variable(deliverArgNames[i],"Ljava/lang/Object;");
		if (targetMethodTypes[i] == java.lang.Object.class)
		  targetMethodArgs[i] = variableExpression;
		else
		  targetMethodArgs[i] = new Cast(descriptorForType(targetMethodTypes[i]),
						 variableExpression);
	      }
	  if (debug)
	    System.out.println("making cast with type = "+descriptorForType(targetType));
	  MethodCall targetCall 
	    = new MethodCall(new Cast(descriptorForType(targetType),
				      targetFieldRef), 
			     targetMethodRef, 
			     targetMethodArgs, 
			     MTH_CALL_VIRTUAL);
	  StatementExpression deliverStatement = new StatementExpression(targetCall);
	  deliverBlock.add(deliverStatement);
	  deliverBlock.add(new Return());
          MethodInfo deliverMethodInfo = new MethodInfo(new Access(ACC_PROTECTED),
							deliverMethodRef,
							deliverBlock,
							deliverArgNames,
							new ClassRef[0]);
	  methodInfosMade.addElement(deliverMethodInfo);
	  c.add(deliverMethodInfo);
	}
      else
	{
	  MethodInfo methodInfo
	    = makeDeliverMethodUsingG2Script(className,targetType,
					     listenerMethod,targetMethod, session,
					     sourceCodeForMethod,
					     knownBeanNames,
					     knownBeans,
					     usingHookupCall);
	  if (methodInfo != null)
	    c.add(methodInfo);
	  else
	    return null;
	}
    
      // add all methods of listener interface, giving
      // special consideration to the chosen listenerMethod
      Method methods[] = esd.getListenerMethods();
      for (k = 0; k < methods.length; k++)
	{
	  Class argTypes[] = methods[k].getParameterTypes();
	  String[] argNames = new String[argTypes.length];
	  for (j = 0; j<argTypes.length ; j++)
	    argNames[j] = "arg"+j;
	  String descriptor = descriptorForMethod(methods[k]);
	  Block block = new Block();
	  if (targetMethod != null)
	    {
	      Class[] targetExceptions = targetMethod.getExceptionTypes();
	      boolean exceptionsAreThrownByTargetMethod = 
		targetExceptions.length > 0;
	      if (exceptionsAreThrownByTargetMethod)
		System.out.println("Warning: target method throws exceptions");
	    }
	  
	  if ((listenerMethod.getName()).equals(methods[k].getName()))
	    {
	      FieldRef debugFieldRef =  new FieldRef("com.gensym.beansruntime.Hookup",
						     "debug","Z");
	      MethodRef pauseMethodRef
		= new MethodRef("com.gensym.beansruntime.Hookup",
				"pauseHookupEvent",
				"([Ljava/lang/Object;)V");
	      if (debug)
		System.out.println("pauseMethodRef = "+pauseMethodRef);

	      Expression[] methodArgs = new Expression[argTypes.length];
	      Expression[] newArrayArgs = new Expression[argTypes.length];
	      for (i = 0; i < argTypes.length; i++)
		{
		  argNames[i] = "arg"+i;
		  methodArgs[i] = new Variable(argNames[i],
					       // the following line should work
					       // except generateVariableIds
					       // does bad things
					       // "Ljava/lang/Object;");
					       descriptorForType(argTypes[i]));
		  newArrayArgs[i] = new Variable(argNames[i],
					       descriptorForType(argTypes[i]));
		}
	      NewArray newArray = new NewArray("[Ljava.lang.Object;",
					       //methodArgs);
					       newArrayArgs);
	      MethodCall pauseCall 
		= new MethodCall(pauseMethodRef, 
				 new Expression[] { newArray },
				 MTH_CALL_VIRTUAL);
	      StatementExpression thenStatement = new StatementExpression(pauseCall);
	      MethodCall deliverCall 
		= new MethodCall(deliverMethodRef,methodArgs, MTH_CALL_VIRTUAL);
	      StatementExpression elseStatement = new StatementExpression(deliverCall);
	      If ifStatement = new If(debugFieldRef,thenStatement,elseStatement);
	      block.add(ifStatement);
	    }
	  MethodRef methodRef = new MethodRef(className,methods[k].getName(),
					      descriptor);
	  block.add(new Return());
	  MethodInfo methodInfo = new MethodInfo(new Access(ACC_PUBLIC),
						 methodRef,
						 block,
						 argNames,
						 new ClassRef[0]); // exceptions thrown
	  methodInfosMade.addElement(methodInfo);
	  c.add(methodInfo);
	}
      /*
      for (int qq = 0; qq<methodInfosMade.size() ; qq++)
	{
	  MethodInfo mInfo = (MethodInfo)methodInfosMade.elementAt(qq);
	  mInfo.forceEmitCode();
	  // mInfo.localize(c.constantPool);
	}
	*/
      return c;
    } catch (Exception e)
      {
	e.printStackTrace();
	return null;
      }
       
    }

  private static void addKnownBeansAsFields(ClassInfo c,
					    String[] knownBeanNames,
					    Object[] knownBeans)
   {
     try
       {
	 int i,len = knownBeanNames.length;
	 for (i=0; i<len ; i++)
	   System.out.println("add fieldInfo for "+knownBeans[i]+
			      " which is "+knownBeanNames[i]);
	 for (i=0; i<len ; i++)
	   c.add(new FieldInfo(new Access(ACC_PUBLIC),
			       new FieldRef(c.getClassName(),
					    knownBeanNames[i],
					    descriptorForType(knownBeans[i]
							      .getClass())))); 
       }
     catch (ClassException e)
       {
	 Trace.exception(e);
	 throw new RuntimeException("Internal HookupFactory failure");
       }
  }

  // G2Script Syntax Support
  private static MethodInfo makeDeliverMethodUsingG2Script(String className,
							   Class targetClass,
							   Method listenerMethod,
							   Method targetMethod,
							   HookupSession session,
							   String sourceCodeForMethod,
							   String[] knownBeanNames,
							   Object[] knownBeans,
							   boolean usingHookupCall)
  {
    String sourceToCompile;
    
    if (sourceCodeForMethod != null)
      sourceToCompile = sourceCodeForMethod;
    else
      {
	StringWriter stringWriter = new StringWriter();
	PrintWriter out = new PrintWriter(stringWriter);
	String targetClassName = targetClass.getName();

	String g2ClassName = g2ify(targetClassName);
	String simpleClassName 
	  = targetClassName.substring(targetClassName.lastIndexOf('.')+1);
	Class[] listenerParamTypes = listenerMethod.getParameterTypes();
	Class[] targetParamTypes = targetMethod.getParameterTypes();
	int i;
	out.print("deliver-event(self :class com.gensym.beansruntime.Hookup");
	if (listenerParamTypes.length > 0)
	  out.print(", ");
	writeArglist(out,"\n    untyped-arg-",listenerParamTypes.length," :class java.lang.Object");
	out.println(")");
	out.println("target"+simpleClassName+" :class "+g2ClassName+";");
	for (i=0; i<listenerParamTypes.length; i++)
	  out.println("  arg"+i+" :class "+
		      g2ify(listenerParamTypes[i].getName())+";");
	out.println("begin");
	if (usingHookupCall && knownBeans.length > 0)
	  {
	    out.println("  {  Note:");
	    for (i=0; i<knownBeans.length; i++)
	      out.println("    the "+g2ify(knownBeanNames[i])+" of self is a "+
			  g2ify(knownBeans[i].getClass().getName()));
	    out.println("  }");
	  }
	out.println("  target"+simpleClassName+" = the target of self;");
	for (i=0; i<listenerParamTypes.length; i++)
	  out.println("  arg"+i+" = untyped-arg-"+i+";");
	out.print(  "  call "+g2ify(targetMethod.getName())+"(target"+simpleClassName);
	if (targetParamTypes.length > 0)
	  out.print(", ");
	writeArglist(out,"arg",targetParamTypes.length,"");
	out.println(")");
	out.println("end");
	sourceToCompile = stringWriter.toString();
      }
    
    ClassInfo uncompiledClass = null;
    try {
      uncompiledClass
	= new ClassInfo(new ClassAccess(RuntimeConstants.ACC_PUBLIC),
			className,
			"com/gensym/beansruntime/Hookup",
			true);
    } catch (ClassException ce)
      {
	// this case will not happen
	Trace.exception(ce);
      }
    System.out.println ("Will compile source code -> " + sourceToCompile);
    CustomHookupEditor customEditor = new CustomHookupEditor (new Frame (),
							      "Custom Hookup Editor",
							      sourceToCompile,
							      HookupFactory.G2SCRIPT,
							      uncompiledClass);
    System.out.println ("Showing editor!");
    customEditor.setVisible (true);
    if (!customEditor.editSucceeded())
      return null;
    String source = customEditor.getSourceCode();
    session.source = source;
    System.out.println("back from editor with\n"+source);
    try {
      Compiler c = new Compiler();
      return c.compileMethod(source,uncompiledClass);
    } catch (CompilerException e)
      {
	// This cannot occur due to the fact that the source has already
	// passed testCompileMethod
	System.out.println("*********** Method Compile failure:");
	e.printStackTrace();
	return null;
      }
  }

  static String g2ify(String name)
  {
    // here , write this and use it in the above method
    // worry about how these can be used in "x :class com.gensym.whizzo.Thing-For-Me"
    // test the text generation aspect of G2SCRIPT hookup generation.
    // get className to CustomHookupEditor constructor 
    // implement the "OF" operator
    StringBuffer buffer = new StringBuffer();
    char[] chars = name.toCharArray();
    int i, len = chars.length;
    boolean lastCharIsDot = false;
    for (i=0; i<len ; i++)
      {
	char ch = chars[i];
	if (Character.isUpperCase(ch) && i > 0)
	  {
	    if (!lastCharIsDot)
	      buffer.append('-');
	    buffer.append(Character.toLowerCase(ch));
	  }
	else if (ch == '.')
	  {
	    buffer.append('.');
	    lastCharIsDot = true;
	  }
	else
	  {
	    buffer.append(ch);
	    lastCharIsDot = false;
	  }
      }
    return buffer.toString();
  }

  // JAVA Syntax Support

  private static Class generateJavaHookupClass(EventSetDescriptor esd,
					       Method listenerMethod,
					       Object sourceBean,
					       Object targetBean,
					       Object callSpecification,
					       HookupSession session,
					       String sourceCode,
					       String[] knownBeanNames,
					       Object[] knownBeans)
  {
    Method targetMethod = null;
    boolean usingHookupCall = false;
    HookupCall hookupCall = null;
    if (callSpecification != null)
      {
	if (callSpecification instanceof HookupCall)
	  {
	    targetMethod = ((HookupCall)callSpecification).method;
	    hookupCall = (HookupCall)callSpecification;
	    usingHookupCall = true;
	  }
	else
	  targetMethod = (Method)callSpecification;
      }
    primClasses.removeAllElements ();

    String packageName = "com.gensym.beaneditor.hookups";
    String targetType  = targetBean.getClass().getName();
    String className   = "Hookup" + Long.toHexString((new Date()).getTime()/10);
    String fileName    = dirName + java.io.File.separator + className + ".java";
    
    Object hookup = null;
    
    if (sourceCode == null)
      {
	// Open the new java source file,
	PrintWriter out = null;
	StringWriter stringBuffer = null;
	try
	  {
	    stringBuffer = new StringWriter ();
	    out = new PrintWriter(stringBuffer);
	  }
	catch (Exception ex)
	  {
	    Trace.exception(ex);
	    Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
					   HookupFactory.class, i18n, "cantCreateHookupFile",
					   new Object[] {}));
	  }
	
	out.println("package " + packageName + ";");
	out.println("");
	out.println("import " + targetType + ";");
	out.println("import " + esd.getListenerType().getName() + ";");
	out.println("import com.gensym.beansruntime.Hookup;");
	
	out.println("");
	out.println("public class " + className + " extends Hookup implements " + 
		    esd.getListenerType().getName() + ", java.io.Serializable");
	out.println("{");    
	// first the friend/knowledge-link fields

	int i;
	if (usingHookupCall)
	  {
	    int len = knownBeanNames.length;
	    for (i=0; i<len ; i++)
	      out.println("  public "+knownBeans[i].getClass().getName()+" "+
			  knownBeanNames[i]+";");
	  }
	
	// second the deliverEvent method
	
	Class[] listenerParamTypes = listenerMethod.getParameterTypes();
	Class[] targetParamTypes = targetMethod.getParameterTypes();
	out.print("  protected void deliverEvent(");
	// write deliver args
	writeArglist(out,"Object untypedArg",listenerParamTypes.length,"");
	out.println(")  {");
	// bind a locals to cast versions of parameters
	for (i=0; i<listenerParamTypes.length; i++)
	  out.println("      "+ getClassTypeAsJavaSource (listenerParamTypes[i]) +" arg"+i+" = "+
		      "("+listenerParamTypes[i].getName()+") untypedArg"+i+";");
	writeArgAccessors (out, listenerParamTypes);
	writeTargetArgs (out, targetParamTypes);	
	Class[] targetExceptions = targetMethod.getExceptionTypes ();
	boolean exceptionsAreThrownByTargetMethod = 
	  targetExceptions.length > 0;
	if (exceptionsAreThrownByTargetMethod)
	  out.println ("        try {");
	out.print("      (("+targetBean.getClass().getName()+
		  ")target)." + targetMethod.getName() + "(");
	
	writeArglist(out,"param",targetParamTypes.length,"");
	out.println(");");
	
	if (exceptionsAreThrownByTargetMethod)
	  out.println ("        } catch (Exception e) {System.err.println (e);}");
	out.println("  }");
	
	// now the listener methods
	
	Method methods[] = esd.getListenerMethods();
	
	for (int k = 0; k < methods.length; k++)
	  {
	    out.println("");
	    out.print("    public void " + methods[k].getName() + "(");
	    
	    Class[] argTypes = methods[k].getParameterTypes();
	    
	    for (i = 0; i < argTypes.length; i++)      
	      out.print((i>0 ? ", " : "") + argTypes[i].getName() + " arg" + i);
	    out.println(")    {");
	    
	    if ((listenerMethod.getName()).equals(methods[k].getName()))
	      {
		out.println("    if (debug)");     
		out.print  ("      pauseHookupEvent(new Object[] {");
		writeArglist(out,"arg",argTypes.length,"");
		out.println("});");
		out.println("    else");
		out.print("      deliverEvent(");
		writeArglist(out,"arg",argTypes.length,"");
		out.println(");");
	      }
	    out.println("    }");
	  }
	out.println();
	writeInitializers (out);
	out.println("}");
	
	out.close();
	sourceCode = stringBuffer.toString();
      }
    else
      {
	// Whip up a new class name
	int classStartIndex  = sourceCode.indexOf ("public class ");
	classStartIndex += 13;
	int classEndIndex = sourceCode.indexOf (' ', classStartIndex);
	sourceCode 
	  = sourceCode.substring(0,classStartIndex) +
	  className +
	  sourceCode.substring(classEndIndex);
      }
    
    // compile the java file
    if (debug)
      System.out.println ("Will compile source code -> " + sourceCode);
    CustomHookupEditor customEditor = new CustomHookupEditor (new Frame (),
							      "Custom Hookup Editor",
							      sourceCode,
							      HookupFactory.JAVA,
							      null);
    if (debug)
      System.out.println ("Showing editor!");
    customEditor.setVisible (true);
    if (debug)
      System.out.println ("\n\nCustom Editor Done!!\n\n");
    if (!customEditor.editSucceeded())
      return null;
    lastClassData = customEditor.getCompiledClassBytes ();

    Class hookupClass = null;
    try {
      G2ClassLoader loader = G2ClassLoader.ourLoader;
      // Now load the class
      hookupClass = loader.loadClass (packageName+"."+className, 
				      lastClassData);
      session.source = customEditor.getSourceCode();
    } catch (Exception e) {
      Trace.exception (e, null);
      Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
				     HookupFactory.class, i18n, "cantLoadHookup", 
				     new Object[] {}));
    }
    
    return hookupClass;
  }

  private static void writeArglist(PrintWriter out, String prefix, int length,
				   String suffix)
  {
    for (int i = 0; i < length ; i++)
      {
	if (i > 0)
	  out.print(", ");
	out.print(prefix + i+suffix);
      }
  }

  static void writeArgAccessors (PrintWriter out, Class[] argTypes) {
    try {
      for (int i=0; i<argTypes.length; i++) {
	out.println ("      /*");
	out.println ("       * Cracking Arg #" + i + " " + argTypes[i].getName ());
	out.println ("       */");
	BeanInfo bi = Introspector.getBeanInfo (argTypes[i]);
	PropertyDescriptor[] pds = bi.getPropertyDescriptors ();
	for (int j=0; j<pds.length; j++) {
	  Method readMethod = pds[j].getReadMethod ();
	  String propertyName = pds[j].getName ();
	  propertyName = mangleIfKeyword (propertyName);
	  out.println ("      " + readMethod.getReturnType ().getName () + " " +
		       propertyName + "= arg" + i + "." +
		       readMethod.getName () + "();");
	}
      }
    } catch (IntrospectionException ie) {
      Trace.exception (ie);	// Silent failure is OK!
    }
  }

  private static final String[] keywords = {"class", "interface", "static", "volatile", "synchronized"};
  private static final String[] keywordSubstitutes = {"clazz", "intf", "staticP", "vltle", "synchrnzed"};
  private static final Vector primClasses = new Vector ();

  private static String mangleIfKeyword (String name) {
    for (int i=0; i<keywords.length; i++)
      if (name.equals (keywords[i]))
	return keywordSubstitutes[i];
    return name;
  }

  static void writeTargetArgs (PrintWriter out, Class[] paramTypes) {
    out.println ();
    out.println ("      /*");
    out.println ("       * Declarations for target method parameters -- Need initialization");
    out.println ("       */");
    for (int i=0; i<paramTypes.length; i++) {
      out.print ("      " + getClassTypeAsJavaSource (paramTypes[i]) + " param" + i);
      if (paramTypes[i].isPrimitive ()) {
	int initializerIndex = primClasses.size ();
	primClasses.addElement (paramTypes[i]);
	out.println (" = primInit" + initializerIndex + ";");
      } else
	out.println (" = null;");
    }
  }

  private static String getClassTypeAsJavaSource (Class c) {
    if (!c.isArray ())
      return c.getName ();
    else
      return getClassTypeAsJavaSource (c.getComponentType ()) + "[]";
  }

  static void writeInitializers (PrintWriter out) {
    out.println ();
    out.println ("    /*");
    out.println ("     * Instance variables for initialization");
    out.println ("     */");
    for (int i=0; i<primClasses.size (); i++) {
      Class primitiveClass = (Class) primClasses.elementAt (i);
      out.println ("    private " + primitiveClass.getName () + " primInit" + i + ";");
    }
  }

  static String getHookupClassSource(Class c)
  {
    Object thing = hookupSources.get(c);
    if (thing instanceof String)
      return (String) thing;
    else
      return null;
  }

  public static void main (String[] args)
  {
    try
      {
	Object[] array = new Object[] { new Integer(3) };
	System.out.println("class "+array.getClass().getName());
	ClassRef cc =  new ClassRef("[Ljava.lang.Object;");
	com.gensym.classtools.Type tpe = cc.getExpressionType();
	System.out.println("tpe = "+tpe+" rank "+tpe.getArrayDimensions());
	FileInputStream in = new FileInputStream(
          "c://bt//jed-h1//java//com//gensym/beaneditor//hookups//"+args[0]);
	ClassInfo myCI = new ClassInfo(in);
	myCI.toStdout();
	in.close();

      } catch (Exception e)
	{
	  e.printStackTrace();
	}
  }
    
}

class HookupSession
{
  String source = null;
}
