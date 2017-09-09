/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GqsQueueImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Wed Jan 13 18:31:34 EST 1999
 *
 */


package com.gensym.classes.modules.gqs;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class GqsQueueImpl extends com.gensym.classes.modules.gfr.GfrObjectWithUuidImpl implements GqsQueue {


    static final long serialVersionUID = 2L;
    private static final Symbol GQS_INITIALLY_MONITOR_FOR_DELETION_EVENTS_ = Symbol.intern ("GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS");
    private static final Symbol GQS_INITIALLY_MONITOR_FOR_ATTRIBUTE_CHANGE_EVENTS_ = Symbol.intern ("GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS");
    private static final Symbol GQS_ITEM_DELETION_CALLBACK_ = Symbol.intern ("GQS-ITEM-DELETION-CALLBACK");
    private static final Symbol GQS_ATTRIBUTE_UPDATE_CALLBACK_ = Symbol.intern ("GQS-ATTRIBUTE-UPDATE-CALLBACK");
    private static final Symbol GQS_ITEM_ADDITION_CALLBACK_ = Symbol.intern ("GQS-ITEM-ADDITION-CALLBACK");
    private static final Symbol GQS_ITEM_REMOVAL_CALLBACK_ = Symbol.intern ("GQS-ITEM-REMOVAL-CALLBACK");
    private static final Symbol GQS_VIEW_TEMPLATE_OR_ACCESS_TABLE_ = Symbol.intern ("GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE");
    private static final Symbol GQS_LOGGING_MANAGER_ = Symbol.intern ("GQS-LOGGING-MANAGER");
    private static final Symbol GQS_UPDATE_LATENCY_ = Symbol.intern ("GQS-UPDATE-LATENCY");
    private static final Symbol _GQS_COLLECTED_ITEMS_ = Symbol.intern ("_GQS-COLLECTED-ITEMS");
    private static final Symbol _GQS_SUBSCRIPTIONS_ = Symbol.intern ("_GQS-SUBSCRIPTIONS");
    private static final Symbol _GQS_VIEW_MANAGERS_ = Symbol.intern ("_GQS-VIEW-MANAGERS");
    private static final Symbol _GQS_MONITOR_FOR_DELETIONS_ = Symbol.intern ("_GQS-MONITOR-FOR-DELETIONS");
    private static final Symbol _GQS_MONITOR_FOR_ATTRIBUTE_CHANGES_ = Symbol.intern ("_GQS-MONITOR-FOR-ATTRIBUTE-CHANGES");
    private static final Symbol _GQS_MONITORED_ATTRIBUTES_ = Symbol.intern ("_GQS-MONITORED-ATTRIBUTES");
    private static final Symbol _GQS_ITEMS_ARE_AWAITING_INSERTION_ = Symbol.intern ("_GQS-ITEMS-ARE-AWAITING-INSERTION");
    private static final Symbol _GQS_ITEMS_AWAITING_INSERTION_ = Symbol.intern ("_GQS-ITEMS-AWAITING-INSERTION");

    /* Generated constructors */

    public GqsQueueImpl() {
        super();
    }

    public GqsQueueImpl(G2Access context, int handle, Structure attributes) {
        super (context, handle, attributes);
    }


    /**
     * Generated Property Setter for attribute -- GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS
     * @param gqsInitiallyMonitorForDeletionEvents new value to conclude for GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void setGqsInitiallyMonitorForDeletionEvents(boolean gqsInitiallyMonitorForDeletionEvents) throws G2AccessException {
        setAttributeValue (GQS_INITIALLY_MONITOR_FOR_DELETION_EVENTS_, new Boolean (gqsInitiallyMonitorForDeletionEvents));
    }

    /**
     * Generated Property Getter for attribute -- GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS
     * @return the value of the GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public boolean getGqsInitiallyMonitorForDeletionEvents() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (GQS_INITIALLY_MONITOR_FOR_DELETION_EVENTS_);
        return ((Boolean)retnValue).booleanValue ();
    }

    /**
     * Generated Property Setter for attribute -- GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS
     * @param gqsInitiallyMonitorForAttributeChangeEvents new value to conclude for GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void setGqsInitiallyMonitorForAttributeChangeEvents(boolean gqsInitiallyMonitorForAttributeChangeEvents) throws G2AccessException {
        setAttributeValue (GQS_INITIALLY_MONITOR_FOR_ATTRIBUTE_CHANGE_EVENTS_, new Boolean (gqsInitiallyMonitorForAttributeChangeEvents));
    }

    /**
     * Generated Property Getter for attribute -- GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS
     * @return the value of the GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public boolean getGqsInitiallyMonitorForAttributeChangeEvents() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (GQS_INITIALLY_MONITOR_FOR_ATTRIBUTE_CHANGE_EVENTS_);
        return ((Boolean)retnValue).booleanValue ();
    }

    /**
     * Generated Property Setter for attribute -- GQS-ITEM-DELETION-CALLBACK
     * @param gqsItemDeletionCallback new value to conclude for GQS-ITEM-DELETION-CALLBACK
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void setGqsItemDeletionCallback(com.gensym.util.Symbol gqsItemDeletionCallback) throws G2AccessException {
        setAttributeValue (GQS_ITEM_DELETION_CALLBACK_, gqsItemDeletionCallback);
    }

    /**
     * Generated Property Getter for attribute -- GQS-ITEM-DELETION-CALLBACK
     * @return the value of the GQS-ITEM-DELETION-CALLBACK attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.util.Symbol getGqsItemDeletionCallback() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (GQS_ITEM_DELETION_CALLBACK_);
        return (com.gensym.util.Symbol)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- GQS-ATTRIBUTE-UPDATE-CALLBACK
     * @param gqsAttributeUpdateCallback new value to conclude for GQS-ATTRIBUTE-UPDATE-CALLBACK
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void setGqsAttributeUpdateCallback(com.gensym.util.Symbol gqsAttributeUpdateCallback) throws G2AccessException {
        setAttributeValue (GQS_ATTRIBUTE_UPDATE_CALLBACK_, gqsAttributeUpdateCallback);
    }

    /**
     * Generated Property Getter for attribute -- GQS-ATTRIBUTE-UPDATE-CALLBACK
     * @return the value of the GQS-ATTRIBUTE-UPDATE-CALLBACK attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.util.Symbol getGqsAttributeUpdateCallback() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (GQS_ATTRIBUTE_UPDATE_CALLBACK_);
        return (com.gensym.util.Symbol)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- GQS-ITEM-ADDITION-CALLBACK
     * @param gqsItemAdditionCallback new value to conclude for GQS-ITEM-ADDITION-CALLBACK
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void setGqsItemAdditionCallback(com.gensym.util.Symbol gqsItemAdditionCallback) throws G2AccessException {
        setAttributeValue (GQS_ITEM_ADDITION_CALLBACK_, gqsItemAdditionCallback);
    }

    /**
     * Generated Property Getter for attribute -- GQS-ITEM-ADDITION-CALLBACK
     * @return the value of the GQS-ITEM-ADDITION-CALLBACK attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.util.Symbol getGqsItemAdditionCallback() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (GQS_ITEM_ADDITION_CALLBACK_);
        return (com.gensym.util.Symbol)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- GQS-ITEM-REMOVAL-CALLBACK
     * @param gqsItemRemovalCallback new value to conclude for GQS-ITEM-REMOVAL-CALLBACK
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void setGqsItemRemovalCallback(com.gensym.util.Symbol gqsItemRemovalCallback) throws G2AccessException {
        setAttributeValue (GQS_ITEM_REMOVAL_CALLBACK_, gqsItemRemovalCallback);
    }

    /**
     * Generated Property Getter for attribute -- GQS-ITEM-REMOVAL-CALLBACK
     * @return the value of the GQS-ITEM-REMOVAL-CALLBACK attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.util.Symbol getGqsItemRemovalCallback() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (GQS_ITEM_REMOVAL_CALLBACK_);
        return (com.gensym.util.Symbol)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE
     * @param gqsViewTemplateOrAccessTable new value to conclude for GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void setGqsViewTemplateOrAccessTable(com.gensym.util.Symbol gqsViewTemplateOrAccessTable) throws G2AccessException {
        setAttributeValue (GQS_VIEW_TEMPLATE_OR_ACCESS_TABLE_, gqsViewTemplateOrAccessTable);
    }

    /**
     * Generated Property Getter for attribute -- GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE
     * @return the value of the GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.util.Symbol getGqsViewTemplateOrAccessTable() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (GQS_VIEW_TEMPLATE_OR_ACCESS_TABLE_);
        return (com.gensym.util.Symbol)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- GQS-LOGGING-MANAGER
     * @param gqsLoggingManager new value to conclude for GQS-LOGGING-MANAGER
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void setGqsLoggingManager(com.gensym.util.Symbol gqsLoggingManager) throws G2AccessException {
        setAttributeValue (GQS_LOGGING_MANAGER_, gqsLoggingManager);
    }

    /**
     * Generated Property Getter for attribute -- GQS-LOGGING-MANAGER
     * @return the value of the GQS-LOGGING-MANAGER attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.util.Symbol getGqsLoggingManager() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (GQS_LOGGING_MANAGER_);
        return (com.gensym.util.Symbol)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- GQS-UPDATE-LATENCY
     * @param gqsUpdateLatency new value to conclude for GQS-UPDATE-LATENCY
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void setGqsUpdateLatency(double gqsUpdateLatency) throws G2AccessException {
        setAttributeValue (GQS_UPDATE_LATENCY_, new Double (gqsUpdateLatency));
    }

    /**
     * Generated Property Getter for attribute -- GQS-UPDATE-LATENCY
     * @return the value of the GQS-UPDATE-LATENCY attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public double getGqsUpdateLatency() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (GQS_UPDATE_LATENCY_);
        return ((Double)retnValue).doubleValue ();
    }

    /**
     * Generated Property Setter for attribute -- _GQS-COLLECTED-ITEMS
     * @param _gqsCollectedItems new value to conclude for _GQS-COLLECTED-ITEMS
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void set_gqsCollectedItems(com.gensym.classes.ItemList _gqsCollectedItems) throws G2AccessException {
        setAttributeValue (_GQS_COLLECTED_ITEMS_, _gqsCollectedItems);
    }

    /**
     * Generated Property Getter for attribute -- _GQS-COLLECTED-ITEMS
     * @return the value of the _GQS-COLLECTED-ITEMS attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.classes.ItemList get_gqsCollectedItems() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (_GQS_COLLECTED_ITEMS_);
        return (com.gensym.classes.ItemList)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- _GQS-SUBSCRIPTIONS
     * @param _gqsSubscriptions new value to conclude for _GQS-SUBSCRIPTIONS
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void set_gqsSubscriptions(com.gensym.classes.modules.gqs.GqsPermanentItemList _gqsSubscriptions) throws G2AccessException {
        setAttributeValue (_GQS_SUBSCRIPTIONS_, _gqsSubscriptions);
    }

    /**
     * Generated Property Getter for attribute -- _GQS-SUBSCRIPTIONS
     * @return the value of the _GQS-SUBSCRIPTIONS attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.classes.modules.gqs.GqsPermanentItemList get_gqsSubscriptions() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (_GQS_SUBSCRIPTIONS_);
        return (com.gensym.classes.modules.gqs.GqsPermanentItemList)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- _GQS-VIEW-MANAGERS
     * @param _gqsViewManagers new value to conclude for _GQS-VIEW-MANAGERS
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void set_gqsViewManagers(com.gensym.classes.ItemList _gqsViewManagers) throws G2AccessException {
        setAttributeValue (_GQS_VIEW_MANAGERS_, _gqsViewManagers);
    }

    /**
     * Generated Property Getter for attribute -- _GQS-VIEW-MANAGERS
     * @return the value of the _GQS-VIEW-MANAGERS attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.classes.ItemList get_gqsViewManagers() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (_GQS_VIEW_MANAGERS_);
        return (com.gensym.classes.ItemList)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- _GQS-MONITOR-FOR-DELETIONS
     * @param _gqsMonitorForDeletions new value to conclude for _GQS-MONITOR-FOR-DELETIONS
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void set_gqsMonitorForDeletions(boolean _gqsMonitorForDeletions) throws G2AccessException {
        setAttributeValue (_GQS_MONITOR_FOR_DELETIONS_, new Boolean (_gqsMonitorForDeletions));
    }

    /**
     * Generated Property Getter for attribute -- _GQS-MONITOR-FOR-DELETIONS
     * @return the value of the _GQS-MONITOR-FOR-DELETIONS attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public boolean get_gqsMonitorForDeletions() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (_GQS_MONITOR_FOR_DELETIONS_);
        return ((Boolean)retnValue).booleanValue ();
    }

    /**
     * Generated Property Setter for attribute -- _GQS-MONITOR-FOR-ATTRIBUTE-CHANGES
     * @param _gqsMonitorForAttributeChanges new value to conclude for _GQS-MONITOR-FOR-ATTRIBUTE-CHANGES
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void set_gqsMonitorForAttributeChanges(boolean _gqsMonitorForAttributeChanges) throws G2AccessException {
        setAttributeValue (_GQS_MONITOR_FOR_ATTRIBUTE_CHANGES_, new Boolean (_gqsMonitorForAttributeChanges));
    }

    /**
     * Generated Property Getter for attribute -- _GQS-MONITOR-FOR-ATTRIBUTE-CHANGES
     * @return the value of the _GQS-MONITOR-FOR-ATTRIBUTE-CHANGES attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public boolean get_gqsMonitorForAttributeChanges() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (_GQS_MONITOR_FOR_ATTRIBUTE_CHANGES_);
        return ((Boolean)retnValue).booleanValue ();
    }

    /**
     * Generated Property Setter for attribute -- _GQS-MONITORED-ATTRIBUTES
     * @param _gqsMonitoredAttributes new value to conclude for _GQS-MONITORED-ATTRIBUTES
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void set_gqsMonitoredAttributes(com.gensym.classes.modules.gqs.GqsPermanentSymbolList _gqsMonitoredAttributes) throws G2AccessException {
        setAttributeValue (_GQS_MONITORED_ATTRIBUTES_, _gqsMonitoredAttributes);
    }

    /**
     * Generated Property Getter for attribute -- _GQS-MONITORED-ATTRIBUTES
     * @return the value of the _GQS-MONITORED-ATTRIBUTES attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.classes.modules.gqs.GqsPermanentSymbolList get_gqsMonitoredAttributes() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (_GQS_MONITORED_ATTRIBUTES_);
        return (com.gensym.classes.modules.gqs.GqsPermanentSymbolList)retnValue;
    }

    /**
     * Generated Property Setter for attribute -- _GQS-ITEMS-ARE-AWAITING-INSERTION
     * @param _gqsItemsAreAwaitingInsertion new value to conclude for _GQS-ITEMS-ARE-AWAITING-INSERTION
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void set_gqsItemsAreAwaitingInsertion(boolean _gqsItemsAreAwaitingInsertion) throws G2AccessException {
        setAttributeValue (_GQS_ITEMS_ARE_AWAITING_INSERTION_, new Boolean (_gqsItemsAreAwaitingInsertion));
    }

    /**
     * Generated Property Getter for attribute -- _GQS-ITEMS-ARE-AWAITING-INSERTION
     * @return the value of the _GQS-ITEMS-ARE-AWAITING-INSERTION attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public boolean get_gqsItemsAreAwaitingInsertion() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (_GQS_ITEMS_ARE_AWAITING_INSERTION_);
        return ((Boolean)retnValue).booleanValue ();
    }

    /**
     * Generated Property Setter for attribute -- _GQS-ITEMS-AWAITING-INSERTION
     * @param _gqsItemsAwaitingInsertion new value to conclude for _GQS-ITEMS-AWAITING-INSERTION
     * @exception G2AccessException if there are any communication problems
     *              or the value does not match with the type specification
     */
    public void set_gqsItemsAwaitingInsertion(com.gensym.classes.ItemList _gqsItemsAwaitingInsertion) throws G2AccessException {
        setAttributeValue (_GQS_ITEMS_AWAITING_INSERTION_, _gqsItemsAwaitingInsertion);
    }

    /**
     * Generated Property Getter for attribute -- _GQS-ITEMS-AWAITING-INSERTION
     * @return the value of the _GQS-ITEMS-AWAITING-INSERTION attribute of this item
     * @exception G2AccessException if there are any communication problems
     */
    public com.gensym.classes.ItemList get_gqsItemsAwaitingInsertion() throws G2AccessException {
        java.lang.Object retnValue = getAttributeValue (_GQS_ITEMS_AWAITING_INSERTION_);
        return (com.gensym.classes.ItemList)retnValue;
    }

    // Method Name Constants
    private static final Symbol MethodName_GET_QUEUE_MANAGER_ = Symbol.intern ("GET-QUEUE-MANAGER");
    private static final Symbol MethodName_GQS_REMOVE_ITEMS_ = Symbol.intern ("GQS-REMOVE-ITEMS");
    private static final Symbol MethodName_GQS_RECEIVE_ITEMS_ = Symbol.intern ("GQS-RECEIVE-ITEMS");
    private static final Symbol MethodName_GQS_RECEIVE_SINGLE_ITEM_ = Symbol.intern ("GQS-RECEIVE-SINGLE-ITEM");
    private static final Symbol MethodName_GQS_REMOVE_SINGLE_ITEM_ = Symbol.intern ("GQS-REMOVE-SINGLE-ITEM");
    private static final Symbol MethodName_GQS_CLEAR_QUEUE_ = Symbol.intern ("GQS-CLEAR-QUEUE");
    private static final Symbol MethodName_GQS_SERVICE_SUBSCRIBERS_ = Symbol.intern ("GQS-SERVICE-SUBSCRIBERS");
    private static final Symbol MethodName_GQS_UNSUBSCRIBE_ = Symbol.intern ("GQS-UNSUBSCRIBE");
    private static String NoBodyExceptionString = "This method has no implementation for local access";


    //Generated Methods

    /**
     * Auto Generated method for G2 Method
     * GQS-QUEUE::GET-QUEUE-MANAGER
     * @return the return from calling GET-QUEUE-MANAGER
     * @exception G2AccessException if there are any communication problems
     * (this:CLASS GQS-QUEUE) = (CLASS REMOTE-QUEUE-EVENT-MANAGER)
     */
    public  com.gensym.classes.modules.grl.RemoteQueueEventManager getQueueManager() throws G2AccessException
    {
        if (isByHandle()) {
            java.lang.Object result;
            java.lang.Object[] args = new java.lang.Object[] {this};
            result = (java.lang.Object)callRPC(MethodName_GET_QUEUE_MANAGER_, args);
            return (com.gensym.classes.modules.grl.RemoteQueueEventManager)result;
        }
        else {
            // No MethodBody for by-copy exported
            throw new RuntimeException(NoBodyExceptionString);
        }
    }

    /**
     * Auto Generated method for G2 Method
     * GQS-QUEUE::GQS-REMOVE-ITEMS
     * @exception G2AccessException if there are any communication problems
     * (this:CLASS GQS-QUEUE,arg1:CLASS ITEM-LIST,arg2:CLASS OBJECT) = ()
     */
    public  void gqsRemoveItems(com.gensym.classes.ItemList arg1,com.gensym.classes.Object arg2) throws G2AccessException
    {
        if (isByHandle()) {
            java.lang.Object result;
            java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
            result = (java.lang.Object)callRPC(MethodName_GQS_REMOVE_ITEMS_, args);
        }
        else {
            // No MethodBody for by-copy exported
            throw new RuntimeException(NoBodyExceptionString);
        }
    }

    /**
     * Auto Generated method for G2 Method
     * GQS-QUEUE::GQS-RECEIVE-ITEMS
     * @exception G2AccessException if there are any communication problems
     * (this:CLASS GQS-QUEUE,arg1:ITEM-OR-VALUE,arg2:CLASS ITEM-LIST,arg3:CLASS OBJECT) = ()
     */
    public  void gqsReceiveItems(java.lang.Object arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.Object arg3) throws G2AccessException
    {
        if (isByHandle()) {
            java.lang.Object result;
            java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
            result = (java.lang.Object)callRPC(MethodName_GQS_RECEIVE_ITEMS_, args);
        }
        else {
            // No MethodBody for by-copy exported
            throw new RuntimeException(NoBodyExceptionString);
        }
    }

    /**
     * Auto Generated method for G2 Method
     * GQS-QUEUE::GQS-RECEIVE-SINGLE-ITEM
     * @exception G2AccessException if there are any communication problems
     * (this:CLASS GQS-QUEUE,arg1:CLASS ITEM,arg2:CLASS OBJECT) = ()
     */
    public  void gqsReceiveSingleItem(com.gensym.classes.Item arg1,com.gensym.classes.Object arg2) throws G2AccessException
    {
        if (isByHandle()) {
            java.lang.Object result;
            java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
            result = (java.lang.Object)callRPC(MethodName_GQS_RECEIVE_SINGLE_ITEM_, args);
        }
        else {
            // No MethodBody for by-copy exported
            throw new RuntimeException(NoBodyExceptionString);
        }
    }

    /**
     * Auto Generated method for G2 Method
     * GQS-QUEUE::GQS-REMOVE-SINGLE-ITEM
     * @exception G2AccessException if there are any communication problems
     * (this:CLASS GQS-QUEUE,arg1:CLASS ITEM,arg2:CLASS OBJECT) = ()
     */
    public  void gqsRemoveSingleItem(com.gensym.classes.Item arg1,com.gensym.classes.Object arg2) throws G2AccessException
    {
        if (isByHandle()) {
            java.lang.Object result;
            java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
            result = (java.lang.Object)callRPC(MethodName_GQS_REMOVE_SINGLE_ITEM_, args);
        }
        else {
            // No MethodBody for by-copy exported
            throw new RuntimeException(NoBodyExceptionString);
        }
    }

    /**
     * Auto Generated method for G2 Method
     * GQS-QUEUE::GQS-CLEAR-QUEUE
     * @exception G2AccessException if there are any communication problems
     * (this:CLASS GQS-QUEUE,arg1:CLASS OBJECT) = ()
     */
    public  void gqsClearQueue(com.gensym.classes.Object arg1) throws G2AccessException
    {
        if (isByHandle()) {
            java.lang.Object result;
            java.lang.Object[] args = new java.lang.Object[] {this,arg1};
            result = (java.lang.Object)callRPC(MethodName_GQS_CLEAR_QUEUE_, args);
        }
        else {
            // No MethodBody for by-copy exported
            throw new RuntimeException(NoBodyExceptionString);
        }
    }

    /**
     * Auto Generated method for G2 Method
     * GQS-QUEUE::GQS-SERVICE-SUBSCRIBERS
     * @exception G2AccessException if there are any communication problems
     * (this:CLASS GQS-QUEUE,arg1:CLASS ITEM-LIST,arg2:CLASS OBJECT) = ()
     */
    public  void gqsServiceSubscribers(com.gensym.classes.ItemList arg1,com.gensym.classes.Object arg2) throws G2AccessException
    {
        if (isByHandle()) {
            java.lang.Object result;
            java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
            result = (java.lang.Object)callRPC(MethodName_GQS_SERVICE_SUBSCRIBERS_, args);
        }
        else {
            // No MethodBody for by-copy exported
            throw new RuntimeException(NoBodyExceptionString);
        }
    }

    /**
     * Auto Generated method for G2 Method
     * GQS-QUEUE::GQS-UNSUBSCRIBE
     * @exception G2AccessException if there are any communication problems
     * (this:CLASS GQS-QUEUE,arg1:CLASS GQS-SUBSCRIPTION,arg2:CLASS GQS-QUEUE,arg3:CLASS OBJECT) = ()
     */
    public  void gqsUnsubscribe(com.gensym.classes.modules.gqs.GqsSubscription arg1,com.gensym.classes.modules.gqs.GqsQueue arg2,com.gensym.classes.Object arg3) throws G2AccessException
    {
        if (isByHandle()) {
            java.lang.Object result;
            java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
            result = (java.lang.Object)callRPC(MethodName_GQS_UNSUBSCRIBE_, args);
        }
        else {
            // No MethodBody for by-copy exported
            throw new RuntimeException(NoBodyExceptionString);
        }
    }

}
