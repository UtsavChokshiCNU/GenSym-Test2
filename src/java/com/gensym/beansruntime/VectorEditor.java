package com.gensym.beansruntime;

import java.util.Vector;

import java.beans.*;
import java.awt.*;
import java.awt.event.*;
import java.lang.reflect.Method;
import com.gensym.message.Trace;
  
public abstract class VectorEditor extends Panel implements PropertyEditor,
  PropertyChangeListener,
  ActionListener, ItemListener, WindowListener
{
  protected Vector vector = getNewVector();
  
  private PropertyChangeSupport support = new PropertyChangeSupport(this);
  private List list;
  private Button newArgumentButton;
  private Button deleteArgumentButton; 
  private Button editArgumentButton;
  private Dialog properties;
  private PropertyEditor editor;
  private int cachedIndex = -1;
  private Panel commandPanel = new Panel();
  private Panel listPanel = new Panel();
  private Panel editPanel;
  private boolean elementIsAtomic = true;
  private Class elementClass;
  private Component editorComponent = null;
  private PropertyDescriptor[] descriptors;
  private PropertyEditor[] editors;
  private Component[] editorComponents;
 
  public VectorEditor(boolean elementIsAtomic, Class elementClass)
  {
    this.elementIsAtomic = elementIsAtomic;
    this.elementClass = elementClass;

    try {
      setLayout(new BorderLayout());
      GridBagLayout gridBag = new GridBagLayout();
      listPanel.setLayout(gridBag);
      GridBagConstraints constraints = new GridBagConstraints();
      constraints.fill = GridBagConstraints.BOTH;
      constraints.gridwidth = GridBagConstraints.REMAINDER;
      constraints.gridheight = 1;
      constraints.weightx = 1.0;
      constraints.weighty = 50.0;
      constraints.insets = new Insets(4,4,4,4);
      
      list = new List();
      gridBag.setConstraints(list,constraints);
      listPanel.add(list);
      list.addItemListener(this);
      
      constraints.gridwidth = GridBagConstraints.RELATIVE;
      constraints.weighty = 1.0;
      newArgumentButton = new Button("Add");
      gridBag.setConstraints(newArgumentButton,constraints);
      listPanel.add(newArgumentButton);
      newArgumentButton.addActionListener(this);
      
      constraints.gridwidth = GridBagConstraints.REMAINDER;
      deleteArgumentButton = new Button("Delete");
      gridBag.setConstraints(deleteArgumentButton,constraints);
      listPanel.add(deleteArgumentButton);
      deleteArgumentButton.addActionListener(this);
      if (!elementIsAtomic)
	gatherEditorsForBean();
      
      if (elementIsAtomic)
	{
	  editor = PropertyEditorManager.findEditor(elementClass);
	  editor.addPropertyChangeListener(this); 
	  constraints.gridwidth = GridBagConstraints.REMAINDER;
	  constraints.weighty = 1.0;
	  constraints.weightx = 1.0;
	  if (editor.getTags() != null)
	    editorComponent = new PropertyChoice(editor);
	  else if (editor.getAsText() != null)
	    editorComponent = new PropertyTextField(editor);
	  else if (editor instanceof Component)
	    editorComponent = (Component)editor;

	    
	  if (editorComponent != null)
	    {
	      gridBag.setConstraints(editorComponent,constraints);
	      listPanel.add(editorComponent);
	    }
	  //editor.setValue(selection);
	  add("Center",listPanel);
	}
      else if (editors.length == 0)
	{
	  add("Center",listPanel);
	}
      else
	{
	  editPanel = new Panel();
	  GridBagLayout editGridBag = new GridBagLayout();
	  editPanel.setLayout(editGridBag);
	  
	  constraints.gridwidth = 1;
	  constraints.gridheight = editors.length;
	  constraints.weightx = 20.0;
	  constraints.weighty = 100.0;
	  editGridBag.setConstraints(listPanel,constraints);
	  editPanel.add(listPanel);

	  GridBagConstraints labelConstraints = new GridBagConstraints();
	  labelConstraints.fill = GridBagConstraints.HORIZONTAL;
	  labelConstraints.gridwidth = GridBagConstraints.RELATIVE;
	  labelConstraints.gridheight = 1;
	  labelConstraints.weightx = 1.0;
	  labelConstraints.weighty = 1.0;
	  GridBagConstraints valueConstraints = new GridBagConstraints();
	  valueConstraints.fill = GridBagConstraints.HORIZONTAL;
	  valueConstraints.gridwidth = GridBagConstraints.REMAINDER;
	  valueConstraints.gridheight = 1;
	  valueConstraints.weightx = 50.0;
	  valueConstraints.weighty = 1.0;

	  // here add labels and components
	  int i,length = editors.length;
	  for (i=0; i<length; i++)
	    {
	      String name = descriptors[i].getDisplayName();
	      Label label = new Label (name + ":", Label.RIGHT);
	      editGridBag.setConstraints(label,labelConstraints);
	      editPanel.add(label);
	      Component component = editorComponents[i];
	      editGridBag.setConstraints(component,valueConstraints);
	      editPanel.add(component);
	    }
	  
	  add("Center",editPanel);
	}
    } catch (Exception e)
      {
	e.printStackTrace();
	System.exit(0);
      }
  }
  
  private void gatherEditorsForBean()
  {
    PropertyDescriptor[] pds = null;
    try
      {
	BeanInfo info = Introspector.getBeanInfo(elementClass);
	pds = info.getPropertyDescriptors();
      }
    catch (IntrospectionException ex)
      {
	Trace.exception(ex);
      }
    Vector editorVector = new Vector();
    Vector editorComponentVector = new Vector();
    Vector propertyDescriptorVector = new Vector();

    for (int i = 0; i < pds.length; i++)
      {          
	Class  propertyType  = pds[i].getPropertyType();
	Method propertyRead  = pds[i].getReadMethod();
	Method propertyWrite = pds[i].getWriteMethod();

	if (propertyRead != null && propertyWrite != null &&
	    !pds[i].isHidden())
	  {
	    Class editorClass = pds[i].getPropertyEditorClass();
	    PropertyEditor propertyEditor = null;
	    if (editorClass != null)
	      {
		try
		  {
		    propertyEditor = (PropertyEditor)editorClass.newInstance();
		  }
		catch (Exception e)
		  {
		    Trace.exception(e);
		  }
	      }
	    if (propertyEditor == null)
	      propertyEditor = PropertyEditorManager.findEditor (propertyType);
	    if (propertyEditor != null)
	      {
		propertyEditor.addPropertyChangeListener(this);
		if (propertyEditor.isPaintable() && propertyEditor.supportsCustomEditor())
		  {
		    // editorVector.addElement(editor);
		    // propertyDescriptorVector.addElement(pds[i]);
		    // editorComponentVector
		    //  .addElement(new PropertyLauncher(frame, editor, propertyRead, bean));
		  }
		else if (propertyEditor.getTags() != null)
		  {
		    editorVector.addElement(propertyEditor);
		    propertyDescriptorVector.addElement(pds[i]);
		    editorComponentVector.addElement(new PropertyChoice(propertyEditor));
		  }
		else if (propertyEditor.getAsText() != null)
		  {
		    editorVector.addElement(propertyEditor);
		    propertyDescriptorVector.addElement(pds[i]);
		    editorComponentVector.addElement(new PropertyTextField(propertyEditor));
		  }
	      }
	  } 
      }
    editors = new PropertyEditor[editorVector.size()];
    editorComponents = new Component[editors.length];
    descriptors = new PropertyDescriptor[editors.length];
    editorVector.copyInto(editors);
    editorComponentVector.copyInto(editorComponents);
    propertyDescriptorVector.copyInto(descriptors);
  }
  
  
  @Override
  public void actionPerformed(ActionEvent event)
  {
    Object object_target = event.getSource();
    
    if (object_target.equals(newArgumentButton))
      {
	int count = list.getItemCount();
	Object newElement = getNewElement();
	vector.addElement(newElement);
	list.add(newElement.toString());          
	list.select(count);
	showSelection(count,true);
	enableEdits();
	
	support.firePropertyChange("",null,null);
	return;
      }
    if (object_target.equals(deleteArgumentButton))
      {
	int count = list.getItemCount();
	if (count > 0)
	  {
	    int index = list.getSelectedIndex();
	    list.remove(index);
	    vector.removeElementAt(index);
	    int newIndex = (index == 0) ? 0 : (index - 1);
	    list.select(newIndex);
	    if (!vector.isEmpty())
	      showSelection(newIndex, true);
	  }
	if (count <= 1) 
	  {
	    disableEdits();
	  }
	support.firePropertyChange("",null,null);
	return;
      }
  }
  
  /** Override this for a subclass of VectorEditor so that
   * items of the type you would like are created by the New
   * button 
   */
  protected abstract Object getNewElement();
  
  /** Override this for a subclass of VectorEditor if you plan
   * to use a subclass of vector 
   */
  protected abstract Vector getNewVector();
  
  
  protected abstract boolean treatElementAsProperty(Object element);
  
  // Other customizable things to add
  // i) filtering changes to obects
  // ii) default filter to prevent those which are 
  // equals
  
  @Override
  public void itemStateChanged(ItemEvent event)
  {
    enableEdits();
    Object objectTarget = event.getSource();
    // System.out.println("item event="+event+" on "+objectTarget);
    
    if (objectTarget.equals(list))
      {
        showSelection(list.getSelectedIndex(),true);
      }
  }
  
  
  
  @Override
  public void setValue(Object o)
  {
    Vector temp = (Vector) o;
    vector = (Vector) (temp.clone());
    
    list.removeAll();
    
    int length = vector.size();
    for (int i = 0 ; i<length ; i++)
      {
	list.add(vector.elementAt(i).toString());
      }
    if (length > 0)
      {
	list.select(0);
	enableEdits();
	showSelection(0,true);
      }
    else
      {
	disableEdits();
      }
  }
  @Override
  public void setAsText(String s) throws java.lang.IllegalArgumentException 
  {}
  
  @Override
  public Object getValue() {
    return vector;
  }
  
  @Override
  public boolean isPaintable() {
    return true;
  }
  
  @Override
  public void paintValue(java.awt.Graphics gfx, java.awt.Rectangle box) {
    Color oldColor = gfx.getColor();
    Font oldFont = gfx.getFont();
    gfx.setColor(Color.white);
    gfx.fillRect(box.x+1, box.y+1, box.width-4, box.height-4);
    gfx.setColor(Color.black);
    gfx.drawRect(box.x, box.y, box.width-3, box.height-3);
    gfx.setFont(new Font("Courier",Font.PLAIN,12));
    FontMetrics metrics = gfx.getFontMetrics();
    gfx.drawString(vector.toString(),box.x+4,box.y+3+metrics.getAscent());
    gfx.setColor(oldColor);
    gfx.setFont(oldFont);
  }
  
  @Override
  public String getJavaInitializationString()
  {
    return "<missing initialization string";
  }   
  
  @Override
  public String getAsText() {
    return "foo(1,2,3)";
  }
  
  @Override
  public String[] getTags() {
    return null;
  }
  
  @Override
  public java.awt.Component getCustomEditor() 
  {
    return this;
  }
  
  @Override
  public boolean supportsCustomEditor()
  {
    return true;
  }
  
  @Override
  public void addPropertyChangeListener(PropertyChangeListener l) 
  {
    support.addPropertyChangeListener(l);
  }
  
  @Override
  public void removePropertyChangeListener(PropertyChangeListener l) 
  {
    support.removePropertyChangeListener(l);
  }
  
  protected void showSelection(int index, boolean reshow)
  {
    if (reshow) {
      // Launch the property editor on the selected object
      Object selection = vector.elementAt(index);
      
      //System.out.println("showSel index="+index+" sel="+selection);
      cachedIndex = index;
      if (elementIsAtomic)
	{
	  editor.setValue(selection);
	  if (editorComponent instanceof Resetable)
	    ((Resetable)editorComponent).reset();
	}
      else
	{
	  int i,length = editors.length;
	  for (i=0; i<length ; i++)
	    {
	      PropertyEditor propertyEditor = editors[i];
	      Method propertyRead  = descriptors[i].getReadMethod();
	      Component component = editorComponents[i];
	      
	      try {
		propertyEditor.setValue(propertyRead.invoke(selection, 
							    new Object[] {}));
	      } catch (Exception e)
		{
		  Trace.exception(e);
		}
	      if (component instanceof Resetable)
		((Resetable)component).reset();
	    }
	  
	}
    }
  }
  
  
  protected void hideSelection() {
    properties.dispose();  
  }
  
  private Frame findParentFrame() {
    Component component;
    
    component = getParent();
    while ((component != null) && (! (component instanceof Frame))) {
      component = component.getParent();
    }
    return (Frame) component;
  }
  
  private void enableEdits() {
    if (editArgumentButton != null)
      editArgumentButton.setEnabled(true);    
    deleteArgumentButton.setEnabled(true);
    if (elementIsAtomic)
      editorComponent.setEnabled(true);
    else
      for (int i = 0; i< editorComponents.length ; i++)
	editorComponents[i].setEnabled(true);
  }
  
  
  private void disableEdits() {
    if (editArgumentButton != null)
      editArgumentButton.setEnabled(false);    
    deleteArgumentButton.setEnabled(false);    
    if (elementIsAtomic)
      editorComponent.setEnabled(false);
    else
      for (int i = 0; i< editorComponents.length ; i++)
	editorComponents[i].setEnabled(false);
  }
  

  // Window events

  @Override
  public void windowOpened(WindowEvent e)
  {
  }
  
  @Override
  public void windowClosing(WindowEvent e)
  {
    
  }
  
  @Override
  public void windowClosed(WindowEvent e)
  {
    if ((cachedIndex > -1) && cachedIndex < vector.size() &&
	cachedIndex < list.getItemCount()) {
      Object val = vector.elementAt(cachedIndex); 
      list.replaceItem(val.toString(),cachedIndex);
      list.select(cachedIndex);
      enableEdits();
      support.firePropertyChange("",null,null);
    }
  }
  
  @Override
  public void windowIconified(WindowEvent e)
  {
  }
  
  @Override
  public void windowDeiconified(WindowEvent e)
  {
  }
  
  @Override
  public void windowActivated(WindowEvent e)
  {
  }
  
  @Override
  public void windowDeactivated(WindowEvent e)
  {
  }
  
  // Property change events 
  
  @Override
  public void propertyChange(PropertyChangeEvent evt)
  {
    if (evt.getSource() instanceof PropertyEditor)
      {
	PropertyEditor propertyEditor = (PropertyEditor) evt.getSource();
	Object value = propertyEditor.getValue();
	
	if ((cachedIndex > -1) && (cachedIndex < vector.size())) 
	  {
	    if (elementIsAtomic)
	      {
		vector.setElementAt(value,cachedIndex);
		list.replaceItem(value.toString(),cachedIndex);
	      }
	    else
	      {
		Object element = vector.elementAt(cachedIndex);
		int i,length = editors.length;
		for (i=0; i<length ; i++)
		  if (propertyEditor.equals(editors[i]))
		    break;
		Method propertyWrite = descriptors[i].getWriteMethod();
		try {
		  propertyWrite.invoke(element,new Object[] { value });
		} catch (Exception e)
		  {
		    Trace.exception(e);
		  }
		list.replaceItem(element.toString(),cachedIndex);
	      }
	    list.select(cachedIndex);
	    support.firePropertyChange("",null,null);
	  }
      }
  }
}       
