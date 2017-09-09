package com.gensym.classes;

import com.gensym.jgi.G2AccessException;
import com.gensym.util.ItemListener;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

public class ItemG2ProxyStubWithoutConstructor extends G2__BaseImpl implements ItemG2Proxy {
    @Override
    public String getUuid() throws G2AccessException {
        return null;
    }

    @Override
    public void setUuid(String uuid) throws G2AccessException {

    }

    @Override
    public Symbol getFoundationClass() throws G2AccessException {
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
    public Symbol getG2ClassName() throws G2AccessException {
        return null;
    }
}
