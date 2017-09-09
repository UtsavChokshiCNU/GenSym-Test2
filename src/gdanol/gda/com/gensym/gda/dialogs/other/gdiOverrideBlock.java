package com.gensym.gda.dialogs.other;

import java.util.Hashtable;
import java.util.Enumeration;
import java.awt.Frame;
import java.lang.reflect.Constructor;

import javax.swing.JPanel;

import com.gensym.ntw.TwAccess;
import com.gensym.message.Trace;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;

import com.gensym.gda.dialogs.gdaDialogManager;

public class gdiOverrideBlock extends overrideDialog {
    
    public gdiOverrideBlock() {}

    public gdiOverrideBlock(java.awt.Frame frame) {
        super(frame);        
        panels=new Hashtable();
    }

    public void setConnection(TwAccess c){
        manager = (gdaDialogManager)c.getDialogManager();
        super.setConnection(c);
    }
    
    /**
        Creates a hidden dialog for each element of the sequence and puts their
        panels on this dialog.
            @param avalues the sequence of the launch structures for each block
                connected at the AL-OUT of this block.
    */
    public void setAttributeValues(Sequence avalues) {
        overrideDialog dialog;
        JPanel dlgPanel;
        Constructor dlgConstructor;
        Structure addData;
        for(int i=0; i < avalues.size(); i++){
            addData = (Structure)avalues.elementAt(i);
            dlgConstructor = manager.findDialogConstructor(addData);
            if (dlgConstructor==null) 
                continue;
            //create dialog
            try  {
                dialog = (overrideDialog) dlgConstructor.newInstance(new Object[]{(Frame)getOwner()});
                dialog.setConnection(getConnection());
                dialog.setAdditionalData(addData);    
            } catch (Exception e) {
                Trace.exception(e);
                continue;
            }
            dlgPanel = dialog.getDialogPanel();
            panels.put(dlgPanel, dialog);
            dpanel.addPanel(dlgPanel, null, avalues.size() - i);//revers order to match GUIDE dialog
        }
        pack();        
    }
    
    /**
        Overrided to call applyDialog() for each hidden dialog.
    */
    public boolean applyDialog() {
        
        for (Enumeration enum=panels.elements();enum.hasMoreElements();) {
            if (!((overrideDialog) enum.nextElement()).applyDialog())
                return false;
        }

        return true;
    }
    
    protected Hashtable panels;
    protected gdaDialogManager manager;
}