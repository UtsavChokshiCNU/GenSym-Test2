/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   VariableOrParameterSpecialImpl.java 
 * 
 * 
 */ 

package com.gensym.classes;

import com.gensym.util.VariableValueListener;
import com.gensym.util.VariableValueEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.UnexpectedException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.message.Trace;
import com.gensym.util.EventMulticaster;
import com.gensym.util.ItemEvent;
import com.gensym.jgi.G2AccessException;

public class VariableOrParameterSpecialImpl extends ItemImpl {

  /**
   * @undocumented A single denotation. Public for subclass access
   */
  public static final Sequence VALUE_DENOTATION = new Sequence();
  private static final Symbol TYPE_ = Symbol.intern ("TYPE");
  private static final Symbol VARIABLE_VALUE_ =
  Symbol.intern ("VARIABLE-VALUE");
  private static final Symbol INITIAL_VALUE2_ = Symbol.intern ("INITIAL-VALUE");
  private static final Symbol SUBSCRIPTION_HANDLE2_ =
  Symbol.intern ("SUBSCRIPTION-HANDLE");

  static {
    try {
      VALUE_DENOTATION.addElement(new Structure(new Symbol[] {TYPE_},
                                                new java.lang.Object[]
						{VARIABLE_VALUE_}));
    } catch (com.gensym.util.NtwIllegalArgumentException ntwiae) {
      throw new UnexpectedException(ntwiae);
    }
  }

  @Override
  protected ItemData makeDataForItem() {
    return new VariableOrParameterData();
  }

  /**
   * Adds <code>valueListener</code> as a listener receiving updates
   * to changes in the value of this <code>VariableOrParameter</code>.
   * Makes an RPC call to G2 if this is the first listener.
   *
   * @param valueListener the listener to add
   * @exception G2AccessException if the RPC call fails.
   */
  public void addVariableValueListener(VariableValueListener valueListener)
  throws G2AccessException{
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

  /**
   * @undocumented
   */
  public Structure addVariableValueListenerRetrievingState(VariableValueListener
							   valueListener)
  throws G2AccessException{
    VariableOrParameterData vopData = (VariableOrParameterData)data;

    synchronized (vopData) {
      addVariableValueListener(valueListener);
      return makeValueSnapshot();
    }
  }

  private Structure makeValueSnapshot() {
    VariableOrParameterData vopData = (VariableOrParameterData)data;
    return new Structure(new Symbol[] {SUBSCRIPTION_HANDLE2_, INITIAL_VALUE2_},
                         new java.lang.Object[]
			 {vopData.valueSubscriptionHandle,
			  vopData.currentValue},
			 2);
  }

  private static final java.lang.Object USER_DATA = 42;

  private java.lang.Object subscribeToValue() throws G2AccessException {
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

  /**
   * Removes <code>valueListener</code> as a listener receiving updates
   * to changes in the value of this <code>VariableOrParameter</code>.
   * Makes an RPC call to G2 if this is the last remaining listener.
   *
   * @param valueListener the listener to add
   * @exception G2AccessException if the RPC call fails.
   */
  public void removeVariableValueListener(VariableValueListener valueListener)
  throws G2AccessException {
    VariableOrParameterData vopData = (VariableOrParameterData)data;
    synchronized (vopData) {
      vopData.valueListener = EventMulticaster.remove (vopData.valueListener,
						       valueListener);
      if (vopData.valueListener == null)
	unsubscribeToValue();
    }
  }

  private void unsubscribeToValue() throws G2AccessException {
    VariableOrParameterData vopData = (VariableOrParameterData)data;
    synchronized (vopData) {
      context.unsubscribeToItem(vopData.valueSubscriptionHandle.intValue());
      vopData.valueSubscribed = false;
    }
  }

  /**
   * @undocumented
   */
  @Override
  public void processItemEvent(ItemEvent event) {
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

  /**
   * @undocumented
   */
  public void processVariableValueEvent(VariableValueEvent event) {
    VariableOrParameterData vopData = (VariableOrParameterData)data;
    synchronized (vopData) {
      vopData.valueListener.valueChanged(event);
    }
  }      
}
