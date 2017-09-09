/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GqsQueue.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Wed Jan 13 18:30:25 EST 1999
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

public interface GqsQueue extends com.gensym.classes.modules.gfr.GfrObjectWithUuid {

    public static final Symbol GQS_QUEUE_ = Symbol.intern ("GQS-QUEUE");
    static final Symbol g2ClassName = GQS_QUEUE_;
    static final Symbol[] classInheritancePath = new Symbol[] {GQS_QUEUE_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


    static final Symbol[] staticAttributes = new Symbol[] {};


    /**
     * Generated Property Getter for attribute -- GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS
     * @return the value of the GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS attribute of this item
     * @exception G2AccessException if there are any communication problems
     *
     * Type Specification for GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS is : 
     * BooleanTruthValue
     *
     */
    public boolean getGqsInitiallyMonitorForDeletionEvents() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS
             * @param gqsInitiallyMonitorForDeletionEvents new value to conclude for GQS-INITIALLY-MONITOR-FOR-DELETION-EVENTS
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void setGqsInitiallyMonitorForDeletionEvents(boolean gqsInitiallyMonitorForDeletionEvents) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS
             * @return the value of the GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS is : 
             * BooleanTruthValue
             *
             */
            public boolean getGqsInitiallyMonitorForAttributeChangeEvents() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS
             * @param gqsInitiallyMonitorForAttributeChangeEvents new value to conclude for GQS-INITIALLY-MONITOR-FOR-ATTRIBUTE-CHANGE-EVENTS
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void setGqsInitiallyMonitorForAttributeChangeEvents(boolean gqsInitiallyMonitorForAttributeChangeEvents) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- GQS-ITEM-DELETION-CALLBACK
             * @return the value of the GQS-ITEM-DELETION-CALLBACK attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for GQS-ITEM-DELETION-CALLBACK is : 
             * Symbol
             *
             */
            public com.gensym.util.Symbol getGqsItemDeletionCallback() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- GQS-ITEM-DELETION-CALLBACK
             * @param gqsItemDeletionCallback new value to conclude for GQS-ITEM-DELETION-CALLBACK
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void setGqsItemDeletionCallback(com.gensym.util.Symbol gqsItemDeletionCallback) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- GQS-ATTRIBUTE-UPDATE-CALLBACK
             * @return the value of the GQS-ATTRIBUTE-UPDATE-CALLBACK attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for GQS-ATTRIBUTE-UPDATE-CALLBACK is : 
             * Symbol
             *
             */
            public com.gensym.util.Symbol getGqsAttributeUpdateCallback() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- GQS-ATTRIBUTE-UPDATE-CALLBACK
             * @param gqsAttributeUpdateCallback new value to conclude for GQS-ATTRIBUTE-UPDATE-CALLBACK
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void setGqsAttributeUpdateCallback(com.gensym.util.Symbol gqsAttributeUpdateCallback) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- GQS-ITEM-ADDITION-CALLBACK
             * @return the value of the GQS-ITEM-ADDITION-CALLBACK attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for GQS-ITEM-ADDITION-CALLBACK is : 
             * Symbol
             *
             */
            public com.gensym.util.Symbol getGqsItemAdditionCallback() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- GQS-ITEM-ADDITION-CALLBACK
             * @param gqsItemAdditionCallback new value to conclude for GQS-ITEM-ADDITION-CALLBACK
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void setGqsItemAdditionCallback(com.gensym.util.Symbol gqsItemAdditionCallback) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- GQS-ITEM-REMOVAL-CALLBACK
             * @return the value of the GQS-ITEM-REMOVAL-CALLBACK attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for GQS-ITEM-REMOVAL-CALLBACK is : 
             * Symbol
             *
             */
            public com.gensym.util.Symbol getGqsItemRemovalCallback() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- GQS-ITEM-REMOVAL-CALLBACK
             * @param gqsItemRemovalCallback new value to conclude for GQS-ITEM-REMOVAL-CALLBACK
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void setGqsItemRemovalCallback(com.gensym.util.Symbol gqsItemRemovalCallback) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE
             * @return the value of the GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE is : 
             * Symbol
             *
             */
            public com.gensym.util.Symbol getGqsViewTemplateOrAccessTable() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE
             * @param gqsViewTemplateOrAccessTable new value to conclude for GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void setGqsViewTemplateOrAccessTable(com.gensym.util.Symbol gqsViewTemplateOrAccessTable) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- GQS-LOGGING-MANAGER
             * @return the value of the GQS-LOGGING-MANAGER attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for GQS-LOGGING-MANAGER is : 
             * Symbol
             *
             */
            public com.gensym.util.Symbol getGqsLoggingManager() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- GQS-LOGGING-MANAGER
             * @param gqsLoggingManager new value to conclude for GQS-LOGGING-MANAGER
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void setGqsLoggingManager(com.gensym.util.Symbol gqsLoggingManager) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- GQS-UPDATE-LATENCY
             * @return the value of the GQS-UPDATE-LATENCY attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for GQS-UPDATE-LATENCY is : 
             * Float
             *
             */
            public double getGqsUpdateLatency() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- GQS-UPDATE-LATENCY
             * @param gqsUpdateLatency new value to conclude for GQS-UPDATE-LATENCY
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void setGqsUpdateLatency(double gqsUpdateLatency) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- _GQS-COLLECTED-ITEMS
             * @return the value of the _GQS-COLLECTED-ITEMS attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for _GQS-COLLECTED-ITEMS is : 
             * (Class ITEM-LIST)
             *
             */
            public com.gensym.classes.ItemList get_gqsCollectedItems() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- _GQS-COLLECTED-ITEMS
             * @param _gqsCollectedItems new value to conclude for _GQS-COLLECTED-ITEMS
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void set_gqsCollectedItems(com.gensym.classes.ItemList _gqsCollectedItems) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- _GQS-SUBSCRIPTIONS
             * @return the value of the _GQS-SUBSCRIPTIONS attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for _GQS-SUBSCRIPTIONS is : 
             * (Class GQS-PERMANENT-ITEM-LIST)
             *
             */
            public com.gensym.classes.modules.gqs.GqsPermanentItemList get_gqsSubscriptions() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- _GQS-SUBSCRIPTIONS
             * @param _gqsSubscriptions new value to conclude for _GQS-SUBSCRIPTIONS
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void set_gqsSubscriptions(com.gensym.classes.modules.gqs.GqsPermanentItemList _gqsSubscriptions) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- _GQS-VIEW-MANAGERS
             * @return the value of the _GQS-VIEW-MANAGERS attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for _GQS-VIEW-MANAGERS is : 
             * (Class ITEM-LIST)
             *
             */
            public com.gensym.classes.ItemList get_gqsViewManagers() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- _GQS-VIEW-MANAGERS
             * @param _gqsViewManagers new value to conclude for _GQS-VIEW-MANAGERS
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void set_gqsViewManagers(com.gensym.classes.ItemList _gqsViewManagers) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- _GQS-MONITOR-FOR-DELETIONS
             * @return the value of the _GQS-MONITOR-FOR-DELETIONS attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for _GQS-MONITOR-FOR-DELETIONS is : 
             * BooleanTruthValue
             *
             */
            public boolean get_gqsMonitorForDeletions() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- _GQS-MONITOR-FOR-DELETIONS
             * @param _gqsMonitorForDeletions new value to conclude for _GQS-MONITOR-FOR-DELETIONS
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void set_gqsMonitorForDeletions(boolean _gqsMonitorForDeletions) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- _GQS-MONITOR-FOR-ATTRIBUTE-CHANGES
             * @return the value of the _GQS-MONITOR-FOR-ATTRIBUTE-CHANGES attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for _GQS-MONITOR-FOR-ATTRIBUTE-CHANGES is : 
             * BooleanTruthValue
             *
             */
            public boolean get_gqsMonitorForAttributeChanges() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- _GQS-MONITOR-FOR-ATTRIBUTE-CHANGES
             * @param _gqsMonitorForAttributeChanges new value to conclude for _GQS-MONITOR-FOR-ATTRIBUTE-CHANGES
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void set_gqsMonitorForAttributeChanges(boolean _gqsMonitorForAttributeChanges) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- _GQS-MONITORED-ATTRIBUTES
             * @return the value of the _GQS-MONITORED-ATTRIBUTES attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for _GQS-MONITORED-ATTRIBUTES is : 
             * (Class GQS-PERMANENT-SYMBOL-LIST)
             *
             */
            public com.gensym.classes.modules.gqs.GqsPermanentSymbolList get_gqsMonitoredAttributes() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- _GQS-MONITORED-ATTRIBUTES
             * @param _gqsMonitoredAttributes new value to conclude for _GQS-MONITORED-ATTRIBUTES
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void set_gqsMonitoredAttributes(com.gensym.classes.modules.gqs.GqsPermanentSymbolList _gqsMonitoredAttributes) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- _GQS-ITEMS-ARE-AWAITING-INSERTION
             * @return the value of the _GQS-ITEMS-ARE-AWAITING-INSERTION attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for _GQS-ITEMS-ARE-AWAITING-INSERTION is : 
             * BooleanTruthValue
             *
             */
            public boolean get_gqsItemsAreAwaitingInsertion() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- _GQS-ITEMS-ARE-AWAITING-INSERTION
             * @param _gqsItemsAreAwaitingInsertion new value to conclude for _GQS-ITEMS-ARE-AWAITING-INSERTION
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void set_gqsItemsAreAwaitingInsertion(boolean _gqsItemsAreAwaitingInsertion) throws G2AccessException;

            /**
             * Generated Property Getter for attribute -- _GQS-ITEMS-AWAITING-INSERTION
             * @return the value of the _GQS-ITEMS-AWAITING-INSERTION attribute of this item
             * @exception G2AccessException if there are any communication problems
             *
             * Type Specification for _GQS-ITEMS-AWAITING-INSERTION is : 
             * (Class ITEM-LIST)
             *
             */
            public com.gensym.classes.ItemList get_gqsItemsAwaitingInsertion() throws G2AccessException;

            /**
             * Generated Property Setter for attribute -- _GQS-ITEMS-AWAITING-INSERTION
             * @param _gqsItemsAwaitingInsertion new value to conclude for _GQS-ITEMS-AWAITING-INSERTION
             * @exception G2AccessException if there are any communication problems
             *              or the value does not match with the type specification
             */
            public void set_gqsItemsAwaitingInsertion(com.gensym.classes.ItemList _gqsItemsAwaitingInsertion) throws G2AccessException;

            /**
             * Auto Generated method for G2 Method
             * GQS-QUEUE::GET-QUEUE-MANAGER
             * @return the return from calling GET-QUEUE-MANAGER
             * @exception G2AccessException if there are any communication problems
             * (this:CLASS GQS-QUEUE) = (CLASS REMOTE-QUEUE-EVENT-MANAGER)
             */
            public  com.gensym.classes.modules.grl.RemoteQueueEventManager getQueueManager() throws G2AccessException;

            /**
             * Auto Generated method for G2 Method
             * GQS-QUEUE::GQS-REMOVE-ITEMS
             * @exception G2AccessException if there are any communication problems
             * (this:CLASS GQS-QUEUE,arg1:CLASS ITEM-LIST,arg2:CLASS OBJECT) = ()
             */
            public  void gqsRemoveItems(com.gensym.classes.ItemList arg1,com.gensym.classes.Object arg2) throws G2AccessException;

            /**
             * Auto Generated method for G2 Method
             * GQS-QUEUE::GQS-RECEIVE-ITEMS
             * @exception G2AccessException if there are any communication problems
             * (this:CLASS GQS-QUEUE,arg1:ITEM-OR-VALUE,arg2:CLASS ITEM-LIST,arg3:CLASS OBJECT) = ()
             */
            public  void gqsReceiveItems(java.lang.Object arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.Object arg3) throws G2AccessException;

            /**
             * Auto Generated method for G2 Method
             * GQS-QUEUE::GQS-RECEIVE-SINGLE-ITEM
             * @exception G2AccessException if there are any communication problems
             * (this:CLASS GQS-QUEUE,arg1:CLASS ITEM,arg2:CLASS OBJECT) = ()
             */
            public  void gqsReceiveSingleItem(com.gensym.classes.Item arg1,com.gensym.classes.Object arg2) throws G2AccessException;

            /**
             * Auto Generated method for G2 Method
             * GQS-QUEUE::GQS-REMOVE-SINGLE-ITEM
             * @exception G2AccessException if there are any communication problems
             * (this:CLASS GQS-QUEUE,arg1:CLASS ITEM,arg2:CLASS OBJECT) = ()
             */
            public  void gqsRemoveSingleItem(com.gensym.classes.Item arg1,com.gensym.classes.Object arg2) throws G2AccessException;

            /**
             * Auto Generated method for G2 Method
             * GQS-QUEUE::GQS-CLEAR-QUEUE
             * @exception G2AccessException if there are any communication problems
             * (this:CLASS GQS-QUEUE,arg1:CLASS OBJECT) = ()
             */
            public  void gqsClearQueue(com.gensym.classes.Object arg1) throws G2AccessException;

            /**
             * Auto Generated method for G2 Method
             * GQS-QUEUE::GQS-SERVICE-SUBSCRIBERS
             * @exception G2AccessException if there are any communication problems
             * (this:CLASS GQS-QUEUE,arg1:CLASS ITEM-LIST,arg2:CLASS OBJECT) = ()
             */
            public  void gqsServiceSubscribers(com.gensym.classes.ItemList arg1,com.gensym.classes.Object arg2) throws G2AccessException;

            /**
             * Auto Generated method for G2 Method
             * GQS-QUEUE::GQS-UNSUBSCRIBE
             * @exception G2AccessException if there are any communication problems
             * (this:CLASS GQS-QUEUE,arg1:CLASS GQS-SUBSCRIPTION,arg2:CLASS GQS-QUEUE,arg3:CLASS OBJECT) = ()
             */
            public  void gqsUnsubscribe(com.gensym.classes.modules.gqs.GqsSubscription arg1,com.gensym.classes.modules.gqs.GqsQueue arg2,com.gensym.classes.Object arg3) throws G2AccessException;

        }
