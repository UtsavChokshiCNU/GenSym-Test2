package com.gensym.ui.toolbar;

import java.awt.Insets;
import java.awt.Image;
import com.gensym.ui.Command;
import com.gensym.ui.CommandListener;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.LookAndFeel;
import javax.swing.JToggleButton;
import javax.swing.ImageIcon;

class ToolBarToggleButton extends JToggleButton{
  private String key;
  private ToolBarCommandAdapter cmdAdapter;

  ToolBarToggleButton(Command command, String cmdKey,
		      ToolBarCommandAdapter cmdAdapter,
		      RepresentationConstraints constraints){
    this(command, cmdKey, cmdAdapter, constraints,
	 ((Boolean)command.getState(cmdKey)).booleanValue());
  }

  ToolBarToggleButton(Command command, String cmdKey, ToolBarCommandAdapter
		      cmdAdapter, RepresentationConstraints constraints,
		      boolean state){
    int type = constraints.getRepresentationType();
    if ((type == constraints.TEXT_ONLY) || (type == constraints.TEXT_AND_ICON)){
      if (command.isImmediate(cmdKey))
	setText(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION));
      else
	setText(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION)+"...");
    }
    if ((type == constraints.ICON_ONLY) || (type == constraints.TEXT_AND_ICON)) {
      Image icon = command.getIcon(cmdKey, Command.SMALL_ICON);
      if (icon != null){
	ImageIcon img = new ImageIcon(icon);
	this.setIcon(img);
      }
    }
    if (LookAndFeel.getUseSnappyLookAndFeel())
      setRolloverEnabled(true);
    setHorizontalAlignment(constraints.getHorizontalAlignment());
    setVerticalAlignment(constraints.getVerticalAlignment());
    setHorizontalTextPosition(constraints.getHorizontalTextPosition());
    setVerticalTextPosition(constraints.getVerticalTextPosition());

    this.key = cmdKey;
    this.cmdAdapter = cmdAdapter;
    cmdAdapter.add(this);

    setMargin(new Insets(0, 0, 0, 0));
    setToolTipText(command.getDescription(cmdKey, Command.LONG_DESCRIPTION));
    this.addActionListener(command);
    if (!command.isAvailable(key)){
    	this.setEnabled(false);
    }
    this.setSelected(state);
  }

  @Override
  public String getActionCommand(){
    return this.key;
  }

  String getKey(){
    return key;
  }

  @Override
  protected void paintBorder(java.awt.Graphics g) {
    if (!LookAndFeel.getUseSnappyLookAndFeel() ||
	getModel().isRollover() ||
	isSelected() ||
	getModel().isPressed())
      super.paintBorder(g);
  }

}

