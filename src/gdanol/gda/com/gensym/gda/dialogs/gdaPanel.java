	
package com.gensym.gda.dialogs;


import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Dimension;
import java.awt.Insets;
import java.util.MissingResourceException;
	
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.border.EmptyBorder;

import com.gensym.controls.FieldType;
import com.gensym.util.Symbol;
import com.gensym.message.Resource;

import com.gensym.gda.controls.*;


/**
gdaPanel is used to place controls on dialog.
*/
public class gdaPanel extends JPanel {

	public gdaPanel(gdaDialog d) {
    	super();
		dialog = d;
		attributeEditorFillConstraint=GridBagConstraints.BOTH;
    	setLayout(gridBagLayout);
		setBorder(emptyBorder);
		
	}

	
	/**
	This method places editor on gdaPanel, uses as label localised message from 
	com.gensym.gda.dialogs.blocks.Message where key is lowercased string representation of
	attribute_ parameter and `sets fieldType to editor.
	*/
	public void placeAttributeEditor(AbstractAttributeEditor editor,
						 Symbol attribute_,
					     FieldType fieldType,
						 int gridy) {
		placeAttributeEditor (editor, dialog.localize(attribute_),attribute_,
			fieldType, gridy);			
	}

	/**
	This method places editor on gdaPanel and uses as label localised message from 
	com.gensym.gda.dialogs.blocks.Message where key is lowercased string representation of
	attribute_ parameter.
	*/
	public void placeAttributeEditor(AbstractAttributeEditor editor,
						 Symbol attribute_,
						 int gridy) {
		placeAttributeEditor (editor, dialog.localize(attribute_),attribute_,gridy);			
	}


	/**
	This method sets fieldType to editor and places it on gdaPanel
	using {@link #placeAttributeEditor(AbstractAttributeEditor, String, Symbol, int) 
	placeAttributeEditor(editor, labelString, attribute_, gridy)} 
	*/
	public void placeAttributeEditor(AbstractAttributeEditor editor,
						String labelString,
					     Symbol attribute_,
					     FieldType fieldType,
						 int gridy) {
						 	
		editor.setFieldType(fieldType);
		placeAttributeEditor(editor, labelString, attribute_, gridy);
		
	}	


	/**
	Sets editor as listener for object update events from dialog
	and sets dialog as listener for object change events from editor.
	*/
	public void registerEditor(AbstractAttributeEditor editor) {
	    dialog.addEditor(editor);
    	editor.addObjectChangeListener(dialog);
    	dialog.addObjectUpdateListener(editor);		
	}	
	
	/**
	Main method for placing AbstractAttributeEditor on gdaPanel.
	@param editor Editor to place on gdaPanel.
	@param labelString The text of the label attached to editor. If labelString is null
	no label is created.
	@param attribute_ The editor attribute name
	@param gridy The row number for editor on gdaPanel
	*/
	public void placeAttributeEditor(AbstractAttributeEditor editor,
						String labelString,
					     Symbol attribute_,
						 int gridy) {
    
    if (labelString!=null) {
    	JLabel label = createLabel(labelString, gridy);
    	editor.setLabel(label);
    }
    
   	editor.setAttribute(attribute_);
    registerEditor(editor);
    
    setDefaultConstraints();

    gridBagConstraints.gridx = (labelString!=null ? 1 : gridBagConstraints.RELATIVE);
    gridBagConstraints.gridwidth = (labelString!=null ? 1 : gridBagConstraints.REMAINDER);
    gridBagConstraints.gridy = gridy;
    gridBagConstraints.anchor = GridBagConstraints.WEST;
    gridBagConstraints.weightx = 1.0;
    gridBagConstraints.weighty = 1.0;
    gridBagConstraints.fill = attributeEditorFillConstraint;

    gridBagLayout.setConstraints(editor, gridBagConstraints);

    add(editor);

  }

	public void addPanel(JPanel panel, String labelString, int gridy) {
		JLabel label=null;
		if (labelString!=null) {
			label = createLabel(labelString, gridy);
		}
		setDefaultConstraints();
	    gridBagConstraints.gridy = gridy;
	    gridBagConstraints.fill = attributeEditorFillConstraint;//GridBagConstraints.HORIZONTAL;
    
		if (label == null) {
			gridBagConstraints.weightx = 0.0;
			gridBagConstraints.gridwidth=GridBagConstraints.REMAINDER;
			gridBagConstraints.gridx = 0;
		} else {
			gridBagConstraints.weightx = 1.0;
			gridBagConstraints.gridx = 1;
    	}
	    gridBagLayout.setConstraints(panel, gridBagConstraints);

    	add(panel);
		
}

  protected JLabel createLabel(String labelText, int gridy) {
    JLabel label = new JLabel(labelText);

    setDefaultConstraints();

    gridBagConstraints.gridy = gridy;
    gridBagConstraints.anchor = GridBagConstraints.EAST;
    gridBagConstraints.weightx = 0.0;

    gridBagLayout.setConstraints(label, gridBagConstraints);

    add(label);

    return label;
  }

  protected void setDefaultConstraints() {
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 0;
    gridBagConstraints.gridwidth = 1;
    gridBagConstraints.anchor = GridBagConstraints.CENTER;
    gridBagConstraints.weightx = 0.0;
    gridBagConstraints.fill = GridBagConstraints.NONE;
    gridBagConstraints.weighty = 0.0;
    gridBagConstraints.insets = insets;
    }

	public Dimension getPreferredSize() {
		Dimension d = super.getPreferredSize();
		if (d.width<minimumPanelWidth) d.width=minimumPanelWidth;
		return d;
	}
	
	protected String localize(String text) {
		try {
			return i18n.getString(text);
		} catch (MissingResourceException e) {
			return text;
		}
	}

	public void setMinimumPanelWidth(int i) {minimumPanelWidth=i;}
	
	private static final EmptyBorder emptyBorder = new EmptyBorder(2, 2, 2, 2);

	protected static final Insets insets = new Insets(5, 5, 5, 5);
	protected static final Insets noInsets = new Insets(0, 0, 0, 0);

	public static final FieldType valueFieldType = new FieldType("Value");
	public static final FieldType textFieldType = new FieldType("Text");
	public static final FieldType quantityFieldType = new FieldType("Quantity");
	public static final FieldType symbolFieldType = new LowerCaseSymbolFieldType();
	public static final FieldType integerFieldType = new FieldType("Integer");
	public static final FieldType floatFieldType = new FieldType("Float");
	public static final FieldType statusFieldType = new StatusFieldType();

	protected static final String[] emptyComboBoxStrings = new String[] {};


	protected static final GridBagLayout gridBagLayout = new GridBagLayout();
	protected static final GridBagConstraints gridBagConstraints = new GridBagConstraints();

	protected gdaDialog dialog;

	protected Resource i18n; 
	protected int minimumPanelWidth = 350;
	protected int attributeEditorFillConstraint;
}