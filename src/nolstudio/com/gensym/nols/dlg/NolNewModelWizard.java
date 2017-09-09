package com.gensym.nols.dlg;

import java.util.*;
import com.gensym.math.matrix.*;
import javax.swing.*;

public interface NolNewModelWizard {
	public void receiveRatingResults(Vector inVars, Vector inputDelays, Vector outVars, Vector ratings);
  	public JFrame getFrame();
}