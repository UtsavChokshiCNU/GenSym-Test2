package com.gensym.gda.controls;


import java.awt.event.FocusListener;
import java.awt.event.FocusEvent;
import java.awt.event.MouseEvent;
import java.awt.Component;
import java.util.EventObject;

import javax.swing.AbstractCellEditor;
import javax.swing.table.TableCellEditor;
import javax.swing.JTable;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.dlgevent.ObjectChangeListener;

public class AttributeCellEditor extends AbstractCellEditor implements ObjectChangeListener, TableCellEditor {
	
	public AttributeCellEditor(AbstractAttributeEditor e) {
		editor=e;
		e.setAttribute(tableCellRendererAttribute_);
		e.addObjectChangeListener(this);
	}
	
	public Component getTableCellEditorComponent (JTable table,
                                               Object value,
                                               boolean isSelected,
                                               int row,
                                               int column) {
        this.value=value;
        Structure s=new Structure();
        s.setAttributeValue(tableCellRendererAttribute_, value);
		editor.objectUpdated(new ObjectUpdateEvent(this, s));
		return editor;
	}
		
	public Object getCellEditorValue() {
		if (editor instanceof TextFieldEditor) {
			((TextFieldEditor)editor).getTextField().focusLost(new FocusEvent(editor, FocusEvent.FOCUS_LOST));
		}
		return value;
	}
	
	public boolean isCellEditable(EventObject anEvent) {
		if (anEvent instanceof MouseEvent) { 
			return ((MouseEvent)anEvent).getClickCount() >= 2;
		}
		return true;
	}

	public void cancelCellEditing() {
		super.cancelCellEditing();
	}
	
	public boolean stopCellEditing() {
		if (!editor.isValid()) {
			editor.setValid(true);
			return false;
		}
		return super.stopCellEditing();
	}
	
	public void objectChanged( ObjectChangeEvent e) {
		value = e.getChangedObject();
	}
	
	public AbstractAttributeEditor getAttributeEditor() {return editor;}
	
	protected AbstractAttributeEditor editor;
	protected Symbol tableCellRendererAttribute_=Symbol.intern("TABLE-CELL-RENDERER-ATTRIBUTE");
	protected Object value;
	
	}