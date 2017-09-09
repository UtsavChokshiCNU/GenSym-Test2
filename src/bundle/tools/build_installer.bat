C:
if exist C:\G2\src\bundle\stage\isproj-g2-84r3 rd /S /Q C:\G2\src\bundle\stage\isproj-g2-84r3
cd C:\G2\src\bundle\tools
buildipr 84r3
cd C:\G2\src\bundle\stage
if exist C:\G2\src\bundle\stage\isproj-g2-84r3_bak1 rd /S /Q C:\G2\src\bundle\stage\isproj-g2-84r3_bak1
cd C:\G2\src\bundle\stage\isproj-g2-84r3
"C:\Program Files\InstallShield\2011\System\IsCmdBld.exe" -p Gensym.ipr -u
cd C:\G2\src\bundle\stage\isproj-g2-84r3
"C:\Program Files\InstallShield\2011\System\IsCmdBld.exe" -p Gensym.ism
cd C:\G2\src\bundle\stage
if exist C:\G2\src\bundle\stage\Gensym84r3.zip del /F /Q C:\G2\src\bundle\stage\Gensym84r3.zip
"C:\Program Files\7-Zip\7z.exe" a Gensym84r3.zip "C:\G2\src\bundle\stage\isproj-g2-84r3\Media\Default\Disk Images\Disk1" -r
