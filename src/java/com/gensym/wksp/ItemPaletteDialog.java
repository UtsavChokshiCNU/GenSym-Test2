package com.gensym.wksp;

import java.awt.Dimension;
import java.util.Vector;
import javax.swing.JTabbedPane;

import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.QuestionDialog;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.ui.ObjectCreator;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;

class ItemPaletteDialog extends GenericPaletteDialog {

  private PalettePane component;
  static final Resource i18n = Resource.getBundle ("com/gensym/wksp/UiLabels");
  static final int defaultIconWidth = 32, defaultIconHeight = 32;
  
  public ItemPaletteDialog (TwConnection cxn) {
    super (null,
	   i18n.format ("itemPaletteTitle", cxn.toShortString()),
	   false,
	   null,
	   null,
	   new PalettePane(cxn),
	   null);

    component = (PalettePane)getDialogComponent();
    Dimension size = component.getTabPreferredSize();
    size.width+=40;
    size.height+=40;
    setSize(size);

  }

  PalettePane getPalettePane() {
    return component;
  }
  
  @Override
  public void setVisible(boolean visible){
    super.setVisible(visible);
    if (!visible) {
      component.cancelDrops();
    }
  }

}

