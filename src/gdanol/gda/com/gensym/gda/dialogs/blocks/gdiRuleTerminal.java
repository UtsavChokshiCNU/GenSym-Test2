package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.ntw.TwAccess;
import com.gensym.gda.controls.*;
import com.gensym.util.symbol.AttributeTypeSpecificationSymbols;

public class gdiRuleTerminal extends BlocksDialog {
	
	public gdiRuleTerminal() {}

	public gdiRuleTerminal(java.awt.Frame frame) {
		super(frame);

		nameTag = new TextOrNoneEditor();
		nameFieldType = new ValidG2NameFieldType();
		dpanel.placeAttributeEditor(nameTag,
			NAME_TAG_, nameFieldType, 0);

		ruleCategory = new TextOrNoneEditor();
		dpanel.placeAttributeEditor(ruleCategory,
			RULE_CATEGORY_, dpanel.symbolFieldType, 1);
			
		validityInterval = new IntervalOrRadioEditor (
			new Symbol[]{INDEFINITE_, SUPPLIED_});
		dpanel.placeAttributeEditor(validityInterval, 
			VALIDITY_INTERVAL_,  2);

		history = new HistoryKeepingSpecEditor();
		dpanel.placeAttributeEditor(history, 
			HISTORY_KEEPING_SPEC_,  3);
		
	}

	public void setConnection(TwAccess connection) {
		super.setConnection(connection);
		nameFieldType.setConnection(connection);
	}
	
	public void initializeEditors() {
		Structure s = getAttributeDescription(NAME_TAG_);
		nameFieldType.setCurrentName((Symbol)s.getAttributeValue(ATTRIBUTE_VALUE_, null));
	}
	
	public boolean applyDialog() {
		Structure s = (Structure)changedAttributes.get(NAME_TAG_.toString());
		boolean applied = super.applyDialog();
		if (applied && s!=null) {
			Symbol name_ = (Symbol)s.getAttributeValue(ATTRIBUTE_VALUE_, null);
			nameFieldType.setCurrentName(name_);
			setTitle(name_.equals(AttributeTypeSpecificationSymbols.NONE_) ? 
					getCommonName() : name_.toString().toLowerCase());
		}
				
		return applied;
	}

	protected HistoryKeepingSpecEditor history;
	
	protected ValidG2NameFieldType nameFieldType;
	
	protected TextOrNoneEditor nameTag;
	protected TextOrNoneEditor ruleCategory;
	protected IntervalOrRadioEditor validityInterval;

	protected final static Symbol NAME_TAG_= Symbol.intern("NAME-TAG");
	protected final static Symbol RULE_CATEGORY_= Symbol.intern("RULE-CATEGORY");
	protected final static Symbol VALIDITY_INTERVAL_ = Symbol.intern("VALIDITY-INTERVAL");
	protected final static Symbol INDEFINITE_ = Symbol.intern("INDEFINITE");
	protected final static Symbol SUPPLIED_ = Symbol.intern("SUPPLIED");
	protected final static Symbol POINTS_= Symbol.intern("POINTS");
	protected final static Symbol TIME_= Symbol.intern("TIME");
	protected final static Symbol HISTORY_KEEPING_SPEC_= Symbol.intern("HISTORY-KEEPING-SPEC");

}