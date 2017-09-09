package com.gensym.nols.main;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.URL;
import java.util.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import com.gensym.nols.util.NolCmdLineArgHandler;

/**
 */
public class NeurOnLine {
	private NolMainFrame frame;
    private String mac      = "com.sun.java.swing.plaf.mac.MacLookAndFeel";
    private String metal    = "javax.swing.plaf.metal.MetalLookAndFeel";
    private String motif    = "com.sun.java.swing.plaf.motif.MotifLookAndFeel";
    private String windows  = "com.sun.java.swing.plaf.windows.WindowsLookAndFeel";

	public static void main(String[] args) {
		String vers = System.getProperty("java.version");		
		if (vers.compareTo("1.1.7") < 0) {
			System.out.println("!!!WARNING: Swing must be run with a " +
				"1.1.7 or higher version VM!!!");
		}
		final NeurOnLine nol = new NeurOnLine(); 
		NolCmdLineArgHandler cmdline = new NolCmdLineArgHandler(args);
		String prjName = cmdline.getOptionValue("-project");
		if(prjName!=null){
			nol.showFrame(prjName);
		}else{
			nol.showFrame(null);
		}
		String hostName = cmdline.getOptionValue("-g2host");
		if(hostName!=null){
			nol.connectG2(args);
		}
		String rootDir = cmdline.getOptionValue("-root");
		if(rootDir!=null){
			nol.setRootDirectory(rootDir);
		}
    }

    public NeurOnLine(){
	String os = System.getProperty("os.name");		
	String currentLF = windows;
	if(os.indexOf("Win") == -1){
	    currentLF = motif;
	}
	try {
	    UIManager.getLookAndFeel();  // this is to work around some swing problems.
	    UIManager.setLookAndFeel(currentLF);
	} catch (Throwable t) {
	    System.err.println(t.toString());
	    return;
	}
	
	try {
	    ErrorManager errMan = new ErrorManager();
	    System.setErr(errMan); //this is just temperary, need to set back.
	    System.setOut(errMan); //this is just temperary, need to set back.
	    
	    Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
	    // MK 2/6/99: put logo onto same thread so it remains visible until main window appears
	    Logo logo = new Logo();
	    logo.showLogo(dim.width/2-320, dim.height/2-240);
	    frame = new NolMainFrame();
	    errMan.setMainFrame(frame);  // so error manager can kill the wait cursor after an error
	    logo.hideLogo();
	}
	catch (java.io.UnsupportedEncodingException ex) {
	    System.out.println("NeurOnLine.NeurOnLine(): Failed to create ErrorManager, UnsupportedEncodingException: " + ex.toString());
	}
    }

	public void showFrame(String projectFileName){
		frame.setVisible(true);
		if(projectFileName != null)
			frame.openProjectActionPerformed(projectFileName);
	}

	public void connectG2(String[] args){
		frame.connectG2(args);
	}

	public void setRootDirectory(String dir){
		frame.setRootDirectory(dir);
	}

	public void clear(){
		frame.dispose();
		frame = null;
	}
}


