package com.gensym.wksp;

import com.gensym.util.WorkspaceEvent;
import com.gensym.util.Symbol;

/**
 * A <code>WorkspaceElement</code> intended for use with <code>TableItem</code>s and
 * <code>FreeFormTable</code>s.
 */
public interface WorkspaceTable extends WorkspaceElement {

  /**
   * An attribute name received <code>handleTableCellChanged</code> in the method for this class.
   *@see #handleTableCellChanged
   */
  static final Symbol ROW_INDEX_ = Symbol.intern("ROW-INDEX");
  /**
   * An attribute name received in the <code>handleTableCellChanged</code> method for this class.
   *@see #handleTableCellChanged
   */
  static final Symbol COLUMN_INDEX_ = Symbol.intern("COLUMN-INDEX");
  /**
   * An attribute name received in the <code>handleTableCellChanged</code> method for this class.
   *@see #handleTableCellChanged
   */  
  static final Symbol TABLE_ROWS_ = Symbol.intern("TABLE-ROWS");
  /**
   * An attribute name received in the <code>handleTableCellChanged</code> method for this class.
   *@see #handleTableCellChanged
   */  
  static final Symbol TABLE_CELLS_ = Symbol.intern("TABLE-CELLS");
  /**
   * An attribute name received in the <code>handleTableCellChanged</code> method for this class.
   *@see #handleTableCellChanged
   */  
  static final Symbol CELL_ATTRIBUTE_NAME_ = Symbol.intern("CELL-ATTRIBUTE-NAME");
  /**
   * An attribute name received in the <code>handleTableCellChanged</code> method for this class.
   *@see #handleTableCellChanged
   */  
  static final Symbol CELL_DISPLAY_TEXT_ = Symbol.intern("CELL-DISPLAY-TEXT");
  
  /**
   * Invoked when the cell of a <code>TableItem</code> or <code>FreeFormTable</code> has changed.
   * @param event A WorkspaceEvent with ID of <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be <code>TABLE_ROWS_</code>
   * for <code>TableItem</code>s and <code>TABLE_CELLS_</code> for <code>FreeFormTables</code>.
   * The attribute named by <code>CELL_ATTRIBUTE_NAME_</code> will specify which attribute
   * of the cell has changed. 
   * The row and column index of the cell that has changed are contained
   * within the attributes <code>ROW_INDEX_</code> and <code>COLUMN_INDEX</code>, and
   * the new value for the cell is contained in the attribute named by
   * <code>WorkspaceElement.NEW_VALUE_</code>.
   */
  public void handleTableCellChanged(WorkspaceEvent event);

  /**
   * Invoked when the table requires reformatting using fresh data.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be <code>TABLE_ROWS_</code>
   * for <code>TableItem</code>s and <code>TABLE_CELLS_</code> for
   * <code>FreeFormTable</code>s.  The attribute named by
   * <code>WorkspaceElement.NEW_VALUE_</code> will contain all the data needed to
   * reconstruct the table from scratch.
   */
  public void handleTableCellsChanged(WorkspaceEvent event);
}


