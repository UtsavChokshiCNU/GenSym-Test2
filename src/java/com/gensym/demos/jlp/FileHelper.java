package com.gensym.demos.jlp;

public class FileHelper {



  public FileHelper()
  {
  }

  /**
   * gives back an ascii string of the int that was passed in
   */
  public String intToAsciiString( int i)
  {
     char c = (char)i;
     String s = new String();
     s = String.valueOf(c);
     return s;
  }

}



