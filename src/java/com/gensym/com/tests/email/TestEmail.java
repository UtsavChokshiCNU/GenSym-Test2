package com.gensym.com.tests.email;

import com.gensym.com.beans.maillib.*;
import com.gensym.com.Variant;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXTraceTool;

import java.awt.*;
import java.awt.event.*;

public class TestEmail extends Frame {
  MabryMailctrl mm;
  DMailEventsListener listener = new SmtpListener();
  Button sendButton = new Button("Send");
  Button exitButton = new Button("Exit");
  Variant v1 = new Variant(1);
  public TestEmail() {
    super("SMTP");
    /*
    ActiveXTraceTool tool =  new ActiveXTraceTool();
    tool.setAxTraceLevel((short)40);
    tool.setLogToStdout(true);
    */

    mm = new MabryMailctrl();
		
    add("Center", mm);	
    System.out.println("in smtp");
    add("North",sendButton);
    add("South",exitButton);
    setBounds(80,180,150,150);
    setBackground(Color.white);
    show();
    
    sendButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        try {	
          Send();
        }
        catch (ActiveXException f)
        {
          f.printStackTrace();
        }
      }
    });
    
    exitButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        System.exit(1);
      }
    });
  }
  
  public void Send() 
    throws ActiveXException
  {
    System.out.println("Send called");
    //mm.addDMailEventsListener(listener);
    short s1 = mm.getAxLastError(); 
    mm.setAxBlocking (true);
    
    mm.setAxConnectType (0);
    mm.setAxDebug ((short) 1);
    //mm.setAxAction ((short)11);//create new message
    //mm.setAxHost("drposey-nt");
    //mm.setAxHost("smtp.per-se.com");
    mm.setAxHost("mailhost.gensym.com");
    //mm.setAxTo("dan_posey@drposey-nt");
    mm.setAxTo("ajs@gensym.com");
    //mm.setAxFrom ("Dan Posey <dan.posey@per-se.com>");
    mm.setAxFrom ("Allan Scott <ajs@gensym.com>");
    //mm.setAxEMailAddress("Dan Posey <dan.posey@per-se.com>");
    mm.setAxAction ((short)3);//connect
    mm.setAxTimeout ((short)150);
    System.out.println("after connect");
    System.out.println("last error: " + s1);
    mm.setAxFlags (64);//mailDstIsHost
    Variant v1 = new Variant("This is only a test.");
    mm.setAxSubject("Smtp ActiveX test");
    mm.setAxBody((short)0, v1);
    //mm.setAxBodyCount((short)0);
    //mm.setAxContentTransferEncoding("x-uuencode");
    String body = v1.getStringValue();
    System.out.println("body is: " + body);	
    mm.setAxAction ((short)15);//write message
    //mm.WriteMessage (v1);	
    for(int i = 0; i<=50; i++){}//just waiting for a while	
    mm.setAxAction ((short)8);//disconnect
    System.out.println("last error: " + s1);
	 		
    
		
  }
  
  public static void main(String[] args) {
    TestEmail MM = new TestEmail();
  }  
  
}

class SmtpListener implements DMailEventsListener {
  
  public void Debug(DMailEventsEvent e) {
    System.out.println("in Debug: " + e);
  }
  
  public void AsyncError(DMailEventsEvent e) {
    System.out.println("in Asyncerror: " + e);
  }
  
  public void Progress(DMailEventsEvent e) {
    System.out.println("in Progress: " + e);
  }
  
  public void Done(DMailEventsEvent e) {
    System.out.println("in Done: " + e);
  }
  
}
