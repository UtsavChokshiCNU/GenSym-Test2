/* FileCopier.java
 */
package com.gensym.tests;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.io.Writer;

public class FileCopier 
{
  public static final byte ABORT     = 1;
  public static final byte OVERWRITE = 2;
  public static final byte PROMPT    = 3;
  public static final byte RENAME    = 4;

  public static final byte CREATE    = 2;

  private static final byte JAVA = -1;
  private static final byte C    = -2;
  private static final byte H    = -3;
  private static final byte TXT  = -4;
  private static final byte MK   = -5;

  private static final byte ANY_OS  = 64;
  private static final byte UNIX    = 65;
  private static final byte WINDOWS = 66;

  private static final String myName = "FileCopier";
  private static final char systemIndependentSeparator = '/';
  private static String osType = "Unknown";

  private boolean isDebug = false;
  private boolean isVerbose = true;
  private byte replaceOption = ABORT;
  private byte noDirectoryOption = ABORT;

  private String nameOfWorkingDirectory;
  private File workingDirectory;


  /****************************************************************************
   *
   *
   ***************************************************************************/
  {
    osType = System.getProperty("os.name");
    if (osType.equals("Windows NT"))
      osType = "Windows";
    if (osType.equals("Windows 95"))
      osType = "Windows";
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  public FileCopier () {
    nameOfWorkingDirectory = System.getProperty("user.dir");
    workingDirectory = new File(nameOfWorkingDirectory);
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public FileCopier (String nameOfWorkingDirectory) {
    if (File.separatorChar == systemIndependentSeparator) {
      this.nameOfWorkingDirectory = nameOfWorkingDirectory;
      workingDirectory = new File(nameOfWorkingDirectory);
    } else {
      this.nameOfWorkingDirectory = 
	nameOfWorkingDirectory.replace
	(systemIndependentSeparator, File.separatorChar);
      workingDirectory = new File(this.nameOfWorkingDirectory);
    }
    if (!workingDirectory.exists() || !workingDirectory.isDirectory()) {
      this.nameOfWorkingDirectory = System.getProperty("user.dir");
      workingDirectory = new File(nameOfWorkingDirectory);
    }
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
  private void debugPrintln (String message) {
    if (isDebug) {
      System.err.println(message);
      System.err.flush();
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private static void println (String message) {
    System.out.println(message);
    System.out.flush();
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void handleSwitch(String switchString) {
    int i, len = switchString.length();
    char option;

    for (i=1; i<len; i++) {
      option = switchString.charAt(i);
      switch (option) {
      case 'f':
	replaceOption = OVERWRITE;
	break;
      case 'i':
	replaceOption = PROMPT;
	break;
      case 'v':
	isVerbose = true;
	break;
      case 'q':
	isVerbose = false;
	break;
      case 'c':
	noDirectoryOption = CREATE;
	break;
      default:
	error("unrecognized switch: " + switchString);
      }
    }
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  public File createFile(String systemIndependentFilename) {
    File returnValue;
    String filename = "";

    if (File.separatorChar == systemIndependentSeparator) {
      filename = systemIndependentFilename;
    } else {
      filename = systemIndependentFilename.replace
	(systemIndependentSeparator, File.separatorChar);
    }
    returnValue = new File(filename);
    if (returnValue.isAbsolute()) {
      return returnValue;
    } else {
      return new File(workingDirectory, filename);
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public String getRelativeParent(String filename) {
    File temp;

    if (File.separatorChar == systemIndependentSeparator) {
      temp = new File(filename);
    } else {
      temp = new File (filename.replace
		       (systemIndependentSeparator, File.separatorChar));
    }
    return temp.getParent();
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public void copy (String srcFileName, String destDirOrFileName) {
    copy(createFile(srcFileName), createFile(destDirOrFileName));
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public void copy (String srcDirName, String filename,
		    String destDirOrFileName) {
    copy(createFile(srcDirName + filename), createFile(destDirOrFileName));
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public void copy (File srcFile, File destDirOrFile) {
    if (destDirOrFile.isDirectory()) {
      copyIntoDirectory(srcFile, destDirOrFile);
    } else {
      copyToFile(srcFile, destDirOrFile);
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public void copyIntoDirectory (File srcFile, File destDir) {
    String destDirName = destDir.getAbsolutePath();

    if (destDirName.charAt(destDirName.length() - 1) == 
	File.separatorChar) {
      copyToFile(srcFile, createFile(destDirName + srcFile.getName()));
    } else {
      copyToFile(srcFile, createFile(destDirName + File.separator + 
				   srcFile.getName()));
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public void copyToFile(File srcFile, File destFile) {
    Reader reader;
    Writer writer;

    reader = createReader(srcFile);
    if (reader == null)
      return;

    writer = createWriter(destFile);
    if (writer == null)
      return;

    if (isVerbose) {
      println("Copying " + srcFile.getAbsolutePath()
	      + " to " + destFile.getAbsolutePath());
    }
    copyWithoutErrorChecking(reader, writer);
  }



  /****************************************************************************
   *
   *
   ***************************************************************************/
  public void oldCopy (String[] args) {
    int len, argIndex = 0;
    File destDir;

    len = args.length - 1;

    destDir = createFile(args[len]);
    if ((destDir.exists()) && (destDir.isFile())) {
      error("when moving multiple files, last argument, " +
	    destDir + " must be a directory.");
      return;
    }


    while ((argIndex<len) && (args[argIndex].charAt(0) == '-')) {
      handleSwitch(args[argIndex]);
      argIndex++;
    }
    if ((len - argIndex) < 1) {
      usage();
      return;
    }

    if ((noDirectoryOption != CREATE) && (!destDir.exists())) {
      error("when moving multiple files, last argument, " +
	    destDir + " must be a directory.");
      return;
    }

    for ( ; argIndex<len; argIndex++) {
      copyIntoDirectory(createFile(args[argIndex]), destDir);
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public void copy (String[] args) {
    int len, filesToCopy, argIndex = 0;
    File destDir;

    len = args.length - 1;
    destDir = createFile(args[len]);

    while ((argIndex<len) && (args[argIndex].charAt(0) == '-')) {
      handleSwitch(args[argIndex]);
      argIndex++;
    }
    filesToCopy = len - argIndex;
    if (filesToCopy < 1) {
      usage();
      return;
    }
    
    // For args like "cp -r -f -q hello.txt goodbye.txt", the last argument
    // actually does NOT need to be a directory.  That's why this is a 
    // special case.
    if (filesToCopy == 1) {
      copy(createFile(args[argIndex]), destDir);
      return;
    }
    
    if ((destDir.exists()) && (destDir.isFile())) {
      error("when moving multiple files, last argument, " +
	    destDir + " must be a directory.  It cannot " +
	    "be a regular file");
      return;
    }

    if ((noDirectoryOption != CREATE) && (!destDir.exists())) {
      error("when moving multiple files, last argument, " +
	    destDir + " must be an existent directory.");
      return;
    }

    for ( ; argIndex<len; argIndex++) {
      copy(createFile(args[argIndex]), destDir);
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public void copyPath (String srcName, File destDir) {
    File srcFile, fullDestDir;
    String subPath;
    String destDirName = destDir.getAbsolutePath();

    subPath = getRelativeParent(srcName);
    srcFile = createFile(srcName);

    if (subPath == null) {
      fullDestDir = createFile(destDirName);
    } else if (destDirName.charAt(destDirName.length() - 1) == File.separatorChar) {
      fullDestDir = createFile(destDirName + subPath);
    } else {
      fullDestDir = createFile(destDirName + File.separator + subPath);
    }
    if (!fullDestDir.exists()) {
      boolean directoriesCreated;
      directoriesCreated = fullDestDir.mkdirs();
      if (directoriesCreated) {
	copyIntoDirectory(srcFile, fullDestDir);
      } else {
	error("Unable to create directory " + fullDestDir);
      }
    } else {
	copyIntoDirectory(srcFile, fullDestDir);
    }
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  public void copyPaths (String[] args) {
    int len, filesToCopy, argIndex = 0;
    File destDir;

    len = args.length - 1;
    destDir = createFile(args[len]);

    while ((argIndex<len) && (args[argIndex].charAt(0) == '-')) {
      handleSwitch(args[argIndex]);
      argIndex++;
    }
    filesToCopy = len - argIndex;
    if (filesToCopy < 1) {
      usage();
      return;
    }
    
    if ((destDir.exists()) && (destDir.isFile())) {
      error("when moving file trees, last argument, " +
	    destDir + " must be a directory.  It cannot " +
	    "be a regular file");
      return;
    }

    for ( ; argIndex<len; argIndex++) {
      copyPath(args[argIndex], destDir);
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private Reader createReader(File file) {
    InputStream iStream;
    String fullSrcName;
    Reader reader = null;

    if (!file.exists()) {
      error("the file to be copied, " +
	    file.getAbsolutePath() + ", does not exist");
      return null;
    }

    if (file.isDirectory()) {
      error("the file to be copied, " +
	    file.getAbsolutePath() + ", is a directory");
      return null;
    }

    try {
      iStream = new BufferedInputStream(new FileInputStream(file));
      if (iStream == null) {
	error("could not create input stream");
	return null;
      }
      reader = new BufferedReader(new InputStreamReader(iStream));
      if (reader == null) {
	error("could not create reader");
	return null;
      }
    } catch (FileNotFoundException e) {
      error("FileNotFoundException" + e.getMessage());
      reader = null;
    } finally {
      return reader;
    }
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private Writer createWriter(File file) {
    OutputStream oStream;
    Writer writer;
    File containingDirectory;

    if ((replaceOption != OVERWRITE) && (file.exists())) {
      switch (replaceOption) {
      case ABORT:
	error("the file to be created, " +
	      file.getAbsolutePath() + ", already exists");
	return null;
      case PROMPT:
	error("the file to be created, " +
	      file.getAbsolutePath() + ", already exists");
	return null;
      case RENAME:
	error("the file to be created, " +
	      file.getAbsolutePath() + ", already exists");
	return null;
      }
    }

    containingDirectory = createFile(file.getParent());
    if (!containingDirectory.exists()) {
      if (noDirectoryOption == CREATE) {
	boolean directoryExists = 
	  containingDirectory.mkdirs();
	if (!directoryExists) {
	  error("could not create directory " +
		containingDirectory.getAbsolutePath());
	  return null;
	}
      } else {
	error(containingDirectory.getAbsolutePath()
	      + " does not exist");
	return null;
      }
    }

    if (!containingDirectory.isDirectory()) {
      error(containingDirectory.getAbsolutePath()
	    + " is not a directory");
      return null;
    }

    try {
      oStream = new BufferedOutputStream(new FileOutputStream(file));
      if (oStream == null) {
	error("could not create output stream");
	return null;
      }
      writer = new BufferedWriter(new OutputStreamWriter(oStream));
      if (writer == null) {
	error("could not create writer for file " + file);
	return null;
      }
      return writer;
    } catch (IOException io) {
      error("could not create writer for file " + file + "(IO Exception)");
      return null;
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void copyWithoutErrorChecking(Reader reader, 
					Writer writer) {
    try {
      int c;

      c = reader.read();
      while (c != -1) {
	writer.write(c);
	c = reader.read();
      }
      reader.close();
      writer.close();
    } catch (IOException io) {
      error("copy: I/O Exception");
      return;
    }
  }



  /****************************************************************************
   *
   *
   ***************************************************************************/
  private static void makeBackupForHome() {
    File nonexistentFile, renameFile;

    nonexistentFile = new File("ab\\cd\\ef\\ghi.txt");
    renameFile = new File("ab\\cd\\ef\\duh.txt");
    println("File = " + nonexistentFile);

    println("exists = " + nonexistentFile.exists());
    println("canRead = " + nonexistentFile.canRead());
    println("canWrite = " + nonexistentFile.canWrite());
    println("isAbsolute = " + nonexistentFile.isAbsolute());
    println("isDirectory = " + nonexistentFile.isDirectory());
    println("isFile = " + nonexistentFile.isFile());

    println("lastModified = " + nonexistentFile.lastModified());
    println("length = " + nonexistentFile.length());
    println("list = " + nonexistentFile.list());

    println("hashCode = " + nonexistentFile.hashCode());

    println("getParent = " + nonexistentFile.getParent());
    println("getName = " + nonexistentFile.getName());
    println("toString = " + nonexistentFile.toString());
    println("getPath = " + nonexistentFile.getPath());
    println("getAbsolutePath = " + nonexistentFile.getAbsolutePath());
    try {
      println("getCanonicalPath = " + nonexistentFile.getCanonicalPath());
    } catch (IOException e) {
      println("Could not obtain canonical path");
    }

    println("mkdir = " + nonexistentFile.mkdir());
    println("mkdirs = " + nonexistentFile.mkdirs());
    println("delete = " + nonexistentFile.delete());
    println("renameTo = " + nonexistentFile.renameTo(renameFile));

    // println("list = " + nonexistentFile.list(FilenameFilter));
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private static void usage () {
    println("Usage: java " + myName + " <srcfile> <destfile>");
    println("      e.g.: java " + myName + " " +
	    File.separator + "gensym" + File.separator + "tw.exe " +
	    File.separator + "telewindows" + File.separator + "tw.exe ");
    println("        or: java " + myName + " " +
	    "gensym" + File.separator + "tw.exe " +
	    "telewindows" + File.separator + "tw.exe ");
    if ((osType != null) && (osType.equals("Windows")))
      println("        or: java " + myName + " c:\\gensym\\tw.exe a:\\tw.exe");

    println("   or: java " + myName + " <srcfiles> <destdir>");
    println("      e.g.: java " + myName + " " +
	    File.separator + "gensym" + File.separator + "tw.exe " +
	    File.separator + "telewindows");
    println("        or: java " + myName + " " +
	    "gensym" + File.separator + "tw.exe " +
	    "telewindows" + File.separator);
    if ((osType != null) && (osType.equals("Windows")))
      println("        or: java " + myName + " c:\\gensym\\tw.exe a:\\");
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public static void main (String[] args) {
    FileCopier f;

    f = new FileCopier();
    if (args.length > 1) {
      f.copy(args);
    } else {
      usage();
    }
  }
}
