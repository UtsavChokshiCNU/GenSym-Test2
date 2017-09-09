
package com.gensym.devtools;
import java.io.*;

/**
 * Reads entire lines from a FileInputStream
 *
 * @author vkp
 * @version 1.0 14 Jun 1997
 *
 */

public class PipeReader extends FileReader {

  public PipeReader (String fileName) throws FileNotFoundException {
    super (fileName);
  }

  public static void main (String[] args) throws FileNotFoundException, IOException {
    
    String line;
    
    for (;;) {
      PipeReader fr = new PipeReader (args[0]);
      for (;;) {
	line = fr.readLine ();
	if (line == "") {
	  fr.close ();
	  break;
	} else
	  System.out.print ("Read line: " + line);
      }
    }
  }

  /**
   * readLine blocks till a full line is read from the
   * underlying stream.
   */
  public String readLine () throws IOException {
    StringBuffer sb = new StringBuffer (20);
    for (;;) {
      int newChar = read ();
      if (newChar < 0) return "";
      sb.append ((char)newChar);
      if (newChar == '\n')
	break;
    }
    return sb.toString ();
  }
}
