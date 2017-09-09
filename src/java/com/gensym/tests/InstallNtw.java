/* InstallNtw.java
 * Copyright (C) 1986-2017 Gensym Corporation.
 * 
 * This class is intentionally in the default package so that the
 * user will need to enter the installation directory to run it
 * and we can then be sure to get the installation directory with
 * the property "user.dir".
 */


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
import java.util.zip.Inflater;
import java.util.zip.ZipInputStream;

public class InstallNtw {

  private static final byte ZIP = InstallationOption.ZIP;
  private static final byte DLL = InstallationOption.DLL;
  private static final byte TXT = InstallationOption.TXT;

  private static final byte COPY = InstallationOption.COPY;
  private static final byte UNZIP = InstallationOption.UNZIP;
  private static final byte SED = InstallationOption.SED;

  private static final byte ANY_OS = InstallationOption.ANY_OS;
  private static final byte UNIX = InstallationOption.UNIX;
  private static final byte WINDOWS = InstallationOption.WINDOWS;

  private static final String myName = "InstallNtw";
  private static boolean debugP = false;
  private static String osType;


  /*************************************************************
   *
   *
   ************************************************************/
  private static String[] copyToLibSubdir = { "lib" };
  private static String[] propertiesSedOptions = null;

  private static InstallationOption[] options = {
    new InstallationOption("properties",      TXT,   SED,  ANY_OS, propertiesSedOptions),
    new InstallationOption("gdoc",            ZIP,  COPY,  ANY_OS, null),
    new InstallationOption("resources",       ZIP,  COPY,  ANY_OS, null),
    new InstallationOption("gclasses",        ZIP,  COPY,  ANY_OS, null),
    new InstallationOption("gdoc",            ZIP, UNZIP,  ANY_OS, null),
    new InstallationOption("resources",       ZIP, UNZIP,  ANY_OS, null),
    new InstallationOption("gclasses",        ZIP, UNZIP,  ANY_OS, null),
    new InstallationOption("libJgiInterface", DLL,  COPY,  ANY_OS, copyToLibSubdir),
    new InstallationOption("JavaContainer",   DLL,  COPY, WINDOWS, copyToLibSubdir)
  };


  /*************************************************************
   *
   *
   ************************************************************/
  {
    osType = System.getProperty("os.name");
    if (osType.equals("Windows NT"))
      osType = "Windows";
    if (osType.equals("Windows 95"))
      osType = "Windows";
  }

  /*************************************************************
   *
   *
   ************************************************************/
  private static void println (String message) {
    System.out.println(message);
    System.out.flush();
  }

  /*************************************************************
   *
   *
   ************************************************************/
  private static void debugPrintln (String message) {
    if (debugP) {
      System.err.println(message);
      System.err.flush();
    }
  }

  /*************************************************************
   *
   *
   ************************************************************/
  private static void usage () {
    String pathSeparator;

    println("Usage: java " + myName + " <installation-directory>");
    if (osType.equals("Windows"))
      println("    e.g.: java " + myName + " c:\\gensym");
    println("      or: java " + myName + "   " + File.separator + "gensym");
    println("      or: java " + myName + "    gensym");
  }


  /*************************************************************
   *
   *
   ************************************************************/
  private static File getOrMakeDirectory (String installDir) {
    File dir;

    dir = new File(installDir);
    if (!dir.exists()) {
      boolean success;

      println("The installation directory, " + installDir +
	      " does not exist.  Creating.");
      success = dir.mkdirs();
      if (success) {
	return dir;
      } else {
	return null;
      }
    } else if (!dir.isDirectory()) {
      println("ERROR: The requested installation directory, " + 
	      installDir + "is not actually a directory.");
      return null;
    } else {
      return dir;
    }
  }


  /*************************************************************
   *
   *
   ************************************************************/
  private static File getSrcDir () {
    File dir;
    String cwd;

    cwd = System.getProperty("user.dir");
    debugPrintln("cwd = " + cwd);
    dir = new File(cwd);
    return dir;
  }


  /*************************************************************
   *
   *
   ************************************************************/
  private static void informUserOfVariables (File destDir) {
  }


  /*************************************************************
   *
   *
   ************************************************************/
  private static void generateBatScript (File destDir) {
    println("");
    println("set PATH=%PATH%;lib;%JAVAHOME%\\bin");
    println("set CLASSPATH=%CLASSPATH%;%JAVAHOME%\\lib\\classes.zip;.");
    println("if NOT \"%HOME%\" == \"\" goto got_home");
    println("set HOME=C:\\");
    println("");
    println(":got_home");
    println("copy .com.gensym.properties %HOME%");
    println("java com.gensym.ntw.Telewindows");
  }


  /*************************************************************
   *
   *
   ************************************************************/
  private static void installNevada (String installDir) {
    File srcDir, destDir;
    InstallationOption currentOption;

    destDir = getOrMakeDirectory(installDir);
    if (destDir == null) {
      usage();
      return;
    }
    srcDir = getSrcDir();

    println("Beginning installation of sequoia-10a0...");
    for (int i=0; i<options.length; i++) {
      options[i].performOption(srcDir, destDir);
    }
    informUserOfVariables(destDir);
    generateBatScript(destDir);
  }

  /*************************************************************
   *
   *
   ************************************************************/
  public static void main (String[] args) {
    if (args.length == 1) {
      installNevada(args[0]);
    } else {
      usage();
    }
  }
}



/*************************************************************
 *  InstallationOption
 *
 ************************************************************/
class InstallationOption {
  static final byte ZIP = -1;
  static final byte DLL = -2;
  static final byte TXT = -3;

  static final byte COPY = 1;
  static final byte UNZIP = 2;
  static final byte SED = 3;

  static final byte ANY_OS = 64;
  static final byte UNIX = 65;
  static final byte WINDOWS = 66;


  private static byte osType;
  private static String unzipperName;

  private String baseName;
  private byte suffixType;
  private byte action;
  private byte requiredOS;
  private String[] actionOptions;
  

  /*************************************************************
   * constructor
   *
   ************************************************************/
  InstallationOption(String baseName, byte suffixType,
		     byte action, byte requiredOS,
		     String[] actionOptions) {
    this.baseName            = baseName;
    this.suffixType          = suffixType;
    this.action              = action;
    this.requiredOS          = requiredOS;
    this.actionOptions       = actionOptions;
  }

  /*************************************************************
   * static initializer
   *
   ************************************************************/
  {
    String osName;

    osName = System.getProperty("os.name");
    if (osName.equals("Windows NT"))
      osType = WINDOWS;
    else if (osName.equals("Windows 95"))
      osType = WINDOWS;
    else if (osName.equals("Solaris"))
      osType = UNIX;
    else {
      println("Error: could not acquire OS type.");
      println("  Assuming some kind of Unix");
      osType = UNIX;
    }
    if (osType == WINDOWS) {
      unzipperName = "C:\\Program Files\\WINZIP\\WINZIP32.EXE";
    } else {
      unzipperName = "/usr/local/bin/unzip";
    }
  }

  /*************************************************************
   *
   *
   ************************************************************/
  private static void println (String message) {
    System.out.println(message);
    System.out.flush();
  }


  /*************************************************************
   *
   *
   ************************************************************/
  private static Reader createReader(File file) {
    InputStream iStream;
    Reader reader;

    try {
      iStream = new BufferedInputStream(new FileInputStream(file));
      if (iStream == null) {
	println("ERROR: could not create input stream");
	return null;
      }
      reader = new BufferedReader(new InputStreamReader(iStream));
      if (reader == null) {
	println("ERROR: could not create reader");
	return null;
      }
      return reader;
    } catch (FileNotFoundException e) {
      println("ERROR: internal error in install program");
      return null;
      /*
    } catch (UnsupportedEncodingException e) {
      println("ERROR: unsupported encoding: none.   " + e.getMessage());
      return null;
    */
    }
  }

  /*************************************************************
   *
   *
   ************************************************************/
  private static Writer createWriter(File file) {
    OutputStream oStream;
    Writer writer;

    try {
      oStream = new BufferedOutputStream(new FileOutputStream(file));
      if (oStream == null) {
	println("ERROR: could not create output stream");
	return null;
      }
      writer = new BufferedWriter(new OutputStreamWriter(oStream));
      if (writer == null) {
	println("ERROR: could not create writer");
	return null;
      }
      return writer;
    } catch (IOException io) {
      println("ERROR: could not create writer");
      return null;
    }
  }


  /*************************************************************
   *
   *
   ************************************************************/
  private static void copyWithoutErrorChecking(Reader reader, 
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
      println("ERROR: copy: I/O Exception");
      return;
    }
  }



  /*************************************************************
   *
   *
   ************************************************************/
  private static void copy (File srcDir, String filename, File destDir, 
		    String relativeDestination) {
    String fullSrcName, fullDestName, fullDestDirName;
    File srcFile, destFile;
    Reader reader;
    Writer writer;

    /* Inconsistency: getAbsolutePath returns the drive letter
     * if it is given, or if a relative path is given, but if
     * given a full pathname without a drive letter (e.g.,
     * "\gensym"), it does not provide the drive letter.
     */
    try {
      fullSrcName = srcDir.getCanonicalPath() + File.separator + filename;
    } catch (IOException io) {
      println("Error: Could not get canonical path for " + srcDir);
      fullSrcName = srcDir.getAbsolutePath() + File.separator + filename;
    }

    try {
      fullDestDirName = destDir.getCanonicalPath();
    } catch (IOException io) {
      println("Error: Could not get canonical path for " + destDir);
      fullDestDirName = destDir.getAbsolutePath();
    }

    if (relativeDestination.length() > 0) {
      File fullDestDir;
      boolean success;

      fullDestDirName = fullDestDirName + File.separator +
	relativeDestination;
      fullDestDir = new File(fullDestDirName);
      if (!fullDestDir.exists()) {
	success = fullDestDir.mkdirs();
      }
    }
    fullDestName = fullDestDirName + File.separator + filename;

    srcFile = new File(fullSrcName);
    destFile = new File(fullDestName);

    if (destFile.exists()) {
      println("ERROR: copy: " + fullDestName + " already exists");
      return;
    }

    if (!srcFile.exists()) {
      println("ERROR: copy: " + fullSrcName + " does not exist");
      return;
    }

    reader = createReader(srcFile);
    writer = createWriter(destFile);
    if ((reader == null) || (writer == null))
      return;

    println("Copying " + fullSrcName + " to " + fullDestName);
    copyWithoutErrorChecking(reader, writer);
  }

  /*************************************************************
   *
   *
   ************************************************************/
  private static int checkForInstallDir(int i, int prev) {
    char c;

    c = (char) i;

    switch (prev) {
    case 0:
    case 8:
      if (c == 'I')
	return prev+1;
      else
	return 0;
    case 1:
      if (c == 'N')
	return 2;
      else
	return 0;
    case 2:
      if (c == 'S')
	return 3;
      else
	return 0;
    case 3:
      if (c == 'T')
	return 4;
      else
	return 0;
    case 4:
      if (c == 'A')
	return 5;
      else
	return 0;
    case 5:
    case 6:
      if (c == 'L')
	return prev+1;
      else
	return 0;
    case 7:
      if (c == 'D')
	return 8;
      else
	return 0;
    case 9:
      if (c == 'R')
	return 10;
      else
	return 0;
    default:
      System.out.println("Internal error in sed");
      return 0;
    }
  }

  /*************************************************************
   *
   *
   ************************************************************/
  private static void writeSubstitute (Writer writer,
				       String substitute) 
       throws IOException {
    int length, i, c;

    length = substitute.length();
    for (i=0; i<length; i++) {
      c = (int) substitute.charAt(i);
      writer.write(c);
    }
  }



  /*************************************************************
   *
   *
   ************************************************************/
  private static void sedWithoutErrorChecking(Reader reader, 
					      Writer writer,
					      String substitute) {
    int c;
    int buf[];
    int prev = 0, current = 0;

    buf = new int[10];
    try {
      c = reader.read();
      while (c != -1) {
	current = checkForInstallDir(c, prev);
	if (current == 0) {
	  if (prev == 0) {
	    writer.write(c);
	  } else {
	    for (int i=0; i<prev; i++)
	      writer.write(buf[i]);
	    prev = 0;
	  }
	} else if (current == 10) {
	  writeSubstitute(writer, substitute);
	  prev = 0;
	  current = 0;
	} else {
	  buf[current-1] = c;
	  prev = current;
	}
	c = reader.read();
	if ((osType == WINDOWS) && (c == ((int) '/'))) {
	  c = (int) '\\';
	}
      }
      reader.close();
      writer.close();
    } catch (IOException io) {
      println("ERROR: sed: I/O Exception");
      return;
    }
  }



  /*************************************************************
   *
   *
   ************************************************************/
  private static void sed (File srcDir, String filename, File destDir) {
    String fullSrcName, fullDestName, installationDirName;
    File srcFile, destFile;
    Reader reader;
    Writer writer;

    /* Inconsistency: 
     *  Assume working directory "d:\", contains directory "gensym":
     *    getAbsolutePath("gensym")    = "d:\gensym"
     *    getAbsolutePath("d:\gensym") = "d:\gensym"
     *    getAbsolutePath("\gensym")   = "\gensym"
     * Since we need to know the drive letter, try to use getCanonicalPath,
     * which can throw an IO Exception.  If that fails for some reason,
     * give it a shot with getAbsolutePath().
     */
    try {
      fullSrcName = srcDir.getCanonicalPath() + File.separator + filename;
    } catch (IOException io) {
      println("Error: Could not get canonical path for " + srcDir);
      fullSrcName = srcDir.getAbsolutePath() + File.separator + filename;
    }
    try {
      installationDirName = destDir.getCanonicalPath();
    } catch (IOException io) {
      println("Error: Could not get canonical path for " + destDir);
      installationDirName = destDir.getAbsolutePath();
    }
    fullDestName = installationDirName + File.separator + filename;

    srcFile = new File(fullSrcName);
    destFile = new File(fullDestName);

    if (destFile.exists()) {
      println("ERROR: sed: " + fullDestName + " already exists");
      return;
    }

    if (!srcFile.exists()) {
      println("ERROR: sed: " + fullSrcName + " does not exist");
      return;
    }

    reader = createReader(srcFile);
    writer = createWriter(destFile);
    if ((reader == null) || (writer == null))
      return;
    println("Copying " + fullSrcName + " to " + fullDestName);
    sedWithoutErrorChecking(reader, writer, installationDirName);
  }

  /*************************************************************
   *
    ZipInputStream zipInputStream;
    Inflater inflater;

    try {
      zipInputStream = new ZipInputStream(new FileInputStream(srcFile));
    } catch (FileNotFoundException e) {
      println("ERROR: could not read " + srcFile.getCanonicalPath());
      return;
    }
    inflater = new Inflater();
   *
   ************************************************************/
  static void unzip (File srcDir, String filename) {
    String fullSrcName, unzipCommand;
    File srcFile, unzipper;
    
    try {
      fullSrcName = srcDir.getCanonicalPath() + File.separator + filename;
    } catch (IOException io) {
      println("Error: Could not get canonical path for " + srcDir);
      fullSrcName = srcDir.getAbsolutePath() + File.separator + filename;
    }

    srcFile = new File(fullSrcName);
    if (!srcFile.exists()) {
      println("ERROR: unzip: " + fullSrcName + " does not exist");
      return;
    }

    unzipper = new File(unzipperName);
    if (unzipper.exists()) {
      println("\nUnzipping " + fullSrcName);
      unzipCommand = unzipperName + " " + fullSrcName;
      try {
	Runtime.getRuntime().exec(unzipCommand);
      } catch (IOException io) {
	println("ERROR: I/O Exception" + io);
	return;
      }
      println("Executed winzip");
    } else {
      println("Sorry, could not locate an appropriate unzip program.");
      println("You should unzip " + fullSrcName + " yourself.");
    }
  }

  /*************************************************************
   *
   *
   ************************************************************/
  static String getSuffix(byte suffixType) {
    switch (suffixType) {
    case ZIP:
      return "zip";
    case TXT:
      return "txt";
    case DLL:
      if (osType == WINDOWS)
	return "dll";
      else
	return "so";
    default:
      println("ERROR: Unknown suffix " + suffixType);
      return "";
    }
  }

  /*************************************************************
   *
   *
   ************************************************************/
  void performOption(File srcDir, File destDir) {
    String filename;

    filename = baseName + "." + getSuffix(suffixType);
    switch (action) {
    case COPY:
      if (actionOptions == null)
	copy(srcDir, filename, destDir, "");
      else
	copy(srcDir, filename, destDir, actionOptions[0]);
      break;
    case UNZIP:
      unzip(destDir, filename);
      break;
    case SED:
      sed(srcDir, filename, destDir);
      break;
    default:
      println("ERROR: Unknown action " + action);
    }      
  }
}

