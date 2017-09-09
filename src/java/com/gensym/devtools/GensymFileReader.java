/****************************************************************************
 * GensymFileReader.java
 * 
 * Author: John Valente
 *
 ***************************************************************************/

package com.gensym.devtools;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.Reader;
import java.io.UnsupportedEncodingException;


public class GensymFileReader extends BufferedReader
{
  private static final int readEOFChar = -1;
  private static final int cvsSeparatorChar = 47;  /* '/' */
  private static final int suffixChar = 46;  /* '.' */
  private static final int newlineBeginning = 13;
  private static final int newlineCompletion = 10;

  private String filename;  // Not verified!!

  /****************************************************************************
   *
   *
   ***************************************************************************/
  public GensymFileReader (InputStreamReader isReader)
  {
    super(isReader);
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public GensymFileReader (InputStreamReader isReader, String filename)
  {
    super(isReader);
    this.filename = filename;
  }



  /****************************************************************************
   *
   *
   ***************************************************************************/
  public static GensymFileReader makeGensymFileReader (String filename,
						       boolean complainIfNotExist)
  {
    File file;
    InputStream iStream;
    String fullSrcName;
    Reader reader = null;

    file = new File(filename);
    if (!file.exists()) {
      if (complainIfNotExist) {
	error("the log file to be read, " +
	      file.getAbsolutePath() + ", does not exist");
      }
      return null;
    }
    if (file.isDirectory()) {
      error("the log file to be read, " +
	    file.getAbsolutePath() + ", is a directory");
      return null;
    }
    try {
      iStream = new BufferedInputStream(new FileInputStream(file));
      if (iStream == null) {
	error("could not create input stream");
	return null;
      }
    } catch (FileNotFoundException e) {
      error("FileNotFoundException creating input stream:" + e.getMessage());
      return null;
    }
    InputStreamReader isReader = new InputStreamReader(iStream); 
    return new GensymFileReader(isReader, filename);
  }


  /****************************************************************************
   *
   *
   ***************************************************************************/
  public static GensymFileReader makeGensymFileReader (String filename)
  {
    return makeGensymFileReader (filename, false);
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  @Override
  public String readLine () {
    int currentChar;
    String line;

    try {
      line = "";
      currentChar = read();
      while ((currentChar == newlineBeginning) ||
	     (currentChar == newlineCompletion)) {
	currentChar = read();
      }
      while ((currentChar != readEOFChar) &&
	     (currentChar != newlineBeginning) &&
	     (currentChar != newlineCompletion)) {
	line += (char) currentChar;
	currentChar = read();
      }
    } catch (IOException io) {
      error("GensymFileReader.readLine: I/O Exception");
      return "";
    }
    return line;
  }


  @Override
  public void close () {
    try {
      super.close ();
    } catch (IOException ioe) {
      error ("I/O Exception closing reader");
    }
  }

  /****************************************************************************
   *
   *
   ***************************************************************************/
  private static void error (String message) {
    System.err.println("ERROR: " + message);
    System.err.flush();
  }

}


