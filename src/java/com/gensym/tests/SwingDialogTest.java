
package com.gensym.tests;

import javax.swing.*;

public class SwingDialogTest {

  public static void main (String[] args) throws Exception {
    javax.swing.UIManager.setLookAndFeel(javax.swing.UIManager.getSystemLookAndFeelClassName());
    JOptionPane.showMessageDialog (null, "Message", "Message", JOptionPane.PLAIN_MESSAGE);
    JOptionPane.showMessageDialog (null, "Information", "Information", JOptionPane.INFORMATION_MESSAGE);
    JOptionPane.showMessageDialog (null, "Warning", "Warning", JOptionPane.WARNING_MESSAGE);
    JOptionPane.showMessageDialog (null, "Question", "Question", JOptionPane.QUESTION_MESSAGE);
    JOptionPane.showMessageDialog (null, "Error", "Error", JOptionPane.ERROR_MESSAGE);
    JOptionPane.showInputDialog (null, "Enter Some Data", "Input", JOptionPane.PLAIN_MESSAGE);
    Exception ex = new Exception ("Connection to G2 at bombay:1111 timed out due to the following problem:" +
				  "No Listener at port 1111 on host bombay found.");
    JOptionPane.showMessageDialog (null, ex.toString (), "Error", JOptionPane.ERROR_MESSAGE);
    JOptionPane.showMessageDialog (null, ex.toString () + com.gensym.core.DebugUtil.getStackTrace (), "Error",
				   JOptionPane.ERROR_MESSAGE);
    System.exit (0);
  }
}
