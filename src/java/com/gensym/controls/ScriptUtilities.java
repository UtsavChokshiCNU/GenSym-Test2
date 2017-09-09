package com.gensym.controls;

import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;

/** The ScriptUtilities component allows scripting languages
 * such as visual basic access to important static methods.
 * that could not be seen otherwise.  Ignore it if you are not
 * using Telewindows2 components from a ActiveX scripting 
 * Environment.
 */

public class ScriptUtilities implements java.io.Serializable
{
  static final long serialVersionUID = 1569286896131415352L;
  public ScriptUtilities()
  {

  }

  /** internSymbol() makes a new symbol from a string for the
   *  various api's in com.gensym.controls that require symbols.
   * @see com.gensym.util.Symbol.
   */
  public Symbol internSymbol(String string)
  {
    return Symbol.intern(string);
  }

  /**
   * For VB use since it cannot call setPropertyValue (java.lang.Object)
   * on an ItemProxy.
   */
  public void setStringPropertyValue (ItemProxy proxy, String attrName, java.lang.String newValue) throws G2AccessException {
    proxy.setPropertyValue (attrName, newValue);
  }

  /**
   * @undocumented For VB use because of bug passing ""
   */
  public void setEmptyStringPropertyValue (ItemProxy proxy, String attrName) throws G2AccessException {
    proxy.setPropertyValue (attrName, "");
  }

  /**
   * For VB use since it cannot call setPropertyValue (java.lang.Object)
   * on an ItemProxy.
   */
  public void setIntPropertyValue (ItemProxy proxy, String attrName, int newValue) throws G2AccessException {
    proxy.setPropertyValue (attrName, new Integer(newValue));
  }

  /**
   * For VB use since it cannot call setPropertyValue (java.lang.Object)
   * on an ItemProxy.
   */
  public void setDoublePropertyValue (ItemProxy proxy, String attrName, double newValue) throws G2AccessException {
    proxy.setPropertyValue (attrName, new Double(newValue));
  }

  /**
   * For VB use since it cannot call setPropertyValue (java.lang.Object)
   * on an ItemProxy.
   */
  public void setBooleanPropertyValue (ItemProxy proxy, String attrName, boolean newValue) throws G2AccessException {

    proxy.setPropertyValue (attrName, newValue ? Boolean.TRUE : Boolean.FALSE);
  }

  /**
   * For VB use since it cannot call setPropertyValue (java.lang.Object)
   * on an ItemProxy. This method deals specifically with the difficulty
   * in passing in a boolean value across the Java Plugin's bean bridge.
   */
  public void setPseudoBooleanPropertyValue (ItemProxy proxy, String attrName, int newValue) throws G2AccessException {

    proxy.setPropertyValue (attrName, (newValue != 0) ? Boolean.TRUE : Boolean.FALSE);
  }

  /**
   * @undocumented for VB/Plug-in problem with booleans.
   */
  public void setAutoUploadForVB (ItemProxy proxy, int autoUploadPseudoBoolean)
  {
    proxy.setAutoUpload(!(autoUploadPseudoBoolean == 0));
  }

  /**
   * @undocumented for VB/Plug-in problem with booleans.
   */
  public void setAutoDownloadForVB (ItemProxy proxy, int autoDownloadPseudoBoolean)
  throws G2AccessException {
    proxy.setAutoDownload(!(autoDownloadPseudoBoolean == 0));
  }

  /**
   * @undocumented Needed for method dispatch in VB to work around
   * Plug-in bug of not delivering exceptions
   */
  public Object getThis () {
    return this;
  }

  /**
   * @undocumented Needed to make instance for VB
   */
  public Object makeInstance(String className) throws ClassNotFoundException,
  InstantiationException, IllegalAccessException {
    ClassLoader loader = getClass().getClassLoader();
    Class clazz;
    if (loader == null)
      clazz = Class.forName(className);
    else
      clazz = loader.loadClass(className);
    return clazz.newInstance();
  }
}
