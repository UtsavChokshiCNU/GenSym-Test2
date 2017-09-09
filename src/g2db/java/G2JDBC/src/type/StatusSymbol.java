package type;

import com.gensym.util.Symbol;

/**
 * Holds return status symbols definitions.
 * @author SoftServe
 *
 */
public class StatusSymbol {

	public static final Symbol SUCCESS = Symbol.intern("SUCCESS");
	public static final Symbol ERROR = Symbol.intern("ERROR");
	public static final Symbol WARNING = Symbol.intern("WARNING");
	public static final Symbol INFO = Symbol.intern("INFO");
	public static final Symbol DISCONNECTED = Symbol.intern("DISCONNECTED");
	public static final Symbol FATAL = Symbol.intern("FATAL");
	public static final Symbol EOCURSOR = Symbol.intern("EOCURSOR");
	
	private StatusSymbol() {
		
	}
}
