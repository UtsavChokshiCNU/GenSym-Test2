
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiLinearScaling extends BlocksDialog{

 public gdiLinearScaling () {}

 public gdiLinearScaling (java.awt.Frame frame) {
    super(frame);

    inputPanel = new BoundPanel(this);
    inputPanel.setBorderTitle(localize("Input"));
    inputUpperBound = new SpinEditor();
    inputLowerBound = new SpinEditor();
    inputPanel.placeAttributeEditor(inputUpperBound, INPUT_UPPER_BOUND_, 0);
    inputPanel.placeAttributeEditor(inputLowerBound, INPUT_LOWER_BOUND_, 1);
    inputPanel.setEditors(inputUpperBound, inputLowerBound);
    dpanel.addPanel(inputPanel, null, 2);

    outputPanel = new BoundPanel(this);
    outputPanel.setBorderTitle(localize("Output"));
    outputUpperBound = new SpinEditor();
    outputLowerBound = new SpinEditor();
    outputPanel.placeAttributeEditor(outputUpperBound, OUTPUT_UPPER_BOUND_, 3);
    outputPanel.placeAttributeEditor(outputLowerBound, OUTPUT_LOWER_BOUND_, 4);
    outputPanel.setEditors(outputUpperBound, outputLowerBound);
    dpanel.addPanel(outputPanel, null, 5);

 }

    protected BoundPanel inputPanel;
    protected SpinEditor inputUpperBound;
    protected SpinEditor inputLowerBound;

    protected BoundPanel outputPanel;
    protected SpinEditor outputUpperBound;
    protected SpinEditor outputLowerBound;

    protected final static Symbol INPUT_UPPER_BOUND_ = Symbol.intern("INPUT-UPPER-BOUND");
    protected final static Symbol INPUT_LOWER_BOUND_ = Symbol.intern("INPUT-LOWER-BOUND");
    protected final static Symbol OUTPUT_UPPER_BOUND_ = Symbol.intern("OUTPUT-UPPER-BOUND");
    protected final static Symbol OUTPUT_LOWER_BOUND_ = Symbol.intern("OUTPUT-LOWER-BOUND");
	
	
	
}