/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      FreeformTable.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:44:03 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface FreeformTable extends com.gensym.classes.Item, com.gensym.classes.NewTable {

  public static final Symbol FREEFORM_TABLE_ = com.gensym.util.symbol.G2ClassSymbols.FREEFORM_TABLE_;
  static final Symbol g2ClassName = FREEFORM_TABLE_;
  static final Symbol[] classInheritancePath = new Symbol[] {FREEFORM_TABLE_, ITEM_, NEW_TABLE_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- TABLE-SIZE
   * @return the value of the TABLE-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TABLE-SIZE is : 
   * (Structure 
    NUMBER-OF-COLUMNS Integer
    NUMBER-OF-ROWS Integer)
   *
   */
  public com.gensym.util.Structure getTableSize() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TABLE-SIZE
   * @param tableSize new value to conclude for TABLE-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTableSize(com.gensym.util.Structure tableSize) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TABLE-CELLS
   * @return the value of the TABLE-CELLS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TABLE-CELLS is : 
   * (Sequence 
    (Sequence 
      (OR (MEMBER NONE)
          (Structure 
            EXPRESSION Text
            CELL-DISPLAY-VALUE Value
            CELL-DISPLAY-TEXT Text
            CELL-FORMAT
              (Structure 
                BACKGROUND-COLOR
                  (OR Symbol
                      (Structure 
                        EXPRESSION Text
                        PRIORITY
                          (MEMBER 1 2 3 4 5 6 7 8 9 10)
                        CURRENT-VALUE Symbol
                        SCAN-INTERVAL Quantity
                        INITIAL-SCAN-WAIT-INTERVAL Quantity
                        VALUE-DOMAIN
                          (MEMBER INFERENCE-ENGINE G2-SIMULATOR)
                        UPDATE-ONLY-WHEN-SHOWN BooleanTruthValue
                        TRACING-AND-BREAKPOINTS
                          (Structure 
                            WARNING-MESSAGE-LEVEL
                              (MEMBER 0 1 2 3)
                            TRACING-MESSAGE-LEVEL
                              (MEMBER 0 1 2 3)
                            BREAKPOINT-LEVEL
                              (MEMBER 0 1 2 3))
                        TIME-OUT-WHEN-REQUESTING-DATA-SEEKING Integer
                        MAY-REQUEST-EVENT-UPDATES BooleanTruthValue
                        MAY-REQUEST-DATA-SEEKING BooleanTruthValue))
                BORDER-COLOR Symbol
                TEXT-COLOR Symbol
                TEXT-ALIGNMENT
                  (MEMBER LEFT CENTER RIGHT)
                TEXT-SIZE
                  (MEMBER SMALL LARGE EXTRA-LARGE))
            CELL-EVALUATION-ATTRIBUTES
              (Structure 
                PRIORITY
                  (MEMBER 1 2 3 4 5 6 7 8 9 10)
                SCAN-INTERVAL Quantity
                INITIAL-SCAN-WAIT-INTERVAL Quantity
                VALUE-DOMAIN
                  (MEMBER INFERENCE-ENGINE G2-SIMULATOR)
                UPDATE-ONLY-WHEN-SHOWN BooleanTruthValue
                TRACING-AND-BREAKPOINTS
                  (Structure 
                    WARNING-MESSAGE-LEVEL
                      (MEMBER 0 1 2 3)
                    TRACING-MESSAGE-LEVEL
                      (MEMBER 0 1 2 3)
                    BREAKPOINT-LEVEL
                      (MEMBER 0 1 2 3))
                TIME-OUT-WHEN-REQUESTING-DATA-SEEKING Integer
                MAY-REQUEST-EVENT-UPDATES BooleanTruthValue
                MAY-REQUEST-DATA-SEEKING BooleanTruthValue)))
      1))
    1))
   *
   */
  public com.gensym.util.Sequence getTableCells() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TABLE-CELLS
   * @param tableCells new value to conclude for TABLE-CELLS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTableCells(com.gensym.util.Sequence tableCells) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EVALUATION-ATTRIBUTES is : 
   * (OR NoItem
      (Structure 
        MAY-REFER-TO-INACTIVE-ITEMS BooleanTruthValue
        MAY-RUN-WHILE-INACTIVE BooleanTruthValue))
   *
   */
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIZE-IN-WORKSPACE
   * @return the value of the SIZE-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIZE-IN-WORKSPACE is : 
   * (OR NoItem
      (Structure 
        WIDTH Quantity
        HEIGHT Quantity))
   *
   */
  public com.gensym.util.Structure getSizeInWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIZE-IN-WORKSPACE
   * @param sizeInWorkspace new value to conclude for SIZE-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSizeInWorkspace(com.gensym.util.Structure sizeInWorkspace) throws G2AccessException;

}
