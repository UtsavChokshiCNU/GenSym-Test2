
package com.gensym.wksp;

import java.util.Vector;
import com.gensym.ui.Command;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import com.gensym.message.Resource;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ui.Command;
import com.gensym.ui.menu.awt.CPopupMenu;

/**
 * A class that is used to determine the Commands that will
 * be used to generate a PopupMenu for the selection on a
 * WorkspaceView
 */
public final class SelectionCommandGenerator {
  
  private final Vector listOfCommands = new Vector (3);
  private static SelectionCommandsFactory factory = new DefaultSelectionCommandsFactoryImpl ();
  private static boolean factoryAlreadySet = false;
  private int mouseX, mouseY;

  private static boolean javaWillCrashWithPopupMenuTitle = true;
  static {
    try {
      javaWillCrashWithPopupMenuTitle = (System.getProperty ("os.name").toLowerCase().indexOf ("windows") >= 0);
    } catch (Exception e) {
      // Who cares?
    }
  }

  /**
   * Package private method for the DefWorkspaceViewEventHandler to call
   * to post a context menu for an Item
   */
  void postContextMenu (WorkspaceView view,
			Item itm,
			MouseEvent mEvt) {
    Item wksp = view.getItem();
    if (!(view.isVisible()&&wksp!=null&&wksp.isValid()&&itm.isValid())) return;
    try {
      Symbol itmClass_ = itm.getG2ClassName ();
      String itmClass  = WorkspaceUtil.computePrettyClassName (itmClass_.getPrintValue ());
      //System.out.println ("Posting context menu");
      CPopupMenu popup = new CPopupMenu();
      int totalCount = 0;
      if (!javaWillCrashWithPopupMenuTitle)
	popup.setLabel (itmClass);
      Vector commands = getRegisteredCommands ();
      for (int i=0; i<commands.size (); i++) {
	SelectionCommand cmd = (SelectionCommand)commands.elementAt (i);
	//System.out.println ("Processing #" + i + " of " + commands.size () +
	//" = " + cmd);
	cmd.setWorkspaceView (view);
	if (cmd instanceof CreationCommands) {
	  if (itm instanceof KbWorkspace)
	    popup.add (cmd);
	} else popup.add(cmd);
	int numItems = popup.getItemCount ();
	if (numItems != totalCount) { // Non empty group -- add Separator
	  totalCount = numItems;
	  if (i != (commands.size() - 1)) { // Last Group -- skip Separator
	    popup.addSeparator ();
	    totalCount++;
	  }
	} else if ((commands.size () != 1) && (i == (commands.size () - 1))) { // Added separator before
	  if (numItems > 0)
	  popup.remove (numItems - 1);                                        // & last group was empty - remove Separator
	}
      }
       view.add (popup);
      mouseX = mEvt.getX ();
      mouseY = mEvt.getY ();
      if (!view.isVisible()) return;
      //popup.show (view, mouseX, mouseY);
      com.gensym.uitools.utils.FontUtil.initMenuComponent
      (popup,
       com.gensym.uitools.utils.FontUtil.sanserifPlain11);
      view.showPopup(popup, mouseX, mouseY);
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
    }
  }

  /**
   * Retruns the most recent location of a menu
   * posting
   */
  Point getLastPostingLocation () {
    return new Point (mouseX, mouseY);
  }

  /**
   * Adds a SelectionCommand to the list of Commands that
   * will be asked to contribute to the PopupMenu that is
   * posted for any Item
   */
  public synchronized void registerCommand (SelectionCommand cmd) {
    listOfCommands.addElement (cmd);
  }

  /**
   * Returns the list of SelectionCommands currently registered
   * to contribute to the Item PopupMenu
   */
  public synchronized Vector getRegisteredCommands () {
    return (Vector) listOfCommands.clone ();
  }

  /**
   * Removes a SelectionCommand from he list of Commands that
   * will be asked to contribute to the PopupMenu that is
   * posted for any Item
   */
  public synchronized void deregisterCommand (SelectionCommand cmd) {
    listOfCommands.removeElement (cmd);
  }

  /**
   * Sets the factory that generates the initial set
   * of SelectionCommands.
   */
  public static void setSelectionCommandsFactory (SelectionCommandsFactory factory) {
    if (factoryAlreadySet)
      throw new RuntimeException ();
    if (factory == null)
      throw new RuntimeException ("Cannot set null factory!");
    factoryAlreadySet = true;
    SelectionCommandGenerator.factory = factory;
  }

  /**
   * Only the WorkspaceView creates a SelectionCommandGenerator
   */
  public SelectionCommandGenerator (WorkspaceView wkspView) {
    Command[] defaultCommands = factory.createCommands (wkspView);
    for (int i=0; i<defaultCommands.length; i++)
      listOfCommands.addElement (defaultCommands[i]);
  }
}

/**
 * Our default implementation of the SelectionCommandsFactory.
 * We need to document the behaviour after we are certain of
 * what it should be. Keep private for now -vkp, 5/7/98
 */
class DefaultSelectionCommandsFactoryImpl implements SelectionCommandsFactory {
  
  @Override
  public SelectionCommand[] createCommands (WorkspaceView view) {
    return new SelectionCommand[] {//new StandardItemCommands (),
                                    new CreationCommands (),
			            new SystemMenuChoiceCommands (),
				    new BeanCommands (),
				    new UserMenuChoiceCommands ()};
  }

}
