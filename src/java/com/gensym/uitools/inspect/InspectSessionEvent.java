package com.gensym.uitools.inspect;

import java.util.EventObject;
import com.gensym.util.Symbol;
import java.util.Vector;

public class InspectSessionEvent extends EventObject
{
  private Symbol status;
  private int itemsToExamine, numberOfItemsExaminedSoFar,numberOfItemsFound;
  private Vector newItemsFound;
  private Object server;
  
  public InspectSessionEvent(InspectSession source,
			     Symbol status,
			     int itemsToExamine,
			     int numberOfItemsExaminedSoFar,
			     int numberOfItemsFound,
			     Vector newItemsFound,
			     Object server)
  {
    super(source);
    this.status = status;
    this.itemsToExamine = itemsToExamine;
    this.numberOfItemsExaminedSoFar = numberOfItemsExaminedSoFar;
    this.numberOfItemsFound = numberOfItemsFound;
    this.newItemsFound = newItemsFound;
    this.server = server;
  }

  public Symbol getStatus()
  {
    return status;
  }

  public int getItemsToExamine()
  {
    return itemsToExamine;
  }

  public int getNumberOfItemsExaminedSoFar(){
      return numberOfItemsExaminedSoFar;
  }

  public int getNumberOfItemsFound(){
      return numberOfItemsFound;
  }

  public Vector getNewItemsFound(){
      return newItemsFound;
  }

  public Object getServer()
  {
    return server;
  }
  
}
