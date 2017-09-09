
package com.gensym.jgi.download.local;

import java.io.*;
import java.util.Enumeration;
import java.util.Locale;
import java.util.Hashtable;
import com.gensym.util.symbol.*;
import com.gensym.types.G2Type;
import com.gensym.g2script.Compiler;
import com.gensym.g2script.ClassInfoFactory;
import com.gensym.util.*;
import com.gensym.jgi.download.*;
import com.gensym.classtools.ClassInfo;
import com.gensym.classtools.ClassException;

import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

class LocalInterfaceGenerator extends InterfaceGenerator implements G2TypeSymbols, 
                                           AttributeTypeSpecificationSymbols,
                                           AttributeExportSymbols,
                                           MethodExportSymbols,
                                           SystemAttributeSymbols {

  // Tracing stuff
  static private MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.download.stubs",
			   LocalInterfaceGenerator.class);
  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;

  static final String specialExtensionName = "Special";
  static final String stubExtension = "Impl";
  static final String proxyStubExtension = "_G2Proxy_";
  static final String stubSpecialExtension = specialExtensionName + stubExtension;
  static final String stubProxySpecialExtension = specialExtensionName + proxyStubExtension + stubExtension;

  private Hashtable classByteCache = new Hashtable();
  private LocalClassNameMapper localNameMapper;

  /**
   * @param genPackage the name of the package in which this InterfaceGenerator will
   * generate classes in, eg. "COM/sun/java/ding"
   * @param location the directory location for the source and
   * class files. "/home/me/java/gensources/"
   * @specificImports a String array containing package class references
   * or specific classes that override the generic imports. May be null to indicate
   * no specific imports.
   */
  LocalInterfaceGenerator (String genPackage,
			   String location,
			   String[] specificImports,
			   LocalClassNameMapper nameMapper) {
    super(genPackage, location, specificImports, nameMapper);
    localNameMapper = nameMapper;
  }

  /**
   * Returns the fully qualified name of the interface.
   */
  byte[] generateLocalInterface (Symbol className_,
			    String genPackage,
			    Symbol[] superClassNames,
			    Symbol[] classInheritancePath,
			    Sequence classAttrDescrpns,
			    Sequence attrDescrpns,
			    MethodInfo[] methodInfoArray) throws IOException {
    String className = className_.getPrintValue ();
    String javaClassName = G2ClassTranslator.createJavaClassNameFromG2ClassName (className_);
    String filename = ensureDirectory (genPackage) + separator +
                      G2ClassTranslator.createJavaClassNameFromG2ClassName (className_) + ".class";
    FileOutputStream fileStream = 
      new FileOutputStream (filename);
    //System.out.println("Filename = " + filename);
    LocalClassGenerationContext igc = new LocalClassGenerationContext (fileStream,
								       true,
								       genPackage,
								       className,
								       localNameMapper);
    String[] superInterfaces = createJavaClassNamesFromG2ClassNames (superClassNames);
    AttrInfo a = getAttributeInfo (classAttrDescrpns, attrDescrpns);

    String mergeFileName = ensureDirectory (genPackage) + separator +
                           javaClassName + 
                           stubSpecialExtension  + ".class";

    ClassInfo ovrClassInfo = null;
    try {    
      File mergeFile = new File(mergeFileName);
      if (mergeFile.exists()) {
	FileInputStream mergeFileStream = new FileInputStream (mergeFileName);
	ovrClassInfo = new ClassInfo(mergeFileStream);
	mergeFileStream.close ();
      }
    } catch (ClassException e) {
      e.printStackTrace();
      throw new RuntimeException("Problem during Interface Override merge " + e.toString());
    }

    igc.generateClass (imports, 
		       null, 
		       superInterfaces, 
		       classInheritancePath,
                       a, 
		       methodInfoArray,
		       ovrClassInfo);

    byte[] bytes = igc.writeClass();
    System.out.flush ();
    fileStream.close ();

    classByteCache.put(genPackage + "." + javaClassName, bytes);

    return bytes;
			      
  }
  
  byte[] generateLocalStub (Symbol className_,
			    Class classToExtend,
			    Symbol[] classesToCollect,
			    String version,
			    String genPackage,
			    Symbol[] classInheritancePath,
			    Sequence classAttrDescrpns,
			    Sequence attrDescrpns,
			    Sequence attrInitializationDescrpns,
			    MethodInfo[] methodInfoArray,
			    Compiler compiler,
			    ClassInfoFactory localClassInfoFactory) 
       throws IOException, G2ClassCompilerException
  {
    String className = className_.getPrintValue ();
    String javaClassName = G2ClassTranslator.createJavaClassNameFromG2ClassName (className_);
    String intfName = genPackage + "." + javaClassName;
    String fileName = ensureDirectory (genPackage) + separator + 
                      javaClassName + stubExtension + version + ".class";
    String fullyQJavaClassName = genPackage + "." + javaClassName + stubExtension + version;
    
    FileOutputStream fileStream = new FileOutputStream (fileName);
    LocalStubGenerationContext igc = new LocalStubGenerationContext (fileStream,
								     false,
								     genPackage,
								     className,
								     version,
								     stubExtension,
								     localNameMapper,
								     compiler,
								     localClassInfoFactory);
    AttrInfo a = getAttributeInfo (classAttrDescrpns, attrDescrpns);
    AttrInfo ia = parseDefinitionAttributeInitializations(attrInitializationDescrpns);
    igc.generateLocalClassImpl (imports,
				classToExtend.getName(),
				classesToCollect,
				new String[] {intfName}, 
				classInheritancePath,
				a, 
				ia,
				methodInfoArray);
    System.out.flush ();
    // Merge in any override methods
    mergeSpecialImpls(classesToCollect,
		      stubSpecialExtension,
		      igc);
    byte[] bytes = igc.writeClass();
    fileStream.close ();

    classByteCache.put(fullyQJavaClassName, bytes);

    return bytes;
  }

  void mergeSpecialImpls(Symbol[] classesToCollect,
			 String specialStubExtension,
			 LocalStubGenerationContext igc) throws IOException
  {
    // Merge in any override methods
    for (int i = 0; i<classesToCollect.length; i++) {
      String javaName = localNameMapper.javaClassNameFromG2ClassName(classesToCollect[i]);
      String homePackage = javaName.substring(0, javaName.lastIndexOf('.'));
      String mergeFileName = 
	ensureDirectory (homePackage) + 
	separator +               
	G2ClassTranslator.createJavaClassNameFromG2ClassName(classesToCollect[i]) + 
	specialStubExtension + ".class";
      System.out.println("looking for special " + mergeFileName );
      File mergeFile = new File(mergeFileName);
      if (mergeFile.exists()) {
	FileInputStream mergeFileStream = new FileInputStream (mergeFileName);
	igc.mergeClass(mergeFileStream);
	mergeFileStream.close ();
      }
    }
  } 

  byte[] generateLocalG2ProxyStub (Symbol className_,
				   Class classToExtend,
				   Symbol[] classesToCollect,
			    String version,
			    String genPackage,
			    Symbol[] classInheritancePath,
			    Sequence classAttrDescrpns,
			    Sequence attrDescrpns,
			    MethodInfo[] methodInfoArray,
			    Compiler compiler,
			    ClassInfoFactory localClassInfoFactory) throws IOException {
    String stubExtension = "_G2Proxy_Impl";
    String className = className_.getPrintValue ();
    String intfName = genPackage + "." + G2ClassTranslator.createJavaClassNameFromG2ClassName (className_);
    String fileName = ensureDirectory (genPackage) + separator + 
                      G2ClassTranslator.createJavaClassNameFromG2ClassName(className_) + stubExtension+ ".class";
    FileOutputStream fileStream = new FileOutputStream (fileName);
    LocalStubGenerationContext igc = new LocalProxyStubGenerationContext (fileStream,
								     false,
								     genPackage,
								     className,
								     version,
								     stubExtension,
								     localNameMapper,
								     compiler,
								     localClassInfoFactory);
    AttrInfo a = getAttributeInfo (classAttrDescrpns, attrDescrpns);
    
    igc.generateClass (imports, 
		       classToExtend.getName(),
		       classesToCollect,
                       new String[] {intfName}, 
		       classInheritancePath,
                       a, 
		       methodInfoArray);
    System.out.flush ();
    mergeSpecialImpls(classesToCollect,
		      stubProxySpecialExtension,
		      igc);

    byte[] bytes = igc.writeClass();
    fileStream.close ();
    return bytes;
  }


  private final static String ARRAY_LENGTH_FOR_     = "ARRAY-LENGTH-FOR";
  private final static String INITIAL_VALUES_FOR_      = "INITIAL-VALUES-FOR";
  private final static Hashtable knownSystemAttTypes = new Hashtable();

  static {
    knownSystemAttTypes.put(ARRAY_LENGTH_, INTEGER_);
    knownSystemAttTypes.put(INITIAL_VALUES_, SEQUENCE_);
    knownSystemAttTypes.put(ARRAY_IS_PERMANENT_, TRUTH_VALUE_);
  }

  /**
   * This method will parse the ATTRIBUTE-INITIALIZATION of a class definition
   * where attributes defined in inherited classes can have their initialized values override
   */
  private AttrInfo parseDefinitionAttributeInitializations(Sequence initAttrsDescrpns) {

    if (initAttrsDescrpns == null) return null;
    int numAttrs = initAttrsDescrpns.size ();
    Symbol[] attrNames = new Symbol[numAttrs], 
             attrTypes = new Symbol[numAttrs];
    Object[] initialValues = new Object[numAttrs];
    boolean[] systemDefined = new boolean[numAttrs];
    int i = 0;
    for (Enumeration initAttrs = initAttrsDescrpns.elements (); initAttrs.hasMoreElements(); i++ ) {
      
	  Structure attr = (Structure) initAttrs.nextElement ();
	  Symbol attrName = (Symbol)attr.getAttributeValue (SYSTEM_ATTRIBUTE_DESIGNATION_, null);
	  if (attrName != null) { // A system attribute initialization
	    // G2 mangles some attribute names here, and does not send type information !
	    // so we have to be quite specfic..WARNING not all attribute init covered here

	    // deal woth mangled names for ARRAY_LENGTH_FOR... and INITIAL_VALUES_FOR...
	    if (attrName.toString().startsWith(ARRAY_LENGTH_FOR_))
	      attrName = ARRAY_LENGTH_;
	    if (attrName.toString().startsWith(INITIAL_VALUES_FOR_))
	      attrName = INITIAL_VALUES_;
	    attrTypes[i] = (Symbol)knownSystemAttTypes.get(attrName);
	    initialValues[i] = attr.getAttributeValue (INITIALIZATION_, null);
	    systemDefined[i] = true;
	  } else { // Potentially a user attribute init
	    // Disabling user attribute init, due to G2 sending type NUMBER for any
	    // numeric type, i.e. we cant ascertain the correct type
	    attrName = null;
	    //attrName = (Symbol) attr.getAttributeValue (USER_ATTRIBUTE_NAME_, null);
	    //if (attrName != null) { //a user attribute initialization
	    //Structure userAttr = (Structure)attr.getAttributeValue (INITIALIZATION_, null);
	    //if (userAttr != null) {
	    //attrTypes[i] = (Symbol)userAttr.getAttributeValue(INITIAL_TYPE_, null);
	    //initialValues[i] = userAttr.getAttributeValue(AttributeExportSymbols.INITIAL_VALUE_, null);
	    //}
	  }
	  attrNames[i] = attrName;

	  //System.out.println(attrName + " " + attrTypes[i] + " " + initialValues[i]); 
    }

    // We have not got this information
    boolean[] readable = null; 
    boolean[] writable = null;
    boolean[] staticP = null;
    Symbol[] origNames = null;
    Symbol[] definingClasses = null; 
    G2Type[] typeSpecifications = null;

    return new AttrInfo (attrTypes, 
			 attrNames, 
			 systemDefined, 
			 readable, 
			 writable, 
			 staticP, 
			 origNames, 
			 definingClasses, 
			 typeSpecifications, 
			 initialValues);
  }

  @Override
  protected String[] createJavaClassNamesFromG2ClassNames (Symbol[] classNames) {
    String[] intfNames = new String[classNames.length];
    for (int i=0; i<classNames.length; i++) {
      Symbol g2ClassSymbol = classNames[i];
      String g2ClassName = g2ClassSymbol.toString();
      // Refer to fully qualified class names, resolve to actual Java Interface names
      if (g2ClassName.indexOf('.') > -1) {
	String g2ClassNameNotQualified = g2ClassName.substring(g2ClassName.lastIndexOf(".")+1);
	String packageName = g2ClassName.substring(0, g2ClassName.lastIndexOf(".")).toLowerCase();
	intfNames[i] = packageName + "." + 
	  G2ClassTranslator.createJavaClassNameFromG2ClassName(Symbol.intern(g2ClassNameNotQualified));
      } else {
	intfNames[i] = nameMapper.javaClassNameFromG2ClassName (g2ClassSymbol);
      }
    }
    return intfNames;
  }

  byte[] getClassBytes(String className) {
    return (byte[])classByteCache.get(className);
  }

}
