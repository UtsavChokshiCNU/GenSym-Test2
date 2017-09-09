
package com.gensym.tests;

import java.io.File;
import java.util.Vector;

import com.gensym.core.GensymApplication;
import com.gensym.devtools.JavaMake;

public class RunmakeJNTW extends GensymApplication
{
  private final static int COMPILE_NOTHING    = 0;
  private final static int COMPILE_CLEAN      = 1;
  private final static int COMPILE_DEBUGGABLE = 2;
  private final static int COMPILE_OPTIMIZED  = 4;

  private sun.tools.javac.Main compiler;
  private int compileType = COMPILE_NOTHING;
  private String srcBox, dstBox, machine;
  private Vector filesToBeCompiled;
  private String jutilMakefileName, jgiMakefileName,
    jgiRMIMakefileName, ntwRMIMakefileName, comMakefileName;
  private File jutilMakefile, jgiMakefile, jgiRMIMakefile,
      ntwRMIMakefile, comMakefile, currentWorkingDirectory;


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private class MakefileNotFoundException extends Exception {
    MakefileNotFoundException (String badMakefile) {
      super(badMakefile);
    }
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private RunmakeJNTW (String[] argv) {
    super(argv);
    srcBox = "d:\\bt\\jv-ab";
    dstBox = "d:\\bt\\jv-ab";
    compiler = new sun.tools.javac.Main(System.err, "javac");
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
  private void error (String message) {
    System.err.println("ERROR: " + message);
    System.err.flush();
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private boolean parseCompileType (String compileType) {
    if (compileType.equals("opt")) {
      this.compileType |= COMPILE_OPTIMIZED;
      return true;
    }
    if (compileType.equals("o")) {
      this.compileType |= COMPILE_DEBUGGABLE;
      return true;
    } 
    if (compileType.equals("clean")) {
      this.compileType |= COMPILE_CLEAN;
      return true;
    }
    return false;
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
  private void setMakefiles (String compileString) {
    jutilMakefileName = srcBox + File.separator + "java" + File.separator +
      "mkfiles" + File.separator + machine + "-jutil";
    jgiMakefileName = srcBox + File.separator + "java" + File.separator +
      "mkfiles" + File.separator + machine + "-jgi-" + compileString;
    jgiRMIMakefileName = srcBox + File.separator + "java" + File.separator +
      "mkfiles" + File.separator + machine + "-jgi-rmi";
    ntwRMIMakefileName = srcBox + File.separator + "java" + File.separator +
      "mkfiles" + File.separator + machine + "-ntw-rmi";
    comMakefileName = srcBox + File.separator + "java" + File.separator +
      "mkfiles" + File.separator + machine + "-container-" + compileString;
      
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void verifyMakefiles () throws MakefileNotFoundException {
    jutilMakefile = new File(jutilMakefileName);
    jgiMakefile = new File(jgiMakefileName);
    jgiRMIMakefile = new File(jgiRMIMakefileName);
    ntwRMIMakefile = new File(ntwRMIMakefileName);
    comMakefile = new File(comMakefileName);
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void runMake (String module, String compileType, 
			String[] arguments) throws MakefileNotFoundException {
    String makefileName;
    File makefile;

    makefileName = srcBox + File.separator + "gen" + File.separator +
      "mfiles" + File.separator + machine + "-" + module + compileType;
    makefile = new File(makefileName);
    if (!makefile.exists()) {
      throw new MakefileNotFoundException(makefileName);
    }
    changeDirectory(srcBox + File.separator + module + File.separator +
		    compileType);
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void simpleMake (File makefile) {
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  private void doDebuggableBuild () {
    JavaMake jmake = new JavaMake();

    setMakefiles("o");
    try {
      verifyMakefiles();
      runMake("rtl", "o", new String[] {});
      runMake("ext", "o", new String[] { "libtcp.lib" });
      runMake("gsi", "o", new String[] { "libgsi.lib" });
      simpleMake(jgiRMIMakefile);
      simpleMake(ntwRMIMakefile);
      simpleMake(jutilMakefile);
      simpleMake(jgiMakefile);
      simpleMake(comMakefile);
      // jmake.compileJavaFilesInSandbox();
    } catch (MakefileNotFoundException exception) {
      error("Makefile not found: " + exception);
    }
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  public static void main (String[] argv) {
    RunmakeJNTW invocation = new RunmakeJNTW(argv);
    invocation.doDebuggableBuild();
  }
}


