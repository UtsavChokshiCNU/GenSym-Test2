
package com.gensym.devtools;

import java.io.*;

public class RegFileFixer {

  public static void main (String[] args) {
    String[] regFiles = collectRegistryFiles (System.getProperty ("user.dir"));
    for (int i=0; i<regFiles.length; i++) {
      String regFile = regFiles[i];
      cleanUpPathsInFile (new File (regFile));
    }
  }



  static String[] collectRegistryFiles (String controlsDir) {
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
  static void cleanUpPathsInFile (File sourceFile) {
    /*System.out.println ("Replace (" + placeHolder1 + " -> " + toReplace1 + ") (" +
			placeHolder2 + " -> " + toReplace2 + ")");*/
    String line;
    //System.out.println(regFileName);
    FileReader fileIn = null;
    FileWriter fileOut = null;
    File destFile = new File (sourceFile.getPath () + "2");
    try {
      fileIn = new FileReader(sourceFile);
      fileOut = new FileWriter(destFile);
      BufferedReader in = new BufferedReader(fileIn);
      PrintWriter out = new PrintWriter(fileOut);
      
      while ((line = in.readLine()) != null) {
	System.out.println ("Read Line = " + line);
	int pos = line.indexOf("\\\\activex");
	if (pos > -1) {
	  System.out.println (" Matched \\\\activex");
	  int posQuote = line.lastIndexOf ('"', pos);
	  if (posQuote == pos - 1)
	    continue;
	  line = line.substring(0, posQuote + 1) + line.substring(pos+2,line.length());
	  System.out.println ("    Fixed Line! -> " + line);
	}
	out.println(line);
      }
      
    } catch (IOException e) {
      System.err.println(e.toString());
    } finally {
      try {
	if (fileIn != null) fileIn.close();
	if (fileOut != null) fileOut.close();
	javaCopyFile (destFile, sourceFile);
	destFile.delete ();
      } catch (IOException e) {
      }
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
      System.err.println(e.toString());
    }
  }


}
