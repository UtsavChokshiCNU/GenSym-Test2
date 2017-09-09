Files in this directory that were committed to cvs are used for compilation
of our java code (bridges, etc) as well as deployment for some of them. Below
is a lit of jar files and there usage.

It is assumed that you also checked out the util directory from cvs and stored
it in c:\bt (the jc.bat script relies on this). JAVAHOME should point to the jdk
installation directory, G2_HOME to the G2 installation directory and G2I_HOME to
the directory where you checked out G2i from csv.


JMail bridge:
-------------
- activation.jar: 	this file comes from the Java JAF package and should be
			added to our bundle installation as part of JMail
- mail.jar:		this file comes from the Java JMail package and should be
			added to our bundle installation as part of JMail
- G2JMail.jar:		this file is created when compiling and packaging our
			source code for the JMail bridge. It should be
			added to our bundle installation as part of JMail


JMS bridge:
-----------
- j2ee.jar:		this file comes from the j2ee reference implementation 
			and is only here to be able to compile the jms bridge
			without installing a jms provider. DO NOT DISTRIBUTE IT.
- G2Jms.jar:		this file is created when compiling and packaging our
			source code for the JMS bridge. It should be
			added to our bundle installation as part of JMS



Optimization engine:
--------------------
- G2JGope.jar:		this file is created when compiling and packaging our
			source code for the Optimization engine. It should be
			added to our bundle installation as part of GOPE optimizer


Development tools:
------------------
- devtools.jar:		this file is for development only. DO NOT DISTRIBUTE IT.
- jhall.jar:		this file comes from the Java help package and is used to
			compile the ReThink/e-SCOR client. It should be added to the
			distribution.