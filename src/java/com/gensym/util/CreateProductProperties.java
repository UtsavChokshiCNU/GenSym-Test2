package com.gensym.util;

import java.io.*;
import java.nio.charset.Charset;

/**
 * This class will copy a given properties file to the default
 * user.home for this machine. Any placeholders found in the file
 * for ROOTDIR are replaced with the root dir given which is normally 
 * the JavaLink installation directory
 */
public class CreateProductProperties { 


  public static void main(String []args) {

    if (args.length == 2) {

      String rootdir = args[1];

      // must add extra \ to Windows style \ file separators
      StringBuffer strn = new StringBuffer(rootdir.length()+5);
      for (int i=0; i<rootdir.length(); i++) {
	  char ch = rootdir.charAt(i);
	  strn.append(ch);
	  if (ch == '\\'){
		  strn.append(ch);
	  }
      }
      rootdir = strn.toString();
	    
      File sourceFile = new File(args[0]);
      System.out.println ( System.getProperty("user.home") + " " + sourceFile.getName());

      File destFile = new File(System.getProperty("user.home") + 
			       File.separator + 
			       sourceFile.getName());

      replacePlaceholderInFile(sourceFile,
			       destFile,
			       "%ROOTDIR%",
			       rootdir );

      System.out.println("Properties, have been set up and copied to default directory (" + 
			 System.getProperty("user.home") + ")");

    } else
      System.out.println("usage: java com.gensym.BuildProductProperties propertiesfilename rootdir");
  }
    

 /**
   * Replace placeholder with toreplace while copying each text line from 
   * sourceFile to destFile
   */
  static void replacePlaceholderInFile(File sourceFile, 
					  File destFile, 
					  String placeholder, 
					  String toreplace) {

    String line;
    //System.out.println(regFileName);
    FileInputStream inStream = null;
    FileOutputStream outStream = null;
    Reader fileIn = null;
    Writer fileOut = null;
    BufferedReader in = null;
    PrintWriter out = null;
    try {
      Charset charset = Charset.defaultCharset();
      
      inStream = new FileInputStream(sourceFile);	
      outStream = new FileOutputStream(destFile);
      
      fileIn = new InputStreamReader(inStream, charset);
      fileOut = new OutputStreamWriter(outStream, charset);
      
      in = new BufferedReader(fileIn);
      out = new PrintWriter(fileOut);

      while ((line = in.readLine()) != null) {
	int pos = line.indexOf(placeholder);
	while (pos > -1) {
	  line = line.substring(0, pos) + toreplace + line.substring(pos+placeholder.length());
	  pos = line.indexOf(placeholder);
	  System.out.println("Replaced in line " + line);
	}
	out.println(line);
      }

    } catch (IOException e) {
      System.out.println(e.toString());
    } finally {
  	  closeSilently(in);
  	  closeSilently(out);
	  closeSilently(fileIn);
	  closeSilently(fileOut);
	  closeSilently(inStream);
	  closeSilently(outStream);
    }
    
  }
  
  private static void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println(e.toString());
      } 
  }

}
