package core;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.CharacterCodingException;
import java.nio.charset.Charset;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.CharsetDecoder;

import exception.WarningMessage;

/**
 * This class is responsible for mapping between DB character set
 * and KB application character set. By default it returns unchanged
 * data
 * @author SoftServe
 *
 */
public class CharsetMapper {
	/**
	 * Current charset
	 */
	private Charset charset = null;
	/**
	 * Decoder form current charset to Unicode string
	 */ 
	private CharsetDecoder decoder = null;
	/**
	 * Encoder from input string to current charset
	 */
	private CharsetEncoder encoder = null;
	
	/**
	 * Creates CharsetMapper for the given charset
	 * @param charsetName valid Java charset name
	 */
	public CharsetMapper(String charsetName) {
		if (charsetName != null) {
			charset = Charset.forName(charsetName);
		}
	}
	/**
	 * Converts input string to string in this charset
	 * @param data input string to convert
	 * @return string in current charset
	 */
	public String convertToThisCharset(String data) {
		if (charset == null) {
			Console.puts(WarningMessage.NULL_CHARSET);
			return data;
		}
		try {
			encoder = charset.newEncoder();
			encoder.reset();
			decoder = charset.newDecoder();
			decoder.reset();
			ByteBuffer bb = encoder.encode(CharBuffer.wrap(data));
			CharBuffer cbuf = decoder.decode(bb);
			return cbuf.toString();
		} catch (CharacterCodingException cde) {
			Console.puts("Exception in CharsetMapper: " + cde.getMessage());
			return data;
		}
	}
}
