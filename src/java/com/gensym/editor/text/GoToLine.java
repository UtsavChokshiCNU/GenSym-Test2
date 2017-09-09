/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GoToLine.java
 *
 */
package com.gensym.editor.text;

import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.text.JTextComponent;
import javax.swing.JTextField;
import java.awt.FlowLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import com.gensym.message.Resource;


public class GoToLine extends Object implements ActionListener {

  private static final boolean debug = false;

  private static Resource i18n = 
  Resource.getBundle("com/gensym/editor/text/TextEditorLabels");

  JTextComponent target;
  JTextField field;
  Toolkit kit;
  
  public GoToLine(JTextComponent target) {
    this.target = target;
    setupUI();
  }


  gotoJPanel ui;
  public JPanel getUI() { return (JPanel)ui; }

  private void setupUI() {
    JLabel label = new JLabel(i18n.getString("gotoline"));
    field = new JTextField( 3 );  // number of columns
    field.setEditable( true );
    field.setText("");
    field.addActionListener( this );

    ui = new gotoJPanel();
    ui.setLayout( new FlowLayout() );
    ui.add(label);
    ui.add(field);

    kit = field.getToolkit();
  }

  class gotoJPanel extends JPanel {
    /* Passed through from G2TextEditor. */
    @Override
    public void requestFocus() {
      field.requestFocus();
    }
  }

  //---- ActionListener method that actually does the goto ----

  @Override
  public void actionPerformed(ActionEvent e) {
    if (debug)
      System.out.println("Starting go to calculation");
    String text = target.getText();
    int currentPos = target.getCaretPosition();
    int fieldValue = getFieldValue();
    if ( fieldValue >= 0 ) {
      if (debug)
	System.out.println("Go to line #" + fieldValue);
      int linePosition = findPositionCorrespondingToLine(text, fieldValue);
      int column = column(text, currentPos);
      int targetCaretPosition = sameColumnOrEndPosition(linePosition, column, text);
      if (debug)
	System.out.println("final target pos = " + targetCaretPosition);
      if (targetCaretPosition >= 0)
	target.setCaretPosition(targetCaretPosition);

      target.requestFocus();
      field.setText("");
    }
  }

  private int findPositionCorrespondingToLine(String text, int targetNumberOfLines) {
    int targetPosition = -1;
    int index = 0;
    int lastIndex = 0;
    for (int count = 0; ; count++){
      if (count == targetNumberOfLines) {
	targetPosition = lastIndex;
	break;
      }
      index = text.indexOf('\n', lastIndex + 1);
      if ( index == -1 ) {
	kit.beep();
	/* there aren't that many lines -- beep? --emacs goes to the end */
	targetPosition = lastIndex;
	break;
      } 
      if (debug)
	System.out.println("N = " + count + "  index = " + index);
      lastIndex = index;
    }
    return targetPosition;
  }

  private int getFieldValue() {
    int value = -1;
    String s = field.getText();
    if ( s.equals("") )
      kit.beep();
    else {
      try {
    	  value = Integer.parseInt(s);
      } catch (NumberFormatException e) {
	kit.beep();
	return -1;
      }
    }
    return value;
  }

  private int findDistanceToFirstNewlineOrStart(String text, int initialPosition) {
    int priorNewLine = text.lastIndexOf('\n', initialPosition);
    if (debug)
      System.out.println("priorNewLine = " + priorNewLine);
    if ( priorNewLine == -1 )
      return 0;
    else
      return priorNewLine;
  }

  private int column(String text, int initialPosition) {
    int thisLineStartsAt = findDistanceToFirstNewlineOrStart(text, initialPosition);
    return initialPosition - thisLineStartsAt;
  }


  /* The  linePosition will be at the end of the line, so we subtract
   * in order to get the the same column as we started at. */
  private int sameColumnOrEndPosition(final int eolPos, final int column, final String text) {
    int startOfThisLine = findDistanceToFirstNewlineOrStart(text, eolPos -1);
    int columnIndex = column;
    if (debug)
      System.out.println("Line ends at " + eolPos + 
			 " and starts at " + startOfThisLine + 
			 " column = " + columnIndex);
    int lineLength = eolPos - startOfThisLine;
    if (lineLength > columnIndex) {
      /* startOfThisLine, when taken as a cursor position, will display
       * at the end of the prior line. So if column is 0 we need to 
       * bump it to get onto the line we're aiming for. */
      if ( columnIndex==0 ){
    	  columnIndex++;
      }
      return startOfThisLine + columnIndex;
    }
    else
      return eolPos;
  }
}
