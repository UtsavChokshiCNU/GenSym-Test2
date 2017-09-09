/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BeanifierCommands.java
 *
 */
package com.gensym.beaneditor;

import java.awt.event.ActionEvent;
import java.util.Vector;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;

import com.gensym.com.BeanXporter;
import com.gensym.com.BeanXporterListener;
import com.gensym.com.BeanXporterEvent;

class BeanifierCommands extends AbstractCommand 
                        implements BeanXporterListener
{
  //Command Keys
  static final String OLE_OBJECT = "InsertOLEObject";
  static final String CONVERT_ACTIVEX_CONTROL = "ToolsConvertActiveXControl";

  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private EditorFrame frame;

  BeanifierCommands(EditorFrame frame){
    super(new CommandInformation[]{
      new CommandInformation(OLE_OBJECT, true, "CommandShortResource", "CommandLongResource", null, null, null, false),
	new CommandInformation(CONVERT_ACTIVEX_CONTROL, true, "CommandShortResource", "CommandLongResource", null, null, null, false)});
    this.frame = frame;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    }

    //System.out.println("BeanifierCommands handling command key:"+cmdKey);
    if (cmdKey.equals(OLE_OBJECT)) 
      frame.application.setBeanSelection("com.gensym.com.ActiveXGenericComponent", null);
    else if (cmdKey.equals(CONVERT_ACTIVEX_CONTROL)) doConvertActiveXControl();
  }

  private void doConvertActiveXControl(){
    BeanXporter bx = frame.application.beanifier;
    bx.addBeanXporterListener(this);
    bx.export(frame);
  }


  // **** BeanXporterListener interface ****
  @Override
  public void exportSuccess(BeanXporterEvent e) 
  {
    Object arg = e.arg;

    if (arg == null)
      return;

    if (! (arg instanceof String))
      return;

    String jarPath = (String) arg;
    if (jarPath.equals(""))
      return;

    frame.application.loadJar(jarPath, true);  
  }
  
  @Override
  public void exportFailure(BeanXporterEvent e)
  {
  }




  void updateAvailability(){
    if (frame.application.inDesignMode())
      setAvailable(OLE_OBJECT, true);
    else
      setAvailable(OLE_OBJECT, false);
  }

}

  
