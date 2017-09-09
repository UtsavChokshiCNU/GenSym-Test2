package com.gensym.uitools.utils;

import java.awt.Container;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseListener;
import java.awt.Cursor;
import java.awt.Color;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Point;
import javax.swing.JComponent;
import javax.swing.Scrollable;

public class ResizeContainer extends Container implements Scrollable {
  private Point rubberBandLocation;  
  private Component component;
  private GridBagLayout layout;
  private GridBagConstraints constraints;
  private int markerSize = 3;
  private Color markerColor = Color.blue;
  private boolean dragInRealTime;    

  public ResizeContainer(Component component) {
    this.component = component;        
    layout = new GridBagLayout();
    setLayout(layout);

    constraints = new GridBagConstraints();    
    constraints.fill = constraints.NONE;    
    constraints.anchor = constraints.NORTHWEST;
    layout.setConstraints(component, constraints);
    add(component);

    constraints.weightx=1; constraints.weighty=1;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    addMarker(constraints.EAST, true, false);
    constraints.gridwidth = 2;
    addMarker(constraints.SOUTH, false, true);
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    addMarker(constraints.SOUTHEAST, true, true);
  }

  private void addMarker(int location, boolean horizontal, boolean vertical) {
    Marker marker = new Marker(horizontal, vertical);
    constraints.anchor = location;
    layout.setConstraints(marker, constraints);
    add(marker);
  }
  
  public void setDragInRealTime(boolean dragInRealTime) {
    this.dragInRealTime = dragInRealTime;
  }

  public void setMarkerColor(Color markerColor) {
    this.markerColor = markerColor;
  }

  public void setMarkerSize(int size) {
    this.markerSize = size;
  }
  
  @Override
  public void paint(Graphics g) {
    super.paint(g);
    if (rubberBandLocation != null) {
      g.setColor(markerColor);
      g.drawRect(0,0, rubberBandLocation.x, rubberBandLocation.y);
    }    
  }
  
  
  //Scrollable Interface
  
  @Override
  public Dimension getPreferredScrollableViewportSize() {
    if (component instanceof Scrollable)
      return ((Scrollable)component).getPreferredScrollableViewportSize();
    else
      return component.getSize();
  }

  @Override
  public int getScrollableBlockIncrement(Rectangle visibleRect,
					 int orientation, int direction) {
    if (component instanceof Scrollable)
      return ((Scrollable)component).getScrollableBlockIncrement(visibleRect, orientation, direction);
    else
      return 8;
  }

  @Override
  public boolean getScrollableTracksViewportHeight() {
    if (component instanceof Scrollable)    
      return ((Scrollable)component).getScrollableTracksViewportHeight();
    else
      return false;
  }

  @Override
  public boolean getScrollableTracksViewportWidth() {
    if (component instanceof Scrollable)    
      return ((Scrollable)component).getScrollableTracksViewportWidth();
    else
      return false;
  }
  
  @Override
  public int getScrollableUnitIncrement(Rectangle visibleRect,
					int orientation, int direction)
  {
    if (component instanceof Scrollable)
      return ((Scrollable)component).getScrollableUnitIncrement(visibleRect, orientation, direction);
    else
      return 4;
  }

  class Marker extends JComponent
  implements MouseMotionListener, MouseListener {
    boolean horizontal, vertical, dragging;
    Marker(boolean horizontal, boolean vertical) {
      this.horizontal = horizontal;
      this.vertical = vertical;
      addMouseMotionListener(this);
      addMouseListener(this);
      setPreferredSize(new Dimension(markerSize, markerSize));
      setBackground(markerColor);
    }
    private final Cursor getResizeCursor() {
      if (horizontal && vertical)
	return Cursor.getPredefinedCursor(Cursor.SE_RESIZE_CURSOR);
      else if (horizontal)
	return Cursor.getPredefinedCursor(Cursor.E_RESIZE_CURSOR);
      else if (vertical)
	return Cursor.getPredefinedCursor(Cursor.S_RESIZE_CURSOR);
      return Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR);
    }
    @Override
    public void mousePressed(MouseEvent e) {}
    @Override
    public void mouseMoved(MouseEvent me) {}    
    @Override
    public void mouseClicked(MouseEvent e) {}
    @Override
    public void mouseEntered(MouseEvent e) {
      if (!dragging)
	setCursor(getResizeCursor());
    }
    @Override
    public void mouseExited(MouseEvent e) {
      if (!dragging)      
	setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }
    @Override
    public void mouseDragged(MouseEvent me) {
      dragging = true;
      Point location = getLocation();
      Dimension size = ResizeContainer.this.getSize();      
      if (horizontal) {
	location.x+=me.getX();
	size.width=location.x+markerSize;
      }
      if (vertical) {
	location.y+=me.getY();
	size.height=location.y+markerSize;
      }
      ResizeContainer.this.setSize(size);
      setLocation(location);
      size.width-=(markerSize+1);
      size.height-=(markerSize+1);
      if (rubberBandLocation == null)
	rubberBandLocation = new Point(0,0);      
      rubberBandLocation.x=size.width;
      rubberBandLocation.y=size.height;
      if (dragInRealTime) 
	component.setSize(size);
      ResizeContainer.this.validate();
      repaint();
    }
    @Override
    public void mouseReleased(MouseEvent me) {
      dragging = false;
      rubberBandLocation = null;
      if (!dragInRealTime) {
	Dimension size = ResizeContainer.this.getSize();            
	size.width-=(markerSize+1);
	size.height-=(markerSize+1);      
	component.setSize(size);
	ResizeContainer.this.validate();
	repaint();
      }
    }    
    @Override
    public void paint(Graphics g) {
      g.setColor(getBackground());
      Dimension size = this.getSize();
      g.fillRect(0,0,size.width,size.height);
    }
  }
  
}

