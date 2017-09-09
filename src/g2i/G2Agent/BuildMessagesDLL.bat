set "CUR_DIR=%~dp0"
set VS2010=%VS100COMNTOOLS%\..\..\VC
cd "%VS2010%"
call vcvarsall.bat x86
cd "%CUR_DIR%"

mc -U G2AgentMessages.mc
rc -r G2AgentMessages.rc
link -dll -noentry -out:.\Release\G2AgentMessages.dll G2AgentMessages.res

