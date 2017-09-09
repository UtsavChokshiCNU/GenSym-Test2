@echo off
cd "%SRCBOX%\Java\activex"
ren *.tlb *.t
ren *.reg *.r
"%JAVAPLUGIN_HOME%\bin\unregbean.exe" -u ExceptionTraceDisplay.Bean
"%JAVAPLUGIN_HOME%\bin\unregbean.exe" -u ItemProxy.Bean
"%JAVAPLUGIN_HOME%\bin\unregbean.exe" -u MultipleWorkspacePanel.Bean
"%JAVAPLUGIN_HOME%\bin\unregbean.exe" -u ScriptUtilities.Bean
"%JAVAPLUGIN_HOME%\bin\unregbean.exe" -u TwConnector.Bean
ren *.t *.tlb
ren *.r *.reg
cd "%SRCBOX%"
