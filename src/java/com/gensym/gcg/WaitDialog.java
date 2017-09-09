
package com.gensym.gcg;

import java.awt.*;
import com.gensym.dlg.StandardDialog;

public class WaitDialog extends StandardDialog {

  static Image img, staticImg;
  private static final Insets msgInsets = new Insets (10, 10, 10, 10);
  private static final Dimension imgSize = new Dimension (60, 80);

  /*  static {
    Class thisClass = WaitDialog.class;
    img =  Toolkit.getDefaultToolkit ().getImage (thisClass.getResource ("wait.gif"));
    staticImg = Toolkit.getDefaultToolkit ().getImage (thisClass.getResource ("swait.gif"));
    Toolkit.getDefaultToolkit().prepareImage (img, -1, -1, null);
    Toolkit.getDefaultToolkit().prepareImage (staticImg, -1, -1, null);
  }*/

  public WaitDialog (Frame f) {
    super (f, "Properties", false,
	   null, null, null, null);
    setSize(250, 100);
    Label label;
    getContentPane().add (label = new Label ("         Generating dialog. Please wait..."));
  }

  //public void paint (Graphics g) {
    //g.drawImage (staticImg, 20, 40, this);
    //g.drawImage (img, 20, 40, this);
  //}

  public static void main (String[] graphics) throws Exception {
    System.out.println ("Showing");
    WaitDialog w = new WaitDialog (null);
    w.setVisible (true);
    Thread.sleep (10000);
    System.out.println ("Hiding");
    w.setVisible (false);
    Thread.sleep (10000);
    System.out.println ("Showing");
    w = new WaitDialog (null);
    w.setVisible (true);
    Thread.sleep (10000);
    System.out.println ("Hiding");
    w.setVisible (false);
    Thread.sleep (10000);
  }

}
