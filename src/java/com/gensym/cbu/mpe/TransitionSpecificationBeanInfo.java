package com.gensym.cbu.mpe;

import java.beans.*;
import com.gensym.core.BaseModifiableBeanInfo;
import com.gensym.denali.common.EnumerationEditor;

public class TransitionSpecificationBeanInfo extends BaseModifiableBeanInfo
  implements TestTypes
{
  @Override
  protected Class getBeanClass()
  {
    return TransitionSpecification.class;
  }

  public static class TypeEditor extends EnumerationEditor
  {
    String[] labels = new String[] { "string", "any digit"};

    protected String[] getEnumerationLabels()
    { 
      return labels;
    }
    
    protected int lookupEnumerationLabel(String label)
    {
      if (label.equals("string"))
	return EQUAL;
      else if (label.equals("any digit"))
	return DIGIT;
      else
	throw new IllegalArgumentException("unknown label "+label);
    }
  }

  @Override
  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor)
  {
    String propertyName = propertyDescriptor.getName();
    if (propertyName.equals("testType"))
      propertyDescriptor.setPropertyEditorClass(TypeEditor.class);
    return propertyDescriptor;
  }

}
