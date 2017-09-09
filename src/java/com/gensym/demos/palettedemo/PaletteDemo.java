/**
 * This demo shows how to use G2Palettes and GFRPalettes.
 * It should be used with palette-demo.kb
 *
 * After connecting to the G2 running palette-demo.kb, two palettes
 *  will pop up.  Create a new workspace and use the palettes to
 *  place fruit objects on the workspace.
 */


package com.gensym.demos.palettedemo;

import java.awt.*;
import java.awt.event.ActionEvent;
import com.gensym.shell.util.*;
import com.gensym.shell.commands.*;
import com.gensym.mdi.*;
import com.gensym.ui.*;
import com.gensym.ui.menu.*;
import com.gensym.ui.palette.*;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.ntw.util.G2Palette;
import com.gensym.ntw.util.G2ObjectCreator;
import com.gensym.message.Trace;
import com.gensym.clscupgr.gfr.*;
import com.gensym.classes.KbWorkspace;
import com.gensym.util.symbol.*;

public class PaletteDemo extends TW2Application implements G2ClassSymbols{

  private static final Symbol APPLE_ = Symbol.intern("APPLE");
  private static final Symbol ORANGE_ = Symbol.intern("ORANGE");
  private static final Symbol EXAMPLE_GFR_PALETTE_ = Symbol.intern("EXAMPLE-GFR-PALETTE");

  private MDIFrame frame;
  private TwAccess currentConnection;
  private TwConnectionListener loginListener;

  private WorkspaceCommands wkspHandler;
  private ExitCommands exitHandler;

  private G2Palette palette;
  private Dialog fruitPalette;

  private GFRPalette gfrPalette;
  private Dialog gfrFruitPalette;

  public PaletteDemo(String[] cmdLineArgs){
    super(cmdLineArgs);

    frame = new MDIFrame("Palette Demo");
    setCurrentFrame(frame);

    CMenuBar menubar = new CMenuBar();
    CMenu fileMenu = new CMenu("File");
    fileMenu.add(wkspHandler = new WorkspaceCommands(frame, currentConnection));
    fileMenu.add(exitHandler = new ExitCommands(frame, currentConnection));
    menubar.add(fileMenu);
    CMenu g2Menu = new CMenu("G2"); 
    g2Menu.add(new ConnectionCommands(this));
    menubar.add(g2Menu);
    frame.setDefaultMenuBar(menubar);

    loginListener = new LoginAdapter();
    fruitPalette = new Dialog(frame, "Fruit Palette", false);
    gfrFruitPalette = new Dialog(frame, "Gfr Fruit Palette", false);

    frame.setSize(400, 300);
    frame.setVisible(true);
  }

  @Override
  public ConnectionManager getConnectionManager(){
    return null;
  }

  @Override
  public TwAccess getConnection(){
    return currentConnection;
  }

  @Override
  public void setConnection(TwAccess connection){
    if (connection == null)
      setConnection0(connection);
    else{
      if (connection.isLoggedIn())
	setConnection0(connection);
      else
	connection.addTwConnectionListener(loginListener);
    }
  }

  private void setConnection0(TwAccess connection){
    if (currentConnection != null)
      currentConnection.removeTwConnectionListener(loginListener);
    currentConnection = connection;
    wkspHandler.setConnection(connection);
    exitHandler.setConnection(connection);
    if (connection != null){
      try{
	palette = new G2Palette(connection, "Fruit Palette");
	palette.add(new G2ObjectCreator(connection, new Symbol[]{APPLE_, ORANGE_}));
	fruitPalette.add(palette, BorderLayout.CENTER);
	fruitPalette.setVisible(true);
	fruitPalette.setSize(150, 80);
      }
      catch(G2AccessException ex){
	Trace.exception(ex);
      }
      try{
	KbWorkspace wksp = (KbWorkspace)connection.getUniqueNamedItem(KB_WORKSPACE_, EXAMPLE_GFR_PALETTE_);
	gfrPalette = new GFRPalette("GFR Fruit Palette", connection, wksp);
	gfrPalette.setOrientation(Palette.VERTICAL);
        gfrFruitPalette.add(gfrPalette, BorderLayout.CENTER);
	gfrFruitPalette.setVisible(true);
	gfrFruitPalette.setSize(60, 200);
      }
      catch(G2AccessException g2ae){
	Trace.exception(g2ae);
      }
    }
  }

  class LoginAdapter extends TwConnectionAdapter{
    @Override
    public void loggedIn(TwConnectionEvent event){
      TwAccess connection = (TwAccess)event.getSource();
      setConnection0(connection);
    }

    @Override
    public void loggedOut(TwConnectionEvent event){
    }
  }

  public static void main(String[] args){
    PaletteDemo demo = new PaletteDemo(args);
  }
}
  


