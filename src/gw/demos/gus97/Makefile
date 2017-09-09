# Makefile for the the java applet.







##### Defines.

# We depend on classes from the following libraries, note
# that the order is important.
#   1. Java
JAVA_CLASSES = /home/bhyde/local/jdk1.1/lib/classes.zip
#   2. Bongo
BONGO_CLASSES = ./bongo.zip
#   3. Marimba
MARIMBA_CLASSES = ./marimba.zip

# Together those make our CLASSPATH dependencies
CLASSPATH = .:$(JAVA_CLASSES):$(BONGO_CLASSES):$(MARIMBA_CLASSES)

# We compile that stuff into a classes directory.
CDIR = ./classes

# With this Java compiler invokation
JAVAC = javac -d $(CDIR) -classpath $(CLASSPATH)

# We develop on a unix box, and install onto this NT PC
NTPC = $(BHPC)

# We work in one directory, but we have another
# that we pack up everything into:
PROJECT = gus97
SITE_ROOT = /tmp/$(PROJECT)
WEB_DIR = /tmp/gus97/website
KB_DIR  = /tmp/gus97/kbs
DEV_DIR = /tmp/gus97/dev






#####  Dependencies.

root:
	echo Make applet, clean, update, pack, and send

# This directory consists of these component parts:
applets : GW MyApplet M3

# GW is a package with a few tools to interface back to G2.
GW :
	$(JAVAC) GW.java

# A very simple applet
M3 : 
	$(JAVAC) M3.java

# My first applet
MyApplet: 
	$(JAVAC) MyApplet.java

clean: init update

init:
	rm -rf $(SITE_ROOT)
	mkdir $(SITE_ROOT)
	mkdir $(WEB_DIR)
	mkdir $(KB_DIR)
	mkdir $(DEV_DIR)
	mkdir $(WEB_DIR)/classes
	unzip -q -d $(WEB_DIR)/classes $(BONGO_CLASSES)
	unzip -q -d $(WEB_DIR)/classes $(MARIMBA_CLASSES)
	cp -rp applets $(WEB_DIR)
	mkdir $(WEB_DIR)/applets/chart
	cp -rp /home/bhyde/src/chartLib/chart $(WEB_DIR)/applets

update:
	cp -rp images $(WEB_DIR)
	cp -rp *.html $(WEB_DIR)
	cp -rp *.gui $(WEB_DIR)
	cp -rp *.kb    $(KB_DIR)
	cp -rp applets $(WEB_DIR)
	cp -rp $(CDIR) $(WEB_DIR)


pack:
	cd $(SITE_ROOT)/..; rm -rf /$(PROJECT).zip
	cd $(SITE_ROOT)/..; zip -qr $(PROJECT).zip gus97

send:
	echo put $(SITE_ROOT)/../$(PROJECT).zip $(PROJECT).zip | ftp $(NTPC)

sendGW:
	cd /gensym/st/ab/iship/dep/intelnt/gw-10r2-C24; zip -qr /tmp/gw-10r2-C24.zip test
	echo put /tmp/gw-10r2-C24.zip gw-10r2-C24.zip | ftp $(NTPC)

sendGM:
	cd /gensym/st/ab/iship/dep/intelnt/gm-10b0-L16; zip -qr /tmp/gm-10b0-L16.zip test
	echo put /tmp/gm-10b0-L16.zip gm-10b0-L16.zip | ftp $(NTPC)


sendG2:
	cd /gensym/st/ab/eship/dep/intelnt/g2-40r3; zip -qr /tmp/g2-40r3.zip test
	echo put /tmp/g2-40r3.zip g2-40r3.zip | ftp $(NTPC)


sendMisc:
	echo put /bt/jh/trail/0080-nt-development.txt 0080-nt-development.txt | ftp $(NTPC)
	echo put /bt/jh/trail/0126-how-to-run-jntw-on-NT.txt 0126-how-to-run-jntw-on-NT.txt | ftp $(NTPC)
