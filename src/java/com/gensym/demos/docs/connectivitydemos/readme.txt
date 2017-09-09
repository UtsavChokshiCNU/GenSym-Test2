The demos in this package all work with connections to G2.  They show examples of using these classes:

	ItemRetriever
	TwAccess
	TwGateway
	TwConnectionInfo
	LoginRequest

The demos all work with a G2 process running on localhost on port 1112, and a KB called connectivity-demos.kb located in the kbs directory of your Telewindows2 Toolkit product directory.  

To run G2 and load the required KB:

-> Execute the rundemo file in this directory.

To run each demo:

-> Execute each class as a java application from the command line, for example:

	java MyConnection

All the demos print statements to the command window to verify the execution of the code.  In addition, the MySecureLoginRequest demo creates a demo frame for launching a login dialog.
