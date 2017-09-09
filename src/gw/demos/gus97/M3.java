// M3 -- a very simple java example.

// package -- resides in the nameless package.

import java.lang.*;
import java.net.*;     // for URLs
import java.awt.*;     // For event handling.
import marimba.gui.*;
// import java.io.*;

public class M3 extends java.applet.Applet {

  GW gw;                      // Interface to G2
  Presentation presentation;  // Interface to UI

  void initPresentation()
  {
    PlayerPanel player;
    try {
      presentation 
	= Presentation.getPresentation(new URL(getDocumentBase(), "m3.gui"));
    } catch (MalformedURLException e) { 
      e.printStackTrace();
    }
    setLayout(new BorderLayout());
    add("Center", player = new PlayerPanel());
    player.setPresentation(presentation);
  }

  // We keep pointers into parts of the UI.
  CommandButtonWidget queryButton;  // Button he submits his request with.
  DropDownListBoxWidget menu;       // What the user wants.
  RichTextBoxWidget resultText;     // Were we put the result.

  void initWidgetGlobals(){
    menu = (DropDownListBoxWidget)presentation.getWidget("menu");
    queryButton = (CommandButtonWidget)presentation.getWidget("queryButton");
    resultText = (RichTextBoxWidget)presentation.getWidget("resultText");  
  }


  //
  // Initialize the Applet.
  //
  public void init() {
    // 1. Create an object to interface back to G2 with. 
    gw = new GW(getDocumentBase());
    // 2. Create our User Interface
    initPresentation();
    // 3. Initialize some pointers into that UI.
    initWidgetGlobals();
    menu.setValue(1); // Set a default choice in the menu.
  }

  //
  // Event Handling
  //
  public boolean handleEvent(Event evt) {

    // We customize only one event, i.e. the command button.
    if( evt.target instanceof CommandButtonWidget
	&& queryButton == (CommandButtonWidget)evt.target 
	&& Event.ACTION_EVENT == evt.id) { 

      // Ask G2, via the inteface, for some text.
      String result = gw.QueryText("m3/q3?V=" + menu.getText());
      // Display that.
      resultText.setText(result);
      // Indicate we handled the event.
      return true;
    } else {
      // Otherwise let the default behavior take care of it.
      return false;
    }
  }

}
