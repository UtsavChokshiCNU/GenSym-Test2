
package com.gensym.dlg;

import java.awt.*;
import java.awt.event.*;

/**
 * Class for displaying a simple error dialog to the user.
 * It has an appropriate icon and button for this kind of usage.
 * Applications should simply need to create a ErrorDialog and
 * display it: 
 * <p><blockquote><pre>
 *     ErrorDialog ed = new ErrorDialog (currentFrame, "Unexpected Error",
 *                                           true, "Exception reported\n" + ex, null);
 *     ed.setVisible (true);
 * </pre></blockquote>
 * Applications could use this to report illegal
 * states to the user.
 *
 * @author vkp
 * @version 1.1 4/28/98 added Javadoc
 *
 */ 
public class ErrorDialog extends IconDialog {

  private static Image img;
  private static final Class thisClass = com.gensym.dlg.ErrorDialog.class;

  static {
    img =  Toolkit.getDefaultToolkit ().getImage (thisClass.getResource ("bomb.gif"));
  }

  private ErrorDialog (String  title,
		       boolean isModal,
		       String  message,
		       StandardDialogClient client) {
    this (null, title, isModal, message, client);
  }

  /**
   * Creates a new ErrorDialog with the specified attributes.
   * An appropriate icon is used and an OK button is placed
   * on the dialog for the user to acknowledge the error notification.
   * @param frame the parent Frame
   * @param title the String to display in a title bar
   * @param isModal whether the dialog is modal
   * @param message a String containing the text of information that
   *    needs to be displayed to the user
   * @param client a StandardDialogClient that is notified of all
   *    commands generated by buttons on the dialog
   */
  public ErrorDialog (Frame   frame,
		      String  title,
		      boolean isModal,
		      String  message,
		      StandardDialogClient client) {
    this (frame, title, isModal, message, img, client);
  }

  /**
   * Creates a custom ErrorDialog.
   * Subclasses can use this to override the default properties
   * like the number and type of buttons, and the Image that
   * is displayed
   * @param frame the parent Frame
   * @param title the String to display in a title bar
   * @param isModal whether the dialog is modal
   * @param buttonLabels an array of String labels for the buttons
   *    at the bottom of the dialog
   * @param buttonCodes an array of codes for the buttons on the
   *    dialog
   * @param message a String containing the text of information that
   *    needs to be displayed to the user
   * @param img the Image to be displayed along with the message
   *    text
   * @param client a StandardDialogClient that is notified of all
   *   commands generated by buttons on the dialog
   */
  protected ErrorDialog (Frame frame, String title, boolean isModal,
			 String[] buttonLabels, int[] buttonCodes,
			 String message, Image img, 
			 StandardDialogClient client) {
    super (frame, title, isModal, buttonLabels, buttonCodes, 
	   message, (img != null ? img : ErrorDialog.img),
	   message.indexOf ("\n") >= 0, client);
  }

  private ErrorDialog (Frame frame, String title, boolean isModal,
		       String message, Image img,
		       StandardDialogClient client) {
    super(frame, title, isModal,
	  new String[] {OK_LABEL},
	  new int[] {OK},
	  message, img,
	  message.indexOf ("\n") >= 0,
	  client);
  }

  /**
   * Determines the alignment of the command buttons at the
   * bottom of the StandardDialog
   * @return a code indicating the preferred position of the buttons
   * @see com.gensym.dlg.StandardDialog#getButtonAlignment
   */
  @Override
  protected int getButtonAlignment () {
    return CENTER;
  }

  /**
   * Overrides setVisible in StandardDialog to beep at the user
   * if the dialog is being managed modally.
   * @param showQ true if the Dialog is being shown, false if
   *    hidden
   */
  @Override
  public void setVisible (boolean showQ) {
    if (isModal ())		// Does not work on solaris -vkp, 4/28/98
      Toolkit.getDefaultToolkit().beep ();
    super.setVisible (showQ);
  }

  /**
   * @undocumented
   */
  public static void main (String[] args) {
    MenuItem mi;
    Frame f = new Frame ("Inform Dialog Test");
    registerFrame (f);
    MenuBar mb = new MenuBar ();
    Menu fileMenu = new Menu ("File");
    fileMenu.add (mi = new MenuItem ("Open"));
    final StandardDialogClient sd = new StandardDialogClient () {
      @Override
      public void dialogDismissed (StandardDialog dlg, int code) {
      }
    };
    mi.addActionListener (new ActionListener () {
      @Override
      public void actionPerformed (ActionEvent e) {
	new ErrorDialog ("From Menu", true, "Message From Menu", sd).show ();
      }
    });
    mb.add (fileMenu);
    f.setMenuBar (mb);
    f.setSize (300, 300);
    f.setVisible (true);
    new Thread (new ErrorDialogLauncher ()).start ();
    System.out.println ("Showing second dialog");
    ErrorDialog d =new ErrorDialog ("Helloooooo...",
				    true,
				    "Line 0\nLine 1\nLine 2\nLine 3",
				    sd);
    d.show ();
  }

}

class ErrorDialogLauncher implements Runnable {
  @Override
  public void run () {
    StandardDialogClient sd = new StandardDialogClient () {
      @Override
      public void dialogDismissed (StandardDialog dlg, int code) {
      }
    };
    ErrorDialog d = new ErrorDialog (null,
				     "Blah...",
				     true,
				     com.gensym.core.DebugUtil.getStackTrace (),
				     sd);
    d.show ();
  }
}
