package com.gensym.beanbuilder;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;


/**
 * This is a utility class that can be used by beans that support bound
 * properties.  You can either inherit from this class or you can use
 * an instance of this class as a member field of your bean and delegate
 * various work to it.
 * <p>
 * This extension of the java.beans.PropertyChangeSupport class adds
 * functionality to handle individual property changes.
 *
 */
public class PropertyChangeSupport extends java.beans.PropertyChangeSupport implements java.io.Serializable
{
	/* 
	If we want to support non-serializable listeners we will have to
	implement the folowing functions and serialize out the listenerTable
	HashTable on our own.

    private void writeObject(ObjectOutputStream s) throws IOException
    private void readObject(ObjectInputStream s) throws ClassNotFoundException, IOException
    */

    /**
     * The listener list.
     * @see #addPropertyChangeListener
     * @see #removePropertyChangeListener
     */
    protected java.util.Hashtable listenerTable;
    private Object source;
    private int propertyChangeSupportSerializedDataVersion = 1;
    
    /**
     * Constructs a PropertyChangeSupport object.
     * @param sourceBean the bean to be given as the source for any events
     */
    public PropertyChangeSupport(Object sourceBean)
    {
		super(sourceBean);
		source = sourceBean;
    }

    /**
     * Adds a PropertyChangeListener to the listener list.
     *
     * @param propertyName the name of the property to add a listener for
     * @param listener the PropertyChangeListener to be added
     * @see #removePropertyChangeListener
     */
    @Override
    public synchronized void addPropertyChangeListener(String propertyName, PropertyChangeListener listener)
    {
    	java.util.Vector listenerList;

    	if(listenerTable == null)
    	{
    		listenerTable = new java.util.Hashtable();
    	}

    	if(listenerTable.containsKey(propertyName))
    	{
    		listenerList = (java.util.Vector)listenerTable.get(propertyName);
    	}
    	else
    	{
    		listenerList = new java.util.Vector();
    	}

    	listenerList.addElement(listener);
    	listenerTable.put(propertyName, listenerList);
    }

    /**
     * Removes a PropertyChangeListener from the listener list.
     *
     * @param propertyName the name of the property to remove a listener for
     * @param listener the PropertyChangeListener to be removed
     * @see #addPropertyChangeListener
     */
    @Override
    public synchronized void removePropertyChangeListener(String propertyName, PropertyChangeListener listener)
    {
    	java.util.Vector listenerList;

		if (listenerTable == null || !listenerTable.containsKey(propertyName))
		{
	    	return;
		}
		listenerList = (java.util.Vector)listenerTable.get(propertyName);
		listenerList.removeElement(listener);
    }

    /**
     * Report a bound property update to any registered listeners.
     * <p>
     * No event is fired if old and new are equal and non-null.
     *
     * @param propertyName the programmatic name of the property
     *		that was changed
     * @param oldValue the old value of the property
     * @param newValue the new value of the property
     */
    @Override
    public void firePropertyChange(String propertyName, Object oldValue, Object newValue)
    {
    	if (oldValue != null && oldValue.equals(newValue))
    	{
    		return;
		}

		super.firePropertyChange(propertyName, oldValue, newValue);

		java.util.Hashtable templistenerTable = null;

		synchronized (this)
		{
			if(listenerTable == null || !listenerTable.containsKey(propertyName))
			{
				return;
			}
		  	templistenerTable = (java.util.Hashtable) listenerTable.clone();
		}

		java.util.Vector listenerList;

		listenerList = (java.util.Vector)templistenerTable.get(propertyName);

	    PropertyChangeEvent evt = new PropertyChangeEvent(source, propertyName, oldValue, newValue);

		for (int i = 0; i < listenerList.size(); i++)
		{
			PropertyChangeListener target = (PropertyChangeListener)listenerList.elementAt(i);
		    target.propertyChange(evt);
		}
    }

}




