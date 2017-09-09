
package com.gensym.demos.singlecxnsdiapp;

import com.gensym.ui.Command;
import com.gensym.ui.CommandListener;
import java.awt.Frame;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;

public class ExitCommandImpl implements Command {

  private static final String EXIT = "exit";

  private static Resource i18nShort = Resource.getBundle ("com/gensym/demos/wksppanel/ShortCommandLabels");

  private static Resource i18nLong  = Resource.getBundle ("com/gensym/demos/wksppanel/LongCommandLabels");

  private static final Class thisClass = ExitCommandImpl.class;

  private TwAccess connection = null;

  public ExitCommandImpl (Frame frame) {
    WindowListener windowClosingAdapter = new WindowAdapter() {
       @Override
       public void windowClosing(WindowEvent e) {
	 exitApp();
       }
     };
    frame.addWindowListener(windowClosingAdapter);
  }

  public void setConnection(TwAccess cxn){
    connection = cxn;
  }

  public void exitApp() {
    if (connection != null)
      connection.closeConnection();
    System.exit (0);
  }

  @Override
  public void actionPerformed(ActionEvent e) {
    exitApp();
  }


  @Override
  public boolean isImmediate(String key){
    return true;
  }

  @Override
  public boolean isAvailable (String cmdKey) {
    return true;
  }

  @Override
  public String[] getKeys() {
    return new String[] {EXIT};
  }

  @Override
  public String getDescription (String cmdKey, String key) {
    if (!cmdKey.equals (EXIT))
      throw new IllegalArgumentException ("Unsupported key - " + cmdKey);
    if (key.equals (Command.SHORT_DESCRIPTION))
      return i18nShort.getString (cmdKey);
    else
      return i18nLong.getString (cmdKey);
  }

  @Override
  public Image getIcon (String cmdKey, String key) {
    if (!cmdKey.equals (EXIT))
      throw new IllegalArgumentException ("Unsupported key - " + cmdKey);
    if (key.equals (Command.SMALL_ICON))
      return Toolkit.getDefaultToolkit().getImage(getClass().getResource (cmdKey + "small.gif"));
    else
      return Toolkit.getDefaultToolkit().getImage(getClass().getResource (cmdKey + "large.gif"));
  }

  @Override
  public Boolean getState(String cmdKey) {
    return null;
  }

  @Override
  public void addCommandListener (CommandListener listener) {
    // Do nothing.
  }

  @Override
  public void removeCommandListener (CommandListener listener) {
    // Do nothing.
  }

  @Override
  public String toString() {
    return "Exit Command";
  }
}
