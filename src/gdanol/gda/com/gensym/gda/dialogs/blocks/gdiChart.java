package com.gensym.gda.dialogs.blocks;

import javax.swing.JPanel;
import javax.swing.BoxLayout;
import javax.swing.border.TitledBorder;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.beansruntime.StringVector;
import com.gensym.ntw.TwAccess;
import com.gensym.gda.controls.*;

public class gdiChart extends BlocksDialog {
	
	public gdiChart() {}

	public gdiChart(java.awt.Frame frame) {
		super(frame);
				
		chartName=new TextFieldEditor();
		nameFieldType=new ValidG2NameFieldType();
		dpanel.placeAttributeEditor(chartName, CHART_NAME_, nameFieldType, 0);
		
		JPanel attributesPanel = new JPanel();
		attributesPanel.setLayout(new BoxLayout(attributesPanel, BoxLayout.X_AXIS));
		BlocksPanel leftPanel = new BlocksPanel(this);
		leftPanel.setMinimumPanelWidth(subPanelWidth);
		BlocksPanel rightPanel = new BlocksPanel(this);
		rightPanel.setMinimumPanelWidth(subPanelWidth);
		attributesPanel.add(leftPanel);
		attributesPanel.add(rightPanel);
		dpanel.addPanel(attributesPanel, null, 1);

		//left attributes panel
		sampleBox=new TypeSizePanel(this, TypeSizePanel.sampleType, false, 1);
		leftPanel.addPanel(sampleBox, null, 0);
		
		chartStyle= new RadioBoxEditor();
		chartStyle.setLabels(new StringVector(new String[] {"line", "scatter"}));
		chartStyle.setMembers(new StringVector(new String[] {"line-chart-style", "scatter-chart-style"}));
		chartStyle.setRowsAndColumns(1, 2);
		leftPanel.placeAttributeEditor(chartStyle, CHART_STYLE_, leftPanel.symbolFieldType, 2);
		
		autoScale=CheckBoxEditor.createYesNoCheckBox();
		leftPanel.placeAttributeEditor(autoScale, AUTO_SCALE_, 1);
		
		xTicks=new SpinEditor(Integer.MIN_VALUE, Integer.MAX_VALUE, 1);
		leftPanel.placeAttributeEditor(xTicks, X_TICKS_, leftPanel.integerFieldType, 3);
		
		yTicks=new SpinEditor(Integer.MIN_VALUE, Integer.MAX_VALUE, 1);
		leftPanel.placeAttributeEditor(yTicks, Y_TICKS_, leftPanel.integerFieldType, 4);

		//right attributes panel
		updateBox=new TypeSizePanel(this, TypeSizePanel.updateType, false, 1);
		rightPanel.addPanel(updateBox, null, 0);
		
		gridVisible=CheckBoxEditor.createYesNoCheckBox();
		rightPanel.placeAttributeEditor(gridVisible, GRID_VISIBLE_, 1);
		
		textSize=new ComboBoxEditor();
		textSize.setChoices(new StringVector(new String[]{
			"extra-large", "large", "small"}));
		rightPanel.placeAttributeEditor(textSize, TEXT_SIZE_, rightPanel.symbolFieldType, 2);		

		yMax=new SpinEditor();
		rightPanel.placeAttributeEditor(yMax, Y_MAX_, 3);

		yMin=new SpinEditor();
		rightPanel.placeAttributeEditor(yMin, Y_MIN_, 4);
		
		JPanel colorsPanel = new JPanel();
		colorsPanel.setLayout(new BoxLayout(colorsPanel, BoxLayout.X_AXIS));
		colorsPanel.setBorder(new TitledBorder(localize("Colors")));

		BlocksPanel leftColors = new BlocksPanel(this);
		leftColors.setMinimumPanelWidth(subPanelWidth);
		BlocksPanel rightColors = new BlocksPanel(this);
		rightColors.setMinimumPanelWidth(subPanelWidth);
		colorsPanel.add(leftColors);
		colorsPanel.add(rightColors);
		dpanel.addPanel(colorsPanel, null, 2);
		
		chartBackgroundColor = new ColorEditor();
		leftColors.placeAttributeEditor(chartBackgroundColor, CHART_BACKGROUND_COLOR_, 0);

		chartBorderColor = new ColorEditor();
		leftColors.placeAttributeEditor(chartBorderColor, CHART_BORDER_COLOR_, 1);

		xAxisColor = new ColorEditor();
		leftColors.placeAttributeEditor(xAxisColor, X_AXIS_COLOR_, 2);

		chartGridColor = new ColorEditor();
		rightColors.placeAttributeEditor(chartGridColor, CHART_GRID_COLOR_, 0);

		chartTextColor = new ColorEditor();
		rightColors.placeAttributeEditor(chartTextColor, CHART_TEXT_COLOR_, 1);

		yAxisColor = new ColorEditor();
		rightColors.placeAttributeEditor(yAxisColor, Y_AXIS_COLOR_, 2);		
		
	}


	public void setConnection(TwAccess connection) {
		super.setConnection(connection);
		nameFieldType.setConnection(connection);
	}
	
	public void initializeEditors() {
		Structure s = getAttributeDescription(CHART_NAME_);
		nameFieldType.setCurrentName((Symbol)s.getAttributeValue(ATTRIBUTE_VALUE_, null));
	}

	protected ValidG2NameFieldType nameFieldType;
	protected TextFieldEditor chartName;
	protected RadioBoxEditor chartStyle;
	protected CheckBoxEditor gridVisible;
	protected CheckBoxEditor autoScale;
	protected ComboBoxEditor textSize;
	protected SpinEditor xTicks;
	protected SpinEditor yTicks;
	protected SpinEditor yMax;
	protected SpinEditor yMin;
	protected TypeSizePanel sampleBox;
	protected TypeSizePanel updateBox;
	protected ColorEditor chartBackgroundColor;
	protected ColorEditor chartGridColor;
	protected ColorEditor chartBorderColor;
	protected ColorEditor chartTextColor;
	protected ColorEditor xAxisColor;
	protected ColorEditor yAxisColor;

	protected final static Symbol CHART_NAME_= Symbol.intern("CHART-NAME");
	protected final static Symbol CHART_STYLE_= Symbol.intern("STYLE");
	protected final static Symbol GRID_VISIBLE_= Symbol.intern("GRID-VISIBLE");
	protected final static Symbol AUTO_SCALE_= Symbol.intern("AUTO-SCALE");
	protected final static Symbol TEXT_SIZE_= Symbol.intern("TEXT-SIZE");
	protected final static Symbol X_TICKS_= Symbol.intern("X-TICKS");
	protected final static Symbol Y_TICKS_= Symbol.intern("Y-TICKS");
	protected final static Symbol Y_MAX_= Symbol.intern("Y-MAX");
	protected final static Symbol Y_MIN_= Symbol.intern("Y-MIN");
	protected final static Symbol CHART_BACKGROUND_COLOR_= Symbol.intern("CHART-BACKGROUND-COLOR");
	protected final static Symbol CHART_GRID_COLOR_= Symbol.intern("CHART-GRID-COLOR");
	protected final static Symbol CHART_BORDER_COLOR_= Symbol.intern("CHART-BORDER-COLOR");
	protected final static Symbol CHART_TEXT_COLOR_= Symbol.intern("CHART-TEXT-COLOR");
	protected final static Symbol X_AXIS_COLOR_= Symbol.intern("X-AXIS-COLOR");
	protected final static Symbol Y_AXIS_COLOR_= Symbol.intern("Y-AXIS-COLOR");

	protected int subPanelWidth=0;
}