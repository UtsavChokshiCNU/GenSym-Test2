
package com.gensym.dlgruntime;

/**
 * The event that encapsulates the state of a
 * launched dialog.
 */
public class DialogStateEvent extends java.util.EventObject {

  /**
   * Type constant indicating that the user
   * has requested a flush of the dialog
   * contents.
   */
  public static final int FLUSH = 0;

  /**
   * Type constant indicating that the user
   * has requested a shutdown of the dialog.
   */
  public static final int SHUTDOWN = 1;

  /**
   * Type constant indicating that the
   * dialog is being launched
   */
  public static final int LAUNCH = 2;

  private int id;

  /**
   * Create a DialogStateEvent with the specified source
   * @param source the source of the event
   * @param id indicates the type of the event
   */
  public DialogStateEvent (Object source, int id) {
    super (source);
    this.id = id;
  }

  /**
   * Returns the type of the event
   * @see #FLUSH
   * @see #SHUTDOWN
   */
  public int getID () {
    return id;
  }

}
