
package com.gensym.gda.controls;

import javax.swing.border.LineBorder;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;

import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.editor.color.*;
import com.gensym.dlg.*;

/**
*/
public class ThreeColorEditor extends ColorEditor {

    public ThreeColorEditor() {
		colorfield.setText("TEXT");
		colorDialog = new G2ColorRegionsDialog(null, "choose a color", true, new ColorDialogClient());
	}

	public void objectUpdated(ObjectUpdateEvent event) {		
		Structure values = (Structure) event.getUpdatedObject();
		try {
			Structure regions = new Structure();

			Symbol color = (Symbol) values.getAttributeValue(backgroundAttribute);
			colorfield.setBackground(G2ColorMap.get(color));
			regions.setAttributeValue(BACKGROUND_AREA_, color);

			color = (Symbol) values.getAttributeValue(borderAttribute);
			colorfield.setBorder(new LineBorder(G2ColorMap.get(color), borderWidth));
			regions.setAttributeValue(BORDER_AREA_, color);
			
			color = (Symbol) values.getAttributeValue(textAttribute);
			colorfield.setDisabledTextColor(G2ColorMap.get(color));			
			regions.setAttributeValue(TEXT_AREA_, color);
			
			((G2ColorRegionsDialog)colorDialog).setRegions(regions);
			colorDialog.pack();
			if(getDisableIfNotUpdated()) setEnabled(true);
		} catch (NoSuchAttributeException e) {
			if(getDisableIfNotUpdated()) setEnabled(false);
		}
	}

	
	protected void fireChangeDialogColors() {
		Structure regions = ((G2ColorRegionsDialog)colorDialog).getRegions();
		Symbol color = (Symbol) regions.getAttributeValue(BACKGROUND_AREA_, null);
		setAttribute(backgroundAttribute);
		colorfield.setBackground(G2ColorMap.get(color));
		fireObjectChange(color);

		color = (Symbol) regions.getAttributeValue(BORDER_AREA_, null);
		setAttribute(borderAttribute);
		colorfield.setBorder(new LineBorder(G2ColorMap.get(color), borderWidth));
		fireObjectChange(color);

		color = (Symbol) regions.getAttributeValue(TEXT_AREA_, null);
		setAttribute(textAttribute);
		colorfield.setDisabledTextColor(G2ColorMap.get(color));			
		fireObjectChange(color);
	}
	
	public void setBackgroundAttribute(Symbol attribute_) {backgroundAttribute=attribute_;}
	public void setBorderAttribute(Symbol attribute_) {borderAttribute=attribute_;}
	public void setTextAttribute(Symbol attribute_) {textAttribute=attribute_;}
	
	public Symbol getBackgroundAttibute() {return backgroundAttribute;}
	public Symbol getBorderAttibute() {return borderAttribute;}
	public Symbol getTextAttibute() {return textAttribute;}
			
	protected Symbol backgroundAttribute;
	protected Symbol textAttribute;
	protected Symbol borderAttribute;
	
	protected static final Symbol BORDER_AREA_=Symbol.intern("BORDER-AREA");
	protected static final Symbol BACKGROUND_AREA_=Symbol.intern("BACKGROUND-AREA");
	protected static final Symbol TEXT_AREA_=Symbol.intern("TEXT-AREA");
	
}