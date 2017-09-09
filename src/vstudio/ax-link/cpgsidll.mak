
debug : .\Debug\gsi.dll

.\Debug\gsi.dll : ..\gsi\Win32\Debug\gsi.dll
	copy ..\gsi\Win32\Debug\gsi.dll .\Debug\gsi.dll

release : .\Release\gsi.dll

.\Release\gsi.dll : ..\gsi\Win32\Release\gsi.dll
	copy ..\gsi\Win32\Release\gsi.dll .\Release\gsi.dll
