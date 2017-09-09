
package com.gensym.jgi.download;

import java.awt.*;
import java.awt.event.*;
import java.util.Locale;
import java.util.Vector;
import com.gensym.jgi.*;
import com.gensym.util.*;

import com.gensym.message.Trace;
import com.gensym.message.TraceOut;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

import com.gensym.core.CmdLineArgHandler;

/** Implements a Javalink utility that connects to a given G2, and downloads the appropriate Java class(es)
 *	corresponding to the specified G2 classes.  In order to support a G2 class in a Java environment, 
 *	this utility will also download the class hierarchy above the specified classes.
 *	For a full description of the DownloadInterfaces utility see Chapter 2 of the G2 Javalink/Gateway 
 *	Users Guide ("Mapping G2 to Java: How to Export a G2 Class as a Java Class").
**/
public class DownloadInterfaces extends Frame {

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.download.stubs",
			   StubClassLoader.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;

  private static TraceOut traceListener = new TraceOut();

  private static volatile String msg = "";

  private static volatile DownloadInterfaces theDownloader;

  private static boolean allowNearest;

  /**
   * @undocumented
   */
  public static boolean IS_BOOTSTRAPPING = false;
  /** Connects to a G2 (default is the G2 on machine "localhost" at port "1111"), 
   *  and downloads all Java interafaces required to export the specified G2 classes.<P>
   *	usage: java com.gensym.jgi.download.DownloadInterfaces<BR>
   *		[-force] [-stubs] [-host hostname] [-port portnumber] -classes g2classname[ g2classname...]<P>
   *	Options:<BR>
   *	<LI>-force -- Optional, download interfaces even if a G2 user class has been previously downloaded
   *	<LI>-stubs -- Optional, generate the implementations for every Java interface created
   *	<LI>-host -- Optional, the host machine of the G2 to download classes from (default is localhost)
   *	<LI>-port -- Optional, the port G2 is running on (default is 1111)
   *	<LI>-class[es] -- The name(s) of the G2 class(es) to download (separated by commas)
   *	@param args command line arguments.
   **/
  public static void main (String[] args) {
    if (args.length < 2) {
      System.err.println ("Usage: java com.gensym.jgi.download.DownloadInterfaces [-force] [-stubs] [-host host] [-port port] -classes CLASS-NAME {, ...}");
      System.exit (2);
    }

    com.gensym.core.GensymApplication.initialize (args);
    DownloadInterfacesApplication application = new DownloadInterfacesApplication(args);
    CmdLineArgHandler argHandler = application.getArgHandler();
    DownloadInterfaces f = new DownloadInterfaces ("Down Load Interfaces Utility");
    boolean forceDownload = argHandler.getSwitchValue ("-force");
    boolean createStubs   = argHandler.getSwitchValue ("-stubs");
    allowNearest          = argHandler.getSwitchValue ("-autoNearest"); 
    IS_BOOTSTRAPPING      = argHandler.getSwitchValue ("-internal-bootstrapping"); 

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
      if (IS_BOOTSTRAPPING)
	System.out.println ("Warning: -internal-bootstrapping set: must be gensym internal use only.");

      f.setLocation (0, 0);
      f.setSize (400, 100);
      f.setVisible (true);
      theDownloader = f;

      WindowListener list =
	new WindowAdapter () {
	  @Override
	  public void windowClosed (WindowEvent we) {
	    we.getWindow().dispose();
	    System.exit(0);
	  }
	  
	  @Override
	  public void windowClosing (WindowEvent we) {
	    we.getWindow().dispose();
	    System.exit(0);
	  }
      };

      f.addWindowListener(list);
      
      G2Gateway.initialize ();
      G2Access x = (G2Access) G2Gateway.getOrMakeConnection (host, port);

      downloadClasses (x, classNames, forceDownload, false);
      if (createStubs) {
	x.closeConnection ();
	x = (G2Access) G2Gateway.getOrMakeConnection (host, port);
	downloadClasses (x, classNames, forceDownload, true);
      }

    } catch (Exception e) {
      Trace.exception (e, null);
      System.out.println(e.toString());
      
    }

    System.out.println("\n Finished");
    System.exit(0);
  }

  /** Instantiates a DownloadInterfaces object with a Frame which displays progress messages.
   *	@param title the title of the frame
   **/
  public DownloadInterfaces (String title) {
    super (title);
  }

  /** Paints the frame.
   *	@param g the graphics window
   **/
  @Override
  public void paint (Graphics g) {
    g.setColor (Color.blue);
    g.drawString (msg, 20, 40);
  }

  /**	Refreshes the contents of the frame (updates the progress message).
  **/
  static void repaintWindow () {
    if (theDownloader != null)
      theDownloader.repaint ();
  }

  /** Downloads all required classes (and all classes in their class hierarchy).
   *	@param x the G2 to download the classes from
   *	@param g2_class_names array containing the names of the G2 classes to be downloaded
   *	@param forceDownload download interfaces even if the G2 user class has previously been downloaded
   *	@param createStubs generate implementations for every Java interface created
   **/
  public static void downloadClasses (G2Access x,
				      String[] g2_class_names,
				      boolean forceDownload,
				      boolean createStubs) {
    StubClassLoader cl = new StubClassLoader (x);
    for (int i=0; i<g2_class_names.length; i++) {
      Symbol className_ = Symbol.intern (g2_class_names[i]);
      try {
	msg = "Downloading Interface for " + className_;
	repaintWindow ();
	downloadClass (x, g2_class_names[i], forceDownload, createStubs, cl);
      } catch (Throwable e) {
	Trace.exception (e, null);
	System.out.println(e.toString());
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
    return downloadClass (x, g2_class_name, forceDownload, createStubs, null);
  }

  /** Downloads the interfaces required to export a single G2 class.
   *	@param x the G2 to download the class from
   *	@param g2_class_name the name of the G2 class to be downloaded
   *	@param forceDownload download interfaces even if the G2 use class has previously been downloaded
   *	@param createStubs generate implementations for every Java interface created
   *	@param cl the class loader to use when downloading classes
   *	@return a definition of the newly-downloaded Class
   **/
  public static Class downloadClass (final G2Access x,
		  final String g2_class_name,
		  final boolean forceDownload,
		  final boolean createStubs,
		  final StubClassLoader cl) {
	StubClassLoader classLoader = cl;  
    if (classLoader == null){
    	classLoader = new StubClassLoader (x);
    }
    classLoader.setForceDownload (forceDownload);
    classLoader.setGenerationMode(allowNearest ?
			 StubClassLoader.GENERATION_AUTO_NEAREST :
			 StubClassLoader.GENERATION_AUTO);
    Class clazz = null;

      Symbol rootClassName_ = Symbol.intern (g2_class_name);
      //try {
	clazz = classLoader.loadClass (rootClassName_, true);
	if (createStubs) {
	  clazz = null;
	  Vector dependentClasses = new Vector (10);
	  dependentClasses.addElement (rootClassName_);
	  for (int i=0; i<dependentClasses.size (); i++) {
	    Symbol className_ = (Symbol) dependentClasses.elementAt (i);
	    Symbol[] dependentClassesOfClass = classLoader.getDependentClasses (className_);
	    for (int j=1; j<dependentClassesOfClass.length; j++) // skip self class
	      if (!dependentClasses.contains(dependentClassesOfClass[j]))
		dependentClasses.addElement (dependentClassesOfClass[j]);
	  }
	  for (int j=dependentClasses.size() -1; j>=0; j--) { // do in reverse order
	    Symbol depClassName_ = (Symbol)dependentClasses.elementAt (j);
	    msg = "Creating Stub for " + depClassName_;
	    repaintWindow ();
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "DIcreatingStub", j, depClassName_);
	    try {
	      clazz = classLoader.loadClass (depClassName_, false);
	    } catch (StubCreationException sce) {
	      Trace.exception (sce);
	    }
	  }
	}
	//} catch (Exception e) {
	//Trace.exception (e, null);
	//}
	//System.out.println(clazz);
      return clazz;
  }
  
}

