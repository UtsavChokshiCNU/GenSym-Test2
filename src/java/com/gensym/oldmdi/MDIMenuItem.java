package com.gensym.oldmdi;
import java.awt.*;

public class MDIMenuItem extends MenuItem implements Cloneable {

  private static int currentserialID = 0;
  private int serialID;
  private static MDIMenuItem[] menuTable = new MDIMenuItem [300];

  public MDIMenuItem (String label) {
    this (label, true);
  }

  private static synchronized int nextID () {
    return currentserialID++;
  }

  public MDIMenuItem (String label, boolean isNewItem) {
    super (label);
    if (isNewItem) {
      serialID = nextID ();
      menuTable[serialID] = this;
    }
  }

  /* Must allow clone in other packages */
  @Override
  public Object clone () {
    String label = getLabel ();
    MDIMenuItem newItem = new MDIMenuItem (label, false);
    newItem.serialID = serialID;
    return newItem;
  }

  public MDIMenuItem getOriginal () {
    return menuTable [serialID];
  }
}
