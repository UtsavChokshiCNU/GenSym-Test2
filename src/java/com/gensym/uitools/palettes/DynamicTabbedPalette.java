package com.gensym.uitools.palettes;

import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import java.util.Hashtable;
import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Container;
import java.awt.Insets;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JFrame;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import com.gensym.ui.menu.awt.CPopupMenu;
import java.util.Vector;
import com.gensym.ui.StructuredCommand;
import java.awt.event.ActionEvent;

public class DynamicTabbedPalette extends JFrame
{
  private CPopupMenu popupMenu = new CPopupMenu ();
  private DynamicPaletteCommand paletteCommand;
  private JTabbedPane paletteGroup;
  //private int paletteCount = 0;  

  protected JTabbedPane createPaletteGroup()
  {
    JTabbedPane paletteGroup = new JTabbedPane(SwingConstants.RIGHT);//TOP);
    paletteGroup.addMouseListener (new MouseAdapter () {
      @Override
      public void mousePressed (MouseEvent mEvt)
	{if (mEvt.isPopupTrigger ()) displayPopup (mEvt);}
      @Override
      public void mouseReleased (MouseEvent mEvt)
	{if (mEvt.isPopupTrigger ()) displayPopup (mEvt);}
      @Override
      public void mouseClicked (MouseEvent mEvt)
	{if (mEvt.isPopupTrigger ()) displayPopup (mEvt);}
    });
    return paletteGroup;
  }

  public void setPaletteGroup(JTabbedPane paletteGroup)
  {
    if (paletteGroup == this.paletteGroup) return;
    if (this.paletteGroup != null)
      getContentPane().remove(this.paletteGroup);
    this.paletteGroup = paletteGroup;
    if (paletteGroup != null)
      getContentPane().add(paletteGroup, BorderLayout.CENTER);
    adjust();
  }
  
  public DynamicTabbedPalette(String title)
  {
    super(title);
    getContentPane().setLayout(new BorderLayout());
    setLocation (0, 0);
    removeCommand = new RemoveCommand();
    pack();

  }

  public DynamicPaletteCommand getPaletteCommand () {
    return paletteCommand;
  }

  protected void setPaletteCommand(DynamicPaletteCommand paletteCommand)
  {
    this.paletteCommand = paletteCommand;
    if (paletteCommand != null) {
      removeCommand.setShortResource(paletteCommand.getShortResource());
      removeCommand.setLongResource(paletteCommand.getLongResource());
    }
  }

  private RemoveCommand removeCommand;
  protected CPopupMenu getPopupMenu(MouseEvent mEvt)
  {
    popupMenu.removeAll();
    if (paletteCommand != null) {
      //shouldn't assume this is an add command
      com.gensym.ui.menu.awt.CMenu addMenu = new com.gensym.ui.menu.awt.CMenu("Add");
      addMenu.add(paletteCommand);
      popupMenu.add(addMenu);
    }
    Object src = mEvt.getSource();
    Vector showingPalettes = getCurrentPaletteNames();
    if (!showingPalettes.isEmpty()) {
      com.gensym.ui.menu.awt.CMenu removeMenu
	= new com.gensym.ui.menu.awt.CMenu("Remove");      
      removeCommand.setNames(showingPalettes);
      removeMenu.add(removeCommand);
      popupMenu.add(removeMenu);
    }
    return popupMenu;
  }

  private Vector getCurrentPaletteNames()
  {
    Vector showingPalettes = new Vector();
    for (int i=0;i<paletteGroup.getTabCount();i++) {
      Component palette = paletteGroup.getComponentAt(i);
      showingPalettes.addElement(palette.getName());
    }
    return showingPalettes;
  }

  public Component getPalette(String name)
  {
    for (int i=0;i<paletteGroup.getTabCount();i++) {
      Component palette = paletteGroup.getComponentAt(i);
      if (name.equals(palette.getName()))
	return palette;
    }
    return null;
  }
  
  class RemoveCommand extends com.gensym.shell.commands.DynamicListCommand
  {
    @Override
    public void actionPerformed(ActionEvent ae)
    {
      //SHOULD MAKE A DYNAMICPALETTECOLLECTIONLISTENER 
      //AND SEND OUT A COLLECTIONCHANGED EVENT
      if (paletteCommand != null) 
	paletteCommand.removePalette(ae.getActionCommand());
      else
	removePalette(getPalette(ae.getActionCommand()));
    }
  }
  
  
  private void displayPopup (MouseEvent mEvt) {
    CPopupMenu popupMenu = getPopupMenu(mEvt);
    paletteGroup.add(popupMenu);
    popupMenu.show (paletteGroup, mEvt.getX(), mEvt.getY());
  }
  
  public void addPalette(String tabLabel, Component palette)
  {
    paletteGroup.addTab (tabLabel, palette);
    //paletteCount++;
    paletteGroup.setSelectedComponent(palette);    
    adjust();
  }

  @Override
  public Dimension getMinimumSize()
  {
    return new Dimension(200,300);
  }

  @Override
  public Dimension getPreferredSize()
  {
    Dimension min = getMinimumSize();
    Dimension current = getSize();
    current.width = Math.max(min.width, current.width);
    current.height = Math.max(min.height, current.height);
    return current;
  }
  
  private void adjust() {
    if (paletteGroup == null) return;
    Dimension size = paletteGroup.getPreferredSize();
    Insets insets = getInsets();
    Dimension newSize = new Dimension(size.width + insets.left + insets.right,
				      size.height + insets.top + insets.bottom);
    setSize(newSize);
    paletteGroup.invalidate();
    invalidate();
    paletteGroup.invalidate();
    paletteGroup.repaint ();
    setSize(getPreferredSize());
  }
  
  public void removePalette(Component palette)
  {
    paletteGroup.remove(palette);
    //--paletteCount;
    adjust();
  }

}
