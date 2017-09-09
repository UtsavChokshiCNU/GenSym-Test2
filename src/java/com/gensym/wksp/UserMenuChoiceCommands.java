
package com.gensym.wksp;

import com.gensym.ui.StructuredCommand;
import java.util.Vector;
import java.util.Hashtable;
import java.awt.Image;
import com.gensym.ui.Command;
import com.gensym.ui.CommandListener;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.StructuredCommandListener;
import java.awt.event.ActionEvent;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.classes.Item;
import com.gensym.classes.UserMenuChoice;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.wksp.configurations.ConfigurationSupport;
import com.gensym.classes.ImplAccess;

/**
 * An implementation of the SelectionCommand interface that
 * exposes the applicable user-menu-choices of the selected
 * item(s) on the PopupMenu that is generated for the
 * selection.
 * @see com.gensym.wksp.SelectionCommandGenerator
 * @see com.gensym.wksp.SelectionCommand
 * 
 * @author vkp
 * @version 1.0 - 5/7/98
 *
 */
public class UserMenuChoiceCommands extends AbstractMenuChoiceCommands {

  private Vector userMenuChoices;
  private String[] userMenuChoiceLabels;

  private Item focalItem;
  private TwConnection cxn;

  /**
   * Creates a new UserMenuChoiceCommands that can be used to
   * generate PopupMenus for Items on workspaces.
   * @see com.gensym.wksp.SelectionCommandGenerator
   */
  public UserMenuChoiceCommands () {
    super (new String[0]);
  }

  @Override
  protected void reset () {
    currentSelection = null;
    userMenuChoices = null;
    focalItem = null;
    cxn = null;
  }

  /**
   * Returns a textual description for command.
   * The key should be either SHORT_DESCRIPTION or
   * LONG_DESCRIPTION. This method is overriden to
   * create a "pretty-printed" name.
   */
  @Override
  public String getDescription (String cmdKey, String key) {
    checkKey (cmdKey);
    int i;
    for (i=0; i<userMenuChoiceLabels.length; i++)
      if (userMenuChoiceLabels[i].equals (cmdKey))
	break;
    return WorkspaceUtil.computePrettyClassName (userMenuChoiceLabels[i]);
  }

  /**
   * Returns the keys for the actions that
   * can be performed by this command. This is
   * basically just a list of the labels of the
   * applicable user-menu-choices for the items
   * in the selection, or the kb-workspace if
   * the selection is empty.
   */
  @Override
  public Vector getStructuredKeys () {
    determineUserMenuChoices ();
    if (userMenuChoices == null)
      return new Vector (0);
    int numUMCs = userMenuChoices.size ();
    if (numUMCs > 0) {
      Vector umcLabels = new Vector (numUMCs);
      try {
	for (int i=0; i<numUMCs; i++) {
	  UserMenuChoice umc = (UserMenuChoice)userMenuChoices.elementAt (i);
	  Symbol umcLabel = umc.getLabel ();
	  umcLabels.addElement (umcLabel.getPrintValue ());
	}
      } catch (G2AccessException g2ae) {
	Trace.exception (g2ae);
      }
      return umcLabels;
    }
    return new Vector (0);
  }


  @Override
  protected void checkKey (String cmdKey) {
    for (int i=0; i<userMenuChoices.size (); i++) {
      if (cmdKey.equals (userMenuChoiceLabels[i]))
	return;
    }
    throw new IllegalArgumentException ("Unknown Key - <" + cmdKey + ">");
  }

  /**
   * The implementation of the execution of this
   * Command
   */
  @Override
  public void actionPerformed (ActionEvent e) {
    String commandKey = e.getActionCommand ();
    for (int i=0; i<userMenuChoices.size (); i++) {
      UserMenuChoice umc = (UserMenuChoice)userMenuChoices.elementAt (i);
      if (userMenuChoiceLabels[i].equals (commandKey)) {
	try {
	  executeMenuChoice (umc, focalItem);
	} catch (G2AccessException gae) {
	  Trace.exception (gae);
	  new com.gensym.dlg.ErrorDialog (null, "Error executing User Menu Choice",
					  true, gae.toString (), null).setVisible (true);
	}
	return;
      }
    }
  }

  private void determineUserMenuChoices () {
    //System.out.println ("Trying to determine UMCs for " + currentSelection.length + " items !");
    if (currentSelection.length == 1)
      focalItem = currentSelection[0].getItem ();
    else if (currentSelection.length == 0)
      focalItem = wkspView.getWorkspace ();
    else
      return;
    try {
      Boolean permitted = Boolean.FALSE;
      Sequence choiceRestrictions = null;
      if (true) {//(userMenuChoiceMode1) {
	cxn = (TwConnection)((ImplAccess)wkspView.getWorkspace()).getContext();
	if (cxn.getG2State ().equals(G2Gateway.RUNNING_) &&
	    ((com.gensym.classes.Block)focalItem).getItemActive ()) {
	  userMenuChoices = focalItem.retrieveCurrentUserMenuChoices ();
	} else
	  userMenuChoices = new Vector ();
      } else 
	userMenuChoices 
	  = ConfigurationSupport.filterChoicesByRestrictions (null,//getUserMenuChoicesForClass(item),
							      choiceRestrictions,
							      permitted.booleanValue());
      int numUMCs = userMenuChoices.size ();
      if (numUMCs > 0) {
	userMenuChoiceLabels = new String[numUMCs];
	for (int i=0; i<numUMCs; i++) {
	  UserMenuChoice umc = (UserMenuChoice)userMenuChoices.elementAt (i);
	  Symbol umcLabel = (Symbol) umc.getLabel ();
	  //System.out.println ("Valid User Menu Choice = " + umcLabel);
	  userMenuChoiceLabels[i] = umcLabel.getPrintValue ();
	}
      }
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
    }
  }

  private static final Hashtable localHandlers = new Hashtable (11);

  /**
   * Indicates that a particular user-menu-choice be handled
   * locally on the client instead of invoking it in G2.
   * @see com.gensym.wksp.MenuChoiceHandler
   */
  public static void setLocalMenuChoiceHandler (UserMenuChoice umc,
						MenuChoiceHandler mc) {
    localHandlers.put (umc, mc);
  }

  /**
   * Removes the local handler registered for the user-menu-choice
   * Further invocations of this choice will execute in G2.
   */
  public static void removeLocalMenuChoiceHandler (UserMenuChoice umc) {
    localHandlers.remove (umc);
  }

  /**
   * To be called to execute any user-menu-choice. It checks to see if
   * there are any local handlers registered for this user-menu-choice
   * and calls them if present, else executes the menu-choice in G2.
   * @see #setLocalMenuChoiceHandler
   * @see #removeLocalMenuChoiceHandler
   */
  public static void executeMenuChoice (UserMenuChoice umc, Item itm) throws G2AccessException {
    MenuChoiceHandler lmc = (MenuChoiceHandler) localHandlers.get (umc);
    if (lmc == null)
      umc.invoke(itm);
    else {
      TwConnection cxn = (TwConnection)((ImplAccess)itm).getContext();
      lmc.executeMenuChoice ((Symbol)umc.getLabel (), itm, cxn);
    }
  }
}
