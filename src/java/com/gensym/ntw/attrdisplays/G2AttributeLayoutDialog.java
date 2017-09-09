package com.gensym.ntw.attrdisplays;

import java.util.Vector;
import javax.swing.JComponent;
import com.gensym.classes.Block;
import com.gensym.classes.Entity;
import com.gensym.classes.Item;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.gcg.AttributeInfo;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.PrettySymbol;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.NtwIllegalArgumentException;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayout;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayoutEditor;
import com.gensym.uitools.attrdisplays.layoutui.AttributeLayoutComponent;
import com.gensym.uitools.attrdisplays.layoutui.ComponentConstructionException;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;

public class G2AttributeLayoutDialog extends StandardDialog {

  private static Resource dlgLabels = Trace.getBundle("com.gensym.uitools.attrdisplays.DialogLabels");
  private Entity entity;
  private AttributeLayoutComponent component;
  private AttributeDisplayLayoutEditor editor;
  private Symbol userMode;
  private Item item;
  private G2AttributeDisplayLayoutConverter converter = 
    new G2AttributeDisplayLayoutConverter();
  private DialogCloser closer;
  private static final Symbol UUID_ = Symbol.intern("UUID");
  private static final Symbol TABLE_HEADER_ = Symbol.intern("TABLE-HEADER");
  public G2AttributeLayoutDialog (String label, Entity entity, TwAccess cxn, 
				  int focusIndex) throws G2AccessException, 
    ComponentConstructionException
  {
    super(null, label, false, 
	  new String[] {OK_LABEL, CANCEL_LABEL, APPLY_LABEL}, 
	  new int[]{OK, CANCEL, APPLY}, 
	  new AttributeLayoutComponent(new G2AttributeDisplayLayoutEditor(new Object[0])),
	  new G2LayoutDlgClient()); 
    

    //setting class fields
    this.entity = entity;
    item = (Item)entity;
    component = (AttributeLayoutComponent)getDialogComponent();
    editor = component.getEditor();
    closer = new DialogCloser(cxn);

    //setting editor choices
    Symbol[] choices  = AttributeInfo.getTableAttributesForMode(cxn, item, cxn.getUserMode());
    int length = choices.length;
    PrettySymbol[] newChoices;
    if (cxn.getG2Version().getMajorVersion() >= 6) {
      newChoices = new PrettySymbol[length+1];
      newChoices[0] = new PrettySymbol(TABLE_HEADER_);
      for (int i=0; i<length; i++)
	newChoices[i+1] = new PrettySymbol(choices[i]);
    } else {
      newChoices = new PrettySymbol[length];
      for (int i=0;i<length;i++)
	newChoices[i] = new PrettySymbol(choices[i]);
    }
    editor.setChoices(newChoices);
    //setting editor initialAttributeDislays
    Sequence currentAttrs = entity.getCurrentAttributeDisplays();
    AttributeDisplayLayout[] currentAttrArray;
    currentAttrArray = converter.convertFromApplication(currentAttrs);
    editor.setInitialAttributeDisplayLayouts(currentAttrArray);
    
    //setting tab labels
    Sequence tempSeq = entity.getAttributeDisplayItems();
    Object nameForTab;
    Vector tabLabels = new Vector();
    if (tempSeq != null) {
      for (int x=tempSeq.size() - 1; x> -1; x--) {
	nameForTab = ((Block)tempSeq.elementAt(tempSeq.size() - x -1)).getNames();
	if (nameForTab == null) 
	  tabLabels.add(Symbol.intern("DISPLAY-" +x));
	else
	  tabLabels.add((Symbol)nameForTab);
      }
    }

    //putting tabs into dialog component
    populateAttrDialog(currentAttrArray, component, tabLabels.toArray());
    component.setSelectedIndex(focusIndex);

    setDefaultButton(OK);
  }

  @Override
  protected int getButtonAlignment() {
    return CENTER;
  }

  /**
   * calls addTab for every initial layout.  
   */
  private void populateAttrDialog(AttributeDisplayLayout[] layouts, 
				  AttributeLayoutComponent dialogComponent, 
				  Object[] tabLabels) 
  {
    int arraySize=0;
    if (layouts != null) 
     arraySize = layouts.length;
    for (int i=0; i<arraySize; i++) {
      dialogComponent.addTab(layouts[i]);
      dialogComponent.setTitleOf(i, new PrettySymbol((Symbol)tabLabels[i]));
    }
    if (arraySize == 0) 
      dialogComponent.addTab(editor.createAttributeDisplayLayout()); 
  }

  private class DialogCloser extends G2ConnectionAdapter {
    G2Access cxn;
    public DialogCloser (TwAccess cxn) {
      this.cxn = (G2Access)cxn;
      this.cxn.addG2ConnectionListener(this);
    }
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent e) {
      cxn.removeG2ConnectionListener(this);
      setVisible(false);
      component.dispose();
    }
  }

  private static class G2LayoutDlgClient implements StandardDialogClient {
    AttributeLayoutComponent component;
    AttributeDisplayLayoutEditor editor;

    private Sequence getConvertedSequence(G2AttributeDisplayLayoutConverter converter) {
      AttributeDisplayLayout[] currentValue = editor.getCurrentAttributeDisplayLayouts();
      Sequence setInfo = converter.convertForApplication(currentValue);
      editor.setInitialAttributeDisplayLayouts(currentValue);
      return setInfo;
    }

    private void setLabels(Sequence attributeDisplayItems) throws G2AccessException {
      Object[] labels = component.getTitles();
      for (int x=0; x<labels.length; x++) {
	if (!(labels[x].toString().toLowerCase().startsWith("display")))
	  if (labels[x] instanceof PrettySymbol)
	    ((Block)attributeDisplayItems.elementAt(labels.length-1-x)).
	      setNames(((PrettySymbol)labels[x]).getSymbol());
	  else
	    ((Block)attributeDisplayItems.elementAt(labels.length-1-x)).
	      setNames(Symbol.intern(labels[x].toString().
				     replace(' ', '-').toUpperCase()));
      }
    }

    @Override
    public void dialogDismissed(StandardDialog thisDialog, int index) {
      G2AttributeLayoutDialog g2Dialog = (G2AttributeLayoutDialog)thisDialog;
      component = g2Dialog.component;
      editor = g2Dialog.editor;

      switch (index) {
      case CANCEL:
	component.dispose();
	break;
      case OK:
	applyDialog(g2Dialog);
	component.dispose();
	break;
      case APPLY:
	applyDialog(g2Dialog);
	    break;
      }
    }

    private void applyDialog(G2AttributeLayoutDialog thisDialog) {
      Sequence convertedSequence;
      Entity dlgEntity = thisDialog.entity;
      
      try {
	convertedSequence = getConvertedSequence(thisDialog.converter);
	dlgEntity.setCurrentAttributeDisplays
	  (convertedSequence);
	setLabels(dlgEntity.getAttributeDisplayItems());
      } catch (G2AccessException g2ae) {
	new WarningDialog (null, dlgLabels.getString
			   ("errorApplyingAttributeDisplayLayoutChanges"),
			   false, g2ae.getMessage(), null).setVisible(true);
      }
    }
    
  }

}
  

