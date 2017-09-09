package com.gensym.editor.text;

/**
 * An interface for abstracting the access to a parsing edit context,
 * intended for use by key adapters such as G2TextAreaKeyAdapter.
 * @see G2TextAreaKeyAdapter
 */
public interface ParserController {
  public void accept();
  public void escape();
}
