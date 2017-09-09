/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ListenerDemoApplet.java
 *
 */
package com.gensym.demos.listenerdemo;

import java.applet.Applet;
import java.awt.Label;
import java.awt.TextArea;
import java.awt.Panel;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.util.StringTokenizer;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.AttributeDenotation;
import com.gensym.demos.democlasses.Planet;

/** Demo applet to illlustrate listening to attribute changes in G2 */

public class ListenerDemoApplet extends Applet implements ItemListener{
  private Thermometer[] thermometer;
  private Label[] label;
  private TwAccess g2Connection;
  private String host;
  private String port;
  private static final Symbol PLANET_ = Symbol.intern("PLANET");
  private int numberOfPlanets = -1;
  private Planet[] planet;
  private double[] temperature;
  private double[] threshold;
  private Thread alarmThread;
  private int countOfAlarms = 0;
  private boolean[] planetInAlarm;
  private static final String delimeter="|";
  private boolean initComplete = false;
  public ListenerDemoApplet () {
  }
   
  @Override
  public String[][] getParameterInfo() {
    String[][] pinfo =
    {{"HOST",          "string",  "machine name for connection"},
     {"PORT",          "integer", "port number for connection"},
     {"PLANET-NAMES",  "string",  "delimited list of planets to monitor"}};
    return pinfo;
  }
     
  @Override
  public void init () {
    if (numberOfPlanets != -1) return;
    TextArea ta = new TextArea("To run the demo, choose Demo > Start Temperature Changes from the menu bar in G2.  \n\nThis applet displays the current temperature for planets in the G2 application.  Changes to the temperature attribute of each planet are reflected in the thermometer for the planet.  When the temperature of a planet goes over its threshold, an alarm beeps until the temperature falls below its threshold.  \n\nTo quit, choose Demo > Stop Temperature Changes from the menu bar in G2, then choose Applet > Quit.\n\nThis demo launches G2 SEQUOIA_REQUIRED_G2_VERSION and loads SQ-DEMOS.KB on port 1234.  To start G2, the demo uses a command line similar to the following: \n\n     g2 -tcpport 1234 -kb <path>\\SQ-DEMOS.KB -name Sequoia-Demo \n\nHere is the specific Java code that interacts with G2:\n\nSubscribe as a listener for changes to the temperature attribute of a planet:\n   planet[i].addItemListener(this), \n\nImplement the interface com.gensym.util.ItemListener:\n   (a) public class ListenerDemoApplet extends Applet implements \n         ItemListener{...}\n   (b) public void itemModified(ItemEvent e){\n\tPlanet item = (Planet)e.getItem();\n\tint i = getPlanetIndex(item);\n\ttemperature[i] = ((Double)e.getNewValue()).doubleValue();\n\tthermometer[i].setTemperature(temperature[i]);\n\tif (isActive()){\n\t\tupdateLabel(label[i], temperature[i]);\n\t\tcheckForAlarm(temperature[i], i);\n\t}\n}\n\nSee com.gensym.demos.ListenerDemoApplet.java for source code.", 6, 60, TextArea.SCROLLBARS_VERTICAL_ONLY);
    ta.setEditable(false);
    add(ta);
    host = getParameter ("HOST");
    port = getParameter ("PORT");
    try {
      if ((host != null) && (port != null)) {
	//Establish a connection to G2
	g2Connection = TwGateway.openConnection(host, port);
	// The following call will fail if the G2 is secure.
	g2Connection.login();

	String planetNames = getParameter("PLANET-NAMES");
	StringTokenizer tokenizer = new StringTokenizer(planetNames, delimeter);
	numberOfPlanets = tokenizer.countTokens();
	planet = new Planet[numberOfPlanets];
	thermometer = new Thermometer[numberOfPlanets];
	label = new Label[numberOfPlanets];
	temperature = new double[numberOfPlanets];
	threshold = new double[numberOfPlanets];
	planetInAlarm = new boolean[numberOfPlanets];
	Symbol planetName_;
	Panel panel;
	Panel labelPanel;
	for (int i=0; i<numberOfPlanets; i++){
	  panel = new Panel();
	  labelPanel = new Panel();
	  panel.setLayout(new BorderLayout(0, 20));
	  labelPanel.setLayout(new GridLayout(2, 1));
	  planetName_ = Symbol.intern(tokenizer.nextToken());
	  //Obtain a stub for G2 instance and cast to appropriate interface
	  planet[i] = (Planet)g2Connection.getUniqueNamedItem(PLANET_, planetName_);
	  //Use accessor methods to get attribute values
	  temperature[i] = planet[i].getTemperature().doubleValue();
	  thermometer[i] = new Thermometer();
	  thermometer[i].setLabel(planetName_.toString());
	  label[i] = new Label("");
	  panel.add(thermometer[i], "Center");
	  panel.add(labelPanel, "South");
	  labelPanel.add(label[i]);
	  add(panel);
	  threshold[i] = planet[i].getTemperatureThreshold().doubleValue();
	  labelPanel.add(new Label("Threshold: "+threshold[i]));
	  thermometer[i].setTemperature(temperature[i]);
	  //Add this applet as a listener for changes to the temperature attribute of a planet
	  planet[i].addItemListener(this);
	}
      }
    } catch (Exception e) {
      e.printStackTrace();
      if ((e instanceof G2AccessException)|
	  (e instanceof ConnectionTimedOutException)){
	System.out.println("G2 SEQUOIA_REQUIRED_G2_VERSION or later needs to be running SQ-DEMOS.KB on port "+port);
	g2Connection = null;
      }
      return;
    }
    validate();
    setVisible(true);
    initComplete = true;
  }

  @Override
  public void start(){
    for (int i=0; i<numberOfPlanets; i++){
      updateLabel(label[i], temperature[i]);
      checkForAlarm(temperature[i], i);
    }
  }

  @Override
  public void stop(){
    if (alarmThread != null) alarmThread.suspend();
    for (int i=0; i<numberOfPlanets; i++) planetInAlarm[i] = false;
    countOfAlarms = 0;
  }

  public void updateLabel(Label label, double temperature){
    label.setText("Temperature: "+temperature);
  }

  private synchronized void checkForAlarm(double temperature, int i){
    if (temperature > threshold[i]) {
      if (!planetInAlarm[i]){
	planetInAlarm[i] = true;
	countOfAlarms = countOfAlarms + 1;
	if (alarmThread == null){
	  Alarm alarm = new Alarm(this); 
	  alarmThread = new Thread(alarm);
	  alarmThread.start();
	}
	else if (countOfAlarms == 1){
	  alarmThread.resume();
	}
      }
    }
    else {
      if (planetInAlarm[i]){
	planetInAlarm[i] = false;
	countOfAlarms = countOfAlarms - 1;
      }
      if ((alarmThread != null)&&(countOfAlarms == 0)) alarmThread.suspend();
    }
  }

  private int getPlanetIndex(Planet p){
    for (int i=0; i<planet.length; i++){
      if (planet[i].equals(p)) return i;
    }
    return -1;
  }

  private static final Symbol TEMPERATURE_ = Symbol.intern ("TEMPERATURE");
  private static final Symbol NAME_ = Symbol.intern ("NAME");

  //Since this applet has subscribed as a com.gensym.util.ItemListener for each of the planets, this method is called when the temperature attribute of the planet in G2 changes
  @Override
  public void itemModified(ItemEvent e){
    if (!initComplete) return;
    Planet item = (Planet)e.getItem();
    int i = getPlanetIndex(item);
    Structure attr = (Structure)e.getDenotation().firstElement();
    if (TEMPERATURE_.equals(attr.getAttributeValue(NAME_, null))) {
      temperature[i] = ((Number)e.getNewValue()).doubleValue();
      thermometer[i].setTemperature(temperature[i]);
      if (isActive()){
	updateLabel(label[i], temperature[i]);
	checkForAlarm(temperature[i], i);
      }
    }
    // else ignore it.
  }

  @Override
  public void itemDeleted(ItemEvent e) {
  }

  @Override
  public void receivedInitialValues(ItemEvent e) {
  }

}
