
package com.gensym.classes;

import java.util.Locale;
import java.io.Serializable;
import com.gensym.util.symbol.G2ClassSymbols;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.message.Trace;
import com.gensym.util.UnexpectedException;
import com.gensym.jgi.G2AccessException;

/**
 * A class that implements the Module interface to represent
 * modules in a G2 Kb. Its data is stored in a transient ModuleData object,
 * so that it is not written out every time the ModuleImpl is sent over
 * a stream. The class redirects all getters to get the data out of the
 * embedded ModuleData and provides package-private setters to update
 * the ModuleData to reflect changes in the Kb.
 */
final class ModuleImpl implements Module, G2ClassSymbols, Serializable {

  private static final MessageKey moduleTraceKey =
    Trace.registerMessageKey ("com.gensym.module", KbImpl.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.classes.TraceMessages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL     = 5;

  private Kb kb;
  private transient ModuleData mData;

  @Override
  public Symbol getName () {
    return mData.moduleName;
  }

  void setName (Symbol newName) {
    mData.moduleName = newName;
  }

  @Override
  public boolean isTopLevel () {
    return mData.isTopLevel;
  }

  void setTopLevel (boolean isTopLevel) {
    mData.isTopLevel = isTopLevel;
  }

  @Override
  public Sequence getRequiredModules () {
    return mData.getRequiredModules ();
  }

  void setRequiredModules (Sequence reqdModules) {
    mData.updateRequiredModules (reqdModules);
  }

  void addTopLevelKbWorkspace (KbWorkspace wksp) {
    mData.topLevelWorkspaces.addElement (wksp);
  }

  void removeTopLevelKbWorkspace (KbWorkspace wksp) {
    mData.topLevelWorkspaces.removeElement (wksp);
  }

  @Override
  public KbWorkspace[] getTopLevelKbWorkspaces () {
    int numWksps = mData.topLevelWorkspaces.size ();
    KbWorkspace[] wksps = new KbWorkspace[numWksps];
    mData.topLevelWorkspaces.copyInto (wksps);
    return wksps;
  }

  @Override
  public DebuggingParameters getDebuggingParameters () {
    return mData.debuggingParameters;
  }

  @Override
  public TimingParameters getTimingParameters () {
    return mData.timingParameters;
  }

  @Override
  public InferenceEngineParameters getInferenceEngineParameters () {
    return mData.inferenceEngineParameters;
  }

  @Override
  public DataServerParameters getDataServerParameters () {
    return mData.dataServerParameters;
  }

  @Override
  public SimulationParameters getSimulationParameters () {
    return mData.simulationParameters;
  }

  @Override
  public KbConfiguration getKbConfiguration () {
    return mData.kbConfiguration;
  }

  @Override
  public PrinterSetup getPrinterSetup () {
    return mData.printerSetup;
  }

  @Override
  public MessageBoardParameters getMessageBoardParameters () {
    return mData.messageBoardParameters;
  }

  @Override
  public LogbookParameters getLogbookParameters () {
    return mData.logbookParameters;
  }

  @Override
  public LogFileParameters getLogFileParameters () {
    return mData.logFileParameters;
  }
  
  @Override
  public ColorParameters getColorParameters () {
    return mData.colorParameters;
  }

  @Override
  public LanguageParameters getLanguageParameters () {
    return mData.languageParameters;
  }

  @Override
  public Fonts getFonts () {
    return mData.fonts;
  }

  @Override
  public EditorParameters getEditorParameters () {
    return mData.editorParameters;
  }

  @Override
  public MenuParameters getMenuParameters () {
    return mData.menuParameters;
  }

  @Override
  public MiscellaneousParameters getMiscellaneousParameters () {
    return mData.miscellaneousParameters;
  }

  @Override
  public DrawingParameters getDrawingParameters () {
    return mData.drawingParameters;
  }

  @Override
  public SavingParameters getSavingParameters () {
    return mData.savingParameters;
  }

  @Override
  public ItemReferenceParameters getItemReferenceParameters () {
    return mData.itemReferenceParameters;
  }

  @Override
  public ServerParameters getServerParameters () {
    return mData.serverParameters;
  }

  @Override
  public G2glParameters getG2glParameters () {
    return mData.g2glParameters;
  }

  @Override
  public VersionControlParameters getVersionControlParameters() {
    return mData.versionControlParameters;
  }

  @Override
  public ModuleInformation getModuleInformation () {
    return mData.moduleInformation;
  }

  @Override
  public Sequence getSystemTables () {
    return mData.getSystemTables ();	// NYI -vkp, 2/23/98
  }

  @Override
  public int hashCode () {
    return mData.moduleInformation.hashCode ();
  }

  @Override
  public boolean equals(java.lang.Object obj) {
	if(obj == null || !getClass().equals(obj.getClass())){
		return false;
	}
	
	ModuleImpl other = (ModuleImpl) obj;
    return (mData.moduleInformation.equals (other.mData.moduleInformation));
  }
  
  private void readObject(java.io.ObjectInputStream stream) throws java.io.IOException, ClassNotFoundException {
    stream.defaultReadObject();
    ModuleInformation mi = (ModuleInformation) stream.readObject ();
    try {
      mData = ((ModuleImpl)kb.getModule (mi)).mData;
    } catch (G2AccessException gae) {
      Trace.exception (gae);
      throw new UnexpectedException (gae, "Unexpected RPC call to g2 in ModuleImpl.readObject");
    }
  }

  private void writeObject (java.io.ObjectOutputStream out) throws java.io.IOException {
    out.defaultWriteObject ();
    out.writeObject (mData.moduleInformation);
  }

  private static final Symbol TOP_LEVEL_MODULE_ = Symbol.intern ("TOP-LEVEL-MODULE");
  private static final Symbol DIRECTLY_REQUIRED_MODULES_ = Symbol.intern ("DIRECTLY-REQUIRED-MODULES");
  private static final Symbol SYSTEM_TABLES_ = Symbol.intern ("SYSTEM-TABLES");
  private static final Symbol SUBSCRIPTION_INITIAL_VALUE_ = Symbol.intern ("SUBSCRIPTION-INITIAL-VALUE");
  private static final Symbol IS_TOP_LEVEL_ = Symbol.intern ("IS-TOP-LEVEL");
  private static final Symbol TOP_LEVEL_KB_WORKSPACES_ = Symbol.intern ("TOP-LEVEL-KB-WORKSPACES");

  Structure makeSnapshot () {
    Structure initialValue = new Structure ();
    Structure snapshot = new Structure ();
    initialValue.setAttributeValue (TOP_LEVEL_MODULE_, mData.moduleName);
    initialValue.setAttributeValue (DIRECTLY_REQUIRED_MODULES_, mData.getRequiredModules ());
    snapshot.setAttributeValue (SUBSCRIPTION_INITIAL_VALUE_, initialValue);
    snapshot.setAttributeValue (SYSTEM_TABLES_, mData.getSystemTables ());
    snapshot.setAttributeValue (IS_TOP_LEVEL_, new Boolean (mData.isTopLevel));
    return snapshot;
  }

  /**
   * Package private constuctor to be called only from KbImpl.
   */
  ModuleImpl (Kb kb, Structure moduleData) {
    this.kb = kb;
    Structure initialValue 
      = (Structure) moduleData.getAttributeValue(SUBSCRIPTION_INITIAL_VALUE_, null);
    Symbol moduleName
      = (Symbol) initialValue.getAttributeValue (TOP_LEVEL_MODULE_, null);
    Sequence requiredModules
      = (Sequence) initialValue.getAttributeValue (DIRECTLY_REQUIRED_MODULES_, null);
    boolean isTopLevel
      = ((Boolean) moduleData.getAttributeValue (IS_TOP_LEVEL_, null)).booleanValue ();
    Sequence workspaces
      = (Sequence) initialValue.getAttributeValue (TOP_LEVEL_KB_WORKSPACES_, null);
    Sequence systemTables
      = (Sequence) moduleData.getAttributeValue (SYSTEM_TABLES_, null);
    Trace.send (DEF_TRACE_LEVEL, moduleTraceKey, i18nTrace, "moduleConstructor",
		moduleName, requiredModules, systemTables);
    Trace.send (10, moduleTraceKey, i18nTrace, "rawModuleData", moduleData);
			
    mData = new ModuleData (moduleName, requiredModules, systemTables, isTopLevel, workspaces);
  }

  void pprint (java.io.PrintWriter out) {
    mData.pprint (out);
  }
}
