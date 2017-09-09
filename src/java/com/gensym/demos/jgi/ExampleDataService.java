/*
 * 
 * Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 * 
 * GENSYM MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, OR NON-INFRINGEMENT. GENSYM SHALL NOT BE LIABLE FOR ANY DAMAGES
 * SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
 * THIS SOFTWARE OR ITS DERIVATIVES.
 * 
 */
package com.gensym.demos.jgi;

import java.util.Hashtable;
import java.util.Vector;
import java.security.SecureRandom;
import java.util.Enumeration;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.jgi.dataservice.*;
import com.gensym.classes.GsiDataService;
import com.gensym.classes.SymbolicVariable;
import com.gensym.classes.TextVariable;
import com.gensym.classes.LogicalVariable;
import com.gensym.classes.IntegerVariable;

/**
 * JavaLink DataService test Class to be used with jgidemo.kb.
 * This class demonstrates the use of Javalink as a DataService for GSI variables
 * To use:
 * <p>1. make sure jgidemo.kb is loaded and started, 
 * <p>2. run this class: java com.gensym.demos.jgi.ExampleDataService
 * <p>3. Follow the instructions found by pressing the GSI-DATA-SERVICE-EXAMPLE button
 *
 */
public class ExampleDataService implements DataServiceListener
{

  private G2Connection g2Connection = null;
  private DataService dataService = null;
  private Hashtable externalDataPointsTable = new Hashtable(211);
  private Scheduler scheduler = new Scheduler();

  /**
   * Constructor
   */
  public ExampleDataService(G2Connection connection) {
    this.g2Connection = connection;
    // Declare a Dataservice for this connection, this listens for updates
    dataService = new DataService(connection, this);
    scheduler.start();
    System.out.println("Got connection...data service enabled");
  }

  private ExternalDataPoint getExternalDataPointFromIdentifingAttributes(Object[] identAtts, 
									 GsiDataService g2Variable) {
    // Here we would work out which external data point to assoicate with 
    // the g2Variable, depending on its identAtts
    // .....
    ExternalDataPoint dataPoint = new ExternalDataPoint(identAtts, g2Variable);
    externalDataPointsTable.put(g2Variable, dataPoint);
    return dataPoint;
  }

  // Implement DataServiceListener, which provides all DataService callbacks

  /**
   * setData is called by G2 when a value has been set on a Gsi Variable using the SET action.
   */
  @Override
  public void setData(DataServiceEvent e) {
    GsiDataService g2Var = e.getDataItem();
    System.out.println("setData being called for " + e.getDataItem() +
		       " set value is " +e.getValue());
    try {
      ExternalDataPoint dataPoint = (ExternalDataPoint)externalDataPointsTable.get(g2Var);
      dataPoint.setExternalValue(e.getValue());
      dataPoint.updateG2();  // make sure that G2 reflects the new external value
    } catch (G2AccessException E) {
      System.out.println("During setData ");
      E.printStackTrace();
    }
  }

  /**
   * getData is called by G2 when it requires a new value from the external system for a Gsi Variable.
   */
  @Override
  public void getData(DataServiceEvent e) {
    GsiDataService g2Var = e.getDataItem();
    //System.out.println("getData being called for " + e.getDataItem());
    try {
      ExternalDataPoint dataPoint = (ExternalDataPoint)externalDataPointsTable.get(g2Var);
      dataPoint.updateG2();
    } catch (G2AccessException E) {
      System.out.println("During getData ");
      E.printStackTrace();
    }
  }

  /**
   * variableRegistration is called when a Variable in G2 requires servicing from a DataService.
   */
  @Override
  public void variableRegistration(DataServiceEvent e) {
    GsiDataService g2Var = e.getDataItem();
    System.out.println("In variableRegistration for " + g2Var);
    Object[] identifyingAttributes = e.getIdentifingAttributes();
    for (int i = 0; i<identifyingAttributes.length; i++) 
      System.out.println("Identifying Attribute " + i + " = " + identifyingAttributes[i]);

    ExternalDataPoint dataPoint = getExternalDataPointFromIdentifingAttributes(identifyingAttributes, g2Var);
    try {
      dataPoint.updateG2();  // Must update G2 with the external variable value on registration
                             // to ensure that G2 knows that this variable has a value and will update
                             // it (via getData)
    } catch (G2AccessException E) {
      System.out.println("During variableRegistration ");
      E.printStackTrace();
    } 
    
  }

  /**
   * variableDeregistration is called by G2 when the variable (previously registered on a DataService)
   * is no longer available (disabled, deleted, or G2 reset/restarted).
   */
  @Override
  public void variableDeregistration(DataServiceEvent e) {
    System.out.println("Variable Deregistration of " + e.getDataItem());
    GsiDataService g2Var = e.getDataItem();  
    ExternalDataPoint dataPoint = (ExternalDataPoint)externalDataPointsTable.remove(g2Var);
    if (dataPoint != null)
      dataPoint.setDeregistered();
  }

  // End Implement DataServiceListener

  private static SecureRandom random = new SecureRandom();

  // Inner class to simulate an ExternalDataPoint

  class ExternalDataPoint {

    int    status = 1;
    Object[] identAtts = null;
    int externalUpdateRate = 1; // 100ms
    long lastUpdate = 0;
    GsiDataService g2Variable = null;
    Object lastValue = null;
    
    public ExternalDataPoint(Object[] identAtts, GsiDataService g2Variable) {
      this.identAtts = identAtts;
      this.g2Variable = g2Variable;
      // We can set the externalUpdateRate from the first IdentAtt
      if ((identAtts.length>0) && (identAtts[0].getClass() == Integer.class)) {
	externalUpdateRate = (int)((Integer)identAtts[0]).intValue();
	System.out.println("externalUpdateRate = " + externalUpdateRate);
      }
    }

    public void setDeregistered() {
      g2Variable = null;  // + Any thing else to the Extrenal Data point.
    }
    
    public int getExternalUpdateRate() {
	return externalUpdateRate;
    }

    public long getLastUpdate() {
      return lastUpdate;
    }

    public void setLastUpdate(long lastUpdate) {
      this.lastUpdate = lastUpdate;
    }

    public Object getExternalValue() {
      if (g2Variable == null) {
    	  return null;
      }
      // Here we would fetch the new value
      if (g2Variable instanceof SymbolicVariable) 
	lastValue = Symbol.intern("DATA-SERVER-SYMBOL");
      else if (g2Variable instanceof TextVariable) 
	lastValue = "Current millis " + System.currentTimeMillis();
      else if (g2Variable instanceof LogicalVariable)
	lastValue = (random.nextDouble() > 0.5 ? Boolean.TRUE : Boolean.FALSE);
      else if (g2Variable instanceof IntegerVariable)
	lastValue = (int)(random.nextDouble()*10);
      else // quantity, float or integer
	lastValue = random.nextDouble(); // simulation, just return random value
      return lastValue;
    }

    public void setExternalValue(Object value) {
      // simulation do nothing !
      // Must work out what value type is
      lastValue = value;
    }

    public int getExternalStatus() {
      // Here we would fetch the internal status
      return (int)(random.nextDouble() * 10); // simulation, just return a random value
    }

    public void updateG2() throws G2AccessException {
       if (g2Variable == null){
    	   return;
       }
      if (lastValue == null) {
    	  getExternalValue();
      }
      g2Variable.setGsiVariableValue(lastValue, getExternalStatus());
    }

  }

  // Inner class to schedule unsolicited updates back to registered variables
  class Scheduler extends Thread {

    @Override
    public void run() {
      Vector pointsToUpdate = new Vector(10);
      for (;;) {
	// Collect all External Data points to update
	long currentTime = System.currentTimeMillis();
	for (Enumeration e = externalDataPointsTable.keys(); e.hasMoreElements();) {

	  GsiDataService g2Variable = (GsiDataService)e.nextElement();
	  ExternalDataPoint dataPoint = (ExternalDataPoint)externalDataPointsTable.get(g2Variable);

	  if (dataPoint.getExternalUpdateRate() > 0 && // 0 means no unsolicated updates
	      ((currentTime - dataPoint.getLastUpdate()) > 
	       (dataPoint.getExternalUpdateRate() * 100))) { //100ms
	    g2Variable.storeGsiVariableStatus(dataPoint.getExternalStatus());
	    g2Variable.storeGsiVariableValue(dataPoint.getExternalValue());
	    pointsToUpdate.addElement(g2Variable);
	    dataPoint.setLastUpdate(currentTime);
	  }
	}
	// Return the value for these variables in one batch
	GsiDataService[] pointsToUpdateArray = new GsiDataService[pointsToUpdate.size()];
	//System.out.println("Sending " + pointsToUpdateArray.length + " var updates to G2 ");
	pointsToUpdate.copyInto(pointsToUpdateArray);
	try {
	  dataService.returnValues(pointsToUpdateArray);
	} catch (G2CommunicationException E) {
	  System.out.println("In scheduler returnValues ");
	  E.printStackTrace();
	} catch (G2AccessException E) {
	  System.out.println("In scheduler returnValues ");
	  E.printStackTrace();
	  }
	pointsToUpdate.removeAllElements();

	try {
	  Thread.sleep(100);
	} catch (Exception e) {}
      }
    }
  }

  /**
   * Main method
   */
  public static void main(String args[])
  {
    // If a Java class wishes to listen for unsolicited connections from a G2 Server
    // Then it must follow the following steps
    
    // 1. Initialize the G2 Gateway Class
    G2Gateway.initialize(new String[] {"-listenerport", "22044"});
    
    try {
    // 2. Set up a connection factory deal with unsolicited G2 connections
    G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory() {
      /**
       * To support G2ConnectionHandlerFactory, called when an unsolicated connection
       * is detected. It is the responsibility of this method to return a G2Connection 
       * that will handle the new connection.
       */
      @Override
      public G2Connection createG2Connection(String connection_data)
	{  
	  G2Gateway new_gateway = new G2Gateway();
	  ExampleDataService egw = new ExampleDataService(new_gateway);
	  return new_gateway;
	} });
    } catch (Error e) { System.out.println("Caught error"); }

    // 3. Startup the G2 gateway interface, allowing network connections and communication
    //    This is done after the connection handle factory is setup, just is case a
    //    G2 has already initiated an unsolicited connection
    G2Gateway.startup();

    System.out.println("ExampleDataService...started...waiting...");

  }

}
