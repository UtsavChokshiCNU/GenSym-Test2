
package com.gensym.demos.wkspdemo;

import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.wksp.*;
import com.gensym.draw.*;
import com.gensym.util.*;
import com.gensym.classes.KbWorkspace;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * This class demonstates how to display a KB-WORKSPACE
 * in a WorkspaceView.
 */
public class WorkspaceFrame extends Frame {

  private static final Symbol DEMO_ = Symbol.intern ("DEMO");
  private transient Image offscreen;
  private transient Graphics og;

  public static void main (String[] args) {
    // Create the frame with a WorkspaceView in it
    Frame f = new WorkspaceFrame ("Workspace Demo");
    // Resize the frame
    f.setBounds (100, 100, 500, 400);
    // Display it
    f.setVisible (true);
  }
  
  private String host = "localhost";
  private String port = "1111";
  private Symbol wkspName = DEMO_;
  private WorkspaceView wkspView;

  WorkspaceFrame (String title) {
    super (title);
    // Exit when the user clicks the close button
    addWindowListener (new WindowAdapter () {
      @Override
      public void windowClosing (WindowEvent we) {
	// shut up shop
	System.exit (0);
      }
    });
    displayWorkspace (host, port, DEMO_);
  }

  private void displayWorkspace (String host, String port, Symbol wkspName_) {
    WorkspaceViewScrollbar vscroll, hscroll;
    try {
      // Make a connection and login
      TwAccess cxn = TwGateway.openConnection (host, port);
      cxn.login ();
      // Get the KB-WORKSPACE to display
      KbWorkspace wksp = (KbWorkspace)cxn.getUniqueNamedItem (com.gensym.util.symbol.G2ClassSymbols.ITEM_,
							      wkspName_);
      // Listen for deletion of workspace
      wksp.addItemListener (new ViewDisposer ());

      // Create the WorkspaceView
      wkspView = new WorkspaceView (wksp);

      // Create the scroll-bars
      Rectangle initialBounds = wkspView.getBounds();
      int initialLeft = initialBounds.x;
      int initialTop = initialBounds.y;
      int initialWidth = initialBounds.width;
      int initialHeight = initialBounds.height;
      hscroll =
	new WorkspaceViewScrollbar (wkspView, LWScrollbar.HORIZONTAL, 0, 1,
				    initialLeft, initialLeft + initialWidth);
      vscroll =
	new WorkspaceViewScrollbar (wkspView, LWScrollbar.VERTICAL, 0, 1,
				    initialTop, initialTop + initialHeight);

      // Associate the scroll-bars with the view
      wkspView.addScrollbar(vscroll, false);
      wkspView.addScrollbar(hscroll, true);

      // Add all UI components to the Frame
      add (wkspView, BorderLayout.CENTER);
      add (vscroll, BorderLayout.EAST);
      add (hscroll, BorderLayout.SOUTH);
    } catch (Exception e) {
      // Display an error dialog if something went wrong
      new com.gensym.dlg.MessageDialog (this,
					"Error!",
					false,
					e.getMessage (),
					(com.gensym.dlg.StandardDialogClient)null).setVisible (true);
    }
  }

  /**
   * Override update to *not* erase the background before painting
   * This reduces flicker.
   */
  @Override
  public void update(Graphics g) {
    paint(g);
  }

  /**
   * Implement double buffering by painting children into an offscreen Image
   * and then blast entire image at once.
   */
  @Override
  public void paint(Graphics g) {
    if(offscreen == null) {
      offscreen = createImage(getSize().width, getSize().height);
      og = offscreen.getGraphics();
    }
    og.setClip(0,0,getSize().width, getSize().height);
    super.paint(og);
    g.drawImage(offscreen, 0, 0, null);
  }

  /**
   * Handle invalidation of double-buffering data
   */
  @Override
  public void invalidate () {
    super.invalidate ();
    offscreen = null;
    og = null;
  }

  class ViewDisposer implements com.gensym.util.ItemListener {
    @Override
    public void receivedInitialValues (ItemEvent e) {
      // No action to take
    }
    @Override
    public void itemModified (ItemEvent e) {
      // Don't care
    }
    @Override
    public void itemDeleted (ItemEvent e) {
      // Dispose of the WorkspaceView
      remove (wkspView);
    }
  }
}
