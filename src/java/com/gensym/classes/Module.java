
package com.gensym.classes;

import java.io.Serializable;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;

public interface Module extends Serializable{

  /**
   * Returns the name of the module
   */
  public Symbol getName ();

  /**
   * Indicates whether this is the top level module
   */
  public boolean isTopLevel ();

  /**
   * Returns the required modules
   * @return A Sequence of Symbols naming the required modules
   */
  public Sequence getRequiredModules ();

  /**
   * Returns an array containing the top-level
   * kb-workspaces asssigned to this Module.
   */
  public KbWorkspace[] getTopLevelKbWorkspaces ();

  /**
   * Returns the DebuggingParameters system table
   */
  public DebuggingParameters getDebuggingParameters ();

  /**
   * Returns the TimingParameters system table
   */
  public TimingParameters getTimingParameters ();

  /**
   * Returns the InferenceEngineParameters system table
   */
  public InferenceEngineParameters getInferenceEngineParameters ();

  /**
   * Returns the DataServerParameters system table
   */
  public DataServerParameters getDataServerParameters ();

  /**
   * Returns the SimulationParameters system table
   */
  public SimulationParameters getSimulationParameters ();

  /**
   * Returns the KbConfiguration system table
   */
  public KbConfiguration getKbConfiguration ();

  /**
   * Returns the PrinterSetup system table
   */
  public PrinterSetup getPrinterSetup ();

  /**
   * Returns the MessageBoardParameters system table
   */
  public MessageBoardParameters getMessageBoardParameters ();

  /**
   * Returns the LogbookParameters system table
   */
  public LogbookParameters getLogbookParameters ();

  /**
   * Returns the LogFileParameters system table
   */
  public LogFileParameters getLogFileParameters ();
  
  /**
   * Returns the ColorParameters system table
   */
  public ColorParameters getColorParameters ();

  /**
   * Returns the LanguageParameters system table
   */
  public LanguageParameters getLanguageParameters ();

  /**
   * Returns the Fonts system table
   */
  public Fonts getFonts ();

  /**
   * Returns the EditorParameters system table
   */
  public EditorParameters getEditorParameters ();

  /**
   * Returns the MenuParameters system table
   */
  public MenuParameters getMenuParameters ();

  /**
   * Returns the MiscellaneousParameters system table
   */
  public MiscellaneousParameters getMiscellaneousParameters ();

  /**
   * Returns the DrawingParameters system table
   */
  public DrawingParameters getDrawingParameters ();

  /**
   * Returns the SavingParameters system table
   */
  public SavingParameters getSavingParameters ();

  /**
   * Returns the MODULE-INFORMATION system table
   * @return The ModuleInformation of this Module
   */
  public ModuleInformation getModuleInformation ();

  /**
   *
   */
  public ItemReferenceParameters getItemReferenceParameters ();

  /**
   *
   */
  public ServerParameters getServerParameters ();

  /**
   *
   */
  public G2glParameters getG2glParameters ();

  /**
   *
   */
  public VersionControlParameters getVersionControlParameters();

  /**
   * Returns all system tables
   * @return A Sequence of all 18 System Table objects
   * associated with this Module.
   */
  public Sequence getSystemTables ();
}
