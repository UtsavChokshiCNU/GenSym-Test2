package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.net.URL;
import java.util.*;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

/** Parent class for dialogs that support the wait cursor */

public class NolDialog extends JDialog {
	private Component gp;  // the glass pane for this component
	private Container nativeContainer;  // the outer frame
	private Cursor outerCursor;

	public NolDialog (JFrame dw, String title, boolean modal) {
		super(dw, title, modal);
		gp = getGlassPane(); 
		gp.addMouseListener(new MouseAdapter(){});
	}

	public void setWaitCursor(boolean p) {
		if(p) {
			gp.setVisible(true);
			gp.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
			// force immediate change of cursor (workaround for needing to jiggle the mouse)
			outerCursor = nativeContainer.getCursor();
			nativeContainer.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
		} else {
			gp.setVisible(false);
			gp.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
			// force immediate change of cursor (workaround for needing to jiggle the mouse)
			if(outerCursor!=null){
				nativeContainer.setCursor(outerCursor);
			}
		}
	}
	
	@Override
	public void addNotify() {
		super.addNotify();
		Container parent = this;
	    while (! ((parent instanceof Panel) ||
			(parent instanceof ScrollPane) ||
			(parent instanceof Window)))
			parent = parent.getParent();
			//if (debug) System.out.println("nativeContainer="+parent);
	   nativeContainer = parent;
	}
}