package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.ComboBoxEditor;

public class gdiRemoteQueueMessage extends gdiQueueMessage {
	protected ComboBoxEditor g2Process;
	
    protected static final Symbol G2_PROCESS_ = Symbol.intern("G2-PROCESS");

    public gdiRemoteQueueMessage(){}

    public gdiRemoteQueueMessage(java.awt.Frame frame){
        super(frame);
        
        g2Process = new ComboBoxEditor();
        dpanel.placeAttributeEditor(g2Process, G2_PROCESS_, dpanel.symbolFieldType, 1);
             
        g2Process.setEnabled(false);
           
    }
    
}