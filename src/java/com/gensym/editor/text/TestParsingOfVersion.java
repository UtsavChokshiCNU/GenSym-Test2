package com.gensym.editor.text;

/* This is a oneoff test of a little special case parser that's used
 * in TextView. It's supposed to do what it's name suggests */

public class TestParsingOfVersion {

  public static void main (String[] args) {
    String testString;
    if ( args.length > 0 )
      testString = args[0];
    else
      testString = System.getProperty("java.version");
    
    if ( isTheVersionOfJDKGreaterThan115(testString) )
      System.out.println("Returns true");
    else
      System.out.println("Returns false");
  }


  private static boolean isTheVersionOfJDKGreaterThan115(String version) {
    System.out.println("Testing the version string \"" + version + "\"");

    if ( version.equals("") )
      return false;   // This is paranoid, but if it's possible, is false the right answer?

    if ( version.length() == 1 ) {          // guards the first substring operation
      if ( Integer.parseInt(version) <= 1 ) // if there no period
	return false; // 1
      else 
	return true;  // 2
    }

    int indexOfFirstPeriod = version.indexOf('.');
    if ( indexOfFirstPeriod == -1 ) // "2b1"
      indexOfFirstPeriod = version.length(); // saves copying code

    String major = version.substring(0, indexOfFirstPeriod);
    if ( Integer.parseInt(major) == 0 ) // beta
      return false;

    if ( Integer.parseInt(major) == 1 ) {
      int indexOfSecondPeriod = version.indexOf('.', indexOfFirstPeriod + 1);
      if ( indexOfSecondPeriod == -1 )  // e.g. "1.2"
	indexOfSecondPeriod = version.length();

      String minor = version.substring(indexOfFirstPeriod + 1, indexOfSecondPeriod);
      if ( ( Integer.parseInt(minor) <= 1 ) &&
	   ( indexOfSecondPeriod != version.length() ) // "1.1"
	   ) {
	String last = version.substring(indexOfSecondPeriod + 1);
	if ( last.indexOf('.') != -1 ) // 1.1.5.1 -- would blow up parseInt
	  return false;  // same policy as verion == ""

	if ( Integer.parseInt(last) <= 5 )
	  return false;

	else
	  return true;
      }
      else
	return true;
    }
    else
      return true;
  }


} // end the class
