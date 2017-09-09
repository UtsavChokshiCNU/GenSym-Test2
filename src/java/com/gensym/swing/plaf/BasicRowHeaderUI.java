
package com.gensym.swing.plaf;

import javax.swing.*;
import javax.swing.plaf.ComponentUI;
import java.awt.*;
import com.gensym.swing.table.TableModel2;
import com.gensym.swing.RowHeader;

public class BasicRowHeaderUI extends RowHeaderUI {

  private int rowHeight, fontHeight;
  private Image cellImage;
  private boolean trace = false;

  public static ComponentUI createUI(JComponent h) {
    return new BasicRowHeaderUI();
  }

  BasicRowHeaderUI () {
  }

  @Override
  public void installUI (JComponent c) {
    RowHeader rowHeader = (RowHeader)c;
    rowHeight = rowHeader.getTable().getRowHeight();// + rowHeader.getTable().getRowMargin ();
    fontHeight = Toolkit.getDefaultToolkit().getFontMetrics (rowHeader.getTable().getFont()).getHeight();
    if (trace)
      System.out.println ("RowHeight = " + rowHeight + ", fontHeight = " + fontHeight);
  }

  @Override
  public void paint (Graphics g, JComponent c) {
    RowHeader rowHeader = (RowHeader)c;
    if (cellImage == null) {
      int rowWidth = rowHeader.getWidth ();
      if (trace)
	System.out.println ("Dbl Buffer Image = " + rowWidth + "x" + rowHeight);
      cellImage = rowHeader.createImage (rowWidth, rowHeight);
      Graphics bufG = cellImage.getGraphics ();
      bufG.setColor (Color.lightGray);
      bufG.fillRect (0, 0, rowWidth, rowHeight);
      bufG.setColor (Color.white);
      bufG.drawLine (0, 0, rowWidth, 0);
      bufG.drawLine (1, 1, rowWidth - 1, 1);
      bufG.drawLine (0, 0, 0, rowHeight);
      bufG.drawLine (1, 0, 1, rowHeight - 1);
      bufG.setColor (Color.darkGray);
      bufG.drawLine (1, rowHeight - 1, rowWidth, rowHeight -1);
      bufG.drawLine (rowWidth - 1, 1, rowWidth - 1, rowHeight - 1);
      bufG.setColor (Color.gray);
      bufG.drawLine (2, rowHeight - 2, rowWidth - 2, rowHeight - 2);
      bufG.drawLine (rowWidth - 2, 2, rowWidth - 2, rowHeight - 2);
    }
    Rectangle invArea = g.getClip().getBounds();
    //g.setColor (Color.lightGray);
    //g.fillRect (invArea.x, invArea.y, invArea.width, invArea.height);
    g.setColor (Color.black);
    if (trace)
      {
	System.out.println ("Row Header needs to draw : " + invArea);
	System.out.println ("Row Height = " + rowHeight);
      }
    JTable table = rowHeader.getTable();
    if (trace)
      System.out.println ("Table dimensions = " + table.getSize ());
    TableModel2 model = (TableModel2) table.getModel ();
    int numRows = rowHeader.getTable().getRowCount ();
    for (int y=invArea.y/rowHeight*rowHeight; y<invArea.y+invArea.height; y+=rowHeight) {
      int rowNumber = y/rowHeight;
      if (rowNumber >= numRows)
	break;
      g.drawImage (cellImage, 0, y, null);
      g.drawString (model.getRowName (rowNumber), 0 + 5, y + (rowHeight + fontHeight)/2 - 3 /*fudge*/);
    }
  }

  // Need better method to determine this
  @Override
  public Dimension getPreferredSize (JComponent c) {
    return new Dimension (75, 1000);
  }

}


