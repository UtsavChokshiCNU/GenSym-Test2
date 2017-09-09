@REM java -jar slave.jar -jnlpUrl http://aar.gdev.com/computer/Gensym-AAR-slave01/slave-agent.jnlp -jnlpCredentials aarjnlp:Bv8QPyh5UVPt

cd ..\Acceptance
call devenv /Build "Debug" Acceptance.sln
cd ..\..\..\automation\Acceptance\
call SlaveLauncher.exe