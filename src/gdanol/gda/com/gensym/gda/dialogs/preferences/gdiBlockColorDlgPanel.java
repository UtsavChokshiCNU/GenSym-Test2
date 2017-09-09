package com.gensym.gda.dialogs.preferences;

import javax.swing.BoxLayout;
import javax.swing.border.TitledBorder;
import javax.swing.JPanel;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiBlockColorDlgPanel extends PreferencesPanel {
	
	public gdiBlockColorDlgPanel(PreferencesDialog dialog) {
		super(dialog);

		settingClass=Symbol.intern("GDL-BLOCK-AND-PATH-COLOR-SETTINGS");
		
		JPanel panel = new JPanel();
		panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
		
		leftPanel=new PreferencesPanel(dialog);
		leftPanel.setBorder(new TitledBorder("Block Colors"));
		leftPanel.setMinimumPanelWidth(0);
		rightPanel=new PreferencesPanel(dialog);
		rightPanel.setMinimumPanelWidth(0);
		rightPanel.setBorder(new TitledBorder("Path Colors"));
		
		panel.add(leftPanel);
		panel.add(rightPanel);
		addPanel(panel, null, 0);

		idle = new ColorEditor();
		leftPanel.placeAttributeEditor(idle, BLOCK_IDLE_COLOR_, 0);
		running = new ColorEditor();
		leftPanel.placeAttributeEditor(running, BLOCK_RUNNING_COLOR_, 1);
		disabled = new ColorEditor();
		leftPanel.placeAttributeEditor(disabled, BLOCK_DISABLED_COLOR_, 2);
		error = new ColorEditor();
		leftPanel.placeAttributeEditor(error, BLOCK_ERROR_COLOR_, 3);
		alarm = new ColorEditor();
		leftPanel.placeAttributeEditor(alarm, BLOCK_ALARM_COLOR_, 4);
		
		pathNoValue = new ColorEditor();
		rightPanel.placeAttributeEditor(pathNoValue , PATH_NO_VALUE_COLOR_, 0);
		pathTrue = new ColorEditor();
		rightPanel.placeAttributeEditor(pathTrue, PATH_TRUE_COLOR_, 1);
		pathFalse= new ColorEditor();
		rightPanel.placeAttributeEditor(pathFalse, PATH_FALSE_COLOR_, 2);
		pathUnknown= new ColorEditor();
		rightPanel.placeAttributeEditor(pathUnknown, PATH_UNKNOWN_COLOR_, 3);
		pathHighlight = new ColorEditor();
		rightPanel.placeAttributeEditor(pathHighlight, PATH_HIGHLIGHT_COLOR_, 4);
		
		
		sseHeaderColors = new ThreeColorEditor();
		sseHeaderColors.setBackgroundAttribute(SSE_HEADER_BACKGROUND_COLOR_);
		sseHeaderColors.setBorderAttribute(SSE_HEADER_BORDER_COLOR_);
		sseHeaderColors.setTextAttribute(SSE_HEADER_TEXT_COLOR_);
		placeAttributeEditor(sseHeaderColors, localize("SseHeaderColorsLabel"), 
			SSE_HEADER_BACKGROUND_COLOR_, 1);
		
	}

	protected PreferencesPanel leftPanel;
	protected PreferencesPanel rightPanel;

	protected ThreeColorEditor sseHeaderColors;
	protected ColorEditor idle;
	protected ColorEditor running;
	protected ColorEditor disabled;
	protected ColorEditor error;
	protected ColorEditor alarm;
	protected ColorEditor pathNoValue;
	protected ColorEditor pathTrue;
	protected ColorEditor pathFalse;
	protected ColorEditor pathUnknown;
	protected ColorEditor pathHighlight;

	
	protected final static Symbol BLOCK_IDLE_COLOR_= Symbol.intern("BLOCK-IDLE-COLOR");
	protected final static Symbol BLOCK_RUNNING_COLOR_= Symbol.intern("BLOCK-RUNNING-COLOR");
	protected final static Symbol BLOCK_DISABLED_COLOR_= Symbol.intern("BLOCK-DISABLED-COLOR");
	protected final static Symbol BLOCK_ERROR_COLOR_= Symbol.intern("BLOCK-ERROR-COLOR");
	protected final static Symbol BLOCK_ALARM_COLOR_= Symbol.intern("BLOCK-ALARM-COLOR");
	protected final static Symbol PATH_NO_VALUE_COLOR_= Symbol.intern("PATH-NO-VALUE-COLOR");
	protected final static Symbol PATH_TRUE_COLOR_= Symbol.intern("PATH-TRUE-COLOR");
	protected final static Symbol PATH_FALSE_COLOR_= Symbol.intern("PATH-FALSE-COLOR");
	protected final static Symbol PATH_UNKNOWN_COLOR_= Symbol.intern("PATH-UNKNOWN-COLOR");
	protected final static Symbol PATH_HIGHLIGHT_COLOR_= Symbol.intern("PATH-HIGHLIGHT-COLOR");
	
	
	protected final static Symbol SSE_HEADER_BACKGROUND_COLOR_= Symbol.intern("SSE-HEADER-BACKGROUND-COLOR");
	protected final static Symbol SSE_HEADER_BORDER_COLOR_= Symbol.intern("SSE-HEADER-BORDER-COLOR");
	protected final static Symbol SSE_HEADER_TEXT_COLOR_= Symbol.intern("SSE-HEADER-TEXT-COLOR");

}