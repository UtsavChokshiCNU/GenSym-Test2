package com.gensym.wksp;


import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.draw.*;
import java.util.Enumeration;
import java.util.Vector;
import java.awt.*; //Rectangle
import java.awt.event.*;
import java.util.Locale;
import com.gensym.classes.Item;
import com.gensym.classes.Block;
import com.gensym.classes.KbWorkspace;


public class WorkspaceUtil extends Object {

  static Integer defaultinteger = new Integer(0);
  static Symbol sleft = Symbol.intern("LEFT");
  static Symbol stop = Symbol.intern("TOP");
  static Symbol sright = Symbol.intern("RIGHT");
  static Symbol sbottom = Symbol.intern("BOTTOM");
  public static int newWorkspaceCount = 1;
  
  public static Rectangle boundsStructureToBounds(Structure boundsStructure) {
    int width = 0; int height = 0;
    if (boundsStructure != null) {
      Integer ileft = (Integer)
	boundsStructure.getAttributeValue(sleft,defaultinteger);
      Integer itop = (Integer)
	boundsStructure.getAttributeValue(stop, defaultinteger);
      Integer iright = (Integer)
	boundsStructure.getAttributeValue(sright, defaultinteger);
      Integer ibottom = (Integer)
	boundsStructure.getAttributeValue(sbottom, defaultinteger);
      int left = ileft.intValue();
      int top = itop.intValue();
      int right = iright.intValue();
      int bottom = ibottom.intValue();
      width = right - left;
      height = top - bottom;//bottom - top;
      return new Rectangle(left, top, width, height);
    } else {
      System.out.println("bounds structure is null");
      return null;
    }
  }

  public static Point[] convertVerticesSequenceToPointArray(Sequence pointsData) {
    //PBK DEAL WITH BAD/NULL pointsData
    Object[] XYcoords = pointsData.getContents();
    int pointCount = XYcoords.length/2;
    Point[] points = new Point[pointCount];
    Integer x,y;
    for (int i = 0; i< pointCount; i++) {
      x = (Integer) XYcoords[2*i];
      y = (Integer) XYcoords[2*i+1];
      points[i]= new Point(x.intValue(),- y.intValue());//converted to user coords
    }
    return points;
  }

  public static Sequence convertPointArrayToVerticesSequence(Point[] points) {
    Sequence verticesSequence = new Sequence();
    for (int i=0;i<points.length;i++) {
      verticesSequence.addElement(new Integer(points[i].x));
      verticesSequence.addElement(new Integer(- points[i].y));
    }
    return verticesSequence;
  }

  public static String computePrettyClassName(String name) {
    StringBuffer _stringb = new StringBuffer (name);
    boolean isNewword = false;
    
    _stringb.setCharAt (0, Character.toTitleCase(_stringb.charAt(0)));
    for (int i = 1; i < _stringb.length(); i++) {
      if (_stringb.charAt(i) == '-') {
	isNewword = true;
	_stringb.setCharAt (i, ' ');
      } else {
	if (isNewword) {
	  isNewword = false;
	  _stringb.setCharAt (i, Character.toTitleCase(_stringb.charAt(i)));
	} else {
	  _stringb.setCharAt (i, Character.toLowerCase(_stringb.charAt(i)));
	}
      }
    }
    return _stringb.toString();
  }

  private static Symbol text_ = Symbol.intern("TEXT");
  private static Symbol procedure_ = Symbol.intern("PROCEDURE");
  public static Symbol unAliasSlotName(Object element,
				       Symbol aliasedSlotName,
				       Symbol g2ClassName) {
    Symbol unAliasedSlotName = null;
    if (aliasedSlotName.equals(text_)) {
      if (g2ClassName.equals(procedure_))
	unAliasedSlotName = Symbol.intern("PROCEDURE-DEFINITION");
      else if (element instanceof WorkspaceTextBox)
	//rule, freetext, etc..
	unAliasedSlotName = Symbol.intern("BOX-TRANSLATION-AND-TEXT");
    }
    return unAliasedSlotName;
  }

}
  

