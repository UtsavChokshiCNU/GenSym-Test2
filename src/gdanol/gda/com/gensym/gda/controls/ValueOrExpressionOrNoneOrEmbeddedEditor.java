    
package com.gensym.gda.controls;

import com.gensym.controls.AttributeEditor;
import com.gensym.controls.FieldType;
import com.gensym.jcontrols.G2TextField;
import com.gensym.jcontrols.G2ComboBox;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.types.G2SyntaxException;
import com.gensym.ntw.TwAccess;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.ItemEvent;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;

import java.util.Vector;
import java.util.Hashtable;

import javax.swing.BorderFactory;
import javax.swing.JRadioButton;
import javax.swing.JLabel;
import javax.swing.JComponent;
import javax.swing.ButtonGroup;


public class ValueOrExpressionOrNoneOrEmbeddedEditor extends AbstractAttributeEditor implements ActionListener {

    private Vector controls;
    private Hashtable editorTable;
    protected ButtonGroup buttons;

    private final static String[] buttonLabels = {"none", 
                                                  "quantity", 
                                                  "var-or-param",
                                                  "expression"};
    
    private final static Symbol NONE_ = Symbol.intern("NONE");
    private Object currentButton;
    
    public ValueOrExpressionOrNoneOrEmbeddedEditor() {
        super();
        buttons = new ButtonGroup();
        controls = new Vector();
        editorTable = new Hashtable(4);
        
        GridBagLayout gridbag = new GridBagLayout();
        GridBagConstraints c = new GridBagConstraints();
        setLayout(gridbag); 
        
        for (int i = 0; i < buttonLabels.length; i++){
            JRadioButton b = new JRadioButton(localize(buttonLabels[i]));
            controls.addElement(b);
            //add an editor
            AbstractAttributeEditor e = null;
            switch(i) {
                case 0: e = new TextFieldEditor();
                        e.setFieldType(new LowerCaseSymbolFieldType());                
                        b.addActionListener(new ActionListener() {
                            public void actionPerformed(ActionEvent event) {
                                switchEditor(event.getSource());
                                fireObjectChange(NONE_);
                            }
                        });
                        break;
                case 1: e = new SpinEditor(-Double.MAX_VALUE, Double.MAX_VALUE, 1.0);
                        //e.setFieldType(new FieldType("Float"));
                        G2TextField f = ((SpinEditor)e).getSpinField().getTextField();
                        f.setText(f.getDefaultContents());
                        b.addActionListener(new ActionListener() {
                            public void actionPerformed(ActionEvent event) {
                                Object src = event.getSource();
                                switchEditor(src);
                                emulateFireObjectChange(((SpinEditor)editorTable.get(src)).getSpinField().getTextField());                           
                            }
                        });
                        break;
                case 2: e = new ComboBoxEditor();
                        e.setFieldType(new LowerCaseSymbolFieldType());
                        b.addActionListener(new ActionListener() {
                            public void actionPerformed(ActionEvent event) {
                                Object src = event.getSource();
                                switchEditor(src);
                                G2ComboBox combo = ((ComboBoxEditor)editorTable.get(src)).getComboBox();
                                combo.itemStateChanged(new ItemEvent(combo, ItemEvent.ITEM_STATE_CHANGED, null, ItemEvent.SELECTED));
                            }
                        });
                        break;
                case 3: e = new TextFieldEditor();
                        ((TextFieldEditor)e).getTextField().setShowQuotesForTextType(false);
                        b.addActionListener(new ActionListener() {
                            public void actionPerformed(ActionEvent event) {
                                Object src = event.getSource();
                                switchEditor(src);
                                emulateFireObjectChange(((TextFieldEditor)editorTable.get(src)).getTextField());                                
                            }
                        });
            }
            
            c.gridwidth = 4;
            c.fill=GridBagConstraints.HORIZONTAL;
            c.weightx=1.0;
            c.gridy = 0;
            gridbag.setConstraints(e, c);
            add((Component)e);
            if (i == 0)
                e.setEnabled(false);
            if (i < 3)
                e.setVisible(false);
            c.gridwidth = 1;
            c.gridy = 1;
            c.gridx = GridBagConstraints.RELATIVE;
            gridbag.setConstraints(b, c);
            add(b);
            buttons.add(b);

            editorTable.put(b, e);
            currentButton = b;
        }        
                
        setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createLineBorder(SystemColor.windowBorder),
                    BorderFactory.createEmptyBorder(2,2,2,2)));    
    }
    
    public void initialize(Structure attributeStructure) {
    
        ((ComboBoxEditor)editorTable.get(controls.elementAt(2))).initialize(attributeStructure);
        
    }


    public void objectUpdated(ObjectUpdateEvent event) {        
        Structure values = (Structure) event.getUpdatedObject();
        try {
            Object val = values.getAttributeValue(getAttribute());
            
            boolean isEmbedded = false;
            int newlySelected = 0;

            if (val instanceof Number)
                newlySelected = 1;
            else       
            if (val instanceof Symbol)
                newlySelected = 2;
            else
            if (val instanceof String)
                newlySelected = 3;
            else
                isEmbedded = true;
            
            if (NONE_.equals(val))
                newlySelected = 0;
            
            JRadioButton newButton = (JRadioButton)controls.elementAt(newlySelected);
            switchEditor(newButton);
            
            if (isEmbedded){
                for (int i = 0; i < controls.size(); i++)
                    ((Component)controls.elementAt(i)).setEnabled(false);
                G2TextField txt = ((TextFieldEditor)editorTable.get(currentButton)).getTextField();
                txt.setText(localize("embedded"));                 
            }else{
                newButton.setSelected(true);
                if (newlySelected != 0)                    
                    ((AttributeEditor)editorTable.get(newButton)).objectUpdated(event);    
            }
                    
        } catch (NoSuchAttributeException e) {
            setEnabled(false);
        }
    }
    
    
    public void actionPerformed(ActionEvent event) {
        switchEditor(event.getSource());    
    }    


    public synchronized void addObjectChangeListener(ObjectChangeListener objectchangelistener) {
        super.addObjectChangeListener(objectchangelistener);
        for(int i = 0; i < controls.size(); i++){
            ((AttributeEditor)editorTable.get(controls.elementAt(i))).addObjectChangeListener(objectchangelistener);
        }
    }

    public void removeObjectChangeListener(ObjectChangeListener objectchangelistener) {
        super.removeObjectChangeListener(objectchangelistener);
        for(int i = 0; i < controls.size(); i++){
            ((AttributeEditor)editorTable.get(controls.elementAt(i))).removeObjectChangeListener(objectchangelistener);
        }
    }

    
    public void setFieldType(FieldType type) {
        if (type.isNumeric())
            ((AbstractAttributeEditor)editorTable.get(controls.elementAt(1))).setFieldType(type);
    }

    public FieldType getFieldType() {
        return ((AbstractAttributeEditor)editorTable.get(controls.elementAt(1))).getFieldType();
    }    
    
    public void setAttribute(Symbol attribute) {
        super.setAttribute(attribute);
        for(int i = 0; i < controls.size(); i++){
            ((AttributeEditor)editorTable.get(controls.elementAt(i))).setAttribute(attribute);
        }
    }

    private void switchEditor(Object button){
        Component e = (Component)editorTable.get(button);
        if (e != null){
            ((Component)editorTable.get(currentButton)).setVisible(false);
            e.setVisible(true);
            if (e.isEnabled()){
                e.requestFocus();
            }
            currentButton = button;
        }
    }
    
    private void emulateFireObjectChange(G2TextField txt){
        String oldText = txt.getText();
        txt.setText(oldText + "0");
        txt.focusGained(new FocusEvent(txt, FocusEvent.FOCUS_GAINED));                                
        txt.setText(oldText);
        txt.focusLost(new FocusEvent(txt, FocusEvent.FOCUS_LOST));
    }


    public boolean isValid() {
        return ((AbstractAttributeEditor)editorTable.get(currentButton)).isValid();
    }

}