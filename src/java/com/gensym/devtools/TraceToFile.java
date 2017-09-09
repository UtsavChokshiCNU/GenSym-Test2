package com.gensym.devtools;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.FileOutputStream;

import com.gensym.message.Trace;
import com.gensym.core.DebugUtil;

/** A debugging class.
 */
public class TraceToFile {
  private static String fileName = "\\temp\\trace.txt";
  private static PrintWriter stream;
  private static FileOutputStream fileStream;

  static {
    Trace.setExceptionTraceOn(true);
    openNewStream(true);
  }      

  public static void setFile(String newFileName, boolean append) {
    if (newFileName == null) {
      closeCurrentStream();
    } else if (!newFileName.equals(fileName)) {
      closeCurrentStream();
      fileName = newFileName;
      openNewStream(append);
    }
  }

  private static void closeCurrentStream() {
    try {
      if (fileStream != null) {
	stream.flush();
	fileStream.close();
      }
    } catch (IOException ioe) {
      Trace.exception(ioe);
    }
    fileStream = null;
    stream = null;
  }

  private static void openNewStream(boolean append) {
    try {
      fileStream = new FileOutputStream(fileName, append);
      stream = new PrintWriter(fileStream, true);
    } catch (IOException ioe) {
      Trace.exception(ioe);
    }
  }

  public static void println(Object string) {
    stream.println(string);
  }
      
  public static void print(Object string) {
    stream.print(string);
  }

  public static void stack() {
    println(DebugUtil.getStackTrace());
  }
    
  public static void main(String[] args) {
    println("foo");
  }
}
