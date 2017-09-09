package com.gensym.gda.dialogs.blocks;

import com.gensym.gda.controls.IntervalEditor;
import com.gensym.gda.controls.ComboBoxEditor;
import com.gensym.gda.controls.IntervalField;
import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;


public abstract class Delay extends BlocksDialog {
	protected IntervalEditor delay;
	protected IntervalEditor countBy;
	protected ComboBoxEditor displayUnits;
	
    protected final static Symbol DELAY_ = Symbol.intern("DELAY");
    protected final static Symbol COUNT_BY_ = Symbol.intern("COUNT-BY");
    protected final static Symbol DISPLAY_UNITS_ = Symbol.intern("DISPLAY-UNITS");
    
    public static final String[] TIME_UNITS_WITHOUT_WEEK = {IntervalField.TIME_UNITS[1],IntervalField.TIME_UNITS[2], IntervalField.TIME_UNITS[3], IntervalField.TIME_UNITS[4]};
    
    public Delay() {}

    public Delay(java.awt.Frame frame) {
        super(frame);

        delay = new IntervalEditor();
        dpanel.placeAttributeEditor(delay, DELAY_, 10);

        countBy = new IntervalEditor();
        dpanel.placeAttributeEditor(countBy, COUNT_BY_, 20);

        displayUnits = new ComboBoxEditor();
        dpanel.placeAttributeEditor(displayUnits, 
            DISPLAY_UNITS_, dpanel.symbolFieldType, 30);
        displayUnits.getComboBox().setChoices(
            new StringVector(TIME_UNITS_WITHOUT_WEEK));        
    }

}