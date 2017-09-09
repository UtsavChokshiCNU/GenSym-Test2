/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	UiSelectionEvent.java
 *
 *   Modifications:
 *
 */
/**
 *
 * This class is used to pass data from one gui component to another
 *
 */
package com.gensym.cdggui.ui;

import java.awt.Event;
import java.util.Hashtable;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;


public class UiSelectionEvent extends java.awt.Event implements java.io.Serializable {

    public static String SELECTED_OBJECT = "SELECTED OBJECT";
    public static String SINGLE_SELECTION = "SINGLE SELECTION";

    public static int NONE = 0;
    public static int SINGLE = 1;
    public static int MULTIPLE = 2;
    public static int UNKNOWN = 128;
    public static int ERROR = 256;


    private Hashtable data;

    public Hashtable getData() {
        return data;
    }



    public int getSelectionStatus()
    {
        if(data==null)
        {
            return UNKNOWN;
        }
        else if (isTrue(SINGLE_SELECTION) && get(SELECTED_OBJECT)!=null )
        {
            return SINGLE;
        }
        else if (isTrue(SINGLE_SELECTION) && get(SELECTED_OBJECT)==null )
        {
            return NONE;
        }
        else if ( !isTrue(SINGLE_SELECTION) && get(SELECTED_OBJECT)!=null )
        {
            return MULTIPLE;
        }
        else if ( !isTrue(SINGLE_SELECTION) && get(SELECTED_OBJECT)==null )
        {
            return NONE;
        }
        else
        {
            return UNKNOWN;
        }

    }


    public void setData(Hashtable newData) {
        data = newData;
    }



    public void setSelectedObject(Object obj)
    {
        put(SELECTED_OBJECT,obj);
        putBoolean(SINGLE_SELECTION,true);
    }


    public Object getSelectedObject()
    {

        return get(SELECTED_OBJECT);
    }



    public void setSelectedObjects(Sequence objs)
    {
        put(SELECTED_OBJECT,objs);
        putBoolean(SINGLE_SELECTION,false);
    }


    public Sequence getSelectedObjects()
    {
        return getSequence(SELECTED_OBJECT);
    }



    public synchronized boolean containsKey(Object key) {
        return data.containsKey(key);
    }

    public synchronized boolean contains(Object value) {
        return data.contains(value);
    }

    public synchronized void clear() {
        data.clear();
    }

    public synchronized Object get(Object key) {
        return data.get(key);
    }


    public synchronized Object put(Object key, Object value) {
        if(key==null)
        System.out.println("null key");
        if(value==null)
        System.out.println("null value");

        return data.put(key, "");//was null
    }

    public synchronized Object remove(Object key) {
        return data.remove(key);
    }

    public int size() {
        return data.size();
    }



    public void putBoolean(String key , boolean value) {
        data.put(key, new Boolean(value));
    }




    public boolean isTrue(String key) {
        Boolean B1 = new Boolean (false);
        if (data.containsKey(key)) {
            B1 = (Boolean) data.get(key);
        }
        return B1.booleanValue();
    }

    public String getString(String key) {
        String s = "";
        if (data.containsKey(key)) {
            s = (String) data.get(key);
        }
        return s;
    }


    public Symbol getSymbol(String key) {
        Symbol s = null;
        if (data.containsKey(key)) {
            s = (Symbol) data.get(key);
        }
        return s;
    }


    public Sequence getSequence(String key) {
        Sequence s = null;
        if (data.containsKey(key)) {
            s = (Sequence) data.get(key);
        }
        return s;
    }


    public Hashtable getHashtable(String key) {
        Hashtable s = null;
        if (data.containsKey(key)) {
            s = (Hashtable) data.get(key);
        }
        return s;
    }



    // symbol keyed variants

    public void putBoolean(Symbol key , boolean value) {
        data.put(key, new Boolean(value));
    }


    public boolean isTrue(Symbol key) {
        Boolean B1 = new Boolean (false);
        if (data.containsKey(key)) {
            B1 = (Boolean) data.get(key);
        }
        return B1.booleanValue();
    }

    public String getString(Symbol key) {
        String s = "";
        if (data.containsKey(key)) {
            s = (String) data.get(key);
        }
        return s;
    }


    public Symbol getSymbol(Symbol key) {
        Symbol s = null;
        if (data.containsKey(key)) {
            s = (Symbol) data.get(key);
        }
        return s;
    }





    public Sequence getSequence(Symbol key) {
        Sequence s = null;
        if (data.containsKey(key)) {
            s = (Sequence) data.get(key);
        }
        return s;
    }

    public Hashtable getHashtable(Symbol key) {
        Hashtable s = null;
        if (data.containsKey(key)) {
            s = (Hashtable) data.get(key);
        }
        return s;
    }





    //special object keyed
    public Symbol getSymbol(Object key) {
        Symbol s = null;
        if (data.containsKey(key)) {
            s = (Symbol) data.get(key);
        }
        return s;
    }


    //default constructer
    public UiSelectionEvent(Object source , int i , Object arg) {
        super(source, i , arg);

        data=(Hashtable)arg;
    }
}
