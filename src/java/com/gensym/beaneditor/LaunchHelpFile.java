package com.gensym.beaneditor;

import java.awt.Frame;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;
import com.gensym.dlg.ErrorDialog;
import com.gensym.message.Trace;

class LaunchHelpFile {
  private static File execFile;
  private static String command;

  static String solarisBrowser;

  static void launch(Frame frame){
    boolean setupDone = true;
    if ((execFile == null) || (!execFile.exists()))
      setupDone = setup(frame);
    if (!setupDone) return;
    Runtime current = Runtime.getRuntime();
    try {
      if (ComponentEditor.windowsPlatform)
	current.exec(command);
      else
	current.exec ("sh " + command);
    }
    catch (java.io.IOException ex){
      //this shouldn't happen
      ErrorDialog dlg = new ErrorDialog(frame, "Error", true, "Error attempting to lauch help. \n\n"+ex.toString(), null);
      dlg.setVisible(true);
      Trace.exception(ex);
    } 
  }

  private static boolean setup(Frame frame){
    String sequoiaHome = System.getProperty("SEQUOIA_HOME");
    if ((sequoiaHome == null)||(sequoiaHome.equals(""))){
      ErrorDialog dlg = new ErrorDialog(frame, "Error", true, "Error attempting to launch help.\n\nEither the environment variable SEQUOIA_HOME is not set or \nComponentEditor was not started with -DSEQUOIA_HOME=%SEQUOIA_HOME%", null);
      dlg.setVisible(true);
      return false;
    }
    
    String dir = System.getProperty("com.gensym.resourcecache.repository");
    if (dir == null)
      dir = System.getProperty("user.home");
    String extension;
    String browser = "";
    if (ComponentEditor.windowsPlatform)
      extension = ".bat";
    else{
      if (solarisBrowser == null){
	ErrorDialog dlg = new ErrorDialog(frame, "Error", true, "Error attempting to launch help.\n\nAn html browser must be specified on the command-line using the -browser option.", null);
	dlg.setVisible(true);
	return false;
      }
      else{
	browser = solarisBrowser + " ";
	extension = ".sh";
      }
    }
    command = dir + File.separator + "cehelp" + Long.toHexString((new Date()).getTime()/10) + extension;
    execFile = new File (command);
    try{
      FileOutputStream fo = new FileOutputStream (execFile);
      PrintWriter pw = new PrintWriter (fo, true);
      String dirr = (ComponentEditor.windowsPlatform ? "Java"+File.separator : "");
      String docFile = browser+sequoiaHome+File.separator+
	dirr
	+"docs"+File.separator+"ControlsOnlineHelp.html";
      pw.print (docFile);
      pw.close ();
      fo.close();
      if (!ComponentEditor.windowsPlatform) {
	Process p = Runtime.getRuntime().exec("chmod u+x "+command);
	int status = -1;
	try {
	  status = p.waitFor ();
	} catch (InterruptedException ie) {
	  ie.printStackTrace ();
	}
      }
      return true;
    }
    catch(IOException ex){
      //this shouldn't happen
      ErrorDialog dlg = new ErrorDialog(frame, "Error", true, "Can not launch help.  Unable to write to "+command, null);
      dlg.setVisible(true);
      return false;
    }
  }
}
