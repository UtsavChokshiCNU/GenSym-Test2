    
package com.gensym.gda.controls;

import com.gensym.controls.AttributeEditor;
import com.gensym.controls.FieldType;
import com.gensym.jcontrols.*;
import com.gensym.dlgevent.*;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.types.G2SyntaxException;
import com.gensym.dlg.WarningDialog;
import com.gensym.message.Resource;

import java.awt.*;
import java.awt.event.*;
import java.beans.Beans;
import java.io.*;
import java.util.Vector;
import java.util.MissingResourceException;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JCheckBox;
import javax.swing.BoxLayout;
import javax.swing.border.BevelBorder;

import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.BorderFactory;


public abstract class FieldOrNoneEditor extends AbstractAttributeEditor implements ActionListener {

    protected JCheckBox noneCheck;
    private static final Symbol NONE = Symbol.intern("NONE");
    
    public FieldOrNoneEditor(AttributeEditor field) {
    	this(field, true);
    }
    
    public FieldOrNoneEditor(AttributeEditor field, boolean placeCheckBelow) {
        super();
        //field.addObjectChangeListener(this);
        setAttributeEditor(field);
        noneCheck = new JCheckBox("none");
        noneCheck.addActionListener( this );
        
        add((Component)field, BorderLayout.CENTER);
        
        add(noneCheck, placeCheckBelow? BorderLayout.SOUTH: BorderLayout.EAST);
        
        setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createLineBorder(SystemColor.windowBorder),
                    BorderFactory.createEmptyBorder(2,2,2,2)));

        
    }

    public void objectUpdated(ObjectUpdateEvent event) {        
        Structure values = (Structure) event.getUpdatedObject();
        try {
            Object val = values.getAttributeValue(getAttribute());
            noneCheck.setSelected(NONE.equals(val));
            if (!noneCheck.isSelected())
                getAttributeEditor().objectUpdated(event);
            else {
            	setDefaultText();
            	((Component)getAttributeEditor()).setEnabled(false);
            }
        } catch (NoSuchAttributeException e) {
            setEnabled(false);
        }
    }

	protected void setDefaultText() {
		G2TextField[] fields = getG2textfields();
		for (int i=0;i<fields.length;i++) {
			fields[i].setText(fields[i].getDefaultContents());
		}
	}
    
/*    public void itemStateChanged(ItemEvent e){
        ((Component)getAttributeEditor()).setEnabled(e.getStateChange() == ItemEvent.DESELECTED);
        if (e.getStateChange() == ItemEvent.SELECTED){
            G2textfield[] field = getG2textfields();
            String oldtext = field[0].getText();
            field[0].setText("0");
            field[0].requestFocus();
            field[0].setText(oldtext);
        }else
            fireObjectChange(NONE);
    }
*/

	public void actionPerformed(ActionEvent event) {

		((Component)getAttributeEditor()).setEnabled(!noneCheck.isSelected());			
		if (noneCheck.isSelected()) 
            fireObjectChange(NONE);
         else {
            G2textfield[] field = getG2textfields();
            field[0].focusLost(new FocusEvent(field[0], FocusEvent.FOCUS_LOST));
            field[0].requestFocus();
		}

         	
	}    
	
    protected abstract G2textfield[] getG2textfields();
}