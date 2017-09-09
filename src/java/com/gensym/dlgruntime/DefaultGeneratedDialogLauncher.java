package com.gensym.dlgruntime;

import java.awt.Component;
import java.awt.Dialog;
import java.awt.Frame;
import java.awt.Rectangle;
import java.awt.Window;
import javax.swing.JComponent;
import javax.swing.JDialog;
import com.gensym.classes.Item;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.ItemProxy;
import com.gensym.core.UiApplication;

/*
 * This class was originally written to handle the fact that
 * the interface GeneratedDialogFactory allows a Component
 * to be returned. The launch method simply checks if the
 * component is a window, and makes a dialog if necessary.
 * In the future, if this needs to be made public, some of
 * the code in this and other launchers (and the dialogManager
 * could be rationalized.
 */
class DefaultGeneratedDialogLauncher extends DefaultDialogLauncher {
  @Override
  public void launch (Component component, ItemProxy[] proxies,
		      String[] proxyNames,
                      Item[] stubs, DialogCommand closer) {
    launch(UiApplication.getCurrentFrame(), component);
  }

  public void launch (Frame owner, Component component) {
    Window dialog;
    if (component instanceof Window) {
      dialog = (Window)component;
    } else if (component instanceof JComponent) {
      dialog = new JDefaultDialog(owner);
      ((JDialog)dialog).getRootPane().add(component);
    } else {
      dialog = new DefaultDialog(owner);
      dialog.add(component);
    }
    dialog.pack();
    centerDialog (dialog);
    dialog.setVisible (true);
  }
}
