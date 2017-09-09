package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.gda.controls.*;
import com.gensym.ntw.TwAccess;
import com.gensym.util.symbol.AttributeTypeSpecificationSymbols;

import com.gensym.gda.controls.TextOrNoneEditor;

public class gdiPathConnectionPost extends BlocksDialog {
	
	public gdiPathConnectionPost() {}

	public gdiPathConnectionPost(java.awt.Frame frame) {
		super(frame);

		name = new TextOrNoneEditor();
		nameFieldType = new ValidG2NameFieldType();
		dpanel.placeAttributeEditor(name, NAME_, nameFieldType,  0);

		
	}
	
	public void setConnection(TwAccess connection) {
		super.setConnection(connection);
		nameFieldType.setConnection(connection);
	}

	protected void initializeEditors() {
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
	
	protected final static Symbol NAME_ = Symbol.intern("NAMES");

}