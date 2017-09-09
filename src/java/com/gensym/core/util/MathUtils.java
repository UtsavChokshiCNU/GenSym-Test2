/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      MathUtils.java
 *               Math utilities
 *
 * Description:
 *
 *      Author:
 *		Robert Penny		Aug/97
 *
 * Modifications:
 *
 */
package com.gensym.core.util;

/** A package to encapsulate mathematical concepts not directly implemented
 * in java.lang.Math */

public class MathUtils {
  public static double floor(double numerator, double divisor) {
    return Math.floor(numerator/divisor);
  }

  public static long floor(long numerator, long divisor) {
    return (long)Math.floor(((double)numerator)/divisor);
  }

  public static int floor(int numerator, int divisor) {
    return (int)Math.floor(((double)numerator)/divisor);
  }

  public static double ceil(double numerator, double divisor) {
    return Math.ceil(numerator/divisor);
  }

  public static double log(double base, double value) {
    return Math.log(value)/Math.log(base);
  }

  private static final double LOG_TEN = Math.log(10);

  public static double logTen(double value) {
    return Math.log(value)/LOG_TEN;
  }

  public static double leastSignificantDecimalDigit(final double number) {
    if (Double.compare(number, 0.0) == 0)
      return 0.0;

    double absNumber = Math.abs(number);

    double power = - Math.ceil(MathUtils.logTen(absNumber));
    for (;;) {
      double factor = Math.pow(10.0, power);
      double shiftedNumber = factor * power;
      double remainder = Math.IEEEremainder(shiftedNumber, 1.0);
      if (Math.abs(1.0 - remainder) < 0.000001 ||
	  Math.abs(remainder) < 0.000001)
	return -power;
      power++;
    }
  }

  /** @return The number of digits in the integer portion of a |number| > 1,
   * or one plus the number of 0's before the first non-zero digit in a
   * 0 < |number| < 1. returns 0 for 0.
   */
  public static int getIntegerPowerOfTen(double x) {
    if (Double.compare(x, 0) == 0)
      return 0;
    else
      return (int)Math.floor(logTen(Math.abs(x)));
  }
}
