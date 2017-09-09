package com.gensym.core;

import java.util.Vector;
import java.io.BufferedReader;
import java.io.Closeable;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.Writer;
import java.nio.charset.Charset;


public class GenerateDocs {
  private int prefix, javaPrefix, swingPrefix;
  private Vector packageNames = new Vector ();
  private String productName;
  private String targetDir;
  private String sourceDir;
  private String javaSrcsDir;
  private String swingSrcsDir;
  private Vector requiredProducts = new Vector();
  private static String MODULE_INFO_FILE_NAME = "package.info";
  private static String INCLUDE_IN_MODULE_TAG = "include-in-module:";
  private static String PACKAGE_IS_PRIVATE_TAG = "package-is-private";
  private static final String PACKAGE_SHIPS_SOURCE_TAG = "dont-delete-java";

  public static void main(String args[]) {
    String fileName;
    String dirName;
    
    GenerateDocs docsGen = new GenerateDocs(args[0], args[1], args[2], args[3], args[4]);
    docsGen.readProductInfo();
    //docsGen.getJavaSrcFiles(args[4]+File.separator+"java");
    docsGen.createProductsArray();
  }
  
  public void readProductInfo() {
    System.out.println("product is: " + productName);
    Product prod = ProductManager.getProduct(productName);
    ProductInfo[] pinfo = prod.getRequiredProducts();
    for (int i=0; i<pinfo.length; i++) {
      requiredProducts.addElement(pinfo[i].getName());
    }
  }
  
  public GenerateDocs(String productName, String targetDir, String sourceDir, 
                      String javaSrcsDir, String swingSrcsDir) {
    this.productName = productName;
    this.sourceDir = sourceDir;
    this.targetDir = targetDir;
    this.javaSrcsDir = javaSrcsDir;
    this.swingSrcsDir = swingSrcsDir;
    this.prefix = sourceDir.length();
    this.javaPrefix = javaSrcsDir.length();
    this.swingPrefix = swingSrcsDir.length();
    this.getSrcFiles(this.swingSrcsDir+File.separator+"com", this.swingPrefix);
    this.getSrcFiles(this.javaSrcsDir+File.separator+"java", this.javaPrefix);
  }
  
  public void getJavaSrcFiles(String javaSrcDirName){
    File javaSrcs = new File (javaSrcDirName);
    String dirList[] = javaSrcs.list();
    String fname;
    
    if (dirList == null) {
      System.out.println("No Dirs for Java Sources");
    }
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = javaSrcs.getAbsolutePath()+File.separator+filename;      
      File sourceFile = new File(targetFilename);
      
      if (sourceFile.isDirectory()){
        fname = targetFilename.substring(this.javaPrefix+1);
        fname = fname.replace(File.separatorChar, '.');        
        packageNames.addElement(fname);
        getJavaSrcFiles(targetFilename);
      }
    }    
  }
  
  public void getSrcFiles(String dirName, int dirPrefix){
    System.out.println("dir is: " + dirName);
    File javaSrcs = new File (dirName);
    String dirList[] = javaSrcs.list();
    String fname;
    
    if (dirList == null) {
      System.out.println("No Dirs for Java/Swing Sources");
    }
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = javaSrcs.getAbsolutePath()+File.separator+filename;      
      File sourceFile = new File(targetFilename);
      
      if (sourceFile.isDirectory()){
        fname = targetFilename.substring(dirPrefix+1);
        fname = fname.replace(File.separatorChar, '.');        
        packageNames.addElement(fname);
        getSrcFiles(targetFilename, dirPrefix);
      }
    }    
  }

  public void createProductsArray() {    
    Vector packages = new Vector();
    String genDir = sourceDir + File.separator + "com" + File.separator + "gensym";
    System.out.println("dir is: " + genDir);
    getDirs(genDir);
    if (! packageNames.isEmpty()) {
      packageNames.insertElementAt("-d", 0);
      packageNames.insertElementAt(targetDir, 1);
      packageNames.insertElementAt("-sourcepath", 2);
    //  packageNames.insertElementAt(sourceDir+File.pathSeparator+javaSrcsDir, 3);
      packageNames.insertElementAt(javaSrcsDir+ File.pathSeparator+swingSrcsDir+ File.pathSeparator+sourceDir,3);

      String[] packagesArray = new String[packageNames.size()];
      packageNames.copyInto(packagesArray);

      try {
        System.out.println("*** Generating Javadoc ***");
        System.out.println("Products: " + this.productName + " " + this.requiredProducts);
        System.out.println("javadoc " + packageNames);
        com.sun.tools.javadoc.Main.main(packagesArray);
      } catch (SecurityException e) { System.out.println("tried to exit"); }
    }
    else
      System.out.println("There are no non-private packages belonging to " + productName);
  }
  
  private void getDirs(String targetDirName) {
    File targetDirectory = new File (targetDirName);
    String dirList[] = targetDirectory.list();
    String fname;
    
    if (dirList == null) {
      System.out.println("No Dirs Found");
    }
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = targetDirectory.getAbsolutePath()+File.separator+filename;      
      File sourceFile = new File(targetFilename);
      
      if (filename.equals(MODULE_INFO_FILE_NAME)) {
	      lookupModuleInfo(sourceFile, targetDirectory);
      }else if (sourceFile.isDirectory() && (!filename.equals("CVS"))) {
        getDirs(targetFilename);
      }
    }
  }

  void lookupModuleInfo(File moduleInfoFile, File sourceDirFile) {
    String fname = "";
    FileInputStream inStream = null;
    Reader fileIn = null;
    BufferedReader in = null;
    try {
      inStream = new FileInputStream(moduleInfoFile);	
      fileIn = new InputStreamReader(inStream, Charset.defaultCharset());
      in = new BufferedReader(fileIn);
      String line;
      boolean include = false;

      while ((line = in.readLine()) != null) {
        if (line.startsWith(INCLUDE_IN_MODULE_TAG) && isProductName(line)){
	        include = true;
        }

	      if (line.startsWith(PACKAGE_IS_PRIVATE_TAG) ||
            line.startsWith (PACKAGE_SHIPS_SOURCE_TAG)) {
          //System.out.println("package is private " + sourceDirFile);
	        include = false;
	      }
      }
      if (include) {
	      //System.out.println("Found module info for " + productName + " at " + sourceDirFile);
        String targetFilename = sourceDirFile.getAbsolutePath();              
        fname = targetFilename.substring(prefix+1);
        fname = fname.replace(File.separatorChar, '.');
        System.out.println(fname);
        packageNames.addElement(fname);
      }
	
    } catch (IOException e) {
      System.out.println(e.toString());
    } finally {
   	  closeSilently(in);
 	  closeSilently(fileIn);
 	  closeSilently(inStream);
    }
  }
  
  private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println(e.toString());
      } 
  }
  
  private boolean isProductName(String line) {
    if (!requiredProducts.isEmpty()) {
      for (int i=0; i<requiredProducts.size(); i++) {
        if ((line.indexOf((String)(requiredProducts.elementAt(i))) > -1) || (line.indexOf(productName) > -1)){
          return true;
        }
      }
        return false;
    }
    return false;
  }
}
