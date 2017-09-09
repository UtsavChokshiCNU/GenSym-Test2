package com.gensym.demos.g2studiosample;

import java.util.Locale;
import java.awt.Container;
import java.awt.event.FocusListener;
import java.awt.event.FocusEvent;
import java.awt.Color;
import java.awt.Component;
import java.awt.Insets;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.message.Trace;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.AttributeEditor;
import com.gensym.gcg.DefaultGeneratedDialogFactory;
import com.gensym.gcg.AttributeInfo;
import com.gensym.gcg.G2TextArea;
import com.gensym.gcg.G2AttributeGroup;
import com.gensym.gcg.GeneratedAttributeTable;
import com.gensym.gcg.AttributeLabel;
import com.gensym.editor.text.G2TextAreaKeyAdapter;
import com.gensym.editor.text.ParserController;
import com.gensym.editor.text.G2SideParser;
import com.gensym.editor.text.Prompter;
import com.gensym.editor.text.EditContext;
import com.gensym.ntw.TwAccess;
import javax.swing.border.EmptyBorder;
import javax.swing.JComponent;
import javax.swing.JTextField;

public class G2StudioGeneratedDialogFactory extends DefaultGeneratedDialogFactory {
  static Insets leftBufferMargins = new Insets(0,3,0,0);  
  static EmptyBorder leftBufferBorder = new EmptyBorder(leftBufferMargins);
  
    @Override
    protected Container generateAttributePanel(TwAccess connection, ItemProxy itemProxy,
					       DialogCommand dialogCommand,
					       Locale locale) throws G2AccessException
    {
      G2AttributeGroup[] groups = getAttributeEditors(connection, itemProxy, dialogCommand, locale);      
      return new GeneratedAttributeTable(connection, itemProxy, dialogCommand, groups, 
					 itemProxy.getAutoUpload());
    }

  @Override
  protected Component getAttributeLabel(TwAccess connection,
					ItemProxy itemProxy,
					DialogCommand dlgCommand,
					AttributeInfo info,
					Locale locale) throws G2AccessException
  {
    AttributeLabel label = new AttributeLabel(connection,
					      itemProxy.getProxy(),
					      info.getAttributeName(), 
					      itemProxy.getAutoUpload());
    label.setBorder(leftBufferBorder);
    return label;
  }
  
    @Override
    protected AttributeEditor getAttributeEditor(TwAccess connection,
						 ItemProxy itemProxy,
						 DialogCommand dlgCommand,
						 AttributeInfo info,
						 Locale locale) throws G2AccessException
    {
      info.initializeEditorInformation();

      if (info.isTextReadable() &&
	  info.isTextWritable() &&
	  !info.getAttributeName().equals(SystemAttributeSymbols.NOTES_)) {
	Object value = null;
	try {
	  value = itemProxy.getProxy().getPropertyValue(info.getAttributeName());
	} catch(NoSuchAttributeException ex){
	  Trace.exception(ex);
	}
	boolean isItem = (value instanceof Item);
	if (!info.hasEditor() || isItem) {
	  AttributeEditor editor = null;
	  if (isItem) {
	    editor = new GreyG2TextArea(connection, itemProxy.getProxy(), (Item)value,
					info.getAttributeName(), info.getDenotation(),  
					connection.getUserMode(), locale);
	  } else {
	    editor = new G2StudioTextArea(connection, itemProxy.getProxy(), info.getDenotation(), 
					  info.getDefiningClass(), info.getSimpleAttributeName());	    

	  }
	  if (editor != null) {
	    hookUpEditor(editor, itemProxy, info.getAttributeName(), info.isValueWritable());
	    return (AttributeEditor)editor;
	  }
	}
      }
      AttributeEditor editor = super.getAttributeEditor(connection, itemProxy, dlgCommand, info, locale);
      if (editor instanceof JTextField) {
	((JTextField)editor).setMargin(leftBufferMargins);
	
      }
      return editor;
    }
  }
  class GreyG2TextArea extends G2TextArea {
  public GreyG2TextArea(TwAccess connection, Item item, Item subItem, Symbol attribute, Structure denotation, 
			Symbol userMode, Locale locale){
    super(connection, item, subItem, attribute, denotation, userMode, locale);
    textArea.setBackground(Color.lightGray);
    textArea.setBorder(G2StudioGeneratedDialogFactory.leftBufferBorder);
  }
  public GreyG2TextArea(TwAccess connection, Item item, Structure denotation, Symbol className, 
			Symbol attributeName){
    super(connection, item, denotation, className, attributeName);
    textArea.setBackground(Color.lightGray);
    textArea.setBorder(G2StudioGeneratedDialogFactory.leftBufferBorder);
  }
    
  }
  class G2StudioTextArea extends G2TextArea
  implements FocusListener, ParserController {
    private G2SideParser parser;
    private G2TextAreaKeyAdapter keyAdapter;
    public G2StudioTextArea(TwAccess connection, Item item, Structure denotation, Symbol className, 
			    Symbol attributeName){
      super(connection, item, denotation, className, attributeName);
      keyAdapter = new G2TextAreaKeyAdapter(textArea, this);
      textArea.setEditable(true);
      textArea.addFocusListener(this);
      textArea.setBorder(G2StudioGeneratedDialogFactory.leftBufferBorder);      
    }
    private void close() {
      if (parser != null) {
	textArea.removeKeyListener(keyAdapter);
	Prompter prompter = EditContext.getContext().getPrompter();
	if (prompter != null)
	  prompter.removePromptSelectionListener(keyAdapter);
	EditContext.getContext().removeEditor(textArea);
	parser = null;      	
      }

    }
    @Override
    public void accept() {
      accept(false);
    }
    private void accept(boolean escapeIfBad) {
      if (item.isValid()&&parser != null) {
	boolean ok = parser.attemptToConcludeParsingContext(item, Boolean.FALSE);
	if (!ok && escapeIfBad) {
	  //show error
	  escape();
	}
      }
    }
    @Override
    public void escape() {
      objectUpdated(new com.gensym.dlgevent.ObjectUpdateEvent(this,this));//refresh w/ old text      
    }    
    @Override
    public void focusGained(FocusEvent fe) {
      if (parser == null) {
	TwAccess cxn=(TwAccess)((ImplAccess)item).getContext();
	try {
	  Symbol className = item.getG2ClassName();
	  parser = EditContext.getContext().addEditor(textArea,cxn,className,attribute);
	  textArea.addKeyListener(keyAdapter);
	  Prompter prompter = EditContext.getContext().getPrompter();
	  if (prompter != null)
	    prompter.addPromptSelectionListener(keyAdapter);
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}
      }
    }
    @Override
    public void focusLost(FocusEvent fe) {
      if (!fe.isTemporary()) {
	accept(true);
	close();
      }
    } 
  };
  
