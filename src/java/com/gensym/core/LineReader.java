
package com.gensym.core;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Vector;

class LineReader {

  InputStream is;
  LineFilter filter;

  LineReader (InputStream is, LineFilter filter) {
    this.is = is;
    this.filter = filter;
  }

  String[] readLines () throws IOException {
    Vector lines = new Vector ();
    String line;
    BufferedReader br = new BufferedReader (new InputStreamReader (is, Charset.defaultCharset()));
    while ((line = br.readLine ()) != null)
      if ((filter == null) || (filter.accept (line)))
	lines.addElement (line);
    String[] linesArray = new String[lines.size ()];
    lines.copyInto (linesArray);
    return linesArray;
  }
  
}
