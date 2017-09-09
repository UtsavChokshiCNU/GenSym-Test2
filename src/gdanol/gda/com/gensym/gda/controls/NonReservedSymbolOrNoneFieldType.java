
package com.gensym.gda.controls;

import java.io.IOException;
import java.io.EOFException;
import com.gensym.types.G2TokenizerException;
import com.gensym.types.G2ParserException;
import com.gensym.message.Resource;
import com.gensym.beansruntime.StringVector;


/**
*/
public class NonReservedSymbolOrNoneFieldType extends LowerCaseSymbolFieldType {

	public NonReservedSymbolOrNoneFieldType() {
    }
    		
    public Object stringToObject(String s)
        throws G2TokenizerException, G2ParserException, EOFException, IOException {
			
        	if (reservedSymbols.contains(s.toLowerCase()))
 				throw new G2ParserException("Data input error: the name <s> is reserved symbol");
	//** translate !!!
	
			return super.stringToObject(s);		
		}    
    
    
	protected final static Resource i18n=Resource.getBundle("com.gensym.gda.controls.Messages");
	protected final static StringVector reservedSymbols=new StringVector(new String[]{
		"a", "above", "across",	"ago","all","an","and","any","at",
        "available-frame-vector", "average", "be", "becomes",
        "begin","begin", "below", "between", "by", "call", "case", "change",
        "checking", "collection", "color-pattern", "conclude",
        "connected", "could", "count", "current", "day", "days",
        "deviation", "do", "down", "during", "else", "end", "every",
        "everything", "exists", "exit", "expiration", "false",
        "first", "focus", "for", "format", "giving", "go", "has",
        "hour", "hours", "if", "in", "infer", "input", "integral",
        "interpolated", "invoke", "is", "last", "maximum",
        "minimum", "minute", "moved", "name", "named", "nearest",
        "no", "none", "not", "nothing", "of", "on", "one", "or",
        "output", "over", "past", "per", "product", "rate", "repeat",
        "return", "rules", "same", "second", "seconds", "send",
        "set", "should", "simulated", "standard", "start",
        "subworkspace", "sum", "symbol", "that", "the", "then",
        "there", "this", "to", "true", "undefined", "unspecified",
        "until", "upon", "value", "values", "via", "wait", "was",
        "week", "weeks", "were", "when", "will", "with", "workspace", "yes"
});
}