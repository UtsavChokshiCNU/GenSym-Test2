

package com.gensym.oldmdi;
import java.awt.*;


public class MDIDoc extends Panel {
  private Object userClient;

  public boolean handleMDIEvent (Event evt) {
    return true;
  }

  public boolean handleMenuEvent (Event evt) {
    return true;
  }
  @Override
  public void paint (Graphics g) {
    //Rectangle bounds = g.getClipRect ();
    //System.out.println ("Painting..." + bounds);
    //System.out.flush ();
    //g.setColor (Color.white);
    //g.fillRect (0, 0, 1000, 1000);
    super.paint(g);
  }

  public void registerUserObject (Object o) {
    userClient = o;
  }

  public Object getUserObject () {
    return userClient;
  }

  @Override
  public void update (Graphics g) {
    paint (g);
  }
}
