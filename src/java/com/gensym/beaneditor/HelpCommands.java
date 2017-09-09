package com.gensym.beaneditor;

import com.gensym.dlg.AboutDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.ErrorDialog;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.message.Resource;
import java.awt.TextArea;
import java.awt.event.ActionEvent;

class HelpCommands extends AbstractStructuredCommand
{
    private static final String CONTENTS = "HelpContents";
    private static final String ABOUT = "HelpAbout";
    private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");
    private EditorFrame frame;

    HelpCommands(EditorFrame editorFrame)
    {
      super(new StructuredCommandInformation[]{
	//new CommandGroupInformation("OnLineHelp", new CommandInformation[]{
	//  new CommandInformation(CONTENTS, true, "CommandShortResource", "CommandLongResource", null, null, null, false)}),	  
	new CommandGroupInformation("About", new CommandInformation[]{
	  new CommandInformation(ABOUT, true, "CommandShortResource", "CommandLongResource", null, null, null, false)})});
        frame = editorFrame;
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent)
    {
        String cmdKey = actionEvent.getActionCommand();
        if (cmdKey == null) return;
        if (!isAvailable(cmdKey))
            throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));

        if (cmdKey.equals(ABOUT)) doAbout();
	else if (cmdKey.equals(CONTENTS)) doContents();
    }

  private void doContents(){
    LaunchHelpFile.launch(frame);
  }
    
  private void doAbout(){
    new AboutDialog(frame, "About Component Editor", true, "Component Editor \nVersion SEQUOIA_PRODUCT_VERSION \nCopyright (C) 1986-2017 Gensym Corporation. \nAll rights reserved.", 3, 40, 20, null).setVisible(true);
  }
  
}



