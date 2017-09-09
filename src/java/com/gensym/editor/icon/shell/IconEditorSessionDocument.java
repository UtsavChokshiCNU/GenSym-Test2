package com.gensym.editor.icon.shell;

import com.gensym.mdi.*;
import com.gensym.ui.toolbar.*;
import com.gensym.ui.menu.*;

import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JLabel;
import javax.swing.JTextField;
import java.awt.event.*;
import java.awt.*;
import java.awt.GridLayout;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.core.ObjectChangedListener;
import java.util.EventObject;
import java.util.Enumeration;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.dlg.MessageDialog;
import com.gensym.ui.RepresentationConstraints;
import javax.swing.SwingConstants;
import com.gensym.uitools.utils.VariableWidthBevelBorder;
import javax.swing.border.BevelBorder;
import java.awt.Color;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.uitools.utils.ResizeContainer;


public class IconEditorSessionDocument extends MDIDocument
implements ObjectChangedListener, PropertyChangeListener
{
  private IconEditor iconEditor;
  private IconEditorCanvas canvas;
  private JTextField coordinates;
  private int initialWidth = 500,initialHeight = 400;
  static CMenu windowMenu = new CMenu("Window");
  static RepresentationConstraints menuConstraints = 
  new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
				SwingConstants.LEFT, 
				SwingConstants.CENTER, 
				SwingConstants.RIGHT, 
				SwingConstants.CENTER);    

  boolean performedLastSave = false;
  
  public IconEditorSessionDocument(IconEditor iconEditor)
  {
    this(createMenuBar(iconEditor),
	 iconEditor.getDefaultWindowMenu(),
	 createToolBar(iconEditor), iconEditor.getWidthField(),
	 iconEditor.getHeightField());
    addPropertyChangeListener(this);
    coordinates = iconEditor.getCoordField();
    this.iconEditor = iconEditor;
  }

  public IconEditorSessionDocument(String title, JMenuBar wkspMenuBar,
				   JMenu wkspWindowMenu,
				   IconEditor iconEditor) {
    super(title, wkspMenuBar, wkspWindowMenu, createToolBar(iconEditor));
    canvas = new IconEditorCanvas(this, iconEditor.getWidthField(),
				  iconEditor.getHeightField(), iconEditor);
    canvas.addMouseMotionListener(new CursorListener());
    JScrollPane scrollPane = new JScrollPane(new ResizeContainer(canvas));
    getContentPane().add(scrollPane, "Center");
    addPropertyChangeListener(this);
    coordinates = iconEditor.getCoordField();
    this.iconEditor = iconEditor;
  }
  
  protected IconEditorSessionDocument(JMenuBar wkspMenuBar,
				      JMenu wkspWindowMenu, 
				      MDIToolBarPanel toolBarPanel,
				      JTextField widthField,
				      JTextField heightField)
  {
    super(wkspMenuBar, wkspWindowMenu, toolBarPanel);
    canvas = new IconEditorCanvas(this, widthField, heightField, iconEditor);
    canvas.addMouseMotionListener(new CursorListener());
    JScrollPane scrollPane = new JScrollPane(new ResizeContainer(canvas));
    getContentPane().add(scrollPane, "Center");
  }

  public IconEditorCanvas getCanvas()
  {
    return canvas;
  }

  static CMenuBar createMenuBar(IconEditor iconEditor)
  {
    IconDescriptionCommands iconDescriptionCommands = iconEditor.iconDescriptionCommands;
    IconEditorSimulationCommands iconEditorSimulationCommands
      = iconEditor.iconEditorSimulationCommands;
    
    CMenuBar menuBar = new CMenuBar();
    CMenu fileMenu = new CMenu("File");
    
    fileMenu.add(iconEditor.iconEditorSessionCommands, IconEditorSessionCommands.NEW, menuConstraints);
    fileMenu.add(iconEditor.iconEditorSessionCommands, IconEditorSessionCommands.OPEN,menuConstraints);
    fileMenu.addSeparator();
    fileMenu.add(iconDescriptionCommands, IconDescriptionCommands.SAVE,menuConstraints);
    fileMenu.add(iconDescriptionCommands, IconDescriptionCommands.SAVE_AS,menuConstraints);
    fileMenu.addSeparator();
    fileMenu.add(iconDescriptionCommands, IconDescriptionCommands.PRINT,menuConstraints);
    fileMenu.addSeparator();    
    fileMenu.add(iconEditor.iconEditorSessionCommands, IconEditorSessionCommands.EXIT,
		 menuConstraints);

    fileMenu.setMargin(new java.awt.Insets(2,5,2,5));        
    CMenu editMenu = new CMenu("Edit");
    editMenu.add(iconDescriptionCommands, IconDescriptionCommands.EDIT_PROPERTIES, menuConstraints);
    editMenu.add(iconDescriptionCommands, IconDescriptionCommands.CLEAR_ICON, menuConstraints);
  
    CMenu toolsMenu = new CMenu("Tools");
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.POINT,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.LINE,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.LINES,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.RECTANGLE,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.FILLED_RECTANGLE,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.POLYGON,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.FILLED_POLYGON,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.CIRCLE,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.FILLED_CIRCLE,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.IMAGE,menuConstraints);
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.TEXT, menuConstraints);
    toolsMenu.addSeparator();
    toolsMenu.add(iconDescriptionCommands, IconDescriptionCommands.MOVE,menuConstraints);

    CMenu layerMenu = new CMenu("Layer");
    layerMenu.add(iconDescriptionCommands, IconDescriptionCommands.FILL_LAYER,menuConstraints);
    layerMenu.add(iconDescriptionCommands, IconDescriptionCommands.OUTLINE_LAYER,menuConstraints);
    layerMenu.addSeparator();
    layerMenu.add(iconDescriptionCommands, IconDescriptionCommands.NEW_LAYER,menuConstraints);
    layerMenu.add(iconDescriptionCommands, IconDescriptionCommands.DELETE_LAYER,menuConstraints);
    layerMenu.add(iconDescriptionCommands, IconDescriptionCommands.CLONE_LAYER,menuConstraints);
    layerMenu.add(iconDescriptionCommands, IconDescriptionCommands.CLEAR_CURRENT_LAYER, menuConstraints);
    layerMenu.add(iconDescriptionCommands, IconDescriptionCommands.UNGROUP, menuConstraints);
    layerMenu.addSeparator();
    layerMenu.add(iconDescriptionCommands, IconDescriptionCommands.CHANGE_LAYER_COLOR,menuConstraints);

    CMenu simulateMenu = new CMenu("Simulate");
    simulateMenu.add(iconEditorSimulationCommands, IconEditorSimulationCommands.SIMULATE,
		     menuConstraints);
    simulateMenu.add(iconEditorSimulationCommands, IconEditorSimulationCommands.PREFERENCES,
		     menuConstraints);
    windowMenu = new CMenu("Window");
    windowMenu.add(iconEditor.tilingCommands, menuConstraints);      
    
    menuBar.add(fileMenu);
    menuBar.add(editMenu);
    menuBar.add(toolsMenu);
    menuBar.add(layerMenu);
    menuBar.add(simulateMenu);
    menuBar.add(windowMenu);
    menuBar.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));
    
    com.gensym.uitools.utils.FontUtil.initMenuElement
      (menuBar,
       new java.awt.Insets(2,0,2,5),
       com.gensym.uitools.utils.FontUtil.sanserifPlain11);    
    return menuBar;

  }
  
  public void actionPerformed(ActionEvent event)
  {
    if (!isSelected()) return;
    Object object_target = event.getSource();

  }
  
  private static MDIToolBarPanel createToolBar(IconEditor iconEditor)
  {
    MDIToolBarPanel panel = new MDIToolBarPanel();
    GridBagLayout layout = new GridBagLayout();    
    panel.setLayout(layout);
    IconDescriptionCommands iconDescriptionCommands = iconEditor.iconDescriptionCommands;
    ZoomCommands zoomCommands = iconEditor.zoomCommands;
    IconEditorSimulationCommands iconEditorSimulationCommands
      = iconEditor.iconEditorSimulationCommands;
    ToolBar toolBar = new ToolBar();
    toolBar.setOrientation(toolBar.VERTICAL);
    toolBar.setLayout(new GridLayout(11, 2));
    toolBar.setBorderPainted(true);
    toolBar.setMargin(new java.awt.Insets(0,0,0,0));
    toolBar.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.MOVE);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.POINT);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.LINE);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.LINES);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.RECTANGLE);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.FILLED_RECTANGLE);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.POLYGON);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.FILLED_POLYGON);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.CIRCLE);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.FILLED_CIRCLE);
    //toolBar.addSeparator();
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.FILL_LAYER);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.OUTLINE_LAYER);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.IMAGE);
    toolBar.add(iconDescriptionCommands, IconDescriptionCommands.TEXT);

    ToolBar toolBar2 = new ToolBar();
    toolBar2.setMargin(new java.awt.Insets(0,0,0,0));
    toolBar2.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));        
    toolBar2.setBorderPainted(true);

    toolBar2.add(iconEditor.iconEditorSessionCommands, IconEditorSessionCommands.NEW);
    toolBar2.add(iconEditor.iconEditorSessionCommands, IconEditorSessionCommands.OPEN);
    toolBar2.add(iconDescriptionCommands, IconDescriptionCommands.SAVE);
    toolBar2.addSeparator();
    toolBar2.add(iconDescriptionCommands, IconDescriptionCommands.EDIT_PROPERTIES);
    toolBar2.add(iconDescriptionCommands, IconDescriptionCommands.CLEAR_ICON);
    toolBar2.addSeparator();    
    toolBar2.add(iconEditorSimulationCommands, IconEditorSimulationCommands.SIMULATE);
    toolBar2.addSeparator();
    toolBar2.add(zoomCommands, ZoomCommands.ZOOM);
    toolBar2.add(zoomCommands, ZoomCommands.ZOOM_IN);
    toolBar2.add(zoomCommands, ZoomCommands.ZOOM_OUT);
    toolBar2.addSeparator();
    toolBar2.add(iconDescriptionCommands, IconDescriptionCommands.NEW_LAYER);
    toolBar2.add(iconDescriptionCommands, IconDescriptionCommands.DELETE_LAYER);
    toolBar2.add(iconDescriptionCommands, IconDescriptionCommands.CLONE_LAYER);
    toolBar2.add(iconDescriptionCommands, IconDescriptionCommands.CLEAR_CURRENT_LAYER);
    toolBar2.add(iconDescriptionCommands, IconDescriptionCommands.UNGROUP);
    toolBar2.addSeparator();
    toolBar2.add(iconDescriptionCommands, IconDescriptionCommands.CHANGE_LAYER_COLOR);

    iconEditor.getContentPanel().add(toolBar, "West");
    GridBagConstraints constraints = new GridBagConstraints();
    constraints.fill = constraints.NONE;//HORIZONTAL;
    constraints.anchor = constraints.WEST;
    constraints.gridwidth = constraints.REMAINDER;
    constraints.weightx = 1;

    layout.setConstraints(toolBar2, constraints);
    panel.add(toolBar2);       
    //layout.setConstraints(toolBar, constraints);    
    //panel.add(toolBar);
    
    return panel;
  }

  @Override
  public java.awt.Dimension getPreferredSize(){
    return new java.awt.Dimension(initialWidth, initialHeight);
  }
  
  @Override
  public void propertyChange(PropertyChangeEvent e) {
    if (lastChangedEvent == null) return;
    String property = e.getPropertyName();
    if (property.equals(IconEditorSessionDocument.IS_SELECTED_PROPERTY)){
      Boolean selected = (Boolean)e.getNewValue();
      if (selected.booleanValue()) {
	notifyUserOfChange(e);
	lastChangedEvent = null;
      } else if (property.equals(IconEditorSessionDocument.IS_CLOSED_PROPERTY)) {
      }
    }
  }

  private void notifyUserOfChange(EventObject e) {
    MessageDialog md = new MessageDialog(getManager().getMDIFrame(),
					 "Document has changed",
					 true,
					 "Document has changed, continue?",
					 null);//StandardDialogClient
    md.setVisible(true);    
  }
  
  private EventObject lastChangedEvent;
  @Override
  public void objectChanged(EventObject e) {
    if (performedLastSave) {
      lastChangedEvent = null;
      performedLastSave = false;
    } else {
      if (isSelected()) {
	notifyUserOfChange(e);
	lastChangedEvent = null;
      } else
	lastChangedEvent = e;
    }
  }

  class CursorListener extends MouseMotionAdapter {
    @Override
    public void mouseMoved(MouseEvent e) {
      coordinates.setText("("+e.getX()+","+e.getY()+")");
    }
  }
  
}


