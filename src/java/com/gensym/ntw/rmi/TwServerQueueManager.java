/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   ServerQueueManager.java 
 * 
 * 
 */ 
  
package com.gensym.ntw.rmi;

import java.util.Hashtable;
import java.util.Enumeration;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.rmi.G2ServerQueueManager;
import com.gensym.jgi.rmi.RMIEventQueueProcessor;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.UnexpectedException;
import com.gensym.util.WorkspaceListener;
import com.gensym.util.WorkspaceEvent;
import com.gensym.ntw.util.TrendChartListener;
import com.gensym.ntw.util.TrendChartEvent;
import com.gensym.ntw.util.KbEvent;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.ntw.util.KbMessageListener;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.WorkspaceShowingEvent;
import com.gensym.classes.Item;
import com.gensym.classes.TrendChart;
import com.gensym.classes.TrendChartImpl;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.KbWorkspaceImpl;
import com.gensym.classes.KbImpl;
import com.gensym.classes.Kb;
import com.gensym.classes.UiClientSession;
import com.gensym.message.Trace;

public class TwServerQueueManager extends G2ServerQueueManager
implements WorkspaceListener, TrendChartListener, KbModuleListener, KbMessageListener,
WorkspaceShowingListener{

  private Hashtable trendChartEventSources = new Hashtable();
  private Hashtable workspaceEventSources = new Hashtable();

  protected TwServerQueueManager(G2Access g2Access,
				 RMIEventQueueProcessor remoteClient) {
    super(g2Access, remoteClient);
  }

  public Structure startTrendChartListening(TrendChart trendChart)
  throws G2AccessException{
    if(addSource(trendChart, trendChartEventSources)) {
      try {
	return
	  ((TrendChartImpl)trendChart).
	  addTrendChartListenerRetrievingState(this);
      } catch (G2AccessException g2ae) {
	trendChartEventSources.remove(trendChart);
	throw g2ae;
      }
    }
    return null;
  }

  public boolean stopTrendChartListening(TrendChart trendChart)
  throws G2AccessException{
    if (trendChartEventSources.get(trendChart) != null) {
      trendChart.removeTrendChartListener(this);
      trendChartEventSources.remove(trendChart);
      return true;
    } else {
      return false;
    }
  }

  Integer showingHandle;

  Integer subscribeToWorkspaceShowing(UiClientSession session)
  throws G2AccessException {
    if (showingHandle == null) {
      showingHandle =
	((TwGateway)g2Access).subscribeToWorkspaceShowing(session);
    }
    return showingHandle;
  }

  void unsubscribeToWorkspaceShowing(Integer subscpnHandle) 
  throws G2AccessException {
    if (showingHandle != null) {
      ((TwGateway)g2Access).unsubscribeToWorkspaceShowing(subscpnHandle);
      showingHandle = null;
    }
  }

  private Kb kb;

  Structure startModuleListening(Kb kb) throws G2AccessException {
    if(this.kb == null) {
      Structure result = ((KbImpl)kb).addKbModuleListenerRetrievingState(this);
      ((KbImpl)kb).addKbMessageListener(this);
      this.kb = kb;
      return result;
    } else {
      throw new UnexpectedException(null,
				    "shouldn't resubscribe to modules!");
    }
  }
  /** There should only be one "kb".
   */
  void stopModuleListening(Kb kb) throws G2AccessException {
    if(kb != null) {
      kb.removeKbModuleListener(this);
      this.kb = null;
    }
  }

  public Structure startWorkspaceListening(KbWorkspace workspace)
  throws G2AccessException{
    try {
      workspaceEventSources.put(workspace, Boolean.TRUE);
      return workspace.addWorkspaceListenerRetrievingState(this);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      try {
	stopWorkspaceListening(workspace);
      } catch (G2AccessException foo) {
	// we were just trying our best to be clean.
	// in all likelihood the stopWorkspaceListening
	// will fail in this case.
	Trace.exception(foo);
      }
      throw g2ae;
    }
  }

  public boolean stopWorkspaceListening(KbWorkspace workspace)
  throws G2AccessException{
    if (workspaceEventSources.get(workspace) != null) {
      workspace.removeWorkspaceListener(this);
      workspaceEventSources.remove(this);
      ((TwRMIServerImpl)g2Access).unrepresentWorkspace(workspace, session);
      return true;
    } else {
      return false;
    }
  }

  @Override
  public void unsubscribeAll() {
    try {
      super.unsubscribeAll();
    } catch (UnexpectedException ue) {
      Trace.exception(ue);
      lastLoopExceptions.addElement(ue);
    }
    for (Enumeration en = trendChartEventSources.keys();
	 en.hasMoreElements();) {
      TrendChart source = (TrendChart)en.nextElement();
      try {
	source.removeTrendChartListener(this);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	lastLoopExceptions.addElement(g2ae);
      }
    }      

    for (Enumeration en = workspaceEventSources.keys();
	 en.hasMoreElements();) {
      KbWorkspace source = (KbWorkspace)en.nextElement();
      try {
	source.removeWorkspaceListener(this);
	((TwRMIServerImpl)g2Access).unrepresentWorkspace(source, session);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	lastLoopExceptions.addElement(g2ae);
      }
    }
    try {
      unsubscribeToWorkspaceShowing(showingHandle);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      lastLoopExceptions.addElement(g2ae);
    }
    try {
      stopModuleListening(kb);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      lastLoopExceptions.addElement(g2ae);
    }

    try {
      ((TwRMIServerImpl)g2Access).releaseUiClientSession(session);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      lastLoopExceptions.addElement(g2ae);
    }
      
    if (!lastLoopExceptions.isEmpty()) {
      // fix this: should add explanatory message
      throw new UnexpectedException((Throwable)lastLoopExceptions.firstElement());
    }
  }

  private UiClientSession session;

  void setSession(UiClientSession session) {
    this.session = session;
  }

  UiClientSession getSession() {
    return session;
  }

  //
  // WorkspaceListener
  //

  @Override
  public void receivedInitialDownload (WorkspaceEvent event) {
    addEvent(event);
  }

  @Override
  public void workspaceItemAdded (WorkspaceEvent event) {
    addEvent(event);
  }

  @Override
  public void workspaceItemRemoved (WorkspaceEvent event) {
    addEvent(event);
  }

  @Override
  public void workspaceResized (WorkspaceEvent event) {
    addEvent(event);
  }

  @Override
  public void workspaceItemMoved (WorkspaceEvent event) {
    addEvent(event);
  }

  @Override
  public void workspaceItemResized (WorkspaceEvent event) {
    addEvent(event);
  }

  @Override
  public void workspaceItemRotated (WorkspaceEvent event) {
    addEvent(event);
  }

  @Override
  public void workspaceItemColorsChanged (WorkspaceEvent event) {
    addEvent(event);
  }

  @Override
  public void workspaceItemIconVariablesChanged (WorkspaceEvent event) {
    addEvent(event);
  }

  @Override
  public void workspaceItemAttributesChanged (WorkspaceEvent event) {
    addEvent(event);
  }

  //
  // TrendChartListener
  //

  @Override
  public void processTrendChartEvent(TrendChartEvent event) {
    addEvent(event);
  }

  //
  // ModuleListener
  //

  @Override
  public void receivedInitialModules (KbEvent evt) {
    addEvent (evt);
  }

  @Override
  public void moduleCreated (KbEvent evt) {
    addEvent (evt);
  }
  
  @Override
  public void moduleDeleted (KbEvent evt) {
    addEvent (evt);
  }
  
  @Override
  public void moduleNameChanged (KbEvent evt) {
    addEvent (evt);
  }
  
  @Override
  public void moduleDependencyChanged (KbEvent evt) {
    addEvent (evt);
  }
  
  @Override
  public void kbCleared (KbEvent evt) {
    addEvent (evt);
  }

  @Override
  public void topLevelWorkspaceAdded (KbEvent evt){
    addEvent (evt);
  }

  @Override
  public void topLevelWorkspaceDeleted (KbEvent evt){
    addEvent (evt);
  }

  @Override
  public void receivedInitialContents (KbEvent evt){
    addEvent (evt);
  }

  @Override
  public void kbMessageAdded(KbEvent evt){
    addEvent (evt);
  }

  @Override
  public void kbMessageDeleted(KbEvent evt){
    addEvent (evt);
  }

  //
  // WorkspaceShowingListener
  //

  @Override
  public void showWorkspace(WorkspaceShowingEvent evt) {
    addEvent (evt);
  }

  @Override
  public void hideWorkspace(WorkspaceShowingEvent evt) {
    addEvent (evt);
  }
}
