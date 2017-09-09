
package com.gensym.gda.controls;

import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.controls.FieldType;
import com.gensym.types.G2SyntaxException;

import java.awt.BorderLayout;

public class IntervalEditor1 extends AbstractAttributeEditor {

    public IntervalEditor1 (IntervalField1 field) {
        intervalField = field;
        add(intervalField, BorderLayout.CENTER);        
        setAttributeEditor(intervalField);
        setBorder(intervalField.getBorder());
        intervalField.setBorder(null);
    }

	public IntervalEditor1() {
		this(new IntervalField1());
	}
	
    public void setFieldType(FieldType type) {intervalField.setFieldType(type);}

    public FieldType getFieldType() { return intervalField.getFieldType();}

    public void setEnabled(boolean enabled) {
        super.setEnabled(enabled);
        intervalField.setEnabled(enabled);
    }

    public void requestFocus(){
        intervalField.requestFocus();
    }
    
	public boolean isValid() {
		return intervalField.isValid();
	}

    public IntervalField1 getIntervalField(){
        return intervalField;
    }
    
    private IntervalField1 intervalField;

}