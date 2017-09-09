
package com.gensym.jgi.download;

import java.lang.reflect.Constructor;
import java.util.Hashtable;
import java.util.Locale;

import com.gensym.core.IntHashtable;
import com.gensym.classes.G2__BaseImpl;
import com.gensym.classes.Item;
import com.gensym.classes.G2_ProxyObject;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.message.Trace;

public class DefaultStubFactory implements G2StubFactory {

  // Tracing stuff
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.download.stubs",
			   DefaultStubFactory.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.download.TraceMessages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;

  private static Resource i18n =
  Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());

  // Fields
  private StubClassLoader loader;
  private G2Access loaderContext;
  private Object[] initargs = new Object[5];
  private Object[] oldinitargs = new Object[3];
  private Hashtable loaderTable = new Hashtable (11);
  private Hashtable loadedClasses = new Hashtable (101);
  private Hashtable constructorStatus = new Hashtable (101);
  private static Class[] params = {G2Access.class, Integer.TYPE, Integer.TYPE, G2__BaseImpl.class, Structure.class};
  private static Class[] priorparams = {G2Access.class, Integer.TYPE, Structure.class};
  private IntHashtable stubTable = new IntHashtable (211);
  private IntHashtable previousVersionTable = new IntHashtable (211);
  private IntHashtable deletedIndexTable = new IntHashtable (211); // version # for each handle

  private static final String NO_SUCH_CLASS_ERROR_TEXT = "NO-SUCH-CLASS-ERROR";

  public DefaultStubFactory (G2Access nativeCxn) {
    loader = new StubClassLoader (nativeCxn);
    loader.addClassInvalidationListener (new ConstructorDecacher ());
    loaderContext = nativeCxn;
  }

  /**
   *
   */
  @Override
  public Item checkExistingStub (int handle, int handleVersion) {
    if (handle == 0)
      return null;
    Item itm = (Item) stubTable.get (handle);
    if (itm != null && ((G2__BaseImpl)itm).getHandleVersion () == handleVersion)
      return itm;
    itm = (Item) previousVersionTable.get (handle);
    if (itm != null && ((G2__BaseImpl)itm).getHandleVersion () == handleVersion)
      return itm;
    return null;
  }

  @Override
  public int getVersionForHandle (int handle) {
    Integer previousVersion = (Integer) deletedIndexTable.get (handle);
    int handleVersion;
    if (previousVersion == null)
      handleVersion = 0;
    else
      handleVersion = previousVersion.intValue () + 1;
    return handleVersion;
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

    //System.out.println ("In DefaultStubFactory::createG2Stub (4 args)");
    //System.out.println ("Lock acquired by Thread " + Thread.currentThread ());

   /*Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "createStub",
	       g2ClassName, new Integer (handle));*/
    
    
    long t0 = System.currentTimeMillis();
    // If we have a handle, then we may already have a stub for this object
    int handleVersion = (handle == 0 ? -1 : getVersionForHandle (handle));
    //System.out.println("******" + handle + "v" + handleVersion + "(handle) " + g2ClassName);
    Item previouslyLoadedItem;
    if (handle != 0)
      {
	previouslyLoadedItem = (Item)stubTable.get (handle);

	if (previouslyLoadedItem == null ||
	    ((G2__BaseImpl)previouslyLoadedItem).getHandleVersion () != handleVersion) {
	  //Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "stubNotCached", handleKey);
	  previouslyLoadedItem = forceStubCreation (g2ClassName, handle, handleVersion, context, attributes);
	  //System.out.println ("No prev stub, createG2Stub (4 arg) forced creation of = " + previouslyLoadedItem + " in " + Thread.currentThread ());
	} else {
	  //Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "stubCached", handleKey);
	  //System.out.println ("Prev Stub = " + previouslyLoadedItem + " in " + Thread.currentThread ());
	  // Update any attributes that have come over (by-COPY-WITH-HANDLE)
	  if (attributes.getAttributeCount() > 1) // 1 beacuse incoming attributes values always contain at 
	                                          // at least the CLASS-NAME
	    ((G2__BaseImpl)previouslyLoadedItem).updateCachedAttributeValue(attributes);
	}
	//System.out.println ("Exiting createG2Stub. Releasing lock in thread" + Thread.currentThread ());
	//System.out.println("******" + handle + "v" + handleVersion + "(handle) createStub took " + (System.currentTimeMillis() - t0) + " " + g2ClassName);
      }
    else // by copy, will always create a new stub
      { // System.out.println("By copy: always create anew");
      previouslyLoadedItem = forceStubCreation (g2ClassName, handle, handleVersion, context, attributes);}
    //storeStubHistory (g2ClassName, handle, handleVersion, previouslyLoadedItem);
    //System.out.println ("Returning " + previouslyLoadedItem +  " for (" + g2ClassName + ", " + handle + ", " + handleVersion + ") at \n" + DebugUtil.getStackTrace ());
    return previouslyLoadedItem;
  }

  @Override
  public Item createG2Stub (Symbol g2ClassName_,
			    int handle,
			    int handleVersion,
			    G2Access context,
			    Structure attributes) {
    Item previouslyLoadedItem = (Item)stubTable.get (handle);
    if (previouslyLoadedItem == null ||
	((G2__BaseImpl)previouslyLoadedItem).getHandleVersion () != handleVersion) {
      previouslyLoadedItem = forceStubCreation (g2ClassName_, handle, handleVersion, context, attributes);
      //System.out.println("createG2Stub (5 args) forced creation of " + previouslyLoadedItem + " for handle " + handle + "v" + handleVersion);

      //storeStubHistory (g2ClassName_, handle, handleVersion, previouslyLoadedItem);
    } // else System.out.println ("createG2Stub (5 args) found prior, " + previouslyLoadedItem + " for handle " + handle + "v" + handleVersion);
    return  previouslyLoadedItem;
  }

  private /*synchronized*/ Item forceStubCreation (Symbol g2ClassName,
						   int handle,
						   int stubVersion,
						   G2Access context,
						   Structure attributes)
  {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterForceStub", g2ClassName);
    Constructor stubClassConstructor;
    String stubClassName = "Who Knows?";
    Boolean useOldParams;
    if ((stubClassConstructor = (Constructor)loadedClasses.get (g2ClassName)) == null) {
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
//	System.out.println("Attempting to find the constructor for " + stubClass);
	try {
	  useOldParams = Boolean.FALSE;
	  stubClassConstructor = stubClass.getConstructor (params);
	} catch (NoSuchMethodException nsme) {
	  System.out.println("Warning: Using old-style downloaded class for " + g2ClassName + ".  Please re-download the class.");
	  useOldParams = Boolean.TRUE;
	}
	if (useOldParams.booleanValue()) {
	  try {
	    stubClassConstructor = stubClass.getConstructor (priorparams);
	  } catch (NoSuchMethodException nsme) {
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "missingConst",
			g2ClassName, nsme);
	    Trace.exception (nsme, "Missing constructor : ->");
	  }

	}	
	loadedClasses.put (g2ClassName, stubClassConstructor);
	constructorStatus.put (g2ClassName, useOldParams);

	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finGetConst", stubClassConstructor);
	stubClassName = stubClass.toString ();
    }
    useOldParams = (Boolean)constructorStatus.get(g2ClassName);
    Integer handleKey, stubVersionKey;
    Item stub = null;
    try {
      synchronized (this) {
	// Lets make sure we never make multiple stubs for the same object
	stub = (Item) stubTable.get (handle);
	if (stub != null && ((G2__BaseImpl)stub).getHandleVersion () == stubVersion)
	  return stub;
        if (useOldParams.booleanValue()) {
	  oldinitargs[0] = context;
	  oldinitargs[1] = handleKey = handle;
	  oldinitargs[2] = attributes;
	  stub = (Item) stubClassConstructor.newInstance (oldinitargs);
	  System.out.println("Warning: Using old-style downloaded class for " + g2ClassName + ".  Please re-download the class.");
	  ((G2__BaseImpl)stub).setHandleVersion (stubVersion);
	} else {
	  initargs[0] = context;
	  initargs[1] = handleKey = handle;
	  initargs[2] = stubVersionKey = stubVersion;
	  initargs[3] = null;
	  initargs[4] = attributes;
	  stub = (Item) stubClassConstructor.newInstance (initargs);
	}
	if (handle != 0) {
	  int currentHandleVersion = getVersionForHandle (handle);
	  if (currentHandleVersion > stubVersion) { // Item has already been deleted
	    G2__BaseImpl stubImpl = (G2__BaseImpl)stub;
	    stubImpl.dispose ();
	    if (currentHandleVersion == stubVersion + 1) // Save it if it is the "last" stub
	      previousVersionTable.put (handle, stub);
	  } else
	    stubTable.put (handle, stub);
	}
	//System.out.println ("Stub = " + stub + " in " + Thread.currentThread ());
      }
      ((G2__BaseImpl)stub).setInternalG2ClassName(g2ClassName);
    } catch (java.lang.reflect.InvocationTargetException ite) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedStubCrtnErr", ite);
      Trace.exception (ite, null);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedStubCrtnErr",ite.getTargetException ());
      Trace.exception (ite.getTargetException (), "While invoking constructor on class: " + stubClassName);
      throw new RuntimeException (ite.toString () + ite.getTargetException ().toString());
    } catch (IllegalAccessException iae) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedStubCrtnErr", iae);
      throw new RuntimeException (iae.toString ());
    } catch (InstantiationException ie) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedStubCrtnErr", ie);
      throw new RuntimeException (ie.toString ());
    }
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "createdStub", stub);
    return stub;
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
    java.lang.Object stub = stubTable.remove (handle);
    //System.out.println ("Removed Stub = " + stub);
    if (stub != null) {
      G2__BaseImpl stubImpl = (G2__BaseImpl)stub;
      stubImpl.dispose ();
      previousVersionTable.put (handle, stub);
    }
    deletedIndexTable.put (handle, Integer.valueOf(getVersionForHandle (handle)));
    if (false) {
      System.out.println ("DefaultStubFactory.invalidateG2Stub (" + handle + ") /" +
			  (stub == null ? "Pending" : "Deleting") +
			  " in " + Thread.currentThread ());
      System.out.flush ();
    }
  }

  /**
   * Lookup a stub using its handle, null if there is no stub for a given handle
   */
  @Override
  public Item getG2StubForHandle(int handle, 
				 G2Access context) {
    return (Item)stubTable.get (handle);
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
    if (context.equals(loaderContext)) {
      loader = null;
      loaderContext = null;
      loadedClasses.clear ();
    }
  }

  /**
   * Makes sure that a G2 class has been loaded
   * This is used to get class information without having
   * an instance of the class
   * @undocumeted
   */
  public com.gensym.classes.G2Definition getOrLoadDefinition (Symbol g2ClassName_) throws G2AccessException {
    try {
      loader.loadClass (g2ClassName_, true);
    } catch (StubCreationException sce) {
      if (sce.getMessage().indexOf (NO_SUCH_CLASS_ERROR_TEXT) >= 0)
	throw new G2AccessException (sce.getMessage ());
      throw sce;
    }
    return loaderContext.getClassManager().getDefinition0 (g2ClassName_);
  }


  private static final int STUB_HISTORY_COUNT = 0;
  private Symbol[] stubs_className = new Symbol [STUB_HISTORY_COUNT];
  private int[] stubs_handle = new int [STUB_HISTORY_COUNT],
                stubs_handleVersion = new int [STUB_HISTORY_COUNT];
  private Item[] stubs_stub = new Item [STUB_HISTORY_COUNT];
  private int x = 0;

  /**
   * 
   * This is used only for development testing, as it has an issue: it is 
   * synchronized,  which results in `stubs_className` and the other fields 
   * being used in both  synchronized  and non-synchronized contexts. So, 
   * for debugging purposes,  uncomment and use  (keeping in mind its 
   * issues), but, comment it out again when you're done.
   *  
   * Used for debugging. Set the STUB_HISTORY_COUNT to an appropriately
   * large number (~10000?). Uncomment calls to this method.
   * Be careful since no stub will ever be garbage-collected.
   */
 /* private synchronized void storeStubHistory (Symbol g2ClassName_,
					      int handle,
					      int handleVersion,
					      Item stub) {
    if (x == 0) {
      stubs_className = new Symbol [STUB_HISTORY_COUNT];
      stubs_handle = new int [STUB_HISTORY_COUNT];
      stubs_handleVersion = new int [STUB_HISTORY_COUNT];
      stubs_stub = new Item [STUB_HISTORY_COUNT];
    }
    stubs_className     [x] = g2ClassName_;
    stubs_handle        [x] = handle;
    stubs_handleVersion [x] = handleVersion;
    stubs_stub [x]          = stub;
    x += 1;
  }*/

  /**
   * Dumps the history of the creation of all stubs.
   */
  public void dumpStubHistory () {
    for (int i=0; i<x; i++)
      System.out.println (stubs_className[i] + "  :  " + stubs_handle[i] + "  :  " +
			  stubs_handleVersion[i] + "  :  " + stubs_stub[i]);
    System.out.println ("Current Versions = \n" + deletedIndexTable);
  }


  /**
   * This listener is used to clear out our cache of constructors
   * when the classes become invalid. This happens when we are
   * using alternate classes and somebody flips into generation
   * mode to actually generate the classes. It can also happen
   * when the class inheritance path changes.
   */
  class ConstructorDecacher implements ClassInvalidationListener {
    @Override
    public void classesInvalidated (ClassInvalidationEvent cie) {
      Symbol[] invalidClasses = cie.getInvalidClasses ();
      //System.out.println ("Classes invalidated -> " + DebugUtil.printArray (invalidClasses));
      for (int i=0; i<invalidClasses.length; i++) {
	loadedClasses.remove (invalidClasses[i]);
      }
    }
  }

    void setLoader(StubClassLoader loader) {
        this.loader = loader;
    }
}
