package com.gensym.tests;

import sun.beans.editors.NumberEditor;
import java.beans.PropertyEditorSupport;

public synchronized class G2DateEditor extends NumberEditor
{
    public void setAsText(String string)
        throws IllegalArgumentException
    {
        setValue(Integer.valueOf(string));
    }

    public G2DateEditor()
    {
    }
}

