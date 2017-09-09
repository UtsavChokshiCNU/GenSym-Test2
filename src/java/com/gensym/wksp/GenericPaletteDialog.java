package com.gensym.wksp;

import java.awt.Component;
import java.awt.Frame;
import java.util.Hashtable;
import javax.swing.ToolTipManager;

import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwConnectionAdapter;


class GenericPaletteDialog extends StandardDialog {

  public GenericPaletteDialog (TwConnection cxn,
			Hashtable paletteHash,
			Frame parent,
			String title,
			boolean isModal,
			String[] btnLabels,
			int[] btnCodes,
			Component x,
			StandardDialogClient c) {
    super (parent, title, isModal, btnLabels, btnCodes, x, c);
    final Hashtable paletteHashtable = paletteHash;
    final TwConnection connexn = cxn;
    paletteHashtable.put (cxn, this);
    cxn.addG2ConnectionListener (new G2ConnectionAdapter() {
      @Override
    public void g2ConnectionClosed(G2ConnectionEvent event) {
	TwConnection sourceCxn = (TwConnection) event.getSource ();
	if (sourceCxn.equals (connexn)) {
	  setVisible (false);
	  paletteHashtable.remove (GenericPaletteDialog.this);
	  connexn.removeG2ConnectionListener (this);
	}
      }
    });
  }
  /* This constructor is to be used by ItemPaletteDialog only! It doesn't need a hashtable,
     its hashtable is kept by PaletteCommands.*/

  public GenericPaletteDialog (Frame parent, String title, boolean isModal, String[] btnLabels,
			       int[] btnCodes, Component x, StandardDialogClient c){
    super (parent, title, isModal, btnLabels, btnCodes, x, c);
  }
}
