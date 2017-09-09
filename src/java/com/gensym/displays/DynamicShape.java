package com.gensym.displays;

import java.awt.*;

/** Encapsulates the ability to recompute bounds and indicate dissatisfaction
 * with new bounds.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 * @deprecated likely to be eliminated
 */
public interface DynamicShape {
  /** The contents of the <code>DynamicShape</code> object may have
   * changed, in which case the bounds may need recalculating */
  public Dimension formatShape() throws UnableToFormatException;

  /** The <code>DynamicShape</code> object promises to attempt to fit into
  * <code>maxBounds</code>, throwing an exception if unable to do so. If
  * the object already fits into maxBounds, this may be a no-op, though the
  * the <code>initialBounds</code> and <code>growVerticallyFirst</code>
  * values may indicate a new preferred shape, so the object could recompute
  * to find the smallest size within the preferred bounds. */
  public Dimension formatShape(Dimension initialBounds,
			       Dimension maxBounds,
			       boolean growVerticallyFirst)
  throws UnableToFormatException;

}
			  
