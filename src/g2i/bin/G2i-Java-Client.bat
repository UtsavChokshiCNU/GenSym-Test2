setlocal
set G2HOME_=%G2_HOME%
set G2IHOME_=%G2I_HOME%

set CLASSPATH_=%G2IHOME_%\java;%CLASSPATH%;C:\JGoEval\JGo.jar;C:\JGoEval\JGoLayout.jar
set CLASSPATH_=%CLASSPATH_%;%G2_HOME%\javalink\classes;%G2_HOME%\tw2\classes
set CLASSPATH_=%CLASSPATH%_;%JAVAHOME%\jre\lib\i18n.jar;%JAVAHOME%\jre\lib\jaws.jar;%JAVAHOME%\jre\lib\rt.jar;%JAVAHOME%\jre\lib\sunrsasign.jar;%JAVAHOME%\lib\dt.jar;%JAVAHOME%\lib\htmlconverter.jar;%JAVAHOME%\lib\tools.jar;%JAVAHOME%\demo\jfc\Java2D\Java2Demo.jar;%JAVAHOME%\docs\guide\imf\spi-sample\CityIM.jar;%JAVAHOME%\docs\guide\awt\demos\lightweight\OpenlookButtons;C:\jdk1.3.1_05\docs\guide\awt\demos\lightweight\Spinner;%JAVAHOME%\docs\guide\awt\demos\lightweight\RoundButtons


rem start "G2i Java Client" /b  %JAVAHOME%\bin\javaw 

cd %G2iHOME_%/java
%JAVAHOME%\bin\java -classpath "%CLASSPATH_%" -Dg2i.home=%G2IHOME_%\com\gensym\g2i  com.gensym.g2i.g2i
