package com.gensym.editor.icon.shell;

import java.awt.event.*;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.mdi.MDIFrame;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.Savable;
import com.gensym.editor.icon.core.IconFormat;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.core.Finder;
import java.awt.Event;
import javax.swing.KeyStroke;

public class IconEditorSessionCommands extends AbstractCommand
{
  private IconEditor iconEditor;
  private static final String shortResource = "IconEditorShortResource";
  private static final String longResource = "IconEditorShortResource";
  private static final String mnemonicResource = "IconEditorMnemonicResource";          
  public static final String NEW = "NewIcon";
  public static final String OPEN = "OpenIcon";
  public static final String EXIT = "Exit";
  private static String imageDir = "images/";
  private Finder finder;
  private IconFormat defaultIconFormat;
  
  public IconEditorSessionCommands(IconEditor iconEditor)
  {
    super(new CommandInformation[]{
      new CommandInformation(NEW, true, shortResource, longResource, 
			     imageDir+"new.gif",
			     null, null, true,mnemonicResource,
			     KeyStroke.getKeyStroke('N', Event.CTRL_MASK)),
	new CommandInformation(OPEN, true, shortResource, longResource,
			       imageDir+"open.gif",
			       null, null, false,mnemonicResource,
			       KeyStroke.getKeyStroke('O', Event.CTRL_MASK)),
      new CommandInformation(EXIT, true, shortResource, longResource, 
			     imageDir+"exit.gif",
			     null, null, true,
			     mnemonicResource,
			     null)});
    this.iconEditor = iconEditor;
  }


  public IconFormat getDefaultIconFormat() {
    return defaultIconFormat;
  }

  private IconFormat getIconFormat(Savable saver) {
    if (saver == null)
      return defaultIconFormat;
    IconFormat format = saver.getIconFormat();
    if (format == null)
      return defaultIconFormat;
    else
      return format;
  }
  
  public void setDefaultIconFormat(IconFormat iconFormat) {
    this.defaultIconFormat = iconFormat;
  }

  public void setIconFinder(Finder finder) {
    this.finder = finder;
  }

  public Finder getFinder() {
    return finder;
  }

  public IconEditorSessionDocument openSession(Finder finder) {
    IconEditorSessionDocument doc = null;
    IconEditorCanvas canvas; 
    if (finder != null) {
      Object formattedIcon = finder.find();
      if (formattedIcon != null) {
	doc = addSession(finder.getLastLocationTitle());
	canvas = doc.getCanvas();
	canvas.setEvaluator(iconEditor.getDefaultEvaluator());	
	Savable autoSaver = finder.getLastLocation();
	getIconFormat(autoSaver).importFormattedIcon(formattedIcon, canvas);      
	if (autoSaver != null)
	  IconDescriptionCommands.setSaver(doc, autoSaver);
	canvas.setHasChanged(false);
      }
    } else {
      doc = addSession("Untitled");
      canvas = doc.getCanvas();
      canvas.setEvaluator(iconEditor.getDefaultEvaluator());
      Layer layer = canvas.addNewLayer(0);
      canvas.setCurrentLayer(layer);
      canvas.setHasChanged(false);
  }
    return doc;
  }
  
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey.equals(OPEN)) 
      openSession(getFinder());
    else if (cmdKey.equals(NEW))
      openSession(null);
    else if (cmdKey.equals(EXIT)) {
      iconEditor.setVisible(false);
      iconEditor.dispose();
    }
  }

  @Override
  protected void setAvailable(String key, boolean available){
    super.setAvailable(key, available);
  }

  public IconEditorSessionDocument addSession(String title) {

    IconEditorSessionDocument doc =
      new IconEditorSessionDocument(title,
				    IconEditorSessionDocument.createMenuBar
				    (iconEditor),
				    IconEditorSessionDocument.windowMenu,
				    iconEditor);
    iconEditor.getManager().addDocument(doc, doc.getPreferredSize());
    return doc;
  }
  
  public IconEditorSessionDocument addSession()
  {
    return addSession("Untitled");//i18n this please
  }


}
