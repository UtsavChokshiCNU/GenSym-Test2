package com.gensym.beaneditor;

import java.awt.Component;
import java.awt.Menu;
import java.awt.MenuItem;
import java.awt.Image;
import java.awt.Color;
import java.awt.Point;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.beans.*;
import java.util.Vector;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.menu.awt.CMenu;
import com.gensym.message.Resource;

class FriendConnectionCommands extends AbstractStructuredCommand{

  static final String DELETE = "DeleteFriendConnection";
  static final String EDIT = "EditFriendConnection";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private Object popupElement;
  private EditorFrame frame;

  FriendConnectionCommands(EditorFrame frame){
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("Delete", new CommandInformation[]{
	new CommandInformation(DELETE, true, shortResource, 
			       longResource, null, null, null, true)}),
	new CommandGroupInformation("Edit", new CommandInformation[]{
	  new CommandInformation(EDIT, true, shortResource, 
				 longResource, null, null, null, false)})});
    
    this.frame = frame;
  }

  @Override
  public void actionPerformed(ActionEvent actionEvent){
    String cmdKey = actionEvent.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    else if (cmdKey.equals(DELETE)) doDelete();
    else if (cmdKey.equals(EDIT)) doEdit();
  }
  
  private void doDelete(){
    BeanCanvas canvas = frame.getCanvas();
    KnowledgeLink link = getLink();
    link.removeLink();
  }
  
  private void doEdit(){
    frame.getBeanEditTool().editFriendLink(getLink());
  }
  
  void setPopupElement(Object element){
    popupElement = element;
    updateAvailability();
  }

  private void updateAvailability(){
    KnowledgeLink link = getLink();
    //setAvailable(EDIT, (link.object instanceof Wrapper));
    setAvailable(DELETE, (link.object instanceof KnowledgeLinkLooseEnd ||
			  !link.subject.anyKnownBeansInUse()));
    setAvailable(EDIT, !link.subject.anyKnownBeansInUse());
  }

  private KnowledgeLink getLink(){
    KnowledgeLink link;
    if (popupElement instanceof KnowledgeLinkLooseEnd){
      KnowledgeLinkLooseEnd end = (KnowledgeLinkLooseEnd)popupElement;
      return end.getLink();
    }
    else
      return(KnowledgeLink)popupElement;
  }
}
