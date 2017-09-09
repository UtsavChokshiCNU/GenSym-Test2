package com.gensym.gda.dialogs.other;

import java.util.Enumeration;
import java.util.Date;
import java.util.Calendar;
import java.text.DateFormat;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.JLabel;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;

import com.gensym.gda.controls.*;

public class gdiOverrideSwitch extends overrideDialog {
    
    public gdiOverrideSwitch() {}

    public gdiOverrideSwitch(java.awt.Frame frame) {
        super(frame);
        
        GridBagConstraints c = new GridBagConstraints();
        GridBagLayout l = (GridBagLayout)dpanel.getLayout();
        
        tickText = localize("time-until-default-option");
        tick = new JLabel(tickText);
        
        c.gridy = 1;
        l.setConstraints(tick, c);
        
        dpanel.add(tick);
        
    }
    
    /**
        Overrided to populate the dialog with the editors (2 or 3 checkboxes depending on the launching structure).
    */
    public void initializeEditors() {
        //Use this structure instead of attributes hashtable to maintain the correct order
        Enumeration attr = attributesStructure.getAttributeNames();
        Structure attribute = null;
        Object prompt = null;
        Symbol name = null;
        for(int i = 2; attr.hasMoreElements(); i++){
            name = (Symbol)attr.nextElement();
            attribute = (Structure)attributes.get(name.toString());            
            prompt = attribute.getAttributeValue(NEW_VALUE_PROMPT_, null);
            CheckBoxEditor editor = new CheckBoxEditor();
            editor.setText((prompt != null)?prompt.toString():name.toString());
            dpanel.placeAttributeEditor(editor, null, name, i);
        }
    }

    /**
        Overrided to update the label displayng the time to the timeout.
    */
    protected void updateCountdownControl(long remTime){
        int oldPrefSize = tick.getPreferredSize().width;
        if (remTime <= 0)
            tick.setText(" ");
        else {
            tick.setText(tickText + " " + remTime / 1000 + " " + localize("seconds"));
        }
        
        if (tick.getPreferredSize().width > oldPrefSize)
            pack();
    }

    public final static Symbol NEW_VALUE_PROMPT_ = Symbol.intern("NEW-VALUE-PROMPT");
    private JLabel tick;
    private String tickText;
}