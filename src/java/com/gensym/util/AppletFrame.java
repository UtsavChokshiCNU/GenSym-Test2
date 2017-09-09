package com.gensym.util;

import java.awt.*;
import java.applet.*;


/**
 * AppletFrame can be used as a Frame to host an Applet class.
 * To use this class, write a public static void method in the
 * applet class that calls startApplet.
 *
 * @version 1.00 11/22/96
 */
public class AppletFrame extends Frame {

  private Applet clientApplet;

  /**
   * Creates a Frame to hold the Applet.
   * Calls init and start.
   * @param className the name of the applet class to instantiate
   * @param title the title for the Frame
   * @param args ??
   */
  public static void startApplet(String className,
				 String title,
				 int width,
				 int height)
  {
    Applet a = null;
    Dimension appletSize;
    try {
      // create an instance of your applet class
      a = (Applet) Class.forName(className).newInstance();
    } catch (ClassNotFoundException e) {
      System.err.print("Error: could not locate class " + className);
      System.err.println(". Quitting.");
      return;
    } catch (InstantiationException e) {
      System.err.println("Error: could not instantiate class " + className);
      return;
    } catch (IllegalAccessException e) {
      System.err.println("Error: Illegal Access Exception " + className);
      return;
    }

    // create new application frame window
    AppletFrame f = new AppletFrame(title);
    f.clientApplet = a;
  
    // add applet to frame window
    f.add("Center", a);
  
    // resize frame window to fit applet
    // assumes that the applet sets its own size
    // otherwise, you should set a specific size here.
    appletSize =  a.getSize();
    f.pack();
    f.setSize(width, height);  

    // show the window
    f.show();

    // initialize the applet
    a.init();
    a.start();
 
  
  }  // end startApplet()
  
  
  // constructor needed to pass window title to class Frame
  private AppletFrame(String name)
  {
    // call java.awt.Frame(String) constructor
    super(name);
  }

  // needed to allow window close
  @Override
  public boolean handleEvent(Event e)
  {
    if (e.id == Event.WINDOW_DESTROY)
      {
	// Be nice as we get out
	clientApplet.stop ();
	clientApplet.destroy ();
	System.exit(0);
	return true;
      }
       
    // it's good form to let the super class look at any 
    // unhandled events
    return super.handleEvent(e);

  }  // end handleEvent()

}   // end class AppletFrame
