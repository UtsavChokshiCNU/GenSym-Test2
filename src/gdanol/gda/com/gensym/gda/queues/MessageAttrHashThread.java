
package com.gensym.gda.queues;

import java.util.Vector;
import com.gensym.message.Trace;
import com.gensym.util.Symbol;
import java.util.Enumeration;
import java.util.Hashtable;
import com.gensym.classes.modules.grl.*;
import com.gensym.classes.modules.gqm.GqmEntry;

public class MessageAttrHashThread implements Runnable 
{
    private static final Symbol
        REMOTE_QUEUE_EVENT_LIST_ = Symbol.intern ("REMOTE-QUEUE-EVENT-LIST");

    Enumeration messages;
    Hashtable msghash;

    MessageAttrHashThread(Enumeration e, Hashtable hash) 
    {
        messages = e;
        msghash = hash;
    }

    public void runThread() 
    {
        new Thread (this).start ();
    }

    public void run() 
    {
        GqmEntry entry;
        MessageBrowserMessage msgObj;
        while (messages.hasMoreElements ())
        {
            entry = (GqmEntry) messages.nextElement ();
            msgObj = (MessageBrowserMessage) msghash.get (entry);
            msgObj.hashImportantAttributes ();
        }
    }

}
