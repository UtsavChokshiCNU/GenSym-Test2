package antlr.collections.impl;

import java.util.Enumeration;
import java.util.NoSuchElementException;
import antlr.collections.Enumerator;

// based on java.lang.Vector; returns any null indices between non-null ones.
class VectorEnumerator implements Enumeration {
	Vector vector;
	int i;


	VectorEnumerator(Vector v) {
		vector = v;
		i = 0;
	}
	public boolean hasMoreElements() {
		synchronized (vector) {
			return i <= vector.lastElement;
		}
	}
	public Object nextElement() {
		synchronized (vector) {
			if (i <= vector.lastElement) {
				return vector.data[i++];
			}
			throw new NoSuchElementException("VectorEnumerator");
		}
	}
}