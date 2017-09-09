
package com.gensym.dlgruntime;

import java.net.URL;

import com.gensym.message.Resource;

public class DialogResource {

  private static Resource i18n = Resource.getBundle("com.gensym.dlgruntime.Messages");

  static volatile DialogReader defaultReader;
  static DialogReader classReader = new DialogClassReader();

  static volatile DialogLauncher defaultLauncher;

  /**
   * The resourceDescription for the resource
   */
  Object resourceDescription;

  /**
   * A reference to the DialogLauncher that is capable of launching this
   * resource.
   */
  private DialogLauncher launcher;

  /**
   * A reference to the DialogResource that knows how to read the resource data
   * from the resourceDescription and also how to create the resource Object.
   */
  private DialogReader reader;

  /**
   * A PageLayout/PageGroup etc.
   */
  Object resource;

  /**
   * The bytes comprising the resource
   */
  Object resourceData;

  /**
   * Redundant?
   */
  int resourceLength;

  /**
   * Make a new DialogResource with a default reader and launcher.
   * @param resourceDescription can be a URL specifying the location
   * of a serialized resource, or a String specifying the name
   * of a Java class.
   */
  public DialogResource (Object resourceDescription) {
    this (resourceDescription, null, null);
  }

  public DialogResource (Object resourceDescription, DialogReader reader, DialogLauncher launcher) {
    this.resourceDescription = resourceDescription;
    this.reader      = reader;
    this.launcher    = launcher;
  }

  /**
   * Called by the DialogManager.
   */
  public DialogReader getDialogReader() {
    if (reader == null) {
      if (resourceDescription instanceof URL)
	reader = defaultReader;
      else if (resourceDescription instanceof String)
	reader = classReader;
      else
	throw new RuntimeException(i18n.format("drInvalidResourceDescription",
					      resourceDescription));
    }
    return reader;
  }

  public DialogLauncher getDialogLauncher() {
    if (launcher == null)
      launcher = defaultLauncher;

    return launcher;
  }

  /**
   * Invokes readResource on the reader with the resourceDescription of the resource and saves the data
   * returned from this call.
   */
  public void readResource () throws java.io.IOException {
    resourceData = getDialogReader().readResource (resourceDescription);
  }

  /**
   * The setResouceData method is only available for subclasses of DialogResource
   * in order that serialized dialogs can be placed directly in resources, normally
   * for testing purposes.
   */
  protected void setResourceData(byte[] data)
  {
    resourceData = data;
  }

  /**
   * Deserializes the resource from the locally held data. If this data has not
   * been read, readResource is called first.
   */
  public Object makeResource () throws ResourceInstantiationException {
    try {
      if (resourceData == null)
	readResource ();
    } catch (java.io.IOException ioe) {
      throw new ResourceInstantiationException ("Exception in reading resource data.", ioe);
    }
    return reader.makeResource (resourceData);
  }

  /*
   * Maybe add a convenience method for launching?
   */

  /*
   * Should WE ensure use of the reader and launcher are thread-safe?
   */
  /**
   * Register a reader that is to be used when one is not
   * passed in. Should only be called once.
   */
  public static void registerReader (DialogReader reader) {
    defaultReader = reader;
  }

  public static DialogReader getRegisteredReader()
  {
    return defaultReader;
  }

  /**
   * Register a launcher that is to be used when one is not passed in.
   * Should only be called once
   */
  public static void registerLauncher (DialogLauncher launcher) {
    defaultLauncher = launcher;
  }

  public static DialogLauncher getRegisteredLauncher()
  {
    return defaultLauncher;
  }

  /**
   * Returns a string representation of the object. Describes the resourceDescription,
   * the reader, and the launcher
   */
  @Override
  public String toString () {
    return super.toString () + "[resourceDescription=" + resourceDescription +
      ",reader=" + reader +
      ",launcher=" + launcher + "]";
  }
}
