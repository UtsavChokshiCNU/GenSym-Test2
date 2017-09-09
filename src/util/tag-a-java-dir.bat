@echo off

rem uses Emacs' etags utility to build a tag file for Java code
rem jh, 5/21/97.

rem This file is designed to be invoked at each directory in a tree of java
rem   files.  The master batch file that invokes the present batch file multiple
rem   times is named tag-all-java-subdirs.bat and is generated automatically by
rem   util\EtagsGenerator.java (q.v.)

rem This batch file takes two command-line arguments:

rem %1% This argument is the pathname of the single TAGS file being built as
rem     this batch file is invoked multiple times.

rem %2% The pathname of the directory to be tagged.  It must a full pathname, so
rem     that meta-dot works from anywhere, not just the Java subdirectory (and
rem     they are legion) in which you happen to be.

if not exist *.java goto end

echo Tagging %2%

setlocal

rem Arrange to append to a single tagfile.
set ETAGS= \emacs-19.34\bin\etags.exe --language=none
set ETAGS= %ETAGS% --append --output=%1%

rem test regular expressions with the Emacs Lisp function 
rem   string-match <regexp-string> <string-to-match>

rem jh, 8/8/97.  Bug - what about package-friendly privacy (i.e.,
rem classes neither "public" nor "private" nor "protected")?

rem This regular expression gets toplevel class and interface names.
rem   Looks for privacy token followed by "class" or "interface" token.
set REGEXP1= --regex=/"[ \t]*\(public\|private\|protected\|abstract\)
set REGEXP1= %REGEXP1%[ \t]*\(class\|interface\)[ \t]*[a-zA-Z0-9_]*"/ 

rem This regular expression looks for some likely method definition
rem sites, missing some, but without false positives.
rem   Looks for two or more tokens, no operators.
set REGEXP2= --regex=/"[ \t]*[a-zA-Z0-9_]+[ \t]+[a-zA-Z0-9_ \t]+
rem   Then looks for parens immediately followed by an 
rem   open-curly-brace or a "throws" token.
set REGEXP2= %REGEXP2%([]a-zA-Z0-9_, \t\n[]*)[ \t\n]*\({\|throws\)"/

rem jh, 8/8/97.  Looks like etags only matches one line at a time,
rem so the above only works if there is an open-curly-brace on the
rem same line.  So we need to get even more heuristic with REGEXP3.  
rem Note that we are still out of luck for package-access methods, 
rem since their lack of qualifier tokens makes them hard to 
rem distinguish from method calls.  I guess we could eke out a
rem few futher wins at distinguishing call sites from declarations 
rem if we looked for two tokens not separated by a comma inside
rem a pair of parentheses when the first is not "new".

rem Look for one of the method-defining tokens followed by an 
rem open paren.
set REGEXP3= --regex=/"[ \t]*[a-zA-Z0-9_]*
set REGEXP3= %REGEXP3%\(public\|private\|protected\|
set REGEXP3= %REGEXP3%synchronized\|native\|volatile\|transient\)
set REGEXP3= %REGEXP3%[a-zA-Z0-9_ \n\t]*("/

%ETAGS% %REGEXP1% %REGEXP2% %REGEXP3% %2%\*.java

endlocal

:end
