REM *** REMEMBER to Set the Release Directory in DISTDIR ***
set DISTDIR=%1
set KBSDIR=%2
echo .
echo "Dist Directory: " %1
echo "KBs Directory: " %2
REM
echo .
rem choice /cYN "Continue?: "
rem if %errorlevel% EQU 1 goto CONTINUE-COPY
REM
REM *******************
rem echo "*** Aborting Build ***"
rem goto ENDALL
REM *******************
:CONTINUE-COPY
REM
REM *** Copy utilities to KBS directory ***
xcopy /Y %DISTDIR%\g2cuidev.kb %KBSDIR%
xcopy /Y %DISTDIR%\g2uifile.kb %KBSDIR%
xcopy /Y %DISTDIR%\g2uimenu.kb %KBSDIR%
xcopy /Y %DISTDIR%\g2uiprnt.kb %KBSDIR%
xcopy /Y %DISTDIR%\g2uitree.kb %KBSDIR%
xcopy /Y %DISTDIR%\gdddemo.kb %KBSDIR%
xcopy /Y %DISTDIR%\gdddev.kb %KBSDIR%
xcopy /Y %DISTDIR%\gddlib.kb %KBSDIR%
xcopy /Y %DISTDIR%\gddroot.kb %KBSDIR%
xcopy /Y %DISTDIR%\gfr.kb %KBSDIR%
xcopy /Y %DISTDIR%\gms.kb %KBSDIR%
xcopy /Y %DISTDIR%\gmsdemo.kb %KBSDIR%
xcopy /Y %DISTDIR%\gold.kb %KBSDIR%
xcopy /Y %DISTDIR%\goldui.kb %KBSDIR%
xcopy /Y %DISTDIR%\guicolor.kb %KBSDIR%
xcopy /Y %DISTDIR%\guidata.kb %KBSDIR%
xcopy /Y %DISTDIR%\guide.doc %KBSDIR%
xcopy /Y %DISTDIR%\guide.kb %KBSDIR%
xcopy /Y %DISTDIR%\guidelib.kb %KBSDIR%
xcopy /Y %DISTDIR%\guidemo.kb %KBSDIR%
xcopy /Y %DISTDIR%\guidesa.kb %KBSDIR%
xcopy /Y %DISTDIR%\guigfr.kb %KBSDIR%
xcopy /Y %DISTDIR%\guimove.kb %KBSDIR%
xcopy /Y %DISTDIR%\guislide.kb %KBSDIR%
xcopy /Y %DISTDIR%\guitools.kb %KBSDIR%
xcopy /Y %DISTDIR%\gxl.kb %KBSDIR%
xcopy /Y %DISTDIR%\gxldemo.kb %KBSDIR%
xcopy /Y %DISTDIR%\protools.kb %KBSDIR%
xcopy /Y %DISTDIR%\ptroot.kb %KBSDIR%
xcopy /Y %DISTDIR%\starter.kb %KBSDIR%
xcopy /Y %DISTDIR%\sys-mod.kb %KBSDIR%
xcopy /Y %DISTDIR%\uil.kb %KBSDIR%
xcopy /Y %DISTDIR%\uilcombo.kb %KBSDIR%
xcopy /Y %DISTDIR%\uildefs.kb %KBSDIR%
xcopy /Y %DISTDIR%\uillib.kb %KBSDIR%
xcopy /Y %DISTDIR%\uilroot.kb %KBSDIR%
xcopy /Y %DISTDIR%\uilsa.kb %KBSDIR%
xcopy /Y %DISTDIR%\uilslide.kb %KBSDIR%
xcopy /Y %DISTDIR%\uiltdlg.kb %KBSDIR%
REM
goto ENDALL 
REM
REM *** Copy utilities to TESTS directory ***
xcopy /Y %DISTDIR%\g2cuidev.kb %TESTSDIR%
xcopy /Y %DISTDIR%\g2uifile.kb %TESTSDIR%
xcopy /Y %DISTDIR%\g2uimenu.kb %TESTSDIR%
xcopy /Y %DISTDIR%\g2uiprnt.kb %TESTSDIR%
xcopy /Y %DISTDIR%\g2uitree.kb %TESTSDIR%
xcopy /Y %DISTDIR%\gddroot.kb %TESTSDIR%
xcopy /Y %DISTDIR%\gfr.kb %TESTSDIR%
xcopy /Y %DISTDIR%\gms.kb %TESTSDIR%
xcopy /Y %DISTDIR%\gold.kb %TESTSDIR%
xcopy /Y %DISTDIR%\goldui.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guicolor.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guidata.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guide.doc %TESTSDIR%
xcopy /Y %DISTDIR%\guide.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guidelib.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guidemo.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guidesa.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guigfr.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guimove.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guislide.kb %TESTSDIR%
xcopy /Y %DISTDIR%\guitools.kb %TESTSDIR%
xcopy /Y %DISTDIR%\gxl.kb %TESTSDIR%
xcopy /Y %DISTDIR%\sys-mod.kb %TESTSDIR%
xcopy /Y %DISTDIR%\uil.kb %TESTSDIR%
xcopy /Y %DISTDIR%\uilcombo.kb %TESTSDIR%
xcopy /Y %DISTDIR%\uildefs.kb %TESTSDIR%
xcopy /Y %DISTDIR%\uillib.kb %TESTSDIR%
xcopy /Y %DISTDIR%\uilroot.kb %TESTSDIR%
xcopy /Y %DISTDIR%\uilsa.kb %TESTSDIR%
xcopy /Y %DISTDIR%\uilslide.kb %TESTSDIR%
xcopy /Y %DISTDIR%\uiltdlg.kb %TESTSDIR%
REM
:ENDALL
REM *** All Done ***
echo .
echo "*** Build Copy Completed ***"



