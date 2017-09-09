
package com.gensym.gda.controls;

import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.jcontrols.G2TextField;

import com.gensym.controls.FieldType;
import java.awt.BorderLayout;

/**
TextFieldEditor uses {@link G2textfield} as AttributeEditor.
@see G2textfield
*/
public class TextFieldEditor extends AbstractAttributeEditor {

    public TextFieldEditor() {
		textField = new G2textfield();
		add(textField, BorderLayout.CENTER);		
		setAttributeEditor(textField);
	}

	public G2TextField getTextField() {return textField;}

    public void setFieldType(FieldType type) {textField.setFieldType(type);}

	public FieldType getFieldType() { return textField.getFieldType();}

	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		textField.setEnabled(enabled);
	}
	
	public boolean isValid() {return textField.isValid();}

    public void setValid(boolean valid) {textField.setValid(valid);}

    public void requestFocus() {textField.requestFocus();}
    public void grabFocus() {textField.grabFocus();}
	
	protected G2textfield textField;

}