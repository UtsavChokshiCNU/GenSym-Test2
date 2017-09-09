
package com.gensym.util;

import java.lang.reflect.Constructor;
import java.util.Hashtable;
import com.gensym.classes.G2__BaseImpl;
import com.gensym.classes.Item;
import com.gensym.classes.G2_ProxyObject;
import com.gensym.jgi.download.ClassInvalidationEvent; 
import com.gensym.jgi.download.ClassInvalidationListener; 
import com.gensym.jgi.download.G2StubFactory; 
import com.gensym.jgi.download.StubClassLoader;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import java.util.Locale;
import java.lang.reflect.InvocationTargetException;
import com.gensym.message.*;
import com.gensym.message.Trace;

abstract public class DefaultStubFactory implements G2StubFactory {

  // Tracing stuff
  static private MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.util.stubs",
			   DefaultStubFactory.class);
  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.util.TraceMessages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;

  static private Resource i18n =
  Trace.getBundle("com.gensym.util.Messages", Locale.getDefault());

  // Fields
  private StubClassLoader loader;
  private G2Access loaderContext;
  private Object[] initargs = new Object[3];
  private Hashtable loaderTable = new Hashtable (11);
  private Hashtable loadedClasses = new Hashtable (101);
  private Class[] params = {G2Access.class, Integer.TYPE, Structure.class};
  private Hashtable loadedTables = new Hashtable (11);

  public DefaultStubFactory (G2Access nativeCxn) {
    setupClassLoader (nativeCxn);
    loader.addClassInvalidationListener (new ConstructorDecacher ());
    loaderContext = nativeCxn;
  }

  private void setupClassLoader (G2Access nativeCxn) {
    loader = new StubClassLoader (nativeCxn);
  }

  /**
   * Returns a new or cached stub for a g2 item. The item
   * is uniquely identified by its handle and context.
   */
  @Override
  public /*synchronized*/ Item createG2Stub (Symbol g2ClassName,
					     int handle,
					     G2Access context,
					     Structure attributes)
 {

    //System.out.println ("In DefaultStubFactory::createG2Stub");
    //System.out.println ("Lock acquired by Thread " + Thread.currentThread ());

    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "createStub",
		g2ClassName, new Integer (handle));
    
    
    long t0 = System.currentTimeMillis();
    //System.out.println("******" + handle + "(handle) " + g2ClassName);
    // If we have a handle, then we may already have a stub for this object
    if (handle != 0)
      {
	Hashtable stubTable = (Hashtable) loadedTables.get (context);
	if (stubTable == null)
	  loadedTables.put (context, stubTable = new Hashtable (201));
	Integer handleKey = new Integer (handle);
	Item previouslyLoadedItem = (Item)stubTable.get (handleKey);

	if (previouslyLoadedItem == null) {
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "stubNotCached", handleKey);
	  previouslyLoadedItem = forceStubCreation (g2ClassName, handle, context, attributes);
	  stubTable.put (handleKey, previouslyLoadedItem);
	} else {
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "stubCached", handleKey);
	}
	//System.out.println ("Exiting createG2Stub. Releasing lock in thread" + Thread.currentThread ());
	//System.out.println("******" + handle + "(handle) createStub took " + (System.currentTimeMillis() - t0) + " " + g2ClassName);
	return previouslyLoadedItem;
      }
    else // by copy, will always create a new stub
      return forceStubCreation (g2ClassName, handle, context, attributes);
  }

  private /*synchronized*/ Item forceStubCreation (Symbol g2ClassName,
						   int handle,
						   G2Access context,
						   Structure attributes)
  {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterForceStub", g2ClassName);
    if (true) {
    Constructor stubClassConstructor;
    String stubClassName = "Who Knows?";
    if ((stubClassConstructor = (Constructor)loadedClasses.get (g2ClassName)) == null) {
      try {
	// check interface is available
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "attmptIntfLoad", g2ClassName);
	Class  interfaceClass = loader.loadClass (g2ClassName, true);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finIntfLoad", interfaceClass);

	Symbol g2StubClassName = g2ClassName;
	if (G2_ProxyObject.class.isAssignableFrom(interfaceClass)) {
	  g2StubClassName = getG2ClassNameForG2ProxyClass(interfaceClass);
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "attmptIntfLoad", g2ClassName);
	  interfaceClass = loader.loadClass (g2StubClassName, true);
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finIntfLoad", interfaceClass);
	}  
	
	// map to implementation class
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "attmptStubLoad", g2ClassName);
	Class  stubClass      = loader.loadClass (g2StubClassName, false);
	try { // This is here due to a strange problem with the JDK1.1.6 JIT
	  // The use of the Constructor with args, later on would fail, if we dont
	  // create a dummy instance here !
	  stubClass.newInstance ();
	} catch (Exception e) {
	  Trace.exception (e);
	}
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finStubLoad", stubClass);
	
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "attmptGetConst");
	loadedClasses.put (g2ClassName, stubClassConstructor = stubClass.getConstructor (params));
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finGetConst", stubClassConstructor);
	stubClassName = stubClass.toString ();
	
      } catch (NoSuchMethodException nsme) {
	// Trace
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "missingConst",
		    g2ClassName, nsme);
	Trace.exception (nsme, "Missing constructor : ->");
      }
      
    }
    
    initargs[0] = context;
    initargs[1] = new Integer (handle);
    initargs[2] = attributes;
    Item stub = null;
    try {
      stub = (Item) stubClassConstructor.newInstance (initargs);
      ((G2__BaseImpl)stub).setInternalG2ClassName(g2ClassName);
    } catch (java.lang.reflect.InvocationTargetException ite) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedStubCrtnErr", ite);
      Trace.exception (ite, null);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedStubCrtnErr",ite.getTargetException ());
      Trace.exception (ite.getTargetException (), "While invoking constructor on class: " + stubClassName);
      throw new RuntimeException (ite.toString () + ite.getTargetException ().toString());
    } catch (IllegalAccessException iae) {//Trace
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedStubCrtnErr", iae);
      throw new RuntimeException (iae.toString ());
    } catch (InstantiationException ie) {//Trace
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedStubCrtnErr", ie);
      throw new RuntimeException (ie.toString ());
    }
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "createdStub", stub);
    return stub;
    }


    //ItemImpl i = new ItemImpl (context, handle, attributes);
    if (false) {
    String stubClassName = "hello"; //generateStubClassName (g2ClassName);
    //System.out.println ("Will try to create : " + stubClassName);
    try {
      Class stubClass = Class.forName ("com.gensym.classes." + stubClassName);
      //System.out.println ("Got stub class : " + stubClass);
      Constructor stubClassConst = stubClass.getConstructor (params);
      //System.out.println ("Got stub class constuctor : " + stubClassConst);
      Item i = (Item)stubClassConst.newInstance (new Object[] {context, new Integer (handle), attributes});
      //System.out.println ("Created stub : " + i);
      return i;
    } catch (Exception e) {
      System.err.println ("Error in DefaultStubFactory.createG2Stub () ->" + e);
      if (e instanceof InvocationTargetException) {
	Throwable t = ((InvocationTargetException)e).getTargetException ();
	System.err.println ("Actual problem -> " + t);
      }
      throw (RuntimeException)e;
    }
    }
    throw new RuntimeException ("Java's last reachable statement check is broken!");
  }

  /** Returns the StubClassLoader for this factory */
  @Override
  public StubClassLoader getStubClassLoader () {
    return loader;
  }

  /**
   * Handles the invalidation of the stub in the context
   * by removing the stub from the cache.
   */
  @Override
  public void invalidateG2Stub (int handle,
				G2Access context) {
    //System.out.println ("DefaultStubFactory.invalidateG2Stub (" + handle + ")");
    Hashtable stubTable = (Hashtable) loadedTables.get (context);
    Integer handleKey = new Integer (handle);
    java.lang.Object stub = stubTable.remove (handleKey);
    //System.out.println ("Removed Stub = " + stub);
    ((com.gensym.classes.G2__BaseImpl)stub).dispose ();
  }

  /**
   * Lookup a stub using its handle, null if there is no stub for a given handle
   */
  @Override
  public Item getG2StubForHandle(int handle, 
				 G2Access context) {
    Hashtable stubTable = (Hashtable) loadedTables.get (context);
    Integer handleKey = new Integer (handle);
    return (Item)stubTable.get (handleKey);
  }

  private Symbol getG2ClassNameForG2ProxyClass(Class g2ProxyClass) {

    try {
      String fieldName = StubClassLoader.g2ProxyTagInterfaceRealClassFieldName;
      java.lang.reflect.Field f = g2ProxyClass.getField (fieldName);
      return (Symbol)f.get (null);
    } catch (Exception e) {
      // this should not happen
      throw new InternalError("Can not find realG2ClassName on G2Proxy Interface Stub," + e.toString());
    }
  }

  /**
   * Invalidates the stub class loader for a connection (maybe a connection has died).
   */
  @Override
  public void invalidateStubClassLoader(G2Access context) {
    // This is a hack solution for now, as we only have one
    // StubClassLoader created, the first time a stub is required
    // To be Changed (mdg, vkp)
    if (context == loaderContext) {
      loader = null;
      loaderContext = null;
      loadedClasses.clear ();
      loadedTables.clear ();
    }
  }

  /**
   * Makes sure that a G2 class has been loaded
   * This is used to get class information without having
   * an instance of the class
   * @undocumeted
   */
  public com.gensym.classes.G2Definition getOrLoadDefinition (Symbol g2ClassName_) throws G2AccessException {
    loader.loadClass (g2ClassName_, true);
    return loaderContext.getClassManager().getDefinition (g2ClassName_);
  }

  /**
   * This listener is used to clear out our cache of constructors
   * when the classes become invalid. This happens when we are
   * using alternate classes and somebody flips into generation
   * mode to actually generate the classes
   */
  class ConstructorDecacher implements ClassInvalidationListener {
    @Override
    public void classesInvalidated (ClassInvalidationEvent cie) {
      Symbol[] invalidClasses = cie.getInvalidClasses ();
      System.out.println ("Classes invalidated -> " +
			  com.gensym.core.DebugUtil.printArray (invalidClasses));
      for (int i=0; i<invalidClasses.length; i++) {
	loadedClasses.remove (invalidClasses[i]);
      }
    }
  }

}
