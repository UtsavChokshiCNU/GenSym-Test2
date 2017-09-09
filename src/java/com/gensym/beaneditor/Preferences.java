package com.gensym.beaneditor;

import java.awt.Color;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.File;


public class Preferences extends Object
  implements java.io.Serializable
{
  Color sizingWidgetHandleColor = Color.white;
  Color sizingWidgetLineColor = Color.black;
  Color containerBackgroundColor = Color.lightGray;
  private boolean expertMode = false;
  private boolean customHookupsAllowed = false;
  private SyntaxType syntax = SyntaxType.JAVA;
  private ColorMap eventColorMapping = ColorMap.getDefaultMap();

  private int defaultContainerWidth = 450;
  private int defaultContainerHeight = 300;

  private FileNameVector defaultJars = new FileNameVector();

  static Preferences currentPreferences;

  static String defaultFileName;
  static String fileName;

  static {
      fileName = System.getProperty ("com.gensym.beaneditor.preferences", null);
      String homeDir = System.getProperty("user.home");
      String fName = "ComponentEditor.prefs";
      if (homeDir != null) defaultFileName = homeDir + File.separator + fName;
      else defaultFileName = fName;
  }


  static void establishPreferences()
  {
    if (fileName == null) fileName = defaultFileName;
    try{
      FileInputStream fis = new FileInputStream(fileName);
      ObjectInputStream ois = new ObjectInputStream(fis);
      Object prefs = ois.readObject();
      if (prefs instanceof Preferences)
	currentPreferences = (Preferences)prefs;
      else currentPreferences = new Preferences();
    }
    catch(Exception ex){
      // ignore all errors and just create a new prefs object
      currentPreferences = new Preferences();
    }
  }

  static void saveCurrentPreferences(){
    try{
      FileOutputStream fos = new FileOutputStream(fileName);
      ObjectOutputStream oos = new ObjectOutputStream(fos);
      oos.writeObject(currentPreferences);
    }
    catch(Exception ex){
      com.gensym.message.Trace.exception(ex);
      //should the user be bothered if their preferences can't be saved?
    }
  }

  public int getDefaultContainerWidth()
  {
    return defaultContainerWidth;
  }

  public void setDefaultContainerWidth(int w)
  {
    defaultContainerWidth = w;
  }

  public int getDefaultContainerHeight()
  {
    return defaultContainerHeight;
  }

  public void setDefaultContainerHeight(int h)
  {
    defaultContainerHeight = h;
  }

  public Color getSizingWidgetHandleColor()
  {
    return sizingWidgetHandleColor;
  }

  public void setSizingWidgetHandleColor(Color c)
  {
    sizingWidgetHandleColor = c;
  }

  public Color getSizingWidgetLineColor()
  {
    return sizingWidgetLineColor;
  }

  public void setSizingWidgetLineColor(Color c)
  {
    sizingWidgetLineColor = c;
  }

  public Color getContainerBackgroundColor()
  {
    return containerBackgroundColor;
  }

  public void setContainerBackgroundColor(Color c)
  {
    containerBackgroundColor = c;
  } 
  
  public boolean isExpertMode(){
    return expertMode;
  }

  public void setExpertMode(boolean expert){
    expertMode = expert;
  }

  public boolean isCustomHookupsAllowed(){
    return customHookupsAllowed;
  }

  public void setCustomHookupsAllowed(boolean customHookupsAllowed){
    this.customHookupsAllowed = customHookupsAllowed;
  }

  public SyntaxType getSyntax(){
    return syntax;
  }

  public void setSyntax(SyntaxType syntax){
    this.syntax = syntax;
  }

  public ColorMap getEventColorMapping(){
    return eventColorMapping;
  }

  public void setEventColorMapping(ColorMap map){
    eventColorMapping = map;
    ComponentEditor.updateConnectionColors();
  }
  
  public FileNameVector getDefaultJars(){
    return defaultJars;
  }

  public void setDefaultJars(FileNameVector jars){
    defaultJars = jars;
  }
 
}
