package com.gensym.editor.text;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.util.Vector;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.classes.FreeText;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.wksp.WorkspaceView;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import com.gensym.message.Resource;


public class G2FontSizeJComboBox extends JComboBox
  implements PropertyChangeListener, SelectionListener, MDIListener, ActionListener, ItemListener {
  private MDIFrame frame = null;
  private WorkspaceView workspaceView = null;
  private WorkspaceElement[] currentSelection = null;
  private Vector selectedFreeTextItems;
  private static final Symbol SMALL_ = Symbol.intern("SMALL");
  private static final Symbol LARGE_ = Symbol.intern("LARGE");
  private static final Symbol XLARGE_ = Symbol.intern("XLARGE");
  private static final Symbol FONT_SIZE_ = Symbol.intern("FONT-SIZE");
  private static final Symbol X_MAGNIFICATION_ = Symbol.intern("X-MAGNIFICATION");
  private static final Symbol Y_MAGNIFICATION_ = Symbol.intern("Y-MAGNIFICATION");
  private static final Object[] fontSizes = new Object [] {"", "8", "9", "10", "11",
                                     "12", "14", "16", "18", "20", "22", "24",
                                     "26", "28", "30", "32", "34", "36", "48","72"};
  private static Resource longBundle = Resource.getBundle("com/gensym/editor/text/CommandLongResource");
  public G2FontSizeJComboBox(MDIFrame parentFrame) {
    super(fontSizes);
    setToolTipText(longBundle.getString("FontSize"));
    if (parentFrame != null){
      frame = parentFrame;
      frame.getManager().addMDIListener(this);
    }

    addActionListener(this);
    addItemListener(this);
    updateAvailability();
  }

  private void setFreeTextSelection() {
    if (currentSelection == null) return;
    for (int i=0; i<currentSelection.length; i++) {
        Item itm = currentSelection[i].getItem();
        if (itm instanceof FreeText) {
          // discard old vector always make a new one for current active doc
          selectedFreeTextItems = new Vector();
          selectedFreeTextItems.add((FreeText) itm);
        }
    }
  }

  private void updateAvailability(){
    boolean  isFreeText= false;

    if (workspaceView != null)
      if (currentSelection != null) {
        for (int i=0; i<currentSelection.length; i++) {
          Item itm = currentSelection[i].getItem();
          if (itm instanceof FreeText) {
            isFreeText = true;
            break;
          }
        }
        if (isFreeText)
          setEnabled(true);
        else {
          setEnabled(false);
          setSelectedIndex(0);
        }

      } else {
          setEnabled(false);
          setSelectedIndex(0);
      }
    else {
      setEnabled(false);
      setSelectedIndex(0);
    }
  }

  private void setWorkspaceView(WorkspaceView workspaceView) {
    currentSelection = null;
    if (this.workspaceView != null)
      this.workspaceView.removeSelectionListener(this);

    this.workspaceView = workspaceView;
    if (this.workspaceView != null) {
      this.workspaceView.addSelectionListener(this);
      currentSelection = workspaceView.getSelection();
    }

    updateAvailability();
  }

  private int getSelectedFontSize () {
    if (getSelectedIndex() == 0) return 0;
    String selectedSize = (String) getSelectedItem();
    return (new Integer(selectedSize)).intValue();
  }

  private Structure getNewFreeTextFont () {
    Structure textFontStructure = new Structure();
    double x_magnification = 0.0;
    double y_magnification = 0.0;
    int fontSize = getSelectedFontSize();
    if (fontSize == 0) return null;

    switch (fontSize) {
      case 8:
        x_magnification = 0.8;
        y_magnification = 0.8;
        break;
      case 9:
        x_magnification = 0.85;
        y_magnification = 0.85;
        break;
      case 10:
        x_magnification = 0.9;
        y_magnification = 0.9;
        break;
      case 11:
        x_magnification = 0.95;
        y_magnification = 0.95;
        break;
      case 12:
        x_magnification = 1.0;
        y_magnification = 1.0;
        break;
      case 14:
        x_magnification = 1.17;
        y_magnification = 1.17;
        break;
      case 16:
        x_magnification = 1.34;
        y_magnification = 1.34;
        break;
      case 18:
        x_magnification = 1.51;
        y_magnification = 1.51;
        break;
      case 20:
        x_magnification = 1.68;
        y_magnification = 1.68;
        break;
      case 22:
        x_magnification = 1.85;
        y_magnification = 1.85;
        break;
      case 24:
        x_magnification = 2.0;
        y_magnification = 2.0;
        break;
      case 26:
        x_magnification = 2.17;
        y_magnification = 2.17;
        break;
      case 28:
        x_magnification = 2.34;
        y_magnification = 2.34;
        break;
      case 30:
        x_magnification = 2.51;
        y_magnification = 2.51;
        break;
      case 32:
        x_magnification = 2.68;
        y_magnification = 2.68;
        break;
      case 34:
        x_magnification = 2.85;
        y_magnification = 2.85;
        break;
      case 36:
        x_magnification = 3.0;
        y_magnification = 3.0;
        break;
      case 48:
        x_magnification = 3.0;
        y_magnification = 3.0;
        break;
      case 72:
        x_magnification = 6.0;
        y_magnification = 6.0;
        break;
    }
    if (fontSize == 72 || fontSize == 48)
      textFontStructure.setAttributeValue(FONT_SIZE_, LARGE_);
    else
      textFontStructure.setAttributeValue(FONT_SIZE_, SMALL_);
    textFontStructure.setAttributeValue(X_MAGNIFICATION_, new Double(x_magnification));
    textFontStructure.setAttributeValue(Y_MAGNIFICATION_, new Double(y_magnification));

    return  textFontStructure;
  }

  // BEGIN: SelectionListener methods
  @Override
  public void selectionChanged(SelectionEvent event){
    currentSelection = workspaceView.getSelection();
    if ( currentSelection.length == 0)
      setSelectedIndex(0);
    setFreeTextSelection();
    updateAvailability();
  }
  // END: SelectionListener methods

  // BEGIN: MDIListener methods - update workspaceview status and G2fontSizeJComboBox
  // status
  @Override
  public void documentAdded(MDIEvent event) {
    MDIDocument document = (MDIDocument)event.getDocument();
    if (document instanceof WorkspaceDocument) {
      document.addPropertyChangeListener(this);
      WorkspaceDocument wkspDoc = (WorkspaceDocument)document;
      setWorkspaceView(wkspDoc.getWorkspaceView());
    }

  }
  // END: MDIListener methods

  // BEGIN: ActionListener methods - get active doc and its currentselection
  @Override
  public void actionPerformed(ActionEvent e) {
    if (frame == null) return;
    MDIDocument activeDoc = frame.getManager().getActiveDocument();
    if (activeDoc == null) return;
    if (activeDoc instanceof WorkspaceDocument)
      setWorkspaceView(((WorkspaceDocument) activeDoc).getWorkspaceView());
    else
      setWorkspaceView(null);
    setFreeTextSelection();
  }
  // END: ActionListener methods

  // BEGIN: PropertyChangeListener methods - reset workspaceview as active doc and
  // update g2fontsizeJcomboBox status
  @Override
  public void propertyChange(PropertyChangeEvent e) {
    WorkspaceDocument document = (WorkspaceDocument)e.getSource();
    if (e.getPropertyName().equals(WorkspaceDocument.IS_SELECTED_PROPERTY)){
      Boolean selected = (Boolean)e.getNewValue();
      if (selected.booleanValue()) {
	      setWorkspaceView(document.getWorkspaceView());
        setFreeTextSelection();
        setSelectedIndex(0);
      }
    }
    else
      if (e.getPropertyName().equals(WorkspaceDocument.IS_CLOSED_PROPERTY)) {
        document.removePropertyChangeListener(this);
        if (currentSelection.length == 0)
          setWorkspaceView(null);
        else 
          if (frame.getManager().getDocumentCount() == 0)
             setWorkspaceView(null);
          else
             setSelectedIndex(0);
      }

  }
  // END: PropertyChangeListener methods

  // BEGIN: ItemListener - update free text based on selected font size
  @Override
  public void itemStateChanged (ItemEvent e) {
    if ((e.getSource() == this) && (e.getStateChange() == ItemEvent.SELECTED)) {
      if (getSelectedIndex() == 0) return;
      if (selectedFreeTextItems == null)
         setFreeTextSelection();
      Structure textFontStructure = getNewFreeTextFont ();
      if (textFontStructure == null) return;
      if (selectedFreeTextItems.size() > 0) {
        for (int i=0; i < selectedFreeTextItems.size(); i++) {
          FreeText itm = (FreeText) selectedFreeTextItems.get(i);
          /*try {
            itm.setItemTextFont(textFontStructure);
          }
          catch (G2AccessException ex) {
            Trace.exception(ex);
          }*/
        }
      }
    }
  }
  // END: ItemListener
}


