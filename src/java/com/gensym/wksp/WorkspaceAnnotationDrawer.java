package com.gensym.wksp;

import java.awt.Component;
import java.awt.Graphics;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;

/**
 * @undocumented
 */

public class WorkspaceAnnotationDrawer implements AnnotationDrawer {

  public final String MANUALLY_DISABLED = "MANUALLY_DISABLED";

   /**
    * @undocumented
    */
   public final String[] getAvailableAnnotations() {
     return new String[] {MANUALLY_DISABLED};
   }
    
   /**
    * @undocumented
    */    
   public boolean[] getCurrentAnnotationStates() {
     return currentAnnotationStates;
   }

   /**
    * @undocumented
    */    
   public void setCurrentAnnotationStates(boolean[] newStates) {
     currentAnnotationStates = newStates;
   }

  private Component disabledAnnotation = new DisabledAnnotation();

  @Override
  public void drawAnnotations(Component representer, Object represented, Graphics g) {
    if (represented instanceof Item)
      drawAnnotations(representer, (Item)represented, g);
  }

  private static boolean[] currentAnnotationStates = new boolean[]{false};

  protected void drawAnnotations(Component representer, Item represented, Graphics g) {
    if (currentAnnotationStates[0]) {
      try {
	if (represented.getManuallyDisabled()) {
	  disabledAnnotation.paint(g);
	}
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
  }
}
    
