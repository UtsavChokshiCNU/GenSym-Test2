package com.gensym.gcg;

import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.ImageIcon;
import javax.swing.JButton;

/**
 * SubDialogLauncher is a button that launches a sub dialog for editing an attribute.
 */
public class SubDialogLauncher extends JButton{

  private static final Class thisClass = com.gensym.gcg.SubDialogLauncher.class;

  private EditedBySubDialog editor;

  public SubDialogLauncher(EditedBySubDialog editor){
    this.editor = editor;
    setMargin(new Insets(0, 0, 0, 0));
    ImageIcon img = 
      new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("more-dots.gif")));
    setIcon(img);
    addActionListener(new ActionAdapter());
  }

  class ActionAdapter implements ActionListener{
    @Override
    public void actionPerformed(ActionEvent e){
      editor.launchSubDialog();
    }
  }
  
}

