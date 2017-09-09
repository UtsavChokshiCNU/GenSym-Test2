package com.gensym.jgi.download.local.denali;

import java.util.Hashtable;
import java.util.Vector;
import java.awt.*;

import com.gensym.core.DebugUtil;
import com.gensym.util.*;
import com.gensym.denali.model.*;
import com.gensym.denali.g2.*;
import com.gensym.denali.common.Geometry;
import com.gensym.denali.common.DirectionConstants;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.Connection;
import com.gensym.classes.Entity;
import com.gensym.classes.TextBox;
import com.gensym.jgi.download.local.G2RTExportManager;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.fida.ClassManagerException;

public class DenaliWorkspaceConverter implements DirectionConstants
{

  private static final Symbol KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE");
  private static final Symbol ICONS_ = Symbol.intern ("ICONS");
  private static final Symbol TYPE_ = Symbol.intern ("TYPE");
  private static final Symbol ITEM_ = Symbol.intern ("ITEM");
  private static final Symbol OBJECT_ = Symbol.intern ("OBJECT");
  private static final Symbol CONNECTION_ = Symbol.intern ("CONNECTION");
  private static final Symbol PATTERN_ = Symbol.intern ("PATTERN");
  private static final Symbol ICON_ = Symbol.intern ("ICON");
  private static final Symbol BOUNDS_ = Symbol.intern ("BOUNDS");
  private static final Symbol TERMINALS_ = Symbol.intern ("TERMINALS");
  private static final Symbol INPUT_ = Symbol.intern ("INPUT");
  private static final Symbol OUTPUT_ = Symbol.intern ("OUTPUT");
  private static final Symbol CLASS_ = Symbol.intern ("CLASS");
  private static final Symbol INDEX_ = Symbol.intern ("INDEX");
  private static final Symbol EMPTY_ = Symbol.intern ("EMPTY");

  private static final Symbol CROSS_SECTION_STRIPES_ = Symbol.intern ("CROSS-SECTION-STRIPES");
  private static final Symbol REGION_NAME_ = Symbol.intern ("REGION-NAME");
  private static final Symbol REGION_SIZE_ = Symbol.intern ("REGION-SIZE");
  private static final Symbol END_ = Symbol.intern ("END");
  
  private static final Symbol INPUT_STUBS_ = Symbol.intern ("INPUT-STUBS");
  private static final Symbol OUTPUT_STUBS_ = Symbol.intern ("OUTPUT-STUBS");
  private static final Symbol CONNECTION_STRUCT_ = Symbol.intern ("CONNECTION-STRUCT");
  private static final Symbol CONFIGURATION_ = Symbol.intern ("CONFIGURATION");
  private static final Symbol NODE_ = Symbol.intern ("NODE");
  private static final Symbol PORT_CONFIGURATION_ = Symbol.intern ("PORT-CONFIGURATION");


  static Hashtable iconTable = new Hashtable ();

  public static final Symbol _GET_WS_CONNECTIONS_RPC = 
                Symbol.intern("_G2RT-GET-WORKSPACE-CONNECTIONS");


  public static void updateLocalKbWorkspaceFromG2Workspace(KbWorkspace g2kbw, 
				      com.gensym.g2export.KbWorkspace localkbw,
						G2RTExportManager exportManager)
       throws G2AccessException, 
	      ClassManagerException
  {
    Sequence itmInfo = getItemInfo(g2kbw, 
				   exportManager);
    com.gensym.g2export.denali.WorkspaceData wsData = createWorkspaceData(g2kbw,
								   itmInfo);
    localkbw.setDenaliWorkspaceData(wsData);
  }  

  static Sequence getItemInfo(KbWorkspace g2kbw, 
		       G2RTExportManager exportManager) 
       throws G2AccessException, ClassManagerException
  {
    G2Access connection = ((ImplAccess)g2kbw).getContext();
    Sequence seq = 
      (Sequence)connection.callRPC(Symbol.intern("_G2RT-GET-WORKSPACE-CONNECTIONS"), 
			    new Object[] {g2kbw});
    Item[] items = new Item[seq.size()];
    for (int i = 0; i< seq.size(); i++)
      items[i] = (Item)seq.elementAt(i);
    
    int fileIndex = 0;
    int itmIndex = 0;
    Sequence itmInfo = new Sequence ();
    for (int i=0; i<items.length; i++) {
      System.out.println (items[i]);
      Item itm = items[i];
      System.out.println ("Item #" + i + " = " + itm);
      Structure itmStruct = null;
      if (itm instanceof Connection) {
	System.out.println ("Stripe Pattern = " +
			    ((Connection)itm).getCrossSectionPatternForClass ());
	Sequence terminals = ((Connection)itm).getConnectionInputAndOutput ();
	System.out.println ("Terminals = " + terminals);
	System.out.println ("Segments  = " + ((Connection)itm).getConnectionPositionSequence ());
	itmStruct = new Structure ();
	itmStruct.setAttributeValue (TYPE_, CONNECTION_);
	itmStruct.setAttributeValue (PATTERN_, 
				     ((Connection)itm).getCrossSectionPatternForClass ());
	Sequence posnSequence =
	  ((Connection)itm).getConnectionPositionSequence ();
	Sequence newSequence = new Sequence ();
	for (int j=0; j<posnSequence.size(); j+=2) {
	  newSequence.addElement (posnSequence.elementAt (j));
	  Integer prevY = (Integer)posnSequence.elementAt (j+1);
	  Integer newY  = new Integer (-prevY.intValue ());
	  newSequence.addElement (newY);
	}
	itmStruct.setAttributeValue (BOUNDS_,
				     newSequence);	
	Structure terms = new Structure ();
	int inputIndex = findIndex (items, (Item) terminals.elementAt (0));
	int outputIndex = findIndex (items, (Item) terminals.elementAt (1));
	System.out.println ("Input = #" + inputIndex + "  " + 
			    "Output = #" + outputIndex);
	terms.setAttributeValue (INPUT_, new Integer (inputIndex));
	terms.setAttributeValue (OUTPUT_, new Integer (outputIndex));
	itmStruct.setAttributeValue (TERMINALS_,
				     terms);
      } else if (itm instanceof Entity) {
	System.out.println ("Icon Description #" + fileIndex + " = " +
			    ((Entity)items[i]).getIconDescriptionForClass ());
	itmStruct = new Structure ();
	itmStruct.setAttributeValue (TYPE_, OBJECT_);
	itmStruct.setAttributeValue (ITEM_, exportManager.createLocalVersionOfG2Item(itm));
	itmStruct.setAttributeValue (ICON_,
				     ((Entity)items[i]).getIconDescriptionForClass ());
	Rectangle bnds = itm.getBounds ();
	bnds = new Rectangle (bnds.x, -bnds.y, bnds.width, bnds.height);
	itmStruct.setAttributeValue (BOUNDS_, bnds);
	System.out.println ("Bounds = " + itm.getBounds ());
	/*DebugUtil.writeToFile (((Entity)items[i]).getIconDescriptionForClass (),
			       "C:\\temp\\icon" + (fileIndex++) + ".icd");*/
      } else if (itm instanceof TextBox) {
	Symbol formatName_ = ((TextBox)itm).getDefaultTextBoxFormatNameForClass ();
	//System.out.println ("Format = " + 
	//		    ((formatName_ != null) ?
	//		     cxn.getFormatInfo (formatName_) : new Structure ()));
      } else {
	itmStruct = new Structure ();
	itmStruct.setAttributeValue (TYPE_, EMPTY_);
	System.out.println ("ERROR! -> " + itm);
      }
      if (itmStruct != null) {
	itmStruct.setAttributeValue (CLASS_, itm.getG2ClassName ());
	itmStruct.setAttributeValue (INDEX_, new Integer (itmIndex++));
	itmInfo.addElement (itmStruct);
      }
    }
    return itmInfo;
  } 
       
       
  static com.gensym.g2export.denali.WorkspaceData createWorkspaceData(KbWorkspace g2kbw,
							       Sequence itmInfo)
       throws G2AccessException
  {
    Hashtable cxnConfigTable = new Hashtable ();
    try {
    int i, numItems = itmInfo.size ();
    Symbol type_, clazz_;
    Structure itmStruct;
        Hashtable connectionDefinitions = new Hashtable();
    Hashtable connectionConfigurations = new Hashtable();
    Hashtable iconDefinitions = new Hashtable();
    Hashtable nodeConfigurations = new Hashtable();
    Vector nodeDatas = new Vector();
    Vector madeConnections = new Vector();
    Vector classesToRegister = new Vector();
    String moduleName = g2kbw.getContainingModule().toString();
    int nodeIndex = 0;
    
    // Pass #0 : Make Xn Defs and Xn Configs
    for (i=0; i<itmInfo.size (); i++) {
      itmStruct = (Structure)itmInfo.elementAt (i);
      type_ = (Symbol) itmStruct.getAttributeValue (TYPE_);
      clazz_ = (Symbol) itmStruct.getAttributeValue (CLASS_);
      if (type_.equals (CONNECTION_)) {
	String configName = clazz_.getPrintValue () + "-CONFIG";
	ConnectionConfiguration cxnConfig;
	if ((cxnConfig = (ConnectionConfiguration)cxnConfigTable.get (configName)) == null) {
	  Structure stripeDescription =
	    (Structure) itmStruct.getAttributeValue (PATTERN_);
	  StripePattern stripes =
	    parseStripeDescription (stripeDescription);
	  int[] stripeWidths = stripes.widths;;
	  Color[] stripeColors = stripes.colors;
	  StandardConnectionDefinition cxnDefn =
	    new StandardConnectionDefinition (null,
					      new DefinitionParameter[0],
					      StandardConnectionDefinition.STRIPED,
					      1,
					      Color.red,
					      null,
					      stripeWidths,
					      stripeColors,
					      null);
	  String cxnDefName = clazz_.getPrintValue ();
	  connectionDefinitions.put(cxnDefName, cxnDefn);
	  //m.setSharedDefinition (cxnDefName, cxnDefn);
	  
	  cxnConfig
	    = new ConnectionConfiguration (cxnDefName,
					   "com.gensym.denali.model.EventPropagator",
					   new SharedDefinitionReference (moduleName,
									  cxnDefName),
					   true,
					   null);
	  connectionConfigurations.put(configName, cxnConfig);
	  //m.setSharedDefinition (configName, cxnConfig);
	  cxnConfigTable.put (configName, cxnConfig);
	}
	itmStruct.setAttributeValue (CONFIGURATION_, cxnConfig);
	Structure terminals = (Structure) itmStruct.getAttributeValue (TERMINALS_);
	int inputIndex = ((Integer)terminals.getAttributeValue (INPUT_)).intValue ();
	int outputIndex = ((Integer)terminals.getAttributeValue (OUTPUT_)).intValue ();
	System.out.println(itmInfo.size() + " " + inputIndex + " " + outputIndex);
	// input of Xn
	Structure nodeStruct = (Structure) itmInfo.elementAt (inputIndex);
	Sequence outputStubs = 
	  (Sequence) nodeStruct.getAttributeValue (OUTPUT_STUBS_, new Sequence ());
	Structure xnReference = new Structure ();
	xnReference.setAttributeValue (CONNECTION_STRUCT_, itmStruct);
	xnReference.setAttributeValue (END_, INPUT_);
	outputStubs.addElement (xnReference);
	nodeStruct.setAttributeValue (OUTPUT_STUBS_, outputStubs);
	// output of Xn
	nodeStruct = (Structure) itmInfo.elementAt (outputIndex);
	Sequence inputStubs = 
	  (Sequence) nodeStruct.getAttributeValue (INPUT_STUBS_, new Sequence ());
	xnReference = new Structure ();
	xnReference.setAttributeValue (CONNECTION_STRUCT_, itmStruct);
	xnReference.setAttributeValue (END_, OUTPUT_);
	inputStubs.addElement (xnReference);
	nodeStruct.setAttributeValue (INPUT_STUBS_, inputStubs);
      }
    }

    // Pass #1 : Make Node Defns and Configs
    for (i=0; i<numItems; i++) {
      itmStruct = (Structure)itmInfo.elementAt (i);
      type_ = (Symbol) itmStruct.getAttributeValue (TYPE_);
      clazz_ = (Symbol) itmStruct.getAttributeValue (CLASS_);
      if (type_.equals (OBJECT_)) {
	// setup icon configs
	String iconConfigName = clazz_.getPrintValue() + "-ICON";
	if (iconTable.get (clazz_) == null) {
	  Structure iconDescription = (Structure) itmStruct.getAttributeValue (ICON_);
	  Object[] iconInfo = IconConverter.makeDynamicElements (iconDescription);
	  StandardIconDefinition iconDefn =
	    //new StandardIconDefinition (new DefinitionParameter[0],
	    //			IconConverter.makeStaticElements
	    //			(iconDescription));
	  new StandardIconDefinition (null,
				      (DefinitionParameter[])iconInfo[0],
				      (IconElement[])iconInfo[1]);
	  iconDefinitions.put(iconConfigName, iconDefn);
	  //m.setSharedDefinition (iconConfigName, iconDefn);
	  iconTable.put (clazz_, iconDefn);
	}
	// setup port configs
	Sequence portsVector = new Sequence ();
	Sequence outputStubs = (Sequence) itmStruct.getAttributeValue (OUTPUT_STUBS_, null);
	Rectangle bnds = 
	  (Rectangle) itmStruct.getAttributeValue (BOUNDS_);
	//System.out.println ("Pass#2: Processing output stubs of " + itmStruct + " \n = " + outputStubs);
	if (outputStubs != null) {
	  for (int j=0; j<outputStubs.size (); j++) {
	    Structure xnReference = (Structure) outputStubs.elementAt (j);
	    Structure cxnStruct = (Structure) xnReference.getAttributeValue (CONNECTION_STRUCT_);
	    Symbol xnClass_ = (Symbol) cxnStruct.getAttributeValue (CLASS_);
	    String cxnConfigName = xnClass_.getPrintValue() + "-CONFIG";
	    Sequence posnSeq = (Sequence) cxnStruct.getAttributeValue (BOUNDS_);
	    int x0 = ((Integer)posnSeq.elementAt (0)).intValue();
	    int y0 = ((Integer)posnSeq.elementAt (1)).intValue();
	    int faceOfStub = Geometry.findClosestSide (bnds.x, bnds.y,
						       bnds.x + bnds.width,
						       bnds.y + bnds.height,
						       x0, y0);
	    int xOffset = x0 - bnds.x - 5;
	    int yOffset = y0 - bnds.y - 5;
	    PortConfiguration portConfig =
	      new PortConfiguration (xnClass_.getPrintValue()+"-OUTPUT-"+j,
				     new SharedDefinitionReference (moduleName, cxnConfigName),
				     false,
				     true,
				     true,
				     xOffset,
				     yOffset,
				     faceOfStub);
	    xnReference.setAttributeValue (PORT_CONFIGURATION_, portConfig);
	    portsVector.addElement (portConfig);
	    System.out.println("Adding outputstub PORT_CONFIGURATION " + portConfig);
	  }
	}
	
	Sequence inputStubs = (Sequence) itmStruct.getAttributeValue (INPUT_STUBS_, null);
	//System.out.println ("Pass#2: Processing input stubs of " + itmStruct + " \n = " + inputStubs);
	if (inputStubs != null) {
	  for (int j=0; j<inputStubs.size (); j++) {
	    Structure xnReference = (Structure) inputStubs.elementAt (j);
	    Structure cxnStruct = (Structure) xnReference.getAttributeValue (CONNECTION_STRUCT_);
	    Symbol xnClass_ = (Symbol) cxnStruct.getAttributeValue (CLASS_);
	    String cxnConfigName = xnClass_.getPrintValue() + "-CONFIG";
	    Sequence posnSeq = (Sequence) cxnStruct.getAttributeValue (BOUNDS_);
	    int numPoints = posnSeq.size ();
	    int x0 = ((Integer)posnSeq.elementAt (numPoints - 2)).intValue();
	    int y0 = ((Integer)posnSeq.elementAt (numPoints - 1)).intValue();
	    int faceOfStub = Geometry.findClosestSide (bnds.x, bnds.y,
						       bnds.x + bnds.width,
						       bnds.y + bnds.height,
						       x0, y0);
	    int xOffset = x0 - bnds.x - 5;
	    int yOffset = y0 - bnds.y - 5;
	    PortConfiguration portConfig =
	      new PortConfiguration (xnClass_.getPrintValue()+"-INPUT-"+j,
				     new SharedDefinitionReference (moduleName, cxnConfigName),
				     true,
				     true,
				     true,
				     xOffset,
				     yOffset,
				     faceOfStub);
	    xnReference.setAttributeValue (PORT_CONFIGURATION_, portConfig);
	    portsVector.addElement (portConfig);
	    System.out.println("Adding inputstubs PORT_CONFIGURATION "+ portConfig);
	  }
	}
	// setup node configs
	int numPorts = portsVector.size ();
	PortConfiguration[] ports = new PortConfiguration [numPorts];
	if (numPorts > 0)
	  portsVector.copyInto (ports);
	SharedDefinitionReference portsSDef[] = new SharedDefinitionReference[numPorts];
	for (int pn = 0; pn<portsSDef.length; pn++) {
	  portsSDef[pn] = new SharedDefinitionReference(moduleName, ports[pn].getName());
	}
	Object localItem = itmStruct.getAttributeValue (ITEM_);
	// need to pass actual object here !!!!
	NodeConfiguration nodeConfig =
	  new NodeConfiguration (null,
				 clazz_.getPrintValue (),
				 true,
				 localItem.getClass().getName(),
				 "com.gensym.denali.graphics.StandardIcon",
				 new SharedDefinitionReference (moduleName, iconConfigName),
				 null,
				 null,
				 null,
				 portsSDef, 
				 null, 
				 null,
				 null);
	classesToRegister.addElement(localItem.getClass().getName());
	System.out.println("Added " + clazz_.getPrintValue());
	String nodeConfigName = "NODE-CONFIG-" + i;
        nodeConfigurations.put(nodeConfigName, nodeConfig);
	//m.setSharedDefinition (nodeConfigName, nodeConfig);

	// Create the node
	nodeDatas.addElement(
	   com.gensym.g2export.denali.WorkspaceData.makeNodeData(
					 nodeConfig, 
					 new NodeVisualInfo (bnds.x, bnds.y,
							     bnds.width + 1, bnds.height + 1),
					 localItem)); 
	//AbstractNode itmNode = w.addNode (nodeConfig,
	//				  new NodeVisualInfo (bnds.x, bnds.y,
	//						      bnds.width + 1, bnds.height + 1));
	System.out.println("Added node " + nodeIndex + " " + localItem);
	itmStruct.setAttributeValue (NODE_, new Integer(nodeIndex++));
      }
    }

    // Pass #2 : Make connections!
    for (i=0; i< numItems; i++) {
      itmStruct = (Structure)itmInfo.elementAt (i);
      type_ = (Symbol) itmStruct.getAttributeValue (TYPE_);
      clazz_ = (Symbol) itmStruct.getAttributeValue (CLASS_);
      if (type_.equals (CONNECTION_)) {
	String configName = clazz_.getPrintValue () + "-CONFIG";
	Structure terminals = (Structure) itmStruct.getAttributeValue (TERMINALS_);
	int inputIndex = ((Integer)terminals.getAttributeValue (INPUT_)).intValue ();
	int outputIndex = ((Integer)terminals.getAttributeValue (OUTPUT_)).intValue ();
	// input of Xn : output stub
	Structure inputItmStruct = (Structure) itmInfo.elementAt (inputIndex);
	int inputNodeIndex = 
	  ((Integer)inputItmStruct.getAttributeValue (NODE_)).intValue();
	//AbstractNode inputNode = 
	//(AbstractNode) inputItmStruct.getAttributeValue (NODE_);
	Sequence outputStubs = 
	  (Sequence) inputItmStruct.getAttributeValue (OUTPUT_STUBS_, new Sequence ());
	PortConfiguration outputPC =
	  getPortConfiguration (outputStubs, itmStruct);
	//Port outputPort = inputNode.getPort (outputPC);
	// output of Xn : input stub
	Structure outputItmStruct = (Structure) itmInfo.elementAt (outputIndex);
	Sequence inputStubs = 
	  (Sequence) outputItmStruct.getAttributeValue (INPUT_STUBS_, new Sequence ());
	PortConfiguration inputPC =
	  getPortConfiguration (inputStubs, itmStruct);
	int outputNodeIndex = 
	  ((Integer)outputItmStruct.getAttributeValue (NODE_)).intValue();
	//AbstractNode outputNode = 
	//(AbstractNode) outputItmStruct.getAttributeValue (NODE_);
	//Port inputPort = outputNode.getPort (inputPC);
	// make the connection
	String cxnConfigName = clazz_.getPrintValue() + "-CONFIG";
	ConnectionConfiguration cxnConfig = 
	  (ConnectionConfiguration) cxnConfigTable.get (cxnConfigName);
	System.out.println("Connected  " + inputNodeIndex + " " + outputNodeIndex);
	madeConnections.addElement( 
	      com.gensym.g2export.denali.WorkspaceData.makeConnectedData ( cxnConfig,
								    inputNodeIndex, 
								    outputPC, 
								    outputNodeIndex, 
								    inputPC));
	//w.connectPortsMinimally (cxnConfig, outputPort, inputPort);
	}
      }
      
      return new com.gensym.g2export.denali.WorkspaceData(moduleName,
						   connectionDefinitions,
						   connectionConfigurations,
						   iconDefinitions,
						   nodeConfigurations,
						   nodeDatas,
						   madeConnections,
						   classesToRegister);
    } catch (NoSuchAttributeException e) {
      e.printStackTrace();
      throw new RuntimeException(e.toString());
    }
  }

  private static StripePattern parseStripeDescription (Structure stripeDescription)
    throws NoSuchAttributeException
  {
    // assume no named regions!
    Sequence stripes = 
      (Sequence) stripeDescription.getAttributeValue (CROSS_SECTION_STRIPES_);
    int numStripes = stripes.size ();
    int[] widths = new int[numStripes];
    Color[] colors = new Color[numStripes];
    for (int i=0; i<numStripes; i++) {
      Structure stripe = (Structure) stripes.elementAt (i);
      int width = ((Integer)stripe.getAttributeValue (REGION_SIZE_)).intValue ();
      Symbol colorName_ = (Symbol) stripe.getAttributeValue (REGION_NAME_);
      Color color = G2ColorMap.get (colorName_);
      widths[i] = width;
      colors[i] = color;
    }
    return new StripePattern (widths, colors);
  }

  private static PortConfiguration getPortConfiguration (Sequence stubs, Structure cxnStruct)
    throws NoSuchAttributeException
  {
    int cxnIndex = ((Integer)cxnStruct.getAttributeValue (INDEX_)).intValue ();
    for (int i=0; i<stubs.size(); i++) {
      Structure xnReference = (Structure) stubs.elementAt (i);
      Structure stubXnStruct = (Structure) xnReference.getAttributeValue (CONNECTION_STRUCT_);
      int index = ((Integer)stubXnStruct.getAttributeValue (INDEX_)).intValue ();
      if (cxnIndex == index) {
	PortConfiguration portConfig =
	  (PortConfiguration) xnReference.getAttributeValue (PORT_CONFIGURATION_);
	return portConfig;
      }
    }
    throw new IllegalStateException (cxnIndex + " not found in stubs");
  }

  private static int findIndex (Item[] list, Item itm) {
    for (int i=0; i<list.length; i++)
      if (itm.equals (list[i]))
	return i;
    throw new IllegalStateException (itm + " not found!");
  }

}

class StripePattern {
  
  int[] widths;
  Color[] colors;
  
  StripePattern (int[] widths, Color[] colors) {
    this.widths = widths;
    this.colors = colors;
  }

}

