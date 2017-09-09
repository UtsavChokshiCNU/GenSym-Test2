package com.gensym.wksp;

import java.awt.*;
import com.gensym.classes.Entity;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;

/**
 *
 * WorkspaceLooseEndImpl <p>
 * A WorkspaceElement for representing a connection's end that is
 * not connnected to an item.  Usually does not appear visually.
 * Can be used for input handling, for dragging the connection
 * to which it is attached.
 *
 */
public class WorkspaceLooseEndImpl extends WorkspaceIconImpl {

  private static boolean workspaceLooseEndDebugP = false;

  /**
   * @param item The g2 item which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   */
  public WorkspaceLooseEndImpl(/*LooseEnd*/Item looseEnd, WorkspaceView parent)
       throws G2AccessException {
    super((Entity)looseEnd, parent);
  }

  /**
   * Paints nothing, unless in debug mode, in which case it
   * paints a red rectangle encompassing the bounds of this
   * element.
   */
  @Override
  public void paint(Graphics g) {
    if (workspaceLooseEndDebugP) {
      g.setColor(Color.red);
      Rectangle[] bounds = getExactBounds();
      g.fillRect(0, 0, bounds[0].width, bounds[0].height);
    }
  }

}

