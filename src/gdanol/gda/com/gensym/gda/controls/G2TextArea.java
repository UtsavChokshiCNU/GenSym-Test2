package com.gensym.gda.controls;

import com.gensym.controls.FieldType;
import com.gensym.controls.AttributeEditor;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.types.G2SyntaxException;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;

import java.awt.event.KeyListener;
import java.awt.event.FocusListener;
import java.awt.event.FocusEvent;
import java.awt.event.KeyEvent;
import java.beans.Beans;
import java.io.IOException;
import java.io.EOFException;
import java.io.Serializable;
import java.io.ObjectInputStream;
import java.util.Vector;
import javax.swing.JComponent;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.Document;
import javax.swing.text.JTextComponent;

/**
Editor for large wrapped texts.
*/
public class G2TextArea extends JTextArea
    implements DocumentListener, ObjectUpdateListener, FocusListener, AttributeEditor, KeyListener {

    public G2TextArea() {
        listeners = null;
        attributeName = "";
        attributeSymbol = null;
        defaultContents = "";
        fieldType = new FieldType();
        inhibitChangePropagation = false;
        inhibitUpdatePropagation = false;
        updateCount = 0;
        nextTextChangeIsProbablyFromTypeIn = true;
        warnOnBadSyntax = true;
        propagateEveryCharacterTyped = false;
        showQuotesForTextType = false;
        setColumns(8);
      	setRows(4);
      	setLineWrap(true);
        initiateModelListening();
        addFocusListener(this);
        addKeyListener(this);
    }

    public synchronized void addObjectChangeListener(ObjectChangeListener objectchangelistener) {
        if(listeners == null)
            listeners = new Vector();
        listeners.addElement(objectchangelistener);
    }

    public void changedUpdate(DocumentEvent documentevent){}

    void fireObjectChange(Object obj) {
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

    protected void fireObjectChangeOnContents() {
        String s = getText();
        Object obj = null;
        try {
            Object obj1;
            if(emptyFieldImpliesNull && s.equals("")) 
            	obj1 = null;
            else
                obj1 = getValidatedValue(s);
            if(obj1 != null || emptyFieldImpliesNull) {
                fireObjectChange(obj1);
                oldText = s;
            }
        }
        catch(G2SyntaxException g2syntaxexception) {
            if(warnOnBadSyntax)
                warningDialog(g2syntaxexception.getMessage());
        }
        catch(EOFException _ex) {
            if(warnOnBadSyntax)
                warningDialog("Incomplete text");
        }
        catch(IOException ioexception) {
            throw new UnexpectedException(ioexception);
        }
    }

    public void focusGained(FocusEvent focusevent) {
        oldText = getText();
    }

    public void focusLost(FocusEvent focusevent) {
        String s = getText();
        boolean flag = s != null ? s.equals(oldText) ^ true : oldText != null;
        if(!focusevent.isTemporary() && flag)
            fireObjectChangeOnContents();
    }

    public Symbol getAttribute() {
        return attributeSymbol;
    }

    public String getDefaultContents() {
        return defaultContents;
    }

    public boolean getEmptyFieldImpliesNull() {
        return emptyFieldImpliesNull;
    }

    public FieldType getFieldType() {
        return fieldType;
    }

  
    private Object getValidatedValue(String s) throws G2SyntaxException, EOFException, IOException {
        if(fieldType.isText() && !showQuotesForTextType)
            s = "\"" + s + "\"";
        Object obj = fieldType.stringToObject(s);
  
	    return obj;
    }

    public boolean getWarnOnBadSyntax() {
        return warnOnBadSyntax;
    }

    private void initiateModelListening() {
        documentAdapter = new G2DocumentAdapter();
        documentAdapter.setG2TextArea(this);
        getDocument().addDocumentListener(documentAdapter);
    }

    public void insertUpdate(DocumentEvent documentevent) {
        textValueChanged();
    }

    public void keyPressed(KeyEvent keyevent) { }

    public void keyReleased(KeyEvent keyevent){
        if(keyevent.getKeyCode() == 10)
            fireObjectChangeOnContents();
    }

    public void keyTyped(KeyEvent keyevent) {}

    public void objectUpdated(ObjectUpdateEvent objectupdateevent) {
        Object obj = objectupdateevent.getUpdatedValue(attributeSymbol, emptyFieldImpliesNull ? null : ((Object) (defaultContents)));
        boolean flag = isEditable();
        if(obj != null) {
            setEditable(true);
            try {
                String s = fieldType.objectToString(obj);
                if(fieldType.isText() && !showQuotesForTextType)
                    s = s.substring(1, s.length() - 1);
                nextTextChangeIsProbablyFromTypeIn = false;
                setText(s);
                oldText = s;
                nextTextChangeIsProbablyFromTypeIn = true;
            }
            catch(IOException ioexception) {
                throw new UnexpectedException(ioexception);
            }
            setEditable(flag);
        }
        else
        if(emptyFieldImpliesNull) {
            setEditable(true);
            setText("");
            setEditable(flag);
        }
        int i = getText().length();
        setSelectionStart(i);
        setSelectionEnd(i);
    }

    private void readObject(ObjectInputStream objectinputstream)
        throws IOException, ClassNotFoundException {
        objectinputstream.defaultReadObject();
        initiateModelListening();
    }

    public synchronized void removeObjectChangeListener(ObjectChangeListener objectchangelistener) {
        if(listeners == null) {
            return;
        }
        else {
            listeners.removeElement(objectchangelistener);
            return;
        }
    }

    public void removeUpdate(DocumentEvent documentevent) {
        textValueChanged();
    }

    public void setAttribute(Symbol symbol) {
        attributeSymbol = symbol;
        attributeName = symbol.toString();
    }

    public void setDefaultContents(String s) {
        defaultContents = s;
    }

    public void setEmptyFieldImpliesNull(boolean flag) {
        emptyFieldImpliesNull = flag;
    }

    public void setFieldType(FieldType fieldtype) {
        fieldType = fieldtype;
    }

    public void setPropagateEveryKeyTyped(boolean flag) {
        propagateEveryCharacterTyped = flag;
    }

    public void setShowQuotesForTextType(boolean flag) {
        showQuotesForTextType = flag;
    }

    public void setWarnOnBadSyntax(boolean flag) {
        warnOnBadSyntax = flag;
    }

    void textValueChanged() {
        if(nextTextChangeIsProbablyFromTypeIn && propagateEveryCharacterTyped)
            fireObjectChangeOnContents();
    }

    private void warningDialog(String s) {
        if(!Beans.isDesignTime())
        {
            WarningDialog warningdialog = new WarningDialog(null, "", true, s, null);
            warningdialog.pack();
            warningdialog.setVisible(true);
        }
    }

    private Vector listeners;
    private String attributeName;
    private Symbol attributeSymbol;
    private String defaultContents;
    private FieldType fieldType;
    private volatile boolean inhibitChangePropagation;
    private volatile boolean inhibitUpdatePropagation;
    private int updateCount;
    private boolean emptyFieldImpliesNull;
    private boolean nextTextChangeIsProbablyFromTypeIn;
    private boolean warnOnBadSyntax;
    private boolean propagateEveryCharacterTyped;
    private boolean showQuotesForTextType;
    private transient G2DocumentAdapter documentAdapter;
    String oldText;
    
    class G2DocumentAdapter implements Serializable, DocumentListener {

    G2DocumentAdapter(){}

    public void changedUpdate(DocumentEvent documentevent){}

    G2TextArea getG2TextArea() {return g2TextArea;}

    public void insertUpdate(DocumentEvent documentevent) {
        textValueChanged();
    }

    public void removeUpdate(DocumentEvent documentevent) {
        textValueChanged();
    }

    void setG2TextArea(G2TextArea g2textarea) {
        g2TextArea= g2textarea;
    }

    private void textValueChanged() {
        if(g2TextArea != null)
            g2TextArea.textValueChanged();
    }

    private transient G2TextArea g2TextArea;
}

}