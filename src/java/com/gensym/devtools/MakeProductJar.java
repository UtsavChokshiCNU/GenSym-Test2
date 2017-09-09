package com.gensym.devtools;

import java.io.File;
import java.io.IOException;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;

import com.gensym.core.CmdLineArgHandler;
import com.gensym.jartools.JarFile;
import com.gensym.jartools.ManifestSection;

public class MakeProductJar {

  public static final String IN_JAR = "IN_JAR";
  public static final String IN_REPOSITORY = "IN_REPOSITORY";

  private static final Hashtable fileTypesToInclude = new Hashtable(23);

  static {
    fileTypesToInclude.put(".cls", IN_JAR); // encrypted classfiles
    fileTypesToInclude.put(".class", IN_JAR);
    fileTypesToInclude.put(".java", IN_REPOSITORY);
    fileTypesToInclude.put(".ser", IN_JAR);
    fileTypesToInclude.put(".ovr", IN_JAR);
    fileTypesToInclude.put(".gif", IN_JAR);
    fileTypesToInclude.put(".jpg", IN_JAR);
    fileTypesToInclude.put(".htm", IN_REPOSITORY);
    fileTypesToInclude.put(".html", IN_REPOSITORY);
    fileTypesToInclude.put(".class", IN_JAR);
    fileTypesToInclude.put(".properties", IN_JAR);
    fileTypesToInclude.put(".kbs", IN_REPOSITORY);
    fileTypesToInclude.put(".txt", IN_JAR);
    fileTypesToInclude.put(".bat", IN_REPOSITORY);
    fileTypesToInclude.put(".sh", IN_REPOSITORY);
    fileTypesToInclude.put(".lisp", IN_JAR);
    fileTypesToInclude.put(".dat", IN_JAR);
  }

  String productName;
  String[] productNames;
  Vector moduleInfos;
  String sourceJavaDir;
  String targetFilePath;
  File jarFile;

  public MakeProductJar(String productName,
			String targetFilePath,
			String sourceJavaDir)
  throws IOException {
    this.productName = productName;
    this.sourceJavaDir = sourceJavaDir;
    this.targetFilePath = targetFilePath;
  }

  public MakeProductJar(String[] productNames,
			String targetFilePath,
			String sourceJavaDir)
       throws IOException {
    this(productNames[0],
	 targetFilePath,
	 sourceJavaDir);
    this.productNames = productNames;
  }

  private String getTypeString(String fileName) {
    int prefixPos = fileName.lastIndexOf(".");
    return prefixPos > -1 ? fileName.substring(prefixPos) : "";
  }

  private boolean includeInJarByType(String fileName) {
    return IN_JAR.equals(fileTypesToInclude.get(getTypeString(fileName)));
  }

  private void collectModuleInfos(boolean strict) {
    ModuleInfoTool infoTool =
      new ModuleInfoTool(sourceJavaDir, null, strict);
    if (productNames == null) 
      moduleInfos = infoTool.getModuleInfos(productName);
    else {
      moduleInfos = new Vector();
      for (int i = 0; i<productNames.length; i++) {
	Vector mInfos = infoTool.getModuleInfos(productNames[i]);
	//System.out.println(productNames[i]);
	moduleInfos.addAll(mInfos);
      }
    }
  }

  private void outputJar() {
    try {
      JarFile jf = new JarFile();
      for (Enumeration e = moduleInfos.elements(); e.hasMoreElements();) {
	ModuleInfo moduleInfo = (ModuleInfo)e.nextElement();
	if (!moduleInfo.dontJarPackage) {
	  jarDir(jf, moduleInfo);// moduleInfo.directoryFile, relativePath, moduleInfo.jarAsBeansList);
	}
      }
      // make a call to save the contents of the jar file

      System.out.println("saving=" + targetFilePath);
      
      jf.saveAs(targetFilePath);
    } catch (Exception e) {
      e.printStackTrace();
      System.out.println(e.toString());}
  }

  boolean jarDir(JarFile jf, ModuleInfo moduleInfo) {
    File dir = moduleInfo.getSourceDirectory();
    Vector beanFiles = moduleInfo.jarAsBeansList;
    // could make a good FileFilter for this
    File dirList[] = dir.listFiles();
    if (dirList == null) {
      System.out.println("null dir");
      return false;
    }
    for (int i=0; i<dirList.length; i++) {
      File file = dirList[i];
      String sourceFilename = file.getAbsolutePath();
      String filename = file.getName();
      if (!file.isDirectory()) {
	try {
	  String relativePath = moduleInfo.getRelativePath();
	  //System.out.println ("Relative path = " + relativePath);
	  String manifestEntryName = relativePath +"/" + filename;
	  if(!"/".equals(File.separator))
	    manifestEntryName = manifestEntryName.replace(File.separatorChar,
							  '/');
	  Vector manifestData = moduleInfo.getManifestData(filename);
	  if (manifestData != null ||
	      BuildProductRepository.wildcardCompare(beanFiles, sourceFilename)) {
	    jf.putFile(sourceFilename, manifestEntryName, true);
	    if (manifestData != null) {
	      ManifestSection ms = jf.getManifestSection(manifestEntryName);
	      for (Enumeration en = manifestData.elements();
		   en.hasMoreElements();) {
		Pair pair = (Pair)en.nextElement();
		ms.add(pair.name, pair.value);
	      }
	    }
	  }
	  else if (includeInJarByType(filename)) {
	    //System.out.println ("Putting " + sourceFilename + " as " + manifestEntryName);
	    jf.putFile(sourceFilename, manifestEntryName);
	  }
	} catch (java.io.IOException e) {
	  e.printStackTrace();
	  System.out.println("Cant put " + filename + "in jar because of " + e.toString());}
      }
    }

    return true;
  }

  public static void main(String[] args) {
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);
    String productName = cmdLine.getOptionValue("-productName");
    String[] productNames = cmdLine.getOptionValues("-productNames");
    String targetFilePath = cmdLine.getOptionValue("-targetFile");
    String sourceJavaDir = cmdLine.getOptionValue("-javaSource");
    boolean strict = cmdLine.getSwitchValue("-strict");

    try {

      MakeProductJar jarMaker = null;

      if (productName != null) {
	jarMaker = new MakeProductJar(productName,
				      targetFilePath,
				      sourceJavaDir);
      } else {
	jarMaker = new MakeProductJar(productNames,
				      targetFilePath,
				      sourceJavaDir);
      }

      jarMaker.collectModuleInfos(strict);
      jarMaker.outputJar();
    } catch (IOException ioe) {
      ioe.printStackTrace();
    }
  }

  @Override
  public String toString() {
    return super.toString() + ":source=" + sourceJavaDir +
      ";target=" + targetFilePath + ";product=" + productName + "]";
  }
}
