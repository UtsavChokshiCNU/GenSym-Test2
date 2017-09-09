
package com.gensym.devtools;
import java.io.*;

/**
 * Package private class necessary to handle the quirky behavior
 * of streams reading from a pipe. If an EOF marker is read,
 * subsequent reads do not block and return illegal characters.
 * This requires reopening the InputStream.
 *
 * @author vkp
 * @version 1.0 14 Jun 1997
 */

class LineReader {

  private PipeReader pin;
  private String fileName;

  LineReader (String fileName) {
    this.fileName = fileName;
  }

  /**
   * readLine blocks till a series of characters followed by a newline
   * is received.
   */
  String readLine () throws IOException {
    String line;
    for (;;) {
      if (pin == null)
	pin = new PipeReader (fileName);
      line = pin.readLine ();
      if (line == "") {
	pin.close ();
	pin = null;
      } else
	return line;
    }
  }

  // Test
  public static void main (String[] args) throws FileNotFoundException, IOException {
    LineReader lr = new LineReader (args[0]);
    for (;;)
      System.out.print (lr.readLine ());
  }

}
