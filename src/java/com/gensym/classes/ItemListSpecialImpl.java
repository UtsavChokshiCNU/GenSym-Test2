package com.gensym.classes;


import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.G2AccessException;

public class ItemListSpecialImpl extends ItemListImpl {

  /**
   * Generated Property Setter for attribute -- G2-LIST-SEQUENCE
   * @param g2ListSequence new value to conclude for G2-LIST-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2ListSequence(com.gensym.util.Sequence g2ListSequence) 
       throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.G2_LIST_SEQUENCE_, g2ListSequence);
    if (isItemLocal()) //by copy 
       setPropertyValue(SystemAttributeSymbols.ELEMENT_TYPE_, 
			    com.gensym.util.symbol.G2TypeSymbols.ITEM_);
  }

  /**
   * Generated Property Getter for attribute -- G2-LIST-SEQUENCE
   * @return the value of the G2-LIST-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getG2ListSequence() 
       throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_LIST_SEQUENCE_);
    return (com.gensym.util.Sequence)retnValue;
  }




}

    
