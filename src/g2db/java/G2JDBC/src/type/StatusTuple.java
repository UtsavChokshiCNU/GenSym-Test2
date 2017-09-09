package type;

import com.gensym.util.Symbol;

/**
 * This class presents canonical return value type
 * which is used by all bridge interface functions
 * @author SoftServe
 *
 */
public class StatusTuple {

	public Symbol getStatus() {
		return status;
	}

	public Integer getCode() {
		return code;
	}

	public String getText() {
		return text;
	}

	private Symbol status = null;
	private Integer code = 0;
	private String text = null;
	
	public StatusTuple(Symbol status, Integer code, String text) {
		this.status = status;
		this.code = code;
		this.text = text;
	}
	
}
