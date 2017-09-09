/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 InternationalizationDemo.java
 *
 */
package com.gensym.demos.internationalizationdemo;

import com.gensym.demos.Demo;
import com.gensym.demos.DemoShell;
import com.gensym.demos.ErrorDialog;
import com.gensym.demos.democlasses.Planet;
import java.awt.*;
import java.awt.event.*;
import java.util.Locale;
import java.util.MissingResourceException;
import com.gensym.message.Resource;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.util.Symbol;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.MessageDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.StandardDialog;

/** Demo class to demonstrate internationlization */
public class InternationalizationDemo implements Demo, StandardDialogClient{
  private String host;
  private String port;
  private Symbol planetName_;
  private DemoShell demoShell;
  private TwAccess g2Connection;
  private Planet planet;
  private static final Symbol PLANET__ = Symbol.intern("PLANET");
  private Resource bundle;
  private Locale english = new Locale("en", "US"); //Create English Locale
  private Locale german = new Locale("de", "DE"); //Create German Locale
  private CheckboxMenuItem englishMenu;
  private CheckboxMenuItem germanMenu;

  @Override
  public void runDemo(Frame frame){
    try{
      if (g2Connection == null) {
	//Establish a connection to G2
	g2Connection = TwGateway.openConnection(host, port);
	// The following call will fail if the G2 is secure.
	g2Connection.login();
      }

      //Obtain a stub for the G2 instance and cast to appropriate interface
      planet =(Planet)g2Connection.getUniqueNamedItem(PLANET__, planetName_);
      //Use accessor method in interface to get attribute value
      int numberOfMoons = planet.getNumberOfMoons();
      String[] initialValues = new String[]{Integer.toString(numberOfMoons)};
      String textboxLabel = null;
      if (bundle != null){
      //localize labels
	try{
	  textboxLabel = bundle.getString("k-NumberOfMoons");
	}catch(MissingResourceException e){
	  ErrorDialog erDlg = new ErrorDialog(e, frame, this, "Error", "Missing resource error.  Dialog text will default to english.");
	  textboxLabel = new String("Number of Moons:");
	}
      }
      String[] textFieldLabels = new String[]{textboxLabel};
      frame.setVisible(true);
      new InputDialog(frame, planetName_.getPrintValue(), true, textFieldLabels, initialValues, (StandardDialogClient)this).setVisible (true);
    } catch (G2AccessException e){
	ErrorDialog errDlg = new ErrorDialog(e, frame, null, "Error", "G2 SEQUOIA_REQUIRED_G2_VERSION or later needs to be running SQ-DEMOS.KB on port "+port+". \n\nError: "+e.getMessage());
	g2Connection = null;
    }
  }

  @Override
  public void dialogDismissed (StandardDialog d, int code) {
    if (d instanceof MessageDialog) return;
    
    InputDialog id = (InputDialog)d;
    if (id.wasCancelled ()) return;

    String[] results = id.getResults ();
    int numberOfMoons = Integer.parseInt(results[0]);
    try{
      //Use accessor method in interface to set attribute value
      planet.setNumberOfMoons(numberOfMoons);
    } catch (Exception e){
       new ErrorDialog(e, (Frame)demoShell, null, "Error", "Lost connection.  Restart G2 SEQUOIA_REQUIRED_G2_VERSION or later with SQ-DEMOS.KB on port "+port);
       g2Connection = null;
    }
  }

  public void addLanguageMenu(){
    MenuBar mb = demoShell.getMenuBar();
    Menu languageMenu = new Menu("Language");
    mb.add(languageMenu);
    englishMenu = new CheckboxMenuItem("English", true);
    languageMenu.add(englishMenu);
    ItemListener l = new ItemAdapter();
    englishMenu.addItemListener(l);
    germanMenu = new CheckboxMenuItem("German", false);
    languageMenu.add(germanMenu);
    germanMenu.addItemListener(l);
  }

  class ItemAdapter implements ItemListener{
      @Override
      public void itemStateChanged(ItemEvent e){
	CheckboxMenuItem cb = (CheckboxMenuItem)e.getSource();
	if (e.getStateChange() == e.SELECTED){
	  if (cb.equals(germanMenu)){
	    //set default Locale to German
	    Resource.setDefaultLocale(german);
	    englishMenu.setState(false);
	  }
	  else{
	    //set Default Locale to English
	    Resource.setDefaultLocale(english);
	    germanMenu.setState(false);
	  }
	  try{
	    //get Resource for current Locale
	    bundle = Resource.getBundle("com/gensym/demos/internationalizationdemo/InternationalizationDemoResource");
	  }catch(MissingResourceException mre){
	    new ErrorDialog(mre, (Frame)demoShell, InternationalizationDemo.this, "Error", "Missing resource error.  Can't find property file for "+mre.getClassName());
	  }
	}
	else{
	  cb.setState(true);
	}
      }
  }

  public static void main(String[] args){
    if (args.length != 3) {
      System.err.println ("Usage: java com.gensym.demos.internationalizationdemo.InternationalizationDemo host port planetName");
      System.exit (2);
    }
    InternationalizationDemo demo = new InternationalizationDemo();
    demo.host = args[0];
    demo.port = args[1];
    demo.planetName_ = Symbol.intern(args[2]);
    String msg = new String("To run the demo, choose a language from the Language menu, then choose File > Run Demo. Repeat for each language.  \n\nYou will see a dialog with a single text box for changing the number of moons of the planet named FOOBAR, localized for the chosen language.  The localization is done in Java.  \n\nEdit the value in the dialog and click OK to see the value change in G2.  \n\nThis demo is the same as com.gensym.demos.demo1.Demo1 except that the labels on the dialog are localized.  \n\nTo quit the demo, choose File > Exit.  \n\nThis demo launches G2 SEQUOIA_REQUIRED_G2_VERSION and loads SQ-DEMOS.KB on port "+demo.port+". To start G2, the demo uses a command line similar to the following: \n\n     g2 -tcpport 1234 -kb <path>\\SQ-DEMOS.KB -name Sequoia-Demo \n\nHere is the specific Java code that interacts with G2:\n\nCreate a Locale:\n     Locale english = new Locale(\"en\", \"US\");\n\nSet the default locale:\n     Resource.setDefaultLocale(english);\n\nGet the Resource for the current Locale:\n     bundle = Resource.getBundle(\"InternationalizationDemoResource\");\n\nLocalize text:\n     bundle.getString(\"NumberOfMoons\");\n\nFor complete demo source code see com.gensym.demos.internationalizationdemo.InternationalizationDemo.java");
    demo.demoShell = new DemoShell("InternationalizationDemo", msg, (Demo)demo, "InternationalizationDemo.java");
    demo.addLanguageMenu();
    //start with English Locale
    Locale.setDefault(demo.english);
    try{
      demo.bundle = Resource.getBundle("com.gensym.demos.internationalizationdemo.InternationalizationDemoResource");
    }catch(MissingResourceException mre){
      ErrorDialog erDlg = new ErrorDialog(mre, (Frame)demo.demoShell, demo, "Error", "Missing resource error.  Can't find property file for "+mre.getClassName());
    }
    demo.demoShell.setSize(600, 400);
    demo.demoShell.setVisible(true);
  }

}

