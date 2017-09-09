package com.gensym.gda.controls;

import java.beans.Beans;
import java.io.IOException;
import java.util.EventObject;
import java.util.Vector;

import javax.swing.JList;
import javax.swing.DefaultListModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.gensym.beansruntime.StringVector;
import com.gensym.controls.AttributeEditor;
import com.gensym.controls.FieldType;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.message.Trace;
import com.gensym.types.G2SyntaxException;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.UnexpectedException;
import com.gensym.core.UiApplication;


/**
Control is JList, which allows to select one of the predefined values
*from the list of choices like in ComboBox.
*/
public class G2ListAsComboBox extends JList
    implements ListSelectionListener, ObjectUpdateListener, AttributeEditor
{

    public G2ListAsComboBox(){
    	super (new DefaultListModel());
        listeners = null;
        attributeName = "";
        attributeSymbol = null;
        defaultContents = "";
        fieldType = new FieldType();
        choices = new StringVector();
        sendNextChangeToG2 = true;
        initializationAttribute = null;
        warnOnBadSyntax = true;
        StringVector stringvector = new StringVector();
        model = (DefaultListModel) getModel();
        stringvector.addElement("\"Choice 0\"");
        setChoices(stringvector);
        addListSelectionListener(this);
    }

    public synchronized void add(String s) {addItem(s);}

    public synchronized void addItem(String s) {
        choices.addElement(s);
        model.addElement(s);
    }

    public synchronized void addObjectChangeListener(ObjectChangeListener objectchangelistener) {
        if(listeners == null)
            listeners = new Vector();
        listeners.addElement(objectchangelistener);
    }

    private void fireObjectChange(Object obj) {
        Vector vector;
        synchronized(this) {
            if(listeners == null) {
                return;
            }
            vector = (Vector)listeners.clone();
        }
        ObjectChangeEvent objectchangeevent;
        if(attributeName.equals(""))
            objectchangeevent = new ObjectChangeEvent(this, obj);
        else
            objectchangeevent = new ObjectChangeEvent(this, obj, attributeName);
        for(int i = 0; i < vector.size(); i++) {
            ObjectChangeListener objectchangelistener = (ObjectChangeListener)vector.elementAt(i);
            objectchangelistener.objectChanged(objectchangeevent);
        }

    }

    public Symbol getAttribute() {return attributeSymbol;}

    public StringVector getChoices() {return choices;}

    public String getDefaultContents() {return defaultContents;}

    public FieldType getFieldType() {return fieldType;}

    public Symbol getInitializationAttribute() {
        return initializationAttribute;
    }

    public boolean getWarnOnBadSyntax() {return warnOnBadSyntax;}

    public void initalizeChoices(ObjectUpdateEvent objectupdateevent) {
        String s = (String)getSelectedValue();
        Symbol symbol = initializationAttribute;
        if(symbol == null)
            symbol = attributeSymbol;
        Object obj = objectupdateevent.getUpdatedObject();
        if((obj instanceof Structure) && symbol != null) {
            Object obj1 = ((Structure)obj).getAttributeValue(symbol, null);
            if(obj1 != null && (obj1 instanceof Vector))
                try {
                    sendNextChangeToG2 = false;
                    removeAllItems();
                    for(int i = 0; i < ((Vector)obj1).size(); i++)
                        try {
                            addItem(fieldType.objectToString(((Vector)obj1).elementAt(i)));
                        } catch(IOException ioexception) {
                            throw new UnexpectedException(ioexception);
                        }

                    int j = choices.indexOf(s);
                    if(j >= 0)
                        setSelectedIndex(j);
                }
                finally {
                    sendNextChangeToG2 = true;
                }
        }
    }

    public synchronized void insert(String s, int i) {
        if(choices.size() >= i)
            choices.insertElementAt(s, i);
        else
            choices.addElement(s);
        model.insertElementAt(s, i);
    }

    public void valueChanged(ListSelectionEvent event) {
        Object obj = event.getSource();
        if(obj == this && sendNextChangeToG2)
            try {
                Object obj1 = getSelectedValue();
                if(obj1 != null ) {
                    Object obj2 = fieldType.stringToObject((String)obj1);
                    fireObjectChange(obj2);
                }
            } catch(G2SyntaxException g2syntaxexception) {
                Trace.exception(g2syntaxexception);
                if(warnOnBadSyntax)
                    warningDialog(g2syntaxexception.getMessage());
                g2syntaxexception.printStackTrace();
            }
            catch(IOException ioexception) {
                throw new UnexpectedException(ioexception);
            }
    }

    public void objectUpdated(ObjectUpdateEvent objectupdateevent) {
        Object obj = objectupdateevent.getUpdatedValue(attributeSymbol, defaultContents);
        try {
            sendNextChangeToG2 = false;
            setSelectedValue(fieldType.objectToString(obj), true);
        } catch(IOException ioexception) {
            throw new UnexpectedException(ioexception);
        } finally {
            sendNextChangeToG2 = true;
        }
    }

    public synchronized void removeAllItems() {
        choices.removeAllElements();
        if(model.getSize() > 0)
            model.removeAllElements();
    }

    public synchronized void removeItem(String s) {
        choices.removeElement(s);
        model.removeElement(s);
    }

    public synchronized void removeItemAt(int i) {
        if(choices.size() > i)
            choices.removeElementAt(i);
        model.removeElementAt(i);
    }

    public synchronized void removeObjectChangeListener(ObjectChangeListener objectchangelistener) {
        if(listeners == null) {
            return;
        } else {
            listeners.removeElement(objectchangelistener);
            return;
        }
    }

    public void setAttribute(Symbol symbol) {
        attributeSymbol = symbol;
        attributeName = symbol.toString();
    }

    public void setChoices(StringVector stringvector) {
        try {
            sendNextChangeToG2 = false;
            int i = stringvector.size();
            removeAllItems();
            for(int j = 0; j < i; j++)
                addItem((String)stringvector.elementAt(j));

        } finally {
            sendNextChangeToG2 = true;
        }
    }

    public void setDefaultContents(String s) {defaultContents = s;}

    public void setFieldType(FieldType fieldtype){fieldType = fieldtype;}

    public void setInitializationAttribute(Symbol symbol) {
        initializationAttribute = symbol;
    }

    public void setWarnOnBadSyntax(boolean flag) {warnOnBadSyntax = flag;}

    private void warningDialog(String s) {
        if(!Beans.isDesignTime()) {
            WarningDialog warningdialog = new WarningDialog(null, "", true, s, null);
            warningdialog.setVisible(true);
        }
    }

    private Vector listeners;
    private String attributeName;
    private Symbol attributeSymbol;
    private String defaultContents;
    private FieldType fieldType;
    private StringVector choices;
    private boolean sendNextChangeToG2;
    private Symbol initializationAttribute;
    private boolean warnOnBadSyntax;
    private DefaultListModel model;
}