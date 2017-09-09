
package com.gensym.ntw.util;

import java.io.*;
import com.gensym.dlg.MessageDialog;
import com.gensym.core.ExitThread;

public class ActiveXRegisterManager {

  private ActiveXRegisterManager () {
  }

  public static void main (String[] args) {
    registerControls (args[0]);
  }

  public static void registerControls (String homeDir) {
    String controlsDir = homeDir + "\\activex";
    String dirList[] = collectRegistryFiles (controlsDir);
    System.out.println ("Collected registry files ->" + controlsDir);
    com.gensym.core.DebugUtil.printArray (dirList);
    String escapedHomeDir = replaceInString (homeDir, "\\", "\\\\");
    String escapedControlsDir = replaceInString (controlsDir, "\\", "\\\\");
    for (int i=0; i<dirList.length; i++) {
      String fileName = dirList[i];
      //System.out.println ("Replacing in " + fileName);
      String sourceFileName = controlsDir + File.separator + fileName;
      File sourceFile = new File (sourceFileName);
      File destFile = new File (sourceFileName + "2");
      replacePlaceHoldersInFile (sourceFile, destFile,
				 "\"activex\\",
				 "\"" + escapedControlsDir + "\\",
         "\"classes\\\\sequoia.jar\"",
         "\"" + escapedHomeDir + "\\\\sequoia.jar\"",
				 "D:\\\\bt\\\\vkp-nt\\\\java\\\\activex",
				 escapedControlsDir);
      javaCopyFile (destFile, sourceFile);
      // delete reg2 file
      try {
	String command = "regedit /s " + sourceFileName;
	System.out.println ("Registering " + sourceFileName);
	Runtime.getRuntime ().exec (command);
      } catch (java.io.IOException ioe) {
	showUser ("The following exception was reporting while registering " +sourceFileName+" : " + ioe);
      }
    }
    showUser ("T2 1.0 Rev. 1 controls have been successfully entered into the registry");

    ExitThread.exit();
  }

  private static java.awt.Frame AFrame;
  private static void showUser (String text) {
    if (AFrame == null) {
      AFrame = new java.awt.Frame ("");
      AFrame.setSize (100, 100);
      AFrame.setLocation (400, 400);
      AFrame.addNotify ();
    }
    MessageDialog iDlg = new MessageDialog (AFrame, "Install Controls", true, text, null);
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
					String toReplace3) {
    /*System.out.println ("Replace (" + placeHolder1 + " -> " + toReplace1 + ") (" +
			placeHolder2 + " -> " + toReplace2 + ")");*/
    String line;
    //System.out.println(regFileName);
    FileReader fileIn = null;
    FileWriter fileOut = null;
    try {
      fileIn = new FileReader(sourceFile);
      fileOut = new FileWriter(destFile);
      BufferedReader in = new BufferedReader(fileIn);
      PrintWriter out = new PrintWriter(fileOut);
      
      while ((line = in.readLine()) != null) {
	int pos = line.indexOf(placeHolder1);
	if (pos > -1) {
	  line = line.substring(0, pos) + toReplace1 + line.substring(pos+placeHolder1.length());
	  //System.out.println("Replaced (1) in line " + line);
	}
	pos = line.indexOf(placeHolder2);
	if (pos > -1) {
	  line = line.substring(0, pos) + toReplace2 + line.substring(pos+placeHolder2.length());
	  //System.out.println("Replaced (2) in line " + line);
	}
	pos = line.indexOf(placeHolder3);
	if (pos > -1) {
	  line = line.substring(0, pos) + toReplace3 + line.substring(pos+placeHolder3.length());
	  //System.out.println("Replaced (3) in line " + line);
	}
	out.println(line);
      }
      
    } catch (IOException e) {
      System.err.println(e.toString());
    } finally {
      try {
	if (fileIn != null) fileIn.close();
	if (fileOut != null) fileOut.close();
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
