package com.gensym.gda.emailer;



import java.net.Socket;

import java.net.UnknownHostException;

import java.net.InetAddress;

import java.io.Serializable;

import java.io.BufferedReader;

import java.io.PrintWriter;

import java.io.InputStreamReader;

import java.io.OutputStreamWriter;

import java.rmi.Remote;

import java.rmi.RemoteException;

import java.util.Date;



public class gdaMail extends Object implements Serializable, Remote

{



    final static int SMTP_PORT = 25;

    InetAddress clientAddress = null;    

    InetAddress smtpAddress = null;

    ThreadGroup outgoingMail = new ThreadGroup ("Outgoing Mail");

    String clientHostName;

    String smtpHostName;

    String from, to, name;

    String subjectText; 

    String messageText; 

    int status;

    

    public gdaMail (String cmdLineArgs [] ) throws UnknownHostException

    {

        super();

        status = initEmail (cmdLineArgs);

        if (status > 0)    // Wrong number of arguments

            return;

                

        new MailerThread (); 

    }

    

    public static void main (String args [])

    {

        try    { new gdaMail (args); }

        catch (UnknownHostException e)    { System.out.println ("Unknown Host: " + e.getMessage ()); } 

    }

    

    public int initEmail ( String cmdLineArgs [] ) throws UnknownHostException

    {

        if (cmdLineArgs.length  != 6)    // localhost, mailhost, subject, message, from, to

            return 1;

            

        setClientHostName (cmdLineArgs [0]);

        setSmtpHostName (cmdLineArgs [1]);

        subjectText = (cmdLineArgs [2]);

        messageText = (cmdLineArgs [3]);

        setFrom (cmdLineArgs [4]);

        setTo (cmdLineArgs [5]);

  

        return 0;

    }



    public void setSmtpHostName (String smtpHostName) throws UnknownHostException 

    { 

        if (smtpHostName  != "" && smtpHostName != null) 

        {

            this.smtpHostName = smtpHostName; 

            smtpAddress = InetAddress.getByName(this.smtpHostName);

        }

        else

            throw new UnknownHostException ("No mail host was specified");

    }



    public String getSmtpHostName () 

    { 

        return smtpHostName;

    }



    public void setClientHostName (String clientHostName) throws UnknownHostException 

    { 

        if (!(clientHostName.equals("")) && clientHostName != null) 

        {

            this.clientHostName = clientHostName;

            if (this.clientHostName.equals("localhost")) 

                { clientAddress = InetAddress.getLocalHost(); } 

            else 

                { clientAddress = InetAddress.getByName(this.clientHostName); }

        }

        else

            throw new UnknownHostException ("No local host was specified");

    }



    public String getClientHostName () 

    { 

        return clientHostName;

    }



    public String getTo ()

    {

        return to;

    }



    public void setTo (String to)

    {

        // checkEmailAddress (to);

        this.to = to;

    }



    public String getFrom ()

    {

        return from;

    }



    public void setFrom (String from)

    {

        // checkEmailAddress(from);

        this.from = from;

    }

    

    void checkEmailAddress (String address) 
    {
        if (address.indexOf ('@') == -1) 
        {
            //throw InvalidEmailAddress;
        }		     
    } 

    class MailerThread implements Runnable
    {
        public MailerThread ()
        {
            Thread mT = new Thread (this);
            mT.start();
        }

        public void run()
        {
            Socket smtpPipe;
            BufferedReader in;
            PrintWriter out;
            
            try
            {
	smtpPipe = new Socket (smtpAddress, SMTP_PORT);
	in = new BufferedReader (new InputStreamReader (smtpPipe.getInputStream ()));
	out = new PrintWriter (new OutputStreamWriter (smtpPipe.getOutputStream ()));
Thread.sleep (5000);
	System.out.println ("Connecting to: " + smtpAddress);
	System.out.println ("###" + in.readLine ());

	System.out.println ("HELO " + clientAddress);      
	out.println ("HELO " + clientAddress);
	out.flush ();
	System.out.println ("###" + in.readLine ());

	System.out.println ("MAIL FROM:<" + from + ">");
	out.println ("MAIL FROM:<" + from + ">");
	out.flush ();
	System.out.println ("###" + in.readLine ());

	System.out.println ("RCPT TO:<" + to + ">");
	out.println ("RCPT TO:<" + to + ">");
	out.flush ();
	System.out.println ("###" + in.readLine ());

	System.out.println ("DATA");
	out.println ("DATA");
	out.flush ();
	System.out.println ("###" + in.readLine ());

	System.out.println ("To: " + to);
	out.println ("To:" + to);
	out.flush ();
	
	System.out.println ("Subject: " + subjectText);
	out.println ("Subject:" + subjectText);
	out.flush ();

	Date date = new Date ();
	System.out.println ("Date:" + date.toString ());
	out.println ("Date:" + date.toString ());
	out.flush ();

	out.println ("");
	out.flush ();
Thread.sleep (3000);
	System.out.println ("Message: " + messageText);
	out.println (messageText);
	out.flush ();

	System.out.println ("CRLF.CRLF");
	out.println (".");
	out.flush ();
	System.out.println ("###" + in.readLine());
Thread.sleep (3000);
	System.out.println ("QUIT");
	out.println ("QUIT");
	out.println ("");
	out.flush ();
	System.out.println ("###" + in.readLine());
Thread.sleep (3000);
	
	System.out.println ("### End of Transmission ###");
            } 

            catch (Exception e)    { throw new RuntimeException( e.getMessage()); } 

        }  // end run

    }  // end MailerThread

} // end gdaMail

