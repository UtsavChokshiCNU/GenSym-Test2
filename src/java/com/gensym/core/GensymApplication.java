/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GensymApplication.java
 *
 */
package com.gensym.core;

import java.net.URL;
import java.io.File;
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.util.Enumeration;
import java.util.Vector;
import java.util.Properties;
import java.util.StringTokenizer;
import java.util.Locale;

import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.message.TraceOut;

/**
 * All Gensym Application classes should subclass
 * GensymApplication. It provides hooks for getting one-time
 * initialization.
 *
 * It performs initialization of System properties that need to
 * be set for some classes to function. This includes paths to our
 * URLStreamHandlers and ContentHandlers. The properties are read
 * from $(user.home)/.com.gensym.properties by default. It
 * can be specified explicitly using the System property
 * com.gensym.properties.url. If no properties file exists, no error
 * will be signalled, unless the the System property
 * com.gensym.properties.url is also set.

 * The class also handles some
 * standard command-line arguments for locale and debugging.
 */

public abstract class GensymApplication {

  /**
   * Remember that properties have been read so as to disallow
   * reading twice.
   */
  private static boolean propsSet = false;

  /**
   * 'Development' mode. Use this to turn on extra tracing etc.
   */
  private static boolean devOption = false;
  private static volatile ClassKeeperThread keeperThread = null;

  /**
   * Command line argument handler.
   */
  protected CmdLineArgHandler commandLineArguments;

  protected static volatile GensymApplication application;

  /**
   * The constructor can only be called from subclasses
   */
  protected GensymApplication (String[] commandLine) {
    commandLineArguments = new CmdLineArgHandler(commandLine);
    initialize (commandLine);
    //initializeProperties();
    application = this;
    //The following is to avoid garbage collection of the application classes
    if (keeperThread == null)
    {
      synchronized (GensymApplication.class) {
        if (keeperThread == null)
        {
          keeperThread = new ClassKeeperThread();
          keeperThread.start();
        }
      }
    }
    keeperThread.noteApplication(this);
  }

  /**
   * Calls static initializers based on the commandLine arguments.
   */
  public static void initialize (String[] commandLine) {
    CmdLineArgHandler commandLineArguments =
      new CmdLineArgHandler (commandLine);
    handleStandardCommandLineArguments (commandLineArguments);
    initializeProperties ();
  }

  /**
   * Read the .com.gensym.properties file to initialize
   * system properties. If no .com.gensym.properties file exists, the
   * System properties are not altered, but no exception is thrown.
   * @throws RuntimeException if <code>com.gensym.properties.url</code>
   * is specified but there is trouble reading from the specified
   * location.
   */
  public static void initialize () {
    initializeProperties ();
  }

  private static void handleStandardCommandLineArguments (CmdLineArgHandler commandLineArguments) {
    devOption = commandLineArguments.getSwitchValue("-development");
    if (devOption)
      Trace.setExceptionTraceOn(true);

    handleLocaleArguments(commandLineArguments);
    String[] traceKeysAr = commandLineArguments.getOptionValues ("-traceKeys");
    String traceKeys = null;
    if (traceKeysAr != null && traceKeysAr.length > 0) {
      StringBuffer sb = new StringBuffer (traceKeysAr[0]);
      for (int j=1; j<traceKeysAr.length; j++)
	sb.append (" ").append (traceKeysAr[j]);
      traceKeys = sb.toString ();
    }
    if (traceKeys == null)
      traceKeys = commandLineArguments.getOptionValue("-traceKey");
    if (devOption)		// Trace Listeners have not been setup yet!
      System.out.println("TraceKeys = " + traceKeys);
    String messages = commandLineArguments.getOptionValue("-messages");

    if (traceKeys != null) {
      TraceOut traceListener = new TraceOut();
      int level = Trace.ALL_LEVELS;
      try {
	level = (int) commandLineArguments.getOptionLong("-traceLevel", Trace.ALL_LEVELS);
      } catch (NumberFormatException nfe) {
	nfe.printStackTrace();
      }
      traceListener.initialize(traceKeys, level, messages);
    }

    boolean traceOn = commandLineArguments.getSwitchValue("-traceOn");
    if (traceOn)
      Trace.setTraceOn(true);

    boolean debugOption = commandLineArguments.getSwitchValue("-debug");
    if (debugOption) {
      TraceOut.setDebug(true);
      Resource.setResourceDebug(true);
    }
  }
  /**
   * @undocumented
   */
  public static boolean getDevOption () {
    return devOption;
  }

  /**
   * @undocumented
   */
  public static void setDevOption (boolean yes) {
    devOption = yes;
  }

  private static void handleLocaleArguments (CmdLineArgHandler commandLineArguments) {

    String language = commandLineArguments.getOptionValue("-language");
    String country  = commandLineArguments.getOptionValue("-country");
    String variant  = commandLineArguments.getOptionValue("-variant");

    Locale defaultLocale = Locale.getDefault();

    if (language == null) {
    	language = defaultLocale.getLanguage();
    }
    if (country == null) {
    	country = defaultLocale.getCountry();
    }
    if (variant == null) {
    	variant = defaultLocale.getVariant();
    }

    // fix this: need error checking here to see if it is really a valid
    // locale?
    try {
      Locale newLocale = new Locale(language, country, variant);
      Locale.setDefault(newLocale);
    } catch (Exception e) {
      Trace.exception(e, null);
    }
  }


  /**
   * NOTE: the algorithm for setting properties once a com.gensym.properties
   * file has been found is as follows:
   * If the property has already been set in the VM, then we will
   * not modify that property. This design was chosen so that the
   * -D switch to "java" could override the values in the
   * com.gensym.properties file (i.e., command-line wins over properties file).
   */
  private static void initializeProperties () {
    if (propsSet)
      return;
    InputStream propStream = null;
    String explicitLocation = System.getProperty ("com.gensym.properties.url", null);
    if (explicitLocation != null) {
      try {
	URL propFileURL = new URL (explicitLocation);
	propStream = propFileURL.openStream ();
	if (devOption)
	  System.out.println ("Reading properties from " + propFileURL);
      } catch (IOException ioe) {
	Trace.exception (ioe);
	throw new RuntimeException("Unable to load specified properties file from " + explicitLocation + " because " + ioe.getMessage());
      }
    } else {
      String homeDir = System.getProperty("user.home");
      String propFileName = ".com.gensym.properties";
      File propertiesFile = new File(homeDir + File.separator + propFileName);
      try {
	propStream = new FileInputStream(propertiesFile);
	if (devOption)
	  System.out.println("Reading properties from " + propertiesFile);
      } catch (FileNotFoundException fnfe) {
	propStream = com.gensym.core.GensymApplication.class.getResourceAsStream ("/.com.gensym.properties");
	if (devOption)
	  System.out.println ("Reading properties as Resource");
	if (propStream == null) {
	  if (devOption)
	    System.out.println("running without loading properties initialization file");
	  propsSet = true;
	  return;
	}
      }
    }
    Properties newProps = new Properties();
    if (propStream != null) {
      try {
	newProps.load(propStream);
	Properties existingProps = System.getProperties ();
	// clean out existing properties
	for (Enumeration e = existingProps.propertyNames();
	     e.hasMoreElements();) {
	  String nextPropName = (String) e.nextElement();
	  // We are "try"ing properties one by one since
	  // security access to properties can be controlled
	  // on an individual basis, and we want to allow
	  // people to set as many as possible
	  try {
	    String value = System.getProperty(nextPropName);
	    if (value != null) {
	      newProps.remove(nextPropName);
	    }
	  } catch (SecurityException se) {
	    Trace.exception(se);
	  }
	}

	for (Enumeration e = newProps.propertyNames();
	     e.hasMoreElements();) {
	  String nextPropName = (String) e.nextElement();
	  String value = (String)newProps.get(nextPropName);
	  if (value != null) {
	    existingProps.put(nextPropName, value);
	  }
	  try {
	    System.setProperties(existingProps);
	  } catch (SecurityException se) {
	    Trace.exception(se);
	  }
	}
      } catch (IOException ie) {
	Trace.exception(ie);
      } finally {
	try {
	  propStream.close();
	} catch (IOException ie2) {
	  Trace.exception (ie2);
	}
      }
    }
    propsSet = true;
  }

  /**
   * @undocumented pre-1.1 Resource mechanism
   */
  public static String locateImageFile (String imageFileName) {
    String imageDirs = System.getProperty("com.gensym.resources.images");
    if (imageDirs == null)
      return imageFileName;
    StringTokenizer tknzr = new StringTokenizer(imageDirs, "|");
    while (tknzr.hasMoreTokens()) {
      String imageDirectory = tknzr.nextToken().trim();
      String imageLocation = imageDirectory + File.separator + imageFileName;
      File imageFile = new File(imageLocation);
      if (imageFile.exists() && imageFile.canRead())
	return imageLocation;
    }
    return null;
  }

  /**
   * @return GensymApplication
   */
  public static GensymApplication getApplication () {
    if (application != null )
      return application;
    return null;
  }

  // -------- BEGINNING OF PATCH --------
  // Patch for e-SCOR to enable additional hooks to influence behavior of
  // core classes. Applications can customize these APIs to implement specific
  // behavior and checks.
  // checkIfPrivate and isBrowserMode is used to disable some functionality that
  // should not be accessible and needs runtime decision.
  //  com.gensym.core.GensymApplication.getApplication()).checkIfPrivate(data.getItem(), false);

  /**
   * Check if an Item is private
   * @undocumented
   */
  public boolean checkIfPrivate(com.gensym.classes.Item itm, boolean showMessage) {
    return false;
  }


  /** Returns true if the current user is in browser mode, i.e. if he
   *  can browse the application without being able to performing any change.
   *  @undocumented
   */
  public boolean isBrowserMode() {
    return false;
  }

  /**
   * getAppFrame
   * @undocumented
   */
  public java.awt.Frame getAppFrame() {
    return null;
  }

  /**
   * Get Workspace Title
   * @undocumented
   */
  public String getWorkspaceTitle(Object item) {
    return null;
  }

  /** Delete an object. Return true if handled, false otherwise. Core APIs
   *  will delete object if false is returned.
   *  @undocumented
   */
  public boolean deleteItem (Object itm,
      boolean withPermanencyChecksDisabled,
      boolean withoutLeavingStubs) throws com.gensym.jgi.G2AccessException {

    return false;
  }

  /**
   * @undocumented
   */
  public void setApplicationBusy(){
  }

  /**
   * @undocumented
   */
  public void setApplicationNormal(){
  }

  // -------- END OF PATCH --------


  class ClassKeeperThread extends Thread{

    private Vector applications = new Vector();
    private boolean keepBusy = true;

    ClassKeeperThread(){
      super("Class Keeper");
      setDaemon(true);
    }

    void noteApplication(GensymApplication app)
      {
    	applications.addElement(app);
      }

    @Override
    public synchronized void run(){
      try{
    	  while (isKeepBusy()) {
			wait();
    	  }
      }
      catch(InterruptedException ex){
      }
    }

	public boolean isKeepBusy() {
		return keepBusy;
	}

	public void setKeepBusy(boolean keepBusy) {
		this.keepBusy = keepBusy;
	}
  }
}
