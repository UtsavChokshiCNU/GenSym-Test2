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
 * This class is used to load the Local proxy implementation
 * stubs for the G2 classes that are downloaded to Java. If it does
 * not find the classes in the <code>CLASSPATH</code>, it uses
 * introspection and additional overrides to generate an appropriate
 * Java class. Method contents are expected to be converted to Java bytecodes
 * using g2Script
 *
 * @version 	1.00, 03/15/99
 * @author      mgribble
 */

public class LocalProxyStubClassLoader extends LocalStubClassLoader {

  private LocalStubClassLoader parentClassLoader;
  static final Class BASE_JAVA_CLASS = com.gensym.g2export.G2__ProxyBaseImpl.class;
  static final String BASE_JAVA_CLASS_NAME = "com.gensym.g2export.G2__ProxyBaseImpl";

  public LocalProxyStubClassLoader(G2Access context, 
			      LocalStubClassLoader parentClassLoader) {
 
    super(context);
    this.parentClassLoader = parentClassLoader;
    //loadedInterfaces = parentClassLoader.getLoadedInterfaces();
    //assignedPackages = parentClassLoader.getAssignedPackages();
    //ClassInheritancePathTable = parentClassLoader.getClassInheritancePathTable();
  }

  @Override
  public Class loadClass(Symbol g2ClassName, boolean isInterface)
  {
    if (isInterface) 
      // ensure main interface loaded
      parentClassLoader.loadClass(g2ClassName, true).hashCode();

    Class clazz = super.loadClass(g2ClassName, isInterface);
    //System.out.println("After..." + clazz + " " + clazz.hashCode());
    return clazz;
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
	  
	  localClassBytes = 
	    ((LocalInterfaceGenerator)igc).generateLocalG2ProxyStub (g2ClassName,
								     javaClassToExtend,
								     classesToCollect,
								     versionStr,
								     generationPackage, 
								     classInhPath,
								     ca, 
								     ia, 
								     methodInfoArray, 
								     g2ScriptCompiler, 
								     localClassInfoFactory);

	    
	  return localClassBytes;
  }

  @Override
  protected String generateStubClassName (Symbol className_) {
    return G2ClassTranslator.createJavaClassNameFromG2ClassName (className_) + "_G2Proxy_Impl";
  }

  @Override
  public Class loadClass (String className, boolean resolve) throws ClassNotFoundException{
    //System.out.println("loadClass " + className + " " + resolve);

    Class clazz = null;
    try {
      clazz = super.findSystemClass (className);
    } catch (ClassNotFoundException cnfe) {
      throw cnfe;
      //throw new InternalError ("StubClassLoader error!");
    }
    if (resolve)
      resolveClass (clazz);
    return clazz;
  }
}
