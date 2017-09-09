package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;
import com.gensym.gda.controls.*;

public class gdiChartCapability extends BlocksDialog {
	
	public gdiChartCapability() {}

	public gdiChartCapability(java.awt.Frame frame) {
		super(frame);
				
		chartName=new ComboBoxEditor();
		dpanel.placeAttributeEditor(chartName, CHART_NAME_, dpanel.symbolFieldType, 0);
		
		chartAttribute=new ComboBoxEditor();
		dpanel.placeAttributeEditor(chartAttribute, CHART_ATTRIBUTE_, dpanel.symbolFieldType, 1);
		
		plotMode = new RadioBoxEditor();
		plotMode.setLabels(new StringVector());
		plotMode.setMembers(new StringVector(new String[] {"continuous", "step"}));
		plotMode.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(plotMode, PLOT_MODE_, dpanel.symbolFieldType, 2);
		
		indicatorVisible=CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(indicatorVisible, INDICATOR_VISIBLE_, 3);
		
		indicator=new ComboBoxEditor();
		indicator.setChoices(new StringVector(new String[]{
			"triangle", "column", "square", "rectangle", "x", "cross", "bar"}));
		dpanel.placeAttributeEditor(indicator, INDICATOR_, dpanel.symbolFieldType, 4);
		
		mayCauseChartUpdate=CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(mayCauseChartUpdate, MAY_CAUSE_CHART_UPDATE_, 5);
		
		eraseHistoryWhenReset=CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(eraseHistoryWhenReset, ERASE_HISTORY_WHEN_RESET_, 6);
		
		lineColor = new ColorEditor();
		dpanel.placeAttributeEditor(lineColor, LINE_COLOR_, 7);

		sampleBox=new TypeSizePanel(this, TypeSizePanel.sampleType, false, 1);
		dpanel.addPanel(sampleBox, null, 8);
		
		updateBox=new TypeSizePanel(this, TypeSizePanel.updateType, false, 1);
		dpanel.addPanel(updateBox, null, 9);
		
	}


	protected ComboBoxEditor chartName;
	protected ComboBoxEditor chartAttribute;
	protected RadioBoxEditor plotMode;
	protected CheckBoxEditor indicatorVisible;
	protected ComboBoxEditor indicator;
	protected CheckBoxEditor mayCauseChartUpdate;
	protected CheckBoxEditor eraseHistoryWhenReset;
	protected TypeSizePanel sampleBox;
	protected TypeSizePanel updateBox;
	protected ColorEditor lineColor;

	protected final static Symbol CHART_NAME_= Symbol.intern("CHART-NAME");
	protected final static Symbol CHART_ATTRIBUTE_= Symbol.intern("CHART-ATTRIBUTE");
	protected final static Symbol PLOT_MODE_= Symbol.intern("PLOT-MODE");
	protected final static Symbol INDICATOR_VISIBLE_= Symbol.intern("INDICATOR-VISIBLE");
	protected final static Symbol INDICATOR_= Symbol.intern("INDICATOR");
	protected final static Symbol MAY_CAUSE_CHART_UPDATE_= Symbol.intern("MAY-CAUSE-CHART-UPDATE");
	protected final static Symbol ERASE_HISTORY_WHEN_RESET_= Symbol.intern("ERASE-HISTORY-WHEN-RESET");
	protected final static Symbol LINE_COLOR_= Symbol.intern("LINE-COLOR");

}