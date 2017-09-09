:ProductManager.bat
:AUTHOR: SJW
:CREATED: 4/26/99 

:DESCRIPTION:   

:CHECK FLAGS
if .%1. == .. goto USAGE

:CHECK IF CLASS FILE EXISTS
if not exist %SRCBOX%\java\com\gensym\core\ProductManager.class goto CHECK_SOURCE
goto RUN

:CHECK_SOURCE
if not exist  %SRCBOX%\java\com\gensym\core\ProductManager.java goto ERROR

:COMPILE
call javac  %SRCBOX%\java\com\gensym\core\ProductManager.java

:RUN
call java com.gensym.core.ProductManager -build -product %1
goto END

:USAGE
echo Usage: ProductManager.bat <PRODUCT_NAME>
echo <PRODUCT_NAME> options are core, javalink, sequoia
goto END

:ERROR
echo ERROR: ProductManager.java not found.  Please check your sandbox.

:END
