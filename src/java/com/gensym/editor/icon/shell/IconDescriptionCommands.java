package com.gensym.editor.icon.shell;


import com.gensym.mdi.MDIListener;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIDocument;

import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
 
import com.gensym.editor.icon.tools.*;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.IconFormat;
import com.gensym.editor.icon.core.Savable;
import com.gensym.editor.icon.core.ElementInconsistancyError;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.shapes.IconElement;
import java.awt.event.ActionEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import java.util.Hashtable;
import com.gensym.message.Trace;
import javax.swing.JColorChooser;
import java.awt.Color;
import java.util.Enumeration;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.dlgs.CanvasPropertiesDialog;
import com.gensym.editor.icon.core.Parameter;
import java.awt.PrintJob;
import java.awt.Graphics;
import java.awt.Event;
import javax.swing.KeyStroke;

public class IconDescriptionCommands extends AbstractCommand
implements MDIListener, PropertyChangeListener
{
  private static final String shortResource = "IconEditorShortResource";
  private static final String longResource = "IconEditorShortResource";
  private static final String mnemonicResource = "IconEditorMnemonicResource";        
  private IconEditorSessionDocument currentDoc;
  private IconEditor frame;
  private static String imageDir = "images/";
  private IconFormat defaultIconFormat;
  private Savable saver;
  private static Hashtable docSpecificSavers = new Hashtable();
  public static String
  POINT = "Point",
    LINE = "Line",
    LINES = "Lines",
    RECTANGLE = "Rectangle",
    FILLED_RECTANGLE = "FilledRectangle",
    POLYGON = "Polygon",
    FILLED_POLYGON = "FilledPolygon",
    CIRCLE = "Circle",
    FILLED_CIRCLE = "FilledCircle",
    IMAGE = "Image",
    TEXT = "Text",
    AIR_BRUSH = "AirBrush",
    MOVE = "Move",
    NEW_LAYER = "NewLayer",
    DELETE_LAYER = "DeleteLayer",
    UNGROUP = "Ungroup",
    SAVE = "Save",
    SAVE_AS = "SaveAs",
    PRINT = "Print",
    CLONE_LAYER = "CopyLayer",
    FILL_LAYER = "FillLayer",
    OUTLINE_LAYER = "OutlineLayer",
    CHANGE_LAYER_COLOR = "ChangeLayerColor",
    CLEAR_ICON = "ClearIcon",
    CLEAR_CURRENT_LAYER = "ClearCurrentLayer",
    EDIT_PROPERTIES = "EditProperties";

  public IconDescriptionCommands(IconEditor parentFrame)
  {
    super(new CommandInformation[]{
      new CommandInformation(POINT, true, shortResource, longResource,
			     imageDir+"point.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(LINE, true, shortResource, longResource,
			     imageDir+"line2.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(LINES, true, shortResource, longResource,
			     imageDir+"lines.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(RECTANGLE, true, shortResource, longResource,
			     imageDir+"rect2.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(FILLED_RECTANGLE, true, shortResource, longResource,
			     imageDir+"filledRect2.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(POLYGON, true, shortResource, longResource,
			     imageDir+"polygon.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(FILLED_POLYGON, true, shortResource, longResource,
			     imageDir+"filledPolygon.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(CIRCLE, true, shortResource, longResource,
			     imageDir+"circle2.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(FILLED_CIRCLE, true, shortResource, longResource,
			     imageDir+"filledCircle2.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(IMAGE, true, shortResource, longResource,
			     imageDir+"imagegray.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(TEXT, true, shortResource, longResource,
			     imageDir+"text.gif",
			     null, new Boolean(false), true,mnemonicResource,null),	
      new CommandInformation(AIR_BRUSH, true, shortResource, longResource,
			     imageDir+"airBrush.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(MOVE, true, shortResource, longResource,
			     imageDir+"pointer2.gif",
			     null, new Boolean(false), true,mnemonicResource,null),
      new CommandInformation(FILL_LAYER, true, shortResource, longResource,
			     imageDir+"fillLayer.gif",
			     null, null, true,mnemonicResource,null),
      new CommandInformation(OUTLINE_LAYER, true, shortResource, longResource,
			     imageDir+"outlineLayer.gif",
			     null, null, true,mnemonicResource,null),
      new CommandInformation(DELETE_LAYER, true, shortResource, longResource,
			     imageDir+"deletelayer.gif",
			     null, null, true,mnemonicResource,
			     KeyStroke.getKeyStroke('D', Event.CTRL_MASK)),
      new CommandInformation(CLONE_LAYER, true, shortResource, longResource,
			     imageDir+"copylayer.gif",
			     null, null, true,mnemonicResource,null),	
      new CommandInformation(NEW_LAYER, true, shortResource, longResource,
			     imageDir+"newlayer.gif",
			     null, null, true,mnemonicResource,null),
      new CommandInformation(CHANGE_LAYER_COLOR, true, shortResource, longResource,
			     imageDir+"editColorSmall.gif",
			     null, null, false),
      new CommandInformation(CLEAR_ICON, true, shortResource, longResource,
			     imageDir+"clearimage.gif",
			     null, null, true),
      new CommandInformation(CLEAR_CURRENT_LAYER, true, shortResource, longResource,
			     imageDir+"clearimage.gif",
			     null, null, true),
      new CommandInformation(EDIT_PROPERTIES, true, shortResource, longResource,
			     imageDir+"properties.gif",
			     null, null, false),
      new CommandInformation(PRINT, true, shortResource, longResource,
			     imageDir+"print.gif",
			     null, null, true,mnemonicResource,
			     KeyStroke.getKeyStroke('P', Event.CTRL_MASK)),
      new CommandInformation(UNGROUP, true, shortResource, longResource,
			     imageDir+"ungroupimage.gif",
			     null, null, true),
      new CommandInformation(SAVE, true, shortResource, longResource,
			     imageDir+"save.gif",
			     null, null, true,mnemonicResource,
			     KeyStroke.getKeyStroke('S', Event.CTRL_MASK)),
      new CommandInformation(SAVE_AS, true, shortResource, longResource,
			     imageDir+"save.gif",
			     null, null, false,mnemonicResource,null)});
    if (parentFrame != null){
      frame = parentFrame;
      frame.getManager().addMDIListener(this);
      MDIDocument[] docs = frame.getManager().getDocuments();
      for (int i=0; i<docs.length; i++){
	if (docs[i] instanceof IconEditorSessionDocument)
	  docs[i].addPropertyChangeListener(this);
      }
    }
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
  
  public void setSaver(Savable saver) {
    this.saver = saver;
  }

  public static void setSaver(IconEditorSessionDocument doc,
			      Savable saver) {
    Savable oldSaver = (Savable)docSpecificSavers.get(doc);
    if (oldSaver != null)
      oldSaver.removeObjectChangedListener(doc);
    docSpecificSavers.put(doc, saver);
    saver.addObjectChangedListener(doc);
    //updateAvailability();
  }

  public static Savable getSaver(IconEditorSessionDocument doc) {
    return (Savable)docSpecificSavers.get(doc);
  }
  
  public Savable getSaver() {
    return saver;
  }
  
  @Override
  public void actionPerformed(ActionEvent e)
  {
    doAction(e.getActionCommand());
  }

  private void doAction(String cmdKey) {
    boolean updateStates = true;
    IconEditorCanvas canvas = null;
    if (currentDoc != null)
      canvas = currentDoc.getCanvas();
    
    if (cmdKey.equals(LINE)) 
      canvas.setEventHandler(new IconLineTool(canvas));
    else if (cmdKey.equals(RECTANGLE)) 	
      canvas.setEventHandler(new IconRectangleTool(canvas));
    else if (cmdKey.equals(AIR_BRUSH))
      canvas.setEventHandler(new AirBrushTool(canvas));
    else if (cmdKey.equals(FILLED_RECTANGLE)) {
      IconRectangleTool tool = new IconRectangleTool(canvas);
      tool.setFilled(true);
      canvas.setEventHandler(tool);
    } else if (cmdKey.equals(POLYGON)) {
      IconPolygonTool tool = new IconPolygonTool(canvas);
      canvas.setEventHandler(tool);
    } else if (cmdKey.equals(FILLED_POLYGON)) {
      IconPolygonTool tool = new IconPolygonTool(canvas);
      tool.setFilled(true);
      canvas.setEventHandler(tool);
    } else if (cmdKey.equals(LINES)) {
      IconLinesTool tool = new IconLinesTool(canvas);
      canvas.setEventHandler(tool);
    } else if (cmdKey.equals(CIRCLE)) {
      IconCircleTool tool = new IconCircleTool(canvas);
      tool.setFilled(false);
      canvas.setEventHandler(tool);
    } else if (cmdKey.equals(FILLED_CIRCLE)) {
      IconCircleTool tool = new IconCircleTool(canvas);
      tool.setFilled(true);
      canvas.setEventHandler(tool);
    } else if (cmdKey.equals(IMAGE)) {
      IconImageTool tool = new IconImageTool(canvas, frame.getFileLocater());
      canvas.setEventHandler(tool);
    } else if (cmdKey.equals(TEXT)) {
      TextTool tool = new TextTool(canvas);
      canvas.setEventHandler(tool);
    } else if (cmdKey.equals(POINT))
      canvas.setEventHandler(new IconPointTool(canvas));
    else if (cmdKey.equals(MOVE)) 
      canvas.setEventHandler(new MoveTool(canvas));
    else if (cmdKey.equals(PRINT)) {
      updateStates = false;
      PrintJob printJob = canvas.getToolkit().getPrintJob(frame, 
							  "Printing", 
							  null);
      if (printJob != null) {
	Graphics graphics = printJob.getGraphics();
	if (graphics != null) {
	  canvas.paint(graphics);
	  graphics.dispose();
	}
	printJob.end();
      }
    } else if (cmdKey.equals(SAVE)) {
      updateStates = false;      
      Savable saver = getSaver(currentDoc);
      boolean isSaveAs = (saver == null);
      if (isSaveAs)
	saver = getSaver();
      doSave(saver, canvas, isSaveAs);
    } else if (cmdKey.equals(SAVE_AS)) {
      updateStates = false;
      Savable saver = getSaver();
      doSave(saver, canvas, true);
    } else if (cmdKey.equals(NEW_LAYER)) {
      updateStates = false;
      Layer newLayer =
	canvas.addNewLayer
	(canvas.getLayerPosition(canvas.getCurrentLayer())+1);
      canvas.setCurrentLayer(newLayer);
    } else if (cmdKey.equals(CHANGE_LAYER_COLOR)) {
      updateStates = false;
      editColor(canvas.getCurrentLayer(), canvas);
    } else if (cmdKey.equals(EDIT_PROPERTIES)) {
      updateStates = false;
      editProperties(currentDoc);
    } else if (cmdKey.equals(CLEAR_ICON)) {
      updateStates = false;
      Layer[] layers = canvas.getLayers();
      int length = layers.length;
      for (int x = 0; x<length; x++)
	canvas.removeLayer(layers[x]);
    } else if (cmdKey.equals(UNGROUP)) {
      Layer layer = canvas.getCurrentLayer();
      int position = canvas.getLayerPosition(layer);
      IconElement tempElement;
      IconElement[] elements = layer.getElementsSnapshot();
      try {
	for (int i = elements.length - 1; i > 0; i--) {
	  tempElement = elements[i];
	  layer.removeElement(tempElement);
	  canvas.addNewLayer(position++).addElement(tempElement);
	}
      } catch (ElementInconsistancyError eie) {
	Trace.exception(eie);
      }
    } else if (cmdKey.equals(CLEAR_CURRENT_LAYER)) {
      updateStates = false;
      Layer layer = canvas.getCurrentLayer();
      /*int position = canvas.getLayerPosition(layer);
      int layerCount = canvas.getLayers().length;
      canvas.removeLayer(layer);*/
      canvas.clearLayer(layer);
      layer.repaint();
      /*if (layerCount>1) {
	canvas.addNewLayer(position);
        canvas.setCurrentLayer(canvas.getLayers()[position]);
	}*/
    } else if (cmdKey.equals(DELETE_LAYER)) {
      updateStates = false;
      Layer layer = canvas.getCurrentLayer();
      canvas.removeLayer(layer);
    } else if (cmdKey.equals(FILL_LAYER)) {
      updateStates = false;
      Layer layer = canvas.getCurrentLayer();
      layer.setFilled(true);
    } else if (cmdKey.equals(OUTLINE_LAYER)) {
      updateStates = false;
      Layer layer = canvas.getCurrentLayer();
      layer.setFilled(false);
    } else if (cmdKey.equals(CLONE_LAYER)) {
      updateStates = false;
      Layer layer = canvas.getCurrentLayer();
      if (layer != null) {
	try {
	  Layer clone = (Layer)layer.copy();
	  canvas.addLayer(clone, canvas.getLayerPosition(layer)+1);
	  canvas.setCurrentLayer(clone);
	} catch (ElementInconsistancyError eie) {
	  Trace.exception(eie);
	}
      }
    }
    //HANDLE RADIO BUTTON BEHAVIOR FOR THE FOLLOWING
    if (updateStates) {
      setState(POINT, Boolean.FALSE);
      setState(LINE, Boolean.FALSE);
      setState(LINES, Boolean.FALSE);
      setState(RECTANGLE, Boolean.FALSE);
      setState(AIR_BRUSH, Boolean.FALSE);
      setState(FILLED_RECTANGLE, Boolean.FALSE);
      setState(POLYGON, Boolean.FALSE);
      setState(FILLED_POLYGON, Boolean.FALSE);
      setState(CIRCLE, Boolean.FALSE);
      setState(FILLED_CIRCLE, Boolean.FALSE);
      setState(IMAGE, Boolean.FALSE);
      setState(TEXT, Boolean.FALSE);
      setState(MOVE, Boolean.FALSE);
      currentToolType = cmdKey;
      setState(cmdKey, Boolean.TRUE);
    }

  }

  private void editProperties(IconEditorSessionDocument doc) {
    CanvasPropertiesDialog ved = new CanvasPropertiesDialog(frame,doc.getCanvas());
    ved.setTitle(doc.getTitle() + " properties");
    ved.setVisible(true);
  }
  
  private void editColor(Layer layer, IconEditorCanvas canvas) {
    if (layer != null) {
      Color color = JColorChooser.showDialog(null,"Edit Color", layer.getColor());
      if (color != null) {
	layer.setColor(color);
	layer.repaint();
	canvas.setHasChanged(true);
	canvas.current_color = color;
	String regionName = layer.getRegionName();
	if (regionName != null)
	  updateLayersWithSameRegionName(regionName, color, canvas);	
	canvas.repaint();       
      }
    }
  }

  private boolean updateLayersWithSameRegionName(String regionName,
						 Color newColor,
						 IconEditorCanvas canvas) {
    boolean changed = false;
    Layer[] layers = canvas.getLayers();
    for (int i=0;i<layers.length;i++) {
      Layer layer = layers[i];
      if (regionName.equals(layer.getRegionName())) {
	layer.setColor(newColor);
	layer.repaint();
	changed = true;
      }
    }
    return changed;
  }
  
  void doSave(Savable saver,
	      IconEditorCanvas canvas,
	      boolean updateDocSaver) {
    IconFormat format = getIconFormat(saver);
    Object description = format.createFormattedIcon(canvas);
    currentDoc.performedLastSave = true;
    boolean didSave = saver.save(description);
    if (!didSave) currentDoc.performedLastSave = false;
    if (didSave && updateDocSaver) {
      Savable autoSaver = saver.getLastLocation();
      if (autoSaver != null) {
	currentDoc.setTitle(autoSaver.getLastLocationTitle());
	currentDoc.repaint();
	setSaver(currentDoc, autoSaver);
      }
    }
    canvas.setHasChanged(false);
  }

  private String currentToolType = FILLED_RECTANGLE;
  private void setCurrentDocument(IconEditorSessionDocument doc) {
    currentDoc = doc;
    if (currentDoc != null)
      doAction(currentToolType);
    updateAvailability();
  }

  @Override
  public void documentAdded(MDIEvent event) {
    MDIDocument document = (MDIDocument)event.getDocument();
    if (document instanceof IconEditorSessionDocument) {
      IconEditorSessionDocument iconDoc = (IconEditorSessionDocument)document;
      iconDoc.addPropertyChangeListener(this);
      setCurrentDocument(iconDoc);      
    }
  }

  private void updateAvailability() {
    //setAvailable(SAVE, (currentDoc != null) && getSaver(currentDoc) != null);
  }
    
  @Override
  public void propertyChange(PropertyChangeEvent e) {
    MDIDocument document = (MDIDocument)e.getSource();
    if (document instanceof IconEditorSessionDocument) {
      IconEditorSessionDocument iconDoc = (IconEditorSessionDocument)document;
      if (e.getPropertyName().equals(IconEditorSessionDocument.IS_SELECTED_PROPERTY)){
	Boolean selected = (Boolean)e.getNewValue();
	//if (selected.booleanValue()) selected = new Boolean(!document.isIcon());
	if (selected.booleanValue()) {
	  setCurrentDocument(iconDoc);	  
	} else {
	  //setCurrentDocument(null);	  
	}
      }
    }
  }

}
