package com.gensym.classes;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.*;

import java.awt.*;
import java.lang.*;
import java.net.MalformedURLException;
import java.util.Vector;

public class ItemG2ProxyStub extends G2__BaseImpl implements ItemG2Proxy {
    private Symbol internalG2ClassName;

    public ItemG2ProxyStub(G2Access access, int handle, int handleVersion, G2__BaseImpl baseImpl, Structure attributes) {
    }

    @Override
    public java.lang.Object getPropertyValue(Symbol attrName) throws G2AccessException, NoSuchAttributeException {
        return null;
    }

    @Override
    public void setPropertyValue(Symbol attrName, java.lang.Object newValue) throws G2AccessException {

    }

    @Override
    public Sequence getVisibleAttributes(Symbol userMode) throws G2AccessException {
        return null;
    }

    @Override
    public Structure getAttributeValues(Sequence attrNames) throws G2AccessException {
        return null;
    }

    @Override
    public Sequence getAttributeDescriptions() throws G2AccessException {
        return null;
    }

    @Override
    public Sequence getAttributeDescriptions(Sequence specificAttributes) throws G2AccessException {
        return null;
    }

    @Override
    public void processItemEvent(ItemEvent e) {

    }

    @Override
    public boolean isLocallyCached() {
        return false;
    }

    @Override
    public void setLocallyCached(boolean cacheLocally) {

    }

    @Override
    public Structure getDialog(Symbol userMode, Structure locale) throws G2AccessException, MalformedURLException {
        return null;
    }

    @Override
    public java.lang.Object getCachedAttributeValue(Symbol attrName, java.lang.Object defaultValue) {
        return null;
    }

    @Override
    public boolean isItemLocal() {
        return false;
    }

    @Override
    public boolean isInstanceOfG2Class(Symbol g2ClassName_) {
        return false;
    }

    @Override
    public G2Definition getDefinition() throws G2AccessException {
        return null;
    }

    @Override
    public void startMethod(Symbol methodName, java.lang.Object[] args) throws G2AccessException {

    }

    @Override
    public java.lang.Object callMethod(Symbol methodName, java.lang.Object[] args, int timeOut) throws G2AccessException {
        return null;
    }

    @Override
    public Sequence getItemConfigurationSnapshot() throws G2AccessException {
        return null;
    }

    @Override
    public Symbol getConnectionStyleSnapshot() {
        return null;
    }

    @Override
    public Vector getCompleteConfigurationSnapshot() throws G2AccessException {
        return null;
    }

    @Override
    public boolean isValid() {
        return false;
    }

    @Override
    public void setAttributeWritesAreCached(boolean status) {

    }

    @Override
    public boolean isAttributeWritesCached() {
        return false;
    }

    @Override
    public void flushAttributeWriteCache() throws G2AccessException {

    }

    @Override
    public Symbol getG2ClassName() throws G2AccessException {
        return null;
    }

    @Override
    public Symbol getFoundationClass() throws G2AccessException {
        return null;
    }

    @Override
    public String getUuid() throws G2AccessException {
        return null;
    }

    @Override
    public void setUuid(String uuid) throws G2AccessException {

    }

    @Override
    public Rectangle getBounds() throws G2AccessException {
        return null;
    }

    @Override
    public void setBounds(int left, int top, int right, int bottom) throws G2AccessException {

    }

    @Override
    public Sequence getContainmentHierarchy() throws G2AccessException {
        return null;
    }

    @Override
    public Sequence getCurrentUserMenuChoices(Symbol userMode) throws G2AccessException {
        return null;
    }

    @Override
    public boolean getTransient() throws G2AccessException {
        return false;
    }

    @Override
    public boolean getManuallyDisabled() throws G2AccessException {
        return false;
    }

    @Override
    public void setManuallyDisabled(boolean manuallyDisabled) throws G2AccessException {

    }

    @Override
    public boolean getPermanent() throws G2AccessException {
        return false;
    }

    @Override
    public boolean getDoNotStripTextMark() throws G2AccessException {
        return false;
    }

    @Override
    public void setDoNotStripTextMark(boolean doNotStripTextMark) throws G2AccessException {

    }

    @Override
    public boolean getStripTextMark() throws G2AccessException {
        return false;
    }

    @Override
    public void setStripTextMark(boolean stripTextMark) throws G2AccessException {

    }

    @Override
    public Symbol getRepresentationType() throws G2AccessException {
        return null;
    }

    @Override
    public String getTableHeader() throws G2AccessException {
        return null;
    }

    @Override
    public int getItemWidth() throws G2AccessException {
        return 0;
    }

    @Override
    public int getItemHeight() throws G2AccessException {
        return 0;
    }

    @Override
    public int getItemYPosition() throws G2AccessException {
        return 0;
    }

    @Override
    public int getItemXPosition() throws G2AccessException {
        return 0;
    }

    @Override
    public void addItemListener(ItemListener il) throws G2AccessException {

    }

    @Override
    public void removeItemListener(ItemListener il) throws G2AccessException {

    }

    @Override
    public void removeItemListenerForThreeTiers(ItemListener l, Sequence subscriptionHandles) throws G2AccessException {

    }

    @Override
    public Sequence addItemListenerRetrievingStateMultiple(ItemListener l, Sequence denotation_sequences) throws G2AccessException {
        return null;
    }

    @Override
    public void removeItemListener(ItemListener il, Symbol[] attributeNames) throws G2AccessException {

    }

    @Override
    public void addItemListener(ItemListener il, Symbol[] attributeNames) throws G2AccessException {

    }

    @Override
    public void restoreNormalSize() throws G2AccessException {

    }

    @Override
    public boolean transferOff() throws G2AccessException {
        return false;
    }

    @Override
    public boolean transferToItem(Item targetItem, Symbol attributeName, Symbol classQualifier) throws G2AccessException {
        return false;
    }

    @Override
    public boolean transferTo(Item targetItem, Symbol attributeName, Symbol classQualifier) throws G2AccessException {
        return false;
    }

    @Override
    public boolean transferToWorkspace(KbWorkspace wksp, int x, int y) throws G2AccessException {
        return false;
    }

    @Override
    public boolean transferTo(KbWorkspace wksp, int x, int y) throws G2AccessException {
        return false;
    }

    @Override
    public Sequence retrieveCurrentUserMenuChoices() throws G2AccessException {
        return null;
    }

    @Override
    public boolean isProprietaryThroughContainment() throws G2AccessException {
        return false;
    }

    @Override
    public boolean moveByForVB(int xDelta, int yDelta, int pseudoBooleanEnlargeWorkspaceIfNecessary) throws G2AccessException {
        return false;
    }

    @Override
    public boolean moveBy(int xDelta, int yDelta, boolean enlargeWorkspaceIfNecessary) throws G2AccessException {
        return false;
    }

    @Override
    public boolean moveForVB(int x, int y, int pseudoBooleanEnlargeWorkspaceIfNecessary) throws G2AccessException {
        return false;
    }

    @Override
    public boolean move(int x, int y, boolean enlargeWorkspaceIfNecessary) throws G2AccessException {
        return false;
    }

    @Override
    public Item g2Clone() throws G2AccessException {
        return null;
    }

    @Override
    public void dropToBottom() throws G2AccessException {

    }

    @Override
    public void liftToTop() throws G2AccessException {

    }

    @Override
    public void makeTransient() throws G2AccessException {

    }

    @Override
    public void makePermanent() throws G2AccessException {

    }

    @Override
    public boolean isEnabled() throws G2AccessException {
        return false;
    }

    @Override
    public void disable() throws G2AccessException {

    }

    @Override
    public void enable() throws G2AccessException {

    }

    @Override
    public void deleteForVB(int pseudoBooleanWithPermanencyChecksDisabled, int pseudoBooleanWithoutLeavingStubs) throws G2AccessException {

    }

    @Override
    public void delete(boolean withPermanencyChecksDisabled, boolean withoutLeavingStubs) throws G2AccessException {

    }

    @Override
    public void setInternalG2ClassName(Symbol g2ClassNameIn) {
        this.internalG2ClassName = g2ClassNameIn;
    }

    public Symbol getInternalG2ClassName() {
        return this.internalG2ClassName;
    }
}
