
package com.gensym.devtools;

import java.io.*;
import java.util.*;

import com.gensym.core.GensymApplication;
import com.gensym.core.DebugUtil;
import com.gensym.message.Trace;
import com.gensym.core.CmdLineArgHandler;

/**
 ** This used to use the compiler from tools.jar:
 ** compiler = new sun.tools.javac.Main(System.err, "javac");
 ** However, this caused spurious compile errors starting in jdk 1.3 so we switched over
 ** to calling Runtime.exec(.."javac"...)
 */
public class JavaMake extends GensymApplication
{
  private String [] javaArgs;
  private String srcBox, dstBox, classpath;
  private boolean useCommandLineOnly = false;
  private boolean forcedCompile = false;
  private boolean verbose = false;
  private boolean quiet = false;
  private boolean dryrun = false;
  private boolean requirePackageInfo = true;
  private File rootDir;
  private File currentWorkingDirectory;
  private long maximumSizeOfSumOfSourceFiles = 200000;
  private int callsToList = 0;
  private Vector compileProducts;
  private Exec runtime; // bbush, Aug 3, 2000

  private static final int readEOFChar = -1;
  private static final int newlineBeginning = 13;
  private static final int newlineCompletion = 10;

  private static final String compilationInstructionsFileName = "package.info";
  private static final String excludeFromCompileString = "exclude-from-compile:";
  private static final String includeInModuleString = "include-in-module:";


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private JavaMake (String[] argv) {
    super(argv);
    srcBox = getSrcBox();
    dstBox = getDstBox();
    rootDir = getRootDir();
    classpath = srcBox + File.separator + "java";
    verbose = commandLineArguments.getSwitchValue("-verbose");
    quiet = commandLineArguments.getSwitchValue("-quiet");
    dryrun = commandLineArguments.getSwitchValue ("-dryrun");
    forcedCompile = commandLineArguments.getSwitchValue ("-forceCompile");
    requirePackageInfo = !commandLineArguments.getSwitchValue ("-all");
    runtime = new Exec();  // bbush, Aug 3, 2000
    
    if (verbose) {
      println("SrcBox = " + srcBox);
      println("DstBox = " + dstBox);
      println("Root = " + rootDir);
    }

    String oldClasspath = System.getProperty("java.class.path");
    if ((oldClasspath != null) && (!oldClasspath.equals(""))) {
      classpath += (File.pathSeparator + oldClasspath);
    }
    javaArgs = new String[] { "javac", "-J-mx" + memorySize, "-classpath", classpath };
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  public JavaMake () {
    this(new String[0]);
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
  private void warn (String message) {
    if (verbose) {
      System.err.println("Warning: " + message);
      System.err.flush();
    }
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void println (String message) {
    System.out.println(message);
    System.out.flush();
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private String getSrcBox () {
    String obtainedSrcBox = null;

    obtainedSrcBox = commandLineArguments.getOptionValue("-srcbox");
    if (obtainedSrcBox != null) {
      useCommandLineOnly = true;
      return obtainedSrcBox;
    }
    obtainedSrcBox = System.getProperty("com.gensym.jmake.srcbox");
    if (obtainedSrcBox != null) {
      return obtainedSrcBox;
    }
    if (obtainedSrcBox != null) {
      return obtainedSrcBox;
    }
    warn("Unable to obtain SRCBOX from command line or System properties.\n");
    return "d:\\bt\\jv-ab";
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private String getDstBox () {
    String obtainedDstBox = null;

    obtainedDstBox = commandLineArguments.getOptionValue("-dstbox");
    if (obtainedDstBox != null) {
      useCommandLineOnly = true;
      return obtainedDstBox;
    }
    if (useCommandLineOnly) {
      return srcBox;
    }
    obtainedDstBox = System.getProperty("com.gensym.jmake.dstbox");
    if (obtainedDstBox != null) {
      return obtainedDstBox;
    }
    return srcBox;
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private File getRootDir () {
    String obtainedRootDir = null;
    File rootDirFile = null;

    obtainedRootDir = commandLineArguments.getOptionValue("-root");
    if (obtainedRootDir == null) {
      obtainedRootDir = commandLineArguments.getOptionValue("-localroot");
      if (obtainedRootDir != null) {
	obtainedRootDir = srcBox + File.separator + obtainedRootDir;
      }
    }
    if ((obtainedRootDir == null) && (!useCommandLineOnly)) {
      obtainedRootDir = System.getProperty("com.gensym.jmake.rootdir");
    }
    if (obtainedRootDir == null) {
      obtainedRootDir = System.getProperty("user.dir");
    }
    rootDirFile = new File(obtainedRootDir);
    // Insert validation here.
    return rootDirFile;
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private boolean changeDirectory (String newDirectoryName) {
    File newDirectory;

    newDirectory = new File(newDirectoryName);
    if (newDirectory.isDirectory()) {
      currentWorkingDirectory = newDirectory;
      return true;
    }
    return false;
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private String [] makeCommandLine(Vector files) {
    int length = javaArgs.length + files.size();
    String [] filesAndCommand = new String[length];
    for(int looper = 0; looper < length; looper++) {
      if(looper < javaArgs.length) {
	filesAndCommand[looper] = javaArgs[looper];
      } else {
	Object obj = files.elementAt(looper-javaArgs.length);
	if(obj instanceof File) {
	  filesAndCommand[looper] = ((File)obj).getPath();
	} else if(obj instanceof String) {
	  filesAndCommand[looper] = (String) obj;
	} else {
	  throw new IllegalArgumentException("Vector must contain either Files or Strings " + files);
	}	     
      }
    }
    return filesAndCommand;
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private boolean compileJavaFiles (Vector filesToBeCompiled) {
    String[] filesAsStrings;
    int i;
    int numArgs = 3;
    boolean result = true;

    if (filesToBeCompiled.size() <= 0) {
      return true;
    }
    
    for (i=0; i < filesToBeCompiled.size(); i++) {
      if (!quiet)
        println("javac " + filesToBeCompiled.elementAt(i));
    }
    if (dryrun)
      return true;
    try {
      runtime.exec(makeCommandLine(filesToBeCompiled), new PrintWriter(System.out, true));
    } catch (Throwable t) {
      System.err.println("---Compile Errors---");
      for (i=0; i< filesToBeCompiled.size(); i++) {
        File file = (File) filesToBeCompiled.elementAt(i);
        // Don't want to check needsToBeCompiled again, because
        // was check on each file in argument vector and needsToBeCompiled does not
        // accurately say whether secondary classes defined in a given file were finished
        // compiling.
        if (needsToBeCompiled (file)) {
          Vector currentFile = new Vector();
          currentFile.addElement(file);
          try {
            println("recompiling (due to errors in group) "+file);
            runtime.exec(makeCommandLine(currentFile), new PrintWriter(System.out, true));
          } catch (Throwable t2) {
            System.err.println("\tFailed: " + "->" + file);
            result = false;
          }
        }
      }
    }
    return result;
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private boolean member (String key, String[] list) {
    int i=0;
    int length;

    if (list == null) return false;
    length = list.length;
    while (i < length) {
      if (key.equals(list[i++])) return true;
    }
    return false;
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private String[] turnVectorIntoArray (Vector theVector) {
    String[] theArray;
    int i;

    if (theVector.size() <= 0) {
      return new String[0];
    }
    theArray = new String[theVector.size()];
    for (i=0; i<theVector.size(); i++) {
      theArray[i] = (String) theVector.elementAt(i);
    }
    return theArray;
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private boolean isExcludeFromCompileLine (String line) {
    if (line.length() > 21) {
      return excludeFromCompileString.equals(line.substring(0, 21));
    } else {
      return false;
    }
  }


  private boolean isIncludeInModuleLine (String line) {
    if (line.length() > 18)
      return includeInModuleString.equals (line.substring(0, 18));
    else
      return false;
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private String[] getExcludedFilesInDirectory (File directory) {
    Vector excludedFiles = new Vector(10);
    GensymFileReader reader;
    String directoryPath, nextLine, filename;
    StringTokenizer wordGetter;

    directoryPath = directory.getPath();
    reader = GensymFileReader.makeGensymFileReader(directoryPath + 
						   File.separator +
						   compilationInstructionsFileName);
    if (reader == null) {
      if (requirePackageInfo) {
	warn("Skipping Package: " + directoryPath + ".  No Package Info.");
	return null;
      } else {
	warn("No package.info for " + directoryPath);
	return new String[0];
      }
    }
    do {
      nextLine = reader.readLine();
      if (isExcludeFromCompileLine(nextLine)) {
	wordGetter = new StringTokenizer(nextLine);
	filename = wordGetter.nextToken();
	while (wordGetter.hasMoreTokens()) {
	  filename = wordGetter.nextToken();
	  excludedFiles.addElement(filename);
	}
      }
    } while (nextLine != "");
    reader.close();
    
    return turnVectorIntoArray(excludedFiles);
  }


  private String[] getModulesOwningDirectory (File directory) {
    Vector owningModules = new Vector (1);
    GensymFileReader reader;
    String directoryPath, nextLine, filename;
    StringTokenizer wordGetter;
    String moduleName = null;

    directoryPath = directory.getPath();
    reader = GensymFileReader.makeGensymFileReader(directoryPath + 
						   File.separator +
						   compilationInstructionsFileName);
    if (reader == null) {
      if (requirePackageInfo) {
	warn("Skipping Package: " + directoryPath + ".  No Package Info.");
	return null;
      } else {
	warn("No package.info for " + directoryPath);
	return null;
      }
    }
    do {
      nextLine = reader.readLine();
      if (isIncludeInModuleLine(nextLine)) {
	wordGetter = new StringTokenizer(nextLine);
	filename = wordGetter.nextToken();
	while (wordGetter.hasMoreTokens()) {
	  moduleName = wordGetter.nextToken();
	  owningModules.addElement (moduleName);
	}
      }
    } while (nextLine != "");
    reader.close();
    
    return turnVectorIntoArray(owningModules);
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private boolean needsToBeCompiled (File file) {
    // This does not handle files that define multiple classes correctly 
    int length, nameLength;
    String fileName, lastFive, basename, className;
    File classFile;

    if (!file.exists()) {
      error("Error: " + file + " does not exist.");
      return false;
    }
    fileName = file.getName();
    length = fileName.length();
    if (length <= 5) 
      return false;
    nameLength = length - 5;
    if (!fileName.endsWith(".java"))
      return false;
    basename = fileName.substring(0, nameLength);
    classFile = new File(file.getParent() + File.separator +
			 basename + ".class");
    if (!classFile.exists()) return true;
    if (classFile.lastModified() <= file.lastModified()) return true;
    // find all secondary class def's in the .java file and check them too!
    try {
      Vector otherClassNames = findOtherClassNames(file,basename);
      if ((otherClassNames.size() > 0) && !quiet)
        System.out.println("other class names for "+basename+" are "+otherClassNames);
      int i,len = otherClassNames.size();
      for (i=0; i<len; i++)
	{
	  File otherClassName =  new File(file.getParent() + File.separator +
					  ((String)otherClassNames.elementAt(i)) + ".class");
	  if (!otherClassName.exists()) {
	    otherClassName =  new File(file.getParent() + File.separator +
				       basename + "$" + ((String)otherClassNames.elementAt(i)) + ".class");
	    if (!otherClassName.exists() || otherClassName.lastModified() <= file.lastModified()) {
	      return true;
	    } else
	      return false;
	  }

	  if (otherClassName.lastModified() <= file.lastModified())
	    return true;
	}
      return false;
    } catch (IOException e)
      {
	e.printStackTrace();
	return true;
      }
  }

  private static final int LINE_START = 1;
  private static final int LINE_C = 2;
  private static final int LINE_L = 3;
  private static final int LINE_A = 4;
  private static final int LINE_S1 = 5;
  private static final int LINE_S2 = 6;
  private static final int LINE_SPACE = 7;
  private static final int LINE_CLASS_NAME = 8;
  private static final int EXIT = 9;

  private Vector findOtherClassNames(File file, String basename)
       throws IOException
  {
    BufferedReader in = new BufferedReader(new FileReader(file));
    String line;
    Vector names = new Vector();
    while ((line = in.readLine()) != null)
      {
	char[] chars = line.toCharArray();
	int i,len = chars.length;
	int identifierStart = -1;
	int identifierLength = -1;
	int state = LINE_START;
	for (i=0; i<len; i++)
	  {
	    if (state == EXIT)
	      break;
	    char ch = chars[i];
	    switch (state)
	      {
	      case LINE_START:
		if (!Character.isWhitespace(ch))
		  {
		    if (ch == 'c')
		      state = LINE_C;
		    else
		      state = EXIT;
		  }
		break;
	      case LINE_C:
		if (ch == 'l')
		  state = LINE_L;
		else
		  state = EXIT;
		break;
	      case LINE_L:
		if (ch == 'a')
		  state = LINE_A;
		else
		  state = EXIT;
		break;
	      case LINE_A:
		if (ch == 's')
		  state = LINE_S1;
		else
		  state = EXIT;
		break;
	      case LINE_S1:
		if (ch == 's')
		  state = LINE_S2;
		else
		  state = EXIT;
		break;
	      case LINE_S2:
		if (Character.isWhitespace(ch))
		  state = LINE_SPACE;
		else
		  state = EXIT;
		break;
	      case LINE_SPACE:
		if (Character.isJavaIdentifierStart(ch))
		  {
		    identifierStart = i;
		    state = LINE_CLASS_NAME;
		  }
		break;
	      case LINE_CLASS_NAME:
		if (!Character.isJavaIdentifierPart(ch))
		  {
		    identifierLength = i-identifierStart;
		    state = EXIT;
		  }
		break;
	      }
	    if (identifierLength != -1)
	      {
		String className = new String(chars,identifierStart,identifierLength);
		if (!className.equals(basename))
		  names.addElement(className);
	      }
	  }
      }
    return names;
  }

  /****************************************************************************
   * There seems to be a problem on Solaris that after doing a number of
   * directories, dirname.list() starts to fail (return null).  I'm reversing
   * the order here just to verify that it is not a problem with a particular 
   * directory, but a problem of quitting somewhere in the middle.
   ***************************************************************************/
  private String[] listFilesInDirectory (File localRoot) {
    String[] original = null;
    String[] reversed;
    int len, i;

    if (!localRoot.isDirectory()) {
      error(localRoot + " is not a directory");
      return null;
    }
    
    if (localRoot.getName().equals("CVS")) {
      warn("Not doing CVS directories.");
      return null;
    }

    try {
      callsToList++;
      original = localRoot.list();
    } catch (Throwable e) {
      error("throwable while making list: " + e);
    }
    if (original == null) {
      warn("" + callsToList +
	   ". Unable to find any files below " + localRoot);
      System.err.println("ls " + localRoot + " = " + original);
      System.err.flush();
      return null;
    }

    len = original.length;
    if (len == 0) return null;
      
    reversed = new String[len];
    for (i=0; i<len; i++) {
      reversed[i] = original[i];
      // len - i - 1
    }
    return reversed;
  }


  /****************************************************************************
   *
   * Note: If getExcludedFilesInDirectory() returns null, that means that it 
   * couldn't read the package information.  If there simply were no excluded
   * files, it returns a zero-length array.
   ***************************************************************************/
  private void compileJavaFilesBelow (File localRoot) {
    String[] files;

    String[] owningModules = getModulesOwningDirectory (localRoot);
    boolean needToCompile = forcedCompile;
    if (owningModules != null) {
      for (int i=0; i<owningModules.length; i++) {
	//System.out.println (com.gensym.core.DebugUtil.printArray (owningModules));
	if (compileProducts == null ||
	    compileProducts.indexOf (owningModules[i]) >= 0) {
	  needToCompile = true;
	  break;
	}
      }
      if (!needToCompile) {
	warn ("Skipping " + localRoot + " because it belongs to extraneous modules :" +
	      owningModules);
	warn ("Currently compiling only -> " + compileProducts);
      }
    } else {
      needToCompile = !requirePackageInfo;
    }

    files = listFilesInDirectory(localRoot);
    if ((files != null) && (files.length > 0)) {
      String[] excludedFiles;
      File subfile;
      String directoryPath;
      Vector filesToBeCompiled = new Vector(10);
      int i, sizeOfSourceCode = 0;

      excludedFiles = getExcludedFilesInDirectory(localRoot);
      for (i=0; i<files.length; i++) {
	subfile = new File(localRoot.getPath() + File.separator + files[i]);
	if (subfile.isDirectory()) {
	  compileJavaFilesBelow(subfile);
	  continue;
	}
	if (excludedFiles != null) {
	  if (member(files[i], excludedFiles)) {
	    warn("Skipping " + localRoot + File.separator + files[i]);
	    continue;
	  }
	}
	if (needToCompile && needsToBeCompiled(subfile)) {
	  filesToBeCompiled.addElement(subfile);
	  if (verbose)
	    println("Adding " + subfile + " to the list");
	  sizeOfSourceCode += subfile.length();
	  if (sizeOfSourceCode > maximumSizeOfSumOfSourceFiles) {
	    compileJavaFiles(filesToBeCompiled);
	    filesToBeCompiled = new Vector(10);
	    sizeOfSourceCode = 0;
	  }
	}
	else if (verbose && needToCompile)
	  println("Not Adding "+subfile);
      }
      compileJavaFiles(filesToBeCompiled);
    }
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void removeFilesOfSuffix (String[] arguments) {
    removeFilesOfSuffix(arguments, false);
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void removeFilesOfSuffix (String[] arguments, 
				    boolean recurseSubdirectories) {
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void cleanJavaFiles () {
    changeDirectory(dstBox + File.separator + "java" + File.separator + "o");
    removeFilesOfSuffix(new String[] {"obj", "c", "h", "RES", "exe"});
    changeDirectory(dstBox + File.separator + "java" + File.separator + "lib");
    removeFilesOfSuffix(new String[] {"dll", "exp", "ilk", "lib", "pdb"});
    changeDirectory(dstBox + File.separator + "java");
    removeFilesOfSuffix(new String[] {"class"}, true);
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  void compileJavaFilesInSandbox (String productName) {
    determineModulesForCompile (productName);
    if (rootDir.isDirectory()) {
      compileJavaFilesBelow(rootDir);
    } else {
      error("root directory, " + rootDir +
	    ", does not exist or is not a directory");
    }
  }

  void determineModulesForCompile (String productName) {
    if (productName == null)
      return;
    String btroot =
      System.getProperty ("com.gensym.devtools.JavaMake.devTreeRoot", null);
    btroot = srcBox + File.separator + "java";
    if (btroot == null)
      return;
    String productDepFile =
      btroot + File.separator +
      "com"  + File.separator +
      "gensym" + File.separator +
      "build"  + File.separator +
      "product-dependencies.dat";
    Properties props;
    try {
      FileInputStream propStream =
	new FileInputStream (productDepFile);
      props = new Properties ();
      props.load (propStream);
      propStream.close ();
    } catch (IOException ioe) {
      System.err.println (ioe);
      Trace.exception (ioe);
      return;
    }
    compileProducts = new Vector ();
    compileProducts.addElement (productName);
    int j=0;
    do {
      String currentProduct = (String)compileProducts.elementAt (j++);
      Vector reqProducts =
	getRequiredProducts (props.getProperty (currentProduct));
      if (reqProducts != null) {
	for (int i=0; i<reqProducts.size(); i++) {
	  String reqProduct = (String)reqProducts.elementAt (i);
	  if (compileProducts.indexOf (reqProduct) < 0)
	    compileProducts.addElement (reqProduct);
	}
      }
    } while (j<compileProducts.size());
  }

  Vector getRequiredProducts (String reqProductsString) {
    Vector products = new Vector ();
    if (reqProductsString != null) {
      StringTokenizer stknzr = new StringTokenizer (reqProductsString);
      while (stknzr.hasMoreElements())
	products.addElement (stknzr.nextElement ());
    }
    return products;
  }

  private void printUsageAndExit () {
    String Usage = "Usage: java com.gensym.devtools.JavaMake <options>\n" +
      "where <options> include:\n\n";
    Usage += "-help               Print this help summary\n";
    Usage += "-?                  Print this help summary\n";
    Usage += "-root               Directory to start compile in. Will traverse hierarchy under it\n";
    Usage += "-product            Name of product to compile. Will compile required products\n";
    Usage += "-quiet              Be more quiet\n";
    Usage += "-verbose            Be more chatty\n";
    Usage += "-dryrun             Show compile commands that will run but do not execute them\n";
    Usage += "-forceCompile       Will compile all files in all directories under root\n";
    Usage += "-localroot          Java package heirarchy in directories\n";
    Usage += "-srcBox             Specifies root of sandbox for getting info about products\n";
    Usage += "-dstBox             Specifies root of sandbox for emitting compiled classes\n";
    System.out.println ("\n" + Usage);
    System.exit (0);
  }


  static String memorySize = "100m";

  /****************************************************************************
   *
   *
   ***************************************************************************/
  public static void main (String[] argv) {
    JavaMake invocation = new JavaMake(argv);
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (argv);
    String productName = cmdLine.getOptionValue ("-product");
    boolean needsHelp = cmdLine.getSwitchValue ("-help");
    boolean quiet = cmdLine.getSwitchValue ("-quiet");
    memorySize = cmdLine.getOptionValue("-memory");
    if (!needsHelp)
      needsHelp = cmdLine.getSwitchValue ("-?");
    if (needsHelp)
      invocation.printUsageAndExit ();
    else {
      if (!quiet)
        System.out.println("Beginning at " + new Date() + "\n");
      invocation.compileJavaFilesInSandbox(productName);
      if (!quiet)
        System.out.println("\nFinished at " + new Date());
      System.out.flush();
    }
  }
}


