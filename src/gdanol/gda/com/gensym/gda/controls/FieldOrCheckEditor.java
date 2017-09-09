    
package com.gensym.gda.controls;

import com.gensym.controls.FieldType;
import com.gensym.controls.AttributeEditor;
import com.gensym.jcontrols.G2TextField;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.types.G2SyntaxException;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.FocusEvent;

import javax.swing.JCheckBox;
import javax.swing.BorderFactory;

/**
*An abstract class representing a control for entering an arbitrary value or selceting a predefined one.
*/
public abstract class FieldOrCheckEditor extends AbstractAttributeEditor implements java.awt.event.ActionListener {
    
    /**
    *CheckBox for predefined value.
    */
    protected JCheckBox noneCheck;
    
    /**
    *Predefined value.
    */
    protected Object checkValue;
    
    /**
    *Default predefined value.
    */
    protected static final Symbol NONE_ = Symbol.intern("NONE");
    
    /**
    Creates a control with specified field and NONE checkbox placed below the field.
    @param AttributeEditor the field for the arbitrary value.
    */        
    public FieldOrCheckEditor(AttributeEditor field) {
    	this(field, true);
    }
    
    /**
    Creates a control with specified field and NONE checkbox.
    @param AttributeEditor the field for the arbitrary value.
    @param placeCheckBelow <i>true</i> to place the checkbox below the field 
    *                  and <i>false</i> to place it to the right of the field.
    */
    public FieldOrCheckEditor(AttributeEditor field, boolean placeCheckBelow) {
        this(field, NONE_, placeCheckBelow);
    }
    
    /**
    Creates a control with specified field and checkbox
    @param AttributeEditor the field for the arbitrary value.
    @param checkValue the predefined value.
    @param placeCheckBelow <i>true</i> to place the checkbox below the field 
    *                  and <i>false</i> to place it to the right of the field.
    */
    public FieldOrCheckEditor(AttributeEditor field, Object checkValue, boolean placeCheckBelow) {
        super();
        setAttributeEditor(field);
        this.checkValue = checkValue;
        noneCheck = new JCheckBox(checkValue.toString().toLowerCase());
        noneCheck.addActionListener( this );
        
        add((Component)field, BorderLayout.CENTER);
        
        add(noneCheck, placeCheckBelow? BorderLayout.SOUTH: BorderLayout.EAST);
        
        setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createLineBorder(SystemColor.textText),
                    BorderFactory.createEmptyBorder(2,2,2,2)));

        
    }

    /**
    *Overwritten to catch a predefined value and reflect it by checking the checkbox.
    */
    public void objectUpdated(ObjectUpdateEvent event) {        
        Structure values = (Structure) event.getUpdatedObject();
        try {
            Object val = values.getAttributeValue(getAttribute());
            noneCheck.setSelected(checkValue.equals(val));
            if (!noneCheck.isSelected())
                getAttributeEditor().objectUpdated(event);
            else {
            	setDefaultText();
            	((Component)getAttributeEditor()).setEnabled(false);
            }
        } catch (NoSuchAttributeException e) {
            if(getDisableIfNotUpdated()) setEnabled(false);
        }
    }
    
    /**
    *Sets the default text for the field.
    */
	protected void setDefaultText() {
		G2TextField[] fields = getG2textfields();
		for (int i=0;i<fields.length;i++) {
			fields[i].setText(fields[i].getDefaultContents());
		}
	}
    
    
    /**
    *Called when the user selects the checkbox and fire ObjectChange if it is checked.
    */
	public void actionPerformed(ActionEvent event) {

		((Component)getAttributeEditor()).setEnabled(!noneCheck.isSelected());			
		if (noneCheck.isSelected()) 
            fireObjectChange(checkValue);
         else {
        	((Component)getAttributeEditor()).requestFocus();
         	
			G2TextField[] fields = getG2textfields();
			for (int i=0;i<fields.length;i++) {
				if (fields[i].hasFocus()) {
					String txt = fields[i].getText();
					fields[i].setText("");
					fields[i].focusGained(new FocusEvent(this, FocusEvent.FOCUS_GAINED));
					fields[i].setText(txt);
				}
			}
		}

         	
	}    
	
    /**
    *Overwritten to reflect the state of the control in the checkbox and in the border color.
    */
    public void setEnabled(boolean flag){
        noneCheck.setEnabled(flag);
        ((Component)getAttributeEditor()).setEnabled(flag);

        setBorder(BorderFactory.createCompoundBorder(
                  BorderFactory.createLineBorder(flag?SystemColor.textText:SystemColor.textInactiveText),
                  BorderFactory.createEmptyBorder(2,2,2,2)));

        super.setEnabled(flag);
    }
    
    /**
    *Abstarct method, which returns text fields of the arbitrary value field.
    *@return the array of text fields (the arbitrary value field may
    *    consists of several text fields, like in {@link IntervalEditor})
    */
    protected abstract G2textfield[] getG2textfields();
}