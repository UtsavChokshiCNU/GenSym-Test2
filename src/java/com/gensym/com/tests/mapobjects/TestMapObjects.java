package com.gensym.com.tests.mapobjects;

import com.gensym.com.beans.mapobjects.*;

import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.Variant;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.ActiveXTraceLevels;
import com.gensym.com.ActiveXTraceTool;
import com.gensym.com.ActiveXException;
import com.gensym.com.NativeMethodBroker;

import java.lang.InterruptedException;

import java.awt.Frame;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.*;

import com.gensym.com.ActiveXTraceTool;

import java.util.Date;

public class TestMapObjects implements WindowListener, ActiveXTraceLevels,
                                     ActiveXRuntimeConstants
{
  private Frame f; 
  private MapobjectsDataconnection dc; 
  private MapobjectsMap map;
  private MapobjectsMaplayer layer;
  private String dbLocation;
  private String dataset;
  private Color backColor;

  public TestMapObjects(String dbLocation, String dataset)
    throws ActiveXException
  {
    this.dbLocation = dbLocation;
    this.dataset = dataset;
    
    // Create a new map
    map =  new MapobjectsMap();        
           
    // Create a Data Connection
    dc=new MapobjectsDataconnection();
      
    // Create a layer
    layer = new MapobjectsMaplayer();
  }    
   
  public void activate() throws ActiveXException
  {
    f =  new Frame();
    // Add the map to the window 
    f.add(map);
    f.setSize(new Dimension(750,450));
    f.addWindowListener(this);
    
    // Show the window containing the map
    f.show();
    
    // Connect to the database
    dc.setAxDatabase(dbLocation);
    dc.Connect();
    
    if (dc.getAxConnected()) {
      // Find the dataset
      GeoDataset gds=dc.FindGeoDataset(dataset);
      layer.setAxGeoDataset(gds);
      
      // Add layer to the map
      Layers layers=map.getAxLayers();
      layers.Add(layer);
      map.Refresh();
    }
    else {
      System.out.println("Server error = " + dc.getAxConnectError());
    }
  }

  public void delete()
  {
    try {
      // Delete the ActiveXComponents
      dc.delete();
      layer.delete();
      map.delete();
    }
    catch (ActiveXException e)
    {
      e.printStackTrace();
      System.out.println("Failure : " + e);
    }
  }

  public static void main(String[] args) {
    /*
    ActiveXTraceTool tool = new ActiveXTraceTool();        
    tool.setAxTraceLevel((short) 40);
    tool.setLogToStdout(true);
    */
    
    TestMapObjects test;
    try {
      if (args.length == 0)
        test = new TestMapObjects("D:\\ESRI\\MapObjects\\Samples\\Data\\World",
        "country");
      else test = new TestMapObjects(args[0], args[1]);
      test.activate();
    }
    catch (ActiveXException e)
    {
      System.out.println("Failure = " + e);
      e.printStackTrace();
    }
  }

  @Override
  public void windowOpened(WindowEvent e) {
  }

  @Override
  public void windowClosing(WindowEvent e) {
    delete();
    System.exit(0);
  }

  @Override
  public  void windowClosed(WindowEvent e) {
    delete();
    System.exit(0);
  }

  @Override
  public void windowIconified(WindowEvent e) {
  }

  @Override
  public  void windowDeiconified(WindowEvent e) {
  }

  @Override
  public  void windowActivated(WindowEvent e) {
  }

  @Override
  public void windowDeactivated(WindowEvent e) {
  }  
}

