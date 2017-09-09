@echo off
rem 
rem %1 - Working copy (e.g. c:\g2) 
rem      or installed version (e.g. "C:\Program Files (x86)\Gensym\g2-8.3r1") 
rem      home directory
rem %2 - nonempty argument means to run performance test against installer 
rem      (e.g. installer)
rem 

setlocal

set UC_ID=uc11rpc
set UC_KB=uc11\uc11rpc.kb
set UC_ITERATIONS=1000000
set UC_SHUTDOWN=true
set UC_SETUP=uc11setup.bat

call run-uc.bat %1 %2
