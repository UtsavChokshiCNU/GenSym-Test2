package com.gensym.cbu.experimental.mibbrowser;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.ImageIcon;

public class FileExitAction extends AbstractAction
{
    public FileExitAction ()
    {
	super("Exit");
	putValue(Action.SHORT_DESCRIPTION,
		 "Quit MibBrowser");
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
	System.out.println("FileExitAction initiated from a " + 
			   e.getSource().getClass());
	System.exit(0);
    }
}
    
