package type;

import com.gensym.util.Symbol;



/**
 * This class holds logger control symbols
 * @author SoftServe
 *
 */
public class LogFileOperation {

	public static final Symbol CLOSE = 
		Symbol.intern("CLOSE");
	public static final Symbol OPEN = 
		Symbol.intern("OPEN");
	
	private LogFileOperation() {
		
	}
}
