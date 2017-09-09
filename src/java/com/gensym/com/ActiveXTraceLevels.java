/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXTraceLevels.java
 *
 *   Author: Allan Scott
 */

package com.gensym.com;

/** The interface <code>ActiveXTraceLevels</code> defines the different
* levels of tracing that are used throughout the com.gensym.com module
* and in the native library JavaContainer.dll
*/
public interface ActiveXTraceLevels
{
   
  /** A trace level.  Equivalent to AX_ALWAYS */
  public static final short AX_DIALOG_BOX  =  0;

  /** A trace level.  Trace only highest priority messages.*/
  public static final short AX_ALWAYS      =  0;
  
  /** A trace level.  Lower priority than AX_DIALOG_BOX, but higher
   *  than AX_PROGRESS.
   */
  public static final short AX_ERROR       = 10;
  
  /** A trace level.  Lower priority than ERROR, but higher than
   *  AX_MORE_DETAIL
   */
  public static final short AX_PROGRESS    = 20;
  
  /** A trace level.  Lower priority than AX_PROGRESS, but higher
   *  than AX_DATA_DUMPS.
   */
  public static final short AX_MORE_DETAIL = 30;
  
  /** A trace level.  Lowest priority */
  public static final short AX_DATA_DUMPS  = 40;

  /** The maximum trace level, equivalent to AX_DATA_DUMPS. Traces
   * all messages.
  */
  public static final short AX_MAX_TRACE_LEVEL = AX_DATA_DUMPS;
  
  /** The minimum trace level, equivalent to AX_ALWAYS
  */
  public static final short AX_MIN_TRACE_LEVEL = AX_DIALOG_BOX;

}
