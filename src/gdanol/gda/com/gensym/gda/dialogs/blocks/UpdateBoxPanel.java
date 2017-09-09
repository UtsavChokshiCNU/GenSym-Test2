
package com.gensym.gda.dialogs.blocks;


import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class UpdateBoxPanel extends gdaPanel {


	public UpdateBoxPanel(gdaDialog listener) {
    	this(listener, UpdateRadioBoxEditor.FIXED, 1);
	}
	
	public UpdateBoxPanel(gdaDialog listener, int type, int minvalue) {
    	super(listener);
		updateType = new UpdateRadioBoxEditor(type);
		placeAttributeEditor(updateType,UPDATE_TYPE_, 1);
	
		updateSize = new SpinEditor(minvalue, Integer.MAX_VALUE, 1);
		placeAttributeEditor(updateSize,UPDATE_SIZE_, integerFieldType, 2);
		setBorder(new TitledBorder(LineBorder.createBlackLineBorder(),
			dialog.localize("Update")));
	
  	}

	public void setUpdateTypeType(int type) {updateType.setType(type);}
	
	public void setUpdateSizeMinValue(int minvalue) {
		updateSize.getSpinField().setMinValue(minvalue);
	}
	
	protected UpdateRadioBoxEditor updateType;
	protected SpinEditor updateSize;

	protected final static Symbol UPDATE_TYPE_= Symbol.intern("UPDATE-TYPE");		
    protected final static Symbol UPDATE_SIZE_ = Symbol.intern("UPDATE-SIZE");		

}