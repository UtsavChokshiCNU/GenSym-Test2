package com.gensym.swing.plaf;

import java.awt.event.*;
import java.beans.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.plaf.*;
import javax.swing.plaf.basic.*;
import com.sun.java.swing.plaf.motif.*;

public class GensymMotifFileChooserUI extends MotifFileChooserUI
{
  private BasicDirectoryModel directoryModel = null;
  private PropertyChangeListener propertyChangeListener = null;
  private AncestorListener ancestorListener = null;

  public GensymMotifFileChooserUI(JFileChooser filechooser) {
    super(filechooser);
  }

  @Override
  protected void installListeners(JFileChooser fc) {
    propertyChangeListener = createPropertyChangeListener(fc);
    if(propertyChangeListener != null) {
      fc.addPropertyChangeListener(propertyChangeListener);
    }
    fc.addPropertyChangeListener(directoryModel);
    
    ancestorListener = new AncestorListener() {
      @Override
      public void ancestorAdded(AncestorEvent e) {
	JButton approveButton = getApproveButton(getFileChooser());
	if(approveButton != null) {
	  approveButton.requestFocus();
	}
      }
      @Override
      public void ancestorRemoved(AncestorEvent e) {
      }
      @Override
      public void ancestorMoved(AncestorEvent e) {
      }
    };
    fc.addAncestorListener(ancestorListener);
    
    
    InputMap inputMap = getInputMap(JComponent.
				    WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);
    SwingUtilities.replaceUIInputMap(fc, JComponent.
				     WHEN_ANCESTOR_OF_FOCUSED_COMPONENT, inputMap);
    ActionMap actionMap = getActionMap();
    SwingUtilities.replaceUIActionMap(fc, actionMap);
  }

  @Override
  protected void uninstallListeners(JFileChooser fc) {
    if(propertyChangeListener != null) {
      fc.removePropertyChangeListener(propertyChangeListener);
    }
    fc.removePropertyChangeListener(directoryModel);
    SwingUtilities.replaceUIInputMap(fc, JComponent.
				     WHEN_ANCESTOR_OF_FOCUSED_COMPONENT, null);
    SwingUtilities.replaceUIActionMap(fc, null);
    fc.removeAncestorListener(ancestorListener);
    ancestorListener = null;
  }

  ActionMap getActionMap() {
    return createActionMap();
  }
  
  ActionMap createActionMap() {
    AbstractAction escAction = new AbstractAction() {
      @Override
      public void actionPerformed(ActionEvent e) {
	getFileChooser().cancelSelection();
      }
      @Override
      public boolean isEnabled(){
	return getFileChooser().isEnabled();
      }
    };
    ActionMap map = new ActionMapUIResource();
    map.put("cancelSelection", escAction);
    return map;
  }

  InputMap getInputMap(int condition) {
    if (condition == JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT) {
      return (InputMap)UIManager.get("FileChooser.ancestorInputMap");
    }
    return null;
  }

    public static ComponentUI createUI(JComponent c)
    {
	return new GensymMotifFileChooserUI((JFileChooser)c);
    }

  @Override
  protected void createModel() {
    directoryModel = new GensymBasicDirectoryModel(getFileChooser());
  }

  @Override
  public BasicDirectoryModel getModel() {
    return directoryModel;
  }
}
