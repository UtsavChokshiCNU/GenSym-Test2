
package com.gensym.wksp;

import java.util.Vector;
import java.awt.event.ActionEvent;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwConnection;
import com.gensym.message.Resource;
import com.gensym.classes.Item;
import com.gensym.classes.G2JavaBean;
import com.gensym.core.UiApplication;
import com.gensym.beansruntime.BeanSheet;

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
public class BeanCommands extends AbstractMenuChoiceCommands {

  private Vector userMenuChoices;
  private String[] userMenuChoiceLabels;

  private Item focalItem;
  private TwConnection cxn;

  public static final String
    EDIT_BEAN = "editbean",
    SAVE_BEAN = "savebean";

  private final Vector choices = new Vector ();
  {
    choices.addElement (EDIT_BEAN);
    choices.addElement (SAVE_BEAN);
  }

  private static final Resource i18n = Resource.getBundle ("com/gensym/wksp/UiLabels");
  private static final Resource i18nLong = Resource.getBundle ("com/gensym/wksp/UiLabelsLong");
  /**
   * Creates a new BeanCommands that can be used to
   * generate PopupMenus for Items on workspaces.
   * @see com.gensym.wksp.SelectionCommandGenerator
   */
  public BeanCommands () {
    super (new String[] {EDIT_BEAN, SAVE_BEAN});
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
    return i18n.getString (cmdKey);
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
    focalItem = null;
    if (currentSelection.length == 1)
      focalItem = currentSelection[0].getItem ();
    if (focalItem != null && focalItem instanceof G2JavaBean)
      return choices;
    else
      return new Vector (0);
  }


  @Override
  public boolean isImmediate (String cmdKey) {
    checkKey (cmdKey);
    return !(cmdKey.equals (EDIT_BEAN));
  }

  /**
   * The implementation of the execution of this
   * Command
   */
  @Override
  public void actionPerformed (ActionEvent e) {
    String commandKey = e.getActionCommand ();
    if (commandKey.equals (EDIT_BEAN)) {
      java.lang.Object bean = ((TestBeanElement)currentSelection[0]).getBean ();
      new BeanSheet (bean, UiApplication.getCurrentFrame (), 50, 50);
    } else {
      java.lang.Object bean = ((TestBeanElement)currentSelection[0]).getBean ();
      G2JavaBean beanItem = (G2JavaBean) currentSelection[0].getItem ();
      System.out.println ("Saving " + bean + " in " + beanItem);
      try {
	beanItem.saveObject (bean);
      } catch (G2AccessException g2ae) {
	new com.gensym.dlg.ErrorDialog (null, "Error in Saving Bean", false,
					g2ae.getMessage (),
					null).setVisible (true);
	Trace.exception (g2ae);
      } catch (Exception ex) {
	new com.gensym.dlg.ErrorDialog (null, "Error in Saving Bean", false,
					ex.getMessage (),
					null).setVisible (true);
      }
    }
      
  }

}
