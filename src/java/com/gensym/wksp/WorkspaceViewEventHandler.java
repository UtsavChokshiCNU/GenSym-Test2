package com.gensym.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.Enumeration;
import java.util.Vector;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.G2Definition;
import com.gensym.draw.PersistentCanvas;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Access;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.dispatcher.*;
import com.gensym.wksp.configurations.ConfigurationSupport;

public class WorkspaceViewEventHandler extends DefaultWorkspaceViewEventHandler
{

  static final long serialVersionUID = 4060715748671234370L;
  private WorkspaceView view;
  private boolean debug = true;
  static final int LOCAL = ConfigurationSupport.LOCAL;
  static final int ALL = ConfigurationSupport.ALL;
  static final int CLASS = ConfigurationSupport.CLASS;
  private static final Symbol ADMINISTRATOR_ = Symbol.intern ("ADMINISTRATOR");
  static int pressDelayInterval = 250; 
  
  private void configureDispatch(Item item, int type, Symbol g2UserMode)
       throws G2AccessException
  {
    if ((item == null) || !item.isValid())
      return;
    ConfigurationSupport.setUserMode(g2UserMode);
    Decision tree;
    if (type == CLASS) {
      G2Definition def = item.getDefinition();
      if (!(def instanceof ClassDefinition))
	return;
      Sequence inhPathSeq = def.getClassInheritancePath();
      Enumeration e = inhPathSeq.elements();
      G2Access context
	= (G2Access)((com.gensym.classes.ItemImpl)item).getContext(); //hack for now
      while(e.hasMoreElements()) {
	Symbol superClassName = (Symbol)e.nextElement();
	try {
	  if (dispatch.getRoot(superClassName) != null)
	    continue; //already configured this class(optimize its inh path later)
	  G2Definition superClass = context.getClassManager().getDefinition(superClassName);
	  if (superClass instanceof ClassDefinition) {
	    ClassDefinition parent = (ClassDefinition)superClass;
	    Vector configurations = new Vector();
	    Vector ic = parent.getInstanceConfiguration();
	    if (ic != null)
	      configurations.addElement(ic);
	    boolean definitionsIsProprietaryThroughContainment
	      = parent.isProprietaryThroughContainment();
	    tree =
	      ConfigurationSupport.getDecisionTree(parent,
						   definitionsIsProprietaryThroughContainment,
						   false,
						   configurations,
						   this);
	    dispatch.setRoot(superClassName, tree);
	  } //else return;//OPTIMIZE LATER
	} catch (Exception exc) {
	  Trace.exception (exc);
	}
      }
    } else {
      boolean itemIsProprietaryThroughContainment
	= item.isProprietaryThroughContainment();
      tree = ConfigurationSupport.getDecisionTree(item,
						  itemIsProprietaryThroughContainment,
						  type,
						  this);
      dispatch.setRoot(item, tree);
    }
  }

  private static Action doNothing = new Action() {
    @Override
    public Object invoke(DispatchTable table) {
      return null;
    }
  };

  @Override
  public void postContextMenu (MouseEvent e)
       throws IllegalAccessException
  {
    try {
      MouseEvent mce = new MouseEvent((Component)e.getSource(),
				      MouseEvent.MOUSE_CLICKED,
				      e.getWhen(),
				      e.BUTTON1_MASK, 
				      e.getX(), e.getY(),
				      1,
				      false);
      MouseEvent mpe = new MouseEvent((Component)e.getSource(),
				      MouseEvent.MOUSE_PRESSED,
				      e.getWhen(),
				      e.BUTTON1_MASK, 
				      e.getX(), e.getY(),
				      1,
				      false);
      MouseEvent mre = new MouseEvent((Component)e.getSource(),
				      MouseEvent.MOUSE_RELEASED,
				      e.getWhen(),
				      e.BUTTON1_MASK, 
				      e.getX(), e.getY(),
				      1,
				      false);      
      Action userAction = null;
      try {	
	dispatch.setEvent(mce);
	userAction = lookupUserAction(mce);
	if (userAction == null || userAction instanceof Noop) {
	  dispatch.setEvent(mpe);
	  userAction = lookupUserAction(mpe);
	}
	if (userAction == null || userAction instanceof Noop) {
	  dispatch.setEvent(mre);
	  userAction = lookupUserAction(mre);
	}
      } finally {
	dispatch.setEvent(e);
      }
      if (userAction == null || userAction instanceof Noop)
	super.postContextMenu(e);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      return;
    }
  }
       
  private Action lookupUserAction(java.util.EventObject e)
       throws IllegalAccessException, G2AccessException
  {
    WorkspaceView view = (WorkspaceView)e.getSource();
    Reference targetRef = new TargetReference();
    Component target = (Component)targetRef.getValue(dispatch);
    Action action = null;
    if (target instanceof WorkspaceElement) {
      Item item = ((WorkspaceElement)target).getItem();
      Decision targetConfigurations = dispatch.getRoot(item);
      action = dispatch.lookupAction(targetConfigurations);
    }
    if (action == null || action instanceof Noop) {
      KbWorkspace wksp = view.getWorkspace();
      Decision containerConfigurations = dispatch.getRoot(wksp);
      action = dispatch.lookupAction(containerConfigurations);
    } 
    if ((action == null || action instanceof Noop) &&
	(target instanceof WorkspaceElement)) {//again!
      Item item = ((WorkspaceElement)target).getItem();//again!
      G2Definition def = item.getDefinition();
      if (def instanceof ClassDefinition) {
	Sequence inhPathSeq = def.getClassInheritancePath ();
	Enumeration parents = inhPathSeq.elements();
	while(parents.hasMoreElements() &&
	      (action == null || action instanceof Noop)) {	    
	  Symbol superClassName = (Symbol)parents.nextElement();
	  Decision instanceConfigurations = dispatch.getRoot(superClassName);
	  action = dispatch.lookupAction(instanceConfigurations);
	}
      }
    }
    return action;
  }
  
  @Override
  protected Action lookupAction(java.util.EventObject e)
  {
    if (dispatch == null)
      return null;
    try {    
      Action action = lookupUserAction(e);
      WorkspaceView view = (WorkspaceView)e.getSource();
      Reference targetRef = new TargetReference();
      Component target = (Component)targetRef.getValue(dispatch);
      boolean haveUserAction = !(action == null || action instanceof Noop);
      if (!haveUserAction) {
	action = super.lookupAction(e);
	if (futureEventMayOverrideEvent(e)&&
	    (target instanceof WorkspaceElement)&&
	    !(target instanceof WorkspaceButton)) {
	  MouseEvent me = (MouseEvent)e;
	  MouseEvent mce = new MouseEvent((Component)e.getSource(),
					  MouseEvent.MOUSE_CLICKED,
					  me.getWhen(),
					  me.getModifiers(),
					  me.getX(), me.getY(),
					  1,
					  false);
	  try {
	    dispatch.setEvent(mce);
	    Action userClickedAction = lookupUserAction(mce);
	    if (userClickedAction != null &&
		!(userClickedAction instanceof Noop)) {
	      specializedEventHandler.setInvoker(this);
	      specializedEventHandler.setAction(action);
	      return doNothing;
	    }
	  } finally {
	    dispatch.setEvent(e);
	  }
	}
      }
      handleEventOverridePossibilities(e,haveUserAction);
      return action;
    } catch (IllegalAccessException iae) {
      Trace.exception(iae);
      return null;
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      return null;
    }
  }

  private void handleEventOverridePossibilities(java.util.EventObject e,
						boolean haveUserAction)
  {
    if (e instanceof java.awt.event.MouseEvent) {
      switch (((java.awt.event.MouseEvent)e).getID()) {
      case java.awt.event.MouseEvent.MOUSE_CLICKED:
	if (haveUserAction) {
	  synchronized(specializedEventHandler) {
	    specializedEventHandler.cancel();
	  };
	} else {
	  Action action = null;
	  synchronized(specializedEventHandler) {
	    action = specializedEventHandler.getAction();
	    if (action != null) invokeAction(action);	    
	    specializedEventHandler.reset();
	  };

	}
	break;
      case java.awt.event.MouseEvent.MOUSE_DRAGGED:
	Action action = null;
	synchronized(specializedEventHandler) {
	  action = specializedEventHandler.getAction();
	  if (action != null) invokeAction(action);
	  specializedEventHandler.reset();
	};
	break;
      }
    }
  }

  static SpecializedEventHandler specializedEventHandler
  = new SpecializedEventHandler();
  static {
    specializedEventHandler.start();
  }

  @Override
  protected void invokeAction(Action action)
  {
    super.invokeAction(action);
  }
  
  private static final boolean futureEventMayOverrideEvent(java.util.EventObject e)
  {
    if (e instanceof java.awt.event.MouseEvent) {
      java.awt.event.MouseEvent me = (java.awt.event.MouseEvent)e;
      return (!me.isPopupTrigger() &&
	      me.getID()==java.awt.event.MouseEvent.MOUSE_PRESSED);
    }
    return false;
  }

  public void configureDispatch(Item item, Symbol userMode)
       throws G2AccessException
  {
    configureDispatch(item, LOCAL, userMode);
    configureDispatch(item, CLASS, userMode);
  }

  public void unConfigureDispatch(Item item)
  {
    dispatch.setRoot(item, null);
    //need to keep instance count for class dispatching
    //and check count before removing
    //dispatch.setRoot(item.getDefinition(), null);
  }
      
  @Override
  public void registerListeners (PersistentCanvas c)
  {
    super.registerListeners(c);
    this.view = (WorkspaceView)c;
    try {
      Item wksp = ((WorkspaceView)c).getItem();
      if (wksp == null) {
	//System.out.println("KbWorkspace not initialized yet!");
	return;
      }
      TwAccess context
      = (TwAccess)((com.gensym.classes.ItemImpl)wksp).getContext(); //hack for now
      Symbol userMode = context.getUserMode();
      configureDispatch(wksp, ALL, userMode);
    } catch (G2AccessException g2ae) {
      if (debug)
	System.out.println(g2ae);
      Trace.exception(g2ae);
    }
  }

  @Override
  public void deregisterListeners (PersistentCanvas c)
  {
    super.deregisterListeners(c);
    Item wksp = ((WorkspaceView)c).getItem();
    unConfigureDispatch(wksp);
  }

  public void clearDispatch() {
    dispatch.clear();
  }

  @Override
  public void userModeChanged(TwConnectionEvent evt)
  {
    Object source = evt.getSource();
    if (source instanceof TwAccess) {
	 Decision defaultRoot = dispatch.getRoot(null);
	 Vector variables = dispatch.getVariables();
	 dispatch.clear();
	 dispatch.clearVariables();
	 dispatch.setRoot(null,defaultRoot);
	 dispatch.setVariables(variables);
      try {
	Symbol userMode = ((TwAccess)source).getUserMode();
	view.configureHandler(userMode);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      } catch (FatalWorkspaceException fwe) {
	Trace.exception(fwe);
      }
    }
  }

}

  class SpecializedEventHandler extends Thread {

    Action specialAction;
    WorkspaceViewEventHandler invoker;
    boolean sleeping = false;

    SpecializedEventHandler () {
      super ("Pending EventHandler"); 
    }

    void setInvoker(WorkspaceViewEventHandler invoker)
    {
      this.invoker = invoker;
    }

    synchronized void reset()
    {
      specialAction = null;
      if (sleeping) {
	notify();
      }
    }

    synchronized void cancel()
    {
      specialAction = null;
      if (sleeping)
	notify();
    }

    synchronized Action getAction()
    {
      return specialAction;
    }
    
    synchronized void setAction(Action action) {
      if (specialAction == null) {
	specialAction = action;
	if (action != null) notify();
      }
      else {
	//System.out.println("DROPPING ACTION " + action);
      }
    }
    
    @Override
    public synchronized void run()
    {
      while (true) {
	try {
	  wait();
	  if (specialAction != null) {
	    //System.out.println("SLEEPING");
	    //long t0 = System.currentTimeMillis ();
	    sleeping = true;
	    wait(WorkspaceViewEventHandler.pressDelayInterval);
	    sleeping = false;
	    //long t1 = System.currentTimeMillis ();
	    //System.out.println("FINISHED SLEEPING("+(t1-t0)+")");
	    if (specialAction != null) {
	      if (invoker!=null)
		invoker.invokeAction(specialAction);		
	      reset();
	    }
	  }
	} catch (java.lang.InterruptedException ie2) {
	  Trace.exception(ie2);
	} 
      }
    }
  }
