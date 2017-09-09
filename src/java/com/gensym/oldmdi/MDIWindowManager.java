
package com.gensym.oldmdi;
import java.awt.*;
import java.util.Vector;
import gjt.RowLayout;
import gjt.Orientation;
import com.gensym.ntw.util.WindowUtil;

class MDIWindowManager implements MDITilingConstants {

  static final int IMPLICIT_FOCUS = 0;
  static final int EXPLICIT_FOCUS = 1;
  private static int numDocs      = 0;

  private MDIClient client;
  private boolean   implicitFocus;
  private boolean   raiseFocusWin;
  private int zOrderingList[] = new int[20];
  private MDITilingManager tm = new MDITilingManager ();
  private Vector visibleDocList  = new Vector (20);

  MDIWindowManager (MDIClient client, int focusPolicy, boolean raiseFocusWin) {
    this.client = client;
    implicitFocus = (focusPolicy == IMPLICIT_FOCUS);
    this.raiseFocusWin = raiseFocusWin;
  }

  synchronized void addDocument (MDIDocNC doc) {
    zOrderingList[numDocs++] = doc.id;
  }

  void handleMouseEvent (MDIDocNC doc, Event evt) {
    if (implicitFocus && !(client.getFocusDocumentNC() == doc))
      client.setMDIFocus (doc);
  }

  void handleFocusEvent (MDIDocNC doc) {
  }

  synchronized void tile (int tilingCode) {
    if (numDocs == 0) return; // throw an exception?
    MDIDocNC[] docs = client.getDocumentsNC ();
    
    tm.clearLayoutComponents ();
    for (int i=0; i<numDocs; i++) {
      int j=zOrderingList[i];
      if (docs[j].isMapped ())
	tm.addLayoutComponent (docs[j]);
    }
    
    tm.setTilingParameters (tilingCode);
    client.setLayout (tm);
    client.invalidate ();
    client.validate ();
    client.setLayout (null);
  }
}
