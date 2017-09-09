package com.gensym.gda.controls;

import com.gensym.controls.AWTDerivedBeanInfo;
import java.awt.Image;
import java.awt.Toolkit;
import java.beans.*;

public class G2SpinFieldBeanInfo extends AWTDerivedBeanInfo
{

    public G2SpinFieldBeanInfo()
    {
        icon32x32 = Toolkit.getDefaultToolkit().getImage(getClass().getResource("g2radiobutton.gif"));
    }

    static Class class$(String s)
    {
        try
        {
            return Class.forName(s);
        }
        catch(ClassNotFoundException classnotfoundexception)
        {
            throw new NoClassDefFoundError(classnotfoundexception.getMessage());
        }
    }

    public Class getBeanClass()
    {
        return class$com$gensym$gda$controls$G2SpinField == null ? (class$com$gensym$gda$controls$G2SpinField= class$("com.gensym.gda.controls.G2SpinField")) : class$com$gensym$gda$controls$G2SpinField;
    }

    public Image getIcon(int i)
    {
        if(i == 2)
            return icon32x32;
        else
            return null;
    }

    protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertydescriptor)
    {
        String s = propertydescriptor.getName();
        if(s.equals("members"))
            propertydescriptor.setExpert(false);
        return propertydescriptor;
    }

    private Image icon32x32;
    static Class class$com$gensym$gda$controls$G2SpinField; /* synthetic field */
}
