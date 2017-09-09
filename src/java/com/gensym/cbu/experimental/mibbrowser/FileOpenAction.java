package com.gensym.cbu.experimental.mibbrowser;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;
import javax.swing.filechooser.*;
import java.util.*;

public class FileOpenAction extends AbstractAction
{
  Vector listeners = new Vector();

  public void addFileOpenActionListener(FileOpenActionListener listener)
    {
      listeners.add(listener);
    }

  public void removeFileOpenActionListener(FileOpenActionListener listener)
    {
      listeners.remove(listener);
    }

  void fireFileOpenEvent (File file)
    {
      for (Enumeration e = listeners.elements(); e.hasMoreElements(); )
	((FileOpenActionListener)(e.nextElement())).openFile(file);
    }
  
    public FileOpenAction ()
    {
	super("Open...", new ImageIcon("resources/fileopen.gif"));
	putValue(Action.SHORT_DESCRIPTION,
		 "Open a new MibFile");
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent)
    {
        JFileChooser fileChooser
	  = new JFileChooser("d:/gensym/pinpoint/event handling/mibs");
	fileChooser.setFileFilter(new javax.swing.filechooser.FileFilter() {
	    @Override
	    public boolean accept(File pathname)
	      {
		return true;
	      }

	    @Override
	    public String getDescription()
	      {
		return "All Files (*)";
	      }

	  });
    fileChooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);

	int returnVal = 
	    fileChooser.showOpenDialog((Component)actionEvent.getSource());

	if (returnVal == JFileChooser.APPROVE_OPTION) {
	    File file = fileChooser.getSelectedFile();
	    //this is where a real application would open the file.
	    fireFileOpenEvent(file);
	    //mibBrowserFrame.loadFile(file);
	    //System.out.println("Opening: " + file.getName());
	} else {
	    System.out.println("Open command cancelled by user.");
	}
    }
}
    





