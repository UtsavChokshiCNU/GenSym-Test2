
package com.gensym.util;

import java.io.*;
import java.nio.charset.Charset;

public class ActiveXRegisterManager {

  private ActiveXRegisterManager () {
  }

  public static void main (String[] args) {
    registerControls (args[0]);
  }

  public static void registerControls (String controlsDir) {
    String dirList[] = collectRegistryFiles (controlsDir);
    System.out.println ("Collected registry files ->");
    com.gensym.core.DebugUtil.printArray (dirList);
    String escapedControlsDir = replaceInString (controlsDir, "/", "\\\\");
    for (int i=0; i<dirList.length; i++) {
      String fileName = dirList[i];
      System.out.println ("Replacing in " + fileName);
      String sourceFileName = controlsDir + File.separator + fileName;
      File sourceFile = new File (sourceFileName);
      File destFile = new File (sourceFileName = "2");
      replacePlaceHoldersInFile (sourceFile, destFile,
				 "activex\\\\beans.ocx",
				 escapedControlsDir + "\\\\beans.ocx",
				 "D:\\\\bt\\\\vkp-nt\\\\java\\\\activex",
				 escapedControlsDir);
      javaCopyFile (destFile, sourceFile);
      // delete reg2 file
      try {
	Runtime.getRuntime ().exec ("ls -l " + sourceFileName);
      } catch (java.io.IOException ioe) {
	System.err.println (ioe);
      }
    }
  }

  private static String[] collectRegistryFiles (String controlsDir) {
    File controlsDirFile = new File (controlsDir);
    String fileList[] = controlsDirFile.list (new FilenameFilter () {
      @Override
      public boolean accept (File dir, String fileName) {
	return fileName.endsWith (".reg");
      }
    });
    return fileList;
  }

  /**
   * Replace placeHolder with toReplace while copying each text line from 
   * sourceFile to destFile
   */
  static void replacePlaceHoldersInFile (File sourceFile, 
					File destFile, 
					String placeHolder1, 
					String toReplace1,
					String placeHolder2,
					String toReplace2) {
    
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
	int pos = line.indexOf(placeHolder1);
	if (pos > -1) {
	  line = line.substring(0, pos) + toReplace1 + line.substring(pos+placeHolder1.length());
	  System.out.println("Replaced (1) in line " + line);
	}
	pos = line.indexOf(placeHolder2);
	if (pos > -1) {
	  line = line.substring(0, pos) + toReplace2 + line.substring(pos+placeHolder2.length());
	  System.out.println("Replaced (2) in line " + line);
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
      System.out.println(e.toString());
    }
  }

  private static String replaceInString (String origString, String pattern, String replacement) {
    int pos, curPosn = 0;
    StringBuffer newStringB = new StringBuffer (origString.length ());
    int patternLength = pattern.length ();
    while ((pos = origString.indexOf (pattern, curPosn)) >= 0) {
      System.out.println ("Index of " + pattern + " in " + origString + " = " + pos);
      newStringB.append (origString.substring (curPosn, pos)).append (replacement);
      curPosn = pos + patternLength;
    }
    if (curPosn != origString.length ())
      newStringB.append (origString.substring (curPosn));
    return newStringB.toString ();
  }

}
