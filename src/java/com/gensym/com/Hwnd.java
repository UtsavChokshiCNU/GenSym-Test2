/******************************************************************************
 * Hwnd.java (com.gensym.com.Hwnd)
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 *
 * @author John Valente
 *
 ******************************************************************************/
package com.gensym.com;

import java.awt.Component;
import java.awt.Point;
import java.awt.peer.ComponentPeer;
import java.awt.peer.LightweightPeer;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/** This class is used to obtain information about an AWT component.
* It contains a handle to the underlying HWND structure containing
* the component, and the x and y offset from the top left of the
* HWND.  Note that this class depends on this being a Sun runtime
* environment of version 1.1 or greater.
*/
public class Hwnd 
{
  /** The value used when the native window cannot be obtained.
   *  Since obtaining the handle to the native window requires
   *  the cooperation of the runtime environment, this value
   *  will be returned for any component when using a nonsupported
   *  implementation.
   */
  public final static int NO_HWND = 0;

  /** An integer representing the handle of the window in the
   *  underlying window system.  Most AWT components will not
   *  have their own windows in the actual implementation.
   *  This is a handle to the window containing the component.
   *  The top left corner of the component is determined by
   *  taking the window indicated by handleToPeer and 
   *  moving xOffset units to the right and yOffset units
   *  down.
   */
  public int handleToPeer = NO_HWND;

  private Point location = null;
  private Component awtComponent = null;

  private static Method  getPeerMethod   = null;
  private static Method  getDSInfoMethod = null;
  private static Method  getHwndMethod   = null;
  private static Method  lockMethod      = null;
  private static Method  unlockMethod    = null;

  private static Object  noArgs[]        = new Object[0];
  private static boolean isSupportedVM   = false;
  private static boolean isVerbose       = false;

  private static final String standardErrorMessage = "\nThis does not appear to "  
  + "be a supported environment for using HWNDs.  This class \ncan only be used "
  + "with the Sun JDK 1.1 or greater on Microsoft Windows platforms.";

  /* The following static block contains most of the implementation
   * of this class.  It is static because I assume that the existence
   * of sun.awt classes is static for a particular VM.
   */
  static {
    String osName = null, javaVendor = null;

    osName = System.getProperty("os.name");
    javaVendor = System.getProperty("java.vendor");
    if ((javaVendor != null) &&
	(osName != null) &&
	// (javaVendor.equals("Sun Microsystems Inc.")) &&
	(osName.equals("Windows NT") || osName.equals("Windows 95") ||
       osName.equals("Windows 98")))  {
      try {
	Class componentClass, drawingSurfaceInfoClass, drawingSurfaceClass;
	Class noClasses[] = new Class[0];

	componentClass = 
	  Class.forName ("java.awt.Component");
	drawingSurfaceClass = 
	  Class.forName("sun.awt.DrawingSurface");
	drawingSurfaceInfoClass =
	  Class.forName("sun.awt.windows.WDrawingSurfaceInfo");
	getPeerMethod =
	  componentClass.getDeclaredMethod ("getPeer", noClasses);
	getDSInfoMethod =
	  drawingSurfaceClass.getDeclaredMethod("getDrawingSurfaceInfo", noClasses);
	getHwndMethod =
	  drawingSurfaceInfoClass.getDeclaredMethod("getHWnd", noClasses);
	unlockMethod = 
	  drawingSurfaceInfoClass.getDeclaredMethod("unlock", noClasses);
	lockMethod = 
	  drawingSurfaceInfoClass.getDeclaredMethod("lock", noClasses);
	isSupportedVM = ((getDSInfoMethod != null) &&
			 (getPeerMethod != null) &&
			 (getHwndMethod != null) &&
			 (unlockMethod != null) &&
			 (lockMethod != null));
      } catch (ClassNotFoundException e) {
	abort("could not access peer classes.\nIs this a Sun 1.1 VM?");
      } catch (NoSuchMethodException e) {
	abort("could not access peer classes.\nIs this a Sun 1.1 VM?");
      } catch (IllegalArgumentException e) {
	abort("illegal argument exception: " + e.getMessage());
      }
    } else {
      System.out.println(standardErrorMessage);
      System.out.flush();
    }
    if (!isSupportedVM) {
      abort("this environment does not seem to provide the " +
	    "necessary classes to use com.gensym.com.Hwnd.");
    }
  }


  /** An Hwnd contains information about an AWT component.  It 
   *  contains a handle to the underlying HWND structure containing
   *  the component, and the x and y offset from the top left of the
   *  HWND.  Note that this class depends on this being a Sun runtime
   *  environment of version 1.1 or greater.
   */
  public Hwnd (Component component) {
    if (isSupportedVM) {
      awtComponent = component;
      try {
	ComponentPeer peer;

	peer = updateLocation();
	
	if (isADrawingSurface(peer)) {
	  Integer hwnd;
	  Object dsInfo;

	  dsInfo = getDSInfoMethod.invoke(peer, noArgs);

	  lockMethod.invoke(dsInfo, noArgs);
	  hwnd = (Integer) getHwndMethod.invoke(dsInfo, noArgs);
	  unlockMethod.invoke(dsInfo, noArgs);
	  
	  handleToPeer = hwnd.intValue();
	}
      } catch (IllegalAccessException e) {
	abort("illegal access exception: " + e.getMessage());
      } catch (InvocationTargetException e) {
	abort("invocation target exception: " + e.getMessage());
      }
    }
  }

  private boolean isADrawingSurface (ComponentPeer peer) {
    // Here, check that (peer instanceof sun.awt.DrawingSurface).  How do 
    // you do that using introspection?
    return (peer != null);
  }

  private ComponentPeer updateLocation () {
    Component iterator = awtComponent;
    boolean done = false;
    ComponentPeer peer;
    int xOffset=0, yOffset=0;

    try {
      peer = (ComponentPeer) getPeerMethod.invoke(iterator, noArgs);
      while (!done) {
	if (iterator == null) {
	  done = true;
	  System.out.println("\nComponent = null.  Could not get hWnd");
	} else if (peer instanceof LightweightPeer) {
	  iterator = iterator.getParent();
	  location = iterator.getLocation();
	  xOffset += location.x;
	  yOffset += location.y;
	  peer = (ComponentPeer) getPeerMethod.invoke(iterator, noArgs);
	} else {
	  done = true;
	  if (peer == null) {
	    System.out.println("\nComponent peer = null.  Could not get hWnd");
	  } else {
	    location = new Point(xOffset, yOffset);
	  }
	}
      }
    } catch (IllegalAccessException e) {
      peer = null;
      abort("illegal access exception: " + e.getMessage());
    } catch (InvocationTargetException e) {
      peer = null;
      abort("invocation target exception: " + e.getMessage());
    } finally {
      System.out.flush();
    }
    return peer;
  }



  /** In case of failure to obtain valid information about the
   *  native window, the constructor can print information
   *  about the type of failure.  That feature can be turned on
   *  or off by using setVerboseMode.
   */
  public static void setVerboseMode (boolean VerboseMode) {
    isVerbose = VerboseMode;
  }

  /** Returns the current status of whether or not to print
   *  failure information.
   */
  public static boolean getVerboseMode () {
    return isVerbose;
  }

  /** Returns the location of 
  * this component inside of the HWND
  */
  public Point getLocation() {
    if (isSupportedVM) {
      updateLocation();
      return location;
    } else {
      return new Point(0, 0);
    }
  }

  private static void abort (String message) {
    if (isVerbose) {
      System.out.println("Error:" + message);
      Thread.dumpStack();
      System.out.flush();
    }
  }

  @Override
  public boolean equals(Object object)
  {
    if (object instanceof Hwnd)
      return ((Hwnd) object).handleToPeer == handleToPeer;
    else return super.equals(object);
  }

  @Override
  public String toString()
  {
    return "com.gensym.com.Hwnd: " + handleToPeer;
  }
}
