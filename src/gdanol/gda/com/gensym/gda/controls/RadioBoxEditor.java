
package com.gensym.gda.controls;

import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.jcontrols.G2Radiobox;
import com.gensym.controls.FieldType;
import com.gensym.controls.AttributeEditor;
import com.gensym.beansruntime.StringVector;

import java.awt.BorderLayout;

/**
RadioBoxEditor uses inner class RadioBox as AttributeEditor.
@See RadioBox
*/
public class RadioBoxEditor extends AbstractAttributeEditor {

    public RadioBoxEditor() {
		radiobox = new RadioBox();
		add(radiobox, BorderLayout.CENTER);		
		setAttributeEditor(radiobox);
		setBorder(javax.swing.border.LineBorder.createBlackLineBorder());
		radiobox.setBorder(new javax.swing.border.EmptyBorder(0, 5, 0, 5));
	}

	public G2Radiobox getRadioBox() {return radiobox;}

    public void setFieldType(FieldType type) {radiobox.setFieldType(type);}

	public FieldType getFieldType() { return radiobox.getFieldType();}

	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		radiobox.setEnabled(enabled);
	}

	public void setLabels(StringVector labels) {radiobox.setLabels(labels);}
	public void setMembers(StringVector members) {radiobox.setMembers(members);}
	public void setRowsAndColumns(int rows, int columns) {
		radiobox.setRows(rows);
		radiobox.setColumns(columns);
	}
	
	
	protected RadioBox radiobox;
	
 	/**
 	Subclass of com.gensym.jcontrols.G2Radiobox for supporting LowerCaseSymbolFieldType.
 	setSelected in com.gensym.jcontrols.G2Radiobox assumes uppercased string.
 	*/
 	class RadioBox extends G2Radiobox implements AttributeEditor {
		public void setSelected(String s) {
			if(this.getFieldType().getTypeName().equals("Symbol"))
				s = s.toUpperCase();
				
			super.setSelected(s);		
		}
	}
		
}