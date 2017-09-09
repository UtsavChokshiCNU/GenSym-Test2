package com.gensym.wksp;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.TableColumnModelListener;
import javax.swing.event.TableColumnModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.event.TableModelEvent;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;
import javax.swing.table.DefaultTableModel;
import com.gensym.classes.FreeformTable;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.WarningDialog;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.message.Trace;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.widgets.Spin;
import com.gensym.widgets.SpinEvent;
import com.gensym.widgets.SpinListener;

public class CellDialog extends StandardDialog implements SpinListener,
ActionListener, ListSelectionListener, TableColumnModelListener {

  private JButton addRowButton, delRowButton, addColButton, delColButton;
  private Spin rowArea, colArea;
  private JTabbedPane tabPane;
  private JPanel component;
  private FreeformTable fft;
  private JTable grid;
  private DefaultTableModel gridModel;
  private ListSelectionModel rowModel;
  private TableColumnModel colModel;
  private Sequence tableCells;
  private DialogCloser closer;
  private int selectedIndex;
  private static Symbol FFT_ = Symbol.intern("FFT"),
    ROW_ = Symbol.intern("ROW"),
    COL_ = Symbol.intern("COL"),
    DIALOG_CONTENTS_ = Symbol.intern("DIALOG-CONTENTS"),
    NONE_ = Symbol.intern("NONE"),
    CELL_FORMAT_ = Symbol.intern("CELL-FORMAT"),
    EXPRESSION_ = Symbol.intern("EXPRESSION"),
    CELL_EVALUATION_ATTRIBUTES_ = Symbol.intern("CELL-EVALUATION-ATTRIBUTES"),
    DEFAULT_CELL_FORMAT_ = Symbol.intern("DEFAULT-CELL-FORMAT"),
    DEFAULT_EVALUATION_SETTING_ = Symbol.intern("DEFAULT-EVALUATION-SETTING");

  public CellDialog (FreeformTable fft, G2Access cxn) {
    super(null, "Edit freeform table cell", false,
	  new String[] {OK_LABEL, CANCEL_LABEL, APPLY_LABEL},
	  new int[]{OK, CANCEL, APPLY},
	  new JPanel(new BorderLayout()),
	  new CellDialogClient());
    component = (JPanel)getDialogComponent();
    this.fft = fft;
    populateDialog();
    pack();
    setSize(new Dimension(635, 370));
    setDefaultButton(OK);
    closer = new DialogCloser(cxn);
  }

  private Spin makeSpin(int maxVal) {
    JTextField  textField = new JTextField ();
    textField.setColumns(3);
    textField.addActionListener(this);
    textField.setText("0");
    textField.setMinimumSize(new Dimension(60, 25));
    Spin spin = new Spin(textField);
    spin.setMinValue(0);
    spin.setMaxValue(maxVal);
    spin.putValue(0);
    spin.setIncrement(1);
    spin.addSpinListener(this);
    return spin;
  }

  private JPanel makeSpinPanel(int rowCount, int colCount) {
    GridBagLayout gbl = new GridBagLayout();
    JPanel panel = new JPanel(gbl);
    JLabel rowLabel, colLabel;
    GridBagConstraints gbc = new GridBagConstraints();
    
    rowArea = makeSpin(rowCount-1);
    colArea = makeSpin(colCount-1);
    rowLabel = new JLabel("row:");
    colLabel = new JLabel("column:");

    gbc.insets = new Insets(5, 5, 5, 5);
    gbc.gridwidth = 1;
    gbl.setConstraints(rowLabel, gbc);
    panel.add(rowLabel);
    gbl.setConstraints(rowArea, gbc);
    panel.add(rowArea);
    gbl.setConstraints(colLabel, gbc);
    panel.add(colLabel);
    gbl.setConstraints(colArea, gbc);
    panel.add(colArea);
    return panel;
  }

  private JPanel makeButtonPanel() {
    GridBagLayout gbl = new GridBagLayout();
    GridBagConstraints gbc = new GridBagConstraints();
    JPanel buttonPanel = new JPanel(gbl);

    addRowButton = new JButton("add row");
    addColButton = new JButton("add column");
    delRowButton = new JButton("delete row");
    delColButton = new JButton("delete column");
    addRowButton.addActionListener(this);
    addColButton.addActionListener(this);
    delRowButton.addActionListener(this);
    delColButton.addActionListener(this);
    addRowButton.setPreferredSize(new Dimension(99, 22));
    delRowButton.setPreferredSize(new Dimension(112, 22));
    addColButton.setPreferredSize(new Dimension(99, 22));
    delColButton.setPreferredSize(new Dimension(112, 22));

    gbc.gridx = 0;
    gbc.gridy = 0;
    gbc.gridwidth = 1;
    gbc.insets = new Insets(5, 10, 0, 5);
    gbl.setConstraints(addRowButton, gbc);
    buttonPanel.add(addRowButton);
    gbc.gridx = 1;
    gbl.setConstraints(delRowButton, gbc);
    buttonPanel.add(delRowButton);
    gbc.gridy = 1;
    gbc.gridx = 0;
    gbl.setConstraints(addColButton, gbc);
    buttonPanel.add(addColButton);
    gbc.gridx = 1;
    gbl.setConstraints(delColButton, gbc);
    buttonPanel.add(delColButton);
    return buttonPanel;
  }

  private JPanel makeControlPanel(int rowCount, int colCount) {
    GridBagLayout gbl = new GridBagLayout();
    JPanel panel = new JPanel(gbl);
    JPanel buttonControls = makeButtonPanel();
    JPanel spinControls = makeSpinPanel(rowCount, colCount);
    GridBagConstraints gbc = new GridBagConstraints();

    grid = makeGrid(rowCount, colCount);
    grid.setTableHeader(null);
    addGridListeners();
    JScrollPane scrollPane = new JScrollPane(grid);
    scrollPane.setMinimumSize(new Dimension(200, 200));

    gbc.gridwidth = GridBagConstraints.REMAINDER;
    gbc.fill = GridBagConstraints.HORIZONTAL;
    gbc.anchor = GridBagConstraints.WEST;
    gbl.setConstraints(spinControls, gbc);
    panel.add(spinControls);
    gbc.anchor = GridBagConstraints.CENTER;
    gbc.fill = GridBagConstraints.NONE;
    gbl.setConstraints(scrollPane, gbc);
    panel.add(scrollPane);
    gbl.setConstraints(scrollPane, gbc);
    panel.add(buttonControls);

    return panel;
  }

  private Sequence copyTableCells() throws G2AccessException {
    Sequence tableCellCopy = new Sequence();
    Sequence fftCells = (Sequence)(fft.getTableCells()).clone();
    for (int i=0; i<fftCells.size(); i++)
      tableCellCopy.addElement(((Vector)fftCells.elementAt(i)).clone());
    return tableCellCopy;
  }
  
  private void populateDialog() {

    try {
      tableCells = copyTableCells();
      Sequence tempSeq = tableCells;
      int rowCount = tempSeq.size();
      int colCount = ((Sequence)tempSeq.elementAt(0)).size();
      JPanel topControls = makeControlPanel(rowCount, colCount);
      GridBagLayout gbl = new GridBagLayout();
      JPanel containingPanel = new JPanel(gbl);
      GridBagConstraints gbc = new GridBagConstraints();
      gbc.insets = new Insets (7, 10, 7, 7);
      component.add(topControls);
      tabPane = new JTabbedPane();
      gbl.setConstraints(tabPane, gbc);
      containingPanel.add(tabPane);
      component.add(containingPanel, BorderLayout.EAST);
      selectedIndex = 0;
      resetPanels();
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private void resetPanels() {
    try {
      Structure forPanels = getStructureForPanels();
      Structure forDefaults = new Structure();
      Structure tempStruct = (Structure)fft.getPropertyValue(DEFAULT_CELL_FORMAT_);
      if (tempStruct == null) tempStruct = new Structure();
      forDefaults.setAttributeValue(CELL_FORMAT_, tempStruct);
      tempStruct = null;
      tempStruct = (Structure)fft.getPropertyValue(DEFAULT_EVALUATION_SETTING_);
      if (tempStruct == null) tempStruct = new Structure();
      forDefaults.setAttributeValue(CELL_EVALUATION_ATTRIBUTES_, tempStruct);
      tabPane.removeAll();
      tabPane.addTab("Cell Expression", new ExpressionPanel(forPanels));
      tabPane.addTab("Cell Format", new FormatPanel(forPanels));
      tabPane.addTab("Default Settings", new EvaluationPanel(forDefaults));
      tabPane.addTab("Default Format", new FormatPanel(forDefaults));
      tabPane.setSelectedIndex(selectedIndex);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    } catch (NoSuchAttributeException nsae) {
      Trace.exception(nsae);
    }
  }

  @Override
  public void spinUp(SpinEvent event) {
    if (event.getSource() == rowArea){
      int row = grid.getSelectedRow();
      if (row < rowArea.getMaxValue())
	grid.setRowSelectionInterval(row+1, row+1);
      else
	java.awt.Toolkit.getDefaultToolkit().beep();
    } else if (event.getSource() == colArea) {
      int col = grid.getSelectedColumn();
      if (col < colArea.getMaxValue())
	grid.setColumnSelectionInterval(col+1, col+1);
      else
	java.awt.Toolkit.getDefaultToolkit().beep();
    }
  }

  @Override
  public void spinDown(SpinEvent event) {
    if (event.getSource() == rowArea){
      int row = grid.getSelectedRow();
      grid.setRowSelectionInterval(row-1, row-1);
    } else if (event.getSource() == colArea) {
      int col = grid.getSelectedColumn();
      grid.setColumnSelectionInterval(col-1, col-1);
    }
  }

  @Override
  public void actionPerformed(ActionEvent event) {
    Object source = event.getSource();
    if (source instanceof JTextField) {
      int sourceVal = new Integer(((JTextField)source).getText()).intValue();
      if (source == rowArea.getTextWidget()) {
	if (sourceVal != grid.getSelectedRow())
	  if (sourceVal <= rowArea.getMaxValue()) 
	    grid.setRowSelectionInterval(sourceVal, sourceVal);
	  else {
	    rowArea.putValue(grid.getSelectedRow());
	    launchWarningDialog(sourceVal, "rows");
	  }
      } else if (source == colArea.getTextWidget())
	if (sourceVal != grid.getSelectedColumn())
	  if (sourceVal <= colArea.getMaxValue())
	    grid.setColumnSelectionInterval(sourceVal, sourceVal);
	  else {
	    colArea.putValue(grid.getSelectedColumn());
	    launchWarningDialog(sourceVal, "columns");
	  }
    } else {
      int currentRow = new Integer(((JTextField)rowArea.getTextWidget())
				   .getText()).intValue();
      int currentCol = new Integer(((JTextField)colArea.getTextWidget())
				   .getText()).intValue();
      if (source == addRowButton) {
	gridModel.insertRow(currentRow+1, makeRow());
	addRow();
      } else if (source == delRowButton) { 
	gridModel.removeRow(currentRow);
	removeRow();
      } else if (source == addColButton) {
	colModel.addColumn(new TableColumn());
	colModel.moveColumn(colModel.getColumnCount()-1, currentCol + 1);
	addColumn();
      } else if (source == delColButton) {
	colModel.removeColumn(colModel.getColumn(currentCol));
	removeColumn();
      }
    }
  }

  private void launchWarningDialog(int limit, String type) {
    new WarningDialog(null, "Value Out of Bounds", true,
		      "There are not "+limit+" "+type+" in this table.",
		      null).setVisible(true);
  }
  
  private void addGridListeners() {
    colModel = grid.getColumnModel();
    for (int i = 0; i<grid.getColumnCount(); i++)
      colModel.getColumn(i).setPreferredWidth(16);
    rowModel = grid.getSelectionModel();
    rowModel.addListSelectionListener(this);
    colModel.addColumnModelListener(this);
  }

  private Vector makeRow() {
    Vector row = new Vector();
    for (int i=0; i<gridModel.getColumnCount(); i++)
      row.addElement(null);
    return row;
  }
  
  private JTable makeGrid(int rowCount, int colCount) {
    gridModel = new DefaultTableModel(rowCount, colCount);
    JTable grid = new JTable();
    grid.setModel(gridModel);
    grid.setSelectionBackground(Color.black);
    grid.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    grid.setRowSelectionAllowed(true);
    grid.setColumnSelectionAllowed(true);
    grid.setRowSelectionInterval(0, 0);
    grid.setColumnSelectionInterval(0, 0);
    grid.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
    return grid;
  }

  @Override
  public void columnSelectionChanged(ListSelectionEvent event) {
    if (event.getValueIsAdjusting()) {
      int first = event.getFirstIndex();
      int last = event.getLastIndex();
      int maxLimit = (int)colArea.getMaxValue();
      if (first != last) {
	if (first<=maxLimit&&last<=maxLimit) {
	  int currentCol = new Integer(((JTextField)colArea.getTextWidget())
				       .getText()).intValue();
	  if (first == currentCol) 
	    colArea.putValue(last);
	  else if (last == currentCol)
	    colArea.putValue(first);
	  setPanelChanges(new Integer(((JTextField)rowArea.getTextWidget())
				      .getText()).intValue(), currentCol);
	}
      }
    }
    selectedIndex = tabPane.getSelectedIndex();
    resetPanels();
  }
  
  @Override
  public void valueChanged(ListSelectionEvent lse) {
    if (lse.getValueIsAdjusting()) { 
      int first = lse.getFirstIndex();
      int last = lse.getLastIndex();
      int maxLimit = (int)rowArea.getMaxValue();
      if (lse.getSource() == rowModel) {
	int currentRow = new Integer(((JTextField)rowArea.getTextWidget())
				     .getText()).intValue();
	if (first != last) {
	  if (first <= maxLimit && last <= maxLimit) {
	    if (first  == currentRow) 
	      rowArea.putValue(last);
	    else if (last == currentRow)
	      rowArea.putValue(first);
	    setPanelChanges(currentRow,
			    new Integer(((JTextField)colArea.
					 getTextWidget()).getText()).
			      intValue());
	  }
	}
      }
    }
    selectedIndex = tabPane.getSelectedIndex();
    resetPanels();
  }

  private void addRow() {
    Sequence firstRow = (Sequence)tableCells.elementAt(0);
    int colCount = firstRow.size();
    Sequence newRow = new Sequence();
    for (int i=0; i<colCount; i++)
      newRow.addElement(NONE_);
    int currentRow = new Integer(((JTextField)rowArea.
				  getTextWidget()).getText()).intValue();
    tableCells.add(currentRow+1, newRow);
    int rowCount = tableCells.size();
    rowArea.setMaxValue(rowCount-1);
  }

  private void removeRow() {
    int currentRow = new Integer(((JTextField)rowArea.
				  getTextWidget()).getText()).intValue();
    tableCells.removeElementAt(currentRow); 
    int rowCount = tableCells.size();
    rowArea.setMaxValue(rowCount-1);
    grid.setRowSelectionInterval(currentRow, currentRow);
  }
  
  @Override
  public void columnAdded(TableColumnModelEvent event) {
  }

  private void addColumn() {
    int rowCount = tableCells.size();
    Sequence tempRow;
    int colCount = ((Sequence)tableCells.elementAt(0)).size();
    int currentCol = new Integer(((JTextField)colArea.getTextWidget())
				 .getText()).intValue();
    for (int i=0; i<rowCount; i++) {
      tempRow = (Sequence)tableCells.elementAt(i);
      tempRow.add(currentCol+1, NONE_);
      tableCells.setElementAt(tempRow, i);
    }
    for (int i = 0; i<grid.getColumnCount(); i++)
      colModel.getColumn(i).setPreferredWidth(16);
    colCount++;
    colArea.setMaxValue(colCount - 1);
  }
  
  @Override
  public void columnMarginChanged(ChangeEvent event) {
  }

  @Override
  public void columnMoved(TableColumnModelEvent event) {
  }

  private void removeColumn() {
    int rowCount = tableCells.size();
    int colCount = ((Sequence)tableCells.elementAt(0)).size();
    Sequence tempRow;
    int currentCol = new Integer(((JTextField)colArea.getTextWidget())
				 .getText()).intValue();
    for (int i=0; i<rowCount; i++) {
      tempRow = (Sequence)tableCells.elementAt(i);
      tempRow.removeElementAt(currentCol);
      tableCells.setElementAt(tempRow, i);
    }
    colCount--;
    colArea.setMaxValue(colCount - 1);
    grid.setColumnSelectionInterval(currentCol, currentCol);
  }
  
  @Override
  public void columnRemoved(TableColumnModelEvent event) {
  }

  private void setPanelChanges(int cellRow, int cellColumn) {
    Structure cellFormat = getFormat();
    Structure cellExpression = getExpression();
    Sequence rowData = (Sequence)tableCells.elementAt(cellRow);
    Object theCell = rowData.elementAt(cellColumn);
	
    if (theCell instanceof Symbol) {
      if (!(cellFormat == null && cellExpression == null)) 
	theCell = new Structure();
    }
    if (theCell instanceof Structure) {
      if (cellFormat == null && cellExpression == null) 
	theCell = NONE_;
      else {
	Object temp = null;
	if (cellFormat != null) 
	  ((Structure)theCell).setAttributeValue(CELL_FORMAT_, cellFormat);
	if (cellExpression != null) {
	  temp = cellExpression.getAttributeValue(EXPRESSION_, null);
	  ((Structure)theCell).setAttributeValue(EXPRESSION_, temp);
	  temp = cellExpression.getAttributeValue(CELL_EVALUATION_ATTRIBUTES_,
						  null);
	    if (temp != null) 
	      ((Structure)theCell).setAttributeValue(CELL_EVALUATION_ATTRIBUTES_, temp);
	}
      }
      rowData.setElementAt(theCell, cellColumn);
    }
    tableCells.setElementAt(rowData, cellRow);
  }
  
  private Structure getFormat() {
    if (tabPane.getTabCount() != 0)
      return ((FormatPanel)tabPane.getComponentAt(1)).getResults();
    else return null;
  }

  private Structure getExpression() {
    if (tabPane.getTabCount() !=0)
      return ((ExpressionPanel)tabPane.getComponentAt(0)).getResults();
    else return null;
  }

  private Structure getStructureForPanels() {
    int currentRow = grid.getSelectedRow();
    int currentCol = grid.getSelectedColumn();
    Sequence rowData = (Sequence)tableCells.elementAt(currentRow);
    Object theCell = rowData.elementAt(currentCol);
    if (theCell instanceof Structure)
      return (Structure)theCell;
    else return new Structure();
  }

  void applyChanges() {
    setPanelChanges(new Integer(((JTextField)rowArea.getTextWidget())
				.getText()).intValue(),
		    new Integer(((JTextField)colArea.getTextWidget())
		      .getText()).intValue());
    try {
      fft.setPropertyValue(DEFAULT_CELL_FORMAT_, ((FormatPanel)tabPane.getComponentAt(3)).getResults());
      fft.setPropertyValue(DEFAULT_EVALUATION_SETTING_, ((EvaluationPanel)tabPane.getComponentAt(2)).getResults());
      fft.setTableCells(tableCells);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }
  
  private static class CellDialogClient implements StandardDialogClient {

    
    @Override
    public void dialogDismissed(StandardDialog thisDialog, int index) {
      if (thisDialog instanceof CellDialog) 
	if (index == thisDialog.OK||index == thisDialog.APPLY) 
	  ((CellDialog)thisDialog).applyChanges();
    }
  }

  private class DialogCloser extends G2ConnectionAdapter {
    G2Access cxn;
    public DialogCloser (G2Access cxn) {
      this.cxn = cxn;
      cxn.addG2ConnectionListener(this);
    }
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent e) {
      cxn.removeG2ConnectionListener(this);
      setVisible(false);
    }
  }
}
