package com.gensym.jgi.dataservice;

import com.gensym.classes.GsiDataService;
import com.gensym.util.Structure;

/**
 * A DataServiceEvent contains data detailing a DataServiceListener event.
 */
public class DataServiceEvent extends java.util.EventObject {

  protected GsiDataService var = null;
  protected Object value = null;
  protected Object[] atts = null;
  protected int eventID = -1;

  /** 
   * The Id set when a DataService setData has occured.
   */
  public static final int SET_DATA_ID = 1;

  /** 
   * The Id set when a DataService getData has occured.
   */
  public static final int GET_DATA_ID = 2;

  /**
   * The Id set when a DataService variableRegistration has occured.
   */
  public static final int VARIABLE_REGISTRATION = 3;

  /**
   * The Id set when a DataService variableDeregistration has occured.
   */
  public static final int VARIABLE_DEREGISTRATION = 4;


  public DataServiceEvent(Object source) {
    super(source);
  }

  public DataServiceEvent(GsiDataService var, int id) {
    super(var);
    this.var  = var;
    eventID = id;
  }

  public DataServiceEvent(GsiDataService var, int id, Object value) {
    this(var, id);
    this.value = value;
  }

  public DataServiceEvent(GsiDataService var, int id, Object[] identifingAttributes) {
    this(var, id);
    atts = identifingAttributes;
  }

  /**
   *@return the Id of the event
   */
  public int getID() {
    return eventID;
  }

  /**
   *@return the value of the event.
   */
  public Object getValue() {
    return value;
  }

  /**
   *@return the GsiDataService Variable that the event occured on 
   */
  public GsiDataService getDataItem() {
    return var;
  }

  /**
   *@return an array of identifing attribute values
   */
  public Object[] getIdentifingAttributes() {
    return atts;
  }

}
