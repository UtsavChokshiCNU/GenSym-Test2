/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TestUtils.java
 *
 */
package com.gensym.tests.auto;

import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import java.util.Vector;

public abstract class TestUtils {
  private static final boolean debugCreate = false;
 
  public static Vector createPossibleItemTypesVector(ConnectionManager connectionMgr){
    Vector possibleItemTypes = new Vector(); 

    // Start with item and then loop recursively over all subclasses until
    // there are no more
    Symbol baseClass = Symbol.intern("ITEM");

    Sequence subclasses = new Sequence(); 
    try {
      System.out.println("calling getDirectSubclasses with: " + baseClass);
      subclasses = (Sequence)((G2Gateway)connectionMgr.getCurrentConnection()).getDirectSubclasses(baseClass);
    }
    catch (G2AccessException ex){
      System.out.println(ex);
    }

    Symbol className = null;
    for (int i=0; i<subclasses.size(); i++){
      System.out.println("num classes: " + subclasses.size());
      className = (Symbol)subclasses.elementAt(i);
      System.out.println(className);
      possibleItemTypes.addElement(className.toString());
    }

    return possibleItemTypes;
  }

  // BEGIN: setupAndCreateItems
  public static Vector setupAndCreateItems(ConnectionManager cm){
    Vector createdItems = null;
    Vector possibleItemTypes = createPossibleItemTypesVector(cm);

    Symbol className = null;
    if (possibleItemTypes.size() > 0){
      System.out.println("***********There are " + possibleItemTypes.size() + " types to create *********");
    
      createdItems = new Vector();

      TwAccess context = cm.getCurrentConnection();

      // create one of every type in the list of possible types
      for (int i = 0; i<possibleItemTypes.size(); i++){
	className = Symbol.intern(((String)possibleItemTypes.elementAt(i)));
	if (debugCreate)
	  System.out.println("[" + i + "]: creating a " + className);
        try {
	  Item item = context.createItem(className);
          createdItems.addElement(item);
	  if (debugCreate)
	    System.out.println("[" + i + "] cont. created and added a " + item);
        }
        catch (G2AccessException ex){
          System.out.println(ex.getMessage());
        }
      }

      System.out.print(createdItems.size() + " items were created");
    }

    return createdItems;
  }
  // END: setupAndCreateItems
} 
