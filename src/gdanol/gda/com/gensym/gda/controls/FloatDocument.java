package com.gensym.gda.controls;

import java.lang.NumberFormatException;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import javax.swing.text.Document;
import javax.swing.text.BadLocationException;
import javax.swing.text.PlainDocument;
import javax.swing.text.AttributeSet;
import com.gensym.message.Resource;

/**
*A document class for text components allowing to enter only float values
*/
public class FloatDocument extends PlainDocument { 
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
            Double.parseDouble(txt);
            super.insertString(offs, str, a);              
            return;
        }catch ( NumberFormatException e) {
            if (txt.equals("-")){
                super.insertString(offs, str, a);  
                return;            
            }
            NumberFormat format = NumberFormat.getNumberInstance(Resource.getDefaultLocale());
            char decSeparator = '.';
            if (format instanceof DecimalFormat)
                decSeparator = ((DecimalFormat)format).getDecimalFormatSymbols().getDecimalSeparator();
            if (txt.indexOf(decSeparator) == (txt.length() - 1)){
                super.insertString(offs, str, a);  
                return;            
            }    
        }
     } 
 }