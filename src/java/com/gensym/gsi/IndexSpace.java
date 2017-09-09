
package com.gensym.gsi;

import java.lang.*;
import java.util.*;

public class IndexSpace {
    private Map indexToObject = new HashMap();
    private Map objectToIndex = new HashMap();
    private LinkedList freeIndices = new LinkedList();
    private int firstUnusedIndex = 0;

    public Integer getFreeIndex() {
	if (freeIndices.size() == 0)
	    return new Integer(firstUnusedIndex++);
	return (Integer)(freeIndices.removeFirst());
    }

    public Integer lookupIndexForObject (Object object) {
	return (Integer)(objectToIndex.get(object));
    }

    public int getIndexForObject (Object object) {
	Integer index = (Integer)(objectToIndex.get(object));
	if (index == null) {
	    index = getFreeIndex();
	    objectToIndex.put(object,index);
	    indexToObject.put(index,object);
	}
	return index.intValue();
    }

    public Object lookupObjectForIndex(int index) {
	return indexToObject.get(new Integer(index));
    }

    public void setObjectForIndex(int idx, Object object) {
	Integer index = new Integer(idx);
	objectToIndex.put(object,index);
	indexToObject.put(index,object);
    }

    public void removeObject (Object object) {
	Integer index = (Integer)(objectToIndex.get(object));
	if (index == null) return;
	objectToIndex.remove(object);
	indexToObject.remove(index);
	freeIndices.add(index);
    }

    public void removeIndex (int idx) {
	Integer index = new Integer(idx);
	Object object = indexToObject.get(index);
	if (object == null) return;
	objectToIndex.remove(object);
	indexToObject.remove(index);
	freeIndices.add(index);
    }

    // map entries

    // clear tables

}
