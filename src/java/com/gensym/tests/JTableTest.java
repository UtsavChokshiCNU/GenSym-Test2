
package com.gensym.tests;

import java.util.Enumeration;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.plaf.*;
import javax.swing.table.*;

import com.gensym.swing.RowHeader;
import com.gensym.swing.table.TableModel2;

public class JTableTest implements Runnable {

  public static void main (String[] args) throws Exception {
    final int numColumns = Integer.parseInt (args[2]);
    final int initRows = Integer.parseInt (args[1]);
    UIManager.setLookAndFeel (UIManager.getSystemLookAndFeelClassName ());
    //UIManager.setLookAndFeel ("com.sun.java.swing.plaf.motif.MotifLookAndFeel");
    JFrame f = new JFrame ("Table Test");
    AbstractTableModel2 tbModel;
    JTable tb = new JTable (tbModel = new AbstractTableModel2 (initRows, numColumns));
    tb.addMouseListener (new TableDisplayMenuPoster ());
    tb.setAutoResizeMode (JTable.AUTO_RESIZE_OFF);
    //tb.setTableHeader (new JTableHeader ());
    JScrollPane scrollPane = new JScrollPane (tb);
    scrollPane.setRowHeaderView (new RowHeader (tb));
    if (args[0].equals ("scroll")) {
      f.getContentPane().add (scrollPane);
      System.out.println ("Scroll Pane pref size = " + scrollPane.getUI().getPreferredSize(scrollPane));
    } else {
      f.getContentPane().add (tb, BorderLayout.CENTER);
      f.getContentPane().add (tb.getTableHeader(), BorderLayout.NORTH);
    }
    System.out.println ("Total width = " + tb.getColumnModel().getTotalColumnWidth());
    System.out.println ("Resize Mode = " + tb.getAutoResizeMode());
    f.pack ();
    f.setVisible (true);
    f.addWindowListener (new WindowAdapter () {
      @Override
      public void windowClosing (WindowEvent wEvt) {
	System.exit (0);
      }
    });
    new Thread (new JTableTest (tbModel)).start();
  }

  private AbstractTableModel2 model;

  JTableTest (AbstractTableModel2 model) {
    this.model = model;
  }

  @Override
  public void run () {
    try {
      while (true) {
	model.addRow();
	Thread.currentThread().sleep (2000);
      }
    } catch (InterruptedException ie) {
      // do nothing
    }
  }

}


class TableDisplayMenuPoster extends MouseAdapter {
  
  JPopupMenu contextMenu;

  TableDisplayMenuPoster () {
  }

  @Override
  public void mousePressed (MouseEvent mEvt) {
    System.out.println ("Press = " + mEvt.isPopupTrigger ());
    if (mEvt.isPopupTrigger ())
      postContextMenu (mEvt);
  }

  @Override
  public void mouseReleased (MouseEvent mEvt) {
    System.out.println ("Release = " + mEvt.isPopupTrigger ());
    if (mEvt.isPopupTrigger ())
      postContextMenu (mEvt);
  }

  @Override
  public void mouseClicked (MouseEvent mEvt) {
    System.out.println ("Click = " + mEvt.isPopupTrigger ());
  }

  private void postContextMenu (MouseEvent mEvt) {
    JTable table = (JTable) mEvt.getSource ();
    int x = mEvt.getX();
    int y = mEvt.getY();
    Point p = new Point (x, y);
    int row = table.rowAtPoint (p);
    int column = table.columnAtPoint (p);
    contextMenu = new JPopupMenu ("Table Cell");
    contextMenu.add (new JMenuItem ("Expression (" + row + "," + column + ")"));
    contextMenu.setInvoker (table);
    contextMenu.show (table, x, y);
  }
}


class AbstractTableModel2 extends AbstractTableModel implements TableModel2  {
  AbstractTableModel2 (int numRows, int numColumns) {
    this.numRows = numRows;
    this.numColumns = numColumns;
  }
  private int numRows, numColumns;
  @Override
  public int getColumnCount () {return numColumns;}
  @Override
  public int getRowCount () {return numRows;}
  @Override
  public Object getValueAt (int rowIndex, int columnIndex)
  {return "value  (" + rowIndex + ", " + columnIndex + ")";}
  @Override
  public String getRowName (int rowIndex) {
    return "R #" + rowIndex;}
  public void addRow () {
    numRows++;
    fireTableDataChanged ();}
}
