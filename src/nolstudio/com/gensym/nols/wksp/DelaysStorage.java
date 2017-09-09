package com.gensym.nols.wksp;

import java.util.HashMap;
import java.util.Map;
import java.util.TreeSet;
import java.util.Vector;

public class DelaysStorage {

	Map<String, TreeSet<Long>> map = new HashMap<String, TreeSet<Long>>();
	
	public Long[] getDelaysFor(String varName) {
		TreeSet<Long> delays = map.get(varName); 
		return delays == null ? new Long[0] : delays.toArray(new Long[0]);
	}

	public void add(Vector<String> vars, Vector<long[]> delays) {
		for (int i = 0; i < vars.size(); ++i) {
			String var = vars.elementAt(i);
			long[] varDelays = delays.isEmpty() ? new long[] {0l}
					: delays.elementAt(i);
			TreeSet<Long> presentDelays = map.get(var);
			if (presentDelays == null) {
				presentDelays = new TreeSet<Long>();
				map.put(var, presentDelays);
			}
			for (long delay: varDelays) {
				presentDelays.add(delay);
			}
		}
	}

}
