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
import java.lang.reflect.Method;
import java.lang.Math;
import java.util.*;
import java.text.*;
import java.util.Properties;

import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;

import com.gensym.jgi.*;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.*;

// ******************************************************************************

public class JMailBridge implements G2ConnectionListener {

	/**
	 * This class provides a process linked to a G2 application (via a
	 * gsi-interface object) to send and receive email
	 */

	// static class variables
	private static final String MIME_MAIL_TEXT_PART_TYPE = "text/plain";
	private static final String MIME_MAIL_HTML_PART_TYPE = "text/html";
	private static final String MIME_MAIL_FILE_PART_TYPE = "attached/file";
	private static final String MIME_MULTI_MAIL_PART_TYPE = "multipart/mixed";
	private static final Symbol MAIL_CONTENT_TYPE = Symbol.intern(new String(
			"TYPE"));
	private static final Symbol MAIL_TEXT_CONTENT = Symbol.intern(new String(
			"CONTENT"));
	private static final Symbol MAIL_FILE_PATH = Symbol.intern(new String(
			"FILEPATH"));
	private static int port;
	private static String[] allowedCmdLineParams = { "-help", "-Help", "-port",
			"-Port", "-?", "-debug" };
	private JMailTransportListener mMailListener;
	
	static G2Connection g2connection;
	//private static final Symbol g2GetGsiConfigurationRPC = Symbol.intern("_JMAIL-GET-GSI-CONFIG");
	private	static final Symbol g2OnUnsolicitedEmailRPC = Symbol.intern("_JMAIL-ON-UNSOLICITED-EMAIL");
	private static final Symbol g2OnDeliveryReportRPC = Symbol.intern("_JMAIL-ON-DELIVERY-REPORT");
	private static final Symbol g2OnErrorRPC = Symbol.intern("_JMAIL-ON-ERROR");

	// constructor
	public JMailBridge(G2Connection g2connection, String cnx_string) {
		
		JMailBridge.g2connection = g2connection;
		
		if (cnx_string.equals(new String("-debug"))) {
			// debug request from G2 - set debugLevel to log ALL messages to console
			G2JavaLog.debugLevel = G2JavaLog.EMAIL_ANALYSIS;
			G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
							"Overriding current JAVA process debug level with max from G2");
		}

		G2JavaLog.log(G2JavaLog.BRIDGE_METHODS,
				"About to register java methods for G2 to call as RPCs");
		registerJavaMethods(g2connection);
		
		G2JavaLog.log(G2JavaLog.BRIDGE_METHODS,
				"Create a G2 Listener object for this connection");
		g2connection.addG2ConnectionListener(this);
		
		this.mMailListener = new JMailTransportListener(this);
	}

	// Begin implementation method definitions:
	// g2IsPaused, g2IsStarted, g2IsResumed, g2IsReset, g2MessageReceived,
	// communicationError, readBlockage, writeBlockage, g2ConnectionClosed,
	// g2ConnectionInitialized

	public void g2IsPaused(G2ConnectionEvent g2e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"G2 is paused - awaiting resume");
	}

	public void g2IsStarted(G2ConnectionEvent g2e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"G2 has (re)started - connection established");
	}

	public void g2IsResumed(G2ConnectionEvent g2e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "G2 has resumed");
	}

	public void g2IsReset(G2ConnectionEvent g2e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"G2 has been reset, awaiting restart");
		System.gc(); // garbage collect while process is idle
	}

	public void g2MessageReceived(G2ConnectionEvent g2e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"Message received from G2: " + g2e.getMessage());
	}

	public void communicationError(G2CommunicationErrorEvent g2ee) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"G2/Java communication error: " + g2ee.getMessage());
	}

	public void readBlockage(G2ConnectionEvent g2e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Error reading from G2");
	}

	public void writeBlockage(G2ConnectionEvent g2e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Error writing to G2");
	}

	public void g2ConnectionClosed(G2ConnectionEvent g2e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "G2 connection closed");
		System.gc(); // garbage collect while process is idle
	}

	public void g2ConnectionInitialized(G2ConnectionEvent g2e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"G2 connection initialized");
		if (G2JavaLog.debugLevel == G2JavaLog.BRIDGE_G2_INTERACTION) {
			g2connection.returnMessage("\n Java Mail Brigde talking with G2.");
		}
	}

	// --------------------------------------------------------------------------------------------------

	/**
	 * Register java methods called by G2 as RPCs.
	 * 
	 */

	private void registerJavaMethods(G2Connection g2connection) {

		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"Registering JAVA methods for G2 to call as RPCs");

		try {
			// create send mail method
			Method sendEmailMethod = this.getClass().getDeclaredMethod(
					"sendMail",
					new Class[] { Structure.class, String.class, String.class, Integer.class,
							Boolean.class, String.class, String.class, Sequence.class,
							Sequence.class, Sequence.class, String.class, String.class,
							String.class });
			g2connection.registerJavaMethod(this, sendEmailMethod, Symbol
					.intern("_jmail-rpc-send-mail"), true);

			// create send multipleparts mime mail method
			Method sendMimeMailMethod = this.getClass().getDeclaredMethod(
					"sendMimeMail",
					new Class[] { Structure.class, String.class, String.class, Integer.class,
							Boolean.class, String.class, String.class, Sequence.class,
							Sequence.class, Sequence.class, String.class, String.class,
							Sequence.class });
			g2connection.registerJavaMethod(this, sendMimeMailMethod, Symbol
					.intern("_jmail-rpc-send-mime-mail"), true);

			// create send multiple mail method
			Method sendMailBundleMethod = this.getClass().getDeclaredMethod(
					"sendMailBundle",
					new Class[] { Structure.class, String.class, String.class, Integer.class,
							Boolean.class, String.class, String.class, Sequence.class });
			g2connection.registerJavaMethod(this, sendMailBundleMethod, Symbol
					.intern("_jmail-rpc-send-mail-bundle"), true);

			// create get mail method
			Method getMailMethod = this.getClass().getDeclaredMethod(
					"getMail",
					new Class[] { Structure.class, String.class, String.class, Integer.class,
							Boolean.class, String.class, String.class, String.class,
							Boolean.class, Integer.class, Integer.class });
			g2connection.registerJavaMethod(this, getMailMethod, Symbol
					.intern("_jmail-rpc-get-mail"), true);

			// shutdown mail method
			g2connection.registerJavaMethod(this, "shutdown", Symbol
					.intern("_jmail-rpc-shutdown"));

			// ping mail method
			g2connection.registerJavaMethod(this, "ping", Symbol
					.intern("_jmail-rpc-ping"));

		} catch (NoSuchMethodException nsme) {
			System.err.println("Could not find method to register for "
					+ nsme.toString());
		}
	}

	// --------------------------------------------------------------------------------------------------

	/**
	 * Terminate this JMS bridge process
	 */
	public void shutdown() {
		System.exit(0);
	}

	// --------------------------------------------------------------------------------------------------

	/**
	 * Ping this JMS bridge process
	 */
	public boolean ping() {
		return true;
	}

	// --------------------------------------------------------------------------------------------------

	/**
	 * Get GSI configuation attribute boolean value, current next two attributes were using.
	 *	- JMAIL-DELIVERY-CONFIRMATION
	 *  - JMAIL-DEBUG
	 */
	private boolean getGSIConfigAttributeBooleanValue(Structure gsiConfig, String attributeName) {
		boolean value = false;
		
		try {
			value = "true".equals(gsiConfig.getAttributeValue(Symbol.intern(attributeName)).toString());
		} catch (NoSuchAttributeException ex) {
			value = false;
			G2JavaLog.log(G2JavaLog.BRIDGE_IO, ex.toString());
		}
		
		return value;
	}
	
	/**
	 * Get GSI configuation attribute boolean value, current next two attributes were using.
	 *	- JMAIL-DELIVERY-CONFIRMATION
	 *  - JMAIL-DEBUG
	 */
	private String getGSIConfigAttributeStringValue(Structure gsiConfig, String attributeName) {
		String value = null;
		
		try {
			value = gsiConfig.getAttributeValue(Symbol.intern(attributeName)).toString();
		} catch (NoSuchAttributeException ex) {
			G2JavaLog.log(G2JavaLog.BRIDGE_IO, ex.toString());
		}
		
		return value;
	}
	
	/**
	 * Get Properties, this method is used to create Properties for session
	 */
	 
	private Properties getProps(
			boolean isSending,
			String protocol,
			Boolean sslEnable,
			String host,
			Integer hostPort) {
		
		Properties props = new Properties();
		
		if (isSending)
			props.put("mail.transport.protocol", protocol);
		else
			props.put("mail.store.protocol", protocol);
		
		String prefix = "mail." + protocol + ".";
		
		props.put(prefix + "host", host);
		if (hostPort.intValue() > 0)
			props.put(prefix + "port", hostPort.toString());
			
		if (sslEnable.booleanValue())
			props.put(prefix + "ssl.enable", "true");
		else
			props.put(prefix + "starttls.enable", "true");
		
		props.put(prefix + "ssl.trust", host);
		
		props.put(prefix + "auth", "true");
		
		return props;
	}

	// --------------------------------------------------------------------------------------------------

	/**
	 * Send Mail method
	 */
	public String sendMail(
			Structure gsiConfig,
			String protocol,
			String host,
			Integer hostPort,
			Boolean sslEnable,
			String userName,
			String password,
			Sequence to,
			Sequence cc,
			Sequence bcc,
			String from,
			String subject,
			String contents) {

		String result = "OK";
		Calendar rightNow = Calendar.getInstance();
		boolean jmailTranDelivery = false;
		boolean jmailDebug = false;

		// Print parameters
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"Trying to send mail: \n"
						+ " Protocol = " + protocol + '\n'
						+ " SSL Enable = " + sslEnable.toString() + "\n"
						+ " Host = " + host + '\n'
						+ " Host Port = " + hostPort.toString() + '\n'
						+ " To = " + to.toString() + '\n'
						+ " Cc = " + cc.toString() + '\n'
						+ " Bcc = " + bcc.toString() + '\n'
						+ " From = " + from + '\n'
						+ " SentTime = " + rightNow.getTime() + '\n'
						+ " Subject = " + subject + '\n'
						+ " Contents = " + contents);

		// Get GSI configration attribute value
		jmailTranDelivery = getGSIConfigAttributeBooleanValue(gsiConfig, "JMAIL-DELIVERY-CONFIRMATION");
		jmailDebug = getGSIConfigAttributeBooleanValue(gsiConfig, "JMAIL-DEBUG");
		
		// Get Authentication
		JMailAuthenticator authenticator = new JMailAuthenticator(userName, password);

		// Get system properties
		Properties props = getProps(true, protocol, sslEnable, host, hostPort);

		G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Custom Properties: " + props.toString());
		
		try {

			// Get session
			Session session = Session.getInstance(props, authenticator);
			session.setDebug(jmailDebug);
			
			// Session session = Session.getDefaultInstance(props, myAuth);
			// //Beware!! this does not work well!!! It does NOT create a new
			// session based on provided properties if one already exists!
			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Created Session object. Properties: " + session.getProperties().toString());

			// Define message
			MimeMessage message = new MimeMessage(session);

			// Set the from address
			message.setFrom(new InternetAddress(from));

			// Set the to addresses
			message.addRecipients(javax.mail.Message.RecipientType.TO,
					JMailMessage.sequenceToAddresses(to));

			// Set the cc addresses
			message.addRecipients(javax.mail.Message.RecipientType.CC,
					JMailMessage.sequenceToAddresses(cc));

			// Set the bcc addresses
			message.addRecipients(javax.mail.Message.RecipientType.BCC,
					JMailMessage.sequenceToAddresses(bcc));

			// Set the subject
			message.setSubject(subject);

			// Set the sent-datestamp
			message.setSentDate(rightNow.getTime());

			// Set the content
			message.setText(contents);

			Transport transport = session.getTransport();

			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Created Transport object");

			if (jmailTranDelivery) {
				
				transport.addTransportListener(new JMailTransportListener(this));
				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Sending via transport properties with listener added: " + transport.toString());

				// Send message
				transport.connect();
				transport.sendMessage(message, JMailMessage.appendSequencesToAddresses(to, cc, bcc));
				transport.close();
				
				G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Send mail success.");

			} else {

				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Sending via transport properties: " + transport.toString());

				// Send message
				Transport.send(message);
				
				G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Send mail success.");
			}
		} catch (MessagingException ex) {
			G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, "Failed to send e-mail:"
					+ '\n' + ex.toString());
			result = "Failed to send e-mail. Error: " + ex.toString();
		}

		return result;
	}

	// --------------------------------------------------------------------------------------------------

	/**
	 * Send Mime Mmail
	 */
	public String sendMimeMail(
			Structure gsiConfig,
			String protocol,
			String host,
			Integer hostPort,
			Boolean sslEnable,
			String userName,
			String password,
			Sequence to,
			Sequence cc,
			Sequence bcc,
			String from,
			String subject,
			Sequence parts) {
		
		String result = "OK";
		Calendar rightNow = Calendar.getInstance();
		boolean jmailTranDelivery = false;
		boolean jmailDebug = false;

		// Print parameters
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
			"Trying to send MIME multiparts mail: \n"
				+ " Protocol = " + protocol + '\n'
				+ " SSL Enable = " + sslEnable.toString() + "\n"
				+ " Host = " + host + '\n'
				+ " Host Port = " + hostPort.toString() + '\n'
				+ " To = " + to.toString() + '\n'
				+ " Cc = " + cc.toString() + '\n'
				+ " Bcc = " + bcc.toString() + '\n'
				+ " From = " + from + '\n'
				+ " SentTime = " + rightNow.getTime() + '\n'
				+ " Subject = " + subject + '\n'
				+ " Contents = " + parts);

		// Get GSI configration attribute value
		jmailTranDelivery = getGSIConfigAttributeBooleanValue(gsiConfig, "JMAIL-DELIVERY-CONFIRMATION");
		jmailDebug = getGSIConfigAttributeBooleanValue(gsiConfig, "JMAIL-DEBUG");

		// Get Authentication
		JMailAuthenticator authenticator = new JMailAuthenticator(userName, password);

		// Get system properties
		Properties props = getProps(true, protocol, sslEnable, host, hostPort);

		G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Custom Properties: " + props.toString());

		try {

			// Get session
			Session session = Session.getInstance(props, authenticator);
			session.setDebug(jmailDebug);
			
			// Session session = Session.getDefaultInstance(props, myAuth);
			// //Beware!! this does not work well!!! It does NOT create a new
			// session based on provided properties if one already exists!
			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Created Session object. Properties: " + session.getProperties().toString());

			// Define message
			MimeMessage message = new MimeMessage(session);

			// Set the from address
			message.setFrom(new InternetAddress(from));

			// Set the to addresses
			message.addRecipients(javax.mail.Message.RecipientType.TO,
					JMailMessage.sequenceToAddresses(to));

			// Set the cc addresses
			message.addRecipients(javax.mail.Message.RecipientType.CC,
					JMailMessage.sequenceToAddresses(cc));

			// Set the bcc addresses
			message.addRecipients(javax.mail.Message.RecipientType.BCC,
					JMailMessage.sequenceToAddresses(bcc));

			// Set the subject
			message.setSubject(subject);

			// Set the sent-timestamp
			message.setSentDate(rightNow.getTime());

			// Set the parts' content
			Multipart mpart = new MimeMultipart();

			for (Iterator ps = parts.iterator(); ps.hasNext();) {

				Structure apart = (Structure) ps.next();
				String ptype = (String) apart.getAttributeValue(
						JMailBridge.MAIL_CONTENT_TYPE, "");
				String pcont = (String) apart.getAttributeValue(
						JMailBridge.MAIL_TEXT_CONTENT, "");
				String pfile = (String) apart.getAttributeValue(
						JMailBridge.MAIL_FILE_PATH, "");

				Collator myCollator = Collator.getInstance();

				if (myCollator.compare(ptype, JMailBridge.MIME_MAIL_TEXT_PART_TYPE) == 0) {
					MimeBodyPart tpart = new MimeBodyPart();
					tpart.setText(pcont);
					mpart.addBodyPart(tpart);
				} else if (myCollator.compare(ptype, JMailBridge.MIME_MAIL_HTML_PART_TYPE) == 0) {
					MimeBodyPart hpart = new MimeBodyPart();
					hpart.setContent(pcont, JMailBridge.MIME_MAIL_HTML_PART_TYPE);
					mpart.addBodyPart(hpart);
				} else if (myCollator.compare(ptype, JMailBridge.MIME_MAIL_FILE_PART_TYPE) == 0
							&& pfile.length() != 0) {
					MimeBodyPart fpart = new MimeBodyPart();
					File f = new File(pfile);
					fpart.setFileName(f.getName());
					fpart.setDataHandler(new DataHandler(new FileDataSource(f)));
					fpart.setDisposition(Part.ATTACHMENT);
					mpart.addBodyPart(fpart);
				}
			}

			message.setContent(mpart);

			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Get send transport object");

			Transport transport = session.getTransport();

			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Created Transport object");

			if (jmailTranDelivery) {

				transport.addTransportListener(new JMailTransportListener(this));
				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Sending via transport properties with listener added: " + transport.toString());

				// Send message
				transport.connect();
				transport.sendMessage(message, JMailMessage.appendSequencesToAddresses(to, cc, bcc));
				transport.close();
				
				G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Send mail success.");

			} else {

				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Sending via transport properties: " + transport.toString());
				
				// Send message
				Transport.send(message);
				
				G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Send mail success.");
			}
		} catch (MessagingException ex) {
			G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, "Failed to send e-mail:"
					+ '\n' + ex.toString());
			result = "Failed to send e-mail. Error: " + ex.toString();
		}

		return result;
	}

	// --------------------------------------------------------------------------------------------------

	/**
	 * This method will send a sequence of emails within one session emails =
	 * sequence of structure(from: text, sent-to: sequence of text, cc: sequence
	 * of text, subject: text, contents: text)
	 */
	public String sendMailBundle(
			Structure gsiConfig,
			String protocol,
			String host,
			Integer hostPort,
			Boolean sslEnable,
			String userName,
			String password,
			Sequence eMailsSeq) {

		String result = "OK";
		boolean jmailTranDelivery = false;
		boolean jmailDebug = false;

		// Print parameters
		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"Trying to send mail bundle:\n"
					+ " Protocol = " + protocol + '\n'
					+ " SSL Enable = " + sslEnable.toString() + "\n"
					+ " Host = " + host + '\n'
					+ " Host Port = " + hostPort.toString() + '\n'
					+ " eMails = " + eMailsSeq.toString());

		// Get GSI configration attribute value
		jmailTranDelivery = getGSIConfigAttributeBooleanValue(gsiConfig, "JMAIL-DELIVERY-CONFIRMATION");
		jmailDebug = getGSIConfigAttributeBooleanValue(gsiConfig, "JMAIL-DEBUG");

		// Get Authentication
		JMailAuthenticator authenticator = new JMailAuthenticator(userName, password);

		// Get system properties
		Properties props = getProps(true, protocol, sslEnable, host, hostPort);

		G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Custom Properties: " + props.toString());

		int i = 0; // counter of emails
		int n = 0; // total number of emails to be send

		try {

			// Containing all structures in the sequence, each structure being one email to send.
			Structure[] eMails = (Structure[]) eMailsSeq.toArray(new Structure[0]); // Will generate a new array of
			n = eMails.length;

			// Get session
			Session session = Session.getInstance(props, authenticator);
			session.setDebug(jmailDebug);

			// Session session = Session.getDefaultInstance(props, myAuth);
			// //Beware!! this does not work well!!! It does NOT create a new
			// session based on provided properties if one already exists!
			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Created Session object. Properties: " + session.getProperties().toString());

			Transport transport = session.getTransport();

			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Created Transport object");

			if (jmailTranDelivery) {
				transport.addTransportListener(mMailListener);
				transport.connect();
				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Sending via transport properties with listener added: " + transport.toString());
			} else { 
				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Sending via transport properties: " + transport.toString());
			}
			

			// Loop over all eMails and convert to array of MimeMessage
			// In this way, all emails are first converted before being send.
			// If anyone fails to convert, no emails will be send.
			MimeMessage[] messages = new MimeMessage[n];

			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Converting G2 e-mail structures to MIME Messages.");

			for (i = 0; i < n; i++) {
				// Define and set message
				messages[i] = JMailMessage.createMimeMessage(session, eMails[i]);
			} // for every eMail structure

			// Loop over all messages and send
			for (i = 0; i < n; i++) {

				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Send mail "	+ (i + 1) + " of " + n);

				// Send message
				if (jmailTranDelivery) {
					transport.sendMessage(messages[i], messages[i].getAllRecipients());
				} else {
					Transport.send(messages[i]);
				}
				
				G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Send mail # " + (i + 1) + " success");
				
			} // for every MimeMessage

			if (jmailTranDelivery) {
				transport.close();
			}
			
		} catch (MessagingException ex) {
			result = "Failed to send e-mail # " + (i + 1) + " of " + n
					+ ". Error: " + '\n' + ex.toString();
			G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, result);
		} catch (NoSuchAttributeException ex) {
			result = "Failed to send e-mail # " + (i + 1) + " of " + n
					+ ". Error: " + '\n' + ex.toString();
			G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, result);
		}

		return result;
	}

	// --------------------------------------------------------------------------------------------------

	// Receive E-mail
	/*
	 * Note that this method will retreive a maximum of 'maxNumMessages'.
	 * Repeated calls will return the SAME messages unless the messages are
	 * deleted!
	 */
	
	public Sequence getMail(
			Structure gsiConfig,
			String protocol,
			String host,
			Integer hostPort,
			Boolean sslEnable,
			String userName,
			String password,
			String folderName,
			Boolean deleteMessages,
			Integer maxNumMessages,
			Integer maxMessageLength) {

		String dir = getGSIConfigAttributeStringValue(gsiConfig, "DOWNLOAD-ATTACHMENT-DIRECTORY-PATH");
		boolean jmailTranDelivery = false;
		boolean jmailDebug = false;

		G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,
				"Trying to get mail: \n"
					+ " Protocal = " + protocol + "\n"
					+ " SSL Enable = " + sslEnable.toString() + "\n"
					+ " Host = " + host + '\n'
					+ " Host Port = " + hostPort.toString() + '\n'
					+ " Folder = " + folderName + '\n'
					+ " Attachment Directory: " + dir + '\n'
					+ " Delete Messages = " + deleteMessages + '\n'
					+ " Max. number of Messages = " + maxNumMessages + '\n');

		// Get GSI configration attribute value
		jmailTranDelivery = getGSIConfigAttributeBooleanValue(gsiConfig, "JMAIL-DELIVERY-CONFIRMATION");
		jmailDebug = getGSIConfigAttributeBooleanValue(gsiConfig, "JMAIL-DEBUG");
		
		// Get Authentication
		JMailAuthenticator authenticator = new JMailAuthenticator(userName, password);

		// Get system properties
		Properties props = getProps(false, protocol, sslEnable, host, hostPort);
		
		try {
			// Get session
			Session session = Session.getInstance(props, authenticator);
			session.setDebug(jmailDebug);

			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Created Session object. Properties: " + session.getProperties().toString());

			// Get the store
			Store store = session.getStore();
			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Fetching store success: " + store.toString());

			// Connect to store
			store.connect();
			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Connecting to store success: " + store.toString());

			// Get folder
			Folder folder = store.getFolder(folderName);

			// Open read-only
			if (deleteMessages.booleanValue()) {
				folder.open(Folder.READ_WRITE);
			} // in order to delete messages!
			else {
				folder.open(Folder.READ_ONLY);
			}

			/*
			 * Test dates: Calendar calendar = Calendar.getInstance(); Date
			 * currentTime = new Date(); calendar.setTime(currentTime);
			 * 
			 * //Long timeMillis = calendar.getTimeInMillis(); SimpleDateFormat
			 * formatter = new SimpleDateFormat("yyyy.MM.dd hh:mm:ss"); String
			 * timeStamp = formatter.format(currentTime);
			 * G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Current-time = " +
			 * timeStamp);
			 */

			// test new messages DOES NOT WORK!
			// int countNewMessages = folder.getNewMessageCount();
			// G2JavaLog.log(G2JavaLog.BRIDGE_IO, "There are " +
			// countNewMessages + " new messages in the folder");
			// Get directory
			javax.mail.Message[] messages = folder.getMessages();

			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Received " + messages.length + " e-mails.");

			Sequence eMails = new Sequence();
			int n = Math.min(messages.length, maxNumMessages.intValue());

			for (int i = 0; i < n; i++) {

				javax.mail.Message message = messages[i];

				// In case of multipart MIME mail
				try {
					if (message.isMimeType("text/plain")) {

						Structure eMail = JMailMessage.messageToStructure(
								message, maxMessageLength.intValue());
						eMails.add(eMail);

					} else if (message.isMimeType("multipart/*")) {

						Multipart mp = (Multipart) message.getContent();
						String strcnt = "";
						String filename = "";
						String fn = "";
						Structure eMail = new Structure();
						
						boolean first = true;
						for (int j = 0, nn = mp.getCount(); j < nn; j++) {

							Part part = mp.getBodyPart(j);
							// String disposition = part.getDisposition();

							if (part.getFileName()==null && part.isMimeType("text/plain")) {
								if (first) {
									// Only accept the first part as the mail content
									first = false;
									strcnt = (String) part.getContent();
									eMail = JMailMessage.messageToStructure(
											message, maxMessageLength.intValue());
									eMail.setAttributeValue(Symbol
											.intern("CONTENTS"), strcnt);
									eMail.setAttributeValue(Symbol
											.intern("CONTENT-IS-PLAIN-TEXT"),
											new Boolean(true));
								}
							} else if (part.getFileName() != null && !part.getFileName().equals("")) {

								StringTokenizer strtok = new StringTokenizer(
										part.getFileName().toString().trim(),
										File.separator);

								while (strtok.hasMoreTokens()) {

									fn = strtok.nextToken();
									File fout = new File(dir + File.separator
											+ fn);
									FileOutputStream fos = new FileOutputStream(
											fout);
									int fs = (int) part.getSize();
									byte[] data = new byte[fs];
									java.io.InputStream is = part
											.getInputStream();
									is.read(data);
									fos.write(data);

									// make sure file resources closed
									// gracefully
									is.close();
									fos.close();

									if (filename.length() == 0) {
										filename = filename.concat(fn);
									} else {
										filename = filename.concat(", " + fn);
									}
								}
								eMail.setAttributeValue(Symbol
										.intern("ATTACHMENT-FILENAME"),
										filename);
							}
						}
						eMails.add(eMail);
					}
				} catch (IOException ioe) {
					G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, ioe.getMessage());
				}

				if (deleteMessages.booleanValue()) {
					message.setFlag(Flags.Flag.DELETED, true);
				}
				// set the deleted flag
				// G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Delete-flag:
				// "+message.isSet(Flags.Flag.DELETED));
			}

			folder.close(deleteMessages.booleanValue());
			store.close();
			
			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Closed folder and store");
			
			return eMails;
			
		} catch (MessagingException ex) {
			
			String message = "Failed to get e-mail: " + ex.toString();
			G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, message);
			Sequence result = new Sequence();
			result.add(message);
			return result;
		}
		/*
		 * catch (IOException ex) { String message = "Failed to get e-mail: " +
		 * ex.toString (); G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, message);
		 * Sequence result = new Sequence(); result.add(message); return result; }
		 * catch (NtwIllegalArgumentException ex) { String message = "Failed to
		 * get e-mail: " + ex.toString ();
		 * G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, message); Sequence result =
		 * new Sequence(); result.add(message); return result; }
		 */
	}

	// --------------------------------------------------------------------------------------------------

	/*
	 * Will send unsolicited e-mail into G2. Not in use right now. Might be used
	 * by polling agent in bridge that checks e-mail periodically.
	 */
	public void g2OnUnsolicitedEmail(javax.mail.Message message) {

		try {

			Structure eMail = JMailMessage.messageToStructure(message, -1);
			G2JavaLog.log(G2JavaLog.BRIDGE_IO,
					"Trying to send mail into G2 as structure: "
							+ eMail.toString());
			
			g2connection.callRPC(g2OnUnsolicitedEmailRPC,
					new java.lang.Object[] { eMail }, 10000);
			
			G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Sent to G2");

		} catch (G2AccessException gae) {
			G2JavaLog.log(G2JavaLog.G2_RPC_ERRS,
					"Cannot send mail into G2 from JMailBridge\n"
							+ gae.getMessage());
		}

		/*
		 * catch (MessagingException ex){ String error = "Failed to receive
		 * e-mail into G2: " + ex.toString ();
		 * G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, error); } catch
		 * (IOException ex) { String error = "Failed to receive e-mail into G2: " +
		 * ex.toString (); G2JavaLog.log(G2JavaLog.NON_FATAL_BRIDGE, error); }
		 */
	}

	// --------------------------------------------------------------------------------------------------

	/*
	 * This method makes G2Connection-specific RPC call to pass along reports to
	 * G2 application.
	 */
	protected Integer g2OnDeliveryReport(Object info) throws G2AccessException {
		Integer retVal = (Integer) g2connection.callRPC(
				g2OnDeliveryReportRPC, new java.lang.Object[] { info },
				10000);
		return retVal;
	}

	// --------------------------------------------------------------------------------------------------

	/*
	 * This method makes G2Connection-specific RPC call to pass along error
	 * messages to G2 application.
	 */
	protected Integer g2OnError(String msg) throws G2AccessException {

		Integer retVal = (Integer) g2connection.callRPC(g2OnErrorRPC,
				new java.lang.Object[] { msg }, 10000);

		return retVal;
	}


	// --------------------------------------------------------------------------------------------------

	/*
	 * This method makes G2Connection-specific RPC call to get GSI
	 * configuration.
	 */
	/* Not used anymore
	private Structure g2GetGsiConfiguration() throws G2AccessException {
		
		g2connection.setRemoteRPCReturnKind(g2GetGsiConfigurationRPC,
				G2Gateway.PASS_BY_COPY);
		
		Structure retVal = (Structure) g2connection.callRPC(
				g2GetGsiConfigurationRPC, new java.lang.Object[0], 10000);
		return retVal;
	}
	*/
	// --------------------------------------------------------------------------------------------------

	/*
	 * Gets the version of JavaLink. (Look at the core.jar->products.dat for the
	 * names of the products) If the product cannot be found, an exception of
	 * class UnknownProductException is thrown, but that is a private class.
	 */
	public static String getJavaLinkVersion() {

		String productName = "javalink";
		String version = "none";

		try {
			com.gensym.core.Product product = com.gensym.core.ProductManager
					.getProduct(productName);
			if (product != null) {
				version = product.getDisplayVersion();
			}
		} catch (Exception ex) {
			version = "the product named '" + productName + "' is unknown";
		}
		return version;
	}

	// --------------------------------------------------------------------------------------------------

	public static void main(String[] args) {
		System.out.println();
		System.out.println("+--------------------------------------------------+");
		System.out.println("");
		System.out.println("    G2 JMail Bridge                               ");
		System.out.println("    " + G2Version.VERSION_INFORMATION + " (Build " + G2Version.BUILD_INFORMATION + ")");
		System.out.println("                                                  ");
		System.out.println("    " + G2Version.COPYRIGHT_INFORMATION + "       ");
		System.out.println("");
		System.out.println("+--------------------------------------------------+");
		System.out.println("");
		System.out.println("JavaLink version: " + JMailBridge.getJavaLinkVersion());

		// Handle command line parameters - allow fuzzy matches
		CmdLineArgHandler cmds = new CmdLineArgHandler(args, JMailBridge.allowedCmdLineParams, true);
		
		// get debug level
		String debugLevelString = cmds.getOptionValue("-debug");

		if (debugLevelString == null) {
			G2JavaLog.debugLevel = 0;
		} else if (debugLevelString.equals("0")) {
			G2JavaLog.debugLevel = 0;
		} else if (debugLevelString.equals("1")) {
			G2JavaLog.debugLevel = 1;
		} else if (debugLevelString.equals("2")) {
			G2JavaLog.debugLevel = 2;
		} else if (debugLevelString.equals("3")) {
			G2JavaLog.debugLevel = 3;
		} else if (debugLevelString.equals("4")) {
			G2JavaLog.debugLevel = 4;
		} else if (debugLevelString.equals("5")) {
			G2JavaLog.debugLevel = 5;
		} else if (debugLevelString.equals("6")) {
			G2JavaLog.debugLevel = 6;
		} else if (debugLevelString.equals("7")) {
			G2JavaLog.debugLevel = 7;
		}

		// request for help
		if (cmds.getSwitchValue("-help") || cmds.getSwitchValue("-Help") || cmds.getSwitchValue("-?")) {
			System.out.println("\nUsage:\t JMailBridge -port <port number>\n");
			System.exit(1);
		}

		// Initialize the G2 listener
		try {
			port = (int) cmds.getOptionLong(new String("-port"), 22044);
			new java.net.ServerSocket(port).close();
			// static class method call
			// G2Gateway.initialize(new String [] {"-listenerport", port+""});
			G2Gateway.initialize(port);
		} catch (IOException ioe) {
			System.err.println("Error: TCP port " + port
					+ " initialization failed");
			System.exit(1);
		} catch (AlreadyInitializedException aie) {
			System.err.println("Error: TCP port " + port
					+ " already initialized");
			System.exit(1);
		}

		// System.out.println("\nFinished with G2Gateway.initialize on port " +
		// port + "\n");

		// Deal with unsolicited connection request from G2 through a Cnx
		// Handler Factory object
		G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory() {
			
			// Implementation of the Cnx Handler Factory method
			public G2Connection createG2Connection(String cnx_data) {
				
				G2Gateway g2gateway = new G2Gateway();
				/*JMailBridge mailBridge =*/ new JMailBridge(g2gateway, cnx_data);
				return g2gateway;
			}
		});

		// Start Gateway
		G2Gateway.startup();

		// G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,"\n\n\nJMailBridge
		// listening for G2 connection on port: "+port);
		System.out.println("\nJMailBridge listening for G2 connection on port: " + port + "\n");
		
	} // end main
} // end Socket Manager class definition
