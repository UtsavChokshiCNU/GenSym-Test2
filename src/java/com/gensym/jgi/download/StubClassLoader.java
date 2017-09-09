/*
 * @(#)StubClassLoader.java	1.0 97/10/22
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */
package com.gensym.jgi.download;

import java.io.File;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.util.Hashtable;
import java.util.Enumeration;
import java.util.Locale;
import java.util.Vector;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import com.gensym.core.GensymApplication;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Version;
import com.gensym.util.*;
import com.gensym.classes.G2Definition;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.ModuleInformation;
import com.gensym.classes.ClassFriendAccess;
import com.gensym.util.symbol.G2ClassSymbols;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.core.DebugUtil;

/**
 * This class is used to load the interfaces and the implementation
 * stubs for the G2 classes that are downloaded to Java. If it does
 * not find the classes in the <code>CLASSPATH</code>, it uses
 * introspection and additional overrides to generate an appropriate
 * Java class.
 *
 * @version 	1.00, 09/15/97
 * @author      vkp, mgribble
 */

/*
 * There is a lot of mysterious goings-on here that needs to be
 * documented. In particular, the order in which things are
 * performed is very particular, so it would be best not to
 * mess with it without a full understanding of how this class
 * works -vkp, 11/6/97
 */

public class StubClassLoader extends ClassLoader 
implements com.gensym.util.symbol.AttributeExportSymbols,
com.gensym.util.symbol.AttributeTypeSpecificationSymbols,
com.gensym.util.symbol.MethodExportSymbols,
com.gensym.util.symbol.OverrideSymbols {

  /**
   * @undocumented
   */
  public static final boolean allowPseudoClasses = true;

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
    Trace.registerMessageKey ("com.gensym.jgi.download.stubs", StubClassLoader.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL     = 5;
  private static final int ALWAYS_TRACE_LEVEL  = 1;
  private static final int DEF_WARN_LEVEL      = 2;
  private static final int BASIC_TRACE_LEVEL   = 3;
  private static final int MINIMAL_TRACE_LEVEL = 4;
  private static final long classLoadTimeout   = 0; // forever
  
  static final Class BASE_JAVA_CLASS = com.gensym.classes.G2__BaseImpl.class;
  static final String BASE_JAVA_CLASS_NAME = "com.gensym.classes.G2__BaseImpl";
  static final String BASE_JAVA_INTERFACE_NAME = "com.gensym.classes.G2__Base";
  // NOTE: the following is kind of a hack: the hyphen is ensure
  // the the following "B" is capitalized when it is converted to
  // a "java name" by the G2ClassTranslator.
  static final Symbol BASE_INTERFACE_SYMBOL = Symbol.intern("G2__-BASE");

  static final String PSEUDO_PACKAGE = "pseudo";

  /*
   * Private Fields
   */
  private G2Access context;
  private ClassManager cdm;
  private String g2Repository, userRepository, g2Package,g2PackageWithoutTrailingDot,
                 userPackage, unspecifiedPackage, pseudoPackage,
                 pseudoPackageWithoutTrailingDot;
  protected InterfaceGenerator igcg2, igcuser;
  protected Hashtable loadedInterfaces = new Hashtable (211),
                      loadedStubs = new Hashtable (211);
  private Hashtable loadingClasses = new Hashtable(211),
                    uncompilableClasses = new Hashtable (211),
                    nearestClassesTable = new Hashtable (211);
  private Hashtable pseudoClasses = new Hashtable(101);
  protected Hashtable assignedPackages = new Hashtable (13); // depth of recursion
  private Hashtable pkgToModuleMap = new Hashtable (13); // # of modules
  private Hashtable pendingDefinitions = new Hashtable (17); // #threads + recursion
  // classes that need to be instantiated before they are loaded
  private Hashtable bestGuessForRecursionTable = new Hashtable(5);
  protected Hashtable classInfoTable = new Hashtable (211);
  private Hashtable overridesTable = new Hashtable (211);
  protected Hashtable ClassAttributeValuesTable   = new Hashtable (211),
		    ClassInheritancePathTable   = new Hashtable (211);
  private Hashtable proxyClasses                = new Hashtable (11);
  private Hashtable uninitlzedClasses           = new Hashtable (101);
  private Hashtable dependentClassesTable       = new Hashtable (23);
  private Hashtable waitingThreads              = new Hashtable (5);
  private Hashtable currentlyLoadingDefinitions = new Hashtable (5);
  private Hashtable fetchingDefinitions         = new Hashtable (5);
  private boolean   generationMode              = false;
  private int       generationModeForUser       = GENERATION_AUTO_NEAREST;
  private static Sequence classDepthTracing     = new Sequence (5);
  private Hashtable exceptionTable              = new Hashtable (5);

  private static Object synchronizer = new Object();

  private volatile Hashtable moduleMappingTable          = null;
  private ClassFriendAccessor classFriend       = null;
  private boolean traceOn                      = false;

  /*
   * Class Constants
   */
  private static final Symbol CLASS_ATTRIBUTES_        = Symbol.intern ("CLASS-ATTRIBUTES"),
                              INSTANCE_ATTRIBUTES_     = Symbol.intern ("INSTANCE-ATTRIBUTES"),
                              DIRECT_SUPERIOR_CLASSES_ = Symbol.intern ("DIRECT-SUPERIOR-CLASSES"),
                              CLASS_INHERITANCE_PATH_  = Symbol.intern ("CLASS-INHERITANCE-PATH"),
		              STATIC_METHODS_          = Symbol.intern ("STATIC-METHODS"),
                              INSTANCE_METHODS_        = Symbol.intern ("INSTANCE-METHODS"),
                              EXPORTED_SOURCE_         = Symbol.intern ("EXPORTED-SOURCE"),
                              HAND_CODED_METHODS_      = Symbol.intern ("HAND-CODED-METHODS"),
                              G2_METHOD_               = Symbol.intern ("G2-METHOD"),
                              G2_METHOD_TEXT_          = Symbol.intern ("G2-METHOD-TEXT");

  private static final Symbol ORIGINAL_ATTRIBUTE_NAME_ = Symbol.intern ("ORIGINAL-ATTRIBUTE-NAME");

  // The superior of all G2 Event Listeners classes
  private static final Symbol G2_EVENT_LISTENER_       = Symbol.intern("G2-EVENT-LISTENER");
  // The superior of all G2 Event Object classes
  private static final Symbol G2_EVENT_OBJECT_         = Symbol.intern("G2-EVENT-OBJECT");

  private static final Symbol G2_GET_CLASS_HASH_ = Symbol.intern ("G2-GET-CLASS-HASH");

  private static final Object nullObj = new NullObject ();

  private static boolean IS_BOOTSTRAPPING = false;
  private static final boolean DISREGARD_MODULE_STABILITY_DECLARATION = false;

  /**
   * Mode to not read class information on loading 
   */
  public static final int GENERATION_OFF  = 0;

  /**
   * Mode to read class information on loading
   */
  public static final int GENERATION_ON   = 1;
  /**
   * Mode to defer reading class information till it
   * is required
   */
  public static final int GENERATION_AUTO = 2;

  /**
   * Same as GENERATION_AUTO except; the nearest loadable class is used if the class is not already
   * downloaded. If a user class, which has not been downloaded, is found to be multi-inherited 
   * from other user classes (that have previously been downloaded) then a interface/stub is
   * auto generated to ensure multi-inheritance.
   */
  public static final int GENERATION_AUTO_NEAREST = 3;

  private boolean useAlternateClasses = true;

  private boolean forceDownload = false;

  private boolean checkForClassChange;

  private static final char sepChar = System.getProperty ("file.separator").toCharArray ()[0];
  private final Vector userPackages = new Vector ();
  {
    String userPackagePrefixList = System.getProperty ("com.gensym.class.user.pkgs");
    userPackagePrefixList += "|" + getUserPackage() + ".unspecified";
    java.util.StringTokenizer packagePrefixIter =
      new java.util.StringTokenizer (userPackagePrefixList, "|");
    while (packagePrefixIter.hasMoreTokens()) {
      String packagePrefix = packagePrefixIter.nextToken ().trim();
      packagePrefix += ".";
      userPackages.addElement (packagePrefix);
    }
  }

 /**
  * Constructs a new <code>StubClassLoader</code>. The <code>G2Access</code>
  * that is passed in to the constructor is used to obtain introspective
  * information about new G2 classes that are downloaded.
  * @param context A <code>G2Access</code> that is used to determine
  *                class information.
  */
  public StubClassLoader(G2Access context) {
    this(context,
	 System.getProperty ("com.gensym.class.g2.package", "com.gensym.classes"),
	 getUserPackage(),
	 new ClassFriendAccess());
  }
	 

  protected StubClassLoader (G2Access context,
			     String g2PackageIn,
			     String userPackageIn,
			     ClassFriendAccessor classFriend ) {
    this.context      = context;
    this.classFriend  = classFriend;
    String separator  = System.getProperty ("file.separator");
    g2Repository      = System.getProperty ("com.gensym.class.g2.repository");
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "g2ReposProp", g2Repository);
    userRepository    = getUserRepository();
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "userReposProp", userRepository);
    this.g2Package         = g2PackageIn;
    this.userPackage       = userPackageIn;
    igcg2             = new InterfaceGenerator (g2Package, g2Repository, null, systemClassNameMapper);
    igcuser           = new InterfaceGenerator (userPackage, userRepository, 
						new String[] {g2Package+"/*"}, userClassNameMapper);
    g2PackageWithoutTrailingDot = g2Package;
    g2Package         += ".";
    pseudoPackage      = g2Package + PSEUDO_PACKAGE;
    pseudoPackageWithoutTrailingDot = pseudoPackage;
    pseudoPackage += ".";
    userPackage       += ".";
    g2Repository      += separator;
    userRepository    += separator;
    cdm = context.getClassManager();
    String checkClassPropValue = System.getProperty ("com.gensym.class.checkClass", "false");
    checkForClassChange = Boolean.getBoolean (checkClassPropValue);
    unspecifiedPackage = userPackage + "unspecified";
    IS_BOOTSTRAPPING = DownloadInterfaces.IS_BOOTSTRAPPING;
  }

  protected InterfaceGenerator getUserInterfaceGenerator() {
    //System.out.println("In StubClassLoader  getUserInterfaceGenerator()");
    return igcuser;
  }

  /**
   * @undocumented
   */
  public void unloadClass(Symbol g2ClassName) {
    // fix this: must unload all subclasses, too.
    loadedInterfaces.remove(g2ClassName);
    loadedStubs.remove(g2ClassName);
    nearestClassesTable.remove(g2ClassName);
    ClassInheritancePathTable.remove(g2ClassName);
    fireInvalidationEvent(new Symbol[] {g2ClassName});
  }

  // vkp recommends that pseudo classes return a real interface if
  // loadClass is called with isInterface=true. Right now, loadClass
  // always returns the Impl for all pseudo classes.

  /**
   * Requests the StubClassLoader to load a class corresponding to
   * a G2 class identified by a symbolic class-name. 
   * @param g2ClassName A symbol naming a G2 class
   * @param isInterface <code>true</code> to generate or load an
   *                    interface; <code>false</code> for an implementation
   *                    stub class.
   */
  public Class loadClass (Symbol g2ClassName,
			  boolean isInterface) {
    //System.out.println ("loadClass (" + g2ClassName + ", " + isInterface + ")");

    Thread currentThread = Thread.currentThread ();

    if (//generationMode && !
	!context.canCallRPC ()) {
      Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "DeferringLoad",
		  g2ClassName);
      throw new StubCreationException ("Need to load " + g2ClassName +
				       " from outside callback thread.");
    }

    synchronized (synchronizer) {

      Exception classLoadingException = null;
      traceOn = Trace.getTraceOn();
      Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "loadClassCall",
		  g2ClassName, isInterface ? Boolean.TRUE : Boolean.FALSE);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "callToLoad",
		  g2ClassName, (isInterface ? Boolean.TRUE : Boolean.FALSE));
      Class clazz;
      Hashtable loadedClasses         = (isInterface ? loadedInterfaces : loadedStubs);
      boolean   classFullyInitialized = (uninitlzedClasses.get (g2ClassName) == null);
      clazz = (Class) loadedClasses.get (g2ClassName);
      boolean   classPreviouslyLoaded = (clazz != null);
      boolean   handedOutPartialClass = false;

      if (traceOn)
	Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "loadClassState",
		    new Object[] {generationMode ? Boolean.TRUE : Boolean.FALSE,
				    classFullyInitialized ? Boolean.TRUE : Boolean.FALSE,
				    classPreviouslyLoaded ? Boolean.TRUE : Boolean.FALSE,
				    clazz,
				    loadingClasses,
				    classDepthTracing});
      //System.out.println (g2ClassName + ", " + isInterface);
      if (clazz != null) {
	Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "ClassInCache");
	if (!generationMode ||
	    classFullyInitialized) {
	  Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "classPrevLoaded",
		      clazz);
	  return clazz;
	}
      } else {
	Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "ClassGenerated");
      }
    
      if (uncompilableClasses.get (g2ClassName) != null) {
	// If we are NOT in the depth of recursion and this class was uncompilable
	// we must ensure its loaded, otherwise return null
	if (!classDepthTracing.isEmpty()) {
	  Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "uncompilableClass",
		      g2ClassName);
	  return null;
	}
      }
    
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "notPrevLoaded",
		  g2ClassName);
    
      PseudoClassInfo pseudoClassInfo =
	(PseudoClassInfo)pseudoClasses.get(g2ClassName);
      boolean isPseudoClass = pseudoClassInfo != null;
      Vector classesToBlendForLoad =
	isPseudoClass ?pseudoClassInfo.classesToBlend : null;

      String className =
	generateClassName(g2ClassName, isInterface, isPseudoClass);
    
      // handle recursion in actively loading interfaces
      Object currentlyLoading = loadingClasses.get (g2ClassName);
      if (currentlyLoading != null) {
	// Allow downloading of stub of class within recursive descent of definition load
	if ((clazz = (Class) currentlyLoadingDefinitions.get (g2ClassName)) != null) { // Note: using clazz variable
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "partialClass", g2ClassName, clazz);
	  if (isInterface) { // hand back the incomplete Class
	    handedOutPartialClass = true;
	    return clazz;
	  } else {// continue on to get or generate stub class
	    clazz = null;
	  }
	}
	if (isInterface) {
	  if (loadedClasses.get (g2ClassName) == null) {
	    Class guess = getBestCurrentGuessForInterface(g2ClassName, loadedClasses);
	    bestGuessForRecursionTable.put(g2ClassName, guess);
	    //loadedInterfaces.put(g2ClassName, guess);
	    return guess;
	    //return null;	// true recursion?
	  }
	  // else continue -> must be generation mode switch flip
	} else {
	  // See the documentation for com.gensym.classes.Interim__StubImpl
	  // to see a situation where stub loading can happen
	  // recursively
	  if (loadedInterfaces.get(g2ClassName) == null &&
	      bestGuessForRecursionTable.get(g2ClassName) != null) {
	    return getBestCurrentGuessForStub(g2ClassName, loadedClasses);
	  }
	}
      } else
	loadingClasses.put (g2ClassName, currentThread);      
    
      // mark interface as being currently loaded
      //loadingClasses.put (g2ClassName, currentThread);
      classDepthTracing.addElement (g2ClassName);
      //debugIndent("add");
      boolean loadedAlternateClass  = false;

      try {
	boolean isSystemClass = com.gensym.classes.SystemPredicate.isSystemClass (g2ClassName);
	if (clazz == null) {
	  // Try as System class first!
	  String fullyQualifiedClassName = null;
	  //long t0 = System.currentTimeMillis ();
	  if (isSystemClass || isPseudoClass) {
	    String packageName = isPseudoClass ? pseudoPackage : g2Package;
	    fullyQualifiedClassName = packageName + className;
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clLookingFor",
			g2ClassName, className, fullyQualifiedClassName);
	    try {
	      clazz = Class.forName (fullyQualifiedClassName,
				     true,
				     Thread.currentThread().getContextClassLoader());
				   
	      // todo: implement verifyPseudoClass (add args as necessary)
// 	    if (isPseudoClass)
// 	      verifyPseudoClass(clazz);
	    } catch (Error classLoadingError) {
	      // empirically found that NoClassDefFoundError can be
	      // thrown. Catching Error in case others can be thrown
	      Trace.exception(classLoadingError);
	      if (isPseudoClass) {
		System.out.println("malformed class " + fullyQualifiedClassName);
		System.out.println("Regenerating");
		throw new ClassNotFoundException("malformed pseudo class");
	      } else
		throw classLoadingError;
	    }
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "classInSystem", clazz);
	    if (IS_BOOTSTRAPPING)
	      throw new ClassNotFoundException ("Bootstrapping Exception!");
	  } else {
	    //long t1 = System.currentTimeMillis ();
            //System.out.println ("Loading " + g2ClassName + " lost " + (t1 -t0) +
	    //	      " in checking for system class");
	    // Ignore, need to try user package
	    if (IS_BOOTSTRAPPING)
	      throw new ClassNotFoundException ("Bootstrapping Exception");
	    // This might be a user class. Setup module map. We cannot possibly
	    // need it before now.
	    if (moduleMappingTable == null) { // call1_to_refreshModuleMappings
	      refreshModuleMappings (true);
	    }
	    String pkgForUserClass = getPackageForLoadableUserClass (className, g2ClassName, isInterface);
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "userPkg", g2ClassName, pkgForUserClass);
	    Symbol[] CIPArray = getClassInheritancePath (g2ClassName);
	    if (isInterface) {
	      if (generationMode) {
		try {
		  initializeClassData (g2ClassName, getClassInfo (g2ClassName, false));
		} catch (G2AccessException g2ae) {
		  Trace.exception (g2ae);
		  throw new StubCreationException (g2ae.getMessage ());
		}
	      }
	      ensureSuperInterfacesAreLoaded (CIPArray);
	    }
	    //System.out.println ("getPackageForLoadableUserClass (" + className + ", " +
	    //	      g2ClassName + ", " + isInterface + ") = " + pkgForUserClass);
	    if (forceDownload &&
		(!moduleOfClassIsStable(g2ClassName, isInterface)
		 || DISREGARD_MODULE_STABILITY_DECLARATION))
	      throw new ClassNotFoundException ("Forced Download");
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "notFoundInSys",
			fullyQualifiedClassName);
	    //Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedError", cnfe);
	    //fullyQualifiedClassName = userPackage + className;
	    //clazz = super.findSystemClass (fullyQualifiedClassName);
	    //same condition as -> (!useAlternateClasses || (nearestClassesTable.get (CIPArray[1]) == null))
	    if (!(useAlternateClasses && (nearestClassesTable.get (CIPArray[1]) != null)))
	      clazz = userPackageIterator.findUserClass (className, pkgForUserClass + ".");
	    if (clazz == null && useAlternateClasses) {
	      clazz = findAlternateClass (g2ClassName, isInterface);
	      Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "foundAltClass", clazz, g2ClassName);
	      loadedAlternateClass = true;
	    }
	    if (clazz == null)
	      throw new ClassNotFoundException ("user class not found");
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "classInUser",
			clazz);
	  }
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "classLoaded", g2ClassName, "locally");
	}  // else Must've flipped the generation switch. Flushing uninitlzedClasses!
	if (isInterface) {
	  if (generationMode) {
	    // We must indicate that we are fully initialized as loadClassInfo may 
	    // try to reload the same, and cause an endless loop
	    if (!classFullyInitialized) {
	      uninitlzedClasses.remove (g2ClassName);
	      //classFullyInitialized = true;
	    }
	    if (!isPseudoClass)
	      loadClassInfo (className, g2ClassName, clazz.getName ());
	  }
	  boolean ok = isPseudoClass || (isSystemClass && classFriend.register (g2ClassName, clazz));
	  //System.out.println ("registration of " + clazz + " required no recursion -> " + ok);
	  if (!IS_BOOTSTRAPPING) {
	    try {
	      //if (!ok) This results in super class definitions being created out of order -vkp, 5/19/98
	      if (isSystemClass)  //!loadedAlternateClass) // We've already done this
		ensureSuperInterfacesAreLoaded (getClassInheritancePath (g2ClassName));
	      if (!isPseudoClass && !(generationMode && !classFullyInitialized))
		makeClassDefinition (g2ClassName, clazz, isSystemClass);
	      //else
	      //System.out.println ("\n\nSkipping makeClassDefinition (" + g2ClassName + ")");
	    } catch (G2AccessException gae) {
	      Trace.exception (gae, null);
	      classLoadingException = new StubCreationException (gae.toString ());
	      throw (StubCreationException)classLoadingException;
	    }
	  }
	}
      
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "classPut", g2ClassName);
	if (isPseudoClass) // hack
	  loadedInterfaces.put(g2ClassName, clazz);
	loadedClasses.put (g2ClassName, clazz); // Might be done twice. Doesn't hurt.
	/*System.out.println ("Loaded " + g2ClassName + " -> Currently loaded = " + loadedClasses + "\n" +
	  "Uncompilable = " + uncompilableClasses);*/
	if (!generationMode)	// Here only because of uninitlzd class found by system class-loader
	  uninitlzedClasses.put (g2ClassName, g2ClassName);
	else if (!classFullyInitialized)
	  uninitlzedClasses.remove (g2ClassName);
	//debugIndent("remove");
	classDepthTracing.removeElementAt (classDepthTracing.size () - 1);
	return clazz;
      } catch (ClassNotFoundException cnfe) {
      
	boolean forcedGenerationModeFlip = false;
	boolean prevUseAlternateClasses  = false;
	//Trace.exception (cnfe, "here @0 ->");
	try { // to throw only StubCreationException

	  byte[] classContents = null;
	  if(!isPseudoClass) {
	    // when introducing NEAREST mode, introduce a member variable
	    // allowedtoSwitch, which is set to true for these two modes,
	    // and set to false for NEAREST
	    if ((generationModeForUser == GENERATION_AUTO ||
		 generationModeForUser == GENERATION_AUTO_NEAREST) &&
		// allowedToSwitch
		!generationMode) {
	      // Trace.setTraceOn(true);
	      System.out.println ("Flipping mode for generating : " + g2ClassName + " (mode = " + generationModeForUser + ")");
	      forcedGenerationModeFlip = true;
	      prevUseAlternateClasses = useAlternateClasses;
	      flushNearestClasses ();
	      useAlternateClasses = false;
	      setGenerationMode1 (true); 
	    }
	  
	    if (!generationMode) // generation mode still off !...fail
	      throw new StubCreationException ("Interface Generation not allowed");
	  
	  } else {
	    classContents = buildPseudoClass(pseudoClassInfo,
					     className,
					     getUserInterfaceGenerator(),
					     systemClassNameMapper);
	  }
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "notFoundAtAll", g2ClassName);
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "trappedError", cnfe);
	
	  Structure classInfo;
	  String serFileName = null;
	  String generationPackage;
	  if (isInterface) {
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "dowloadingInfo", g2ClassName);
	    classInfo = (Structure) classInfoTable.get (g2ClassName);
	    if (classInfo == null)
	      classInfo = getClassInfo (g2ClassName, false);
	  } else if (isPseudoClass){
	    classInfo = null;
	  } else {
	    classInfo = (Structure) classInfoTable.get (g2ClassName);
	  }

	  Boolean isSystemDefined = isPseudoClass ? Boolean.FALSE :
	    (Boolean) classInfo.getAttributeValue (IS_SYSTEM_DEFINED_);
	  boolean isSystemClass = isSystemDefined.booleanValue ();
	  if (isPseudoClass) {
	    generationPackage = pseudoPackage;
	  } else {
	    if (isInterface) {
	      serFileName = writeClassInfo (className, g2ClassName, classInfo); // write out while pristine
	      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "ensureReqd");
	      initializeClassData (g2ClassName, classInfo);
	      String assignedPackage = determinePackageForClass (g2ClassName, isSystemClass);
	      ensureDependentClassesAreLoaded (classInfo, context);
	      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finishEnsure", g2ClassName);
	      if (isSystemClass)
		classFriend.register (g2ClassName,
				      makeInheritancePathFromClassInfo (classInfo), // optimize later
				      getClassAttrNames (classInfo));
	      resolveAttributeNameCollisions (g2ClassName, classInfo);
	    } 
	  
	    InterfaceGenerator igc = (isSystemClass ? igcg2 : getUserInterfaceGenerator());
	    Sequence ca = (Sequence) classInfo.getAttributeValue (CLASS_ATTRIBUTES_);
	    Sequence ia = (Sequence) classInfo.getAttributeValue (INSTANCE_ATTRIBUTES_, null);
	  
	    Sequence im = (Sequence) classInfo.getAttributeValue (INSTANCE_METHODS_, null);
	    // We dont expect the next two attributes unless an Export-definition defines them
	    Sequence sm = (Sequence) classInfo.getAttributeValue (STATIC_METHODS_, null);
	    String hm = (String) classInfo.getAttributeValue (HAND_CODED_METHODS_, "");
	    ClassOverrides hmOverrides = createOverridesFromHandCodedMethods(hm);
	  
	    ClassOverrides ov;
	    MethodInfo methodInfoArray[];
	    if (isInterface) {
	      Sequence directSupClasses =
		(Sequence) classInfo.getAttributeValue (DIRECT_SUPERIOR_CLASSES_);
	      if (traceOn)
		Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "directSups",
			    g2ClassName, directSupClasses.size(), directSupClasses);
	      Symbol[] superClasses;
	      if (directSupClasses.isEmpty()) {
		superClasses = new Symbol[] {BASE_INTERFACE_SYMBOL};
	      } else {
		superClasses = new Symbol[directSupClasses.size()];
		int i = 0;
		for (Enumeration e = directSupClasses.elements (); e.hasMoreElements (); i++)
		  superClasses[i] = (Symbol)e.nextElement ();
	      }
	    
	      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finSups", g2ClassName);
	      Symbol[] classInhPath = makeInheritancePathFromClassInfo (classInfo);
	      ov = (ClassOverrides) overridesTable.get (g2ClassName);
	      Hashtable overridesInfTable = new Hashtable(1);
	      if (ov != null){
	    	  overridesInfTable.put(g2ClassName, ov);
	      }
	      if (hmOverrides != null){
	    	  overridesInfTable.put(HAND_CODED_METHODS_, hmOverrides);
	      }
	      // -vkp, 7/14/98 workaround problem of defn having methods referencing the class it defines
	      boolean skipMethods = (isSystemClass || isDefinition (classInhPath));
	      if (skipMethods) // Dont generate method stubs for system classes
		methodInfoArray = new MethodInfo[0];
	      else
		methodInfoArray = generateG2MethodStubInfo(im, sm, g2ClassName, classInhPath, classInhPath, true, false);
	      generationPackage = (String) assignedPackages.get (g2ClassName);
	      //System.out.println ("Determined Package from table of " + g2ClassName + " to be : " + generationPackage);
	    
	      if (GensymApplication.getDevOption ())
		System.out.println ("Generating " + g2ClassName + " interface in " +
				    generationPackage);
	      classContents = generateInterface (igc, generationPackage, g2ClassName, superClasses,
						 classInhPath, ca, ia, methodInfoArray, overridesInfTable);
	      relocateClassInfo (serFileName, generationPackage);
	    } else {
	      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "collectAttrs", g2ClassName);
	      Symbol classToExtend = chooseClassToExtend(g2ClassName);
	      Symbol[] classesToCollect;
	      if (G2ClassSymbols.ROOT_.equals(g2ClassName)) {
		classesToCollect = new Symbol[] {G2ClassSymbols.ROOT_};
	      } else {
		loadClass(classToExtend, false);
		classesToCollect = collectClassesToCollect(g2ClassName, classToExtend);
	      }
	      if (traceOn)
		Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "chooseExtension",
			    classToExtend,
			    (traceOn ?
			     (Object)DebugUtil.printArray(classesToCollect) :
			     (Object)classesToCollect));
	    
	      ca = appendInheritedAttributes (ca, g2ClassName, classesToCollect, true);
	      ia = appendInheritedAttributes (ia, g2ClassName, classesToCollect, false);
	      Symbol[] classInhPath   = (Symbol[]) ClassInheritancePathTable.get (g2ClassName);
	    
	      boolean skipMethods = (isSystemClass || isDefinition (classInhPath));
	      if (skipMethods) // Dont generate method stubs for system classes and definitions
		methodInfoArray = new MethodInfo[0];
	      else
		methodInfoArray = generateG2MethodStubInfo(im, sm, g2ClassName, classInhPath, classesToCollect, false, false); 
	      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "endCollectAttrs", g2ClassName);
	      Hashtable overridesInhTable = collectInheritedOverrides (classesToCollect);
	      if (hmOverrides != null){
	    	  overridesInhTable.put(HAND_CODED_METHODS_, hmOverrides);
	      }
	    
	      Class intfClass = (Class) loadedInterfaces.get (g2ClassName);	// Never null?
	      String intfClassName = intfClass.getName ();
	      generationPackage = intfClassName.substring (0, intfClassName.lastIndexOf ('.'));
	    
	      if (GensymApplication.getDevOption ())
		System.out.println ("Generating " + g2ClassName + " stub in " +
				    generationPackage);
	      classContents = generateStub (igc, g2ClassName, classToExtend,
					    classesToCollect,
					    generationPackage, classInhPath,
					    ca, ia, methodInfoArray, overridesInhTable);
	    }
	  }
	  // compile
	  String repository = (isSystemClass || isPseudoClass ? g2Repository : userRepository);

	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "startCompiler");
	  if (classContents == null) {
	    try {
	      SourceCompiler.Compile (repository + (generationPackage + ".").replace ('.', sepChar) +
				      className + ".java");
	    } catch (JavaClassCompilerException jcce) {
	      //Trace.exception (jcce);
	      System.out.println ("Error compiling File. Discarding initial exception; will resolve in second compilation pass.");
	      classLoadingException = jcce;
	      //System.out.println ("Caught " + jcce + " while compiling " + g2ClassName);
	      //System.out.println ("   Class List = " + classDepthTracing.expand ());
	      if (g2ClassName.equals (classDepthTracing.elementAt (0))) {
		//debugIndent("Throwing jcce");
		classDepthTracing.removeElementAt (classDepthTracing.size () - 1);
		throw jcce;
	      }
	      //System.out.println ("Ignoring error in compiling inner class -> " + g2ClassName +
	      //	       " in package " + generationPackage);
	      uncompilableClasses.put (g2ClassName, generationPackage);
	      //debugIndent("catching JCCE remove");
	      if (!classDepthTracing.isEmpty()) {
		classDepthTracing.removeElementAt (classDepthTracing.size () - 1);
	      } else if (debug)
		System.out.println("Egads, classDepthTracing was empty (catching JCCE)!!!");
	      Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "quitUncompilable",
			  g2ClassName);
	      return null;
	    }
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "endCompiler"); 
	    String classFileName = (repository + (generationPackage + ".").replace ('.', sepChar) +
				    className + ".class");
	    // read, define, resolve class
	    File cFile = new File (classFileName);
	    int classFileLength = (int)cFile.length();
	    classContents = new byte[classFileLength]; 
	    DataInputStream CFStream = new DataInputStream (new FileInputStream (cFile));
	    CFStream.readFully(classContents);
	    CFStream.close();
	  }
	  clazz = defineClass (null, classContents, 0, classContents.length);
	  if (isSystemClass)
	    classFriend.register (g2ClassName, clazz);
	  resolveClass (clazz);

	  Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "classLoaded", g2ClassName, " after generation");
	  if (!IS_BOOTSTRAPPING && isInterface && !isPseudoClass)
	    makeClassDefinition (g2ClassName, clazz, isSystemClass);
	  loadedClasses.put (g2ClassName, clazz);
	  if (isPseudoClass) {
	    loadedStubs.put(g2ClassName, clazz);
	    loadedInterfaces.put(g2ClassName, clazz);
	    loadedStubs.put(clazz, clazz);
	  } else if (!isInterface) // Store mapping between interface and implementation class
	    loadedClasses.put (loadedInterfaces.get (g2ClassName), clazz);
	  /*System.out.println ("Loaded " + g2ClassName + " -> Currently loaded = " + loadedClasses +
	    "\nUncompilable = " + uncompilableClasses);*/
	  //debugIndent("!isInterface [not really] remove");
	  if (!classDepthTracing.isEmpty()) {
	    classDepthTracing.removeElementAt (classDepthTracing.size () - 1);
	  } else if (debug)
	    System.out.println("Egads, classDepthTracing was empty (hm.  where are we?  after compilation)");
	  //System.out.println ("Removing " + g2ClassName + " from assignedPackage after successful compile");
	  assignedPackages.remove (g2ClassName);
	  return clazz;
	} catch (StubCreationException se) {
	  classLoadingException = se;
	  se.printStackTrace ();
	  throw se; // recursive call to loadClass. let it unwind.
	} catch (Exception e) {
	  Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "excptLoadClass", className, e, classDepthTracing.expand ());
	  classDepthTracing.removeAllElements ();
	  esilDepth=0;
	  StubCreationException se = new StubCreationException ("Caught " + e.getClass().getName().toString() + "\n " + e.getMessage());
	  classLoadingException = se;
	  e.printStackTrace ();
	  throw se;
	} finally { // If we flipped the switch then flip it back...
	  if (forcedGenerationModeFlip) {
	    setGenerationMode1 (false);
	    useAlternateClasses = prevUseAlternateClasses;
	  }
	}
      } finally {
	// One way or the other, we are not loading this anymore
	synchronized (loadingClasses) {
	  loadingClasses.remove (g2ClassName);
	  if (loadedInterfaces.get (g2ClassName) != null &&
	      uncompilableClasses.get (g2ClassName) != null)
	    uncompilableClasses.remove (g2ClassName);
	  if (traceOn)
	    Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace, "exitLoadClass",
			g2ClassName, classDepthTracing.size (), classDepthTracing.expand ());
	  bestGuessForRecursionTable.remove(g2ClassName);
	  if (handedOutPartialClass && classLoadingException != null) {
	    loadedStubs.remove (g2ClassName); // We might have succeeded in initializing the stub!
	    fireInvalidationEvent (new Symbol[] {g2ClassName});
	  }
	}
      }
    }
  }

  /**
   * A wild guess as to what class to load when an unpleasant
   * recursion would otherwise cause us to return NULL.
   * @see com.gensym.classes.Interim__StubImpl
   */
  private Class getBestCurrentGuessForInterface(Symbol g2ClassName,
						Hashtable loadedClasses)
  {
    Symbol[] inhPath = getClassInheritancePath(g2ClassName);
    if (inhPath == null) {
      // should never reach here
      System.err.println("Trying to guess and failed for " + g2ClassName);
      return null;
    }

    for (int i = 0; i < inhPath.length; i++) {
      Class clazz = (Class)loadedClasses.get(inhPath[i]);
      if (clazz != null)
	return clazz;
    }

    // should never reach here
    System.err.println("Guess attempt failed for " + g2ClassName +
		       ";inhpath=" + DebugUtil.printArray(inhPath));
    return null;
  }

  private Class getBestCurrentGuessForStub(Symbol g2ClassName,
					   Hashtable loadedClasses)
  {
    try {
      return loadClass("com.gensym.classes.Interim__StubImpl");
    } catch (ClassNotFoundException cnfe) {
      Trace.exception(cnfe);
      throw new NoClassDefFoundError();
    }
  }

  private Class[] collectClassesToDelegate(Vector classesToBlendForLoad,
						  Symbol classToExtend) {
    int size = classesToBlendForLoad.size();
    Class[] classesToDelegate = new Class[size - 1];
    int j = 0;
    for (int i = 0; i < size; i++) {
      Symbol classSym = (Symbol)classesToBlendForLoad.elementAt(i);
      if (!classSym.equals(classToExtend)) {
	// note that since ensureSuperInterfacesLoaded has already been
	// called, then loadClass(classSym, true) has already been called
	classesToDelegate[j] = loadClass(classSym, false);
	j++;
      }
    }

    return classesToDelegate;
  }      

  /**
   * NOTE: if the classesToBlendLoad have any of the same
   * attribute names defined on them, then we have an unresolveable
   * conflict.
   */
  private byte[] buildPseudoClass(PseudoClassInfo pseudoClassInfo,
				 String className,
				 InterfaceGenerator ig,
				 ClassNameMapper nameMapper)
  throws IOException {
    Symbol className_ = pseudoClassInfo.pseudoClassName;
    if (GensymApplication.getDevOption())
      System.out.println("Building pseudo class: " + className_);

    Vector classesToBlendForLoad = pseudoClassInfo.classesToBlend;
    Symbol classToExtend_ = pseudoClassInfo.classToExtend;
    Class classToExtend = loadClass(classToExtend_, false);

    Class[] classesToDelegate =
      collectClassesToDelegate(classesToBlendForLoad, classToExtend_);

    return ig.generatePseudoStub(className,
				 pseudoPackage,
				 classToExtend,
				 classesToDelegate);
  }

  protected String generateClassName(Symbol g2ClassName, boolean isInterface,
			   boolean isPseudoClass) {
    if (isPseudoClass)
      return generatePseudoClassName(g2ClassName);
    else if (isInterface)
      return generateInterfaceName(g2ClassName);
    else
      return generateStubClassName(g2ClassName);
  }

  /**
   * @undocumented
   * NOTE: the validity of this limit needs to be
   * checked on every operating system.
   */
  public static final int FILE_NAME_LIMIT = 200; // should be safe

  String generatePseudoClassName(Symbol g2ClassName) {
    String stubName = generateStubClassName(g2ClassName);
    if (stubName.length() < FILE_NAME_LIMIT) {
      return stubName;
    } else { // make a digest to reduce collision possibilities
      try {
	MessageDigest md = MessageDigest.getInstance("MD5");
      
	// This is exactly how G2 hashes the username and password
	md.reset();
	md.update(stubName.getBytes(Charset.defaultCharset()));

	byte[] digest = md.digest();
	return "Long" + toHex(digest) + "Impl";
      } catch (NoSuchAlgorithmException nsae) {
	throw new UnexpectedException(nsae);
      }
    }
  }

  /**
   * Lifted from LoginRequest
   * @undocumented
   */
  public static String toHex(byte[] bytes) {
    int length = bytes.length;

    StringBuffer buf = new StringBuffer();

    for (int i = 0; i < length; i++) {
      int bite = bytes[i];
      if (bite < 0)
	bite = 256 + bite;
      
      if (bite < 16)
	buf.append("0");
      
      buf.append(Integer.toHexString(bite));
    }

    return buf.toString();
  }

      

  /**
   * @undocumented 
   */
  protected Class loadClassBytes(byte[] classbytes) {
    	Class clazz = defineClass (null, classbytes, 0, classbytes.length);
	resolveClass (clazz);
	return clazz;
  }   

  private boolean isDefinition (Symbol[] classInhPath) {
    for (int i=0; i<classInhPath.length; i++)
      if (G2ClassSymbols.DEFINITION_.equals(classInhPath[i]))
	return true;
    return false;
  }

  /**
   * The loader is in loadNearest Class mode:
   * Find the nearest loadable interface for a given user class (system classes are assumed to loadable)
   *   if the class is multi-inherited then
   *     if there is a loadable user class then generate a stub to preserve inheritance
   *     else no user class on inhertance path, load nearest system class
   *     There is no nearest class loaded for Event, Listener and G2 Java Proxy classes
   * <p>
   * The requirement of findAlternateClass is as follows:
   * There is a g2 class (called here G2-CLASS). For G2-CLASS, there
   * will be one or more super-classes (called here SUPER-CLASS[])
   * in g2 that have corresponding "loadable" java classes (JAVA-CLASS[])
   * available to the class loader. The following statement must be true:
   * For every instance INSTANCE of G2-CLASS, the java statement will return
   * a value of true: INSTANCE instanceof JAVA-CLASS[i] for every i.
   * <p>
   * For multiple inheritance, there is a list of "loadable" java interfaces
   * where none of the java interfaces inherits from any of the other
   * java interfaces in this list. A pseudo class is generated that implements
   * all of these interfaces.
   */
  private Class findAlternateClass (Symbol g2ClassName_, boolean isInterface) {
    if (isInterface) {
      Symbol[] startClassInhPath = getClassInheritancePath (g2ClassName_);
      //System.out.println ("Find Alternate Class for " + g2ClassName_ + " = " + DebugUtil.printArray (startClassInhPath));
      Symbol firstParent_ = startClassInhPath[1];
      Symbol[] superClassInhPath = getClassInheritancePath (firstParent_);
      Symbol altClassName_;
      if ((superClassInhPath.length != (startClassInhPath.length - 1)) && // Multiply inheriting
	  !isSubclassOfG2ProxyClass(startClassInhPath)) {                 // Not a "copy" subclass
	// Ensure G2 imported Java proxys are treated correctly
	Vector classesToBlend = getClassesToBlend(startClassInhPath);
	if (allowPseudoClasses) {
	  if (classesToBlend.size() == 1) {
	    Symbol newAltClass_ = (Symbol)classesToBlend.firstElement();
	    Class clazz = (Class)loadedInterfaces.get (newAltClass_);
	    Trace.send (ALWAYS_TRACE_LEVEL, traceKey, i18nTrace,
			"findAltClassSimple", newAltClass_, clazz);
	    if (clazz != null) {
	      nearestClassesTable.put (g2ClassName_, newAltClass_);
	      return clazz;
	    } else { // not sure when this would be, but proceed onto old code
	      throw new StubCreationException("Interface for alternate class " +
					      newAltClass_ +
					      " not found while loading " +
					      g2ClassName_);
	    }
	  } else {
	    // want to do as much as possible with module-qualified
	    // names to ensure no conflict between different G2's
	    // sharing the same java class repository.
	    try {
	      Symbol[] qualifiedNames = makeQualifiedNames(classesToBlend);
	      symbolSorter.quickSortInPlace(qualifiedNames);
	      Symbol pseudoClassName = makePseudoClassName(qualifiedNames);
	      Symbol classToExtend = chooseClassToExtend(classesToBlend);
	      Symbol[] pseudoClassesToCollect =
		getClassesToCollectForPseudo(pseudoClassName,
					     classesToBlend,
					     classToExtend);
	      PseudoClassInfo pseudoInfo =
		new PseudoClassInfo(pseudoClassName,
				    classToExtend,
				    classesToBlend,
				    pseudoClassesToCollect,
				    startClassInhPath);
	      pseudoClasses.put(pseudoClassName, pseudoInfo);
	      nearestClassesTable.put (g2ClassName_, pseudoClassName);
	      return loadClass(pseudoClassName, false);
	    } catch (G2AccessException g2ae) {
	      Trace.exception(g2ae);
	      throw new UnexpectedException(g2ae);
	    } catch (NoClassDefFoundError ncdfe) {
	      Trace.exception(ncdfe);
	      throw new UnexpectedException(ncdfe);
	    }
	  }
	}
	Symbol superClassName_ = startClassInhPath[1];
	altClassName_ = (Symbol) nearestClassesTable.get (superClassName_);
	if (altClassName_ == null)
	  altClassName_ = superClassName_;
	Symbol[] altCIP = getClassInheritancePath (altClassName_);
	//System.out.println ("     > Got " + altClassName_ + " as possible class for " + g2ClassName_);
	for (int i=2; i<startClassInhPath.length; i++) {
	  //System.out.println ("  MI#" + i + "> " + altClassName_);
	  Symbol currentSuperClassName_ = startClassInhPath[i];
	  Symbol currentSuperOrAltClassName_ = (Symbol) nearestClassesTable.get (currentSuperClassName_);
	  if (currentSuperOrAltClassName_ == null)
	    currentSuperOrAltClassName_ = currentSuperClassName_;
	  /*System.out.println ("      > reconciling " + currentSuperOrAltClassName_ +
	    "(alt for " + currentSuperClassName_ + ") with " + altClassName_);*/
	  if (!(altClassName_.equals (currentSuperOrAltClassName_))) {
	    Symbol newAltClassName_ = resolveMultipleInheritanceForAlternateClassLoad (altCIP, currentSuperOrAltClassName_);
	    //System.out.println ("      > Resolved -> " + newAltClassName_);
	    if (newAltClassName_ == null)
	      return null;
	    else if (!(newAltClassName_.equals (altClassName_))) {
	      altClassName_ = newAltClassName_;
	      altCIP = getClassInheritancePath (altClassName_);
	    }
	  }
	}
      } else {
	altClassName_ = (Symbol) nearestClassesTable.get (firstParent_);
	if (altClassName_ == null)
	  altClassName_ = firstParent_;
      }
      //classFriend.register (g2ClassName_, classInhPath, new Symbol[0]);
      nearestClassesTable.put (g2ClassName_, altClassName_);
      Class clazz = (Class)loadedInterfaces.get (altClassName_);
      if (GensymApplication.getDevOption ())
	System.out.println("Thin load of " + altClassName_ + "(" + clazz + ") for " + g2ClassName_);
      return clazz;
    } else {
      Symbol actualClassName_ = (Symbol) nearestClassesTable.get (g2ClassName_);
      if (actualClassName_ == null)
	return null;		// Force generation of this class Impl
      else
	return loadClass (actualClassName_, false);
    }
  }

  /**
   * Returns an array of all the classes in a class inheritance
   * path that have specific disjoint interfaces.
   * DISJOINT:
   * if A and B are both classes in the path, then A and B are
   * said to be disjoint if an instance of A is not an instance
   * of B and visa-versa. They likely share a common superclass,
   * but neither could be said to extend the other.
   * SPECIFIC:
   * An class is said to have a specific interface if its loadedInterface
   * is not a "nearest" interface.
   */
  private Vector getClassesToBlend(Symbol[] inheritancePath) {
    Symbol[] copyOfPath = (Symbol[])inheritancePath.clone();
    Vector classesToBlend = new Vector();

    for (int i = 0; i < copyOfPath.length; i++) {
      Symbol classToCheck = copyOfPath[i];
      if(classToCheck != null) {
	if(hasDedicatedInterface(classToCheck)) {
	  knockOutInheritancePath(classToCheck, copyOfPath, i);
	  classesToBlend.addElement(classToCheck);
	} else {
	  copyOfPath[i] = null;
	}
      }
    }

    return classesToBlend;
  }

  private final boolean hasDedicatedInterface(Symbol className_) {
    return (loadedInterfaces.get(className_) != null &&
	    nearestClassesTable.get(className_) == null);
  }

  private final void knockOutInheritancePath(final Symbol classToCheck,
		  				final Symbol[] path,
		  				final int start) {
    Symbol[] classesToExclude = getClassInheritancePath(classToCheck);
    int startIndex = start;
    for(int i = 0; i< classesToExclude.length; i++) {
      for(int j = startIndex; j < path.length; j++) {
	if(classesToExclude[i].equals(path[j])) {
	  startIndex = j + 1;
	  path[j] = null;
	  break;
	}
      }
    }
  }

  private static QuickSorter symbolSorter = 
  new QuickSorter () {
    @Override
    public boolean lessThan(Object a, Object b) {
      String aString = ((Symbol)a).getPrintValue();
      String bString = ((Symbol)b).getPrintValue();
      return aString.compareTo(bString) < 0;
    }
  };

  private Symbol makePseudoClassName(Symbol[] names) {
    StringBuffer buf = new StringBuffer();
    for (int i = 0; i < names.length - 1; i++) {
      buf.append(names[i].getPrintValue());
      buf.append(classSeparator);
    }
    buf.append(names[names.length - 1]);
    return Symbol.intern(buf.toString());
  }

  private Symbol[] makeQualifiedNames(Vector names) throws G2AccessException {
    int size = names.size();
    Symbol[] qualifiedNames = new Symbol[size];

    for (int i = 0; i < size; i++) {
      qualifiedNames[i] = makeQualifiedName((Symbol)names.elementAt(i));
    }
    return qualifiedNames;
  }

  private static final String moduleSeparator = "___-";
  private static final String classSeparator = "____-";

  private Symbol makeQualifiedName(Symbol name) throws G2AccessException {
    // we are assuming here that, because this class
    // already has a loaded interface, we can ask for its
    // definitions in a simple manner...
    G2Definition definition = context.getDefinition(name);
    if (definition instanceof ClassDefinition) {
      Symbol defnModule = ((ClassDefinition)definition).getContainingModule();
      String qualifiedString =
	defnModule.getPrintValue() + moduleSeparator + name.getPrintValue();
      return Symbol.intern(qualifiedString);
    } else
      return name;
  }
    


  private Symbol resolveMultipleInheritanceForAlternateClassLoad (Symbol[] classInhPath1,
								  Symbol className2_) {
    int i;
    Symbol className1_ = classInhPath1[0];
    for (i=1; i<classInhPath1.length; i++) {
      if (classInhPath1[i].equals (className2_))
	return className1_;
    }
    //System.out.println ("      > 1 : " + className2_ + " not in " + DebugUtil.printArray (classInhPath1));
    Symbol[] classInhPath2 = getClassInheritancePath (className2_);
    for (i=1; i<classInhPath2.length; i++) {
      if (classInhPath2[i].equals (className1_))
	return className2_;
    }
    //System.out.println ("      > 2 : " + className1_ + " not in " + DebugUtil.printArray (classInhPath2));
    return null;
  }
  

  MultiPackageChecker userPackageIterator = new MultiPackageChecker ();

  class MultiPackageChecker {

    MultiPackageChecker () {
    }

    long cum = 0;
    Class findUserClass (String className) {
      int numPackages = userPackages.size ();
      int failureCount = 0;
      long t0 = System.currentTimeMillis ();
      for (int i=numPackages-1; i>=0; i--) {
	//for (int i=0; i<numPackages - 1; i++) {
	try {
	  //System.out.println ("MultiPackageChecker:: Looking for " + (userPackages.elementAt (i) + className));
	  String packageForCurrentUserClass = (String) userPackages.elementAt (i);
	  Class clazz = findSystemClass1 (packageForCurrentUserClass + className);
	  if (i != numPackages - 1)  {// If successful, move to end
	    userPackages.removeElementAt (i);
	    userPackages.addElement (packageForCurrentUserClass);
	  }
	  long t1 = System.currentTimeMillis ();
	  cum += (t1 - t0);
	  //System.out.println ("Loading " + className + " took " + (t1 - t0) + "ms (Total = " +
	  //	      cum + ") - " + failureCount + " failures");
	  return clazz;
	} catch (ClassNotFoundException cnfe) {
	  Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "userClassNotFound",
		      cnfe);
	  failureCount++;
	}
      }
      return null;
    }

    Class findUserClass (String className, String packageNameWithDot) {
      try {
	return findSystemClass1 (packageNameWithDot + className);
      } catch (ClassNotFoundException cnfe) {
	//System.out.println (cnfe + " while attempting " + packageNameWithDot + className);
	// This is OK!
	return null;
      }
    }

  }

  protected ClassNameMapper systemClassNameMapper = new ClassNameMapper () {
    private String stdPrefix = System.getProperty ("com.gensym.class.g2.package") + ".";
    private String g2VersionString;
    @Override
    public String javaClassNameFromG2ClassName (Symbol g2ClassName_) {
      return stdPrefix + G2ClassTranslator.createJavaClassNameFromG2ClassName (g2ClassName_);
    }
    @Override
    public String getVersionForClass (Symbol g2ClassName_) {
      //ignore class-name
      if (g2VersionString == null) {
	G2Version g2Version = context.getG2Version ();
	String revType = g2Version.getReleaseQuality ();
	StringBuffer buf = new StringBuffer (20);
	g2VersionString = buf.append (g2Version.getMajorVersion ())
	                     .append (".")
	                     .append (g2Version.getMinorVersion ())
	                     .append (" ")
	                     .append (revType)
	                     .append (" ")
	                     .append (g2Version.getRevision ())
	                     .append (" (")
	                     .append (g2Version.getBuildID ())
	                     .append (")").toString ();
      }
      return g2VersionString;
    }
  };

  protected Hashtable getLoadedInterfaces() {
    return loadedInterfaces;
  }

  protected String lookupAssignedPackage(Symbol g2ClassName) {
    return (String)assignedPackages.get(g2ClassName);
  }

  protected Hashtable getLoadedStubs() {
    return loadedStubs;
  }  
 
  protected ClassNameMapper userClassNameMapper = new ClassNameMapper () {
    //private String sysPrefix = System.getProperty ("com.gensym.class.g2.package") + ".";
    private String stdPrefix = getUserPackage() + ".";
    @Override
    public String javaClassNameFromG2ClassName (Symbol g2ClassName_) {
      Class clazz = (Class)loadedInterfaces.get (g2ClassName_);
      if (clazz == null) {
	String previouslyAssignedPackage = (String) assignedPackages.get (g2ClassName_);
	if (previouslyAssignedPackage != null) {
	  //System.out.println (">>> NameMapper: " + g2ClassName_ + " -> previously assigned to " + previouslyAssignedPackage);
	  stdPrefix = previouslyAssignedPackage + ".";
	} else {
	  // Please leave this alone!
	  System.out.println (">>> NameMapper: " + g2ClassName_ + " -> Duh? returning fallback " + stdPrefix);
	  Thread.dumpStack ();
	  System.out.println ("Class Queue = " + classDepthTracing.expand ());
	  throw new Error("Can't find package for G2 class:" + g2ClassName_ + " Call gensym customer support");
	  //System.exit (2);
	}
	return stdPrefix + G2ClassTranslator.createJavaClassNameFromG2ClassName (g2ClassName_);
      } else {
	//System.out.println (">>> NameMapper: " + g2ClassName_ + " -> Previously loaded class : " + clazz.getName ());
	return clazz.getName ();
      }
    }
    @Override
    public String getVersionForClass (Symbol g2ClassName_) {
      return "5.1 Rev. 1"; // determine from module-information-object
    }
  };


  /*
   * This method is used to bounce the call to findSystemClass.
   * This works around a bug in the JDK 1.1.5- compiler that inner
   * classes do not have access to inherited protected methods of
   * the outer class.
   */
  private Class findSystemClass1 (String className) throws java.lang.ClassNotFoundException {
    return Class.forName (className,
			  true, 
			  Thread.currentThread().getContextClassLoader());
  }

  protected byte[] generateInterface (InterfaceGenerator igc,
				  String generationPackage,
				  Symbol g2ClassName,
				  Symbol[] superClassNames,
				  Symbol[] classInheritancePath,
				  Sequence classAttrDescrpns,
				  Sequence attrDescrpns,
				  MethodInfo[] methodInfoArray,
				  Hashtable overridesTable) throws IOException, JavaClassCompilerException {

    igc.generateInterface (g2ClassName,
			   generationPackage,
			   superClassNames, 
			   classInheritancePath, 
			   classAttrDescrpns, 
			   attrDescrpns, 
			   methodInfoArray, 
			   overridesTable);

    // Dont bother creating external event and listener classes for Proxy classes
    if (getRealG2ClassForG2ProxyClass(g2ClassName,
				      classInheritancePath) != null) return null;  

    // This interface may also extend G2-EVENT-OBJECT, is which case we must
    // create a separate event class that extends java.util.EventObject
    boolean eventClass = isG2ClassG2EventClass(g2ClassName);

    // This interface may also extend G2-EVENT-OBJECT, is which case we must
    // create a separate event class that extends java.util.EventObject
    if (isG2EventClass(g2ClassName, classInheritancePath)) {
      String filename = igc.generateExternalG2EventInterface(g2ClassName, 
							     generationPackage,
							     superClassNames, 
							     classInheritancePath, 
							     classAttrDescrpns, 
							     attrDescrpns, 
							     methodInfoArray, 
							     overridesTable);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "startCompiler");
      SourceCompiler.Compile (filename);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "endCompiler");	
    }

    // This interface may also extend G2-EVENT-LISTENER, is which case we must
    // create a separate event listener interface that extends java.util.EventListener
    if (isG2ListenerClass(g2ClassName, classInheritancePath)) {
      String filename = igc.generateExternalG2ListenerInterface(g2ClassName,
							     generationPackage,
							     superClassNames, 
							     classInheritancePath, 
							     classAttrDescrpns, 
							     attrDescrpns, 
							     methodInfoArray, 
							     overridesTable);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "startCompiler");
      SourceCompiler.Compile (filename);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "endCompiler");
    }

    return null;
  }

  private Sequence getDirectSuperiorClasses(Symbol g2ClassName) {
    Sequence directSuperiors = new Sequence(), classInhList = new Sequence();
    Symbol[] classInhPath = getClassInheritancePath (g2ClassName);
    for (int i=1; i<classInhPath.length; i++) {
      Symbol superClassName = classInhPath[i];
      if (!classInInheritancePathOfCurrentSuperiors (superClassName, classInhList)) {
	directSuperiors.addElement (superClassName);
	classInhList.addElement (getClassInheritancePath(superClassName));
      }
    }
    return directSuperiors;
  }

  /**
   * Determines if className is already present in the inheritance path of
   * all the classes that have been collected so far as established parents.
   */
  private boolean classInInheritancePathOfCurrentSuperiors (Symbol className,
							    Vector classInhList) {
    for (int i=0; i<classInhList.size (); i++) {
      Symbol[] inhPath = (Symbol[]) classInhList.elementAt (i);
      for (int j=0; j<inhPath.length; j++)
	if (className.equals (inhPath[j]))
	  return true;
    }
    return false;
  }

  private Symbol chooseClassToExtend(Symbol g2ClassName) {
    if (G2ClassSymbols.ROOT_.equals(g2ClassName))
      return null;

    Sequence directSuperiors = getDirectSuperiorClasses(g2ClassName);
    return chooseClassToExtend(directSuperiors);
  }

  private Symbol chooseClassToExtend(Vector directSuperiors) {
    Symbol mostValuableParent = (Symbol)directSuperiors.firstElement();
    int extensionValue = determineExtensionValue(mostValuableParent);

    int size = directSuperiors.size();

    for (int i = 1; i < size; i++) {
      Symbol superior = (Symbol)directSuperiors.elementAt(i);
      int currExtensionValue = determineExtensionValue(superior);
      if (currExtensionValue > extensionValue) {
	extensionValue = currExtensionValue;
	mostValuableParent = superior;
      }
    }

    return mostValuableParent; // will never be null
  }

  /**
   * returns the number of classes in the inheritancePath that
   * have overrides.
   */
  private int determineExtensionValue(Symbol g2ClassName) {
    int extensionValue = 0;
    Symbol[] inheritancePath = getClassInheritancePath(g2ClassName);

    for (int i = 0; i < inheritancePath.length; i++) {
      ClassOverrides overrides =
	(ClassOverrides)overridesTable.get(inheritancePath[i]);
      if (overrides != null)
	extensionValue++;
    }

    return extensionValue;
  }

  private Symbol[] collectClassesToCollect(Symbol g2ClassName, Symbol classToExtend) {

    Symbol[] 
      baseInheritancePath = getClassInheritancePath(g2ClassName),
      superInheritancePath = getClassInheritancePath(classToExtend);
    return knockOutSuperClasses(baseInheritancePath, superInheritancePath);
  }

  private static Symbol[] knockOutSuperClasses(Symbol[] baseInheritancePathIn,
					       Symbol[] superInheritancePath) {
    Symbol[] baseInheritancePath = (Symbol[])baseInheritancePathIn.clone();
    int excluded = 0;

    // take out everything in baseInheritancePath that is also in
    // superInheritancePath
    for(int i = 0; i< superInheritancePath.length; i++) {
      int start = 1;
      for(int j = start; j < baseInheritancePath.length; j++) {
	if(superInheritancePath[i].equals(baseInheritancePath[j])) {
	  excluded++;
	  start = j + 1;
	  baseInheritancePath[j] = null;
	  break;
	}
      }
    }

    Symbol[] classesToCollect =
      new Symbol[baseInheritancePath.length - excluded];
    int index = 0;
    for(int i = 0; i < baseInheritancePath.length; i++) {
      if (baseInheritancePath[i] != null)
	classesToCollect[index++] = baseInheritancePath[i];
    }

    return classesToCollect;
  }

  Symbol[] getClassesToCollectForPseudo(Symbol pseudoClassName,
					Vector classesToBlend,
					Symbol classToExtend) {
    return collectAllSuperClassesExcept(pseudoClassName,
					classesToBlend,
					classToExtend);
  }

  private boolean symbolArrayContainsSymbol(Symbol[] array, Symbol object) {
    for(int i = 0; i < array.length; i++) {
      if (object.equals(array[i]))
	return true;
    }
    return false;
  }

  /**
   * This does not keep the same order as the classes appeared
   * in the original inheritance path from which classesToBlend
   * was derived.
   */
  Symbol[] collectAllSuperClassesExcept(Symbol pseudoClassName,
					Vector classesToBlend,
					Symbol classToExtend) {
    Symbol[] unneededSuperClasses =
      getClassInheritancePath(classToExtend);
    Vector superClasses = new Vector();
    superClasses.addElement(pseudoClassName);
    int size = classesToBlend.size();
    for (int i = 0; i < size; i++) {
      Symbol clazz = (Symbol)classesToBlend.elementAt(i);
      if (!clazz.equals(classToExtend)) {
	Symbol[] currentInhPath = getClassInheritancePath(clazz);
	for (int j = 0; j < currentInhPath.length; j++) {
	  Symbol superClass = currentInhPath[j];
	  if (!symbolArrayContainsSymbol(unneededSuperClasses, superClass) &&
	      !superClasses.contains(superClass)){
	    superClasses.addElement(superClass);
	  }
	}
      }
    }
    Symbol[] returnValue = new Symbol[superClasses.size()];
    superClasses.copyInto(returnValue);
    return returnValue;
  }

//   /**
//    * this is the start of a method that would keep the order.
//    */
//   private Symbol[] knockOutNonSuperClasses(Symbol[] inhPathIn,
// 					   Vector classesToBlend) {
//     Symbol[] inhPath = (Symbol[])inhPathIn.clone();
//     Symbol[] collected = new Symbol[inhPath.length];
//     int size = classesToBlend.size();

//     for (int i = 0; i < size; i++) {
//       Symbol clazz = (Symbol)classesToBlend.elementAt(i);
//       Symbol currentInhPath
//     for (int i = 0; i < inhPath.length; i++) {
//       if

  protected byte[] generateStub (InterfaceGenerator igc,
				 Symbol g2ClassName, 
				 Symbol classToExtend,
				 Symbol[] classesToCollect,
				 String generationPackage, 
				 Symbol[] classInhPath,
				 Sequence ca, 
				 Sequence ia, 
				 MethodInfo[] methodInfoArray, 
				 Hashtable overridesInhTable) throws IOException
  {
    Class javaClassToExtend =
      G2ClassSymbols.ROOT_.equals(g2ClassName) ?
      BASE_JAVA_CLASS :
      (Class)loadedStubs.get(classToExtend); // better be there already!

    igc.generateStub (g2ClassName, javaClassToExtend, classesToCollect,
		      generationPackage, classInhPath,
		       ca, ia, methodInfoArray, overridesInhTable);

     return null;
 }
  

  /*
   * This can be used to determine the java package assignment for a G2
   * class. It should only be called for classes that have not been
   * loaded i.e. classes not seen before or classes that failed
   * compilation in a previous pass.
   */
  private String determinePackageForClass (Symbol g2ClassName_, boolean isSystemClass) {
    if (isSystemClass) {
      assignedPackages.put (g2ClassName_, g2PackageWithoutTrailingDot);
      return g2PackageWithoutTrailingDot;
    } else {
      String packageForClassFailingCompilation = (String) uncompilableClasses.get (g2ClassName_);
      if (packageForClassFailingCompilation != null)
	return packageForClassFailingCompilation;
      String pkgForClass = (String) assignedPackages.get (g2ClassName_);
      if (pkgForClass != null)
	return pkgForClass;
      if (fetchingDefinitions.get (g2ClassName_) != null)
	return "";
      try {
	System.err.println ("determinePackageForClass (" + g2ClassName_ + ") got a cache miss. Please report to Customer Service.");
        // Keep going
	ClassDefinition definition = ((DefinitionInfo)pendingDefinitions.get (g2ClassName_)).defn;
	Object x = null;
	//*context.getUniqueNamedItem (com.gensym.util.symbol.G2ClassSymbols.DEFINITION_, g2ClassName_);
	//System.out.println ("PD.get (" + g2ClassName_ + ") = " + x);
	if (false) {// definition != x) {
	  Thread.dumpStack ();
	  throw new Error ("Internal Error at 0! for class " + g2ClassName_ + " : " +
			   definition + " != " + x);
	}
	Symbol defnModule_ = definition.getContainingModule ();
	pkgForClass = getPackageNameForModule (defnModule_);
	assignedPackages.put (g2ClassName_, pkgForClass);
	return pkgForClass;
      } catch (G2AccessException gae) {
	Trace.exception (gae);
	throw new StubCreationException (gae.getMessage ());
      }
    }
  }

  private static final Symbol G2_GET_SHORT_CLASS_INFO_ = Symbol.intern ("G2-GET-SHORT-CLASS-INFO");
  private static final Symbol G2_GET_CLASS_INHERITANCE_PATH_ = Symbol.intern ("G2-GET-CLASS-INHERITANCE-PATH");

  private static final boolean useNewAPI = true;
  private String getPackageForLoadableUserClass (String className, Symbol g2ClassName_, boolean isInterface) {
    try {
      if (isInterface) {
	ClassDefinition definition;
	Symbol defnModule_;
	Sequence clsInhPathSeq;
	// Keep track of the fact that we can't determine module until we get the definition
	fetchingDefinitions.put (g2ClassName_, g2ClassName_);
	if (!useNewAPI) {
	  definition= (ClassDefinition) context.getUniqueNamedItem
	    (com.gensym.util.symbol.G2ClassSymbols.DEFINITION_,
	     g2ClassName_);
	  defnModule_ = definition.getContainingModule ();
	  clsInhPathSeq = (Sequence) context.callRPC (G2_GET_CLASS_INHERITANCE_PATH_,
						       new Object[] {g2ClassName_});
	} else {
  	  Sequence classData = (Sequence) context.callRPC (G2_GET_SHORT_CLASS_INFO_,
  							   new Object[] {g2ClassName_});
  	  clsInhPathSeq = (Sequence) classData.elementAt (0);
  	  definition = (ClassDefinition) classData.elementAt (1);
  	  defnModule_ = (Symbol) classData.elementAt (2);
	}
	Symbol[] clsInhPath = new Symbol[clsInhPathSeq.size()];
	clsInhPathSeq.copyInto (clsInhPath);
	ClassInheritancePathTable.put (g2ClassName_, clsInhPath);
	fetchingDefinitions.remove (g2ClassName_);  // Module known
	/*
	System.out.println ("Using " + (useNewAPI ? "new" : "old") +
			    " API -> Defn " + definition + " for " + g2ClassName_ + " in module " +
			    defnModule_);
	System.out.println (" >> CIP.put (" + g2ClassName_ + ", " + clsInhPathSeq);
	*/
	String pkgName = getPackageNameForModule (defnModule_);
	DefinitionInfo defnInfo = new DefinitionInfo (definition, defnModule_);
	pendingDefinitions.put (g2ClassName_, defnInfo);
	assignedPackages.put (g2ClassName_, pkgName);
	//System.out.println ("PD.put (" + g2ClassName_ + ") = " + definition);
	//System.out.println ("Returning package : " + pkgName + " for " + g2ClassName_); 
	return pkgName;
      } else {
	Class intfClass = (Class) loadedInterfaces.get (g2ClassName_);
	if (intfClass == null)
	  intfClass = (Class) currentlyLoadingDefinitions.get (g2ClassName_);
	String intfClassName = intfClass.getName();
	return intfClassName.substring (0, intfClassName.lastIndexOf ('.'));
      }
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
      throw new StubCreationException ("Unknown class - " + className + " : " + g2ae.getMessage ());
    }
  }

  /**
   * Returns a package for the named module.
   * The return value has no trailing dot.
   */
  protected String getPackageNameForModule (Symbol moduleName_) {
    String pkgName = null;
    if (moduleName_ == null)
      pkgName = unspecifiedPackage;
    else {
      if (moduleMappingTable == null) // unnecessary. see label call1_to_refreshModuleMappings
	refreshModuleMappings (true);
      ModuleInfo modinfo = (ModuleInfo)moduleMappingTable.get (moduleName_);
      if (modinfo != null)
	pkgName = modinfo.javaPackageForModule;
      if (pkgName == null) {
	refreshModuleMappings (false);
	modinfo = (ModuleInfo)moduleMappingTable.get (moduleName_);
	if (modinfo != null)
	  pkgName = modinfo.javaPackageForModule;
      }
      if (pkgName == null) // We should already have a name from refreshModuleMappings for all modules.
	throw new Error ("Assertion Violation: No package name found in getPackageNameForModule. Please call customer support!");
    }
    return pkgName;
  }
    
  private boolean inRefreshContext = false;
  /**
   * Called to update the module-mappings hash table. It only
   * adds new entries and never changes existing entries.
   * This means that module-maps are valid for the life of the
   * StubClassLoader. This makes sense because any modification
   * would invalidate already generated classes in that package.
   *
   * - 6/30/98 Made this a synchronized method. Do not call this
   * method unless you have to. Initially it is called if the
   * table has not been set up. In that case, we make a new table
   * and set it to the instance field after it is initialized.
   */
  private void refreshModuleMappings (boolean makeNewTable) {
    Hashtable x = moduleMappingTable;
    if (makeNewTable) {
      if (moduleMappingTable == null) {
	x = new Hashtable (7);
      } else
	return;			// Competing thread made the table
    }
    try {
      if (inRefreshContext) {	// ModuleInformation was not found on the CLASSPATH?
	if (traceOn)
	  Trace.send (DEF_WARN_LEVEL, traceKey, i18nTrace, "recursionInRMM",
		      classDepthTracing.expand ());
	return;
      }
      inRefreshContext = true;
      //System.out.println ("Calling getModuleInstances ()");
      Sequence moduleInfos = getModuleInstances ();
      /*System.out.println ("Moduleinfos = an instance of " + moduleInfos.getClass ().getName () +
			  " with " + moduleInfos.size () + " elements ");
			  System.out.flush ();
    
      System.out.println ("System.out.println getModuleInstances () = " + moduleInfos.expand ());*/
      for (Enumeration e = moduleInfos.elements ();
	   e.hasMoreElements ();) {
	ModuleInformation mi = (ModuleInformation) e.nextElement ();
	Symbol moduleName_   = mi.getTopLevelModule ();
	if (moduleName_ != null && x.get (moduleName_) == null) {
	  Sequence moduleAnnotations = mi.getModuleAnnotations ();
	  ModuleInfo moduleInfo =
	    makeModuleInfo(moduleAnnotations, moduleName_);
	  String javaExportPackageForModule = 
	    moduleInfo.javaPackageForModule;
	  x.put (moduleName_, moduleInfo);
	  pkgToModuleMap.put (javaExportPackageForModule, moduleName_);
	  userPackages.addElement (javaExportPackageForModule + ".");
	}
      }
    } catch (G2AccessException gae) {
      Trace.exception (gae);
      throw new StubCreationException (gae.getMessage ());
    } finally {
      inRefreshContext = false;
      if (moduleMappingTable == null)
	moduleMappingTable = x;
    }
  }

  /**
   * @undocumented 
   */
  public void loseModuleMappings() {
    moduleMappingTable = null;
  }

  private static final Symbol JAVA_PACKAGE_FOR_EXPORT_
                    = Symbol.intern ("JAVA-PACKAGE-FOR-EXPORT");
  private static final Symbol ANNOTATION_NAME_
                    = Symbol.intern ("ANNOTATION-NAME");
  private static final Symbol ANNOTATION_VALUE_
                    = Symbol.intern ("ANNOTATION-VALUE");
  private static final Symbol MODULE_IS_STABLE_
                    = Symbol.intern ("MODULE-IS-STABLE");

  /**
   * Return the exported PackageName for a Module
   */
  protected ModuleInfo makeModuleInfo(Sequence moduleAnnotations, Symbol moduleName_) {
    String javaExportPackageForModule = 
      getSpecificAnnotation (moduleAnnotations, JAVA_PACKAGE_FOR_EXPORT_);
    if (javaExportPackageForModule == null) {
      String packageName = makeJavaPackageNameForModule (moduleName_);
      javaExportPackageForModule = userPackage + packageName;
    }
    Object moduleStabililityAnnotation = 
      getSpecificAnnotation (moduleAnnotations, MODULE_IS_STABLE_);
    boolean moduleIsStable;
    if (moduleStabililityAnnotation == null)
      moduleIsStable = false;
    else
      moduleIsStable = (moduleStabililityAnnotation instanceof Boolean ?
			 (Boolean) moduleStabililityAnnotation :
			 new Boolean ((String)moduleStabililityAnnotation)).booleanValue();
    return new ModuleInfo (javaExportPackageForModule, moduleIsStable);
  }

  /**
   * Called only for user classes
   */
  private boolean moduleOfClassIsStable (Symbol g2ClassName_, boolean isInterface) {
    Symbol defnModule_;
    if (isInterface)
      defnModule_ = ((DefinitionInfo)pendingDefinitions.get (g2ClassName_)).moduleName_;
    else { // depends on unique module -> package names
      Class intfClass = (Class) loadedInterfaces.get (g2ClassName_); // guaranteed non-null
      String intfClassName = intfClass.getName();
      String pkgName = intfClassName.substring (0, intfClassName.lastIndexOf ('.'));
      defnModule_ = (Symbol)pkgToModuleMap.get (pkgName);
      if (defnModule_ == null) // unspecified module
	return false;
    }
    return ((ModuleInfo)moduleMappingTable.get (defnModule_)).moduleIsStable;
  }
  /**
   * Extracts the package prefix specified in the module-annotations
   * Sequence.
   * @param annotations the annotations Sequence
   * @return String the package-prefix (may be null)
   */
  protected String getSpecificAnnotation (Sequence annotations, Symbol interestedAnnotationName) {
    for (Enumeration e = annotations.elements ();
	 e.hasMoreElements ();) {
      Structure annotation   = (Structure) e.nextElement ();
      Symbol annotationName_ = (Symbol) annotation.getAttributeValue (ANNOTATION_NAME_, null);
      if (annotationName_.equals (interestedAnnotationName)) { // can never be null?
	Object annotationValue = annotation.getAttributeValue (ANNOTATION_VALUE_, null);
	if (annotationValue instanceof String)
	  return (String)annotationValue;
	else
	  return null;
      }
    }
    return null;
  }


  private static final Symbol MODULE_INFORMATION_
                  = Symbol.intern ("MODULE-INFORMATION");
  private static final Symbol G2_GET_ITEMS_OF_CLASS_
                  = Symbol.intern ("G2-GET-ITEMS-OF-CLASS");
  /**
   * Retrieves all instances of MODULE-INFORMATION
   * items from the context.
   * @return A Sequence of all the module-information items.
   * @exception G2AccessException if there are communucation problems
   */
  private Sequence getModuleInstances () throws G2AccessException {
    Sequence modules = context.getStrictInstancesOfClass (MODULE_INFORMATION_);
    return modules;
  }

  /**
   * Creates a package name from a module name by
   * (1) lowercasing the symbol
   * (2) discarding non-alphanumeric characters
   */
  protected String makeJavaPackageNameForModule (Symbol moduleName_) {
    String modName = moduleName_.getPrintValue ().toLowerCase ();
    StringBuffer pkg = new StringBuffer ();
    for (int i=0; i<modName.length(); i++) {
      char c = modName.charAt (i);
      if ((c >= 'a' && c <='z') || (c >= '0' && c <= '9')) // discard all other characters
	pkg.append (c);
    }
    if (pkg.length () > 0 && Character.isDigit (pkg.charAt (0)))
      pkg.insert (0, 'n');
    return pkg.toString ();
  }

  private static final Symbol G2_GET_CLASS_INFO_ = Symbol.intern ("G2-GET-CLASS-INFO");

  protected Structure getClassInfo (Symbol className, 
				  boolean includeInheritedAttributes) 
       throws G2AccessException{
    Object[] args = new Object[] {className, (includeInheritedAttributes ? Boolean.TRUE : Boolean.FALSE)};
    Structure retnvalue = (Structure)context.callRPC (G2_GET_CLASS_INFO_, args, 0);
    return (Structure)retnvalue;
  }


  /*
   * This is a weaker cousin of the next method. It is
   * called when generationMode is turned off to ensure that
   * the super class definitions are loaded into the
   * ClassManager
   */
  protected void ensureSuperInterfacesAreLoaded (Symbol[] classInheritancePath) {
//     Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "ensureSuperShort",
// 		DebugUtil.printArray (classInheritancePath));
    /*
      // You would think this would be faster. I certainly did :-<
    if (classInheritancePath.length == 1)
      return;
    Symbol superClassName_ = classInheritancePath[1];
    if (loadedInterfaces.get (superClassName_) != null) {
      Symbol[] superInhPath = classFriend.getClassInheritancePath (superClassName_);
      if (superInhPath.length == (classInheritancePath.length - 1))
	return;
    }
    */
    //long t0 = System.currentTimeMillis ();
    for (int i=1; i<classInheritancePath.length; i++) {
      if (traceOn)
	Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "ensureSuperLoadingClass",
		    classInheritancePath[0], i, classInheritancePath[i]);
      loadClass (classInheritancePath[i], true);
    }
    //classes[xx] = classInheritancePath [0];
    //times[xx++] = System.currentTimeMillis () - t0;
    //cumul += times[xx - 1];
  }

//   private Symbol[] classes = new Symbol[1000];
//   private long[] times = new long[1000];
//   private int xx = 0;
//   private long cumul = 0;


//   public void dump () {
//     for (int i=0; i<xx; i++)
//       System.out.println (classes[i] + " = " + times[i]);
//     System.out.println (cumul + " for " + xx + " classes");
//   }

  /**
   * Does the job of ensuring that all necessary classes are loaded
   * and ensures that the dependent classes are noted
   */
  protected void ensureDependentClassesAreLoaded (Structure classInfo, G2Access context) {
    Sequence classInhPathSeq = 
      (Sequence) classInfo.getAttributeValue (CLASS_INHERITANCE_PATH_, null);
    if (traceOn)
      Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "depClassLoad",
		  classInhPathSeq.elementAt (0));
    classInhPathSeq = (Sequence)classInhPathSeq.clone ();
    ensureSuperInterfacesAreLoaded (classInfo, context);
    Sequence requiredClasses = ensureEmbeddedClassesAreLoaded (classInfo, context);
    classInhPathSeq.concatenate (requiredClasses);
    /*System.out.println ("Required Classes for " +
			classInhPathSeq.elementAt (0) +
			" = " + requiredClasses);*/
    int numClasses = classInhPathSeq.size ();
    Symbol[] dependentClasses = new Symbol [numClasses];
    classInhPathSeq.copyInto (dependentClasses);
    if (traceOn)
      Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "depClassesList",
		  dependentClasses[0], DebugUtil.printArray (dependentClasses));
    dependentClassesTable.put (dependentClasses[0], dependentClasses);
  }


  /**
   * Makes sure the class is initialized before getting the dependent classes
   */
  public Symbol[] getDependentClasses (Symbol g2ClassName) {
    if (uninitlzedClasses.get (g2ClassName) != null) {
      try {
	generationMode = true;
	loadClass (g2ClassName, true);
      } finally {
	generationMode = false;
      }
    }
    return (Symbol[]) dependentClassesTable.get (g2ClassName);
  }

  /**
   * @undocumented For CDGCLIENT preloading. Review before making public.
   * @return an array containing the names of the classes that have actually been
   * transferred over this connection.
   */
  public Symbol[] getStubClasses () {
    Vector classes = new Vector ();
    synchronized (loadedStubs) {
      Enumeration e = loadedStubs.keys ();
      while (e.hasMoreElements ())
	classes.addElement (e.nextElement ());
    }
    int numClasses = classes.size ();
    Symbol[] retnClasses = new Symbol[numClasses];
    classes.copyInto (retnClasses);
    return retnClasses;
  }

  private volatile int esilDepth;
  private void ensureSuperInterfacesAreLoaded (Structure classInfo, G2Access context) {
    try {
      Symbol g2ClassName = (Symbol)classInfo.getAttributeValue (CLASS_NAME_);
      esilDepth++;
      if (traceOn)
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterESIL", g2ClassName,
		    esilDepth, Thread.currentThread ());
      Sequence supG2Classes = (Sequence) classInfo.getAttributeValue (DIRECT_SUPERIOR_CLASSES_);
      if (supG2Classes.isEmpty()) {
    	  esilDepth--;
    	  return;
      } // ROOT!
      if (traceOn)
	Trace.send (MINIMAL_TRACE_LEVEL, traceKey, i18nTrace, "checkSups",
		    supG2Classes.size (),
		    classInfo.getAttributeValue (CLASS_NAME_),
		    supG2Classes.expand ());
      for (Enumeration e = supG2Classes.elements (); e.hasMoreElements ();) {
	Symbol superClass = (Symbol) e.nextElement ();
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "intfCheck", superClass);
	loadClass (superClass, true);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "intfDone", superClass);
      }
      if (traceOn)
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "exitESIL", g2ClassName,
		    esilDepth, Thread.currentThread ());
      esilDepth--;
    } catch (NoSuchAttributeException nsfe) {
      //Trace
      Trace.exception (nsfe);
      System.err.println (nsfe);
      System.exit (2);
    }
  }


  private Sequence ensureEmbeddedClassesAreLoaded (Structure classInfo, G2Access context) {

    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterESCL");
    Sequence requiredClasses = new Sequence (5);
    try {
      Symbol g2ClassName = (Symbol)classInfo.getAttributeValue (CLASS_NAME_);

      Sequence attClasses = (Sequence) classInfo.getAttributeValue (CLASS_ATTRIBUTES_);
      if (traceOn)
	Trace.send (MINIMAL_TRACE_LEVEL, traceKey, i18nTrace, "checkVarClass",
		    attClasses.size (),
		    classInfo.getAttributeValue (CLASS_NAME_));
      Enumeration e = attClasses.elements ();
      while (e.hasMoreElements ()) {
        Structure attInfo = (Structure) e.nextElement ();
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "checkAttrClass", attInfo);
	Structure typeInfo = (Structure) attInfo.getAttributeValue(TYPE_, null);
	if (typeInfo == null)
	  continue;
	Symbol attClass = TypeHandler.getTypeFromTypeDescription (typeInfo);
	if (!TypeHandler.isClassType (attClass))
	  continue;
	if (g2ClassName.equals(attClass))
	  continue;

	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "checkEmbIntf", attClass, g2ClassName);
	loadClass (attClass, true);
	requiredClasses.addElement (attClass);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finEmbIntf", attClass);
      }

      // heck lets do it all again for instance attributes

      attClasses = (Sequence) classInfo.getAttributeValue (INSTANCE_ATTRIBUTES_);
      e = attClasses.elements ();
      if (traceOn)
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "checkVarClass", attClasses.size (), g2ClassName);
      while (e.hasMoreElements ()) {
        Structure attInfo = (Structure) e.nextElement ();
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "checkAttrClass", attInfo);
	Structure typeInfo = (Structure) attInfo.getAttributeValue(TYPE_, null);
	if (typeInfo == null)
	  continue;
	Symbol attClass = TypeHandler.getTypeFromTypeDescription (typeInfo);
	if (g2ClassName.equals(attClass))
	  continue;
	if (!TypeHandler.isClassType (attClass))
	  continue;
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "checkEmbIntf", attClass, g2ClassName);
	loadClass (attClass, true);
	requiredClasses.addElement (attClass);	  
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finEmbIntf", attClass);
      }

      // and again for instance methods arguments and result types

      Boolean isSystemDefined = (Boolean) classInfo.getAttributeValue (IS_SYSTEM_DEFINED_ , 
								       new Boolean(false));
      Sequence classInhPathSeq = 
        (Sequence) classInfo.getAttributeValue (CLASS_INHERITANCE_PATH_, null);
      Symbol[] classInhPath = new Symbol [ classInhPathSeq.size ()];
      classInhPathSeq.copyInto (classInhPath);
      boolean skipMethods = (isSystemDefined.booleanValue() || isDefinition (classInhPath));
      if (!skipMethods) // Dont load method signatures for system classes or definitions
	try {
	Sequence methodSeq = (Sequence) classInfo.getAttributeValue (INSTANCE_METHODS_);
	Sequence methodClasses = ensureEmbeddedMethodClassesAreLoaded(methodSeq, context);
	requiredClasses.concatenate (methodClasses);
	methodSeq = (Sequence) classInfo.getAttributeValue (STATIC_METHODS_);
        methodClasses = ensureEmbeddedMethodClassesAreLoaded(methodSeq, context);
	requiredClasses.concatenate (methodClasses);
      } catch (NoSuchAttributeException nsfe)
	{ // This attribute not available
	}
      
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "exitESCL");

    } catch (NoSuchAttributeException nsfe) {
      Trace.exception (nsfe);
      throw new UnexpectedException (nsfe);
    }
    return requiredClasses;
  }

  /** 
   * Load any Classes embedded in method argument or result types 
   */ 
  private Sequence ensureEmbeddedMethodClassesAreLoaded (Sequence methodSeq, G2Access context) {
    
    Sequence methodClasses = new Sequence (5);
    Enumeration e = methodSeq.elements ();
    if (traceOn)
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterEEMCAL", methodSeq.size ());
    while (e.hasMoreElements ()) {
      Structure methodStruct = (Structure) e.nextElement ();
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "checkMethodClass", methodStruct);
      try {
	
	// Argument types
	Sequence argumentTypes = (Sequence) methodStruct.getAttributeValue(ARGUMENT_TYPES_, null);
	for (Enumeration args = argumentTypes.elements(); args.hasMoreElements();) {
	  Object arg = args.nextElement();
	  if (arg instanceof com.gensym.util.Structure) {
	    Symbol argClass = (Symbol) ((Structure)arg).getAttributeValue(CLASS_);
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "checkEmbIntf", argClass);
	    //System.out.println("In args " + argClass.toString());
	    loadClass (argClass, true);
	    methodClasses.addElement (argClass);
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finEmbIntf", argClass);
	  }
	}
	
	// Result types
	Sequence resultTypes = (Sequence) methodStruct.getAttributeValue(RESULT_TYPES_, null);
	for (Enumeration results = resultTypes.elements(); results.hasMoreElements();) {
	  Object res = results.nextElement();
	  if (res instanceof com.gensym.util.Structure) {
	    Symbol resClass = (Symbol) ((Structure)res).getAttributeValue(CLASS_);
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "checkEmbIntf", resClass);
	    //System.out.println(resClass.toString());
	    loadClass (resClass, true);
	    methodClasses.addElement (resClass);
	    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finEmbIntf", resClass);
	  }
	}
	
      } catch (NoSuchAttributeException nsfe)
	{ // This attribute is not a class
	}
    }
    
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "exitEEMCAL");
    return methodClasses;
  }
  
  /**
   * Create Override from handcoded methods exported from an Interface definition for this 
   * class
   */
  ClassOverrides createOverridesFromHandCodedMethods(final String hcm)
  {
    if (hcm.equals(""))
      return null;

    // need to add a dummy class around code, so the Override Anaylzer is happy
    String handCodedMethod = "\npublic class dummy { \n" + hcm + "\n}";

    OverrideAnalyzer o = new OverrideAnalyzer ();
    Structure s = o.parse (handCodedMethod);
    try {
      return new ClassOverrides(s);
    } catch (MalformedOverridesException e) {
      return null;
    }
  }

  private static final Symbol G2_INCLUDE_METHOD_TEXT_IN_EXPORT_ = 
                              Symbol.intern ("G2-INCLUDE-METHOD-TEXT-IN-EXPORT");
  private boolean exportMethodSource = false;

  /**
   * Enables the inclusion of Method Source when constructing Method references.
   * As we have to read G2 for the text of each method, we dont always want to do this
   */
  protected void setExportMethodSource(boolean status) throws G2AccessException {
    exportMethodSource = status;
    context.callRPC (G2_INCLUDE_METHOD_TEXT_IN_EXPORT_, 
		     new Object[] {status ? Boolean.TRUE : Boolean.FALSE});      
  }

  /**
   * Check and return method text for a G2 class, given data read from classInfo
   */
  protected String checkMethodText(Symbol g2ClassName, Structure g2MethodData, String methodText) {
    return methodText;
  }

  /**
   * Create method stub information for each G2 method exported for this class.
   * Ensure that inherited methods signatures do not interfer with the current classes methods
   * Three situations are dealt with here;
   * 1. Check for any method of the current class with the same method as a super class method
   *    but with different return types. Not allowed in Java, but allowed in G2
   *    Currently, these methods are removed...TBD...The super method remains...
   *    as recursion ensures that the super class signature will take priority
   * 2. Any methods of super classes that have been overidden by the class are not
   *    included in the implementation file.
   * 3. Any methods of multi-inherited super classes not overridden and not inherited from the 
   *    implementation inhertance are included in the implementation only
   *    (rem the generated interface uses inheritance, while the implementation inherits from its nearest
   *     Impl class, but must still implement methods from parameter collectedClasses)
   */
  MethodInfo[] generateG2MethodStubInfo (Sequence instanceMethods, 
					 Sequence staticMethods,
					 Symbol g2ClassName, 
					 Symbol[] classInhPath,
					 Symbol[] collectedClasses,
					 boolean isInterface,
					 boolean isPseudoClass)
  {
    
    // WARNING WARNING DO NOT LOOK AT INHERTIED STATIC METHODS YET

    int numInstMethods = instanceMethods != null ? instanceMethods.size() : 0;
    MethodInfo[] methodInfoArray = new MethodInfo[numInstMethods];
    Hashtable definedMethods = new Hashtable(211);
    Hashtable classesDefiningReturnType = new Hashtable(21);
    Hashtable returnTypesForMethod = new Hashtable(21);
    Hashtable classesDefiningReturnTypeForConflict = new Hashtable(21);

    // We move from the top of the heir down 
    // (as we need to know the first definiton of a signature)
    for (int i = classInhPath.length; i>0; i--) {
	Symbol classInhName = classInhPath[i-1];	
	try {
	  Structure inhClassInfo = (Structure) classInfoTable.get (classInhName);
	  if (isPseudoClass && inhClassInfo == null)
	    continue;

	  Sequence ia = (Sequence) inhClassInfo.getAttributeValue (INSTANCE_METHODS_);

	  for (Enumeration inhClassMethods = ia.elements(); inhClassMethods.hasMoreElements();) {
	    Structure inhMethodStruct = (Structure) inhClassMethods.nextElement();
	    Symbol inhMethodName = 
	      (Symbol) inhMethodStruct.getAttributeValue(com.gensym.util.symbol.MethodExportSymbols.METHOD_NAME_, null);
	    Sequence inhResultTypes   = (Sequence) inhMethodStruct.getAttributeValue(RESULT_TYPES_, null);
	    //System.out.println("classInh " + classInhName + " " + inhMethodName + " " + inhResultTypes);
	    if (returnTypesForMethod.get(inhMethodName) == null) {
	      returnTypesForMethod.put(inhMethodName, inhResultTypes);
	      classesDefiningReturnType.put(inhMethodName, classInhName);
	    }

	    if (!classesDefiningReturnType.get(inhMethodName).equals(classInhName) &&
		!inhResultTypes.equals(returnTypesForMethod.get(inhMethodName))) {
	      classesDefiningReturnTypeForConflict.put(inhMethodName, classesDefiningReturnType.get(inhMethodName));
	      //System.out.println("Selecting " + classesDefiningReturnType.get(inhMethodName) + " as return type for " + inhMethodName.toString());
	    }
	  }
	} catch (NoSuchAttributeException e) {
	  Trace.exception (e);
	  throw new UnexpectedException (e);
	}
    }


    // Now check for any overridden methods, include them with mangled names so that they can 
    // be called from the implementation class and interface
    // If we are creating the implementation also include inhertied methods
    Vector newMethods = new Vector(211);
    MethodInfo newMethodInfo;

    // fix this: should I stick the class-to-extend at the beginning of
    // this array and actually visit that during this loop?
    for (int i = (isPseudoClass ? 1 : 0); i<collectedClasses.length; i++) {

      Symbol classInhName = collectedClasses[i];
      try {
	Structure inhClassInfo = (Structure) classInfoTable.get (classInhName);
	//System.out.println("Loop: class " + classInhName.toString());
	Sequence ia = (Sequence) inhClassInfo.getAttributeValue (INSTANCE_METHODS_);
	for (Enumeration inhClassMethods = ia.elements(); inhClassMethods.hasMoreElements();) {
	  Structure inhMethodStruct = (Structure)inhClassMethods.nextElement();
	  Symbol    inhMethodName = 
	    (Symbol) inhMethodStruct.getAttributeValue(com.gensym.util.symbol.MethodExportSymbols.METHOD_NAME_, null);
	  //System.out.println("  Loop: inhmethodname " + inhMethodName);
	  Sequence   inhArgumentTypes= (Sequence)inhMethodStruct.getAttributeValue(ARGUMENT_TYPES_, null);
	  Integer    inhArgsSizeObj = inhArgumentTypes.size();
	  Sequence   inhResultTypes = (Sequence)inhMethodStruct.getAttributeValue(RESULT_TYPES_, null);
	  boolean    inhIsStatic    = ((Boolean)inhMethodStruct.getAttributeValue(IS_STATIC_, new Boolean(false))).booleanValue();
	  String     inhMethodSource  = 
	    checkMethodText(g2ClassName, 
			 inhMethodStruct,
			 (String)inhMethodStruct.getAttributeValue(G2_METHOD_TEXT_, ""));
	  
	  boolean overridden = false;

	  Hashtable inhMethodsForName = (Hashtable)definedMethods.get(inhMethodName);
	  if (inhMethodsForName == null) {
	    inhMethodsForName = new Hashtable(4);
	    definedMethods.put(inhMethodName, inhMethodsForName);
	  }

	  Symbol classThatDefinesReturnType = 
	    (Symbol)classesDefiningReturnTypeForConflict.get(inhMethodName);
	  Sequence returnTypeForMethod = 
	    (Sequence)returnTypesForMethod.get(inhMethodName);
	  Sequence firstArgTypeForArgNum = (Sequence)inhMethodsForName.get(inhArgsSizeObj);

	  // As G2 can have inhertied methods, with the same argument signature and name but different
	  // return types...not allowed by Java. And as inhertied classes have already been created
	  // we must mangle the current class'es methods, which conflict
	  if (classThatDefinesReturnType != null && 
	      //classThatDefinesReturnType != classInhName &&
	      !inhResultTypes.equals(returnTypesForMethod.get(inhMethodName)))
	      //  !curMethodInfo.G2ResultTypes.equals(returnTypeForMethod)) {
	      // THE METHOD WILL BE REMOVED...FROM THE INTERFACE AND IMPLEMENTATION
	      // MORE WORK REQUIRED TO INCLUDE IT
	      overridden = true;

	  else if (firstArgTypeForArgNum != null) {

	    boolean mangleInhMethod = true;
	    // loose first arg of method, as this is class instance
	    Sequence inhArgumentTypesMinus = (Sequence)inhArgumentTypes.clone();
	    //System.out.println(inhArgumentTypesMinus);
	    inhArgumentTypesMinus.removeElementAt(0);
	    makeArgsUniqueForJavaExport(inhArgumentTypesMinus);
	    //System.out.println(inhArgumentTypesMinus + "\n" + firstArgTypeForArgNum);
	    if (!inhArgumentTypesMinus.toString().equals(firstArgTypeForArgNum.toString()))
	      // if the current class method of this name and number args but different argument types 
	      // then we dont need to mangle the name, Java will accept this as a polymorphic method
	      mangleInhMethod = false;
	    //System.out.println("Mangled: " + mangleInhMethod);

	    if (mangleInhMethod) {
	      // MDG 17/NOV/98, the implementation is nolonger flat, we inherit from a nearest 
	      // superclass Impl, no longer includ emangled versions of superior methods

	      // There is an override conflict, as the implementation is flat, 
	      // we must include a specific mangled method as a call to the superior method directly
	      //newMethodInfo = new MethodInfo(inhMethodName, 
	      ///			     inhIsStatic, 
	      //			     inhArgumentTypes, 
	      //			     inhResultTypes,
	      //			     inhMethodSource,
	      //			     classInhName,
	      //			     classInhName,
	      //			     this);
	      // Mangle method name, so it does not conflict with orginal overridden method
	      //newMethodInfo.G2MethodName = Symbol.intern(inhMethodName.toString() +
	      //					 "$"+
	      //					 classInhName.toString()); 
	      //System.out.println("Adding mangled  " + newMethodInfo.G2MethodName + " " + classInhName);
	      //newMethods.addElement(newMethodInfo);
	      overridden = true;
	    }
	  }

	  if (!overridden && (g2ClassName.equals(classInhName) || !isInterface)) {
	    // We are building the interface for g2ClassName (just include g2ClassName's methods), or
	    // we are building the methods for the implementation, as it is flat, we must include
	    // the methods for inhertited methods, that have not been overridden.
	    newMethodInfo = new MethodInfo(inhMethodName, 
					   inhIsStatic, 
					   inhArgumentTypes, 
					   inhResultTypes,
					   inhMethodSource,
					   classInhName,     
					   // Setting this parameter, will set the class appended to the method name.
					   // sent to g2 CLASS::METHOD-NAME, G2 complains if there is an absolute
					   // reference to a method name that is not defined for the current class
					   g2ClassName.equals(classInhName) ? null : classInhName,
					   this);
	
	    Sequence inhArgumentTypesMinus = (Sequence)inhArgumentTypes.clone();
	    inhArgumentTypesMinus.removeElementAt(0); // remove self class (param 0)
	    makeArgsUniqueForJavaExport(inhArgumentTypesMinus);
	    inhMethodsForName.put(inhArgsSizeObj, inhArgumentTypesMinus);
	    newMethods.addElement(newMethodInfo);
	  }
	} 
	} catch (NoSuchAttributeException e) {
	  Trace.exception (e);
	  throw new UnexpectedException (e);
	}
    }

    int i=0;
    // We do not include/resolve inherited static methods  (YET)
    // They are not included in interfaces, and have additional arguments when inserted in the implementation
    if (staticMethods != null)
    for (Enumeration MethodEnum = staticMethods.elements(); 
	 MethodEnum.hasMoreElements(); i++)
      {
	Structure methodStruct = (Structure)MethodEnum.nextElement();
	Symbol methodName      = (Symbol) methodStruct.getAttributeValue(com.gensym.util.symbol.MethodExportSymbols.METHOD_NAME_, null);
	boolean isStatic       = ((Boolean)methodStruct.getAttributeValue(IS_STATIC_, new Boolean(false))).booleanValue();
	Sequence argumentTypes = (Sequence) methodStruct.getAttributeValue(ARGUMENT_TYPES_, null);
	Sequence resultTypes   = (Sequence) methodStruct.getAttributeValue(RESULT_TYPES_, null);
	String   methodSource  = (String)   methodStruct.getAttributeValue(METHOD_SOURCE_, "");

	newMethods.addElement( new MethodInfo(methodName, 
					      isStatic,
					      argumentTypes,
					      resultTypes,
					      methodSource,
					      g2ClassName,
					      null,
					      this));
  
      }

    MethodInfo[] newMethodInfoArray = new MethodInfo[newMethods.size()];
    int pos = 0;
    for (Enumeration e = newMethods.elements(); e.hasMoreElements(); pos++)
      newMethodInfoArray[pos] = (MethodInfo)e.nextElement();

    return newMethodInfoArray;
  }
    
  /**
   * Cater for an unfortunate special case, G2 types VALUE and ITEM_OR_VALUE
   * will get emitted both as java.lang.Object. To ensure that we dont
   * get duplicate methd definitions, we must ensure that we can compare
   * these two types and get true
   */
  private void makeArgsUniqueForJavaExport(Sequence args) {
    for (int i = 0; i< args.size(); i++) {
      Object argTypeObj = args.elementAt(i);
      if (argTypeObj instanceof Symbol && 
	  ((Symbol)argTypeObj).equals(com.gensym.util.symbol.G2TypeSymbols.VALUE_))
	    args.setElementAt(com.gensym.util.symbol.G2TypeSymbols.ITEM_OR_VALUE_, i);
    }
  }
	  

  /**
   * This method is called by the system when any of our classes
   * reference other classes. It should only be called with
   * system classes that can be found by the system class loader.
   * @param className the name of the desired <code>Class</code>
   * @param resolve   <code>true</code> if the <code>Class</code>
   *                  must be resolved.
   * @return the resulting <code>Class</code>, or <code>null</code>
   *         if it was not found.
   */
  /* Can this be called to resolve a class twice?
     We'll know soon...*/
  @Override
  public Class loadClass (String className, boolean resolve) throws ClassNotFoundException{
    Class clazz = null;
    try {
      clazz = Class.forName (className,
			     true,              
			     Thread.currentThread().getContextClassLoader());
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "loadedSysClass", clazz, className);
    } catch (ClassNotFoundException cnfe) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "loadProblem", this, className);
      Trace.exception (cnfe);
      throw cnfe;
      //throw new InternalError ("StubClassLoader error!");
    }
    if (resolve)
      resolveClass (clazz);
    return clazz;
  }

  protected String generateInterfaceName (Symbol className_) {
    return G2ClassTranslator.createJavaClassNameFromG2ClassName (className_);
  }

  protected String generateStubClassName (Symbol className_) {
    return G2ClassTranslator.createJavaClassNameFromG2ClassName (className_) + "Impl";
  }

  private Hashtable collectInheritedOverrides (Symbol[] classesToCollect) {
    
    Hashtable overridesInhTable = new Hashtable();

    for (int i=0; i< classesToCollect.length; i++) {
	Symbol nextClassName = classesToCollect[i];
	ClassOverrides ovInherited = (ClassOverrides) overridesTable.get (nextClassName);
	if (ovInherited != null) {
	  //System.out.println("****** Entering " + nextClassName + "in hash table");
	  overridesInhTable.put(nextClassName, ovInherited);
	}
    }

    return overridesInhTable;
  }

  // I don't understand the validity of the following comment. In light
  // of my work unflattening the class hierarchy, it's good to
  // be able to append. Maybe it refers specifically to the
  // first signature of appendInheritedAttributes. That one is not
  // useful in my current work. rpenny (11/10/98)

  // appendInheritedAttributes should go away. All calls should be to
  // collectInheritedAttributes
  Sequence collectInheritedAttributes (Symbol g2ClassName, boolean staticAttributes) {
    try {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterCIA",
		  g2ClassName, (staticAttributes ? Boolean.TRUE : Boolean.FALSE));
      Structure classInfo = (Structure) classInfoTable.get (g2ClassName);
      Sequence attributes = (Sequence) classInfo.getAttributeValue (staticAttributes ? CLASS_ATTRIBUTES_ : INSTANCE_ATTRIBUTES_);
      Sequence s = appendInheritedAttributes (attributes, g2ClassName, staticAttributes);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "exitCIA");
      return s;
    } catch (NoSuchAttributeException nsae) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "errorCIA", nsae);
      Trace.exception (nsae);
    }
    throw new RuntimeException ("Error in collecting (0)" +
				(staticAttributes ? "static " : "instance ") +
				"attributes of " + g2ClassName);
  }
    

  private Sequence appendInheritedAttributes (Sequence attributes,
					      Symbol g2ClassName,
					      boolean staticAttributes) {
    Class currentClass = (Class) loadedInterfaces.get (g2ClassName);
    try {
      Symbol[] classInheritancePath   = (Symbol[]) ClassInheritancePathTable.get (g2ClassName); //preferred
      return appendInheritedAttributes (attributes, g2ClassName,
					classInheritancePath, staticAttributes);
    } catch (Exception e) {
      Trace.exception (e, "Will throw RuntimeException for this -> 2");
      throw new RuntimeException ("Error in collecting (1) " +
				  (staticAttributes ? "static " : "instance ") +
				  "attributes of " + g2ClassName +"\n" + e);
    }
  }

  private Sequence appendInheritedAttributes (final Sequence attributes,
								  final Symbol g2ClassName,
								  final Symbol[] classesToCollect,
								  final boolean staticAttributes) {

    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterAppInhAttr");
    int i=0;
    Symbol attrType_ = (staticAttributes ? CLASS_ATTRIBUTES_ : INSTANCE_ATTRIBUTES_);
    try {
      Sequence clonedAttributes  = (Sequence) attributes.clone ();
      int numInstAttrs              = clonedAttributes.size ();
      if (traceOn) {
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "origClassAttr", g2ClassName, numInstAttrs, clonedAttributes);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "moreClasses", classesToCollect.length - 1);
      }
      Sequence[] otherAttributes    = new Sequence[classesToCollect.length - 1];
      for (i=1; i< classesToCollect.length; i++) {
	Symbol nextClassName = classesToCollect[i];
	if (traceOn)
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "nextClass", i, nextClassName);
	// We expect this table to be filled up with the attributes
	// description if we hooked into the class loading. This should never
	// be null. But for now check before using...
	Structure nextClassInfo = (Structure) classInfoTable.get (nextClassName);
	if (nextClassInfo == null) {
	  Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "unInitClass", nextClassName);
	  // register Class????
	  loadClassInfo (generateInterfaceName (nextClassName),
			 nextClassName,
			 ((Class)loadedInterfaces.get (nextClassName)).getName ());
	  nextClassInfo   = (Structure) classInfoTable.get (nextClassName);
	}
	Sequence otherAttr   = (Sequence) nextClassInfo.getAttributeValue (attrType_);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "attrList", otherAttr);
	otherAttributes[i - 1] = otherAttr;
	numInstAttrs        += otherAttr.size ();
	if (traceOn)
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "runningTotal", otherAttr.size (), numInstAttrs);
      }
      clonedAttributes.ensureCapacity (numInstAttrs);
      for (i=0; i<classesToCollect.length - 1; i++)
    	  clonedAttributes.concatenate (otherAttributes[i]);
      removeDuplicateAttributes (clonedAttributes);
      if (traceOn)
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "exitingAppInhAttr", clonedAttributes.size ());
      return clonedAttributes;
    } catch (Exception e) {
      Trace.exception (e, "Will throw RuntimeException for this -> 1");
      throw new RuntimeException ("Error in collecting (2) " +
				  (staticAttributes ? "static " : "instance ") +
				  "attributes of " + g2ClassName + "\n" + e);
    }
  }

  private void removeDuplicateAttributes (Sequence attributes) {
    Enumeration e = attributes.elements ();
    int i=0;
    try {
      while (e.hasMoreElements ()) {
	Structure currentAttr = (Structure) e.nextElement ();
	Symbol   currAttrName = (Symbol) currentAttr.getAttributeValue (ATTRIBUTE_NAME_);
	if (traceOn)
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "examDuplAttr",
		      currAttrName, currentAttr.getAttributeValue (DEFINING_CLASS_), i);
	int elementCount = attributes.size ();
	for (int j=elementCount - 1; j>i; j--) {
	  Structure attr = (Structure) attributes.elementAt (j);
	  if ((attr.getAttributeValue (ATTRIBUTE_NAME_)).equals (currAttrName)) {
	    if (traceOn)
	      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "remDuplAttr",
			  currAttrName, attr.getAttributeValue (DEFINING_CLASS_), j);
	    attributes.removeElementAt (j);
	  }
	}
	i++;
      }
    } catch (NoSuchAttributeException nsae) {
      System.err.println (nsae);
      System.exit (2);
    }
  }

  private Symbol[] getClassAttrNames (Structure classInfo) throws NoSuchAttributeException {
    Sequence classAttributes = (Sequence)classInfo.getAttributeValue (CLASS_ATTRIBUTES_);
    int numClassAttributes = classAttributes.size ();
    Symbol[] attrs = new Symbol [numClassAttributes];
    for (int i=0; i<numClassAttributes; i++)
      attrs[i] = 
	(Symbol) ((Structure) classAttributes.elementAt (i)).getAttributeValue (ATTRIBUTE_NAME_);
    return attrs;
  }

  class SearchTreeNode {Symbol name; int lastVisited;}

  /* There is no need for G2 to send us the inheritance path
   * We should be able to compute it knowing the direct superiors
   */
  private Symbol[] computeClassInheritancePath (Symbol g2ClassName) {
    return new Symbol[0];
  }

  private InputStream findClassInfoStream (String className) {
    InputStream strm = null;
    strm = ClassLoader.getSystemResourceAsStream (className.replace ('.', '/') + ".ser");
    if (GensymApplication.getDevOption ())
      System.out.println ("findClassInfoStream (" + className + ") = " + strm);
    return strm;
  }


  /* This should be saved as a single jar file to optimize
   * file access.
   */
  // Read and Write from the correct repository!
  protected void loadClassInfo (String className, Symbol g2ClassName, String javaClassName) {

    Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "enterLoadClassInfo", className, g2ClassName, javaClassName);
    try {
      // We may already have the classInfo but, still need to resolve dependant classes
      Structure classInfo = (Structure)classInfoTable.get(g2ClassName);
      if (classInfo == null) {
	InputStream dataStrm = findClassInfoStream (javaClassName);
	if (dataStrm == null)
	  throw new RuntimeException ("No class info file found for " + className
				      + "/" + g2ClassName);
	java.io.ObjectInput s = new java.io.ObjectInputStream (dataStrm);
	classInfo = (Structure) s.readObject ();
	s.close ();
      }
      initializeClassData (g2ClassName, classInfo);
      ensureDependentClassesAreLoaded (classInfo, context);
      //ensureSuperInterfacesAreLoaded (classInfo, context);
      //ensureEmbeddedClassesAreLoaded (classInfo, context);
      boolean isSystemDefined = 
	((Boolean)classInfo.getAttributeValue (IS_SYSTEM_DEFINED_, nullObj)).booleanValue ();
      readOverridesIfAny (className, g2ClassName, isSystemDefined, classInfo);
      resolveAttributeNameCollisions (g2ClassName, classInfo);
    } catch (RuntimeException e) {
      Trace.exception (e, null);
      throw e;
    } catch (Exception e) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clInfoLoadErr", javaClassName, e);
      Trace.exception (e, null);
      throw new RuntimeException ("Unsupported configuration (class found without corresponding class info)" + javaClassName + "). " + e + "Please report to Customer Service.");          
    }
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "exitLoadClassInfo", className, g2ClassName);
  }

  // Really bad hack. The class-info should be written in the correct lcoation
  private void relocateClassInfo (String origFileName, String classPackage) {
    File serFile = new File (origFileName);
    String newFileName = serFile.getParent () + sepChar +
      classPackage.replace ('.', sepChar) + sepChar + serFile.getName ();
    //System.out.println ("Renaming " + origFileName + " to " + newFileName);
    File destFile = new File (newFileName);
    boolean renamed = serFile.renameTo (destFile);
    if (!renamed) {
      boolean oldFileDeleted = destFile.delete ();
      if (!oldFileDeleted)
	throw new RuntimeException ("Could not delete old class info file");
      renamed = serFile.renameTo (destFile);
      if (!renamed)
	throw new RuntimeException ("Could not rename class info file");
    }
  }
		    
  private String writeClassInfo (String className, Symbol g2ClassName,
			       Structure classInfo) {
    String fileName = null;
    Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "writeClassInfoCall",
		g2ClassName);
    try {
      sanitizeClassInfo (classInfo);
      boolean isSystemDefined = 
	((Boolean) classInfo.getAttributeValue (IS_SYSTEM_DEFINED_)).booleanValue ();
      String repository = (isSystemDefined ? g2Repository : userRepository);
      fileName = repository + className + ".ser";
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "writeClassInfo", g2ClassName, fileName);
      java.io.FileOutputStream f = new java.io.FileOutputStream(fileName);
      java.io.ObjectOutput s = new java.io.ObjectOutputStream(f);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clInfo", classInfo);
      s.writeObject (classInfo);
      Sequence attributes = (Sequence) classInfo.getAttributeValue (CLASS_ATTRIBUTES_);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "classAttrs", attributes.expand ());
      attributes = (Sequence) classInfo.getAttributeValue (INSTANCE_ATTRIBUTES_);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "instAttrs", attributes.expand ());
      s.flush ();
      f.close ();
      readOverridesIfAny (className, g2ClassName, isSystemDefined, classInfo);
      return fileName;
    } catch (Exception e) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clInfoWriteErr", className, fileName);
      Trace.exception (e, "Class-info write failure while trying to write " + g2ClassName);
      throw new RuntimeException ("Error writing class info: " + e);
    }
  }

  /*
   * This procedure (when implemented) will clean up raw info:
   * To Do: rename private classes (BLOCK, ENTITY, KB-FRAME)
   *        strip class-qualified static attributes.
   *
   */
  private void sanitizeClassInfo (Structure classInfo) {
  }
  
  /**
   * Hack! will go away
   * @deprecated
   * @undocumented
   */
  private com.gensym.classes.G2Definition getDefinition (Symbol g2ClassName) throws G2AccessException {
    // Guard against this when !generationMode
    return cdm.getDefinition (g2ClassName);
  }

  /**
   * Returns the interface given a g2 class name symbol
   * @param g2ClassName_ the name of the g2 class
   * @return a java <code>Class</code> for the corresponding interface
   * <b>if it is has been loaded already</b>, <code>null</code> otherwise.
   * @see #loadClass
   */
  public Class getInterface (Symbol g2ClassName_) {
    return (Class) loadedInterfaces.get (g2ClassName_);
  }

  private static final Object empty = new Object ();

  /**
   * gets the value of a class attribute
   */
  private Object getStaticAttributeValue (final Symbol className, final Symbol attrName) throws G2AccessException {
    // Guard against this when !generationMode
    Symbol[] inheritancePath = (Symbol[])ClassInheritancePathTable.get (className);
    for (int i=0; i<inheritancePath.length; i++) {
      Symbol classNameFound = inheritancePath[i];
      Object staticAttributeValue = empty; //getDefinedStaticAttributeValueIfAny (className, attrName);
      Object newMethodStaticAttributeValue = cdm.getClassAttributeValue (classNameFound, attrName);

      /*
      System.out.println ("Get Static Attribute Value :::::::>>>>>>>\nOld= " + staticAttributeValue +
			  "\nNew = " + newMethodStaticAttributeValue);
			  */

      if (!empty.equals(staticAttributeValue))
	return staticAttributeValue;
      else
	return newMethodStaticAttributeValue;
    }
    throw new RuntimeException (attrName + " not found as a static attribute in the inheritance path of "
				+ inheritancePath[0] + ".");
  }

  private Object getDefinedStaticAttributeValueIfAny (Symbol className, Symbol attrName) {
    // Guard against this when !generationMode
    Structure attrsOnThisClass = (Structure) ClassAttributeValuesTable.get (className);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clAttrs", className, attrsOnThisClass);
    // Yet another case of walking up the hierarchy and
    // hitting a class that hasn't been initialized properly
    if (attrsOnThisClass == null) {
      loadClassInfo (generateInterfaceName (className), className, ((Class)loadedInterfaces.get (className)).getName ());
      attrsOnThisClass = (Structure) ClassAttributeValuesTable.get (className);
    }
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clAttrs", className, attrsOnThisClass);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "attmptGetClAttr", attrName, attrsOnThisClass);
    return attrsOnThisClass.getAttributeValue (attrName, empty);
  }

  /*
   * set the attribute on a class
   */
  private void setStaticAttributeValue (final Symbol className, final Symbol attrName, final Object newValue) {
    Symbol[] inheritancePath = (Symbol[])ClassInheritancePathTable.get (className);
    for (int i=0; i<inheritancePath.length; i++) {
      Symbol classNameFound = inheritancePath[i];
      Object staticAttributeValue = getDefinedStaticAttributeValueIfAny (classNameFound, attrName);
      if (!empty.equals(staticAttributeValue))
	setDefinedStaticAttribute (classNameFound, attrName, newValue);
      return;
    }
    throw new RuntimeException (attrName + " not found as a static attribute in the inheritance path of "
				+ inheritancePath[0] + ".");
  }

  private void setDefinedStaticAttribute (Symbol className, Symbol attrName, Object newValue) {
    Structure attrsOnThisClass = (Structure) ClassAttributeValuesTable.get (className);
    // Call rpc, which updates this table
    attrsOnThisClass.setAttributeValue (attrName, newValue);
  }

  private static final Symbol NO_OVERRIDE_ = Symbol.intern ("NO-OVERRIDE");
  private void initializeClassData (Symbol g2ClassName,
				    Structure classInfo)
  throws G2AccessException {
    try {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterICAL", g2ClassName);
      int numClassAttrs = ((Sequence)classInfo.getAttributeValue (CLASS_ATTRIBUTES_)).size ();
      int numInstAttrs = ((Sequence)classInfo.getAttributeValue (INSTANCE_ATTRIBUTES_)).size ();
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "putCIInTable",
		  g2ClassName, numClassAttrs, numInstAttrs);
      classInfoTable.put (g2ClassName, classInfo);
      Symbol[] inhPath = makeInheritancePathFromClassInfo (classInfo);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "putIPInTable",
		  inhPath, inhPath.length, ClassInheritancePathTable);
      ClassInheritancePathTable.put (g2ClassName, inhPath);
      //Sequence classAttributes = collectInheritedAttributes (g2ClassName, true);
      Structure classAttributeValues = new Structure (); //downloadClassAttributeValues (g2ClassName, classAttributes);
      ClassAttributeValuesTable.put (g2ClassName, classAttributeValues);
    } catch (NoSuchAttributeException nsae) {
      System.err.println (nsae);
      throw new RuntimeException (nsae.toString ());
    }
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "newClassDataCaching", g2ClassName);
  }

  protected void makeClassDefinition (Symbol g2ClassName,
				    Class clazz,
				    boolean isSystemClass) throws G2AccessException {
    try {
      currentlyLoadingDefinitions.put (g2ClassName, clazz);
      G2Definition definition = null;
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "makeClassDefn",
		  g2ClassName, isSystemClass ? Boolean.TRUE : Boolean.FALSE);
      if (isSystemClass) {
	if (traceOn)
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "checkExistingSystemClassDef",
		      g2ClassName, cdm.getDefinition0 (g2ClassName));
	// If we are using a shared system class manager, Make like a tree and leave.
	
	if (cdm.getDefinition0 (g2ClassName) != null)
	  return;
      }
      if (!isSystemClass) {
	definition = (G2Definition) ((DefinitionInfo)pendingDefinitions.remove (g2ClassName)).defn;
	fixupClassInheritancePathAttribute (definition, g2ClassName);
	Object x = null;//*context.getUniqueNamedItem (com.gensym.util.symbol.G2ClassSymbols.DEFINITION_, g2ClassName);
	//System.out.println ("PD.remove (" + g2ClassName + ") =  " + x + ", " + t);
	if (false) {//definition != x) {
	Thread.dumpStack ();
	throw new Error ("Internal Error at 1! for class " + g2ClassName + " : " +
			 definition + " != " + x);
	}
	if (checkForClassChange) {
	  G2Access cxn = ((com.gensym.classes.ImplAccess)definition).getContext ();
	  java.lang.Object retn = cxn.callRPC (G2_GET_CLASS_HASH_,
					       new Object[] {g2ClassName},
					       0);
	  //System.out.println ("Whooo -> " + retn + ", a " + retn.getClass ());
	  //System.out.println (DebugUtil.printArray (retn) + " ==> " + new String ((char[])retn));
	  //System.out.println ("As Hex String = > " + charArrayToHexString ((char[])retn));
	}
      } else {
	//Sequence classAttributes = collectInheritedAttributes (g2ClassName, true);
	Sequence classAttributes = classFriend.getStaticAttributes (g2ClassName);
	//System.out.println ("Static Attributes for " + g2ClassName + " = \n" +
	//		  		  "  " + classAttributes.expand ());
	Structure classAttributeValues =
	  downloadClassAttributeValues2 (g2ClassName, classAttributes);
	definition = new com.gensym.classes.SystemClassDefinitionImpl 
	  (g2ClassName, classAttributeValues);
      }
      cdm.storeClassDefinition(g2ClassName, definition, isSystemClass);
    } finally {
      currentlyLoadingDefinitions.remove (g2ClassName);
    }
  }

  private void fixupClassInheritancePathAttribute (G2Definition defn, Symbol g2ClassName_) {
    com.gensym.classes.ClassDefinition cdefn = (com.gensym.classes.ClassDefinition) defn;
    Symbol[] classInhPath = getClassInheritancePath (g2ClassName_);
    Sequence classInhPathSeq = new Sequence (classInhPath.length);
    for (int i=0; i<classInhPath.length; i++)
      classInhPathSeq.addElement (classInhPath[i]);
    cdefn.setSystemClassInheritancePath (classInhPathSeq);
  }

  private String charArrayToHexString (char[] data) {
    StringBuffer hexRepresentation = new StringBuffer ("");
    for (int i=0; i<data.length; i++) {
      String intAsHexString = Integer.toHexString ((int)data[i]);
      String padding        = "0000".substring (0, 4 - intAsHexString.length ());
      hexRepresentation.append (padding).append (intAsHexString);
    }
    return hexRepresentation.toString ();
  }

  Structure downloadClassAttributeValues2 (Symbol g2ClassName, Sequence attrNames) {
    Structure classAttributeValues = new Structure ();
    try {
      if (!attrNames.isEmpty()) {
	classAttributeValues =
	  context.getClassAttributeValues (g2ClassName, attrNames);
 	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clAttrVal",
 		    attrNames, g2ClassName, classAttributeValues);
      }
      // Set up the PART-OF-CLASS-INFO attributes.
      Structure classInfo = (Structure) classInfoTable.get (g2ClassName);
      classAttributeValues.setAttributeValue
	(DIRECT_SUPERIOR_CLASSES_,
	 classFriend.getDirectSuperiorClasses (g2ClassName));
      Symbol[] classInhPath =
	classFriend.getClassInheritancePath (g2ClassName);
      Sequence classInhPathSeq = new Sequence (classInhPath.length);
      for (int i=0; i<classInhPath.length; i++)
	classInhPathSeq.addElement (classInhPath[i]);
      classAttributeValues.setAttributeValue
	(CLASS_INHERITANCE_PATH_,
	 classInhPathSeq);
      classAttributeValues.setAttributeValue
	(CLASS_NAME_, g2ClassName);
    } catch (G2AccessException gae) {
      Trace.exception (gae, "Caught during class attribute value fetch : ");
      throw new StubCreationException (gae.getMessage ());
    }
    return classAttributeValues;
  }

  Structure downloadClassAttributeValues0 (Symbol g2ClassName, Sequence classAttributes) {
    Structure classAttributeValues = new Structure ();
    Enumeration e = classAttributes.elements ();
    try {
      if (traceOn)
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "beginClAttr",
		    classAttributes.size (), g2ClassName);
      while (e.hasMoreElements ()) {
	Structure attrDescpn = (Structure) e.nextElement ();
	Symbol attrName = (Symbol)attrDescpn.getAttributeValue (ATTRIBUTE_NAME_);
	try {
	  java.lang.Object attrValue = 
	    context.getClassAttributeValue (g2ClassName, attrName);
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clAttrVal",
		      attrName, g2ClassName, attrValue);
	  classAttributeValues.setAttributeValue (attrName, attrValue);
	} catch (G2AccessException gae) {
	  Trace.exception (gae, "Caught during class attribute value fetch : ");
	  throw new StubCreationException (gae.getMessage ());
	}
      }
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finishClAttr",
		  g2ClassName);
    } catch (NoSuchAttributeException nsae) {
      Trace.exception (nsae, "Caught during attribute value fetch :");
      throw new UnexpectedException (nsae);
    }
    return classAttributeValues;
  }

  Structure downloadClassAttributeValues (Symbol g2ClassName, Sequence classAttributes) {
    Structure classAttributeValues = new Structure ();
    Sequence attrNames = new Sequence (classAttributes.size ());
    Enumeration e = classAttributes.elements ();
    try {
      while (e.hasMoreElements ()) {
	Structure attrDescpn = (Structure) e.nextElement ();
	Symbol attrName = (Symbol)attrDescpn.getAttributeValue (ATTRIBUTE_NAME_);
	attrNames.addElement (attrName);
      }
      java.lang.Object attrValue = 
	context.getClassAttributeValues (g2ClassName, attrNames);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clAttrVal",
		  attrNames, g2ClassName, attrValue);
      classAttributeValues = (Structure) attrValue;
      // Set up the PART-OF-CLASS-INFO attributes.
      Structure classInfo = (Structure) classInfoTable.get (g2ClassName);
      classAttributeValues.setAttributeValue
	(DIRECT_SUPERIOR_CLASSES_,
	 classInfo.getAttributeValue (DIRECT_SUPERIOR_CLASSES_));
      classAttributeValues.setAttributeValue
	(CLASS_INHERITANCE_PATH_,
	 classInfo.getAttributeValue (CLASS_INHERITANCE_PATH_));
      classAttributeValues.setAttributeValue
	(CLASS_NAME_, g2ClassName);
    } catch (G2AccessException gae) {
      Trace.exception (gae, "Caught during class attribute value fetch : ");
      throw new StubCreationException (gae.getMessage ());
    } catch (NoSuchAttributeException nsae) {
      Trace.exception (nsae, "Caught during attribute value fetch :");
      throw new UnexpectedException (nsae);
    }
    return classAttributeValues;
  }

  private void resolveAttributeNameCollisions (Symbol g2ClassName, Structure classInfo) {
    /* We need to have unique property names in a class!
     * The first class to define an attribute gets to keep
     * the simple name for the property. Any subclasses that
     * shadow the attribute has a qualified property name.
     */
    try {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterRANC", g2ClassName);
      Sequence classAttrs = (Sequence) classInfo.getAttributeValue (CLASS_ATTRIBUTES_);
      Sequence inheritedClassAttributes = new Sequence ();
      inheritedClassAttributes = appendInheritedAttributes (inheritedClassAttributes, g2ClassName, true);
      qualifyOrRemoveAnyRedefinedAttributes (g2ClassName, classAttrs, inheritedClassAttributes);
      Sequence instAttrs = (Sequence) classInfo.getAttributeValue (INSTANCE_ATTRIBUTES_);
      Sequence inheritedInstanceAttributes = new Sequence ();
      inheritedInstanceAttributes = appendInheritedAttributes (inheritedInstanceAttributes, g2ClassName, false);
      qualifyOrRemoveAnyRedefinedAttributes (g2ClassName, instAttrs, inheritedInstanceAttributes);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "exitRANC", g2ClassName);
    } catch (NoSuchAttributeException nsae) {
      System.err.println (nsae);
      throw new RuntimeException (nsae.toString ());
    }
  }

  private static final Symbol OBJECT_DEFINITION_ = Symbol.intern ("OBJECT-DEFINITION");
  private static final Symbol CONNECTION_DEFINITION_ = Symbol.intern ("CONNECTION-DEFINITION");
  private static final Symbol MESSAGE_DEFINITION_ = Symbol.intern ("MESSAGE-DEFINITION");
  private void qualifyOrRemoveAnyRedefinedAttributes (Symbol g2ClassName,
						      Sequence definedAttributes,
						      Sequence inheritedAttributes) {
    try {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterQARD", g2ClassName);
      java.util.Vector duplicates = null;
      int attrIndex = 0;
      duplicates = new java.util.Vector ();
      Enumeration e = definedAttributes.elements ();
      while (e.hasMoreElements ()) {
	Structure attrDescrpn = (Structure) e.nextElement ();
	Symbol attrName = (Symbol) attrDescrpn.getAttributeValue (ATTRIBUTE_NAME_);
	if (attributeExistsInList (attrName, inheritedAttributes)) {
	  duplicates.insertElementAt (attrIndex, 0);
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "resolvDupl",
		      "Removed attribute " ,
		      attrName, g2ClassName);
	}
	attrIndex++;
      }
      e = duplicates.elements ();
      while (e.hasMoreElements ())
	definedAttributes.removeElementAt (((Integer)e.nextElement ()).intValue ());

      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "exitQARD", g2ClassName);
    } catch (NoSuchAttributeException nsae) {
      System.err.println (nsae);
      throw new RuntimeException (nsae.toString ());
    }
  }

  /* Evil is being perpetuated here. I'm mutating the original class attribute
   * descriptions. If a property has a qualified name, then the original name
   * is saved.
   */
  private void qualifyAttributeName (Symbol g2ClassName,
				     Symbol attrName,
				     Structure attrDescrpn) {
    attrDescrpn.setAttributeValue (ATTRIBUTE_NAME_,
				   Symbol.intern (attrName.getPrintValue () +
						  "$" +
						  g2ClassName.getPrintValue ()));
    attrDescrpn.setAttributeValue (ORIGINAL_ATTRIBUTE_NAME_,
				   attrName);
    if (traceOn)
      Trace.send (DEF_WARN_LEVEL, traceKey, i18nTrace, "qualifyingAttribute",
		  attrName, g2ClassName, attrDescrpn.getAttributeValue (ATTRIBUTE_NAME_, null));
  }


  private Symbol[] makeInheritancePathFromClassInfo (Structure classInfo) {
    try {
      Sequence classInhPathSeq = 
	(Sequence) classInfo.getAttributeValue (CLASS_INHERITANCE_PATH_);
      Symbol g2ClassName =
	(Symbol) classInfo.getAttributeValue (CLASS_NAME_);
      if (traceOn)
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clInhPath",
		    g2ClassName, classInhPathSeq.expand ());
      Symbol[] classInhPath = new Symbol [classInhPathSeq.size ()];
      for (int i=0; i<classInhPath.length; i++)
	classInhPath[i] = (Symbol) classInhPathSeq.elementAt (i);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "finMakeClInhPath", g2ClassName);
      return classInhPath;
    } catch (NoSuchAttributeException nsae) {
      Trace.exception (nsae);
      throw new RuntimeException (nsae.toString ());
    }
  }

  /*
   * Overrides are just structures so that they can potentially be generated
   * in G2.
   */
  protected void readOverridesIfAny (String className, Symbol g2ClassName, boolean isSystemDefined, Structure classInfo) {
    try {
      if (!isSystemDefined)
	return;
      String repository = (isSystemDefined ? g2Repository : userRepository);
      String fileName = g2Package.replace ('.', '/') + className + ".ovr";
      if (GensymApplication.getDevOption ())
	System.out.println ("Reading overrides from " + fileName);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "readOverrides", g2ClassName, fileName);
      InputStream fi = ClassLoader.getSystemResourceAsStream(fileName);
      if (fi != null) {
	java.io.ObjectInput s = new java.io.ObjectInputStream (fi);
	Structure overridesStruct = (Structure) s.readObject ();
	ClassOverrides overrides = new ClassOverrides (overridesStruct);
	overridesTable.put (g2ClassName, overrides);
	fi.close ();
	enforceOverridesForClass (g2ClassName, overrides, classInfo);
      } else {
	Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "NoOverrides",
		    g2ClassName);
      }
    } catch (MalformedOverridesException moe) {
      // What to do?
      Trace.exception (moe, "Error reading overrides for class " + g2ClassName);
    } catch (Exception larry) {
      Trace.send (DEF_WARN_LEVEL, traceKey, i18nTrace, "OverridesReadProblem",
		  g2ClassName, larry);
      Trace.exception (larry);
      throw new StubCreationException (larry.getMessage ());
    }
  }

  private void enforceOverridesForClass (Symbol g2ClassName, ClassOverrides overrides, Structure classInfo) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterEOC", g2ClassName);
    try {
      Sequence classAttrs = (Sequence) classInfo.getAttributeValue (CLASS_ATTRIBUTES_);
      Sequence instAttrs = (Sequence) classInfo.getAttributeValue (INSTANCE_ATTRIBUTES_);
      Enumeration e = overrides.getProperties ();
      while (e.hasMoreElements ()) {
	Symbol attrName = (Symbol) e.nextElement ();
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "ensurePropAbs", attrName);
	ensureAttributeNotInList (attrName, classAttrs);
	ensureAttributeNotInList (attrName, instAttrs);
      }
    } catch (NoSuchAttributeException nsae) {
      System.err.println (nsae);
      throw new RuntimeException (nsae.toString ());
    }
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "exitEOC", g2ClassName);
  }

  private void ensureAttributeNotInList (Symbol attrNameToRemove, Sequence attrDescrpns) throws NoSuchAttributeException {
    Enumeration e = attrDescrpns.elements ();
    while (e.hasMoreElements ()) {
      Structure attrDescrpn = (Structure) e.nextElement ();
      Symbol attrName = (Symbol) attrDescrpn.getAttributeValue (ATTRIBUTE_NAME_);
      if (attrName.equals (attrNameToRemove)) {
	attrDescrpns.removeElement (attrDescrpn);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "removingProp", attrName);
	if (traceOn)
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "origClassAttr",
		      "SOME-CLASS", attrDescrpns.size (), attrDescrpns);
	Structure classInfo = (Structure) classInfoTable.get (Symbol.intern ("FOO4"));
	if (classInfo != null) {
	  Sequence instAttrs = (Sequence) classInfo.getAttributeValue (INSTANCE_ATTRIBUTES_, null);
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "origClassAttr",
		      "FOO4 in table", instAttrs.size (), instAttrs);
	}
	return; // Look for only one occurence?
      }
    }
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "newProp", attrNameToRemove);
  }

  private boolean attributeExistsInList (Symbol testAttrName, Sequence attrDescrpns) throws NoSuchAttributeException {
    Enumeration e = attrDescrpns.elements ();
    while (e.hasMoreElements ()) {
      Structure attrDescrpn = (Structure) e.nextElement ();
      Symbol attrName = (Symbol) attrDescrpn.getAttributeValue (ATTRIBUTE_NAME_);
      if (testAttrName.equals (attrName))
	return true;
    }
    return false;
  }

  /*
   * Tells you whether an attribute is "overridden", static, instance, or non-existant
   * Not completely designed or implemented.
   */
  private int getAttributeKind (Symbol g2ClassName, Symbol attrName) {
    try {
      Structure classInfo = (Structure) classInfoTable.get (g2ClassName);
      Sequence classAttrs = (Sequence) classInfo.getAttributeValue (CLASS_ATTRIBUTES_);
      if (attributeExistsInList (attrName, classAttrs))
	return 0;
      Sequence instAttrs = (Sequence) classInfo.getAttributeValue (INSTANCE_ATTRIBUTES_);
      if (attributeExistsInList (attrName, instAttrs))
	return 1;
      ClassOverrides overrides = (ClassOverrides) overridesTable.get (g2ClassName);
      if (overrides.propertyExists (attrName))
	return 2;
    } catch (NoSuchAttributeException nsae) {
      System.err.println (nsae);
      throw new RuntimeException (nsae.toString ());
    }
    return -1;
  }

  protected Symbol[] getClassInheritancePath (Symbol g2ClassName_) {
    if (com.gensym.classes.SystemPredicate.isSystemClass (g2ClassName_))
      return classFriend.getClassInheritancePath (g2ClassName_);
    else
      return (Symbol[])ClassInheritancePathTable.get (g2ClassName_);
  }

  /**
   * Returns the value of a flag that indicates whether this ClassLoader
   * will generate new classes for unknown Interfaces and Stubs.
   * @return <code>true</true> if class generation is allowed; <code>
   *         false</code> otherwise.
   * @see #setGenerationMode
   */
  public int getGenerationMode () {
    return generationModeForUser;
  }

  // review synchronization, rpenny 9-7-99
  /**
   * Allows or disallows this ClassLoader to generate new
   * Interfaces and stubs for unknown G2 classes.
   * @param <code>newMode</code>
   * @see #getGenerationMode
   */
  public void setGenerationMode (int newMode) {
//     boolean oldUseAlternateClass = useAlternateClass;
    int oldMode;
    if ((oldMode = generationModeForUser) == newMode)
      return;
//     allowedToSwitch = (generationModeForUser == GENERATION_AUTO ||
// 	       generationModeForUser == GENERATION_AUTO_NEAREST);
    generationModeForUser = newMode;
    if (oldMode == GENERATION_AUTO_NEAREST) { // || oldMode == NEAREST
      flushNearestClasses ();
      useAlternateClasses = false;
    }
    if (newMode == GENERATION_ON)
      setGenerationMode1 (true);
    else 
      setGenerationMode1 (false);
    if (newMode == GENERATION_AUTO_NEAREST)// || newMode == NEAREST
      useAlternateClasses = true;
//     if(oldUseAlternateClass && !useAlternateClass)
//       flushNearestClasses ();
  }

  private void setGenerationMode1 (boolean newMode) {
    boolean oldMode = generationMode;
    Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "genModeFlip",
		newMode ? Boolean.TRUE : Boolean.FALSE);
    generationMode = newMode;
    if (!oldMode && newMode)
      flushUninitializedClasses (); // What to do if this throws an error?
  }

  /**
   * Clears out the table that retains the associations between a
   * class-name and the name of the alternate class that was used
   * as a replacement when GENERARATION_AUTO_NEAREST was in effect.
   */
  private void flushNearestClasses () {
    /* Get locks. Clear tables. decache constructors */
    Symbol[] invalidatedClasses;
    synchronized (loadedInterfaces) {
      synchronized (loadedStubs) {
	int i=0;
	invalidatedClasses = new Symbol[nearestClassesTable.size ()];
	Enumeration classKeys = nearestClassesTable.keys ();
	while (classKeys.hasMoreElements ()) {
	  Symbol invalidClass = (Symbol) classKeys.nextElement ();
	  invalidatedClasses[i++] = invalidClass;
	  loadedInterfaces.remove (invalidClass);
	  loadedStubs.remove (invalidClass);
	  uninitlzedClasses.remove (invalidClass);
	}
	nearestClassesTable.clear ();
      }
    }
    if (traceOn)
      Trace.send (BASIC_TRACE_LEVEL, traceKey, i18nTrace, "flushedNearest",
		  new Object [] {loadedInterfaces, loadedStubs, loadingClasses, uninitlzedClasses});
    fireInvalidationEvent (invalidatedClasses);
  }

  /**
   * Could put some more thread-safety protection
   * in this method. But it is not anticipated to be called
   * often.
   */
  private void fireInvalidationEvent (Symbol[] invalidatedClasses) {
    ClassInvalidationEvent cie = new ClassInvalidationEvent (this, invalidatedClasses);
    for (int i=0; i<invalidationListeners.size(); i++) {
      ClassInvalidationListener cil = (ClassInvalidationListener) invalidationListeners.elementAt (i);
      cil.classesInvalidated (cie);
    }
  }

  private Vector invalidationListeners = new Vector ();

  public void addClassInvalidationListener (ClassInvalidationListener cil) {
    invalidationListeners.addElement (cil);
  }

  void removeClassInvalidationListener (ClassInvalidationListener cil) {
    invalidationListeners.removeElement (cil);
  }

  /**
   * Enables regeneration of an interface even if it can be
   * found locally. Set forceDownload is set to true to
   * refresh the interface when the G2 class has changed.
   * @param force a whether or not to force a new interface to be
   *   generated
   * #see getForceDownload
   */
  public void setForceDownload (boolean force) {
    forceDownload = force;
  }

  /**
   * Get the current forceDownload mode
   * @return the current forceDownload mode.
   * #see setForceDownload
   */
  public boolean getForceDownload () {
    return forceDownload;
  }

  protected G2Access getContext () {
    return context;
  }


  private synchronized void flushUninitializedClasses () {
    /*
    System.out.println ("\n\nIn flushUninitializedClasses : Need to flush -> ");
    for (Enumeration classNames = uninitlzedClasses.keys ();
	 classNames.hasMoreElements ();)
      System.out.print (classNames.nextElement () + " ");
    System.out.println ("\n LoadingClasses list -> ");
    for (Enumeration classNames = loadingClasses.keys ();
	 classNames.hasMoreElements ();)
      System.out.print (classNames.nextElement () + " ");
    System.out.println ();
    */
    for (Enumeration classNames = uninitlzedClasses.keys ();
	 classNames.hasMoreElements ();) {
      Symbol uninitializedClassName = (Symbol)classNames.nextElement ();
      if (pseudoClasses.get(uninitializedClassName) == null)
	loadClass (uninitializedClassName, true);
    }
    /*
    System.out.println ("Finished flushUninitializedClasses! Dumping State. Uninitialized Classes ->");
    for (Enumeration classNames = uninitlzedClasses.keys ();
	 classNames.hasMoreElements ();)
      System.out.print (classNames.nextElement () + " ");
    System.out.println ("\n LoadingClasses list -> ");
    for (Enumeration classNames = loadingClasses.keys ();
	 classNames.hasMoreElements ();)
      System.out.print (classNames.nextElement () + " ");
    System.out.println ();
    */
    for (Enumeration classNames = loadingClasses.keys ();
	 classNames.hasMoreElements ();) {
      Symbol className = (Symbol)classNames.nextElement();
      if (pseudoClasses.get(className) == null)
	cacheClassInfo (className);
    }
  }

  private void cacheClassInfo (Symbol className_) {
    try {
      //System.out.println ("  cacheClassInfo (" + className_ + "). LoadingClasses = " + loadingClasses + "  Stack of loadClass = " + classDepthTracing.expand ());
      if (classInfoTable.get (className_) != null)
	return;	 // Can happen if flushUninitializedClasses is called multiple times
      Structure classInfo = getClassInfo (className_, false);
      initializeClassData (className_, classInfo);
      String assignedPackage = determinePackageForClass
	(className_,
	 com.gensym.classes.SystemPredicate.isSystemClass (className_));
    } catch (G2AccessException gae) {
      Trace.exception (gae);
      throw new StubCreationException (gae.getMessage ());
    }
  }

  /**
   * @undocumented
   */
  public ClassManager getClassManager() {
    return cdm;
  }


  //A well known interface, that tags a G2 Item as being a G2 Event object
  static final String g2EventTagInterfaceName = "com.gensym.classes.G2_EventObject";
  //A G2 External event class is always subclasses from this
  static final String externalG2EventClassName = "com.gensym.classes.G2_ExternalEventObjectRoot";
  //Method that gets called to find the external event class
  static final String getExternalEventClassMethodName = "getExternalEventClass";

  /**
   * Return the External name of an G2 Listener Interface class
   */
  static String getExternalG2EventClassName(String G2EventName) {
    // check for package
    String className = G2EventName;
    int dotPos = G2EventName.lastIndexOf(".");
    if (dotPos > 1) {
      className = G2EventName.substring(dotPos + 1);
    }
    return "G2_" + className;
  }


  /**
   * Check whether a G2 class is or a subclass of G2 Event class
   * ??? Limited to direct subclass of G2-EVENT-OBJECT
   */
  static boolean isG2EventClass(Symbol className, Symbol[] classInhPath) {
    if (classInhPath.length < 1){
    	return false;
    }
    for (int i=0; i<classInhPath.length; i++) { 
      if (classInhPath[i].equals(G2_EVENT_OBJECT_)) 
	return true;
    }
    return false;
  }

  /**
   * Check whether a G2 class is a subclass of a G2 Event class
   */
  boolean isG2EventClass(Symbol className) {
    Symbol[] classInhPath = getClassInheritancePath(className);
    if (classInhPath == null) 
      return false;
    return isG2EventClass(className, classInhPath);
  }

  
  /**
   * Check whether a G2 class is the base G2-EVENT-OBJECT
   */
  static boolean isG2ClassG2EventClass(Symbol className_) {
    return (className_.equals(G2_EVENT_OBJECT_));
  }

  /**
   * Return the External Java Class Name of a G2 Listener Interface class
   */
  static String getExternalG2ListenerClassName(String G2ListenerName) {
    // check for package
    String className = G2ListenerName;
    int dotPos = G2ListenerName.lastIndexOf(".");
    if (dotPos > 1) {
      className = G2ListenerName.substring(dotPos + 1);
    }
    return "G2_" + className;
  }

  /**
   * Check whether a G2 class is a subclass of G2 Event Listener class
   * ??? Limited to direct subclass of G2-EVENT-LISTENER
   */
  static boolean isG2ListenerClass(Symbol className, Symbol[] classInhPath) {
    if (classInhPath.length < 1){
    	return false;
    }
    for (int i=0; i<classInhPath.length; i++) { 
      if (classInhPath[i].equals(G2_EVENT_LISTENER_) && !className.equals(G2_EVENT_LISTENER_)) 
	return true;
    }
    return false;
  }

  
  /**
   * Check whether a G2 class is the base G2-EVENT-LISTENER-CLASS
   */
  static boolean isG2ClassG2EventListenerClass(Symbol className_) {
    return (className_.equals(G2_EVENT_LISTENER_));
  }

  //A well known interface, that tags a G2 Item as being a G2 Proxy object
  static final String g2ProxyTagInterfaceName = "com.gensym.classes.G2_ProxyObject";
  public static final String g2ProxyTagInterfaceRealClassFieldName = "realG2ClassName";


  /**
   * Check whether a G2 class is the base G2 Proxy Object Class
   */
  static boolean isG2ClassG2ProxyClass(Symbol className_) {
    return (className_.equals(com.gensym.jgi.G2JavaStubController.JGI_PROXY_MIXIN_CLASS_));
  }

  /** Check whether a G2 class has the base G2 Proxy Object class in its inheritance
   */
  static boolean isSubclassOfG2ProxyClass(Symbol[] classInhPath) {
    Symbol JGI_PROXY_MIXIN_CLASS_ = com.gensym.jgi.G2JavaStubController.JGI_PROXY_MIXIN_CLASS_;
    int inhPathLength = classInhPath.length;

    for (int i=0; i< inhPathLength; i++) {
      if (classInhPath[i].equals(JGI_PROXY_MIXIN_CLASS_)) {
	// found proxy class
	  return true;
      }
    }
    return false;
  }

  /**
   * Return the super Class if g2ClassName is a proxy class for its super class
   * by having JGI_G2PROXY_MIXIN_CLASS_ mixed within its inheritance path.
   * For anybody wondering what this is all about...
   * This is for JavaLink professional where any G2 class and methods (via G2Script)
   * can be exported to Java (by copy). The Java proxy for the original G2 class can then be
   * reimported into G2 and subclassed from the original G2 class. G2 can request the
   * java proxy to be instanstiated in the connected VM, however as the java proxy 
   * inherits from the original G2 class, any method or rule references will also apply
   * to the external java instance.
   * This method will detect the java proxy, that has been subclassed from an existing G2 class,
   * when we hit the proxy, we must create an interface that points DefaultStubFactory to the 
   * the actual G2 class name, otherwise StubClassLoader will create stub interfaces for
   * the java proxy (as its already a java proxy for a G2 class, there is no need for it).
   */
  static Symbol getRealG2ClassForG2ProxyClass(Symbol g2ClassName, 
					      Symbol[] classInhPath) {

    Symbol JGI_G2PROXY_MIXIN_CLASS_ = com.gensym.jgi.G2JavaStubController.JGI_G2PROXY_MIXIN_CLASS_;
    int inhPathLength = classInhPath.length;

    if (inhPathLength < 2){
    	return null; // cant be a proxy class (inh path too short)
    }
    for (int i=0; i< inhPathLength; i++) {
      //System.out.println(i + " " + classInhPath[i]);
      if (classInhPath[i].equals(JGI_G2PROXY_MIXIN_CLASS_)) {
	// found proxy class
	// return the direct super class, as g2ClassName is a proxy for it
	  return classInhPath[1];
      }
    }
    return null;
  }


  /**
   * @undocumented
   */
  public static String getUserPackage() {
    String userPackage = System.getProperty ("com.gensym.class.user.package");
    if (userPackage == null)
      userPackage = "com.gensym.classes.modules";

    return userPackage;
  }

  /**
   * @undocumented
   */
  public static String getUserRepository() {
   return System.getProperty ("com.gensym.class.user.repository");
  }

  static boolean debug = false;
/* Uncomment this when you want to reenable debug setting.
  public static boolean setDebug(boolean value) {
    debug = value;
    return debug;
  }
  public static boolean getDebug() {
    return debug;
  }
*/

  static void debugIndent (String message) {
    int i;
    if (debug) {
      System.out.print(Thread.currentThread());
      for (i=0;i < classDepthTracing.size();i++)
	System.out.print("  ");
      System.out.print(classDepthTracing.size() + ": " + message + ": ");
      for (i=classDepthTracing.size()-1; i >= 0; i--)
	System.out.print(classDepthTracing.elementAt(i) + " ");
      System.out.println();
    }
  }

    void setTraceOn() {
        traceOn = Trace.getTraceOn();
    }
}


/**
 * This class exists purely so that its toString method is more
 * descriptive than Object
 */
class NullObject {
  @Override
  public String toString () {
    return "Null Object";
  }
}


class PseudoClassInfo {
  Symbol pseudoClassName;
  Vector classesToBlend;
  Symbol[] classesToCollect;
  Symbol[] originalInheritancePath;
  Symbol classToExtend;

  PseudoClassInfo(Symbol pseudoClassName,
		  Symbol classToExtend,
		  Vector classesToBlend,
		  Symbol[] classesToCollect,
		  Symbol[] originalInheritancePath) {
    this.pseudoClassName = pseudoClassName;
    this.classToExtend = classToExtend;
    this.classesToBlend = classesToBlend;
    this.classesToCollect = classesToCollect;
    this.originalInheritancePath = originalInheritancePath;
  }
    
}

class ModuleInfo {

  String javaPackageForModule;
  boolean moduleIsStable;

  ModuleInfo (String javaPackageForModule, boolean moduleIsStable) {
    this.javaPackageForModule = javaPackageForModule;
    this.moduleIsStable = moduleIsStable;
  }

}

class DefinitionInfo {

  ClassDefinition defn;
  Symbol moduleName_;

  DefinitionInfo (ClassDefinition defn, Symbol moduleName_) {
    this.defn = defn;
    this.moduleName_ = moduleName_;
  }

}
