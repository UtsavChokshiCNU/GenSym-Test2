package com.gensym.icons;

import java.util.*;
import java.awt.*;
import com.gensym.util.*;
import com.gensym.message.*;


public class PowerSymbol extends Object {

  protected boolean isdynamic = false;
  private Symbol symbolVariable;
  private Symbol currentValue;

  public PowerSymbol(Symbol symbol) {
    isdynamic = true; //I cant tell, so yes
    this.symbolVariable = symbol;
    this.currentValue = symbol;
  }

  private Symbol eval(Symbol symbolVariable,
		      Structure variables,
		      Structure overrides) {
    Symbol value = null;
    if (overrides != null) {
      value = (Symbol) overrides.getAttributeValue(symbolVariable, null);
      if (value != null)
	return (Symbol) value;
    }
    if (variables != null) {
      value = (Symbol) variables.getAttributeValue(symbolVariable, null);
      if (value != null)
	return (Symbol) value;
    }
    return currentValue;
  }

  public void eval(Structure variables, Structure overrides) {
    this.currentValue = eval(symbolVariable, variables, overrides);
  }

  public Symbol currentValue() {
    return currentValue;
  }
  
}



       
    
