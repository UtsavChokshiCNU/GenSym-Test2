package com.gensym.core.util;

import java.util.Map;
import java.util.HashMap;
import java.beans.BeanInfo;
import java.beans.PropertyDescriptor;
import java.beans.Introspector;
import java.beans.IntrospectionException;

/**
 * After the descriptor is looked up using bean class and property name, 
 * this info is stored in a hash map. This will improve the performance 
 * of finding descpritor for the bean class and property name next time.	
 */
public class MemoizedBeanInfo {

  private MemoizedBeanInfo(){
  }

  private static final MemoizedBeanInfo MEMOIZED_BEAN_INFO = new MemoizedBeanInfo();

  public static MemoizedBeanInfo getMemoizedBeanInfo(){
    return MEMOIZED_BEAN_INFO;
  }


  Map beanClassToDescriptorsMap = new HashMap();

  Map createPropertyNameToDescriptorMap(Class beanClass, String propertyName)
  throws IntrospectionException {
    BeanInfo beanInfo = Introspector.getBeanInfo(beanClass);
    PropertyDescriptor[] descriptors = beanInfo.getPropertyDescriptors();
    Map propertyNameToDescriptorMap = new HashMap();
    if(descriptors != null){
      for(int i = 0; i < descriptors.length; i++){
        propertyNameToDescriptorMap.put(descriptors[i].getName(), descriptors[i]);
      }
    }
    return propertyNameToDescriptorMap;
  }

  public PropertyDescriptor getDescriptor(Class beanClass, String propertyName)
  throws IntrospectionException {
    Map propertyNameToDescriptorMap = (Map)beanClassToDescriptorsMap.get(beanClass);
    if (propertyNameToDescriptorMap == null){
      propertyNameToDescriptorMap = createPropertyNameToDescriptorMap(beanClass, propertyName);
      beanClassToDescriptorsMap.put(beanClass, propertyNameToDescriptorMap);
    }
    return (PropertyDescriptor)propertyNameToDescriptorMap.get(propertyName);
  }


}

