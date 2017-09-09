
package com.gensym.oldmdi;
import java.awt.*;


public class MDIMenu extends Menu implements Cloneable {

  private boolean inUse;
  
  public MDIMenu (String label, boolean istearoff) {
    super (label, istearoff);
  }
  
  @Override
  public synchronized void add (String label) {
    MDIMenuItem newItem =  new MDIMenuItem (label);
    add (newItem);
  }


  @Override
  public Object clone () {
    if (!inUse) {
      inUse = true;
      return this;
    }

    int numItems = countItems ();
    MDIMenu newMenu = new MDIMenu (getLabel(), false);
    newMenu.inUse = true;
    for (int i=0; i<numItems; i++) {
      MenuItem mi = getItem (i);
      if (mi instanceof MDIMenu) {
	MDIMenu mdiM = (MDIMenu)mi;
	mdiM = (MDIMenu) mdiM.clone ();
	newMenu.add (mdiM);
      } else {
	String lbl = mi.getLabel ();
	if (lbl.equals ("-"))
	  newMenu.addSeparator ();
	else
	  newMenu.add ((MDIMenuItem)((MDIMenuItem)mi).clone());
      }
    }
    return newMenu;
  }
}
