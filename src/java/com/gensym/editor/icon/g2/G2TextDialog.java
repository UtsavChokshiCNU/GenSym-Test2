package com.gensym.editor.icon.g2;

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
import com.gensym.editor.icon.dlgs.TextDialog;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.g2.Util;
import com.gensym.message.Trace;
import com.gensym.ntw.util.G2FontMap;
import com.gensym.util.Symbol;

public class G2TextDialog extends TextDialog {

  public G2TextDialog(Frame parent, IconText text,
		    IconEditorCanvas canvas) {
    super(parent, text, canvas);
    JPanel component = (JPanel)getDialogComponent();
    JComboBox fontChooser = new JComboBox(new Object[]{"small", "large", "extra-large"});
    setInitialFont(fontChooser, text);
    JPanel fontPanel = new JPanel();
    fontPanel.add(new JLabel("Font Size: "));
    fontPanel.add(fontChooser);
    fontChooser.addActionListener(new FontListener());
    component.add(fontPanel, "South");
    component.add(textField);
    JPanel coordinatePanel = new JPanel();
    coordinatePanel.add(new JLabel("x: "));
    coordinatePanel.add(xField);
    coordinatePanel.add(new JLabel("y: "));
    coordinatePanel.add(yField);
    Object y = iconText.getExpression(IconText.Y);
    if (y instanceof Integer) {
      yField.setText(new Integer(((Integer)y).intValue() +
		     (int)iconText.getBounds().getHeight()).toString());
    }
    yField.removeActionListener(coordinateListener);
    xField.removeActionListener(coordinateListener);
    CoordinateListener cl = new CoordinateListener();
    yField.addActionListener(cl);
    xField.addActionListener(cl);
    component.add(coordinatePanel, "North");
    pack();
  }

  private IconText getIconText() {
    return iconText;
  }

  private JTextField getXField() {
    return xField;
  }

  private JTextField getYField() {
    return yField;
  }  

  private IconEditorCanvas getCanvas() {
    return canvas;
  }
  
  private void setInitialFont(JComboBox box, IconText iconText) {
    Object fontExpression = iconText.getExpression(IconText.FONT);
    if (fontExpression instanceof Font) {
      Font font = (Font)fontExpression;
      if (font.getSize() >= 24)
	box.setSelectedIndex(2);
      else if (font.getSize() >= 18)
	box.setSelectedIndex(1);
      else box.setSelectedIndex(0);
    }
    else if (fontExpression instanceof Symbol){
      if (fontExpression == Util.SMALL_)
	box.setSelectedIndex(0);
      else if (fontExpression == Util.LARGE_)
	box.setSelectedIndex(1);
      else if (fontExpression == Util.EXTRA_LARGE_)
	box.setSelectedIndex(2);
    }
  }
  protected class CoordinateListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
      IconText iconText = getIconText();
      JTextField xField = getXField();
      JTextField yField = getYField();
      IconEditorCanvas canvas = getCanvas();
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
      iconText.setBounds(x, y-20, 50, 20);
      canvas.getCurrentLayer().repaint();
      canvas.repaint();
    }
  }
  class FontListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      if (source instanceof JComboBox) {
	IconText iconText = getIconText();
	IconEditorCanvas canvas = getCanvas();	
	String fontChoice = (String)((JComboBox)source).getSelectedItem();
	if (fontChoice.equals("small"))
	  iconText.setFont(G2FontMap.get(Symbol.intern("SMALL")));
	else if (fontChoice.equals("large"))
	  iconText.setFont(G2FontMap.get(Symbol.intern("LARGE")));
	else if (fontChoice.equals("extra-large"))
	  iconText.setFont(G2FontMap.get(Symbol.intern("EXTRA-LARGE")));
	canvas.getCurrentLayer().repaint();
	canvas.repaint();
      }
    }
  }

}
