package com.gensym.beaneditor;

import java.awt.Color;
import java.beans.PropertyEditorManager;
import java.util.Hashtable;

class ColorMap extends Hashtable implements java.io.Serializable{

  private static final Class thisClass = com.gensym.beaneditor.ColorMap.class;
  private static final  Class editor = com.gensym.beaneditor.ColorMapEditor.class;

  private static final int NUMBER_OF_COLORS = 9;

  private static ColorMap defaultMap = new ColorMap();
  private static Color[] standardColors = new Color[]{Color.red, Color.blue, Color.yellow, Color.green, Color.orange, Color.pink, Color.cyan, Color.magenta, Color.white};
  private static boolean[] used = new boolean[NUMBER_OF_COLORS];
  private static boolean standardColorsUsedUp = false;

  static{
    PropertyEditorManager.registerEditor(thisClass, editor);
    for (int i=0; i<NUMBER_OF_COLORS; i++)
      used[i] = false;
  }

  ColorMap(){}

  ColorMap(int size){
    super(size);
  }

  public static ColorMap getDefaultMap(){
    return defaultMap;
  }

  private void markColorUsed(Color color){
    int index = -1;
    for (int i=0; i< NUMBER_OF_COLORS; i++){
      if (standardColors[i].equals(color)){
	index = i;
	break;
      }
    }
    if (index >= 0) used[index] = true;
  }


  @Override
  public Object put(Object event, Object color){
    return put(event, color, true);
  }

  private Object put(Object event, Object color, boolean markUsed){
    if ((color instanceof Color)  && markUsed){
      markColorUsed((Color)color);
    }
    return super.put(event, color);
  }

  public Color getOrAssignColor(Object event){
    Object color = super.get(event);
    if (color != null) return (Color)color;
    else return getRandomColorTryStandardColorsFirst(event);
  }

  private int getNextAvailableStandardColor(){
    if (standardColorsUsedUp) return -1;
    int index = -1;
    for (int i=0; i < NUMBER_OF_COLORS; i++){
      if (!used[i]){
	index = i;
	break;
      }
    }

    if (index >= 0)
      return index;

    standardColorsUsedUp = true;
    return -1;
  }

  private Color getRandomColor(){
    int r = (int)(255 * Math.random());
    int g = (int)(255 * Math.random());
    int b = (int)(255 * Math.random());
    return new Color(r, g, b);
  }

  private Color getRandomColorTryStandardColorsFirst(Object key){
    int index = getNextAvailableStandardColor();
    Color newColor;
    if (index >= 0){
      newColor = standardColors[index];
      used[index] = true;
    }
    else{
      newColor = getRandomColor();
      while (get(key) != null)
	newColor = getRandomColor();
    }
    put(key, newColor, false);
    return newColor;
  }


}

