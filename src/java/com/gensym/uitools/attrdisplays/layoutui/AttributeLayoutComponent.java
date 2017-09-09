package com.gensym.uitools.attrdisplays.layoutui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.Vector;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.DefaultListModel;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.InputDialog;     
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.uitools.attrdisplays.layoutmodel.CollectionListener;
import com.gensym.uitools.attrdisplays.layoutmodel.CollectionEvent;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayout;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayoutEditor;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutStructure;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutTableModel;

public class AttributeLayoutComponent extends TabbedControlPanel
implements ActionListener, StandardDialogClient, CollectionListener {

  private static Resource dlgLabels = Trace.getBundle("com.gensym.uitools.attrdisplays.DialogLabels");
  private JButton removeTabButton;
  private JButton insertTabButton;
  private JButton editLabelButton;
  private int tabNo = 0;
  private Vector tabLabels = new Vector();
  protected String newTabLabel;
  protected boolean editFlag = false;
  protected AttributeDisplayLayoutEditor editor;

  private AttributeLayoutComponent (JButton[] buttons,
				   AttributeDisplayLayoutEditor editor)
  {
    super(buttons);
    removeTabButton = buttons[1];
    insertTabButton = buttons[0];
    editLabelButton = buttons[2];
    removeTabButton.addActionListener(this);
    insertTabButton.addActionListener(this);
    editLabelButton.addActionListener(this);
    removeTabButton.setToolTipText("Remove this display");
    insertTabButton.setToolTipText("Add a new display");
    editLabelButton.setToolTipText("Name this display");
    this.editor = editor;
    if (editor.getCurrentAttributeDisplayLayouts().length == 0)
      editor.addAttributeDisplay(null);
    editor.addCollectionListener(this);
  }
  
  public AttributeLayoutComponent (AttributeDisplayLayoutEditor editor)
   throws ComponentConstructionException {
    this(new JButton[]{new JButton(dlgLabels.getString("insert")), 
			 new JButton(dlgLabels.getString("remove")),
			 new JButton(dlgLabels.getString("nameDisplay"))},
	 editor);
    if (editor == null)
      throw new ComponentConstructionException("Null editor given to component");

  }
  
  public void setSelectedIndex(int i) {
    tabbedPane.setSelectedComponent(tabbedPane.getComponentAt(i));
  }

  public void removeCurrentTab() {
    tabLabels.removeElementAt(tabbedPane.getSelectedIndex());
    tabbedPane.removeTabAt(tabbedPane.getSelectedIndex());
    if (tabbedPane.getTabCount() == 0) 
      addTab(editor.createAttributeDisplayLayout());
  }

  public void addTab(AttributeDisplayLayout adl) {
    AttributeDisplayLayoutPanel tabToAdd = createTab(adl);
    String tabLabel = tabToAdd.getLabel();
    tabbedPane.addTab(tabLabel, (JComponent)tabToAdd);
    tabLabels.addElement(tabLabel);
  }

  AttributeDisplayLayoutPanel createTab(AttributeDisplayLayout adl) {
    LayoutTableModel tableModel = editor.createLayoutTableModel(adl);
    DefaultListModel listModel = editor.createListModel(tableModel);

    String tabLabel;

    if (newTabLabel == null || newTabLabel.compareTo("") == 0)
      tabLabel = "display " +(tabNo++);
    else
      tabLabel = newTabLabel;
    newTabLabel = "";
    AttributeDisplayLayoutPanel tabToAdd = 
      new AttributeDisplayLayoutPanel(listModel, tableModel, tabLabel,
				      adl.getGlobalLayout(),
				      editor);
    tabToAdd.addCollectionListener(this);
    return tabToAdd;
  }

  public void insertNewTabAt(int i) {
    Object title = tabLabels.elementAt(i);
    AttributeDisplayLayoutPanel tabToAdd = createTab(editor.createAttributeDisplayLayout());
    tabbedPane.add((JComponent)tabToAdd, i);
    tabLabels.insertElementAt("", i);
    String newtitle = tabToAdd.getLabel();
    setTitleOf(i, newtitle);
    setTitleOf(i+1, title);
  }

  public void setTitleOf(int index, Object title) {
    tabbedPane.setTitleAt(index, title.toString());
    tabLabels.setElementAt(title, index);
  }

  @Override
  public void dialogDismissed(StandardDialog labelDlg, int i) {
    if (labelDlg instanceof InputDialog)
      if (i == labelDlg.OK || i == labelDlg.APPLY) {
	newTabLabel = ((InputDialog)labelDlg).getResults()[0];
	if (editFlag == true && -1 < tabbedPane.getTabCount()) {
	  if (newTabLabel.compareTo("") !=0) {
	    setTitleOf(tabbedPane.getSelectedIndex(), newTabLabel);
	  }
	  editFlag = false;
	  newTabLabel = "";
	} 
      }
  }

  public Object[] getTitles() {
    return tabLabels.toArray();
  }

  public void dispose() {
    AttributeDisplayLayoutPanel panel;

    editor.removeCollectionListener(this);
    for (int i = 0; i<tabbedPane.getTabCount(); i++ ) {
      panel = (AttributeDisplayLayoutPanel)tabbedPane.getComponentAt(i);
      panel.removeCollectionListener(this);
    }
  }

  @Override
  public void actionPerformed(ActionEvent ae) {
      if (ae.getSource() == insertTabButton) 
	editor.insertAttributeDisplayAt(tabbedPane.getSelectedIndex(), null);
      else if (ae.getSource() == removeTabButton) 
	editor.removeAttributeDisplayAt(tabbedPane.getSelectedIndex());
      else if (ae.getSource() == editLabelButton) {
	InputDialog labelDlg = new InputDialog(null, dlgLabels.getString
						 ("namingNewAttributeDisp"),
						 true, new String[] 
						 {dlgLabels.getString
					       ("nameLabelForNewAttDisplay")},
						 new String[] {""}, this);

	editFlag = true;
	labelDlg.setVisible(true);
      }

  }

  public AttributeDisplayLayoutEditor getEditor() {
    return editor;
  }

  @Override
  public void collectionChanged(CollectionEvent collectionEvent){
    Object source = collectionEvent.getSource();

    if (source instanceof AttributeDisplayLayoutPanel) {
      panelEvent((AttributeDisplayLayoutPanel)source);
    } else if (source instanceof 
	       AttributeDisplayLayoutEditor) {
      editorEvent((AttributeDisplayLayoutEditor)source);
    }
  }
 
  private void editorEvent(AttributeDisplayLayoutEditor editor) {
    LayoutTableModel tableModel;
    DefaultListModel listModel;
    int length = editor.getCurrentAttributeDisplayLayouts().length;
    int tabCount = tabbedPane.getTabCount();
    if (length > tabCount) 
      insertNewTabAt(tabbedPane.getSelectedIndex());
    else if (length < tabCount) 
      removeCurrentTab();
    else {
      int index = tabbedPane.getSelectedIndex();
      ((AttributeDisplayLayoutPanel)tabbedPane.getSelectedComponent()).
	resetLists(editor.getListModelAt(index), editor.getTableModelAt(index));
    }
  }

  private void panelEvent(AttributeDisplayLayoutPanel panel) {
    int sourceIndex = tabbedPane.indexOfComponent(panel);
    AttributeDisplayLayout[] adls = editor.getCurrentAttributeDisplayLayouts();
    int edLength = adls.length;
    int tabCount = tabbedPane.getTabCount();
    AttributeDisplayLayout adl;
    if (edLength >= tabCount)
      adl = adls[sourceIndex];
    else adl = null;
    if (adl == null)
      adl = editor.createAttributeDisplayLayout();
    if (edLength > 0) {
      editor.setAttributeDisplayLayoutAt(sourceIndex, panel.getResults(adl));
    } else{ 
      editor.addAttributeDisplay(null);
      editor.setAttributeDisplayLayoutAt(sourceIndex, panel.getResults(adl));
    }
  }
}
