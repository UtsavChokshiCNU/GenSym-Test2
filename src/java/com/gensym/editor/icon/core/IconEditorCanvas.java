package com.gensym.editor.icon.core;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import java.util.Vector;
import java.util.Enumeration;
import com.gensym.editor.icon.shell.IconEditorSessionDocument;
import com.gensym.editor.icon.shell.IconEditor;
import com.gensym.editor.icon.shapes.IconElement;
import com.gensym.editor.icon.tools.ChangeTool;
import com.gensym.editor.icon.tools.MoveTool;
import com.gensym.message.Trace;
import com.gensym.editor.icon.core.ElementInconsistancyError;
import java.util.Hashtable;
import java.awt.Point;
import com.gensym.dlg.MessageDialog;
import java.awt.Frame;
import java.awt.Container;
import javax.swing.JTextField;
import java.awt.RenderingHints;

/**
 * @author Paul B. Konigsberg
 */

public class IconEditorCanvas extends ToolContainer
{
  private Layer currentLayer;
  private Vector layers = new Vector();
  private boolean privateRemoving = false;
  private int iconWidth = 50, iconHeight = 50;
  private Vector layerListeners = new Vector();
  private static final int ADDED = 0, REMOVED = 1, SELECTED = 2, UNSELECTED = 3, RESIZED = 4;
  private Evaluator evaluator;
  private Tool defaultTool = new ChangeTool(this);
  private IconEditorSessionDocument sessionDocument;
  private JTextField widthField, heightField;
  private AffineTransform tx;
  private boolean hasChanged;
  private IconEditor iconEditor;
  
  public IconEditorCanvas() {
    setIconWidth(iconWidth);
    setIconHeight(iconHeight);
  }

  public IconEditorCanvas(IconEditorSessionDocument sessionDocument,
			  JTextField widthField,
			  JTextField heightField, IconEditor iconEditor) {
    this();
    this.sessionDocument = sessionDocument;
    this.widthField = widthField;
    widthField.setText(""+iconWidth);
    this.heightField = heightField;
    heightField.setText(""+iconHeight);
    FieldListener fl = new FieldListener();
    widthField.addActionListener(fl);
    heightField.addActionListener(fl);
    this.iconEditor = iconEditor;
  }

  public boolean getHasChanged() {
    return hasChanged;
  }

  public void setHasChanged(boolean changed) {
    hasChanged = changed;
  }
  
  @Override
  protected void processMouseEvent (MouseEvent e){
    inverseTransformMouseEvent(e);
    super.processMouseEvent (e);
  }
  
  @Override
  protected void processMouseMotionEvent (MouseEvent e){
    inverseTransformMouseEvent(e);
    super.processMouseMotionEvent (e);
  }

  private final void inverseTransformMouseEvent(MouseEvent e){
   if (tx != null){
      Point location = e.getPoint();
      int originalX = location.x;
      int originalY = location.y;
      try{
	tx.inverseTransform(location, location);
	e.translatePoint(location.x - originalX, 
			 location.y - originalY);
      }
      catch(NoninvertibleTransformException ex){
	Trace.exception(ex);
      }
    }
  }

  @Override
  public void paint(Graphics g){
    if (g instanceof Graphics2D && tx != null) {
      ((Graphics2D)g).transform(tx);
      ((Graphics2D)g).setRenderingHint(RenderingHints.KEY_ANTIALIASING,
				       RenderingHints.VALUE_ANTIALIAS_ON);
    }
    super.paint(g);
  }
    @Override
    public void repaint(){
    super.repaint(0, 0, 0, getWidth(), getHeight());
  }

  @Override
  public void repaint(long tm) {
    super.repaint(tm, 0, 0, getWidth(), getHeight());
  }

  @Override
  public void repaint (long tm, int x, int y, int width, int height) {
    if (tx != null){
      Point p1 = new Point(x, y);
      Point p2 = new Point(width, height);
      tx.transform(p1, p1);
      tx.transform(p2, p2);
      super.repaint (tm, p1.x-1, p1.y-1, p2.x+2, p2.y+2);
    }
    else
      super.repaint(tm, x, y, width, height);
  }
  public Evaluator getEvaluator() {
    return this.evaluator;
  }

  
   public void setScale(double sx, double sy) throws NoninvertibleTransformException{
    if (tx == null || (tx != null && (sx != tx.getScaleX() || sy != tx.getScaleY()))){
      AffineTransform newTx = new AffineTransform();
      newTx.setToScale(sx, sy);
      setTransform(newTx);
    }
  }

  /**
   * Sets the x-axis scaling factor
   * @see #setScaleY
   * @see #setScale
   */
  public void setScaleX(double sx) throws NoninvertibleTransformException{
    setScale(sx, getScaleY());
  }

  /**
   * Sets the y-axis scaling factor
   * @see #setScaleX
   * @see #setScale
   */
  public void setScaleY(double sy) throws NoninvertibleTransformException{
    setScale(getScaleX(), sy);
  }

  /**
   * Returns the x-axis scaling factor
   */
  public double getScaleX(){
    if (tx == null)
      return 1.0;
    return tx.getScaleX();
  }

  /**
   * Returns the y-axis scaling factor
   */
  public double getScaleY(){
    if (tx == null)
      return 1.0;
    return tx.getScaleY();
  }

  /**
   * @undocumented until scrolling works with rotation
   */
  protected void setTransform(AffineTransform tx) throws NoninvertibleTransformException{
    if (tx != null && tx.getDeterminant() != 0.0){
      this.tx = tx;
      setIconSize(getIconWidth().intValue(), getIconHeight().intValue());
      repaint();
    }
    else
      throw new NoninvertibleTransformException("Determinant is 0");
  }

  @Override
  public Dimension getPreferredSize(){
    Dimension size = new Dimension(iconWidth+1, iconHeight+1);
    if (tx == null){
      return size;
    }
      //assumes tx is just a scale, handle generic tx?
      double sx = tx.getScaleX();
      double sy = tx.getScaleY();
      return new Dimension(Math.round((float)(size.width*sx)), Math.round((float)(size.height*sy)));
  }

  /**
   * @undocumented until scrolling works with rotation
   */
  protected AffineTransform getTransform(){
    if (tx != null)
      return (AffineTransform)tx.clone();
    return null;
  }

  private void setIconEditor(IconEditor iconEditor) {
    this.iconEditor = iconEditor;
  }

  public IconEditor getIconEditor() {
    return iconEditor;
  }
  
  public IconEditorCanvas copy() {
    IconEditorCanvas copy = new IconEditorCanvas();
    if (iconEditor != null)
      copy.setIconEditor(iconEditor);
    copy.setIconWidth(getIconWidth().intValue());
    copy.setIconHeight(getIconHeight().intValue());
    if (evaluator != null)
      copy.setEvaluator(evaluator.copy());
    Layer[] layers = getLayers();
    for (int i=0;i<layers.length;i++) {
      try {
	copy.addLayer(layers[i].copy(),i);
      } catch (ElementInconsistancyError eie) {
	Trace.exception(eie);
      }
    }
    copy.setEventHandler(null);
    return copy;
  }
  
  public void setEvaluator(Evaluator evaluator) {
    this.evaluator = evaluator;
  }
  
  public int getLayerPosition(Layer layer)
  {
    return layers.indexOf(layer);
  }

  public Layer addNewLayer(int zPosition)
  {
    Layer newLayer = new Layer();
    newLayer.setColor(current_color);
    addLayer(newLayer, zPosition);
    return newLayer;
  }

  public void addLayer(Layer layer, int zPosition)
  {
    hasChanged = true;
    Layer realCurrentLayer = currentLayer;
    currentLayer = layer;
    layer.setMinimumWidth(getIconWidth().intValue());
    layer.setMinimumHeight(getIconHeight().intValue());
    layers.insertElementAt(layer,zPosition);
    IconElement[] e = layer.getElementsSnapshot();
    layer.clear();
    synchronized(this) {
      for (int i = e.length-1;i>-1; i--) {
	IconElement ie = e[i];
	ie.setLayer(null);
	addElement((Component)ie);
      }
    }
    currentLayer = realCurrentLayer;
    updateLayerListeners(layer, ADDED);
  }

  public void addLayerListener(LayerListener listener)
  {
    layerListeners.addElement(listener);
  }

  public void removeLayerListener(LayerListener listener)
  {
    layerListeners.removeElement(listener);
  }
  
  public Layer[] getLayers()
  {
    Layer[] layerArray = new Layer[layers.size()];
    layers.copyInto(layerArray);
    return layerArray;
  }
  
  private void removeElementsOfLayer(Layer layer) {
    IconElement[] elts = layer.getElementsSnapshot();
    privateRemoving = true;
    for (int i=0;i<elts.length;i++) {
      Component elt = (Component)elts[i];
      removeElement(elt);
    }
    privateRemoving = false;
  }
  
  public boolean removeLayer(Layer layer)
  {
    hasChanged = true;
    if (layers.contains(layer)) {
      int index = layers.indexOf(layer);
      layers.removeElementAt(index);
      if (index != 0 && currentLayer == layer) 
	setCurrentLayer((Layer)layers.elementAt(Math.max(0, index-1)));      
      removeElementsOfLayer(layer);
    }
    updateLayerListeners(layer, REMOVED);
    if (layers.size() == 0) {
      addNewLayer(0);
      setCurrentLayer((Layer)layers.elementAt(0));
    }
    return true;
  }

  private void updateLayerListeners(Layer layer, int methodType)
  {
    Vector lCopy = null;
    synchronized(this) {
      lCopy = (Vector)layerListeners.clone();
    }
    Enumeration e = lCopy.elements();
    while (e.hasMoreElements()) {
      LayerListener l = (LayerListener)e.nextElement();
      switch (methodType) {
      case ADDED:
	l.layerAdded(layer);
	break;
      case REMOVED:
	l.layerRemoved(layer);
	break;
      case SELECTED:
	l.layerSelected(layer);
	break;
      case UNSELECTED:
	l.layerUnSelected(layer);
	break;
      case RESIZED:
	l.layersResized();
      }
    }
  }

  private Tool disabledTool;
  @Override
  public void setEventHandler(Tool eh) {
    if (disabledTool == null)
      super.setEventHandler(eh);
    else {
      if (eh instanceof MoveTool)
	super.setEventHandler(eh);
      disabledTool = eh;
    }
  }
  
  public void setCurrentLayer(Layer layer)
  {
    if (currentLayer != null) {
      currentLayer.setSelected(false);
      updateLayerListeners(currentLayer, UNSELECTED);
      currentLayer.repaint();      
    } 
    if (layer == null) {
      Tool tmpDisabledTool = getEventHandler();
      if (!(tmpDisabledTool instanceof MoveTool))
	setEventHandler(defaultTool);
      disabledTool = tmpDisabledTool;
      currentLayer = layer;
      updateLayerListeners(layer, SELECTED);
    } else if (layers.contains(layer)) {
      if (disabledTool != null) {
	Tool tmpDisabledTool = disabledTool;
	disabledTool = null;
	setEventHandler(tmpDisabledTool);
      }      
      currentLayer = layer;
      current_color = layer.getColor();
      if (currentLayer != null) {
	currentLayer.setSelected(true);
	currentLayer.repaint();
	updateLayerListeners(layer, SELECTED);
      }
    } else {
      //throw an error
      System.out.println("NOT SETTING CURRENT LAYER BECAUSE IT ISNT ADDED YET");
    }
  }
  
  public Layer getCurrentLayer()
  {
    return currentLayer;
  }

  @Override
  public void addElement(Component component) {
    hasChanged = true;
    IconElement prevElement = null;
    int position=getComponents().length;//bottom
    int layerPosition = getLayerPosition(currentLayer);
    while (prevElement == null && layerPosition > -1) {
      Layer layer = (Layer)layers.elementAt(layerPosition);
      prevElement = layer.getTopMostElement();
      layerPosition--;
    }
    if (prevElement != null)
      position = getElementPosition((Component)prevElement);
    addElement(component, position);
  }
  
  @Override
  public Component add(Component component, int position)
  {
    hasChanged = true;
    if (currentLayer == null) {
      Container frame = this;
      while (!(frame instanceof Frame))
	frame = frame.getParent();
      (new MessageDialog((Frame)frame, "",true,"Please select a layer in which to draw",null)).setVisible(true);
      repaint();
      return null;
    }
    if (component instanceof IconElement) {
      try {
	currentLayer.addElement((IconElement)component);
	repaint();
	currentLayer.repaint();
	return super.add(component, position);
      } catch (ElementInconsistancyError eie) {
	System.out.println(eie);
	return null;
      }
    } else
      return super.add(component, position);
  }

  @Override
  public String toString() {
    return "IconEditorCanvas:"+hashCode();
  }

  public void clearLayer(Layer layer) {
    hasChanged = true;
    IconElement[] elts = layer.getElementsSnapshot();
    for (int i=0;i<elts.length;i++) 
      removeElement((Component)elts[i]);
  }
  
  @Override
  public void remove(int i)
  {
    hasChanged = true;
    Component component = getComponent(i);
    if (!privateRemoving && component instanceof IconElement) {
      try {
	IconElement elt = (IconElement)component;
	Layer layer = elt.getLayer();
	layer.removeElement(elt);
	layer.repaint();
	super.remove(i);
      } catch (ElementInconsistancyError eie) {
	System.out.println(eie);
      }
    } else
      super.remove(i);
  }

  public Integer getIconWidth()
  {
    return new Integer(iconWidth);
  }


  @Override
  public void setSize(Dimension size) {
    setIconSize(size.width, size.height);
  }
  
  public void setIconWidth(int width)
  {
    setIconSize(width,iconHeight);
  }
  
  public Integer getIconHeight()
  {
    return new Integer(iconHeight);
  }

  public void setIconSize(int width, int height) {
    hasChanged = true;
    iconWidth = width;
    iconHeight = height;
    
    Point location = getLocation();
    reshape(location.x,location.y,iconWidth,iconHeight);
    Enumeration e = layers.elements();
    while (e.hasMoreElements()) {
      Layer elt = (Layer)e.nextElement();
      elt.setMinimumWidth(width);      
      elt.setMinimumHeight(height);
      elt.setSize(width,height);
    }
    if (widthField != null) 
      widthField.setText(""+width);
    if (heightField != null) 
      heightField.setText(""+height);
    updateLayerListeners(null, RESIZED);
    validate();
  }

  public void setIconHeight(int height)
  {
    setIconSize(iconWidth, height);
  }

  public Object getIconBackgroundLayer()
  {
    return null;
  }


  class FieldListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
      JTextField source = (JTextField)e.getSource();
      int newVal = new Integer(source.getText()).intValue();

      if (source == widthField)
	setIconWidth(newVal);
      else if (source == heightField)
	setIconHeight(newVal);
    }
  }
}
