package com.gensym.editor.text;

import java.awt.Button;
import java.awt.Color;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;


public class G2FreeTextFontSizeDialog extends StandardDialog {
  private Symbol SMALL_ = Symbol.intern("SMALL");
  private static final Symbol LARGE_ = Symbol.intern("LARGE");
  private Symbol FONT_SIZE_ = Symbol.intern("FONT-SIZE");
  private Symbol X_MAGNIFICATION_ = Symbol.intern("X-MAGNIFICATION");
  private Symbol Y_MAGNIFICATION_ = Symbol.intern("Y-MAGNIFICATION");
  private G2FreeTextFontSizePanel freeTextPanel;

  public G2FreeTextFontSizeDialog(Frame parentFrame, String title,
                                  boolean isModal,
			          StandardDialogClient client) {
    this(parentFrame, title, isModal,
	 new String[] {OK_LABEL, APPLY_LABEL, CANCEL_LABEL},
	 new int[] {OK, APPLY, CANCEL},
	 new G2FreeTextFontSizePanel(),
	 client);
  }

  private G2FreeTextFontSizeDialog(Frame parentFrame,
			       String title,
			       boolean isModal,
			       String[] labels,
			       int[] ids,
			       G2FreeTextFontSizePanel freeTextFontSizePanel,
			       StandardDialogClient client)
  {
    super(parentFrame, title, isModal,
	  labels, ids, freeTextFontSizePanel,
	  new DialogClient(client));
    this.freeTextPanel = freeTextFontSizePanel;
  }

  @Override
  protected int getButtonAlignment(){
    return CENTER;
  }

  public Structure getNewFreeTextFont () {
    Structure textFontStructure = new Structure();
    double x_magnification = 0.0;
    double y_magnification = 0.0;
    int fontSize = freeTextPanel.getSelectedFontSize();
    if (fontSize == 0) return null;

    switch (fontSize) {
      case 8:
        x_magnification = 0.8;
        y_magnification = 0.8;
        break;
      case 9:
        x_magnification = 0.85;
        y_magnification = 0.85;
        break;
      case 10:
        x_magnification = 0.9;
        y_magnification = 0.9;
        break;
      case 11:
        x_magnification = 0.95;
        y_magnification = 0.95;
        break;
      case 12:
        x_magnification = 1.0;
        y_magnification = 1.0;
        break;
      case 14:
        x_magnification = 1.17;
        y_magnification = 1.17;
        break;
      case 16:
        x_magnification = 1.34;
        y_magnification = 1.34;
        break;
      case 18:
        x_magnification = 1.51;
        y_magnification = 1.51;
        break;
      case 20:
        x_magnification = 1.68;
        y_magnification = 1.68;
        break;
      case 22:
        x_magnification = 1.85;
        y_magnification = 1.85;
        break;
      case 24:
        x_magnification = 2.0;
        y_magnification = 2.0;
        break;
      case 26:
        x_magnification = 2.17;
        y_magnification = 2.17;
        break;
      case 28:
        x_magnification = 2.34;
        y_magnification = 2.34;
        break;
      case 30:
        x_magnification = 2.51;
        y_magnification = 2.51;
        break;
      case 32:
        x_magnification = 2.68;
        y_magnification = 2.68;
        break;
      case 34:
        x_magnification = 2.85;
        y_magnification = 2.85;
        break;
      case 36:
        x_magnification = 3.0;
        y_magnification = 3.0;
        break;
      case 48:
        x_magnification = 3.0;
        y_magnification = 3.0;
        break;
      case 72:
        x_magnification = 6.0;
        y_magnification = 6.0;
        break;
    }
    if (fontSize == 72 || fontSize == 48)
      textFontStructure.setAttributeValue(FONT_SIZE_, LARGE_);
    else
      textFontStructure.setAttributeValue(FONT_SIZE_, SMALL_);
    textFontStructure.addAttribute(X_MAGNIFICATION_, new Double(x_magnification));
    textFontStructure.addAttribute(Y_MAGNIFICATION_, new Double(y_magnification));

    return  textFontStructure;
  }

 }
  class DialogClient implements StandardDialogClient , java.io.Serializable {
    private StandardDialogClient userClient;

    DialogClient(StandardDialogClient userClient)
    {
      this.userClient = userClient;
    }

    @Override
    public void dialogDismissed (StandardDialog dlg, int code) {
      if (userClient != null)
	userClient.dialogDismissed(dlg, code);
      if (code == com.gensym.dlg.CommandConstants.APPLY)
        return;
    }
  }


