package com.gensym.wksp.configurations;

import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.dlg.*;
import com.gensym.jgi.*;
import com.gensym.wksp.*;
import com.gensym.classes.Item;
import java.util.Locale;

public class WorkspaceActions extends TwActions
implements java.io.Serializable
{

  public WorkspaceActions()
  {
    setLocal(Locale.getDefault());
  }
  
  public WorkspaceActions(TwAccess cxn,
			  TwCallbacks cb)
  {
    setTwAccess(cxn);
    setTwCallbacks(cb);
    setLocal(Locale.getDefault());
  }
  
  //LOCAL EVENT HANDLER UI
  public void initiateTransfer(Item item,
			       int initialX, int initialY,
			       WorkspaceView initialWorkspace)
  {
    try {
      item.transferTo (initialWorkspace.getWorkspace(),
		       initialX, initialY);
    } catch(G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    //WorkspaceView.currentTransferItem = item;
  }

  public void clone(WorkspaceElement element, WorkspaceView view)
       throws G2AccessException
  {
    Item item = element.getItem();
    int x = item.getItemXPosition()+2;
    int y = item.getItemYPosition()-2;
    initiateTransfer(element.getItem().g2Clone(), x, y, view);
  }

  public void move(WorkspaceElement element)
  {
    //handler.doDragPress((MouseEvent)new EventReference().getValue(table));
  }

}
