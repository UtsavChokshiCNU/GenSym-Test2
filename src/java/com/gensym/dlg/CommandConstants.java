
package com.gensym.dlg;

/**
 * A collection of constants for identifying the
 * types of command buttons in StandardDialogs.
 *
 * @author  : vkp
 * @version : 1.0 10/06/97
 * @version : 1.1 4/28/98  Added Javadoc
 */

public interface CommandConstants {

  /**
   * The OK command constant. Typically indicates
   * dismissal of the dialog by acceptance.
   */
  final int OK = 0;

  /**
   * The APPLY command constant. Typically indicates
   * a request to apply the changes without dismissing
   * the dialog.
   */
  final int APPLY = 1;

  /**
   * The CANCEL command constant. Typically indicates
   * a complete retraction of all changes.
   */
  final int CANCEL = 2;

  /**
   * The YES command constant. Typically indicates an
   * acceptance of an application request.
   */
  final int YES = 3;

  /**
   * The NO command constant. Typically indicates a
   * decline of an application request.
   */
  final int NO = 4;

  /**
   * The DISMISS command constant. Typically indicates
   * a request to dismiss an informational Dialog.
   */
  final int DISMISS = 5;

  /**
   * The HELP command constant. Typically indicates
   * a request for more information.
   */
  final int HELP = 6;

  /**
   * The CLOSE command constant. Typically indicates
   * a request to dismiss a general dialog.
   */
  final int CLOSE = 7;

}
