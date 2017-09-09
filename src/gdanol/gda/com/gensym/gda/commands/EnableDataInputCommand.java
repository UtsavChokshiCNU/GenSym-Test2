package com.gensym.gda.commands;

import java.awt.event.ActionEvent;

import com.gensym.core.UiApplication;
import com.gensym.ui.CommandInformation;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.Item;

/**
Implements Enable Data Input command. Finds the GDL-DATA-ENTRY-RULES object and
listens for the ACTIVE attribute of it. If object is not found the
command is disabled. When command is choosen calls GDL-ENABLE-DATA-INPUT or
GDL-DISABLE-DATA-INPUT procedures depend on current state.
*/
public class EnableDataInputCommand extends gdaAbstractCommand {

    public EnableDataInputCommand(UiApplication uiapplication) {
		super(uiapplication,
			new CommandInformation[] {
	            new CommandInformation(ENABLE_DATA_INPUT, true, shortResource, longResource, null, null, Boolean.FALSE, true, mnemonicResource, null), 
			}
		);

		dataInputListener=new GdlDataInputListener();
		gdlDataEntry=null;
		checkDataInputListener();
		updateAvailability();
    }

    protected void setCurrentConnection(TwAccess twaccess) {
		currentConnection=twaccess;
    	checkDataInputListener();
		updateAvailability();
    }

    public void commandPerformed(ActionEvent actionevent) {
        String s = actionevent.getActionCommand();
        if (s!=ENABLE_DATA_INPUT)
        	return;
        Boolean state = getState(ENABLE_DATA_INPUT);
		try {
			currentConnection.callRPC(state.booleanValue() ? GDL_DISABLE_DATA_INPUT_RPC : GDL_ENABLE_DATA_INPUT_RPC,
				new Object[] {currentConnection.retrieveSession()}
			);
		} catch (G2AccessException e) {Trace.exception(e);}
    }

    public void updateAvailability () {
		setAvailable(ENABLE_DATA_INPUT, gdlDataEntry!=null);
    }

    public void setState(String cmdKey, Boolean state) {super.setState(cmdKey, state);}
    
    protected void checkDataInputListener() {
    	if (gdlDataEntry!=null) {
    		try {
    			gdlDataEntry.removeItemListener(dataInputListener);
    		} catch (G2AccessException gae) {Trace.exception(gae);}
    		gdlDataEntry=null;
    	}

    	if (currentConnection==null)
    		return;
    	
    	try {
    		gdlDataEntry = currentConnection.getUniqueNamedItem(
    			GDL_DATA_ENTRY_SUPERIOR_, GDL_DATA_ENTRY_RULES_NAME_);
    		gdlDataEntry.addItemListener(dataInputListener);
    	} catch (G2AccessException e) {Trace.exception(e);}
    		
    }
    
    
    class GdlDataInputListener implements ItemListener {
 		public GdlDataInputListener() {}
 		
    	public void receivedInitialValues(ItemEvent e) {
    		Structure values = (Structure) e.getNewValue();
    		Boolean checked = (Boolean) values.getAttributeValue(ACTIVE_, null);
    		if (checked!=null)
    			setState(ENABLE_DATA_INPUT, checked);
    	}
    	
    	public void itemModified(ItemEvent e) {
            Structure structure = (Structure)e.getDenotation().get(0);
            Symbol symbol = (Symbol)structure.getAttributeValue(NAME_, null);
            if (!ACTIVE_.equals(symbol))
            	return;
            setState(ENABLE_DATA_INPUT, (Boolean)e.getNewValue());    		
    	}
    	
    	public void itemDeleted(ItemEvent e) {}
    }
    
    public static final String ENABLE_DATA_INPUT = "EnableDataInput";
	protected static final Symbol GDL_ENABLE_DATA_INPUT_RPC = 
		Symbol.intern("GDL-ENABLE-DATA-INPUT");
	protected static final Symbol GDL_DISABLE_DATA_INPUT_RPC = 
		Symbol.intern("GDL-DISABLE-DATA-INPUT");

	protected static final Symbol GDL_DATA_ENTRY_RULES_NAME_ = Symbol.intern("GDL-DATA-ENTRY-RULES");
    protected static final Symbol GDL_DATA_ENTRY_SUPERIOR_ = Symbol.intern("GDL-DATA-ENTRY-SUPERIOR");
    protected static final Symbol ACTIVE_ = Symbol.intern("ACTIVE");
	protected static final Symbol NAME_ = Symbol.intern("NAME");
		
//	protected static final Symbol GDL_ENGINE_NAME_ = Symbol.intern("GDL-ENGINE");
//  protected static final Symbol GDL_APPLICATION_ENGINE_ = Symbol.intern("GDL-APPLICATION-ENGINE");

    protected GdlDataInputListener dataInputListener;
    protected Item gdlDataEntry;
}