package com.gensym.gda.commands;

import com.gensym.core.UiApplication;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.*;
import com.gensym.shell.util.*;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.clscupgr.gfr.GFRPalette;
import com.gensym.classes.Entity;
import com.gensym.classes.KbWorkspace;
import com.gensym.util.Symbol;
import com.gensym.mdi.MDIFrame;

import java.awt.*;
import java.awt.event.*;
import java.util.Hashtable;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;

/**
Implements Palettes command with the four subcommands: Data,
Inference, Action, and Other. When the submenu command is choosen the
appropriate palettes are created (if you choose it at first time) and displayed.
*/
public class PalettesCommands extends gdaAbstractCommand {


  
    public PalettesCommands(UiApplication uiapplication) {
    	
        super(uiapplication, new CommandInformation[] {
            new SubCommandInformation(PALETTES, true, shortResource, longResource, null, null, null, mnemonicResource, new CommandInformation[] {
             	new CommandInformation(DATA_PALETTES, true, shortResource, longResource, null, null, null, true, mnemonicResource, null),
               	new CommandInformation(INFERENCE_PALETTES, true, shortResource, longResource, null, null, null, true, mnemonicResource, null),
               	new CommandInformation(ACTION_PALETTES, true, shortResource, longResource, null, null, null, true, mnemonicResource, null),
               	new CommandInformation(OTHER_PALETTES, true, shortResource, longResource, null, null, null, true, mnemonicResource, null)
           	})
        });
    }
  
    public void commandPerformed(ActionEvent actionevent) {
        String s = actionevent.getActionCommand();

        JFrame palettes = null;
		
		if (s.equals(DATA_PALETTES)) {
			if(dataPalettes==null) {
				dataPalettes=new JFrame("Data");
				dataPalettes.setIconImage(app.getCurrentFrame().getIconImage());
				dataPalettes.getContentPane().add(createDataPalettes());
				dataPalettes.pack();
			}
			palettes=dataPalettes;
		} else if (s.equals(INFERENCE_PALETTES)) {
			if(inferencePalettes==null) {
				inferencePalettes=new JFrame("Inference");
				inferencePalettes.setIconImage(app.getCurrentFrame().getIconImage());
				inferencePalettes.getContentPane().add(createInferencePalettes());
				inferencePalettes.pack();
			}
			palettes=inferencePalettes;
		} else if (s.equals(ACTION_PALETTES)) {
			if(actionPalettes==null) {
				actionPalettes=new JFrame("Action");
				actionPalettes.setIconImage(app.getCurrentFrame().getIconImage());
				actionPalettes.getContentPane().add(createActionPalettes());
				actionPalettes.pack();
			}
			palettes=actionPalettes;
		} else if (s.equals(OTHER_PALETTES)) {
			if(otherPalettes==null) {
				otherPalettes=new JFrame("Other");
				otherPalettes.setIconImage(app.getCurrentFrame().getIconImage());
				otherPalettes.getContentPane().add(createOtherPalettes());
				otherPalettes.pack();
			}
			palettes=otherPalettes;
		}
		palettes.setVisible(true);
    }


    public void updateAvailability () {
		if (currentConnection==null)
			setAvailable(PALETTES, false);
		else {
			try {
				currentConnection.getUniqueNamedItem(com.gensym.util.symbol.G2ClassSymbols.ITEM_,
					GDL_ENTRY_POINTS_);
				setAvailable(PALETTES, true);
			}catch (G2AccessException e) {
			  System.out.println("BUG " + e);
				setAvailable(PALETTES, false);
			}
		}
    }

    
	protected GFRPalette createPalette(Symbol paletteName) {
		GFRPalette palette;
		Entity container;
		KbWorkspace ws;
		try {
			container=(Entity)currentConnection.getUniqueNamedItem(object_, paletteName);
			ws=container.getSubworkspace();
			palette = new GFRPalette(emptyString, currentConnection, ws);
		} catch (G2AccessException gae) {
			Trace.exception(gae);
			return null;
		}
		return palette;
	}


	protected JTabbedPane createDataPalettes() {
		JTabbedPane dataTabs= new JTabbedPane();
		dataTabs.addTab(localize("EntryPointsPalette"), createPalette (GDL_ENTRY_POINTS_));
		dataTabs.addTab(localize("SignalGeneratorsPalette"), createPalette (GDL_SIGNAL_GENERATORS_));
		dataTabs.addTab(localize("DataFiltersPalette"), createPalette ( GDL_DATA_FILTERS_));
		dataTabs.addTab(localize("ArithmeticPalette"), createPalette (GDL_ARITHMETIC_));
		dataTabs.addTab(localize("FunctionsPalette"), createPalette (GDL_FUNCTIONS_));
		dataTabs.addTab(localize("DataControlPalette"), createPalette (GDL_DATA_CONTROL_));
		dataTabs.addTab(localize("TimeSeriesPalette"), createPalette (GDL_TIME_SERIES_));
		dataTabs.addTab(localize("SPCPalette"), createPalette (GDL_SPC_));
		return dataTabs;
	}	
	
	protected JTabbedPane createInferencePalettes() {
		JTabbedPane inferenceTabs = new JTabbedPane();
		inferenceTabs.addTab(localize("ObservationsPalette"), createPalette(GDL_LIMIT_OBSERVATIONS_));
		inferenceTabs.addTab(localize("LogicGatesPalette"), createPalette(GDL_LOGIC_GATES_));
		inferenceTabs.addTab(localize("TabularGatesPalette"), createPalette(GDL_TABULAR_GATES_));
		inferenceTabs.addTab(localize("EvidenceGatesPalette"), createPalette(GDL_EVIDENCE_GATES_));
		inferenceTabs.addTab(localize("TemporalGatesPalette"), createPalette(GDL_TEMPORAL_GATES_));
		inferenceTabs.addTab(localize("Counters&TimersPalette"), createPalette(GDL_COUNTERS_AND_TIMERS_));
		inferenceTabs.addTab(localize("ConditionsPalette"), createPalette(GDL_CONDITIONS_));
		
		return inferenceTabs;
	}

	protected JTabbedPane createActionPalettes() {
		JTabbedPane actionTabs = new JTabbedPane();
		actionTabs.addTab(localize("SystemActionsPalette"), createPalette(GDL_SYSTEM_ACTIONS_));
		actionTabs.addTab(localize("BlockActionsPalette"), createPalette(GDL_BLOCK_ACTIONS_));
		actionTabs.addTab(localize("ControlActionsPalette"), createPalette(GDL_CONTROL_ACTIONS_));
		actionTabs.addTab(localize("QueryActionsPalette"), createPalette(GDL_QUERY_ACTIONS_));
		
		return actionTabs;
	}

	protected JTabbedPane createOtherPalettes() {
		JTabbedPane otherTabs= new JTabbedPane();
		otherTabs.addTab(localize("EncapsulatorsPalette"), createPalette(GDL_ENCAPSULATORS_));
		otherTabs.addTab(localize("AlarmDisplaysPalette"), createPalette(GDL_ALARM_DISPLAYS_));
		otherTabs.addTab(localize("PathDisplaysPalette"), createPalette(GDL_PATH_DISPLAYS_));
		otherTabs.addTab(localize("CapabilitiesAndRestrictionsPalette"), createPalette(GDL_CAPABILITIES_AND_RESTRICTIONS_));
		otherTabs.addTab(localize("ConnectionsPalette"), createPalette(GDL_CONNECTIONS_));
		otherTabs.addTab(localize("NetworkInterfacesPalette"), createPalette(GDL_NETWORK_));
//		otherTabs.addTab(localize("RuleTerminalsPalette"), createPalette(GDL_RULE_TERMINALS_));
		otherTabs.addTab(localize("StubToolsPalette"), createPalette(GDL_STUB_TOOLS_));
		
		return otherTabs;
	}


    public static final String PALETTES = "Palettes";
    public static final String DATA_PALETTES = "DataPalettes";
    public static final String INFERENCE_PALETTES = "InferencePalettes";
    public static final String ACTION_PALETTES = "ActionPalettes";
    public static final String OTHER_PALETTES = "OtherPalettes";
    
    private static final String shortResource = "ShortResource";
    private static final String longResource = "LongResource";
    private static final String mnemonicResource = "MnemonicResource";
    
	protected Symbol object_ = Symbol.intern("OBJECT");
	//Data palette names
	protected static final Symbol GDL_ENTRY_POINTS_=Symbol.intern("GDL-SENSORS-PALETTE");
	protected static final Symbol GDL_SIGNAL_GENERATORS_=Symbol.intern("GDL-GENERATORS-PALETTE");
	protected static final Symbol GDL_DATA_FILTERS_=Symbol.intern("GDL-FILTERS-PALETTE");
	protected static final Symbol GDL_ARITHMETIC_=Symbol.intern("GDA-ARITHMETIC-PALETTE");
	protected static final Symbol GDL_FUNCTIONS_=Symbol.intern("GDL-FUNCTIONS-PALETTE");
	protected static final Symbol GDL_DATA_CONTROL_=Symbol.intern("GDL-DATA-CONTROL-PALETTE");
	protected static final Symbol GDL_TIME_SERIES_=Symbol.intern("GDL-TIME-SERIES-PALETTE");
	protected static final Symbol GDL_SPC_=Symbol.intern("GDL-SPC-PALETTE");
	
	//Inference palette names
	protected static final Symbol GDL_LIMIT_OBSERVATIONS_=Symbol.intern("GDL-LIMIT-OBSERVATIONS-PALETTE");
	protected static final Symbol GDL_LOGIC_GATES_=Symbol.intern("GDL-LOGIC-GATES-PALETTE");
	protected static final Symbol GDL_TABULAR_GATES_=Symbol.intern("GDL-TABULAR-GATES-PALETTE");
	protected static final Symbol GDL_EVIDENCE_GATES_=Symbol.intern("GDL-EVIDENCE-GATES-PALETTE");
	protected static final Symbol GDL_TEMPORAL_GATES_=Symbol.intern("GDL-TEMPORAL-GATES-PALETTE");
	protected static final Symbol GDL_COUNTERS_AND_TIMERS_=Symbol.intern("GDL-COUNTERS-AND-TIMERS-PALETTE");
	protected static final Symbol GDL_CONDITIONS_=Symbol.intern("GDL-CONDITIONS-PALETTE");
	
	//Action palette names
	protected static final Symbol GDL_SYSTEM_ACTIONS_=Symbol.intern("GDL-SYSTEM-ACTIONS-PALETTE");
	protected static final Symbol GDL_BLOCK_ACTIONS_=Symbol.intern("GDL-BLOCK-ACTIONS-PALETTE");
	protected static final Symbol GDL_CONTROL_ACTIONS_=Symbol.intern("GDL-CONTROL-ACTIONS-PALETTE");
	protected static final Symbol GDL_QUERY_ACTIONS_=Symbol.intern("GDL-QUERY-ACTIONS-PALETTE");
	

	//Other palette names
	protected static final Symbol GDL_ENCAPSULATORS_=Symbol.intern("GDA-ENCAPSULATION-BLOCK-PALETTE");
	protected static final Symbol GDL_ALARM_DISPLAYS_=Symbol.intern("GAD-ALARM-DISPLAYS-PALETTE");
	protected static final Symbol GDL_PATH_DISPLAYS_=Symbol.intern("GDL-PATH-DISPLAYS-PALETTE");
	protected static final Symbol GDL_CAPABILITIES_AND_RESTRICTIONS_=Symbol.intern("GDL-CAPABILITIES-AND-RESTRICTIONS-PALETTE");
	protected static final Symbol GDL_CONNECTIONS_=Symbol.intern("GDA-PATH-CONNECTION-POSTS-PALETTE");
	protected static final Symbol GDL_NETWORK_=Symbol.intern("GPE-PALETTE");
	protected static final Symbol GDL_RULE_TERMINALS_=Symbol.intern("GDA-RULE-TERMINALS-PALETTE");
	protected static final Symbol GDL_STUB_TOOLS_=Symbol.intern("GDA-STUB-TOOLS-PALETTE");
	
	
	protected static final Symbol GDL_OBSERVATIONS_=Symbol.intern("GDL-LIMIT-OBSERVATIONS-PALETTE");

	protected JFrame dataPalettes;
	protected JFrame inferencePalettes;
	protected JFrame actionPalettes;
	protected JFrame otherPalettes;
	protected static String emptyString="";
		
}
