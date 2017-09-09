package com.gensym.displays;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.G2FontMap;
import com.gensym.draw.TextCell;
import com.gensym.draw.TextStyle;
import java.util.*;
import java.awt.*;

/** A container that holds usually just a text string, but can also hold
 * any other visual element that could be associated with a label.
 * has convenience methods for having an icon to the left or right of
 * the label text. Currently only the text part is implemented.
 * This turns out to be somewhat analagous to java.swing.JLabel.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */

public class ChartLabel extends Component implements DynamicShape {
  public static final TextStyle DEFAULT_TEXT_STYLE =
  new TextStyle(G2FontMap.HM14, 0, 0, 2);

  public static final Color DEFAULT_TEXT_COLOR = Color.black;
  public static final Color DEFAULT_BACKGROUND_COLOR = Color.white;
  public static final int DEFAULT_MARGIN = 4;
  public static final int DEFAULT_BOTTOM_MARGIN = 2;
  private static Resource i18n =
  Resource.getBundle("com.gensym.displays.Messages");
  private static Resource i18nTrace =
  Resource.getBundle("com.gensym.displays.TraceMessages");
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays", ChartLabel.class);

  private boolean needsFormatting = true;
  private boolean valid = false;
  private boolean invalidElement = false;

  private boolean growVerticallyFirst;
  private Dimension maxSize;
  private TextCell textCell;

  /** @param maxSize attempts to grow the label beyond this dimension
   * will result in an error message displayed in the label.
   * @param initialSize initial values for both dimensions are derived
   * from this dimension, and the non-growing dimension will maintain this
   * value until the growing dimension reaches its max.
   * @param growVertically First defaults to <code>true</code>. Grows
   * horizontally if <code>false</code>. currently, only growVerticallyFirst
   * is emplemented.
   * @see format() */
  public ChartLabel(Dimension initialSize,
		    Dimension maxSize,
		    boolean growVerticallyFirst,
		    String initialText,
		    TextStyle textStyle,
		    int justification,
		    Color backgroundColor,
		    Color textColor,
		    int borderWidth,
		    Color borderColor) {
    textCell = new TextCell(initialSize.width, initialText, textStyle,
			    backgroundColor, textColor,
			    borderWidth, borderColor);
    Trace.send(10, traceKey, i18nTrace, "ChartLabel", initialSize, backgroundColor,
	       textColor);
    setSize(initialSize);
    this.maxSize = maxSize;
    this.growVerticallyFirst = growVerticallyFirst;
    textCell.setTextJustification(justification);
    textCell.setLeftMargin(DEFAULT_MARGIN);
    textCell.setRightMargin(DEFAULT_MARGIN);
    textCell.setTopMargin(DEFAULT_MARGIN);
    textCell.setBottomMargin(DEFAULT_BOTTOM_MARGIN);
  }

  @Override
  public Dimension formatShape() throws UnableToFormatException {
    return formatShape(getSize(), maxSize, growVerticallyFirst);
  }

  /** Currently, reformatting will only take place if the current
   * size exceed the <code>newMaxSize</code> or if the label
   * has already been marked as needing formatting (e.g., if the text has
   * changed. Also, newSize is ignored for now if formatting is not
   * necessary. */
  @Override
  public Dimension formatShape(Dimension newSize,
			       Dimension newMaxSize,
			       boolean newGrowVerticallyFirst)
  throws UnableToFormatException {
    if(newSize.width > newMaxSize.width ||
       newSize.height > newMaxSize.height) {
      throw new IllegalArgumentException
	(i18n.format("SizeExceedsMaxSize", newSize, newMaxSize));
    }
    Trace.send(10, traceKey, i18nTrace, "clformatShape1",
	       newSize, newMaxSize, getSize());
    int height = newSize.height;
    int width = newSize.width;
    needsFormatting = (needsFormatting ||
		       (height > newMaxSize.height) ||
		       (width > newMaxSize.width));

    if(!needsFormatting)
      return getSize();

    String cellText = textCell.getText();
      
    if (cellText == null || "".equals(cellText)) {
      height = 0;
    } else {
      maxSize = newMaxSize;
      growVerticallyFirst = newGrowVerticallyFirst;
      textCell.setWidth(newSize.width);
      textCell.format(this);
      newSize.height = textCell.getHeight();
      
      if (textCell.getHeight() > maxSize.height) {
	// too high, try growing horizontally
	textCell.setWidth(maxSize.width);
	textCell.format(this);
	if (textCell.getHeight() > maxSize.height) {
	  // still couldn't fit
	  invalidElement = true;
	  newSize = maxSize;
	  needsFormatting = false;
	  throw new UnableToFormatException(i18n.format("TextExceedsMaxSize",
							new Object[]
							{textCell.getText(),
							   getSize(),
							   maxSize}));
	}
      }
    }

    setSize(newSize);
    invalidElement = false;
    needsFormatting = false;
    invalidate();
    Dimension size = getSize();
    Trace.send(10, traceKey, i18nTrace, "clformatShape2", size);
    return size;
  }

  public void setTextColor(Color color) {
    textCell.setTextColor(color);
    repaint();
  }

  public Color getTextColor() {
    return textCell.getTextColor();
  }

  @Override
  public void invalidate() {
    super.invalidate();
    valid = false;
  }

  public void invalidateFormat() {
    needsFormatting = true;
  }

  public void setText(String text) {
    textCell.setText(text);
    invalidateFormat();
    invalidate();
  }

  /** Note that this does not guarantee that the label will end up
   * this width, only that it will attempt to fit within this width.
   * @see setMaxSize */
  public void setWidth(int width) {
    textCell.setWidth(width);
    invalidateFormat();
    invalidate();
  }

  /** This method has no idea if it is possible to fit within the
   * the dimensions inidicated. That is determined the next time
   * the label is formatted.
   * @see format(Graphics)
   */
  public void setMaxSize(Dimension newMaxSize){
    maxSize = newMaxSize;
    invalidateFormat();
  }

  @Override
  public void paint(Graphics g) {
    textCell.draw(g, 0, 0);
  }
}
