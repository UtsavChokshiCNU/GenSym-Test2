
package com.gensym.classes;

import com.gensym.ntw.util.KbModuleListener;
import com.gensym.ntw.util.KbMessageListener;
import com.gensym.util.Symbol;
import com.gensym.classes.ModuleInformation;
import com.gensym.jgi.G2AccessException;

public interface Kb {

  /**
   * Returns all the Modules in the Kb.
   * @return An array containing all the Modules in the Kb.
   */
  public Module[] getModules () throws G2AccessException;

  /**
   * Returns the top level module
   * @return The Module representing the top-level module
   */
  public Module getTopLevelModule () throws G2AccessException;

  /**
   * Retrieves a module by name.
   * Returns null if no such module exists
   * @param moduleName The name of the module. This can be null.
   * @return A Module with this value for the TOP-LEVEL-MODULE attribute.
   */
  public Module getModule (Symbol moduleName) throws G2AccessException;

  /**
   * Add listener to be notified for module changes in this Kb
   * @param listener The KbModuleListener to add
   * #see com.gensym.ntw.util.KbModuleListener
   */
  public void addKbModuleListener (KbModuleListener listener) throws G2AccessException;

  /**
   * Remove listener from notifications for Kb changes
   * @param listener The KbModuleListener to remove
   * #see com.gensym.ntw.util.KbModuleListener
   */
  public void removeKbModuleListener (KbModuleListener listener) throws G2AccessException;

  /**
   * Retrieves a Module byobject given the ModuleInformation System Table
   */
  public Module getModule (ModuleInformation mi) throws G2AccessException;

  /**
   * Add listener to be notified for messages from this Kb
   * For example, Message Board and Logbook messages.
   * @param listener The KbMessageListener to add
   * #see com.gensym.ntw.util.KbMessageListener
   */
  public void addKbMessageListener (KbMessageListener listener) throws G2AccessException;

  /**
   * Add listener to be notified for messages from this Kb
   * For example, Message Board and Logbook messages.
   * @param listener The KbMessageListener to remove
   * #see com.gensym.ntw.util.KbMessageListener
   */
  public void removeKbMessageListener (KbMessageListener listener) throws G2AccessException;


}
