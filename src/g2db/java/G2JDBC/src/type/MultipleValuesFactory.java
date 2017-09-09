package type;

import com.gensym.jgi.MultipleValuesHolder;

/**
 * Utility class for filling MultipleValuesHolder type
 * @author SoftServe
 *
 */
public class MultipleValuesFactory {

	public static MultipleValuesHolder create3(Object o1, Object o2, Object o3) {
		MultipleValuesHolder mvh = new MultipleValuesHolder();
		mvh.add(o1);
		mvh.add(o2);
		mvh.add(o3);
		mvh.add(0);
		mvh.add(0);
		return mvh;
	}
	
	public static MultipleValuesHolder create4(Object o1, Object o2, Object o3, Object o4) {
		MultipleValuesHolder mvh = new MultipleValuesHolder();
		mvh.add(o1);
		mvh.add(o2);
		mvh.add(o3);
		mvh.add(o4);
		mvh.add(0);
		mvh.add(0);
		return mvh;
	}
	
	public static MultipleValuesHolder create5(Object o1, Object o2, Object o3, Object o4, Object o5) {
		MultipleValuesHolder mvh = new MultipleValuesHolder();
		mvh.add(o1);
		mvh.add(o2);
		mvh.add(o3);
		mvh.add(o4);
		mvh.add(o5);
	    return mvh;
	}

	public static MultipleValuesHolder create6(Object o1, Object o2, Object o3, Object o4, Object o5, Object o6) {
		MultipleValuesHolder mvh = new MultipleValuesHolder();
		mvh.add(o1);
		mvh.add(o2);
		mvh.add(o3);
		mvh.add(o4);
		mvh.add(o5);
		mvh.add(o6);		
		return mvh;
	}
}
