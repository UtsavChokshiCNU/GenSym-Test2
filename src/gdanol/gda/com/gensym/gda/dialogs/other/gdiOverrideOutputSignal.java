package com.gensym.gda.dialogs.other;

import java.util.Enumeration;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;

import com.gensym.gda.controls.*;

public class gdiOverrideOutputSignal extends overrideDialog {
    
    public gdiOverrideOutputSignal() {}
    
    public gdiOverrideOutputSignal(java.awt.Frame frame) {
        super(frame);
    }
    
    /**
        Overrided to set the default (client-side localized) override text in
        case the appropriate attribute of the launching structure is absent.
        Default override text is for this dialog is "Press OK or APPLY to output a control signal".
    */
    public void setAdditionalData(Structure additionalData) {
        super.setAdditionalData(additionalData);
        
        String OverrideText = (String)additionalData.getAttributeValue(OVERRIDE_TEXT_, null);
        if (OverrideText == null)
            addOverrideText(localize("press-ok-or-apply-to-output-a-control-signal"));
            
    }
    
}
    