
package com.gensym.tests;

import java.util.Date;
import java.util.TimeZone;
import java.text.SimpleDateFormat;

public class DateBug {

  public static void main (String[] args) {
    Date theDate = new Date ();
    System.out.println ("Now = " + theDate);
    SimpleDateFormat formatter = new SimpleDateFormat ();
    System.out.println ("Formatted = " + formatter.format (theDate));
    formatter.setTimeZone (TimeZone.getDefault ());
    System.out.println ("Fixed = " + formatter.format (theDate));
  }

}
