
package com.gensym.jgi;

import java.util.Enumeration;
import java.lang.reflect.*;
import java.util.Vector;
import java.util.Hashtable;
import java.rmi.RemoteException;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.G2_EventObject;
import com.gensym.classes.G2_ExternalEventObjectRoot;
import com.gensym.classes.G2Definition;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.G2ClassTranslator;
import com.gensym.util.Symbol;
import com.gensym.util.DownLoad;
import com.gensym.util.MethodInvocationException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.message.Trace;
import com.gensym.jgi.download.G2StubCreationException;
import com.gensym.jgi.rmi.RMIEventQueueProcessor;
import com.gensym.jgi.rmi.G2RMIAccess;


/**
 * This class is utilized by G2 to create and control java classes and instances.
 * G2 accesses the Java objects via G2 stubs uploaded via the class.
 * 
 * @version 	1.5 July 98
 *
 * @author M.D.Gribble
 */
public class G2JavaStubController
{

  private DownLoad downloader = new DownLoad();
  private Hashtable connectionsTable = new Hashtable(11);
  
  /**
   * The oldest version of G2 JavaLink module at the other end
   * of a G2Gateway connection. This can change on every
   * release of JavaLink.
   */
  private static final String JAVALINK_MINIMUM_VERSION_STRING = "Version 1.0 Rev 1 A14";
  public static final G2Version JAVALINK_MINIMUM_VERSION = new G2Version (JAVALINK_MINIMUM_VERSION_STRING);

  public static final Symbol 
        JGI_PROXY_MIXIN_CLASS_ = Symbol.intern("JGI-JAVA-PROXY");
  public static final Symbol
        JGI_G2PROXY_MIXIN_CLASS_ = Symbol.intern("JGI-JAVA-G2PROXY");

  private static final Symbol 
        JgiCreateClassAndReturnProxySymbol = Symbol.intern("JGI-CREATE-CLASS-AND-RETURN-PROXY"),
	JgiCreateClassAndReturnProxyForEventSourceSymbol = 
                              Symbol.intern("JGI-CREATE-CLASS-AND-RETURN-PROXY-FOR-EVENT-SOURCE"),
	JgiRemoveProxyAssociation = Symbol.intern("JGI-REMOVE-PROXY-ASSOCIATION"),
	JgiRemoveProxyEventListener = Symbol.intern("JGI-REMOVE-PROXY-EVENT-LISTENER"),
	JgiAddProxyEventListener = Symbol.intern("JGI-ADD-PROXY-EVENT-LISTENER"),
        JGI_GET_JAVALINK_MODULE_VERSION_ = Symbol.intern("JGI-GET-JAVALINK-MODULE-VERSION");

  private static final String
        NoProxyExceptionString = "Could not find Java instance associated with passed G2 Proxy";

  private static final Symbol G2_ARRAY_SEQUENCE_ = Symbol.intern("G2-ARRAY-SEQUENCE");

  private static final Symbol CLASS_ = Symbol.intern("CLASS");
  private static final Symbol VAL_  = Symbol.intern("VAL");
  private static final Symbol NONE_ = Symbol.intern("NONE");
  private static final Symbol JAVA_PARAMETER_TYPES_ = Symbol.intern("JAVA-PARAMETER-TYPES");
  private static final Symbol JAVA_CLASSNAME_ = Symbol.intern("JAVA-CLASSNAME");
  private static final Symbol G2_EVENT_LISTENER_ = Symbol.intern("G2-EVENT-LISTENER");

  protected static volatile G2JavaStubController controller = null;

  // We force the use of getG2JavaStubController
  private void G2JavaStubController() {
  }

  /** @undocumented
   * There should only ever by one of these per VM
   */ 
  public static synchronized G2JavaStubController getG2JavaStubController() {
    if (controller == null)
      synchronized (G2JavaStubController.class) {
        if (controller == null)
          controller = new G2JavaStubController(); 
      }
    return controller;
  }

  /**
   * @undocumentated
   */
  public DownLoad getDownloader() {
    return downloader;
  }

  /**
   * @undocumented
   */
  public void setDownloader(DownLoad newDownLoader) {
    downloader = newDownLoader;
  }

  /**
   * @undocumentated
   * Set an optional factory for a conneciton that can provide java objects that represent G2 Items
   * when the controller can not find an association between a G2 item and a Java object.
   */
  public void setJavaObjectForG2ItemFactory(G2Access connection, JavaObjectForG2ItemFactory factory) {
    ConnectionRegistry registryInfo = getConnectionRegistry(connection);
    registryInfo.setJavaObjectForG2ItemFactory(factory);
  }

  /**
   * @undocumentated
   * Set an optional factory for a connection that can provide G2 class names for a given Java object
   * when the controller can not find an G2 class name for the proxy for a Java object
   */
  public void setG2ClassForJavaObjectFactory(G2Access connection, G2ClassForJavaObjectFactory factory) {
     ConnectionRegistry registryInfo = getConnectionRegistry(connection);
     registryInfo.setG2ClassForJavaObjectFactory(factory);
  }

  /**
   * @undocumentated
   * Set an optional factory that can provide a G2 Item for a given Java object
   * when the controller is trying to resolveJavaObjects to G2 Items but can not find 
   * an associated G2 Item, it the connection's registry
   */
  public void setG2ItemForJavaObjectFactory(G2Access connection, G2ItemForJavaObjectFactory factory) {
     ConnectionRegistry registryInfo = getConnectionRegistry(connection);
     registryInfo.setG2ItemForJavaObjectFactory(factory);
  }

  private G2JavaStubClassReflectionProvider g2JavaStubClassReflectionProvider =
                   new G2JavaStubGenerator();

  /**
   * @undocumentated
   * Set the G2JavaStubClassReflectionProvider that will be used to create data for
   * G2 when it wishes to create stubs that represent Java Classes.
   */
  public void setG2JavaStubClassReflectionProvider(G2JavaStubClassReflectionProvider provider) {
    g2JavaStubClassReflectionProvider = provider;
  }


  // Methods that are public here are being accessed by reflection by JGI

  /**
   * Compile Java Class Source Text and "Load" the subsequent 
   * classs into the runtime.
   *
   * <P>This method compiles the source given as a paramater. If successfull
   * the .class file is loaded into the current runtime and resolved
   * aganist current loaded classes. As a source file can contain many
   * class definitions, a classname parameter must be specified. This 
   * specifies which class to load and resolve. This class loaded 
   * allows classes to be loaded even when they have already part of
   * the runtime. This allows dynamic updating of class definitions.
   * However, note that class instances created from old definitions
   * will still use their orginal class definition.
   *
   *@param classname The class to compile in the source code
   *@param source  The Java source text
   *
   *@return If errors where found during the source compilation the
   * compiler error message is returned. The text of exceptions raised
   * is returned and the class is not loaded. If the source compiles
   * and the class loads and resolves then a empty string "" is returned
   @exception com.gensym.util.JavaClassCompilerException if the compilation failed
   */
  String loadJavaClass(String classname, String source)
       throws com.gensym.util.JavaClassCompilerException
  {
    return downloader.loadJavaClass(classname, source);
  }

  /**
   * Create a Java Class Instance, for a given G2 Class
   *
   * <P>Thie method will create a  new instance if a class previsouly downloaded
   * using <B>loadJavaClass</B>. The Java object created is then recorded as associated
   * with the g2 proxy.
   * <P>The method will lookup the constructor that matches the classes in args.
   * If no arguments can be found then NoSuchMethodException will be raised.
   * <P>If an IllegalAccessException is thrown, the class may not be declared
   * public
   * 
   *@param g2proxy     Assumed to be a "by-handle" proxy for a G2 object wanting to
   *                   control a G2 object.
   *@param class_name  The class of the instance to create.
   *@param args        The constructors parameters
   *@exception ClassNotFoundException If the Java class can not be found
   *@exception InstantiationException If a newInstance can be created of Java class
   *@exception IllegalAccessException If the runtime does not allow access to Java class instances
   *@exception com.gensym.util.MethodInvocationException when a problem occurs dynamically invoking newInstance
   *@exception NoSuchMethodException If newInstance on Java_class can not be found
   *@exception G2AccessException when a problem occurs as a result of communicating with G2.
   */
  public void newInstance(Item g2proxy, String java_class_name, Sequence args)
       throws ClassNotFoundException, 
	 InstantiationException, 
	 IllegalAccessException,
	 com.gensym.util.MethodInvocationException,
	 NoSuchMethodException,
	 G2AccessException
  {
    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);


    // Get the Class signatures for this constructor and
    // Make sure that we dont have any arguments, that are actually G2 stubs for Java objects
    Class[] argClasses = getArgClassesAndResolve(registryInfo, null, args);

    // Try to create the Java object
    Object obj = downloader.newInstance(java_class_name, args, argClasses);

    // Register this G2 class as tied to the thing we have just created
    registryInfo.registerG2ClassWithJavaClass(g2proxy, java_class_name);

    // Record this instance and its relationship with the java instance
    // WARNING ONE-TO-ONE MAPPING
    registryInfo.associate(g2proxy, obj);
  }


  /** 
   * Call A Method on an instance created previously by newInstance
   * The calling arguments are send via a Sequence. All Wrapped prmitive types
   * wrapped in the arguments are unwrapped before invoking the method
   *
   * @param g2Proxy     The g2proxy the call was made on in G2
   * @param method_name The method to call
   * @param args        The Sequence of arguments to pass to the method
   *
   *@exception IllegalAccessException If the runtime does not allow access to Java class instances
   *@exception InstantiationException If problems creating any java objects for return values
   *@exception com.gensym.util.MethodInvocationException while dynamically invoking a method
   *@exception NoSuchMethodException If the method could not be found
   *@exception G2AccessException when a problem occurs as a result of communicating with G2.
   */
  public Object callMethod(Item g2proxy, 
			  String method_name, 
			  Sequence args)
       throws NoSuchMethodException,
	 IllegalAccessException,
	 InstantiationException,
	 com.gensym.util.MethodInvocationException,
         G2AccessException,
	 RemoteException
  {

    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);

    // Find the Java object associated with this g2proxy
    Object javaobj = registryInfo.getAssociatedJavaObject(g2proxy);

    // Get the Class signatures for this method call and
    // Make sure that we dont have any arguments, that are actually G2 stubs for Java objects
    Class[] argClasses = getArgClassesAndResolve(registryInfo, javaobj, args);


    return callMethod(g2proxy, javaobj, registryInfo, method_name, null, args, argClasses);
  }


  /** 
   * Call A Listener Method on an Listener interface exported from G2. Specifically 
   * designed to send the event attributes seperate...so we dont need to 
   * call G2 to get the events attributes, and we dont get a delete notification 
   * when the event is deleted in G2. The event in G2 can be deleted and still allow
   * the event to be sent to the client asynchronously.
   *
   * @param g2proxy     The g2 proxy the call was on
   * @param method_name The method name to call
   * @param g2method    The method object is G2, used to lookup the java method to call
   * @param eventClassSymbol The G2 class name of thee event
   * @param eventAttributes The Events attributes sent by-handle...to make this more efficient
   *                    Otherwise Java will have to call g2 for its attributes
   * @param g2EventSource The source of the event, sent by handle, not included in the attributes of 
   *                     g2EventIn
   *
   *@exception IllegalAccessException If the runtime does not allow access to Java class instances
   *@exception InstantiationException If problems creating any java objects for return values
   *@exception com.gensym.util.MethodInvocationException while dynamically invoking a method
   *@exception NoSuchMethodException If the method could not be found
   *@exception G2AccessException when a problem occurs as a result of communicating with G2.
   */
  public void callG2ItemListenerMethod(Item g2proxy,
				   String methodName,
				   Item g2method,
				   Symbol g2EventClassSym,
				   Structure eventAttributes,
				   Item g2EventSource) throws 
         NoSuchMethodException,
	 IllegalAccessException,
	 InstantiationException,
	 com.gensym.util.MethodInvocationException,
         G2AccessException,
	 ClassNotFoundException,
	 RemoteException {

    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);
    if (registryInfo.getAssociatedJavaObject(g2proxy).equals(g2proxy))
      return;

    G2_ExternalEventObjectRoot event = null;
    try {
      event = 
	G2_ExternalEventObjectRoot.createExternalEventObject(g2EventSource, 
							     eventAttributes,
							     g2EventClassSym, 
							     registryInfo.g2connection);


      } catch (G2AccessException e) {
	throw new RuntimeException(e.toString());
      }
      //System.out.println("Resolve Event" + event + " source " + g2item);
    Sequence args = new Sequence();
    args.addElement(event);
    callMethod(g2proxy,
	       methodName,
	       g2method,
	       args);
  }

  /** 
   * Call A Method on an instance created previously by newInstance
   * The calling arguments are send via a Sequence. This version of callMethod
   * also takes the G2 Method, which is used as a key to access the prelooked 
   * up java Method to invoke. The G2 Method, contains Java signature information to pre
   * lookup the Java Method.
   *
   * @param g2Proxy     The g2 proxy the call was on
   * @param method_name The method name to call
   * @param g2method    The method object is G2, used to lookup the java method to call
   * @param args        The Sequence of arguments to pass to the method
   *
   *@exception IllegalAccessException If the runtime does not allow access to Java class instances
   *@exception InstantiationException If problems creating any java objects for return values
   *@exception com.gensym.util.MethodInvocationException while dynamically invoking a method
   *@exception NoSuchMethodException If the method could not be found
   *@exception G2AccessException when a problem occurs as a result of communicating with G2.
   */
  public Object callMethod(final Item g2proxy, 
		  final String methodName,
		  final Item g2method, 
		  final Sequence args)
       throws NoSuchMethodException,
	 IllegalAccessException,
	 InstantiationException,
	 com.gensym.util.MethodInvocationException,
         G2AccessException,
	 ClassNotFoundException,
	 RemoteException
  {
	Sequence sequence = args;  
    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);
    Object javaobj = registryInfo.getAssociatedJavaObject(g2proxy);
    //System.out.println("callmethod " + g2proxy + " " + g2method + " " + javaobj + " " + javaobj.getClass());
    Method method = registryInfo.lookupMethod(javaobj.getClass(), g2method);
    boolean g2ListenerMethods = true;
    if (method == null) {

      G2Definition g2Definition = g2proxy.getDefinition();
      String targetClassName = null;
      Sequence inhPath = null;
      try {
	inhPath = g2Definition.getClassInheritancePath();
	targetClassName = (String)((Item)g2Definition).getPropertyValue(JAVA_CLASSNAME_);
      } catch (NoSuchAttributeException e) {
	throw new G2AccessException("Could not read " + JAVA_CLASSNAME_ +
				    " attribute from G2 Defintion for " + g2proxy +
				    " during attempt to call " + methodName);
      }
      // We are checking for the G2 Listener methods here, as exported G2 Listener methods
      // always resolve to external events and listener classes with G2_ appended to the original
      // G2 Item stub
      if (inhPath.contains(G2_EVENT_LISTENER_)) { 
	targetClassName = getG2_ClassName(targetClassName);
      }
      Class targetClass = downloader.lookupClass(targetClassName);
      Class[] parameterClasses = getJavaMethodParameterTypes(g2method);
      //System.out.println("Registred method " + targetClassName); 
      method = targetClass.getMethod(methodName, parameterClasses);
      registryInfo.registerMethod(javaobj.getClass(), g2method, method);
    }

    if (method == null)
      throw new NoSuchMethodException("Cant find method registered for method(" + 
				      methodName + ")" +
				      " for g2proxy " + g2proxy + 
				      ", args where " + sequence);
    
    sequence = resolveG2StubsInSequence(registryInfo, javaobj, sequence);
    
    return callMethod(g2proxy, javaobj, registryInfo, null, method, sequence, null);
  }


  private Class[] getJavaMethodParameterTypes(Item g2method) 
    throws G2AccessException,
           MethodInvocationException,
           ClassNotFoundException {
    Sequence parameterClassesSeq = null;
    try {
      parameterClassesSeq = (Sequence)g2method.getPropertyValue(JAVA_PARAMETER_TYPES_);
    } catch (NoSuchAttributeException e) {
      throw new MethodInvocationException("Could not read " + JAVA_PARAMETER_TYPES_ + 
					  " attribute from G2 method " + g2method);
    }
    
    int numParameters = parameterClassesSeq.size();
    Class[] parameterClasses = new Class[numParameters];
    
    for (int i = 0; i<numParameters; i++) {
      String parameterClassStr = (String)parameterClassesSeq.elementAt(i);
      parameterClasses[i] = downloader.lookupClass(parameterClassStr);
      if (G2_EventObject.class.isAssignableFrom(parameterClasses[i])) {
	parameterClassStr = getG2_ClassName(parameterClassStr);
	parameterClasses[i] = downloader.lookupClass(parameterClassStr);
      }
    }
    return parameterClasses;
  }
    
  private String getG2_ClassName(String javaClassName) {
    // Hack as all G2 Listener and events are translated into  
    // we must ensure that G2_ is added to the event class names
    // G2 Listener and G2 Event methods are always resolved to external 
    // events and listener classes with G2_ appended to the original
    // G2 Item stub
    int dotIndex = javaClassName.lastIndexOf(".");
    return javaClassName.substring(0,dotIndex) + 
      ".G2_" +  javaClassName.substring(dotIndex+1);
  }

  private Object callMethod(Item g2proxy,
			    Object javaobj,
			    ConnectionRegistry registryInfo,
			    String method_name,
			    Method method,
			    Sequence args,
			    Class[] argClasses)

    throws NoSuchMethodException,
	 IllegalAccessException,
	 InstantiationException,
	 com.gensym.util.MethodInvocationException,
         G2AccessException,
	 RemoteException {

    // If javaobj is an adapter , throw an exception, A Cyclic calls will occur
    // as adapters call back into the same method on the g2 object
    // TBD !!!!

    if (javaobj == null)
      throw new IllegalAccessException(NoProxyExceptionString); 

    Object retval = null;

    // For LocalMultiCasters, we call each listener
    if (javaobj instanceof LocalMultiCaster) {
      LocalMultiCaster localMultiCaster = (LocalMultiCaster)javaobj;
      LocalMultiCaster clocalMultiCaster = (LocalMultiCaster)localMultiCaster.clone();
      for (int i=0; i<clocalMultiCaster.size(); i++) {
	Object ele = clocalMultiCaster.elementAt(i);
	try {
	  callJavaMethod(g2proxy, 
			 ele,
			 method_name, 
			 method,
			 args, 
			 argClasses, 
			 registryInfo);
	  // We dont actually need to worry about returns from multicast calls
	} catch (Exception e) {
	  localMultiCaster.listenerError(ele, e);
	}  
      }
    } else
      retval = callJavaMethod(g2proxy, 
			      javaobj, 
			      method_name,
			      method,
			      args, 
			      argClasses,
			      registryInfo);

    return retval;

  }


  private Object callJavaMethod(Item g2proxy,
				Object javaobj,
				String method_name,
				Method method,
				Sequence args,
				Class[] argClasses,
				ConnectionRegistry registryInfo)
                           throws NoSuchMethodException,
				  IllegalAccessException,
				  InstantiationException,
				  com.gensym.util.MethodInvocationException,
				  G2AccessException,
				  RemoteException {

      // Any G2JavaStubControllerListener is called via an Asynchronous event
      if (javaobj instanceof G2JavaStubControllerListener) {
        G2JavaStubControllerEvent event = new G2JavaStubControllerEvent(this,
						G2JavaStubControllerEvent.CALL_ASYNC_METHOD,
					        g2proxy,
						(method == null ? method_name : method.getName()),
						args);
	G2JavaStubControllerListener controllerListener = 
	                                 (G2JavaStubControllerListener)javaobj;
	controllerListener.callMethod(event);
	return null;
      }

    // Call the method
    Object retval = null;
    if (method == null)
      retval = downloader.callMethod(javaobj, method_name, args, argClasses);  
    else {
      try {
	//System.out.println(javaobj + " " + args + " " + method );
	retval = method.invoke(javaobj, args.getContents());
      } catch (InvocationTargetException e) {
	e.getTargetException().printStackTrace();
	throw new MethodInvocationException (method_name + " caused " + 
					     e.getTargetException().toString());
      }
    }
    
    // And we must make sure that any Java objects are converted to G2 stubs
    // that may be embedded in any compound object structures that get sent back to G2
    return resolveJavaObjects(registryInfo, retval);
  }


  /** 
   * Call A Static Method on a Java class. 
   * The calling arguments are send via a Sequence. All Wrapped prmitive types
   * wrapped in the arguments are unwrapped before invoking the method
   *
   * @param g2proxy     A dummy instance of the G2 class that will represent the class we are calling
   * @param method_name The method to call
   * @param args        The Sequence of arguments to pass to the method
   *@exception ClassNotFoundException If the java_class_name could not be found
   *@exception IllegalAccessException If the runtime does not allow access to this Java class method
   *@exception com.gensym.util.MethodInvocationException while dynamically invoking a method
   *@exception NoSuchMethodException If the method could not be found
   *@exception InstantiationException If problems creating any java objects for return values 
   *@exception G2AccessException when a problem occurs as a result of communicating with G2.
   */
  public Object callStaticMethod(Item g2proxy, 
				String java_class_name, 
				String method_name, 
				Sequence args)
       throws ClassNotFoundException, 
	 NoSuchMethodException, 
	 IllegalAccessException,
	 InstantiationException,
	 com.gensym.util.MethodInvocationException,
         G2AccessException
  {
    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);

    // Get the Class signatures for this constructor and
    // Make sure that we dont have any arguments, that are actually G2 stubs for Java objects
    Class[] argClasses = getArgClassesAndResolve(registryInfo, null, args);

    // Call the method
    Object retval = downloader.callStaticMethod(java_class_name, method_name, args, argClasses);  
    
    // And we must make sure that any Java objects are converted to G2 stubs
    // that may be embedded in any compound object structures that get sent back to G2
    retval = resolveJavaObjects(registryInfo, retval);

    return retval;
  }

  /** 
   * Call A Static Method on a Java class. This version of callStaticMethod
   * also takes the G2 Method, which is used as a key to access the prelooked 
   * up java Method to invoke. The G2 Method, contains Java signature information to pre
   * lookup the Java Method.
   *
   * @param g2proxy     A dummy instance of the G2 class that will represent the class we are calling
   * @param method_name The method to call
   * @param args        The Sequence of arguments to pass to the method
   *@exception ClassNotFoundException If the java_class_name could not be found
   *@exception IllegalAccessException If the runtime does not allow access to this Java class method
   *@exception com.gensym.util.MethodInvocationException while dynamically invoking a method
   *@exception NoSuchMethodException If the method could not be found
   *@exception InstantiationException If problems creating any java objects for return values 
   *@exception G2AccessException when a problem occurs as a result of communicating with G2.
   */
  public Object callStaticMethod(final Item g2proxy, 
		  final String java_class_name, 
		  final String methodName, 
		  final Item g2method,
		  final Sequence args)
       throws ClassNotFoundException, 
	 NoSuchMethodException, 
	 IllegalAccessException,
	 InstantiationException,
	 com.gensym.util.MethodInvocationException,
         G2AccessException
  {
	Sequence sequence = args;  
    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);
    Class targetClass = downloader.lookupClass(java_class_name);
    Method method = registryInfo.lookupMethod(targetClass, g2method);
    if (method == null) {
      Class[] parameterClasses = getJavaMethodParameterTypes(g2method);
      method = targetClass.getMethod(methodName, parameterClasses);
      registryInfo.registerMethod(targetClass, g2method, method);
    }

    sequence = resolveG2StubsInSequence(registryInfo, targetClass, sequence);

    Object retval = null;
    try {
      // Call the static method
      retval = method.invoke(null, sequence.getContents());  
    } catch (InvocationTargetException e) {
      throw new MethodInvocationException("Static method " + methodName + " caused " + 
					     e.getTargetException().toString());
    }
    
    // And we must make sure that any Java objects are converted to G2 stubs
    // that may be embedded in any compound object structures that get sent back to G2
    retval = resolveJavaObjects(registryInfo, retval);

    return retval;
  }


  /** 
   * Remove the reference to an object previsouly created using
   * <B>newInstance</B>. 
   *
   * <P>The reference to a previsouly created object is removed from
   * the classes internal lookup. If there are no other references to the
   * object in the current runtime, it will be deleted next time the 
   * VM's garbage collector executes.
   *
   * @param handle  Handle of the object to dereference
   * @return true if the refernce was removed sucessfully ot false if the 
   * the did not refer to an object
   *@exception IllegalAccessException If there is no access to the object
   *@exception G2AccessException  a problem occured while accessing G2
   */
  public void deleteInstance(Item g2proxy)
       throws IllegalAccessException,
	 G2AccessException,
	 RemoteException
  {

    deleteInstance(g2proxy, true);
     
  }

  public void deleteInstance(Item g2proxy, boolean strictCheck)
       throws IllegalAccessException,
	 G2AccessException,
	 RemoteException
  {
    //System.out.println("Deleteing " + g2proxy);
    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);

    // Find the Java object associated with this g2proxy
    Object javaobj = registryInfo.removeAssociation(g2proxy);
 
    // TBD
    //if (javaobj instanceof G)
    //  ((G2RMIJavaStubController)javaobj).deleteInstance(g2proxy, strictCheck);

    if (strictCheck && javaobj == null)
      throw new IllegalAccessException(NoProxyExceptionString); 

    // The java object should now be free to be garbage collected
     
  }


  /**
   * Return information enabling G2 to build G2 stubs
   * that allow access to a named Java class properties and methods.
   *
   *	       
   *@exception ClassNotFoundException The java class could not be found
   *@exception G2StubCreationException An error occured whil creating the G2 stub information
   */
  final Structure getG2StubsForJavaClass(String class_name, Symbol g2ClassName, boolean recurse)
       throws 
  ClassNotFoundException, G2StubCreationException
  {
    if (g2JavaStubClassReflectionProvider != null) {
      Class the_class = downloader.lookupClass(class_name);
      return g2JavaStubClassReflectionProvider.getG2StubDetailsForJavaClass
	(class_name, the_class, g2ClassName, recurse, false);
    } else
      throw new G2StubCreationException
	("Can not create G2 Stub details as there is no G2JavaStubClassReflectionProvider");
  }


  public void checkForValidBeanClass (String className)
       throws ClassNotFoundException, G2StubCreationException
  {
    System.out.println ("\n\nBoo\n\n");
    Class.forName (className);
  }


  /**
   * Return information enabling G2 to build G2 stub wrapper bean
   * that allow access to a named Java class properties and methods.
   *
   *	       
   *@exception ClassNotFoundException The java class could not be found
   *@exception G2StubCreationException An error occured whil creating the G2 stub information
   */
  final Structure getG2StubsForJavaBeanClass (String class_name, Symbol g2ClassName, boolean recurse)
       throws 
  ClassNotFoundException, G2StubCreationException
  {
    if (g2JavaStubClassReflectionProvider != null) {
      Class the_class = downloader.lookupClass(class_name);
      return g2JavaStubClassReflectionProvider.getG2StubDetailsForJavaClass
	(class_name, the_class, g2ClassName, recurse, true);
    } else
      throw new G2StubCreationException
	("Can not create G2 Stub details as there is no G2JavaStubClassReflectionProvider");
  }
  
  /**
   * Return the java types for all the method parameter and return types
   * for the given class
   *
   *@param class_name class of interest
   *@param recurse flag to indicate whether or not to recure up the class hierarchy
   *@exception G2StubCreationException An error occured whil creating the G2 stub information
   */
  final Sequence findStubHierarchyForjavaClass(String class_name, boolean recurse)
       throws
  ClassNotFoundException, G2StubCreationException
  {
    if (g2JavaStubClassReflectionProvider != null) {
      Class the_class = downloader.lookupClass(class_name);
      return g2JavaStubClassReflectionProvider.findDependentClasses
	(class_name, the_class, recurse);
    } else throw new G2StubCreationException
       ("Can not find dependant Classes for G2 Java Stub as there is no G2JavaStubClassReflectionProvider");
  }


  /**
   * Record a G2 class, as representing a Java class for a particular context
   *@exception G2AccessException A problem occured while accessing G2
   */
  void registerG2ClassWithJavaClass(Item g2proxy, String java_class_name)
       throws G2AccessException
  {  
    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);
    
    registryInfo.registerG2ClassWithJavaClass(g2proxy, java_class_name);
  }

  /**
   * Assoicate a G2Proxy with a java object for a connection
   */
  public void associate(G2Connection g2Connection,
			Item g2Proxy,
			Object javaObject) {
    
    // Get the connection Registry for this connection
    ConnectionRegistry registryInfo = getConnectionRegistry(g2Connection);  

     registryInfo.associate(g2Proxy, javaObject);

  }

  /**
   * Add a Java object as a listener for events from a G2 Event Source.
   *
   *@param g2EventSource The G2 Item that the Java Object will be listening too
   *@param adderMethodName The G2 Method name on G2EventSource for adding this listener
   *@param javaProxyClass The name of the Java listener class of which we are interested in
   *@param g2ParentClass The G2 class that the proxy class will inherit from in G2
   *@param javaListener The Java Listener object
   *@return The G2 ITEM Proxy that was used to listen for the G2 events
   * 
   */
   public synchronized Item addJavaListenerToG2EventSource (Item  g2EventSource,
							    Symbol adderMethodName,
							    String javaProxyClass,
							    Symbol g2ParentClass,
							    Object javaListener)
       throws G2AccessException {
    
    // Get the connection Registry for this connection
    ConnectionRegistry registryInfo = getConnectionRegistry(g2EventSource);  
    G2Connection g2Connection = (G2Connection)registryInfo.g2connection;

    // Have we created a proxy for this listener already ?
    LocalMultiCaster localMultiCaster = registryInfo.getMultiCaster(g2EventSource, g2ParentClass);

    //System.out.println(" adding " + javaListener + " " + g2EventSource );
    if (localMultiCaster == null) 
      // Create a G2 proxy for these listeners
      localMultiCaster = new LocalMultiCaster();

    if (localMultiCaster.g2proxy == null) {
       // Create a G2 proxy for these listeners (Multicaster just created, or its G2 proxt has been deleted)
      registryInfo.setMultiCaster(g2EventSource, g2ParentClass, localMultiCaster);
      Item g2proxy = getG2ProxyForJavaObjectAttachedToEventSource(g2Connection,
								  javaProxyClass,
								  g2ParentClass,
								  localMultiCaster,
								  g2EventSource);
      localMultiCaster.g2proxy = g2proxy;
      localMultiCaster.g2Connection = g2Connection;
    }

    if (javaListener instanceof RMIEventQueueProcessor) {
      // Assume that the RMI client is being serviced by a G2RMIAccess connection on the server side
      try {
      localMultiCaster.addElement(((G2RMIAccess)g2Connection).
				  getClientListenerForG2JavaStubController((RMIEventQueueProcessor)javaListener));
      } catch (RemoteException e) {
	throw new G2AccessException(e, "While calling getClientListenerForG2JavaStubController for " + javaListener);
      }
    } else
      localMultiCaster.addElement(javaListener);

    if (!localMultiCaster.listening) {
      // Add a listener to the G2EventSource so the multicaster will receive events
      Object[] args = new java.lang.Object[] {localMultiCaster.g2proxy, adderMethodName, g2EventSource };
      g2Connection.callRPC(JgiAddProxyEventListener, args);
      localMultiCaster.listening = true;
    }


    return localMultiCaster.g2proxy;
  }

  /**
   * Return an Item that represents a G2 ITEM that is a proxy for a
   * Java Object added as a listener to an Event Source in G2.
   * If parentClass is not none then the G2 Proxy Class generated will be
   * managled, to not interfer with "offical" JLP Java Proxy classes.
   * If javaProxyClass is null, then an "offical" JLP G2 Java proxy class
   * will be assumed.
   *
   *@param g2Connection the G2 where to access the proxy.
   *@param javaProxyClass the G2 Class name, used to create an instance of a proxy
   * in the event that an existing proxy could not be found. Set null to
   * use the default G2 Class registered for the class of JavaObject.
   *@param g2ParentClass the G2 class created will inherit from this G2 Class
   *  set to the Symbol NONE to not parent from a specified class
   *@param javaObject the Java Object to create a proxy for.
   *@param eventSource the event source
   *@exception G2AccessException When there is a problem communicating with G2 or
   * a G2 Class could not be found to create the proxy ITEM
   */
  final Item getG2ProxyForJavaObjectAttachedToEventSource(final G2Connection g2Connection, 
		  final String javaProxyClass,
		  final Symbol g2ParentClass,
		  final Object javaObject,
		  final Item   eventSource)
       throws G2AccessException

  {
	String javaProxyClassName = javaProxyClass;
    // An Item is already a proxy if its not local
    if (javaObject instanceof Item && !((Item)javaObject).isItemLocal())
      return (Item)javaObject; 

    // Get the connection Registry for this connection
    ConnectionRegistry registryInfo = getConnectionRegistry(g2Connection);   

    // We are actually looking for a G2 Item that may already be associated 
    // with javaObject
    Item g2proxy = registryInfo.getG2ProxyForJavaObject(javaObject);

    if (g2proxy != null)
      return g2proxy; //resolved

    Symbol g2ProxyClassSym = null;
    if (!g2ParentClass.equals(NONE_))
      // Name of the G2 class used for the proxy is mangled, 
      // so as not to intefer with full import loading of this java class
      // via JavaLink professional
      g2ProxyClassSym = Symbol.intern("_AG2PROXYLISTENER_" + javaProxyClassName.toUpperCase());

    if (javaProxyClassName == null) {
      // If g2ProxyClass has not been specified then generate a class name that 
      // G2 would like us to use to send this object back to G2
      javaProxyClassName = javaObject.getClass().getName();
    }

    if (g2ProxyClassSym == null)
      g2ProxyClassSym = registryInfo.getG2ClassForJavaObject(javaObject);

    //if (g2proxyClass != null) System.out.println(g2proxyClass.toString());

    if (g2ProxyClassSym == null)
      throw new G2AccessException("No G2 Class Could be found to create a proxy for a" +
			      javaObject.getClass().getName());

    //Ensure that there is a compatible javalink version running on this connection
    registryInfo.ensureJavaLinkModuleVersionIsValid();
 
    // Ask G2 to create an instance of a specified class and return its proxy
    // if the parentG2Name is not None, it is assumed that we are creating
    // a proxy for a java class (named by java_or_g2_class_name), that is parented from
    // an existing G2 class (parentG2ClassName)
    // If the G2 Proxy class does not exist, it will be generated automatically in G2.
    Item newproxy =  
	(Item)g2Connection.callRPC(JgiCreateClassAndReturnProxyForEventSourceSymbol, 
			     new Object[] {g2ProxyClassSym, 
					   g2ParentClass, // parent class for the Proxy class
					   javaProxyClassName,
					   eventSource  } , 0);
    

    registryInfo.associate(newproxy, javaObject);

    return newproxy; //resolved    
  }


  /**
   * Remove a Java Object from listening for events from a G2 Event Source
   *
   *@param g2EventSource The G2 Item that the Java Object was listening too
   *@param removerMethodName The G2 Method name on G2EventSource for removing this listener
   *@param javaProxyClass The name of the Java listener class of which we where interested in
   *@param g2ParentClass The G2 class that the proxy class will inherit from in G2
   *@param javaListener The Java Listener object
   *@param The G2 ITEM Proxy that was used to listen for the G2 events. If NULL, then there is 
   *        no proxy listener to remove from the G2 Event Source Listener list. This may occur
   *        when MultiCast Listeners are dispatching events from the G2 Event Source. 
   *        (in which case this method is responsible for  removing the Java Listener from 
   *        receiving events from the Event MultiCaster).
   *
   */
   public synchronized Item removeJavaListenerFromG2EventSource(
						   Item g2EventSource,
						   Symbol removerMethodName,
						   String javaProxyClass,
						   Symbol g2ParentClass,
						   Object javaListener)
       throws G2AccessException {
    
    // Get the connection Registry for this connection
    ConnectionRegistry registryInfo = getConnectionRegistry(g2EventSource);
    G2Access g2Connection = registryInfo.g2connection; 

    // Have we created a proxy for this listener already ?
    LocalMultiCaster localMultiCaster = registryInfo.getMultiCaster(g2EventSource, g2ParentClass);

    if (localMultiCaster != null) {  
      if (javaListener instanceof RMIEventQueueProcessor) {
	try {
	  localMultiCaster.removeElement(((G2RMIAccess)g2Connection).
				       getClientListenerForG2JavaStubController((RMIEventQueueProcessor)javaListener));
	} catch (RemoteException e) {
	  throw new G2AccessException(e, "While calling getClientListenerForG2JavaStubController for " + javaListener);
	}
      }
      else
	localMultiCaster.removeElement(javaListener);

      // As there are no java objects left, return the g2proxy we are using to gather
      // these events, and  remove this from the G2 Event Source
      if (localMultiCaster.isEmpty()) {
	Object[] args = new java.lang.Object[] {localMultiCaster.g2proxy, removerMethodName, g2EventSource };
        g2Connection.callRPC(JgiRemoveProxyEventListener, args);
	localMultiCaster.listening = false;
	return localMultiCaster.g2proxy;
      }
    }
    // The multiCaster may already be listening, we dont want the MultiCaster g2proxy from
    // being removed from the G2 Event Source listener list.
    return null;
  }

  /**
   * Return an Item that represents a G2 ITEM that is a proxy for a
   * Java Object.
   * If parentClass is not none then the G2 Proxy Class generated will be
   * managled, to not interfer with "offical" JLP Java Proxy classes.
   * If javaProxyClass is null, then an "offical" JLP G2 Java proxy class
   * will be assumed.
   *
   *@param g2Connection the G2 where to access the proxy.
   *@param javaProxyClass the G2 Class name, used to create an instance of a proxy
   * in the event that an existing proxy could not be found. Set null to
   * use the default G2 Class registered for the class of JavaObject.
   *@param g2ParentClass the G2 class created will inherit from this G2 Class
   *  set to the Symbol NONE to not parent from a specified class
   *@param javaObject the Java Object to create a proxy for.
   *@exception G2AccessException When there is a problem communicating with G2 or
   * a G2 Class could not be found to create the proxy ITEM
   */
  final Item getG2ProxyForJavaObject(final G2Connection g2Connection, 
		  final String javaProxyClass,
		  final Symbol g2ParentClass,
		  final Object javaObject)
       throws G2AccessException

  {
	String javaProxyClassName = javaProxyClass;
    // An Item is already a proxy if its not local
    if (javaObject instanceof Item && !((Item)javaObject).isItemLocal())
      return (Item)javaObject; 

    // Get the connection Registry for this connection
    ConnectionRegistry registryInfo = getConnectionRegistry(g2Connection);   

    // We are actually looking for a G2 Item that may already be associated 
    // with javaObject
    Item g2proxy = registryInfo.getG2ProxyForJavaObject(javaObject);

    if (g2proxy != null)
      return g2proxy; //resolved

    Symbol g2ProxyClassSym = null;
    if (!g2ParentClass.equals(NONE_))
      // Name of the G2 class used for the proxy is mangled, 
      // so as not to intefer with full import loading of this java class
      // via JavaLink professional
      g2ProxyClassSym = Symbol.intern("_AG2PROXY_" + javaProxyClassName.toUpperCase());

    if (javaProxyClassName == null) {
      // If g2ProxyClass has not been specified then generate a class name that 
      // G2 would like us to use to send this object back to G2
      javaProxyClassName = javaObject.getClass().getName();
    }

    if (g2ProxyClassSym == null)
      g2ProxyClassSym = registryInfo.getG2ClassForJavaObject(javaObject);

    //if (g2proxyClass != null) System.out.println(g2proxyClass.toString());

    if (g2ProxyClassSym == null)
      throw new G2AccessException("No G2 Class Could be found to create a proxy for a" +
			      javaObject.getClass().getName());

    // No proxy so far, so get G2 to create us a proxy for this class
    Item newproxy = createG2ObjectAndReturnProxy(registryInfo, 
				 g2ProxyClassSym, // This is G2 Proxy class name
				 g2ParentClass,   // Optional parent class for the Proxy class
				 javaProxyClassName); // This is the Java class to create a proxy for

    registryInfo.associate(newproxy, javaObject);

    return newproxy; //resolved    
  }

  /**
   * Create a Java Array Class Instance, for a given G2 Class and specified size
   *
   * <P>Thie method will create a  new instance if a class previsouly downloaded
   * using <B>loadJavaClass</B>. The Java object created is then recorded as associated
   * with the g2 proxy.
   * <P>If an IllegalAccessException is thrown, the class may not be declared
   * public
   * 
   *@param g2proxy     Assumed to be a "by-handle" proxy for a G2 object wanting to
   *                   control a G2 object.
   *@param class_name  The class of the array type instance to create.
   *@param initialSize  The initial size of the array
   *@exception ClassNotFoundException If the Java class can not be found
   *@exception InstantiationException If a newInstance can be created of Java class
   *@exception IllegalAccessException If the runtime does not allow access to Java class instances
   *@exception NoSuchMethodException If newInstance on Java_class can not be found
   *@exception G2AccessException when a problem occurs as a result of communicating with G2.
   */
  void newArrayInstance(Item g2proxy, String java_class_name, int size)
       throws ClassNotFoundException, 
	 InstantiationException, 
	 IllegalAccessException,
	 NoSuchMethodException,
	 G2AccessException
  {
    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);

    // Try to create the Java object
    Object obj = downloader.newArrayInstance(java_class_name, size);

    // Register this G2 class as tied to the thing we have just created
    registryInfo.registerG2ClassWithJavaClass(g2proxy, java_class_name);

    // Record this instance and its relationship with the java instance
    // WARNING ONE-TO-ONE MAPPING
    registryInfo.associate(g2proxy, obj);

  }

  /**
   * Create a Java Array Class Instance, for a given G2 Class and specified dimensions
   *
   * <P>Thie method will create a  new instance if a class previsouly downloaded
   * using <B>loadJavaClass</B>. The Java object created is then recorded as associated
   * with the g2 proxy.
   * <P>If an IllegalAccessException is thrown, the class may not be declared
   * public
   * 
   *@param g2proxy     Assumed to be a "by-handle" proxy for a G2 object wanting to
   *                   control a G2 object.
   *@param class_name  The class of the array type instance to create.
   *@param dimensions  A Sequence of integers specifing the dimensions required
   *@exception ClassNotFoundException If the Java class can not be found
   *@exception InstantiationException If a newInstance can be created of Java class
   *@exception IllegalAccessException If the runtime does not allow access to Java class instances
   *@exception IllegalArgumentException If the dimensions sequence does not contain Integers
   *@exception com.gensym.util.MethodInvocationException when a problem occurs dynmically invoking newInstance
   *@exception G2AccessException when a problem occurs as a result of communicating with G2.
   */
  void newArrayInstanceWithDimensions(Item g2proxy, String java_class_name, Sequence dimensions)
       throws ClassNotFoundException, 
	 InstantiationException, 
	 IllegalAccessException,
         IllegalArgumentException,
	 NoSuchMethodException,
	 G2AccessException
  {
    ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);

    int length = dimensions.size();
    int[] dimensionsArray = new int[length];
    for (int i=0; i<length; i++) {
      Object dimension = dimensions.elementAt(i);
      if (dimension != null && dimension.getClass() == Integer.class) 
	dimensionsArray[i] = ((Integer)dimension).intValue();
      else
	throw new IllegalArgumentException("An invalid dimension specifier was found " + dimension +
					   ".Dimension specifiers must be integers");
    }

    // Try to create the Java object
    Object obj = downloader.newArrayInstance(java_class_name, dimensionsArray);

    // Register this G2 class as tied to the thing we have just created
    registryInfo.registerG2ClassWithJavaClass(g2proxy, java_class_name);

    // Record this instance and its relationship with the java instance
    // WARNING ONE-TO-ONE MAPPING
    registryInfo.associate(g2proxy, obj);

  }

  /**
   * @exception IllegalArgumentException If the specified object is not
   * an array
   * @exception ArrayIndexOutOfBoundsException If the specified index
   * argument is negative, or if it is greater than or equal to the
   * length of the specified array
   */
  Sequence getArrayElement(Item g2proxy, int pos)
    throws ArrayIndexOutOfBoundsException,
    IllegalAccessException,
    IllegalArgumentException,
    G2AccessException {
      
      ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);

      // Find the Java object associated with this g2proxy
      Object javaobj = registryInfo.getAssociatedJavaObject(g2proxy);

      if (javaobj == null)
	throw new IllegalAccessException(NoProxyExceptionString); 

      if (!javaobj.getClass().isArray()) {
	throw new IllegalArgumentException(g2proxy + " [proxy for " + javaobj + "] does not represent an array");
      }

      Object retval = Array.get(javaobj, pos);

      // And we must make sure that any Java objects are converted to G2 stubs
      // that may be embedded in any compound object structures that get sent back to G2
      retval = resolveJavaObjects(registryInfo, retval);
      Sequence retseq = new Sequence(1);
      retseq.addElement(retval);
      return retseq;
  }

  /**
   * @exception IllegalArgumentException If the specified object is not
   * an array
   * @exception ArrayIndexOutOfBoundsException If the specified index
   * argument is negative, or if it is greater than or equal to the
   * length of the specified array
   */
  void setArrayElement(final Item g2proxy, final int pos, final Object element)
    throws ArrayIndexOutOfBoundsException,
    IllegalAccessException,
    IllegalArgumentException,
    G2AccessException {
      
      ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);
      Object elementObj = element;
      // Find the Java object associated with this g2proxy
      Object javaobj = registryInfo.getAssociatedJavaObject(g2proxy);

      // Make sure that we dont have a element, that is actually G2 stubs for Java objects
      elementObj = resolveG2Stubs(registryInfo, javaobj, elementObj);

      if (javaobj == null)
	throw new IllegalAccessException(NoProxyExceptionString); 

      if (!javaobj.getClass().isArray()) {
	throw new IllegalArgumentException(g2proxy + " [proxy for " + javaobj + "] does not represent an array");
      }

      Array.set(javaobj, pos, elementObj);
  }

  /**
   * Copy the contents of the local array associated with g2proxy to the g2proxy
   * @exception IllegalArgumentException If the specified object is not
   * an array
   * @exception ArrayIndexOutOfBoundsException If the specified index
   * argument is negative, or if it is greater than or equal to the
   * length of the specified array
   */
  void getArrayContents(Item g2proxy)
    throws ArrayIndexOutOfBoundsException,
    IllegalAccessException,
    IllegalArgumentException,
    G2AccessException {
      
      ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);

      // Find the Java object associated with this g2proxy
      Object javaobj = registryInfo.getAssociatedJavaObject(g2proxy);

      if (javaobj == null)
	throw new IllegalAccessException(NoProxyExceptionString); 

      if (!javaobj.getClass().isArray()) {
	throw new IllegalArgumentException(g2proxy + " [proxy for " + javaobj + "] does not represent an array");
      }

      int length = Array.getLength(javaobj);
      Sequence retseq = new Sequence(length);
      for (int i=0; i<length; i++) {
	Object arrayVal = Array.get(javaobj, i);
	//we must make sure that any Java objects are converted to G2 stubs
	// that may be embedded in any compound object structures that get sent back to G2
	arrayVal = resolveJavaObjects(registryInfo, arrayVal);
	//System.out.println("getting " + arrayVal + " at " + i);
	retseq.addElement(arrayVal);
      }
      g2proxy.setPropertyValue(G2_ARRAY_SEQUENCE_,retseq);
  }

  /**
   * Set the local array contents to that of the g2proxy
   * @exception IllegalArgumentException If the specified object is not
   * an array
   * @exception ArrayIndexOutOfBoundsException If the specified index
   * argument is negative, or if it is greater than or equal to the
   * length of the specified array
   */
  void setArrayContents(Item g2proxy)
    throws ArrayIndexOutOfBoundsException,
    IllegalAccessException,
    IllegalArgumentException,
    com.gensym.util.NoSuchAttributeException,
    G2AccessException {
      
      ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);

      // Find the Java object associated with this g2proxy
      Object javaobj = registryInfo.getAssociatedJavaObject(g2proxy);

      if (javaobj == null)
	throw new IllegalAccessException(NoProxyExceptionString); 

      if (!javaobj.getClass().isArray()) {
	throw new IllegalArgumentException(g2proxy + " [proxy for " + javaobj + "] does not represent an array");
      }

      Sequence arraySequence = (Sequence)g2proxy.getPropertyValue(G2_ARRAY_SEQUENCE_);
      int size = arraySequence.size();
      for (int i=0; i<size; i++) {
	Object arrayElement = arraySequence.elementAt(i);
	// Make sure that we dont have any arguments, that are actually G2 stubs for Java objects
	arrayElement = resolveG2Stubs(registryInfo, javaobj, arrayElement);
	//System.out.println("setting " + arrayElement + " at  " + i);
	Array.set(javaobj, i, arrayElement);
      }
  }

  /**
   * Process incomming G2JavaStubController Events.
   */
  public void processG2JavaStubControllerEvent(G2JavaStubControllerEvent e) 
  throws NoSuchMethodException,
	 IllegalAccessException,
	 InstantiationException,
	 com.gensym.util.MethodInvocationException,
         G2AccessException,
	 RemoteException {
    //System.out.println(e + " " + e.getTarget() + " id" + e.getID() + " args " + e.getArgs());
    int id = e.getID();
    if (id == G2JavaStubControllerEvent.CALL_ASYNC_METHOD)
      callMethod(e.getTarget(),
		 e.getMethodName(),
		 e.getArgs());
    else if (id == G2JavaStubControllerEvent.DELETE_INSTANCE)
	   deleteInstance(e.getTarget());
  }

  /**
    * @undocumented
   */
  public static final String callG2ProxyFromJava_MethodName = "callG2ProxyFromJava";
  /**
   * @undocumented
   */
  public Object callG2ProxyFromJava(final G2Access context, final Symbol methodName, final Object[] javaParams) 
      throws G2AccessException {
    Object targetObj = null;
    Object[] javaParamArray = javaParams;
    // A method call, will have the first argument set to the item being called
    if (javaParamArray.length > 0)
      targetObj = javaParamArray[0]; 
    ConnectionRegistry registryInfo = getConnectionRegistry((G2Connection)context);
    javaParamArray = resolveJavaObjectsInObjectArray(registryInfo, javaParamArray);
    Object ret = context.callRPC(methodName, javaParamArray);
    return resolveG2Stubs(registryInfo, targetObj, ret);
  }

  /**
   * Try to convert a G2 Item to its associated java object (if any). The
   * ge Item is returned if no associated Java Object was found.
   */
  public Object resolveG2Stub(Item g2Object) throws G2AccessException {
    ConnectionRegistry registryInfo = getConnectionRegistry(g2Object);
    return resolveG2ItemStub(registryInfo, null, g2Object);
  }

  /**
   * Try to convert any embedded g2 stubs to java Objects
   */
  public Object resolveG2Stubs(G2Access connection, Object targetObj, Object obj) throws G2AccessException {
    ConnectionRegistry registryInfo = getConnectionRegistry((G2Connection)connection);
    return resolveG2Stubs(registryInfo, targetObj, obj);
  }

  /**
   * Try to convert any embedded g2 stubs to java objects
   * If any of you are wondering why we dont just override resolveG2Stubs for
   * each class we need to resolve...well there seems to be a VM feature/error in JDK1.1.
   * where once the object has been cast for a method parameter (in the call to resolveG2Stubs
   * it is cast to Object), the VM will then dispatch on the cast class, not the actual class !!!
   */
  private Object resolveG2Stubs(ConnectionRegistry registryInfo, Object targetObj, Object o) {

    if (o == null)
      return null;

    if (o instanceof Item)
      return resolveG2ItemStub(registryInfo, targetObj, (Item)o);
    else if (o instanceof Sequence)
      return resolveG2StubsInSequence (registryInfo, targetObj, (Sequence)o);
    else if (o instanceof Structure)
      return resolveG2StubsInStructure (registryInfo, targetObj, (Structure)o);
    else if (o instanceof Object[])
      return resolveG2StubsInObjectArray (registryInfo, targetObj, (Object[])o);
    else
      return o;
  }

  private Object resolveG2ItemStub (ConnectionRegistry registryInfo, Object targetObj, Item g2item) {

    // Look for any events objects and resolve them to their external event objects
    if (g2item instanceof G2_EventObject) {
      
      G2_EventObject g2Event = (G2_EventObject)g2item;
      Item source = g2item;
      G2_ExternalEventObjectRoot event = null;
      try {
	 event = 
	   G2_ExternalEventObjectRoot.createExternalEventObject(null, //read source from event
							       g2item, 
							      g2Event.getExternalEventClass());
      } catch (G2AccessException e) {
	throw new RuntimeException(e.toString());
      }
      //System.out.println("Resolve Event" + event + " source " + g2item);
      return event;
    }

    Symbol g2ClassName = null;
    try {
      g2ClassName =(Symbol)g2item.getPropertyValue(CLASS_);
    } catch (com.gensym.util.NoSuchAttributeException e) { Trace.exception(e); }
    catch (G2AccessException e) { Trace.exception(e); }

    // We are actually looking for any Items that may be associated with a
    // java object that was previously created
    Object java_object = registryInfo.getAssociatedJavaObject(targetObj, g2item);
    if (java_object == null) {
      String javaClass = registryInfo.getJavaClassForG2Class(g2ClassName);
      if (javaClass != null)
	throw new RuntimeException("Can find associated Java Object for " + 
				   g2item + "whose G2 Class was registered for Java Class " + javaClass);
      return g2item;  // leave it alone
    }
    else return java_object; // resolved
  }

  private Sequence resolveG2StubsInSequence (ConnectionRegistry registryInfo, 
					     Object targetObj, 
					     Sequence s) {
    if (s.isEmpty())
      return s;
    int i, numElts = s.size ();
    for (i=0; i<numElts; i++) {
      Object o = s.elementAt (i);
      s.setElementAt (resolveG2Stubs (registryInfo, targetObj, o), i);
    }
    return s;
  }

  private Structure resolveG2StubsInStructure (ConnectionRegistry registryInfo, 
					       Object targetObj, 
					       Structure s) {
    Enumeration keys = s.getAttributeNames ();
    Enumeration vals = s.getAttributeValues ();
    while (keys.hasMoreElements ()) {
      Symbol key = (Symbol) keys.nextElement ();
      Object val =  resolveG2Stubs(registryInfo, targetObj, vals.nextElement ());
      s.setAttributeValue (key, val);
    }
    return s;
  }

  private Object[] resolveG2StubsInObjectArray (ConnectionRegistry registryInfo, 
						Object targetObj, 
						Object[] oarray) {
    for (int i = 0; i<oarray.length; i++) {
      oarray[i] = resolveG2Stubs(registryInfo, targetObj, oarray[i]);
    }
    return oarray;
  }

  /**
   * Try to convert a Java Object to its asscoiated G2 Item accross a conneciton
   * (if any). If there was no association found, then the java_object is returned.
   */
  public Object resolveJavaObject(G2Access connection, Object java_object) 
       throws G2AccessException {
	 ConnectionRegistry registryInfo = getConnectionRegistry(connection);
	 return resolveJavaObject(registryInfo, java_object);
  }
    
  /**
   * Try to convert any embedded java objects to g2 stubs
   */
  private Object resolveJavaObjects(ConnectionRegistry registryInfo, Object o) 
       throws G2AccessException 
  {

    if (o == null)
      return null;

    if (o instanceof Sequence)
      return resolveJavaObjectsInSequence (registryInfo, (Sequence)o);
    else if (o instanceof Structure)
      return resolveJavaObjectsInStructure (registryInfo, (Structure)o);
    else if (o instanceof Object[])
      return resolveJavaObjectsInObjectArray (registryInfo, (Object[])o);
    else 
      return resolveJavaObject(registryInfo, o);
  }


  private Object resolveJavaObject (ConnectionRegistry registryInfo, Object java_object) 
       throws G2AccessException
  {

    // We are actually looking for any Items that may associated with a
    // java object that was previously created
    Item g2proxy = registryInfo.getG2ProxyForJavaObject(java_object);

    if (g2proxy == null)
      g2proxy = registryInfo.getG2ProxyForJavaObjectFromFactory(java_object);

    if (g2proxy != null)
      return g2proxy; //resolved

    // An Item is already a proxy if its not local
    if (java_object instanceof Item && !((Item)java_object).isItemLocal())
      return (Item)java_object; 

    // May be there is a class that the G2 would like us to use to send this object back to G2
    Symbol g2proxyClass = registryInfo.getG2ClassForJavaObject(java_object);

    //System.out.println(g2proxyClass);
    

    if (g2proxyClass == null)
      return java_object;  // leave
    else {


      // G2 has told us which class to create, so get it to create us a proxy for this class
      Item newproxy = createG2ObjectAndReturnProxy(registryInfo, 
						  g2proxyClass, 
						  Symbol.intern("NONE"),
						  java_object.getClass().getName() );
      registryInfo.associate(newproxy, java_object);

      return newproxy; //resolved    
    }
  }


  private Item createG2ObjectAndReturnProxy(ConnectionRegistry registryInfo, 
					   Symbol g2_class_name, 
					   Symbol parentG2ClassName,
					   String java_class_name) throws G2AccessException {
   
    G2Access g2Connection = registryInfo.g2connection;

    //Ensure that there is a compatible javalink version running on this connection
    registryInfo.ensureJavaLinkModuleVersionIsValid();
 
    // Ask G2 to create an instance of a specified class and return its proxy
    // if the parentG2Name is not None, it is assumed that we are creating
    // a proxy for a java class (named by java_or_g2_class_name), that is parented from
    // an existing G2 class (parentG2ClassName)
    // If the G2 Proxy class does not exist, it will be generated automatically in G2.
    return 
	(Item)g2Connection.callRPC(JgiCreateClassAndReturnProxySymbol, 
			     new Object[] {g2_class_name, parentG2ClassName, java_class_name} , 0);
  }

  private Sequence resolveJavaObjectsInSequence (ConnectionRegistry registryInfo, Sequence s) 
       throws G2AccessException
  {
    if (s.isEmpty())
      return s;
    int i, numElts = s.size ();
    for (i=0; i<numElts; i++) {
      Object o = s.elementAt (i);
      s.setElementAt (resolveJavaObjects (registryInfo, o), i);
    }
    return s;
  }

  private Structure resolveJavaObjectsInStructure (ConnectionRegistry registryInfo, Structure s) 
       throws G2AccessException
  {
    Enumeration keys = s.getAttributeNames ();
    Enumeration vals = s.getAttributeValues ();
    while (keys.hasMoreElements ()) {
      Symbol key = (Symbol) keys.nextElement ();
      Object val =  resolveJavaObjects(registryInfo, vals.nextElement ());
      s.setAttributeValue (key, val);
    }
    return s;
  }

  private Object[] resolveJavaObjectsInObjectArray (ConnectionRegistry registryInfo, Object[] oarray) 
       throws G2AccessException 
  {
    for (int i = 0; i<oarray.length; i++) {
      oarray[i] = resolveJavaObjects(registryInfo, oarray[i]);
    }
    return oarray;
  }


  /**
   * Get a registry info object for a g2Proxy
   */
  private ConnectionRegistry getConnectionRegistry(Item g2proxy) throws G2AccessException
  {
    
    // Try to find the connection class tables for this g2proxy
    G2Access g2connection = ((ImplAccess)g2proxy).getContext();

    if (g2connection == null)
      throw new G2AccessException(
	 "No G2 connection for G2 proxy, G2 proxies for Java objects must have a valid g2 connection");

    ConnectionRegistry registryInfo = (ConnectionRegistry)connectionsTable.get(g2connection);

    if (registryInfo == null)
      registryInfo = new ConnectionRegistry(g2connection);

    connectionsTable.put(g2connection, registryInfo);

    return registryInfo;

  }

  /**
   * Get a registry info object for a connection
   */
  private ConnectionRegistry getConnectionRegistry(G2Connection g2Connection)
  {
    return getConnectionRegistry((G2Access)g2Connection);
  }

  /**
   * Get a registry info object for a connection
   */
  private ConnectionRegistry getConnectionRegistry(G2Access g2Connection)
  {
    ConnectionRegistry registryInfo = (ConnectionRegistry)connectionsTable.get(g2Connection);
    
    if (registryInfo == null)
      registryInfo = new ConnectionRegistry(g2Connection);
    
    connectionsTable.put(g2Connection, registryInfo);
    
    return registryInfo;

  }

  /**
   * Remove a connection from the registry
   */
  private void removeConnectionRegistry(G2Access g2Connection) {
    connectionsTable.remove(g2Connection);
  }

  // Because we are using reflection, we must find out
  // if the arg types are actually arg types
  private Class[] getArgClassesAndResolve(ConnectionRegistry registryInfo, 
					  Object targetObj,
					  Sequence args) throws G2AccessException {
    int size = args.size();
    Class argClasses[] = new Class[size]; 

    for (int i = 0; i < size; i++) {
      Object arg = args.elementAt(i);
      try {
	Class newParamClass = null;
	Class origParamClass = arg.getClass();
	if (arg instanceof Item) {
	  Symbol g2ClassName = null;
	  g2ClassName =(Symbol)(((Item)arg).getPropertyValue(CLASS_)); // we need the interface name
	  newParamClass = G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);
	} else {
	  newParamClass = G2ClassTranslator.getJavaTypeForG2WrappedPrimitive(origParamClass);
	}
	if (arg instanceof Item) {
	  Object newarg = resolveG2Stubs(registryInfo, targetObj, arg);
	  if (newParamClass != null) 
	  // The G2 arg indicated a Java Type
	    argClasses[i] = newParamClass;
	  else 
	    // We must recheck the class, as a G2 arg may have been resolved into a java object.
	    argClasses[i] = newarg.getClass();
	  args.setElementAt(newarg, i);
	} else if (newParamClass != null)
	  // The G2 arg indicated a  primitive
	    argClasses[i] = newParamClass;
	else
	  argClasses[i] = origParamClass;
	//System.out.println("Selecting param " + argClasses[i] + " for " + origParamClass);
      } catch (com.gensym.util.NoSuchAttributeException e) { 
	throw new G2AccessException("Could not find G2 attribute " + e.getMessage() + "\n  G2proxy was " + arg);
      }
    }
    //System.out.println(args);
    return argClasses;
  }

  private Object getJavaTypeObjectForG2Type(Item g2proxy) {

    try {
      Symbol g2ClassName =(Symbol)g2proxy.getPropertyValue(CLASS_);

      Class knownType = G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);
      if (knownType != null) {
	Class paramClass = knownType;
	Object val = g2proxy.getPropertyValue(VAL_); 

	if (paramClass == Long.TYPE) 
	  // G2 object wil be a string with the digits
	  val = Long.valueOf((String)val);
	else if (paramClass == Integer.TYPE)
	  val = Integer.valueOf((String)val);
	else if (paramClass == Float.TYPE)
	  // JavaLink will send G2 Floats as Doubles
	  val = Float.valueOf(((Double)val).floatValue());
	else if (paramClass == Byte.TYPE)
	  // Val will be an Integer
	  val = Byte.valueOf(((Integer)val).byteValue());
	else if (paramClass == Short.TYPE)
	  // Val will be an Integer
	  val = Short.valueOf(((Integer)val).shortValue());
	else if (paramClass == Character.TYPE)
	  if (val instanceof String) {
	    // Val will be a String from G2
	    if (((String)val).length() < 1)
	      val = Character.valueOf(' ');
	    else
	      val = Character.valueOf(((String)val).charAt(0));
	  }
	//System.out.println("Made " + val + " " + val.getClass() + " for " + g2proxy);

	return val;
      }
    } catch (com.gensym.util.NoSuchAttributeException e) { 
      throw new RuntimeException("Could not find G2 attribute " + e.getMessage() + "\n  g2proxy was " + g2proxy);
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
    return null;
  }




  /**
   * Inner Class to contain g2proxy<>javaobject registration for a particular connection
   */
  class ConnectionRegistry extends G2ConnectionAdapter {

    private Hashtable registeredG2Classes = new Hashtable(21);
    private Hashtable registeredJavaClasses = new Hashtable(21);
    private Hashtable controlledJavaObjects = new Hashtable(21);
    private Hashtable associatedG2Proxies = new Hashtable(21);
    private Hashtable registeredMethodTables = new Hashtable(11);
    // Table of MultiCasters for a g2proxy
    private Hashtable associatedG2ProxyMultiCasters = new Hashtable(20);
    private JavaObjectForG2ItemFactory javaObjectForG2ItemFactory = null;
    private G2ClassForJavaObjectFactory g2ClassForJavaObjectFactory = null;
    private G2ItemForJavaObjectFactory g2ItemForJavaObjectFactory = null;

    G2Access g2connection = null;

    ConnectionRegistry(G2Access g2connection)
    {
      this.g2connection = g2connection;
      if (javaObjectForG2ItemFactory == null)
	// Default factory, creates listener adapters for G2 objects that implemet listener interfaces
	setJavaObjectForG2ItemFactory(new G2JavaListenerProxyAdapterFactory());
      g2connection.addG2ConnectionListener(this);
    }

    @Override
    public void g2ConnectionClosed(G2ConnectionEvent e) {
      synchronized(this) {
	removeConnectionRegistry(g2connection);
	g2connection.removeG2ConnectionListener(this);
	g2connection = null;
	controlledJavaObjects.clear();
	associatedG2Proxies.clear();
	registeredMethodTables.clear();
      }
    }

    /**
     * Record a G2 class, as representing a Java class for a particular context
     */
    final void registerG2ClassWithJavaClass(Item g2proxy, String java_class_name)
	 throws G2AccessException
    {  
      //System.out.println("registerG2ClassWithJavaClass" + g2proxy.getG2ClassName() + "," + java_class_name);
      Symbol g2Class = g2proxy.getG2ClassName();
      String javaClassName = java_class_name.intern();
      registeredG2Classes.put(javaClassName, g2Class);
      registeredJavaClasses.put(g2Class, javaClassName);
    }

    /** 
     * record G2 classes, as representing Java classes for a particular context
     */
    final void registerG2ClassWithJavaClass(Structure registerG2ClassInfo)
    {  
    	 return;
      /*
       * This code is currently unused but still might be needed in future.
       * for (Enumeration e=registerG2ClassInfo.getAttributeNames(); e.hasMoreElements(); ) {
	Symbol g2Class = (Symbol)e.nextElement();
	{
	  if (registeredJavaClasses.get(g2Class) == null) {
	  
	    String javaClassName = (String)registerG2ClassInfo.getAttributeValue(g2Class, null);
	    //System.out.println("registerG2ClassWithJavaClass" + g2Class + "," + javaClassName);
	    if (javaClassName != null) {
	      javaClassName = javaClassName.intern();
	      registeredG2Classes.put(javaClassName, g2Class);
	      registeredJavaClasses.put(g2Class, javaClassName);
	    }
	  }
	}
      }*/
    }

    /**
     * Record a G2 proxy instance which is now associated with a java object.
     */
    final synchronized void associate(Item g2proxy, Object java_object)
    {
      //System.out.println("associate" + g2proxy + "," + java_object);
      controlledJavaObjects.put(g2proxy, java_object);
      associatedG2Proxies.put(java_object, g2proxy);
    }

    /**
     * Get Java object associated with a G2 proxy.
     */
    final Object getAssociatedJavaObject(Item g2proxy) {
      return getAssociatedJavaObject(null, g2proxy);
    }

    /**
     * Get Java object associated with a G2 proxy. Traget object known
     */
    final Object getAssociatedJavaObject(Object targetObj, Item g2proxy)
    {
      //System.out.println("getAssociatedJavaObject" + g2proxy.toString());
      Object java_object = controlledJavaObjects.get(g2proxy);
      if (java_object == null){
    	  java_object = getJavaTypeObjectForG2Type(g2proxy);
      }
      //System.out.println("associated " + java_object + " " + javaObjectForG2ItemFactory);
      if (java_object == null && javaObjectForG2ItemFactory != null)
	java_object = javaObjectForG2ItemFactory.getJavaObjectForG2Item(g2connection,
									targetObj,
									g2proxy);
      return (java_object == null ? g2proxy : java_object);
    }

    /**
     * Get G2 proxy associated with a java object.
     */
    final synchronized Item getG2ProxyForJavaObject(Object java_object)
    {

      //System.out.println("getG2ProxyForJavaObject" + java_object.toString());
      Item g2proxy = (Item)associatedG2Proxies.get(java_object);
      if (g2proxy != null) {
	if (g2proxy.isValid())
	  return g2proxy;
	else
	  removeAssociation(g2proxy);
      }
      return null;
    }

    /**
     * Get G2 proxy associated with a java object, if no Item already associated
     * check the external G2ItemForJavaObject factory if set.
     */
    final Item getG2ProxyForJavaObjectFromFactory(Object java_object) throws G2AccessException
    {
      Item proxy = null;
      if (g2ItemForJavaObjectFactory != null)
	proxy = g2ItemForJavaObjectFactory.getG2ItemForJavaObject(g2connection, java_object);
      return proxy;
    }

    /**
     * Get a G2 proxy class for a given G2 Class java object.
     */
    final Symbol getG2ClassForJavaObject(Object java_object)
    {
      //System.out.println("g2G2ClassForJavaClass" + java_object.toString());
      if (java_object == null)
	return null;
      Class javaClass = java_object.getClass();
      String javaClassName = javaClass.getName().intern();
      Symbol g2ClassName = (Symbol)registeredG2Classes.get(javaClassName);
      if (g2ClassName == null) {

	// Try to make up a name using our knownledge of JavaLink mapping
	// and how java stubs are imported into G2
	if (!G2ClassTranslator.isJavaClassHandledByJavaLinkOnReturnToG2(javaClass)) {
	  if (g2ClassForJavaObjectFactory != null)
	    g2ClassName = g2ClassForJavaObjectFactory.getG2ClassForJavaObject(g2connection, java_object);
	  if (g2ClassName == null)
	    g2ClassName = G2ClassTranslator.createG2NameFromJavaName(javaClassName);
	  registeredG2Classes.put(javaClassName, g2ClassName);
	  registeredJavaClasses.put(g2ClassName, javaClassName);
	}
      }
      return g2ClassName;
    }

    /**
     * Get any Java class name associated with a G2 class name
     */
    final String getJavaClassForG2Class(Symbol g2ClassName)
    {
      return (String)registeredJavaClasses.get(g2ClassName);
    }

    /**
     * Remove a G2 proxy association with a java_object
     */
    final Object removeAssociation(Item g2proxy)
    {
      // Look up any MultiCasters we may be using for this object
      Hashtable proxyMultiCasterHash = (Hashtable)associatedG2ProxyMultiCasters.remove(g2proxy);
      if (proxyMultiCasterHash != null)
	proxyMultiCasterHash.clear();

      Object java_object = controlledJavaObjects.remove(g2proxy);
      if (java_object != null) {
	if (java_object instanceof LocalMultiCaster)
	  ((LocalMultiCaster)java_object).disable();
	associatedG2Proxies.remove(java_object);

	// Loose any reference to the objects class, if we are removing the last 
	// association with such a class
	//Class clazz = java_object.getClass();
	//boolean foundClass = false;
	//for (Enumeration e = associatedG2Proxies.keys(); e.hasMoreElements();) {
	//  if (e.nextElement().getClass() == clazz) {
	//    foundClass = true;
	//    break;
	//  } // Another proxy for this class
	//}
	//if (!foundClass) registeredMethodTables.remove(clazz);
      }
      
      return java_object;
    }
      

    /**
     * Set an optional factory that can provide java objects that represent G2 Items
     * when the controller can not find an association between a G2 item and a Java object.
     */
    void setJavaObjectForG2ItemFactory(JavaObjectForG2ItemFactory factory) {
      javaObjectForG2ItemFactory = factory;
    }

    /**
     * Set an optional factory that can provide G2 class names for a given Java object
     * when the controller can not find an G2 class name for the proxy for a Java object
     */
    void setG2ClassForJavaObjectFactory(G2ClassForJavaObjectFactory factory) {
      g2ClassForJavaObjectFactory = factory;
    }

    /**
     * Set an optional factory that can provide G2 Item for a given Java object
     * when the registry can not find an association from a Java object to a G2 Item
     */
    void setG2ItemForJavaObjectFactory(G2ItemForJavaObjectFactory factory) {
      g2ItemForJavaObjectFactory = factory;
    }
    
    final LocalMultiCaster getMultiCaster(Item g2Proxy, Symbol g2ClassName) {
      Hashtable proxyMultiCasterHash = (Hashtable)associatedG2ProxyMultiCasters.get(g2Proxy);
      if (proxyMultiCasterHash == null){
    	  return null;
      }

      LocalMultiCaster classMultiCaster = (LocalMultiCaster)proxyMultiCasterHash.get(g2ClassName);
      return classMultiCaster;
    }

    final void setMultiCaster(Item g2Proxy, Symbol g2ClassName, LocalMultiCaster multiCaster) {
      Hashtable proxyMultiCasterHash = (Hashtable)associatedG2ProxyMultiCasters.get(g2Proxy);
      if (proxyMultiCasterHash == null) {
	proxyMultiCasterHash = new Hashtable();
	associatedG2ProxyMultiCasters.put(g2Proxy, proxyMultiCasterHash);
      }

      proxyMultiCasterHash.put(g2ClassName, multiCaster);
    }

    final void registerMethod(Class javaProxyClass, Item g2Method, Method method) {
      Hashtable registeredMethodsTableForProxyClass = 
	(Hashtable)registeredMethodTables.get(javaProxyClass);
      if (registeredMethodsTableForProxyClass == null) {
	registeredMethodsTableForProxyClass = new Hashtable(11);
	registeredMethodTables.put(javaProxyClass, registeredMethodsTableForProxyClass );
      }
      registeredMethodsTableForProxyClass.put(g2Method, method);
    }

    final Method lookupMethod(Class javaProxyClass, Item g2Method) {
      Hashtable registeredMethodsTableForProxyClass = 
	(Hashtable)registeredMethodTables.get(javaProxyClass);
      if (registeredMethodsTableForProxyClass == null){
    	  return null;
      }
      return (Method)registeredMethodsTableForProxyClass.get(g2Method);
    }

    private boolean versionCheckedAndOK = false;

    final void ensureJavaLinkModuleVersionIsValid() throws G2AccessException {
      if (!versionCheckedAndOK) {
	String hostName = g2connection.g2GetHostName();
	String portName = g2connection.g2GetPortNumberOrName();
	String versionString = "";
	try {
	versionString = (String) g2connection.callRPC 
	                     (JGI_GET_JAVALINK_MODULE_VERSION_, new Object[] {});
	} catch (G2AccessException e) {
	  Trace.exception (e);
	  throw new G2AccessException("Could not read the current JavaLink Module version loaded into the G2 @(" +
				      hostName + ":" + portName + "). " +
				      " G2 must be started and you must upgrade/load the JavaLink Module Version " + 
				      JAVALINK_MINIMUM_VERSION_STRING + " or later into this G2.");
	}
	G2Version version = new G2Version (versionString);
	G2Version minimumVersion = JAVALINK_MINIMUM_VERSION;
	  if (version.compareTo (minimumVersion) < 0) {
	     versionCheckedAndOK = false;
	       throw new G2AccessException ("JavaLink Module KB Version mismatch. " +
					    " You must upgrade the JavaLink Module loaded into the G2 @(" + 
					    hostName + ":" + portName + ") to at least version " + 
					    JAVALINK_MINIMUM_VERSION_STRING  + ".\n(" + version + 
					    " is older than minimum required version " + minimumVersion + " )");
	  } else
	    versionCheckedAndOK = true;
      }
    }

  } // inner class ConnectionResgistry


  // Inner class holding listeners for Multicast events
  class LocalMultiCaster extends Vector {
    Item g2proxy;  // The g2 proxy we are using to receive events
    G2Connection g2Connection; 
    boolean listening = false;

    void listenerError(Object listener, Exception e) throws G2AccessException {
      removeElement(listener);
      g2Connection.reportLogBookErrorMessage(
					     Symbol.intern("G2-EVENT-MULTICAST-ERROR"), 
					     "Exception thrown while sending G2 Event to " + listener +
					     "from " + g2proxy + 
					     "\n Events will no longer be sent to this object" +
					     "\n Exception was " + e.toString());
      // If there has been a listener error and we have no listeners left...
      // If the listeners are in trouble (i.e. RMI client disconnects), they may not be able to remove themselves
      // we therfore delete the g2proxy for our multicaster, so its not "left' in G2.
      if (elementCount == 0) {
	g2Connection.callRPC(JgiRemoveProxyAssociation, new Object[] {g2proxy});
	// Ensure that we re-ask G2 for the proxy if we re-use this multicaster
	// In the case of a Multicaster on the G2 side, the proxy may not be deleted
	ConnectionRegistry registryInfo = getConnectionRegistry(g2proxy);
	registryInfo.removeAssociation(g2proxy);
	disable();
      }
    }

    void disable() {
      g2proxy = null;
      listening = false;
    }
  }
}



