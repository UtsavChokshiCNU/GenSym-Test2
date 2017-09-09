package com.gensym.jms;

import java.util.*;
import java.io.*;
import java.lang.*;
import java.text.Collator;
import javax.naming.*;
import javax.jms.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.core.*;
import com.gensym.classes.*;

/**
 * <p>Title: G2-JMS Bridge</p>
 * <p>Description: The class G2Jms listens to a G2 application as to what JMS
 * destination resources ("Topic" or "Queue") it will listen to for input and/or
 * output JMS messages, and pass along the JMS messages between the destination
 * resources and G2.  It supports two JMS messaging models, i.e. point-to-point and
 * publish/subscribe.</p>
 * <p>Copyright: Copyright (c) 2002</p>
 * <p>Company: Gensym Corporation</p>
 * @author Frank Wu
 * @see MessageListener, G2ConnectionListener
 * @version Alpha v1.0
 */
public class G2Jms implements MessageListener, G2ConnectionListener{
  private javax.jms.TopicConnection mTConnection = null;
  private javax.jms.TopicSession mTopSession = null;
  private javax.jms.TopicPublisher mPublisher = null;
  private javax.jms.TopicSubscriber mSubscriber = null;
  private javax.jms.TopicSession mTopicSession = null;
  private javax.jms.Topic mInTopic = null;
  private javax.jms.Topic mOutTopic = null;
  private javax.jms.QueueConnection mQConnection = null;
  private javax.jms.QueueSession mQueSession = null;
  private javax.jms.QueueSender mSender = null;
  private javax.jms.QueueReceiver mReceiver = null;
  private javax.jms.QueueSession mQueueSession = null;
  private javax.jms.Queue mInQueue = null;
  private javax.jms.Queue mOutQueue = null;
  private GsiJms mGsi = null;
  private boolean mDebug = false;
  private Symbol getGsiConfigurationSymbol =
      Symbol.intern("_JMS-GET-GSI-CONFIG");
  private Symbol getJmsOnMessageSymbol =
      Symbol.intern("_JMS-ON-MESSAGE");
  private Symbol getJmsOnErrorSymbol =
      Symbol.intern("_JMS-ON-ERROR");
  private Symbol getJmsSetStatusSymbol =
      Symbol.intern("_JMS-SET-STATUS");

  // static class variables
  private static G2Connection mG2connection = null;

  private static int mPort;
  private static String [] allowedCmdLineParams
      = {"-help", "-Help","-port","-Port", "-?", "-debug"};
  private static String [] allowedConnectionParams
      = {"-debug", "-host", "-user-name", "-password"};


  /**
   * Default class constructor
   */
  public G2Jms(){
  }


  /**
   * Class constructor
   * @param connection, G2Connection to GSI instance
   * @param cnx_data, commands passed from GSI instance
   */
  public G2Jms(G2Connection connection, String cnx_string){
    this.mG2connection = connection;
    if (cnx_string.equals(new String("-debug"))){
      mDebug = true;
    }
    initializeLocalRPCs(connection);
    connection.addG2ConnectionListener(this);
  }


  public void initializeLocalRPCs(G2Connection con){
    // Declare which Java methods and their equivalent G2 RPC NAME,
    // in this class that can be called by the G2 connection
    con.registerJavaMethod(
        this,
        "publishTopicMessage",
        Symbol.intern("JMS-PUBLISH-TOPIC-MESSAGE"));

    con.registerJavaMethod(
        this,
        "sendQueueMessage",
        Symbol.intern("JMS-SEND-QUEUE-MESSAGE"));

    con.registerJavaMethod(
        this,
        "killJmsBridge",
        Symbol.intern("JMS-SHUTDOWN"));

    con.registerJavaMethod(
        this,
        "disconnectJms",
        Symbol.intern("JMS-DISCONNECT"));

  }


  /**
   * This Method is called when the connected G2 has been paused .
   */
  public void g2IsPaused(G2ConnectionEvent e){
    System.out.println("G2 has been paused...");
  }


  /**
   * This method is called when the connected G2 has been resumed.
   */
  public void g2IsResumed(G2ConnectionEvent e){
    System.out.println("G2 has been resumed...");
  }


 /**
   * This method is called when the connected G2 has been reset.
   */
  public void g2IsReset(G2ConnectionEvent e){
    System.out.println("G2 has been reset...");
  }


  /**
   * This method is called when the connected G2 has been started.
   */
  public void g2IsStarted(G2ConnectionEvent e){
    System.out.println("G2 has been started...");
  }


  /**
   * Called when G2 sends a message to the G2Connection.
   */
  public void g2MessageReceived(G2ConnectionEvent e){
    System.out.println("Message received from G2 was: " + e.getMessage());
  }


  /**
   * Called when an asynchronous error has occured in the G2 communications interface
   * for the G2Connection
   *
   *@param error_event An G2CommunicationErrorEvent describing the error that occured.
   */
  public void communicationError(G2CommunicationErrorEvent error_event){
    System.out.println(error_event.getMessage());
  }


  /**
   * Called when the network cannot deliver data that Java is attempting to write to G2.
   */
  public void readBlockage(G2ConnectionEvent event){
    System.out.println("Java bridge failed to write to G2 due to network problem...");
  }


  /**
   * Called when the network cannot deliver data that G2 is attempting to write to Java.
   */
  public void writeBlockage(G2ConnectionEvent event){
    System.out.println("G2 failed to write to Java bridge due to network problem...");
  }


  /**
   * This method is called when the G2 connection has been shutdown.
   */
  public void g2ConnectionClosed(G2ConnectionEvent e){
    System.out.println("G2 Connection has been closed...");
    try {
      //Gracefully close down JMS connection resources
      if (mSubscriber != null) mSubscriber.close();
      if (mReceiver != null) mReceiver.close();
      if (mTConnection != null) mTConnection.close();
      if (mQConnection != null) mQConnection.close();
    }catch (javax.jms.JMSException jmse){
      jmse.printStackTrace();
    }
  }


  /**
   * A connection has been established between this connection and a G2 GSI-INTERFACE.
   * This method is called, so the connection specific information can be set up.
   * Specifically, declaring G2 methods and procedures that this connection would like to call.
   * Note: G2 method and procedure declarations are connection specific.
   */
  public void g2ConnectionInitialized(G2ConnectionEvent e){
    String remote_process_string = e.getMessage();
    try {
      System.out.println("Connected to JMS provider from G2 @" + mG2connection.g2GetHostName() +
                         ":" + mG2connection.g2GetPortNumberOrName());
    } catch (G2AccessException E) { System.out.println(E.toString()); }

    // Send a "hi" message to G2's message board
    mG2connection.returnMessage("Connected to JMS bridge (rpis = " + remote_process_string + ")");

    try{
      //Getting all user configuration for jms-interface from G2
      Structure gsiConfig = (Structure) this.getGsiConfiguration();
      if (mDebug) System.out.println("gsi config = " + gsiConfig);
      mGsi = new GsiJms(gsiConfig);
    }catch (G2AccessInitiationException E) { System.out.println(E.toString());
    }catch (G2AccessException ae) { System.out.println(ae.toString());
    }
    try {
        TopicConnectionFactory tFactory = null;
        QueueConnectionFactory qFactory = null;
        Context jndi = null;

        //Create an InitialContext instance based on the provided properties
        String initialContextFactory = mGsi.mJmsInitCntxFactory;
        String providerURL = mGsi.mJmsProviderURL;
        Hashtable props = null;
        String tConnectionFactory = mGsi.mJmsTopConFactory;
        String qConnectionFactory = mGsi.mJmsQueConFactory;
        Collator myCollator = Collator.getInstance();
        if (myCollator.compare(initialContextFactory, "unspecified") != 0 ||
            myCollator.compare(providerURL, "unspecified") != 0){
          props = new Properties();
          props.put(Context.INITIAL_CONTEXT_FACTORY, initialContextFactory);
          props.put(Context.PROVIDER_URL, providerURL);
        }
        jndi = new InitialContext(props);
        if (mDebug) System.out.println("Got an instance of "+ jndi.getClass().toString());

        if (mGsi.mJmsDestType.compareToIgnoreCase("topic") == 0) {
          tFactory = (TopicConnectionFactory) jndi.lookup(tConnectionFactory);

          if (mDebug && tFactory != null) System.out.println("Got topic connection factory...");
          if (mGsi.mJmsUsername.trim().length() == 0 || mGsi.mJmsPassword.trim().length() == 0) {
            mTConnection = tFactory.createTopicConnection();
          }else {
            mTConnection = tFactory.createTopicConnection(
              mGsi.mJmsUsername,
              mGsi.mJmsPassword);
          }
          if (mDebug && mTConnection != null) System.out.println("Got topic connection...");
          mTConnection.setClientID(mGsi.mJmsClientID);
          mTopSession = mTConnection.createTopicSession(
              mGsi.mJmsTranDelivery,
              mGsi.mJmsAckMode);

          if (myCollator.compare(mGsi.mJmsInbox, "unspecified") != 0) {
            mInTopic = (Topic) jndi.lookup(mGsi.mJmsInbox);
          }
          if (myCollator.compare(mGsi.mJmsOutbox, "unspecified") != 0) {
            mOutTopic = (Topic) jndi.lookup(mGsi.mJmsOutbox);
          }
          if (mDebug && mInTopic != null) System.out.println("Connected to JMS Topic: " +
              mGsi.mJmsInbox + " for inbound messages");
          if (mDebug && mOutTopic != null) System.out.println("Connected to JMS Topic: " +
              mGsi.mJmsOutbox + " for outbound messages");
          this.jmsSetStatus(Symbol.intern("CONNECTED"));
          if (mInTopic == null) return;
          mTopicSession = mTConnection.createTopicSession(
              mGsi.mJmsTranDelivery,
              mGsi.mJmsAckMode);
          if (mGsi.mJmsDurableSub) {
            mSubscriber = mTopicSession.createDurableSubscriber(
                mInTopic,
                mGsi.mJmsSubName,
                (myCollator.compare(mGsi.mJmsSelector, "unspecified") == 0 ?
                null : mGsi.mJmsSelector),
                mGsi.mJmsLocalCopy);
          }else{
            mSubscriber = mTopicSession.createSubscriber(
                mInTopic,
                (myCollator.compare(mGsi.mJmsSelector, "unspecified") == 0 ?
                null : mGsi.mJmsSelector),
                mGsi.mJmsLocalCopy);
          }
          mSubscriber.setMessageListener(this);
          mTConnection.start();
        }else if (mGsi.mJmsDestType.compareToIgnoreCase("queue") == 0) {
          qFactory = (QueueConnectionFactory) jndi.lookup(qConnectionFactory);
          if (mDebug) System.out.println("Got queue connection factory...");
          if (mGsi.mJmsUsername.trim().length() == 0 || mGsi.mJmsPassword.trim().length() == 0) {
            mQConnection = qFactory.createQueueConnection();
          }else {
            mQConnection = qFactory.createQueueConnection(
              mGsi.mJmsUsername,
              mGsi.mJmsPassword);
          }
          if (mDebug) System.out.println("Got queue connection...");
          mQConnection.setClientID(mGsi.mJmsClientID);
          mQueSession = mQConnection.createQueueSession(
              mGsi.mJmsTranDelivery,
              mGsi.mJmsAckMode);
          if (myCollator.compare(mGsi.mJmsInbox, "unspecified") != 0) {
            mInQueue = (javax.jms.Queue) jndi.lookup(mGsi.mJmsInbox);
          }
          if (myCollator.compare(mGsi.mJmsOutbox, "unspecified") != 0) {
            mOutQueue = (javax.jms.Queue) jndi.lookup(mGsi.mJmsOutbox);
          }
          if (mDebug) System.out.println("Connected to JMS Queue: " +
              mGsi.mJmsInbox + " for inbound messages");
          if (mDebug) System.out.println("Connected to JMS Queue: " +
              mGsi.mJmsOutbox + " for outbound messages");
          this.jmsSetStatus(Symbol.intern("CONNECTED"));
          if (mInQueue == null) return;
          mQueueSession = mQConnection.createQueueSession(
              mGsi.mJmsTranDelivery,
              mGsi.mJmsAckMode);
          mReceiver = mQueueSession.createReceiver(
            mInQueue,
            (myCollator.compare(mGsi.mJmsSelector, "unspecified") == 0 ?
              null : mGsi.mJmsSelector));
          mReceiver.setMessageListener(this);
          mQConnection.start();
        }
      }catch (JMSException jmse){
        jmse.printStackTrace();
        this.releaseResources();
      }catch(javax.naming.NamingException jne){
        jne.printStackTrace();
        this.releaseResources();
      }catch (G2AccessException ge){
      ge.printStackTrace();
      }
  }


  /**
   * To Implement G2_EventSourceListener exported from G2 Event
   * Generator class G2EventSourceClass.
   * /

  public void anEvent(G2_EventSourceEvent arg1) throws G2AccessException
  {
    System.out.println("Received an event from " + arg1.getSource() + "..." +
                       arg1.getMessage());
  }


  /**
   * Broadcast a text message to subscribers of a topic
   * @param g2msg text message passed over from G2
   * @param header Header information for the JMS message
   * @param property Property information for the JMS message
   */
  public int publishTopicMessage(String g2msg,
                                 Structure header,
                                 Structure property){
    try {
      //Setting up a TextMessage
      javax.jms.TextMessage msg = mTopSession.createTextMessage();
      if (mDebug) System.out.println("Received a G2 string and publishing a text message:");
      if (mDebug) System.out.println("\""+g2msg+"\"");
      msg.setText(g2msg);
      if (mDebug) System.out.println("\nSetting up message property");
      setProperty(msg, property);
      Integer mode = (Integer) header.getAttributeValue(mGsi.mJmsDeliveryMode,
          javax.jms.Message.DEFAULT_DELIVERY_MODE);
      Integer priority = (Integer) header.getAttributeValue(mGsi.mJmsPriority,
          javax.jms.Message.DEFAULT_PRIORITY);
      Number ttl = (Number) header.getAttributeValue(mGsi.mJmsTimeToLive,
          javax.jms.Message.DEFAULT_TIME_TO_LIVE);
      String corrid = (String) header.getAttributeValue(mGsi.mJmsCorrelationID, "");
      String type = (String) header.getAttributeValue(mGsi.mJmsType, "");
      if (mDebug) System.out.println("Mode="+mode+", Priority="+priority+
                                     ", Expiration="+ttl+", CorrelationID="+
                                     corrid+", MessageType="+type);
      msg.setJMSDeliveryMode(mode.intValue());
      msg.setJMSPriority(priority.intValue());
      msg.setJMSExpiration(ttl.longValue());
      msg.setJMSCorrelationID(corrid);
      msg.setJMSType(type);
      mPublisher = mTopSession.createPublisher(mOutTopic);
      mPublisher.setDeliveryMode(mode.intValue());
      mPublisher.setPriority(priority.intValue());
      mPublisher.setTimeToLive(ttl.longValue());
      mPublisher.publish(msg);
    }catch ( javax.jms.JMSException jmse ){
      jmse.printStackTrace();
    }catch (NoSuchAttributeException nae){
      nae.printStackTrace();
    }
    return 1;
  }


  /**
   * Broadcast a map message to subscribers of a topic
   * @param g2msg Name-value pairs passed over from G2
   * @param header Header information for the JMS message
   * @param property Property information for the JMS message
   */
  public int publishTopicMessage(Structure g2msg,
                                 Structure header,
                                 Structure property){
    try {
      //Setting up a MapMessage
      javax.jms.MapMessage msg = mTopSession.createMapMessage();
      if (mDebug) System.out.println("\nSetting up message property");
      setProperty(msg, property);
      String tmsg = null;
      for (Enumeration mapNames = g2msg.getAttributeNames();
           mapNames.hasMoreElements();){
        Symbol nextName = (Symbol) mapNames.nextElement();
        String key = nextName.toString();
//        String nextVal = (String) g2msg.getAttributeValue(nextName);
        java.lang.Object nextVal = (java.lang.Object) g2msg.getAttributeValue(nextName);
        if (mDebug) System.out.println(nextVal.toString());
//        msg.setObject(key, nextVal);
        if (nextVal instanceof Symbol) {
          msg.setString(key, nextVal.toString()+"%%?syym%?%");
        }
        else if (nextVal instanceof Sequence) {
          Sequence valSeq = (Sequence) nextVal;
          String keyVal = "%%?sqqn%?%";
          for (Iterator vals=valSeq.iterator(); vals.hasNext();){
            java.lang.Object val = (java.lang.Object) vals.next();
            if (val instanceof Symbol){
              keyVal = keyVal+val.toString()+"%sym&";
            }
            else if (val instanceof String){
              keyVal = keyVal+val.toString()+"%str&";
            }
            else if (val instanceof Integer){
              keyVal = keyVal+val.toString()+"%int&";
            }
            else if (val instanceof Double){
              keyVal = keyVal+val.toString()+"%flt&";
            }
            else if (val instanceof Boolean){
              keyVal = keyVal+val.toString()+"%bln&";
            }
          }
          if (mDebug) System.out.println("key= "+nextName);
          if (mDebug) System.out.println("Sequence value is: "+keyVal);
          msg.setString(key, keyVal);
        }
        else if (nextVal instanceof Structure ||
                 nextVal instanceof Sequence ||
                 nextVal instanceof com.gensym.classes.Object){
          if (mDebug) System.out.println("Should not come here, the class of "+
              nextVal.getClass().getName());
        }
        else msg.setObject(key, nextVal);

        if (mDebug) tmsg = (tmsg == null ? "" : tmsg) +
          nextName + ":" + nextVal.toString() + " ";
      }

      if (mDebug) System.out.println("Received a structure and publishing a map message: "+
                                     "\n"+tmsg);
      Integer mode = (Integer) header.getAttributeValue(mGsi.mJmsDeliveryMode,
    	  javax.jms.Message.DEFAULT_DELIVERY_MODE);
      Integer priority = (Integer) header.getAttributeValue(mGsi.mJmsPriority,
          javax.jms.Message.DEFAULT_PRIORITY);
      Number ttl = (Number) header.getAttributeValue(mGsi.mJmsTimeToLive,
          javax.jms.Message.DEFAULT_TIME_TO_LIVE);
      String corrid = (String) header.getAttributeValue(mGsi.mJmsCorrelationID, "");
      String type = (String) header.getAttributeValue(mGsi.mJmsType, "");
      if (mDebug) System.out.println("Mode="+mode+", Priority="+priority+
                                     ", Expiration="+ttl+", CorrelationID="+
                                     corrid+", MessageType="+type);
      msg.setJMSDeliveryMode(mode.intValue());
      msg.setJMSPriority(priority.intValue());
      msg.setJMSExpiration(ttl.longValue());
      msg.setJMSCorrelationID(corrid);
      msg.setJMSType(type);
      mPublisher = mTopSession.createPublisher(mOutTopic);
      mPublisher.setDeliveryMode(mode.intValue());
      mPublisher.setPriority(priority.intValue());
      mPublisher.setTimeToLive(ttl.longValue());
      mPublisher.publish(msg);
    }catch ( javax.jms.JMSException jmse ){
      jmse.printStackTrace();
    }catch (com.gensym.util.NoSuchAttributeException nae){
      nae.printStackTrace();
    }
    return 1;
  }


  /**
   * Broadcast a map message to subscribers of a topic
   * @param names A list of names passed over from G2
   * @param values A list of matching values passed over from G2
   * @param header Header information for the JMS message
   * @param property Properties for the JMS message
   */
  public int publishTopicMessage(Sequence names,
                                 Sequence values,
                                 Structure header,
                                 Structure property){
    try{
      //Setting up a MapMessage
      javax.jms.MapMessage msg = mTopSession.createMapMessage();
      if (mDebug) System.out.println("Received 2 sequences and publishing a map message..");
      if (mDebug) System.out.println("\nSetting up message property");
      setProperty(msg, property);
      for (Iterator ns=names.iterator(), vals=values.iterator(); ns.hasNext()
           &&vals.hasNext();){
        String key = (String) ns.next();
 //       String val = (String) vals.next();
        java.lang.Object val = (java.lang.Object) vals.next();
        if (mDebug) System.out.println("key="+key+" value="+val.toString());
 //       msg.setString(key, val);
        if (val instanceof Symbol) {
         msg.setString(key, val.toString()+"%%?syym%?%");
        }
        else if (val instanceof Structure ||
                 val instanceof Sequence ||
                 val instanceof com.gensym.classes.Object){
          if (mDebug) System.out.println("Should not come here, the class of "+
              val.getClass().getName());
        }
        else msg.setObject(key, val);
      }
      Integer mode = (Integer) header.getAttributeValue(mGsi.mJmsDeliveryMode,
          javax.jms.Message.DEFAULT_DELIVERY_MODE);
      Integer priority = (Integer) header.getAttributeValue(mGsi.mJmsPriority,
          javax.jms.Message.DEFAULT_PRIORITY);
      Number ttl = (Number) header.getAttributeValue(mGsi.mJmsTimeToLive,
          javax.jms.Message.DEFAULT_TIME_TO_LIVE);
      String corrid = (String) header.getAttributeValue(mGsi.mJmsCorrelationID, "");
      String type = (String) header.getAttributeValue(mGsi.mJmsType, "");
      if (mDebug) System.out.println("Mode="+mode+", Priority="+priority+
                                     ", Expiration="+ttl+", CorrelationID="+
                                     corrid+", MessageType="+type);
      msg.setJMSDeliveryMode(mode.intValue());
      msg.setJMSPriority(priority.intValue());
      msg.setJMSExpiration(ttl.longValue());
      msg.setJMSCorrelationID(corrid);
      msg.setJMSType(type);
      mPublisher = mTopSession.createPublisher(mOutTopic);
      mPublisher.setDeliveryMode(mode.intValue());
      mPublisher.setPriority(priority.intValue());
      mPublisher.setTimeToLive(ttl.longValue());
      mPublisher.publish(msg);
    }catch ( javax.jms.JMSException jmse ){
      jmse.printStackTrace();
    }catch (NoSuchAttributeException nae){
      nae.printStackTrace();
    }
    return 1;
  }


  /**
   * Send a text message to one of receiver(s) listening to a queue
   * @param g2msg text message passed over from G2
   * @param header Header information for the JMS message
   * @param property Property information for the JMS message
   */
  public int sendQueueMessage(String g2msg,
                              Structure header,
                              Structure property){
    try {
      //Setting up a TextMessage
      javax.jms.TextMessage msg = mQueSession.createTextMessage();
      if (mDebug) System.out.println("Received a G2 string and sending a text message:");
      if (mDebug) System.out.println("\""+g2msg+"\"");
      msg.setText(g2msg);
      if (mDebug) System.out.println("\nSetting up message property");
      setProperty(msg, property);
      Integer mode = (Integer) header.getAttributeValue(mGsi.mJmsDeliveryMode,
          javax.jms.Message.DEFAULT_DELIVERY_MODE);
      Integer priority = (Integer) header.getAttributeValue(mGsi.mJmsPriority,
          javax.jms.Message.DEFAULT_PRIORITY);
      Number ttl = (Number) header.getAttributeValue(mGsi.mJmsTimeToLive,
          javax.jms.Message.DEFAULT_TIME_TO_LIVE);
      String corrid = (String) header.getAttributeValue(mGsi.mJmsCorrelationID, "");
      String type = (String) header.getAttributeValue(mGsi.mJmsType, "");
      if (mDebug) System.out.println("Mode="+mode+", Priority="+priority+
                                     ", Expiration="+ttl+", CorrelationID="+
                                     corrid+", MessageType="+type);
      msg.setJMSDeliveryMode(mode.intValue());
      msg.setJMSPriority(priority.intValue());
      msg.setJMSExpiration(ttl.longValue());
      msg.setJMSCorrelationID(corrid);
      msg.setJMSType(type);
      mSender = mQueSession.createSender(mOutQueue);
      mSender.setDeliveryMode(mode.intValue());
      mSender.setPriority(priority.intValue());
      mSender.setTimeToLive(ttl.longValue());
      mSender.send(msg);
//      mSender.send(
//          msg,
//          javax.jms.Message.DEFAULT_DELIVERY_MODE,
//          javax.jms.Message.DEFAULT_PRIORITY,
//          javax.jms.Message.DEFAULT_TIME_TO_LIVE);
    }catch ( javax.jms.JMSException jmse ){
      jmse.printStackTrace();
    }catch(NoSuchAttributeException nae){
      nae.printStackTrace();
    }
    return 1;
  }


  /**
   * Send a map message to one of receiver(s) listening to a queue
   * @param g2msg Name-value pairs passed over from G2
   * @param header Header information for the JMS message
   * @param property Property information for the JMS message
   */
  public int sendQueueMessage(Structure g2msg,
                              Structure header,
                              Structure property){
    try {
      //Setting up a MapMessage
      javax.jms.MapMessage msg = mQueSession.createMapMessage();
      if (mDebug) System.out.println("\nSetting up message property");
      setProperty(msg, property);
      String tmsg = null;
      for (Enumeration mapNames = g2msg.getAttributeNames();
           mapNames.hasMoreElements();){
//        Symbol nextName = (Symbol) mapNames.nextElement();
//        String key = nextName.toString();
//        String nextVal = (String) g2msg.getAttributeValue(nextName);
//        msg.setString(key, nextVal);
//        tmsg = (tmsg == null ? "" : tmsg) + nextName + ":" + nextVal + " ";
        Symbol nextName = (Symbol) mapNames.nextElement();
        String key = nextName.toString();
        java.lang.Object nextVal = (java.lang.Object) g2msg.getAttributeValue(nextName);
        if (mDebug) System.out.println(nextVal.toString());
        if (nextVal instanceof Symbol) {
          msg.setString(key, nextVal.toString()+"%%?syym%?%");
        }
        else if (nextVal instanceof Sequence) {
          Sequence valSeq = (Sequence) nextVal;
          String keyVal = "%%?sqqn%?%";
          for (Iterator vals=valSeq.iterator(); vals.hasNext();){
            java.lang.Object val = (java.lang.Object) vals.next();
            if (val instanceof Symbol){
              keyVal = keyVal+val.toString()+"%sym&";
            }
            else if (val instanceof String){
              keyVal = keyVal+val.toString()+"%str&";
            }
            else if (val instanceof Integer){
              keyVal = keyVal+val.toString()+"%int&";
            }
            else if (val instanceof Double){
              keyVal = keyVal+val.toString()+"%flt&";
            }
            else if (val instanceof Boolean){
              keyVal = keyVal+val.toString()+"%bln&";
            }
          }
          if (mDebug) System.out.println("key= "+nextName);
          if (mDebug) System.out.println("Sequence value is: "+keyVal);
          msg.setString(key, keyVal);
        }
        else if (nextVal instanceof Structure ||
                 nextVal instanceof Sequence ||
                 nextVal instanceof com.gensym.classes.Object){
          if (mDebug) System.out.println("Should not come here, the class of "+
              nextVal.getClass().getName());
        }
        else msg.setObject(key, nextVal);

        if (mDebug) tmsg = (tmsg == null ? "" : tmsg) +
          nextName + ":" + nextVal.toString() + " ";
      }

      if (mDebug) System.out.println("Received a structure and sending a map message: "+
                                     "\n"+tmsg);
      Integer mode = (Integer) header.getAttributeValue(mGsi.mJmsDeliveryMode,
    		  javax.jms.Message.DEFAULT_DELIVERY_MODE);
      Integer priority = (Integer) header.getAttributeValue(mGsi.mJmsPriority,
    		  javax.jms.Message.DEFAULT_PRIORITY);
      Number ttl = (Number) header.getAttributeValue(mGsi.mJmsTimeToLive,
          	  javax.jms.Message.DEFAULT_TIME_TO_LIVE);
      String corrid = (String) header.getAttributeValue(mGsi.mJmsCorrelationID, "");
      String type = (String) header.getAttributeValue(mGsi.mJmsType, "");
      if (mDebug) System.out.println("Mode="+mode+", Priority="+priority+
                                     ", Expiration="+ttl+", CorrelationID="+
                                     corrid+", MessageType="+type);
      msg.setJMSDeliveryMode(mode.intValue());
      msg.setJMSPriority(priority.intValue());
      msg.setJMSExpiration(ttl.longValue());
      msg.setJMSCorrelationID(corrid);
      msg.setJMSType(type);
      mSender = mQueSession.createSender(mOutQueue);
      mSender.setDeliveryMode(mode.intValue());
      mSender.setPriority(priority.intValue());
      mSender.setTimeToLive(ttl.longValue());
      mSender.send(msg);
    }catch ( javax.jms.JMSException jmse ){
      jmse.printStackTrace();
    }catch (com.gensym.util.NoSuchAttributeException nae){
      nae.printStackTrace();
    }
    return 1;
  }


  /**
   * Send a map message to one of receiver(s) listening to a queue
   * @param names A list of names passed over from G2
   * @param values A list of matching values passed over from G2
   * @param header Header information for the JMS message
   * @param property Property information for the JMS message
   */
  public int sendQueueMessage(Sequence names,
                              Sequence values,
                              Structure header,
                              Structure property){
    try{
      //Setting up a MapMessage
      javax.jms.MapMessage msg = mQueSession.createMapMessage();
      if (mDebug) System.out.println("Received 2 sequences and sending a map message..");
      if (mDebug) System.out.println("\nSetting up message property");
      setProperty(msg, property);
      for (Iterator ns=names.iterator(), vals=values.iterator(); ns.hasNext()
           &&vals.hasNext();){
        String key = (String) ns.next();
 //       String val = (String) vals.next();
        java.lang.Object val = (java.lang.Object) vals.next();
        if (mDebug) System.out.println("key="+key+" value="+val.toString());
 //       msg.setString(key, val);
        if (val instanceof Symbol) {
         msg.setString(key, val.toString()+"%%?syym%?%");
        }
        else if (val instanceof Structure ||
                 val instanceof Sequence ||
                 val instanceof com.gensym.classes.Object){
          if (mDebug) System.out.println("Should not come here, the class of "+
              val.getClass().getName());
        }
        else msg.setObject(key, val);
      }
      Integer mode = (Integer) header.getAttributeValue(mGsi.mJmsDeliveryMode,
          javax.jms.Message.DEFAULT_DELIVERY_MODE);
      Integer priority = (Integer) header.getAttributeValue(mGsi.mJmsPriority,
          javax.jms.Message.DEFAULT_PRIORITY);
      Number ttl = (Number) header.getAttributeValue(mGsi.mJmsTimeToLive,
          javax.jms.Message.DEFAULT_TIME_TO_LIVE);
      String corrid = (String) header.getAttributeValue(mGsi.mJmsCorrelationID, "");
      String type = (String) header.getAttributeValue(mGsi.mJmsType, "");
      if (mDebug) System.out.println("Mode="+mode+", Priority="+priority+
                                     ", Expiration="+ttl+", CorrelationID="+
                                     corrid+", MessageType="+type);
      msg.setJMSDeliveryMode(mode.intValue());
      msg.setJMSPriority(priority.intValue());
      msg.setJMSExpiration(ttl.longValue());
      msg.setJMSCorrelationID(corrid);
      msg.setJMSType(type);
      mSender = mQueSession.createSender(mOutQueue);
      mSender.setDeliveryMode(mode.intValue());
      mSender.setPriority(priority.intValue());
      mSender.setTimeToLive(ttl.longValue());
      mSender.send(msg);
    }catch ( javax.jms.JMSException jmse ){
      jmse.printStackTrace();
    }catch (NoSuchAttributeException nae){
      nae.printStackTrace();
    }
    return 1;
  }


  /**
   * Terminate this JMS bridge process
   */
  public void killJmsBridge(){
    try {
      System.out.println("Terminating JMS bridge connected to G2 @" + mG2connection.g2GetHostName() +
                         ":" + mG2connection.g2GetPortNumberOrName());
    } catch (G2AccessException E) { System.out.println(E.toString()); }
    this.exit();
  }


  /**
   * Disconnect this JMS bridge process to JMS provider
   */
  public void  disconnectJms(){
    try {
      System.out.println("Disconnected to JMS provider from JMS bridge connected to G2 @" + mG2connection.g2GetHostName() +
                         ":" + mG2connection.g2GetPortNumberOrName());
    } catch (G2AccessException E) { System.out.println(E.toString()); }
    this.releaseResources();
  }


  /**
   * This method receives asynchronously delivered messages
   * @param msg an instance of jms message
   */
  public void onMessage(javax.jms.Message msg){
    processMessage(msg);
  }


  /**
   * Set propert value to a message
   */
  private void setProperty(javax.jms.Message msg, Structure prop)
      throws JMSException, MessageFormatException, NoSuchAttributeException{
    for (Enumeration propNames = prop.getAttributeNames();propNames.hasMoreElements();){
      Symbol propName = (Symbol) propNames.nextElement();
      String key = propName.toString();
      java.lang.Object propVal = (java.lang.Object) prop.getAttributeValue(propName);
      if (mDebug) System.out.println("\nSetting property name: "+
                                     key+" = "+propVal.toString());
      msg.setObjectProperty(key, propVal);
    }
  }


  /*
   * This method makes G2Connection-specific RPC call to pass along messages to
   * G2 application.
   */
  private Integer g2OnMessage(Structure structVal, Structure header, Structure property)
      throws G2AccessException{
    Integer retVal = (Integer) mG2connection.callRPC(
        getJmsOnMessageSymbol,
        new java.lang.Object[] {structVal, header, property},
        10000);
    return retVal;
  }


  /*
   * This method makes G2Connection-specific RPC call to pass along messages to
   * G2 application.
   */
  private Integer g2OnMessage(String textVal, Structure header, Structure property)
      throws G2AccessException {
    Integer retVal = (Integer) mG2connection.callRPC(
        getJmsOnMessageSymbol,
        new java.lang.Object[] {textVal, header, property},
        10000);
    return retVal;
  }


  /*
   * This method makes G2Connection-specific RPC call to pass error state info.
   */
  private Integer jmsOnError(String textVal) throws G2AccessException{
    Integer retVal = (Integer) mG2connection.callRPC(
        getJmsOnErrorSymbol,
        new java.lang.Object[] {textVal},
        10000);
    return retVal;
  }


  /*
   * This method makes G2Connection-specific RPC call to set connection status.
   */
  private Integer jmsSetStatus(Symbol s) throws G2AccessException{
    if (mDebug) System.out.println("jms status = "+s.toString());
    Integer retVal = (Integer) mG2connection.callRPC(
        getJmsSetStatusSymbol,
        new java.lang.Object[] {s},
        10000);
    return retVal;
  }


  /*
   * This method makes G2Connection-specific RPC call to get GSI configuration.
   */
  private Structure getGsiConfiguration() throws G2AccessException{
    mG2connection.setRemoteRPCReturnKind(
        getGsiConfigurationSymbol,
        G2Gateway.PASS_BY_COPY);
    Structure retVal =  (Structure) mG2connection.callRPC(
        getGsiConfigurationSymbol,
        new java.lang.Object[0],
        10000);
    return retVal;
  }


  /*
   * This method processes a JMS message before sending it over to G2
   */
  private void processMessage(javax.jms.Message msg){
     Structure structval = new Structure();
     Structure header = new Structure();
     Structure property = new Structure();
     try {
       //Get and set all message headers
//       header.setAttributeValue(Symbol.intern("JMS-DESTINATION"), msg.getJMSDestination());
       header.setAttributeValue(Symbol.intern("JMS-DELIVERY-MODE"),
                                msg.getJMSDeliveryMode());
       header.setAttributeValue(Symbol.intern("JMS-MESSAGE-ID"),
                                msg.getJMSMessageID());
       header.setAttributeValue(Symbol.intern("JMS-TIMESTAMP"),
                                msg.getJMSTimestamp());
       header.setAttributeValue(Symbol.intern("JMS-EXPIRATION"),
                                msg.getJMSExpiration());
       header.setAttributeValue(Symbol.intern("JMS-REDELIVERED"),
                                msg.getJMSRedelivered());
       header.setAttributeValue(Symbol.intern("JMS-PRIORITY"),
                                msg.getJMSPriority());
//      header.setAttributeValue(Symbol.intern("JMS-REPLY-TO"), msg.getJMSReplyTo());
       header.setAttributeValue(Symbol.intern("JMS-CORRELATION-ID"),
                                msg.getJMSCorrelationID());
       header.setAttributeValue(Symbol.intern("JMS-TYPE"),
                                msg.getJMSType());

       //Get and set all message properties
       Enumeration propertyNames = msg.getPropertyNames();
       while(propertyNames.hasMoreElements()){
         String name = (String) propertyNames.nextElement();
         java.lang.Object value = msg.getObjectProperty(name);
         if (mDebug ) System.out.println("\n"+name+" = "+value);
         property.setAttributeValue(Symbol.intern(name.toUpperCase()), value);
       }

       //Recontruct a message and send it to G2
       if (msg instanceof MapMessage) {
         MapMessage mapmsg = (MapMessage) msg;
         for (Enumeration mapnames = mapmsg.getMapNames();
              mapnames.hasMoreElements();){
           String nextname = (String) mapnames.nextElement();
           java.lang.Object nextval = null;
           nextval = mapmsg.getObject(nextname);
           if (nextval != null){
             if (mDebug) System.out.println(nextname + ":" + nextval.toString());
             Symbol symname = Symbol.intern(nextname.toUpperCase());
             if (nextval instanceof String){
               String strval = (String) nextval;
               if (strval.endsWith("%%?syym%?%")) {
                 strval = strval.substring(0, strval.indexOf("%%?syym%?%"));
                 Symbol strutval = Symbol.intern(strval);
                 structval.setAttributeValue(symname, strutval);
               }
               else if (strval.startsWith("%%?sqqn%?%")){
                 strval = strval.substring(10, strval.length());
                 Sequence seqval = null;
                 seqval = this.convertText2Sequence(strval, "%", "&");
                 structval.setAttributeValue(symname, seqval);
               }
               else structval.setAttributeValue(symname, strval);
             }else{
                 structval.setAttributeValue(symname, nextval);
             }
           }
         }
         if (structval != null) {
           Integer g2Ret = this.g2OnMessage(structval, header, property);
           if (mDebug) mG2connection.returnMessage("Received a mapMessage from a JMS topic: " +
                                       structval);
           if (g2Ret.intValue() == 1) {
             msg.acknowledge();
           }
         }
       }else if (msg instanceof TextMessage){
         TextMessage textmsg = (TextMessage) msg;
         String textval = textmsg.getText();
         Integer g2Ret = this.g2OnMessage(textval, header, property);
         if (g2Ret.intValue() == 1) {
             msg.acknowledge();
           }
       }
     }catch (java.lang.RuntimeException rte){
       rte.printStackTrace();
     }catch (G2AccessException ge){
       ge.printStackTrace();
     }catch (javax.jms.JMSException jmse){
       jmse.printStackTrace();
    }
  }


    /*
   * Convert string value to G2 Sequence
   */
  private Sequence convertText2Sequence(final String val, final String d1, final String dl){
    Sequence seqval = new Sequence();
    String value = val;
    if (mDebug) System.out.println(value+" has value(type) info:" );
    while (value.length() > 0){
      String va = value.substring(0, value.indexOf(dl)+1);
      String typ = va.substring(va.length()-4, va.length()-1);
      String vv = va.substring(0, va.length()-5);
      if (mDebug) System.out.print(vv+"("+typ+") ");
      value = value.substring(va.length(), value.length());
      int ind = seqval.size();
      if (typ.compareToIgnoreCase("str") == 0) {
        seqval.insertElementAt(vv, ind);
      }
      else if (typ.compareToIgnoreCase("sym") == 0 ){
        seqval.insertElementAt(Symbol.intern(vv), ind);
      }
      else if (typ.compareToIgnoreCase("bln") == 0){
        seqval.insertElementAt(Boolean.valueOf(vv), ind);
      }
      else if (typ.compareToIgnoreCase("int") == 0){
        seqval.insertElementAt(Integer.valueOf(vv), ind);
      }
      else if (typ.compareToIgnoreCase("flt") == 0){
        seqval.insertElementAt(Double.valueOf(vv), ind);
      }
      else System.out.println("Failed to formalizing a sequence value.");
    }
    return seqval;
  }


  /*
   * Method to close resourses without exit the bridge
   */
  private void releaseResources(){
    try {
      //Gracefully close down JMS connection resources
      if (mSubscriber != null) mSubscriber.close();
      if (mReceiver != null) mReceiver.close();
      //close connection resource
      this.jmsSetStatus(Symbol.intern("DISCONNECTED"));
      //if (mG2connection != null) mG2connection = null;
      if (mTConnection != null) mTConnection.close();
      if (mQConnection != null) mQConnection.close();
    }catch (javax.jms.JMSException jmse){
      jmse.printStackTrace();
    }catch (G2AccessException ge){ge.printStackTrace();}
  }


  /*
   * Method to close resourses and exit from the program execution
   */
  private void exit(){
    //Gracefully exit, close system resources
    try {
      //Gracefully close down JMS connection resources
      if (mSubscriber != null) mSubscriber.close();
      if (mReceiver != null) mReceiver.close();
      //close the durable subscription
      //mTSession.unsubscribe("Input Subscription");
      if (mTConnection != null) mTConnection.close();
      if (mQConnection != null) mQConnection.close();
      this.jmsSetStatus(Symbol.intern("DISCONNECTED"));
      mG2connection.closeConnection();
    }catch (javax.jms.JMSException jmse){
      jmse.printStackTrace();
      System.exit(0);
    }catch (G2AccessException ge){
      ge.printStackTrace();
    }
    System.exit(0);
  }


  /*
   * Gets the version of JavaLink.
   * (Look at the core.jar->products.dat for the names of the products)
   * If the product cannot be found, an exception of class UnknownProductException is thrown, but that is a private class.
   */
  public static String getJavaLinkVersion(){
    String productName = "javalink";
    String version = "none";
    try{
      com.gensym.core.Product product = com.gensym.core.ProductManager.getProduct(productName);
      if (product != null){
        version = product.getDisplayVersion();
      }
    }
    catch (Exception ex) {
      version = "the product named '"+ productName + "' is unknown";
    }
    return version;
  }


  /**
   *main method
   */
  public static void main(String args[]){

    System.out.println();
          System.out.println("+--------------------------------------------------+");
          System.out.println("");
          System.out.println("    G2 Java Message Service (JMS) Bridge          ");
	  System.out.println("    " + G2Version.VERSION_INFORMATION + " (Build " + G2Version.BUILD_INFORMATION + ")");
	  System.out.println("");
	  System.out.println("    " + G2Version.COPYRIGHT_INFORMATION + "        ");
	  System.out.println("");
          System.out.println("+--------------------------------------------------+");
          System.out.println("");
    System.out.println("JavaLink version: " + G2Jms.getJavaLinkVersion());

    // Initialize the G2 listener
    CmdLineArgHandler cmdline = new CmdLineArgHandler(args, G2Jms.allowedCmdLineParams, true);
    try{
      mPort = (int) cmdline.getOptionLong(new String("-port"), 22070);
      new java.net.ServerSocket(mPort).close();
      G2Gateway.initialize(mPort);
    }
    catch(IOException ioe){
      System.err.println("Error: TCP port "+mPort+" initialization failed");
      System.exit(1);
    }
    catch(AlreadyInitializedException aie){
      System.err.println("Error: TCP port "+mPort+" already initialized");
      System.exit(1);
    }

    // Deal with unsolicited connection request from G2 through a Cnx Handler Factory object
    G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory(){
    // Implementation of the Cnx Handler Factory method
      public G2Connection createG2Connection(String cnx_data){
        G2Gateway mG2connectionLocal = new G2Gateway();
        new G2Jms(mG2connectionLocal, cnx_data);
        return mG2connectionLocal;
      }
    });

    G2Gateway.startup();
//    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
//      "\n\n\nJMS_Bridge listening for G2 connection on port: "+port);
    System.out.println("\nG2-JMS bridge...started...listening for G2 connection on port: "+
                       mPort+"\n");
  }


  /**
   * <p>Title: G2-JMS Bridge</p>
   * <p>Description: An inner class to handle configuration of a GSI object at G2</p>
   * <p>Copyright: Copyright (c) 2002</p>
   * <p>Company: Gensym Corporation</p>
   * @author Frank Wu
   * @version Alpha v1.0
   */
  class GsiJms {
    private boolean mJmsDurableSub = false;
    private boolean mJmsLocalCopy = false;
    private boolean mJmsTranDelivery = false;
    private boolean mJmsSyncDelivery = false;
    private int mJmsAckMode = javax.jms.Session.AUTO_ACKNOWLEDGE;
    private int mJmsPersist = javax.jms.Message.DEFAULT_DELIVERY_MODE;
    private int mJmsMsgPriority = javax.jms.Message.DEFAULT_PRIORITY;
    private long mJmsMsgTOL = javax.jms.Message.DEFAULT_TIME_TO_LIVE;
    private String mJmsInitCntxFactory = "";
    private String mJmsProviderURL = "";
    private String mJmsTopConFactory = "";
    private String mJmsQueConFactory = "";
    private String mJmsInbox = "";
    private String mJmsOutbox = "";
    private String mJmsDestType = "";
    private String mJmsSelector = "";
    private String mJmsSubName = "";
    private String mJmsClientID = "";
    private String mJmsUsername = "";
    private String mJmsPassword = "";
    private String mJmsStringProperty;
    private String mJmsIntProperty;
    private String mJmsBooleanProperty;
    private String mJmsDoubleProperty;
    private String mJmsFloatProperty;
    private String mJmsByteProperty;
    private String mJmsLongProperty;
    private String mJmsShortProperty;
    private String mJmsObjectProperty;
    private Symbol mJmsDeliveryMode = Symbol.intern("JMS-DELIVERY-MODE");
    private Symbol mJmsPriority = Symbol.intern("JMS-PRIORITY");
    private Symbol mJmsTimeToLive = Symbol.intern("JMS-TIME-TO-LIVE");
    private Symbol mJmsCorrelationID = Symbol.intern("JMS-CORRELATION-ID");
    private Symbol mJmsType = Symbol.intern("JMS-TYPE");

    public GsiJms(Structure gsiConfig){
      try{
        mJmsInitCntxFactory = gsiConfig.getAttributeValue(Symbol.intern("JMS-INITIAL-CONTEXT-FACTORY")).toString();
        mJmsProviderURL = gsiConfig.getAttributeValue(Symbol.intern("JMS-PROVIDER-URL")).toString();
        mJmsTopConFactory = gsiConfig.getAttributeValue(Symbol.intern("JMS-TOPIC-CONNECTION-FACTORY")).toString();
        mJmsQueConFactory = gsiConfig.getAttributeValue(Symbol.intern("JMS-QUEUE-CONNECTION-FACTORY")).toString();
        mJmsDestType = gsiConfig.getAttributeValue(Symbol.intern("JMS-DESTINATION-TYPE")).toString();
        mJmsInbox = gsiConfig.getAttributeValue(Symbol.intern("JMS-INPUT-DESTINATION-NAME")).toString();
        mJmsOutbox = gsiConfig.getAttributeValue(Symbol.intern("JMS-OUTPUT-DESTINATION-NAME")).toString();
        mJmsSelector = gsiConfig.getAttributeValue(Symbol.intern("JMS-INPUT-DESTINATION-SELECTOR")).toString();
        mJmsDurableSub = "true".equals(gsiConfig.getAttributeValue(Symbol.intern("JMS-DURABLE-TOPIC-SUBSCRIPTION")).toString());
        mJmsSubName = gsiConfig.getAttributeValue(Symbol.intern("JMS-DURABLE-SUBSCRIPTION-NAME")).toString();
        mJmsLocalCopy = "true".equals(gsiConfig.getAttributeValue(Symbol.intern("JMS-TOPIC-RECEIVE-LOCAL-COPY")).toString());
        mJmsTranDelivery = "true".equals(gsiConfig.getAttributeValue(Symbol.intern("JMS-TRANSACTED-DELIVERY")));
        mJmsAckMode = gsiConfig.getAttributeValue(Symbol.intern("JMS-ACKNOWLEDGE-MODE")).equals(Symbol.intern("CLIENT_ACKNOWLEDGE"))
        		? Session.CLIENT_ACKNOWLEDGE : Session.AUTO_ACKNOWLEDGE;
        mJmsAckMode = gsiConfig.getAttributeValue(Symbol.intern("JMS-ACKNOWLEDGE-MODE")).equals(Symbol.intern("DUPS_OK_ACKNOWLEDGE")) 
        		? Session.DUPS_OK_ACKNOWLEDGE : mJmsAckMode;
        
        mJmsSyncDelivery = "true".equals(gsiConfig.getAttributeValue(Symbol.intern("JMS-SYNCHRONOUS-DELIVERY")).toString());
        mJmsPersist = "true".equals(gsiConfig.getAttributeValue(Symbol.intern("JMS-PERSISTENT-DELIVERY")).toString())
                     	? javax.jms.DeliveryMode.PERSISTENT : javax.jms.DeliveryMode.NON_PERSISTENT;
        Integer priority = (Integer) gsiConfig.getAttributeValue(Symbol.intern("JMS-MESSAGE-PRIORITY"));
        mJmsMsgPriority = priority.intValue();
        Integer timeToLive = (Integer) gsiConfig.getAttributeValue(Symbol.intern("JMS-MESSAGE-ALIVE-TIME"));
        mJmsMsgTOL = timeToLive.intValue();
        mJmsUsername = gsiConfig.getAttributeValue(Symbol.intern("JMS-USERNAME")).toString();
        mJmsPassword = gsiConfig.getAttributeValue(Symbol.intern("JMS-PASSWORD")).toString();
        mJmsClientID = gsiConfig.getAttributeValue(Symbol.intern("JMS-CLIENT-ID")).toString();

        //Check the user configuration value using system printout for now.
        //For improved logging, to be upgraded to use java.util.logging APIs
        //provided in Java SDK 1.4
        if (G2Jms.this.mDebug) System.out.println("**********************");
        if (G2Jms.this.mDebug) System.out.println("initCntxFac="+mJmsInitCntxFactory+
            ", URL="+mJmsProviderURL);
        if (G2Jms.this.mDebug) System.out.println("TopConFac="+mJmsTopConFactory+
            ", QueConFac="+mJmsQueConFactory);
        if (G2Jms.this.mDebug) System.out.println("destType="+mJmsDestType+
            ", inbox="+mJmsInbox+", outbox="+mJmsOutbox);
        if (G2Jms.this.mDebug) System.out.println("selector="+mJmsSelector+
            ", localCopy="+mJmsLocalCopy);
        if (G2Jms.this.mDebug) System.out.println("durableSub="+mJmsDurableSub+
            ", SubscriptionName="+mJmsSubName);
        if (G2Jms.this.mDebug) System.out.println("transDelivery="+mJmsTranDelivery+
            ", ackMode="+mJmsAckMode);
        if (G2Jms.this.mDebug) System.out.println("priority="+mJmsMsgPriority+
            ", tol="+mJmsMsgTOL+", persistentDelivery="+mJmsPersist);
        if (G2Jms.this.mDebug) System.out.println("usr="+mJmsUsername+
            ", pwd="+mJmsPassword+", clientID="+mJmsClientID);
        if (G2Jms.this.mDebug) System.out.println("**********************");
      }catch (NoSuchAttributeException na){ System.out.println(na.toString());
      }
    }
  }
}