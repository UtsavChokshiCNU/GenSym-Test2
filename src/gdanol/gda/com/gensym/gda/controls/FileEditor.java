
package com.gensym.gda.controls;

import com.gensym.controls.FieldType;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JFileChooser;

import com.gensym.controls.FieldType;

import com.gensym.util.Symbol;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.files.URLFile;
import com.gensym.files.URLFileSystemView;
import com.gensym.ntw.files.T2URLDirectoryModel;
import com.gensym.ntw.files.G2File;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.LoadSaveKBTools;

import java.net.URL;

/**
FileEditor is used for selecting file from File System.
It should browse the file system of G2 server, but now 
it browse the file system of tw2 client. Will be fixed on
next phase. (Or may be use tw2 file browser which should be
used, for example, for load *.kb dialog?)
*/
public class FileEditor extends TextFieldEditor{

    public FileEditor() {
		super();
		selectFile = new JButton("...") {
			public boolean isFocusTraversable() {return false;}
		};
		int h = textField.getPreferredSize().height;
		selectFile.setPreferredSize(new Dimension(h,h));
		add(selectFile, BorderLayout.EAST);

		selectFile.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				selectFileAction(e);
			}
		});
		
		textField.setShowQuotesForTextType(false);
		setBorder(textField.getBorder());
		textField.setBorder(null);
        URLFileSystemView urlfilesystemview = new URLFileSystemView(
        	new T2URLDirectoryModel(false, true, false, null, null));
        fc = new JFileChooser(urlfilesystemview);

    }

	protected void selectFileAction(ActionEvent e) {
        G2ConnectionInfo g2connectioninfo = registerCurrentConnection();
		textField.requestFocus();
		fc.setSelectedFile(G2File.makeG2File(getAbsolutePath(textField.getText())));
		int option = fc.showDialog(this, localize("FileChooserApproveButton"));
		if (option == JFileChooser.CANCEL_OPTION)
			return;
		textField.setText(getPathFromURL((URLFile)fc.getSelectedFile()));
		textField.focusLost(new FocusEvent(textField, FocusEvent.FOCUS_LOST));
        G2File.deregisterG2ConnectionInfo(g2connectioninfo);
	}
	

	protected String getAbsolutePath(String path) {
		boolean pathIsAbsolute=true;
        try{
        	if(path.equals(""))
        		pathIsAbsolute=false;
        	else {
	        	if (typeOfFileSystem==null)
	            	typeOfFileSystem = LoadSaveKBTools.typeOfFileSystem(connection);
	            	
	            if(typeOfFileSystem.equals(WIN32_))
					pathIsAbsolute = (path.charAt(1)==':');
	           	else
					pathIsAbsolute = (path.charAt(0)=='/');
        	}
        } catch (G2AccessException e) {Trace.exception(e);}
        
		if (!pathIsAbsolute) {
			if (defaultDirectory==null) {
				try { 
					defaultDirectory = (String)LoadSaveKBTools.defaultDirectory(connection);
				} catch (G2AccessException e) {Trace.exception(e);}
			}
			path = defaultDirectory + path;

		}
		return prefix + LoadSaveKBTools.revertG2FileSpecificationToURLString(connection, path);
	}
	
	protected String getPathFromURL(URLFile file) {
		String path = LoadSaveKBTools.getG2FileSpecificationFromURL(connection, file);
		try {
			if (defaultDirectory==null)
				defaultDirectory = (String)LoadSaveKBTools.defaultDirectory(connection);
		
			if (path.startsWith(defaultDirectory))
				path=path.substring(defaultDirectory.length());
		} catch (G2AccessException e) {Trace.exception(e);}
			
		return path;
	}
	public void setConnection(TwAccess twaccess) {
		connection=twaccess;
        G2ConnectionInfo g2connectioninfo = ((G2Gateway)connection).getG2ConnectionInfo();
        String s = g2connectioninfo.getHost();
        String s1 = g2connectioninfo.getPort();
        prefix = "g2://" + s + ":" + s1 + "/serverFileSystem/";
 
	}
	
	//fieldtype must me text only
    public void setFieldType(FieldType type) {}

	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		selectFile.setEnabled(enabled);
	}

	    private G2ConnectionInfo registerCurrentConnection() {
        G2ConnectionInfo g2connectioninfo = null;
        try {
            g2connectioninfo = new G2ConnectionInfo(connection.g2GetHostName(), connection.g2GetPortNumberOrName());
            G2File.registerG2ConnectionInfo(g2connectioninfo);
        }
        catch(G2AccessException g2accessexception) {
            Trace.exception(g2accessexception);
        }
        return g2connectioninfo;
    }

// JFileChooser related methods
    public JFileChooser getFileChooser() {return fc;}
    
    public void setFileDialogTitle(String title) {
		if (fc!=null) fc.setDialogTitle(title);
	}
	
	public String getFileDialogTitle() {return fc.getDialogTitle();}
	
    public void setFileSelectionMode(int mode) {fc.setFileSelectionMode(mode);}
    public int getFileSelectionMode() {return fc.getFileSelectionMode();}
	
	private JButton selectFile;
	private JFileChooser fc;

	protected  String prefix;
	protected TwAccess connection;					
    private static Symbol G2_DEFAULT_DIRECTORY_ = Symbol.intern("G2-DEFAULT-DIRECTORY");
    private static Symbol WIN32_ = Symbol.intern("WIN32");

    private Symbol typeOfFileSystem;
    private String defaultDirectory;
}