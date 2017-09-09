Chestnut notes
===============

Those are random notes derived from my Chestnut experience - budden73 (Denis Budyak)

Parts of Chestnut
-----------------

Chestnut consists of:
- translator (lisp application which takes lisp files and produces C files), located at src/chestnut
- C runtime library, located at src/rtl

Librtl is a C library containing hand-written C code for Chestnut runtime. On windows, it is built with src\vstudio\librtl\librtl.vcxproj . 
 
Versions of Chestnut
--------------------

There are several attributes of Chestnut version:
- platform
- bitness (32 or 64)
- underlying lisp implmenetation
- multithreading support

So names of Chestnut binaries are like 
```
src/chestnut/<platform><bitness>/trans-[mt-]<lisp-implementation>[.exe]
```

Building and running Chestnut
-----------------

### Concepts and examples

We're in the Lisp world, there's no distinct boundary between building Chestnut and translating app with Chestnut. 

Chestnut is one lisp application which can be loaded into the lisp image. 

Then one can proceed to translation controlled by the script. Simple (but not studied yet) example of translation script is src/rtl/tests/thread/translate.lisp. 

Alternatively, one can save lisp image with Chestnut enabled. This image can be used later as a command-line translator. This seem to be done by 

Chestnut binaries mentioned before are just images saved this way. They are used to build G2, see "translate" target in src/ant/build.xml.

### Command line options of Chestnut binaries

Main thing to know it that they depend on lisp implementation. 

While using *sbcl translator, pass build script as
```
*sbcl --load <script.lisp>
```
For CCL, something like this seem to work:
```
*ccl -n -l <script.lisp> --
```

### Chestnut with SLIME

This is an example how to build G2 in SLIME. This can be useful if you want trace of break some functions of Chestnut. 

First, create `start_emacs.bat` as follows:

### start_emacs.bat
```
set SBCL_HOME=c:\G2\src\tools\lisp\sbcl-1.3.7
cd /d c:\g2\src
D:\emacs-23.3\bin\runemacs.exe
```

Then run it and do the following (M-Key in EMACS culture is the same as Alt-Key). 
```
; issue a command to run slime:
 M-- M-x slime ccl64
; in slime, enter the following commands
(setf (current-directory) "c:/g2/src/chestnut/src/trans" *default-pathname-defaults* (current-directory))
(pushnew :optimize-translator *features*)
(pushnew :translator-supports-thread *features*)
(load (compile-file "../../../lisp/portable-threads.lisp"))
(load "build.lisp") 
; this is the end of loading chestnut - now we will load G2

(setf (current-directory) #p"c:/g2/src/lisp/" *default-pathname-defaults* (current-directory))
(load "123") ; load this only if you want to translate G2
Option and switches: 3urpmx
```

### Chestnut in Lispworks IDE

This is example how to build threaded examples, e.g. MTG2. Most code is borrowed from 
`src\chestnut\src\trans\3.lisp`

```
(change-directory "c:/g2/src/chestnut/src/trans")
;; borrowed from from 3.lisp
(pushnew :optimize-translator *features*)
(pushnew :translator-supports-thread *features*)
(load (compile-file "../../../lisp/portable-threads.lisp"))
(load "build.lisp") 
;(load "c:/g2/src/lisp/123.lisp") ; for translation of G2
```

Tests
-----

Tests for chestnut runtime is in src/rtl/tests. There is also src/vstudio/librtl/rtl_tests.sln Visual Studio solution which even builds and runs. 

Another set of tests is "ctest" system in src/lisp/systems.lisp - it is for testing foreign functions in C. I don't know yet how to build it, but obviously one can take 'ab', 'ls' or whatever g2 "system" as an example. 

Miscellaneous
------------

### Macros
It looks like macros cause problems. For each macro, something should be set up so that Chestnut knows how to translate this macro. Workaround for dummies is to wrap
your macros into `(eval-when (:compile-toplevel) ...)`. 

### Translate-file and translate-files
There are at least two ways to translate: trans:translate-file and trans:translate-files . It seems that translate-files creates main file as well. And, obviously there should be more differences. 

### Hanging translation in ccl

It happens. E.g. on my VM it always happens after `git clean -d -f`. Somewhere on a confluence there is a mention of some hang up while doing translation with Chestnut. Maybe it is the same thing, maybe not. 

### Incremental translation

I tried to translate G2 incrementally once, passing 3upmx, but it took more time than direct translation. Maybe my computer
was busy by some other things - I don't know.  

### Symbols of Chestnut runtime

See src/chestnut/src/trans/lisp/symbols.lisp

Other sources of information
-----------------------------

svn/documentation/trails.pdf
Something is mentioned in Confluence
