package com.gensym.jgi.download.local;

import com.gensym.core.GensymApplication;
import com.gensym.core.CmdLineArgHandler;

class DownloadLocalInterfacesApplication extends GensymApplication {
  DownloadLocalInterfacesApplication (String[] args) { super(args); }
  CmdLineArgHandler getArgHandler() { return commandLineArguments; }
}

