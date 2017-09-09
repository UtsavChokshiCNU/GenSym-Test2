package com.gensym.wksp;

import com.gensym.util.WorkspaceEvent;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;

/**
 * A <code>WorkspaceTable</code> intended for use with a <code>FreeformTable</code>.
 */
public interface WorkspaceFreeformTable extends WorkspaceTable {

  /**
   * An attribute name received in the <code>handleTableCellChanged</code> method for this class.
   * @see #handleTableCellChanged
   */  
  final static Symbol CELL_DISPLAY_TEXT_ = Symbol.intern("CELL-DISPLAY-TEXT");
  
  /**
   * An attribute name contained within the cell information, for each cell of the table.
   */  
  final static Symbol CELL_FORMAT_ = Symbol.intern("CELL-FORMAT");
  /**
   * An attribute name contained within the cell format, for each cell of the table.
   */  
  final static Symbol BACKGROUND_COLOR_ = Symbol.intern("BACKGROUND-COLOR");
  /**
   * An attribute name contained within the cell format, for each cell of the table.
   */  
  final static Symbol TEXT_COLOR_ = Symbol.intern("TEXT-COLOR");
  /**
   * An attribute name contained within the cell format, for each cell of the table.
   */    
  final static Symbol BORDER_COLOR_ = Symbol.intern("BORDER-COLOR");
  /**
   * An attribute name contained within the cell format, for each cell of the table.
   */    
  final static Symbol TEXT_SIZE_ = Symbol.intern("TEXT-SIZE");
  /**
   * An attribute name contained within the cell format, for each cell of the table.
   */      
  final static Symbol TEXT_ALIGNMENT_ = Symbol.intern("TEXT-ALIGNMENT");
  /**
   * An attribute name contained within the itemModified method for this class.
   */        
  final static Symbol DEFAULT_CELL_FORMAT_ = SystemAttributeSymbols.DEFAULT_CELL_FORMAT_;
  /**
   * An attribute name contained within the table default cell format.
   */      
  final static Symbol WIDTH_ = Symbol.intern("WIDTH");
  /**
   * An attribute name contained within the table default cell format.
   */        
  final static Symbol HEIGHT_ = Symbol.intern("HEIGHT");


}
