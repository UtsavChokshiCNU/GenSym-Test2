set JAVA_HOME=C:\Java\jdk1.6.0_16
set PATH=%JAVA_HOME%\bin;%PATH%;%1;%ANT_HOME%\bin

shift

ant %1 %2 %3 %4 %5 %6 %7 %8 %9