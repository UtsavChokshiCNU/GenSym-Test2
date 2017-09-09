package com.gensym.gda.dialogs.blocks;

import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;
import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiObjectHighlighter extends BlocksDialog {
	
	public gdiObjectHighlighter() {}

	public gdiObjectHighlighter(java.awt.Frame frame) {
		super(frame);
				
		target=new ComboBoxEditor();
		dpanel.placeAttributeEditor(target, TARGET_, dpanel.symbolFieldType, 0);

		BlocksPanel panel = new BlocksPanel(this);
		panel.setBorder(new TitledBorder(LineBorder.createBlackLineBorder(),localize("RegionColors")));
		dpanel.addPanel(panel, null, 1);
		
		backgroundHighlightColor=new ColorOrNoneEditor();
		panel.placeAttributeEditor(backgroundHighlightColor, 
			BACKGROUND_HIGHLIGHT_COLOR_, 0);

		outlineHighlightColor=new ColorOrNoneEditor();
		panel.placeAttributeEditor(outlineHighlightColor, 
			OUTLINE_HIGHLIGHT_COLOR_, 1);
		
		statusHighlightColor=new ColorOrNoneEditor();
		panel.placeAttributeEditor(statusHighlightColor, 
			STATUS_HIGHLIGHT_COLOR_, 2);

		alarmHighlightColor=new ColorOrNoneEditor();
		panel.placeAttributeEditor(alarmHighlightColor, 
			ALARM_HIGHLIGHT_COLOR_, 3);
		
	}


	protected ComboBoxEditor target;
	protected ColorOrNoneEditor backgroundHighlightColor;
	protected ColorOrNoneEditor outlineHighlightColor;
	protected ColorOrNoneEditor statusHighlightColor;
	protected ColorOrNoneEditor alarmHighlightColor;

	protected final static Symbol TARGET_= Symbol.intern("TARGET");
	protected final static Symbol BACKGROUND_HIGHLIGHT_COLOR_= Symbol.intern("BACKGROUND-HIGHLIGHT-COLOR");
	protected final static Symbol OUTLINE_HIGHLIGHT_COLOR_= Symbol.intern("OUTLINE-HIGHLIGHT-COLOR");
	protected final static Symbol STATUS_HIGHLIGHT_COLOR_= Symbol.intern("STATUS-HIGHLIGHT-COLOR");
	protected final static Symbol ALARM_HIGHLIGHT_COLOR_= Symbol.intern("ALARM-HIGHLIGHT-COLOR");

}