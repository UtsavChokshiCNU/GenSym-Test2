package com.gensym.oldmdi;
import java.awt.*;

public class MDICheckboxMenuItem extends CheckboxMenuItem implements Cloneable {

  private static int currentserialID = 0;
  private int serialID;
  private static MDICheckboxMenuItem[] menuTable = new MDICheckboxMenuItem [20];

  public MDICheckboxMenuItem (String label) {
    this (label, true);
  }

  private static synchronized int nextID () {
    return currentserialID++;
  }

  public MDICheckboxMenuItem (String label, boolean isNewItem) {
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
    MDICheckboxMenuItem newItem = new MDICheckboxMenuItem (label, false);
    newItem.serialID = serialID;
    return newItem;
  }

  public MDICheckboxMenuItem getOriginal () {
    return menuTable [serialID];
  }

  @Override
  public synchronized void setState(boolean b) {
    super.setState (b);
  }
}
