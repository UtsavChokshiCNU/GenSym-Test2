package com.gensym.jgi.download;

import com.gensym.core.GensymApplication;
import com.gensym.core.CmdLineArgHandler;

class DownloadInterfacesApplication extends GensymApplication {
  DownloadInterfacesApplication (String[] args) { super(args); }
  CmdLineArgHandler getArgHandler() { return commandLineArguments; }
}

