
package com.gensym.jgi.download;

import java.io.*;
import java.util.Enumeration;
import java.util.Locale;
import java.util.Hashtable;
import com.gensym.util.symbol.*;
import com.gensym.types.G2Type;
import com.gensym.util.*;
import com.gensym.classtools.ClassException;

import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

public class InterfaceGenerator implements G2TypeSymbols, 
                                           AttributeTypeSpecificationSymbols,
                                           MethodExportSymbols
{

  // Tracing stuff
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.download.stubs",
			   InterfaceGenerator.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;

  private static final Resource i18n =
  Resource.getBundle("com.gensym.jgi.download.Messages");

  //Fields
  protected static final String separator = System.getProperty ("file.separator");
  private String defaultRepository;
  private Symbol[] privateClasses = {Symbol.intern ("BLOCK"), Symbol.intern ("ENTITY"),
				     Symbol.intern ("TEXT-BOX")},
                   publicClasses  = {Symbol.intern ("WORKSPACE-ITEM"), Symbol.intern ("ICONIC-ITEM"),
				     Symbol.intern ("TEXT-ITEM")};
  private String genPackage, g2ObjectClass; // harmless import hack
  protected String[] imports;
  protected ClassNameMapper nameMapper;
  private static String g2Package = "com.gensym.classes"; // System.getProperty ("com.gensym.class.g2.package");
  private static final String[] standardImports = new String[] {"com.gensym.util.Structure",
								  "com.gensym.util.Sequence",
								  "com.gensym.util.Symbol",
								  "com.gensym.util.symbol.SystemAttributeSymbols",
								  "com.gensym.jgi.*"};

  /**
   * @param genPackage the name of the package in which this InterfaceGenerator will
   * generate classes in, eg. "COM/sun/java/ding"
   * @param location the directory location for the source and
   * class files. "/home/me/java/gensources/"
   * @specificImports a String array containing package class references
   * or specific classes that override the generic imports. May be null to indicate
   * no specific imports.
   */
  protected InterfaceGenerator (final String genPackage,
		  final String location,
		  final String[] specificImports,
		  final ClassNameMapper nameMapper) {
	String packageName = genPackage;  
	String loc = location;
    if (packageName.endsWith("."))
    	packageName = packageName.substring(0, packageName.length() - 1);
    if (loc != null &&
	(loc.endsWith("\\") || loc.endsWith("/")))
    	loc = loc.substring(0, loc.length() - 1);
    defaultRepository = loc;
    this.genPackage = G2ClassTranslator.dotPackageFromSlashPackage (packageName);
    this.nameMapper = nameMapper;
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "intfGenConst", this);
    //System.out.println ("new InterfaceGenerator (" + this.genPackage + " -- " + g2Package + ")");
    if (!this.genPackage.equals (g2Package))
      g2ObjectClass =
	G2ClassTranslator.dotPackageFromSlashPackage
	(g2Package + "/Object");
    setupImports (specificImports);
  }

  private void setupImports (String[] specificImports) {
    //Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "importG2Obj", g2ObjectClass);
    //System.out.println ("setupImports -> " + specificImports + " & " + g2ObjectClass);
    int numImports, numSpecificImports;
    if (specificImports == null) {
      if (g2ObjectClass == null) {
	imports = standardImports;
	return;
      }
      numSpecificImports = 0;
    } else
      numSpecificImports = specificImports.length;
    numImports = 5 + numSpecificImports + (g2ObjectClass == null ? 0 : 1);
    
    imports = new String[numImports];

    int i=0;
    for (; i<numSpecificImports; i++)
      imports[i] = G2ClassTranslator.dotPackageFromSlashPackage (specificImports[i]);

    imports[i++] = "com.gensym.util.Structure";
    imports[i++] = "com.gensym.util.Sequence";
    imports[i++] = "com.gensym.util.Symbol";
    imports[i++] = "com.gensym.util.symbol.SystemAttributeSymbols";
    imports[i++] = "com.gensym.jgi.*";

    if (g2ObjectClass != null)
      imports[i++] = g2ObjectClass;
  }

  /**
   * Returns the fully qualified name of the interface.
   */
  String generateInterface (Symbol className_,
			    String genPackage,
			    Symbol[] superClassNames,
			    Symbol[] classInheritancePath,
			    Sequence classAttrDescrpns,
			    Sequence attrDescrpns,
			    MethodInfo[] methodInfoArray,
			    Hashtable overridesTable) throws IOException {
    //className_ = mapToPublicClassName (className_);
    String className = className_.getPrintValue ();
    String filename = ensureDirectory (genPackage) + separator +
                      G2ClassTranslator.createJavaClassNameFromG2ClassName (className_) + ".java";
    FileOutputStream fileStream = 
      new FileOutputStream (filename);
    try {
      ClassGenerationContext igc = new ClassGenerationContext (fileStream,
							       true,
							       genPackage,
							       className,
							       nameMapper);
      
      String[] superInterfaces = createJavaClassNamesFromG2ClassNames (superClassNames);
      
      AttrInfo a = getAttributeInfo (classAttrDescrpns, attrDescrpns);
      
      igc.generateClass (imports, 
			 null,
			 classInheritancePath,
			 superInterfaces, 
			 classInheritancePath,
			 a, 
			 methodInfoArray,
			 overridesTable);
      System.out.flush ();
    } finally {
      fileStream.close ();
    }

    return "com.gensym.classes." + "Item";
  }

  private Hashtable packageMap = new Hashtable (7);
  private static final char sepChar = separator.toCharArray ()[0];

  private String ensureDirectory(String repository, String packageName) {
    String directoryName = (String) packageMap.get (packageName);
    if (directoryName == null) {
      directoryName = repository + separator + packageName.replace ('.', sepChar);
      new File (directoryName).mkdirs ();
      packageMap.put (packageName, directoryName);
    }
    return directoryName;
  }
  protected String ensureDirectory (String packageName) {
    return ensureDirectory(defaultRepository, packageName);
  }
    


  /**
   * Creates an external G2 Event Object Class that extetnds java.util.EventObject not Item
   * @returns the file name generated
   */
  String generateExternalG2EventInterface (Symbol className_,
					   String genPackage,
					   Symbol[] superClassNames,
					   Symbol[] classInheritancePath,
					   Sequence classAttrDescrpns,
					   Sequence attrDescrpns,
					   MethodInfo[] methodInfoArray,
					   Hashtable overridesTable) throws IOException {

    String className = className_.getPrintValue ();
    String[] superInterfaces = createJavaClassNamesFromG2ClassNames (superClassNames);
    AttrInfo a = getAttributeInfo (classAttrDescrpns, attrDescrpns);			     

      String externalClassName = 
	StubClassLoader.getExternalG2EventClassName(
			G2ClassTranslator.createJavaClassNameFromG2ClassName (className_));
      String externalG2ClassName =                                           
	                StubClassLoader.getExternalG2EventClassName("-" + className_.toString());
                        // we added a "-" here to ensure that the first letter of the className is
                        // uppercased by createJavaClassNameFromG2ClassName in ClassGenerationContext


      String evfilename = ensureDirectory (genPackage) + 
	                  separator + 
	                  externalClassName + 
	                  ".java";

      FileOutputStream evfileStream = 
	new FileOutputStream (evfilename );
      EventClassGenerationContext evoigc = new EventClassGenerationContext (evfileStream,
									    genPackage,
									    externalG2ClassName,
									    className,
									    nameMapper);
      evoigc.generateClass (imports, 
			    StubClassLoader.externalG2EventClassName, 
			    new String[0], //superinterfaces
			    classInheritancePath,
			    a,
			    methodInfoArray, 
			    overridesTable);
      System.out.flush ();
      evfileStream.close ();

    return evfilename;
  }


  String generateExternalG2ListenerInterface (Symbol className_,
					      String genPackage,
					      Symbol[] superClassNames,
					      Symbol[] classInheritancePath,
					      Sequence classAttrDescrpns,
					      Sequence attrDescrpns,
					      MethodInfo[] methodInfoArray,
					      Hashtable overridesTable) throws IOException {


    String className = className_.getPrintValue ();
    String[] superInterfaces = createJavaClassNamesFromG2ClassNames (superClassNames);
    AttrInfo a = getAttributeInfo (classAttrDescrpns, attrDescrpns);

    String externalClassName = 
      StubClassLoader.getExternalG2ListenerClassName(
		   G2ClassTranslator.createJavaClassNameFromG2ClassName (className_));
    String externalG2ClassName =                                           
      StubClassLoader.getExternalG2ListenerClassName("-" + className_.toString());
    // we added a "-" here to ensure that the first letter of the className is
    // uppercased by createJavaClassNameFromG2ClassName in ClassGenerationContext


    String evfilename = ensureDirectory (genPackage) + 
	                  separator + 
	                  externalClassName + 
	                  ".java";

      FileOutputStream evfileStream = 
	new FileOutputStream (evfilename );
      ClassGenerationContext evigc = new ClassGenerationContext (evfileStream,
								 true,
								 genPackage,
								 externalG2ClassName,
								 nameMapper);
      evigc.generateG2EventListenerExternalInterface (imports, 
						      null, 
						      new String[] {"java.util.EventListener"}, //superinterfaces
						      classInheritancePath,
						      methodInfoArray, 
						      overridesTable);
      System.out.flush ();
      evfileStream.close ();

    return evfilename;
  }


  private Symbol mapToPublicClassName (Symbol privateClassName_) {
    for (int i=0; i<privateClasses.length; i++)
      if (privateClassName_.equals (privateClasses[i]))
	return publicClasses[i];
    return privateClassName_;
  }

  String generateStub (Symbol className_,
		       Class classToExtend,
		       Symbol[] classesToCollect,
		       String genPackage,
		       Symbol[] classInheritancePath,
		       Sequence classAttrDescrpns,
		       Sequence attrDescrpns,
		       MethodInfo[] methodInfoArray,
		       Hashtable overridesTable) throws IOException {
    //className_ = mapToPublicClassName (className_);
    String className = className_.getPrintValue ();
    String intfName = G2ClassTranslator.createJavaClassNameFromG2ClassName (className_);
    String fileName = ensureDirectory (genPackage) + separator + intfName + "Impl.java";
    FileOutputStream fileStream = new FileOutputStream (fileName);
    try {
    StubGenerationContext igc = new StubGenerationContext (fileStream,
							   false,
							   genPackage,
							   className,
							   nameMapper);
    AttrInfo a = getAttributeInfo (classAttrDescrpns, attrDescrpns);

    igc.generateClass (imports, classToExtend.getName(),
		       classesToCollect,
                       new String[] {intfName}, classInheritancePath,
                       a, methodInfoArray, overridesTable);
    System.out.flush ();
    fileStream.close ();
    //System.out.println ("Closing " + defaultRepository + separator +  intfName + "Impl.java");
    } finally {
      //System.out.println ("Done with stub generation for " + className_);
    }

    return "com.gensym.classes." + "ItemImpl";
  }

  byte[] generatePseudoStub(String className,
			    String genPackage,
			    Class classToExtend,
			    Class[] classesToDelegate)
  throws ClassFileGenerationException {
    String qualifiedName = genPackage + className;
    PseudoClassGenerator generator =
      new PseudoClassGenerator(qualifiedName, classToExtend, classesToDelegate);
    try {
      byte[] classBytes = generator.getClassBytes();
      writeClassBytesIfDesired(classBytes, genPackage, className, qualifiedName);
      return classBytes;
    } catch (ClassException ce) {
      throw new ClassFileGenerationException(ce, i18n.format("igUnableToGenerateClassDescription", qualifiedName));
    }
  }

  private void writeClassBytesIfDesired(byte[] classBytes, String genPackage,
					String className, String qualifiedName)
  throws ClassFileGenerationException {
    String repository = StubClassLoader.getUserRepository();
    if (repository == null)
      return;
    FileOutputStream fileStream = null;
    String fileName = null;
    try {
      fileName = ensureDirectory (repository, genPackage) + File.separator + className + ".class";
      fileStream = new FileOutputStream (fileName);
      fileStream.write(classBytes);
    } catch (IOException ioe) {
      throw new ClassFileGenerationException(ioe, i18n.format("igUnableToWriteClassToFile", qualifiedName, fileName));
    } catch (SecurityException se) {
      
    } finally {
      try {
	if (fileStream != null)
	  fileStream.close();
      } catch (IOException ioe2) {
	Trace.exception(ioe2);
      }
    }
  }
    
  private static final Symbol ORIGINAL_ATTRIBUTE_NAME_ = Symbol.intern ("ORIGINAL-ATTRIBUTE-NAME");
  protected AttrInfo getAttributeInfo (Sequence classAttrDescrpns, Sequence attrDescrpns) {

    try {
      int numInstAttrs = attrDescrpns.size ();
      int numClassAttrs = classAttrDescrpns.size ();
      int numAttrs = numInstAttrs + numClassAttrs, i=0;
      boolean moreElements = true, staticAttr = false;
      Symbol[] attrNames = new Symbol[numAttrs], attrTypes = new Symbol[numAttrs],
	       origNames = new Symbol[numAttrs], definingClasses = new Symbol[numAttrs];
      boolean[] systemDefined = new boolean[numAttrs],
	        readable = new boolean[numAttrs], writable = new boolean[numAttrs],
	        staticP = new boolean[numAttrs];
      G2Type[] typeDescriptions = new G2Type[numAttrs];
      Object[] initialValues = new Object[numAttrs];
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "attrInfo", attrDescrpns.size (), classAttrDescrpns.size ());
      if (numAttrs > 0) {
	for (Enumeration instAttrs = attrDescrpns.elements (),
	       clAttrs = classAttrDescrpns.elements (),
	       attrs = instAttrs;
	     moreElements;
	     i++) {
	  if (!attrs.hasMoreElements ()) {
	    if (staticAttr)
	      moreElements = false;
	    else {
	      staticAttr = true;
	      attrs = clAttrs;
	      moreElements = (numClassAttrs > 0);
	    }
	    if (!moreElements)
	      break;
	  }
	  Structure attr = (Structure) attrs.nextElement ();
	  Symbol attrName = (Symbol) attr.getAttributeValue (ATTRIBUTE_NAME_);
	  Symbol origName = (Symbol) attr.getAttributeValue (ORIGINAL_ATTRIBUTE_NAME_, attrName);
	  Symbol definingClass = (Symbol) attr.getAttributeValue (DEFINING_CLASS_);
	  Object initialValue = attr.getAttributeValue(INITIAL_VALUE_, null);
	  Object td = attr.getAttributeValue (TYPE_, null);
	  //System.out.println ("G2 TYPE STRUCTURE FROM DESCRIPTION FOR " + attrName + " = " + td);
	  //Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "typeSpec", attrName, td);
	  Structure typeDescpn = maybeUndoPaulsBrokenTypeSpecification (td);
	  //Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "typeSpecFixed", typeDescpn);
	  boolean valueReadable = ((Boolean) attr.getAttributeValue (VALUE_READABLE_)).booleanValue ();
	  boolean valueWritable = ((Boolean) attr.getAttributeValue (VALUE_WRITABLE_)).booleanValue ();
	  boolean isSystemDefined = ((Boolean) attr.getAttributeValue (IS_SYSTEM_DEFINED_)).booleanValue ();
	  if (typeDescpn == null)
	    attrTypes[i] = ITEM_OR_VALUE_;
	  else
	    attrTypes[i] = TypeHandler.getTypeFromTypeDescription (typeDescpn);
	  attrNames[i] = attrName;
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "makingAttrInfo",
		      (staticAttr ? "static" : "instance"), attrTypes[i], attrName);
	  valueReadable |= staticAttr; // All static attributes are value readable - vkp 10/15/97
	  systemDefined[i]   = isSystemDefined;
	  readable[i]        = valueReadable;
	  writable[i]        = valueWritable;
	  staticP[i]         = staticAttr;
	  origNames[i]       = origName;
	  definingClasses[i] = definingClass;
	  initialValues[i]   = initialValue;
	  //System.out.println ("G2 TYPE STRUCTURE = " + typeDescpn);
	  if (typeDescpn != null)
	    typeDescriptions[i]= G2Type.makeG2TypeFromDescription (typeDescpn);
	}
      }
      return new AttrInfo (attrTypes, attrNames, systemDefined, readable, 
			   writable, staticP, origNames, definingClasses, 
			   typeDescriptions, initialValues);
    } catch (NoSuchAttributeException nsae) {
      System.err.println (nsae);
      Thread.dumpStack ();
      System.exit (1);
    }
    return null;
  }
					     
    

  private static final Symbol POSITIVE_INTEGER_ = Symbol.intern ("POSITIVE-INTEGER");

  private Structure maybeUndoPaulsBrokenTypeSpecification (Object td) {
    if (td == null)
      return null;
    if (td instanceof Structure)
      return (Structure)td;
    if (td instanceof Symbol) {
      Symbol type;
      if (td.equals (POSITIVE_INTEGER_))
	type = INTEGER_;
      else if (td.equals (SYMBOL_))
	type = SYMBOL_;
      else
	type = ITEM_OR_VALUE_;
      Structure s = new Structure ();
      s.setAttributeValue (TYPE_OR_OPERATOR_, type);
      return s;
    } else
      throw new RuntimeException ("Unknown Type Specification : " + td);
  }

  protected String[] createJavaClassNamesFromG2ClassNames (Symbol[] classNames) {
    String[] intfNames = new String[classNames.length];
    for (int i=0; i<classNames.length; i++) {
      Symbol className_ = classNames[i];
      intfNames[i] = nameMapper.javaClassNameFromG2ClassName (className_);
    }
    return intfNames;
  }
}
