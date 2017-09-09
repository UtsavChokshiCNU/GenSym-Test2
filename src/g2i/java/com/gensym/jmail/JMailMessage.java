package com.gensym.jmail;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Gensym Copyright (c) 2004-2006</p>
 * <p>Company: Gensym Corporation</p>
 * @author not attributable
 * @version 1.0
 */

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;

import javax.mail.*;
import javax.mail.internet.*;

import com.gensym.util.*;

public class JMailMessage {
	
	static Symbol fromS = Symbol.intern("FROM");
	static Symbol toS = Symbol.intern("SENT-TO"); // Note that "TO" is a reserved symbol in G2.
	static Symbol ccS = Symbol.intern("CC");
	static Symbol bccS = Symbol.intern("BCC");
	static Symbol receivedDateS = Symbol.intern("RECEIVED-DATE");
	static Symbol sentDateS = Symbol.intern("SENT-DATE");
	static Symbol recentFlag = Symbol.intern("RECENT-FLAG");
	static Symbol seenFlag = Symbol.intern("SEEN-FLAG");
	static Symbol deletedFlag = Symbol.intern("DELETED-FLAG");
	static Symbol subjectS = Symbol.intern("SUBJECT");
	static Symbol contentsS = Symbol.intern("CONTENTS");
	static Symbol contentTruncatedS = Symbol.intern("CONTENT-TRUNCATED");
	static Symbol contentPlainTextS = Symbol.intern("CONTENT-IS-PLAIN-TEXT");
	static Symbol errorMessageS = Symbol.intern("ERROR-MESSAGE");
	static Symbol filename = Symbol.intern("ATTACHMENT-FILENAME");
	static Symbol stringTestS = Symbol.intern("STRING-TEST"); // CR problem test

	public JMailMessage() {
	}

	/*
	 * if maxMessageLength < 0, the lwnght of the message-content will NOT be
	 * checked of truncated
	 */
	public static Structure messageToStructure(Message message,	int maxMessageLength) {
		
		Structure eMail = new Structure();
		String receivedDateTimeStamp = "";
		String sentDateTimeStamp = "";
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd hhmmss");
		
		try {

			Date receivedDate = message.getReceivedDate(); // BEWARE!: date might be null!
			if (receivedDate != null) {
				receivedDateTimeStamp = dateFormat.format(receivedDate);
			}

			Date sentDate = message.getSentDate(); // BEWARE!: date might be null!
			if (sentDate != null) {
				sentDateTimeStamp = dateFormat.format(sentDate);
			}

			eMail.setAttributeValue(fromS, addressesToSequence(message.getFrom()));
			eMail.setAttributeValue(toS, addressesToSequence(message.getRecipients(Message.RecipientType.TO)));
			eMail.setAttributeValue(ccS, addressesToSequence(message.getRecipients(Message.RecipientType.CC)));
			eMail.setAttributeValue(receivedDateS, receivedDateTimeStamp);
			eMail.setAttributeValue(sentDateS, sentDateTimeStamp);
			eMail.setAttributeValue(subjectS, message.getSubject());
			eMail.setAttributeValue(recentFlag, new Boolean(message.isSet(Flags.Flag.RECENT)));
			eMail.setAttributeValue(seenFlag, new Boolean(message.isSet(Flags.Flag.SEEN)));
			eMail.setAttributeValue(deletedFlag, new Boolean(message.isSet(Flags.Flag.DELETED)));

			// Get the content. Make sure it is not too big and of type plain-text.
			// eMail.setAttributeValue (contentsS, message.getContent().toString());
			boolean contentIsPlainText = true;
			boolean contentTruncated = false;
			String content = "";
			
			if (message.isMimeType("text/plain")) {

				content = message.getContent().toString();

				if (maxMessageLength >= 0 && content.length() > maxMessageLength) {
					
					StringBuffer cb = new StringBuffer(content);
					cb.setLength(maxMessageLength);
					
					content = cb.toString();
					contentTruncated = true;
				}
				
			} else {
				
				contentIsPlainText = false;
			}
			
			eMail.setAttributeValue(contentsS, content);
			eMail.setAttributeValue(contentTruncatedS, new Boolean(contentTruncated));
			eMail.setAttributeValue(contentPlainTextS, new Boolean(contentIsPlainText));

			// insert a test string
			/*
			 * String testString = "Line 1" + '\n' + "Line 2" + '\n' + "Line 3";
			 * eMail.setAttributeValue (stringTestS, testString); //CR-problem
			 * test
			 */

			/*
			 * Why does java not allow unicode characters for CR or LF ?????????
			 * And why do I get a CR in G2? if
			 * (message.getContent().toString().indexOf(' ') == -1) {
			 * G2JavaLog.log(G2JavaLog.BRIDGE_IO, "The contents of this email
			 * contains at least one <CR>:\n" +
			 * message.getContent().toString()); } if
			 * (message.getContent().toString().indexOf(' ') == -1) {
			 * G2JavaLog.log(G2JavaLog.BRIDGE_IO, "The contents of this email
			 * contains at least one <LF>:\n" +
			 * message.getContent().toString()); }
			 * 
			 * byte[] contentBytes = message.getContent().toString().getBytes();
			 * G2JavaLog.log(G2JavaLog.BRIDGE_IO, "The bytes of the contents of
			 * this email:"); printArray(contentBytes);
			 */

			// analyseString(message.getContent().toString());
			// analyseString(testString);
			return eMail;
			
		} catch (MessagingException ex) {
			
			String errorMessage = "Failed to convert message to structure: "
					+ ex.toString();
			G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, errorMessage);
			eMail.setAttributeValue(errorMessageS, errorMessage);
			return eMail;
			
		} catch (IOException ex) {
			
			String errorMessage = "Failed to convert message to structure: "
					+ ex.toString();
			G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, errorMessage);
			eMail.setAttributeValue(errorMessageS, errorMessage);
			return eMail;
		}
	}

	/*
	 * Convert Internet Addresses to a sequence of text 
	 */
	public static Sequence addressesToSequence(Address[] addresses) {
		Sequence sequence = new Sequence();
		if (addresses != null) {
			for (int i = 0; i < addresses.length; i++) {
				sequence.add(addresses[i].toString());
			}
		}
		return sequence;
	}

	/*
	 * convert a sequence of text into an array of Internet Addresses.
	 */
	public static Address[] sequenceToAddresses(Sequence sequence) {

		// Will generate a new array of String containing all strings in the sequence
		// not taking into account empty strings
		String[] stringAddresses = (String[]) sequence.toArray(new String[0]); 
		InternetAddress[] addresses;
		int n = 0;

		for (int i = 0; i < stringAddresses.length; i++) {
			if (stringAddresses[i].length() > 0)
				n++;
		}

		addresses = new InternetAddress[n];

		try {
			for (int i = 0; i < stringAddresses.length; i++) {
				if (stringAddresses[i].length() > 0) {
					addresses[i] = new InternetAddress(stringAddresses[i]);
				}
			}
		} catch (AddressException ex) {
			G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE,
							"Failed to send e-mail because could not convert email-address to InternetAddress:"
									+ '\n' + ex.toString());
			addresses = new InternetAddress[0];
		}

		return addresses;
	}

	/*
	 * Creates a new array of String containing all strings in the sequences
	 * skipping empty strings
	 */
	public static InternetAddress[] appendSequencesToAddresses(Sequence seq1, Sequence seq2, Sequence seq3) {

		String[] stringAddresses1 = (String[]) seq1.toArray(new String[0]); 
		String[] stringAddresses2 = (String[]) seq2.toArray(new String[0]);
		String[] stringAddresses3 = (String[]) seq3.toArray(new String[0]);
		InternetAddress[] addresses;
		int n = 0;

		for (int i = 0; i < stringAddresses1.length; i++) {
			if (stringAddresses1[i].length() > 0)
				n++;
		}
		for (int i = 0; i < stringAddresses2.length; i++) {
			if (stringAddresses2[i].length() > 0)
				n++;
		}
		for (int i = 0; i < stringAddresses3.length; i++) {
			if (stringAddresses3[i].length() > 0)
				n++;
		}

		addresses = new InternetAddress[n];

		try {

			int j = 0;
			for (int i = 0; i < stringAddresses1.length; i++) {
				if (stringAddresses1[i].length() > 0) {
					addresses[i] = new InternetAddress(stringAddresses1[i]);
					j++;
				}
			}
			for (int i = 0; i < stringAddresses2.length; i++) {
				if (stringAddresses2[i].length() > 0) {
					addresses[j] = new InternetAddress(stringAddresses2[i]);
					j++;
				}
			}
			for (int i = 0; i < stringAddresses3.length; i++) {
				if (stringAddresses3[i].length() > 0) {
					addresses[j] = new InternetAddress(stringAddresses3[i]);
					j++;
				}
			}
			
		} catch (AddressException ex) {
			G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE,
							"Failed to send e-mail because could not convert email-address to InternetAddress:"
									+ '\n' + ex.toString());
			addresses = new InternetAddress[0];
		}

		return addresses;
	}

	/*
	 * Sets the attributes of the MimeMessage from the eMail structure
	 */ 
	public static MimeMessage createMimeMessage(Session session, Structure eMail)
			throws NoSuchAttributeException, MessagingException {

		// Define message
		MimeMessage message = new MimeMessage(session);

		// Set the from address
		message.setFrom(new InternetAddress((String) eMail.getAttributeValue(JMailMessage.fromS)));

		// Set the to addresses
		message.addRecipients(Message.RecipientType.TO, JMailMessage.sequenceToAddresses((Sequence) eMail.getAttributeValue(JMailMessage.toS)));

		// Set the cc addresses
		message.addRecipients(Message.RecipientType.CC, JMailMessage.sequenceToAddresses((Sequence) eMail.getAttributeValue(JMailMessage.ccS)));

		// Set the cc addresses
		message.addRecipients(Message.RecipientType.BCC, JMailMessage.sequenceToAddresses((Sequence) eMail.getAttributeValue(JMailMessage.bccS)));

		// Set the subject
		message.setSubject((String) eMail.getAttributeValue(JMailMessage.subjectS));

		// Set the content
		message.setText((String) eMail.getAttributeValue(JMailMessage.contentsS));

		// Set the sent-datestamp
		Calendar rightNow = Calendar.getInstance();
		message.setSentDate(rightNow.getTime());

		return message;
	}

	/* private static void printArray (byte[] b) {
	// for (int i=0; i<b.length; i++) {
	// System.out.println(b[i]);
	// }
	/* }

	private static String contentsAsByteString(String s) throws IOException {
		StringBuffer byteString = new StringBuffer("");
		byte[] b = s.getBytes();

		for (int i = 0; i < b.length; i++) {
			byteString.append(b[i] + " ");
			if (i > 0 && i % 20 == 0) {
				byteString.append('\n');
			}
		}
		return byteString.toString();
	}

	public static void analyseString(String s) throws IOException {
		G2JavaLog.log(G2JavaLog.EMAIL_ANALYSIS,
				"Analysis of the following string:\n" + s);
		G2JavaLog.log(G2JavaLog.EMAIL_ANALYSIS, "End-of-line analysis:\n"
				+ endOfLineAnalysis(s));
		G2JavaLog.log(G2JavaLog.EMAIL_ANALYSIS,
				"The bytes of the contents of this email:\n"
						+ contentsAsByteString(s));

	}

	private static String endOfLineAnalysis(String s) throws IOException {
		StringBuffer outString = new StringBuffer("");
		int numCrLf = 0;
		int numLf = 0;

		byte[] b = s.getBytes();
		for (int i = 0; i < b.length; i++) {

			if (b[i] == 13) {

				if (i + 1 < b.length && b[i + 1] == 10) {
					numCrLf++;
					i++;
				} else {
					outString
							.append("Found a CR that is NOT followed by a LF! in byte #"
									+ i + '\n');
				}

			} else if (b[i] == 10) {

				if (i > 0 && (i + 1) < b.length && b[i - 1] > 32
						&& b[i + 1] > 32) {
					numLf++;
				} else {
					outString
							.append("Found a LF that is either preceded or followed by a ASCII-control character at byte #"
									+ i + '\n');
				}

			} else {
			}

		}// loop

		outString.append("The string contains " + numCrLf
				+ " CR-LF combinations and " + numLf + " single LFs.");

		return outString.toString();
	}

	/*
	 * private static void checkContentsForCR(String s) throws IOException { int
	 * numCrLf = 0; int numLf = 0;
	 * 
	 * byte[] b = s.getBytes(); for (int i=0; i<b.length; i++) {
	 * 
	 * if (b[i] == 13){
	 * 
	 * if (i+1 < b.length && b[i+1] == 10){ numCrLf++; i++; } else
	 * {System.out.println("Found a CR that is NOT followed by a LF!");}
	 *  } else if (b[i] == 10){
	 * 
	 * if (i > 0 && (i+1) < b.length && b[i-1] > 32 && b[i+1] > 32){ numLf++; }
	 * else {System.out.println("Found a LF that is either preceded or followed
	 * by a ASCII-control character: ");}
	 *  } else {}
	 * 
	 * }//loop
	 * 
	 * G2JavaLog.log(G2JavaLog.BRIDGE_IO, "The following string contains " +
	 * numCrLf + " CR-LF combinations and " + numLf + " single LFs: "+ '\n' +
	 * s); }
	 */
}