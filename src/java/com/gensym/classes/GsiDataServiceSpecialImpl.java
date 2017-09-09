
package com.gensym.classes;

import com.gensym.util.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;

public class GsiDataServiceSpecialImpl extends ItemImpl {

  /**
   * Store the GSI-VARIABLE-STATUS of this GSI variable. The GSI status of this Data item is not updated
   * in G2 until the variables value is updated.
   */
  public void storeGsiVariableStatus(int statusValue) {
    // The GSI-VARIABLE-STATUS need to be stored locally
    // It can only be sent back via a gsi_return_values
    VariableOrParameterData vopData = (VariableOrParameterData)data;
    checkValueOkVariableStatus(statusValue);
    vopData.localStatus = statusValue;
  }

  /**
   * Get the stored GSI-VARIABLE-STATUS of this GSI variable. This GSI status of this Data item is not updated
   * in G2 until the variables value is updated using VaraiableOrParameter.setValue
   */
  public int getStoredGsiVariableStatus() {
    VariableOrParameterData vopData = (VariableOrParameterData)data;
    return vopData.localStatus;
  }

  /**
   * Set the value of the corresponding Gsi Variable in G2, updating its GSI-VARIABLE-STATUS, as set by
   * storeGsiVariableStatus().
   */
  public void setGsiVariableValue(java.lang.Object value, int status) throws G2AccessException {
    checkValueOkVariableClass(value);
    checkValueOkVariableStatus(status);
    ((G2Gateway)context).returnValues(new Item[] {this}, 
    new java.lang.Object[] {value}, 
    new int[] { status });
  }

  protected void checkValueOkVariableClass(java.lang.Object value) {
    if (value instanceof Integer && 
	(this instanceof IntegerVariable ||
	 this instanceof QuantitativeVariable)) { return; }
    if (value instanceof Double && 
	(this instanceof FloatVariable ||
	 this instanceof QuantitativeVariable)) { return; }
    if (value instanceof String && this instanceof TextVariable ) { 
    	return; 
    }
    if (value instanceof Symbol && this instanceof SymbolicVariable) { 
    	return; 
    }
    if (value instanceof Boolean && this instanceof LogicalVariable ) { 
    	return;
    } 
    
    throw new IllegalArgumentException("The value " + value + 			       
				       " is of the wrong type to send back to G2 variable (" + 
				       this + ") + of class " + getActualAttributes().getAttributeValue(CLASS_, null));
  }

  protected void checkValueOkVariableStatus(int status) {
    if (status < 0)
      throw new IllegalArgumentException("The GSI variable status value " + status + " must be nonnegative.");
  }

  /**
   * Set the value of the corresponding Gsi Variable in G2 as set by storeGSIVariableValue and
   * updating its GSI-VARIABLE-STATUS, as set by storeGsiVariableStatus().
   */
  public void returnGsiVariableValue() throws G2AccessException {
    VariableOrParameterData vopData = (VariableOrParameterData)data; 
    setGsiVariableValue(vopData.localCurrentValue, vopData.localStatus);
  }

  /**
   * Store a value to be sent back to this GSI variable during a batch update operation.
   * (For example using com.gensym.jgi.dataservice.DataService.setGsiVariables())
   * @param The Value to store for this GSI-VARIABLE
   */
  public void storeGsiVariableValue(java.lang.Object value) {
    checkValueOkVariableClass(value);
    VariableOrParameterData vopData = (VariableOrParameterData)data;
    
    vopData.localCurrentValue = value;
  }

  /**
   * Get the stored value to be sent back to this GSI variable during a batch update operation.
   * (For example using com.gensym.jgi.dataservice.DataService.setGsiVariables())
   * @param The Value to store for this GSI-VARIABLE
   */
  public java.lang.Object getStoredGsiVariableValue() {
    VariableOrParameterData vopData = (VariableOrParameterData)data;
    return vopData.localCurrentValue;
  }

  private static final Symbol LAST_RECORDED_VALUE_ = Symbol.intern("LAST-RECORDED-VALUE");
  /**
   * Return the value of this GSI-VARIABLE as set by a SET G2 action.
   */
  public java.lang.Object getValueFromSetAction() {
    /** Last recorded value will be set during the resolution of this item by the native lib */
    Structure attributes = getActualAttributes();
    return attributes.getAttributeValue(LAST_RECORDED_VALUE_, null);
  }

}
