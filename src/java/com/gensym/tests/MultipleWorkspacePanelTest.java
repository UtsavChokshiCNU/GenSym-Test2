
package com.gensym.tests;

import com.gensym.wksp.*;
import java.awt.*;
import java.awt.Button;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import java.awt.event.*;

public class MultipleWorkspacePanelTest extends Frame implements ActionListener {
  
  private MultipleWorkspacePanel mp;

  private static final Symbol KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE"),
                              FOO_          = Symbol.intern ("FOO"),
                              GOO_          = Symbol.intern ("GOO"),
                              BOO_          = Symbol.intern ("BOO");

  public static void main (String[] args) throws G2AccessException, ConnectionTimedOutException {
    MultipleWorkspacePanelTest p = new MultipleWorkspacePanelTest ();
    p.addWindowListener(new WindowAdapter() {
      @Override
      public void windowClosing(WindowEvent e) {
	System.exit(0);
      }
    });
    String host = args[0];
    String port = args[1];
    TwAccess context = TwGateway.openConnection (null, host, port);
    context.login();
    KbWorkspace w1 = (KbWorkspace) context.getUniqueNamedItem (KB_WORKSPACE_, FOO_);
    KbWorkspace w2 = (KbWorkspace) context.getUniqueNamedItem (KB_WORKSPACE_, GOO_);
    KbWorkspace w3 = (KbWorkspace) context.getUniqueNamedItem (KB_WORKSPACE_, BOO_);
    context.addWorkspaceShowingListener (p.mp);
    p.mp.addWorkspace (w1, true);
    p.mp.addWorkspace (w2, true);
    p.mp.addWorkspace (w3, true);
    p.mp.setCurrentWorkspace (w1);

    Button b;
    Panel controlPanel = new Panel();
    controlPanel.setLayout (new BorderLayout ());    
    b = new Button(">>>");
    b.addActionListener(p);
    controlPanel.add("East", b);
    b = new Button("<<<");
    b.addActionListener(p);
    controlPanel.add("West",b);
    b = new Button("CENTER");
    b.addActionListener(p);
    controlPanel.add("Center", b);
    p.add("North",controlPanel);
    p.setSize (500, 500);
    p.setVisible (true);
  }

  MultipleWorkspacePanelTest () {
    setLayout (new BorderLayout ());
    add (mp = new MultipleWorkspacePanel (), "Center");
  }
  

  @Override
  public void actionPerformed(ActionEvent e) {
    String arg = e.getActionCommand();
    
    if ("first".equals(arg)) {
      //  ((CardLayout)mView.getLayout()).first(view);
    } else if (">>>".equals(arg)) {
      mp.nextWorkspace();
    } else if ("<<<".equals(arg)) {
      mp.previousWorkspace();
    } else if ("last".equals(arg)) {
      //((CardLayout)cards.getLayout()).last(cards);
    } else {
      //((CardLayout)cards.getLayout()).show(cards,(String)arg);
    }
  }
}
