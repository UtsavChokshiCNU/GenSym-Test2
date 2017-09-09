
package com.gensym.devtools;

import java.io.*;
import java.util.*;

/**
 * If the Java VM is launched with the main method of this
 * class, it comes up as a daemon to service compilation requests.
 * The daemon opens a stream to a named pipe (passed in as an
 * argument) and listens for requests. The request is then
 * handed off to another thread to complete. The cmdline
 * read is of the form:
 * <options>* <JavaFileName>.java <ResultFileName>
 * The output of the compiler (warnings + errors) are
 * returned in the results file.
 * The class uses private classes in the sun.* packages
 * to implement its functionality. This means that it
 * can go away with any Rev. of the JDK.
 * Each machine that is used for java development needs to
 * have one of these daemons running. It can safely handle
 * multiple concurrent users and requests.
 *
 * @author vkp
 * @version 1.0 14 Jun 1997
 * @see com.gensym.devtools.JavaCompilerThread
 *
 */
public class JavaCompilerDaemon extends Thread {

  private String pfileName;

  public static void main (String args[]) {
    new JavaCompilerDaemon (args).watch ();
  }

  JavaCompilerDaemon (String[] args) {
    int numArgs = args.length;
    pfileName = args[numArgs - 1];
  }

  public void watch () {
    LineReader lr = new LineReader (pfileName);
    String cmd;
    /* Infinite loop for requests.
       LineReader is an abstraction to handle the fact that
       the stream is not quite well behaved after reading an EOF.
       A subsequent read does not block. This requires closing
       and reopening the stream */
    for (;;) {
      try {
	cmd = lr.readLine ();
	new JavaCompilerThread (cmd).start ();
      } catch (IOException ie) {
	System.err.println (ie);
	System.exit (2);
      }
    }
  }
  
}
