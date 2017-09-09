
package com.gensym.swing;

import java.awt.Point;
import java.beans.*;

import javax.swing.*;
import com.gensym.swing.plaf.*;

/*

TO DO

1. Some sort of dimension control - other than 75x100
2. Implement Accessible
3. Metal L&F
4. Define UI interaction - selection?

*/

public class RowHeader extends JComponent /*implements Accessible*/ {

  public static final String uiClassID = "RowHeaderUI";
  private JTable table;

  static {
    try {
      // setup defaults table
      UIManager.getLookAndFeelDefaults ().put (uiClassID,
					       determineUIClassName (UIManager.getLookAndFeel()));
      // listen for L&F changes
      UIManager.addPropertyChangeListener (new PropertyChangeListener () {
	@Override
	public void propertyChange (PropertyChangeEvent pce) {
	  // if l&f changed and we can handle it,
	  // call getLookAndFeelDefaults().put (uiClassID, "??");
	}
      });
    } catch (Exception e) {
      e.printStackTrace ();
    }
  }

  private static String determineUIClassName (LookAndFeel lf) {
    String lfClassName = lf.getClass().getName();
    System.out.println ("L&F = " + lfClassName);
    if (lfClassName.equals ("com.sun.java.swing.plaf.windows.WindowsLookAndFeel"))
      return "com.gensym.swing.plaf.BasicRowHeaderUI";
    else if (lfClassName.equals ("com.sun.java.swing.plaf.motif.MotifLookAndFeel"))
      return "com.gensym.swing.plaf.MotifRowHeaderUI";
    else if (lfClassName.equals ("javax.swing.plaf.metal.MetalLookAndFeel"))
      return "oops";
    return "com.gensym.swing.plaf.BasicRowHeaderUI";
  }

  /**
   * Return the key for UI lookup
   */
  @Override
  public String getUIClassID() {
    return uiClassID;
  }

  /**
   * Narrow the argument type
   */
  public void setUI(RowHeaderUI ui){
    if (this.ui != ui) {
      super.setUI(ui);
      repaint();
    }
  }

  @Override
  public void updateUI(){
    setUI((RowHeaderUI)UIManager.getUI(this));
    revalidate();
    repaint ();
  }

  public RowHeader (JTable table) {
    this.table = table;
    updateUI ();
  }


  public JTable getTable () {
    return table;
  }

  public int rowAtPoint (Point p) {
    int rowHeight = table.getRowHeight ();
    return p.x/rowHeight;
  }

}
