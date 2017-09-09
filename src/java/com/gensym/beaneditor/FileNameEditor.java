package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;

import java.beans.*;

public class FileNameEditor extends Panel implements PropertyEditor, ActionListener, 
KeyListener{

  private PropertyChangeSupport support = new PropertyChangeSupport(this);
  private TextField textField;
  private Button browseButton;
  private String fileName = "";
  private String prevJarDir;

  public FileNameEditor(){
    textField = new TextField(30);
    textField.addKeyListener(this);
    add(textField);
    browseButton = new Button("Choose File...");
    browseButton.addActionListener(this);
    add(browseButton);
  }

  @Override
  public void actionPerformed(ActionEvent event){
    Object source = event.getSource();
    if (source instanceof Button){
      FileDialog fd = new FileDialog(ComponentEditor.getCurrentFrame(), "Load Jar", FileDialog.LOAD);	
      if (prevJarDir == null)
      prevJarDir = System.getProperty("user.dir");
      fd.setDirectory (prevJarDir);
      fd.setFile("*.jar");
      fd.show();
      String fname = fd.getFile();
      String dname = fd.getDirectory();
    
      if (fname != null && dname != null){
	prevJarDir = dname;
	setValue(dname+fname);
	support.firePropertyChange("",null,null);
      }
    }
    else
      support.firePropertyChange("",null,null);
  }

  @Override
  public void keyReleased(KeyEvent e){
    support.firePropertyChange("",null,null);
  }
  
  @Override
  public void keyPressed(KeyEvent e){}
  
  @Override
  public void keyTyped(KeyEvent e){}

  //PropertyEditor methods
  @Override
  public void setValue(Object value){
    fileName = (String)value;
    textField.setText(fileName);
  } 

  @Override
  public Object getValue(){
    fileName = textField.getText();
    return fileName;
  } 

  @Override
  public String getAsText(){
    return null;
  } 

  @Override
  public void setAsText(String text) throws IllegalArgumentException{
    throw new IllegalArgumentException("setAsText not supported");
  } 

  @Override
  public String[] getTags(){
    return null;
  } 

  @Override
  public boolean isPaintable(){
    return true;
  } 

  @Override
  public void paintValue(Graphics gfx , Rectangle box) {
    Color oldColor = gfx.getColor();
    Font oldFont = gfx.getFont();
    gfx.setColor(Color.white);
    gfx.fillRect(box.x+1, box.y+1, box.width-4, box.height-4);
    gfx.setColor(Color.black);
    gfx.drawRect(box.x, box.y, box.width-3, box.height-3);
    gfx.setFont(new Font("Courier",Font.PLAIN,12));
    FontMetrics metrics = gfx.getFontMetrics();
    gfx.drawString(fileName,box.x+4,box.y+3+metrics.getAscent());
    gfx.setColor(oldColor);
    gfx.setFont(oldFont);
  }

  @Override
  public String getJavaInitializationString(){
    return "ColorMap.getDefaultTable()";
  }

  @Override
  public void addPropertyChangeListener(PropertyChangeListener listener){
    support.addPropertyChangeListener(listener);
  } 
  @Override
  public void removePropertyChangeListener(PropertyChangeListener listener){
    support.removePropertyChangeListener(listener);
  } 

  @Override
  public boolean supportsCustomEditor(){
    return true;
  } 

  @Override
  public Component getCustomEditor(){
    return this;
  } 

  @Override
  public void setEnabled(boolean state){
    super.setEnabled(state);
    textField.setEnabled(state);
    browseButton.setEnabled(state);
  }
}
