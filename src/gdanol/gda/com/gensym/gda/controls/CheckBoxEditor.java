
package com.gensym.gda.controls;

import java.awt.BorderLayout;

import com.gensym.util.Symbol;
import com.gensym.controls.FieldType;

/**
CheckBoxEditor uses {@link G2CheckValueBox} as AttributeEditor.
@see G2CheckValueBox
*/
public class CheckBoxEditor extends AbstractAttributeEditor {

    public CheckBoxEditor() {
		checkbox = new G2CheckValueBox();
		add(checkbox, BorderLayout.CENTER);		
		setAttributeEditor(checkbox);
	}

	public G2CheckValueBox getCheckBox() {return checkbox;}
	
	public void setFieldType(FieldType type) {}

	public FieldType getFieldType() { return null;}

	public void setOnvalue(Object value) {checkbox.setOnvalue(value);}

	public void setOffvalue(Object value) {checkbox.setOffvalue(value);}	

	public Object getOnvalue() {return checkbox.getOnvalue();}
	public Object getOffvalue() {return checkbox.getOffvalue();}
	
	public void setText(String text) {checkbox.setText(text);}
	public String getText() {return checkbox.getText();}
	
	/**
	Enables/disables also checkbox.
	*/
	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		checkbox.setEnabled(enabled);
	}

	/**
	Returns the CheckBoxEditor where on value is YES Symbol,
	and off value is NO Symbol.
	*/
	public static CheckBoxEditor createYesNoCheckBox() {
		CheckBoxEditor yesno = new CheckBoxEditor();
		yesno.setOnvalue(YES_);
		yesno.setOffvalue(NO_);
		return yesno;
	}

	
	// CheckBox methods
	public void setState(boolean state) {checkbox.setState(state);}
	public boolean isSelected() {return checkbox.isSelected();}
	
	protected G2CheckValueBox checkbox;

	protected final static Symbol YES_ = Symbol.intern("YES");
	protected final static Symbol NO_ = Symbol.intern("NO");
	

}