
package com.gensym.ntw;

import java.awt.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.message.*;
import com.gensym.ntw.*;
import com.gensym.dlg.*;
import com.gensym.oldmdi.*;
import com.gensym.wksp.*;
import com.gensym.draw.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Access;
import com.gensym.classes.KbWorkspace;

class GetWkspHandler implements StandardDialogClient, Runnable {
  
  private TwAccess context;
  private NtwFrame currentFrame;
  private Sequence listOfWksps;

  GetWkspHandler (TwAccess context) {
    if (context == null) {
      System.out.print("Warning: creating workspace handler with ");
      System.out.println("context == null");
    }
    this.context = context;
  }

  @Override
  public void run () {
    if (context == null)
      System.out.println("Warning: context == null");
    currentFrame = Telewindows.staticFrame;
    try {
      listOfWksps = context.getNamedWorkspaces ();
    } catch (G2AccessException g2ae) {
      g2ae.printStackTrace();
      return;
    }
    int numWksps = listOfWksps.size ();
    String[] names = new String [numWksps];
    for (int i=0; i<numWksps; i++)
      names[i] = ((Symbol)listOfWksps.elementAt(i)).getPrintValue();
    new SelectionDialog (currentFrame, "Get Workspace", false, 
			 "Choose Workspace", 
			 names, false, -1, true, this).setVisible (true);
  }

  @Override
  public void dialogDismissed (StandardDialog d, int code) {
    SelectionDialog osd = (SelectionDialog)d;

    if (osd.wasCancelled ())
      return;

    int chosenWkspIndex = osd.getResult ();
    //System.out.println ("GetWkspHandler dialogDismissed called ->" + chosenWkspIndex);
    Symbol chosenWkspName = (Symbol) listOfWksps.elementAt (chosenWkspIndex);
    new WorkspaceDownloader (context, chosenWkspName).start ();
  }


}

class WorkspaceDownloader extends Thread {

  private TwAccess context;
  private Symbol name;

  WorkspaceDownloader (TwAccess g2context, Symbol wkspName) {
    context = g2context;
    name = wkspName;
  }

  private static Symbol kbWorkspace_ = Symbol.intern("KB-WORKSPACE");
  @Override
  public void run () {

    NtwFrame currentFrame;

    currentFrame = Telewindows.staticFrame;

    new NtwNotification (NtwNotification.STATUSCHANGE,
			 0, "", this, NtwNotification.ACTIVITY_START).send ();


    KbWorkspace kbWorkspace = null;
    try {
      Object thing
	= ((G2Access)context).getUniqueNamedItem(kbWorkspace_,
						 name);
      kbWorkspace = (KbWorkspace) thing;
    } catch (G2AccessException g2ae) {
      // fix this: is this the right way to handle it?
      new NtwNotification (NtwNotification.EXCEPTION,
			   0, g2ae.getMessage(), this,
			   NtwNotification.ACTIVITY_START).send ();
      Trace.exception(g2ae, "COULDN'T FIND KB-WORKSPACE NAMED " +
		      name.toString());
      return;
    }
    WorkspaceView view = new WorkspaceView(kbWorkspace);
    Rectangle initialBounds = view.getBounds();
    int initialLeft = initialBounds.x;
    int initialTop = initialBounds.y;
    int initialWidth = initialBounds.width;
    int initialHeight = initialBounds.height;
    view.setEventHandler (new RubberBandHandler ());
    int scrollBarWidth = 15;
    MDIDoc newpanel
      = currentFrame.createNewDocument (name.getPrintValue(),
					new Dimension (initialWidth + scrollBarWidth,
						       initialHeight + scrollBarWidth));
    newpanel.setLayout (new BorderLayout ());
    ViewScrollbar hscroll = new ViewScrollbar (view,Scrollbar.HORIZONTAL, 0,1,
					       initialLeft, initialLeft + initialWidth);
    ViewScrollbar vscroll = new ViewScrollbar (view,Scrollbar.VERTICAL, 0,1,
					       initialTop, initialTop + initialHeight);
    view.addScrollbar(vscroll,false);
    view.addScrollbar(hscroll,true);
    newpanel.add("South",  hscroll);
    newpanel.add("East",   vscroll);
    newpanel.add("Center", view);
    newpanel.validate();
    newpanel.setVisible(true);
    view.setDoubleBuffered (true);
    new NtwNotification (NtwNotification.STATUSCHANGE,
			 0, "", this, NtwNotification.ACTIVITY_STOP).send ();
    newpanel.registerUserObject (view);

  }

}

