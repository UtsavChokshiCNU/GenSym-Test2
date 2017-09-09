package com.gensym.cbu.experimental.mibbrowser;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.ImageIcon;

public class HelpAboutAction extends AbstractAction
{
    public HelpAboutAction ()
    {
	super("About");
	putValue(Action.SHORT_DESCRIPTION,
		 "Show Version Info about MibBrowser");
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
	System.out.println("HelpAboutAction initiated from a " + 
			   e.getSource().getClass());
    }
}
    
