package com.gensym.JMibParser;

import java.util.*;

//gensym imports
import com.gensym.util.*;

//Adventnet imports
import com.adventnet.snmp.mibs.MibOperations;
import com.adventnet.snmp.mibs.MibModule;
import com.adventnet.snmp.mibs.MibNode;
import com.adventnet.snmp.mibs.MibException;

public class ParseResult {
  //Symbols for overal structure to return:
  //Note that symbols need to be UPPER-CASE !!!!!! Otherwise G2 will have a problem recognizing them.
  static Symbol mibNotificationsS = Symbol.intern ("NOTIFICATIONS");
  static Symbol mibNotificationObjectsS = Symbol.intern ("MIB-NOTIFICATION-OBJECTS");
  static Symbol mibOtherObjectsS = Symbol.intern ("MIB-OTHER-OBJECTS");
  static Symbol mibNodesS = Symbol.intern ("MIB-NODES");
  static Symbol mibErrorS = Symbol.intern ("ERROR-TEXT");

  //Symbols for structure per node:
  static Symbol labelS = Symbol.intern ("LABEL");
  static Symbol statusS = Symbol.intern ("STATUS");
  static Symbol syntaxS = Symbol.intern ("SYNTAX");
  static Symbol descriptionS = Symbol.intern ("DESCRIPTION");
  static Symbol numberedOidS = Symbol.intern ("NUMBERED-OID");
  static Symbol namedOidS = Symbol.intern ("NAMED-OID");
  static Symbol mibObjectsS = Symbol.intern ("MIB-OBJECTS");

  //Sets to sort nodes:
  java.util.Set mibNotifications = new HashSet(); //contains instances of MibNode that are notifications
  java.util.Set mibNotificationsObjects = new HashSet(); //contains instances of MibNode that are objects used by notifications
  java.util.Set mibOtherObjects = new HashSet(); //contains instances of MibNode that are leafs and not used by any notifications
  java.util.Set mibNodes = new HashSet(); //contains instances of MibNode that are NOT leafs

  //Error-text:
  String mibErrorText = "OK";

  //AdventNet debug flag:
  public static boolean adventNetDebug = false;

  MibOperations mibops = new MibOperations(); //One that does the loading and parsing

  public ParseResult() {
  }


  /*
   * moduleNames - A space separated list of files.
   * searchPath - String specifying the search path, for multiple paths separate the paths by the pipe (|)
          symbol.
   */
  public Structure loadAndParseMib(String moduleName, String searchPath){
    String result = "OK";


    mibops.setDebug(ParseResult.adventNetDebug);
    if (ParseResult.adventNetDebug) {
    	G2JavaLog.log(G2JavaLog.BRIDGE_IO, "The debug-flag for AdventNet-MibOperations is turned ON. To avoid these messages, set the bridge-debug-level to 6 or lower.");
    }
    mibops.setMibPath(searchPath);
    try{
      //mibops.loadMibModule("RFC1213-MIB");
      //mibops.loadMibModule("SNMPv2-TC");
      //mibops.loadMibModule("SNMPv2-SMI");
      G2JavaLog.log(G2JavaLog.BRIDGE_IO, "About to load " + moduleName);
      MibModule mibModule = mibops.loadMibModule(moduleName);
      G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Load of " + moduleName + " completed.");
      //MibModule mibModule = mibops.getMibModule(moduleName);
      if (mibModule != null){
        G2JavaLog.log(G2JavaLog.BRIDGE_IO, "About to parse " + moduleName);
        this.parseMib(mibModule);
        G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Parsing of " + moduleName + " completed");
      }
      else {
        result = "Failed to obtain mib-module for " + moduleName;
        G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, result);
        this.mibErrorText = result;
      }

    }
    catch (MibException mibe){
      result = "Mib load failed because of a mib-parsing problem: \n"+mibe.toString ();
      G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, result);
      this.mibErrorText = result;
    }
    catch (java.io.FileNotFoundException fnfe){
      result = "Mib load failed because the mib-file was not found: \n"+fnfe.toString ();
      G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, result);
      this.mibErrorText = result;
    }
    catch (java.io.IOException ioe){
      result = "Mib load failed because of some IOException: \n"+ioe.toString ();
      G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, result);
      this.mibErrorText = result;
    }

    Structure resultStruct = this.getResultStructure();
    return resultStruct;
  }

  public String parseMib (MibModule mibModule){
    String result = "OK";

    //Get Notifications:
    G2JavaLog.log(G2JavaLog.BRIDGE_IO, "About to collect all notifications and their objects");
    for (Enumeration nodes = mibModule.getDefinedNotifications(); nodes.hasMoreElements();) {
      MibNode node = (MibNode) nodes.nextElement();
      this.mibNotifications.add(node);

      //G2JavaLog.log(G2JavaLog.BRIDGE_IO, "The objects of notification" + node.getLabel() + " :" + node.getObjectNames());
      Vector objectNames = node.getObjects(); //if no trap objects, then returns null!
      if (objectNames != null) {
        Vector objects = mibops.getNodesFromNames(objectNames);
        for (Iterator i = objects.iterator(); i.hasNext(); ) {
          MibNode object = (MibNode) i.next();
          this.mibNotificationsObjects.add(object); //Set ensures uniqueness
          //System.out.println("Label:"+object.getLabel()+" - "+
            //                "OID:"+object.getNumberedOIDString());
        }//for
      }//if has trap variables
    }//for each notification

    //Get Other leafs and nodes:
    G2JavaLog.log(G2JavaLog.BRIDGE_IO, "About to collect all other leafs and nodes");
    for (Enumeration nodes = mibModule.getDefinedNodes(); nodes.hasMoreElements();) {
      MibNode node = (MibNode) nodes.nextElement();

      if (!this.mibNotificationsObjects.contains(node) && !this.mibNotifications.contains(node)) {
        if (node.isLeaf()) {
          this.mibOtherObjects.add(node);
        }
        else {
          this.mibNodes.add(node);
        }
      }
    }

    return result;
  }


  //---------------------Get results methods-------------------------------------
  public Structure getResultStructure(){
    Structure resultStruct = new Structure();

    resultStruct.setAttributeValue (this.mibNotificationsS, this.getNotificationsSequence());
    resultStruct.setAttributeValue (this.mibNotificationObjectsS, this.getNotificationObjectsSequence());
    resultStruct.setAttributeValue (this.mibOtherObjectsS, this.getOtherObjectsSequence());
    resultStruct.setAttributeValue (this.mibNodesS, this.getNodesSequence());
    resultStruct.setAttributeValue (this.mibErrorS, this.mibErrorText);

    return resultStruct;
  }

  //test method to test structure return value
  public Structure getTestResultStructure(){
    Property[] properties = new Property[4];
    properties[0] = new Property(this.mibNotificationsS, "Some notifications");
    properties[1] = new Property(this.mibNotificationObjectsS, "Some notification objects");
    properties[2] = new Property(this.mibOtherObjectsS, "Some other objects");
    properties[3] = new Property(this.mibNodesS, "Some nodes");
    Structure resultStruct = new Structure(properties);

    /*resultStruct.setAttributeValue (this.mibNotificationsS, "Some notifications");
    resultStruct.setAttributeValue (this.mibNotificationObjectsS, "Some notification objects");
    resultStruct.setAttributeValue (this.mibOtherObjectsS, "Some other objects");
    resultStruct.setAttributeValue (this.mibNodesS, "Some nodes");
    */
    return resultStruct;
  }

  public Sequence getNotificationsSequence(){
    Sequence seq = new Sequence();

    for (Iterator i = this.mibNotifications.iterator(); i.hasNext(); ) {
      MibNode node = (MibNode) i.next();
      seq.add(this.notificationToStructure(node));
    }

    return seq;
  }

  public Sequence getNotificationObjectsSequence(){
    Sequence seq = new Sequence();

    for (Iterator i = this.mibNotificationsObjects.iterator(); i.hasNext(); ) {
      MibNode node = (MibNode) i.next();
      seq.add(this.mibObjectToStructure(node));
    }

    return seq;
  }

  public Sequence getOtherObjectsSequence(){
    Sequence seq = new Sequence();

    for (Iterator i = this.mibOtherObjects.iterator(); i.hasNext(); ) {
      MibNode node = (MibNode) i.next();
      seq.add(this.mibObjectToStructure(node));
    }

    return seq;
  }

  public Sequence getNodesSequence(){
    Sequence seq = new Sequence();

    for (Iterator i = this.mibNodes.iterator(); i.hasNext(); ) {
      MibNode node = (MibNode) i.next();
      seq.add(this.leafToStructure(node));
    }

    return seq;
  }


  public Structure notificationToStructure(MibNode node){
    Structure struct = new Structure();

    struct.setAttributeValue (labelS, node.getLabel());
    struct.setAttributeValue (statusS, node.getStatus());
    struct.setAttributeValue (descriptionS, this.getCleanDescription(node));
    struct.setAttributeValue (numberedOidS, node.getNumberedOIDString());
    struct.setAttributeValue (namedOidS, node.getOIDString());

    Sequence objects = new Sequence();
    Vector mibObjectNames = node.getObjects(); //if no trap objects, then returns null!
    if (mibObjectNames != null) {
      for (Iterator i = mibObjectNames.iterator(); i.hasNext();) {
        String objectName = (String) i.next();
        objects.add(objectName);
      }
    }// if notification has objects
    struct.setAttributeValue (mibObjectsS, objects);



    return struct;
  }

  public Structure mibObjectToStructure(MibNode node){
    Structure struct = new Structure();

    struct.setAttributeValue (labelS, node.getLabel());
    struct.setAttributeValue (syntaxS, node.getSyntax().toString());
    struct.setAttributeValue (statusS, node.getStatus());
    struct.setAttributeValue (descriptionS, this.getCleanDescription(node));
    struct.setAttributeValue (numberedOidS, node.getNumberedOIDString());
    struct.setAttributeValue (namedOidS, node.getOIDString());

    return struct;
  }

  public Structure leafToStructure(MibNode node){
    Structure struct = new Structure();

    struct.setAttributeValue (labelS, node.getLabel());
    struct.setAttributeValue (numberedOidS, node.getNumberedOIDString());
    struct.setAttributeValue (namedOidS, node.getOIDString());

    return struct;
  }

  public String getCleanDescription(MibNode node){
    String s = node.getDescription();

    //Maybe better not do the stripping of CR and multiple spaces.
    //Some tables will be mis-formatted.
    /*
    s = s.replace('\n', ' ');

    int pos;
    while (true) {
      pos = s.indexOf("  ");
      if (pos == -1) {break;}
      StringBuffer sb = new StringBuffer(s);
      sb.deleteCharAt(pos);
      s = sb.toString();
    }
    */
    return s;
  }

}