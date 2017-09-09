/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GsiDataServiceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:03 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;

public class GsiDataServiceImpl extends com.gensym.classes.VariableImpl implements GsiDataService {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  private static final Symbol LAST_RECORDED_VALUE_ = Symbol.intern("LAST-RECORDED-VALUE");
  /* Generated constructors */

  public GsiDataServiceImpl() {
    super();
  }

  public GsiDataServiceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GsiDataServiceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - STORED-GSI-VARIABLE-STATUS */
  /**
   * Get the stored GSI-VARIABLE-STATUS of this GSI variable. This GSI status of this Data item is not updated
   * in G2 until the variables value is updated using VaraiableOrParameter.setValue
   */
  @Override
  public int getStoredGsiVariableStatus() {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        return vopData.localStatus;
      
  }


  /* Overriden Property - GSI-VARIABLE-VALUE */

  /**
   * Set the value of the corresponding Gsi Variable in G2, updating its GSI-VARIABLE-STATUS, as set by
   * storeGsiVariableStatus().
   */
  @Override
  public void setGsiVariableValue(java.lang.Object value, int status) throws G2AccessException   {
    
        checkValueOkVariableClass(value);
        checkValueOkVariableStatus(status);
        ((G2Gateway)context).returnValues(new Item[] {this}, 
        new java.lang.Object[] {value}, 
        new int[] { status });
      
  }

  /* Overriden Property - STORED-GSI-VARIABLE-VALUE */
  /**
   * Get the stored value to be sent back to this GSI variable during a batch update operation.
   * (For example using com.gensym.jgi.dataservice.DataService.setGsiVariables())
   * @param The Value to store for this GSI-VARIABLE
   */
  @Override
  public java.lang.Object getStoredGsiVariableValue() {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        return vopData.localCurrentValue;
      
  }


  /* Overriden Property - VALUE-FROM-SET-ACTION */
  /**
   * Return the value of this GSI-VARIABLE as set by a SET G2 action.
   */
  @Override
  public java.lang.Object getValueFromSetAction() {
    
                                                                                                   
        Structure attributes = getActualAttributes();
        return attributes.getAttributeValue(LAST_RECORDED_VALUE_, null);
      
  }


  /**
   * Generated Property Setter for attribute -- GSI-INTERFACE-NAME
   * @param gsiInterfaceName new value to conclude for GSI-INTERFACE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGsiInterfaceName(com.gensym.util.Symbol gsiInterfaceName) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GSI_INTERFACE_NAME_, gsiInterfaceName);
  }

  /**
   * Generated Property Getter for attribute -- GSI-INTERFACE-NAME
   * @return the value of the GSI-INTERFACE-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getGsiInterfaceName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GSI_INTERFACE_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- GSI-VARIABLE-STATUS
   * @return the value of the GSI-VARIABLE-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getGsiVariableStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GSI_VARIABLE_STATUS_);
    return ((Integer)retnValue).intValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  /* Overriden method - STORE-GSI-VARIABLE-VALUE */
  @Override
  public void storeGsiVariableValue(java.lang.Object value)
 {
    
        checkValueOkVariableClass(value);
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        
        vopData.localCurrentValue = value;
      
  }

  /* Overriden method - RETURN-GSI-VARIABLE-VALUE */
  @Override
  public void returnGsiVariableValue() throws G2AccessException
 {
    
        VariableOrParameterData vopData = (VariableOrParameterData)data; 
        setGsiVariableValue(vopData.localCurrentValue, vopData.localStatus);
      
  }

  /* Overriden method - CHECK-VALUE-OK-VARIABLE-STATUS */
  protected void checkValueOkVariableStatus(int status)
 {
    
        if (status < 0)
          throw new IllegalArgumentException("The GSI variable status value " + status + " must be nonnegative.");
      
  }

  /* Overriden method - CHECK-VALUE-OK-VARIABLE-CLASS */
  protected void checkValueOkVariableClass(java.lang.Object value)
 {
    
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

  /* Overriden method - STORE-GSI-VARIABLE-STATUS */
  @Override
  public void storeGsiVariableStatus(int statusValue)
 {
    
                                                            
                                                           
        VariableOrParameterData vopData = (VariableOrParameterData)data;
        checkValueOkVariableStatus(statusValue);
        vopData.localStatus = statusValue;
      
  }

  
}
