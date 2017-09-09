package com.gensym.wksp;

import com.gensym.jgi.G2AccessException;
import com.gensym.draw.*;
import com.gensym.classes.Table;
import com.gensym.classes.Item;
import com.gensym.classes.FreeformTable;
import com.gensym.classes.NewTable;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.*;
import java.awt.*;
import java.util.*;

/**
 *
 * WorkspaceFreeformTableImpl <p>
 * A WorkspaceTable that appears as FreeformTable
 */

public class WorkspaceFreeformTableImpl extends BasicDrawElement
implements WorkspaceFreeformTable
{
  private TextCell[][] tableCells;
  private WorkspaceElementHelper helper;
  private boolean notFormatted = true;
  private Rectangle[] bounds;
  private int cellWidth;
  private int cellHeight;
  private Symbol defaultTextColor;
  private Symbol defaultBackgroundColor;
  private Symbol defaultBorderColor;
  private Symbol defaultTextSize;
  private Symbol defaultTextAlignment;
  private static final int defaultTopMargin = 2;
  private static final int defaultLeftMargin = 8;
  private static final int defaultRightMargin = 8;
  private final static Integer defaultCellWidth = new Integer(70);
  private final static Integer defaultCellHeight = new Integer(25);
  private final static Structure cellFormatDefault = new Structure();
  private static final Symbol BACKGROUND_ = Symbol.intern ("BACKGROUND");
  private static final Symbol FOREGROUND_ = Symbol.intern ("FOREGROUND");
  private final static Symbol WHITE_ = Symbol.intern("WHITE");
  private final static Symbol BLACK_ = Symbol.intern("BLACK");
  private final static Symbol SMALL_ = Symbol.intern("SMALL");
  private static final Symbol LEFT_  = Symbol.intern ("LEFT");
  private static final Symbol CENTER_= Symbol.intern ("CENTER");
  private final static Symbol RIGHT_ = Symbol.intern("RIGHT");
  private static final Symbol CURRENT_VALUE_ = Symbol.intern ("CURRENT-VALUE");
  private static int borderWidth = 2;
  private static final Symbol[] neededAttributes = {DEFAULT_CELL_FORMAT_};
  
  public WorkspaceFreeformTableImpl(FreeformTable table, WorkspaceView parent)
       throws G2AccessException
  {
     //WE NEED TO SUBSCRIBE TO THE DEFAULT_CELL_FORMAT_ of the table.
    setCanvas(parent);
    this.helper = new WorkspaceElementHelper(this,this,this,(Item)table,parent);
    ((Item)table).addItemListener((com.gensym.util.ItemListener)this, neededAttributes);
    bounds = helper.getExactBounds((Item)table);
    setBounds(bounds[0]);
    //init(table, parent, table.getTableCells());
  }

  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e) {
    try {
      FreeformTable table = (FreeformTable)e.getItem();
      WorkspaceView parent = (WorkspaceView)getParent();
      Sequence tableCells = table.getTableCells();
      init(table, parent, tableCells);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  private void init(FreeformTable table,
		    WorkspaceView parent,
		    Sequence tableCells)
       throws G2AccessException
  {
    Structure defaultCellFormat = ((NewTable)table).getDefaultCellFormat();
    if (defaultCellFormat == null)
      defaultCellFormat = cellFormatDefault;
    initializeDefaultCellFormat(defaultCellFormat);
    this.tableCells = getTableCells(tableCells,
				    cellWidth,
				    cellHeight,
				    defaultTextColor,
				    defaultBackgroundColor,
				    defaultBorderColor,
				    parent.getColorTable(),
				    defaultTextSize,
				    defaultTextAlignment);
  }

  private void initializeDefaultCellFormat(Structure defaultCellFormat) {       
    cellWidth
      = ((Integer)defaultCellFormat.getAttributeValue(WIDTH_,defaultCellWidth)).intValue();
    cellHeight
      = ((Integer)defaultCellFormat.getAttributeValue(HEIGHT_,defaultCellHeight)).intValue();
    defaultTextColor
      = (Symbol)defaultCellFormat.getAttributeValue(TEXT_COLOR_, FOREGROUND_);
    // expressions are not allowed in the default cell format
    defaultBackgroundColor
      = (Symbol)defaultCellFormat.getAttributeValue(BACKGROUND_COLOR_,BACKGROUND_);
    defaultBorderColor
      = (Symbol)defaultCellFormat.getAttributeValue(BORDER_COLOR_,FOREGROUND_);
    defaultTextSize
      = (Symbol)defaultCellFormat.getAttributeValue(TEXT_SIZE_,SMALL_);
    defaultTextAlignment
      = (Symbol)defaultCellFormat.getAttributeValue(TEXT_ALIGNMENT_,RIGHT_);
  }

  private static TextCell[][] getTableCells(Sequence tableRowsSequence,
					    int cellWidth,
					    int cellHeight,
					    Symbol defaultTextColor,
					    Symbol defaultBackgroundColor,
					    Symbol defaultBorderColor,
					    ColorTable colorTable,
					    Symbol defaultTextSize,
					    Symbol defaultTextAlignment) {
    int tableRowCount = tableRowsSequence.size();
    int tableColumnCount = ((Sequence)tableRowsSequence.elementAt(0)).size();//throw error if inconsistent?
    TextCell[][] tableCells = new TextCell[tableRowCount][tableColumnCount];

    Sequence currentRow;
    Object currentCellData;
    for (int i = 0; i < tableRowCount; i++) {
      currentRow = (Sequence)tableRowsSequence.elementAt(i);
      for (int j = 0; j < tableColumnCount; j++) {
	currentCellData = currentRow.elementAt(j);
	if (currentCellData instanceof Structure) 
	  tableCells[i][j] = createTextCell((Structure)currentCellData,
					    cellWidth,
					    cellHeight,
					    defaultTextColor,
					    defaultBackgroundColor,
					    defaultBorderColor,
					    colorTable,
					    defaultTextSize,
					    defaultTextAlignment);
      }
    }
    return tableCells;
  }

  private static TextCell createTextCell(Structure textCellData,
					 int cellWidth,
					 int cellHeight,
					 Symbol defaultTextColor,
					 Symbol defaultBackgroundColor,
					 Symbol defaultBorderColor,
					 ColorTable colorTable,
					 Symbol defaultTextSize,
					 Symbol defaultTextAlignment) {
    Symbol backgroundColor, textColor, borderColor, G2FontName, justification_;
    Structure cellFormat
      = (Structure) textCellData.getAttributeValue(CELL_FORMAT_, cellFormatDefault);
    backgroundColor = getCellBackgroundColor(cellFormat, BACKGROUND_COLOR_, defaultBackgroundColor);
    
    textColor = (Symbol) cellFormat.getAttributeValue(TEXT_COLOR_,defaultTextColor);
    borderColor = (Symbol) cellFormat.getAttributeValue(BORDER_COLOR_,defaultBorderColor);
    G2FontName = (Symbol) cellFormat.getAttributeValue(TEXT_SIZE_,defaultTextSize);
    justification_ = (Symbol) cellFormat.getAttributeValue(TEXT_ALIGNMENT_,defaultTextAlignment);
    int justfnCode;
    if (justification_.equals (LEFT_))
      justfnCode = TextCell.LEFT;
    else if (justification_.equals (CENTER_))
      justfnCode = TextCell.CENTER;
    else
      justfnCode = TextCell.RIGHT;
    Font theFont = G2FontMap.get(G2FontName);
    TextStyle style = new TextStyle(theFont,0,0,0,true);//spacing, indents???
    String text = (String) textCellData.getAttributeValue(CELL_DISPLAY_TEXT_, "");
    TextCell newTextCell =  new TextCell (cellWidth, 
					  text,
					  style,
					  colorTable.lookup (backgroundColor!=null?
							     backgroundColor:
							     defaultBackgroundColor),
					  colorTable.lookup (textColor),
					  borderWidth,
					  colorTable.lookup (borderColor));
    if (backgroundColor != null)
      newTextCell.setDrawBackground(true);
    newTextCell.setHeight(cellHeight);
    newTextCell.setTextJustification (justfnCode);
    newTextCell.setBorderWidth(borderWidth);
    newTextCell.setRightMargin(defaultRightMargin);   
    newTextCell.setLeftMargin(defaultLeftMargin);
    newTextCell.setTopMargin(defaultTopMargin);
    return newTextCell;
  }

  private Color getTextColor()
  {
    return canvas.getColorTable().lookup(defaultTextColor);
  }
  
  private Color getBorderColor() {
    return canvas.getColorTable().lookup(defaultBorderColor);
  }

  private Color getBackgroundColor() {
    return canvas.getColorTable().lookup(defaultBackgroundColor);
  }

  private void formatCell(TextCell cell, Graphics g) {
    if (g != null) {//what should I do if it's null????
      cell.format(g);
    }
    cell.setHeight(cellHeight);
  }
  
  private void formatCells(Graphics g) {
    int rowCount = tableCells.length;
    int columnCount = tableCells[0].length;
    for (int i = 0; i<rowCount; i++) {
      for (int j = 0;j<columnCount; j++) {
	if (tableCells[i][j] != null)
	  formatCell(tableCells[i][j], g);	
      }
    }
  }

  /**
   * Paints the Freeform Table
   */
  @Override
  public void paint(Graphics g)
  {
    if (notFormatted) {
      formatCells(g);
      //setMargins();
      notFormatted = false;
    }

    int currentLeft,currentTop;
    Rectangle bounds = getExactBounds()[0];
    int left = borderWidth, top = borderWidth;
    int width = bounds.width, height = bounds.height;
    int right = left + width;
    int bottom = top + height;

    g.setColor(getBackgroundColor());
    g.fillRect(0, 0, width, height);

    Color borderColor = getBorderColor();
    int rowCount = tableCells.length;
    int columnCount = tableCells[0].length;
    TextCell currentCell;
    for (int i = 0; i < rowCount; i++) {
      currentTop = top + i*(borderWidth+cellHeight);
      for (int j = 0; j < columnCount; j++) {
	currentLeft = left + j*(borderWidth+cellWidth);
	currentCell = tableCells[i][j];
	if (currentCell != null)
	  currentCell.draw(g, currentLeft, currentTop);
      }
      g.setColor(borderColor);
      g.fillRect(left, cellHeight + currentTop,
		 width - 2*borderWidth, borderWidth);
    }
    for (int j = 0; j < columnCount; j++) {
      currentLeft = left + j*(borderWidth+cellWidth);
      g.setColor(borderColor);
      g.fillRect(currentLeft + cellWidth,borderWidth,
		 borderWidth,height-2*borderWidth);
    }
    g.setColor(borderColor);
    drawRect(g, 0, 0, width, height,borderWidth);
    if (isCut ()) {
      helper.paintCutStatus (g, 0, 0, width, height);
    }
  }

  private void drawRect(Graphics g,
			int left,int top,int width,int height,
			int borderWidth) {
    int right = left + width;
    int bottom = top + height;
    g.fillRect(left, top, width, borderWidth);
    g.fillRect(left, top, borderWidth, height);
    g.fillRect(left,bottom-borderWidth, width, borderWidth);
    g.fillRect(right-borderWidth,top, borderWidth, height);
  }


  /*Interface API*/
  
  @Override
  public Rectangle[] getExactBounds() {
    return bounds;
  }

  public int[] getCellCoordinates(int mouseX, int mouseY)
  {
    Rectangle viewBounds = canvas.getViewBounds();
    int x = mouseX+viewBounds.x;
    int y = mouseY+viewBounds.y;
    int columnIndex = (x-bounds[0].x-borderWidth)/(cellWidth+borderWidth);
    int rowIndex = (y-bounds[0].y-borderWidth)/(cellHeight+borderWidth);
    return new int[] {rowIndex, columnIndex};
  }
  
  @Override
  public void shift (int shift_x, int shift_y)
  {
    helper.shift(shift_x, shift_y);
    bounds[0].translate(shift_x, shift_y);
    Point location = getLocation();
    setLocation(location.x + shift_x, location.y + shift_y);
  }

  @Override
  public void setSize(int width, int height) {
    bounds[0].width = width;
    bounds[0].height = height;
    super.setSize(width,height);
    //notFormatted = true;
  }
  
  @Override
  public boolean inside(int logical_x, int logical_y)
  {
    return contains(logical_x, logical_y);
  }

  @Override
  public boolean contains(int x, int y)
  {
   return helper.contains(x,y);
  }

  
  /*WORKSPACE ATTRIBUTE TABLE API*/

  /**
   * Invoked when a cell of the FreeFormTable has changed.
   * @param event A WorkspaceEvent with ID of ITEM_CHANGE.<p>
   * The event's info will contain a structure whose attribute named by
   * WorkspaceElement.ATTRIBUTE_NAME_ will be TABLE_CELLS_.
   * The attribute named by CELL_ATTRIBUTE_NAME_ will specify the specific attribute
   * of the cell which has changed. (In G251r1 this can have either the value
   * CELL_DISPLAY_TEXT_ or BACKGROUND_COLOR_, the later corresponding to the
   * CURRENT_VALUE_ of the BACKGROUND_COLOR_ of the CELL_FORMAT_.  In earlier versions
   * of G2 this attribute only had the value CELL_DISPLAY_TEXT_).
   * The row and column index of the cell that has
   * changed are contained within the attributes ROW_INDEX and COLUMN_INDEX,
   * and the new value for the cell is contained in the attribute named by
   * WorkspaceElement.NEW_VALUE. Updates the table accordingly.
   */
  @Override
  public void handleTableCellChanged(WorkspaceEvent event) {
    Structure updateInfo = event.getInfo();
    int rowIndex
      = ((Integer)updateInfo.getAttributeValue(ROW_INDEX_, null)).intValue();
    int columnIndex
      = ((Integer)updateInfo.getAttributeValue(COLUMN_INDEX_, null)).intValue();
    TextCell cell = tableCells[rowIndex][columnIndex];
    Symbol cellAttributeName =
      (Symbol)updateInfo.getAttributeValue(CELL_ATTRIBUTE_NAME_, null);
    if (cell != null) {
      if (CELL_DISPLAY_TEXT_.equals(cellAttributeName)) {
	String newText
	  = (String)updateInfo.getAttributeValue(NEW_VALUE_, "*error*");
	cell.setText(newText);
	formatCell(cell, getGraphics());//notFormatted = true;
      } else if (BACKGROUND_COLOR_.equals(cellAttributeName)) {
	Symbol bgColor
	  = getCellBackgroundColor(updateInfo, NEW_VALUE_, defaultBackgroundColor);
	if (bgColor == null) bgColor = defaultBackgroundColor;//can actually have the
	// value null
	cell.setBackgroundColor(canvas.getColorTable().lookup(bgColor));
      }
    } else {
      throw new NullPointerException("ERROR: RECIEVING UPDATE FOR CELL (" +
				     rowIndex + "," + columnIndex +
				     ") which doesn't exist!!!");
    }
			 
    int left = bounds[0].x + borderWidth + columnIndex*(cellWidth+borderWidth);
    int top = bounds[0].y + borderWidth + rowIndex*(cellHeight+borderWidth);
    Rectangle cellBounds = new Rectangle(left,top,cellWidth,cellHeight);
    Rectangle[] invalRegion = {cellBounds};

    ((WorkspaceView)getParent()).invalidate(invalRegion);
  }

  /**
   * Invoked when the table requires reformatting using fresh data.
   * @param event A WorkspaceEvent with ID of ITEM_CHANGE.<p>
   * The event's info will contain a structure whose attribute named by
   * WorkspaceElement.ATTRIBUTE_NAME_ will be TABLE_CELLS_.
   * The attribute named by WorkspaceElement.NEW_VALUE will contain all
   * the data needed to reconstruct the table from scratch.
   * Updates the table accordingly.
   */
  @Override
  public void handleTableCellsChanged(WorkspaceEvent event) {
    Structure updateInfo = event.getInfo();
    this.tableCells
      = getTableCells((Sequence)updateInfo.getAttributeValue(NEW_VALUE_, "*error*"),
		      cellWidth, cellHeight,
		      defaultTextColor,
		      defaultBackgroundColor,
		      defaultBorderColor,
		      canvas.getColorTable(),
		      defaultTextSize,
		      defaultTextAlignment);
    Rectangle bounds = getExactBounds()[0];
    //notFormatted = true; 
    Rectangle[] invalRegion = {bounds};
    notFormatted = true;
    ((WorkspaceView)getParent()).invalidate(invalRegion);
  }
  
  /*WORKSPACE ELEMENT API*/

  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    Sequence tableRowsSequence = null;
    try {
      tableRowsSequence = ((FreeformTable)getItem()).getTableCells();	
    } catch (G2AccessException g2ae) {
      System.out.println(g2ae);
      return;
    }
    int rowCount = tableCells.length, columnCount = tableCells[0].length;
    for (int i = 0; i < rowCount; i++) {
      TextCell[] currentRow = tableCells[i];
      TextCell currentCell;
      Structure currentCellData, currentCellFormat;
      Color textColor = getTextColor();
      Color backgroundColor = getBackgroundColor();
      for (int j = 0; j < columnCount; j++) {	  
	currentCell = currentRow[j];
	if (currentCell != null) {
	  currentCellData = (Structure)((Sequence)tableRowsSequence.elementAt(i)).elementAt(j);
	  currentCellFormat
	    = (Structure) currentCellData.getAttributeValue(CELL_FORMAT_, cellFormatDefault);
	  Symbol textColorSymbol
	    = (Symbol) currentCellFormat.getAttributeValue(TEXT_COLOR_,defaultTextColor);  
	  Symbol cellBackgroundSymbol
	    = getCellBackgroundColor(currentCellFormat, BACKGROUND_COLOR_, null);
	  if (textColorSymbol != null)
	    textColor = canvas.getColorTable().lookup(textColorSymbol);
	  if (cellBackgroundSymbol != null)
	    backgroundColor = canvas.getColorTable().lookup(cellBackgroundSymbol);
	  currentCell.setTextColor(textColor);
	  currentCell.setBackgroundColor(backgroundColor);
	}
      }
    }
    canvas.invalidateElement(this);
  }

  static private Symbol getCellBackgroundColor(Structure cellFormat, Symbol slotName, Symbol defaultBackgroundColor) {
    Symbol backgroundColor = null;
    Object bgColorOrExpression = cellFormat.getAttributeValue(slotName, defaultBackgroundColor);
    if (bgColorOrExpression instanceof Symbol)
      backgroundColor = (Symbol) bgColorOrExpression;
    else if (bgColorOrExpression instanceof Structure)
      backgroundColor =
	(Symbol)((Structure)bgColorOrExpression).getAttributeValue
	(CURRENT_VALUE_, defaultBackgroundColor);

    return backgroundColor;
  }


  @Override
  public void handleWorkspaceItemMoved(WorkspaceEvent event) {
    helper.shift(event);   
  }

  /**
   * Resizes the DrawElement to the given Rectangle.
   */
  @Override
  public void handleWorkspaceItemResized(WorkspaceEvent event) {
    helper.resize(event);
  }

  @Override
  public void itemModified (ItemEvent e) {
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
    if (DEFAULT_CELL_FORMAT_.equals(attributeName)) {
      try {
	initializeDefaultCellFormat((Structure) e.getNewValue());
	this.tableCells
	  = getTableCells(((FreeformTable)getItem()).getTableCells(),//cache this info??
			  cellWidth, cellHeight,
			  defaultTextColor,
			  defaultBackgroundColor,
			  defaultBorderColor,
			  canvas.getColorTable(),
			  defaultTextSize,
			  defaultTextAlignment);
      } catch (G2AccessException g2ae) {
      }
      helper.itemModified(e);
      Rectangle bounds = getExactBounds()[0];
      Rectangle[] invalRegion = {bounds};
      notFormatted = true;
      ((WorkspaceView)getParent()).invalidate(invalRegion);
    }
  }

  @Override
  public void itemDeleted (ItemEvent e) {
    helper.itemDeleted(e);
  }

  @Override
  public Item getItem() {
    return helper.getItem();
  }

  @Override
  public void select () {
    helper.select();
  }

  @Override
  public void unselect () {
    helper.unselect();
  }

  @Override
  public boolean isSelected () {
    return helper.isSelected();
  }

  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    return helper.getDraggingGhost(left,top,width,height);
  }

  @Override
  public DraggingGhost getDraggingGhost () {
    return helper.getDraggingGhost();
  }
  
  @Override
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    return helper.getDraggingGhost(markerLocn, currentX, currentY);
  }

  @Override
  public PopupMenu getContextMenu () {
    return helper.getContextMenu();
  }

  @Override
  public String toString()
  {
    String theString = "default";
    try {
      theString = "#<" + helper.getG2ClassName().toString() +
      " @" + Integer.toHexString(super.hashCode()) + ">";
    } catch (G2AccessException e) {}

    return theString;
  }

  @Override
  public boolean isCut () {
    return helper.isCut ();
  }

  @Override
  public void setCut (boolean newCutState) {
    helper.setCut (newCutState);
    repaint ();
  }

  @Override
  public void dispose() throws G2AccessException{
    getItem().removeItemListener(this, neededAttributes);
  }

}
