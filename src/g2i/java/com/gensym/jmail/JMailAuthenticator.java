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

public class JMailAuthenticator extends Authenticator {
	
	private String userName;
	private String password;

	public JMailAuthenticator(String myUserName, String myPassword) {
		this.userName = myUserName;
		this.password = myPassword;
	}

	public PasswordAuthentication getPasswordAuthentication() {
		PasswordAuthentication myAuth = new PasswordAuthentication(
				this.userName, this.password);
		return myAuth;
	}
}