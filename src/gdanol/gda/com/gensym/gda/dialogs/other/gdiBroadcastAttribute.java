package com.gensym.gda.dialogs.other;

import java.awt.Frame;
import javax.swing.ListSelectionModel;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;

import com.gensym.message.Resource;

import com.gensym.gda.controls.*;

/**
    Class implementing Broadcast Attribute dialog. Uses the symbol ATTRIBUTE
    as the ATTRIBUTE-VALUE of the launchung structure and the list of attribute
    names tho choose from as the ELEMENTS sequence.
*/
public class gdiBroadcastAttribute extends com.gensym.gda.dialogs.blocks.BlocksDialog {

    public gdiBroadcastAttribute() {}
    
    public gdiBroadcastAttribute(Frame frame) {
        super(frame);
        i18n = Resource.getBundle("com.gensym.gda.dialogs.other.Messages");
        
        attr = new ListEditor ();
        attr.getList().setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        dpanel.placeAttributeEditor(attr, localize("broadcast-attribute"), ATTRIBUTE_, dpanel.symbolFieldType, 0);
    }

    /**
        Overrides {@link com.gensym.gda.dialogs.gdaDialog#applyDialog} 
        to call _GDL-UPDATE-DEFAULT-VALUES-OF-SS-BLOCKS in G2
    */
    public boolean applyDialog() {
        
        if (!editorsAreValid())
            return false;
            
        Structure attrdesc = (Structure)changedAttributes.get(ATTRIBUTE_.toString());
        if (attrdesc!=null) {    	
	        try {
	            connection.callRPC(GDL_UPDATE_DEFAULT_VALUES_OF_SS_BLOCKS_PROC_,
	                new Object[]{
	                	editedItem, 
	                	attrdesc.getAttributeValue(ATTRIBUTE_VALUE_,null), 
	                	connection.retrieveSession()});
	        } catch (G2AccessException e) {
	            Trace.exception(e);
	            return false;
	        }
        }
        changedAttributes.clear();
        return true;
    }


    private ListEditor attr;
    private static final Symbol ATTRIBUTE_ = Symbol.intern("ATTRIBUTE");
    private static final Symbol GDL_UPDATE_DEFAULT_VALUES_OF_SS_BLOCKS_PROC_ = 
    	Symbol.intern("_GDL-UPDATE-DEFAULT-VALUES-OF-SS-BLOCKS");
}