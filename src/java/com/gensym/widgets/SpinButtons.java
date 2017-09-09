package com.gensym.widgets;

import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Container;

class SpinButtons extends Container {

  static final long serialVersionUID = 2L;

  SpinButtons(SpinButton upButton, SpinButton downButton,
	      GridBagConstraints buttonConstraints) {
    GridBagLayout gridbag = new GridBagLayout();
    setLayout(gridbag);
      
    gridbag.setConstraints(upButton, buttonConstraints);
    add(upButton);
      
    gridbag.setConstraints(downButton, buttonConstraints);
    add(downButton);
    upButton.setVisible(true);
    downButton.setVisible(true);
  }
}
