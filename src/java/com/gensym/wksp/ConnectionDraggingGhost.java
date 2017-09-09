
package com.gensym.wksp;

import com.gensym.draw.ConnectionElement;
import com.gensym.draw.Segment;

import java.awt.*;

class ConnectionDraggingGhost extends DraggingGhost {

  private boolean kinked = false;
  boolean firstSegmentIsHorizontal = true;
  
  @Override
  void display (WorkspaceView canvas) {
    for (int i=0; i<elements.length; i++)
      canvas.addElement (elements[i]);
    canvas.invalidate (boundsArray);
  }

  ConnectionElement getConnectionElement() {
    return (ConnectionElement)elements[0];
  }

  private boolean endSegmentIsHorizontal(int verticeCount) {
    boolean lengthIsOdd = ((verticeCount - 2*(verticeCount/2)) == 1);
    return (lengthIsOdd?!firstSegmentIsHorizontal:firstSegmentIsHorizontal);
  }
  
  @Override
  void shift (WorkspaceView canvas, int deltaX, int deltaY) {      
    ConnectionElement connectionElement = getConnectionElement();
    Point[] vertices = connectionElement.getVertices();    
    int length = vertices.length;
    Point endPoint = vertices[length-1];
    Point prevPoint = vertices[length-2];
    boolean endSegmentIsHorizontal = endSegmentIsHorizontal(length);
    boolean isDiagonal = (connectionElement.getStyle() == ConnectionElement.DIAGONAL);
    if (!isDiagonal&&length == 2) 
      kinked = true;
    boolean needToAddBend = (kinked&&(isDiagonal ||
				      (endSegmentIsHorizontal?deltaY!=0:deltaX!=0)));
    if (needToAddBend) {
      vertices = addNewPointAtEnd(vertices);
      kinked = false;
      length+=1;
      endPoint = vertices[length-1];
      prevPoint = vertices[length-2];
      endSegmentIsHorizontal = endSegmentIsHorizontal(length);
    }
    if (!isDiagonal) {
      if (endSegmentIsHorizontal)
	prevPoint.setLocation(prevPoint.x, prevPoint.y + deltaY);
      else 
	prevPoint.setLocation(prevPoint.x + deltaX, prevPoint.y);
    }

    endPoint.setLocation(endPoint.x + deltaX, endPoint.y + deltaY);
    Rectangle[] bounds = connectionElement.getExactBounds();
    connectionElement.setVertices(vertices);
    canvas.invalidate(bounds);
    canvas.invalidateElement(connectionElement);
  }

  void setKinked(boolean kinked) {
    this.kinked = kinked;
  }

  private Point[] addNewPointAtEnd(Point[] vertices) {
    int length = vertices.length;
    Point[] newVertices = new Point[length+1];
    for (int i=0; i<length; i++) {
      newVertices[i] = vertices[i];
    }
    Point endPoint = vertices[length-1];
    newVertices[length] = new Point(endPoint.x,endPoint.y);
    return newVertices;
  }
      
  @Override
  void dispose (WorkspaceView canvas) {
    for (int i=0; i<elements.length; i++)
      canvas.removeElement (elements[i]);
  }

}
