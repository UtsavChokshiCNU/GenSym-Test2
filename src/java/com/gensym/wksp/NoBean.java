
package com.gensym.wksp;

import java.awt.Component;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Font;
import com.gensym.draw.TextCell;
import com.gensym.draw.TextStyle;

class NoBean extends Component {

  private TextCell textCell;
  private boolean formatted = false;

  NoBean (String beanClassName) {
    textCell = new TextCell(0,
			    beanClassName,
			    new TextStyle(new Font ("sansserif", Font.PLAIN, 14), 4,8,2),
			    null, Color.black, 0, null);
  }

  @Override
  public void setBounds (int x, int y, int width, int height) {
    super.setBounds (x, y, width, height);
    textCell.setWidth (width);
    formatted = false;
  }
  
  @Override
  public void paint (Graphics g) {
    g.setColor (Color.gray);
    Dimension size = getSize ();
    g.fill3DRect (0, 0, size.width, size.height, true);
    drawLabel (g);
  }

  private void drawLabel (Graphics g) {
    if (!formatted) {
      textCell.format (g);
      formatted = true;
    }
    textCell.draw (g, 0, 0);
  }

}
