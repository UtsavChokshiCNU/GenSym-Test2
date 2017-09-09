@echo off

cd "C:\G2\src\tests\ShortestPathDemo"

"C:\G2\dst\g2\opt\g2.exe" -ok "C:\G2\license\g2sitev83.ok" -tcpport 1111 -rgn1lmt 250000000 -log "C:\G2\src\tests\ShortestPathDemo\admin\g2_log.txt" -module-map "C:\G2\src\tests\ShortestPathDemo\admin\g2.mm" -module-search-path "C:\G2\src\tests\ShortestPathDemo\kbs" -conf "C:\G2\src\tests\ShortestPathDemo\admin\config.xml" -kb "C:\G2\src\tests\ShortestPathDemo\kbs\drms.kb" -name "Gensym - Shortest Path Demo" -start -exit-on-abort -no-window

pause
