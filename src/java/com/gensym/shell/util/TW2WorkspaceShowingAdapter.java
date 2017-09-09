/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TW2WorkspaceShowingAdapter.java
 *
 */
package com.gensym.shell.util;

import java.awt.Component;
import java.awt.Frame;
import java.util.Vector;
import java.awt.Point;
import java.awt.Rectangle;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.DefaultWorkspaceShowingAdapter;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.WorkspaceShowingEvent;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.core.UiApplication;
import com.gensym.jgi.G2AccessException;
import com.gensym.wksp.WorkspaceView;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Item;
import com.gensym.message.Trace;

/**
 *  This adapter class implements the WorkspaceShowingListener interface
 *  for SDI applications.  showWorkspace adds a workspace view to the center
 *  of the current frame.  hideWorkspace removes the workspace view from the current
 *  frame.
 */
public class TW2WorkspaceShowingAdapter extends DefaultWorkspaceShowingAdapter {

  /** 
   *  Creates a TW2WorkspaceShowingAdapter for a single connection application.
   *  Once this adapter is created, it will show and hide workspace views
   *  according to the WorkspaceShowing protocol.
   */
  public TW2WorkspaceShowingAdapter(TwAccess connection) throws G2AccessException{
    super (connection);
    setConnection (connection);
  }

  /** 
   *  Creates a TW2WorkspaceShowingAdapter for a multiple connection application.
   *  Once this adapter is created, it will show and hide workspace views
   *  according to the WorkspaceShowing protocol.
   */
  public TW2WorkspaceShowingAdapter(ConnectionManager connectionManager) throws G2AccessException{
    super (null);
    ContextChangedListener contextChangedListener =
         new ContextChangedAdapterForShowingAdapter (connectionManager, this);
    connectionManager.addContextChangedListener(contextChangedListener);
  }

}
