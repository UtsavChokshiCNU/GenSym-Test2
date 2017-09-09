package com.gensym.wksp;

import java.awt.*;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.TextBoxFormat;
import java.util.*;
import com.gensym.draw.*;
import com.gensym.classes.ReadoutTable;
import com.gensym.classes.Table;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.util.G2FontMap;


/**
 *
 * WorkspaceAttributeTable <p>
 * A WorkspaceElement that appears as an attribute-table
 * Text of the rows and the table borders and dividers
 * will draw by default.
 *
 */
public class WorkspaceTableImpl extends BasicDrawElement
implements WorkspaceTable
{
  private static Symbol leftTextSymbol = Symbol.intern("LEFT-TEXT");
  private static boolean workspaceAttributeTableDebugP = false;
  private String thetext = "DEFAULT TEXT";
  public static final Symbol FOREGROUND_ = Symbol.intern ("FOREGROUND");
  private Symbol tableFormatType;
  private Symbol tableFont;
  private Symbol leftCellFormatName;
  private Symbol rightCellFormatName;
  private TextBoxFormat tableFormat;
  private TextBoxFormat leftTextBoxFormat;
  private TextBoxFormat rightTextBoxFormat;
  private Symbol borderColor = FOREGROUND_;
  private Symbol textLineColor = FOREGROUND_;
  private boolean drawBorder;
  private boolean drawVerticalDivider = true;
  private boolean drawHorizontalDivider;
  private static int dividerWidth = 0, borderWidth;
  private WorkspaceElementHelper helper;
  private Rectangle[] bounds;
  private static int leftMargin, rightMargin;
  TableRow[] tableRows = null;
  boolean notFormatted = true;
  static boolean tableFormatDebugP = false;


  /**
   * Will take responsibility for initializing the table rows and
   * format using the formatType/formatInfo obtained through the Item. 
   * @param table The Table which this element is to represent.
   * @param parent The view into which this element is being added. 
   */
  public WorkspaceTableImpl(Table table, WorkspaceView parent)
       throws G2AccessException 
  {
    drawBorder = true;
    drawHorizontalDivider = false;    
    setupFormats(table);
    Color textColor = parent.getColorTable().lookup(FOREGROUND_);
    tableRows = getTableRows(table,
			     WorkspaceElementHelper.getExactBounds((Item)table),
			     tableFormat,
			     leftTextBoxFormat,
			     rightTextBoxFormat,
			     tableFont,
			     textColor);
    this.helper = new WorkspaceElementHelper(this,
					     this,
					     this,
					     (Item)table,
					     parent);
    bounds = helper.getExactBounds((Item)table);
    setBounds(bounds[0]);
  }
  
  private static int getBorderWidth(TextBoxFormat tableFormat) {
    return tableFormat.getTableBorderWidth().intValue();
  }
  
  static TableRow[] getTableRows(Table table,
				 Rectangle[] bounds,
				 TextBoxFormat tableFormat,
				 TextBoxFormat leftTextBoxFormat,
				 TextBoxFormat rightTextBoxFormat,
				 Symbol tableFont,
				 Color textColor)
       throws G2AccessException
  {
    if (tableFormatDebugP)
      {
	System.out.println("tableFormat details "+tableFormat.dumpInternals());
	System.out.println("leftCellFormat details "+leftTextBoxFormat.dumpInternals());
	System.out.println("rightCellFormat details "+rightTextBoxFormat.dumpInternals());
      }

    Sequence tableRowsSequence = table.getTableRows();
    int borderWidth = getBorderWidth(tableFormat);
    TextStyle leftTextStyle = getTextStyle(table, leftTextBoxFormat, tableFont);
    TextStyle rightTextStyle = getTextStyle(table, rightTextBoxFormat, tableFont);
    int leftCellLeftMargin = leftTextBoxFormat.getLeftMargin().intValue();
    int leftCellRightMargin = leftTextBoxFormat.getRightMargin().intValue();
    int minimumFormatWidth = leftTextBoxFormat.getMinimumFormatWidth();
    if (tableFormatDebugP)
      System.out.println("really should consider formatting left column to "+
			 minimumFormatWidth);
    TableRow[] tableRows;
    int tableRowCount = tableRowsSequence.size();
    tableRows = new TableRow[tableRowCount];
    Enumeration tableRowsDataPass1 = tableRowsSequence.elements();
    Enumeration tableRowsData = tableRowsSequence.elements();
    Structure tableRowData;
    TableRow tableRow;
    int i = 0;
    int maximumLeftTextWidth = 0;
    String currentLeftText;
        
    while (tableRowsDataPass1.hasMoreElements()) {
      tableRowData = (Structure) tableRowsDataPass1.nextElement();
      currentLeftText = (String) tableRowData.getAttributeValue(leftTextSymbol, null);
      if (currentLeftText != null) 
	{
	  int computedLeftWidth
	    = Paragraph.computeFormattedWidth(currentLeftText,
					      (minimumFormatWidth - 
					       (leftCellLeftMargin + 
						leftCellRightMargin)),
					      leftTextStyle);
	  if (tableFormatDebugP)
	    System.out.println("new computed width = "+computedLeftWidth);
	  maximumLeftTextWidth = Math.max(maximumLeftTextWidth,computedLeftWidth);
	}
    }

    int leftWidth = maximumLeftTextWidth + leftCellLeftMargin + leftCellRightMargin;
    int rightWidth = (bounds[0].width -
		      (leftWidth + dividerWidth + borderWidth*2));
    
    while (tableRowsData.hasMoreElements()) {
      tableRowData = (Structure) tableRowsData.nextElement();
      tableRow = new TableRow(tableRowData,
			      leftWidth,
			      rightWidth,
			      leftTextStyle,
			      rightTextStyle,
			      textColor);
      tableRows[i] = tableRow;
      i++;
    }
    return tableRows;
  }

  private static final Symbol
  // table format names
  ATTRIBUTES_TABLE_FORMAT_
  = Symbol.intern ("ATTRIBUTES-TABLE-FORMAT"),
    NEW_ATTRIBUTES_TABLE_FORMAT_
  = Symbol.intern ("NEW-ATTRIBUTES-TABLE-FORMAT"),
    ATTRIBUTE_DISPLAY_TABLE_FORMAT_
  = Symbol.intern ("ATTRIBUTE-DISPLAY-TABLE-FORMAT"),
    READOUT_TABLE_FORMAT_
  = Symbol.intern ("READOUT-TABLE-FORMAT"),

    // text cell format names
    ATTRIBUTE_DISPLAY_VALUE_FORMAT_
  = Symbol.intern ("ATTRIBUTE-DISPLAY-VALUE-FORMAT"),
    LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_
  = Symbol.intern ("LARGE-ATTRIBUTE-DISPLAY-VALUE-FORMAT"),
    EXTRA_LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_
  = Symbol.intern ("EXTRA-LARGE-ATTRIBUTE-DISPLAY-VALUE-FORMAT"),

    ATTRIBUTE_DISPLAY_DESCRIPTION_FORMAT_
  = Symbol.intern ("ATTRIBUTE-DISPLAY-DESCRIPTION-FORMAT"),
    LARGE_ATTRIBUTE_DISPLAY_DESCRIPTION_FORMAT_
  = Symbol.intern ("LARGE-ATTRIBUTE-DISPLAY-DESCRIPTION-FORMAT"),
    EXTRA_LARGE_ATTRIBUTE_DISPLAY_DESCRIPTION_FORMAT_
  = Symbol.intern ("EXTRA-LARGE-ATTRIBUTE-DISPLAY-DESCRIPTION-FORMAT"),

    SMALL_ATTRIBUTE_DESCRIPTION_FORMAT_
  = Symbol.intern ("SMALL-ATTRIBUTE-DESCRIPTION-FORMAT"),
    ATTRIBUTE_DESCRIPTION_FORMAT_//attr-tables
  = Symbol.intern ("ATTRIBUTE-DESCRIPTION-FORMAT"),
    EXTRA_LARGE_ATTRIBUTE_DESCRIPTION_FORMAT_
  = Symbol.intern ("EXTRA-LARGE-ATTRIBUTE-DESCRIPTION-FORMAT"),

    SMALL_ATTRIBUTE_VALUE_FORMAT_
  = Symbol.intern ("SMALL-ATTRIBUTE-VALUE-FORMAT"),
    ATTRIBUTE_VALUE_FORMAT_
  = Symbol.intern ("ATTRIBUTE-VALUE-FORMAT"),
    EXTRA_LARGE_ATTRIBUTE_VALUE_FORMAT_
  = Symbol.intern ("EXTRA-LARGE-ATTRIBUTE-VALUE-FORMAT"),

    READOUT_TABLE_TEXT_CELL_FORMAT_
  = Symbol.intern("READOUT-TABLE-TEXT-CELL-FORMAT"),

  HM14_ = Symbol.intern("HM14"),
  HM18_ = Symbol.intern("HM18"),
  HM24_ = Symbol.intern("HM24");

  private static Symbol getCellFormatType(Symbol repType,
					  Symbol g2Font)
  {
    Symbol formatType = null;
    if (WorkspaceRepresentationTypes.ATTRIBUTE_DISPLAY_.equals(repType)) {
      if (G2FontMap.HM14_.equals(g2Font) ||
	  G2FontMap.SMALL_.equals(g2Font))
	formatType = TextBoxFormat.ATTRIBUTE_DISPLAY_VALUE_FORMAT_;
      else if (G2FontMap.HM18_.equals(g2Font) ||
	       G2FontMap.LARGE_.equals(g2Font))
	formatType = TextBoxFormat.LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_;
      else if (G2FontMap.HM24_.equals(g2Font) ||
	       G2FontMap.EXTRA_LARGE_.equals(g2Font))
      	formatType = TextBoxFormat.EXTRA_LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_;
    } /*else if (WorkspaceRepresentationTypes.ATTRIBUTE_TABLE_.equals(g2Font) ||
	       WorkspaceRepresentationTypes.ATTRIBUTE_TABLE_WITH_HEADER_.equals(g2Font)) {
      if (G2FontMap.HM14_.equals(g2Font) ||
	  G2FontMap.SMALL_.equals(g2Font))
	formatType = TextBoxFormat.SMALL_ATTRIBUTE_DESCRIPTION_FORMAT_;
      else if (G2FontMap.HM18_.equals(g2Font) ||
	       G2FontMap.LARGE_.equals(g2Font))
	formatType = TextBoxFormat.ATTRIBUTE_DESCRIPTION_FORMAT_;
      else if (G2FontMap.HM24_.equals(g2Font) ||
	       G2FontMap.EXTRA_LARGE_.equals(g2Font))
      	formatType = TextBoxFormat.EXTRA_LARGE_ATTRIBUTE_DESCRIPTION_FORMAT_;
    }*/
      
    return formatType;
  }


  private void  setupFormats(Table table) throws G2AccessException
  {
    // establish table format and font
    tableFormatType = table.getFormatType();
    if (table instanceof ReadoutTable)
      tableFont = HM14_;
    else
      tableFont = ((com.gensym.classes.TableItem)table).getTableFontSize();
    TwAccess theContext
      = (TwAccess)((com.gensym.classes.ItemImpl)table).getContext(); //hack
    Structure formatInfo = theContext.getFormatInfo(tableFormatType);
    if (formatInfo != null) 
      tableFormat = new TextBoxFormat(formatInfo);
    else
      tableFormat = new TextBoxFormat(new Structure());
    
    // establish cell formats
    if (tableFormatType.equals(ATTRIBUTES_TABLE_FORMAT_)||
	tableFormatType.equals(NEW_ATTRIBUTES_TABLE_FORMAT_))
      {
	setDividerWidth(1);
	setDrawHorizontalDivider(true);
	if (tableFont.equals(HM14_))
	  {
	    leftCellFormatName = SMALL_ATTRIBUTE_DESCRIPTION_FORMAT_;
	    rightCellFormatName = SMALL_ATTRIBUTE_VALUE_FORMAT_;
	  }
	else if (tableFont.equals(HM18_))
	  {
	    leftCellFormatName = ATTRIBUTE_DESCRIPTION_FORMAT_;
	    rightCellFormatName = ATTRIBUTE_VALUE_FORMAT_;
	  }
	else if (tableFont.equals(HM24_))
	  {
	    leftCellFormatName = EXTRA_LARGE_ATTRIBUTE_DESCRIPTION_FORMAT_;
	    rightCellFormatName = EXTRA_LARGE_ATTRIBUTE_VALUE_FORMAT_;
	  }
	else
	  {
	    leftCellFormatName = ATTRIBUTE_DESCRIPTION_FORMAT_;
	    rightCellFormatName = ATTRIBUTE_VALUE_FORMAT_;
	    Trace.exception(new RuntimeException("unexpected table font "+tableFont));
	  }
      }
    else if (tableFormatType.equals(ATTRIBUTE_DISPLAY_TABLE_FORMAT_))
      {
	if (tableFont.equals(HM14_))
	  {
	    leftCellFormatName = ATTRIBUTE_DISPLAY_DESCRIPTION_FORMAT_;
	    rightCellFormatName = ATTRIBUTE_DISPLAY_VALUE_FORMAT_;
	  }
	else if (tableFont.equals(HM18_))
	  {
	    leftCellFormatName = LARGE_ATTRIBUTE_DISPLAY_DESCRIPTION_FORMAT_;
	    rightCellFormatName = LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_;
	  }
	else if (tableFont.equals(HM24_))
	  {
	    leftCellFormatName = EXTRA_LARGE_ATTRIBUTE_DISPLAY_DESCRIPTION_FORMAT_;
	    rightCellFormatName = EXTRA_LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_;
	  }
	else
	  {
	    leftCellFormatName = ATTRIBUTE_DISPLAY_DESCRIPTION_FORMAT_;
	    rightCellFormatName = ATTRIBUTE_DISPLAY_VALUE_FORMAT_;
	    Trace.exception(new RuntimeException("unexpected table font "+tableFont));
	  }
      }
    else if (tableFormatType.equals(READOUT_TABLE_FORMAT_))
      {
	leftCellFormatName = READOUT_TABLE_TEXT_CELL_FORMAT_;
	rightCellFormatName = READOUT_TABLE_TEXT_CELL_FORMAT_;
      }
    else
      {
	leftCellFormatName = ATTRIBUTE_DESCRIPTION_FORMAT_;
	rightCellFormatName = ATTRIBUTE_VALUE_FORMAT_;
	Trace.exception(new RuntimeException("unexpected table format "+
					     tableFormatType));
      }

    formatInfo = theContext.getFormatInfo(leftCellFormatName);
    if (formatInfo != null) 
      leftTextBoxFormat = new TextBoxFormat(formatInfo);
    else
      leftTextBoxFormat = new TextBoxFormat(new Structure());
    formatInfo = theContext.getFormatInfo(rightCellFormatName);
    if (formatInfo != null) 
      rightTextBoxFormat = new TextBoxFormat(formatInfo);
    else
      rightTextBoxFormat = new TextBoxFormat(new Structure());
  }

  private static TextStyle getTextStyle(Table table,
					TextBoxFormat textBoxFormat,
					Symbol tableFont)
					
       throws G2AccessException
  {    
    int first_line_indent = textBoxFormat.getFirstLineIndent().intValue();
    int textlinespacing = textBoxFormat.getTextLineSpacing().intValue();
    int subsequent_line_indent = textBoxFormat.getSubsequentLineIndent().intValue();

    if (tableFormatDebugP)
      System.out.println("for "+tableFont+" got "+G2FontMap.get(tableFont));
    TextStyle style =  new TextStyle(G2FontMap.get(tableFont),
				     first_line_indent,
				     subsequent_line_indent,
				     textlinespacing,
				     true);
    // The following hax will remain for the short term
    //style.setLineHeight(textBoxFormat.getLineHeight());
    Symbol repType = null;
    try {
      repType = ((Item)table).getRepresentationType();
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    Symbol cellFormat = getCellFormatType(repType,tableFont);
    if (tableFormatDebugP)
      System.out.println("cellFormatType = "+cellFormat);
    style.setLineHeight(textBoxFormat.getLineHeight(cellFormat));
    style.setBaselineOffset(textBoxFormat.getBaselineOffset());
    return style;
  }
  
  private int roundDown(double val) {
   int roundedValue = (int) Math.round(val);
   if (roundedValue>val)
     return roundedValue - 1;
   else
     return roundedValue;
  }

  private int roundUp(double val) {
   int roundedValue = (int) Math.round(val);
   if (roundedValue<val)
     return roundedValue + 1;
   else
     return roundedValue;
  }

  private int getTotalHeightOfRows() {
    int tableRowCount = tableRows.length;
    int totalHeightOfRows=0;
    TableRow tableRow;
    int rowHeight;
    for (int i=0; i<tableRowCount;i++) {
      tableRow = tableRows[i];
      rowHeight=tableRow.getHeight();
      totalHeightOfRows=totalHeightOfRows+rowHeight+dividerWidth;
    }
    return totalHeightOfRows;
  }
  
  boolean checkMarginFormatting() {
    int borderWidth = getBorderWidth(tableFormat);      
    Rectangle[] bounds=getExactBounds();
    int height =  bounds[0].height;
    int totalHeightOfRows = getTotalHeightOfRows();
    if (totalHeightOfRows == (height-(borderWidth*2))) {
      System.out.println("SET MARGIN REFORMAT WORKED\n\n\n");
      return true;
    } else {
      System.out.println("SET MARGIN REFORMAT ERROR " + totalHeightOfRows +
			 "!=" +  (height-borderWidth*2));
      return false;
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

  private Rectangle getRowBounds(TableRow row) {
    int rowCount = tableRows.length;
    Rectangle[] bounds=getExactBounds();
    int left = bounds[0].x;
    int top = bounds[0].y;
    TableRow currentTableRow;
    int rowHeight;
    int borderWidth = getBorderWidth(tableFormat);      
    int currentBottom = top + borderWidth;

    for (int i = 0; i<rowCount; i++) {
      currentTableRow = tableRows[i];
      rowHeight = currentTableRow.getHeight();
      if (currentTableRow == row) 
	return new Rectangle(left + borderWidth, currentBottom,
			     bounds[0].width,rowHeight);
      currentBottom = currentBottom + rowHeight + dividerWidth;
    }
    return null;
  }
  
  /**
   * @param width The width of the border of each cell of this table in pixels.
   */
  public void setCellBorderWidth(int width) {
    int rowCount = tableRows.length;
    for (int i=0;i<rowCount;i++)
      tableRows[i].setCellBorderWidth(width);
  }

  /**
   * @param width The width of the dividers of this table in pixels.
   */
  public void setDividerWidth(int width) {
    this.dividerWidth = width;
  }

  private void setMargins() { //pad the margins to fit the table height
    int tableRowCount = tableRows.length;
    int borderWidth = getBorderWidth(tableFormat);      
    TableRow tableRow;
    int totalHeightOfRows=getTotalHeightOfRows();
    Rectangle[] bounds=getExactBounds();
    int height =  bounds[0].height;
    int leftoverHeight = (height-borderWidth*2) - totalHeightOfRows;
    
    if (workspaceAttributeTableDebugP)
      System.out.println("leftoverHeight = " + leftoverHeight + "\n\n\n");
    double leftoverPerRow = leftoverHeight/tableRowCount;
    if (workspaceAttributeTableDebugP){
      System.out.println("tableRowCount = " + tableRowCount);
      System.out.println("leftoverPerRow = " + leftoverPerRow);
    }
    
    int topMargin, bottomMargin, defaultTopMargin = 5;
    double halfLeftoverPerRow = leftoverPerRow/2;
    if (tableRowCount>1 || halfLeftoverPerRow <= defaultTopMargin) {
      topMargin = roundUp(halfLeftoverPerRow);
      bottomMargin = roundDown(halfLeftoverPerRow);
    } else {
      topMargin = 5;
      bottomMargin = (int)leftoverPerRow - topMargin;
    }

    int totalHandOut = (topMargin + bottomMargin)*tableRowCount;
    int remainder = leftoverHeight - totalHandOut;
    if (workspaceAttributeTableDebugP)
      System.out.println("topMargin = " + topMargin + "bottomMargin = " + bottomMargin + "\n\n");
    int currentMargin;
    int remainderPadding = 1;
    int newMargin;
    for (int l=0; l<tableRowCount;l++) { 
      remainder -= 1;
      if (remainder<0)
	remainderPadding = 0;
      tableRow = tableRows[l];
      currentMargin = tableRow.getTopMargin();
      newMargin = topMargin+currentMargin;
      if (l==0)//problems with readout tables getting clipped(would rather clip at the bottom)
	newMargin = Math.max(newMargin, 0);
      if (workspaceAttributeTableDebugP)
	System.out.println("setting topmargin in each tablerow to " + newMargin);
      tableRow.setTopMargin(newMargin);
      
      currentMargin = tableRow.getBottomMargin();
      newMargin = bottomMargin+currentMargin+remainderPadding;
      if (l==0)//problems with readout tables getting clipped(would rather clip at the bottom)
	newMargin = Math.max(newMargin, 0);      
      tableRow.setBottomMargin(newMargin);
    }	
  }
  /**
   * Pretty prints the table.
   */
  public void pprint() {
    int count = tableRows.length;
    System.out.println("\n ________________________________");
    System.out.println("[             TABLE              ]");
    System.out.println(" ________________________________");
    for (int i = 0; i<count; i++) {
      TableRow tableRow = tableRows[i];
      System.out.println(tableRow);
    }
    System.out.println("  ________________________________\n");

  }

  /**
   * @param borderColor a Symbol naming a G2 color to be used to
   * draw the outer border of this table.
   */
  public void setBorderColor(Symbol borderColor) {
    this.borderColor = borderColor;
  }

  /**
   * @return the Color currently being used to draw the
   * outer border of this table.
   */
  public Color getBorderColor() {
    return canvas.getColorTable().lookup(borderColor);
  }

  /**
   * @return the Color currently being used to draw the
   * text of this table.
   */
  public Color getTextLineColor() {
    return canvas.getColorTable().lookup(textLineColor);
  }

  /**
   * @param drawBorder a boolean representing whether or not
   * to draw the outer border of this table.
   */
  public void setDrawBorder(boolean drawBorder) {
    this.drawBorder = drawBorder;
  }

  /**
   * @param drawDivider a boolean representing whether or not
   * to draw the inner, vertical divider of this table.
   */
  public void setDrawVerticalDivider(boolean drawDivider){
    this.drawVerticalDivider = drawDivider;
  }

  /**
   * @return a boolean representing whether or not the
   * table's horizontal, row dividers will be drawn.
   */
  public boolean getDrawHorizontalDivider() {
    return drawHorizontalDivider;
  }

  /**
   * @param drawDivider a boolean representing whether or not to
   * draw the table's horizontal, row dividers.
   */
  public void setDrawHorizontalDivider(boolean drawDivider){
    this.drawHorizontalDivider = drawDivider;
  }

  void format(Graphics g) {
    int rowCount = tableRows.length;
    TableRow currentTableRow;
    for (int i = 0; i<rowCount; i++) {
      currentTableRow = tableRows[i];
      currentTableRow.format(g);
    }
  }

  /**
   * Paints an attribute table without a header row.
   */
  @Override
  public void paint(Graphics g)
  {
    if (notFormatted) {
      format(g);
      setMargins();
      notFormatted = false;
    }
      
    int rowCount = tableRows.length;
    int left = 0;
    int top = 0;
    Rectangle[] bounds=getExactBounds();
    int width = bounds[0].width;
    int height = bounds[0].height;
    int right = left + width;
    int bottom = top + height;

    TableRow currentTableRow;
    int rowHeight;
    int borderWidth = getBorderWidth(tableFormat);      
    int currentBottom = top + borderWidth;
    for (int i = 0; i<rowCount; i++) {
      currentTableRow = tableRows[i];
      rowHeight = currentTableRow.getHeight();      
      currentTableRow.Draw(g,
			   left+borderWidth,
			   currentBottom,
			   drawVerticalDivider,
			   getBorderColor());
      if (drawHorizontalDivider) {
	g.setColor(getBorderColor());
	g.drawLine(left + borderWidth, currentBottom-dividerWidth,
		   right - borderWidth, currentBottom-dividerWidth);
      }
      currentBottom = currentBottom + rowHeight + dividerWidth;
    }
    if (drawBorder) {
      g.setColor(getBorderColor());
      drawRect(g, left, top, width, height,borderWidth);
    }
    if (isCut ()) {
      Rectangle[] exbnds = getExactBounds ();
      Rectangle bnds = exbnds[0];
      helper.paintCutStatus (g, bnds.x, bnds.y, bnds.width, bnds.height);
    }
  }

  int getRowIndex(int mouseY) {
    int rowCount = tableRows.length;
    Rectangle[] bounds=getExactBounds();
    int borderWidth = getBorderWidth(tableFormat);
    WorkspaceView view = (WorkspaceView)getParent();
    Rectangle vBounds = view.getViewBounds();
    int top = 0;
    mouseY -= bounds[0].y;
    mouseY += vBounds.y;
    int currentBottom = top+borderWidth;
    TableRow currentTableRow;
    for (int i = 0; i<rowCount; i++) {
      currentTableRow = tableRows[i];
      int rowHeight = currentTableRow.getHeight();            
      currentBottom +=(rowHeight + dividerWidth);
      if (mouseY < currentBottom) 
	return i;
    }
    return -1;    
  }
  
  /**
   * @return the table row index and the cell index
   * that contains the point (x,y)
   * @see getTableRow
   */
  public int[] getTableRowIndex(int x, int y) {
    int rowCount = tableRows.length;
    Rectangle[] bounds=getExactBounds();
    int left = bounds[0].x + x;//bug?
    int top = bounds[0].y + y;//bug?
    int cellIndex = -1;
    TableRow currentTableRow;
    int[] indices = new int[2];
    for (int i = 0; i<rowCount; i++) {
      currentTableRow = tableRows[i];
      cellIndex = currentTableRow.inside(x,y);
      if (cellIndex != -1) {
	indices[0] = i;
	indices[1] = cellIndex;
	return indices;
      }
    }
    return null;
  }

  /**
   * @returns the TableRow at the given index
   * @see getTableRowIndex
   */
  public TableRow getTableRow(int index) {
    if (//(index>0) &&
	(index<tableRows.length))
      return tableRows[index];
    else
      return null;
  }

  /**
   * @return the TextCell that contains the point (x,y)
   * @see getTableRowIndex
   */
  public TextCell getCell(int x, int y) {
    int rowCount = tableRows.length;
    Rectangle[] bounds=getExactBounds();
    int left = bounds[0].x + x;//bug?
    int top = bounds[0].y + y;//bug?
    int cellIndex = -1;
    TableRow currentTableRow;
    for (int i = 0; i<rowCount; i++) {
      currentTableRow = tableRows[i];
      cellIndex = currentTableRow.inside(x,y);
      if (cellIndex != -1)
	return currentTableRow.getCell(cellIndex);
    }
    return null;
  }
  
  @Override
  public Rectangle[] getExactBounds() {
    return bounds;
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
    redoTable();
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
   * Invoked when the cell of a the table has changed.
   * @param event A WorkspaceEvent with ID of ITEM_CHANGE.<p>
   * The event's info will contain a structure whose attribute named by
   * WorkspaceElement.ATTRIBUTE_NAME_ will be TABLE_ROWS.
   * The attribute named by CELL_ATTRIBUTE_NAME will specify which
   * attribute of the cell has changed. (In G250r1 this will always
   * have the value CELL_DISPLAY_TEXT).
   * The row and column index of the cell that has changed are contained
   * within the attributes ROW_INDEX and COLUMN_INDEX, and the new value
   * for the cell is contained in the attribute named by
   * WorkspaceElement.NEW_VALUE. Updates the cell accordingly.
   */
  @Override
  public void handleTableCellChanged(WorkspaceEvent event) {
    Structure updateInfo = event.getInfo();
    int rowIndex
      = ((Integer)updateInfo.getAttributeValue(ROW_INDEX_, null)).intValue();
    int columnIndex
      = ((Integer)updateInfo.getAttributeValue(COLUMN_INDEX_, null)).intValue();
    String newText
      = (String)updateInfo.getAttributeValue(NEW_VALUE_, null);
    TableRow row = getTableRow(rowIndex);
    TextCell cell = row == null ? null : row.getCell(columnIndex);
    if (newText == null || cell == null) {
      // can't update in place if text or cell missing
      redoTable();
      return;
    }

    Rectangle rowBoundsBefore = getRowBounds(row);
    if (columnIndex == 0) 
      {
	//we really need to reformat the whole table since the width of the table
	//could have changed or the vertical divider may have shifted!!!!!
	if (tableFormatDebugP)
	  System.out.println("LHS update case "+newText);
	Font theFont = G2FontMap.get(tableFont);
	Table table = (Table)getItem();
	TextStyle leftTextStyle;
	try {
	  leftTextStyle = getTextStyle(table, leftTextBoxFormat, tableFont);
	} catch (G2AccessException g2ae)
	  {
	    throw new RuntimeException("connection failure in table cell update");
	  }
	int leftCellLeftMargin = leftTextBoxFormat.getLeftMargin().intValue();
	int leftCellRightMargin = leftTextBoxFormat.getRightMargin().intValue();
	int minimumFormatWidth = leftTextBoxFormat.getMinimumFormatWidth();
	int textStringWidth 
	  = Paragraph.computeFormattedWidth(newText,
					    (minimumFormatWidth - 
					     (leftCellLeftMargin + 
					      leftCellRightMargin)),
					    leftTextStyle);
	int currentWidth = cell.getWidth();
	cell.setWidth(Math.max(currentWidth,leftMargin + rightMargin +
			       textStringWidth));
      } 
    else 
      {
	if (tableFormatDebugP)
	  System.out.println("RHS update case "+newText);
	int borderWidth = getBorderWidth(tableFormat);
	int leftMargin = tableFormat.getLeftMargin().intValue();
	int rightMargin = tableFormat.getRightMargin().intValue();
	TextCell leftCell = row.getCell(0);
	int leftWidth = 0;
	if (leftCell != null)
	  leftWidth = leftCell.getWidth();
	cell.setWidth(getBounds().width -
		      (dividerWidth + borderWidth*2 + leftWidth));
      }

    cell.setText(newText);
    notFormatted = true; // just do the cell???
    row.invalidateRowFormatting();
    Rectangle rowBoundsAfter = getRowBounds(row);
    Rectangle[] invalRegion = {rowBoundsBefore, rowBoundsAfter };
    ((WorkspaceView)getParent()).invalidate(invalRegion);
  }

  @Override
  public void handleTableCellsChanged(WorkspaceEvent event)
  {
    //Sequence rows = event.getInfo();
    redoTable();
  }

  protected void setFormatting() 
  {}

  private void redoTable() {
    try {
      tableRows = getTableRows((Table)getItem(),
			       WorkspaceElementHelper.getExactBounds(getItem()),
			       tableFormat,
			       leftTextBoxFormat,
			       rightTextBoxFormat,
			       tableFont,
			       getTextLineColor());
      notFormatted = true;
      setFormatting();
      canvas.invalidateElement(this);
      return;
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }
  
  /*WORKSPACE ELEMENT API*/

  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    int rowCount = tableRows.length;
    TableRow currentTableRow;
    for (int i = 0; i<rowCount; i++) {
      currentTableRow = tableRows[i];
      currentTableRow.setTextColor(getTextLineColor());
    }
    canvas.invalidateElement(this);
    /*  Structure updateInfo = event.getInfo();
	Structure colorPatternChanges
	= (Structure) updateInfo.getAttributeValue(_color_pattern_changes, null);
	*/
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
  public void receivedInitialValues (ItemEvent e) {
    helper.receivedInitialValues(e);
  }

  @Override
  public void itemModified (ItemEvent e) {
    helper.itemModified(e);
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
    getItem().removeItemListener(this);
  }

}
