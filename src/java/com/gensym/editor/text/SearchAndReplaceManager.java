/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SearchAndReplaceManager.java
 *
 *
 * Version 1.2  May 1999
 * Author: ddm
 *
 */
package com.gensym.editor.text;

import javax.swing.JPanel;
import javax.swing.JFrame;
import java.awt.FlowLayout;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Window;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import com.gensym.core.GensymLogo;
import com.gensym.message.Resource;


class SearchAndReplaceManager implements ActionListener {

  private JFrame frame;
  private SearchField search;
  private Session session;

  JButton next, prior;

  private static Resource i18n = 
     Resource.getBundle("com/gensym/editor/text/TextEditorLabels");




  /* The constructor brings up a frame and lays out the text field and
   * button. After that everything is event driven by the user typing
   * into the text field or clicking the buttons.  This managers the
   * enablement state of the buttons given the results of the searches
   * (which are update with each text event on the text field) and
   * handles their action events. */

  SearchAndReplaceManager(TextSearchTarget editor) {
    this.session = session;

    search = new SearchField(editor);

    frame = new JFrame(i18n.getString("Search"));
    frame.getContentPane().setLayout( new FlowLayout( FlowLayout.LEFT ) ); 
                                                   // or align, hgap, vgap
    frame.getContentPane().add(search);

    frame.setIconImage(GensymLogo.get());

    JPanel p = new JPanel();
    next = new JButton(i18n.getString("FindNext"));
    next.setActionCommand("next");
    p.add(next);
    prior = new JButton(i18n.getString("FindPrevious"));
    prior.setActionCommand("prior");
    p.add(prior);
    frame.getContentPane().add(p);

    /* Old reasoning: You don't know if you can find another one until you've found
     *   at least one instance already, so these start out disabled. 
     * New: There are bugs in the update logic. Starting the buttons out enabled
     *   and leaving them that way. User will get beeps when there are no more
     *   instances to be found.  */
    next.setEnabled( true );
    prior.setEnabled( true );

    next.addActionListener( this );
    prior.addActionListener( this );

    frame.addWindowListener
      (
       new WindowAdapter () {
	@Override
	public void windowClosing (WindowEvent we) {
	  frame.setVisible( false ); 
	}
      }
	);

    frame.pack();
    frame.setVisible( true );
  }


  
  @Override
  public void actionPerformed(ActionEvent e) {
    String command = e.getActionCommand();
    if ( command.equals("next") )
      nextButtonLogic();
    else 
      if ( command.equals("prior") )
	priorButtonLogic();
  }


  void nextButtonLogic() {
    search.setDirection( SearchField.FORWARDS );
    search.setReferenceCursor( search.getDot() );
    search.search();
    //    if ( search.getMatched() )
    //      prior.setEnabled( true );
  }

  void priorButtonLogic() {
    search.setDirection( SearchField.BACKWARDS );
    search.setReferenceCursor( boundsCheck( search.getMark() ) );
    search.search();
    //    if ( search.getMatched() )
    //      next.setEnabled( true );
  }


  /* (In a better world, e.g. Lisp, this would be a macrolet because it's
   *  so special purpose and knows so much about its argument).
   * The search.mark is set by indexOf. As a result, if there is no match
   * it can have the value -1, which is not going to work as the starting
   * point of a search. */
  private int boundsCheck(int newReferencePoint ) {
    if ( newReferencePoint == -1 ) {
      return search.getDot() // the right endpoint of the last match. It is only 
	                     // reset if there is a match.
              - search.getPattern().length();
    }
    else
      return newReferencePoint;
  }



  /* These are used by Session when its search initiation method is
   * used again after there has already been a search up and at the
   * end of the session. */

  void show() { 
    frame.setVisible( true ); 
    search.selectAll();
    search.requestFocus();
  }

  void shutdown() { frame.dispose(); }

}

  
