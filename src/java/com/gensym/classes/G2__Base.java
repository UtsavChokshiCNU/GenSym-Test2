
package com.gensym.classes;

import java.net.MalformedURLException;
import java.util.Vector;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.ExportedG2Class;

public interface G2__Base extends ExportedG2Class {
  public java.lang.Object getPropertyValue (Symbol attrName) throws G2AccessException,
                                                                    NoSuchAttributeException;

  public void setPropertyValue (Symbol attrName, java.lang.Object newValue) throws G2AccessException;

  public Sequence getVisibleAttributes (Symbol userMode) throws G2AccessException;

  public Structure getAttributeValues (Sequence attrNames) throws G2AccessException;

  public Sequence getAttributeDescriptions () throws G2AccessException;

  public Sequence getAttributeDescriptions (Sequence specificAttributes) throws G2AccessException;

  public void processItemEvent (com.gensym.util.ItemEvent e);

  /** 
   * @deprecated
   * This method is no longer useful, what remains is a stub which returns false.
   */
  public boolean isLocallyCached ();

  /** 
   * @deprecated
   * This method is no longer useful, what remains is a stub.
   */
  public void setLocallyCached (boolean cacheLocally);

  public Structure getDialog (Symbol userMode, Structure locale) throws G2AccessException, MalformedURLException;

  /** 
   * This method looks up a value of an attribute in the Items local Cache and does not cause an
   * RPC call to G2 for the item.
   * When Items are sent from G2 to Java BY-COPY-AND-HANDLE, they may be created with 
   * pre initialized attribute values sent from G2. This method can be used to retrieve these values
   * without causing an RPC call to G2.
   */
  public java.lang.Object getCachedAttributeValue(Symbol attrName, java.lang.Object defaultValue);

  /**
   * Is this object operating remotely ? 
   * An G2 Item sent from G2 can be sent as;
   * 1. "BY HANDLE" in which case this Item represents a remote G2 object.
   * 2. "BY COPY" the object is locally held and has no relation to an exisiting G2 Object. 
   */
  public boolean isItemLocal ();

  /**
   * The G2 named equivalent of <code>instanceof</code>.
   * Use instead of getting the class from G2 in order to call
   * instanceOf(). This method doesn't require that the class named by
   * <code>g2ClassName_</code> be loaded on the client.
   * @return <code>true</code> if "<item> is a <g2ClassName_>" would return
   * <code>true</code> for this item in G2, false otherwise
   */
  public boolean isInstanceOfG2Class (Symbol g2ClassName_);

  /**
   * Returns a G2Definition object corresponding to the class of this
   * Item. If this is an instance of a user-defined class then the
   * G2Definition will be a <code>Definition</code> (an abstract class). It will
   * be one of : <code>ClassDefinition</code>, <code>ObjectDefinition</code>,
   * <code>MessageDefinition</code>, or <code>ConnectionDefinition</code>.
   * @return A G2Defintiion for the class of this Item
   * @exception G2AccessException if there are any communication problems
   */
  public G2Definition getDefinition () throws G2AccessException;
  
  /**
   * start the named method on the Item in G2
   * @param methodName the name of the method to call
   * @param args the arguments to the method
   * @throws G2AccessException On Communication error
   * @see #com.gensym.jgi.G2Gateway.startRPC
   */
  public void startMethod (Symbol methodName, java.lang.Object[] args) throws G2AccessException;

  /**
   * Call the named method on the Item in G2
   * @param methodName the name of the method to call
   * @param args the arguments to the method
   * @param timeOut the time-out for the call in milliseconds
   * @return the return value of the call or a Sequence containing
   * the multiple return values of the call.
   * @throws G2AccessException On Communication error or in the procedure call
   * @see #com.gensym.jgi.G2Gateway.callRPC
   */
  public java.lang.Object callMethod (Symbol methodName, java.lang.Object[] args, int timeOut)
     throws G2AccessException;

  // The following two methods are accessors to optimization snapshots
  // of some specific pieces of Item state. For WorkspaceView use only!

  /**
   * This returns the snapshot of the configuration that was sent
   * when the item was downloaded as part of representWorkspace.
   * For WorkspaceView use only!
   * @throws G2AccessException Can call G2 when is called on a KbWorkspace
   * for the first time
   * @undocumented
   */
  public Sequence getItemConfigurationSnapshot() throws G2AccessException;

  /**
   * Returns the ConnectionStyle snapshot that was sent
   * when the item was downloaded as part of representWorkspace.
   * For WorkspaceView use only!
   * @undocumented
   */
  public Symbol getConnectionStyleSnapshot();

  /**
   * @undocumented
   */
  public Vector getCompleteConfigurationSnapshot() throws G2AccessException;

  /**
   * Return the validity status of an item.  An item becomes invalid if there
   * has been a change in or deletion of the item on the G2 side.
   * 
   */
  public boolean isValid();

  /** 
   * If called with true any attributes set on a "by-handle" item will not be 
   * written to the G2 item, but cached until flushAttributeWriteCache is called.
   * @param status set true to enable the AttributeWritesCache.
   */
  public void setAttributeWritesAreCached(boolean status);

  /**
   * Return the status of the AttributeWriteCache.
   * @return false == The AttributeWriteCache is disabled, any attribute sets
   *                  will be passed to the G2 item (default).
   *         true  == The AttributeWriteCache is enabled, any attribute sets
   *                  will be not be passed to G2, until flushAttributeWriteCache is called.
   */
  public boolean isAttributeWritesCached();

  /**
   * Send any attribute updates currently "waiting" to be written back to 
   * the item in G2 from the AttributeWriteCache. The attribute changes are sent
   * using one network call.
   */
  public void flushAttributeWriteCache() throws G2AccessException;

}
