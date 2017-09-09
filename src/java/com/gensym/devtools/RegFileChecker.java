
package com.gensym.devtools;

import java.io.*;
import java.util.*;

public class RegFileChecker {

  public static void main (String[] args) throws Exception {
    String[] regFiles = RegFileFixer.collectRegistryFiles
      (System.getProperty ("user.dir"));
    Properties correctIDs = new Properties ();
    InputStream is = new FileInputStream (new File (args[0]));
    correctIDs.load (is);
    for (int i=0; i<regFiles.length; i++) {
      String regFile = regFiles[i];
      String controlName = regFile.substring (0, regFile.indexOf ('.'));
      String correctID = correctIDs.getProperty (controlName);
      String controlID = obtainIDFromRegFile (regFile);
      if (correctID == null || correctID.equals (controlID)) {
	System.out.print (controlName + " : " +
			  controlID + " -> OK");
	if (correctID == null)
	  System.out.println ("  New");
	else
	  System.out.println ("");
      } else {
	System.out.println (controlName + " has differing IDs\n" +
			    "  Desired = " + correctID + "\n" +
			    "   Actual = " + controlID);
      }
    }
  }

  static String obtainIDFromRegFile (String regFileName) throws IOException {
    File regFile = new File (regFileName);
    String line;
    FileReader fileIn = new FileReader(regFile);
    BufferedReader in = new BufferedReader(fileIn);

    while ((line = in.readLine()) != null) {
      int pos = line.indexOf ("HKEY_CLASSES_ROOT\\CLSID");
      if (pos >= 0) {
	pos = line.indexOf ("\\{");
	String ID = line.substring (pos + 2, pos + 2 + 36);
	in.close ();
	return ID;
      }
    }
    in.close ();
    return null;
  }

}
