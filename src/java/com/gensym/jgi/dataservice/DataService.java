package com.gensym.jgi.dataservice;

import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.classes.Item;
import com.gensym.classes.GsiDataService;
import com.gensym.classes.Variable;

/**
 * This class provides a JavaLink connection with G2 Variable DataService capabilities.
 * When a G2 Variable class also inherits from the GSI-DATA-SERVICE mixin G2 class, 
 * and the Variable's GSI-INTERFACE-NAME attribute is set to the name of a GSI-INTERFACE connected
 * to a JavaLink connection, then G2 will attempt to call specified callbacks on the connection.
 * When creating an instance of this class, an open JavaLink G2Connection and a DataServiceListener 
 * are required. The DataServiceListener will then be called with the following events:
 * <LI>setData, when a SET action is performed on the G2 variable.
 * <LI>getData, when G2 requires a new value for the G2 variable.
 * <LI>variableRegistration, when G2 first sends a reference for the variable to JavaLink 
 * (before the first getData or setData).
 * <LI>variableDeregistration, when a previously registered variable is deleted, or disabled. 
 */
public class DataService extends JGIDataService  {

  private static final Symbol LAST_RECORDED_VALUE_ = Symbol.intern("LAST-RECORDED-VALUE");

  /**
   * Create a DataService for a G2Connection, any DataService events are reported to the
   * specified DataServiceListener.
   *@param connection the open G2Connection for this DataService
   *@param listener the DataServiceListener that will recieve the DataService events
   */
  public DataService(G2Connection connection, DataServiceListener listener) {
    super(connection, listener);
  }

  /**
   * Allows a group of Gsi Variables to be updated with one call to G2.
   * This method takes an array of GsiDataService variables and will write their
   * last stored local value and status back to each corresponding variable in G2.
   * This method is faster for updating many variables in one go as there is one network
   * call to G2 that contains the data for all the variables.
   * This method will use the last stored value and status of a GsiDataService as set by 
   * GsiDataService.setStoredGsiVariableValue and GsiDataService.setStoredGsiVariableStatus 
   * respectively.
   *@param vars the array of GsiDataVariables to update
   */
  public void returnValues(GsiDataService[] vars) 
      throws G2AccessException, 
             G2CommunicationException {
    int numvars = vars.length;
    if (numvars == 0) {
    	return;
    }
    int[] statuses = new int[numvars];
    Object[] values = new Object[numvars];
    for (int i = 0; i<vars.length; i++) {
      GsiDataService var = vars[i];
      statuses[i] = var.getStoredGsiVariableStatus();
      values[i] = var.getStoredGsiVariableValue();
    }
    ((G2Gateway)connection).returnValues(vars, values, statuses);
  }
  

  /**
   * @undocumented
   * Called by the connection
   */
  @Override
  public void dispatchDataServiceEvent(Object data, int eventId, Object[] identifyingAttributes) {

    //System.out.println("In dispatchDataServiceEvent" + data + " " + eventId );

    switch (eventId) {

    case DataServiceEvent.SET_DATA_ID: 

      Item[] items = (Item[])data;
      for (int i=0; i<items.length; i++) {
	Item item = items[i];
	if (item instanceof GsiDataService && item instanceof Variable) {
	  Object value = ((GsiDataService)item).getValueFromSetAction();
	  DataServiceEvent event = new DataServiceEvent((GsiDataService)item,
							DataServiceEvent.SET_DATA_ID,
							value);
	  listener.setData(event);
	}
      }
      break;
    case DataServiceEvent.GET_DATA_ID:

      items = (Item[])data;
      for (int i=0; i<items.length; i++) {
	Item item = items[i];
	if (item instanceof GsiDataService && item instanceof Variable) {
	  DataServiceEvent event = new DataServiceEvent((GsiDataService)item,
							DataServiceEvent.GET_DATA_ID);
	  listener.getData(event);
	}
      }
      break;
    case DataServiceEvent.VARIABLE_REGISTRATION:

      Item item = (Item)data;
      if (item instanceof GsiDataService && item instanceof Variable) {
	DataServiceEvent event = new DataServiceEvent((GsiDataService)item,
						      DataServiceEvent.VARIABLE_REGISTRATION,
						      identifyingAttributes);
	listener.variableRegistration(event);
      }
      break;
    case DataServiceEvent.VARIABLE_DEREGISTRATION:

      item = (Item)data;
      if (item instanceof GsiDataService && item instanceof Variable) {
	DataServiceEvent event = new DataServiceEvent((GsiDataService)item,
						      DataServiceEvent.VARIABLE_DEREGISTRATION);
	listener.variableDeregistration(event);
      }
      break;
    default:
    }
  }
}


