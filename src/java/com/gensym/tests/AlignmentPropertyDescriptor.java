
package com.gensym.tests;

import java.beans.*;
import java.util.*;

public class AlignmentPropertyDescriptor extends PropertyDescriptor {
  String[] names;
  int[] values;

  public AlignmentPropertyDescriptor (String propertyName, Class beanClass, String[] names, int[] values) throws IntrospectionException {
    super (propertyName, beanClass);
    this.names = names;
    this.values = values;
  }

  @Override
  public Class getPropertyEditorClass() {
    return AlignmentEditor.class;
  }

}
