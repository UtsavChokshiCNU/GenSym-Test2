/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 com.gensym.com.ActiveXGenericComponent.java
 *
 *   Author: John Valente, Allan Scott
 */
package com.gensym.com;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.Rectangle;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyVetoException;

/** This class can be used to represent any Insertable ActiveX component.
 *  When it is added into an AWT Container, it pops up a dialog box so
 *  the user may select which type of ActiveX component it should be.
 */
public class ActiveXGenericComponent extends ActiveXDefaultComponentImpl
{
  private static final int MAX_WIDTH  = 1000;
  private static final int MAX_HEIGHT =  800;

  /* classID is a static field in ActiveXComponent because,
   * by default, a particular ActiveXComponent will have
   * a particular class ID.  However, this Java class can be used
   * to implement many different ActiveX classes, so the classID
   * must be on a per-instance basis.
   */
  private Guid classID = null;

  /** @undocumented */
  public native static ActiveXModes prompt_for_insert_object(int hWnd);

  /** The constructor sets the size and makes the control visible by
   *  default
   */
  public ActiveXGenericComponent () {
      setSize(400, 300);
      setVisible(true);
  }

  
  /** Called automatically by the (AWT) container when this object is
   *  added.  Instantiating an GenericActiveXObject does next to nothing.  It
   *  is not until it is added to a container that it begins
   *  "running".  The addNotify method causes a modal dialog box to
   *  come up and ask the user to select an object.  At that point, if
   *  the user did not hit "Cancel", the ActiveX server is started up.
   *  If the user did cancel the dialog box, then this will be a
   *  pretty useless object.  However, calling remapObject() will
   *  re-prompt the user to select an object and so can be used to
   *  start up the server at a later time.  Also, calling setClassID()
   *  can be used to start up a server without prompting if the
   *  class ID is known ahead of time.
   */
  @Override
  public void addNotify () {
    super.addNotify();
    if (!hasBeenAdded) {
      hasBeenAdded = true;
      hWnd = new Hwnd(this);
      if (hWnd.handleToPeer == Hwnd.NO_HWND) {
	message(AX_ERROR, "Failed to obtain HWND for " + this);
	return;
      }
      message(AX_PROGRESS, "HWND for " + this + " = " + hWnd);

      try {
        insertObject();
      }
      catch (ActiveXException e) {
          message(AX_ERROR, "Failed to create ActiveXProxy" + e);
	  return;
      }
      message(AX_DATA_DUMPS, "made new ActiveXProxy! = " + axProxy);
    }
  }


  private synchronized void insertObject () throws ActiveXException {
    ActiveXModes modes;
    
    axProxy = null;

    modes = promptForInsertObject(hWnd.handleToPeer);
    if (modes == null) {
      return;
    }

    classID = modes.getClassID();
    if (classID == null) {
      return;
    }

    axProxy = new ActiveXProxy(hWnd, modes, this);
  }

  /** Can be used to re-prompt the user and start up a server if
   *  "Cancel" was selected when the object was added to its
   *  container.  The name suggests that this method can be used to
   *  switch an GenericActiveXObject from one to another.  However, that's
   *  not implemented (yet?).
   */
  public void remapObject () throws ActiveXException {
    if (classID == null) {
        insertObject();
    } else {
      message(ERROR, "Will not remap object while current object " +
	      "is running");
    }
  }


  /** Can be used to start up a server if the class ID is known
   *  and the object is not running.  If there is already a 
   *  running server inside this object, the attempt to set
   *  the class ID will be rejected.
   */
  @Override
  public synchronized void setClassID (Guid classID) 
    throws PropertyVetoException
  {
    if ((this.classID == null) && (axProxy == null)) {
      this.classID = classID;
      try {
        axProxy = new ActiveXProxy(hWnd, new ActiveXModes(classID), this);
      }
      catch (ActiveXException e)
      {
        throw new PropertyVetoException("Could not create ActiveXProxy for classID",
                    new PropertyChangeEvent(this, "classID",
                                            this.classID, classID));  
      }
    } else {
      super.setClassID(classID);
    }
  }


  /** Does a setOpenInWindow(boolean) if the given int
   *  matches the clientSite of this object.
   */
/*
  public boolean setOpenInWindow(int clientSite, boolean isOpen) {
    if (axProxy == null)
      return false;

    if (this.clientSite == clientSite) {
      setOpenInWindow(isOpen);
      return true;
    }

    return false;
  }
*/

  /** Constructs and displays a modal dialog box which asks the
   *  user to select an ActiveX control from a list of insertable
   *  objects, and returns a Guid corresponding to the control 
   *  that the user chose.
   */
  public static ActiveXModes promptForInsertObject(int hWnd) {
    ActiveXModes modes;
    Guid clsid;

    modes = NativeMethodBroker.promptForInsertObject(hWnd);	
    clsid = modes.getClassID();

    if (clsid.isNullGuid())
      return null;

    return modes;
  }


  /** Return a String that represents this component
   */
  @Override
  public String toString() {
    Dimension size = getSize();
    int width = size.width;
    int height = size.height;
    if (hWnd == null) {
      return("a ActiveXGenericComponent (package com.gensym.com), " + 
	     ((classID == null) ? "ID = null" : classID.toString()) +
	     ", containing " + axProxy +
	     "of size  [" + width + ", " + height + "]");
    } else {
       
      return("a ActiveXGenericComponent (package com.gensym.com), " + 
	     ((classID == null) ? "ID = null" : classID.toString()) +
	     ", containing " + axProxy +
	     ", at (" + 0 + ", " + 0 + "),  " +
	     "of size  [" + width + ", " + height + "]");
    }
  }
}
