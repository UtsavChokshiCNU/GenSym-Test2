// package -- resides in the nameless package.

import java.lang.*;
import java.awt.*;
import java.net.*;
import marimba.gui.*;
import java.io.*;


/// An example of a temperature conversion applet.
/// The GUI for this applet is created with Bongo
/// and is stored in a filed called <b>temp.gui</b>.
/// @author Arthur van Hoff

public class MyApplet extends java.applet.Applet {
  Presentation presentation;
  PlayerPanel player;
  PlayerUtil util;

  GW gw;

  void initPresentation()
  {
    try {
      presentation 
	= Presentation.getPresentation(new URL(getDocumentBase(), "m1.gui"));
    } catch (MalformedURLException e) { 
      e.printStackTrace();
    }
    trace("PRESENTATION: " + presentation);
    setLayout(new BorderLayout());
    add("Center", player = new PlayerPanel());
    player.setPresentation(presentation);
    util = new PlayerUtil(player);
  }

  ///
  /// Tracing
  ///
  private boolean trace = true;
  void trace(String text) {
    if (trace) {
      System.out.println("MA:"+text);
    }
  }

  ///
  /// Initialize the applet
  ///
  public void init() {
    trace("Init");
    gw = new GW(getDocumentBase());
    initPresentation();
    
    trace("INIT DONE");
    initWidgetGlobals();
  }



  //
  // Event Handling
  //
  public boolean handleEvent(Event evt) {
    // Try various event handlers.
    return FC_tangle(evt)
      || ask_g2_tangle(evt)
      || super.handleEvent(evt);
  }




  //
  // The "Ask G2" tangle
  //
  RichTextBoxWidget resultText;
  CommandButtonWidget queryButton;

  void initWidgetGlobals(){
    resultText = (RichTextBoxWidget)presentation.getWidget("resultText");
    queryButton = (CommandButtonWidget)presentation.getWidget("queryButton");
  }

  // Event handler for this tangle.
  boolean ask_g2_tangle(Event evt){
    if( evt.target instanceof CommandButtonWidget
	&& queryButton == (CommandButtonWidget)evt.target 
	&& Event.ACTION_EVENT == evt.id) { 
      gw.QueryTuples("data/t1.tup");
      resultText.setText(gw.describeAllTuples());
      return true;
    }
    return false;
  }

  //
  // F <-> Celcius tangle.
  //
  boolean FC_tangle(Event evt){
    //    trace("FC_Tangle");
    if (evt.target instanceof Widget) {
      Widget w = (Widget)evt.target;
      String nm = w.getName();
      
      switch (evt.id) {
      case Event.SCROLL_LINE_UP:
      case Event.SCROLL_LINE_DOWN:
      case Event.SCROLL_PAGE_UP:
      case Event.SCROLL_PAGE_DOWN:
      case Event.SCROLL_ABSOLUTE:
	if ("slider-C".equals(nm)) {
	  int c = ((SliderWidget)w).getIntegerValue();
	  int f = c * 9 / 5 + 32;
	  util.setValue("value-C", new Integer(c));
	  util.setValue("value-F", new Integer(f));
	  util.setValue("slider-F", new Integer(f));
	  return true;
	}
	if ("slider-F".equals(nm)) {
	  int f = ((SliderWidget)w).getIntegerValue();
		    int c = (f - 32) * 5 / 9;
		    util.setValue("value-F", new Integer(f));
		    util.setValue("value-C", new Integer(c));
		    util.setValue("slider-C", new Integer(c));
		    return true;
	}
	break;
      }
    }
    return false;
  }
  
  
}
