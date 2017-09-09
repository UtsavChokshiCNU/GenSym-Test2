
package com.gensym.jgi.download;

import com.gensym.classes.Item;
import com.gensym.jgi.G2Access;
import com.gensym.util.*;

/**
 * This interface defines a factory for G2 stubs. It is used by a G2Callbacks
 * in order to create com.gensym.classes.Item implementations corresponding
 * to G2 items that are passed through this interface.
 *
 * @author vkp
 * @version 1.0 09/15/1997
 * @see com.gensym.jgi.G2Callbacks
 */
public interface G2StubFactory {

  /**
   * Returns a <code>com.gensym.classes.Item</code> implemenatation instance 
   * for an item with handle <code>handle</code> passed through context<code>
   * context</code> and with attributes <code>attributes</code>.
   */
  Item createG2Stub (Symbol className,
		     int handle,
		     G2Access context,
		     Structure attributes);

  /**
   * Makes a specific stub version
   */
  Item createG2Stub (Symbol className,
		     int handle,
		     int handleVersion,
		     G2Access context,
		     Structure attributes);
  /**
   * Fill in comments
   */
  Item checkExistingStub (int handle, int handleVersion);
  /**
   * This is a notification from G2 that <code>handle</code> in <code>context
   * </code> has been invalidated.
   */
  void invalidateG2Stub (int handle,
			 G2Access context);

  /** 
   * Returns the G2 Stub that (may be) asscoiated with a given handle
   */
  Item getG2StubForHandle(int handle,
			  G2Access context);

  /**
   * Returns the ClassLoader used by this Factory
   */
  /*
   * Who uses this?
   */
  public StubClassLoader getStubClassLoader();

 /**
   * Invalidates the stub class loader for a connection (maybe a connection has died).
   */
  public void invalidateStubClassLoader(G2Access context);

  /**
   * Returns the next version for a handle
   */
  public int getVersionForHandle (int handle);
}
