    
package com.gensym.gda.controls;

import com.gensym.controls.AttributeEditor;
import com.gensym.controls.FieldType;
import com.gensym.jcontrols.G2TextField;
import com.gensym.jcontrols.G2ComboBox;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.beansruntime.StringVector;
import com.gensym.types.G2SyntaxException;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.Item;
import com.gensym.message.Trace;
import com.gensym.classes.VariableOrParameter;
import com.gensym.jgi.G2AccessException;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.ItemEvent;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Button;

import java.util.Vector;
import java.util.Hashtable;
import java.util.Locale;
import java.util.Iterator;
import java.io.IOException;

import javax.swing.BorderFactory;
import javax.swing.JRadioButton;
import javax.swing.JLabel;
import javax.swing.JComponent;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JPanel;

/**
*A class for entering arbitrary number or text 
*or selecting one of the predefined symbols or NONE.
*The type of value is controlled by the radiobuttons below the field.
*Each value type (number, symbol or text) has its own field
*(Spin, Combobox and TextField respectively).
*If the current value of appropriate attribute is not of simple type
*the control is disabled and the text "embedded" is displayed.
*/
public class QuantityOrSymbolOrNoneOrEmbeddedEditor extends AbstractAttributeEditor {

    private Vector controls;
    private Hashtable editorTable;
    protected ButtonGroup buttons;

    private final static String[] buttonLabels = {"none", 
                                                  "quantity", 
                                                  "var-or-param"};
    
    private final static Symbol NONE_ = Symbol.intern("NONE");
    private Object currentButton;
    
    private TwAccess connection;
    private Object updatedValue;
    private JButton embeddedEditorButton;
    
    public QuantityOrSymbolOrNoneOrEmbeddedEditor() {
        super();
        buttons = new ButtonGroup();
        controls = new Vector();
        editorTable = new Hashtable(3);
        
        GridBagLayout panelGridbag = new GridBagLayout();
        JPanel editorPanel = new JPanel(panelGridbag);

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
            }
            
            c.fill=GridBagConstraints.BOTH;
            c.weightx=1.0;
            c.weighty=1.0;
            c.gridy = 0;
            
            panelGridbag.setConstraints(e, c);
            
            editorPanel.add((Component)e);
            if (i == 0)
                e.setEnabled(false);
            if (i < 2)
                e.setVisible(false);
            c.gridwidth = 1;
            c.gridy = 1;
            c.gridx = GridBagConstraints.RELATIVE;
            c.fill=GridBagConstraints.HORIZONTAL;
            c.weighty=0.0;
            gridbag.setConstraints(b, c);
            add(b);
            buttons.add(b);

            editorTable.put(b, e);
            currentButton = b;
            
        }        
        
        embeddedEditorButton = new JButton("...");
        Font font = ((Component)editorTable.get(currentButton)).getFont();
        embeddedEditorButton.setFont(font.deriveFont(Font.BOLD));

        int h = ((Component)editorTable.get(currentButton)).getPreferredSize().height;
        embeddedEditorButton.setPreferredSize(new Dimension(h,h));

        
        c.gridy = 0;
        c.fill = GridBagConstraints.BOTH;
        c.weightx=0.0;
        c.weighty=0.0;

        panelGridbag.setConstraints(embeddedEditorButton, c);
                
        editorPanel.add(embeddedEditorButton);
        
        embeddedEditorButton.setVisible(false);
        embeddedEditorButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                try{
                    if (updatedValue instanceof Item)
                        connection.getDialogManager().editItem(QuantityOrSymbolOrNoneOrEmbeddedEditor.this, (Item)updatedValue, connection.getUserMode(), Locale.getDefault());
                }catch(com.gensym.jgi.G2AccessException e0){
                    Trace.exception(e0);
                }catch(com.gensym.dlgruntime.ResourceInstantiationException e1){
                    Trace.exception(e1);
                }catch(java.net.MalformedURLException e2){
                    Trace.exception(e2);
                }
            }
        });
        
        c.gridy = 0;
        c.gridx = GridBagConstraints.REMAINDER;
        c.gridwidth = 3;
        c.weightx=1.0;
        c.weighty=1.0;
        
        gridbag.setConstraints(editorPanel, c);
        add(editorPanel);
        
        setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createLineBorder(SystemColor.windowBorder),
                    BorderFactory.createEmptyBorder(2,2,2,2)));    
    }
    
 /*   public void initialize(Structure attributeStructure) {
    
        ((ComboBoxEditor)editorTable.get(controls.elementAt(2))).initialize(attributeStructure);
        
    }
*/
    public void setConnection(TwAccess connection){
        this.connection = connection;
    }
    
    public void objectUpdated(ObjectUpdateEvent event) {        
        Structure values = (Structure) event.getUpdatedObject();
        
        try {

        //Andrew added to initialize combobox elements ---
        	((ComboBoxEditor)editorTable.get(controls.elementAt(2))).objectUpdated(event);
        //End Andrew added ---
            updatedValue = values.getAttributeValue(getAttribute());
            boolean isEmbedded = false;
            int newlySelected = 0;

            if (updatedValue instanceof Number)
                newlySelected = 1;
            else       
            if (updatedValue instanceof Symbol)
                newlySelected = 2;
            else {
                isEmbedded = true;
            }
            if (NONE_.equals(updatedValue))
                newlySelected = 0;
            
            JRadioButton newButton = (JRadioButton)controls.elementAt(newlySelected);
            switchEditor(newButton);
            
            if (isEmbedded){
                for (int i = 0; i < controls.size(); i++)
                    ((Component)controls.elementAt(i)).setEnabled(false);
                G2TextField txt = ((TextFieldEditor)editorTable.get(currentButton)).getTextField();
                String newText = localize("embedded");
               
                if (updatedValue instanceof VariableOrParameter){
                    try{
                        newText = ((VariableOrParameter)updatedValue).
                                    getValueStructure().
                                        getAttributeValue(Symbol.intern("DATA-POINT-VALUE")).toString();
                        embeddedEditorButton.setVisible(true);
                    }catch (G2AccessException e1){
                        Trace.exception(e1);
                    }catch (NoSuchAttributeException e2){
                        embeddedEditorButton.setVisible(true);
                        Trace.exception(e2);                        
                    }
                } else
                if (updatedValue instanceof Item)
                    try{
                        newText =  ((Item)updatedValue).getG2ClassName().toString();
                        embeddedEditorButton.setVisible(true);                        
                    }catch (G2AccessException e3){
                        Trace.exception(e3);                        
                    }
                else 
                    newText = updatedValue.toString();

                txt.setText(newText);
            }else{
                embeddedEditorButton.setVisible(false);
                newButton.setSelected(true);
                if (newlySelected != 0)                    
                    ((AttributeEditor)editorTable.get(newButton)).objectUpdated(event);    
            }
                    
        } catch (NoSuchAttributeException e) {
            if(getDisableIfNotUpdated()) setEnabled(false);
        }
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

    /**
    *Shows spin, combobox or textfield according to the button.
    *@param button selected radio button.
    */
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
    
    /**
    *Overwritten to reflect the state of the control in the checkbox and in the border color.
    */
    public void setEnabled(boolean flag){
        
        for(int i = 0; i < controls.size(); i++){
            ((Component)controls.elementAt(i)).setEnabled(flag);
            ((Component)editorTable.get(controls.elementAt(i))).setEnabled(flag);
        }

        setBorder(BorderFactory.createCompoundBorder(
                  BorderFactory.createLineBorder(flag?SystemColor.textText:SystemColor.textInactiveText),
                  BorderFactory.createEmptyBorder(2,2,2,2)));

        super.setEnabled(flag);
    }
    
    
    /**
    *Trys to fire ObjectChange event. Used when switching from one field type
    *to another.
    *@param txt new field originating ObjectChange event.
    */
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