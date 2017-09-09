
package com.gensym.wksp;

import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;
import java.util.Vector;

import com.gensym.jgi.G2Gateway;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;

class WorkspaceClipboardData implements Transferable {

  private Vector data;
  private static Class g2ObjectArrayClass = (new Item[0]).getClass ();
  static DataFlavor G2ObjectFlavor =
    new DataFlavor (g2ObjectArrayClass, "G2 Object");
  private static DataFlavor[] supportedFlavors = {G2ObjectFlavor, DataFlavor.stringFlavor};
  private WorkspaceView wkspView;
  private Item workspace;
  private WorkspaceElement[] selection;
  private boolean isCut;
  static final int G2_OBJECT = 0,
                   STRING    = 1;

  WorkspaceClipboardData (WorkspaceView wkspView, boolean isCut) {
    this.wkspView = wkspView;
    selection = wkspView.getSelection ();
    this.isCut = isCut;
    // Need this so that we know the source w/o the view being "alive"
    this.workspace = wkspView.getItem ();
  }

  void elementChanged (WorkspaceElement elt) {
    for (int i=0; i<selection.length; i++)
      if (selection[i].equals (elt)) {
	wkspView.resetClipboardContents ();
	break;
      }
  }

  WorkspaceElement[] getSelectionSnapshot () {
    return selection;
  }

  boolean wasCut () {
    return isCut;
  }

  @Override
  public DataFlavor[] getTransferDataFlavors() {
    return supportedFlavors;
  }

  @Override
  public boolean isDataFlavorSupported (DataFlavor flavor) {
    return (flavor.equals(supportedFlavors[G2_OBJECT]) ||
	    flavor.equals(supportedFlavors[STRING]));
  }

  @Override
  public Object getTransferData (DataFlavor flavor) throws UnsupportedFlavorException, IOException {
    Object transferData;
    if (flavor.equals (supportedFlavors [G2_OBJECT])) {
      transferData =  makeObjectArrayFromSelection ();
    } else if (flavor.equals (supportedFlavors [STRING])) {
      transferData =  makeStringDescriptionOfSelection ();
    } else
      throw new UnsupportedFlavorException (flavor);
    if (isCut)
      wkspView.resetClipboardContents ();
    return transferData;
  }

  private Item[] makeObjectArrayFromSelection () {
    int numItems = selection.length;
    Item[] g2Items = new Item[numItems];
    for (int i=0; i<numItems; i++) {
      g2Items[i] = selection[i].getItem ();
    }
    return g2Items;
  }

  private String makeStringDescriptionOfSelection () {
    Item[] g2Items = makeObjectArrayFromSelection ();
    return com.gensym.core.DebugUtil.printArray (g2Items);
  }

  // Since we are making up the rules, we can cheat a little...
  boolean checkPasteCompatibility (WorkspaceView otherWkspView) {
    G2Gateway thisCxn = (G2Gateway) ((ImplAccess)workspace).getContext ();
    G2Gateway requestingPasteCxn = (G2Gateway) ((ImplAccess)otherWkspView.getItem()).getContext ();
    return thisCxn.equals (requestingPasteCxn);	// Only allow transfers within the same Xn
  }

}
