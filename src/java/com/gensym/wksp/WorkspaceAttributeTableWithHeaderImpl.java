package com.gensym.wksp;

import java.awt.*;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import com.gensym.draw.*;
import com.gensym.classes.Item;
import com.gensym.classes.Table;
import com.gensym.jgi.G2AccessException;

/**
 *
 * WorkspaceAttributeTableWithHeader <p>
 * A WorkspaceAttributeTable that appears with the right text of the
 * first row center justified, with white text on a black background.
 *
 */
public class WorkspaceAttributeTableWithHeaderImpl
extends WorkspaceAttributeTableImpl {

  private boolean workspaceAttributeTableWithHeaderDebugP = false;

  /**
   * @param item The g2 item which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   */  
  public WorkspaceAttributeTableWithHeaderImpl(Table item, WorkspaceView parent)
  throws G2AccessException {
    super (item,parent);
    // setBorderWidth(2);
    setFormatting();
  }

  @Override
  protected void setFormatting() {
    super.setFormatting();
    setDividerWidth(1);
    setDrawHorizontalDivider(true);
    setCellBorderWidth(2);
    //setFontsize(18);
    int rowCount;
    TextCell tmpCell;
    if ((tableRows != null) && ((rowCount = tableRows.length) >0)) {
      TableRow header = tableRows[0];
      TextCell headerCell = header.getCell(1);
      headerCell.setBackgroundColor(Color.black);
      if (workspaceAttributeTableWithHeaderDebugP){
	headerCell.setBorderColor(Color.red);
	headerCell.setDrawBorder(true);
	headerCell.setBackgroundColor(Color.blue);
      } 
      headerCell.setTextColor(Color.white);
      headerCell.setDrawBackground(true);
      headerCell.setTextJustification (TextCell.CENTER);

      if (workspaceAttributeTableWithHeaderDebugP) {
	if (rowCount >10) {
	  tableRows[2].getCell(1).setDrawBackground(true);
	  tableRows[2].getCell(1).setBackgroundColor(Color.cyan);

	  tmpCell = tableRows[4].getCell(1);
	  if (tmpCell != null) {
	    tmpCell.setDrawBorder(true);
	    tmpCell.setBorderColor(Color.green);
	    tmpCell.setDrawBackground(true);
	    tmpCell.setBackgroundColor(Color.yellow);
	    tmpCell.setTextColor(Color.orange);
	  }
	  
	  tableRows[6].getCell(1).setBorderColor(Color.green);
	  tableRows[6].getCell(1).setDrawBorder(true);
	  
	  tableRows[7].getCell(1).setTextColor(Color.blue);
	  tableRows[7].getCell(1).setDrawBorder(true);
	  tableRows[7].getCell(1).setBorderColor(Color.pink);
	  tmpCell = tableRows[8].getCell(0);
	  if (tmpCell != null) {
	    tmpCell.setDrawBorder(true);
	    tmpCell.setBorderColor(Color.red);
	  }
	  
	  tableRows[9].getCell(1).setReverseVideo();
	  tableRows[9].getCell(1).setDrawBackground(true);
	  tmpCell = tableRows[rowCount-1].getCell(1);
	  tmpCell.setDrawBorder(true);
	  tmpCell.setBorderColor(Color.red);
	  tmpCell.setDrawBackground(true);
	  tmpCell.setBackgroundColor(Color.yellow);
	    
	}
      }
    }
  }

  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    int rowCount = tableRows.length;
    TableRow currentTableRow;
    //NEED TO SKIP THE HEADER
    for (int i = 1; i<rowCount; i++) {
      currentTableRow = tableRows[i];
      currentTableRow.setTextColor(getTextLineColor());
    }
    canvas.invalidateElement(this);
  }

}
