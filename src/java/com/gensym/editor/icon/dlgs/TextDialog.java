package com.gensym.editor.icon.dlgs;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Container;
import java.awt.Frame;
import java.awt.Font;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import com.gensym.dlg.StandardDialog;
import com.gensym.editor.icon.shapes.IconText;
import com.gensym.editor.icon.core.IconEditorCanvas;

public class TextDialog extends StandardDialog {

  protected IconText iconText;
  protected IconEditorCanvas canvas;
  protected JTextField xField, yField, textField;
  protected CoordinateListener coordinateListener;
  private Font defaultFont = new Font("sansserif", Font.PLAIN, 14);
  
  public TextDialog(Frame parent, IconText text,
		    IconEditorCanvas canvas) {
    super(parent, "Text Tool", false,
	  null, null, new JPanel(new BorderLayout()), null);
    xField = new JTextField();
    yField = new JTextField();
    coordinateListener = new CoordinateListener();
    xField.setColumns(5);
    xField.addActionListener(coordinateListener);
    yField.setColumns(5);
    yField.addActionListener(coordinateListener);
    iconText = text;
    this.canvas = canvas;
    textField = new JTextField();
    textField.setText(iconText.getExpression(IconText.TEXT).toString());
    textField.getDocument().addDocumentListener(new DocAdapter());
    if (iconText != null) {
      if (iconText.getExpression(IconText.X) != null)
	xField.setText(iconText.getExpression(IconText.X).toString());
      if (iconText.getExpression(IconText.Y) != null)
	yField.setText(iconText.getExpression(IconText.Y).toString());
    }
    this.addWindowListener(new MyWindowAdapter());
  }

  protected class MyWindowAdapter extends WindowAdapter {
    @Override
    public void windowClosing(WindowEvent e) {
      if (textField.getText().equals(""))
	iconText.setBounds(0,0,0,0);
    }
  }

  protected class CoordinateListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
      int x = 0; int y = 0;
      Object temp = iconText.getExpression(IconText.X);
      if (temp != null && temp instanceof Integer)
	x = ((Integer)temp).intValue();
      temp = null;
      if (xField.getText() != null && !(xField.getText().trim().equals("")))
	if (0 <= new Integer(xField.getText().trim()).intValue())
	  x = new Integer(xField.getText().trim()).intValue();
      temp = iconText.getExpression(IconText.Y);
      if (temp != null && temp instanceof Integer)
	y = ((Integer)temp).intValue();
      if (yField.getText() != null && !(yField.getText().trim().equals("")))
	if (0 <= new Integer(yField.getText().trim()).intValue())
	  y = new Integer(yField.getText().trim()).intValue();
      iconText.setBounds(x, y, 50, 20);
      canvas.getCurrentLayer().repaint();
      canvas.repaint();
    }
  }
  
  protected class DocAdapter implements DocumentListener {

    @Override
    public void changedUpdate(DocumentEvent e){}
    @Override
    public void insertUpdate(DocumentEvent e) {
      Document source = (Document)e.getDocument();
      String text = "";
      try {
	text = source.getText(0, source.getLength());
      } catch (BadLocationException ble) {//This should never happen
      }
      iconText.setText(text);
      canvas.getCurrentLayer().repaint();
      canvas.repaint();
    }
    
    @Override
    public void removeUpdate(DocumentEvent e) {
      Document source = (Document)e.getDocument();
      String text = "";
      try {
	text = source.getText(0, source.getLength());
      } catch (BadLocationException ble) {//This should never happen
      }
      iconText.setText(text);
      canvas.getCurrentLayer().repaint();
      canvas.repaint();
    }
    
  }
}
