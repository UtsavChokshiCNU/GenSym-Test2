package com.gensym.tests.jgi.testharness;

import java.util.*;
import java.io.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;
import com.gensym.core.CmdLineArgHandler;

public class MailSender {

  public static void send(String host,
			  String from,
			  String[] to,
			  String subject,
			  String message) 
       throws MessagingException
  {	
    if (to == null || (to != null && to.length == 0))
      throw new MessagingException("No Recipients specified");
    host = (host == null ? "hqmail" : host);
    boolean debug = true;
    message = message+"\n";

    // create some properties and get the default Session
    Properties props = System.getProperties();
    props.put("mail.smtp.host", host);
    
    Session session = Session.getDefaultInstance(props, null);
    session.setDebug(debug);
    
    try {
      //*******************************************************
      // Additional recipients may be added to this array here.
      //*******************************************************
      InternetAddress[]  addresses = new InternetAddress[to.length];
      for (int i = 0; i<to.length; i++) {
	addresses[i] = new InternetAddress(to[i]);
      };
      
      // create a message
      MimeMessage msg = new MimeMessage(session);
      msg.setFrom(new InternetAddress(from));
      msg.setRecipients(Message.RecipientType.TO, addresses);
      msg.setSubject(subject);
      
      // create and fill the first message part
      MimeBodyPart mbp1 = new MimeBodyPart();
      mbp1.setText(message);
      
      // create the second message part
      //    MimeBodyPart mbp2 = new MimeBodyPart();
      
      // attach the file to the message
      //  FileDataSource fds=new FileDataSource(filename);
      //  mbp2.setDataHandler(new DataHandler(fds));
      //  mbp2.setFileName(filename);
      
      // create the Multipart and its parts to it
      Multipart mp = new MimeMultipart();
      mp.addBodyPart(mbp1);
      //	    mp.addBodyPart(mbp2);
      
      // add the Multipart to the message
      msg.setContent(mp);
      
      // set the Date: header
      msg.setSentDate(new Date());
      
      // send the message
      Transport.send(msg);
      
    } catch (MessagingException mex) {
      mex.printStackTrace();
      Exception ex = null;
      if ((ex = mex.getNextException()) != null) {
	ex.printStackTrace();
      }
      throw mex;
    }
  }


  public static void main(String[] args) {

    CmdLineArgHandler cmdLine = new CmdLineArgHandler(args);
    
    String host = cmdLine.getOptionValue("-host");
    String from = cmdLine.getOptionValue("-from");
    String[] to = cmdLine.getOptionValues("-to");
    String subject = cmdLine.getOptionValue("-subject");
    String message = cmdLine.getOptionValue("-message");
    

    if (to == null || from == null || subject == null || message == null) {
      System.out.println("usage: java ReportSender -from <sender> -to <recipient>[,<recipient>] -subject <subject> -message <msg> [-host <mail host name>]");
      System.exit(1);
    }

    try {
      MailSender.send(host,
		      from,
		      to,
		      subject,
		      message);
      
      
    } catch (MessagingException mex) {
      mex.printStackTrace();
      Exception ex = null;
      if ((ex = mex.getNextException()) != null) {
	ex.printStackTrace();
      }
    }
  }
}

