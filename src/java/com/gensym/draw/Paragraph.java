package com.gensym.draw;

import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Toolkit;

/*
 *
 * Paragraph
 *
 */

public class Paragraph extends Object
{
  protected TextLine startLine = null;
  protected TextLine endLine = null;
  protected int firstIndent = 0;
  protected int subsequentIndent = 0;
  protected int formatWidth = 200;
  private Font font;
  private static boolean breakOnHyphens = true;
  static boolean paragraphDebugP = false;
  static boolean widthCalculationDebugP = false;
  private boolean preferG2CharWidths = false;


  Paragraph (String text, Font font,
	     int formatWidth,
	     int firstIndent, int subsequentIndent,
	     boolean preferG2CharWidths)
    {
      this.font = font;
      this.firstIndent = firstIndent;
      this.subsequentIndent = subsequentIndent;
      this.formatWidth = formatWidth;
      this.preferG2CharWidths = preferG2CharWidths;

      TextLine line = new TextLine(text);
      line.paragraph = this;
      this.startLine = line;
      this.endLine = line;
  }
  
  Paragraph (Font font,
	     int formatWidth,
	     int firstIndent, int subsequentIndent,
	     boolean preferG2CharWidths)
  {
    this.font = font;
    this.firstIndent = firstIndent;
    this.subsequentIndent = subsequentIndent;
    this.formatWidth = formatWidth;
    this.preferG2CharWidths = preferG2CharWidths;
  }

  public static int computeFormattedWidth(String text,
					  int formatWidth,
					  TextStyle style)
  {
    if ("".equals(text))
      return style.first_indent;
    Paragraph testParagraph = new Paragraph(text,
					    style.font,
					    formatWidth,
					    style.first_indent, 
					    style.subsequent_indent,
					    style.preferG2CharWidths);
    Toolkit toolkit = Toolkit.getDefaultToolkit();
    testParagraph.format(toolkit.getFontMetrics(style.font));
    TextLine line = testParagraph.startLine;
    int maxLineWidth = 0;
    boolean isFirst = true;
    do {
      int lineWidth;
      if (isFirst)
	lineWidth = style.first_indent + line.formattedWidth;
      else
	lineWidth = style.subsequent_indent + line.formattedWidth;
      maxLineWidth = Math.max(maxLineWidth,lineWidth);
      line = line.next;
      isFirst = false;
    } while (line != null && !line.equals(testParagraph.endLine));
    return maxLineWidth;
  }

  public void dump(java.io.PrintStream out)
  {
    out.println("Paragraph fwidth ="+formatWidth+" indent1 "+
		firstIndent+" indentn "+subsequentIndent);
    TextLine line = startLine;
    do {
      out.println("  \""+line.text+"\"");
      line = line.next;
    } while (line != null && this.equals(line.paragraph));
  }

  
  protected Paragraph nextParagraph ()
  {
    TextLine nextLine = endLine.next;

    if (nextLine == null)
        return null;
    else
        return nextLine.paragraph;
  }
  
  protected Paragraph previousParagraph ()
  {
    TextLine previousLine = endLine.previous;
 
     if (previousLine == null)
        return null;
    else
        return previousLine.paragraph;
  }

  protected void linkNext(Paragraph paragraph)
  {
    endLine.next = paragraph.startLine;
    paragraph.startLine.previous = endLine;
  }

  protected void addTextLine(TextLine line)
  {
     line.paragraph = this;

     if (startLine == null)
     {
         startLine = line;
         endLine = line;
     }
     else
     {
         endLine.next = line;
         line.previous = endLine;
         endLine = line;
     }
  }

  protected String extractText(TextLine fromLine, int fromIndex,
                               TextLine toLine, int toIndex)

  {
     String res = "";

     if (fromLine.equals(toLine))
       {
	 res = fromLine.text.substring(fromIndex,toIndex);
       }
     else
     {
        StringBuffer buffer = new StringBuffer();
        TextLine line = fromLine;

	do 
	  {
	    int startIndex = ((line.equals(fromLine)) ? fromIndex : 0);
	    int endIndex = ((line.equals(toLine)) ? toIndex : line.text.length());
	    buffer.append(line.text.substring(startIndex,endIndex));
	    if (line.equals(toLine)) {
	    	break;
	    }
	    line = line.next;
	  } while (true);
	res = buffer.toString();
	      
     }
     if (paragraphDebugP) {
       System.out.println(fromLine.text+" From index = "+fromIndex);
       System.out.println(toLine.text+" to index = "+toIndex);
       System.out.println("Extracted Line: "+res);
     }
     return res;
  }

  /**
   * @deprecated pass in a FontMetrics instead.
   * @see #format(FontMetrics)
   */
  public void format(Graphics graphics) {
     graphics.setFont(font);
     FontMetrics metrics = graphics.getFontMetrics();
     format(metrics);
  }

  /** Lays out the paragraph according to the <code>metrics</code>.
   */
  public void format(FontMetrics metrics) {
     Paragraph scratchParagraph 
         = new Paragraph(font,formatWidth,
                        firstIndent,subsequentIndent,preferG2CharWidths);
     int lineWidth = formatWidth - firstIndent;
     int accumulatedWidth = 0;
     int accumulatedWidthAtBreak = 0;
     TextLine line = startLine;
     int index = 0;
     TextLine currentStartLine = startLine;
     int currentStartIndex = 0;
     char ch;
     char lastBreakChar = (char)0;
     int newWidth;
     boolean breakFound = false;
     int charCount = 0;
     int breakCharCount = -1;
     TextLine breakEndLine = null;
     int breakEndIndex = 0;
     int whiteCount = 0;
     boolean isFirstLine = true;

/*     System.out.println("grphcs="+graphics+" fnt="+font); */

     if (startLine.equals(endLine) && startLine.text.equals(""))
       {
	 if (paragraphDebugP)
	   System.out.println("No formatting for empty paragraph ");
	 return;
       }
     int[] charWidths = getG2CharWidthArray();

     while ((line != null) && 
            (index < line.text.length()))
     {
       // System.out.println("loop top "+line.text.substring(0,index));
       ch = line.text.charAt(index);
       if (charWidths != null && (ch > 32) && (ch < 256))
	 newWidth = charWidths[ch];
       else
	 newWidth = metrics.charWidth(ch);

       if (Character.isWhitespace(ch) ||
	   (breakOnHyphens && (ch == '-' || ch == (char)173)))
	 {
	   if (!breakFound ||
	       (charCount != (breakCharCount + 1))) // non-consecutive brk chars.
	     {
	       breakFound = true;
	       accumulatedWidthAtBreak = accumulatedWidth;
	       if (Character.isWhitespace(ch)) 
		 whiteCount = 1;
	       else
		 whiteCount = 0;
	     }
	   else // we have a break followed by another break immediately
	     {
	       if (Character.isWhitespace(lastBreakChar))
		 {
		   if (Character.isWhitespace(ch))
		     whiteCount++;
		   else
		     whiteCount = 0;
		 }
	       else if (Character.isWhitespace(ch))
		 whiteCount = 1;
	     }
         breakEndLine = line;
         breakEndIndex = index + 1;
	 lastBreakChar = ch;
	 breakCharCount = charCount;
       }

       if (widthCalculationDebugP)
	 {
	   System.out.println(accumulatedWidth+" ?< "+lineWidth+
			      " for ch["+index+"]="+ch+" with width "+newWidth);
	 }
       if ((newWidth + accumulatedWidth) > lineWidth)
       {
          if (breakFound)
	    {
	      String text = extractText
		(currentStartLine,currentStartIndex,
		 breakEndLine, breakEndIndex);
	      TextLine newLine = new TextLine(text,
					       text.length() - whiteCount,
					       accumulatedWidthAtBreak);
	      scratchParagraph.addTextLine(newLine);
	      currentStartLine = breakEndLine;
	      currentStartIndex = breakEndIndex;
	      line = breakEndLine;
	      index = breakEndIndex;              
	    }
          else /*  breaking for run-on word */
	    {
              String text = extractText
		(currentStartLine,currentStartIndex,
		 line, index);
              TextLine newLine = new TextLine(text,
					      text.length(),
					      accumulatedWidth+newWidth);
	      
              scratchParagraph.addTextLine(newLine);
              currentStartLine = line;
              currentStartIndex = index;            
	    }
	  if (isFirstLine) {
	    lineWidth = formatWidth - subsequentIndent;
	    isFirstLine = false;
	  }
          breakFound = false;
	  breakCharCount = -1;
          whiteCount = 0;
          accumulatedWidth = 0;
       }
       else if (line.next == null && (index+1 == line.text.length()))
       {
         String text = extractText
                             (currentStartLine,currentStartIndex,
                              line, index+1);    
         TextLine newLine = new TextLine(text,
					 text.length(),
					 accumulatedWidth + newWidth);

         scratchParagraph.addTextLine(newLine);
       }
       else
	 {
	   accumulatedWidth += newWidth;
	 }

       index++;
       // can be greater if line break occurs at end input line
       if (index >= line.text.length()) 
       {
         line = line.next;
         index = 0;
       }
     } 

     if (paragraphDebugP)
       System.out.println("after main format loop");
     startLine = scratchParagraph.startLine;
     endLine = scratchParagraph.endLine;
     line = startLine;
     while (true)
     {
       line.paragraph = this;
       if (line.equals(endLine))
           break;
       line = line.next;
     }
     if (paragraphDebugP)
       System.out.println("after copy loop");
  }

  private int[] getG2CharWidthArray()
  {
    if (preferG2CharWidths)
      {
	switch (com.gensym.ntw.util.G2FontMap.getMatchingG2FontSize (font.getSize()))
	  {
	  case 14: return G2FontWidths.HM14;
	  case 18: return G2FontWidths.HM18;
	  case 24: return G2FontWidths.HM24;
	  default: return null;
	  }
      }
    else
      return null;
  }

  public void dispose() {
    this.startLine = null;
    this.endLine = null;
    this.font = null;
  }

}
