package com.gensym.gda.dialogs.other;

import com.gensym.beansruntime.StringVector;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;

import com.gensym.gda.controls.*;

public class gdiOverrideStatus extends overrideDialog {
    
    public gdiOverrideStatus() {}

    public gdiOverrideStatus(java.awt.Frame frame) {
        super(frame);
    }
    
    
    public void initializeEditors() {
        Structure attribute = (Structure)attributes.get(OVERRIDE_VALUE_.toString());
        Boolean unknownButton = (Boolean)attribute.getAttributeValue(UNKNOWN_BUTTON_, null);
        Object objLabel;
        
        status = new RadioBoxEditor();
        if ((unknownButton != null) && unknownButton.booleanValue()){
            status.setMembers(new StringVector(new String[] {"true", "unknown", "false"}));
            status.setLabels(new StringVector(new String[]{
            (objLabel = attribute.getAttributeValue(DESCRIPTION_WHEN_TRUE_, null))!=null?
                objLabel.toString():localize("set-true-and-lock"),
            (objLabel = attribute.getAttributeValue(DESCRIPTION_WHEN_UNKNOWN_, null))!=null?
                objLabel.toString():localize("set-unknown-and-lock"),
            (objLabel = attribute.getAttributeValue(DESCRIPTION_WHEN_FALSE_, null))!=null?
                objLabel.toString():localize("set-false-and-lock"),            
            }));
            status.setRowsAndColumns(3, 1);
        }else{
            status.setMembers(new StringVector(new String[] {"true", "false"}));
            status.setLabels(new StringVector(new String[]{
            (objLabel = attribute.getAttributeValue(DESCRIPTION_WHEN_TRUE_, null))!=null?
                objLabel.toString():localize("set-true-and-lock"),
            (objLabel = attribute.getAttributeValue(DESCRIPTION_WHEN_FALSE_, null))!=null?
                objLabel.toString():localize("set-false-and-lock"),            
            }));
            status.setRowsAndColumns(2, 1);
        }
        dpanel.placeAttributeEditor(status, null, OVERRIDE_VALUE_, dpanel.statusFieldType, 1);
        pack();
    }
    
    
    protected RadioBoxEditor status;
    //public final static Symbol STATUS_ = Symbol.intern("STATUS-VALUE");
    public final static Symbol UNKNOWN_BUTTON_ = Symbol.intern("UNKNOWN-BUTTON");
    public final static Symbol DESCRIPTION_WHEN_TRUE_ = Symbol.intern("DESCRIPTION-WHEN-TRUE");
    public final static Symbol DESCRIPTION_WHEN_UNKNOWN_ = Symbol.intern("DESCRIPTION-WHEN-UNKNOWN");
    public final static Symbol DESCRIPTION_WHEN_FALSE_ = Symbol.intern("DESCRIPTION-WHEN-FALSE");
}