package com.gensym.gda.controls;

import java.lang.NumberFormatException;
import javax.swing.text.Document;
import javax.swing.text.BadLocationException;
import javax.swing.text.PlainDocument;
import javax.swing.text.AttributeSet;

/**
*A document class for text components allowing to enter only integer values
*/
public class IntegerDocument extends PlainDocument { 
    public void insertString(int offs, String str, AttributeSet a) 
        throws BadLocationException { 
        if (str == null) { 
            return;
        } 
        if (str.equals("")){
            super.insertString(offs, str, a); 
            return;
        }
        String txt = getText(0, getLength());
        if (offs < 0 || offs > txt.length())
            throw new BadLocationException("", offs);
        String left = txt.substring(0, offs);
        String right = txt.substring(offs);
        txt = left + str + right;
        try{
            Integer.parseInt(txt);
            super.insertString(offs, str, a);              
            return;
        }catch ( NumberFormatException e) {
            if (txt.equals("-")){
                super.insertString(offs, str, a);  
                return;            
            }    
        }
     } 
 }