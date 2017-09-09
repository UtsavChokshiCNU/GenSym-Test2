package com.gensym.cbu.messageserver;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Date;
import java.beans.PropertyChangeListener;

public interface Message {

  public String getTargetId();

  public String getSenderId();

  public String getEventType();
  
  public String getMainText();
  
  public String getAdditionalText();
  
  public int getPriority();

  public Date getPublicationDate();

  public String getAcknowledger() throws MessageNotAcknowledgedException;

  public Date getAcknowledgementDate() throws MessageNotAcknowledgedException;

  public MessageServer getMessageServer();
}
