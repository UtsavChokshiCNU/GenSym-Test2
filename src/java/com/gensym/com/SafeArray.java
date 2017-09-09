/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.SafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>SafeArray</code> is a representation in Java of the ActiveX
* safe array.  It is used with the <code>Variant</code> class as the
* generic way of representing array data that is passed to and from
* ActiveX controls.
* <p>
*/
public abstract class SafeArray implements ActiveXRuntimeConstants {

  /** @undocumented */
  static {
    NativeMethodBroker.loadLibrary();
  }

  /** @undocumented */
  private int handle = 0;

  /** @undocumented */
  protected SafeArray(short arrayType, int lBounds[], int uBounds[]) {
    createArray(arrayType, lBounds, uBounds);
  }

  /** @undocumented */
  protected SafeArray(short arrayType, int length) {
    int lBounds[] = {0};
    int uBounds[] = {length - 1};

    createArray(arrayType, lBounds, uBounds);
  }

  /** @undocumented */
  protected SafeArray(SafeArray array) {
    handle = array.copy();
  }

  /** @undocumented */
  protected SafeArray(int arrayHandle) {
    if (!claimHandle(arrayHandle))
       return;

    handle = arrayHandle;
  }

  /** @undocumented */
  private void createArray(short arrayType, int lBounds[], int uBounds[]) {
    if (lBounds == null || uBounds == null || uBounds.length != lBounds.length)
       return;

    handle = create(arrayType, lBounds, uBounds);
  }

  /** @undocumented */
  private native int create(short arrayType, int lBounds[], int uBounds[]);

  /** @undocumented */
  static private native boolean claimHandle(int handle);

  /** @undocumented 
  * The native code will call this to get our handle.
  */
  public int getHandle() {
    return handle;
  }

  /** Determines if two Java safe array objects reference the same native
  * data. */
  public native boolean isSameNativeArray(SafeArray safeArray);

  /** @undocumented Returns the type of the safe array as a constant in class
  * ActiveXRuntimeConstants. */
  abstract short getType();

  /** Creates a identical copy of this SafeArray. */
  @Override
  public abstract Object clone();

  /** @undocumented */
  private native int copy();

  /** Cleans up native resources, but only destroys the native safe array
  * if this is the last safe array object to reference the array (many
  * Java objects may reference the same native array) and ownership has been
  * given to Java. If the native resources are large and you do not want to
  * wait for garbage collection you may call dispose.
  */
  @Override
  protected void finalize() {
    nativeFinalize();
  }

  /** @undocumented */
  private native void nativeFinalize();

  /** This is a useful method for large safe arrays. It signals that this
  * object is done with the native safe array and it can be destroyed.
  * If it was the last SafeArray object to reference the native array
  * (many Java objects may reference the same native array)
  * the array will be destroyed if unlocked. The ownership of the array is not
  * checked. Returns true if the array was not locked, false if it was not
  * destroyed because the native safe array was locked. <p>
  * Note: This is optional, if the safe array is small you can let
  * the finalizer dispose of the safe array.
  */
  public boolean dispose() {
    boolean destroyed;

    destroyed = destroy();
    if (destroyed)
      handle = 0;

    return destroyed;
  }

  /** @undocumented */
  protected native boolean destroy();

  /** Returns true if this object references a native safe array. */
  public native boolean isValid();

  /** Returns true if this object owns the safe array. <p>
  * Note: More than one SafeObject can end up owning the same
  * native safe array. */
  public native boolean isOwner();

  /** Gets the number of dimensions of the native safe array. */
  public native int getDimensions();

  /** Gets the lower bound for a dimension of the native safe array.
  * The first dimension is 1.
  */
  public native int getLBound(int dimension);

  /** Gets the upper bound for a dimension of the native safe array.
  * The first dimension is 1.
  */
  public native int getUBound(int dimension);

  /** @undocumented */
  protected native void putElements(int indexes[], Object objects);

  /** @undocumented */
  protected native Object getElements(int indexes[], int n);

  /** @undocumented */
  protected native Object getAllElements();

  /** Increments the lock count of the native safe array. Calling destroy on
  * SafeArray that is locked does nothing which can be a cause of memory leaks.
  */
  public native void lock();

  /** Decrements the lock count of the native safe array. */
  public native void unlock();

  /** Take ownership of the native safe array so it can be destroyed
  * automatically by the finalize method.
  */
  public native void takeOwnership();

  /** Gives up ownership of the native safe array so an ActiveX control can
  * take ownership. This should be called when returning an array from an
  * event.
  */
  public native void giveUpOwnership();
}
