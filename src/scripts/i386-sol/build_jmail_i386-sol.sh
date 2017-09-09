#!/bin/sh

. ./set_env_i386-sol.sh

CLASSPATH=${CLASSPATH}:${SRCBOX}/g2i/java/:${SRCBOX}/g2i/java/classes/:${SRCBOX}/g2i/java/lib/:${SRCBOX}/g2i/java/classes/activation.jar:${SRCBOX}/g2i/java/classes/mail.jar
export CLASSPATH

$SRCBOX/util/jmake $SRCBOX/g2i/java/com/gensym/jmail G2Jmail
#$JAVA_HOME/bin/java  -mx100m com.gensym.devtools.JavaMake -srcbox $SRCBOX -root $SRCBOX/g2i/java/com/gensym/jmail -product G2Jmail -quiet

# create JAR's and put them to ${G2i_HOME}/java/classes:
cd $JAVA_SRCBOX
$SRCBOX/util/jmake com/gensym/devtools devtools
cd $G2i_HOME/java
SOURCE_DIR=$G2i_HOME
TARGET_CLASSES=$SOURCE_DIR/java/classes
$JAVA_HOME/bin/java -mx50m com.gensym.devtools.MakeProductJar -productName G2Jmail -sourceDir $SOURCE_DIR/java -targetFile $TARGET_CLASSES/G2JMail.jar -javaSource $SOURCE_DIR/java
