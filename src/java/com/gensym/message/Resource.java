package com.gensym.message;

import java.util.*;
import java.io.IOException;
import java.text.MessageFormat;

/** A helper class that aids in the debugging of resource providing
 * and assists in making resource usage simpler. It is a wrapper around
 * java.util.ResourceBundle.
 * <p>
 * Debugging: After Resource.setResourceDebug(true) is called, when a resource
 * is not found, rather than throwing an
 * exception, the various format and getString methods
 * return the key and print an error message to standard out.
 * <p>
 * Convenience: the various <code>format</code> methods take both the message
 * lookup key, and the arguments that should be used to substitute into the
 * variable parts of the found string. For this it uses
 * java.text.MessageFormat.
 * <p>
 * Additional Functionality: This class is Serializable, and it achieves this
 * by looking up the associated ResourceBundle during the readObject() method.
 * @author Robert Penny
 * @version 1.2
 * @see java.util.ResourceBundle
 * @see java.text.MessageFormat
 */

public class Resource implements java.io.Serializable {
  //
  // class members
  //
  
  protected static boolean resourceDebug = false;
  private static ResourceBundle i18n;
  //  
  private static String missingBundleString =
  "Unable to locate bundle \"{0}\", because: \"{1}\"";
  private static String missingLookupString =
  "Unable to locate resource \"{0}\" in bundle \"{1}\", because: \"{2}\"";
  private static String mismatchedLookupString =
  "The key \"{0}\" in the resource named \"{1}\" resulted in the template \"{2}\", which did not match the arguments: {3}";
  private static String unknownMessage = "UNKNOWN_MESSAGE";

  static {
    try {
      i18n = ResourceBundle.getBundle("com.gensym.message.Messages");
      missingBundleString = i18n.getString("Resource_unableToLocateBundle");
      missingLookupString = i18n.getString("Resource_unableToLocateString");
      mismatchedLookupString = i18n.getString("Resource_mismatchedLookupString");
      unknownMessage = i18n.getString("Resource_unknownMessage");
    } catch (Exception mre) {
      mre.printStackTrace();
    }
  }

  // will be overriding the pattern, so would prefer if there was a no-arg
  // constructor, so just putting in any old string
  private static MessageFormat fmt = new MessageFormat(missingBundleString);
  private static final boolean debug = false;
  private static volatile Locale defaultLocale;
  private static Hashtable localeTable = new Hashtable();

  //
  // instance members
  //

  private transient ResourceBundle realBundle;
  private transient Locale locale;
  private transient boolean damagedBundle;
  private String resourceName;

  /** package private constructor to enable DummyResource to work.
   */
  Resource(String resourceName) {
    this.resourceName = resourceName;
    initializeLocale();
  }
    
  /** Acts as a forwarder to vanilla ResourceBundles */
  protected Resource (String resourceName, Locale locale)
  throws MissingResourceException {
    //System.out.println("makingResource: " + resourceName);
    this.resourceName = resourceName;
    this.locale = locale;
    initializeLocale();
  }

  private void initializeLocale() {
    if (locale == null)
      locale = getDefaultLocale();
  }

  /** This method is made protected in order allow an application a chance
   * to provide a new "realBundle" (e.g., create a new .properties file)
   * and re-initialize the Resource. */
  protected void initializeBundle() throws MissingResourceException {
    try {
      realBundle = ResourceBundle.getBundle(resourceName, locale);
      damagedBundle = false;
    } catch (MissingResourceException mre) {
      damagedBundle = true;
      if (resourceDebug) {
	mre.printStackTrace();
      } else {
	mre.fillInStackTrace();
	throw mre;
      }
    }
  }

  public String getResourceName() {
    return resourceName;
  }

  public static void setDefaultLocale (Locale locale) {
    defaultLocale = locale;
  }

  public static Locale getDefaultLocale () {
    if (defaultLocale == null) {
      return Locale.getDefault();
    }
    return defaultLocale;
  }

  public static Resource getBundle(String resourceName) {
    return getBundle(resourceName, getDefaultLocale());
  }

  public static Resource getBundle(final String resourceName, final Locale locale) {
    //System.out.println("getBundle: " + resourceName);
    Locale localeObj = (locale == null ? getDefaultLocale() : locale);
    Hashtable bundleTable = (Hashtable)localeTable.get(localeObj);
    if (bundleTable == null) {
      bundleTable = new Hashtable();
      localeTable.put(localeObj, bundleTable);
    }
    Resource resource = (Resource)bundleTable.get(resourceName);
    if (resource == null) {
      resource = new Resource(resourceName, localeObj);
      bundleTable.put(resourceName, resource);
    }
    return resource;
  }
  
  /** Controls exception throwing of <code>getString()</code>.
   * @param on If <code>on</code> is <code>true</code>, then
   * instead of throwing an exception, <code>getString()</code>
   * will print a log message.
   * @see Resource#getString
   */
  public static void setResourceDebug(boolean on) {
    resourceDebug = on;
  }

  private void readObject(java.io.ObjectInputStream in)
  throws IOException, ClassNotFoundException {
    try {
      in.defaultReadObject();
    } catch (java.io.NotActiveException ex) {
      if (resourceDebug)
	ex.printStackTrace();
    }
    initializeLocale();
  }

  public String getString(String key) throws MissingResourceException {
    if(debug)
      System.out.println("Entered Resource.getString: " + key);

    if (realBundle == null) {
      if (damagedBundle) {
	if (resourceDebug)
	  return key;
      } else {
	initializeBundle();
	if (damagedBundle && resourceDebug)
	  return key;
      }
    }
    
    String value = null;
    try {
      value = realBundle.getString(key);
    } catch (MissingResourceException ex) {
      Object[] args = {key, resourceName, ex.getMessage()};
      // can think of no tidier way that avoids recursion:
      fmt.applyPattern(missingLookupString);
      StringBuffer errorMessage = fmt.format(args, new StringBuffer(), null);
      String errorMessageString = errorMessage.toString ();
      if (resourceDebug)
	System.out.println(errorMessageString);
      value = unknownMessage;
      if(!resourceDebug) {
	throw new MissingResourceException (errorMessageString, resourceName, key);
      }
    }
    return value;
  }


  /** Format the message using the message template retrieved by <code>key</code>
   * @see java.text.MessageFormat
   */
  public String format(String key, Object[] args) throws
  MissingResourceException{
    if(debug)
      System.out.println("Entered Resource.format: " + Arrays.toString(args) + " " + key);
    
    String messageTemplate = getString(key);
    if (args == null) {
      return messageTemplate;
    }
    
    Object arg = null;
    for (int i = 0 ; i<args.length; i++) {
      arg = args[i];
      if (arg == null)
	args[i] = "<NULL>";
      else
	args[i] = arg.toString();
    }
    
    try {
      fmt.applyPattern(messageTemplate);
      return fmt.format(args, new StringBuffer(), null).toString();
    } catch (IllegalArgumentException ex) {
      if (resourceDebug)
	ex.printStackTrace();
      else
	throw ex;

      Object[] errorArgs = {key, resourceName, messageTemplate, Arrays.toString(args)};
      try {
	fmt.applyPattern(mismatchedLookupString);
	StringBuffer errorMessageBuffer = fmt.format(errorArgs,
						     new StringBuffer(),
						     null);
	String errorMessage = errorMessageBuffer.toString();
	System.out.println(errorMessage.toString());
      } catch (Exception ex2) {
	ex2.printStackTrace();
      }
      return key;
    }
  }
  
  private Object[] oneArg = new Object[1];
  private Object[] twoArgs = new Object[2];

  /** convenience method that also reduces garbage collection */
  public String format(String key, Object arg) throws MissingResourceException {
    oneArg[0] = arg;
    return format(key, oneArg);
  }

  /** convenience method that also reduces garbage collection */
  public String format(String key, Object arg1, Object arg2)
       throws MissingResourceException {
    twoArgs[0] = arg1;
    twoArgs[1] = arg2;
    return format(key, twoArgs);
  }

  String toStringString;

  @Override
  public String toString() {
    if (toStringString == null) {
      String resourceString = (realBundle == null ? resourceName :
			       realBundle.toString());
      toStringString = getClass().getName() + "[" + resourceString + "]";
    }
    return toStringString;
  }

  @Override
  public boolean equals(Object obj) {
    if (obj == null || !getClass().equals(obj.getClass())) {
      return false;
    }
    Resource other = (Resource)obj;
    if (resourceName.equals(other.resourceName)) {
      return (locale.equals(other.locale));
    } else
      return false;
  }

  private int hashCode;
  private boolean hashCodeIsSet;

  @Override
  public int hashCode() {
    if (!hashCodeIsSet) {
      if (resourceName != null)
	// NOTE: Resources using different locales are usually
	// stored in different hashtables, so there is no need to
	// incur the overhead of modifying the hashCode to incorporate
	// the locale.
	hashCode = resourceName.hashCode();
      hashCodeIsSet = true;
    }

    return hashCode;
  }
}
