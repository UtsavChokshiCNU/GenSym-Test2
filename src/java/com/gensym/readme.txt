README.txt
Author: Paul B. Konigsberg
Data: Sept. 12 1997
Project: Nevada

----------------------------------------------------------------------------
Current Containment Hierchy:
 The following is an outline of the current shell being used to piece
 together many of Nevada's components.  It is meant only as a guide for
 understanding how these components could be pieced together.  Some of
 these components may soon become obsolete, or may undergo many structural
 changes.  The package outline(see below) is meant to help summarize which
 of these packages/components are more permanent.
----------------------------------------------------------------------------

Key for Reading the Graph:
	"-->" Means subclasses,implements
	 "-"  Means contains
	"()"  Means comments

			----------------------

Telewindows(-->Object):
   -NtwFrame(outer application shell):
	    (-->MDIFrame-->Frame)
		-MDIDocs:(-->Panel)
			-WorkspaceView:(-->PersistentCanvas-->Container)
				-WorkspaceViewAdapter(listens to JWorkspace)
				-JWorkspace(temporary workspace proxy)
						-TwGateway:(private)						
						-public api:
						(access to g2 workspace data &
	   					 api to change g2 workspace data)
						-ability to be listened to
				-WorkspaceElements:(-->Component,DrawElement)
					-WorkspaceJItemAdapter(listens to JItem)
					-JItems(temporary item proxy)
						-TwGateway:(private)
						-public api:
						(access to g2 item data &
						 api to change g2 items data)
						-ability to be listened to
				-RubberBandHandler(-->WkspCommandHandler
						high-level semantic events)
				-WkspEventHandler(low-level, mouse,etc.. events)
		-MDIMenus(-->Menu)
			-MDIMenuItems(-->MenuItem)
		-Dialogs(these seem to "belong" to the frame)
  -Local/Resource (internationization)
  -TwAccess[] (TwGateways-Connections to Servers-JavaLink)



----------------------------------------------------------------------------
Packages Guide:
----------------------------------------------------------------------------
adg		Automatic Dialog Generator(deprecated jpt)
cdm		Class Definition Manager(pbk)
		(soon to be incorporated into native java
		 Classes/Interfaces by vkp)
beaneditor      Our own bean editor(tob/jed)
classtools		class file utilities / back-end emitting of class files (ajs)
com		ActiveX to beans bridge (jv)
controls        Utility beans for the dialog editor(jed,tob)
data            (mkramer's groups stuff)
dataaware       Obsolete?(jpt?)
devtools        (vkp)
displays        A package of G2's displays(Trend-charts, dials, etc. rpenny,pbk)
dlg             A dialog utility package (3rd party hack I think)
draw		A package of "smart" drawing tools (PersistentCanvas)(jed)
icons		G2's icon descriptions(pbk)
irm             A Manager(hashtable) for allocating and storing "renderings"
		of G2's icon descriptions(pbk)
jgi		Java G2 Inteface-Interface for make remote calls to G25.0
		(presently uses native gsi code, ie platform specific).
		This is what is know as JavaLink/G2-Gateway:Java.
		(mGribble/vkp)
jgsi            Obsolete
mdi             Multiple Document Interface(vkp)
net
ntw		Top level of Nevada's Telewindows.  Mostly a hap-hazard piecing
		together of the other various modules. Uses jgi, mdi, wksp, draw,
		irm, cdm, icons, adg, resources, util
ntwod           Obsolete
reflect         ??
resources       java .properties files(generic symbol to language specific string
		mapping) for internalization (currently contains menu, and window
		trimming files)(rpenny)
rmi             Remote Method Invocation(3 tier implementation -rpenny)
tests           A directory of hacks tests
util            A general utility package (contains G2's primitive types
                in java plus much more) (vkp,pbk, rpenny)
wksp	        G2's workspaces(pbk)
wrkspc          Obsolete




