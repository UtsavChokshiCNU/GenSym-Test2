package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiTwoSidedCusum extends gdiSpcRun {
	
	public gdiTwoSidedCusum() {}

	public gdiTwoSidedCusum(java.awt.Frame frame) {
		super(frame);

		slackPanel = new BoundPanel(this);

		upperSlack = new SpinEditor(0, Double.MAX_VALUE, 1);
		slackPanel.placeAttributeEditor(upperSlack, localize("Upper"), UPPER_SLACK_, 0);
		lowerSlack = new SpinEditor(0, Double.MAX_VALUE, 1);
		slackPanel.placeAttributeEditor(lowerSlack, localize("Lower"), LOWER_SLACK_, 1);
		slackPanel.setEditors(upperSlack, lowerSlack);
		slackPanel.setBorderTitle(localize("Slack"));
		dpanel.addPanel(slackPanel, null, 0);

	}
	
	protected BoundPanel slackPanel;
	protected SpinEditor upperSlack;
	protected SpinEditor lowerSlack;

	protected final static Symbol UPPER_SLACK_=Symbol.intern("UPPER-SLACK");
	protected final static Symbol LOWER_SLACK_=Symbol.intern("LOWER-SLACK");


}