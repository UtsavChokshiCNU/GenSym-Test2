package com.gensym.cbu.odie;

import java.net.Socket;
import java.net.UnknownHostException;
import java.net.InetAddress;
import java.io.Serializable;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Date;

public class SmtpResponse extends Object implements Serializable, Response
{
  public SmtpResponse () throws UnknownHostException
  {
    super();
    setSmtpHostName("hqmail.gensym.com");
    setClientHostName("localhost"); 
  }

  String name = "";
  public void setName(String name) 
  {
    this.name = name;
  }

  public String getName () 
  { 
    return name;
  }

  String smtpHostName;

  public void setSmtpHostName (String smtpHostName) 
       throws UnknownHostException 
  { 
    if (smtpHostName  != "" && smtpHostName != null) 
      {
      this.smtpHostName = smtpHostName; 
      smtpAddress = InetAddress.getByName(this.smtpHostName);
    }
  } // end setSmtpHostName

  public String getSmtpHostName () 
  { 
    return smtpHostName;
  }

  InetAddress smtpAddress = null;

  final static int SMTP_PORT = 25;

  InetAddress clientAddress = null;

  ThreadGroup outgoingMail = new ThreadGroup ("outgoing mail");

  String clientHostName = "localhost";

  public void setClientHostName (String clientHostName) 
       throws UnknownHostException 
  { 
    if (!(clientHostName.equals("")) && clientHostName != null) 
      {
	this.clientHostName = clientHostName; 
	if (this.clientHostName.equals("localhost")) 
	  { 
	    clientAddress = InetAddress.getLocalHost();
	  } 
	else 
	  {
	    clientAddress = InetAddress.getByName(this.clientHostName);
	  }
      }
  }//end setClientHostName

  public String getClientHostName () 
  { 
    return clientHostName;
  }

  String to;

  public String getTo()
  {
    return to;
  }

  public void setTo(String to)
  {
    checkEmailAddress(to);
    this.to = to;
  }

  String from;

  public String getFrom()
  {
    return from;
  }

  public void setFrom(String from)
  {
    checkEmailAddress(from);
    this.from = from;
  }

  class ResponseThread implements Runnable
  {
    OdieEvent odieEvent;
    
    public ResponseThread(OdieEvent odieEvent)
    {
      this.odieEvent = odieEvent;
      Thread t = new Thread (this);
      t.start();
    }

    @Override
    public void run()
    {
      Socket smtpPipe;
      BufferedReader in;      
      PrintWriter out;
      
      try {
	smtpPipe = new Socket(smtpAddress, SMTP_PORT);
	in = new BufferedReader(new InputStreamReader(smtpPipe.getInputStream()));
	out = new PrintWriter(new OutputStreamWriter(smtpPipe.getOutputStream()));
	
	System.out.println("Connecting to " + smtpAddress);
	System.out.println("###" + in.readLine());
	
	System.out.println("HELO " + clientAddress);      
	out.println("HELO " + clientAddress);
	out.flush();
	System.out.println("###" + in.readLine());
      
	System.out.println("MAIL FROM:<" + from + ">");
	out.println("MAIL FROM:<" + from + ">");
	out.flush();
	System.out.println("###" + in.readLine());
	
	System.out.println("RCPT TO:<" + to + ">");
	out.println("RCPT TO:<" + to + ">");
	out.flush();
	System.out.println("###" + in.readLine());
	
	System.out.println("DATA");
	out.println("DATA");
	out.flush();
	System.out.println("###" + in.readLine());
	
	System.out.println("To:" + to);
	out.println("To:" + to);
	out.flush();
	
	System.out.println("Subject:" + odieEvent.getMessageText());
	out.println("Subject:" + odieEvent.getMessageText());
	out.flush();
	
	Date date = new Date();
	System.out.println("Date:" + date.toString());
	out.println("Date:" + date.toString());
	out.flush();
	
	out.println("");
	out.flush();

	System.out.println(odieEvent.getAdditionalText());
	out.println(odieEvent.getAdditionalText());
	out.flush();
	
	System.out.println("CRLF.CRLF");
	out.println(".");
	out.flush();
	System.out.println("###" + in.readLine());

	System.out.println("QUIT");
	out.println("QUIT");
	out.println("");
	out.flush();
	System.out.println("###" + in.readLine());
      } 
      catch (Exception e) 
	{ 
	  e.printStackTrace ();
	  throw new RuntimeException( e.getMessage());
	} 
    }
  }

  @Override
  public void respond (OdieEvent odieEvent)
  {
    new ResponseThread(odieEvent);
  }//end respond

  void checkEmailAddress(String address) 
  {
    if (address.indexOf('@') == -1) 
      {
	//throw InvalidEmailAddress;
      }		     
  } //end checkEmailAddress
} // end SmtpClient



