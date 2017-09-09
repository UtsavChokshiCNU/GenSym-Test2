 /*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TW2DefaultCommandLineHandler.java
 *
 */
package com.gensym.shell.util;

import java.util.Properties;

import com.gensym.clscupgr.ModuleManager;
import com.gensym.clscupgr.gms.GMSModuleHandlerFactory;
import com.gensym.clscupgr.ModuleHandlerFactoryAlreadyRegisteredException;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.LoginRequest;
import com.gensym.util.Symbol;

/**
 * Parses all the CommandLine arguments supported by Telewindows2Toolkit
 * and initializes the appropriate states.
 */
public class TW2DefaultCommandLineHandler {

  private TwConnectionInfo connectionInfo = null;
  private LoginRequest loginRequest = null;

  TW2DefaultCommandLineHandler(String[] args) {
    CmdLineArgHandler handler = new CmdLineArgHandler(args);
    String url   = handler.getOptionValue ("-url");
    String host  = handler.getOptionValue ("-host");
    String port  = handler.getOptionValue ("-port");
    String userName = handler.getOptionValue("-userName");
    String mode = handler.getOptionValue("-userMode");
    String password = handler.getOptionValue("-password");
    String okFile = handler.getOptionValue("-ok");

    if ( okFile != null ) {
      /* If we don't do this, the next LoginRequest to be made will default
       * to the value (if any) in its .com.gensym.properties whereas this
       * command line value should override it. */
      Properties sysProps = System.getProperties();
      sysProps.put("com.gensym.resources.okFile", okFile);
    }
    
    if ((host != null) && (port != null))
      connectionInfo = new TwConnectionInfo(url, host, port);

    Symbol userName_ = null;
    Symbol mode_ = null;
    Symbol password_ = null;
    if (userName != null) userName_ = Symbol.intern(userName);
    if (mode != null) mode_ = Symbol.intern(mode);
    if (password != null) password_ = Symbol.intern(password);
    loginRequest = new LoginRequest(mode_, userName_, password_, okFile);
  }

  /**
   * @return the TwConnectionInfo created from parsing the command 
   * line arguments (url, host, port)
   */
  public TwConnectionInfo getG2ConnectionInformation() {
    return connectionInfo;
  }

  /**
   * @return the LoginRequest created from parsing the command
   * line arguments (mode, user-name, password) 
   */
  public LoginRequest getLoginRequest(){
    return loginRequest;
  }
}
