
package com.gensym.classes;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;

/* 
 * Holds data for a ModuleImpl object.
 * Need not be serializable. This is created only within
 * the contructor of a ModuleImpl.
 */
class ModuleData {

  volatile Symbol moduleName;
  volatile Symbol[] requiredModuleNames;
  volatile boolean isTopLevel;
  Sequence systemTables;
  Sequence topLevelWorkspaces;

  ModuleData (Symbol moduleName, Sequence reqdModules, Sequence systemTables,
	      boolean isTopLevel, Sequence topLevelWorkspaces) {
    this.moduleName = moduleName;
    this.isTopLevel = isTopLevel;
    this.topLevelWorkspaces = topLevelWorkspaces != null ?
      (Sequence) topLevelWorkspaces.clone () : new Sequence ();
    updateRequiredModules (reqdModules);
    setupModuleTables (systemTables);
  }

  synchronized void updateRequiredModules (Sequence reqdModules) {
    if (reqdModules == null)
      requiredModuleNames = new Symbol[0];
    else {
      int numModules = reqdModules.size ();
      requiredModuleNames = new Symbol[numModules];
      reqdModules.copyInto (requiredModuleNames);
    }
  }

  synchronized Sequence getRequiredModules () {
    Sequence reqdModules = new Sequence (requiredModuleNames.length);
    for (int i=0; i<requiredModuleNames.length; i++)
      reqdModules.addElement (requiredModuleNames[i]);
    return reqdModules;
  }

  /*
   * We can do this because all modules must have one
   * instance of all these tables and no more. Furthermore
   * system-tables are final classes. 
   */
  private void setupModuleTables (Sequence systemTables) {
    this.systemTables = systemTables;
    for (int i=0; i<systemTables.size (); i++) {
      SystemTable table = (SystemTable) systemTables.elementAt (i);
      int tableIndex = -1;
      if (table instanceof DebuggingParameters)
	debuggingParameters = (DebuggingParameters) table;
      else if (table instanceof TimingParameters)
	timingParameters = (TimingParameters) table;
      else if (table instanceof InferenceEngineParameters)
	inferenceEngineParameters = (InferenceEngineParameters) table;
      else if (table instanceof DataServerParameters)
	dataServerParameters = (DataServerParameters) table;
      else if (table instanceof SimulationParameters)
	simulationParameters = (SimulationParameters) table;
      else if (table instanceof KbConfiguration)
	kbConfiguration = (KbConfiguration) table;
      else if (table instanceof PrinterSetup)
	printerSetup = (PrinterSetup) table;
      else if (table instanceof MessageBoardParameters)
	messageBoardParameters = (MessageBoardParameters) table;
      else if (table instanceof LogbookParameters)
	logbookParameters = (LogbookParameters) table;
      else if (table instanceof LogFileParameters)
	logFileParameters = (LogFileParameters) table;
      else if (table instanceof ColorParameters)
	colorParameters = (ColorParameters) table;
      else if (table instanceof LanguageParameters)
	languageParameters = (LanguageParameters) table;
      else if (table instanceof Fonts)
	fonts = (Fonts) table;
      else if (table instanceof EditorParameters)
	editorParameters = (EditorParameters) table;
      else if (table instanceof MenuParameters)
	menuParameters = (MenuParameters) table;
      else if (table instanceof MiscellaneousParameters)
	miscellaneousParameters = (MiscellaneousParameters) table;
      else if (table instanceof DrawingParameters)
	drawingParameters = (DrawingParameters) table;
      else if (table instanceof SavingParameters)
	savingParameters = (SavingParameters) table;
      else if (table instanceof ModuleInformation)
	moduleInformation = (ModuleInformation) table;
      else if (table instanceof ItemReferenceParameters)
	itemReferenceParameters = (ItemReferenceParameters)table;
      else if (table instanceof ServerParameters)
	serverParameters = (ServerParameters)table;
      else if (table instanceof G2glParameters)
	g2glParameters = (G2glParameters)table;
      else if (table instanceof VersionControlParameters)
	versionControlParameters = (VersionControlParameters)table;
      else
	throw new RuntimeException ("Unknown class of System Table : " + table.getClass().getName ());
    }
  }

  synchronized Sequence getSystemTables () {
    return (Sequence) systemTables.clone ();
  }

  DebuggingParameters debuggingParameters;

  TimingParameters timingParameters;

  InferenceEngineParameters inferenceEngineParameters;

  DataServerParameters dataServerParameters;

  SimulationParameters simulationParameters;

  KbConfiguration kbConfiguration;

  PrinterSetup printerSetup;

  MessageBoardParameters messageBoardParameters;

  LogbookParameters logbookParameters;

  LogFileParameters logFileParameters;
  
  ColorParameters colorParameters;

  LanguageParameters languageParameters;

  Fonts fonts;

  EditorParameters editorParameters;

  MenuParameters menuParameters;

  MiscellaneousParameters miscellaneousParameters;

  DrawingParameters drawingParameters;

  SavingParameters savingParameters;

  ModuleInformation moduleInformation;

  ItemReferenceParameters itemReferenceParameters;
  
  ServerParameters serverParameters;

  G2glParameters g2glParameters;

  VersionControlParameters versionControlParameters;

  void pprint (java.io.PrintWriter out) {
    out.println ("  " + moduleName + (isTopLevel ? " TOP" : " NOT-TOP"));
    out.println ("    requires " + com.gensym.core.DebugUtil.printArray (requiredModuleNames));
    out.println ("    system-tables = " + systemTables);
    out.println ("    workspaces = " + topLevelWorkspaces);    
  }
}
