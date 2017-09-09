package com.gensym.wksp;

import java.awt.*;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.TextBoxFormat;
import java.util.*;
import com.gensym.draw.*;
import com.gensym.classes.Item;
import com.gensym.classes.Table;
import com.gensym.jgi.G2AccessException;

/**
 *
 * WorkspaceAttributeDisplay <p>
 * A DrawElement that appears as an attribute-display
 *
 */
public class WorkspaceAttributeDisplayImpl extends WorkspaceAttributeTableImpl 
{
  /**
   * @param item The g2 item which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   * @see initialize
   */
  public WorkspaceAttributeDisplayImpl(Table item, WorkspaceView parent)
  throws G2AccessException {
    super (item, parent);
    setFormatting();
    updateColors(item, parent.getColorTable());
  }


  private static Symbol rightTextColorSymbol = Symbol.intern("RIGHT-TEXT-LINE-COLOR");
  private static Symbol leftTextColorSymbol = Symbol.intern("LEFT-TEXT-LINE-COLOR");
  private static Symbol foregroundSymbol = Symbol.intern("FOREGROUND");

  protected void updateColors(Table table, ColorTable colorTable) {
    Sequence tableRowsSequence = null;
    try {
      tableRowsSequence = table.getTableRows();
    } catch (Exception e) {
      System.err.println("Error: " + e);
    }
      
    Enumeration tableRowsData = tableRowsSequence.elements();
    TableRow currentTableRow;
    Structure tableRowData;
    int i = 0;
    while (tableRowsData.hasMoreElements()) {
      tableRowData = (Structure) tableRowsData.nextElement();
      currentTableRow = tableRows[i];
      Color rightTextColor =
	colorTable.lookup((Symbol) tableRowData.getAttributeValue(rightTextColorSymbol, foregroundSymbol));
      currentTableRow.setRightTextColor(rightTextColor);
      Color leftTextColor =
	colorTable.lookup((Symbol) tableRowData.getAttributeValue(leftTextColorSymbol, foregroundSymbol));
      currentTableRow.setLeftTextColor(leftTextColor);
      i++;
    }
    canvas.invalidateElement(this);
  }

  @Override
  protected void setFormatting() {
    //setBorderWidth(0);
    setDividerWidth(0);
    setDrawBorder(false);
    setDrawVerticalDivider(false);
  }

}
