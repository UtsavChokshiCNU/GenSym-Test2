package com.gensym.icons;

import java.util.*;
import java.awt.*;
import com.gensym.util.*;
import com.gensym.message.*;


public class PowerLabel extends Object {

  protected boolean isdynamic = false;
  private Symbol labelVariable;
  private String currentValue = "default";
  private boolean powerLabelDebugP = false;

  public PowerLabel(Object label) {
    if (label instanceof Symbol) {
      isdynamic = true;
      this.labelVariable = (Symbol) label;
    } else if (label instanceof String) {
      this.currentValue = (String) label;
    }
  }

  private String eval(Symbol labelVariable,
		      Structure variables,
		      Structure overrides) {
    if (powerLabelDebugP) {
      System.out.println("Evaling Label "+ labelVariable + overrides + variables);
    }
    Object value = null;
    if (overrides != null) {
      value = overrides.getAttributeValue(labelVariable, null);
      if (value != null)
	return (String) value;
    }
    if (variables != null) {
      value = variables.getAttributeValue(labelVariable, null);
      if (value != null)
	return (String) value;
    }
    return currentValue;
  }

  public void eval(Structure variables, Structure overrides) {
    this.currentValue = eval(labelVariable, variables, overrides);
  }

  @Override
  public String toString() {
    return currentValue;
  }
  
}



       
    
