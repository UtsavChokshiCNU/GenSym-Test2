/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 FindAndReplace.java
 *
 *
 * Version 1.0  April 2000
 * Author: ddm
 *
 */
package com.gensym.editor.text;

import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.BoxLayout;
import javax.swing.BorderFactory;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;
import java.awt.FlowLayout;
import java.awt.Color;
import java.awt.Toolkit;
import java.awt.Window;
import java.awt.Dimension;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import com.gensym.core.GensymLogo;
import com.gensym.message.Resource;


class FindAndReplace extends JFrame implements ActionListener, ServiceStateListener {

  private boolean debug = false;

  private JFrame frame;
  private SearchField search;
  private JTextField replace;
  private TextSearchTarget editor;

  JButton next, prior, replaceButton, replaceAllButton;
  JLabel searchLabel, replaceLabel;
  JPanel searchPanel, replacePanel, 
    searchButtonsPanel, replaceButtonsPanel,
    buttonsPanel, inputFields;

  private static Resource i18n = 
     Resource.getBundle("com/gensym/editor/text/TextEditorLabels");




  /* The constructor brings up a frame and lays out the text field and
   * button. After that everything is event driven by the user typing
   * into the text field or clicking the buttons.  This managers the
   * enablement state of the buttons given the results of the searches
   * (which are update with each text event on the text field) and
   * handles their action events. */

  FindAndReplace(TextSearchTarget editor) {
    this.editor = editor;

    setTitle(i18n.getString("SearchAndReplace"));
    setBackground(Color.lightGray);
    setIconImage(GensymLogo.get());

    //--- buttons
    next = new JButton(i18n.getString("FindNext"));
    next.setActionCommand("next");
    next.setEnabled( true );
    next.addActionListener( this );

    prior = new JButton(i18n.getString("FindPrevious"));
    prior.setActionCommand("prior");
    prior.setEnabled( true );
    prior.addActionListener( this );

    replaceButton = new JButton(i18n.getString("ReplaceButton"));
    replaceButton.setActionCommand("replace");
    replaceButton.setEnabled( false );
    replaceButton.addActionListener( this );

    replaceAllButton = new JButton(i18n.getString("ReplaceAllButton"));
    replaceAllButton.setActionCommand("replaceAll"); 
    replaceAllButton.setEnabled( false );
    replaceAllButton.addActionListener( this );



    //--- The Search field
    search = new SearchField(editor);
    searchLabel = new JLabel(i18n.getString("FindLabel"));
    searchPanel = new JPanel();
    searchPanel.setLayout( new BoxLayout(searchPanel, BoxLayout.X_AXIS) );
    searchPanel.add(searchLabel);
    searchPanel.add(search);

    //--- Replace field
    replace = new ReplaceField();
    replaceLabel = new JLabel(i18n.getString("ReplaceLabel") );
    replacePanel = new JPanel();
    replacePanel.setLayout( new BoxLayout(replacePanel, BoxLayout.X_AXIS) );
    replacePanel.add(replaceLabel);
    replacePanel.add(replace);


    //--- put it all together
    setupLook();

    //--- listen to the search results
    search.addServiceStateListener( this );

    //--- the rest

    addWindowListener
      (
       new WindowAdapter () {
	@Override
	public void windowClosing (WindowEvent we) {
	  setVisible( false ); 
	}
      }
	);

    pack();
    setVisible( true );
  }




  //--- button action dispatch

  @Override
  public void actionPerformed(ActionEvent e) {
    String command = e.getActionCommand();
    if ( command.equals("next") )
      nextButtonLogic();
    else if ( command.equals("prior") )
      priorButtonLogic();
    else if ( command.equals("replace") )
      replaceButtonLogic();
    else if ( command.equals("replaceAll") )
      replaceAllButtonLogic();
  }


  /* Sent by SearchField depending on the match result of a search. */
  @Override
  public void serviceStateChanged (ServiceStateEvent event) {
    String service = event.getService();
    if (service.equals(event.Replace)) {
      replaceButton.setEnabled(event.getState());
      replaceAllButton.setEnabled(event.getState());
    }
  }


  void nextButtonLogic() {
    search.setDirection( SearchField.FORWARDS );
    search.setReferenceCursor( search.getDot() );
    search.search();
  }

  void priorButtonLogic() {
    search.setDirection( SearchField.BACKWARDS );
    search.setReferenceCursor( boundsCheck( search.getMark() ) );
    search.search();
  }

  void replaceButtonLogic() {
    String replacement = replace.getText();
    if ( !replacement.equals("") ) {
      editor.replaceRegion(replacement, search.getMark(), search.getDot());
    }
  }

  void replaceAllButtonLogic() {
    while ( search.getMatched() ) {
      replaceButtonLogic();
      nextButtonLogic();
    }
  }


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
  // With this implemented as a frame this show -> setVisible interacts
  // with the one in JFrame and you get an infinite loop. It's presumably
  // completely superfluous -- so check that and then delete this
  //  public void show() { 
  //    if ( !isVisible() ) {
  //      setVisible( true ); 
  //      search.selectAll();
  //      search.requestFocus();
  //    }
  //  }

  void shutdown() { dispose(); }


  class ReplaceField extends JTextField { }




  void setupLook() {
    search.setPreferredSize( new Dimension(100, 20));
    replace.setPreferredSize( new Dimension(100, 20));
    search.setMaximumSize( new Dimension(200, 20));
    replace.setMaximumSize( new Dimension(200, 20));
    search.setMinimumSize( new Dimension(25, 20));
    replace.setMinimumSize( new Dimension(25, 20));

    /* Separate the labels from the text fields. */
    searchLabel. setBorder(BorderFactory.createEmptyBorder(0,0,0,2)); // top, left, bottom, right
    replaceLabel.setBorder(BorderFactory.createEmptyBorder(0,0,0,2));

    /* Separate the two fields. */
    searchPanel.setBorder(BorderFactory.createEmptyBorder(0,0,15,0));

    inputFields = new JPanel();
    inputFields.setLayout( new BoxLayout(inputFields, BoxLayout.Y_AXIS) );
    inputFields.add(searchPanel);
    inputFields.add(replacePanel);
    /* Separate the fields from the buttons. */
    inputFields.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 7));

    searchButtonsPanel = new JPanel();
    searchButtonsPanel.add(next); 
    searchButtonsPanel.add(prior);
    /* Separate the two sets of buttons. */
    searchButtonsPanel.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 5));

    replaceButtonsPanel = new JPanel();
    replaceButtonsPanel.add(replaceButton);
    replaceButtonsPanel.add(replaceAllButton);

    buttonsPanel = new JPanel();
    buttonsPanel.setLayout( new BoxLayout(buttonsPanel, BoxLayout.Y_AXIS) );
    buttonsPanel.setBorder(BorderFactory.createEmptyBorder(2, 0, 5, 5));
    buttonsPanel.add(searchButtonsPanel);
    buttonsPanel.add(replaceButtonsPanel);

    getContentPane().setLayout( new BoxLayout( getContentPane(), BoxLayout.X_AXIS) );
    getContentPane().add(inputFields);
    getContentPane().add(buttonsPanel);

  }


}

  
