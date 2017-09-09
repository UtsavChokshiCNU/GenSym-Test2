/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXRuntimeConstants.java
 *
 *   Author: Allan Scott
 */

package com.gensym.com;

/** The interface <code>ActiveXRuntimeConstants</code> provides
* a convenient way of referring to some static constants that
* are used throughout the com.gensym.com package.  This means that
* if you are planning on using com.gensym.com all you need to do is
* make your class implement <code>ActiveXRuntimeConstants</code> and
* you have access to all the constants provided by this interface
*<p>
* The constants in this interface can be divided into four categories:
* <ul>
* <li> Constants used to represent undefined C pointer values. For example:
* AX_NO_CLIENT_SITE and AX_NO_DISPATCH;
* <li> Constants used to represent dispatch types through the 
* <code>ActiveXDispatchable</code> interface.  For example AX_INVOKE,
* AX_PROPERTYGET and AX_PROPERTYSET;
* <li> Constants used to represent the type of a <code>Variant</code>.
* For example AX_I1, AX_I2, AX_BOOL;
* <li> Constants used in <code>ActiveXMode</code> to describe options
* for creating, activating and displaying an ActiveX component.
* </ul>
*<p>
* @see ActiveXProxy
* @see ActiveXDispatchable
* @see Variant
* @see ActiveXModes
*/
public interface ActiveXRuntimeConstants
{
    
  /** The value that is assigned to a variable representing
   *  a client site pointer when no client site is available.  This
   *  can be returned by the getClientSite() method of ActiveXProxy
   *  when the ActiveX component associated with the ActiveXProxy
   *  does not exist.
   */
  public static final int AX_NO_CLIENT_SITE = 0;

  /** The value that represents no dispatch pointer.  This must be 
  * returned by the getDispatchPointer method in implementations
  * of ActiveXDispatchable to indicate the the dispatch pointer
  * does not exist.
  */
  public static final int AX_NO_DISPATCH = 0;


  /* Dispatch types used by ActiveXDispatchable */
  
  /** The value that is used to indicate to the 
  * axInvoke() method in ActiveXDispatchable that this is a 
  * method call (rather than a property set or get).
  */
  public static final int AX_INVOKE = 0;
  
  /** The value that is used to indicate to the 
  * axInvoke() method in ActiveXDispatchable that this is a 
  * property get (rather than a method call or property set).
  */
  public static final int AX_PROPERTYGET = 1;

  /** The value that is used to indicate to the 
  * axInvoke() method in ActiveXDispatchable that this is a 
  * property set (rather than a method call or property get).
  */
  public static final int AX_PROPERTYSET = 2;


  /* Type flags for the contents of a Variant */

  /* The first group of typeflags should match the OLE automation
     VARENUM enumeration */

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_EMPTY          =  0;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_NULL           =  1;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_I2             =  2;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_I4             =  3;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_R4             =  4;
 
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_R8             =  5;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_CY             =  6;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_DATE           =  7;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_BSTR           =  8;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_DISPATCH       =  9;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_HERROR         = 10;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_BOOL           = 11;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_VARIANT        = 12;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_UNKNOWN        = 13;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_UI1            = 17;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_RESERVED      = (short)0x8000;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_BYREF         = (short)0x4000;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_ARRAY         = (short)0x2000;

  /* The following typeflags are for non-variant types */

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_I1             = 16;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_UI2            = 18;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_UI4            = 19;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_I8             = 20;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_INT            = 22;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_UINT           = 23;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_VOID           = 24;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_USERDEFINED    = 29;

  // The following types are java type mapped to OLE Variant types

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_BYTE           = AX_UI1;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_SHORT          = AX_I2;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_BOOLEAN        = AX_BOOL;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_INTEGER        = AX_I4;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_LONG           = AX_I8;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_FLOAT          = AX_R4;
  
  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_DOUBLE         = AX_R8;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_CURRENCY       = AX_CY;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_STRING         = AX_BSTR;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_IUNKNOWN       = AX_UNKNOWN;

  // The following types are for are BeanXporter internal use.

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_VECTOR         = AX_USERDEFINED;

  /** A typeflag, used in <code>Variant</code>
  */
  public static final short AX_COLOR          = (short)0x0800;

  // ActiveX error codes

  /** An error code of to be passed for missing optional parmeters.
  * DISP_E_PARAMNOTFOUND = 0x80020004, defined in WINERROR.H
  */ 
  public static final int AX_E_PARAMNOTFOUND = 0x80020004;

  /* ActiveXModes bitflags */
  
  /** A bitflag, used in <code>ActiveXModes</code>
  * to indicate that the component should be created by OLE linking.
  * For future use. Currently OLE linking is not supported.
  */
  public static final int AX_CREATE_LINK = 0x0001;
  

  /** A bitflag, used in <code>ActiveXModes</code>
  * to indicate that the component should be created from an
  * existing file. 
  */
  public static final int AX_CREATE_FROM_FILE = 0x0002;
 	
  /** A bitflag used in <code>ActiveXModes</code> to indicate the 
  *  remote creation of the component.  For future use. Remote
  *  creation is not currently supported.
  */
  public static final int AX_LOCATE_REMOTE = 0x0004;

  /** A bitflag used in <code>ActiveXModes</code> to indicate 
   * whether the component should be activated in place or out
   * of place. For future use.  Currently in place activation is
   * always preferred.
   */
  public static final int AX_ACTIVATE_IN_PLACE = 0x0008;
	
  /** A bitflag used in <code>ActiveXModes</code> if set implies
   * the component should be displayed as an icon.  For future use.
   * Currently iconic display is not supported.
   */
  public static final int AX_DISPLAY_AS_ICON = 0x0010;

  /** A bitflag used in <code>ActiveXModes</code> to indicate that
  * the component can not be inserted as an OLE document.
  */
  public static final int AX_NOT_INSERTABLE = 0x0020;


}

