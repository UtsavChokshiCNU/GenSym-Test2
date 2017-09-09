/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 UiApplication.java
 *
 */
package com.gensym.core;

import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Rectangle;
import java.util.Hashtable;

/**
 * A Class that can be used as the parent of all User Interface applications.
 * It provides support for getting the Frame (or the current Frame of a 
 * multiple Frame application) and handling of command-line options.
 */
public abstract class UiApplication extends com.gensym.core.GensymApplication {

  private Hashtable menuFactories = new Hashtable();
  private Hashtable toolBarFactories = new Hashtable();  
  private MenuFactory defaultMenuFactory;
  private ToolBarFactory defaultToolBarFactory;
  private static boolean isMultipleFrames;
  private static volatile Rectangle stdBounds;

  private static volatile Frame currentOrOnlyFrame;
  private static volatile String title = null;
  private static volatile String geometry = null;

  /**
   * Creates a UIApplication
   */
  protected UiApplication (String[] commandLine, boolean isMultipleFrames) {
    super (commandLine);
    initBounds();
    this.isMultipleFrames = isMultipleFrames;
    handleUICommandLineArguments (commandLineArguments);
  }

  private void initBounds() {
    if (stdBounds != null) {
      throw new RuntimeException ("Only one UIApplication object may be created");
    } else {
      synchronized (UiApplication.class) {
        if (stdBounds == null) {
          stdBounds = new Rectangle(0, 0, 900, 700);
        } else {
          throw new RuntimeException ("Only one UIApplication object may be created");
        }
      }
    } 
  }

  /**
   * Indicates whether this application supports multiple Frames
   * @return true if this application opens multiple Frames, false otherwise
   */
  public static boolean isMultipleFrameApplication () {
    return isMultipleFrames;
  }

  /**
   * This sets the current Frame (which will be returned by getCurrentFrame).
   * Subclasses that support multiple Frames may use this.
   * @param frame the current Frame
   */
  protected static void setCurrentFrame (Frame frame) {
    currentOrOnlyFrame = frame;
  }

  /**
   * Returns the current Frame of the application.
   * This can be used in the presentation of dialogs etc.
   * @return the current Frame of this UIApplication
   */
  public static Frame getCurrentFrame () {
    return currentOrOnlyFrame;
  }

  private static void handleUICommandLineArguments (CmdLineArgHandler commandLineArguments) {
    title = commandLineArguments.getOptionValue ("-title");
    geometry = commandLineArguments.getOptionValue ("-geometry");
  }

  /**
   * Modifies the bounds of the Frame to fit into the
   * specified geometry.
   * @param frame the Frame to resize
   * @param geometry the geometry specified in the form w x h + x + y
   */
  protected static void setBoundsForFrame(Frame frame, String geometry) {
    frame.setBounds(parseBounds(geometry));
  }

  /**
   * Returns the title string, if one was requested in the
   * command line passed to the constructor.
   * @return the requested title for the application Frame
   */
  public static String getTitleInformation () {
    return title;
  }

  /**
   * Returns the requested geometry. If no geometry was requested
   * on the command line, null is returned
   * @return a String specifying the desired bounds for the
   *   application Frame
   */
  public static String getGeometryInformation () {
    return geometry;
  }

  /**
   * Parses standard X argument for geometry. It takes a
   * String of the form "widthxheight[+-]{-}x[+-]{-}y" and returns
   * the bounds specifed. The x and y components are the offsets
   * from the edges of the screen. A positive x or y indicates a
   * margin on the left or top and a negative y indicates a margin
   * on the bottom or right. If any of the components are missing,
   * the corresponding component of the default geometry
   * 900x700+0+0 is used
   * @param optn a String of the form wxh+x+y
   * @return a Rectangle outlining the desired bounds
   */
  protected static Rectangle parseBounds (String optn) {
    int x, y, width, height;
    if (optn == null || optn.equals (""))
      return stdBounds;
    int xIndex  = optn.indexOf ('x');
    int ppIndex = optn.indexOf ('+');
    int pmIndex = optn.indexOf ('-');
    int pIndex  = (ppIndex*pmIndex >= 0 ?
		   Math.min (ppIndex, pmIndex) : Math.max (ppIndex, pmIndex));
    
    if (xIndex < 0) {
      if (pIndex > 0)
	width = Integer.parseInt (optn.substring (0, pIndex));
      else
	width = stdBounds.width;
      height = stdBounds.height;
    } else {
      if (xIndex != 0)
	width = Integer.parseInt (optn.substring (0, xIndex));
      else
	width = stdBounds.width;
      if (pIndex < 0)
	height= Integer.parseInt (optn.substring (xIndex + 1));
      else
	height = Integer.parseInt (optn.substring (xIndex + 1, pIndex));
    }
    
    if (pIndex < 0) {
      x = 0;
      y = 0;
    } else {
      boolean pxNegOffset = (pIndex == pmIndex);
      boolean pyNegOffset;
      int pyIndex= optn.indexOf ('+', pIndex + 2);
      if (pyIndex < 0) {
	pyIndex = optn.indexOf ('-', pIndex + 2);
	pyNegOffset = (pyIndex > 0);
      } else
	pyNegOffset = false;
      pIndex++;
      if (pyIndex < 0) {
	x = Integer.parseInt (optn.substring (pIndex));
	y = 0;
      } else {
	x = Integer.parseInt (optn.substring (pIndex, pyIndex));
	pyIndex++;
	y = Integer.parseInt (optn.substring (pyIndex));
      }
      if (pxNegOffset || pyNegOffset) {
	Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
	if (pxNegOffset) {
		x = -x + screenSize.width - width;
	}
	if (pyNegOffset) {
		y = -y + screenSize.height - height;
	}
      }
    }
    return new Rectangle (x, y, width, height);
  }

  /**
   * Sets the toolbar factory to be used for generating toolbar for this application
   * @param factoryKey the key object to be used for storing and retrieving the given factory
   */
  public void setToolBarFactory(Object factoryKey, ToolBarFactory factory) {
    if (factoryKey != null)
      toolBarFactories.put(factoryKey, factory);
    else
      defaultToolBarFactory = factory;    
  }
  
  /**
   * @return the ToolBarFactory for the given factoryKey.
   */
  public ToolBarFactory getToolBarFactory(Object factoryKey) {
    ToolBarFactory factory = null;
    if (factoryKey != null)
      factory = (ToolBarFactory)toolBarFactories.get(factoryKey);
    if (factory == null)
      factory = defaultToolBarFactory;
    return factory;
  }

  /**
   * Sets the menu factory to be used for generating menu bars for this application
   * @param factoryKey the key object to be used for storing and retrieving the given factory
   */
  public void setMenuFactory(Object factoryKey, MenuFactory factory) {
    if (factoryKey != null)
      menuFactories.put(factoryKey, factory);
    else
      defaultMenuFactory = factory;    
  }
  
  /**
   * @return the MenuFactory for the given factoryKey.
   */
  public MenuFactory getMenuFactory(Object factoryKey) {
    MenuFactory factory = null;
    if (factoryKey != null)
      factory = (MenuFactory)menuFactories.get(factoryKey);
    if (factory == null)
      factory = defaultMenuFactory;
    return factory;
  }
    
}
