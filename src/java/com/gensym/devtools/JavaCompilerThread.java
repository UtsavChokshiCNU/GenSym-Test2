
package com.gensym.devtools;
import java.io.*;
import java.util.*;

/**
 * Helper thread to run compilations for JavaComplierDaemon.
 * It takes the command-line options and (currently one) java
 * file-name and constitutes the array required by sun.tools.javac.Main.
 * The last token in the command-line is the file to which the
 * results of the compilation should be written out to.
 * 
 * @author vkp
 * @version 1.0 14 Jun 1997
 * @see com.gensym.devtools.JavaCompilerDaemon
 *
 */
public class JavaCompilerThread extends Thread {

  private String cmd;
  private String[] jargs;
  private Vector optionsVctr = new Vector (5);

  JavaCompilerThread (String args) {
    cmd = args;
  }

  @Override
  public void run () {
    PrintStream printStream = System.err;
    String jfile = null, jrfile = null;
    String scratchfile = "/tmp/jr-results-" + (int)(java.lang.Math.random()*10000);
      
    sun.tools.javac.Main cobject;
    try {
      jrfile = getResultsFileName ();
      jargs = setupJavaCompile ();
      jfile = jargs [jargs.length - 1];
      printStream = new PrintStream (new FileOutputStream (scratchfile));
      cobject = new sun.tools.javac.Main(printStream, "javac");
      System.err.println ("Compiling: " + jfile + " => " + jrfile);
      long t0 = System.currentTimeMillis ();
      boolean jflag = !cobject.compile (jargs);
      long t1 = System.currentTimeMillis ();
      System.err.println ("Finished Compiling " + jfile + " -> " + jflag + " [" + (t1 - t0) + "] ms");
      printStream.close ();
      Runtime.getRuntime().exec ("mv " + scratchfile + " " + jrfile);
    } catch (IOException ie) {
      System.err.println (ie);
    }
  }
  
  private String getResultsFileName () {
    int lastSpaceIndex = cmd.lastIndexOf (' ');
    return (cmd.substring (lastSpaceIndex + 1, cmd.length() - 1));
  }

  private String[] setupJavaCompile () {
    optionsVctr.removeAllElements ();
    for (StringTokenizer tknzr = new StringTokenizer (cmd, " ");
	 tknzr.hasMoreElements ();) {
      String tkn = tknzr.nextToken ();
      optionsVctr.addElement (tkn);
    }
    int numTkns = optionsVctr.size ();
    optionsVctr.removeElementAt (numTkns - 1);
    String[] jargs = new String[numTkns - 1];
    optionsVctr.copyInto (jargs);
    return jargs;
  }
    
  
}
