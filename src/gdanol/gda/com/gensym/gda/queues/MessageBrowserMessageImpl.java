/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MessageBrowserMessageImpl.java
 *
 */

package com.gensym.gda.queues;

import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.classes.modules.gda.GdaAlarmEntry;
import com.gensym.classes.Message;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ItemDeletedException;
import com.gensym.message.Trace;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import java.awt.Color;
import java.util.Hashtable;
import java.util.Enumeration;

public class MessageBrowserMessageImpl implements MessageBrowserMessage
{
    private GqmEntry message;
    private Hashtable attributeValues = new Hashtable ();
    private boolean acknowledged = false;
    private int severity = 0;
    private static Hashtable priorityColorMap = new Hashtable();
    
    private static final Symbol
        GQM_CREATION_TIME_ = Symbol.intern ("GQM-CREATION-TIME"),
        GQM_MESSAGE_TEXT_ = Symbol.intern ("GQM-MESSAGE-TEXT"),
        GQM_PRIORITY_ = Symbol.intern ("GQM-PRIORITY");

    public MessageBrowserMessageImpl (GqmEntry msg, boolean initText) 
    {
        message = msg;
        if (msg instanceof GdaAlarmEntry)
        {
            try
            {
                severity = ((GdaAlarmEntry) msg).getGdaSeverity ();
                acknowledged = ((GdaAlarmEntry) msg).getAcknowledged ();
            }
            catch (G2AccessException gae)    { Trace.exception (gae); }
        }
    }

    public void hashImportantAttributes () 
    {
        try 
        {
            Sequence attrNameSeq = new Sequence ();
            attrNameSeq.addElement (GQM_CREATION_TIME_);            
            attrNameSeq.addElement (GQM_MESSAGE_TEXT_);

            Structure attrValStruc = message.getAttributeValues (attrNameSeq);
            Enumeration valE = attrValStruc.getAttributeValues ();
            while (valE.hasMoreElements ()) 
            {
                //*** The return order of the attr values is funny ***
                attributeValues.put(GQM_CREATION_TIME_, valE.nextElement());
                attributeValues.put(GQM_MESSAGE_TEXT_, valE.nextElement());
            }
        }
        catch (G2AccessException gae)    { Trace.exception(gae); }
    }

    //*** Return value of -1 indicates that row does not exist ***
    public int getRowIndex (String creationTime, String messageText) 
    {
        String cTime, mText;

        try 
        {
            cTime = (new Double (message.getGqmCreationTime ())).toString ();
            mText = message.getGqmMessageText ().toString ();

            if (cTime.equals (creationTime) && mText.equals (messageText))
                return 1;
        }
        catch (G2AccessException g2ae)    { Trace.exception (g2ae); }
        
        return -1;
    }

    public void setValueForAttributeFromMessage (Symbol attributeName, Object value)
    {
        attributeValues.put (attributeName, value);
    }

    public Object getValueForAttributeFromMessage (Symbol attributeName) 
    {
        Object attributeValue = attributeValues.get (attributeName);
        if (attributeValue == null) 
        {
            try 
            {
                //System.out.println("MBMI:63--> getting attr value from G2");
                attributeValue = message.getPropertyValue (attributeName);
                attributeValues.put (attributeName, attributeValue);
                return attributeValue;
            } 
            catch (com.gensym.util.NoSuchAttributeException nsae) 
            {
                Trace.exception (nsae);
                return null;
            } 
            catch (G2AccessException gae)
            { 
                Trace.exception (gae);
                return null;
            }
        }
        return attributeValue;
    }

    //***  May be useful later when we do alarms ***
    public void setValueAt (Object aValue, int row, int column, String colName) 
    {
    /******* Do nothing for message queue *****
        if (colName.equals ("Ack")) 
        {
            try 
            {
                 Boolean boo = new Boolean (aValue.toString ());
                if (boo.booleanValue()) 
                {
                    System.out.println("in acknowledged" + aValue.toString());
                    message.setSmhAcknowledgementStatus(Symbol.intern ("ACKNOWLEDGED"));
                }
                else 
                {
                    System.out.println("in unacknowledged" + aValue.toString());
                    message.setSmhAcknowledgementStatus(Symbol.intern ("UNACKNOWLEDGED"));
                }
            }
            catch (G2AccessException gae) { Trace.exception(gae); }
        }
        *********************/
    }

    public GqmEntry getMessage ()
    {
        return message;
    }

    private Color getBackgroundColor (Integer priority)
    {
        Symbol colorSymbol = (Symbol) priorityColorMap.get (priority);
        if (colorSymbol == null) 
        {
            Symbol GET_BACKGROUND_COLOR_FOR_PRIORITY_ = Symbol.intern ("GET-BACKGROUND-COLOR-FOR-PRIORITY");
            GqmEntry msg = getMessage ();
 
            try 
            {
                com.gensym.jgi.G2Access cxn = ((com.gensym.classes.ItemImpl)msg).getContext ();
                colorSymbol = (Symbol) cxn.callRPC (GET_BACKGROUND_COLOR_FOR_PRIORITY_, new Object[] {priority});
                priorityColorMap.put (priority, colorSymbol);
            }
            catch (G2AccessException gae)    { Trace.exception(gae); }
        }
        if (colorSymbol == null)
            return Color.white;
        else
            return G2ColorMap.get (colorSymbol);
    }

    boolean getAcknowledged ()
    {
        return acknowledged;
    }

    public Color getBackgroundColor ()
    {
        if (message instanceof GdaAlarmEntry)
        {
            System.out.println ("Ackd: " + acknowledged);
            if (acknowledged)
                return ShowQueuesCommand.getColorForSeverity (0);
            else
                return ShowQueuesCommand.getColorForSeverity (severity); 
        }
        else
            return Color.white;
    }

    public Color getForegroundColor ()
    {
        return Color.black;
    }

}

