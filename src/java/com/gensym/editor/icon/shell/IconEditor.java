package com.gensym.editor.icon.shell;

import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIListener;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.ui.Command;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.Savable;
import com.gensym.editor.icon.core.Finder;
import com.gensym.editor.icon.core.IconFormat;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.core.LayerListener;
import com.gensym.uitools.utils.PanelExpander;
import com.gensym.uitools.utils.StatusBar;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.YesNoDialog;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import javax.swing.JTextField;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JViewport;
import javax.swing.JCheckBox;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.util.Hashtable;
import com.gensym.editor.icon.shapes.IconElement;
import com.gensym.editor.icon.core.ElementInconsistancyError;
import com.gensym.message.Trace;
import javax.swing.filechooser.FileFilter;
import javax.swing.JFileChooser;
import com.gensym.ui.menu.CPopupMenu;
import java.net.MalformedURLException;
import java.net.URL;
import java.io.File;
import com.gensym.editor.icon.core.FileLocater;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.uitools.utils.VariableWidthBevelBorder;
import java.awt.Color;
import javax.swing.border.LineBorder;
import javax.swing.border.BevelBorder;
import javax.swing.JSplitPane;
import java.util.Vector;

public class IconEditor extends MDIFrame
{  
  private static final boolean isMultipleFrames = true;
  protected IconEditorCanvas currentCanvas;  
  Command iconEditorSessionCommands, tilingCommands;
  LayerPanel layerPanel;
  JScrollPane layerPanelScroller;
  private static MDIFrame mdiFrame;
  private PropertyChangeAdapter propertyChangeAdapter;
  protected LayerAdapter layerAdapter;
  protected JPanel statusPanel;
  private MDIAdapter mdiAdapter;
  private LayerDragAdapter layerDragAdapter;
  ZoomCommands zoomCommands;
  IconDescriptionCommands iconDescriptionCommands;
  IconEditorSimulationCommands iconEditorSimulationCommands;
  private FileLocater fileLocater;
  private IconFormat defaultIconFormat;
  private Evaluator evaluator;
  private JTextField widthField, heightField, coordField;
  private Container contentPanel;  

  public IconEditor()
  {
    super("Icon Editor");
    Image image =
      Toolkit.getDefaultToolkit().getImage(IconEditor.class.getResource("images/image.gif"));
    if (image != null)
      setIconImage(image);
    iconDescriptionCommands = new IconDescriptionCommands(this);
    zoomCommands = new ZoomCommands(this);
    iconEditorSessionCommands = new IconEditorSessionCommands(this);
    iconEditorSimulationCommands = new IconEditorSimulationCommands(this);
    tilingCommands = getManager().getTilingCommand();
    
    initFrame();    
    mdiAdapter = new MDIAdapter();
    getManager().addMDIListener(mdiAdapter);
    MDIDocument[] docs = getManager().getDocuments();
    propertyChangeAdapter = new PropertyChangeAdapter();
    layerAdapter = new LayerAdapter();
    for (int i=0; i<docs.length; i++){
      if (docs[i] instanceof IconEditorSessionDocument)
	docs[i].addPropertyChangeListener(propertyChangeAdapter);
    }
    createMenuBar();
    createToolBar();
  }

  private void initFrame() {
    createLayerPanel();
    JPanel statusBar = setupStatusPanel();
    
    JSplitPane splitPane;
    contentPanel = new JPanel();
    contentPanel.setLayout(new BorderLayout());
    contentPanel.add(getManager());
    splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
			       contentPanel, layerPanelScroller);
    splitPane.setDividerLocation(360);
    splitPane.setDividerSize(2);
    com.gensym.ntw.util.VersionHelper.setResizeWeight(splitPane, 1.0);
    layerPanelScroller.setPreferredSize(new Dimension(50,50));    
    getContentPane().add(splitPane);
    getContentPane().add(statusBar, BorderLayout.SOUTH);
  }
  
  @Override
  public void setVisible(boolean visible) {
    if (!visible) {
      Vector docs = getDocumentsChanged();
      for (int i=0;i<docs.size(); i++) {
	IconEditorSessionDocument doc =
	  (IconEditorSessionDocument)docs.elementAt(i);
	new YesNoDialog(this, "Save",
			true, "Do you want to save "+doc.getTitle(),
			new SaveClient(doc)).setVisible(true);
      }
    }
    super.setVisible(visible);
  }
  
  public Evaluator getDefaultEvaluator() {
    return evaluator;
  }
  
  public void setDefaultEvaluator(Evaluator evaluator) {
    this.evaluator = evaluator;    
  }
  
  public void setDefaultIconFormat(IconFormat iconFormat) {
    this.defaultIconFormat = iconFormat;
    ((IconEditorSessionCommands)iconEditorSessionCommands).setDefaultIconFormat(iconFormat);
    iconDescriptionCommands.setDefaultIconFormat(iconFormat);    
  }
  
  public void setIconFinder(Finder finder) {
    ((IconEditorSessionCommands)iconEditorSessionCommands).setIconFinder(finder);        
  }

  public void setIconSaver(Savable saver) {
    iconDescriptionCommands.setSaver(saver);
  }

  public void setIconSaver(IconEditorSessionDocument doc,
			   Savable saver) {
    iconDescriptionCommands.setSaver(doc,saver);
  }
  
  public IconEditorSessionDocument openSession(Finder finder) {
    IconEditorSessionDocument doc =
      ((IconEditorSessionCommands)iconEditorSessionCommands).openSession(finder);
    return doc;
  }

  Vector getDocumentsChanged() {
    MDIDocument[] docs = getManager().getDocuments();
    Vector returnVector = new Vector();
    int length = docs.length;
    for (int i=0; i<length; i++)
      if (((IconEditorSessionDocument)docs[i]).getCanvas().getHasChanged())
	returnVector.addElement((IconEditorSessionDocument)docs[i]);
    return returnVector;
  }

  private JPanel setupStatusPanel() {
    GridBagLayout gbl = new GridBagLayout();
    GridBagConstraints gbc = new GridBagConstraints();
    statusPanel = new JPanel(gbl);
    JPanel filler = new JPanel();
    JLabel widthLabel, heightLabel, coordLabel;
    widthLabel = new JLabel(" width:");
    heightLabel = new JLabel(" height:");
    widthField = new JTextField();
    heightField = new JTextField();
    coordField = new JTextField();
    coordField.setBorder(null);
    widthField.setEditable(true);
    heightField.setEditable(true);
    coordField.setEditable(false);
    coordField.setBackground(Color.lightGray);
    widthField.setBackground(Color.white);
    heightField.setBackground(Color.white);
    widthField.setHorizontalAlignment(JTextField.RIGHT);
    heightField.setHorizontalAlignment(JTextField.RIGHT);
    coordField.setHorizontalAlignment(JTextField.CENTER);
    widthField.setColumns(3);
    heightField.setColumns(3);
    coordField.setColumns(6);
    gbc.anchor = GridBagConstraints.EAST;
    gbc.weightx = .9;
    gbc.gridwidth = 6;
    gbc.fill = GridBagConstraints.HORIZONTAL;
    gbl.setConstraints(filler, gbc);
    gbc.gridwidth = 1;
    gbc.weightx = 0.01;
    gbc.fill = GridBagConstraints.NONE;
    gbl.setConstraints(widthLabel,gbc);
    gbl.setConstraints(heightLabel, gbc);
    gbl.setConstraints(widthField, gbc);
    gbl.setConstraints(heightField, gbc);
    gbl.setConstraints(coordField, gbc);
    statusPanel.setBorder(new LineBorder(Color.lightGray));
    statusPanel.add(filler);
    statusPanel.add(coordField);
    statusPanel.add(widthLabel);
    statusPanel.add(widthField);
    statusPanel.add(heightLabel);
    statusPanel.add(heightField);
    return statusPanel;
  }

  public JTextField getWidthField() {
    return widthField;
  }
  public JTextField getHeightField() {
    return heightField;
  }
  public JTextField getCoordField() {
    return coordField;
  }
  
  private void createLayerPanel()
  {
    JPanel encapsulatingPanel = new JPanel(new BorderLayout());
    MDIManager manager = getManager();
    
    layerPanel = new LayerPanel();
    layerPanel.setLayout(new FlowLayout(FlowLayout.LEADING, 10,10));
    layerPanel.setBackground(Color.lightGray);
    layerPanelScroller = new JScrollPane(layerPanel,
					 JScrollPane.VERTICAL_SCROLLBAR_NEVER,
					 JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

    layerPanel.addMouseListener(new LayerPanelMouseAdapter(layerPanel));
    layerDragAdapter = new LayerDragAdapter();
    layerPanel.addMouseMotionListener(layerDragAdapter);
    layerPanel.addMouseListener(layerDragAdapter);
  }

  Container getContentPanel() {
    return contentPanel;
  }
  
  private void updateLayers(IconEditorCanvas canvas)
  {
    this.currentCanvas = canvas;
    if (canvas == null) {
      layerPanel.removeAll();
      layerPanel.validate();
      layerPanel.repaint();
    } else {
      Layer[] layers = canvas.getLayers();
      for (int i=0;i<layers.length;i++){
	addLayerView(layers[i]);
      }
      layerPanel.validate();
      layerPanel.repaint();
    }
	
  }

  private static int layerViewBorderWidth = 5;
  private static LineBorder selectedBorder = new LineBorder(Color.yellow, layerViewBorderWidth);
  private static LineBorder highlightBorder = new LineBorder(Color.cyan, layerViewBorderWidth);

  class LayerView extends JPanel //Container
  implements ActionListener {
    Layer layer;
    JCheckBox checkBox;
    LayerView(Layer layer) {
      setLayout(new BorderLayout());

      this.layer = layer;
      checkBox = new JCheckBox();
      checkBox.doClick();
      checkBox.addActionListener(this);
      checkBox.setToolTipText("Toggle Layer Visibility");//i18n
      add(checkBox, "South");      
      add(layer, "North");
      checkBox.setOpaque(false);
      checkBox.setLocation(0,0);
    }

    public void setSelected(boolean selected) {
      if (selected) 
	setBorder(selectedBorder);
      else
	setBorder(null);
    }

    public void setHighlighted(boolean highlighted) {
      if (highlighted) 
	setBorder(highlightBorder);
      else
	setBorder(null);
    }
    @Override
    public Dimension getPreferredSize() {
      Dimension layerSize = layer.getPreferredSize();
      int borderWidth = 0;
      if (getBorder()!= null) {
	borderWidth = layerViewBorderWidth*2;
	layerSize.width+=borderWidth;
	layerSize.height+=borderWidth;
      }
      return layerSize;
    }
    
    @Override
    public void actionPerformed(ActionEvent ae) {
      int layerCount = currentCanvas.getLayers().length;
      layer.setEnabled(!layer.isEnabled());
      if (!layer.isEnabled() && layer.isSelected()) {
	int layerPosition = currentCanvas.getLayerPosition(layer);
	if (layerPosition != 0) 
	  currentCanvas.setCurrentLayer
	    (currentCanvas.getLayers()[Math.max(0, layerPosition-1)]);
	else 
	  ((LayerView)layerViews.get(layer)).checkBox.doClick();
      }
    }
  }

  private Hashtable layerViews = new Hashtable();
  private void addLayerView(Layer layer)
  {
    int position = currentCanvas.getLayerPosition(layer);
    LayerView layerView = new LayerView(layer);
    layerViews.put(layer, layerView);
    layerPanel.add(layerView,position);
    layerPanel.validate();
    validate();
    layerPanel.repaint();
    if (currentCanvas.getCurrentLayer() == null) 
      currentCanvas.setCurrentLayer(layer);
  }

  private void removeLayerView(Layer layer)
  {
    LayerView layerView = (LayerView)layerViews.get(layer);
    layerPanel.remove(layerView);
    layerPanel.validate();
    validate();
    layerPanel.repaint();

  }

  private void createMenuBar()
  {
    CMenuBar menuBar = new CMenuBar();
    CMenu fileMenu = new CMenu("File");
    fileMenu.add(iconEditorSessionCommands, IconEditorSessionCommands.NEW,
		 IconEditorSessionDocument.menuConstraints);
    fileMenu.add(iconEditorSessionCommands, IconEditorSessionCommands.OPEN,
		 IconEditorSessionDocument.menuConstraints);
    fileMenu.addSeparator();
    fileMenu.add(iconEditorSessionCommands, IconEditorSessionCommands.EXIT,
		 IconEditorSessionDocument.menuConstraints);
    CMenu windowMenu = new CMenu("Window");
    windowMenu.add(tilingCommands);
    
    menuBar.add(fileMenu);
    menuBar.add(windowMenu);
    menuBar.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));    
    setDefaultMenuBar(menuBar);
  }

  private void createToolBar()
  {
    MDIToolBarPanel panel = new MDIToolBarPanel();
    ToolBar toolBar = new ToolBar();
    toolBar.setBorderPainted(true);
    toolBar.add(iconEditorSessionCommands, IconEditorSessionCommands.NEW);
    toolBar.add(iconEditorSessionCommands, IconEditorSessionCommands.OPEN);
    toolBar.setMargin(new java.awt.Insets(0,0,0,0));
    panel.setLayout(new BorderLayout());
    panel.add(toolBar, "West");
    setDefaultToolBarPanel(panel);
  }

  class LayerPanel extends JPanel {
    private InsertionPoint insertionPoint;
    Component getComponentToLeft(int x)
    {
      Component[] elements = getComponents();
      int i, len = elements.length;
      for (i = 0; i<len ; i++)
	if (elements[i].getLocation().x > x) {
	  if (i==0)
	    return null;
	  else
	    return elements[i-1];
	}
      return elements[len-1];
    }

    @Override
    public void paint(Graphics g) {
      super.paint(g);
      Rectangle bounds = getBounds();
      int bd = 2;
      g.setColor(Color.darkGray);
      g.drawLine(bd, bd, bounds.width-2*bd, bd);
      g.drawLine(bd, bd, bd, bounds.height -2*bd);
      g.setColor(Color.white);
      g.drawLine(bounds.width-2*bd, bd, bounds.width-2*bd, bounds.height -2*bd);
      g.drawLine(bd, bounds.height -2*bd, bounds.width-2*bd, bounds.height -2*bd);
      if (insertionPoint != null) {
	Point loc = insertionPoint.getLocation();
	g.translate(loc.x,loc.y);
	insertionPoint.paint(g);
	g.translate(-loc.x,-loc.y);
      }
    }
  }

  class InsertionPoint extends Component {
    Color color = Color.black;
    int width = 10;
    @Override
    public void paint(Graphics g) {
      g.setColor(color);
      Dimension size = getSize();
      int yPadding = 10;
      g.fillPolygon(new int[]{0,size.width, size.width/2},
      new int[]{yPadding/2,yPadding/2,yPadding/2+size.width}, 3);
      g.fillPolygon(new int[]{0,size.width, size.width/2},
      new int[]{size.height-yPadding*2,
		  size.height-yPadding*2,
		  size.height-((yPadding*2+size.width) + 2)}, 3);      
    }
  }
  
  class LayerDragAdapter extends MouseAdapter implements MouseMotionListener {
    LayerView focalLayer;
    boolean dragged = false;
    int startX, startY;
    final int START_DRAG_DISTANCE = 4;
    InsertionPoint insertPoint = new InsertionPoint();

    private Layer highlightedLayer;    
    @Override
    public void mouseDragged(MouseEvent me) {
      if (highlightedLayer != null) {
	LayerView layerView = (LayerView)layerViews.get(highlightedLayer);
	layerView.setHighlighted(false);
	highlightedLayer.setHighlighted(false);
	highlightedLayer.repaint();
	highlightedLayer = null;
      }
      Component c = ((Container)me.getSource()).getComponentAt(me.getX(), me.getY());
      if (!dragged && focalLayer != null &&
	  Math.sqrt(Math.pow(me.getX()-startX,2) +
		    Math.pow(me.getY()-startY,2)) > START_DRAG_DISTANCE) {
	dragged = true;
	layerPanel.setCursor(createCursor(focalLayer.layer));
      } else if (dragged && c instanceof LayerPanel){
	layerPanel.insertionPoint = insertPoint;
	insertPoint.setSize(insertPoint.width, layerPanel.getSize().height);
	insertPoint.setLocation(me.getX()-insertPoint.width/2, 0);
	layerPanel.repaint();
      } else if (c instanceof LayerView) {
	layerPanel.insertionPoint = null;
	if (c != focalLayer) {
	  highlightedLayer = ((LayerView)c).layer;
	  highlightedLayer.setHighlighted(true);
	  ((LayerView)c).setHighlighted(true);
	}
	layerPanel.repaint();
      }
    }   

    @Override
    public void mouseMoved(MouseEvent me) {
      Component c = ((Container)me.getSource()).getComponentAt(me.getX(), me.getY());
      if (!dragged) {
	if (c instanceof LayerView)
	  layerPanel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
	else
	  layerPanel.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
      } 
    }

    @Override
    public void mouseReleased(MouseEvent me) {
      if (highlightedLayer != null) {
	LayerView layerView = (LayerView)layerViews.get(highlightedLayer);
	layerView.setHighlighted(false);
	highlightedLayer.setHighlighted(false);
	highlightedLayer.repaint();
	highlightedLayer = null;
      }
      Point pt = me.getPoint();
      if (dragged) {
	Component c = ((Container)me.getSource()).getComponentAt(me.getX(), me.getY());
	if (c instanceof LayerPanel) {
	  LayerView componentToLeft = (LayerView)layerPanel.getComponentToLeft(me.getX());
	  if (componentToLeft != focalLayer) {
	    currentCanvas.removeLayer(focalLayer.layer);
	    if (componentToLeft != null)
	      currentCanvas.addLayer(focalLayer.layer,
				     currentCanvas.getLayerPosition(componentToLeft.layer)+1);
	    else
	      currentCanvas.addLayer(focalLayer.layer, 0);
	    currentCanvas.setCurrentLayer(focalLayer.layer);
	  }
	  layerPanel.insertionPoint = null;
	  layerPanel.repaint();	  
	} else if (c instanceof LayerView && c != focalLayer) {
	  Layer layer = ((LayerView)c).layer;
	  int currentLayerPosition = currentCanvas.getLayerPosition(focalLayer.layer);
	  int desiredLayerPosition = currentCanvas.getLayerPosition(layer);
	  boolean isCopy = me.isControlDown();
	  if (!isCopy)
	    currentCanvas.removeLayer(focalLayer.layer);
	  IconElement[] elts = focalLayer.layer.getElementsSnapshot();
	  currentCanvas.setCurrentLayer(layer);
	  for (int i=0;i<elts.length;i++) {
	    IconElement elt = elts[i];
	    try {
	      if (!isCopy) {
		focalLayer.layer.removeElement(elt);
		currentCanvas.addElement((Component)elt);
	      } else
		currentCanvas.addElement((Component)elt.copy());
	    } catch(ElementInconsistancyError eie) {
	      Trace.exception(eie);
	    }
	  }
	  layerPanel.repaint();
	}
	layerPanel.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	
	focalLayer = null;
	dragged = false;
      }
      layerPanel.insertionPoint = null;
    }
    
    @Override
    public void mousePressed(MouseEvent me) {
      Component c = ((Container)me.getSource()).getComponentAt(me.getX(), me.getY());
      if (c instanceof LayerView) {
	startX = me.getX(); startY = me.getY();
	focalLayer = (LayerView)c;
      }
    }
  }

  private static Cursor createCursor(Layer layer) {
    Image image = createImage(layer);
    Dimension size = layer.getPreferredSize();
    size = java.awt.Toolkit.getDefaultToolkit().getBestCursorSize(size.width,size.height);
    Cursor cursor = null;
    try {
      cursor =
	java.awt.Toolkit.getDefaultToolkit().createCustomCursor(image,
								new Point(size.width/2,
									  size.height/2),
								layer.toString());
    } catch (IndexOutOfBoundsException ioobe) {
      Trace.exception(ioobe);
    }
    return cursor;
  }
  
  private static Image createImage(Layer layer) {
    Color clr = layer.getColor();
    layer.setColor(Color.black);
    Dimension size = layer.getPreferredSize();
    Image image = layer.createImage(size.width, size.height);
    Graphics g = image.getGraphics();
    layer.paint(g);
    layer.setColor(clr);
    return image;
  }
  
  class LayerPanelMouseAdapter extends MouseAdapter
  {
    private CPopupMenu popup;
    private Container lp;
    
    LayerPanelMouseAdapter(Container lp) {
      this.lp = lp;
      popup = new CPopupMenu("Change");
      popup.add(iconDescriptionCommands, IconDescriptionCommands.NEW_LAYER,
		IconEditorSessionDocument.menuConstraints);
      popup.add(iconDescriptionCommands, IconDescriptionCommands.DELETE_LAYER,
		IconEditorSessionDocument.menuConstraints);
      popup.add(iconDescriptionCommands, IconDescriptionCommands.CLONE_LAYER,
		IconEditorSessionDocument.menuConstraints);
      popup.add(iconDescriptionCommands,
		IconDescriptionCommands.CLEAR_CURRENT_LAYER,
		IconEditorSessionDocument.menuConstraints);
      popup.add(iconDescriptionCommands, IconDescriptionCommands.UNGROUP,
		IconEditorSessionDocument.menuConstraints);
      popup.addSeparator();
      popup.add(iconDescriptionCommands, IconDescriptionCommands.CHANGE_LAYER_COLOR,
		IconEditorSessionDocument.menuConstraints);
      popup.setInvoker(lp);
    }
    
    private void doMouseEvent(MouseEvent me) {
      Component c = ((Container)me.getSource()).getComponentAt(me.getX(), me.getY());
      if (c instanceof LayerView) {
	Layer layer = ((LayerView)c).layer;
	if (!layer.isEnabled())
	  ((LayerView)c).checkBox.doClick();
	currentCanvas.setCurrentLayer(layer);
      }
    }

    private void doPopup(MouseEvent me) {
      Component c = ((Container)me.getSource()).getComponentAt(me.getX(), me.getY());
      if (c instanceof LayerView) {
	doMouseEvent(me);
	Point p = me.getPoint();
	popup.show(lp,p.x,p.y);
      }
    }
    
    @Override
    public void mouseClicked(MouseEvent me) {
      if (me.isPopupTrigger())
	doPopup(me);
    }

    @Override
    public void mouseReleased(MouseEvent me) {
      if (me.isPopupTrigger())
	doPopup(me);      
    }
    
    @Override
    public void mousePressed(MouseEvent me) {
      if (me.isPopupTrigger())
	doPopup(me);
      else
	doMouseEvent(me);
    }
  }
  
  class MDIAdapter implements MDIListener {
    @Override
    public void documentAdded(MDIEvent event) {
      MDIDocument document = (MDIDocument)event.getDocument();
      if (document instanceof IconEditorSessionDocument) {
	IconEditorSessionDocument iconDoc = (IconEditorSessionDocument)document;
	iconDoc.addPropertyChangeListener(propertyChangeAdapter);
	IconEditorCanvas canvas = iconDoc.getCanvas();
	canvas.addLayerListener(layerAdapter);
	updateLayers(canvas);
      }
    }
  }

  class PropertyChangeAdapter implements PropertyChangeListener {
    @Override
    public void propertyChange(PropertyChangeEvent e) {
      MDIDocument document = (MDIDocument)e.getSource();
            if (document instanceof IconEditorSessionDocument) {
	IconEditorSessionDocument iconDoc = (IconEditorSessionDocument)document;
	String property = e.getPropertyName();
	if (property.equals(IconEditorSessionDocument.IS_SELECTED_PROPERTY)){
	  Boolean selected = (Boolean)e.getNewValue();
	  if (selected.booleanValue()) 
	    updateLayers(iconDoc.getCanvas());
	  else 
	    updateLayers(null);	  
	} else if (property.equals(IconEditorSessionDocument.IS_CLOSED_PROPERTY)) {
	  contentPanel.remove(contentPanel.getComponentAt(new Point(1, 1)));
	  validate();
	  if (iconDoc.getCanvas()==currentCanvas) 
	    updateLayers(null);	  
	}
      }
    }
  }

  public class LayerAdapter implements LayerListener {
    @Override
    public void layerAdded(Layer layer)
    {
      addLayerView(layer);
    }
    
    @Override
    public void layerRemoved(Layer layer)
    {
      removeLayerView(layer);
    }

    @Override
    public void layerUnSelected(Layer layer) {
      LayerView layerView = (LayerView)layerViews.get(layer);
      layerView.setSelected(false);
      layerPanel.repaint();            
    }
    
    @Override
    public void layerSelected(Layer layer) {
      if (layer != null) {
	Point layerPosition = layer.getLocation();
	JViewport viewPort = layerPanelScroller.getViewport();
	Rectangle viewRect = viewPort.getViewRect();
	if (!viewRect.contains(layerPosition)) {
	  if ((viewRect.x+viewRect.width) < layerPosition.x)
	    layerPosition.translate(viewRect.width, 0);
	  viewPort.setViewPosition(layerPosition);
	}
	LayerView layerView = (LayerView)layerViews.get(layer);
	layerView.setSelected(true);
	layerPanel.repaint();      
      }
    }
    @Override
    public void layersResized() {
      layerPanel.validate();
      validate();
      layerPanel.repaint();      
    }
  }

  public void setFileLocater(FileLocater fileLocater) {
    this.fileLocater = fileLocater;
  }
  
  public FileLocater getFileLocater() {
    if (fileLocater == null) {
      fileLocater = new FileLocater() {
	@Override
	public URL getFile(FileFilter filter) {
	  String startingDirectoryName =
	    "file:///"+ System.getProperty("user.dir").replace('\\','/');
	  JFileChooser chooser = new JFileChooser(new File(startingDirectoryName));
	  
	  if (filter != null) 
	    chooser.setFileFilter(filter);
	  Frame parent = null;
	  int returnVal = chooser.showOpenDialog(parent);
	  if (returnVal == JFileChooser.APPROVE_OPTION) {
	    try {
	      return chooser.getSelectedFile().toURL();
	    } catch (MalformedURLException murle) {
	      Trace.exception(murle);
	      return null;
	    }
	  } else
	    return null;
	}
      };
    }
    return fileLocater;
  }
  class SaveClient implements StandardDialogClient {

    private IconEditorSessionDocument doc;
    
    public SaveClient (IconEditorSessionDocument doc) {
      this.doc = doc;
    }
    @Override
    public void dialogDismissed(StandardDialog dlg, int index) {
      if (index == dlg.YES) {
	Savable saver = IconDescriptionCommands.getSaver(doc);
	if (saver == null)
	  saver = new com.gensym.editor.icon.g2.G2IconDescriptionSaver();
	iconDescriptionCommands.doSave(saver,doc.getCanvas(), false);
      }
    }
  }
  
}



