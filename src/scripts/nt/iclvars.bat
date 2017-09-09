@echo off
Rem Intel(R) C++ Compiler Build Environment for 32-bit applications

echo.
echo Intel(R) C++ Compiler 9.0 Build Environment for 32-bit applications
echo Copyright (C) 1985-2005 Intel Corporation. All rights reserved.
echo.

@call "C:\Program Files\Microsoft Visual Studio\VC98\Bin\Vcvars32.bat"

echo.

SET ICPP_COMPILER90=C:\Program Files\Intel\Compiler\C++\9.0

SET INTEL_SHARED=C:\Program Files\Common Files\Intel\Shared Files

SET INTEL_LICENSE_FILE=C:\Program Files\Common Files\Intel\Licenses

SET PATH=%ICPP_COMPILER90%\Ia32\Bin;%INTEL_SHARED%\Ia32\Bin;%PATH%

SET LIB=%ICPP_COMPILER90%\Ia32\Lib;%LIB%

SET INCLUDE=%ICPP_COMPILER90%\Ia32\Include;%INCLUDE%

