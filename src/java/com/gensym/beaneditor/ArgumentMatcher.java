package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import java.util.Vector;
import java.util.Enumeration;
import javax.swing.JButton;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.StandardDialog;

class ArgumentMatcher implements StandardDialogClient{

  private Frame frame;
  private HookupCall call;
  private Class eventType;
  private HookupArgument[] arguments;
  private Object[] choicesPerArgument;

  ArgumentMatcher(Frame frame, HookupCall call, Class eventType){
    this.call = call;
    this.eventType = eventType;
    this.frame = frame;
  }
  
  HookupArgument[] matchArguments(){
    int len = call.arguments.length;
    if (len == 0) return call.arguments;
    if ((len == 1) && (eventType == call.arguments[0].type)){
      HookupArgument hookupArgument = call.arguments[0];
      hookupArgument.valueType = HookupArgument.OBJECT_ITSELF;
      hookupArgument.objectName = "event";
      return call.arguments;
    } 
    arguments = new HookupArgument[len];
    for (int i=0; i<len; i++)
      this.arguments[i] = call.arguments[i];
    choicesPerArgument = new Object[len];
    for (int i=0; i<len; i++){
      HookupChoices[] hookupChoices = arguments[i].getHookupChoices(call, eventType);
      choicesPerArgument[i] = hookupChoices;
    }
    new ArgumentMatcherDialog(frame, this).setVisible(true);
    return arguments;
  }

  @Override
  public void dialogDismissed(StandardDialog dlg, int cmdCode) {
    if (dlg.wasCancelled ())
      arguments = null;
  }
    
  class ArgumentMatcherDialog extends StandardDialog implements PropertyChangeListener{

    private JButton okButton;
    private ArgumentMatcherPanel panel;

    ArgumentMatcherDialog(Frame frame, StandardDialogClient client){
      super(frame, "Edit Arguments", true,
	    new String[] {OK_LABEL, CANCEL_LABEL}, new int[] {OK, CANCEL}, 
	    null, client);
      setDialogComponent (new ArgumentMatcherPanel());
      setTitle("Edit Arguments: "+call.method.getName()+"()");
      okButton = getJButton(OK);
      panel = (ArgumentMatcherPanel)getDialogComponent();
      panel.addPropertyChangeListener(this);
      okButton.setEnabled(panel.isAvailable());
    }

    @Override
    protected int getButtonAlignment () {
      return StandardDialog.CENTER;
    }

    @Override
    public void propertyChange(PropertyChangeEvent e){
      okButton.setEnabled(((Boolean)e.getNewValue()).booleanValue());
    }    
  }

  class ArgumentMatcherPanel extends Panel implements ItemListener, KeyListener{

    private GridBagLayout gridbag = new GridBagLayout();
    private GridBagConstraints c = new GridBagConstraints();

    private List argumentList;
    private CheckboxGroup valueTypeGroup;
    private Checkbox objectCheckbox, propCheckbox, constantCheckbox;
    private Choice objectChoice, propObjectChoice, propChoice, constantTypeChoice;
    private TextField constantTextField;
    private Label constantTypeLabel;

    private boolean available= false;
    private Vector listeners = new Vector();

    ArgumentMatcherPanel(){
      setLayout(gridbag);
      c.fill = GridBagConstraints.BOTH;
      c.anchor = GridBagConstraints.WEST;
      c.insets = new Insets(5, 5, 5, 5);
      Label label;
      label = new Label("Argument:");
      addWithConstraints(label);

      c.gridwidth = GridBagConstraints.REMAINDER;
      label = new Label("Value for argument:");
      addWithConstraints(label);

      c.gridheight = 4;
      c.gridwidth = 1;
      c.weighty = 1;
      c.weightx = 0.5;
      argumentList = new List();
      argumentList.addItemListener(this);
      addWithConstraints(argumentList);

      c.gridheight = 1;
      c.weighty = 0;
      c.weightx = 0;
      valueTypeGroup = new CheckboxGroup();
      objectCheckbox = new Checkbox("Object:", valueTypeGroup, false);
      objectCheckbox.addItemListener(this);
      addWithConstraints(objectCheckbox);
  
      c.gridwidth = GridBagConstraints.REMAINDER;
      c.weightx = 0.25;
      objectChoice = new Choice();
      objectChoice.addItemListener(this);
      addWithConstraints(objectChoice);

      c.gridwidth = 1;
      c.weightx = 0;
      propCheckbox = new Checkbox("Property:", valueTypeGroup, false);
      propCheckbox.addItemListener(this);
      addWithConstraints(propCheckbox);
      
      c.weightx = 0.25;
      propObjectChoice = new Choice();
      propObjectChoice.addItemListener(this);
      addWithConstraints(propObjectChoice);

      c.gridwidth = GridBagConstraints.REMAINDER;
      propChoice = new Choice();
      propChoice.addItemListener(this);
      addWithConstraints(propChoice);

      c.gridwidth = 1;
      c.weightx = 0;
      constantCheckbox = new Checkbox("Constant:", valueTypeGroup, false);
      constantCheckbox.addItemListener(this);
      addWithConstraints(constantCheckbox);

      c.gridwidth = GridBagConstraints.REMAINDER;
      c.weightx = 0.5;
      constantTextField = new TextField();
      constantTextField.addKeyListener(this);
      addWithConstraints(constantTextField);

      c.anchor = GridBagConstraints.EAST;
      c.gridwidth = GridBagConstraints.RELATIVE;
      c.weightx = 0;
      c.gridx = 2;
      constantTypeLabel = new Label("Type:");
      addWithConstraints(constantTypeLabel);

      c.weightx = 1;
      c.gridx = 3;
      constantTypeChoice = new Choice();
      constantTypeChoice.addItemListener(this);
      addWithConstraints(constantTypeChoice);

      //initialize argument list
      for (int i=0; i<arguments.length; i++){
	argumentList.add(arguments[i].name);
      }
      argumentList.select(0);
      initializeControls();
      updateAvailability();
    }

    private void addWithConstraints(Component component){
     gridbag.setConstraints(component, c);
     add(component);
    }

    private void initializeControls(){
      objectChoice.removeAll();
      propObjectChoice.removeAll();
      propChoice.removeAll();
      constantTextField.setText("");
      constantTypeChoice.removeAll();

      int index = argumentList.getSelectedIndex();
      if (index >= 0){
	HookupChoices[] choices = (HookupChoices[])choicesPerArgument[index];
	for (int i=0; i<choices.length; i++){
	  HookupChoices choice = choices[i];
	  if (choice.objectName.equals("source")){
	    if (choice.isObjectItselfApplicable)
	      objectChoice.add("source");
	    if (choice.applicableProperties != null && choice.applicableProperties.length > 0)
	      propObjectChoice.add("source");
	  }
	  else if (choice.objectName.equals("target")){
	    if (choice.isObjectItselfApplicable)
	      objectChoice.add("target");
	    if (choice.applicableProperties != null && choice.applicableProperties.length > 0)
	      propObjectChoice.add("target");
	  }
	  else if (choice.objectName.equals("event")){
	    if (choice.isObjectItselfApplicable)
	      objectChoice.add("event");
	    if (choice.applicableProperties != null && choice.applicableProperties.length > 0)
	      propObjectChoice.add("event");
	  }
	  else{//friend
	    if (choice.isObjectItselfApplicable)
	      objectChoice.add(choice.objectName);
	    if (choice.applicableProperties != null && choice.applicableProperties.length > 0)
	      propObjectChoice.add(choice.objectName);
	  }
	}

	objectCheckbox.setEnabled(objectChoice.getItemCount() > 0);
	propCheckbox.setEnabled(propObjectChoice.getItemCount() > 0);
	
	String[] types = getPossibleConstantTypes(arguments[index].type);
	for (int i=0; i<types.length; i++)
	  constantTypeChoice.add(types[i]);

	HookupArgument hookupArgument = arguments[index];
	switch(hookupArgument.valueType){
	case HookupArgument.UNSPECIFIED: 
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  constantTypeChoice.select(0);
	  break;
	case HookupArgument.CONSTANT_INT:
	  constantTypeChoice.select("int");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_LONG:
	  constantTypeChoice.select("long");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_CHAR:
	  constantTypeChoice.select("char");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_SHORT:
	  constantTypeChoice.select("short");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_BYTE:
	  constantTypeChoice.select("byte");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_DOUBLE:
	  constantTypeChoice.select("double");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_FLOAT:
	  constantTypeChoice.select("float");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_BOOLEAN:
	  constantTypeChoice.select("boolean");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_NULL:
	  constantTypeChoice.select("null");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_STRING:
	  constantTypeChoice.select("String");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.CONSTANT_SYMBOL: 
	  constantTypeChoice.select("Symbol");
	  constantTextField.setText(hookupArgument.constantExpression);
	  valueTypeGroup.setSelectedCheckbox(constantCheckbox);
	  break;
	case HookupArgument.OBJECT_ITSELF:
	  valueTypeGroup.setSelectedCheckbox(objectCheckbox);
	  break;
	case HookupArgument.OBJECT_PROPERTY:
	valueTypeGroup.setSelectedCheckbox(propCheckbox);
	break;
	}

	initializeChoices();
      }
    }

    @Override
    public void itemStateChanged(ItemEvent event){
      Object source = event.getSource();
      int index = argumentList.getSelectedIndex();
      HookupArgument hookupArgument = arguments[index];
      if (source instanceof List)
	initializeControls();
      else if (source instanceof Checkbox)
        initializeChoices();
      else if (source instanceof Choice){
	if (source.equals(objectChoice)){
	  hookupArgument.objectName = objectChoice.getSelectedItem();
	}
	else if (source.equals(propObjectChoice)){
	  hookupArgument.objectName = propObjectChoice.getSelectedItem();
	  initializePropertyChoices();
	  hookupArgument.propertyName = propChoice.getSelectedItem();
	}
	else if (source.equals(propChoice)){
	  hookupArgument.propertyName = propChoice.getSelectedItem();
	}
	else if (source.equals(constantTypeChoice)){
	  hookupArgument.valueType = getConstantValueType();
	  hookupArgument.constantExpression = constantTextField.getText();
	}
      }
      updateAvailability();
    }
    
    private void initializeChoices(){
      objectChoice.setEnabled(false);
      propObjectChoice.setEnabled(false);
      propChoice.setEnabled(false);
      constantTextField.setEnabled(false);
      constantTypeChoice.setEnabled(false);
      constantTypeLabel.setEnabled(false);

      Checkbox selectedCB = valueTypeGroup.getSelectedCheckbox();
      if (selectedCB != null){
	int index = argumentList.getSelectedIndex();
	HookupArgument hookupArgument = arguments[index];
	if (selectedCB.equals(objectCheckbox)){
	  objectChoice.setEnabled(true);
	  hookupArgument.valueType = HookupArgument.OBJECT_ITSELF;
	  hookupArgument.objectName = objectChoice.getSelectedItem();
	  hookupArgument.propertyName = null;
	  hookupArgument.constantExpression = null;
	}
	else if (selectedCB.equals(propCheckbox)){
	  propObjectChoice.setEnabled(true);
	  propChoice.setEnabled(true);
	  initializePropertyChoices();
	  hookupArgument.valueType = HookupArgument.OBJECT_PROPERTY;
	  hookupArgument.objectName = propObjectChoice.getSelectedItem();
	  hookupArgument.propertyName = propChoice.getSelectedItem();
	  hookupArgument.constantExpression = null;
	}
	else{
	  constantTextField.setEnabled(true);
	  constantTypeChoice.setEnabled(true);
	  constantTypeLabel.setEnabled(true);
	  constantTextField.requestFocus();
	  hookupArgument.valueType = getConstantValueType();
	  hookupArgument.objectName = null;
	  hookupArgument.propertyName = null;
	  hookupArgument.constantExpression = constantTextField.getText();
	}
      }
    }

    private void initializePropertyChoices(){
      propChoice.removeAll();
      String objectName = propObjectChoice.getSelectedItem();
      if (objectName != null){
	int index = argumentList.getSelectedIndex();
	HookupChoices[] choices = (HookupChoices[])choicesPerArgument[index];
	for (int i=0; i<choices.length; i++){
	  HookupChoices choice = choices[i];
	  if (choice.objectName.equals(objectName)){
	    for (int j=0; j<choice.applicableProperties.length; j++)
	      propChoice.add(choice.applicableProperties[j]);
	  }
	}
      }
    }

    private int getConstantValueType(){
      String type = constantTypeChoice.getSelectedItem();
      if (type.equals("int")) return HookupArgument.CONSTANT_INT;
      else if (type.equals("long")) return HookupArgument.CONSTANT_LONG;
      else if (type.equals("char")) return HookupArgument.CONSTANT_CHAR;
      else if (type.equals("short")) return HookupArgument.CONSTANT_SHORT;
      else if (type.equals("byte")) return HookupArgument.CONSTANT_BYTE;
      else if (type.equals("double")) return HookupArgument.CONSTANT_DOUBLE;
      else if (type.equals("float")) return HookupArgument.CONSTANT_FLOAT;
      else if (type.equals("boolean")) return HookupArgument.CONSTANT_BOOLEAN;
      else if (type.equals("null")) return HookupArgument.CONSTANT_NULL;
      else if (type.equals("String")) return HookupArgument.CONSTANT_STRING;
      else if (type.equals("Symbol")) return HookupArgument.CONSTANT_SYMBOL;
      else return -1;
    }

    private String[] getPossibleConstantTypes(Class type){
      Vector types = new Vector();
      if (type.isAssignableFrom(Integer.TYPE))
	types.addElement("int");
      if (type.isAssignableFrom(Long.TYPE))
	types.addElement("long");
      if (type.isAssignableFrom(Character.TYPE))
	types.addElement("char");
      if (type.isAssignableFrom(Short.TYPE))
	types.addElement("short");
      if (type.isAssignableFrom(Byte.TYPE))
	types.addElement("byte");
      if (type.isAssignableFrom(Double.TYPE))
	types.addElement("double");
      if (type.isAssignableFrom(Float.TYPE))
	types.addElement("float");
      if (type.isAssignableFrom(Boolean.TYPE))
	types.addElement("boolean");
      if (type.isAssignableFrom(String.class))
	types.addElement("String");
      if (type.isAssignableFrom(com.gensym.util.Symbol.class))
	types.addElement("Symbol");
      if (!type.isPrimitive())
	types.addElement("null");
      String[] possibleTypes = new String[types.size()];
      types.copyInto(possibleTypes);
      return possibleTypes;
    }

    @Override
    public void keyPressed(KeyEvent event){
    }

    @Override
    public void keyTyped(KeyEvent event){
    }

    @Override
    public void keyReleased(KeyEvent event){
      int index = argumentList.getSelectedIndex();
      HookupArgument hookupArgument = arguments[index];
      hookupArgument.constantExpression = constantTextField.getText();
      updateAvailability();
    }

    boolean isAvailable(){
      return available;
    }

    private void updateAvailability(){
      int len = arguments.length;
      String result = null;
      for (int i=0; i<len; i++){
	HookupArgument hookupArgument = arguments[i];
	result = hookupArgument.getErrorIfAny(call, eventType);
	if (result != null)
	  break;
      }
      boolean currentAvailability = (result == null);
      if (currentAvailability != available){
	available = currentAvailability;
	notifyPropertyChange();
      }
    }

    @Override
    public void addPropertyChangeListener(PropertyChangeListener listener){
      listeners.addElement(listener);
    }

    @Override
    public void removePropertyChangeListener(PropertyChangeListener listener){
      listeners.removeElement(listener);
    }

    private void notifyPropertyChange(){
      Boolean oldValue, newValue;
      if (available){
	oldValue = Boolean.FALSE;
	newValue = Boolean.TRUE;
      }
      else{
	oldValue = Boolean.TRUE;
	newValue = Boolean.FALSE;
      }
      PropertyChangeEvent e = new PropertyChangeEvent(this, "Available", oldValue, newValue);
      Vector l;
      synchronized(this) {l = (Vector)listeners.clone();}
      Enumeration dispatchList = l.elements();
      while (dispatchList.hasMoreElements()){
	PropertyChangeListener listener = ((PropertyChangeListener)dispatchList.nextElement());
	listener.propertyChange(e);
      }
    }
  }
}
