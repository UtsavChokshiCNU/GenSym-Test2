/*
 * @(#)LocalStubClassLoader.java        1.0 98/08/15
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */
package com.gensym.jgi.download.local;


import java.io.File;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Hashtable;
import java.util.Enumeration;
import java.util.Locale;
import java.util.Hashtable;
import java.util.Vector;
import java.lang.reflect.Field;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.JGInterface;
import com.gensym.jgi.download.*;
import com.gensym.jgi.G2JavaStubController;
import com.gensym.jgi.G2Version;

import com.gensym.classes.G2Definition;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.ModuleInformation;
import com.gensym.classes.ClassFriendAccess;
import com.gensym.classes.Item;
import com.gensym.classes.Definition;
import com.gensym.classes.SystemPredicate;
import com.gensym.util.symbol.G2ClassSymbols;
import com.gensym.util.symbol.MethodExportSymbols;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.core.DebugUtil;
import com.gensym.g2script.Compiler;
import com.gensym.g2script.ClassInfoFactory;
import com.gensym.util.*;
import com.gensym.fida.ClassManager;
import com.gensym.naming.resource.*;

/**
 * This class is used to load the Local interfaces and the implementation
 * stubs for the G2 classes that are downloaded to Java. If it does
 * not find the classes in the <code>CLASSPATH</code>, it uses
 * introspection and additional overrides to generate an appropriate
 * Java class. Method contents are expected to be converted to Java bytecodes
 * using g2Script
 *
 * @version 	1.00, 08/15/98
 * @author      mgribble
 */

public class LocalStubClassLoader extends com.gensym.jgi.download.StubClassLoader {


  private final static String g2Package = "com.gensym.g2export" + ".";
  private final static String g2PackageWithoutDot = "com.gensym.g2export";
  private String userPackage = getLocalUserPackagePrefix();
  private String implPostfix = "Impl";
  protected Hashtable implVersionTable = new Hashtable(11);
  private Hashtable loadedG2ProxyImpls = new Hashtable();
  private Hashtable currentlyLoadingImpls = new Hashtable();
  private Hashtable currentlyLoadingInterfaces = new Hashtable();
  private Hashtable currentSystemLoadedInterfaces = new Hashtable();
  private Hashtable currentSystemLoadedImpls = new Hashtable();
  private boolean generateG2ProxyStubClass = true;
  private ClassManager classManager = null;

  static final Class BASE_JAVA_CLASS = com.gensym.g2export.G2__BaseImpl.class;
  static final Class BASE_JAVA_CLASS_INTERFACE = com.gensym.g2export.G2__Base.class;
  static final String BASE_JAVA_CLASS_NAME = "com.gensym.g2export.G2__BaseImpl";
  static final String BASE_JAVA_INTERFACE_NAME = "com.gensym.g2export.G2__Base";
  // NOTE: the following is kind of a hack: the hyphen is ensure
  // the the following "B" is capitalized when it is converted to
  // a "java name" by the G2ClassTranslator.
  static final Symbol BASE_INTERFACE_SYMBOL = Symbol.intern("G2__-BASE");

 private static final Symbol 
                              INSTANCE_METHODS_        = Symbol.intern ("INSTANCE-METHODS"),
                              EXPORTED_SOURCE_         = Symbol.intern ("EXPORTED-SOURCE"),
                              G2_METHOD_TEXT_          = Symbol.intern ("G2-METHOD-TEXT"),
			      CLASS_INHERITANCE_PATH_  = Symbol.intern ("CLASS-INHERITANCE-PATH"),
                              CLASS_ATTRIBUTES_        = Symbol.intern ("CLASS-ATTRIBUTES"),
                              INSTANCE_ATTRIBUTES_     = Symbol.intern ("INSTANCE-ATTRIBUTES"),
                              DIRECT_SUPERIOR_CLASSES_ = Symbol.intern ("DIRECT-SUPERIOR-CLASSES"),
                              SUBSTITUTE_JAVA_INTERFACE_CLASS_NAME_ = 
                                               Symbol.intern("SUBSTITUTE-JAVA-INTERFACE-CLASS-NAME"),
			      SUBSTITUTE_JAVA_IMPLEMENTATION_CLASS_NAME_ = 
                                               Symbol.intern("SUBSTITUTE-JAVA-IMPLEMENTATION-CLASS-NAME"),
			      EXPORT_CLASS_METHODS_TO_JAVA_ = Symbol.intern("EXPORT-CLASS-METHODS-TO-JAVA");

  private String getLocalUserPackagePrefix() {
    String userPackage = System.getProperty ("com.gensym.class.user.localpackage");
    userPackage = (userPackage == null ? "com.gensym.g2export.modules" : userPackage);
    return userPackage + ".";
  }

  protected Hashtable getAssignedPackages()
  {
    return assignedPackages;
  }

  protected Hashtable getClassInheritancePathTable()
  {
    return ClassInheritancePathTable;
  }

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
    Trace.registerMessageKey ("com.gensym.jgi.download.stubs", LocalStubClassLoader.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private LocalInterfaceGenerator igcuser;

  private static Hashtable connectionClassInfoTableTable = new Hashtable(5);

   /**
  * Constructs a new <code>StubClassLoader</code>. The <code>G2Access</code>
  * that is passed in to the constructor is used to obtain introspective
  * information about new G2 classes that are downloaded.
  * @param context A <code>G2Access</code> that is used to determine
  *                class information.
  */
  public LocalStubClassLoader(G2Access context) {
    this(context,
	  g2PackageWithoutDot,
	  (System.getProperty ("com.gensym.class.user.localpackage") == null ? 
	   "com.gensym.g2export.modules" : System.getProperty ("com.gensym.class.user.localpackage")),
	  new com.gensym.g2export.LocalClassFriendAccess());
    String g2Repository      = System.getProperty ("com.gensym.class.g2.repository");
    String userRepository    = System.getProperty ("com.gensym.class.user.repository");
    igcg2             = new LocalInterfaceGenerator (g2Package, g2Repository, null, systemClassNameMapper);
    igcuser           = new LocalInterfaceGenerator (userPackage, userRepository, 
						     new String[] {g2PackageWithoutDot+"/*"}, userClassNameMapper);
    setGenerationMode(StubClassLoader.GENERATION_AUTO);
    try {
      setExportMethodSource(true);
    } catch (G2AccessException e) {
      throw new StubCreationException("Could not export G2 Method Source, Wrong G2 Version (should be h20>) " +
				      e.toString());
    }
    classInfoTable = getClassInfoForConnection(context);
  }

  protected LocalStubClassLoader (G2Access context,
			   String g2Package,
			   String userPackage,
			   ClassFriendAccessor classFriend ) {
    super(context,
	  g2Package,
	  userPackage,
	  classFriend);
  }

  void setClassManager(ClassManager classManager)
  {
    if (this.classManager == null)
      this.classManager = classManager;
  }

  private Hashtable exportedToClassManagerHash = new Hashtable();
  
  private void informClassManager(Symbol g2ClassName,
				  Class clazz,
				  boolean isInterface,
				  boolean force)
  {
    try {
      if (classManager == null) return;
      if (exportedToClassManagerHash.get(clazz.getName()) == null) {
	ResourceDescriptor descriptor = null;
	if (!isInterface) {
	  String interfaceClassName = ((Class)loadedInterfaces.get(g2ClassName)).getName();
	  String bindName = interfaceClassName.replace('.','/')+".class";
	  descriptor = new InterfaceDescriptor(bindName,
					       getClassBytes(interfaceClassName),
					       "Exported Interface for G2 Class " + g2ClassName,
					       "",
					       clazz.getName());

	  classManager.export(descriptor);
       
	  bindName = clazz.getName().replace('.','/')+".class";
	  descriptor = new ClassDescriptor(bindName,
					   getClassBytes(clazz.getName()),
					   "Exported Impl for G2 Class " + g2ClassName,
					   "");
	  classManager.export(descriptor);
	  exportedToClassManagerHash.put(clazz.getName(), Boolean.TRUE);
	}
      }
    } catch (Exception e) {
      throw new RuntimeException(e.toString());
    }

  }

  private void informClassManager(Class clazz) 
  {
     try {
      String className = clazz.getName();
      if (classManager == null) return;
      if (exportedToClassManagerHash.get(className) == null) {
	ResourceDescriptor descriptor = null;
	if (!clazz.isInterface()) {
	  descriptor = new InterfaceDescriptor(className.replace('.','/')+".class",
					       getClassBytes(className),
					       "",
					       "",
					       clazz.getName());
	} else
	  descriptor = new ClassDescriptor(clazz.getName().replace('.','/')+".class",
					   getClassBytes(clazz.getName()),
					   "",
					   "");
	classManager.export(descriptor);
      }
    } catch (Exception e) {
      throw new RuntimeException(e.toString());
    }

  }

  private Hashtable getClassInfoForConnection(G2Access connection) {
    Hashtable classInfoTable = (Hashtable)connectionClassInfoTableTable.get(connection);
    if (classInfoTable == null) {
      classInfoTable = new Hashtable(21);
      connectionClassInfoTableTable.put(connection, classInfoTable);
    }
    return classInfoTable;
  }

  public String generateClassName(Symbol g2ClassName, boolean isInterface)
  {
    return super.generateClassName(g2ClassName, isInterface, false);
  }

  @Override
  protected InterfaceGenerator getUserInterfaceGenerator() {
    //System.out.println("In LocalStubClassLoader  getUserInterfaceGenerator()");
    return igcuser;
  }

  public Class lookupClassNoGeneration(Symbol g2ClassName, boolean isInterface) {
    Class localClass = (Class)(isInterface ? loadedInterfaces.get(g2ClassName) :
			    loadedStubs.get(g2ClassName));
    return localClass;
  }

  /**
   * This method will check and update for any class changes that may have occured on g2ClassName
   * since the last time a G2 Class was downloaded by a LocalStubClassLoader
   *@return true if we must regenerate the classes hierarchy
   */
  public boolean updateAndCheckForClassChange(Symbol g2ClassName, boolean onlyStub) {
    // Invalidate classInfo for this class, to make sure we reload the Method info
    // This dumb now, Better Invalidation checks to come
    Structure lastClassInfo = null;
    try {
      lastClassInfo = (Structure)classInfoTable.get(g2ClassName);
      if (lastClassInfo != null && 
	  isG2ClassResolveable(g2ClassName) && 
	  getAnySubstituteClass(g2ClassName, false) == null &&
	  !isClassStable(g2ClassName)){
	Sequence classInhPathSeq = 
	  (Sequence) lastClassInfo.getAttributeValue (CLASS_INHERITANCE_PATH_, null);
	//System.out.println("Got classInfo for " + g2ClassName);
	int numInPath = classInhPathSeq.size();
	for (int i =0; i < numInPath; i++) {
	  Symbol inhG2ClassName =(Symbol)classInhPathSeq.elementAt(i);
	  if (!com.gensym.classes.SystemPredicate.isSystemClass (inhG2ClassName) && 
	      isG2ClassResolveable(inhG2ClassName) &&
	      getAnySubstituteClass(inhG2ClassName, false) == null &&
	      !isClassStable(inhG2ClassName) ) {    
	    Structure classInfo = getClassInfo(inhG2ClassName, false);
	    Structure origClassInfo = (Structure)classInfoTable.get(inhG2ClassName);
	    //System.out.println("onlystub is "+onlyStub);
	    if (onlyStub) {
	      // Only stub, refesh methods, leave heir alone
	      refreshClassInfoMethodText(origClassInfo, classInfo);
	      // Clear out stub from previously loaded, table, so it is reloaded
	      // next time LoadClass is called
	      //System.out.println("removeing " + inhG2ClassName);
	      loadedStubs.remove(inhG2ClassName);
	    }
	    else
	      classInfoTable.put(inhG2ClassName, classInfo);
	  }
	}
      }
    } catch (G2AccessException e) {
      throw new StubCreationException(e.toString());
    }
    // return true if we have not seen the class before or we are only generating the stubs
    return (lastClassInfo == null || !onlyStub);
  }


  private void refreshClassInfoMethodText(Structure origClassInfo, Structure newClassInfo) {
    Symbol className = (Symbol)origClassInfo.getAttributeValue(CLASS_NAME_, null);
    Sequence om = (Sequence) origClassInfo.getAttributeValue (INSTANCE_METHODS_, null);
    Sequence nm = (Sequence) newClassInfo.getAttributeValue (INSTANCE_METHODS_, null);
    if (om == null || om == null) 
      throw new StubCreationException("Cant Find INSTANCE-ATTRIBUTES (orig = " + om + ", new = " + nm + ")");
    for (Enumeration origClassMethods = om.elements(); origClassMethods.hasMoreElements();) {
      Structure origMethodStruct = (Structure)origClassMethods.nextElement();
      Symbol    origMethodName = 
	(Symbol) origMethodStruct.getAttributeValue(MethodExportSymbols.METHOD_NAME_, null);
      Sequence   origArgumentTypes= (Sequence)origMethodStruct.getAttributeValue(ARGUMENT_TYPES_, null);
      Sequence   origResultTypes = (Sequence)origMethodStruct.getAttributeValue(RESULT_TYPES_, null);

      boolean foundMethodUpdate = false;
      
      // Find the same method in the new Structure
      for (Enumeration newClassMethods = nm.elements(); newClassMethods.hasMoreElements();) {
	Structure newMethodStruct = (Structure)newClassMethods.nextElement();
	if (newMethodStruct != null) {
	  Symbol    newMethodName = 
	    (Symbol) newMethodStruct.getAttributeValue(MethodExportSymbols.METHOD_NAME_, null);
	  Sequence newArgumentTypes= (Sequence)newMethodStruct.getAttributeValue(ARGUMENT_TYPES_, null);
	  Sequence newResultTypes = (Sequence)newMethodStruct.getAttributeValue(RESULT_TYPES_, null);
	  if (origMethodName.equals(newMethodName) &&
	      origArgumentTypes.equals(newArgumentTypes) &&
	      origResultTypes.equals(newResultTypes)) {
	    origMethodStruct.setAttributeValue(G2_METHOD_TEXT_, 
					       (String)newMethodStruct.getAttributeValue(G2_METHOD_TEXT_, ""));     
	    System.out.println("**Updated " + origMethodName);
	    foundMethodUpdate = true;
	    break;
	  }
	}
      }
      if (!foundMethodUpdate)
	// Raise an exception here ?
        throw new StubCreationException("The method " + className + "::" + origMethodName+ "(" + origArgumentTypes + ") could not be found or has changed, this " + className + " can not be updated");
      //System.out.println("**Warning :: No update for " + origMethodName + " (" + origArgumentTypes + ")");
    }
  }

  public synchronized Class loadClassFromSystem(Symbol g2ClassName, 
				    boolean isInterface)
  {
      Hashtable currentLoadedClasses = (isInterface ? 
					currentSystemLoadedInterfaces :
					currentSystemLoadedImpls);
      
      Class clazz = (Class)currentLoadedClasses.get(g2ClassName);
      try { 
	if (clazz == null) {
	  boolean isSystemClass = 
	    com.gensym.classes.SystemPredicate.isSystemClass (g2ClassName);
	  String packageName = null;
	  String className = generateClassName(g2ClassName, isInterface, false);
	  // Why is this being checked here ?
	  if (g2ClassName.toString().equals("DEFAULT-JUNCTION"))
	    className = (isInterface ? 
			 "com.gensym.g2export.DefaultJunction" : 
			 "com.gensym.g2export.DefaultJunctionImpl");
	  if (isSystemClass) {
	    packageName = g2Package;
	  } else {
	    Definition g2def = (Definition)getContext().getDefinition(g2ClassName);
	  Symbol moduleName = g2def.getContainingModule();
	  packageName = getPackageNameForModule(moduleName);
	  }
	  clazz = super.findSystemClass(packageName + "." + className);
	  currentLoadedClasses.put(g2ClassName, clazz);
	}
      } catch (G2AccessException e) {
	throw new StubCreationException(e.toString());
      } catch (ClassNotFoundException e) {
	Trace.exception(e);
	return null;
      }
      return clazz;
  }
	

  @Override
  public Class loadClass(Symbol g2ClassName, boolean isInterface) {
    
    //System.out.println("loadClass(" + g2ClassName + "," + isInterface + ")");
    Hashtable currentlyLoading = (isInterface ? 
				  currentlyLoadingInterfaces :
				  currentlyLoadingImpls);

    Class subsClass = getAnySubstituteClass(g2ClassName, isInterface);

    boolean doInformClassManager = !SystemPredicate.isSystemClass(g2ClassName);
    Boolean recordedForceDownLoad = null;
    // This is a HACK to allow us to stop generating for classes that we have
    // know are stable (we want to treat them like System classes effectively)
    // mucking around with the global forceDownload makes this not thread safe !!!!
    if (isClassStable(g2ClassName)) {
      boolean force = getForceDownload();
      recordedForceDownLoad = (force ? Boolean.TRUE : Boolean.FALSE);
      setForceDownload(false);
      doInformClassManager = false; // Stable classes should be on the classpath
    }

    // We record classes currently being loaded (so that we have information
    // for G2Script compiler). Note: Multi-threaded and recursive downloading is dealt 
    // by the StubClassLoader.
    currentlyLoading.put(g2ClassName, Thread.currentThread());

    //System.out.println(getForceDownload());
    Class clazz = super.loadClass(g2ClassName, isInterface);
    //System.out.println("super.loadClass is " + clazz + "for " + g2ClassName);

 
    // We support versioning for stubs
    if (!isInterface) {
      int version = 1;
      Integer versionObj = (Integer)implVersionTable.get(g2ClassName);
      if (versionObj != null)
	version = versionObj.intValue() + 1;
      implVersionTable.put(g2ClassName, new Integer(version));
    }

    if (clazz != null)
      currentlyLoading.remove(g2ClassName);

    if (recordedForceDownLoad != null)
      setForceDownload(recordedForceDownLoad.booleanValue());

    if (clazz != null && doInformClassManager)
      informClassManager(g2ClassName, clazz, isInterface, getForceDownload());

    if (subsClass != null) return subsClass;

    return clazz;
  }

  synchronized Class loadG2ProxyStub(Symbol g2ClassName) {
      generateG2ProxyStubClass = true;
      Class localProxyStub = (Class)loadedG2ProxyImpls.get(g2ClassName);
      if (localProxyStub == null) {
	loadClass(g2ClassName, false);
	localProxyStub =  (Class)loadedG2ProxyImpls.get(g2ClassName);
      }
      return localProxyStub;
  }

  synchronized Class loadG2ProxyStubOld(Symbol g2ClassName) {
      generateG2ProxyStubClass = true;
      Class localStub = (Class)loadedStubs.get(g2ClassName);
      loadedStubs.remove(g2ClassName);
      Class clazz = null;
      //try {
	clazz = loadClass(g2ClassName, false);
	loadedG2ProxyImpls.put(g2ClassName, clazz);
	//} finally {
	if (localStub != null) loadedStubs.put(g2ClassName, localStub);
	generateG2ProxyStubClass = false;
	//}
      return clazz;
  }

  //protected void ensureSuperInterfacesAreLoaded (Symbol[] classInheritancePath) {

    // We dont want to load the class hier for fullyQualifiedClassName 
    // as it will refer to a known Java class
  //Symbol g2ClassName = classInheritancePath[0];
  //if (!isG2ClassResolveable(g2ClassName)) return;
  //System.out.println("Letting " + g2ClassName + " through");

  //super.ensureSuperInterfacesAreLoaded(classInheritancePath);
  //}

  //protected void ensureDependentClassesAreLoaded (Structure classInfo, G2Access context) {
  // Sequence classInhPathSeq = 
  //   (Sequence) classInfo.getAttributeValue (CLASS_INHERITANCE_PATH_, null);

  // Symbol g2ClassName = (Symbol)classInhPathSeq.elementAt(0);
  //if (!isG2ClassResolveable(g2ClassName)) return;

  //System.out.println("Letting " + g2ClassName + " through");
  //super.ensureDependentClassesAreLoaded(classInfo, context);
  //}

  @Override
  protected void loadClassInfo(String className, Symbol g2ClassName, String javaClassName) {
    if (!isG2ClassResolveable(g2ClassName)) {
      Structure classInfo = new Structure();
      classInfo.setAttributeValue(CLASS_ATTRIBUTES_, new Sequence());
      classInfo.setAttributeValue(INSTANCE_ATTRIBUTES_, new Sequence());
      Sequence classInhPath = new Sequence();
      classInhPath.addElement(g2ClassName);
      classInfo.setAttributeValue(CLASS_INHERITANCE_PATH_, classInhPath);
      classInfo.setAttributeValue(CLASS_NAME_, g2ClassName);
      classInfo.setAttributeValue(DIRECT_SUPERIOR_CLASSES_, new Sequence());
      classInfo.setAttributeValue(IS_SYSTEM_DEFINED_, new Boolean(true));
      classInfoTable.put(g2ClassName, classInfo);
    }
    super.loadClassInfo(className, g2ClassName, javaClassName);
  }

  private boolean isG2ClassResolveable(Symbol g2ClassName) {
    // We dont want to load the class hier for fullyQualifiedClassName 
    // as it will refer to a known java class
    if (g2ClassName.toString().indexOf('.') > -1) 
      return false;

    // We can not allow root class of Java stubs to be resolved
    if (g2ClassName.equals(G2JavaStubController.JGI_PROXY_MIXIN_CLASS_))
      return false;

    return true;
  }
  

  @Override
  protected void makeClassDefinition (Symbol g2ClassName,
				    Class clazz,
				    boolean isSystemClass) throws G2AccessException {  
  }


  @Override
  protected byte[] generateInterface (InterfaceGenerator igc,
				      String generationPackage,
				      Symbol g2ClassName,
				      Symbol[] superClassNames,
				      Symbol[] classInheritancePath,
				      Sequence classAttrDescrpns,
				      Sequence attrDescrpns,
				      MethodInfo[] methodInfoArray,
				      Hashtable overridesTable) throws IOException, JavaClassCompilerException { 
	 if (!exportClassMethods(g2ClassName))
	   methodInfoArray = new MethodInfo[0];

	 //System.out.println("In generateInterface");
	 byte[] localClassBytes = 
	   ((LocalInterfaceGenerator)igc).generateLocalInterface (g2ClassName, generationPackage, superClassNames,
				       classInheritancePath, classAttrDescrpns, attrDescrpns, methodInfoArray);

	 return localClassBytes;

   }


  @Override
  protected byte[] generateStub (InterfaceGenerator igc,
				 Symbol g2ClassName, 
				 Symbol classToExtend,
				 Symbol[] classesToCollect,
				 String generationPackage, 
				 Symbol[] classInhPath,
				 Sequence ca, 
				 Sequence ia, 
				 MethodInfo[] methodInfoArray, 
				 Hashtable overridesInhTable) throws IOException {

	  Integer versionObj = (Integer)implVersionTable.get(g2ClassName);
	  String versionStr = (versionObj == null ? "" : versionObj.toString());
	  byte[] localClassBytes;

	  Class javaClassToExtend = null;
	  if (G2ClassSymbols.ROOT_.equals(g2ClassName) || 
	      (classToExtend.toString().indexOf(".") > 0))			  
	    // Root and fully qualified interface name extends BaseImpl
	    javaClassToExtend = BASE_JAVA_CLASS;
	  else 
	    javaClassToExtend = (Class)loadedStubs.get(classToExtend); // better be there already!
	  

	  //if (generateG2ProxyStubClass) {
	  //  byte[] localProxyClassBytes = 
	  //    ((LocalInterfaceGenerator)igc).generateLocalG2ProxyStub (g2ClassName,
	  //							       javaClassToExtend,
	  //							       classesToCollect,
	  //	 						       versionStr,
	  //	 						       generationPackage, 
	  //							       classInhPath,
	  //							       ca, 
	  //							       ia, 
	  //							       methodInfoArray, 
	  //							       g2ScriptCompiler, 
	  //							       localClassInfoFactory);
	  //  Class clazz = loadClassBytes(localProxyClassBytes);
	  //  loadedG2ProxyImpls.put(g2ClassName, clazz);
	  //} 

	    Sequence defAttrInitializationDescrpns = null;
	    try {
	      // Attribute initializations of a G2 class override inherited attributes init
	      com.gensym.classes.G2Definition def = getClassManager().getDefinition(g2ClassName);
	      defAttrInitializationDescrpns = def.getAttributeInitializations();
	    } catch (G2AccessException ex) {
	      throw new StubCreationException(ex.toString());
	    }

	    //for (int i = 0;  i<methodInfoArray.length; i++) {
	    //  System.out.println(methodInfoArray[i].getG2MethodSource() 
	    //		 + " " + methodInfoArray[i].getDefiningG2Class());
	    //}

	    for (int i = 0; i<methodInfoArray.length; i++) {
	      Symbol definingClass = methodInfoArray[i].getAbsoluteG2ClassReference();
	      if (definingClass == null) definingClass = methodInfoArray[i].getDefiningG2Class();
	      if (!exportClassMethods(definingClass)) {
		methodInfoArray[i].setActive(false);
		//System.out.println("Set " + methodInfoArray[i].getG2MethodName() + " " + definingClass);
	      }
	    }

	    localClassBytes = 
	      ((LocalInterfaceGenerator)igc).generateLocalStub (g2ClassName,
								javaClassToExtend,
								classesToCollect,
								versionStr,
								generationPackage, 
								classInhPath,
								ca, 
								ia,
								defAttrInitializationDescrpns,
								methodInfoArray, 
								g2ScriptCompiler, 
								localClassInfoFactory);

	    
	  return localClassBytes;
  }


  //protected void readOverridesIfAny (String className, 
  //			     Symbol g2ClassName, 
  //			     boolean isSystemDefined, 
  //			     Structure classInfo) {
  //}

  /**
   * Check and return method text for a G2 class, given data read from classInfo
   */
  @Override
  protected String checkMethodText(Symbol g2ClassName, Structure g2MethodData, String methodText) {
    //System.out.println("Was asked to check \n" + methodText);
    return methodText;
  }

  /**
   * Makes sure the class is initialized before getting the dependent classes
   */
  @Override
  public Symbol[] getDependentClasses (Symbol g2ClassName) {
    Symbol[] dependentClasses = super.getDependentClasses(g2ClassName);
    return dependentClasses;
  }


  private static final Symbol JAVA_PACKAGE_FOR_EXPORT_
                    = Symbol.intern ("JAVA-PACKAGE-FOR-EXPORT");
  private static final Symbol JAVA_PACKAGE_FOR_LOCAL_EXPORT_
                    = Symbol.intern ("JAVA-PACKAGE-FOR-LOCAL-EXPORT");
  private static final Symbol JAVA_EXPORTED_PACKAGE_STABILITY_
                    = Symbol.intern ("JAVA-EXPORTED-PACKAGE-STABILITY");
  private static final Symbol STABLE_
                    = Symbol.intern ("STABLE");
  private static final Symbol ANNOTATION_NAME_
                    = Symbol.intern ("ANNOTATION-NAME");
  private static final Symbol ANNOTATION_VALUE_
                    = Symbol.intern ("ANNOTATION-VALUE");

  private static final Hashtable exportedPackageStabilityTable = new Hashtable();

  protected boolean isClassStable(Symbol g2ClassName)
  {
    G2Definition g2Definition = null;
    try {
      g2Definition = getContext().getDefinition(g2ClassName);
 
      if (g2Definition instanceof Definition) {
	Definition def = (Definition)g2Definition;
	Symbol module = def.getContainingModule();
	Boolean stable = (Boolean)exportedPackageStabilityTable.get(module);
	if (stable != null)
	  return stable.booleanValue();
      }
    } catch (G2AccessException e) {
      throw new RuntimeException("Could not read G2 Module Stability for " + g2ClassName 
				 + " because of " + e.toString());
    }
    return false;
  }


  /**
   * Extracts the package prefix specified in the module-annotations
   * Sequence.
   * @param annotations the annotations Sequence
   * @return String the package-prefix (may be null)
   */
  @Override
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


  /**
   * Return the exported PackageName for a Module
   */
  protected String getExportPackage(Sequence moduleAnnotations, Symbol moduleName_) {
    String javaExportPackageForModule = 
      getSpecificAnnotation (moduleAnnotations, JAVA_PACKAGE_FOR_LOCAL_EXPORT_);
    String javaLinkExportPackageForModule = 
      getSpecificAnnotation (moduleAnnotations, JAVA_PACKAGE_FOR_EXPORT_);
    if (javaLinkExportPackageForModule != null &&
	javaExportPackageForModule != null &&
	javaLinkExportPackageForModule.equals(javaExportPackageForModule))
      throw new RuntimeException("Module Annotation " + JAVA_PACKAGE_FOR_LOCAL_EXPORT_ 
				 + "is not allowed to be the same as " + 
				 JAVA_PACKAGE_FOR_EXPORT_ + " in module " + moduleName_);
    if (javaExportPackageForModule == null) {
      String packageName = makeJavaPackageNameForModule (moduleName_);
      javaExportPackageForModule = userPackage + packageName;
    }

    // Check for stability
    Object stableObj = extractAttributeFromAnnotations(moduleAnnotations, JAVA_EXPORTED_PACKAGE_STABILITY_);
    if (stableObj != null && stableObj instanceof Symbol && STABLE_.equals(stableObj))
      exportedPackageStabilityTable.put(moduleName_, Boolean.TRUE);
    else 
      exportedPackageStabilityTable.put(moduleName_, Boolean.FALSE);

    return javaExportPackageForModule;
  }

  protected Object extractAttributeFromAnnotations (Sequence annotations, Symbol interestedAnnotationName) {
    for (Enumeration e = annotations.elements ();
	 e.hasMoreElements ();) {
      Structure annotation   = (Structure) e.nextElement ();
      Symbol annotationName_ = (Symbol) annotation.getAttributeValue (ANNOTATION_NAME_, null);
      if (annotationName_.equals (interestedAnnotationName)) { // can never be null?
	Object annotationValue = annotation.getAttributeValue (ANNOTATION_VALUE_, null);
	return annotationValue;
      }
    }
    return null;
  }

  // The javac compiler needs a freaking overhaul
  @Override
  protected G2Access getContext () {
    return super.getContext ();
  }

  private Hashtable exportClassMethodsCheckTable = new Hashtable();

  boolean exportClassMethods(Symbol g2ClassName) {
    
    Boolean check = (Boolean)exportClassMethodsCheckTable.get(g2ClassName);
    if (check != null)
      return check.booleanValue();

    G2Definition g2Definition = null;
    try {
      g2Definition = getContext().getDefinition(g2ClassName);
    } catch (G2AccessException e) {
      throw new RuntimeException("Could not read G2 Defintion for " + g2ClassName 
				 + " because of " + e.toString());
    }
    try {
      check = 
	(Boolean)((Item)g2Definition).getPropertyValue(EXPORT_CLASS_METHODS_TO_JAVA_);
    } catch (Exception e) {
      Trace.exception(e, "No Substitute Interface found");
      check = new Boolean(true);
    }
    
    exportClassMethodsCheckTable.put(g2ClassName, check);

    return check.booleanValue();
  }


  private static final Hashtable substituteInterfaces  = new Hashtable();
  private static final Hashtable substituteClasses = new Hashtable();
  static {
    // Allow generic references to be java.lang.Object not com.gensym.g2exort.Object
    substituteInterfaces.put(OBJECT_, java.lang.Object.class);
    substituteInterfaces.put(ITEM_, java.lang.Object.class);
    substituteInterfaces.put(ITEM_OR_VALUE_, java.lang.Object.class);
  }

  

  Class getAnySubstituteClass(Symbol g2ClassName, boolean isInterface) {
    
    Class externalClass = (Class)(isInterface ? substituteInterfaces.get(g2ClassName) :
	                  substituteClasses.get(g2ClassName));
    G2Definition g2Definition = null;
    try {
      g2Definition = getContext().getDefinition(g2ClassName);
    } catch (G2AccessException e) {
      throw new RuntimeException("Could not read G2 Defintion for " + g2ClassName 
				 + " because of " + e.toString());
    }
    String subIntfClassName = null;
    String subImplClassName = null;
    try {
      if (g2Definition instanceof Item) {
	subIntfClassName = 
	  (String)((Item)g2Definition).getPropertyValue(SUBSTITUTE_JAVA_INTERFACE_CLASS_NAME_);
	if (subIntfClassName != null) {
	  try {
	    subImplClassName = 
	      (String)((Item)g2Definition).getPropertyValue(SUBSTITUTE_JAVA_INTERFACE_CLASS_NAME_);
	  } catch (NoSuchAttributeException e) {
	    throw new RuntimeException("In class definition " + g2ClassName + 
				       ", when declaring a substitute interface " + subIntfClassName + 
				       "you must also declare a substitute implementation class name");
	  }
	}
      }
    } catch (Exception e) {
      Trace.exception(e, "No Substitute Interface found");
    }

    if (subIntfClassName != null && subImplClassName != null) {
      try {
	if (isInterface) {
	  if (!subIntfClassName.equals("")) {
	    externalClass = super.findSystemClass(subIntfClassName);    
	    if (externalClass != null) {
	      substituteInterfaces.put(g2ClassName, externalClass);
	    }
	  } else if (!subImplClassName.equals("")) {
	    externalClass = super.findSystemClass(subImplClassName); 
	    if (externalClass != null) {
	      substituteClasses.put(g2ClassName, externalClass);
	    }
	  }
	}
      } catch (ClassNotFoundException e) { 
	throw new RuntimeException("Can not find substitute external Java Class " + 
				   (isInterface ? subIntfClassName : subImplClassName ) + 
				   "for qualified G2 class " + g2ClassName);
      }

    } else if (g2ClassName.toString().indexOf('.') > -1) {
      // Fully qualified names are assumed not to be G2 classes
      String javaName = null;
      try {
        javaName = getFullyQualifiedJavaClassNameFromG2Name(g2ClassName);
	externalClass = super.findSystemClass(javaName);
	//if (!externalClass.isInterface() && isInterface)
	//  throw new StubCreationException("G2 classes only extend Java interfaces not. " + 
	//				  g2ClassName + " refers to a Java Class " + 
	//				  externalClass + " which is not an interface");
      } catch (ClassNotFoundException e) { 
	throw new RuntimeException("Can not find external Java Class " + javaName + 
				   "for qualified G2 class " + g2ClassName);
      }
    } else if (!isG2ClassResolveable(g2ClassName)) {
      externalClass = (isInterface ? BASE_JAVA_CLASS_INTERFACE  : 
		       BASE_JAVA_CLASS);
    }

    return externalClass;
  }


  protected LocalClassNameMapper systemClassNameMapper = new LocalClassNameMapper () {
    private String stdPrefix = g2Package; //g2package is a static, so it will be init
    private String g2VersionString;

    @Override
    public String substituteJavaClassNameFromG2ClassName (Symbol g2ClassName_) {
      Class subsClass = getAnySubstituteClass(g2ClassName_, true);
      return (subsClass == null ? null : subsClass.getName());
    }

    @Override
    public String javaClassNameFromG2ClassName (Symbol g2ClassName_) {
      return stdPrefix + G2ClassTranslator.createJavaClassNameFromG2ClassName (g2ClassName_);
    }
    @Override
    public String getVersionForClass (Symbol g2ClassName_) {
      //ignore class-name
      if (g2VersionString == null) {
	G2Version g2Version = getContext().getG2Version ();
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

  protected LocalClassNameMapper userClassNameMapper = new LocalClassNameMapper () {
    private String stdPrefix = getLocalUserPackagePrefix();

    @Override
    public String substituteJavaClassNameFromG2ClassName (Symbol g2ClassName_) {
      Class subsClass = getAnySubstituteClass(g2ClassName_, true);
      return (subsClass == null ? null : subsClass.getName());
    }

    @Override
    public String javaClassNameFromG2ClassName (Symbol g2ClassName_) {

      // Qualified names refer driectly to Java classes
      if (g2ClassName_.toString().indexOf('.') > -1) 
	return G2ClassTranslator.createJavaClassNameFromG2ClassName (g2ClassName_);

      Class clazz = (Class)getLoadedInterfaces().get (g2ClassName_);
      if (clazz == null) {
	String previouslyAssignedPackage = (String) lookupAssignedPackage (g2ClassName_);
	if (previouslyAssignedPackage != null) {
	  //System.out.println (">>> NameMapper: " + g2ClassName_ + " -> previously assigned to " + previouslyAssignedPackage);
	  stdPrefix = previouslyAssignedPackage + ".";
	} else {
	  // Please leave this alone!
	  System.out.println (">>> NameMapper: " + g2ClassName_ + " -> Duh? returning fallback " + stdPrefix);
	  Thread.dumpStack ();
	  System.exit (2);
	}
	return stdPrefix + G2ClassTranslator.createJavaClassNameFromG2ClassName (g2ClassName_);
      } else {
	//System.out.println (">>> NameMapper: " + g2ClassName_ + " -> Previously loaded class : " + clazz.getName ());
	return clazz.getName ();
      }
    }
    @Override
    public String getVersionForClass (Symbol g2ClassName_) {
      return "";
    }
  };

  
  ClassInfoFactory getClassInfoFactory() {
    return localClassInfoFactory;
  }

  /**
   * ClassInfoFactory provides information for the G2Script Compiler
   */
  protected ClassInfoFactory localClassInfoFactory = new ClassInfoFactory() {
    // There are calls to loadClass here, these methods must NOT be called
    // when generating interfaces, as it may destroy the interface loading order
    private String stdSysPrefix =  g2Package;
    private String stdPrefix = getLocalUserPackagePrefix();

    @Override
    public com.gensym.classtools.ClassInfo generateClassInfo(String className) {
      return null;
    }

    /**
     * Some knowledge of how G2script calls this is very useful...
     * It always asks the Factory method for the Java Name for a g2ClassName
     * so if its refering to a Java Class, we can do a loadClass to make sure its
     * loaded, as G2Script will attempt to load the class next.
     * Call getClassForName below
     */
    @Override
    public String getJavaNameForG2ClassName(String g2ClassName) {
      System.out.println("getJavaNameForG2ClassName(" + g2ClassName + ")");
      Symbol g2ClassName_ = Symbol.intern(g2ClassName);
      // Qualified G2 Class names are assumed to refer to Java Class names...leave alone
      if (g2ClassName.indexOf('.') > -1) {
	String unqClassName = g2ClassName.substring(g2ClassName.lastIndexOf(".")+1);
	String packageName = g2ClassName.substring(0,g2ClassName.lastIndexOf("."));
	return packageName.toLowerCase() + "." + 
	  G2ClassTranslator.createJavaClassNameFromG2ClassName (Symbol.intern(unqClassName));
      }

      // This is a G2 Class reference, generate its local class name
      Class clazz = loadClass(g2ClassName_, true);
      return (clazz == null ? null : clazz.getName());
    }

    @Override
    public Class getClassForName(String javaClassName) throws ClassNotFoundException {
      //System.out.println("getClassForName(" + javaClassName + ")");
      String g2ClassNameStr = javaClassName.substring(javaClassName.lastIndexOf(".")+1);
      // and just in case Descriptor classes are sent
      g2ClassNameStr = g2ClassNameStr.substring(g2ClassNameStr.lastIndexOf("/")+1);
      Symbol g2ClassName = null;
      boolean isImpl = false;
      
      if (javaClassName.endsWith(implPostfix)) {
	g2ClassName = 
	  G2ClassTranslator.createG2ClassNameFromJavaClassName(
				  g2ClassNameStr.substring(0,g2ClassNameStr.lastIndexOf(implPostfix)));
	isImpl = true;
	//System.out.println("Is Impl...");
      } else
	g2ClassName = G2ClassTranslator.createG2ClassNameFromJavaClassName(g2ClassNameStr);
	
      System.out.println("Trying to load " + g2ClassName);

      // Search for a previously loaded class that matches this Java Name
      for (Enumeration e = getLoadedInterfaces().elements(); e.hasMoreElements();) {
	Class clazz = (Class)(e.nextElement());
	if (clazz.getName().equals(javaClassName)) {
	  if (!isImpl) {
	    // Return the interface
	    Class subsIntf = getAnySubstituteClass(g2ClassName, true);
	    Class returnClass =  (subsIntf == null ? clazz : subsIntf);
	    System.out.println(" getClassForName returned " + returnClass);
	    return returnClass;
	  }
	  else return loadClass(g2ClassName, false); // Return the stub (load if necessary)
	}
      }
      System.out.println("Check currentlyLoading");
      
      // May be the class is currently loading
      Hashtable currentlyLoading = (isImpl ? currentlyLoadingImpls : currentlyLoadingInterfaces);
      for (Enumeration e = currentlyLoading.keys(); e.hasMoreElements();) {
	Symbol currentlyLoadingClassName = (Symbol)(e.nextElement());
	System.out.println(currentlyLoadingClassName);
	if (currentlyLoadingClassName.equals(g2ClassName))
	  return null; // we have not finished loading this yet
      }

      // Does ths package spec match what known prefixes
      //if (javaClassName.indexOf(stdSysPrefix) > -1 ||
      //  javaClassName.indexOf(stdPrefix) > -1 ) {
	// G2 class references should have been found above, this is a catch
	// This is a G2 class reference, load any required interfaces
      //Class jlClassIntf = loadClass(g2ClassName, true);
      //System.out.println("Loaded " + g2ClassName + " from jlClassIntf" );
      //return jlClassIntf;
      //} else {
      System.out.println("Loading " + g2ClassName + " from system");
      return findSystemClass1 (javaClassName); // Not a G2 class reference
    }

    @Override
    public String getImplementationClassName(String interfaceName) {
      Class subsImpl = null;
      for (Enumeration e = substituteInterfaces.keys(); e.hasMoreElements();) {
	Symbol g2ClassName = (Symbol)e.nextElement();
	Class clazz = (Class)substituteInterfaces.get(g2ClassName);
	if (clazz.getName().equals(interfaceName)) {
	    // Return the interface
	    subsImpl = (Class)substituteClasses.get(g2ClassName);
	    break;
	}
      }
      if (subsImpl == null)
	return interfaceName + implPostfix;
      else
	return subsImpl.getName();
    }

    /** Denote an interface as being special 
     * regarding the fact that it would like to have fields, yet 
     * can only have Java Beans style properties
     */
    @Override
    public boolean interfaceHasImplicitProperties(String qualifiedName) {
      return true;
    }
      
    /** Returned name MUST be the name of a method on the interface
     *  for further introspection.
     */
    @Override
    public String getImplicitPropertyGetter(String interfaceName, 
					    String g2AttributeName) {
      //System.out.println("getImplicitPropertyGetter(" + interfaceName + "," + g2AttributeName + ")");
     String str = "get" + G2ClassTranslator.initCap(G2ClassTranslator.slotNameFromG2Slot(g2AttributeName));
     return str;
    }
    
    @Override
    public String getImplicitPropertySetter(String interfaceName, 
					    String g2AttributeName) {
      //System.out.println("getImplicitPropertySetter(" + interfaceName + "," + g2AttributeName + ")");
      return "set" + G2ClassTranslator.initCap(G2ClassTranslator.slotNameFromG2Slot(g2AttributeName));
    }

    @Override
    public boolean allowGlobalNameReferences() {
      return true;
    }
  };

  protected Compiler g2ScriptCompiler = new Compiler(localClassInfoFactory);

  /*
   * This method is used to bounce the call to findSystemClass.
   * This works around a bug in the JDK 1.1.5- compiler that inner
   * classes do not have access to inherited protected methods of
   * the outer class.
   */
  private Class findSystemClass1 (String className) throws java.lang.ClassNotFoundException {
    return super.findSystemClass (className);
  }

  @Override
  protected Hashtable getLoadedInterfaces() {
    return loadedInterfaces;
  }

  @Override
  protected String lookupAssignedPackage(Symbol g2ClassName) {
    return (String)assignedPackages.get(g2ClassName);
  }

  @Override
  protected Hashtable getLoadedStubs() {
    return loadedStubs;
  }  

  @Override
  protected Class loadClassBytes(byte[] classbytes) {
    	Class clazz = defineClass (null, classbytes, 0, classbytes.length);
	resolveClass (clazz);
	return clazz;
  }

  private String getFullyQualifiedJavaClassNameFromG2Name(Symbol g2ClassSymbol) {
    String g2ClassName = g2ClassSymbol.toString();
    String g2ClassNameNotQualified = g2ClassName.substring(g2ClassName.lastIndexOf(".")+1);
    String packageName = g2ClassName.substring(0, g2ClassName.lastIndexOf(".")).toLowerCase();
    return packageName + "." + 
      G2ClassTranslator.createJavaClassNameFromG2ClassName(Symbol.intern(g2ClassNameNotQualified));
  }

  public byte[] getClassBytes(String className) throws ClassNotFoundException {
    // try user byte cache first
    byte[] classBytes = igcuser.getClassBytes(className);
    if (classBytes == null)
      classBytes = com.gensym.naming.resource.ResourceLoader.getClassDataFromSystem(className);
    return classBytes;
  }


}
