package com.gensym.wksp;

import java.lang.Object;
import java.awt.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.draw.*;

/**
 *
 * TableRow
 *
 */

public class TableRow extends Object
{
  private static Symbol leftTextSymbol = Symbol.intern("LEFT-TEXT");
  private static Symbol rightTextSymbol = Symbol.intern("RIGHT-TEXT");
  private static int leftCellIndex = 0;
  private static int rightCellIndex = 1;
  private TextCell leftCell;
  private TextCell rightCell;
  private TextStyle leftStyle;
  private TextStyle rightStyle;

  private Color default_background_color = Color.white;
  private Color textColor = Color.black;
  private Color default_border_color = Color.black;
  private int default_border_width = 0;
  private int dividerWidth = 1;
  private static int defaultRightMargin = 4;//11;
  private static int defaultLeftMargin = 4;
  private boolean leftCellNotFormatted = true;
  private boolean rightCellNotFormatted = true;
  private static boolean tableRowDebugP = false;


  
  public TableRow(Structure tableRowData, int leftWidth,int rightWidth,
		  TextStyle leftStyle,
		  TextStyle rightStyle,
		  Color textColor)
  {
    this.textColor = textColor;
    this.leftStyle = leftStyle;
    this.rightStyle = rightStyle;
    initialize(tableRowData, leftWidth, rightWidth);
  }


  private void initializeTextCell(int cellIndex,
				  String text,
				  int cellWidth) 
  {
    if (text != null)
      {
	TextCell newCell = new TextCell(cellWidth, 
					text,
					((cellIndex == 0) ? leftStyle : rightStyle),
					default_background_color,
					textColor,
					default_border_width,
					default_border_color);
	if (cellIndex == 0) 
	  {
	    newCell.setTextJustification (TextCell.RIGHT);
	    newCell.setRightMargin (defaultRightMargin);
	    leftCell = newCell;
	  } 
	else
	  {
	    newCell.setLeftMargin(defaultLeftMargin);
	    rightCell = newCell;
	  }
      }
  }
  
  private int widthOfTextString(String theString,Font theFont) {
    Toolkit toolkit = Toolkit.getDefaultToolkit();
    FontMetrics metrics = toolkit.getFontMetrics(theFont);
    return metrics.stringWidth(theString);
  }

  public TextCell addCell(int index, String text, int width)
  {
    initializeTextCell(index, text, width);
    leftCellNotFormatted = true;
    rightCellNotFormatted = true;
    return getCell(index);
  }
  
  public void initialize(Structure tableRowData,
			 int leftCellWidth, 
			 int rightCellWidth) {
			 
    String leftText = (String) tableRowData.getAttributeValue(leftTextSymbol, null);
    String rightText = (String) tableRowData.getAttributeValue(rightTextSymbol, null);
    
    initializeTextCell(leftCellIndex, leftText, leftCellWidth);
    if (leftText == null)
      rightCellWidth = rightCellWidth + leftCellWidth + dividerWidth;
    initializeTextCell(rightCellIndex, rightText, rightCellWidth);
  }
  
  public void format(Graphics g) {
    if (leftCellNotFormatted && (leftCell != null)) {
      leftCellNotFormatted = false;
      leftCell.format(g);
    }
    if (rightCellNotFormatted && (rightCell != null)) {
      rightCellNotFormatted = false;
      rightCell.format(g);
    }
  }

  void invalidateRowFormatting()
  {
    leftCellNotFormatted = true;
    rightCellNotFormatted = true;
  }
  
  public void Draw (Graphics g, int shift_x, int shift_y,
		    boolean drawDivider,
		    Color dividerColor)
  {
    int currentSpacingBetweenCells = 0;
    int leftCellWidth = 0;
    if (leftCell != null) {
      leftCellWidth = leftCell.getWidth();
      leftCell.draw(g, shift_x, shift_y);
      currentSpacingBetweenCells = dividerWidth;
      if (drawDivider) {
	g.setColor(dividerColor);
	int shiftedDividerLeft = leftCellWidth + shift_x;
	g.drawLine(shiftedDividerLeft,
		   shift_y,
		   shiftedDividerLeft,
		   shift_y + getHeight());
      }
    }
    if (rightCell != null) {
      rightCell.draw(g,
		     shift_x + leftCellWidth + currentSpacingBetweenCells,
		     shift_y);
    }
  }		   



  public void setRightTextColor(Color textColor) {
    this.textColor = textColor;
    if (rightCell != null) {
      rightCell.setTextColor(textColor);
    }
  }

  public void setLeftTextColor(Color textColor) {
    this.textColor = textColor;
    if (leftCell != null) {
      leftCell.setTextColor(textColor);
    }
  }

  public void setTextColor(Color textColor) {
    this.textColor = textColor;
    if (rightCell != null) {
      rightCell.setTextColor(textColor);
    }
    if (leftCell != null) {
      leftCell.setTextColor(textColor);
    }
  }
      
  public int getTopMargin() {
    TextCell cell = rightCell;
    if (cell == null) 
      cell = leftCell;
    if (cell == null) 
	return 0;
    else
      return cell.getTopMargin();
  }

  public int getBottomMargin() {
    TextCell cell = rightCell;
    if (cell == null) 
      cell = leftCell;
    if (cell == null) 
      return 0;
    else 
      return cell.getBottomMargin();
  }

  public void setLeftMargin(int margin) {
    if (rightCell != null)
      rightCell.setLeftMargin(margin);
  }

  public void setRightMargin(int margin) {
    if (leftCell != null)
      leftCell.setRightMargin(margin);
  }
  
  public void setTopMargin(int margin) {
    if (tableRowDebugP)
      System.out.println("setting topmargin in row to " + margin);
    if (leftCell != null)
      leftCell.setTopMargin(margin);
    if (rightCell != null)
      rightCell.setTopMargin(margin);
  }

  public void setCellBorderWidth(int width) {
    if (leftCell != null)
      leftCell.setBorderWidth(width);
    if (rightCell != null)
      rightCell.setBorderWidth(width);
  }
  
  public void setBottomMargin(int margin) {
    if (leftCell != null)
      leftCell.setBottomMargin(margin);
    if (rightCell != null)
      rightCell.setBottomMargin(margin);
  }
  
  public int getHeight() {
    int leftHeight = 0;
    int rightHeight = 0;
    if (leftCell != null)
      leftHeight = leftCell.getHeight();
    if (rightCell != null)
      rightHeight = rightCell.getHeight();
	
    return Math.max(rightHeight,leftHeight);
  }
  
  @Override
  public String toString() {
    return " [ " + leftCell + " | " + rightCell + " ]";
  }
  

  public int inside(int logical_x, int logical_y)
  {
    if ((leftCell != null)&&(leftCell.inside(logical_x, logical_y)))
      return leftCellIndex;
    else if ((rightCell != null)&&(rightCell.inside(logical_x, logical_y)))
      return rightCellIndex;
    else
      return -1;
  }

  public TextCell getCell(int index) {
    if (index == leftCellIndex)
      return leftCell;
    else if (index == rightCellIndex)
      return rightCell;
    else
      return null;
  }
  

}
