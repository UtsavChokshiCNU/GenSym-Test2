zip %1%.zip regsvr32.exe
zip %1%.zip reg_axclient.bat
zip %1%.zip unreg_axclient.bat
zip %1%.zip AXClient.txt
zip %1%.zip AXClient.hlp
zip %1%.zip AXClient.cnt
zip %1%.zip AXClient.h
zip %1%.zip AXClient_i.c
cd release
zip ..\%1%.zip AXClient.dll
cd ..
zip %1%.zip docs\*.*
zip %1%.zip vbdemo\*.*
zip %1%.zip vbshell\*.*
zip %1%.zip WSSelectionAPI\*.*
