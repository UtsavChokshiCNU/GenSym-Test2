package com.gensym.wksp.configurations;

import com.gensym.dispatcher.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.wksp.*;
import com.gensym.jgi.*;
import java.awt.*;
import java.lang.reflect.*;
import java.awt.event.*;

public class OperationTypeCondition extends CompoundCondition
implements NonMenuChoices, ConfigurationSymbols
{
  private static final Symbol MENU_CHOICES_ = Symbol.intern ("MENU-CHOICES");
  private Condition condition;
  private static final Symbol OPERATION_TYPE_ = Symbol.intern ("OPERATION-TYPE");
  private static final int NO_MOUSE_MODIFIERS = KeyCodeCondition.NO_MOUSE_MODIFIERS;
  
  public OperationTypeCondition(Structure statement) 
       throws G2AccessException,
	 UnsupportedConfigurationException
  {
    Symbol operationType
      = (Symbol)statement.getAttributeValue(OPERATION_TYPE_, null);    
    if (operationType.equals(ITEM_MENU_) ||
	operationType.equals(TABLE_MENU_) ||
	operationType.equals(NON_MENU_) ||//supported elsewhere
	MOVING_.equals(operationType) ||
	operationType.equals(ATTRIBUTE_VISIBILITY_))
      throw new UnsupportedConfigurationException(statement,
						  "OperationType " + operationType.toString());
    
    try {
      if (TYPING_.equals(operationType)) {
	Condition keyEvent = new EventCondition(java.awt.event.KeyEvent.class);
	condition= new AndCondition(keyEvent,
				    new AWTEventIdCondition(KeyEvent.KEY_PRESSED));
      } else {
	Condition mouseEvent = new EventCondition(java.awt.event.MouseEvent.class);
	if (PRESSING_.equals(operationType)) {
	  condition = new AndCondition(mouseEvent,
				     new AWTEventIdCondition(MouseEvent.MOUSE_PRESSED));
	} else if (RELEASING_.equals(operationType)) {
	  condition = new AndCondition(mouseEvent,
				       new AWTEventIdCondition(MouseEvent.MOUSE_RELEASED));
	  condition
	    = new AndCondition(condition,
			       new AndCondition
			       (new SimpleCondition(SimpleCondition.EQUAL,
						    new VariableReference("startX", Integer.TYPE),
						    new VariableReference("currentX",Integer.TYPE)),
				new SimpleCondition(SimpleCondition.EQUAL,
						    new VariableReference("startY", Integer.TYPE),
						    new VariableReference("currentY",Integer.TYPE))));	
	} else if (SELECTING_.equals(operationType)) {
	  condition = new AndCondition(mouseEvent,
				     new AWTEventIdCondition(MouseEvent.MOUSE_CLICKED));
	  condition = new AndCondition(condition,
				       KeyCodeCondition.modifiersCondition(NO_MOUSE_MODIFIERS));
	} else if (SELECTING_ABSOLUTELY_.equals(operationType)) {
	  condition = new AndCondition(mouseEvent,
				       new AWTEventIdCondition(MouseEvent.MOUSE_CLICKED));
	  condition = new AndCondition(condition,
				       KeyCodeCondition.modifiersCondition(NO_MOUSE_MODIFIERS));
	} 
      }
    } catch (NonStaticMethodException nsme) {
      Trace.exception(nsme);
    }
  }

  @Override
  public boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException
  {
    if (condition != null) {
      /*if (condition.isSatisfied(table))
	System.out.println("OP TYPE SATISFIED for condition = " +condition);*/
      return condition.isSatisfied(table);
    } else
      return false;
  }

  @Override
  public String toString()
  {
    if (condition != null)
      return condition.toString();
    else
      return "false";
  }

}
