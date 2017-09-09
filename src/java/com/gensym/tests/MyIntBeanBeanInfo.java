
package com.gensym.tests;

import java.beans.*;
import java.util.*;

public class MyIntBeanBeanInfo extends SimpleBeanInfo {

  static Class beanClass = MyIntBean.class;

  @Override
  public BeanDescriptor getBeanDescriptor() {
	return null;
  }

  @Override
  public PropertyDescriptor[] getPropertyDescriptors() {
    try {
      return new PropertyDescriptor[] {
	new PropertyDescriptor ("XAlignment", beanClass),
	new AlignmentPropertyDescriptor ("YAlignment", beanClass,
					 new String[] {"Left", "Center", "Right"},
					 new int[] {0, 1, 2})
      };
    } catch (Exception e) {
      e.printStackTrace ();
      return null;
    }
  }
  
}
