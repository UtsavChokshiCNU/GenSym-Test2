SET PATH=.;.\jre\bin
SET CLASSPATH=.;.\jre\lib\rt.jar;.\jre\lib\jaws.jar;.\jre\lib\i18n.jar;.\jre\lib\sunrsasign.jar

java -Xmx340m com.gensym.nols.deploy.ModelReader %1
