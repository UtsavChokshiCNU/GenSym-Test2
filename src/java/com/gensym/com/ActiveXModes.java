/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 com.gensym.com.ActiveXModes.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

import java.io.Serializable;

/** The class <code>ActiveXModes</code> is used to control how an
 *  ActiveX component is created, located, and activated.
 * <p>
 *  Instances of this class are passed to the constructor of
 * <code>ActiveXProxy</code> to provide information on which
 *  class to create and the creation, location and activation
 *  policy to follow.
 * <p>
 *  The constructors of ActiveXModes use bitflags that are defined in
 *  <code>ActiveXRuntimeConstants</code>.
 * <p>
 *  @see ActiveXProxy;
 *  @see com.gensym.com.Guid
 *  @see ActiveXRuntimeConstants
 */
public class ActiveXModes implements Serializable, ActiveXRuntimeConstants 
{

  static final long serialVersionUID = 833040316939062118L;

  private static final int DEFAULT_MODES = 0;

  private Guid classID;
  private int modes;
  private String fileLocationIfAny;
  private String remoteHostIfAny;
  private License license;

  /** Construct an <code>ActiveXModes</code> object,
   *  with an associated license
  */
  public ActiveXModes(Guid classID,
		      int modes,
		      String fileLocationIfAny,
		      String remoteHostIfAny,
                  License license) {
    this.modes = modes;
    this.fileLocationIfAny = fileLocationIfAny;
    this.remoteHostIfAny = remoteHostIfAny;
    this.classID = classID;
    this.license = license;
  }
	
  /** Construct an <code>ActiveXModes</code> object.
  */
  public ActiveXModes(Guid classID,
		      int modes,
		      String fileLocationIfAny,
		      String remoteHostIfAny) {
    this.modes = modes;
    this.fileLocationIfAny = fileLocationIfAny;
    this.remoteHostIfAny = remoteHostIfAny;
    this.classID = classID;
  }

  /** Construct an <code>ActiveXModes</code> object,
   * providing bitflags that control creation
   * activation and location.
   */
  public ActiveXModes(Guid classID, int modes) {
    this(classID, modes, null, null);
  }

  /** Construct an <code>ActiveXModes</code> object
  * using the default creation, activation and location
  * modes, and an associated license.
  */
  public ActiveXModes(Guid classID, License license) {
    this(classID, DEFAULT_MODES, null, null, license);
  }

  /** Construct an <code>ActiveXModes</code> object,
   * providing bitflags that control creation
   * activation and location, and an associated license.
   */
  public ActiveXModes(Guid classID, int modes, License license) {
    this(classID, modes, null, null, license);
  }

  /** Construct an <code>ActiveXModes</code> object
  * using the default creation, activation and location
  * modes.
  */
  public ActiveXModes(Guid classID) {
    this(classID, DEFAULT_MODES, null, null);
  }

  /** Does this ActiveXModes specify the creation of
  * a new ActiveX component?
  */
  public boolean isCreateNew() {
    return ((modes & AX_CREATE_LINK) == 0); 
  }

  /** Does this ActiveXModes specify linking to an
  * existing ActiveX component or an existing file?
  */
  public boolean isLink() {
    return ((modes & AX_CREATE_LINK) != 0); 
  }

  /** Does this ActiveXModes specify creating an
  * ActiveX component from a file?
  */
  public boolean isCreateFromFile() {
    return ((modes & AX_CREATE_FROM_FILE) != 0); 
  }

  /** Does this ActiveXModes specify that the
  * component being created is not an insertable
  * OLE document?
  */
  public boolean isNotInsertable() {
    return ((modes & AX_NOT_INSERTABLE) != 0);
  }

  /** Return the classID associated with this
  * ActiveXModes.
  */
  public Guid getClassID() {
    return classID;
  }

  /** Return the License associated with this 
  * ActiveXModes
  */
  public License getLicense() {
    return license;
  }

  /** Return the file location that this ActiveXModes
  * specifies if indeed it does.  Can return null if
  * this ActiveXModes specifies none.
  */
  public String getFileLocationIfAny() {
    return fileLocationIfAny;
  }

  /** Return a string that represents this ActiveXModes.
  */
  @Override
  public String toString() {
    return "<ActiveXModes, " + classID +
      ", modes = " + Integer.toBinaryString(modes) + 
      ", fileLocationIfAny = " + fileLocationIfAny + 
      ", remoteHostIfAny = " + remoteHostIfAny + ">";
  }

}
