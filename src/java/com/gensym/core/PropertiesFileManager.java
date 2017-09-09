package com.gensym.core;

import java.io.Closeable;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Writer;
import java.nio.charset.Charset;
import java.util.Vector;

/**
 * This file takes in a product name and a properties-file name and creates a properties file
 * from the product's properties.dat file. The properties.dat file is in the marker package of the
 * product, e.g. sequoia -> com.gensym.ntw, javalink -> com.gensym.jgi.
 * The properties.dat format is as follows
 * name=key
 * intelnt-deafult-value=value
 * sparcsol-default-value=value
 * annotations should be used before the key and should begin with a '#'.
 * So an example of a properties.dat file is:
 * #
 * #key for classes dir
 * name=com.gensym.classes.dir
 * intelnt-default-value=%PRODUCT_ROOT%\classes\lib
 * sparcsol-default-value=%PRODUCT_ROOT/classes/lib
 * 
 */
public class PropertiesFileManager {
  private String product;
  private String PropsFilePath;

  private PropertiesFileManager (String product, String filename) {
    this.product = product;
    this.PropsFilePath = filename;
  }
  
  private String[] openPropsDataFile() {
    Product prod = ProductManager.getProduct(this.product);
    String packageName = prod.getMarkerPackage();
    String resourceName = "/" + packageName + "/properties.dat";
    InputStream is = getClass ().getResourceAsStream (resourceName);    
    try {
      String[] lines = new LineReader (is, new LineFilter () {
	      @Override
	      public boolean accept (String line) {
	        return true;
	      }
      }).readLines ();
      is.close ();
      return lines;
    } catch (Exception ioe) {
      System.err.println (ioe);
    }
    return null;
  }
  
  private void buildPropsFile(String[] lines) throws MalformedPropertiesFileException{
    int indx;
    String os;
    String osname = System.getProperty("os.name");
    String osarch = System.getProperty("os.arch");
    Vector comments = new Vector();
    FileOutputStream outStream = null;
    Writer fileOutputStream=null;
    PrintWriter fileWriter=null;
    try {
      File propFile = new File(this.PropsFilePath);
      outStream = new FileOutputStream(propFile);
      fileOutputStream = new OutputStreamWriter(outStream, Charset.defaultCharset());
      fileWriter = new PrintWriter (fileOutputStream);
    
    if ((os = getPlatformName(osname, osarch)) == null)
      throw new MalformedPropertiesFileException ("OS not supported");
    
    int i=-1;
    while (++i<lines.length) {
      while (lines[i].trim().startsWith ("#") && (i<lines.length)) {
        fileWriter.println(lines[i]);
        comments.addElement(lines[i++]);
      }
      
      if ( (lines[i].startsWith("name")) && ((indx = lines[i].indexOf("=")) >0) ){
        String key = lines[i].substring(indx+1, lines[i].length());
        System.out.println(key);
        fileWriter.print(key+"=");
        if ( lines[++i].startsWith(os+"-default-value") && ((indx = lines[i].indexOf("=")) >0) ){
          String value = lines[i].substring(indx+1, lines[i].length());
          System.out.println(value);
          fileWriter.println(value);
          i++;
        }
        else if ( lines[++i].startsWith(os+"-default-value") && ((indx = lines[i].indexOf("=")) >0) ) {
          String value = lines[i].substring(indx+1, lines[i].length());
          System.out.println(value);
          fileWriter.println(value);
        }
        else
          throw new MalformedPropertiesFileException ("No '" + os+"-default-value' specified in " + lines[i]);
      }
      else
        throw new MalformedPropertiesFileException ("Incorrect File format in");
    }
    }
    catch (IOException e) {
      System.err.println(e.toString());
    }
    finally {
	  closeSilently(fileWriter);
	  closeSilently(fileOutputStream);
	  closeSilently(outStream);
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
  
  private String getPlatformName(String osname, String osarch) {
    if ((osname.indexOf("Windows") > -1))
      return "intelnt";
    else if ((osarch.indexOf("sparc") > -1))
      return "solaris";
    else
      return null;
  }

  public static void main(String args[]) {
    if (args.length == 2) {
      PropertiesFileManager pfm = new PropertiesFileManager(args[0], args[1]);
      String[] entries = pfm.openPropsDataFile();
      try {
        pfm.buildPropsFile(entries);
      }
      catch (MalformedPropertiesFileException e) {
        System.err.println(e);
      }
    }
    else {
         System.out.println("uagse: java com.gensym.PropertiesFileManager productname propsfilepath");
         System.out.println("e.g. java com.gensym.PropertiesFileManager sequoia c:\\.com.gensym.props");
    }
  }
}
