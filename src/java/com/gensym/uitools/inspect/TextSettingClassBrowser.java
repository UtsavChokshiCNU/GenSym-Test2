package com.gensym.uitools.inspect;

import com.gensym.ntw.util.ClassBrowserScrollPane;
import com.gensym.ntw.util.BrowserSymbols;
import javax.swing.event.TreeSelectionListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.tree.TreeSelectionModel;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import javax.swing.JTree;
import javax.swing.text.JTextComponent;
import javax.swing.JButton;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import java.awt.Frame;

public class TextSettingClassBrowser extends StandardDialog
implements BrowserSymbols, TreeSelectionListener
{
  
  private JButton okButton;
  private JTree tree;
  private ClassBrowserScrollPane pane;

  public TextSettingClassBrowser(JTextComponent textComponent,
				 Frame parentFrame,
				 TwAccess connection,
				 Symbol baseClass)
  {
    super(parentFrame,
	  "Class Browser",
	  false,
	  new String[] {OK_LABEL, CANCEL_LABEL},
	  new int[] {OK, CANCEL}, 
	  new ClassBrowserScrollPane(connection, ALL_, baseClass),
	  new BrowserClient(textComponent));
    pane = (ClassBrowserScrollPane)getDialogComponent();
    tree = pane.getTree();
    TreeSelectionModel selectionModel = tree.getSelectionModel();
    selectionModel.addTreeSelectionListener(this);
    selectionModel.setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
    okButton = getJButton(OK);
    okButton.setEnabled(false);
    setSize(300, 300);
  }

  @Override
  public void valueChanged(TreeSelectionEvent event){
    okButton.setEnabled(true);
  }

  public String getResult(){
    return pane.getUserObjectForSelectedTreeNode().toString();
  }
  
}

class BrowserClient implements StandardDialogClient{
  
  private JTextComponent tc;
  
  BrowserClient(JTextComponent tc) {
    this.tc = tc;
  }
  
  @Override
  public void dialogDismissed(StandardDialog d, int cmdCode){
    if (d.wasCancelled()) return;
    
    String result = ((TextSettingClassBrowser)d).getResult();
    tc.setText(result);
  }
}

