
package com.gensym.classes;

import java.util.Vector;

import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.jgi.download.G2StubFactory;
import com.gensym.message.*;

public class DeferredStub implements Item {
  Symbol className;
  int handle;
  G2Access context;
  Structure attributes;
  int handleVersion;

  public DeferredStub (G2StubFactory fac,
		       Symbol className,
		       int handle,
		       G2Access context,
		       Structure attributes) {
    this.context = context;
    this.handle = handle;
    this.className = className;
    this.attributes = attributes;
    this.handleVersion = fac.getVersionForHandle (handle);
  }

  public Item resolve (G2StubFactory fac) {
    boolean newlyCreated = false;
    Item itm = fac.checkExistingStub (handle, handleVersion);
    if (itm == null) {
      newlyCreated = true;
      itm = fac.createG2Stub (className, handle, handleVersion, context, attributes);
    }
    //System.out.println ("DS: Resolved " + this + " -> " + itm + (newlyCreated ? " NEW " : " DELETED ")); System.out.flush ();
    if (((G2__BaseImpl)itm).getHandleVersion () != handleVersion)
	System.err.println ("Error! Resolved " + this + " to " + itm + ". Please report to Customer Support.");
    return itm;
  }

  /**
   * Does not copy attributes...for fast attributed StubResolution.
   */
  public Structure getAttributes () {return attributes;}

  public java.lang.Object getAttributeValue (Symbol attrName) {return null;}
  @Override
  public java.lang.Object getCachedAttributeValue(Symbol attrName, java.lang.Object defaultValue) {
    return attributes.getAttributeValue(attrName, defaultValue);
  }
  public Class getG2Class () {return null;}
  public Symbol getName () {return null;}
  @Override
  public boolean getTransient () {return true;}
  @Override
  public boolean getPermanent () {return false;}
  @Override
  public boolean getManuallyDisabled() {return false;}
  @Override
  public Symbol getRepresentationType () {return null;}
  @Override
  public String getTableHeader() {return null;}
  @Override
  public int getItemXPosition () {return 0;}
  @Override
  public int getItemYPosition () {return 0;}
  @Override
  public int getItemWidth () {return 0;}
  @Override
  public int getItemHeight () {return 0;}
  public Sequence  getClassAttributes () {return null;}
  public Sequence  getInstanceAttributes () {return null;}
  public Structure getTypeDescription (Symbol attrName) {return null;}
  @Override
  public com.gensym.util.Symbol getFoundationClass() {return null;}
  @Override
  public com.gensym.util.Symbol getG2ClassName() {return null;}
  @Override
  public void addItemListener(com.gensym.util.ItemListener il) {}
  @Override
  public void addItemListener (ItemListener il, Symbol[] attributeNames) throws G2AccessException {}
  @Override
  public Sequence addItemListenerRetrievingStateMultiple (ItemListener l, Sequence denotation_sequences) throws G2AccessException{return null;}
  @Override
  public void removeItemListener(com.gensym.util.ItemListener il) {}
  @Override
  public void removeItemListener (ItemListener il, Symbol[] attributeNames) throws G2AccessException {}
  @Override
  public void  removeItemListenerForThreeTiers(com.gensym.util.ItemListener l, Sequence subscriptionHandles) throws com.gensym.jgi.G2AccessException {}
  @Override
  public void processItemEvent(com.gensym.util.ItemEvent e) {}
  @Override
  public G2Definition getDefinition() {return null;}
  @Override
  public boolean isLocallyCached () {return false;}
  @Override
  public void setLocallyCached (boolean cacheLocally) {}
  @Override
  public java.lang.Object getPropertyValue (Symbol attrName) {return null;}
  @Override
  public void setPropertyValue (Symbol attrName, java.lang.Object newValue) {}
  @Override
  public Sequence getVisibleAttributes (Symbol userMode) {return null;}
  @Override
  public Structure getAttributeValues (Sequence attrNames) {return null;}
  @Override
  public Sequence getAttributeDescriptions (Sequence specificAttrs) {return null;}
  @Override
  public Sequence getAttributeDescriptions () {return null;}
  @Override
  public Structure getDialog (Symbol userMode, Structure locale) {return null;}
  @Override
  public boolean isInstanceOfG2Class(Symbol g2ClassName_) {return false;}
  @Override
  public boolean isItemLocal () {return false;}
  @Override
  public void delete (boolean withPermanencyChecksDisabled,
		      boolean withoutLeavingStubs) {}
  @Override
  public void deleteForVB (int pseudoBooleanWithPermanencyChecksDisabled,
			   int pseudoBooleanWithoutLeavingStubs) throws G2AccessException {}
  @Override
  public void enable () {}
  @Override
  public void disable () {}
  @Override
  public void makePermanent () {}
  @Override
  public void makeTransient () {}
  @Override
  public void liftToTop () {}
  @Override
  public void dropToBottom () {}
  @Override
  public Item g2Clone() throws G2AccessException {return null;}
  @Override
  public boolean move (int x, int y,
		       boolean enlargeWorkspaceIfNecessary)
       throws G2AccessException {return false;}
  @Override
  public boolean moveBy(int xDelta,int yDelta,
			boolean enlargeWorkspaceIfNecessary)
       throws G2AccessException {return false;}
  @Override
  public boolean moveByForVB (int xDelta,
			      int yDelta,
			      int pseudoBooleanEnlargeWorkspaceIfNecessary)
       throws G2AccessException {return false;}
  @Override
  public boolean moveForVB (int x,
			    int y,
			    int pseudoBooleanEnlargeWorkspaceIfNecessary)
       throws G2AccessException {return false;}
  @Override
  public Sequence getContainmentHierarchy()
       throws G2AccessException {return null;}
  @Override
  public Sequence getCurrentUserMenuChoices(Symbol userMode)
       throws G2AccessException {return null;}
  @Override
  public Sequence retrieveCurrentUserMenuChoices() {return null;}
  public boolean transfer(Item targetItem,
			  int x,
			  int y,
			  java.lang.Object attributeNameOrFalse,
			  java.lang.Object classQualifierOrFalse)
       throws G2AccessException {return false;}
  @Override
  public boolean isEnabled () {return true;}
  @Override
  public boolean transferTo (KbWorkspace wksp, int x, int y) {return false;}
  @Override
  public boolean transferTo (Item targetItem, Symbol attributeName, Symbol classQualifier) {return false;}
  @Override
  public boolean transferToItem (Item targetItem, Symbol attributeName, Symbol classQualifier) throws G2AccessException {return false;}
  @Override
  public boolean transferToWorkspace (KbWorkspace wksp, int x, int y) throws G2AccessException {return false;}
  @Override
  public boolean transferOff () {return false;}

  @Override
  public void setBounds(int left, int top, int right, int bottom) {}
  @Override
  public void restoreNormalSize() {}
  @Override
  public boolean isProprietaryThroughContainment () {return false;}
  @Override
  public Sequence getItemConfigurationSnapshot() {return null;}
  @Override
  public Symbol getConnectionStyleSnapshot() {return null;}
  @Override
  public boolean isValid() {return false;}
  @Override
  public void startMethod (Symbol methodName, java.lang.Object[] args) {}
  @Override
  public java.lang.Object callMethod (Symbol methodName, java.lang.Object[] args, int timeOut) {return null;}
  @Override
  public java.awt.Rectangle getBounds() {return null;}
  public com.gensym.util.Structure addItemListenerRetrievingState(com.gensym.util.ItemListener il) {return null;}
  public void dumpWkspItemList() {}
  @Override
  public String toString () {
    return super.toString () + "{# = " + handle + "v" + handleVersion + "}";
  }
  @Override
  public void setAttributeWritesAreCached(boolean status) {}
  @Override
  public boolean isAttributeWritesCached() { return false; }
  @Override
  public void flushAttributeWriteCache() throws G2AccessException {}
  @Override
  public Vector getCompleteConfigurationSnapshot() throws G2AccessException {return null;}
  @Override
  public java.lang.String getUuid() throws G2AccessException {return null;}
  @Override
  public void setUuid(java.lang.String s) throws G2AccessException {}
  @Override
  public void setManuallyDisabled(boolean b) throws G2AccessException {}
  @Override
  public boolean getDoNotStripTextMark() throws G2AccessException {return false;}
  @Override
  public void setDoNotStripTextMark(boolean b) throws G2AccessException {}
  @Override
  public boolean getStripTextMark() throws G2AccessException {return false;}
  @Override
  public void setStripTextMark(boolean b) throws G2AccessException {}
}
