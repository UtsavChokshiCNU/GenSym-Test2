package com.gensym.devtools;

import java.io.PrintWriter;
import java.io.InputStream;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;


/**
 * It executes a command in a separate process using
 * the runtime's exec method.
 * @version August 2000
 * @author Brian O. Bush
 */
final class Exec {
  /**
   * Executes a command in a separate process using
   * the runtime's exec method.
   * @see java.lang.Runtime#exec(String[])
   * @param args operands given to exec method of the runtime
   * @param out place to write messages
   * @exception CommandFailedException if operation failed
   */
  public void exec(String[] args, PrintWriter out) throws CommandFailedException {
    String msg = null;		// For error messages
    try {
      // Create the child process.
      Process p = Runtime.getRuntime().exec(args);
      // Start a thread which copies the input stream to out.
      Thread t = new Thread(new BufferedCopy(p.getInputStream(), out));
      t.start();
      // Copy the error stream.
      new BufferedCopy(p.getErrorStream(), out).run();
      int exitCode = p.waitFor(); // Wait for the termination of the child
      t.join();			// Wait for the end of the input stream
      if (exitCode != 0) {
	if (args.length > 0) {	// Copy command when an error occurs
	  msg = args[0];
	  for (int i = 1; i < args.length; i++)
	    msg += " " + args[i];
	}
	else
	  msg = "No args to exec";
      }
    }
    catch (IOException ioEx) {	// from exec
      msg = "In exec: " + ioEx.toString();
    }
    catch (InterruptedException iEx) { // from waitFor
      msg = "In waitFor: " + iEx.toString();
    }
    if (msg != null)
      throw new CommandFailedException(msg);
  }

  /**
   * An object which copies the input stream to out.
   * The copy can be run by a thread.
   */
  private static class BufferedCopy implements Runnable {
    private InputStream is;
    private PrintWriter out;

    BufferedCopy(InputStream is, PrintWriter out) {
      this.is = is;
      this.out = out;
    }
      
    @Override
    public void run() {
      BufferedReader br = new BufferedReader(new InputStreamReader(is));
      try {
	for (;;) {
	  String line = br.readLine();
	  if (line == null)
	    break;
	  out.println(line);
	}
	br.close();
      }
      catch (IOException ex) { }
    }
  }

  /**
   * An entry point for testing exec commands.
   * It simply passes the arguments to the exec operation.
   * @param args operands for the command
   */
  public static void main(String[] args) {
    PrintWriter out = new PrintWriter(System.out, true);
    try {
      new Exec().exec(args, out);
    }
    catch (Throwable t) {
      System.err.println("Internal error: " + t.getMessage());
      t.printStackTrace();
    }
    out.println("Exec command completed");
  }
}
