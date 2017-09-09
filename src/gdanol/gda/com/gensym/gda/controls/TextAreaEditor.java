
package com.gensym.gda.controls;

import com.gensym.controls.FieldType;

import java.awt.BorderLayout;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;

/**
TextAreaEditor uses {@link G2TextArea} as AttributeEditor.
@see G2TextArea
*/
public class TextAreaEditor extends AbstractAttributeEditor {

    public TextAreaEditor() {
		textArea = new G2TextArea();
		add(new JScrollPane(textArea), BorderLayout.CENTER);		
		setAttributeEditor(textArea);
	}

    public TextAreaEditor(int rows) {
        this();
        textArea.setRows(rows);
    }
        
	public G2TextArea getTextArea() {return textArea;}

    public void setFieldType(FieldType type) {textArea.setFieldType(type);}

	public FieldType getFieldType() { return textArea.getFieldType();}

	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		textArea.setEnabled(enabled);
	}

    public void setRows(int rows) {textArea.setRows(rows);}
    
    public int getRows() {return textArea.getRows();}
    
	private G2TextArea textArea;

}