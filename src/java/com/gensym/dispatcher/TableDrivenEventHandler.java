package com.gensym.dispatcher;

import java.util.Locale;
import java.awt.*;
import java.awt.event.*;
import com.gensym.draw.EventHandler;
import com.gensym.draw.PersistentCanvas;
import com.gensym.message.Trace;
import com.gensym.dlg.MessageDialog;

public class TableDrivenEventHandler extends EventHandler
{
  protected transient Object origItm, prevItm;
  protected transient FocusListener focalComponent = null;
  protected transient Reference startX = new VariableReference("startX",Integer.TYPE);
  protected transient Reference startY = new VariableReference("startY",Integer.TYPE);
  protected transient Reference currentXRef = new VariableReference("currentX",Integer.TYPE);
  protected transient Reference currentYRef = new VariableReference("currentY",Integer.TYPE);
  protected static int DBLCLICK_INTERVAL = 250;
  public DispatchTable dispatch;

  private Decision createEventDispatch() {
    try {
      SwitchDecision rootSwitch = new InstanceOfSwitchDecision(new EventReference());
      rootSwitch.addCase(MouseEvent.class, new Noop());
      rootSwitch.addCase(KeyEvent.class, new Noop());
      rootSwitch.addCase(FocusEvent.class, new Noop());
      rootSwitch.addCase(ContainerEvent.class, new Noop());
      rootSwitch.addCase(ComponentEvent.class, new Noop());
      /*rootSwitch.addCase(ActionEvent.class, new Noop());
	rootSwitch.addCase(AdjustmentEvent.class, new Noop());
	rootSwitch.addCase(ItemEvent.class, new Noop());
	rootSwitch.addCase(TextEvent.class, new Noop());
	rootSwitch.addCase(WindowEvent.class, new Noop());
	rootSwitch.addCase(PaintEvent.class, new Noop());
	rootSwitch.addCase(InputEvent.class, new Noop());*/
      rootSwitch.setDefault(new Noop());
      return rootSwitch;
    } catch (Exception e) {
      System.out.println("TOP:BAD TABLE  " + e);
      return null;
    }
  }
  
  protected DispatchTable createDispatchTable()
  {
    DispatchTable dispatch = new DispatchTable();
    dispatch.setRoot(null, createEventDispatch());
    Variable startX = new Variable("startX", null, Integer.TYPE, true);
    dispatch.addVariable(startX);
    Variable startY = new Variable("startY", null, Integer.TYPE, true);
    dispatch.addVariable(startY);
    Variable currentX = new Variable("currentX", null, Integer.TYPE, true);
    dispatch.addVariable(currentX);
    Variable currentY = new Variable("currentY", null, Integer.TYPE, true);
    dispatch.addVariable(currentY);
    return dispatch;
  }

  public TableDrivenEventHandler ()
  {
    this.dispatch = createDispatchTable();
    listenerTypes = COMPONENTLISTENER|MOUSELISTENER |
      MOUSEMOTIONLISTENER | KEYLISTENER | FOCUSLISTENER;
  }

  protected void setStartLocation(int x, int y) {
    try {
      dispatch.setVariable("startX", new Integer(x));
      dispatch.setVariable("startY", new Integer(y));
    } catch (NoSuchVariableException nsve) {
      Trace.exception(nsve);
    }
  }
  
  protected void setCurrentLocation(int x, int y) {
    try {
      dispatch.setVariable("currentX", new Integer(x));
      dispatch.setVariable("currentY", new Integer(y));
    } catch (NoSuchVariableException nsve) {
      Trace.exception(nsve);
    }
  }

  protected void updateDispatchForEvent(java.util.EventObject e)
  {
    updateDispatchForEvent(e, true);
  }
  
  protected void updateDispatchForEvent(java.util.EventObject e,
					boolean resetTarget)
  {
    int x =0, y = 0;
    dispatch.setEvent(e);
    PersistentCanvas canvas = (PersistentCanvas)e.getSource();
    dispatch.setContainer(canvas);
    if (e instanceof MouseEvent) {
      x = ((MouseEvent)e).getX(); y = ((MouseEvent)e).getY();
      setCurrentLocation(x, y);
      if (resetTarget)
	dispatch.setTarget(canvas.findElement(x, y, true));
    } else {
      try {
	x = ((Integer)currentXRef.getValue(dispatch)).intValue();
	y = ((Integer)currentYRef.getValue(dispatch)).intValue();
	dispatch.setTarget(canvas.findElement(x, y, true));
      } catch (IllegalAccessException iae) {
	Trace.exception(iae);
      } catch (NullPointerException npe) {
	dispatch.setTarget(canvas);
	Trace.exception(npe);
      }
    }
  }

  protected Action lookupAction(java.util.EventObject e)
  {
    if (dispatch == null)
      return null;
    try {
      return dispatch.lookupAction(dispatch.getRoot(null));
    } catch (IllegalAccessException iae) {
      Trace.exception(iae);
      return null;
    }
  }

  private void handleInvocationError(String shortDescription,
				     String longDescription)
  {
    if (com.gensym.core.GensymApplication.getDevOption())
      new MessageDialog(null,
			shortDescription,
			false,
			longDescription,
			null).setVisible(true);      
  }
  
  protected void invokeAction(Action action)
  {
    try {
      if (action != null || !(action instanceof Noop)) {
	try {
	  //System.out.println("INVOKING " + action);
	  action.invoke(dispatch);
	} catch (ClassCastException cce) {
	  handleInvocationError("Invalid Class ",
				action.toString() +
				" is not applicable to " +
				cce.getMessage());
	}
      }
    } catch (java.lang.IllegalArgumentException iae) {
      handleInvocationError("Dispatch IllegalArgumentException", 
			   iae.getMessage() +
			   getStackTrace(iae) +
			   "\n\nForAction(s):\n" + action);
    } catch (java.lang.reflect.InvocationTargetException ite) {
      handleInvocationError("Dispatch InvocationTargetException",
			    ite.getTargetException() + "\n" +
			    ite.getMessage() + "\n" +
			    getStackTrace(ite) +
			    "\n\nFor Action(s):\n" + action);
    } catch (Exception exc) {//G2AccessException g2ae ????
      handleInvocationError("Dispatch Exception", 
			    exc.getMessage() +
			    getStackTrace(exc) +
			    "\n\nForAction(s):\n" + action);
    }
  }

  private static String getStackTrace (Exception e) {
    java.io.ByteArrayOutputStream bos = new java.io.ByteArrayOutputStream (400);
    java.io.PrintWriter pw = new java.io.PrintWriter (bos);
    //e.fillInStackTrace ();
    e.printStackTrace (pw);
    pw.flush ();
    pw.close ();
    String backTrace = bos.toString ();
    int newLineIndex = backTrace.indexOf ('\n');
    newLineIndex = backTrace.indexOf ('\n', newLineIndex + 1);
    return (backTrace.substring (newLineIndex + 1, backTrace.length () - 1));
  }

  @Override
  public void componentAdded(ContainerEvent e) {
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }
  
  @Override
  public void componentRemoved(ContainerEvent e){
    updateDispatchForEvent(e);
    dispatch.setTarget(null);
    invokeAction(lookupAction(e));
  }
       
  @Override
  public void componentMoved(ComponentEvent e) {
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }
  
  @Override
  public void componentShown(ComponentEvent e) {
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }
  
  @Override
  public void componentResized(ComponentEvent e){
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }
  
  @Override
  public void componentHidden(ComponentEvent e){
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }

  @Override
  public void mouseMoved(MouseEvent e) {
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }

  @Override
  public void mouseEntered (MouseEvent e) {
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }
  
  @Override
  public void mouseExited (MouseEvent e) {
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }

  @Override
  public void mousePressed (MouseEvent e) {
    if (!e.isMetaDown())
      setStartLocation(e.getX(), e.getY());
    updateDispatchForEvent(e);
    Component comp = (Component)dispatch.target;
    if (comp != null)
      comp.requestFocus();
    invokeAction(lookupAction(e));
  }
  
  @Override
  public void mouseDragged (MouseEvent e) {
    updateDispatchForEvent(e, false);
    invokeAction(lookupAction(e));
  }
  
  @Override
  public void mouseReleased (MouseEvent e) {
    updateDispatchForEvent(e, false);
    invokeAction(lookupAction(e));
  }
  
  @Override
  public void mouseClicked (MouseEvent e)
  {
    if (!e.isMetaDown()) 
      setStartLocation(e.getX(), e.getY());
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }

  @Override
  public void keyPressed(KeyEvent e)
  {
    //System.out.println ("Key Pressed: " + e);
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }

  @Override
  public void keyReleased(KeyEvent e)
  {
    //updateDispatchForEvent(e);
    //invokeAction(lookupAction(e));
  }

  @Override
  public void keyTyped(KeyEvent e)
  {
    updateDispatchForEvent(e);
    invokeAction(lookupAction(e));
  }

  @Override
  public void focusGained(FocusEvent e)
  {
    if (focalComponent != null)
      focalComponent.focusGained(e);
  }
  
  @Override
  public void focusLost(FocusEvent e)
  {
    if (focalComponent != null)
      focalComponent.focusLost(e);
  }

}
