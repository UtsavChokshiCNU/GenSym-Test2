
package com.gensym.wksp;

import com.gensym.draw.DrawElement;
import java.awt.*;

class DraggingGhost {
  Component[] elements;
  Rectangle[] boundsArray = new Rectangle[1];

  Rectangle getBounds() {
    return boundsArray[0];
  }
  
  void display (WorkspaceView canvas) {
    for (int i=0; i<elements.length; i++)
      canvas.addElement (elements[i]);
    canvas.invalidate (boundsArray);
  }

  void shift (WorkspaceView canvas, int deltaX, int deltaY) {
    Point loc = boundsArray[0].getLocation();
    boundsArray[0].setLocation(loc.x+deltaX, loc.y+deltaY);
    for (int i=0; i<elements.length; i++) {
      canvas.shiftElement (elements[i], deltaX, deltaY);
      
    }
  }

  void dispose (WorkspaceView canvas) {
    for (int i=0; i<elements.length; i++)
      canvas.removeElement (elements[i]);
  }
}
