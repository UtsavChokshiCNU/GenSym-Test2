
package com.gensym.tests;

import java.awt.Rectangle;
import java.awt.Point;
import java.util.Vector;
import com.gensym.core.*;
import com.gensym.util.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Item;
import com.gensym.classes.ItemImpl;
import com.gensym.classes.Entity;
import com.gensym.classes.Connection;
import com.gensym.classes.TextBox;
import com.gensym.classes.TableItem;
import com.gensym.denali.common.DirectionConstants;

public class DumpWkspForDenali {

  private static final int INPUT = 0, OUTPUT = 1;

  private static final Symbol KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE");
  private static final Symbol TYPE_ = Symbol.intern ("TYPE");
  private static final Symbol TEXT_BOX_ = Symbol.intern ("TEXT-BOX");
  private static final Symbol OBJECT_ = Symbol.intern ("OBJECT");
  private static final Symbol CONNECTION_ = Symbol.intern ("CONNECTION");
  private static final Symbol PATTERN_ = Symbol.intern ("PATTERN");
  private static final Symbol ICON_ = Symbol.intern ("ICON");
  private static final Symbol BOUNDS_ = Symbol.intern ("BOUNDS");
  private static final Symbol LOCATION_ = Symbol.intern ("LOCATION");
  private static final Symbol TERMINALS_ = Symbol.intern ("TERMINALS");
  private static final Symbol DIRECTION_ = Symbol.intern ("DIRECTION");
  private static final Symbol INPUT_ = Symbol.intern ("INPUT");
  private static final Symbol OUTPUT_ = Symbol.intern ("OUTPUT");
  private static final Symbol CLASS_ = Symbol.intern ("CLASS");
  private static final Symbol INDEX_ = Symbol.intern ("INDEX");
  private static final Symbol EMPTY_ = Symbol.intern ("EMPTY");
  private static final Symbol TEXT_ = Symbol.intern ("TEXT");
  private static final Symbol LEFT_TEXT_ = Symbol.intern ("LEFT-TEXT");
  private static final Symbol RIGHT_TEXT_ = Symbol.intern ("RIGHT-TEXT");
  private static final Symbol FONT_SIZE_ = Symbol.intern ("FONT-SIZE");
  private static final Symbol ICON_VARIABLES_ = Symbol.intern ("ICON-VARIABLES");
  private static final Symbol LOOSE_END_ = Symbol.intern ("LOOSE-END");

  public static void main (String[] args) throws Exception {
    GensymApplication.initialize (args);
    CmdLineArgHandler argHandler = new CmdLineArgHandler (args);
    String host = argHandler.getOptionValue ("-host");
    if (host == null)
      host = "localhost";
    String port = argHandler.getOptionValue ("-port");
    if (port == null)
      port = "1111";
    TwGateway cxn = (TwGateway) TwGateway.openConnection (host, port);
    cxn.login ();
    WorkspaceListener nullListener = new WorkspaceAdapter ();
    String wkspName = argHandler.getOptionValue ("-wksp");
    KbWorkspace wksp = (KbWorkspace) cxn.getUniqueNamedItem (KB_WORKSPACE_, Symbol.intern (wkspName));
    wksp.addWorkspaceListener (nullListener);
    Item[] items = wksp.getItems();
    Rectangle bounds = wksp.getBounds ();
    int wkspLeft = bounds.x;
    int wkspTop = -bounds.y;
    Vector looseEnds = new Vector ();
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
	Sequence posnSequence =
	  ((Connection)itm).getConnectionPositionSequence ();
	for (int j=0; j<posnSequence.size(); j+=2) {
	  int x = ((Integer)posnSequence.elementAt (j)).intValue();
	  int y = ((Integer)posnSequence.elementAt (j+1)).intValue();
	  Integer newX  = new Integer (x - wkspLeft);
	  Integer newY  = new Integer (-y - wkspTop);
	  posnSequence.setElementAt (newX, j);
	  posnSequence.setElementAt (newY, j + 1);
	}

	if (terminals.elementAt (0) instanceof Boolean)
	  terminals.setElementAt (makeNewLooseEnd(cxn, looseEnds, posnSequence, INPUT), 0);
	if (terminals.elementAt (1) instanceof Boolean)
	  terminals.setElementAt (makeNewLooseEnd(cxn, looseEnds, posnSequence, OUTPUT), 1);
	System.out.println ("Segments  = " + ((Connection)itm).getConnectionPositionSequence ());
	itmStruct = new Structure ();
	itmStruct.setAttributeValue (TYPE_, CONNECTION_);
	itmStruct.setAttributeValue (PATTERN_, 
				     ((Connection)itm).getCrossSectionPatternForClass ());
	itmStruct.setAttributeValue (BOUNDS_,
				     posnSequence);	
	Structure terms = new Structure ();
	int inputIndex = findIndex ((Item) terminals.elementAt (0), items, looseEnds);
	int outputIndex = findIndex ((Item) terminals.elementAt (1), items, looseEnds);
	System.out.println ("Output Item = " + terminals.elementAt (1) + " in " + com.gensym.core.DebugUtil.printArray(items));
	System.out.println ("Input = #" + inputIndex + "  " + 
			    "Output = #" + outputIndex);
	terms.setAttributeValue (INPUT_, new Integer (inputIndex));
	terms.setAttributeValue (OUTPUT_, new Integer (outputIndex));
	itmStruct.setAttributeValue (TERMINALS_,
				     terms);
      } else if (itm instanceof Entity) {
	if (false) System.out.println ("Icon Description #" + fileIndex + " = " +
			    ((Entity)items[i]).getIconDescriptionForClass ());
	itmStruct = new Structure ();
	itmStruct.setAttributeValue (TYPE_, OBJECT_);
	itmStruct.setAttributeValue (ICON_,
				     ((Entity)items[i]).getIconDescriptionForClass ());
	Rectangle bnds = itm.getBounds ();
	bnds = new Rectangle (bnds.x - wkspLeft,
                              -bnds.y - wkspTop,
			      bnds.width, bnds.height);
	itmStruct.setAttributeValue (BOUNDS_, bnds);
	System.out.println ("Bounds = " + bnds);
	/*DebugUtil.writeToFile (((Entity)items[i]).getIconDescriptionForClass (),
			       "C:\\temp\\icon" + (fileIndex++) + ".icd");*/
      } else if (itm instanceof TextBox) {
	Symbol formatName_ = ((TextBox)itm).getDefaultTextBoxFormatNameForClass ();
	System.out.println ("Format = " + 
			    ((formatName_ != null) ?
			     cxn.getFormatInfo (formatName_) : new Structure ()));
      } else if (itm instanceof TableItem) {
	itmStruct = new Structure ();
	itmStruct.setAttributeValue (TYPE_, TEXT_BOX_);
	TableItem tblItm = (TableItem)itm;
	Symbol fontSize = tblItm.getTableFontSize ();
	itmStruct.setAttributeValue (FONT_SIZE_, fontSize);
	Sequence tableRows = tblItm.getTableRows ();
	Rectangle bnds = itm.getBounds ();
	bnds = new Rectangle (bnds.x - wkspLeft,
                              -bnds.y - wkspTop,
			      bnds.width, bnds.height);
	itmStruct.setAttributeValue (BOUNDS_, bnds);
	Structure rowInfo = (Structure)tableRows.elementAt (0);
	String displayText = (String) rowInfo.getAttributeValue (LEFT_TEXT_, null);
	if (displayText == null)
	  displayText = (String) rowInfo.getAttributeValue (RIGHT_TEXT_, null);
	itmStruct.setAttributeValue (TEXT_, displayText);
	System.out.println ("Text = " + tableRows + " in " + fontSize +
			    "\nBounds = " + bnds);
			    
      }
      if (itmStruct != null &&
	  itm instanceof Entity)
	itmStruct.setAttributeValue (ICON_VARIABLES_,
				     ((Entity)itm).getIconVariables());
      if (itmStruct == null) {
	itmStruct = new Structure ();
	itmStruct.setAttributeValue (TYPE_, EMPTY_);
	System.out.println ("ERROR! -> " + itm);
      }
      itmStruct.setAttributeValue (CLASS_, itm.getG2ClassName ());
      itmStruct.setAttributeValue (INDEX_, new Integer (itmIndex++));
      itmInfo.addElement (itmStruct);

      System.out.println ("Added :::: " + itmStruct);
      System.out.println ("INDEX = " + (itmIndex - 1) + " for " + itm + "\n");
    }
    for (int i=0; i<looseEnds.size(); i++) {
      Item itm = (Item) looseEnds.elementAt (i);
      Structure itmStruct = new Structure ();
      itmStruct.setAttributeValue (TYPE_, LOOSE_END_);
      itmStruct.setAttributeValue (CLASS_, LOOSE_END_);
      itmStruct.setAttributeValue (INDEX_, new Integer (items.length + i));
      itmStruct.setAttributeValue (LOCATION_, itm.getPropertyValue (LOCATION_));
      itmStruct.setAttributeValue (DIRECTION_, itm.getPropertyValue (DIRECTION_));
      itmInfo.addElement (itmStruct);
    }
    DebugUtil.writeToFile (itmInfo, "C:\\temp\\opex.dump");
    System.exit (0);
  }

  private static int findIndex (Item itm, Item[] list, Vector looseEnds) {
    for (int i=0; i<list.length; i++)
      if (itm.equals (list[i]))
	return i;
    for (int i=0; i<looseEnds.size(); i++)
      if (itm.equals (looseEnds.elementAt (i)))
	return list.length + i;
    throw new IllegalStateException (itm + " not found!");
  }

  private static Item makeNewLooseEnd (TwAccess connection, Vector looseEnds,
				       Sequence posnSequence, int terminalType) throws G2AccessException {
    Item looseEnd = new ItemImpl (connection, 0, null);
    looseEnds.addElement (looseEnd);
    int numElements = posnSequence.size();
    int x0, y0, x1, y1, direction;
    if (terminalType == INPUT) {
      x0 = ((Integer)posnSequence.elementAt (0)).intValue();
      y0 = ((Integer)posnSequence.elementAt (1)).intValue();
      x1 = ((Integer)posnSequence.elementAt (2)).intValue();
      y1 = ((Integer)posnSequence.elementAt (3)).intValue();
      System.out.println ("INPUT: x0="+x0+" y0="+y0 + "x1="+x1 + "y1="+y1);
      if (y0 == y1)
	direction = (x0 > x1 ? DirectionConstants.LEFT : DirectionConstants.RIGHT);
      else
	direction = (y0 > y1 ? DirectionConstants.TOP : DirectionConstants.BOTTOM);
    } else {
      x0 = ((Integer)posnSequence.elementAt (numElements - 2)).intValue();
      y0 = ((Integer)posnSequence.elementAt (numElements - 1)).intValue();
      x1 = ((Integer)posnSequence.elementAt (numElements - 4)).intValue();
      y1 = ((Integer)posnSequence.elementAt (numElements - 3)).intValue();
      System.out.println ("OUTPUT: x0="+x0+" y0="+y0 + "x1="+x1 + "y1="+y1);
      if (y0 == y1)
	direction = (x0 > x1 ? DirectionConstants.LEFT : DirectionConstants.RIGHT);
      else
	direction = (y0 > y1 ? DirectionConstants.TOP : DirectionConstants.BOTTOM);
    }
    System.out.println (">. posnSeq = " + posnSequence +  " Terminal = " + terminalType + " Direction = " + direction);
    looseEnd.setPropertyValue (LOCATION_, new Point (x0, y0));
    looseEnd.setPropertyValue (DIRECTION_, new Integer (direction));
    return looseEnd;
  }
}
