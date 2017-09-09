package com.gensym.nols.util;

import java.util.*;
import java.awt.*;
import java.io.*;

public class Parser {
	
	public Parser() {
		super();
	}

	public static final Vector string2Strings(String S, String separator){	
		if(separator.equals(String.valueOf('\u0020'))){
			return string2StringsWhiteSpace(S);
		}
		else{
			return string2StringsNonWhiteSpace(S,separator);
		}
	}

	private static final Vector string2StringsNonWhiteSpace(String S, String separator){		
		Vector stElements = new Vector() ;
		int stringLength = S.length();
		if (stringLength == 0){
			return stElements;
		}
		int searchAt=0;  // beginning of search field
		int sepIndex;  // beginning of next token
		int sepLength = separator.length();
		while(searchAt <= stringLength) {
			sepIndex = S.indexOf(separator,searchAt);
			if(sepIndex==-1) {  // last token
				stElements.addElement(S.substring(searchAt,stringLength).trim());   // eliminate trim?
				break;
			} else {
				stElements.addElement(S.substring(searchAt,sepIndex).trim());  // eliminate trim?
				searchAt = sepIndex + sepLength;
			}
		}
		return stElements; 
	}

	private static final Vector string2StringsWhiteSpace(String S) {
		// Separates S using series of whitespace characters as delimiter
		// Multiple consecutive whitespace characters constitutes ONE (!) separator
		char space = '\u0020';
		Vector stElements = new Vector();
		int stringLength = S.length();
		if (stringLength == 0) {
			return stElements;
		}
		int startReal = -1;  // location of "real" (non-white) characters
		int endReal = -1;
		boolean reading = false;
		// might want to create a char array for faster access instead of S.charAt(i)?
		for(int i=0;i<stringLength;i++) {
			if(S.charAt(i) != space) {   // Possibly change to > to consider all white space characters?
				// a real character
				if(!reading) {
					startReal = i; 
					reading = true;
				}
			} else {
				// a whitespace character
				if(reading) {
					endReal = i;
					reading = false;
					stElements.addElement(S.substring(startReal,endReal));
				}
			}
		}
		if(reading) {
			stElements.addElement(S.substring(startReal,stringLength));
		}
		return stElements;
	}
}
