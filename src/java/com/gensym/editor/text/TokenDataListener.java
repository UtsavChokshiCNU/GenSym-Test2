/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TokenDataListener.java
 *
 */
package com.gensym.editor.text;


/** This is the listener for TokenData events, which provide information
 * from the Parser about its 'cursor-token', the token that the parser's
 * logical cursor is in.
 *
 * @author David McDonald
 * @version 1.0
  * @undocumented -- final Text Editor API is still under review
 */
interface TokenDataListener extends java.util.EventListener {

  /* This method must be implemented by any TokenDataListener */
  void assimilateTokenData (TokenDataEvent e);

}
