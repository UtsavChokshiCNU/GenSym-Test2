
package com.gensym.tests;

import java.awt.*;
import javax.swing.*;

public class SplitPaneTest extends Frame {

  public SplitPaneTest (String title) {
    super (title);
  }


  public static void main (String[] args) throws Exception {
    //UIManager.setLookAndFeel (UIManager.getSystemLookAndFeelClassName ());
    SplitPaneTest spt = new SplitPaneTest ("Split Pane Test");
    JTextArea textArea0 = new JTextArea (), textArea1 = new JTextArea ();
    textArea0.setFont(new Font("Dialog", Font.PLAIN, 12));
    textArea0.setEditable (true);
    textArea1.setEditable (false);
    textArea0.setBackground (Color.white);
    textArea1.setBackground (Color.lightGray);

    JScrollPane scroller0 = makeScrollPane (600, 500);
    scroller0.getViewport().add(textArea0);

    JScrollPane scroller1 = makeScrollPane (600, 150);
    JPanel diagnostics = new JPanel ();
    diagnostics.setLayout (new BorderLayout ());
    JLabel l;
    diagnostics.add (l = new JLabel ("Compiler Diagnostics:"), BorderLayout.NORTH);
    l.setBackground (Color.red);
    diagnostics.add (scroller1, BorderLayout.CENTER);
    scroller1.getViewport().add (textArea1);

    JSplitPane sp = new JSplitPane (JSplitPane.VERTICAL_SPLIT,
				    scroller0, diagnostics);
    spt.add (sp, BorderLayout.CENTER);
    spt.pack ();
    sp.setDoubleBuffered (true);
    System.out.println (sp.isOneTouchExpandable ());
    spt.setVisible (true);
  }

  static JScrollPane makeScrollPane (int x, int y) {
    final int paneWidth = x, paneHeight = y;
    return new JScrollPane(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED) {
      @Override
      public Dimension getPreferredSize() {
	return new Dimension(paneWidth, paneHeight);
      }
      @Override
      public Dimension getMinimumSize () {
	return new Dimension (100, 100);
      }
      @Override
      public float getAlignmentX() {
	return LEFT_ALIGNMENT;
      }
    };
  }

}

