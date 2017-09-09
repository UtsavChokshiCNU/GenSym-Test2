package com.gensym.beaneditor;

import java.awt.Component;
import java.awt.Point;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.util.Vector;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;

class InsertFriendConnectionCommand extends AbstractCommand{

  private static final String INSERT_FRIEND_CONNECTION = "InsertFriendConnection";

  private EditorFrame frame;

  InsertFriendConnectionCommand(EditorFrame frame, String label){
    super(new CommandInformation[]{
      new CommandInformation(INSERT_FRIEND_CONNECTION, true, null, null, 
				 null, null, null, true, label, label, null, null)});
    this.frame = frame;
    updateAvailability();
  }

  void updateAvailability(){
    
    setAvailable(INSERT_FRIEND_CONNECTION, 
		 (frame.getBeanEditTool() == null ? false : frame.getBeanEditTool().selectionCount() == 1));
  }

  @Override
  public void actionPerformed(ActionEvent actionEvent){
    String cmdKey = actionEvent.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException("Command is unavailable");
    if (cmdKey.equals(INSERT_FRIEND_CONNECTION)){
      Component[] selection = frame.getBeanEditTool().getSelection();
      Wrapper currentWrapper = (Wrapper)selection[0];
      Point location = currentWrapper.getLocation();
      int x = location.x + currentWrapper.getSize().width;
      int y = location.y + (currentWrapper.getSize().height / 2);
      KnowledgeLinkLooseEnd end = new KnowledgeLinkLooseEnd(x+25, y-5, 10, 10);
      frame.getCanvas().addElement(end);
      Point center1 = currentWrapper.centerPoint(), center2 = new Point(x+25, y);
      Point[] points = { center1, center2 };
      int[] widths = { 1 };
      String[] stripeNames = { "only" };
      Color[] colors = { Color.black };
      String[] colorNames = { "only" };
      KnowledgeLink link = new KnowledgeLink(null, currentWrapper, end,
					     points, widths, stripeNames,
					     colorNames, colors);
      end.setLink(link);
      //add links to end so they don't get in the way of drag & drop
      frame.getCanvas().addElement(link, -1); 
    }
  }
}
