package com.gensym.shell.commands;

import java.awt.Frame;
import com.gensym.mdi.MDIFrame;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.StructuredCommandInformation;

abstract class BasicCommand extends AbstractStructuredCommand{

  private Frame frame;
  private boolean mdiApplication;

  protected BasicCommand(StructuredCommandInformation[] structure, Frame frame){
    super(structure);
    this.frame = frame;
  }

  protected Frame getFrame(){
    return frame;
  }

  protected boolean isMDIApplication(){
    return frame instanceof MDIFrame;
  }

  protected void setAvailability(boolean available){
    String[] keys = getKeys();
    for (int i=0; i<keys.length; i++)
      setAvailable(keys[i], available);
  }

}
