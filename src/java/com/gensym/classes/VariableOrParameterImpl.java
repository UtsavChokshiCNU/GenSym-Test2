/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      VariableOrParameterImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:22 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.VariableValueListener;
import com.gensym.util.VariableValueEvent;
import com.gensym.util.UnexpectedException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.message.Trace;
import com.gensym.util.EventMulticaster;
import com.gensym.util.ItemEvent;
import com.gensym.jgi.G2AccessException;

public class VariableOrParameterImpl extends com.gensym.classes.ObjectImpl implements VariableOrParameter {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  public static final Sequence VALUE_DENOTATION = new Sequence();
  /* Overriden Field */
  private static final Symbol TYPE_ = Symbol.intern ("TYPE");
  /* Overriden Field */
  private static final Symbol VARIABLE_VALUE_ = Symbol.intern ("VARIABLE-VALUE");
  /* Overriden Field */
  private static final Symbol INITIAL_VALUE2_ = Symbol.intern ("INITIAL-VALUE");
  /* Overriden Field */
  private static final Symbol SUBSCRIPTION_HANDLE2_ = Symbol.intern ("SUBSCRIPTION-HANDLE");
  /* Overriden Field */
  private static final java.lang.Object USER_DATA = 42;
  /* Generated constructors */

  public VariableOrParameterImpl() {
    super();
  }

  public VariableOrParameterImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public VariableOrParameterImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- TRACING-AND-BREAKPOINTS
   * @param tracingAndBreakpoints new value to conclude for TRACING-AND-BREAKPOINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTracingAndBreakpoints(java.lang.Object tracingAndBreakpoints) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_, tracingAndBreakpoints);
  }

  /**
   * Generated Property Getter for attribute -- TRACING-AND-BREAKPOINTS
   * @return the value of the TRACING-AND-BREAKPOINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getTracingAndBreakpoints() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DATA-TYPE
   * @param dataType new value to conclude for DATA-TYPE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDataType(com.gensym.util.Symbol dataType) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DATA_TYPE_, dataType);
  }

  /**
   * Generated Property Getter for attribute -- DATA-TYPE
   * @return the value of the DATA-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getDataType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DATA_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- HISTORY-KEEPING-SPEC
   * @param historyKeepingSpec new value to conclude for HISTORY-KEEPING-SPEC
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setHistoryKeepingSpec(com.gensym.util.Structure historyKeepingSpec) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.HISTORY_KEEPING_SPEC_, historyKeepingSpec);
  }

  /**
   * Generated Property Getter for attribute -- HISTORY-KEEPING-SPEC
   * @return the value of the HISTORY-KEEPING-SPEC attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getHistoryKeepingSpec() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.HISTORY_KEEPING_SPEC_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- LAST-RECORDED-VALUE-TEXT
   * @return the value of the LAST-RECORDED-VALUE-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getLastRecordedValueText() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LAST_RECORDED_VALUE_TEXT_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- VALUE-STRUCTURE-USING-UNIX-TIME
   * @param valueStructureUsingUnixTime new value to conclude for VALUE-STRUCTURE-USING-UNIX-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setValueStructureUsingUnixTime(com.gensym.util.Structure valueStructureUsingUnixTime) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VALUE_STRUCTURE_USING_UNIX_TIME_, valueStructureUsingUnixTime);
  }

  /**
   * Generated Property Getter for attribute -- VALUE-STRUCTURE-USING-UNIX-TIME
   * @return the value of the VALUE-STRUCTURE-USING-UNIX-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getValueStructureUsingUnixTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VALUE_STRUCTURE_USING_UNIX_TIME_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- VALUE-STRUCTURE
   * @param valueStructure new value to conclude for VALUE-STRUCTURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setValueStructure(com.gensym.util.Structure valueStructure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VALUE_STRUCTURE_, valueStructure);
  }

  /**
   * Generated Property Getter for attribute -- VALUE-STRUCTURE
   * @return the value of the VALUE-STRUCTURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getValueStructure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VALUE_STRUCTURE_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- HISTORY-USING-UNIX-TIME
   * @param historyUsingUnixTime new value to conclude for HISTORY-USING-UNIX-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setHistoryUsingUnixTime(com.gensym.util.Sequence historyUsingUnixTime) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.HISTORY_USING_UNIX_TIME_, historyUsingUnixTime);
  }

  /**
   * Generated Property Getter for attribute -- HISTORY-USING-UNIX-TIME
   * @return the value of the HISTORY-USING-UNIX-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getHistoryUsingUnixTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.HISTORY_USING_UNIX_TIME_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- HISTORY
   * @param history new value to conclude for HISTORY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setHistory(com.gensym.util.Sequence history) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.HISTORY_, history);
  }

  /**
   * Generated Property Getter for attribute -- HISTORY
   * @return the value of the HISTORY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getHistory() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.HISTORY_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- EFFECTIVE-DATA-TYPE
   * @return the value of the EFFECTIVE-DATA-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getEffectiveDataType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.EFFECTIVE_DATA_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_, evaluationAttributes);
  }

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_);
    return (com.gensym.util.Structure)retnValue;
  }

  /* Overriden  - VARIABLEVALUE Event Listener - Adder1 */
  @Override
  public void addVariableValueListener(VariableValueListener valueListener)
  throws G2AccessException {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data;
    
        synchronized (vopData) {
          vopData.valueListener = EventMulticaster.add (vopData.valueListener,
    						    valueListener);
          java.lang.Object currentValue = subscribeToValue();
          valueListener.receivedInitialValue(new VariableValueEvent(this,
    								currentValue,
    								VariableValueEvent.INITIAL_VALUE));
        }
      
  }

  /* Overriden  - VARIABLEVALUE Event Listener - Remover1 */
  @Override
  public void removeVariableValueListener(VariableValueListener valueListener)
  throws G2AccessException   {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        synchronized (vopData) {
          vopData.valueListener = EventMulticaster.remove (vopData.valueListener,
    						       valueListener);
          if (vopData.valueListener == null)
    	unsubscribeToValue();
        }
      
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  /* Overriden method - MAKE-DATA-FOR-ITEM */
  @Override
  protected ItemData makeDataForItem()
 {
    
        return new VariableOrParameterData();
      
  }

  /* Overriden method - STATIC */
  static
 {
    
        try {
          VALUE_DENOTATION.addElement(new Structure(new Symbol[] {TYPE_},
                                                    new java.lang.Object[]
    						{VARIABLE_VALUE_}));
        } catch (com.gensym.util.NtwIllegalArgumentException ntwiae) {
          throw new UnexpectedException(ntwiae);
        }
      
  }

  /* Overriden method - PROCESS-VARIABLE-VALUE-EVENT */
  @Override
  public void processVariableValueEvent(VariableValueEvent event)
 {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        synchronized (vopData) {
          vopData.valueListener.valueChanged(event);
        }
      
  }

  /* Overriden method - PROCESS-ITEM-EVENT */
  @Override
  public void processItemEvent(ItemEvent event)
 {
    
        Integer handle = event.getSubscriptionHandle();
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        synchronized (vopData) {
          if (handle.equals(vopData.valueSubscriptionHandle)) {
    	java.lang.Object newValue = event.getNewValue();
    	vopData.currentValue = newValue;
    	vopData.valueListener.valueChanged(new VariableValueEvent
    					   (this, newValue,
    					    VariableValueEvent.NEW_VALUE));
          } else {
    	super.processItemEvent(event);
          }
        }
      
  }

  /* Overriden method - UNSUBSCRIBE-TO-VALUE */
  private void unsubscribeToValue() throws G2AccessException
 {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        synchronized (vopData) {
          context.unsubscribeToItem(vopData.valueSubscriptionHandle.intValue());
          vopData.valueSubscribed = false;
        }
      
  }

  /* Overriden method - SUBSCRIBE-TO-VALUE */
  private java.lang.Object subscribeToValue() throws G2AccessException
 {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        synchronized (vopData) {
          if (vopData.valueSubscribed) {
    	return vopData.currentValue;
          }
    
          Structure struct = context.subscribeToItem(this, VALUE_DENOTATION,
    						 USER_DATA);
          try {
    	vopData.valueSubscriptionHandle =
    	  ((Integer) struct.getAttributeValue (SUBSCRIPTION_HANDLE2_));
    	vopData.currentValue =
    	  struct.getAttributeValue (INITIAL_VALUE2_);
    	vopData.valueSubscribed = true;
    	return vopData.currentValue;
          } catch (NoSuchAttributeException nsae) {
    	Trace.exception(nsae, null);
    	throw new UnexpectedException(nsae);
          }
        }
      
  }

  /* Overriden method - MAKE-VALUE-SNAPSHOT */
  private Structure makeValueSnapshot()
 {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        return new Structure(new Symbol[] {SUBSCRIPTION_HANDLE2_, INITIAL_VALUE2_},
                             new java.lang.Object[]
    			 {vopData.valueSubscriptionHandle,
    			  vopData.currentValue},
    			 2);
      
  }

  /* Overriden method - ADD-VARIABLE-VALUE-LISTENER-RETRIEVING-STATE */
  @Override
  public Structure addVariableValueListenerRetrievingState(VariableValueListener
							   valueListener)
  throws G2AccessException
 {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data;
    
        synchronized (vopData) {
          addVariableValueListener(valueListener);
          return makeValueSnapshot();
        }
      
  }

  
}
