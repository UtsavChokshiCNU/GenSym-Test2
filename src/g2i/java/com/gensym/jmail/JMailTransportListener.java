package com.gensym.jmail;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Gensym Copyright (c) 2004-2006</p>
 * <p>Company: Gensym Corporation</p>
 * @author not attributable
 * @version 1.0
 */

import javax.mail.*;
import javax.mail.event.*;
import com.gensym.jgi.*;
import com.gensym.util.*;

public class JMailTransportListener implements TransportListener {

	private JMailBridge mBridge;

	// Class Constructor
	public JMailTransportListener() {
	}

	public JMailTransportListener(JMailBridge mb) {
		this.mBridge = mb;
	}

	public JMailBridge getBridge() {
		return mBridge;
	}

	public void messageDelivered(TransportEvent e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Delivered message to:");
		printAddresses(e);
	}

	public void messageNotDelivered(TransportEvent e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Failed to deliver message to:");
		printAddresses(e);
	}

	public void messagePartiallyDelivered(TransportEvent e) {
		G2JavaLog.log(G2JavaLog.BRIDGE_IO, "Partially delivered message to:");
		printAddresses(e);
	}

	public void printAddresses(TransportEvent e) {
		
		Address[] addresses;
		Message msg = e.getMessage();
		int i, max;

		Structure info = new Structure();
		Sequence validAddresses = new Sequence();
		Sequence unsentAddresses = new Sequence();
		Sequence invalidAddresses = new Sequence();

		// Show valid email addresses and information about message that could not be sent
		try {

			info.setAttributeValue(Symbol.intern("FROM"), JMailMessage.addressesToSequence(msg.getFrom()));
			info.setAttributeValue(Symbol.intern("TO"), JMailMessage.addressesToSequence( msg.getRecipients(Message.RecipientType.TO)));
			info.setAttributeValue(Symbol.intern("CC"), JMailMessage.addressesToSequence( msg.getRecipients(Message.RecipientType.CC)));
			info.setAttributeValue(Symbol.intern("BCC"), JMailMessage.addressesToSequence( msg.getRecipients(Message.RecipientType.BCC)));
			info.setAttributeValue(Symbol.intern("SUBJECT"), msg.getSubject());

			addresses = e.getValidSentAddresses();
			if (addresses != null)
				max = addresses.length;
			else
				max = 0;

			for (i = 0; i < max; i++) {
				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "\t" + addresses[i] + " -valid sent");
				//mBridge.g2OnDeliveryReport("Address: " + addresses[i] + ", Status: sent, Message: " + msg);
				validAddresses.add(addresses[i].toString());
			}
			info.setAttributeValue(Symbol.intern("VALID-ADDRESSES"), validAddresses);
			
			// Show valid unsent addresses
			addresses = e.getValidUnsentAddresses();
			if (addresses != null)
				max = addresses.length;
			else
				max = 0;

			for (i = 0; i < max; i++) {
				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "\t" + addresses[i] + " -valid unsent");
				//mBridge.g2OnDeliveryReport("Address: " + addresses[i] + ", Status: not sent, Message: " + msg);
				unsentAddresses.add(addresses[i].toString());
			}
			info.setAttributeValue(Symbol.intern("UNSENT-ADDRESSES"), unsentAddresses);

			// Show invalid email addresses
			addresses = e.getInvalidAddresses();
			if (addresses != null)
				max = addresses.length;
			else
				max = 0;

			for (i = 0; i < max; i++) {
				G2JavaLog.log(G2JavaLog.BRIDGE_IO, "\t" + addresses[i] + " -invalid");
				//mBridge.g2OnDeliveryReport("Invalid Address: " + addresses[i] + ", Status: not sent, Message: " + msg);
				invalidAddresses.add(addresses[i].toString());				
			}
			info.setAttributeValue(Symbol.intern("INVALID-ADDRESSES"), invalidAddresses);

			mBridge.g2OnDeliveryReport(info);

		} catch (MessagingException me) {
			me.printStackTrace();
		} catch (G2AccessException ae) {
			ae.printStackTrace();
		}
	}
}
