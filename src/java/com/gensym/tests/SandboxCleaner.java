/****************************************************************************
 * SandboxCleaner.java
 * 
 * Author: John Valente
 *
 * To use: 
 *   First, create a file of your CVS "complaints" by saying:
 *     > cd %SRCBOX%
 *     > cvs co -P java > java-co.log
 *   Then, (until this class handles command line arguments properly),
 *   edit this file to use the correct sourceLocation, destLocation, 
 *   and relativeLogFileLocation.  destLocation should exist already.
 *   Compile this file, and run it with no arguments.  It will move all
 *   of the files that CVS complained about to another location.
 ***************************************************************************/

package com.gensym.tests;

import com.gensym.core.GensymApplication;
import com.gensym.devtools.GensymFileReader;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.Reader;
import java.io.UnsupportedEncodingException;


public class SandboxCleaner extends GensymApplication
{
  private static final short moveFileFlag   = 1;
  private static final short cleanupCVSFlag = 2;

  private static final int readEOFChar = -1;
  private static final int cvsSeparatorChar = 47;  /* '/' */
  private static final int suffixChar = 46;  /* '.' */
  private static final int newlineBeginning = 13;
  private static final int newlineCompletion = 10;

  private String sourceLocation = "d:\\bt\\jv-ab";
  private String destLocation = "d:\\bt\\modified";
  private String relativeLogFileLocation = "logs\\java.log";
  private String[] relevantDirectories;
  private Reader reader;
  private int sizeOfDirectoriesArray = 10;
  private int numberOfDirectories = 0;

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private SandboxCleaner (String[] cmdLineArgs)
  {
    super(cmdLineArgs);
    relevantDirectories = new String[sizeOfDirectoriesArray];
    reader = GensymFileReader.makeGensymFileReader
      (sourceLocation + File.separator + relativeLogFileLocation);
  }



  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void error (String message) {
    System.err.println("ERROR: " + message);
    System.err.flush();
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void print (String message) {
    System.out.print(message);
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void println (String message) {
    System.out.println(message);
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private boolean moveExistentFile (String preSuffixPath, String suffix,
				    File srcFile) {
    String dstFileName;
    File dstFile;
    int iteration = 1;

    dstFileName = destLocation + File.separator + preSuffixPath + suffix;
    dstFile = new File(dstFileName);
    while (dstFile.exists()) {
      iteration++;
      dstFileName = destLocation + File.separator + preSuffixPath +
	"-" + iteration + suffix;
      dstFile = new File(dstFileName);
    }
    File dstDir = new File(dstFile.getParent());
    if (!dstDir.exists()) {
      dstDir.mkdirs();
    }
    if (!dstDir.isDirectory()) {
      error("destination directory exists, but is a file: " +
	    dstDir + " (aborting).");
      return false;
    }
    println("Moving \"" + srcFile + "\" to \"" + dstFileName + "\"");
    srcFile.renameTo(dstFile);
    return true;
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void addDirectory (String directory) {
    int i;

    for (i=0; i<numberOfDirectories; i++)
      if (directory.equals(relevantDirectories[i])) 
	return;
    if (numberOfDirectories < sizeOfDirectoriesArray)
      relevantDirectories[numberOfDirectories++] = directory;
    else {
      String[] tempArray;

      tempArray = relevantDirectories;
      sizeOfDirectoriesArray = (sizeOfDirectoriesArray * 2) -
	(sizeOfDirectoriesArray / 2);
      relevantDirectories = new String[sizeOfDirectoriesArray];
      for (i=0; i<numberOfDirectories; i++)
	relevantDirectories[i] = tempArray[i];
      relevantDirectories[i] = directory;
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void printDirectories () {
    int i, j, k, dot2, dot3;
    String[] files;
    String cvsFile, directoryName, basename, suffix;
    File file, directory;

    for (i=0; i<numberOfDirectories; i++) {
      directoryName = sourceLocation + File.separator + relevantDirectories[i];
      directory = new File(directoryName);
      if (directory.isDirectory()) {
	files = directory.list();
	for (j=0; j<files.length; j++) {
	  cvsFile = files[j];
	  file = new File(directoryName + File.separator + cvsFile);
	  if (file.exists() &&
	      (cvsFile.charAt(0) == '.') &&
	      (cvsFile.charAt(1) == '#')) {
	    dot2 = 0;
	    k = 1;
	    basename = "";
	    suffix = "";
	    while ((dot2 == 0) && (++k < cvsFile.length()))
	      if (cvsFile.charAt(k) == '.') dot2 = k;
	    if (dot2 > 2) {
	      basename = cvsFile.substring(2, dot2);
	      dot3 = dot2;
	      while ((dot3 == dot2) && (++k < cvsFile.length()) &&
		     cvsFile.charAt(k) != '1')
		if (cvsFile.charAt(k) == '.') dot3 = k;
	      if (dot3 > dot2)
		suffix = cvsFile.substring(dot2, dot3);
	    }
	    moveExistentFile(relevantDirectories[i] + File.separator + basename,
			     suffix, file);
	  }
	}
      }
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/ 
  private boolean maybeMoveFile (String preSuffixPath, String suffix,
				 boolean moveIt) {
    String srcFileName;
    File srcFile;
    
    srcFileName = sourceLocation + File.separator + preSuffixPath + suffix;
    srcFile = new File(srcFileName);
    if (!srcFile.exists()) {
      error("Can't file file \"" + srcFileName + "\"");
      return false;
    }

    if (srcFile.isDirectory() && srcFile.list().length <= 0) {
      boolean deletedFile = false;
      try {
	deletedFile = srcFile.delete();
      } catch (SecurityException exception) {
	/* Fine, don't delete it -- do try to move it. */
	deletedFile = false;
      }
      moveIt = !deletedFile;
    }

    if (moveIt) {
      return moveExistentFile(preSuffixPath, suffix, srcFile);
    } else {
      println("Leaving \"" + srcFileName + "\" alone.");
      return true;
    }
  }
  

  /****************************************************************************
   * This method is only called by readUpdateFile, which does a null check
   * on reader at the beginning, so we know when this method is reached that
   * reader is non-null.
   ***************************************************************************/
  private boolean getFilenameAndMoveFile (int previousChar, boolean moveIt) {
    int currentChar = previousChar;
    short currentPosition = -1, positionOfLastSeparatorChar = -1;
    String preSuffixPath = "", suffix = "";
    boolean doingSuffix = false;

    try {
      while ((currentChar != readEOFChar) && (currentChar != newlineBeginning)) {
	currentPosition++;
	if (currentChar == cvsSeparatorChar) {
	  if (doingSuffix) {
	    doingSuffix = false;
	    preSuffixPath += suffix;
	    suffix = "";
	  }
	  positionOfLastSeparatorChar = currentPosition;
	  currentChar = (int) File.separatorChar;
	}
	if (currentChar == suffixChar) {
	  if (doingSuffix) {
	    preSuffixPath += suffix;
	    suffix = "";
	  }
	  doingSuffix = true;
	}
	if (doingSuffix) suffix += (char) currentChar;
	else preSuffixPath += (char) currentChar;
	currentChar = reader.read();
      }
      addDirectory(preSuffixPath.substring(0, positionOfLastSeparatorChar));
      maybeMoveFile(preSuffixPath, suffix, moveIt);
      return (currentChar == newlineBeginning);
    } catch (IOException io) {
      error("readUpdateFile: I/O Exception");
      return false;
    }
  }



  /****************************************************************************
   *
   *
   ***************************************************************************/
  private short decodeCVSCode (char code) {
    short instructions = 0;

    switch (code) {
    case 'C':
      instructions |= cleanupCVSFlag;
    case '?':
    case 'M':
      instructions |= moveFileFlag;
      break;
    case 'U':
    case 'P':
      break;
    default:
      error("Unknown CVS status code: '" + code + "'");
    }
    return instructions;
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void readUpdateFile () {
    if (reader == null) {
      error("Could not read update file.");
      return;
    }
    try {
      int currentChar;
      short instructions;

      currentChar = reader.read();
      while (currentChar != readEOFChar) {
	instructions = decodeCVSCode((char) currentChar);
	do currentChar = reader.read(); while (currentChar == 32);
	if (getFilenameAndMoveFile(currentChar, 0 != (instructions & moveFileFlag)))
	  do {
	    currentChar = reader.read();
	  } while ((currentChar == newlineBeginning) || (currentChar == newlineCompletion));
      }
      reader.close();
      printDirectories();
    } catch (IOException io) {
      error("readUpdateFile: I/O Exception");
      return;
    }
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  public static void main (String argv[]) {
    SandboxCleaner sc = new SandboxCleaner(argv);
    sc.readUpdateFile();
  }

}

