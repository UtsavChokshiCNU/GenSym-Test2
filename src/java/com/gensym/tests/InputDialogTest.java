
package com.gensym.tests;

import java.awt.*;
import java.awt.event.*;
import com.gensym.dlg.*;

public class InputDialogTest extends com.gensym.core.UiApplication implements StandardDialogClient {

  InputDialogTest () {
    super (new String[] {}, false);
  }

  public static void main (String[] args) {
    
    Frame f = new Frame ();
    InputDialogTest i = null;
    (i =new InputDialogTest ()).setCurrentFrame (f);
    f.setSize (500, 500);
    f.setVisible (true);
    String[] labels = {"Hostie:", "Portie:", "Hurl:", "Pwd:"};
    String[] initialValues = {"bombay", "6666", "//blech/server", "hmmmm"};
    String[] btnLabels = {"Yeah!", "Nah!"};

    InputDialog id = new InputDialog (null, "Initiate Connection", true,
				      labels, btnLabels, initialValues,
				      (StandardDialogClient)i);
    id.setInputFieldColumns (25);
    id.setNoEcho (3);
    f.addWindowListener (new WindowAdapter () {
      @Override
      public void windowClosing (WindowEvent wEvt) {
	System.exit (0);
      }
    });
    id.setInitialFocus (1);

    id.setVisible (true);
  }

  @Override
  public void dialogDismissed (StandardDialog d, int code) {
    InputDialog med = (InputDialog)d;
    if (med.wasCancelled ()) {
      System.out.println ("Dialog was cancelled.");
      return;
    }

    System.out.println ("Dialog was okayed.");
    String[] results = med.getResults ();
    for (int i=0; i<results.length; i++)
      System.out.println (" #" + i + " :  " + results[i]);
  }

}
