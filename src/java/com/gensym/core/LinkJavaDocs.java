package com.gensym.core;

import java.io.BufferedReader;
import java.io.Closeable;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.io.Reader;
import java.io.Writer;
import java.nio.charset.Charset;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Enumeration;
import java.util.Vector;

public class LinkJavaDocs {
  private int prefix;
  private String productName;
  private String targetDir;
  private String sourceDir;
  private String javaDocDir;
  private String javaSwingDocsDir;
  private String linkDirPath;
  private Vector packageNames = new Vector ();
  private Vector requiredProductInfos = new Vector();
  private Vector requiredProductNames = new Vector();
  private static String MODULE_INFO_FILE_NAME = "package.info";
  private static String INCLUDE_IN_MODULE_TAG = "include-in-module:";
  private static String PACKAGE_IS_PRIVATE_TAG = "package-is-private";
  private static String HTML_EXT = ".html";
  private static final int MAX_FILE_LENGTH = 30;
  private static final String PACKAGE_SHIPS_SOURCE_TAG = "dont-delete-java";

  public static void main(String args[]) {
    LinkJavaDocs docsLinker = new LinkJavaDocs(args[0], args[1], args[2]);
    docsLinker.readProductPackages();
    docsLinker.loadProductPackages();
    docsLinker.printAll();
    docsLinker.fixHtmlFiles();
  }
  
  private void printAll() {
    for (Enumeration e = requiredProductInfos.elements(); e.hasMoreElements();) {
      ProductPacakgesInfo packageInfo = (ProductPacakgesInfo)e.nextElement();
      System.out.println(packageInfo.packageName);
      System.out.println(packageInfo.ownPackages);
    }
  }
  
  public LinkJavaDocs(String productName, String sourceDir, String javaDocDir) {
    this.productName = productName;
    this.sourceDir = sourceDir;
    this.prefix = sourceDir.length();
    this.javaDocDir = javaDocDir;
    this.linkDirPath = ".." + File.separator + ".." + File.separator + ".." + File.separator +
                       productName + File.separator + "docs" + File.separator + "api" + File.separator;
    System.out.println(this.linkDirPath);
  }

  public void readProductPackages() {
    Product prod = ProductManager.getProduct(this.productName);
    System.out.println("Found product: " + prod);
    ProductInfo[] pinfo = prod.getRequiredProducts();
    for (int i=0; i<pinfo.length; i++) {
      requiredProductNames.addElement(pinfo[i].getName());
    }
  }
  
  private void loadProductPackages() {
    String targetDirName = sourceDir + File.separator + "com" + File.separator + "gensym";    
    for (int i=0; i<this.requiredProductNames.size(); i++) {
      Vector packages = new Vector();
      getBelongingPackages((String)(requiredProductNames.elementAt(i)), targetDirName, packages);
      requiredProductInfos.addElement(
        new ProductPacakgesInfo((String)requiredProductNames.elementAt(i),packages));
    }
  }

  private void getBelongingPackages(String pname, String targetDirName, Vector packages) {
    String fname;
    String fullProdname;
    File targetDirectory = new File (targetDirName);
    String dirList[] = targetDirectory.list();
    
    if (dirList == null) {
      System.out.println("No Dirs Found");
    }
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = targetDirectory.getAbsolutePath()+File.separator+filename;      
      File sourceFile = new File(targetFilename);
      
      if (filename.equals(MODULE_INFO_FILE_NAME)) {
	      fullProdname = lookupModuleInfo(pname, sourceFile, targetDirectory);
        if (fullProdname != null)
          packages.addElement(fullProdname);
      }else if (sourceFile.isDirectory() && (!filename.equals("CVS"))) {
        getBelongingPackages(pname, targetFilename, packages);
      }
    }
  }

  private String lookupModuleInfo(String prodName, File moduleInfoFile, File sourceDirFile) {
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
        if (line.startsWith(INCLUDE_IN_MODULE_TAG) && (line.indexOf(prodName) > -1)){
	        include = true;
        }

	      if (line.startsWith(PACKAGE_IS_PRIVATE_TAG) ||
            line.startsWith (PACKAGE_SHIPS_SOURCE_TAG)) {
	        include = false;
	      }
      }
      if (include) {
        String targetFilename = sourceDirFile.getAbsolutePath();              
        fname = targetFilename.substring(prefix+1);
        fname = fname.replace(File.separatorChar, '.');
        return(fname);
      }
    } catch (IOException e) {
      System.out.println(e.toString());
    } finally {
    	closeSilently(in);
    	closeSilently(fileIn);
    	closeSilently(inStream);
    }
    return null;
  }
  
  private void fixHtmlFiles() {
    File targetDirectory = new File (this.javaDocDir);
    String dirList[] = targetDirectory.list();
    
    if (dirList == null) {
      System.out.println("No Files Found");
    }
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = targetDirectory.getAbsolutePath()+File.separator+filename;      
      File sourceFile = new File(targetFilename);
      
      if (targetFilename.lastIndexOf(".html") > 1){
        System.out.println("Parsing file: " + sourceFile);
        parseHtmlFile(sourceFile);
      }
    }    
  }
  
  private String varLine;

  private void parseHtmlFile(File file) {
    String line;
    FileInputStream inStream = null;
    FileOutputStream outStream = null;
    Reader fileIn = null;
    Writer fileOut = null;
    BufferedReader in = null;
    PrintWriter out = null;
    File destFile = new File (file.getPath () + ".copy");
    try {
      Charset charset = Charset.defaultCharset();
      
      inStream = new FileInputStream(file);	
      outStream = new FileOutputStream(destFile);
      
      fileIn = new InputStreamReader(inStream, charset);
      fileOut = new OutputStreamWriter(outStream, charset);
      
      in = new BufferedReader(fileIn);
      out = new PrintWriter(fileOut);
      
      while ((line = in.readLine()) != null) {
        varLine = line;
	      int pos = line.indexOf(".html");
	      if (pos > -1) {
          do {
            line = varLine;
            checkLine(varLine);
          } while ( !line.equals(varLine) );
	      }
	      out.println(varLine);
      }
    } catch (IOException e) {
      System.err.println(e.toString());
    } finally {
	  closeSilently(in);
	  closeSilently(out);
	  closeSilently(fileIn);
	  closeSilently(fileOut);
	  closeSilently(inStream);
	  closeSilently(outStream);
	  
      javaCopyFile (destFile, file);
      destFile.delete ();
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
  
  private void checkLine(String line){
    for (Enumeration e = requiredProductInfos.elements(); e.hasMoreElements();) {
      ProductPacakgesInfo packageInfo = (ProductPacakgesInfo)e.nextElement();
      String product = packageInfo.packageName;
      Vector modules = packageInfo.ownPackages;
      for (int i=0; i<modules.size(); i++) {
        String modulePath = (String)modules.elementAt(i);
        int pos = line.indexOf(modulePath);
	      if (pos > -1) {
          fixLine(line, modulePath, product);
	      }        
      }
    }
  }
  
  private void fixLine(final String line, final String path, final String product) {
    String finalLine = null;
    String filePath = "\"" + path;
    int startPos = line.indexOf(filePath);
    int cursor = startPos + filePath.length();
    String productInstalledDir = ".." + File.separator + ".." + File.separator + ".." + File.separator + ".." + File.separator +
                       product.toUpperCase()+"_INSTALL_DIR" + File.separator + "docs" + File.separator + "api" + File.separator;
    
    if ( line.charAt(cursor)== '.') {
      cursor++;
    }
    int endPos = line.indexOf('.', cursor);
    if (endPos > -1) {
      if ( ((endPos - cursor) < MAX_FILE_LENGTH) && 
           (line.regionMatches(endPos, HTML_EXT, 0, HTML_EXT.length())) )  {
        boolean isLegalName = checkIfLegalFilename(line.substring(cursor,endPos));
        if (isLegalName) {
          String firstPart = line.substring(0,startPos+1);
          String endPart = line.substring(startPos+1, line.length());
          finalLine = firstPart+productInstalledDir+endPart;
          varLine = finalLine;
        }
        else
          System.out.println(line.substring(cursor,endPos) + " is not a legal file name");
      }
    }
  }
  
  private boolean checkIfLegalFilename(String str) {
    for (int i =0; i<str.length(); i++) {
      if ( Character.isLetterOrDigit(str.charAt(i)) || str.charAt(i) == '_' 
           || str.charAt(i) == '$' ) 
        continue;
      else return false;
    }
    return true;
  }
  
  static void javaCopyFile(File sourceFile, File targetFile) {    
    try {
      FileInputStream inf = new FileInputStream(sourceFile);
      FileOutputStream outf = new FileOutputStream(targetFile);
      
      byte[] ba = new byte[4096];
      int bytes_read;
      while ((bytes_read = inf.read(ba)) != -1) {
	      outf.write(ba, 0, bytes_read);
      }
      inf.close();
      outf.close();
    } catch (Exception e) {
      System.err.println(e.toString());
    }
  }

  
  class ProductPacakgesInfo {

    ProductPacakgesInfo(String packagename, Vector ownPackages) {
      this.packageName = packagename;
      this.ownPackages = ownPackages;
    }

    String packageName;
    Vector ownPackages;
  }  
}
