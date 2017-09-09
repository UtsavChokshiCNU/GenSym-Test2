package com.gensym.cbu.experimental.cbudataviewer;

import javax.swing.JTable;
import javax.swing.JScrollPane;
import javax.swing.JPanel;
import javax.swing.JFrame;
import java.awt.*;
import java.awt.event.*;
import com.gensym.cbu.messageserver.MessageServerImpl;
import com.gensym.cbu.messageserver.MessageServer;
import com.gensym.cbu.messageserver.Message;
import com.gensym.cbu.messageserver.MessageAlreadyAcknowledgedException;
import com.gensym.cbu.messageserver.MessageImpl;
import com.gensym.cbu.messageserver.MessageServerListener;
import java.rmi.RemoteException;
import javax.swing.table.TableModel;
import javax.swing.table.DefaultTableModel;
import java.util.Date;
import java.util.Vector;


public class MessageServerDemo extends JFrame 
{
  MessageServerImpl messageServerImpl;
  MessageServerMessageCbuDataAdapter adapter;
  CbuJTableDataViewer table;
  CbuPieChartDataViewer pieChart;


  public MessageServerDemo() 
  {
    super("Data Browser Demo");

    messageServerImpl = new MessageServerImpl();
    adapter = new MessageServerMessageCbuDataAdapter();
    messageServerImpl.addMessageServerListener((MessageServerListener)adapter);

    table = new CbuJTableDataViewer();
    table.setPropertiesToDisplay(new String[] {"TargetId", "SenderId", "EventType", "MainText", 
						 "AdditionalText", "Priority", "PublicationDate", 
						 "Acknowledger", "AcknowledgementDate"});

   table.setLabels(new String[] {"Target", "Sender", "Event Type", "Main Text", 
						 "Additional Info", "Priority", "Pub. Date", 
						 "Ack'er", "Ack Date"});

    adapter.addCbuDataAdapterListener((CbuDataAdapterListener)table);

    //    JTable table = new DataBrowserTable((TableModel)messageServerDataBrowserTranslator);
    table.setPreferredScrollableViewportSize(new Dimension(500, 300));
    
    //Create the scroll pane and add the table to it. 
    JScrollPane scrollPane = new JScrollPane(table);
    
    //Add the scroll pane to this window.
    getContentPane().add(scrollPane, BorderLayout.CENTER);
    



    addWindowListener(new WindowAdapter() {
      @Override
      public void windowClosing(WindowEvent e) {
	    System.exit(0);
      }
    });
  }

  public static void main(String[] args) 
  {
    MessageServerDemo frame = new MessageServerDemo();

    frame.pack();
    frame.setVisible(true);

    pause (1000);
    frame.messageServerImpl.addMessage("Mary", "Campione", "Snowboarding", "hello", "world", 1);
    pause (1000);
    frame.messageServerImpl.addMessage("Alison", "Huml", "Rowing", "hello", "world", 2);
    pause (1000);
    frame.messageServerImpl.addMessage("Kathy", "Walrath", "Chasing Toddlers", "hello", "world", 3);
    pause (1000);
    frame.messageServerImpl.addMessage("Mark", "Andrews", "Speed Reading", "hello", "world", 4);
    pause (1000);
    Message m1 = frame.messageServerImpl.addMessage("Angela", "Lih", "Teaching HS", "hello", "world", 10);
    pause (1000);
    frame.messageServerImpl.addMessage("Mary", "Campione", "Snowboarding", "hello", "world", 11);
    pause (1000);
    frame.messageServerImpl.addMessage("Alison", "Huml", "Rowing", "hello", "world", 21);
    pause (1000);
    frame.messageServerImpl.addMessage("Kathy", "Walrath", "Chasing Toddlers", "hello", "world", 31);
    pause (1000);
    frame.messageServerImpl.addMessage("Mark", "Andrews", "Speed Reading", "hello", "world", 41);
    pause (1000);
    frame.messageServerImpl.addMessage("Angela", "Lih", "Teaching HS", "hello", "world", 51);
    pause (1000);

    try
      {
	System.out.println("acknowledging message about Angela w/p 10");
	frame.messageServerImpl.acknowledgeMessage(m1, "Kevin", new Date());
      }
    catch (MessageAlreadyAcknowledgedException e)
      {}
    pause (1000);

    System.out.println("changing acknowledged message about Angela to priority 200");
    frame.messageServerImpl.changeMessagePriority(m1, 200);
    pause (1000);

    System.out.println("deleting acknowledged message about Angela");
    frame.messageServerImpl.deleteMessage(m1);
    pause (1000);

  }

  static public void pause(long millis)
  {
    try{
      Thread.currentThread().sleep(millis);
    }
    catch(InterruptedException e)
      {}
  }
}




