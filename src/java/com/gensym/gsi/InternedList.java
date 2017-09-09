
package com.gensym.gsi;

public class InternedList {

    static HashMap table = new HashMap();

    Object value;
    List plist = null;

    @Override
    public int hashCode() {
	if (value == null) return 0;
	return value.hashCode();
    }

    private InternedList(object obj) {
	value = obj;
    }

    public static InternedList intern(Object obj) {
	InternedList result = table.get(obj);
	if (result == null) {
	    result = new InternedList(obj);
	    table.put(obj,result);
	}
	return result;
    }

    public Object value() {
	return value;
    }

}
