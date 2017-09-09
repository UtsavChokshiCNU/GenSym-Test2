    
package com.gensym.gda.controls;

import com.gensym.controls.AttributeEditor;
import com.gensym.controls.FieldType;
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
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;

import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.JRadioButton;
import javax.swing.ButtonGroup;

/**
*An abstract class representing a control for entering an arbitrary value or selceting 
*the value from the set of predefined ones.
*/
public abstract class FieldOrRadioEditor extends AbstractAttributeEditor implements ActionListener {

    private Vector controls;
    private Vector controlSymbols;
    private int currentlySelected;

    /**
    *Creates a control with specified field and several radio buttons 
    *placed below the field.
    *@param AttributeEditor the field for the arbitrary value.
    *@param values array of predefined values.
    */    
    public FieldOrRadioEditor(AttributeEditor field, Object[] values) {
        super();
        buttons = new ButtonGroup();
        currentlySelected = 0;
        setAttributeEditor(field);
        controls = new Vector();
        controlSymbols = new Vector();

        GridBagLayout gridbag = new GridBagLayout();
        GridBagConstraints c = new GridBagConstraints();
        setLayout(gridbag); 
        c.gridwidth = GridBagConstraints.REMAINDER;
        c.fill=GridBagConstraints.BOTH;
        c.weightx=1.0;
        c.weighty=1.0;
        gridbag.setConstraints((Component)field, c);
        add((Component)field);
        JRadioButton b = new JRadioButton(AbstractAttributeEditor.localize("select-text"));
        b.addActionListener(this);
        c.fill=GridBagConstraints.HORIZONTAL;
        c.gridwidth = 1;
        c.gridy = 1;
        c.gridx = GridBagConstraints.RELATIVE;
        c.weighty=0.0;
        gridbag.setConstraints(b, c);
        add(b);
        buttons.add(b);
        controls.addElement(b);
        controlSymbols.addElement("select-text");
        
        for (int i = 0; i < values.length; i++){
            b = new JRadioButton(values[i].toString().toLowerCase());
            controls.addElement(b);
            controlSymbols.addElement(values[i]);    
            b.addActionListener(this);  
            gridbag.setConstraints(b, c);
            add(b);
            buttons.add(b);
        }
        
        setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createLineBorder(SystemColor.windowBorder),
                    BorderFactory.createEmptyBorder(2,2,2,2)));

        
    }

    /**
    *Overwritten to catch a predefined value and reflect it by checking 
    *one of the radio buttons.
    */
    public void objectUpdated(ObjectUpdateEvent event) {        
        Structure values = (Structure) event.getUpdatedObject();
        try {
            Object val = values.getAttributeValue(getAttribute());
            int i = controlSymbols.indexOf(val);
            if (i > 0){
                currentlySelected = i;
                ((JRadioButton)controls.elementAt(i)).setSelected(true);
                setDefaultText();
                ((Component)getAttributeEditor()).setEnabled(false);
            } else {
                currentlySelected = 0;
                ((JRadioButton)controls.elementAt(0)).setSelected(true);
                getAttributeEditor().objectUpdated(event);
            }
        } catch (NoSuchAttributeException e) {
            if(getDisableIfNotUpdated())  setEnabled(false);
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
    *Called when the user selects one of the radiobuttons
    *and fire ObjectChange if it is for the predefined value or
    *moves focus to the arbitrary value field.
    */
	public void actionPerformed(ActionEvent event) {
		JRadioButton radio = (JRadioButton) event.getSource();
		int index = controls.indexOf(radio);
        currentlySelected = index;
        if (index > 0){
        	((Component)getAttributeEditor()).setEnabled(false);
            fireObjectChange(controlSymbols.elementAt(index));
        }else{
        	((Component)getAttributeEditor()).setEnabled(true);
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
    *Abstarct method, which returns text fields of the arbitrary value field.
    *@return the array of text fields (the arbitrary value field may
    *    consists of several text fielsd, like in {@link IntervalEditor}).
    */
    protected abstract G2textfield[] getG2textfields();
    
    /**
    *An object ensuring that one and only one radio button 
    *is selected at a given time.
    */
    protected ButtonGroup buttons;
}