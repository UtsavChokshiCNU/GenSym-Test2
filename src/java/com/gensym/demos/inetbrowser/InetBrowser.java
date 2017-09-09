package com.gensym.demos.inetbrowser;

import com.gensym.demos.inetbrowser.shdocvw.WebBrowser;
import com.gensym.demos.inetbrowser.shdocvw.DWebBrowserEventsListener; 
import com.gensym.demos.inetbrowser.shdocvw.DWebBrowserEventsEvent; 

import com.gensym.com.ActiveXException;
import com.gensym.com.Variant;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Panel;
import java.awt.Frame;
import java.awt.Color;
import java.awt.Button;
import java.awt.Label;
import java.awt.TextField;

public class InetBrowser extends Panel implements WindowListener 
{
  private WebBrowser browser;
  private Button back;
  private Button forward;
  private Button home;
  private Button refresh;
  private TextField url;
  private Label urlLabel;
  private Panel topPanel;
  private Panel bottomPanel;

  public InetBrowser()
  {
    ActionListener actionListener = new InetBrowserActionListener();
    setLayout(new BorderLayout(0, 5));

    Panel topPanel = new Panel();
    
    home = new Button("Home");
    back = new Button("Back");
    forward = new Button("Forward");
    refresh = new Button("Refresh");

    home.addActionListener(actionListener);
    back.addActionListener(actionListener);
    forward.addActionListener(actionListener);
    refresh.addActionListener(actionListener);

    topPanel.add(home);
    topPanel.add(back);
    topPanel.add(forward);

    add(topPanel,"North");
    
    browser = new WebBrowser();

    add(browser, "Center");
    
    Panel bottomPanel = new Panel();
    
    urlLabel = new Label("URL:", Label.LEFT);
    url = new TextField("http://www.gensym.com/java") {
            @Override
            public Dimension getMinimumSize() {
              return getPreferredSize(); 
            }
            @Override
            public Dimension getPreferredSize() {
              return new Dimension(250, 20); 
            }      
    };
    url.addActionListener(actionListener);

    bottomPanel.add(urlLabel);
    bottomPanel.add(url);
    bottomPanel.add(refresh);

    add(bottomPanel,"South");
  }

  public void navigateToCurrentURL() throws ActiveXException
  {
    browser.Navigate(url.getText());
    DWebBrowserEventsListener listener = new InetBrowserNavigateListener();
    browser.addDWebBrowserEventsListener(listener);
  }

  //************ Configuring dimensions *********************
  
  @Override
  public Dimension getMinimumSize() 
  {
    return getPreferredSize();
  }
  
  @Override
  public Dimension getPreferredSize() 
  {    
    return new Dimension(500, 400);
  }

  //*************** ActionListener for button actions *****

  class InetBrowserActionListener implements ActionListener 
  {
    @Override
    public void actionPerformed(ActionEvent event) {
      Object cmdSource = (Object)event.getSource ();
      
      if (cmdSource == back) 
      {
         System.out.println("BACK");
         try {
           browser.GoBack();
         }
         catch (ActiveXException e) {
            System.out.println("BACK failed");
         }
      }
      else if (cmdSource == forward) {
        System.out.println("FORWARD");
        try {
          browser.GoForward();
        }
        catch (ActiveXException e) {
          System.out.println("FORWARD failed");
        }
      }
      else if (cmdSource == home) {
         System.out.println("HOME");
         try {
          browser.GoHome();
         }
         catch (ActiveXException e) {
           System.out.println("HOME failed");
         }
      }
      else if (cmdSource == refresh) {
         System.out.println("REFRESH");
         try {
          browser.Refresh();
         }
         catch (ActiveXException e) {
           System.out.println("HOME failed");
         }
      }
      else if (cmdSource == url) {
        String newUrl = url.getText();
        System.out.println("NAVIGATE");
        try {
          browser.Navigate(newUrl);
        }
        catch (ActiveXException e) {
          System.out.println("HOME failed");
        }
      }
    }
  }

  // ************** Changes to the URL *******************

  class InetBrowserNavigateListener implements DWebBrowserEventsListener 
  {
  
  public void BeforeNavigate (DWebBrowserEventsEvent e) 
  {
  }

  public void NavigateComplete (DWebBrowserEventsEvent e)
  {
    Variant[] arguments;
    Variant arg;
    String newUrl;

    arguments = e.getArguments();
    arg = arguments[0];
    newUrl = arg.getStringValue();
    url.setText(newUrl);
  }

  public void StatusTextChange (DWebBrowserEventsEvent e) {}

  public void ProgressChange (DWebBrowserEventsEvent e) {}

  public void DownloadComplete (DWebBrowserEventsEvent e) {}

  public void CommandStateChange (DWebBrowserEventsEvent e){}

  public void DownloadBegin (DWebBrowserEventsEvent e) {}

  public void NewWindow (DWebBrowserEventsEvent e) {}

  public void TitleChange (DWebBrowserEventsEvent e) {}

  public void FrameBeforeNavigate (DWebBrowserEventsEvent e) {}

  public void FrameNavigateComplete (DWebBrowserEventsEvent e) {}

  public void FrameNewWindow (DWebBrowserEventsEvent e) {}

  public void Quit (DWebBrowserEventsEvent e) {}

  public void WindowMove (DWebBrowserEventsEvent e) {}

  public void WindowResize (DWebBrowserEventsEvent e) {}

  public void WindowActivate (DWebBrowserEventsEvent e) {}

  public void PropertyChange (DWebBrowserEventsEvent e) {}

  }      

  //***************  Testing Code ************************

  public static void main(String[] args) {
    Frame frame =  new Frame("InetBrowser");
    
    try {
      InetBrowser inetBrowser = new InetBrowser();
      frame.add(inetBrowser);
      inetBrowser.setBackground(Color.lightGray);
      frame.setSize(inetBrowser.getPreferredSize());
      frame.addWindowListener(inetBrowser);
      frame.show();
      inetBrowser.navigateToCurrentURL();
      }
      catch(Exception e) {
        e.printStackTrace();
        System.out.println("Failure : " + e);
      }      
    }    


    @Override
    public void windowOpened(WindowEvent e) {
    }

    @Override
    public void windowClosing(WindowEvent e) {
        System.exit(0);
    }
    
    @Override
    public  void windowClosed(WindowEvent e) {
        System.exit(0);
    }

    @Override
    public void windowIconified(WindowEvent e) {
    }

    @Override
    public  void windowDeiconified(WindowEvent e) {
    }


    @Override
    public  void windowActivated(WindowEvent e) {
    }

    @Override
    public void windowDeactivated(WindowEvent e) {
    }

}
