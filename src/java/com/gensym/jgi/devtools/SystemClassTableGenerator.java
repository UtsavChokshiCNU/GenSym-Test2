
package com.gensym.jgi.devtools;

import java.lang.reflect.Field;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.FilenameFilter;
import java.util.Hashtable;
import com.gensym.core.GensymApplication;
import com.gensym.message.Trace;
import com.gensym.util.Symbol;

public class SystemClassTableGenerator {

  private static final String fileSep = File.separator;
  private Hashtable classNamesTable, attributeNamesTable;
  private PrintWriter output;

  public static void main (String[] args) throws Exception {
    GensymApplication.initialize (args);
    SystemClassTableGenerator generator = new SystemClassTableGenerator ();
    generator.run ();
  }

  private void run () throws IOException {
    initializeClassNames ();
    initializeAttributeNames ();
    openStream ();
    writePreamble ();
    openTable ();
    writeTable ();
    closeTable ();
    writeAccessors ();
    closeStream ();
  }

  private void initializeClassNames () {
    classNamesTable = new Hashtable (239);
    fillTableWithFieldMapping ("com.gensym.util.symbol.G2ClassSymbols", classNamesTable);
  }

  private void initializeAttributeNames () {
    attributeNamesTable = new Hashtable (731);
    fillTableWithFieldMapping ("com.gensym.util.symbol.VirtualAttributeSymbols", attributeNamesTable);
    fillTableWithFieldMapping ("com.gensym.util.symbol.SystemAttributeSymbols", attributeNamesTable);
  }

  private void fillTableWithFieldMapping (String className,
					  Hashtable table) {
    try {
      Class classSymbolsClass = Class.forName (className);
      Field[] symbolFields = classSymbolsClass.getFields ();
      for (int i=0; i<symbolFields.length; i++) {
	//System.out.println (symbolFields[i].getName () + " = " + symbolFields[i].get (null));
	String fieldName = symbolFields[i].getName ();
	Symbol fieldValue = (Symbol) symbolFields[i].get (null);
	String symbolString = fieldValue.getPrintValue ();
	table.put (symbolString, fieldName);
	//System.out.println (symbolString + " = " + fieldName);
      }
      return;
    } catch (ClassNotFoundException cnfe) {
      Trace.exception (cnfe);
    } catch (IllegalAccessException iae) {
      Trace.exception (iae);
    }
    throw new Error ("Unexpected error : class not found or inaccessible. Run -development");
  }

  

  private void openStream () throws IOException {
    String dirName = System.getProperty ("com.gensym.class.g2.repository");
    dirName += fileSep + "com" + fileSep + "gensym" + fileSep + "classes";
    String fileName = dirName + fileSep + "G2__ClassTable.java";
    File javaFile = new File (fileName);
    FileOutputStream fiStream = new FileOutputStream (javaFile);
    output = new PrintWriter (fiStream, true);
  }

  private void writePreamble () {
    iprintln ("package com.gensym.classes;");
    println ();

    iprintln ("import java.util.Hashtable;");
    iprintln ("import com.gensym.util.Symbol;");
    iprintln ("import com.gensym.util.symbol.G2ClassSymbols;");
    iprintln ("import com.gensym.util.symbol.SystemAttributeSymbols;");
    println ();
    iprintln ("class G2__ClassTable implements G2ClassSymbols, SystemAttributeSymbols {");
    println ();
    increaseIndent (2);
    iprintln ("static Hashtable classTable = new Hashtable (239);");
    iprintln ("static Hashtable attributesTable = new Hashtable (17);");
    println ();
  }

  private void openTable () {
    println ();
    iprintln ("static {");
    increaseIndent (2);
  }

  private void closeTable () {
    decreaseIndent (2);
    iprintln ("}");
  }

  private void writeAccessors () {
    println ();
    iprintln ("static boolean isSystemClass (Symbol className_) {");
    increaseIndent (2);
    iprintln ("return classTable.get (className_) != null;");
    decreaseIndent (2);
    iprintln ("}");
    println ();
    iprintln ("static Symbol[] getClassInheritancePath (Symbol className_) {");
    increaseIndent (2);
    iprintln ("return (Symbol[])classTable.get (className_);");
    decreaseIndent (2);
    iprintln ("}");
    println ();
    iprintln ("static Symbol[] getStaticAttributes (Symbol className_) {");
    increaseIndent (2);
    iprintln ("if (attributesTable.get (className_) == null)");
    iprintln ("  return new Symbol[0];");
    iprintln ("return (Symbol[])attributesTable.get (className_);");
    decreaseIndent (2);
    iprintln ("}");
    println ();
  }

  private void writeTable () throws IOException {
    String dirName = System.getProperty ("com.gensym.class.g2.repository");
    dirName += fileSep + "com" + fileSep + "gensym" + fileSep + "classes";
    File directory = new File (dirName);
    String[] javaFiles = collectJavaFiles (directory);
    //System.out.println ("Found : " + com.gensym.core.DebugUtil.printArray (javaFiles));
    Class rootClass = com.gensym.classes.Root.class;
    for (int i=0; i<javaFiles.length; i++) {
      String javaClassName = javaFiles[i].substring (0, javaFiles[i].indexOf ('.'));
      try {
	Class javaClass = Class.forName ("com.gensym.classes." + javaClassName);
	if (javaClass.isInterface () &&
	    rootClass.isAssignableFrom (javaClass)) {
	  //System.out.println ("Java Class#" + i + " = " + javaClassName);
	  java.lang.Object[] classAttributes = getAttributes (javaClass);
	  writeTableEntry (classAttributes);
	}
      } catch (ClassNotFoundException cnfe) {
	  Trace.exception (cnfe);
	  continue; // don't care?
      }
    }
  }

  private Object[] getAttributes (Class clazz) {
    try {
      Field classInhPathField = clazz.getField ("classInheritancePath");
      Object classInheritancePath = classInhPathField.get (null);
      Field staticAttributesField = clazz.getField ("staticAttributes");
      Object staticAttributes = staticAttributesField.get (null);
      return new Object[] {classInheritancePath, staticAttributes};
    } catch (NoSuchFieldException nsfe) {
      Trace.exception (nsfe);
    } catch (IllegalAccessException iae) {
      Trace.exception (iae);
    }
    throw new Error ("Field not found in class. Run -development");
  }
  
  private void writeTableEntry (Object[] attributes) {
    Object[] classInheritancePath = (Object[])attributes[0];
    Object[] staticAttributes = (Object[])attributes[1];
    Symbol className_ = (Symbol)classInheritancePath[0];
    iprint ("classTable.put (");
    print (getClassNameVariable (className_));
    println (",");
    increaseIndent (16);
    iprint ("new Symbol[] {");
    increaseIndent (14);
    for (int i=0; i<classInheritancePath.length; i++) {
      Symbol inhPathClassName_ = (Symbol) classInheritancePath[i];
      if (i == 0)
	print (getClassNameVariable (inhPathClassName_));
      else {
	println (", ");
	iprint (getClassNameVariable (inhPathClassName_));
      }
    }
    println ("});");
    decreaseIndent (16 + 14);

    if (staticAttributes.length != 0) {
      System.out.println (className_ + " defines " + staticAttributes.length + " static variables");
      iprint ("attributesTable.put (");
      print (getClassNameVariable (className_));
      println (", ");
      increaseIndent (16);
      iprint ("new Symbol[] {");
      increaseIndent (14);
      for (int i=0; i<staticAttributes.length; i++) {
	Symbol attributeName_ = (Symbol) staticAttributes[i];
	if (i == 0) 
	  print (getAttributeNameVariable (attributeName_));
	else {
	  println (", ");
	  iprint (getAttributeNameVariable (attributeName_));
	}	  
      }
      println ("});");
      decreaseIndent (16 + 14);
    }
  }

  private String getClassNameVariable (Symbol classSymbol_) {
    String className = classSymbol_.getPrintValue ();
    String varName = (String) classNamesTable.get (className);
    if (attributeNamesTable.get (className) != null)
      return "G2ClassSymbols." + varName;
    else
      return varName;
  }

  private String getAttributeNameVariable (Symbol attributeSymbol_) {
    String attributeName = attributeSymbol_.getPrintValue ();
    if (classNamesTable.get (attributeName) != null) // also names a class!
      return "G2ClassSymbols." + classNamesTable.get (attributeName);
    return (String) attributeNamesTable.get (attributeName);
  }

  private String[] collectJavaFiles (File dir) {
    String[] fileList = dir.list (new FilenameFilter () {
      @Override
      public boolean accept (File dir, String fileName) {
	return fileName.endsWith (".java");
      }
    });
    return fileList;
  }

  private void closeStream () {
    decreaseIndent (2);
    iprintln ("}");
  }

  private int indent = 0;
  private String indentString = "";
  private String SPACES = "                                                                    ";

  protected synchronized void increaseIndent (int delta) {
    indent += delta;
    indentString = SPACES.substring (0, indent);
  }

  protected synchronized void decreaseIndent (int delta) {
    indent -= delta;
    if (indent < 0)
      indent = 0;
    indentString = SPACES.substring (0, indent);
  }

  void print (String x) {
    output.print (x);
  }

  void println (String x) {
    output.println (x);
  }

  void println () {
    output.println ();
  }

  void iprint (String x) {
    output.print (indentString);
    output.print (x);
  }

  void iprintln (String x) {
    iprint (x);
    output.println ();
  }


}
