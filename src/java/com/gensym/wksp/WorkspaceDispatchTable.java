package com.gensym.wksp;

import java.util.Locale;
import java.awt.*;
import java.awt.event.*;
import java.util.EventObject;
import com.gensym.classes.Item;
import com.gensym.classes.CheckBox;
import com.gensym.classes.RadioButton;
import com.gensym.classes.KbWorkspaceImpl;
import com.gensym.draw.*;
import com.gensym.dispatcher.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;

public class WorkspaceDispatchTable extends DispatchTable
{
  public WorkspaceViewListener handler;
  //private AutoDispatch autoDispatch;
  public static boolean auto = false;

  @Override
  public String toString() {
    if (auto)
      return ""; //autoDispatch.toString();
    else {
      String str =
	"package com.gensym.wksp;\n"+
	"import com.gensym.jgi.G2AccessException;\n" +
	"import com.gensym.draw.PersistentCanvas;\n" +
	"import com.gensym.dispatcher.Variable;\n" +
	"import java.util.*;\n" +
	"import java.awt.*;\n" +
	"import java.awt.event.*;\n\n\n" +
	"/**\n"+
	"* AutoDispatch\n"+
	"*/\n\n\n"+
	"public class AutoDispatch extends Object {\n\n"+
	"transient WorkspaceViewListener aWorkspaceViewListener;\n" +
	super.toString() + "\n}";
      return str;
    }
  }

  /*public void autoDispatch()
  throws G2AccessException, IllegalAccessException
  {
    autoDispatch.dispatch();
  }
  */
  
  public WorkspaceDispatchTable(WorkspaceViewListener handler) {
    this.handler = handler;
    if (auto)
      return;//createAutoDispatch();
    else {
      createEventDispatch();
      Variable uiMode = new Variable("uiMode", new Integer(-1), Integer.TYPE, true);
      addVariable(uiMode);
      Variable startX = new Variable("startX", new Integer(0), Integer.TYPE, true);
      addVariable(startX);
      Variable startY = new Variable("startY", new Integer(0), Integer.TYPE, true);
      addVariable(startY);
      Variable currentX = new Variable("currentX", new Integer(0), Integer.TYPE, true);
      addVariable(currentX);
      Variable currentY = new Variable("currentY", new Integer(0), Integer.TYPE, true);
      addVariable(currentY);
      Variable sliderInput = new Variable("sliderInput", null, SliderInput.class, true);
      addVariable(sliderInput);
      Variable g2IsRunning = new Variable("g2IsRunning", null, Boolean.TYPE, true);
      addVariable(g2IsRunning);
    }
  }

  /*private void createAutoDispatch() {
    autoDispatch = new AutoDispatch();
    autoDispatch.aTableDrivenHandler = handler;
  }*/
  
  private void createEventDispatch() {
    try {
      SwitchDecision rootSwitch = new InstanceOfSwitchDecision(new EventReference());
      rootSwitch.addCase(WorkspaceEvent.class, new Noop());
      rootSwitch.addCase(MouseEvent.class, createMouseDispatch());
      //rootSwitch.addCase(KeyEvent.class, createKeyDispatch());
      rootSwitch.addCase(FocusEvent.class, createFocusDispatch());
      rootSwitch.addCase(ContainerEvent.class, createContainerDispatch());//subclass of compE
      rootSwitch.addCase(ComponentEvent.class, createComponentDispatch());
      /*rootSwitch.addCase(ActionEvent.class, createActionDispatch());
	rootSwitch.addCase(AdjustmentEvent.class, createAdjustmentDispatch());
	rootSwitch.addCase(ItemEvent.class, createItemDispatch());
	rootSwitch.addCase(TextEvent.class, createTextDispatch());
	rootSwitch.addCase(WindowEvent.class, createWindowDispatch());
	rootSwitch.addCase(PaintEvent.class, createPaintispatch());
	rootSwitch.addCase(InputEvent.class, createInputDispatch());*/
      rootSwitch.setDefault(new Noop());
      setRoot(null, rootSwitch);
    } catch (Exception e) {
      System.out.println("TOP:BAD TABLE  " + e);
    }
  }

  private Decision createMouseReleasedDispatch() {
    try {
      SwitchDecision switchD
	= new SwitchDecision(new VariableReference("uiMode", Integer.TYPE));
      switchD.addCase(WorkspaceViewListener.LASSO,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doLassoRelease", handler,
				       new EventReference(MouseEvent.class)));
      switchD.addCase(WorkspaceViewListener.DRAG,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doDragRelease", handler,
				       new Reference[]
				       { new EventReference(MouseEvent.class),
					   new ConstantReference(Boolean.TYPE, new Boolean(true))}));

      switchD.addCase(WorkspaceViewListener.CONNECTION_DRAG,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doConnectionDragRelease", handler,
				       new EventReference(MouseEvent.class)));
      switchD.addCase(WorkspaceViewListener.BUTTON_PRESS,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doButtonRelease", handler,
				       new EventReference(MouseEvent.class)));
      switchD.addCase(WorkspaceViewListener.RESIZING,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doResizeRelease", handler,
				       new EventReference(MouseEvent.class)));
      switchD.addCase(WorkspaceViewListener.SLIDER_DRAG,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doSliderRelease", handler,
				       new EventReference(MouseEvent.class)));
      switchD.setDefault(new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
					  "endDragState", handler,
					  new EventReference(MouseEvent.class)));
      return switchD;
    } catch (Exception e) {
      System.out.println("BAD MOUSE RELEASED DISPATCH " + e);
    }
    return null;
  }
  
  private Decision createMouseDraggedDispatch() {
    try {
      SwitchDecision switchD
	= new SwitchDecision(new VariableReference("uiMode", Integer.TYPE));
      switchD.addCase(WorkspaceViewListener.LASSO,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doLassoDrag", handler, new EventReference(MouseEvent.class)));
      switchD.addCase(WorkspaceViewListener.CONNECTION_DRAG,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doConnectionDragDrag", handler,
				       new EventReference(MouseEvent.class)));
      switchD.addCase(WorkspaceViewListener.BUTTON_PRESS,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doButtonDrag", handler,
				       new EventReference(MouseEvent.class)));
      switchD.addCase(WorkspaceViewListener.RESIZING,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doResizeDrag", handler,
				       new EventReference(MouseEvent.class)));
      switchD.addCase(WorkspaceViewListener.SLIDER_DRAG,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doSliderDrag", handler,
				       new EventReference(MouseEvent.class)));
      switchD.setDefault(new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
					  "doDragDrag", handler, new EventReference(MouseEvent.class)));
      return switchD;
    } catch (Exception e) {
      System.out.println("BAD MOUSE DRAGGED DISPATCH " + e);
    }
    return null;
  }

  private Decision createMouseClickedDispatch() {
    try {
      SwitchDecision switchD
	= new SwitchDecision(new VariableReference("uiMode", Integer.TYPE));
      switchD.setDefault(new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
					  "doMouseClicked", handler, new EventReference(MouseEvent.class)));
      return switchD;
    } catch (Exception e) {
      System.out.println("BAD MOUSE CLICKED DISPATCH " + e);
    }
    return null;    
  }
  
  private Decision createMouseMovedDispatch() {
    try {
      SwitchDecision switchD
	= new SwitchDecision(new VariableReference("uiMode", Integer.TYPE));
      switchD.addCase(WorkspaceViewListener.CONNECTION_DRAG,
		      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				       "doConnectionDragDrag", handler,
				       new EventReference(MouseEvent.class)));
      switchD.setDefault(new Noop());
      return switchD;
    } catch (Exception e) {
      System.out.println("BAD MOUSE MOVE DISPATCH " + e);
    }
    return null;    
  }

  private Node createSliderPressAction() {
    try {
      CompoundAction cAction = new CompoundAction();
      cAction.addNode(new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
					 "noteSliderPress", handler,
					 new Reference[]
					 {new EventReference(MouseEvent.class),
					    new TargetReference(SliderInput.class)}));
      
      cAction.addNode(new DispatchSetAction("currentX",
					    Integer.TYPE,
					    new VariableReference("startX", Integer.TYPE)));
      cAction.addNode(new DispatchSetAction("currentY",
					    Integer.TYPE,
					    new VariableReference("startY", Integer.TYPE)));
      Reference sliderInputRef = new TargetReference(SliderInput.class);
      cAction.addNode(new DispatchSetAction("sliderInput",
					    com.gensym.wksp.SliderInput.class,
					    sliderInputRef));
      cAction.addNode(new DispatchSetAction("uiMode",
					    Integer.TYPE,
					    new Integer(WorkspaceViewListener.SLIDER_DRAG)));
      Reference sliderRef
	= new NestedPropertyReference(com.gensym.wksp.WorkspaceSliderImpl.class,
				      "getSlider",
				      new VariableReference("sliderInput",
							    com.gensym.wksp.SliderInput.class));
      cAction.addNode(new SimpleAction("com.gensym.wksp.WorkspaceSliderImpl",
					 "setDragging",
					 sliderRef,
					 new ConstantReference(Boolean.TYPE, new Boolean(true))));
      return cAction;
    } catch (Exception e) {
      System.out.println("BAD SLIDER PRESS " + e);
    }
    return null;    
  }

  private Node createWorkspaceElementMousePressedDispatch() {
    try {
    return new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
			    "doWorkspaceElementMousePressed", handler,
			    new EventReference(MouseEvent.class));
    /*SwitchDecision targetClassSwitch = new InstanceOfSwitchDecision(new TargetReference());
    targetClassSwitch.addCase(WorkspaceButton.class, && g2IsRunning((WorkspaceView)canvas))
			      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
					       "doButtonPress", handler,
					       new EventReference(MouseEvent.class)));
    targetClassSwitch.addCase(ConnectionElement.class,
			      new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
					       "doConnectionMousePressed", handler,
					       new EventReference(MouseEvent.class)));
    targetClassSwitch.setDefault();
    else {
      WorkspaceView view = ((WorkspaceView)canvas);
      if (w.isSelected ()) {
	if (e.isShiftDown ()) {
	  view.removeElementFromSelection (w);
	  return;
	}
	doDragPress (e);
      } else {
	if (!e.isShiftDown ())
	  view.clearSelection ();
	view.addElementToSelection (w);
	doDragPress (e);
      }
    }*/
    } catch (Exception e) {
      System.out.println("BAD WORKSPACE ELEMENT MOUSE PRESSED DISPATCH");
    }
    return null;
  }

  private Node createMousePressedDispatch() {
    Decision top;
    try {
      InstanceOfSwitchDecision targetSwitchClass 
	= new InstanceOfSwitchDecision(new TargetReference());
      Decision decision
	= new Decision
	(new SimpleCondition(SimpleCondition.EQUAL,
			     new VariableReference("uiMode", Integer.TYPE),
			     new ConstantReference
			     (Integer.TYPE,
			      new Integer(WorkspaceViewListener.CONNECTION_DRAG))),
	 new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
			  "doConnectionDragMousePressed", handler,
			  new Reference[]
			  {new EventReference(MouseEvent.class),
			     new TargetReference(Component.class),
			     new ContainerReference(PersistentCanvas.class)}),
	 targetSwitchClass);
      targetSwitchClass.addCase(WorkspaceElement.class, createWorkspaceElementMousePressedDispatch());
      targetSwitchClass.addCase(com.gensym.wksp.MarkerElement.class,
				new SimpleAction
				("com.gensym.wksp.WorkspaceViewListener",
				 "doResizePress", handler,
				 new Reference[]
				 {new EventReference(MouseEvent.class),
				    new TargetReference(com.gensym.wksp.MarkerElement.class)}));
      targetSwitchClass.addCase(SliderInput.class, createSliderPressAction());	   
      //Should check that the target == null
      targetSwitchClass.setDefault(new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
						    "doLassoPress", handler,
						    new EventReference(MouseEvent.class)));
      CompoundAction cAction = new CompoundAction();
      cAction.addNode
	(new DispatchSetAction("startX",
			       Integer.TYPE,
			       new NestedPropertyReference(Integer.TYPE,
							   "getX",
							   new EventReference(MouseEvent.class))));
      cAction.addNode
	(new DispatchSetAction("startY",
			       Integer.TYPE,
			       new NestedPropertyReference(Integer.TYPE,
							   "getY",
							   new EventReference(MouseEvent.class))));
      cAction.addNode(decision);
      top=new Decision(new SimpleCondition
		       (SimpleCondition.EQUAL,
			new ConstantReference(Boolean.TYPE, new Boolean(true)),
			new NestedPropertyReference(Boolean.TYPE,
						    "isMetaDown",
						    new EventReference(MouseEvent.class))),
		       new Decision
		       (new SimpleCondition(SimpleCondition.EQUAL,
					    new VariableReference("uiMode", Integer.TYPE),
					    new ConstantReference
					    (Integer.TYPE,
					     new Integer(-1))),
			new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
					 "postContextMenu", handler,
					 new EventReference(MouseEvent.class)),
			new Noop()),
		       cAction);
    } catch (Exception e) {
      System.out.println("BAD MOUSE PRESS DISPATCH " + e);
      return null;
    }
    return top;
  }
      
  private Decision createMouseDispatch() {
    try {
      SwitchDecision switchD
	= new SwitchDecision(new NestedPropertyReference(Integer.TYPE,"getID",
							 new EventReference(MouseEvent.class)));
      switchD.addCase(MouseEvent.MOUSE_PRESSED, createMousePressedDispatch());
      switchD.addCase(MouseEvent.MOUSE_RELEASED, createMouseReleasedDispatch());
      switchD.addCase(MouseEvent.MOUSE_DRAGGED, createMouseDraggedDispatch());
      switchD.addCase(MouseEvent.MOUSE_CLICKED, createMouseClickedDispatch());
      switchD.addCase(MouseEvent.MOUSE_MOVED, createMouseMovedDispatch());
      switchD.setDefault(new Noop());
      return switchD;
    } catch (Exception e) {
      System.out.println("BAD MOUSE DISPATCH " + e);
    }
    return null;
  }

  private Decision createKeyDispatch() {
    //NOT RECIEVING KEY EVENTS YET!!!!!
    int inc = 10;
    try {
      SwitchDecision switchD
	= new SwitchDecision(new NestedPropertyReference(Integer.TYPE,"getKeyCode",
							 new EventReference(KeyEvent.class)));
      switchD.addCase(KeyEvent.VK_DOWN,
		      new SimpleAction("com.gensym.draw.PersistentCanvas",
				       "scrollView",
				       new ContainerReference(com.gensym.draw.PersistentCanvas.class),
				       new Reference[] { new ConstantReference(Integer.TYPE,
									       new Integer(inc)),
							   new ConstantReference(Boolean.TYPE,
										 new Boolean(false))}));
      switchD.addCase(KeyEvent.VK_UP,
		      new SimpleAction("com.gensym.draw.PersistentCanvas",
				       "scrollView",
				       new ContainerReference(com.gensym.draw.PersistentCanvas.class),
				       new Reference[] { new ConstantReference(Integer.TYPE,
									       new Integer(-inc)),
							   new ConstantReference(Boolean.TYPE,
										 new Boolean(false))}));
      switchD.addCase(KeyEvent.VK_LEFT,
		      new SimpleAction("com.gensym.draw.PersistentCanvas",
				       "scrollView",
				       new ContainerReference(com.gensym.draw.PersistentCanvas.class),
				       new Reference[] { new ConstantReference(Integer.TYPE,
									       new Integer(-inc)),
							   new ConstantReference(Boolean.TYPE,
										 new Boolean(true))}));
      switchD.addCase(KeyEvent.VK_RIGHT,
		      new SimpleAction("com.gensym.draw.PersistentCanvas",
				       "scrollView",
				       new ContainerReference(com.gensym.draw.PersistentCanvas.class),
				       new Reference[] { new ConstantReference(Integer.TYPE,
									       new Integer(inc)),
							   new ConstantReference(Boolean.TYPE,
										 new Boolean(true))}));


      switchD.setDefault(new Noop());
      return switchD;
    } catch (Exception e) {
      System.out.println("BAD KEY DISPATCH" + e);
    }
    return null;
  }

  private Decision createFocusDispatch() {
    return new Decision(new FalseCondition(), new Noop(), new Noop());
  }

  private Decision createComponentDispatch() {
    try {
      return new Decision(new FalseCondition(), new Noop(), new Noop());
      
    } catch (Exception e) {
      System.out.println("BAD COMPONENT DISPATCH");
    }
    return null;
  }

  private Decision createContainerDispatch() {
    try {
      InstanceOfSwitchDecision childSwitchClass 
	= new InstanceOfSwitchDecision
	(new NestedPropertyReference(Component.class,"getChild",
				     new EventReference(ContainerEvent.class)));
      SwitchDecision switchID
	= new SwitchDecision(new NestedPropertyReference(Integer.TYPE,"getID",
							 new EventReference(ContainerEvent.class)));
      childSwitchClass.addCase(WorkspaceElement.class, switchID);
      switchID.addCase(ContainerEvent.COMPONENT_ADDED, new Noop());
      switchID.addCase(ContainerEvent.COMPONENT_REMOVED, new Noop());
      switchID.setDefault(new Noop());
      childSwitchClass.setDefault(new Noop());
      return childSwitchClass;
    } catch (Exception e) {
      System.out.println("BAD CONTAINER DISPATCH");
    }
    return null;
  }

  SliderInput getSliderInput() {
    try {
      return (SliderInput)getVariable("sliderInput").getValue();
    } catch (NoSuchVariableException nsve) {
      Trace.exception(nsve);
      return null;
    }
  }

  @Override
  public void setEvent(EventObject event)
  {
    /*if (auto)
      autoDispatch.theEvent = event;*/
    super.setEvent(event);
  }

  @Override
  public void setContainer(Container container)
  {
    /*if (auto)
      autoDispatch.theContainer = container;*/
    super.setContainer(container);
  }

  @Override
  public void setTarget(Object target)
  {
    /*if (auto)
      autoDispatch.theTarget = target;*/
    super.setTarget(target);
  }

  @Override
  public void setVariable(String name, Object value)
       throws NoSuchVariableException
  {
    /*if (auto)
      autoDispatch.setVariable(name, value);
    else*/
      super.setVariable(name,value);
  }

  @Override
  protected Variable getVariable(String name)
       throws NoSuchVariableException
  {
    /*if (auto)
      return autoDispatch.getVariable(name);
    else*/
      return super.getVariable(name);
  }
  
}
