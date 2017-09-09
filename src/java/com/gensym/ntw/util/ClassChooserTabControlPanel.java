package com.gensym.ntw.util;

import javax.swing.JButton;
import javax.swing.JTabbedPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JRadioButton;
import javax.swing.ButtonGroup;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import com.gensym.uitools.utils.TabbedControlPanel;
import com.gensym.message.Resource;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import java.awt.GridLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import javax.swing.border.CompoundBorder;
import javax.swing.border.TitledBorder;
import javax.swing.border.EmptyBorder;
import java.awt.Insets;

public class ClassChooserTabControlPanel extends TabbedControlPanel
  implements ActionListener, StandardDialogClient {
  private static Resource dlgLabels = Resource.getBundle("com.gensym.ntw.util.ClassChooserTabControlDialogLabels");
  private JButton removeTabButton;
  private JButton insertTabButton;
  private JButton editLabelButton;
  private JRadioButton smallIconRButton, largeIconRButton,
    textAndIcon, textOnly, iconOnly;
  int selectedIndex = 0;
  private JTabbedPane ccTabPane;
  private TwAccess currentConnection;
  private boolean isEditMode;
  Vector iconSizes, buttonStyles;
  private static final int TEXT_AND_ICON = 2, ICON_ONLY = 0, TEXT_ONLY = 1;

  private ClassChooserTabControlPanel (JButton[] buttons,
				       String[] tabNames,
                                       Component[] tabComponents,
				       JRadioButton smallIconRButton,
				       JRadioButton largeIconRButton)
  {
    super(tabComponents, tabNames, buttons,
	  createRadioButtonPanel("Icon Size",
				 new JRadioButton[]{smallIconRButton,
						    largeIconRButton}));
    setUpButtonType();
    this.largeIconRButton = largeIconRButton;
    this.smallIconRButton = smallIconRButton;    
    smallIconRButton.addActionListener(this);
    largeIconRButton.addActionListener(this);    
    removeTabButton = buttons[1];
    insertTabButton = buttons[0];
    editLabelButton = buttons[2];
    removeTabButton.addActionListener(this);
    insertTabButton.addActionListener(this);
    editLabelButton.addActionListener(this);
    removeTabButton.setToolTipText(dlgLabels.getString("removeToolTip"));
    insertTabButton.setToolTipText(dlgLabels.getString("insertToolTip"));
    editLabelButton.setToolTipText(dlgLabels.getString("editToolTip"));

  }

  private void setUpButtonType() {
    textOnly = new JRadioButton("Text Only");
    iconOnly = new JRadioButton("Icon Only");
    textAndIcon = new JRadioButton("Text and Icon");
    textOnly.addActionListener(this);
    iconOnly.addActionListener(this);
    textAndIcon.addActionListener(this);
    Component indicator = statusIndicatorAndButtonsPanel.getComponent(1);
    GridBagConstraints gbc = new GridBagConstraints();
    gbc.gridheight = 1;
    gbc.gridwidth = gbc.REMAINDER;
    gbc.insets = new Insets(2, 0, 0, 0);
    GridBagLayout gbl = (GridBagLayout)statusIndicatorAndButtonsPanel.
      getLayout();
    gbl.setConstraints(indicator, gbc);
    Component buttonStyle =
      createRadioButtonPanel("Button Style", new JRadioButton[]{iconOnly,
								textOnly,
								textAndIcon});
    gbl.setConstraints(buttonStyle, gbc);
    statusIndicatorAndButtonsPanel.add(buttonStyle);
  }

  JRadioButton[] getRadioButtons() {
    return new JRadioButton[]{iconOnly, textOnly, textAndIcon,
			      largeIconRButton, smallIconRButton};
  }
  public JTabbedPane getTabbedPane() {
    return tabbedPane;
  }

  private static Component createRadioButtonPanel(String title,
						  JRadioButton[] buttons) {
    JPanel iconPanel = new JPanel();
    iconPanel.setBorder(new CompoundBorder(new TitledBorder(title),
					   new EmptyBorder(new Insets(2,2,2,2))));
    int buttonCount = buttons.length;    
    iconPanel.setLayout(new GridLayout(buttonCount,1));    
    ButtonGroup group = new ButtonGroup();    
    for (int i=0;i<buttonCount;i++) {
      JRadioButton button = buttons[i];
      group.add(button);
      iconPanel.add(button);
    }
    return iconPanel;
  }
    
  public ClassChooserTabControlPanel (TwAccess connection, String[] tabNames, Component[] tabComponents,
                                        int selectedTab, Vector oldIconSizes, Vector oldButtonStyles) {
    this(new JButton[]{new JButton(dlgLabels.getString("insert")),
                        new JButton(dlgLabels.getString("remove")),
                        new JButton(dlgLabels.getString("nameDisplay"))},
	 tabNames, tabComponents,
	 new JRadioButton("Small(16x16)"),
	 new JRadioButton("Large(32x32)"));
    iconSizes = oldIconSizes;
    buttonStyles = oldButtonStyles;
    if (oldButtonStyles == null
	|| oldButtonStyles.size() != oldIconSizes.size()) {
      buttonStyles = new Vector();
      for (int i=0; i< oldIconSizes.size(); i++)
	buttonStyles.addElement(new Integer(TEXT_AND_ICON));
    }
    currentConnection = connection;
    selectedIndex = selectedTab;
    ccTabPane = tabbedPane;
    ccTabPane.addChangeListener(new TabChangedAdapter());
    ccTabPane.setSelectedIndex(selectedIndex);
    // set icon size because changeevent will not fire initially
    if (((Integer) oldIconSizes.elementAt(selectedIndex)).intValue() == 0)
      smallIconRButton.setSelected(true);
    else
      largeIconRButton.setSelected(true);
    switch (((Integer)oldButtonStyles.elementAt(selectedIndex)).intValue()) {
					case TEXT_AND_ICON:
					  textAndIcon.setSelected(true);
					  break;
					case TEXT_ONLY:
					  textOnly.setSelected(true);
					  break;
					case ICON_ONLY:
					  iconOnly.setSelected(true);
					  break;
  }
    //iconSizes = oldIconSizes;
  }

  public Symbol[] getSelection(){
    return getSelection(selectedIndex);
  }

  public Symbol[] getSelection(int index){
    ClassChooserPanel classChooserPanel = (ClassChooserPanel) ccTabPane.getComponentAt(index);
    return classChooserPanel.getSelection();
  }

  /**
   * @undocumented
   */
  public void addNewTab (String tabName) {
    if (ccTabPane.indexOfTab(tabName) != -1) return;
    // can'nt be null object here must make a non-null object otherwise you will get exception when you make a
    // new ClassChooserPanel. this is why Symbol.intern("") is here.
    ClassChooserPanel ccPanel = new ClassChooserPanel(currentConnection, new Symbol[] {Symbol.intern("")});
    //ClassChooserPanel ccPanel = new ClassChooserPanel(currentConnection, new Symbol[0]);
    ccTabPane.addTab(tabName, ccPanel);
    iconSizes.addElement(new Integer(1));
    buttonStyles.addElement(new Integer(TEXT_AND_ICON));
  }

  public void renameTab(String tabName) {
    int selectedIndex = ccTabPane.getSelectedIndex();
    ccTabPane.setTitleAt(selectedIndex, tabName);
  }

  public void removeTab (int index) {
    ccTabPane.removeTabAt(index);
    iconSizes.removeElementAt(index);
    buttonStyles.removeElementAt(index);
  }

  public Vector getIconSizes() {
    return iconSizes;
  }

  public Vector getButtonStyles() {
    return buttonStyles;
  }
  
  class TabChangedAdapter implements ChangeListener {
    @Override
    public void stateChanged(ChangeEvent e) {
      int index = ((JTabbedPane) e.getSource()).getSelectedIndex();
      if (((Integer) iconSizes.elementAt(index)).intValue() == 0)
        smallIconRButton.setSelected(true);
      else
        largeIconRButton.setSelected(true);
      switch (((Integer) buttonStyles.elementAt(index)).intValue()) {
	case 0: iconOnly.setSelected(true); break;
	case 1: textOnly.setSelected(true); break;
	case 2: textAndIcon.setSelected(true); break;
      }
    }
  }

  @Override
  public void actionPerformed(ActionEvent ae) {
   Object activeObject = ae.getSource();
   if (activeObject instanceof JButton) {
    if ((JButton) activeObject == removeTabButton)
      removeTab(tabbedPane.getSelectedIndex());
    else if (((JButton) activeObject == insertTabButton) || ((JButton) activeObject == editLabelButton)) {
      if ((JButton)activeObject == editLabelButton)
        isEditMode = true;
      else
        isEditMode = false;
      InputDialog labelDlg = new InputDialog(null, dlgLabels.getString
						 ("namingNewAttributeDisp"),
						 true, new String[] 
						 {dlgLabels.getString
					       ("nameLabelForNewAttDisplay")},
						 new String[] {""}, this);


      labelDlg.setVisible(true);
    }
   } else if (activeObject instanceof JRadioButton) {
      // for radio buttons
      int index = ccTabPane.getSelectedIndex();
      if ( (JRadioButton) activeObject == smallIconRButton)
	iconSizes.setElementAt(new Integer (0), index);
      if ( (JRadioButton) activeObject == largeIconRButton)
        iconSizes.setElementAt(new Integer (1), index);
      if ( (JRadioButton) activeObject == iconOnly)
        buttonStyles.setElementAt(new Integer (ICON_ONLY), index);
      if ( (JRadioButton) activeObject == textOnly)
        buttonStyles.setElementAt(new Integer (TEXT_ONLY), index);
      if ( (JRadioButton) activeObject == textAndIcon)
        buttonStyles.setElementAt(new Integer (TEXT_AND_ICON), index);
   }

  }

  @Override
  public void dialogDismissed(StandardDialog labelDlg, int i) {
    if (labelDlg instanceof InputDialog)
      if (i == labelDlg.OK || i == labelDlg.APPLY) {
	String newTabLabel = ((InputDialog)labelDlg).getResults()[0];
        if (isEditMode)
          renameTab(newTabLabel);
        else
          addNewTab(newTabLabel);

      }
  }
}
