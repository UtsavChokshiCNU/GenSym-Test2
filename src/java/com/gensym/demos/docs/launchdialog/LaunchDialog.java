/*
* Copyright (C) 1986-2017 Gensym Corporation. 
* All Rights Reserved.
*
* 	 LaunchDialog.java
*
*/

package com.gensym.demos.docs.launchdialog;

import java.awt.Component;
import java.awt.Frame;
import java.awt.Window;
import java.awt.Dialog;
import java.awt.event.*;
import java.net.URL;
import com.gensym.dlgruntime.*;
import com.gensym.controls.ItemProxy;

public class LaunchDialog {

  // Create default reader and launcher
  private DefaultDialogReader reader = new DefaultDialogReader ();
  private DefaultDialogLauncher launcher = new DefaultDialogLauncher();

  private static final String FILE = "file:///c:/gensym/Telewindows2Toolkit/Java/classes/com/gensym/demos/docs/launchdialog/LaunchDialogExample.ser";

  private void showDialog(Frame f) {
    try{
      // Make the dialog resource object
      Object resource = reader.makeResource (reader.readResource (new URL (FILE)));
      //Get item proxies from the resource
      ItemProxy[] proxies = reader.getItemProxies(resource);
      //Get component for the resource
      Component dlg = reader.getComponent(resource);
      //Register the frame 
      launcher.registerFrame(f);
      //Launch it!
      launcher.launch (dlg, proxies[0], null, null);
    } catch (Exception e){
      e.printStackTrace();
    }
  }

  public static void main (String args[]) {
    //Create an adapated frame so we can close it
    LaunchDialog d = new LaunchDialog();
    Frame f = new Frame("Launch Dialog Example");
    WindowAdapter wa =
      new WindowAdapter() {
      @Override
      public void windowClosing (WindowEvent e) {
	System.exit(0);
      }
    };
    f.addWindowListener(wa);
    f.setSize(600,400);
    f.show();
    d.showDialog(f);
  }
}




