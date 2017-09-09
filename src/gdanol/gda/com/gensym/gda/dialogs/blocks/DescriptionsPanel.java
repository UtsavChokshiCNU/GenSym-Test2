
package com.gensym.gda.dialogs.blocks;


import com.gensym.util.Symbol;

import com.gensym.gda.controls.TextAreaEditor;

/**
DescriptionsPanel contains controls for the next attributes:
description-when-true, description-when-false, 
descrtiption-when-unknown, description-of-input.
If the attribute description-of-input is not defined for the block
then the corresponding control is disabled.
*/
public class DescriptionsPanel extends BlocksPanel {

  public DescriptionsPanel(BlocksDialog listener) {
    super(listener);
	TextAreaEditor editor = new TextAreaEditor(1);
	placeAttributeEditor(editor, DESCRIPTION_WHEN_TRUE_, textFieldType, 0);

	editor = new TextAreaEditor(1);
	placeAttributeEditor(editor, DESCRIPTION_WHEN_FALSE_, textFieldType, 1);

	editor = new TextAreaEditor(1);
	placeAttributeEditor(editor, DESCRIPTION_WHEN_UNKNOWN_, textFieldType, 2);

	editor = new TextAreaEditor(1);
	placeAttributeEditor(editor, DESCRIPTION_OF_INPUT_, textFieldType, 3);
	
  }


    protected final static Symbol DESCRIPTION_OF_INPUT_= Symbol.intern("DESCRIPTION-OF-INPUT");		
    protected final static Symbol DESCRIPTION_WHEN_FALSE_= Symbol.intern("DESCRIPTION-WHEN-FALSE");
    protected final static Symbol DESCRIPTION_WHEN_TRUE_= Symbol.intern("DESCRIPTION-WHEN-TRUE");
    protected final static Symbol DESCRIPTION_WHEN_UNKNOWN_= Symbol.intern("DESCRIPTION-WHEN-UNKNOWN");


}