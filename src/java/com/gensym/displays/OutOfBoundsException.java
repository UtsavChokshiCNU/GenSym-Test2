/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 OutOfBoundsException.java
 *
 *  Description:
 *               Indicates a value exceeding a numeric bounds.
 *
 *	 Author:
 *		Robert Penny		Aug/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.displays;

import com.gensym.message.Resource;

/** Used to indicate that a numeric argument exceeded bounds imposed
 * by the throwing method.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 * @deprecated May be eliminated.
 */
public class OutOfBoundsException extends Exception {
  private static Resource i18n =
  Resource.getBundle("com.gensym.displays.Messages");
  
  public double offendingValue;
  public double offendedValue;

  OutOfBoundsException(double offendingValue, double offendedValue) {
    this.offendingValue = offendingValue;
    this.offendedValue = offendedValue;
  }

  @Override
  public String getMessage() {
    return i18n.format("OutOfBoundsException",
		       new Double(offendingValue),
		       new Double(offendedValue));
  }
    
}
