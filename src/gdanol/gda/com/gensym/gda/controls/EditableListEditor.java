
package com.gensym.gda.controls;

import java.awt.BorderLayout;
import java.awt.Dimension;

import java.util.Iterator;
import java.io.IOException;

import javax.swing.JTable;
import javax.swing.JScrollPane;
import javax.swing.table.DefaultTableModel;
import javax.swing.event.CellEditorListener;
import javax.swing.event.ChangeEvent;

import com.gensym.util.Symbol;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.util.NoSuchAttributeException;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.controls.FieldType;
import com.gensym.beansruntime.StringVector;
//import com.gensym.message.Trace;

/**
*/
public class EditableListEditor extends AbstractAttributeEditor implements CellEditorListener{

    public EditableListEditor() {
    	this("");
	}	
	
    public EditableListEditor(String title) {
		tableModel=new SingleRowTableModel(title);
		table = new JTable(tableModel);
        table.getTableHeader().setReorderingAllowed(false);
		setVisibleRows(5);
		add(scrollPane = new JScrollPane(table), BorderLayout.CENTER);
		editorElement=new TextFieldEditor();
		cellEditor=new AttributeCellEditor(editorElement);
		cellEditor.addCellEditorListener(this);
		table.setDefaultEditor(Object.class, cellEditor);

	}

    public void setFieldType(FieldType type) {
    	fieldType=type;
    	editorElement.setFieldType(type);
    }

	public FieldType getFieldType() { return fieldType;}

	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		table.removeEditor();
		table.setEnabled(enabled);
		scrollPane.setEnabled(enabled);
		table.getTableHeader().setEnabled(enabled);
	}

	public void setVisibleRows(int i) {
		table.setPreferredSize(null);
		Dimension size = table.getPreferredSize();
		size.height = size.height +  i * table.getRowHeight()+(i+1) * table.getRowMargin();
		setPreferredSize(size);		

	}
	
	public void objectUpdated(ObjectUpdateEvent event) {
		Structure values = (Structure) event.getUpdatedObject();
		
		try {
			Sequence elements= (Sequence)values.getAttributeValue(getAttribute());
			setElements(elements);
			if (getDisableIfNotUpdated()) setEnabled(true);
		} catch(NoSuchAttributeException e) {
			if (getDisableIfNotUpdated()) setEnabled(false);
		}

	}
		
	protected void setElements(Sequence elements) {
		tableModel.setRowCount(elements.size());
		for (int i=0;i<elements.size();i++) { 
			tableModel.setValueAt(elements.get(i), i, 0);
		}
	}
	
	
	public void editingCanceled(ChangeEvent e) {}
	
	public void editingStopped(ChangeEvent e) {
		fireObjectChange(tableModel.getValueSequence());
	}

	
	public void removeCellEditor() {table.removeEditor();}
	
	public void addRow(Object[] rowData) {
		tableModel.addRow(rowData);
		fireObjectChange(tableModel.getValueSequence());	
	}
	
	public void removeRow(int row) {
		tableModel.removeRow(row);
		fireObjectChange(tableModel.getValueSequence());
	}
	
	public int getRowCount() {return tableModel.getRowCount();}
	
	
	protected JTable table;
	protected JScrollPane scrollPane;
	protected SingleRowTableModel tableModel;
	protected FieldType fieldType;
	protected AbstractAttributeEditor editorElement;
	protected AttributeCellEditor cellEditor;
	
    private final static Symbol ELEMENTS_ = Symbol.intern("ELEMENTS");
	
    
    protected class SingleRowTableModel extends DefaultTableModel {
    	public SingleRowTableModel (String title) {
    		super(new Object[]{title}, 0);
    	}
    	
    	
    	public Sequence getValueSequence() {
    		Sequence values=new Sequence();
    		int rows=this.getRowCount();
    		values.setSize(rows);
    		for (int i=0;i<rows;i++) {values.set(i, getValueAt(i, 0));}
    		return values;
    	}
    	
    }
 
    
}