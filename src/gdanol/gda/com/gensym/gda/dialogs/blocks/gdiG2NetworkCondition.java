
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.gda.controls.*;
import com.gensym.ntw.TwAccess;
import com.gensym.util.symbol.AttributeTypeSpecificationSymbols;

public class gdiG2NetworkCondition extends gdiInferenceOutputAction {
	
	public gdiG2NetworkCondition() {}

	public gdiG2NetworkCondition(java.awt.Frame frame) {
		super(frame);

		name = new TextOrNoneEditor();
		nameFieldType = new ValidG2NameFieldType();
		dpanel.placeAttributeEditor(name, NAME_, nameFieldType,  0);
		
		logic = new CheckBoxEditor();
		logic.setOnvalue(FUZZY_);
		logic.setOffvalue(DISCRETE_);
		logic.getCheckBox().setText(localize("Fuzzy"));
		dpanel.placeAttributeEditor(logic, LOGIC_, 14);
		
		transmittingHost = new TextFieldEditor();
		dpanel.placeAttributeEditor(transmittingHost, TRANSMITTING_HOST_, 
			dpanel.symbolFieldType, 17);
		transmittingHost.getTextField().setEditable(false);
		
	}
	
	
	public void setConnection(TwAccess connection) {
		super.setConnection(connection);
		nameFieldType.setConnection(connection);
	}
	
	public void initializeEditors() {
		Structure s = getAttributeDescription(NAME_);
		nameFieldType.setCurrentName((Symbol)s.getAttributeValue(ATTRIBUTE_VALUE_, null));
	}
	
	public boolean applyDialog() {
		Structure s = (Structure)changedAttributes.get(NAME_.toString());
		boolean applied = super.applyDialog();
		if (applied && s!=null) {
			Symbol name_ = (Symbol)s.getAttributeValue(ATTRIBUTE_VALUE_, null);
			nameFieldType.setCurrentName(name_);
			setTitle(name_.equals(AttributeTypeSpecificationSymbols.NONE_) ? 
					getCommonName() : name_.toString().toLowerCase());
		}
			
		return applied;
	}

	protected ValidG2NameFieldType nameFieldType;
	protected TextOrNoneEditor name;
	protected CheckBoxEditor logic;
	//read-only attribute
	protected TextFieldEditor transmittingHost;


	protected final static Symbol NAME_ = Symbol.intern("NAMES");
	protected final static Symbol LOGIC_ = Symbol.intern("LOGIC");
	protected final static Symbol FUZZY_= Symbol.intern("FUZZY");
	protected final static Symbol DISCRETE_= Symbol.intern("DISCRETE");
	protected final static Symbol TRANSMITTING_HOST_= 
		Symbol.intern("TRANSMITTING-HOST");

}