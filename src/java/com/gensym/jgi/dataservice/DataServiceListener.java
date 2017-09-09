package com.gensym.jgi.dataservice;

import com.gensym.util.*;
import com.gensym.jgi.*;

/**
 *The DataServiceListener will be called with the following events:
 * <LI>setData, when a SET action is performed on the G2 variable.
 * <LI>getData, when G2 requires a new value for the G2 variable.
 * <LI>variableRegistration, when G2 first sends a reference for the variable to JavaLink 
 * (before the first getData or setData).
 * <LI>variableDeregistration, when a previously registered variable is deleted, or disabled. 
 */
public interface DataServiceListener extends java.util.EventListener {

  /**
   * setData is called by G2 when a value has been set on a Gsi Variable using the SET action.
   *@param e A DataServiceEvent detailing the event 
   *  e.getDataItem() will contain the GsiDataService variable that caused the event
   *  e.getValue() will contain the value set by the SET action.
   */
  public void setData(DataServiceEvent e);

  /**
   * getData is called by G2 when it requires a new value from the external system for a Gsi Variable.
   *@param e A DataServiceEvent detailing the event 
   *  e.getDataItem() will contain the GsiDataService variable that caused the event
   *
   */
  public void getData(DataServiceEvent e);

  /**
   * variableRegistration is called when a Variable in G2 requires servicing from a DataService.
   *@param e A DataServiceEvent detailing the event 
   *  e.getDataItem() will contain the GsiDataService variable that caused the event
   *  e.getIdentifingAttributes() returns the identifing attributes values for this registration
   */
  public void variableRegistration(DataServiceEvent e);
  
  /**
   * variableDeregistration is called by G2 when a variable (previously registered on a DataService)
   * is no longer available (disabled, deleted, or G2 reset/restarted).
   * @param e A DataServiceEvent detailing the event 
   *   e.getDataItem() will contain the GsiDataService variable that caused the event
   */
  public void variableDeregistration(DataServiceEvent e);
}
