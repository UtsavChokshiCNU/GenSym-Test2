
package com.gensym.ntw.util;

import java.util.Locale;
import com.gensym.classes.Module;
import com.gensym.classes.Kb;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

public class KbEvent extends java.util.EventObject {

  private static final MessageKey moduleTraceKey =
    Trace.registerMessageKey ("com.gensym.module", KbEvent.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.ntw.util.TraceMessages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL     = 5;

  public static final int MODULE_CREATED            = 0;

  public static final int MODULE_DELETED            = 1;

  public static final int MODULE_NAME_CHANGED       = 2;

  public static final int MODULE_DEPENDENCY_CHANGED = 3;

  public static final int MODULE_INITIAL_DOWNLOAD   = 4;

  public static final int KB_CLEARED                = 5;

  public static final int KB_MESSAGES_INITIAL_DOWNLOAD     = 6;

  public static final int KB_LOGBOOK_MESSAGE_ADDED         = 7;

  public static final int KB_MESSAGE_BOARD_MESSAGE_ADDED   = 8;

  public static final int KB_LOGBOOK_MESSAGE_DELETED       = 9;

  public static final int KB_MESSAGE_BOARD_MESSAGE_DELETED = 10;

  public static final int TOP_LEVEL_KB_WORKSPACE_ADDED     = 11;

  public static final int TOP_LEVEL_KB_WORKSPACE_DELETED   = 12;

  private transient Module module;

  private int id;

  private java.lang.Object evtData;

  /**
   * @undocumented
   */
  public KbEvent (Kb source, Module module, int evtType, java.lang.Object evtData) {
    super (source);
    this.module = module;
    id = evtType;
    this.evtData = evtData;
    Trace.send (DEF_TRACE_LEVEL, moduleTraceKey, i18nTrace, "kbEvtConstructor",
		source, module, describeEventType (), evtData);
  }

  /**
   * Get the module that caused this change. This will be null for the initial
   * download event.
   */
  public Module getModule () {
    return module;
  }

  /**
   * The id indicating the type of event
   */
  public int getID () {
    return id;
  }

  /**
   * Retrieves data specific to the type of the event. In particular, the data for the
   * different event types defined above are:
   * <pre> MODULE_INITIAL_DOWNLOAD : A Sequence of structure of initial data for each module present</pre>
   * <pre> MODULE_CREATED          : A structure with the initial data for that module</pre>
   * <pre> MODULE_DELETED          : Not defined</pre>
   * <pre> MODULE_NAME_CHANGED     : A Symbol that is the new name for that module</pre>
   * <pre> MODULE_DEPENDENCY_CHANGED: A Sequence of Symbols naming dependent modules</pre>
   * <pre> TOP_LEVEL_WORKSPACE_ADDED: A Kbworkspace</pre>
   * <pre> TOP_LEVEL_WORKSPACE_DELETED: A Kbworkspace</pre>
   * <pre> KB_MESSAGES_INITIAL_DOWNLOAD : A Structure containing two attributes:</pre>
   * <pre> LOGBOOK</pre> which is a Sequence of Messages.
   * <pre> MESSAGE-BOARD</pre> which is a Sequence of Messages.
   * <pre> KB_LOGBOOK_MESSAGE_ADDED: A Message</pre>
   * <pre> KB_MESSAGE_BOARD_MESSAGE_ADDED: A Message</pre>
   * <pre> KB_LOGBOOK_MESSAGE_DELETED: A Message</pre>
   * <pre> KB_MESSAGE_BOARD_MESSAGE_DELETED: A Message</pre>
   * The initial data for a module is a structure containing the following slots:
   * <pre>SYSTEM-TABLES : A Sequence of system tables for the module</pre>
   * <pre>IS-TOP-LEVEL  : A Boolean indicating whether this is the top level module in the KB
   * <pre>SUBSCRIPTION-INITIAL-VALUE</pre> : A Structure containing two attributes 
   * <pre>TOP-LEVEL-MODULE</pre> naming the module (which could be null) and
   * <pre>DIRECTLY-REQUIRED-MODULES</pre> which is a Sequence of Symbols.
   */
  public java.lang.Object getData () {
    return evtData;
  }

  /**
   * Write out the Event using defaultWriteObject and then write out the source
   * (the Kb) and the Module, if the id is not MODULE_CREATED.
   */
  private void writeObject (java.io.ObjectOutputStream out) throws java.io.IOException {
    out.defaultWriteObject ();
    out.writeObject (source);
    if (id != MODULE_CREATED)
      out.writeObject (module);
  }

  /**
   * Read the Event using defaultReadObject. Then read the source and conditionally,
   * the Module of the Event.
   */
  private void readObject (java.io.ObjectInputStream in) throws java.io.IOException, ClassNotFoundException {
    in.defaultReadObject ();
    source = in.readObject ();
    if (id != MODULE_CREATED)
      module = (Module) in.readObject ();
  }

  /**
   * Returns a String describing this Event.
   */
  @Override
  public String toString () {
    String moduleName;
    if (module != null) {
      com.gensym.util.Symbol moduleName_ = module.getName ();
      if (moduleName_ != null)
	moduleName = moduleName_.getPrintValue ();
      else
	moduleName = "ANONYMOUS-MODULE";
    } else
      moduleName = null;
    return (super.toString () + "[Module = " + moduleName +
	    ", Event = " + describeEventType () +
	    ", " + " Data = " + evtData);
  }

  private String describeEventType () {
    switch (id)
      {
      case MODULE_CREATED: return "MODULE CREATED";
      case MODULE_DELETED: return "MODULE DELETED";
      case MODULE_NAME_CHANGED: return "MODULE NAME CHANGED";
      case MODULE_DEPENDENCY_CHANGED: return "MODULE DEPENDENCY CHANGED";
      case MODULE_INITIAL_DOWNLOAD: return "MODULE INITIAL DOWNLOAD";
      case KB_CLEARED: return "KB CLEARED";
      case KB_MESSAGES_INITIAL_DOWNLOAD: return "KB MESSAGES INITIAL DOWNLOAD";
      case KB_LOGBOOK_MESSAGE_ADDED: return "KB LOGBOOK MESSAGE ADDED";
      case KB_MESSAGE_BOARD_MESSAGE_ADDED: return "KB MESSAGE BOARD MESSAGE ADDED";
      case KB_LOGBOOK_MESSAGE_DELETED: return "KB LOGBOOK MESSAGE DELETED";
      case KB_MESSAGE_BOARD_MESSAGE_DELETED: return "KB MESSAGE BOARD MESSAGE DELETED";
      case TOP_LEVEL_KB_WORKSPACE_ADDED: return "TOP LEVEL WORKSPACE ADDED";
      case TOP_LEVEL_KB_WORKSPACE_DELETED: return "TOP LEVEL WORKSPACE REMOVED";
      default: throw new RuntimeException ("Illegal event code in KbEvent. Please see vkp");
      }
  }
      
}
