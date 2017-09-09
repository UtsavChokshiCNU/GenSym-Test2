
package com.gensym.gda.controls;

import java.io.IOException;
import java.io.EOFException;
import com.gensym.types.SymbolType;
import com.gensym.types.G2TokenizerException;
import com.gensym.types.G2ParserException;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.message.Resource;

/**
Used for validation of text field where the name of object is entered.
Check in the stringToObject if there is an item with the name represented
by the string. If the name exists and it is not a currentName then stringToObject
method throws G2ParserException. 
*/
public class ValidG2NameFieldType extends LowerCaseSymbolFieldType {

	public ValidG2NameFieldType() {
		connection = null;
    }
		public ValidG2NameFieldType(TwAccess twaccess) {
			connection = twaccess;
    }
    
 		/**
 		Connection to g2 process where to search named item
 		*/
    public void setConnection(TwAccess twaccess) {connection = twaccess;}
    
		/**
			If the name of the edited item equals String in stringToObject it is 
			not error.
		*/
    public void setCurrentName(Symbol name) {	currentName = name;}

		public Symbol getCurrentName() {return currentName;}
		
    public Object stringToObject(String s)
        throws G2TokenizerException, G2ParserException, EOFException, IOException {

			Symbol obj = (Symbol) super.stringToObject(s);
			if (obj.equals(currentName))
				return obj;
			try {
				connection.getUniqueNamedItem(itemClass_, obj);
			} catch (G2AccessException e) {
				return obj;
			}
		
			throw new G2ParserException(i18n.getString("ItemWithThisNameAlreadyExists"));
		}    
    
    
	protected static Symbol itemClass_ = Symbol.intern("ITEM");
  	protected TwAccess connection;
  	protected Symbol currentName;
	protected final static Resource i18n=Resource.getBundle("com.gensym.gda.controls.Messages");

}