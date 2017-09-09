
package com.gensym.classes;

/**
 * This interface is for friendly access only and is subject
 * to change without notification
 */
import com.gensym.util.Sequence;

public interface ImplAccess {

  public com.gensym.jgi.G2Access getContext ();

  public com.gensym.util.Structure getAttributes ();

  public java.awt.Rectangle getBounds () throws com.gensym.jgi.G2AccessException;

  public com.gensym.util.Structure addItemListenerRetrievingState (com.gensym.util.ItemListener l)
           throws com.gensym.jgi.G2AccessException;

  public com.gensym.util.Sequence addItemListenerRetrievingStateMultiple (com.gensym.util.ItemListener l, Sequence denotation_sequences)
           throws com.gensym.jgi.G2AccessException;

  public void removeItemListenerForThreeTiers(com.gensym.util.ItemListener l, Sequence subscriptionHandles)
           throws com.gensym.jgi.G2AccessException;

  public com.gensym.util.Structure getAttributeTexts (com.gensym.util.Sequence attributeNames)
           throws com.gensym.jgi.G2AccessException;

  public void addStubInvalidationListener(com.gensym.util.StubInvalidationListener listener);

  public void removeStubInvalidationListener(com.gensym.util.StubInvalidationListener listener);
}
