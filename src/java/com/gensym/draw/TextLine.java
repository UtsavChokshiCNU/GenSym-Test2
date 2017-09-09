package com.gensym.draw;

import java.lang.Object;

/*
 *
 * TextLine
 *
 */

class TextLine extends Object
{
  protected String text;
  protected TextLine previous = null;
  protected TextLine next = null;
  protected Paragraph paragraph = null;
  protected int activeLength = 0;
  int formattedWidth = 0;


  public TextLine(String text)
  {
    this.text = text;
    activeLength = text.length();
  }

  public TextLine(String text, int activeLength,
		  int formattedWidth)
  {
    this.text = text;
    this.activeLength = activeLength;
    this.formattedWidth = formattedWidth;
  }

  public void dispose() {
    this.text = null;
    this.next = null;
    this.previous = null;
    this.paragraph = null;
  }

}
