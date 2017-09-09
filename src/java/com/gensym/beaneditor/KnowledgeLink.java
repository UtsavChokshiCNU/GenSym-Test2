package com.gensym.beaneditor;

import java.awt.*;
import java.util.Vector;
import com.gensym.draw.*;
import java.lang.Math;

public class KnowledgeLink extends ConnectionElement implements java.io.Serializable
{

  static final long serialVersionUID = -24657748205196955L;
  static Vector links = new Vector();

  Wrapper subject;
  Object object;
  String name;

  public KnowledgeLink(String name, Wrapper subject, Object object,
		       Point[] vertices,
		       int[]widths, Object[] stripePattern,
		       Object[] logicalColors, Color[] colors)
  {
    super(vertices,widths,stripePattern,logicalColors,colors, DIAGONAL);
    this.name = name;
    this.subject = subject;
    this.object = object;
    subject.knowledgeLinks.addElement(this);
    if (object instanceof Wrapper)
      ((Wrapper)object).knowledgeLinks.addElement(this);
    links.addElement(this);
  }

  void updateVertices()
  {
    Point center1 = subject.centerPoint();
    Point center2;
    if (object instanceof Wrapper)
      center2 = ((Wrapper)object).centerPoint();
    else
      center2 = ((KnowledgeLinkLooseEnd)object).centerPoint();

    canvas.invalidateElement(this);
    setVertices(new Point[] { center1, center2 });
    canvas.invalidateElement(this);
  }

  void removeLink(){
    canvas.removeElement(this);
    subject.knowledgeLinks.removeElement(this);
    if (object instanceof Wrapper)
      ((Wrapper)object).knowledgeLinks.removeElement(this);
    else
      canvas.removeElement((KnowledgeLinkLooseEnd)object);
    links.removeElement(this);
  }
  
}
