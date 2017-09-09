package com.gensym.displays;

import java.util.*;
import java.text.SimpleDateFormat;
import java.text.DateFormat;
import com.gensym.util.MathUtils;
import com.gensym.message.Resource;

/** Miscellaneous utilities not covered by Date and Calendar.
 */
public class TimeUtils {

  public static final int MINUTE = 60000, HOUR = 3600000, DAY = 86400000;
  private static final Date dateUtil = new Date();
  // this is a bug: should be getOffset() to get daylight savings handled
  // correctly
  private static int rawOffset = TimeZone.getDefault().getRawOffset();

//   static long millisToday() {
//     long currentTime = System.currentTimeMillis() + offset;
//     return currentTime % DAY;
//   }

  static final long adjustmentForDaylightSavings(long time) {
    return TimeZone.getDefault().inDaylightTime(new Date(time)) ? HOUR : 0;
  }

  static final long adjustForTimeZone(long rawTime) {
    return rawTime - rawOffset - adjustmentForDaylightSavings(rawTime);
  }

  /** returns the time (in milliseconds) of the preceding midnight in
   * the current time zone.
   */
  static long midnight() {
    long currentTime = System.currentTimeMillis();
    long millisToday = currentTime % DAY;
    return adjustForTimeZone(currentTime - millisToday);
  }

  /** Translates G2 style date format strings into actual DateFormat
   * (SimpleDateFormat) objects.
   * @param map a resource that maps G2 date format strings into java
   * date format patterns
   * @param g2Format a G2 date format string.
   */
  public static DateFormat g2DateFormatToJava(Resource map,
					      String g2Format) {
    String javaString = map.getString(g2Format);
    SimpleDateFormat dateFormatter = new SimpleDateFormat(javaString);
    // Hack for Java bug #4035146 (fixed in jdk1.2 beta3)
    dateFormatter.setTimeZone (TimeZone.getDefault ());	
    return dateFormatter;
  }

  public static void main (String[] args) {
    Date midnight = new Date(midnight());
//     Date millisToday = new Date(millisToday());

    DateFormat dateFormatter = new SimpleDateFormat();
    dateFormatter.setTimeZone (TimeZone.getDefault ());	// Hack for Java bug

    System.out.println(rawOffset);
//     System.out.println(dateFormatter.format(millisToday));
    System.out.println(dateFormatter.format(midnight));
    System.out.println(dateFormatter.format(new Date(midnight() +
						     2*HOUR + 23*MINUTE)));
  }
}
    
