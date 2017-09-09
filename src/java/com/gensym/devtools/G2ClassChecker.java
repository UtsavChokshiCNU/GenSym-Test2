package com.gensym.devtools;

import java.util.Hashtable;
import java.util.Enumeration;
import java.util.Vector;
import java.io.IOException;
import java.io.File;
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.G2ClassTranslator;
import com.gensym.message.Trace;

public class G2ClassChecker {

  private G2Access context;
  public G2ClassChecker(G2Access context) {
    this.context = context;
  }
  public static final Symbol G2_DUMP_TW2_CLASS_HIERARCHY_ = Symbol.intern ("G2-DUMP-TW2-CLASS-HIERARCHY");
  public static final Symbol ITEM_ = Symbol.intern ("ITEM");
  public static final Symbol G2_GET_CLASS_INFO_ = Symbol.intern ("G2-GET-CLASS-INFO");
  public static final Symbol CLASS_NAME_ = Symbol.intern ("CLASS-NAME");
  public static final Symbol SUBCLASS_STRUCTURES_ = Symbol.intern ("SUBCLASS-STRUCTURES");
  private Hashtable infoHash = new Hashtable(211);
  private Hashtable classHash = new Hashtable(211);

  private Structure retrieveHierarchy(Symbol className) throws G2AccessException {
    return (Structure)context.callRPC(G2_DUMP_TW2_CLASS_HIERARCHY_,
					     new Object[] {className});
  }

  private static Structure findSavedInfo(Symbol g2Name) throws IOException,
  ClassNotFoundException{
    File infoDir = findInfoDir();
    String fileName = infoName2FileName(g2Name);
    File infoFile = new File(infoDir, fileName);

    if (infoFile.exists()) {
      return (Structure)readObjectFromFile(infoFile);
    } else {
      return null;
    }
  }

  private static Object readObjectFromFile(File file) throws IOException,
  ClassNotFoundException {
    InputStream is = null; 
    ObjectInputStream ois = null;
    Object object = null;
    try {
      is = new FileInputStream(file);
      ois = new ObjectInputStream(is);
      object = ois.readObject();
    } finally {
      if (is != null)
	is.close();
      if (ois != null)
	ois.close();
    }

    return object;
  }

  private Vector findChangedInfos() throws NoSuchAttributeException {
    Vector changedInfos = new Vector();
    for (Enumeration en = infoHash.elements(); en.hasMoreElements();) {
      try {
	Structure struct = (Structure)en.nextElement();
	Symbol g2Name = (Symbol)struct.getAttributeValue(CLASS_NAME_);
	Structure savedInfo = findSavedInfo(g2Name);
	if (!struct.equals(savedInfo))
	  changedInfos.addElement(struct);
      } catch (Exception ioe) {
	Trace.exception(ioe);
      }
    }
    return changedInfos;
  }
      

  private static String infoName2FileName(Symbol infoName) {
    String javaName = G2ClassTranslator.createJavaClassNameFromG2ClassName(infoName);
    return javaName + ".ser";
  }

  private Vector newClasses = new Vector();

  private void fillInClassInfo(Structure node) {
    try {
      Symbol className = (Symbol)node.getAttributeValue(CLASS_NAME_);
      Object info = infoHash.get(className);
      if (info == null) {
	info = (Structure)context.callRPC(G2_GET_CLASS_INFO_,
					  new Object[] {className, Boolean.FALSE});
	infoHash.put(className, info);
	Sequence subclasses =
	  (Sequence)node.getAttributeValue(SUBCLASS_STRUCTURES_, null);
	if (subclasses != null) {
	  for (Enumeration en = subclasses.elements(); en.hasMoreElements();) {
	    Structure subclassNode = (Structure)en.nextElement();
	    fillInClassInfo(subclassNode);
	  }
	}
      }
    } catch (G2AccessException g2ae) {
      newClasses.addElement(node);
    } catch (Exception ex) {
      ex.printStackTrace();
    }
  }

  private void printNewClasses() {
    if (newClasses.isEmpty()) {
      System.out.println("NO NEW CLASSES FOUND");
    } else {
      System.out.println("**** NEW CLASSES ****");
      for (Enumeration en = newClasses.elements(); en.hasMoreElements();) {
	Structure node = (Structure)en.nextElement();
	System.out.println(node.getAttributeValue(CLASS_NAME_, null));
      }
    }
  }

  private static File findInfoDir() throws IOException {
    String root = System.getProperty("com.gensym.class.g2.repository");
    String dirName = root + File.separator + "com" + File.separator +
      "gensym" + File.separator + "classes";
    return new File(dirName);
  }

  private static void printChangedClasses(Vector changedInfos) {
    if (changedInfos.isEmpty()) {
      System.out.println("NO CLASS CHANGES FOUND");
    } else {
      System.out.println("**** CHANGED CLASSES ****");
      for (Enumeration en = changedInfos.elements(); en.hasMoreElements();) {
	Structure info = (Structure)en.nextElement();
	System.out.println(info.getAttributeValue(CLASS_NAME_, null));
      }
      System.out.println("      ****     "); 
    }
  }

  public static void main(String[] args) {
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);
    // information for connecting to G2
    String url   = cmdLine.getOptionValue ("-url");
    String host  = cmdLine.getOptionValue ("-host");
    host = (host == null ? "localhost" : host);
    String port  = cmdLine.getOptionValue ("-port");
    port = (port == null ? "1111" : port);
    // information to find a unique named item in G2
    String classString = cmdLine.getOptionValue ("-class");
    // convert the strings to symbols
    Symbol clazz = (classString == null ? ITEM_ : 
		    Symbol.intern(classString.toUpperCase()));
    try {
      System.out.println("Connecting to: url=" + url + ";host=" + host +
			";port=" + port);
      G2Access context = G2Gateway.getOrMakeConnection(url, host, port);
      System.out.println("Connected");
      G2ClassChecker checker = new G2ClassChecker(context);

      System.out.println("Getting class hierarchy");
      Object dump = checker.retrieveHierarchy(clazz);

      System.out.println("Getting class infos");
      checker.fillInClassInfo((Structure)dump);

      System.out.println("Comparing class versions");
      Vector changedInfos = checker.findChangedInfos();
      printChangedClasses(changedInfos);
      checker.printNewClasses();

    } catch (Exception e) {
      e.printStackTrace();
    }

    System.exit(0);
  }
}
    
    
