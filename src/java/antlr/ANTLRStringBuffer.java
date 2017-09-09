package antlr;

/**
 * <b>SOFTWARE RIGHTS</b>
 * <p>
 * ANTLR 2.6.0 MageLang Institute
 * <p>
 * We reserve no legal rights to the ANTLR--it is fully in the
 * public domain. An individual or company may do whatever
 * they wish with source code distributed with ANTLR or the
 * code generated by ANTLR, including the incorporation of
 * ANTLR, or its output, into commerical software.
 * <p>
 * We encourage users to develop software with ANTLR. However,
 * we do ask that credit is given to us for developing
 * ANTLR. By "credit", we mean that if you use ANTLR or
 * incorporate any source code into one of your programs
 * (commercial product, research project, or otherwise) that
 * you acknowledge this fact somewhere in the documentation,
 * research report, etc... If you like ANTLR and have
 * developed a nice tool with the output, please mention that
 * you developed it using ANTLR. In addition, we ask that the
 * headers remain intact in our source code. As long as these
 * guidelines are kept, we expect to continue enhancing this
 * system and expect to make other tools available as they are
 * completed.
 * <p>
 * The ANTLR gang:
 * @version ANTLR 2.6.0 MageLang Institute
 * @author Terence Parr, <a href=http://www.MageLang.com>MageLang Institute</a>
 * @author <br>John Lilley, <a href=http://www.Empathy.com>Empathy Software</a>
 */
// Implementation of a StringBuffer-like object that does not have the
// unfortunate side-effect of creating Strings with very large buffers.

public class ANTLRStringBuffer {
	protected char[] buffer = new char[8];
	protected int length = 0;		// length and also where to store next char


	public ANTLRStringBuffer() {}
	public final void append(char c) {
		// This would normally be  an "ensureCapacity" method, but inlined
		// here for speed.
		if (length >= buffer.length) {
			// Compute a new length that is at least double old length
			int newSize = buffer.length;
			while (length >= newSize) {
				newSize *= 2;
			}
			// Allocate new array and copy buffer
			char[] newBuffer = new char[newSize];
			for (int i = 0; i < length; i++) {
				newBuffer[i] = buffer[i];
			}
			buffer = newBuffer;
		}
		buffer[length] = c;
		length++;
	}
	public final void append(String s) {
		for (int i = 0; i < s.length(); i++) {
			append(s.charAt(i));
		}
	}
	public final char charAt(int index) { return buffer[index]; }
	public final char[] getBuffer() { return buffer; }
	public final int length() { return length; }
	public final void setCharAt(int index, char  ch) { buffer[index] = ch; }
	public final void setLength(int newLength) {
		if (newLength < length) {
			length = newLength;
		} else {
			while (newLength > length) {
				append('\0');
			}
		}
	}
	public final String toString() {
		return new String(buffer, 0, length);
	}
}