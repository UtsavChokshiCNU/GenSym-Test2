
package com.gensym.gda.dialogs.blocks;


import java.awt.event.FocusEvent;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.EmptyBorder;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.controls.AttributeEditor;
import com.gensym.util.Structure;

import com.gensym.gda.controls.*;

/**TypeSizePanel contains three controls:
one is RadioBoxEditor for setting type (points, time and optionally fixed),
second is SpinEditor for setting points, if points is selected, and
third is intervalEditor for setting time, if time is selected.
At the same point of time only SpinEditor or IntervalEditor is visible.
*/
public class TypeSizePanel extends BlocksPanel {

	public TypeSizePanel(BlocksDialog listener) {
    	this(listener, updateType, true, 1);
	}
	
	public TypeSizePanel(BlocksDialog listener, String panelType, 
		boolean hasfixed, int minvalue) {
    	
    	super(listener);
		
		border = new TitledBorder(LineBorder.createBlackLineBorder(),"");
		setBorder(border);
		setMinimumPanelWidth(0);

		type = new RadioBoxEditor();
		type.setLabels(new StringVector());
		//editor for points
		size = new SpinEditor(minvalue, Integer.MAX_VALUE, 1);
		//editor for time
		size2 = new IntervalEditor();
		size.addObjectChangeListener(sizeChangeListener);
		size2.addObjectChangeListener(sizeChangeListener);
		
		setFixed(hasfixed);
		setType(panelType);
	
		placeAttributeEditor(type, type.getAttribute(), symbolFieldType,  0);
		placeAttributeEditor(size2, size2.getAttribute(), integerFieldType, 1);		
		placeAttributeEditor(size, size.getAttribute(), integerFieldType, 1);			

		GridBagConstraints c = gridBagLayout.getConstraints(size);
		int sizeheight = size.getPreferredSize().height;
		int size2height = size2.getPreferredSize().height;
		int top = (int)((size2height-sizeheight)/2);
		int bottom = size2height-sizeheight - top;

		c.insets.top = c.insets.top + top;
		c.insets.bottom = c.insets.bottom + bottom;
		gridBagLayout.setConstraints(size, c);

		size2.setVisible(false);
		
		type.addObjectChangeListener(new ObjectChangeListener() {
			public void objectChanged(ObjectChangeEvent e) {
				updateSizeEditor(e.getChangedObject());
			}
		});
    	dialog.addObjectUpdateListener(new ObjectUpdateListener() {
    		public void objectUpdated(ObjectUpdateEvent e) {
    			updateSizeEditor(e.getUpdatedValue(type.getAttribute()));
    		}
    	});
  	}

	protected void updateSizeEditor (Object typeValue) {
		if (TIME_.equals(typeValue)) {
			size.setVisible(false);
			size2.setVisible(true);
		} else {
			size2.setVisible(false);
			size.setVisible(true);
		}
		
		size.setEnabled(!FIXED_.equals(typeValue));
	}
	
	public void setSizeMinValue(int minvalue) {
		size.getSpinField().setMinValue(minvalue);
	}


	/**
	TypeSizePanel can be one of two types: updateType (by default) and sampleType.
	if type is updateType then TypeSizePanel edit attributes update-type and update-size.
	if type is sampleType then TypeSizePanel edit attributes sample-type and sample-size.
	*/
	public void setType(String paneltype) {
		if (paneltype.equalsIgnoreCase(updateType)) {
			panelType = updateType;
			type.setAttribute(UPDATE_TYPE_);
			size.setAttribute(UPDATE_SIZE_);
			size2.setAttribute(UPDATE_SIZE_);
			border.setTitle(localize(updateType));
		} else if (paneltype.equalsIgnoreCase(sampleType)) {
			panelType=sampleType;
			type.setAttribute(SAMPLE_TYPE_);
			size.setAttribute(SAMPLE_SIZE_);
			size2.setAttribute(SAMPLE_SIZE_);
			border.setTitle(localize(sampleType));
		} //  *** else throw exception !!!
	}

		
	public String getType() {return panelType;}
		
	/**
	Define if the type control (RadioBoxEditor) should contain fixed choice.
	*/
	public void setFixed(boolean hasFixed) {
		this.hasFixed = hasFixed;
		if(hasFixed) {
			type.setMembers(fixed);
			type.setRowsAndColumns(1, 3);
		} else {
			type.setMembers(nofixed);
			type.setRowsAndColumns(1, 2);
		}
	}	

	public void setTypeAttribute(Symbol attribute_) {type.setAttribute(attribute_);}	
	public void setSizeAttribute(Symbol attribute_) {size.setAttribute(attribute_);}	

	public Symbol getSizeAttribute() {return size.getAttribute();}	
	public Symbol getTypeAttribute() {return type.getAttribute();}	

	public boolean hasFixed() {return hasFixed;}
	
	protected RadioBoxEditor type;
	protected SpinEditor size;
	protected IntervalEditor size2;
	protected javax.swing.JLabel label;

	protected final static Symbol UPDATE_TYPE_= Symbol.intern("UPDATE-TYPE");		
    protected final static Symbol UPDATE_SIZE_ = Symbol.intern("UPDATE-SIZE");		
	protected final static Symbol SAMPLE_TYPE_= Symbol.intern("SAMPLE-TYPE");		
    protected final static Symbol SAMPLE_SIZE_ = Symbol.intern("SAMPLE-SIZE");		

	protected final static String Points="points";
	protected final static String Time="time";
	protected final static String Fixed="fixed";
	
	
	public final static String sampleType = "Sample";
	public  final static String updateType = "Update";
		
	protected final static StringVector fixed = new StringVector(
		new String[] {Points, Fixed, Time});
	protected final static StringVector nofixed = new StringVector(
		new String[] {Points, Time});
	
	
	private String panelType;
	private boolean hasFixed;
	private TitledBorder border;
	private final static Symbol TIME_ = Symbol.intern(Time.toUpperCase());	
	private final static Symbol FIXED_ = Symbol.intern(Fixed.toUpperCase());	
	
	
	protected ObjectChangeListener sizeChangeListener = new ObjectChangeListener() {
		public void objectChanged(ObjectChangeEvent e) {
			AttributeEditor source = (AttributeEditor) e.getSource();
			AttributeEditor changed;
			AttributeEditor toUpdate;
			if (source==size) {
				changed = size; toUpdate = size2;
			} else if (source==size2) {
				changed = size2; toUpdate = size;
			} else
				return;
			
			Structure structure = new Structure();
			structure.setAttributeValue(source.getAttribute(),e.getChangedObject());
			ObjectUpdateEvent updateEvent = new ObjectUpdateEvent(changed, structure);
			toUpdate.objectUpdated(updateEvent);
		}
	};
}