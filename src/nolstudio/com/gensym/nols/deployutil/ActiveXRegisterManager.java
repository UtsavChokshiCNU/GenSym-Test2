package com.gensym.nols.deployutil;

import java.io.*;
import java.nio.charset.Charset;
import java.awt.*;


public class ActiveXRegisterManager {

  private ActiveXRegisterManager () {
  }

  public static void main (String[] args) {
    registerControls (args[0], args[1]);
  }

  public static void registerControls (String homeDir, String pluginDir) {
    String controlsDir = homeDir + "\\ActiveX";
    String plugDir = pluginDir + "\\bin";
    // returns the list of .reg files
    String dirList[] = collectRegistryFiles (controlsDir);
    //System.out.println ("Collected registry files ->" + controlsDir);
    // fix the directory names to have double slashes
    String escapedHomeDir = replaceInString (homeDir, "\\", "\\\\");
    String escapedControlsDir = replaceInString (controlsDir, "\\", "\\\\");
    String escapedPluginDir = replaceInString (plugDir, "\\", "\\\\");
    
    // iterate through the collected .reg files and replace the given text
    for (int i=0; i<dirList.length; i++) {
      String fileName = dirList[i];
      //System.out.println ("Replacing in " + fileName);
      String sourceFileName = controlsDir + File.separator + fileName;
      //System.out.println ("sourceFileName is " + sourceFileName);
      File sourceFile = new File (sourceFileName);
      File destFile = new File (sourceFileName + "2");
      //about to do the replace in the file
      replacePlaceHoldersInFile (sourceFile, destFile,
				 "beans.ocx",
				 escapedPluginDir + "\\\\beans.ocx",
				  "\"OnlineProcessor",
				 "\"" + escapedControlsDir + "\\\\OnlineProcessor",
				 "\"ActiveX",
				 "\"" + escapedControlsDir,
				 "NOLProcessor.tlb",
				 escapedControlsDir + "\\\\NOLProcessor.tlb");
      //copy the destination file back to source file
      javaCopyFile (destFile, sourceFile);
      // exit here for now, without registering
      //System.exit(0);
      try {
	String command = "regedit /s " + sourceFileName;
	System.out.println ("Registering " + sourceFileName);
	Runtime.getRuntime ().exec (command);
      } catch (java.io.IOException ioe) {
	showUser ("The following exception was reporting while registering "
               +sourceFileName+" : " + ioe);
      }
    }
    System.exit (0);
  }

  private static volatile java.awt.Frame AFrame;
  private static void showUser (String text) {
    if (AFrame == null) {
      synchronized (ActiveXRegisterManager.class) {
        if (AFrame == null) {
          AFrame = new java.awt.Frame ("");
          AFrame.setSize (100, 100);
          AFrame.setLocation (400, 400);
          AFrame.addNotify ();
        }
      }
    }
    //MessageDialog iDlg = new MessageDialog (AFrame, "Install Controls", true, text, null);
    Dialog iDlg = new Dialog(AFrame, "Install Controls", true);
    iDlg.pack ();
    java.awt.Rectangle bounds = iDlg.getBounds ();
    iDlg.setBounds (0, 0, bounds.width, bounds.height);
    iDlg.getToolkit ().beep ();
    iDlg.setVisible (true);
    java.awt.Toolkit.getDefaultToolkit().beep();
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
					 String toReplace2,
					 String placeHolder3,
					 String toReplace3,
					 String placeHolder4,
					 String toReplace4) {
    /*System.out.println ("Replace (" + placeHolder1 + " -> " + toReplace1 + ") (" +
			placeHolder2 + " -> " + toReplace2 + ")");*/
    String line;
    //System.out.println(regFileName);
    FileInputStream inStream = null;
    FileOutputStream outStream = null;
    Reader streamReader = null;
    Writer streamWriter = null;
    BufferedReader in = null;
    PrintWriter out = null;
    try {
      Charset charset = Charset.defaultCharset();
      inStream = new FileInputStream(sourceFile);	
      outStream = new FileOutputStream(destFile);
      
      streamReader = new InputStreamReader(inStream, charset);
      streamWriter = new OutputStreamWriter(outStream, charset);
      
      in = new BufferedReader(streamReader);
      out = new PrintWriter(streamWriter);
      
      while ((line = in.readLine()) != null) {
	int pos = line.indexOf(placeHolder1);
	if (pos > -1) {
	  line = line.substring(0, pos) + toReplace1 + 
	    line.substring(pos+placeHolder1.length());
	  //System.out.println("Replaced (1) in line " + line);
	}
	pos = line.indexOf(placeHolder2);
	if (pos > -1) {
	  line = line.substring(0, pos) + toReplace2 + 
	    line.substring(pos+placeHolder2.length());
	  //System.out.println("Replaced (2) in line " + line);
	}
	pos = line.indexOf(placeHolder3);
	if (pos > -1) {
	  line = line.substring(0, pos) + toReplace3 + 
	    line.substring(pos+placeHolder3.length());
	  //System.out.println("Replaced (3) in line " + line);
	}
	pos = line.indexOf(placeHolder4);
	if (pos > -1) {
	  line = line.substring(0, pos) + toReplace4 + 
	    line.substring(pos+placeHolder4.length());
	  //System.out.println("Replaced (4) in line " + line);
	}
	out.println(line);
      }
      
    } catch (IOException e) {
      System.err.println(e.toString());
    } finally {
  	  closeSilently(in);
  	  closeSilently(out);
	  closeSilently(streamReader);
	  closeSilently(streamWriter);
  	  closeSilently(inStream);
	  closeSilently(outStream);
    }
    
  }
  
  private static void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println("NON-FATAL: Error while closing stream : " + e.toString());
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

  private static String replaceInString (String origString, String pattern, String replacement) {
    int pos, curPosn = 0;
    StringBuffer newStringB = new StringBuffer (origString.length ());
    int patternLength = pattern.length ();
    while ((pos = origString.indexOf (pattern, curPosn)) >= 0) {
      //System.out.println ("Index of " + pattern + " in " + origString + " = " + pos);
      newStringB.append (origString.substring (curPosn, pos)).append (replacement);
      curPosn = pos + patternLength;
    }
    if (curPosn != origString.length ())
      newStringB.append (origString.substring (curPosn));
    return newStringB.toString ();
  }

}
