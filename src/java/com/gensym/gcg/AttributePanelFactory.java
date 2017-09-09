package com.gensym.gcg;

import java.util.Locale;
import java.awt.Container;
import com.gensym.jgi.G2AccessException;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.ntw.TwAccess;

public interface AttributePanelFactory {
  public Container generatePanel(TwAccess connection, ItemProxy itemProxy,
				 DialogCommand dialogCommand,
				 Locale locale) throws G2AccessException;

}
