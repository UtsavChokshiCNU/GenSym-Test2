/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 FontPanel.java
 *
 */
package com.gensym.uiutil;

import java.awt.Button;
import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.Label;
import java.awt.List;
import java.awt.Panel;
import java.awt.Rectangle;
import java.awt.TextArea;
import java.awt.TextField;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.beans.PropertyEditor;
import com.gensym.message.Resource;
import com.gensym.core.util.QuickSorter;

/**
 * FontPanel create a panel containing components that make up the editor for font
 * selection. This panel is used by the Component Editor's Property Editors and by
 * FontDialog.
 */

public class FontPanel extends Panel implements PropertyEditor
{
  private static Resource i18n = 
		Resource.getBundle("com.gensym.resources.FontEditorLabels");
  private Font currentFont = null;
  private Toolkit toolkit;

  private TextArea previewArea;

  private List nameList;
  private List sizeList;
  private List styleList;

  private TextField nameField;
  private TextField sizeField;
  private TextField styleField;

  private String fonts[];
  private String styleNames[] = {i18n.getString("Plain"),
				 i18n.getString("Italic"),
				 i18n.getString("Bold"),
				 i18n.getString("BoldItalic")};
  private int styles[] = {Font.PLAIN, Font.ITALIC, Font.BOLD, Font.BOLD + Font.ITALIC};
  private int pointSizes[] = {3, 5, 8, 10, 12, 14, 18, 24, 36, 48};
  private PropertyChangeSupport support = new PropertyChangeSupport(this);

  private boolean previewTextStatic = false;

  public static final int NO_BUTTONS = 0;
  public static final int OK = 1;
  public static final int APPLY = 10;
  public static final int CANCEL = 100;
  public static final int DISMISS = 1000;

  /**
   * Constructs a font panel with three lists for the font name, style and
   * size, and a preview area that displays sample text in the selected values.
   */
  public FontPanel(){
    // This constructor is used by the BeanSheet, passing APPLY on to
    // addButtonsToFontPanel() is a hack for now. Ideally BeanSheet could
    // use the 2nd constructor and we can delete this one.

    //Thread.dumpStack ();
    GridBagLayout gridBagLayout = new GridBagLayout();
    GridBagConstraints gridBagConstraints = new GridBagConstraints();
    setLayout(gridBagLayout);

    createFontPanel(gridBagLayout, gridBagConstraints);

    addButtonsToFontPanel(APPLY);
  }

  public FontPanel(int buttonFlag) {
    GridBagLayout gridBagLayout = new GridBagLayout();
    GridBagConstraints gridBagConstraints = new GridBagConstraints();
    setLayout(gridBagLayout);

    createFontPanel(gridBagLayout, gridBagConstraints);

    if (buttonFlag > 0)
      addButtonsToFontPanel(buttonFlag);
  }

  // BEGIN: createFontPanel
  private void createFontPanel(GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints) {
    setBackground(Color.lightGray);
    toolkit = Toolkit.getDefaultToolkit();
    fonts = toolkit.getFontList();
    QuickSorter qs = new QuickSorter () {
      @Override
      public boolean lessThan(Object a, Object b) {
	return a.toString().toLowerCase().
	  compareTo(b.toString().toLowerCase()) < 0;
      }
    };
    qs.quickSortInPlace (fonts);
    
    gridBagConstraints.weightx = 0.5;
    gridBagConstraints.weighty = 0.0;
    gridBagConstraints.anchor = 17;
    gridBagConstraints.fill = 2;
    gridBagConstraints.insets = new Insets(5, 5, 0, 5);
    
    Label nameLabel = makeLabel(i18n.getString("FontLabel"), 0, gridBagLayout, gridBagConstraints);

    gridBagConstraints.weightx = 0.4;
    Label styleLabel = makeLabel(i18n.getString("FontStyle"), 0, gridBagLayout, gridBagConstraints);

    gridBagConstraints.weightx = 0.1;
    gridBagConstraints.gridwidth = 0;
    Label sizeLabel = makeLabel(i18n.getString("Size"), 0, gridBagLayout, gridBagConstraints);
    
    gridBagConstraints.weightx = 0.5;
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = -1;
    gridBagConstraints.gridwidth = 1;
    gridBagConstraints.fill = 2;
    gridBagConstraints.insets = new Insets(0, 5, 0, 5);
  
    nameField = makeTextField(false, Color.white, gridBagLayout, gridBagConstraints);
    
    gridBagConstraints.weightx = 0.4;
    gridBagConstraints.gridwidth = -1;
    gridBagConstraints.gridx = -1;
    
    styleField = makeTextField(false, Color.white, gridBagLayout, gridBagConstraints);

    gridBagConstraints.weightx = 0.1;
    gridBagConstraints.gridwidth = 0;
    
    sizeField = makeTextField(false, Color.white, gridBagLayout, gridBagConstraints);
    
    gridBagConstraints.weightx = 0.5;
    gridBagConstraints.weighty = 1.0;
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridwidth = 1;
    gridBagConstraints.insets = new Insets(0, 5, 5, 5);
    gridBagConstraints.fill = 1;

    nameList = makeList(6, false, gridBagLayout, gridBagConstraints);
    for (int i = 0; i < fonts.length; i++)
      nameList.addItem(fonts[i]);

    nameList.addItemListener(new ItemListener() {
      @Override
      public void itemStateChanged(ItemEvent e) {
	nameField.setText(nameList.getSelectedItem());
	updatePreview();
	}
    });
    
    gridBagConstraints.weightx = 0.4;
    gridBagConstraints.gridx = -1;
    
    styleList = makeList(6, false, gridBagLayout, gridBagConstraints);
    for (int j = 0; j < styleNames.length; j++)
      styleList.addItem(styleNames[j]);

    styleList.addItemListener(new ItemListener() {
      @Override
      public void itemStateChanged(ItemEvent e) {
	styleField.setText(styleList.getSelectedItem());
	updatePreview();
      }
    });
      
    gridBagConstraints.weightx = 0.1;
    gridBagConstraints.gridwidth = 0;
    
    sizeList = makeList(6, false, gridBagLayout, gridBagConstraints);
    for (int k = 0; k < pointSizes.length; k++)
      sizeList.addItem(String.valueOf(pointSizes[k]));

    sizeList.addItemListener(new ItemListener() {
      @Override
      public void itemStateChanged(ItemEvent e) {
	sizeField.setText(sizeList.getSelectedItem());
	updatePreview();
      }
    });
		
    gridBagConstraints.weightx = 0.0;
    gridBagConstraints.weighty = 0.0;
    //gridBagConstraints.anchor = 10;
    gridBagConstraints.anchor = GridBagConstraints.WEST;
    gridBagConstraints.gridy = -1;
    gridBagConstraints.fill = 0;
    gridBagConstraints.insets = new Insets(10, 5, 5, 5);
    gridBagConstraints.gridwidth = 0;
    
    makeLabel(i18n.getString("Preview"), 0, gridBagLayout, gridBagConstraints);
    
    //previewArea = new PreviewArea(); //TextArea("", 4, 45, 3);
    previewArea = new TextArea("");
    previewArea.setEditable(false);
    previewArea.setBackground(Color.white);

    gridBagConstraints.gridx = 0;
    gridBagConstraints.anchor = GridBagConstraints.WEST;
    gridBagConstraints.gridy = -1;
    gridBagConstraints.fill = GridBagConstraints.BOTH;
    gridBagConstraints.insets = new Insets(0, 5, 5, 5);
    gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
    gridBagLayout.setConstraints(previewArea, gridBagConstraints);
    
    add(previewArea);
  }

  // BEGIN: createFontPanel
  private void createFontPanelSDM(GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints) {
    // sdm: I'm still working on this
    setBackground(Color.lightGray);
    toolkit = Toolkit.getDefaultToolkit();
    fonts = toolkit.getFontList();
    QuickSorter qs = new QuickSorter () {
      @Override
      public boolean lessThan(Object a, Object b) {
	return a.toString().toLowerCase().
	  compareTo(b.toString().toLowerCase()) < 0;
      }
    };
    qs.quickSortInPlace (fonts);

    /*
    gridBagConstraints.weightx = 0.5;
    gridBagConstraints.weighty = 0.0;
    gridBagConstraints.anchor = 17;
    */
    gridBagConstraints.insets = new Insets(5, 5, 0, 5);
    //gridBagConstraints.fill = GridBagConstraints.VERTICAL;
    gridBagConstraints.anchor = GridBagConstraints.WEST;
    gridBagConstraints.gridwidth = GridBagConstraints.RELATIVE;
    Label nameLabel = makeLabel(i18n.getString("FontLabel"), 0, gridBagLayout, gridBagConstraints);

    //gridBagConstraints.weightx = 0.4;
    Label styleLabel = makeLabel(i18n.getString("FontStyle"), 0, gridBagLayout, gridBagConstraints);

    //gridBagConstraints.weightx = 0.1;
    //gridBagConstraints.gridwidth = 0;
    gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
    Label sizeLabel = makeLabel(i18n.getString("Size"), 0, gridBagLayout, gridBagConstraints);

    //gridBagConstraints.weightx = 0.5;
    //gridBagConstraints.gridx = 0;
    //gridBagConstraints.gridy = -1;
    //gridBagConstraints.gridwidth = 1;
    //gridBagConstraints.fill = 2;

    gridBagConstraints.insets = new Insets(0, 5, 0, 5);
    gridBagConstraints.fill = GridBagConstraints.BOTH;
    gridBagConstraints.gridwidth = GridBagConstraints.RELATIVE;
    nameField = makeTextField(false, Color.white, gridBagLayout, gridBagConstraints);
    
     //gridBagConstraints.weightx = 0.4;
     //gridBagConstraints.gridwidth = -1;
     //gridBagConstraints.gridx = -1;
    
    styleField = makeTextField(false, Color.white, gridBagLayout, gridBagConstraints);

    //gridBagConstraints.weightx = 0.1;
    //gridBagConstraints.gridwidth = 0;
    
    gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
    sizeField = makeTextField(false, Color.white, gridBagLayout, gridBagConstraints);

    /*
    gridBagConstraints.weightx = 0.5;
    gridBagConstraints.weighty = 1.0;
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridwidth = 1;
    gridBagConstraints.insets = new Insets(0, 5, 5, 5);
    gridBagConstraints.fill = 1;
    */
    gridBagConstraints.gridwidth = GridBagConstraints.RELATIVE;

    nameList = makeList(6, false, gridBagLayout, gridBagConstraints);
    for (int i = 0; i < fonts.length; i++)
      nameList.addItem(fonts[i]);

    nameList.addItemListener(new ItemListener() {
      @Override
      public void itemStateChanged(ItemEvent e) {
	nameField.setText(nameList.getSelectedItem());
	updatePreview();
	}
    });
    
    //gridBagConstraints.weightx = 0.4;
    //gridBagConstraints.gridx = -1;
    
    styleList = makeList(6, false, gridBagLayout, gridBagConstraints);
    for (int j = 0; j < styleNames.length; j++)
      styleList.addItem(styleNames[j]);

    styleList.addItemListener(new ItemListener() {
      @Override
      public void itemStateChanged(ItemEvent e) {
	styleField.setText(styleList.getSelectedItem());
	updatePreview();
      }
    });  
    
    //gridBagConstraints.weightx = 0.1;
    //gridBagConstraints.gridwidth = 0;
    gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
    
    sizeList = makeList(6, false, gridBagLayout, gridBagConstraints);
    for (int k = 0; k < pointSizes.length; k++)
      sizeList.addItem(String.valueOf(pointSizes[k]));

    sizeList.addItemListener(new ItemListener() {
      @Override
      public void itemStateChanged(ItemEvent e) {
	sizeField.setText(sizeList.getSelectedItem());
	updatePreview();
      }
    });

    //

    /*
    gridBagConstraints.weightx = 0.0;
    gridBagConstraints.weighty = 0.0;
    //gridBagConstraints.anchor = 10;
    gridBagConstraints.anchor = GridBagConstraints.WEST;
    gridBagConstraints.gridy = -1;
    gridBagConstraints.fill = 0;
    gridBagConstraints.insets = new Insets(10, 5, 5, 5);
    gridBagConstraints.gridwidth = 0;
    */
    
    //makeLabel(i18n.getString("Preview"), 0, gridBagLayout, gridBagConstraints);
   
    previewArea = new TextArea("");
    //previewArea.setEditable(false);
    //previewArea.setBackground(Color.white);

    /*
    gridBagConstraints.gridx = 0;
    gridBagConstraints.anchor = GridBagConstraints.WEST;
    gridBagConstraints.gridy = -1;
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = -1;
    gridBagConstraints.insets = new Insets(0, 5, 5, 5);
    */
    //gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
    //gridBagConstraints.fill = GridBagConstraints.BOTH;

    //gridBagLayout.setConstraints(previewArea, gridBagConstraints);
    //add(previewArea);
  }

  // BEGIN: addButtonsToFontPanel
  private void addButtonsToFontPanel(int buttonFlag){
    boolean addOK = false;
    boolean addApply = false;
    boolean addCancel = false;
    boolean addDismiss = false;

    if (buttonFlag >= DISMISS){
      addDismiss = true;
      buttonFlag -= DISMISS;
      }

    if (buttonFlag >= CANCEL){
      addCancel = true;
      buttonFlag -= CANCEL;
    }

    if (buttonFlag >= APPLY){
      addApply = true;
      buttonFlag -= APPLY;
    }

    if (buttonFlag >= OK){
      addOK = true;
      buttonFlag -= OK;
    }

    GridBagConstraints gbCon = new GridBagConstraints();
    GridBagLayout gbLay = new GridBagLayout();

    gbCon.insets = new Insets (5, 5, 5, 5);
    gbCon.gridwidth = GridBagConstraints.RELATIVE;
    gbCon.fill = GridBagConstraints.HORIZONTAL;
    gbCon.anchor = GridBagConstraints.EAST;

    //gbCon.gridwidth = GridBagConstraints.BOTH;
    
    if (addOK){
      Button okButton = new Button(i18n.getString("DialogOK"));
      okButton.addActionListener(new ActionListener() {
	@Override
	public void actionPerformed(ActionEvent e) {
	  support.firePropertyChange("", null, null);
	  // need to do something to shutdown the "dialog" containing this panel
	}
      });

      gbLay.setConstraints(okButton, gbCon);
      add(okButton);
    }

    if (addApply){
      Button applyButton = new Button(i18n.getString("DialogApply"));
      applyButton.addActionListener(new ActionListener() {
	@Override
	public void actionPerformed(ActionEvent e) {
	  support.firePropertyChange("", null, null);
	}
      });

      gbLay.setConstraints(applyButton, gbCon);
      add(applyButton); 
    }
  
    if (addCancel){
      Button cancelButton = new Button(i18n.getString("DialogCancel"));
      cancelButton.addActionListener(new ActionListener() {
	@Override
	public void actionPerformed(ActionEvent e) {
	  // need to do something to shutdown "dialog" containing panel
	}
      });

      gbLay.setConstraints(cancelButton, gbCon);
      add(cancelButton); 
    }

    if (addDismiss){
      Button dismissButton = new Button(i18n.getString("DialogDismiss"));
      dismissButton.addActionListener(new ActionListener() {
	@Override
	public void actionPerformed(ActionEvent e) {
	  // need to do something to shutdown "dialog" containing panel
	}
      });

      gbLay.setConstraints(dismissButton, gbCon);
      add(dismissButton); 
    }
  }
  // END: addButtonsToFontPanel

  // BEGIN: GridBag convenience methods
  private Label makeLabel(String string, int i, GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints){
    Label label = new Label(string, i);
    gridBagLayout.setConstraints(label, gridBagConstraints);
    add(label);
    return label;
  }

  private TextField makeTextField(boolean flag, Color color, GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints){
    TextField textField = new TextField();
    textField.setEditable(flag);
    textField.setBackground(color);
    gridBagLayout.setConstraints(textField, gridBagConstraints);
    add(textField);
    return textField;
  }

  private List makeList(int i, boolean flag, GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints){
    List list = new List(i,flag);
    gridBagLayout.setConstraints(list, gridBagConstraints);
    add(list);
    return list;
  }
  // END: GridBag convenience methods

  @Override
  public void addPropertyChangeListener(PropertyChangeListener propertyChangeListener){
    support.addPropertyChangeListener(propertyChangeListener);
  }

  @Override
  public void removePropertyChangeListener(PropertyChangeListener propertyChangeListener){
    support.removePropertyChangeListener(propertyChangeListener);
  }

  @Override
  public String getAsText(){
    return null;
  }

  @Override
  public Component getCustomEditor(){
    return this;
  }

  @Override
  public String getJavaInitializationString(){
    return currentFont.getFamily() + "\", " + currentFont.getStyle() + ", " + currentFont.getSize() + ")";
  }

  @Override
  public String[] getTags(){
    return null;
  }

  /** 
   * Get the current font
   * @returns the Font that is currently selected.
   */
  @Override
  public Object getValue(){
    return currentFont;
  }

  @Override
  public boolean isPaintable(){
    return true;
  }

  /**
   * Paints the rectangle of the properties page
   */
  @Override
  public void paintValue(Graphics graphics, Rectangle rectangle){
    Font tfont = graphics.getFont();
    graphics.setFont(currentFont);
    FontMetrics fontMetrics = graphics.getFontMetrics();
    int i = (rectangle.height - fontMetrics.getAscent()) / 2;
    graphics.drawString(currentFont.getName(), 0, rectangle.height - i);
    graphics.setFont(tfont);
  }

  @Override
  public void setAsText(String string) throws IllegalArgumentException {
    throw new IllegalArgumentException(string);
  }

  /**
   * Set the font
   * @param object The font to be set.
   */
  @Override
  public void setValue(Object object){
    currentFont = (Font)object;
    changeFont(currentFont);
  }

  @Override
  public boolean supportsCustomEditor(){
    return true;
  }

  private void changeFont(Font newFont){
    //System.out.println("changeFont: " + newFont);

    if (newFont == null)
      return;

    String name = newFont.getName();
    int size = newFont.getSize();
    int style = newFont.getStyle();

    currentFont = newFont;

    //System.out.println("currentFont now is: " + currentFont);

    nameField.setText(name);
    styleField.setText(styleNames[style]);
    sizeField.setText(String.valueOf(size));

    int k = 0;
    for (int j = 0; j < nameList.getItemCount(); j++){
      if (name.equals(fonts[j]))
	k = j;
    }
    nameList.select(k);

    styleList.select(style);

    k = 0;
    for (int j = 0; j < pointSizes.length; j++){
      if (size == pointSizes[j])
	k = j;
    }
    sizeList.select(k);
    support.firePropertyChange("", null, null);
    previewArea.setFont(newFont);

    if ((nameList.getSelectedItem() != null) && (previewTextStatic == false))
      previewArea.setText(nameList.getSelectedItem());
  }

  private void updatePreview(){
    //System.out.println("running updatePreview");

    if ((nameList.getSelectedItem() != null) &&
	(styleList.getSelectedIndex() > -1) &&
	(sizeList.getSelectedIndex() > -1)){
      Font tfont = new Font(nameList.getSelectedItem(), 
			    styles[styleList.getSelectedIndex()], 
			    pointSizes[sizeList.getSelectedIndex()]);

      previewArea.setFont(tfont);

      //System.out.println("setting currentFont to: " + tfont);
      currentFont = tfont;

      if (previewTextStatic == false)
	previewArea.setText(nameList.getSelectedItem());
    } 
  }

  /**
   * Update preview area with the specified text
   * @param text A String containing the text to update the preview area with.
   */
  public void setPreviewText(String text){
    previewArea.setText(text);
  }

  /**
   * Set a flag indicating whether or not the text in the preview area should be
   * static
   */
  public void previewTextStatic(boolean flag){
    previewTextStatic = flag;
  }

  /**
   * Get the preview area
   * @returns the TextArea that is used as the font preview area
   */
  public TextArea getPreviewArea(){
    return previewArea;
  }

  /**
   * Get the font 
   * @returns the Font that is currently selected.
   **/
  public Font getSelectedFont(){
    //System.out.println("FontPanel.getSelectedFont => " + currentFont);
    return currentFont;
  }

  /**
   * Set the current font  
   * @param newfont The Font to be set.
   **/
  public void setSelectedFont(Font newFont){
    changeFont(newFont);
  }

  /** 
   * Set the current font 
   * @param name  The name of the font.
   * @param style The style of the font.
   * @param size  The size of the font.
   **/
  public void setSelectedFont(String name, int style, int size){
    Font tfont = new Font(name, style, size);
    changeFont(tfont);
  } 
}

