package com.gensym.gda.queues;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import java.util.Enumeration;

public class MessageBrowserFilter extends Object 
{
    private int index;
    private Sequence attributeNames;
    private Sequence attributeValues;
    private Sequence workingValues;
    private boolean state;
    private boolean orFilter;
    private boolean editable;
    private Symbol groupName;
    private String objectFilterSubclass;

    public MessageBrowserFilter (int ind, Sequence attrNames,
                                Sequence attrValues, boolean filter, boolean orFil, Symbol grp) 
   {
        index = ind;
        attributeNames = attrNames;
        attributeValues = attrValues;
        state = filter;
        orFilter = orFil;
        workingValues = attrValues;
        groupName = grp;
        objectFilterSubclass = "";
    }

    public void setObjectFilterSubclass (String subclass) 
    {
       objectFilterSubclass = subclass;
    }
    
    public String getObjectFilterSubclass () 
    {
      return objectFilterSubclass;
    }
    
    public Symbol getGroupName () 
    {
      return groupName;
    }

    public void setState (boolean newState) 
    {
        state = newState;
    }

    public int getIndex () 
    {
        return index;
    }

    public Sequence getAttributeNames () 
    {
        return attributeNames;
    }

    public Sequence getAttributeValues () 
    {
        return attributeValues;
    }

    public void setAttributeValues(Sequence newVal) 
    {
        attributeValues = newVal;
    }

    public Sequence getWorkingValues () 
    {
        return workingValues;
    }

    public void setWorkingValues(Sequence newVal) 
    {
        workingValues = newVal;
    }

    public boolean getState () 
    {
        return state;
    }

    public boolean isFilterOR () 
    {
        return orFilter;
    }

    public boolean isEditable ()
    {
        return editable;
    }

    public void setEditable (boolean editable)
    {
        this.editable = editable;
    }

}

