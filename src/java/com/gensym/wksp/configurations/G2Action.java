package com.gensym.wksp.configurations;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.dispatcher.*;
import com.gensym.wksp.*;
import java.awt.event.*;
import java.awt.*; 
import java.util.*;
import java.lang.reflect.*;
import com.gensym.classes.Root;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Message;
import com.gensym.classes.FreeformTable;
import com.gensym.classes.G2Definition;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.UserMenuChoice;

public class G2Action extends Action {
  private static boolean debug = true;
  public static final Symbol LIFT_TO_TOP_ = Symbol.intern ("LIFT-TO-TOP");
  public static final Symbol DROP_TO_BOTTOM_ = Symbol.intern ("DROP-TO-BOTTOM");
  public static final Symbol TABLE_ = Symbol.intern ("TABLE");
  public static final Symbol TRANSFER_ = Symbol.intern ("TRANSFER");
  public static final Symbol MOVE_ = Symbol.intern ("MOVE");
  public static final Symbol COLOR_ = Symbol.intern ("COLOR");
  public static final Symbol DELETE_ = Symbol.intern ("DELETE");
  public static final Symbol ENABLE_ = Symbol.intern ("ENABLE");
  public static final Symbol DISABLE_ = Symbol.intern ("DISABLE");
  public static final Symbol DESCRIBE_ = Symbol.intern ("DESCRIBE");
  public static final Symbol VIEW_CHANGE_LOG_ = Symbol.intern ("VIEW-CHANGE-LOG");
  public static final Symbol NAME_ = Symbol.intern ("NAME");
  public static final Symbol GO_TO_REFERENCED_ITEM_ = Symbol.intern ("GO-TO-REFERENCED-ITEM");
  public static final Symbol CLONE_AS_TREND_CHART_ = Symbol.intern ("CLONE-AS-TREND-CHART");
  public static final Symbol EDIT_ = Symbol.intern ("EDIT");
  public static final Symbol CLONE_ = Symbol.intern ("CLONE");
  public static final Symbol CHANGE_MIN_SIZE_ = Symbol.intern ("CHANGE-MIN-SIZE");
  public static final Symbol GO_TO_MESSAGE_ORIGIN_ = Symbol.intern ("GO-TO-MESSAGE-ORIGIN");
  public static final Symbol GO_TO_SUBWORKSPACE_ = Symbol.intern ("GO-TO-SUBWORKSPACE");
  public static final Symbol CREATE_INSTANCE_ = Symbol.intern ("CREATE-INSTANCE");
  public static final Symbol EDIT_ICON_ = Symbol.intern ("EDIT-ICON");
  public static final Symbol TABLE_OF_VALUES_ = Symbol.intern ("TABLE-OF-VALUES");
  public static final Symbol ROTATE_REFLECT_ = Symbol.intern ("ROTATE-REFLECT");
  public static final Symbol CHANGE_SIZE_ = Symbol.intern ("CHANGE-SIZE");
  public static final Symbol CREATE_SUBWORKSPACE_ = Symbol.intern ("CREATE-SUBWORKSPACE");
  public static final Symbol EDIT_CELL_EXPRESSION_ = Symbol.intern ("EDIT-CELL-EXPRESSION");
  public static final Symbol EDIT_CELL_FORMAT_ = Symbol.intern ("EDIT-CELL-FORMAT");
  public static final Symbol OTHER_EDITS_ = Symbol.intern ("OTHER-EDITS");
  public static final Symbol ADD_ROW_ = Symbol.intern ("ADD-ROW");
  public static final Symbol ADD_COLUMN_ = Symbol.intern ("ADD-COLUMN");
  public static final Symbol DELETE_ROW_ = Symbol.intern ("DELETE-ROW");
  public static final Symbol DELETE_COLUMN_ = Symbol.intern ("DELETE-COLUMN");
  public static final Symbol HIDE_NAME_ = Symbol.intern ("HIDE-NAME");
  public static final Symbol DESCRIBE_CONFIGURATION_ = Symbol.intern ("DESCRIBE-CONFIGURATION");
  public static final Symbol NEW_OBJECT_ = Symbol.intern ("NEW-OBJECT");
  public static final Symbol NEW_WORKSPACE_ = Symbol.intern ("NEW-WORKSPACE");
  public static final Symbol NEW_RULE_ = Symbol.intern ("NEW-RULE");
  public static final Symbol NEW_DISPLAY_ = Symbol.intern ("NEW-DISPLAY");
  public static final Symbol NEW_DEFINITION_ = Symbol.intern ("NEW-DEFINITION");
  public static final Symbol NEW_FREE_TEXT_ = Symbol.intern ("NEW-FREE-TEXT");
  public static final Symbol NEW_BUTTON_ = Symbol.intern ("NEW-BUTTON");
  public static final Symbol CLONE_WORKSPACE_ = Symbol.intern ("CLONE-WORKSPACE");
  public static final Symbol HIDE_WORKSPACE_ = Symbol.intern ("HIDE-WORKSPACE");
  public static final Symbol SHRINK_WRAP_ = Symbol.intern ("SHRINK-WRAP");
  public static final Symbol DELETE_WORKSPACE_ = Symbol.intern ("DELETE-WORKSPACE");
  public static final Symbol MAIN_MENU_ = Symbol.intern ("MAIN-MENU");
  public static final Symbol OPERATE_ON_AREA_ = Symbol.intern ("OPERATE-ON-AREA");
  public static final Symbol MISCELLANY_ = Symbol.intern ("MISCELLANY");
  public static final Symbol PRINT_ = Symbol.intern ("PRINT");
  public static final Symbol START_ = Symbol.intern ("START");
  public static final Symbol PAUSE_ = Symbol.intern ("PAUSE");
  public static final Symbol RESTART_ = Symbol.intern ("RESTART");
  public static final Symbol RESET_ = Symbol.intern ("RESET");
  public static final Symbol RESUME_ = Symbol.intern ("RESUME");
  Symbol actionName;
  public static final Symbol USER_MENU_CHOICE_ = Symbol.intern ("USER-MENU-CHOICE");
  static final Symbol TEXT_ = Symbol.intern ("TEXT");
  public static final Symbol NAMES_ = Symbol.intern ("NAMES");
  public static final Symbol KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE");
  public static final Symbol TABLE_CELLS_ = Symbol.intern ("TABLE-CELLS");
  public static final Symbol NONE_ = Symbol.intern ("NONE");
  public static final Symbol SHOW_ = Symbol.intern ("SHOW");
  public static final Symbol HIDE_ = Symbol.intern ("HIDE");
  public static final Symbol ICON_DESCRIPTION_ = Symbol.intern ("ICON-DESCRIPTION");
  public static final Symbol NOTHING_ = Symbol.intern ("NOTHING");
  private static WorkspaceActions actions = new WorkspaceActions();

  
  public G2Action(Symbol actionName) {
    this.actionName = actionName;
  }

  @Override
  public Object invoke(DispatchTable table) 
       throws IllegalAccessException,
	 IllegalArgumentException,
	 InvocationTargetException
  {
    synchronized (this) {
    try {
      if (actionName == null || NOTHING_.equals(actionName)) {
	//System.out.println("DOING NOTHING");
	return null;
      }
      Object target = new TargetReference().getValue(table);
      WorkspaceView container
	= (WorkspaceView)(new ContainerReference().getValue(table));
      Item item = null;
      if (target instanceof WorkspaceElement)//Need ItemView class
	item = ((WorkspaceElement)target).getItem();
      else if (target instanceof WorkspaceView)
	item = ((WorkspaceView)target).getItem();
    
      Item workspace = container.getItem();
      TwGateway gateway
	= (TwGateway)((ImplAccess)workspace).getContext(); //hack for now=
      actions.setTwAccess((TwAccess)gateway);
      actions.setTwCallbacks((TwCallbacks)gateway);
      if (LIFT_TO_TOP_.equals(actionName)) {
	actions.liftToTop(item); return null;
      } else if (DROP_TO_BOTTOM_.equals(actionName)) {
	actions.dropToBottom(item); return null;
      } else if (TABLE_.equals(actionName)) {
	Symbol mode = gateway.getUserMode ();
	actions.editProperties(container, item, mode);
	return null;
      } else if (TRANSFER_.equals(actionName)) {
	Point location = ((Component)target).getLocation();
	int x = location.x + 2;
	int y = location.y + 2;
	actions.initiateTransfer(item, x, y, container);
	return null;
      } else if (MOVE_.equals(actionName)) {
	actions.move((WorkspaceElement)target); return null;
      } else if (COLOR_.equals(actionName)) {
	actions.editColor(item); return null;
      } else if (DELETE_.equals(actionName)) {
	actions.delete(item); return null;
      } else if (ENABLE_.equals(actionName)) {
	actions.enable(item); return null;
      } else if (DISABLE_.equals(actionName)) {
	actions.disable(item); return null;
      } else if (DESCRIBE_.equals(actionName)) {
	actions.describe(item); return null;
      } else if (VIEW_CHANGE_LOG_.equals(actionName)) {
	actions.viewChangeLog(item); return null;
      } else if (NAME_.equals(actionName)) {
	actions.editTextProperty(item, NAMES_); return null;
      } else if (GO_TO_MESSAGE_ORIGIN_.equals(actionName) ||
		 GO_TO_REFERENCED_ITEM_.equals(actionName)) {
	actions.goToMessageOrigin((com.gensym.classes.Message)item);
	return null;
      } else if (CLONE_AS_TREND_CHART_.equals(actionName)) {
	actions.cloneAsTrendChart(item);
	return null;
      } else if (EDIT_.equals(actionName)) {
	actions.editTextProperty(item, TEXT_);
	return null;
      } else if (CLONE_.equals(actionName)) {
	actions.clone((WorkspaceElement)target, container); return null;
      } else if (CHANGE_MIN_SIZE_.equals(actionName)) {
	actions.changeMinSize(item); return null;
      } else if (GO_TO_SUBWORKSPACE_.equals(actionName)) {
	actions.goToSubworkspace((Entity)item); return null;
      } else if (CREATE_INSTANCE_.equals(actionName)) {
	if (item instanceof com.gensym.classes.ClassDefinition) 
	  actions.createInstance((ClassDefinition)item, (KbWorkspace)workspace);
	return null;
      } else if (EDIT_ICON_.equals(actionName)) {
	if (item instanceof com.gensym.classes.ClassDefinition) 
	  actions.editTextProperty(item, ICON_DESCRIPTION_); return null;
      } else if (TABLE_OF_VALUES_.equals(actionName)) {
	actions.tableOfValues(item); return null;
      } else if (ROTATE_REFLECT_.equals(actionName)) {
	actions.editOrientation((Entity)item); return null;
      } else if (CHANGE_SIZE_.equals(actionName)) {
	actions.changeSize(item); return null;
      } else if (CREATE_SUBWORKSPACE_.equals(actionName)) {
	actions.createSubworkspace((Entity)item); return null;
      } else if (EDIT_CELL_EXPRESSION_.equals(actionName)) {
	actions.editFreeformTable((FreeformTable) item, TABLE_CELLS_);
	return null;
      } else if (EDIT_CELL_FORMAT_.equals(actionName)) {
	actions.editFreeformTable((FreeformTable) item, TABLE_CELLS_);
	return null;
      } else if (OTHER_EDITS_.equals(actionName)) {
	actions.editFreeformTable((FreeformTable) item, TABLE_CELLS_);
	return null;
      } else if (ADD_ROW_.equals(actionName)) {
	try {
	  FreeformTable fft = (FreeformTable)item;
	  int currentX
	    = ((Integer)(new VariableReference("currentX",Integer.TYPE)).getValue(table)).intValue();
	  int currentY
	    = ((Integer)(new VariableReference("currentY",Integer.TYPE)).getValue(table)).intValue();
	  int[] coords = ((WorkspaceFreeformTableImpl)target).getCellCoordinates(currentX, currentY);
	  int index = coords[0];
	  actions.insertRow(fft, index);
	} catch (NoSuchVariableException nsve) {
	  Trace.exception(nsve);
	} 
	return null;
      } else if (ADD_COLUMN_.equals(actionName)) {
	try {
	  FreeformTable fft = (FreeformTable)item;
	  int currentX
	    = ((Integer)(new VariableReference("currentX",Integer.TYPE)).getValue(table)).intValue();
	  int currentY
	    = ((Integer)(new VariableReference("currentY",Integer.TYPE)).getValue(table)).intValue();
	  int[] coords = ((WorkspaceFreeformTableImpl)target).getCellCoordinates(currentX, currentY);
	  int index = coords[1];
	  actions.insertColumn(fft, index);
	} catch (NoSuchVariableException nsve) {
	  Trace.exception(nsve);
	} 	  
	return null;
      } else if (DELETE_ROW_.equals(actionName)) {
	try {
	  FreeformTable fft = (FreeformTable)item;
	  int currentX
	    = ((Integer)(new VariableReference("currentX",Integer.TYPE)).getValue(table)).intValue();
	  int currentY
	    = ((Integer)(new VariableReference("currentY",Integer.TYPE)).getValue(table)).intValue();
	  int[] coords = ((WorkspaceFreeformTableImpl)target).getCellCoordinates(currentX, currentY);
	  int index = coords[0];
	  actions.deleteRow(fft, index);
	} catch (NoSuchVariableException nsve) {
	  Trace.exception(nsve);
	} 
	return null;
      } else if (DELETE_COLUMN_.equals(actionName)) {
	try {
	  FreeformTable fft = (FreeformTable)item;
	  int currentX
	    = ((Integer)(new VariableReference("currentX",Integer.TYPE)).getValue(table)).intValue();
	  int currentY
	    = ((Integer)(new VariableReference("currentY",Integer.TYPE)).getValue(table)).intValue();
	  int[] coords = ((WorkspaceFreeformTableImpl)target).getCellCoordinates(currentX, currentY);
	  int index = coords[1];	
	  actions.deleteColumn(fft, index);
	} catch (NoSuchVariableException nsve) {
	  Trace.exception(nsve);
	}
	return null;
      } else if (HIDE_NAME_.equals(actionName)) {
	actions.hideName((Entity)item); return null;      
      } else if (DESCRIBE_CONFIGURATION_.equals(actionName)) {
	actions.describeConfiguration(item); return null;
      } else if (NEW_WORKSPACE_.equals(actionName)) {
	actions.newWorkspace(); return null;
      } else if (NEW_OBJECT_.equals(actionName)) {
	actions.newObject(); return null;
      } else if (NEW_RULE_.equals(actionName)) {
	actions.newRule(); return null;
      } else if (NEW_DISPLAY_.equals(actionName)) {
	actions.newDisplay(); return null;
      } else if (NEW_DEFINITION_.equals(actionName)) {
	actions.newDefinition(); return null;
      } else if (NEW_FREE_TEXT_.equals(actionName)) {
	actions.newFreeText(); return null;
      } else if (NEW_BUTTON_.equals(actionName)) {
	actions.newButton(); return null;
      } else if (CLONE_WORKSPACE_.equals(actionName)) {
	actions.cloneWorkspace((KbWorkspace)workspace); return null;
      } else if (HIDE_WORKSPACE_.equals(actionName)) {
	actions.hideWorkspace((KbWorkspace)workspace); return null;
      } else if (SHRINK_WRAP_.equals(actionName)) {
	actions.shrinkWrap((KbWorkspace)workspace); return null;
      } else if (DELETE_WORKSPACE_.equals(actionName)) {
	actions.delete(workspace); return null;
      } else if (MAIN_MENU_.equals(actionName)) {
	actions.mainMenu(); return null;
      } else if (OPERATE_ON_AREA_.equals(actionName)) {
	actions.operateOnArea(); return null;
      } else if (MISCELLANY_.equals(actionName)) {
	actions.miscellany(); return null;
      } else if (PRINT_.equals(actionName)) {
	actions.print((Component)target); return null;
      } else if (START_.equals(actionName)) {
	actions.startG2(); return null;
      } else if (PAUSE_.equals(actionName)) {
	actions.pauseG2(); return null;
      } else if (RESUME_.equals(actionName)) {
	actions.resumeG2(); return null;
      } else if (RESET_.equals(actionName)) {
	actions.resetG2(); return null;
      } else if (RESTART_.equals(actionName)) {
	actions.restartG2(); return null; 
      } else {
	actions.invokeUserMenuChoice(actionName, item);
	return null;
      }
    } catch (G2AccessException g2ae){
      if (debug)
	System.out.println(g2ae);
      Trace.exception(g2ae);
      return null;
    }
    //System.out.println("doing " + actionName); return null;
    }
  }

  @Override
  public String toString()
  {
    return "((WorkspaceView)container).getActions().invoke(" + actionName+ ", target)";
  }

}
