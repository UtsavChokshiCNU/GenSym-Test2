
package com.gensym.devtools;

import java.awt.*;
import java.awt.event.*;

public class OverrideEditor extends Frame {

  private Button propsButton, methodsButton;
  private TabPanel tabPanel;

  public static void main (String[] args) {

    OverrideEditor o = new OverrideEditor ("Class Overrides");
    o.setSize (400, 400);
    o.setLocation (50, 50);
    o.setVisible (true);

  }

  public OverrideEditor (String title) {
    super (title);
    setLayout (new BorderLayout ());
    propsButton = new Button ("Properties");
    methodsButton = new Button ("Methods");
    ActionListener tabbtnListener = new ActionListener () {
      @Override
      public void actionPerformed(ActionEvent e) {
	Button btnPressed = (Button)e.getSource ();
	String cardCmd = (btnPressed == propsButton ? "properties" : "methods");
	tabPanel.show (cardCmd);
      }
    };
    Panel p = new TabBar (new Button[] {propsButton, methodsButton}, tabbtnListener);
    add ("North", p);
    ColoredPanel c0 = new ColoredPanel (Color.blue),
                 c1 = new ColoredPanel (Color.yellow);
    tabPanel = new TabPanel (new Component[] {c0, c1}, new String[] {"properties", "methods"});
    add ("Center", tabPanel);
    
  }
}


class ColoredPanel extends Panel {

  private Color color;
  private static Dimension prefDims = new Dimension (200, 200);

  ColoredPanel (Color colour) {
    color = colour;
  }

  @Override
  public void paint (Graphics g) {
    Rectangle bnds = getBounds ();
    g.setColor (color);
    g.fillRect (bnds.x, bnds.y, bnds.width, bnds.height);
  }

  @Override
  public Dimension getPreferredSize () {
    return prefDims;
  }
}

class TabBar extends Panel {

  TabBar (Button[] btns, ActionListener listnr) {
    setLayout (new FlowLayout (FlowLayout.LEFT));
    for (int i=0; i<btns.length; i++) {
      add (btns[i]);
      btns[i].addActionListener (listnr);
    }
  }

  @Override
  public void paint (Graphics g) {
    Rectangle bnds = getBounds ();
    g.setColor (Color.green);
    g.fillRect (bnds.x, bnds.y, bnds.width, bnds.height);
  }
}

class TabPanel extends Panel {

  private CardLayout c;

  TabPanel (Component[] cmpts, String[] names) {
    setLayout (c = new CardLayout ());
    for (int i=0; i<cmpts.length; i++)
      add (cmpts[i], names[i]);
  }

  void show (String name) {
    c.show (this, name);
  }

  @Override
  public void paint (Graphics g) {
    Rectangle bnds = getBounds ();
    g.setColor (Color.black);
    g.fillRect (bnds.x, bnds.y, bnds.width, bnds.height);
  }

}
