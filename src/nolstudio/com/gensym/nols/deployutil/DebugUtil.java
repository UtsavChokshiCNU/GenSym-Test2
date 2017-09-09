
package com.gensym.nols.deployutil;

import java.awt.Color;
import java.io.*;
import java.lang.reflect.Array;
import java.nio.charset.Charset;

public final class DebugUtil {

  private static final Resource i18n =
  Trace.getBundle("com.gensym.nols.deployutil.Messages");

  private DebugUtil () {
  }

  public static String getName (Color color) {
    if (Color.white.equals(color))
      return "White";
    else if (Color.lightGray.equals(color))
      return "Light Gray";
    else if (Color.gray.equals(color))
      return "Gray";
    else if (Color.darkGray.equals(color))
      return "Dark Gray";
    else if (Color.black.equals(color))
      return "Black";
    else if (Color.red.equals(color))
      return "Red";
    else if (Color.pink.equals(color))
      return "Pink";
    else if (Color.orange.equals(color))
      return "Orange";
    else if (Color.yellow.equals(color))
      return "Yellow";
    else if (Color.green.equals(color))
      return "Green";
    else if (Color.magenta.equals(color))
      return "Magenta";
    else if (Color.cyan.equals(color))
      return "Cyan";
    else if (Color.blue.equals(color))
      return "Blue";
    else
      return ("NonStandard " + color);
  }

  /** This should take args to append or overwrite the file
   */
  public static boolean writeToFile (Object o, String fileName) {
    try {
      java.io.FileOutputStream f = new java.io.FileOutputStream(fileName);
      java.io.ObjectOutput s = new java.io.ObjectOutputStream(f);
      s.writeObject (o);
      s.flush ();
      f.close ();
      return true;
    } catch (Exception e) {
      System.out.println ("Error during save of " + o + " : " + e);
      e.printStackTrace ();
      return false;
    }
  }

  /** Maybe another function to read more than one object?
   */
  public static Object readFromFile (String fileName) {
    try {
      java.io.FileInputStream f = new java.io.FileInputStream (fileName);
      java.io.ObjectInput s = new java.io.ObjectInputStream (f);
      Object o = s.readObject ();
      f.close ();
      return o;
    } catch (Exception e) {
      System.out.println ("Error during load from file : " + fileName);
      e.printStackTrace ();
      return null;
    }
  }

  public static Object[] readFromFile (String fileName, int numObjects) {
    Object[] objects = new Object[numObjects];
    try {
      java.io.FileInputStream f = new java.io.FileInputStream (fileName);
      java.io.ObjectInput s = new java.io.ObjectInputStream (f);
      if (numObjects != 0) {
	for (int i=0; i<numObjects; i++) 
	  objects[i] = s.readObject ();
      } else {
	int i=0;
	objects = new Object[100];
	try {
	  for (;;)
	    objects[i++] = s.readObject ();
	} catch (Exception e) {
	  i--;
	  Trace.exception (e, null);
	  System.err.println ("Error after reading " + i + " objects : " + e);
	  e.printStackTrace ();
	}
	Object[] retn = new Object[i];
	System.arraycopy (objects, 0, retn, 0, i);
	objects = retn;
      }
      f.close ();
      return objects;
    } catch (Exception e) {
      System.out.println ("Error during load from file : " + fileName);
      e.printStackTrace ();
      return null;
    }
  }

  /*
   *
   */
  public static void pause (final String msg, final boolean allowCommands) {
	  String message = msg;
	  if (!pause)
      return;
    try {
      if (message == null)
	message = "DebugUtil.pause> ";
      while (true) {
	System.out.print (message);
	char typedChar = (char) System.in.read ();
	while (System.in.available () > 0)
	  System.in.read ();
	if (!allowCommands)
	  return;
	if (typedChar == 'b')
	  dumpStack ();
	else if (typedChar == 'c' || typedChar == '\n')
	  return;
	else if (typedChar == 'q')
	  System.exit (0);
	else if (typedChar == 'o')
	  setPause (false);
	else if (typedChar == '?')
	  System.out.println (helpMsg);
      }
    } catch (java.io.IOException ioe) {
    }
  }

  private static final Throwable e = new Throwable ();
  private static boolean pause = false;
  private static final String helpMsg 
  = "b - backtrace" +
    "c - continue" +
    "q - quit (exit VM)" +
    "o - turn pause off" +
    "? - list commands";

  public static void setPause (boolean pauseState) {
    pause = pauseState;
  }

  private static void dumpStack () {
    ByteArrayOutputStream bos = new ByteArrayOutputStream (400);
    PrintWriter pw = new PrintWriter (new OutputStreamWriter(bos, Charset.defaultCharset()));
    e.fillInStackTrace ();
    e.printStackTrace (pw);
    pw.flush ();
    pw.close ();
    String backTrace = "";
    try{
    	backTrace = bos.toString (Charset.defaultCharset().name());
    }catch(UnsupportedEncodingException ee){
    	 System.err.println ("Error in dumpStack : " + ee);
    }
    int newLineIndex = backTrace.indexOf ('\n');
    newLineIndex = backTrace.indexOf ('\n', newLineIndex + 1);
    newLineIndex = backTrace.indexOf ('\n', newLineIndex + 1);
    System.out.println (backTrace.substring (newLineIndex + 1, backTrace.length () - 1));
  }

  public static String getStackTrace (Throwable t) {
    ByteArrayOutputStream bos = new ByteArrayOutputStream (400);
    PrintWriter pw = new PrintWriter (new OutputStreamWriter(bos, Charset.defaultCharset()));
    t.printStackTrace (pw);
    pw.flush ();
    pw.close ();
    String backTrace = "";
    try{
    	backTrace = bos.toString (Charset.defaultCharset().name());
    }catch(UnsupportedEncodingException ee){
    	System.err.println ("Error in getStackTrace : " + ee);
    }
    return backTrace;
  }

  public static String getStackTrace () {
    ByteArrayOutputStream bos = new ByteArrayOutputStream (400);
    PrintWriter pw = new PrintWriter (new OutputStreamWriter(bos, Charset.defaultCharset()));
    synchronized (e) {
      e.fillInStackTrace ();
      e.printStackTrace (pw);
    }
    pw.flush ();
    pw.close ();
    String backTrace = "";
    try{
    	backTrace = bos.toString (Charset.defaultCharset().name());
    }catch(UnsupportedEncodingException ee){
    	System.err.println ("Error in getStackTrace : " + ee);
    }
    
    int newLineIndex = backTrace.indexOf ('\n');
    newLineIndex = backTrace.indexOf ('\n', newLineIndex + 1);
    //newLineIndex = backTrace.indexOf ('\n', newLineIndex + 1);
    //newLineIndex = backTrace.indexOf ('\n', newLineIndex + 1);
    return (backTrace.substring (newLineIndex + 1, backTrace.length () - 1));
  }

  public static String getStackTrace (int depth) {
    String fullStackTrace = getStackTrace ();
    int startIndex = fullStackTrace.indexOf ('\n', 0);
    int endIndex = fullStackTrace.indexOf ('\n', startIndex + 1);
    for (int i=0; i<depth; i++) {
      endIndex = fullStackTrace.indexOf ('\n', endIndex + 1);
      if (endIndex < 0) {
	endIndex = fullStackTrace.length ();
	break;
      }
    }
    return fullStackTrace.substring (0, endIndex);
  }

  public static String printArray (Object array) {
    return printArray (array, 0, -1);
  }

  /**
   * @param array the array to be printed.
   * @param start the first element to be printed.
   * @param end the (inclusive) last element
   */
  public static String printArray (final Object array, final int start, final int end) {
	  int endIndex = end;
    if (array == null)
      return "null";
    if (!array.getClass().isArray ())
      throw new IllegalArgumentException ("arg to printArray must be an Array");
    if (endIndex == -1)
      endIndex = Math.max(0, Array.getLength (array) - 1);
    
    int length = Array.getLength (array);
    if (length == 0)
      return "[]";

    if (endIndex < 0 || start < 0)
      throw new IllegalArgumentException(i18n.format("duInvalidEndpoint", start, endIndex));

    endIndex = Math.min(endIndex, length - 1);

    StringBuffer buffer = new StringBuffer ("[");
    for (int i=start; i <= endIndex; i++)
      buffer.append (Array.get (array, i)).append (i != length - 1 ? " " : "");
    buffer.append ("]");

    return buffer.toString ();
  }

  public static String describe (Object o) {
    if (o == null)
      return "null";
    return new StringBuffer ("Class ").append(o.getClass().getName()).append (" -> ").append (o.toString()).toString ();
  }

  /**
   * Returns a copy of the String with all occurences of
   * the specified character removed.
   */
  public static String removeCharFromString (String s, char charToRemove) {
    if (s.indexOf (charToRemove) < 0)
      return s;
    int numChars = s.length (), j = 0;
    char[] characters = new char[numChars];
    char c;
    for (int i=0; i<numChars; i++)
      if ((c = s.charAt (i)) != charToRemove)
	characters[j++] = c;
    return new String (characters, 0, j);
  }

}

