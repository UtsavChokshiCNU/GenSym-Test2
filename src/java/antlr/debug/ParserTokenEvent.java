package antlr.debug;

public class ParserTokenEvent extends Event {
	public static final int LA=0;
	public static final int CONSUME=1;

	private int value;
	private int amount;

	public ParserTokenEvent(Object source) {
		super(source);
	}
	public ParserTokenEvent(Object source, int type,
	                        int amount, int value) {
		super(source);
		setValues(type,amount,value);
	}
	public int getAmount() {
		return amount;
	}
	public int getValue() {
		return value;
	}
	void setAmount(int amount) {
		this.amount = amount;
	}
	void setValue(int value) {
		this.value = value;
	}
	/** This should NOT be called from anyone other than ParserEventSupport! */
	void setValues(int type, int amount, int value) {
		super.setValues(type);
		setAmount(amount);
		setValue(value);
	}
	public String toString() {
		if (getType()==LA)
			return "ParserTokenEvent [LA," + getAmount() + "," +
			       getValue() + "]"; 
		else
			return "ParserTokenEvent [consume,1," +
			       getValue() + "]"; 
	}
}