package com.gensym.uitools.utils;

import java.awt.Frame;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.Event;
import javax.swing.KeyStroke;
import javax.swing.JTree;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.dlg.MessageDialog;
import com.gensym.message.Resource;
import java.awt.Component;

public class JExplorerMainMenuCommands extends AbstractCommand
{
  private JExplorer explorer;
  private Component container;
  private static final String shortResource = "JExplorerShortResource";
  private static final String longResource = "JExplorerLongResource";
  private static final Resource i18n
  = Resource.getBundle("com/gensym/uitools/utils/JExplorerShortResource");
  public static final String mnemonicResource = "JExplorerMnemonicResource";
  public static final String
    CLOSE = "close",
    EDIT_ATTRIBUTES = "editAttributes",
    VIEW_LIST = "viewList",
    VIEW_DETAILS = "viewDetails",
    REFRESH_VIEW = "refreshView",
    EXPAND_ALL = "expandAll",
    COLLAPSE_ALL = "collapseAll",  
    ABOUT = "about";

  public JExplorerMainMenuCommands(JExplorer explorer, Component container)
  {
    super(new CommandInformation[]{
	new CommandInformation(CLOSE, true,
			       shortResource, longResource,
			       null,
			       null, null, true,
			       mnemonicResource, null),
	  new CommandInformation(EDIT_ATTRIBUTES, true,
				 shortResource, longResource,
				 null,
				 null, null, false),
	  //mnemonicResource, null),				 
	  new CommandInformation(VIEW_LIST, false,//coming soon!
				 shortResource, longResource,
				 "viewList.gif",
				 null,Boolean.FALSE, true,
				 mnemonicResource, null),
	  new CommandInformation(VIEW_DETAILS, true,
				 shortResource, longResource,
				 "viewDetails.gif",
				 null, Boolean.TRUE, true,
				 mnemonicResource, null),
	  new CommandInformation(REFRESH_VIEW, true,
				 shortResource, longResource,
				 "refresh.gif",
				 null, null, true,
				 mnemonicResource, null),
	  new CommandInformation(EXPAND_ALL, true,
				 shortResource, longResource,
				 "expandAll.gif",
				 null, null, true,
				 mnemonicResource,
				 KeyStroke.getKeyStroke('8', Event.CTRL_MASK+Event.SHIFT_MASK)),
	  new CommandInformation(COLLAPSE_ALL, true,
				 shortResource, longResource,
				 "collapseAll.gif",
				 null, null, true,
				 mnemonicResource,
				 KeyStroke.getKeyStroke('/', Event.CTRL_MASK+Event.SHIFT_MASK)), 
	  new CommandInformation(ABOUT, true,
				 shortResource, longResource,
				 null,
				 null, null, true,
				 mnemonicResource, null)});
    this.explorer = explorer;
    this.container = container;
  }
 
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (CLOSE.equals(cmdKey)) {
      if (container != null)
	container.setVisible(false);
    } else if (EDIT_ATTRIBUTES.equals(cmdKey)) {
      editAttributes();
    } else if (VIEW_DETAILS.equals(cmdKey)) {
      setState(VIEW_DETAILS, Boolean.FALSE);
      setState(VIEW_LIST, Boolean.FALSE);
      setState(VIEW_DETAILS, Boolean.TRUE);
      explorer.setViewType(JExplorer.VIEW_DETAILS);
    } else if (VIEW_LIST.equals(cmdKey)) {
      setState(VIEW_DETAILS, Boolean.FALSE);
      setState(VIEW_LIST, Boolean.FALSE);
      setState(VIEW_LIST, Boolean.TRUE);
      explorer.setViewType(JExplorer.VIEW_LIST);
    } else if (REFRESH_VIEW.equals(cmdKey)) {
      explorer.refresh();
    } else if (EXPAND_ALL.equals(cmdKey)) {
      expandAll(explorer.splitPane.tree);
    } else if (COLLAPSE_ALL.equals(cmdKey)) {
      collapseAll(explorer.splitPane.tree);
    } else if (ABOUT.equals(cmdKey)) {
      new MessageDialog((container instanceof Frame)?
			(Frame)container:null,
			i18n.getString("about"),
			false,
			i18n.getString("aboutText"),
			null).setVisible(true);
    } 
  }

  private void editAttributes() {
    
  }

  public void expandAll(JTree tree) {
    for (int i=0;i<tree.getRowCount();i++) 
      tree.expandRow(i);
  }

  public void collapseAll(JTree tree) {
    for (int i=tree.getRowCount()-1;i>=0;i--)
      tree.collapseRow(i);
  }
  
    
}

