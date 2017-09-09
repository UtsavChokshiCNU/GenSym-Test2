package com.gensym.ntw.util;

import com.gensym.dlg.QuestionDialog;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.ntw.TwAccess;
import java.util.Vector;
import java.awt.Frame;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.classes.Item;
import com.gensym.ntw.util.uitools.IconKBTools;
import java.awt.Image;
import javax.swing.JPanel;
import java.awt.GridLayout;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JCheckBox;
import javax.swing.border.EtchedBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.CompoundBorder;
import javax.swing.JLabel;
import javax.swing.JButton;
import java.awt.BorderLayout;
import com.gensym.uitools.utils.StatusBar;

public class UnsolicitedDialog extends QuestionDialog {

  private Vector pushButtonStructures;
  private int dialogID;
  private int reasonForCallback;//should be protected in standard dialog!
  private static final Symbol
  TEXT_ = Symbol.intern ("TEXT"),
    VALUE_ = Symbol.intern ("VALUE"),
    NAME_ = Symbol.intern ("NAME");
  private TwAccess connection;
  private CheckBoxPanel checkBoxPanel;
  private StatusBar statusBar;

  UnsolicitedDialog(TwAccess connection,
		    Frame frame,
		    String title,
		    int dialogID,
		    Sequence pushButtonStructures,
		    String checkBoxLabel,
		    Sequence checkBoxStructures,
		    String message,
		    Item focalItem,
		    StatusBar statusBar)
  {
    super(frame,
	  title,
	  false,
	  getButtonLabels(pushButtonStructures),
	  getButtonCodes(pushButtonStructures),
	  message,
	  createImage(focalItem),
	  null);
    this.statusBar = statusBar;
    this.connection = connection;
    this.dialogID = dialogID;

    JPanel messagePanel = (JPanel)getDialogComponent();    
    if (!checkBoxStructures.isEmpty()) {
      checkBoxPanel = new CheckBoxPanel(checkBoxLabel,checkBoxStructures);
      checkBoxPanel.setBorder(new CompoundBorder(new EmptyBorder(messagePanel.getInsets()),
						 new EtchedBorder()));
      messagePanel.add(checkBoxPanel,"South");
    }
    if (statusBar != null) {
      JPanel southernPanel = new JPanel();
      southernPanel.setLayout(new BorderLayout());
      southernPanel.add(getCommandPanel());
      southernPanel.add(statusBar, BorderLayout.SOUTH);
      getContentPane().add(southernPanel, BorderLayout.SOUTH);
    }
      
    this.pushButtonStructures = pushButtonStructures;
  }

  public static UnsolicitedDialog createDialog(Frame frame,
					       UnsolicitedDialogEvent event,
					       StatusBar statusBar) {
    String title = event.getDialogName().toString();
    String message = "";
    String checkBoxLabel = null;
    Sequence pushButtonStructures = new Sequence();
    Sequence checkBoxStructures = new Sequence();
    Item focalItem = null;
    Sequence dialogInfo = event.getDialogInfo();
    int count = dialogInfo.size();
    for (int i=0;i<count;i++) {
      Structure struct = (Structure)dialogInfo.elementAt(i);
      Symbol type = (Symbol)struct.getAttributeValue(event.TYPE_, null);
      if (event.TEXT_.equals(type)) {
	boolean isCheckBoxLabel = false;
	if (i+1<count) {
	  Structure nextStruct = (Structure)dialogInfo.elementAt(i+1);
	  Symbol nextType = (Symbol)nextStruct.getAttributeValue(event.TYPE_, null);
	  isCheckBoxLabel = event.CHECK_BOX_.equals(nextType);
	}
	String newString = (String)struct.getAttributeValue(event.TEXT_, null);
	if (isCheckBoxLabel)
	  checkBoxLabel = newString;
	else 
	  message+=newString+"\n";
      } else if (event.BUTTON_.equals(type))
	pushButtonStructures.addElement(struct);
      else if (event.CHECK_BOX_.equals(type))
	checkBoxStructures.addElement(struct);
      else if (event.ITEM_.equals(type))
	focalItem = (Item)struct.getAttributeValue(event.ITEM_, null);
      //Structure {TYPE:ITEM, ITEM:com.gensym.classes.KbWorkspaceImpl@e80d3c70(KB-WORKSPACE, # = 67v0, ok), NAME:UNEDITABLE-ITEM}

    }
    return new UnsolicitedDialog((TwAccess)event.getSource(),
				 frame,
				 title,
				 event.getDialogID(),
				 pushButtonStructures,
				 checkBoxLabel,
				 checkBoxStructures,
				 message,
				 focalItem,
				 statusBar);
  }
  
  class CheckBoxPanel extends JPanel {
    Sequence checkBoxStructures;
    CheckBoxPanel(String checkBoxLabel, Sequence checkBoxStructures) {
      int count = checkBoxStructures.size();
      setLayout(new GridLayout(count+1,1));
      if (checkBoxLabel != null)
	add(new JLabel(checkBoxLabel));
      for (int i=0;i<count;i++) {
	Structure struct = (Structure)checkBoxStructures.elementAt(i);
	String text = (String)struct.getAttributeValue(TEXT_, "none");
	Boolean selected = (Boolean)struct.getAttributeValue(VALUE_, Boolean.FALSE);
	if (selected == null)
	  selected = Boolean.FALSE;
	JCheckBox checkBox = new JCheckBox(text, selected.booleanValue());
	checkBox.addChangeListener(new CheckBoxStructureUpdater(struct));
	add(checkBox);
      }
      this.checkBoxStructures = checkBoxStructures;
    }
    class CheckBoxStructureUpdater implements ChangeListener {
      private Structure struct;
      CheckBoxStructureUpdater(Structure struct) {
	this.struct = struct;
      }
      @Override
      public void stateChanged(ChangeEvent ce) {
	JCheckBox button = (JCheckBox)ce.getSource();
	struct.setAttributeValue(VALUE_,
				 button.isSelected()?Boolean.TRUE:Boolean.FALSE);
      }

    }
  }

  public void updateButton(Symbol oldButtonName,
			   String newButtonLabel,
			   Symbol newButtonName)
  {
    int buttonCount = pushButtonStructures.size();
    String[] labels = new String[buttonCount];
    for (int i=0;i<buttonCount;i++) {
      Structure buttonStructure = (Structure) pushButtonStructures.elementAt(i);
      Symbol name = (Symbol)buttonStructure.getAttributeValue(NAME_, null);
      if (oldButtonName.equals(name)) {
	JButton button = getJButton(i);
	button.setLabel(newButtonLabel);
	buttonStructure.setAttributeValue(NAME_, newButtonName);
	buttonStructure.setAttributeValue(TEXT_, newButtonLabel);	
	break;
      }
    }
  }
  
  public void setStatus(String message, int region) {
    if (statusBar != null)
      statusBar.setStatus(message, region);
  }
  
  private static Image createImage(Item focalItem) {
    Image image = null;
    if (focalItem != null) 
      image = IconKBTools.getIconForItem(focalItem, true, 50,50).getImage();
    return image;
  }
  
  private static String[] getButtonLabels(Vector buttonStructures) {
    int buttonCount = buttonStructures.size();
    String[] labels = new String[buttonCount];
    for (int i=0;i<buttonCount;i++) {
      Structure buttonStructure = (Structure) buttonStructures.elementAt(i);
      labels[i] = (String)buttonStructure.getAttributeValue(TEXT_, "none");
    }
    return labels;    
  }

  private static int[] getButtonCodes(Vector buttonStructures) {
    int buttonCount = buttonStructures.size();
    int[] codes = new int[buttonCount];
    for (int i=0;i<buttonCount;i++)
      codes[i]=i;
    return codes;
  }
  
  private Sequence getReturnValues() {
    Sequence returnValues = null;
    if (checkBoxPanel != null)
      returnValues = checkBoxPanel.checkBoxStructures;
    else
      returnValues = new Sequence();
    returnValues.addElement(pushButtonStructures.elementAt(reasonForCallback));
    return returnValues;
  }
  
  private static final Symbol
  G2_RETURN_VALUES_TO_UNSOLICITED_DIALOG_ =
  Symbol.intern ("G2-RETURN-VALUES-TO-UNSOLICITED-DIALOG");
  
  private void returnValues() {
    try {
      connection.callRPC(G2_RETURN_VALUES_TO_UNSOLICITED_DIALOG_,
			 new Object[] {new Integer(getID()),
					 getReturnValues(),
					 connection.getSession()});
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  @Override
  protected void dispatchCallback (int code) {
    reasonForCallback = code;
    returnValues();
  }
  
  public int getID() {
    return dialogID;
  }
  
}
	 
