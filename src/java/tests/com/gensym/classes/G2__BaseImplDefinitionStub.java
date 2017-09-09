package com.gensym.classes;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.*;

import java.lang.Object;

public class G2__BaseImplDefinitionStub extends G2__BaseImpl implements Definition {

    public Symbol g2ClassName = null;
    public Sequence classPathSequence = new Sequence();

    public G2__BaseImplDefinitionStub() { }

    public G2__BaseImplDefinitionStub(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes)
    {
        super(context, handle, handleVersion, wrap, attributes);
    }

    @Override
    public Symbol getG2ClassName() throws G2AccessException {
        return g2ClassName;
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
    public KbWorkspace getSubworkspace() throws G2AccessException {
        return null;
    }

    @Override
    public void setSubworkspace(KbWorkspace workspace) throws G2AccessException {

    }

    @Override
    public Sequence getAttributeDisplayItems() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public Object getNameBoxItem() throws G2AccessException {
        return null;
    }

    @Override
    public Structure getIconVariables() throws G2AccessException {
        return new Structure();
    }

    @Override
    public void setIconVariables(Structure iconVariables) throws G2AccessException {

    }

    @Override
    public Symbol getIconColor() throws G2AccessException {
        return null;
    }

    @Override
    public void setIconColor(Symbol iconColor) throws G2AccessException {

    }

    @Override
    public Symbol getIconReflection() throws G2AccessException {
        return null;
    }

    @Override
    public void setIconReflection(Symbol iconReflection) throws G2AccessException {

    }

    @Override
    public int getIconHeading() throws G2AccessException {
        return 0;
    }

    @Override
    public void setIconHeading(int iconHeading) throws G2AccessException {

    }

    @Override
    public Structure getItemColorPattern() throws G2AccessException {
        return null;
    }

    @Override
    public void setItemColorPattern(Structure itemColorPattern) throws G2AccessException {

    }

    @Override
    public Structure getSizeInWorkspace() throws G2AccessException {
        return null;
    }

    @Override
    public void setSizeInWorkspace(Structure sizeInWorkspace) throws G2AccessException {

    }

    @Override
    public Sequence getCurrentAttributeDisplays() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public void setCurrentAttributeDisplays(Sequence currentAttributeDisplays) throws G2AccessException {

    }

    @Override
    public Structure getNameBox() throws G2AccessException {
        return null;
    }

    @Override
    public void setNameBox(Structure nameBox) throws G2AccessException {

    }

    @Override
    public Symbol getStripeColor() throws G2AccessException {
        return null;
    }

    @Override
    public void setStripeColor(Symbol stripeColor) throws G2AccessException {

    }

    @Override
    public Symbol getBorderColor() throws G2AccessException {
        return null;
    }

    @Override
    public void setBorderColor(Symbol borderColor) throws G2AccessException {

    }

    @Override
    public Symbol getTextColor() throws G2AccessException {
        return null;
    }

    @Override
    public void setTextColor(Symbol textColor) throws G2AccessException {

    }

    @Override
    public Symbol getForegroundColor() throws G2AccessException {
        return null;
    }

    @Override
    public void setForegroundColor(Symbol foregroundColor) throws G2AccessException {

    }

    @Override
    public Symbol getBackgroundColor() throws G2AccessException {
        return null;
    }

    @Override
    public void setBackgroundColor(Symbol backgroundColor) throws G2AccessException {

    }

    @Override
    public Structure getIconDescriptionForClass() throws G2AccessException {
        return null;
    }

    @Override
    public Symbol reflectVertically() throws G2AccessException {
        return null;
    }

    @Override
    public Symbol reflectHorizontally() throws G2AccessException {
        return null;
    }

    @Override
    public void setBounds(int left, int top, int right, int bottom) throws G2AccessException {

    }

    @Override
    public Sequence getContainmentHierarchy() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public Sequence getCurrentUserMenuChoices(Symbol userMode) throws G2AccessException {
        return new Sequence();
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
        return new Sequence();
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
    public Sequence getSystemClassInheritancePath() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public void setSystemClassInheritancePath(Sequence newClassInhPath) {

    }

    @Override
    public Object getClassAttributeValue(Symbol attrName) throws G2AccessException {
        return null;
    }

    @Override
    public Structure getAuthors() throws G2AccessException {
        return new Structure();
    }

    @Override
    public void setAuthors(Structure authors) throws G2AccessException {

    }

    @Override
    public Sequence getChangeLog() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public Symbol getClassName() throws G2AccessException {
        return g2ClassName;
    }

    @Override
    public void setClassName(Symbol className) throws G2AccessException {

    }

    @Override
    public Sequence getDirectSuperiorClasses() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public void setDirectSuperiorClasses(Sequence directSuperiorClasses) throws G2AccessException {

    }

    @Override
    public Sequence getClassSpecificAttributes() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public void setClassSpecificAttributes(Sequence classSpecificAttributes) throws G2AccessException {

    }

    @Override
    public Sequence getInstanceConfiguration() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public void setInstanceConfiguration(Sequence instanceConfiguration) throws G2AccessException {

    }

    @Override
    public boolean getInstantiate() throws G2AccessException {
        return false;
    }

    @Override
    public void setInstantiate(boolean instantiate) throws G2AccessException {

    }

    @Override
    public boolean getIncludeInMenus() throws G2AccessException {
        return false;
    }

    @Override
    public void setIncludeInMenus(boolean includeInMenus) throws G2AccessException {

    }

    @Override
    public Sequence getClassInheritancePath() throws G2AccessException {
        return classPathSequence;
    }

    @Override
    public Sequence getInheritedAttributes() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public Sequence getInitializableSystemAttributes() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public Sequence getAttributeInitializations() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public void setAttributeInitializations(Sequence attributeInitializations) throws G2AccessException {

    }

    @Override
    public Structure getIconDescription() throws G2AccessException {
        return new Structure();
    }

    @Override
    public void setIconDescription(Structure iconDescription) throws G2AccessException {

    }

    @Override
    public void addDefinitionListener(DefinitionListener newListener) throws G2AccessException {

    }

    @Override
    public void removeDefinitionListener(DefinitionListener oldListener) throws G2AccessException {

    }

    @Override
    public void itemDeleted(ItemEvent e) {

    }

    @Override
    public void itemModified(ItemEvent e) {

    }

    @Override
    public void receivedInitialValues(ItemEvent e) {

    }

    @Override
    public void processDefinitionEvent(DefinitionEvent defnEvent) {

    }

    @Override
    public Sequence getItemConfiguration() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public void setItemConfiguration(Sequence itemConfiguration) throws G2AccessException {

    }

    @Override
    public Object getNames() throws G2AccessException {
        return null;
    }

    @Override
    public void setNames(Object names) throws G2AccessException {

    }

    @Override
    public int getLayerPosition() throws G2AccessException {
        return 0;
    }

    @Override
    public Block getFollowingItemInWorkspaceLayering() throws G2AccessException {
        return null;
    }

    @Override
    public void setFollowingItemInWorkspaceLayering(Block followingItemInWorkspaceLayering) throws G2AccessException {

    }

    @Override
    public Structure getPositionInWorkspace() throws G2AccessException {
        return new Structure();
    }

    @Override
    public void setPositionInWorkspace(Structure positionInWorkspace) throws G2AccessException {

    }

    @Override
    public Sequence getRelationships() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public void setRelationships(Sequence relationships) throws G2AccessException {

    }

    @Override
    public Sequence getItemNotes() throws G2AccessException {
        return new Sequence();
    }

    @Override
    public Symbol getContainingModule() throws G2AccessException {
        return null;
    }

    @Override
    public boolean getItemActive() throws G2AccessException {
        return false;
    }

    @Override
    public Symbol getItemStatus() throws G2AccessException {
        return null;
    }

    @Override
    public boolean getInstantiateForClass() throws G2AccessException {
        return false;
    }

    @Override
    public boolean getIncludeInMenusForClass() throws G2AccessException {
        return false;
    }

    @Override
    public Object getSystemMenuChoicesForClass() throws G2AccessException {
        return null;
    }
}
