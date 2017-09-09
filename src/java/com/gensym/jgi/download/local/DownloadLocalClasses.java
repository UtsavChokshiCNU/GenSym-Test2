
package com.gensym.jgi.download.local;

import java.awt.*;
import java.awt.event.*;
import java.util.Locale;
import java.util.Vector;
import java.util.Hashtable;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.jgi.download.*;
import com.gensym.g2script.ClassInfoFactory;

import com.gensym.message.Trace;
import com.gensym.message.TraceOut;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

import com.gensym.core.CmdLineArgHandler;

/** Implements a Javalink Prodessional utility that connects to a given G2, 
 *  and downloads the appropriate Java local class(es)
 *  corresponding to the specified G2 classes.  In order to support a G2 class in a Java environment, 
 *  this utility will also download the class hierarchy above the specified classes.
**/
public class DownloadLocalClasses extends com.gensym.jgi.G2ConnectionAdapter {

  /*
   * Standard Tracing Requirements
   */
  static private MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.download.stubs",
			   DownloadLocalClasses.class);
  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;

  private static TraceOut traceListener = new TraceOut();
  private static DownloadLocalClasses downloaderInstance = new DownloadLocalClasses();
  private static String msg = "";

  private static Hashtable connectionLoaderTable = new Hashtable();
  private static Hashtable connectionProxyLoaderTable = new Hashtable();

  /** Connects to a G2 (default is the G2 on machine "localhost" at port "1111"), 
   *  and downloads all Java interafaces required to export the specified G2 classes.<P>
   *	usage: java com.gensym.util.DownloadLocalClasses<BR>
   *		[-force] [-stubs] [-host hostname] [-port portnumber] -classes g2classname[, g2classname...]<P>
   *	Options:<BR>
   *	<LI>-force -- Optional, download classes even if a G2 user class has been previously downloaded
   *	<LI>-stubs -- Optional, generate the implementations for every Java interface created
   *	<LI>-host -- Optional, the host machine of the G2 to download classes from (default is localhost)
   *	<LI>-port -- Optional, the port G2 is running on (default is 1111)
   *	<LI>-class[es] -- The name(s) of the G2 class(es) to download (separated by commas)
   *	@param args command line arguments.
   **/
  public static void main (String[] args) {
    if (args.length < 2) {
      System.err.println ("Usage: java com.gensym.util.DownloadLocalCLasses [-force] [-stubs] [-host host] [-port port] -classes CLASS-NAME {, ...}");
      System.exit (2);
    }

    DownloadLocalInterfacesApplication application = new DownloadLocalInterfacesApplication(args);
    CmdLineArgHandler argHandler = application.getArgHandler();
    boolean forceInterfaces = argHandler.getSwitchValue ("-force");
    boolean createStubs   = argHandler.getSwitchValue ("-stubs");
    boolean forceStubs    = argHandler.getSwitchValue ("-forcestubs");
    boolean generateG2Proxies = argHandler.getSwitchValue ("-proxy");

    if (forceStubs) createStubs = true;  // obviouisly forceStubs will turn on createStubs

    try {
      String host = argHandler.getOptionValue ("-host");
      if (host == null)
	host = "localhost";
      String port = argHandler.getOptionValue ("-port");
      if (port == null)
	port = "1111";
      String[] classNames = argHandler.getOptionValues ("-class");
      if (classNames == null)
	classNames = argHandler.getOptionValues ("-classes");
      if (classNames == null || classNames.length == 0) {
	Exception err = new IllegalArgumentException ("No classes specified for download. Use -classes <className>...");
	System.err.println (err.getMessage ());
	throw err;
      }

      G2Gateway.initialize ();
      G2Access x = (G2Access) G2Gateway.getOrMakeConnection (host, port);
      System.out.println("Connected");

      downloadClasses (x, 
		       classNames, 
		       forceInterfaces, 
		       forceStubs, 
		       createStubs, 
		       generateG2Proxies);      

    } catch (Exception e) {
      Trace.exception (e, null);
      e.printStackTrace();
      
    }

    System.out.println("\n Finished");
    System.exit(0);
  }


  /** Downloads all required classes (and all classes in their class hierarchy).
   *	@param x the G2 to download the classes from
   *	@param g2_class_names array containing the names of the G2 classes to be downloaded
   *	@param forceDownload download interfaces even if the G2 user class has previously been downloaded
   *	@param createStubs generate implementations for every Java interface created
   **/
  public static void downloadClasses (G2Access x,
				      String[] g2_class_names,
				      boolean forceInterfaces,
				      boolean forceStubs,
				      boolean createStubs,
				      boolean generateG2Proxies) {
    LocalStubClassLoader cl =  (generateG2Proxies ? 
				getLocalProxyStubClassLoaderForConnection(x, false) : 
				getLocalStubClassLoaderForConnection(x, false));
    for (int i=0; i<g2_class_names.length; i++) {
      Symbol className_ = Symbol.intern (g2_class_names[i]);
      try {
	downloadClass (x, 
		       g2_class_names[i], 
		       forceInterfaces, 
		       forceStubs, 
		       createStubs,
		       cl);
      } catch (Throwable e) {
	Trace.exception (e, null);
	e.printStackTrace();
      }  
    }
  }

  /** Downloads the interfaces required to export a single G2 class.
   *	@param x the G2 to download the class from
   *	@param g2_class_name the name of the G2 class to be downloaded
   *	@param forceDownload download interfaces even if the G2 user class has previously been downloaded
   *	@param createStubs generate implementations for every Java interface created
   *	@return a definition of the newly-downloaded Class
   **/
  public static Class downloadClass (G2Access x,
				     String g2_class_name,
				     boolean forceDownload,
				     boolean createStubs) {
    return downloadClass (x, 
			  g2_class_name, 
			  forceDownload, 
			  forceDownload, 
			  createStubs, 
			  null);
  }


  public static Class redownloadClass(G2Access x,
			       Symbol g2ClassName,
			       boolean createStubs,
			       boolean onlyStub,
			       Structure additionalData) 
       throws G2AccessException
  {

    LocalStubClassLoader currentClassLoader = getLocalStubClassLoaderForConnection(x, false);

    //if (currentClassLoader.lookupClassNoGeneration(g2ClassName, createStubs) != null && !onlyStub) {
      //Java treats Java classes as unique by name and classloader
    //currentClassLoader = getLocalStubClassLoaderForConnection(x, true);
    //}

    boolean interfaceExistsAlready = currentClassLoader.lookupClassNoGeneration(g2ClassName, true) != null;
    currentClassLoader.updateAndCheckForClassChange(g2ClassName, interfaceExistsAlready);

    //if (interfaceExistsAlready && needToDoInterface)
    //  throw new G2AccessException("Cannot reexport " + 
    //				  g2ClassName + "." + 
    //				  "The siganture of " + g2ClassName + " has changed since the last download");

    return downloadClass(x, 
			 g2ClassName.toString(), 
			 !interfaceExistsAlready, 
			 true, 
			 createStubs, 
			 currentClassLoader);
  }
    
  /**
   * This method will return the interface or stub for a given G2 class name.
   * If the class has not been previously downloaded, it will be created
   */
  public static Class getClassForG2Class(G2Access x,
				  Symbol g2ClassName,
				  boolean isInterface) {
    LocalStubClassLoader currentClassLoader = 
      getLocalStubClassLoaderForConnection(x, false);

    Class clazz = currentClassLoader.loadClassFromSystem(g2ClassName, isInterface);
    if (clazz != null) return clazz;

    return downloadClass(x, 
			 g2ClassName.toString(), 
			 false,  // Dont force 
			 false, 
			 !isInterface, 
			 currentClassLoader);
  }

  static ClassInfoFactory getClassInfoFactory(G2Access x) {
     LocalStubClassLoader currentClassLoader = 
      getLocalStubClassLoaderForConnection(x, false);
     return currentClassLoader.getClassInfoFactory();
  }

  /**
   * Get a LocalStubClassLoader for a G2Access connection
   */
  public static LocalStubClassLoader getLocalStubClassLoaderForConnection(G2Access x, 
								    boolean forcenew) {
    LocalStubClassLoader currentClassLoader = (LocalStubClassLoader)connectionLoaderTable.get(x);
    if (forcenew || currentClassLoader == null) {
      if (currentClassLoader == null) {
	x.addG2ConnectionListener(downloaderInstance);
      }
      currentClassLoader = new LocalStubClassLoader(x);
      connectionLoaderTable.put(x,currentClassLoader);
    }
    return currentClassLoader;
  }

 /**
   * Get a LocalProxyStubClassLoader for a G2Access connection
   */
  public static LocalProxyStubClassLoader getLocalProxyStubClassLoaderForConnection(G2Access x, 
								    boolean forcenew) {
    LocalProxyStubClassLoader currentClassLoader = (LocalProxyStubClassLoader)connectionProxyLoaderTable.get(x);
    if (forcenew || currentClassLoader == null) {
      if (currentClassLoader == null) {
	x.addG2ConnectionListener(downloaderInstance);
      }
      currentClassLoader = new LocalProxyStubClassLoader(x, getLocalStubClassLoaderForConnection(x, false));
      connectionProxyLoaderTable.put(x,currentClassLoader);
    }
    return currentClassLoader;
  }


  public static Class getG2ProxyStubClass(G2Access x,
					  Symbol g2ClassName) {
    LocalStubClassLoader currentClassLoader = getLocalProxyStubClassLoaderForConnection(x, false);
    currentClassLoader.setGenerationMode(StubClassLoader.GENERATION_AUTO);
    
    Class clazz = currentClassLoader.loadClassFromSystem(g2ClassName, false);
    if (clazz != null) return clazz;

    return downloadClass(x,
			 g2ClassName.toString(),
			 false,
			 false,
			 true,
			 currentClassLoader);
  }

  /** Downloads the interfaces required to export a single G2 class.
   *	@param x the G2 to download the class from
   *	@param g2_class_name the name of the G2 class to be downloaded
   *	@param forceDownload download interfaces even if the G2 use class has previously been downloaded
   *	@param createStubs generate implementations for every Java interface created
   *	@param cl the class loader to use when downloading classes
   *	@return a definition of the newly-downloaded Class
   **/
  public static Class downloadClass (G2Access x,
				     String g2_class_name,
				     boolean forceInterface,
				     boolean forceStub,
				     boolean createStubs,
				     LocalStubClassLoader cl) {
    //System.out.println(forceInterface + " " + forceStub + " " + createStubs);
    G2JavaStubController controller = G2JavaStubController.getG2JavaStubController();
    DownLoad downloader = controller.getDownloader();

    if (cl == null)
      cl =  getLocalStubClassLoaderForConnection(x, false);
    cl.setForceDownload (forceInterface);
    cl.setGenerationMode(StubClassLoader.GENERATION_AUTO);
    Class clazz = null;

    Symbol rootClassName_ = Symbol.intern (g2_class_name);
    clazz = cl.loadClass (rootClassName_, true);
    downloader.loadClass(clazz);
    if (createStubs) {
      clazz = null;
      Sequence dependentClasses = new Sequence (10);
      dependentClasses.addElement (rootClassName_);
      for (int i=0; i<dependentClasses.size (); i++) {
	Symbol className_ = (Symbol) dependentClasses.elementAt (i);
	Symbol[] dependentClassesOfClass = cl.getDependentClasses (className_);
	if (dependentClassesOfClass != null) {
	  for (int j=1; j<dependentClassesOfClass.length; j++) // skip self class
	    if (!dependentClasses.contains(dependentClassesOfClass[j]))
	      dependentClasses.addElement (dependentClassesOfClass[j]);
	}
      }
      //System.out.println(dependentClasses);
      if (!forceInterface) // forceInterface overrides forceStub (impl must match interfaces)
	cl.setForceDownload(forceStub); 
      for (int j=dependentClasses.size() -1; j>=0; j--) { // do in reverse order
	Symbol depClassName_ = (Symbol)dependentClasses.elementAt (j);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "DIcreatingStub",
		    new Integer (j), depClassName_);
	clazz = cl.loadClass (depClassName_, false);
	if (forceInterface || forceStub) {
	// Ensure that the current class cache is aware of the new classes
	  if (clazz != null) 
	    downloader.loadClass(clazz); // Impl
	  Class intForClazz = cl.lookupClassNoGeneration(depClassName_, true);
	  if (intForClazz != null)
	    downloader.loadClass(intForClazz); // Interface for Impl
	}
      }
    }
    return clazz;
  }


  /** Overridden g2ConnectionClosed from super class
   */
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent e) {
    G2Access connection = (G2Access)e.getSource();
    connectionLoaderTable.remove(connection);
    connection.removeG2ConnectionListener(this);
  }

  
}









