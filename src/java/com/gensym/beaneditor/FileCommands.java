/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 FileCommands.java
 *
 */
package com.gensym.beaneditor;


import java.awt.FileDialog;
import java.awt.event.ActionEvent;
import java.util.Vector;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.ObjectOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;
import javax.swing.JFileChooser;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlgruntime.PageGroup;
import com.gensym.beansruntime.G2ClassLoader;
import com.gensym.beansruntime.BeanInputStream;
import com.gensym.files.*;
import com.gensym.ntw.files.*;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Helper;
import com.gensym.classes.modules.uillib.UilTailoredDialog;

public class FileCommands extends AbstractStructuredCommand implements 
StandardDialogClient{

  //Command Keys
  static final String NEW = "FileNew";
  static final String DIALOG = "FileNewDialog";
  static final String TABBED_DIALOG = "FileNewTabbedDialog";
  static final String IMPORT = "FileImport";
  static final String UIL_MASTER_DIALOG = "FileImportUILMasterDialog";
  static final String OPEN = "FileOpen";
  static final String LOAD_JAR = "FileLoadJar";
  static final String SAVE = "FileSave";
  static final String SAVE_AS = "FileSaveAs";
  static final String EXIT = "FileExit";
  private static final String[] cmdKeys = 
    new String[]{DIALOG, TABBED_DIALOG, OPEN, LOAD_JAR, SAVE, SAVE_AS, EXIT};


  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");
  private static final Resource i18n = Resource.getBundle("com.gensym.resources.Messages");
  private static int GUI_LEVEL = 2;
  private static int tempFileCount = 0;
  private EditorFrame frame;
  private PageCommands pageCommands;
  private PageGroupCommands pageGroupCommands;
  private int newDialogCounter;
  private URLFile cachedSelectedFile = null;
  private String currentCommand;
  private String prevJarDir;

  private static java.lang.reflect.Method doLoadMethod;
  private static java.lang.reflect.Method doOpenMethod;

  static{
    try{
      doLoadMethod = ComponentEditor.class.getDeclaredMethod("loadJar", new Class[]{String.class, Boolean.TYPE});
      doOpenMethod = FileCommands.class.getDeclaredMethod("doOpen", new Class[]{});
    }
    catch(NoSuchMethodException ex){
      Trace.exception(ex);
    }
  }


  FileCommands(EditorFrame frame, PageCommands pageCommands, 
	       PageGroupCommands pageGroupCommands){
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("New&Open", new CommandInformation[]{
        new SubCommandInformation(NEW, true, shortResource, longResource, 
				  null, null, null, new CommandInformation[]{
          new CommandInformation(DIALOG, true, shortResource, longResource, 
				 "new_dialog.gif", null, null, true)}),
	  //new CommandInformation(TABBED_DIALOG, true, shortResource, longResource, 
	  //	 	 	   "new_tabbed_dialog.gif", null, null, true)}),
        new CommandInformation(OPEN, true, shortResource, longResource, 
			       "open.gif", null, null, false)}),
      new CommandGroupInformation("ImportGroup", new CommandInformation[]{
	new SubCommandInformation(IMPORT, true, shortResource, longResource,
				  null, null, null, new CommandInformation[]{
	  new CommandInformation(UIL_MASTER_DIALOG, true, shortResource, longResource, 
				 null, null, null, false)})}),
      new CommandGroupInformation("Load", new CommandInformation[]{
        new CommandInformation(LOAD_JAR, true, shortResource, longResource, 
			       null, null, null, false)}),
      new CommandGroupInformation("Save", new CommandInformation[]{
        new CommandInformation(SAVE, true, shortResource, longResource, 
			       "save.gif", null, null, true),
	  new CommandInformation(SAVE_AS, true, shortResource, longResource, 
				 null, null, null, false)}),
      new CommandGroupInformation("Exit", new CommandInformation[]{
        new CommandInformation(EXIT, true, shortResource, longResource, 
			       null, null, null, true)})});

    this.frame = frame;
    this.pageCommands = pageCommands;
    this.pageGroupCommands = pageGroupCommands;
    newDialogCounter = 1;
    frame.updateTitle("Dialog"+newDialogCounter+".ser");
  }

  @Override
  public String[] getKeys(){
    return cmdKeys;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    }

    //System.out.println("FileCommands handling command key:"+cmdKey);
    if (cmdKey.equals(LOAD_JAR)) doLoadJar();
    else if (cmdKey.equals(SAVE)) doSave();
    else if (cmdKey.equals(SAVE_AS)) doSaveAs();
    else {
      currentCommand = cmdKey;
      saveAndExecuteCommand();
    }
  }

  private void saveAndExecuteCommand(){
    if (frame.containsNonTrivialComponents() && frame.getBeanEditTool().dirtyBit){
      String name;
      if (cachedSelectedFile == null)
	name = "Dialog"+newDialogCounter + ".ser";
      else
	name = cachedSelectedFile.getName();
      new QuestionDialog(frame, "Component Editor", true, "Do you want to save changes to \'"+name+"\'?", this).setVisible(true);
    }
    else doCurrentCommand();
  }

  private void doCurrentCommand(){
    if (currentCommand == null) return;
    if (currentCommand.equals(DIALOG)) doNewDialog(frame.SIMPLE_DIALOG);
    else if (currentCommand.equals(TABBED_DIALOG)) doNewDialog(frame.TABBED_DIALOG);
    else if (currentCommand.equals(OPEN)){
      Helper helper = new Helper(this, doOpenMethod, new Object[]{});
      helper.setPriority(Thread.MIN_PRIORITY);
      helper.start();
    }
    else if (currentCommand.equals(UIL_MASTER_DIALOG)) doImportMasterDialog();
    else if (currentCommand.equals(EXIT)) doExit();
    currentCommand = null;
  }

  private void doNewDialog(int type){
    cachedSelectedFile = null;
    newDialogCounter++;
    frame.updateTitle("Dialog"+newDialogCounter+".ser");
    frame.clearEditingSession();
    if (type == frame.SIMPLE_DIALOG)
      frame.setupSimpleDialog();
    else if (type == frame.TABBED_DIALOG)
      frame.setupTabbedDialog(true);
  }

  void openTabbedDialog(BeanInputStream ois)
       throws IOException, ClassNotFoundException
  {
    frame.setupTabbedDialog(false);
    PageGroup pageGroup = (PageGroup)ois.readObject();
    URL baseURL = pageGroup.getLocation();
    String[] tabNames = pageGroup.getTabNames();
    String[] pageLocations = pageGroup.getPages();
    int i, len = tabNames.length;
    // BeanCanvas loadCanvas = canvas;
    for (i=0; i<len; i++)
      {
	BeanCanvas loadCanvas = new BeanCanvas();
	pageCommands.extendPages(loadCanvas,tabNames[i]);
	URL pageURL = new URL(baseURL,pageLocations[i]);
	URLConnection cxn = pageURL.openConnection();
	cxn.connect();
	InputStream inputStream = cxn.getInputStream ();
	BeanInputStream pageStream = new BeanInputStream(inputStream,
							 G2ClassLoader.ourLoader);
	loadCanvas.loadContents(pageStream);
	pageStream.close();
	inputStream.close();
      }
  }

  public void doOpen(){
    URLFile selectedFile = getFileNameFromUser("Open",true,false);
    doOpen (selectedFile);
  }

  void doOpen (URLFile selectedFile) {
    if (selectedFile != null){
      frame.clearEditingSession();
      InputStream is = null;
      BeanInputStream ois;
      boolean isSimple = true;
      boolean okToRead = false;
      try{    
	is = selectedFile.getInputStream();
	ois = new BeanInputStream(is, G2ClassLoader.ourLoader);
	if (ois.readObject() instanceof PageGroup)
	  isSimple = false;
	ois.close();
	is.close();
	//fis = ((G2ClassLoader)(G2ClassLoader.ourLoader)).getResourceAsStream(dname + fname);
	okToRead = true;
      }
      catch (Exception ex){
	Trace.exception(ex, null);
	//sendErrorMessage("noFile",null);//
      Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
				     ComponentEditor.class, i18n,
				     "unableToOpenFile", 
				     new Object[] {selectedFile.toString()}));
      } 	    
      if (okToRead){
	try{ 
	  is = selectedFile.getInputStream();
	  ois = new BeanInputStream(is, G2ClassLoader.ourLoader);
	  if (isSimple){
	    frame.setupSimpleDialog();
	    frame.getCanvas().loadContents(ois);
	  }
	  else
	    openTabbedDialog(ois);
	  ois.close();
	  is.close();
	}
	catch (Exception ex){
	  ex.printStackTrace();
	  //sendErrorMessage("badFormat",null);//
	  Trace.exception (ex, null);
	}
	frame.updateTitle((cachedSelectedFile == null) ? "" :
			  cachedSelectedFile.getName());
	frame.updateConnectionColors();
	frame.validate();
      }
    }
    
    BeanCanvas canvas = frame.getCanvas();
    canvas.setMinimumLogicalSize();
  }

  private void doImportMasterDialog(){
    URLFile selectedURL = getFileNameFromUserForUILDialogImport();
    //System.out.println(selectedURL);
    if (selectedURL == null) return;
    if (selectedURL instanceof UILDialogImportDialogFile){
      UILDialogImportDialogFile dlgFile = (UILDialogImportDialogFile)selectedURL;
      try{
	UilTailoredDialog dlg = dlgFile.getDialog();	
	if (dlg != null){	
	  doNewDialog(frame.SIMPLE_DIALOG);
	  frame.getCanvas().setScroll();
	  UilDialogConverter dlgConverter = new UilDialogConverter(frame, dlgFile.getConnectionForItem(), 
								   dlg);
	  dlgConverter.convertDialog();
	}
	else
	  new WarningDialog(frame, "Component Editor", true, "UIL master dialog with url=\""+selectedURL+"\" could not be found.", null).setVisible(true);

      }
      catch(G2AccessException ex){
	new WarningDialog(frame, "Component Editor", true, "Unable to import UIL master dialog with url=\""+selectedURL+"\"\n"+ex.getMessage(), null).setVisible(true);
      }
    }
    else
      new WarningDialog(frame, "Component Editor", true, "UIL master dialog with url=\""+selectedURL+"\" could not be found.", null).setVisible(true);
  }

  private void doLoadJar(){
    FileDialog fd = new FileDialog(frame, "Load", FileDialog.LOAD);	
    if (prevJarDir == null)
      prevJarDir = System.getProperty("user.dir");
    fd.setDirectory (prevJarDir);
    fd.setFile("*.jar");
    fd.show();
    String fname = fd.getFile();
    String dname = fd.getDirectory();
    
    if (fname != null && dname != null){
      prevJarDir = dname;
      File file  = new File(dname, fname);
      FileInputStream fis = null;    
	try{    
	  fis = new FileInputStream(file);
	  fis.close();}
	catch (Exception ex){
	  //sendErrorMessage("noFile",null);//
	  Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
					 ComponentEditor.class, i18n,
					 "unableToOpenFile", new Object[] {dname+fname}));
	} 
	if (fis != null){
	  Helper helper = new Helper(frame.application, doLoadMethod, new Object[]{dname + fname, new Boolean(true)});
	  helper.start();
	}
    }
  }
  
  private URLFile getFileNameFromUserForUILDialogImport()
  {
    UILDialogImportFileSystemView model = new UILDialogImportFileSystemView(null);
    JFileChooser fileChooser = new JFileChooser("g2:",model);
    String prompt = "Import UIL Master Dialog";
    fileChooser.setDialogTitle(prompt);
    fileChooser.setApproveButtonText("Import");
    int dialogStatus = fileChooser.showDialog(frame,prompt);
    URLFile result = (URLFile) fileChooser.getSelectedFile();
    // String filename = fileChooser.getFilenameText();
    if (dialogStatus == JFileChooser.APPROVE_OPTION)
      {
	if (false) 
	  {
	    // URLFile directory = (URLFile) model.getCurrentDirectory();
	    // String newURL = directory.getPath()+"/"+filename;
	    // result = URLFile.makeFileFromPath(newURL);
	  }
	return result;
      }
    else
      return null;
  }

  private URLFile getFileNameFromUser(String prompt, boolean cacheIt,
				      boolean isSave)
  {
    /*    G2ConnectionInfo info = null;
    if (frame.application.hostName != null && 
	frame.application.portName != null)
      info = new G2ConnectionInfo(frame.application.hostName,
      frame.application.portName);*/
    String startingDirectoryName = (cachedSelectedFile == null ?
				    "file:///"+
				    System.getProperty("user.dir").replace('\\','/') :
				    cachedSelectedFile.getParent());
    T2URLDirectoryModel directoryModel 
      = new T2URLDirectoryModel(true,true,true,null,startingDirectoryName);
    URLFileSystemView model 
      = new URLFileSystemView(directoryModel);
    JFileChooser fileChooser = new JFileChooser(startingDirectoryName,model);
    fileChooser.setDialogTitle(prompt);
    if (isSave)
      fileChooser.setApproveButtonText("Save");
    else
      fileChooser.setApproveButtonText("Open");
    int dialogStatus = fileChooser.showDialog(frame,prompt);
    URLFile result = (URLFile) fileChooser.getSelectedFile();
    System.out.println("getUICLassid "+fileChooser.getUIClassID());
    // String filename = fileChooser.getFilenameText();
    if (dialogStatus == JFileChooser.APPROVE_OPTION)
      {
	// this is a workaroud for a bug in JFileChooser --
	// it seems to have no mechanism for dealing with 
	// new file names, which is something that one may 
	// encounter while saving.
	if (false) // filename != null)
	  {
	    // URLFile directory = (URLFile) model.getCurrentDirectory();
	    // String newURL = directory.getPath()+"/"+filename;
	    // result = URLFile.makeFileFromPath(newURL);
	    // if (false)
	    //   System.out.println("FileChooser Save Workaround:  newURL = "+
	    //			 newURL+" yielding "+result);
	  }
	if (cacheIt)
	  cachedSelectedFile = result;
	return result;
      }
    else
      return null;
  }

  private static boolean isWindows = System.getProperty("os.name").startsWith("Windows");

  // in JDK12 this could simple call File.createTempFile...
  private static File createTempFile(String name, String extension) {
    String tempDirName = System.getProperty("com.gensym.resourcecache.repository");
    if (tempDirName == null) {
      tempDirName = isWindows ? "c:\\Temp" : "/tmp";
    }
    return new File(tempDirName + File.separatorChar + name + '.' + extension);
  }

  
  private void executeSaveCommand(URLFile selectedFile)
  {
    // System.out.println("saveCommand "+selectedFile);
    int b;
    if (frame.getDialogType() == frame.SIMPLE_DIALOG)
      try {
      File tempFile = createTempFile("tmpdlg"+(tempFileCount++), "ser");
      OutputStream os = new FileOutputStream(tempFile);
      frame.getCanvas().save(os);
      os.close();
      InputStream is = new FileInputStream(tempFile);
      os = selectedFile.getOutputStream();
      while ((b = is.read()) != -1)
	os.write(b);
      is.close();
      os.close();
    } catch (IOException e)
      {
	System.out.println("Problems saving dialog");
	Trace.exception(e);
      }
    else
      {
	try
	  {    
	    File tempFile = createTempFile("tmpdlg"+(tempFileCount++), "ser");
	    OutputStream os = new FileOutputStream(tempFile);
	    ObjectOutputStream oos = new ObjectOutputStream(os);
	    // HERE - must fix up pageGroup Saving
	    PageGroup pageGroup
	      = pageGroupCommands.makePageGroup(selectedFile.getPath(),
						selectedFile.getName(),
						false);
	    oos.writeObject(pageGroup);
	    oos.close();
	    os.close();
	    
	    InputStream is = new FileInputStream(tempFile);
	    os = selectedFile.getOutputStream();
	    while ((b = is.read()) != -1)
	      os.write(b);
	    is.close();
	    os.close();
	  }
	catch (Exception ex)
	  {
	    System.out.println("Component editor save failed to "+selectedFile);
	    ex.printStackTrace();
	  }
      }
    frame.updateTitle(selectedFile.getName());
    frame.getBeanEditTool().dirtyBit = false;
  }

  private void doSave(){
    frame.getBeanEditTool().clearSelection();
    if (cachedSelectedFile == null){
      URLFile newSelectedFile = getFileNameFromUser("Save As",true,true);
      if (newSelectedFile == null) return;
    }
    executeSaveCommand(cachedSelectedFile);
  }

  private void doSaveAs(){
    frame.getBeanEditTool().clearSelection();
    if (getFileNameFromUser("Save As",true,true) != null)
      executeSaveCommand(cachedSelectedFile);
  }

  private void doExit(){
    frame.application.exit();
  }

  @Override
  public void dialogDismissed (StandardDialog d, int cmdCode){
    d.setVisible(false);
    if (cmdCode == CommandConstants.YES) {
      if (cachedSelectedFile == null){
	if (getFileNameFromUser("Save as",true,true) != null)
	  {
	    executeSaveCommand(cachedSelectedFile);
	    doCurrentCommand();
	  }
	else
	  {
	    currentCommand = null;
	  }
      }
      else {
	executeSaveCommand(cachedSelectedFile);
	doCurrentCommand();
      }
    }
    else if (cmdCode == CommandConstants.NO){
      doCurrentCommand();
    }
    else{
      currentCommand = null;
    }
  }
}
