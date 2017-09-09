/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.NativeMethodBroker.java
 *
 *   Authors: John Valente, Allan Scott
 */
package com.gensym.com;

import java.awt.Color;
import java.awt.Graphics;
import java.io.Serializable;
import java.util.Vector;
import java.util.Locale;

import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;

/** An uninstantiable class which serves as a broker between
 *  Java and JavaContainer.dll, the C library which supports
 *  the ActiveX calls.  Also keeps track of all of the ActiveX
 *  objects created in this Virtual Machine, and provides a few
 *  functions for iterating over them.<p>
 * 
 *  Note: Many public, static methods in this class depend on native
 *  methods, and therefore depend on the JavaContainer dynamic 
 *  library being loaded.  However, they do not check that the library
 *  is loaded.  It is up to the caller to attempt to load the library 
 *  and check that it has been loaded by calling this class's loadLibrary
 *  method and checking its return result.  In any case, the methods
 *  are not really intended to be used by other classes.  They are used
 *  by ActiveXProxy or other memebers of this package.  They are being
 *  made public for any really ambitious projects that want to improve
 *  on ActiveXProxy, and also because JavaBeans seems to have random
 *  failures which appear to vary inversely from the percentage of
 *  methods which are public.<p>
 *
 *  The methods which fall into this category are:
 *   startUp
 *   insertObjectFromClsid
 *   activateObject
 *   renderObject
 *   deleteObject
 *   copyObject
 *   updateStuff
 *   beanifyObject
 *   shutDown
 */


public final class NativeMethodBroker implements ActiveXTraceLevels
{ 
  private static short C_TraceLevel = AX_MIN_TRACE_LEVEL;
  private static ProxyWrapper tableOfProxies = null;

  private static final short clearFlags = 3;
  private static final int hInstance = 4194304;
  private static final String defaultAppName = "Gensym ActiveX Container";
  
  private native static boolean clear (short flags);
  private native static void containerSetup (String s, int hInstance);
  private native static void terminate (int hWnd);
  
  /*
   * Standard Tracing Requirements
   */
  static private MessageKey traceKey; // defined before use below

  static private Resource i18nTrace = 
  Trace.getBundle("com.gensym.com.TraceMessages",
		  Locale.getDefault());

  /*
   * Standard Messaging Requirements
   */

  static private Resource i18n =
  Resource.getBundle("com.gensym.resources.Messages",
		     Locale.getDefault());


  /* libraryIsLoaded is accessible to other classes in the package */
  static boolean libraryIsLoaded = false;  

  private native static void set_trace_level (short newTraceLevel);
  private native static Vector browse_type_library (String libraryName);
  private native static int get_IDispatch (int clientSite);
  
  static int USE_JAVAC = 0x0001;
  static int EMIT_EXCEPTIONS = 0x0002;
  static int USE_VERSIONS = 0x0004;

  private native static void beanify(String clsid, 
                                      String libPath,
                                      String emitPackage,
                                      String emitDirectory,
                                      int flags);
  public static void beanifyClass(String clsid, 
                                  String libPath,
                                  String emitPackage,
                                  String emitDirectory,
                                  int flags)
  {
    beanify(clsid,libPath,emitPackage,emitDirectory, flags);
  }

  private native static boolean beanify_from_progid
    (String progid,
    String emitPackage,
    String emitDirectory,
    int flags);

  public static boolean beanifyFromProgid(String progid, 
                                  String emitPackage,
                                  String emitDirectory,
                                  int flags)
  {
    return beanify_from_progid(progid,emitPackage,emitDirectory, flags);
  }

  private native static void collect_emitted_files_info (BeanXporter b);
  public static void collectEmittedFilesInfo (BeanXporter b) {
    collect_emitted_files_info(b);
  }

  public native static void collect_info (BeanXporter b, boolean detailed);
  public static void collectInfoAboutControls (BeanXporter b, boolean detailed) {
    collect_info(b, detailed);
  }

  static {
    loadLibrary();
  }

  private NativeMethodBroker () {
    traceln("Error: NativeMethodBroker cannot be instantiated");
    System.exit(-1);
  }


  public static ActiveXModes promptForInsertObject (int hWnd) {
    if (libraryIsLoaded) {
      return ActiveXGenericComponent.prompt_for_insert_object(hWnd);
    } else {
      traceln(AX_ERROR, "Could not find JavaContainer.dll in your PATH");
      return new ActiveXModes(new Guid());
    }
  }


  /** Loads the JavaContainer dynamic library. */
  public static boolean loadLibrary (boolean definitely) {
    if (libraryIsLoaded && !definitely)
      return true;
    try {
      System.loadLibrary("JavaContainer");
      System.out.println("com.gensym.com: Loaded JavaContainer.");
      containerSetup(defaultAppName, hInstance);
      clear(clearFlags);
      set_trace_level(C_TraceLevel);
      libraryIsLoaded = true;
      return true;
    } catch (UnsatisfiedLinkError e) {
      System.out.println("com.gensym.com: Error! Could not load JavaContainer.");
      return false;
    }
  }

  /** Loads the JavaContainer dynamic library if it is not already loaded. */
  public static boolean loadLibrary () {
    return loadLibrary(false);
  }


  /** Sends a message to any listeners.  
   */
  public synchronized static void traceln (String message) {
    traceln(AX_ALWAYS, message);
  }

  /** Sends a message to any listener who is listening at the appropriate
   *  debug level.  If the message is an AX_ERROR or worse this will send a 
   *  message event, otherwize the message will only be sent if tracing
   *  has been switched on by a call to Trace.setTraceOn(true).
   */
  public static void traceln (int messagePriority, String message) {
    if (traceKey == null) {
      traceKey = Trace.registerMessageKey("com.gensym.com",
					  NativeMethodBroker.class);
    } 
    if (AX_ERROR >= messagePriority) {
      Message.send(new MessageEvent(messagePriority, "com.gensym.com",
				    NativeMethodBroker.class, i18nTrace, 
				    "default", new Object[] {message}));
    } else {
      Trace.send(messagePriority, traceKey, i18nTrace, "default", message);
    }
  }



  /** Set the C_TraceLevel cutoff for tracing that is produced 
  * by the JavaContainer library.  This provides a means of 
  * controlling the amount of tracing calls that are made into
  * Java from the library and is therefore useful for performance
  * tweaking. 
  */
  public static boolean setTraceLevel (short newTraceLevel) {
    if ((newTraceLevel >= AX_MIN_TRACE_LEVEL) &&
	(newTraceLevel <= AX_MAX_TRACE_LEVEL)) {
      C_TraceLevel = (short) newTraceLevel;
      set_trace_level(C_TraceLevel);
      return true;
    } else {
      return false;
    }
  }

  /** Get the traceLevel used by the JavaContainer library */
  public static short getTraceLevel () {	
    return C_TraceLevel;
  }

  //**********************************************************************
 
 
   /** Adds a control to the table.  This method is called by ActiveXProxy,
    *  so wrapper objects do not need to call it themselves.
    */
   public static void registerProxy (ActiveXProxy object) {
       tableOfProxies = new ProxyWrapper(object, tableOfProxies);
   } 
 
   /** Adds a control to the table.  This method is called by ActiveXProxy,
    *  so wrapper objects do not need to call it themselves.
    */
   public static void registerProxy (int clientSite,
 				      ActiveXProxy object) {
       tableOfProxies = new ProxyWrapper(object, tableOfProxies);
   }
 
   /** Returns the object with the given client site pointer, if such
    *  an object exists in the table.
    */
   public static ActiveXProxy getProxy (int clientSite) {
     if (tableOfProxies == null)
       return null;
     else
       return tableOfProxies.get(clientSite);
   }
 
   /** Removes a control from the table. */
   public static void deregisterProxy (ActiveXProxy object) {
     if (tableOfProxies == null)
       return;

     tableOfProxies = tableOfProxies.remove(object);
   } 


  //**********************************************************************
  // Wrappers for native functions

  //**********************************************************************
  // Methods which really are intended to be public, and can be used
  // by other classes.

  /** If the given string names a file which contains type information,
   *  emits a Java source file which exposes the methods
   *  and properties contained in the type library as Java methods.
   */
  public static void browseTypeLibrary (String libraryName) {
    browse_type_library(libraryName);
  }

  /** If the client site given points to an object which supports IDispatch,
   *  returns the pointer to the IDispatch interface, which can then
   *  be used with comInvoke, comPropertySet, comPropertyGet.
   */
  public static int getDispatchPointer (int clientSite) {
    if (clientSite == ActiveXProxy.AX_NO_CLIENT_SITE) {
      return ActiveXDispatchable.AX_NO_DISPATCH;
    } else {
      return get_IDispatch(clientSite);
    }
  }

  

//**********************************************************************
   // Callbacks from native code.
 
   /** Tells the object with the given client site that it is now
    *  "open".
    */
   public static void setOpenInWindow (int clientSite, boolean isOpen) {
     if (tableOfProxies != null)
       tableOfProxies.setOpenInWindow(clientSite, isOpen);
   }
 
   /** Redraws the object with the given client site. */
   public synchronized static void redrawObject (int clientSite) {
     ActiveXProxy proxy;
 
     traceln(AX_DATA_DUMPS, "Redrawing for proxy " + clientSite);
     proxy = tableOfProxies.get(clientSite);
     if (proxy != null)
       proxy.repaint();
   }

   /** Event forwarding from C to Java
   */
   public static void forwardActiveXEvent(int clientSite,
                                   Guid iid,
                                   int dispid,
                                   String eventName,
                                   Variant[] arguments)
   {
     ActiveXProxy proxy;

     proxy = tableOfProxies.get(clientSite);

     if (proxy != null)
        proxy.forwardActiveXEvent(iid,
                       dispid, eventName, arguments); 
   }
}


  class ProxyWrapper implements Serializable { 
   ActiveXProxy object;
   ProxyWrapper next;
 
   ProxyWrapper (ActiveXProxy object, ProxyWrapper list) {
     this.object = object;
     next = list;
   }
 
   boolean setOpenInWindow (int clientSite, boolean isOpen) {
     if (object.getClientSite() == clientSite) {
       return true;
     }
     if (next == null)
       return false;
     return next.setOpenInWindow(clientSite, isOpen);
   }

   ProxyWrapper remove(ActiveXProxy object) {
     if (this.object == object)
         return next;

     if (next != null)
       next = next.remove(object);

     return this;
   }
     
   ActiveXProxy get (int clientSite) {
     if (object.getClientSite() == clientSite) {
 	return object;
       }
 
     if (next == null)
       return null;
 
     return next.get(clientSite);
   }
 
   @Override
   public String toString () {
     return("object = " + object + "; next = " + next);
   }
 }

