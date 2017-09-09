package com.gensym.gda.queues;

import java.util.Hashtable;
import java.util.Enumeration;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.modules.grl.G2_RemoteQueueEventListener;
import com.gensym.classes.modules.grl.RemoteQueueEventManager;
import com.gensym.classes.modules.grl.G2_RemoteQueueEvent;
import com.gensym.classes.modules.gqs.*;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

public class QueueInfo {

    private static Hashtable queueInfos = new Hashtable();
    private Sequence contents;
    private Structure queueEventData;
    private G2_RemoteQueueEventListener listener;
    private RemoteQueueEventManager manager;
    private Object theSource;
    private static final Symbol REMOTE_QUEUE_EVENT_LIST_
        = Symbol.intern ("REMOTE-QUEUE-EVENT-LIST");

    public static void removeQueueListener(GqsQueue queue,
                                           G2_RemoteQueueEventListener listener)
        throws G2AccessException
    {
        QueueInfo queueInfo = (QueueInfo)queueInfos.get(queue);
        if (queueInfo != null)
            queueInfo.manager.removeG2_RemoteQueueEventListener(listener);
    }

    public static void addQueueListener(GqsQueue queue,
                                        G2_RemoteQueueEventListener newListener)
        throws G2AccessException
    {
        QueueInfo queueInfo = (QueueInfo)queueInfos.get(queue);
        if (queueInfo == null) {
            queueInfo = new QueueInfo(queue);
            queueInfos.put(queue, queueInfo);
        }
        class G2_RemoteQueueEventProxy extends G2_RemoteQueueEvent {
            private QueueInfo queueInfo;
            G2_RemoteQueueEventProxy(QueueInfo queueInfo)
            {
                super(queueInfo.theSource, null);
                this.queueInfo = queueInfo;
            }

            public com.gensym.util.Structure getRemoteQueueEventData() throws G2AccessException
            {
                return queueInfo.queueEventData;
            }
        }
        G2_RemoteQueueEvent initialStateEvent = new G2_RemoteQueueEventProxy(queueInfo);
        newListener.queueReceivedInitialState(initialStateEvent);
        queueInfo.manager.addG2_RemoteQueueEventListener(newListener);
    }

    public void finalize() {
        System.out.println("FINALIZING");
        try {
            if (listener != null) {
                System.out.println("REMOVING LISTENER " + listener);
                manager.removeG2_RemoteQueueEventListener(listener);
            }
        } catch (G2AccessException g2ae) {
            System.out.println(g2ae);
        }
    }

    QueueInfo(GqsQueue queue) throws G2AccessException
    {
        manager = queue.getQueueManager();
        listener = new G2_RemoteQueueEventListener()  {
                       public void queueItemsAdded(G2_RemoteQueueEvent arg1) throws G2AccessException
                       {
                           Structure data = arg1.getRemoteQueueEventData();
                           Sequence items = (Sequence)data.getAttributeValue(REMOTE_QUEUE_EVENT_LIST_, null);
                       if (items != null) {
                               Enumeration e = items.elements();
                           while(e.hasMoreElements()) {
                                   contents.addElement(e.nextElement());
                               }
                           }
                       }

                       public void queueItemsRemoved(G2_RemoteQueueEvent arg1) throws G2AccessException
                       {
                           Structure data = arg1.getRemoteQueueEventData();
                           Sequence items = (Sequence)data.getAttributeValue(REMOTE_QUEUE_EVENT_LIST_, null);
                       if (items != null) {
                               Enumeration e = items.elements();
                           while(e.hasMoreElements()) {
                                   contents.removeElement(e.nextElement());
                               }
                           }
                       }

                       public void queueItemsAttributeChanged(G2_RemoteQueueEvent arg1) throws G2AccessException
                       {
                       }

                       public void queueReceivedInitialState(G2_RemoteQueueEvent arg1) throws G2AccessException
                       {
                           theSource = arg1.getSource();
                           Structure data = arg1.getRemoteQueueEventData();
                           Sequence items = (Sequence)data.getAttributeValue(REMOTE_QUEUE_EVENT_LIST_, new Sequence());
                           contents = items;
                           queueEventData = data;
                       }

                       public void queueInvalidateState(G2_RemoteQueueEvent arg1) throws G2AccessException
                       {
                           Structure data = arg1.getRemoteQueueEventData();
                           Sequence items = (Sequence)data.getAttributeValue(REMOTE_QUEUE_EVENT_LIST_, new Sequence());
                           contents = items;
                           queueEventData.setAttributeValue(REMOTE_QUEUE_EVENT_LIST_, contents);
                       }
                   };
        manager.addG2_RemoteQueueEventListener(listener);
        com.gensym.jgi.G2Access cxn = ((com.gensym.classes.ItemImpl)manager).getContext();
        com.gensym.classes.modules.grl.RemoteQueueEvent initialStateEvent =
          (com.gensym.classes.modules.grl.RemoteQueueEvent)
          cxn.callRPC(_GRL_CREATE_INITIAL_STATE_EVENT_, new Object[]{manager});
        G2_RemoteQueueEvent g2InitialStateEvent = (G2_RemoteQueueEvent)
                com.gensym.classes.G2_ExternalEventObjectRoot.createExternalEventObject
                (queue,
                 initialStateEvent,
                 initialStateEvent.getExternalEventClass());
        listener.queueReceivedInitialState(g2InitialStateEvent);
    }
    public static final Symbol _GRL_CREATE_INITIAL_STATE_EVENT_ =
        Symbol.intern ("_GRL-CREATE-INITIAL-STATE-EVENT");
}
