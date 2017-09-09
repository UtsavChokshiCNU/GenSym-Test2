package com.gensym.beansruntime;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.beans.*;
import java.lang.reflect.*;
import com.gensym.dlg.TabGroupPanel;
import com.gensym.core.util.QuickSorter;
import com.gensym.message.Trace;

public class BeanSheet extends Dialog implements WindowListener, PropertyChangeListener
{   
  private Object             bean;
  private Frame              frame;
  private Panel              propPanel  = new Panel();
  private TabGroupPanel      tabPanel   = new TabGroupPanel();
  private GridBagLayout      gridLayout = new GridBagLayout();
  private Panel              gridPanel  = new Panel();
  private PropertyDescriptor props[];
  private PropertyEditor     editors[];
  private int                maxEditors = 15;
  private int                perPanel = 0;
  private int                numPages = 1;
  private Vector             launchers = new Vector();
  
  public BeanSheet(Object newBean, Frame newFrame, int x, int y)
  {
    super (newFrame, "Properties", true);
    frame = newFrame;
    bean = newBean;
    String name = newBean.getClass().getName();
    int index = name.lastIndexOf('.');
    setTitle(name.substring(index+1)+" Properties");
    try
      {
	BeanInfo info = Introspector.getBeanInfo(bean.getClass());
	props = info.getPropertyDescriptors();
	QuickSorter qs = 
	  new QuickSorter ()
	  {
	    @Override
	    public boolean lessThan(Object a, Object b)
	      {
		PropertyDescriptor p1 = (PropertyDescriptor) a;
		PropertyDescriptor p2 = (PropertyDescriptor) b;
		return p1.getName().toUpperCase().
		  compareTo(p2.getName().toUpperCase()) < 0;
	      }
	  };
	qs.quickSortInPlace(props);
      }
    catch (IntrospectionException ex)
      {
	Trace.exception(ex);
      }

    // Set up the panel arrangement

    tabPanel.setBackground (Color.lightGray);
    tabPanel.addTab ("General", propPanel);
        
    gridPanel.setBackground (Color.lightGray);
    gridPanel.setLayout(gridLayout);
    GridBagConstraints constraints = new GridBagConstraints();
    constraints.fill    = GridBagConstraints.BOTH;
    constraints.anchor  = GridBagConstraints.CENTER;
    constraints.insets  = new Insets (10, 10, 10, 10);
    constraints.weightx = 10;
    constraints.weighty = 10;
    gridLayout.setConstraints (tabPanel, constraints);

    int count = 0;
    int size = 0;

    editors = new PropertyEditor[props.length];

    // Register custom editors
    try
      {
	PropertyEditorManager.registerEditor (java.awt.Font.class,
		     Class.forName ("com.gensym.uiutil.FontPanel"));
	PropertyEditorManager.registerEditor (java.awt.Color.class,
                     Class.forName ("com.gensym.uiutil.ColorEditor"));
      }
    catch (Exception e)
      {
	System.err.println (e);
	e.printStackTrace ();
      }

    for (int i = 0; i < props.length; i++)
      {          
	String propertyName  = props[i].getDisplayName();
	Class  propertyType  = props[i].getPropertyType();
	Method propertyRead  = props[i].getReadMethod();
	Method propertyWrite = props[i].getWriteMethod();

	if (propertyRead != null && propertyWrite != null &&
	    !props[i].isHidden() && 
	    (isPropertyDisplayable(props[i])))
	  {
	    // Setup the property editor for this property
	    Class editorClass = props[i].getPropertyEditorClass();

	    PropertyEditor editor = null;
	    if (editorClass != null)
	      {
		try
		  {
		    editor = (PropertyEditor)editorClass.newInstance();
		  }
		catch (Exception e)
		  {
		    Trace.exception(e);
		  }
	      }

	    // If the editor is still null, then try to find one
	    if (editor == null)
	      {
		editor = PropertyEditorManager.findEditor (propertyType);
	      }
	    if (editor != null)
	      {
		boolean good = true;
		try
		  {
		    Object value = propertyRead.invoke (bean, new Object[] {});
		    editor.setValue(value);
		  }
		catch (InvocationTargetException ite) {
		  Trace.exception(ite.getTargetException());
		  good = false;
		}
		catch (Exception e)
		  {
		    Trace.exception(e);
		    good = false;
		  }
		if (good)
		  {
		    editors[i] = editor;
		    count++;
		    perPanel++;
		    
		    if (perPanel > maxEditors)
		      {                                 
			propPanel.setLayout (new GridLayout (maxEditors, 2));
			numPages++;
			
			propPanel = new Panel();
			
			tabPanel.addTab ("General " + numPages, propPanel);
			perPanel = 1;
		      }
		    
		    
		    size = propertyName.length() > size ? propertyName.length() : size;
		    
		    propPanel.add (new Label (propertyName + ":    ", Label.RIGHT));
		    
		    if (editor.isPaintable() && editor.supportsCustomEditor())
		      {
			PropertyLauncher launcher = new PropertyLauncher(frame, editor, propertyRead, bean);
			propPanel.add(launcher);
			launchers.addElement(launcher);
		      }
		    else if (editor.supportsCustomEditor())
		      {
			Component editorComponent = editor.getCustomEditor();
			if (!(editorComponent instanceof Window))
			  propPanel.add(editorComponent);
		      }
		    else if (editor.getTags() != null)
		      {
			propPanel.add(new PropertyChoice(editor));
		      }
		    else if (editor.getAsText() != null)
		      {
			String init = editor.getAsText();
			propPanel.add(new PropertyTextField(editor));
		      }
		    
		    // Moved after editor component creation to get rid of all
		    // of the initial calls to the setter.
		    editor.addPropertyChangeListener(this);
		  } // end if good 
		
	      } // else (no editor) skipping property...

	  } // else (not visible) skipping property...

      }

    // We need to pad the panel with components on the last page
    if (numPages > 1)
      {
	for (int j = perPanel; j < maxEditors; j++)
	  {
	    propPanel.add(new Label(" "));
	  }
      }

    Insets insets = getInsets();
        
    propPanel.setLayout (new GridLayout (numPages > 1 ? maxEditors : perPanel, 2));
        
    gridPanel.add (tabPanel);     
    add ("Center", gridPanel);

    pack ();

    Point loc = frame.getLocation();
    setLocation (loc.x + x, loc.y + y);
    //setResizable(false);

    addWindowListener(this);
    show();
  }

  protected boolean isPropertyDisplayable(PropertyDescriptor prop){
    return true;
  }

  @Override
  public void propertyChange(PropertyChangeEvent evt)
  {
    if (evt.getSource() instanceof PropertyEditor)
      {
	PropertyEditor editor = (PropertyEditor) evt.getSource();
	Object value = editor.getValue();

	for (int i = 0; i < props.length; i++)
	  {
	    if (editor.equals(editors[i]))
	      {
			Method propertyWrite = props[i].getWriteMethod();
	
			try
			  {
			    propertyWrite.invoke(bean, new Object[] { value });
			    for (int j=0; j < launchers.size(); j++)
			      {
				((Canvas)launchers.elementAt(j)).repaint();
			      }
			  }
			catch (Exception e)
			  {
			    Trace.exception(e);
			  }
	
			continue; // drop out of the loop
	      }
	  }
      }
  }
 
  // Window events

  @Override
  public void windowOpened(WindowEvent e)
  {
  }

  @Override
  public void windowClosing(WindowEvent e)
  {
    Component focusOwner = getFocusOwner();
    if (focusOwner instanceof PropertyTextField)
      ((PropertyTextField)focusOwner).applyChanges();

    e.getWindow().dispose();
  }

  @Override
  public void windowClosed(WindowEvent e)
  {
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
}
