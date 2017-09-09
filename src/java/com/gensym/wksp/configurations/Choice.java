package com.gensym.wksp.configurations;

import com.gensym.util.Symbol;

public class Choice {
  private Symbol operationType, name;

  /**
   * @param name a Symbol naming a G2 menu choice.
   * @param operationType a Symbol naming the valid operation type
   * of a configuration statement.
   * @see OperationTypes
   */
  public Choice(Symbol name, Symbol operationType) {
    this.name = name;
    this.operationType = operationType;
  }
  /**
   * @return the operation type for this Choice.
   */
  public Symbol getOperationType() {
    return operationType;
  }

  /**
   * @return the name for this choice
   */
  public Symbol getName() {
    return name;
  }
    
}
