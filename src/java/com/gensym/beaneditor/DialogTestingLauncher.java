package com.gensym.beaneditor;

import javax.swing.JPanel;
import javax.swing.JDialog;
import com.gensym.dlgruntime.*;
import java.awt.*;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.ItemProxy;
import com.gensym.classes.Item;

public class DialogTestingLauncher extends DefaultDialogLauncher
{
  EditorFrame editorFrame = null;

  public DialogTestingLauncher(EditorFrame frame)
  {
    editorFrame = frame;
  }

  @Override
  public void dialogShutdown (DialogCommandEvent event)
  {
    storeReference (event.getSource ());
    super.dialogShutdown (event);
    editorFrame.launchComplete ();
  }

  // overriden to create a JDialog instead of a Dialog
  @Override
  public void launch (Component component, ItemProxy[] proxies,
		      String[] proxyNames, Item[] stubs, DialogCommand cmdBean) {
    JDialog dialog = new JDialog(editorFrame);
    JPanel p = new JPanel();
    dialog.getContentPane().add(p);
    p.add(component);
    dialog.pack();
    super.launch(dialog, proxies, proxyNames, stubs, cmdBean);
  }

  private final java.util.Hashtable tempRef = new java.util.Hashtable (3);
  void hookupJarCommandBean (Object commandBean, Component c) {
    tempRef.put (commandBean, c);
  }

  private void storeReference (Object commandBean) {
    Component c = (Component)tempRef.remove (commandBean);
    if (c == null)		// The generated command bean
      return;
    if (!(c instanceof Window)) {
      Container p = c.getParent ();
      while (!(p instanceof Window)) {
	p = p.getParent ();
      }
      c = p;
    }
    dialogs.put (commandBean, (Dialog) c);
  }

}
