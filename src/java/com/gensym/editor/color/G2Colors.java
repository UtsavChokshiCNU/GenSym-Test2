/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Colors.java
 *
 */
package com.gensym.editor.color;

import java.awt.Color;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.nio.charset.Charset;
import java.util.Hashtable;
import java.util.Vector;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;

public class G2Colors {

  private static String g2ColorStringsResource = "com/gensym/editor/color/G2ColorStrings";
  private static String g2ColorSymbolsResource = "com/gensym/editor/color/G2ColorSymbols";
  private static String g2ColorRGBValuesFile = "G2ColorRGBValues.properties";

  private Hashtable colorStringToColorSymbol = new Hashtable();
  private Hashtable colorStringToColorObject = new Hashtable();
  private Hashtable colorObjectToColorString = new Hashtable();
  private Hashtable colorSymbolToColorString = new Hashtable();

  protected String colorStrings[] = null;
  protected Color colorObjects[] = null;

  protected int numColors = 0;
  
  public G2Colors() {
    this(g2ColorStringsResource, g2ColorSymbolsResource, g2ColorRGBValuesFile);
  }

  public G2Colors (String g2ColorStringsResource,
		   String g2ColorSymbolsResource,
		   String g2ColorRGBValuesFile) {
    this.g2ColorStringsResource = g2ColorStringsResource;
    this.g2ColorSymbolsResource = g2ColorSymbolsResource;
    this.g2ColorRGBValuesFile = g2ColorRGBValuesFile;
    processColorResources();
  }

  private void processColorResources() { 
    // Setup RGB properties file for tokenized reading
    Class thisClass = getClass();
    InputStream dataIn = thisClass.getResourceAsStream(g2ColorRGBValuesFile);
    InputStreamReader readerIn = new InputStreamReader(dataIn, Charset.defaultCharset());
    StreamTokenizer tokenizer = new StreamTokenizer(readerIn);

    // Get Resources for color names and symbols
    Resource colorStringsBundle = Resource.getBundle(g2ColorStringsResource);
    Resource colorSymbolsBundle = Resource.getBundle(g2ColorSymbolsResource);

    Vector names = new Vector();
    Vector rgbs = new Vector();

    Symbol colorSymbol;
 
    boolean done = false; 
    int token = 0;
    
    while (!done) {
      try {
	token = tokenizer.nextToken();
      } catch (IOException e) {
	System.out.println(e);
      }
      
      if (token == tokenizer.TT_EOF) 
	done = true;
      
      if (!done) {
	if (token == tokenizer.TT_NUMBER) {
	  //System.out.println ("token: nval=> " + tokenizer.nval);
	  rgbs.addElement(new Double(tokenizer.nval));
	}
	
	else if (token == tokenizer.TT_WORD) {
	  //System.out.println (numColors+": token: sval=> " + tokenizer.sval);  
	  names.addElement(colorStringsBundle.getString(tokenizer.sval).trim());
	  colorSymbol = Symbol.intern(colorSymbolsBundle.getString(tokenizer.sval).trim());
	  colorStringToColorSymbol.put((String)names.elementAt(numColors), 
				       colorSymbol);
	  colorSymbolToColorString.put(colorSymbol, 
				       (String)names.elementAt(numColors));
	  numColors = numColors + 1;
	}
      }
    }  

    colorStrings = new String[numColors];
    colorObjects = new Color[numColors];
    for (int i=0; i<numColors; i++) {
      colorStrings[i] = names.elementAt(i).toString();
      colorObjects[i] = new Color(((Double)rgbs.elementAt(i*3)).intValue(),
			          ((Double)rgbs.elementAt((i*3)+1)).intValue(),
			          ((Double)rgbs.elementAt((i*3)+2)).intValue());
      colorStringToColorObject.put(colorStrings[i], colorObjects[i]);
      colorObjectToColorString.put(colorObjects[i], colorStrings[i]);
    }
  }

  /**
   * @return int The number of colors processed during the initialization of
   * G2Colors
   */
  public int getNumberOfColors() {
    if (numColors == 0) {
    	processColorResources();
    }
    return numColors;
  }

  /**
   * Returns a Symbol for the specified color string.
   * @param colorString A String representing a standard G2 color.
   * @return Symbol A Symbol that is the g2 symbol name for the
   * specified color string
   */
  public Symbol getColorSymbolForColorString (String colorString) {
    if (numColors == 0) {
    	processColorResources();
    }
    return (Symbol)colorStringToColorSymbol.get(colorString);
  }

  /**
   * Returns a String for the specified G2 color symbol
   * @param colorSymbol A Symbol representing the name of a standard
   * G2 color.
   * @return String A String containing the name of the G2 color
   */
  public String getColorStringForColorSymbol (Symbol colorSymbol) {
    if (numColors == 0) {
    	processColorResources();
    }
    return (String)colorSymbolToColorString.get(colorSymbol);
  }

  /**
   * Returns a Color component for the speficied G2 standard color.
   * @param colorString A String representing the name of a G2 color.
   * @return Color A Color component for the G2 standard color.
   */
  public Color getColorObjectForColorString (String colorString) {
    if (numColors == 0) {
    	processColorResources();
    }
    return (Color)colorStringToColorObject.get(colorString);
  }

  /**
   * Returns a String for the specified color object
   * @param colorObject a Color object representing a standard G2 color.
   * @return String A String representing the name of a G2 color.
   */
  public String getColorStringForColorObject(Color colorObject) {
    if (numColors == 0) {
    	processColorResources();
    }
    return (String)colorObjectToColorString.get(colorObject);
  }

  public static void main (String[] cmdLineArgs) {
    G2Colors colors = new G2Colors();
  }
}
