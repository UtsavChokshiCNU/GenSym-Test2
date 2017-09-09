package com.gensym.gcg;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JPanel;
import com.gensym.controls.DialogCommand;
import com.gensym.message.Resource;

class GeneratedCommandPanel extends JPanel{

  private static final Resource i18n = Resource.getBundle("com.gensym.gcg.UiLabels");

  private static final String OK = "OK";
  private static final String APPLY = "Apply";
  private static final String CANCEL = "Cancel";

  GeneratedCommandPanel(DialogCommand dialogCommand){
    setLayout(new FlowLayout(FlowLayout.CENTER));
    ActionListener listener = new CommandButtonAdapter(dialogCommand);
    add(createButton(OK, listener));
    add(createButton(APPLY, listener));
    add(createButton(CANCEL, listener));
  }

  private JButton createButton(String key, ActionListener actionListener){
    JButton button = new JButton(i18n.getString(key));
    button.setActionCommand(key);
    button.addActionListener(actionListener);
    return button;
  }
  
  class CommandButtonAdapter implements ActionListener{
    
    private DialogCommand dialogCommand;
    
    CommandButtonAdapter(DialogCommand dialogCommand){
      this.dialogCommand = dialogCommand;
    }
    
    @Override
    public void actionPerformed(ActionEvent event){
      String key = event.getActionCommand();
      if (key.equals(OK))	
	dialogCommand.ok();
      else if (key.equals(APPLY))
	dialogCommand.apply();
      else
	dialogCommand.close();
    }
  }
  
}
