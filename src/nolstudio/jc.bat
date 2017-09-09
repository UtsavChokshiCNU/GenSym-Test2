REM delete all classes
del /s *.class

REM compile everything
javac -J-mx120m -g:none -O com\gensym\nols\main\NeurOnLine.java
javac -g:none -O com\gensym\nols\data\function\*.java
javac -g:none -O com\gensym\nols\deploy\*.java
javac -g:none -O com\gensym\nols\deployutil\ActiveXRegisterManager.java
javac -g:none -O com\gensym\nols\data\VersionManager.java
javac -g:none -O com\gensym\nols\data\VersionManagerForOnlineProcessor.java
javac -g:none -O com\gensym\nols\data\VersionManagerForOnlineOptimizer.java

pause

