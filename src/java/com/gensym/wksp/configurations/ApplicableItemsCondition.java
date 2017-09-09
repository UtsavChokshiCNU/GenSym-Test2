package com.gensym.wksp.configurations;

import com.gensym.dispatcher.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.wksp.*;
import com.gensym.jgi.*;
import com.gensym.classes.Item;
import java.awt.event.*;
import java.lang.reflect.*;
import java.util.Enumeration;

public class ApplicableItemsCondition extends CompoundCondition
{
  private Condition condition;
  private static final Symbol THIS_ = Symbol.intern ("THIS");
  private static final Symbol NON_MENU_ = Symbol.intern ("NON-MENU");

  public ApplicableItemsCondition(Sequence applicableItems,
				  Symbol operationType,
				  boolean allowThisItemConfigurations,
				  Item item)
       throws G2AccessException
  {

    Enumeration e = applicableItems.elements();
    if (e.hasMoreElements()) {
      Symbol firstSymbol = (Symbol)e.nextElement();
      condition = createCondition(firstSymbol,
				  operationType,
				  allowThisItemConfigurations,
				  item);
      if (firstSymbol.equals(THIS_)) return;
    }
    while (e.hasMoreElements()) {
      condition = new OrCondition(condition,
				  createCondition((Symbol)e.nextElement(),
						  operationType,
						  allowThisItemConfigurations,
						  item));
    }
  }
			      
  private boolean isG2ClassName(Symbol name) {
    return (!name.equals(THIS_));
  }

  public static boolean viewSelectionContainsInstanceOfClass(WorkspaceView view,
							     Symbol g2ClassName)
       throws G2AccessException
  {
    Sequence inheritancePath;
    WorkspaceElement[] selection = view.getSelection();
    WorkspaceElement elt;
    for (int i=0;i<selection.length;i++) {
      elt = selection[i];
      if (elt.getItem().isInstanceOfG2Class(g2ClassName))
	return true;
    }
    return false;
  }

  public static Method viewSelectionContainsInstanceOfClass;
  static {
    try {
      viewSelectionContainsInstanceOfClass
	= ApplicableItemsCondition.class.getMethod("viewSelectionContainsInstanceOfClass",
						   new Class[]
						   {com.gensym.wksp.WorkspaceView.class,
						      com.gensym.util.Symbol.class});
    } catch (NoSuchMethodException nsme) {
      Trace.exception(nsme);
    }
  }

  public static boolean isInstanceOfG2Class(Item item, Symbol g2ClassName) {
    if (item == null) return false;
    return item.isInstanceOfG2Class(g2ClassName);
  }
  public static Method isInstanceOfG2Class;
  static {
    try {
      isInstanceOfG2Class
	= ApplicableItemsCondition.class.getMethod("isInstanceOfG2Class",
						   new Class[]
						   {com.gensym.classes.Item.class,
						    com.gensym.util.Symbol.class});
    } catch (NoSuchMethodException nsme) {
      Trace.exception(nsme);
    }
  }
  
  private Condition createCondition(Symbol itemOrClassName,
				    Symbol operationType,
				    boolean allowThisItemConfigurations,
				    Item item)
  {
    if (isG2ClassName(itemOrClassName)) {
      try {
	if (NON_MENU_.equals(operationType))
	  return
	    new SimpleCondition(viewSelectionContainsInstanceOfClass, 
				new ContainerReference(WorkspaceView.class),
				new ConstantReference(itemOrClassName));
	else
	  return
	    new SimpleCondition(isInstanceOfG2Class,
				new NestedPropertyReference
				(Item.class,
				 "getItem",
				 new TargetReference(WorkspaceElement.class)),
				new ConstantReference(itemOrClassName));
      } catch (NonStaticMethodException nsme) {
	Trace.exception(nsme);
	return null;
      }
    } else {
      if (allowThisItemConfigurations) {       
	//System.out.println("SETTING THIS DISPATH FOR " + item);
	return new SimpleCondition(SimpleCondition.EQUAL,
				   new NestedPropertyReference
				   (Item.class,
				    "getItem",
				    new TargetReference(item.getClass())),
				   new ConstantReference(item));
      }
    }
      return null;
  }
  
  @Override
  public boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException
  {
    if (condition != null) {
      /*if (condition.isSatisfied(table))
	System.out.println("APP ITEMS SATISFIED for condition = " +condition);*/
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
