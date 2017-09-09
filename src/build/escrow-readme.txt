Brief instructions on how to build G2 and related products from the escrow
sources.

To build from a development environment, in addition to the files provided with
the escrow distribution, you will need a Sun Solaris machine running SunOS 5.6,
with the GNU gcc compiler installed.  To compile the resulting G2 on another
platform, you will need the appropriate platform's C compiler.  More information
below.



BUILDING G2 FROM C:

If you just want to build from the C sources (which were translated from the
lisp sources in many cases), you can use the runmake script, located in the
scripts directory.  This has a number of required environment variables:

SRCBOX: the top level "sandbox" of the compile.  E.g. /usr/escrow
DSTBOX: the "destination sandbox" for output.  We provide a platform hierarchy
	of output files to simplify building for multiple platforms from the
	same source tree.  E.g. /usr/escrow/dst/sparcsol
MACHINE: the machine type.  Supported machines: intelnt, sparcsol, hp9000s700,
	hpia64, linux, alphaosf, and rs6000.
PATH:	Modify to include $SRCBOX/scripts (%SRCBOX%\scripts\nt on Windows)
DISPLAY:Must be set for X in order to display the resulting G2

WINDOWS ONLY:
SCRIPTSBOX:equivalent to SRCBOX in escrow; location of "scripts" directory.
Compiler specific variables are set up with batch files:
C:\Program Files\Microsoft Visual Studio\VC98\Bin\VCVARS32.BAT
C:\Program Files\Microsoft SDK\SETENV.BAT
C:\Program Files\Intel\CPP\Compiler80\Ia32\Bin\iclvars.bat

runmake takes two required arguments, module and compile-type.  You can give
additional optional arguments to make.
e.g.
runmake gsi opt skeleton

The possibilities for module are: g2 tw gsi gw rtl fnt ext jpeg xml twplug, and,
on Windows only, activex gservice scintilla twng widgets xtp.  g2 tw gsi and gw
are translated from lisp; the rest are C-only modules.  There are some
dependencies within the modules.  Here is a build order which will work on Solaris:
	ext rtl fnt jpeg tw xml gsi gw g2
On windows, there are more modules:
	ext rtl fnt jpeg xml scintilla tw twplug gsi gw g2 xtp widgets twng activex gservice

If you want to put the files in a similar hierarchy as they would be when
shipped, use "install" target for runmake: runmake gsi opt install.  For the
kbs, this is done into a staging area with sparcsol's runmake kbs opt.

g2db is the G2 Database Bridges directory and its build procedure does not work
with runmake.  Instead you use the script g2db/mak/bdb (build database
bridge).  To actually build database bridges is more work because you need to
set up your database client, which is beyond the scope of this document.  g2pi
similarly does not work with runmake, and has its own g2pi/c/build-g2pi.bat.
	
Oracle Database Bridge Additional Environment Variables
GSIDIR:	Location of result of "runmake gsi opt install"
ORACLE_HOME: This would be the location of the oracle product. The build script
	for this module checks the ending directory name to find the appropriate
	makefile. For example, with Oracle 9.2, it specifically looks for the
	directory "920".
LD_LIBRARY_PATH	Modify to include $ORACLE_HOME/lib
PATH	Modify to include $ORACLE_HOME/bin


BUILDING G2 FROM LISP:

As mentioned at the top of this document, the following can only be executed on
a Sun Solaris machine running SunOS 5.6.

If you want to build from the Lisp sources, you will have to create some files,
with the following command:

First, cd to the top-level directory of the escrow.  Then, assuming csh,
echo \"`pwd`\" > lisp/dstbox.dat
echo \"`pwd`\" > lisp/srcbox.dat
echo \"`pwd`\" > lisp/toolsdir.dat

To use the development environment, cd to the lisp directory, and start up the
regular lucid compiler, ../lisp-clos-50.  Once it has started, (load "123"), and
answer 1 or 1r to the question of what to do.  It will expect you to have a
DISPLAY variable set for X in order to display the resulting G2.

To use the chestnut translator, similarly start up the chestnut compiler,
../trans-32b3c, and (load "123").  This time answer 3xp.

Use runmake as before on the resulting C sources which will be placed in the
g2 etc. directories.



OPENSSL:

The openssl module contains the download from www.openssl.org, with instructions
on building in openssl/README.gensym.  Pre-built libraries are in the "specific"
directory under the appropriate platform directory.

XML:

Similarly, the libxml2 module is the XML C parser and toolkit developed for the
Gnome project downloaded from http://xmlsoft.org/.  Instructions on building are
in libxml2/README.gensym.  Pre-built libraries are in the "specific" directory
under the appropriate platform directory.


JAVA PRODUCTS:

java is the source hierarchy for javalink and Telewindows 2, and it also does
not work with runmake.  Instead it uses its own utility called jmake to create
the java class files.  To use, set SRCBOX/DSTBOX as above.  jmake takes 2
arguments: a directory and a product.  The first product you need to build is
devtools, which doesn't do dependencies properly and so you have to specify the
directory to use as its own directory, and then you can make javalink separately
with the top-level directory.  Assuming your working directory is $SRCBOX/java,
and you have either $SRCBOX/scripts or %SRCBOX%\scripts\nt on your path,
these commands should work:

Additional environment variables needed:
PATH:	Must also include the java binary directory (E.g. /usr/j2se/bin)
CLASSPATH:Should include $SRCBOX/java and the usual locations of the java
	libraries as well as tools.jar. (E.g. /usr/j2se/lib, /usr/j2se/jre/lib,
	/usr/j2se/lib/tools.jar) 
LD_LIBRARY_PATH:Modify to include $SRCBOX/java/lib
JAVA_HOME:	Should point to where java is located
GSIBOX: Location of result of scripts/pm-gsi-promote, after runmake gsi o-mt

Windows additions:



jmake com/gensym/devtools devtools
jmake . javalink

Telewindows 2's "product" is its internal name, which is "sequoia".

Javalink also requires GSI to build the native interface DLL.  The makefile is
located in $SRCBOX/java/mkfiles/<platform>-jgilib-o, where platform is sparcsol,
intelnt, etc.  A number of environment variables must be set up, and these are
documented at the top of the makefiles. GSIBOX would be the directory containing
all the GSI libraries, including those which are generated from other products
such as ext and rtl (that is, equivalent to what would be shipped).

To build the javalink DLL, simply cd to the directory you wish the object files
to go in, and use make -f $SRCBOX/java/mkfiles/<platform>-jgilib-o.  On windows,
use nmake, and of course %SRCBOX%.  Note that there was a special reentrant
version of GSI used for javalink for many platforms: sparcsol, HP, RS/6000.  The
sources are probably not in your escrow, but the changes are not very large, and
with each G2 release are being pared down.  Details are provided in the trail
file mentioned below.



BUILDING ACTIVEXLINK:

ActiveXLink has its own complex build procedure.  First, you may wish to update
the build version, with build/update-rc-files activex/G2Com/G2Com.rc (a Solaris
script.)

Now, on a Windows machine, set the environment variable GSIDIR to the location
of the gsi you intend to use, probably %DSTBOX%\gsi\tape.  Start Visual Studio
version 6, load up %SRCBOX%\activex\G2Com\G2Com.dsw, and build.  You can do this
from the commandline (or supervisor) with:

msdev.exe #SRCBOX\activex\G2Com\G2Com.dsw /MAKE "G2Com - Win32 Release"

Finally, you need to stage ActiveX, which there is a script to do, but it
depends a lot on Gensym's internal filesystem structure, since it uses the
previously shipping version for some of the demos and other static files.  It
will need editing to work at a non-Gensym location.  Find it in
scripts/stage-axl (a Solaris script.)

Some more details about ActiveXLink can be found in the trail document
0243-activex-trivia.txt.  If you need to do it "properly" you'll need to acquire
a digital signature authorization from a provider like Verisign and sign
g2com.dll.  Our signature process is in activex\G2Com\axl-sign.bat, but depends
upon mapped drives and thus will need to be adjusted.  There is also a similar
digital signature procedure for the Telewindows ActiveX control, located in
activex\control\auxi\twaxsign.bat



APPLICATION PRODUCTS  (G2 developers utilities, e-SCOR, ReThink, Optegrity,
Integrity, NOL, HLA)

These products each have their own build script, called CreateBuild.bat, located
in the bin directory.  Each of them has a list of required environment variables
in commentary at the top.  For the escrow, these values will be useful:

G2_DB	should contain database kb files (E.g. %SRCBOX%\g2db\kbs)
JAVA_SRCBOX	should be equivalent to SRCBOX
CLASSPATH	should also include %SRCBOX%\g2i\java



The main developers utilities are in g2i/bin; the rest of the products' build
scripts are all located in g2i/sites/<productname>/bin.

The TWOCX CAB file is more complex to build, and should be done first.
Located in g2i\TwOCX\cab.  Procedure:
msdev TelewindowsAx.dsw /make @"TelewindowsAX - Win32 Release@" 
  Copy files to a staging directory:
  From twng: pegrp32g.dll and twng.exe
  From the Release directory: TelewindowsAx.ocx 
  Sign twng.exe
  makecab /F TelewindowsAX.DDF
  Sign the resulting cab file.  Copy to g2i\data for further processing by 
  g2i CreateBuild.bat.



MORE AUTOMATION:

Our environment is set up with a unix fileserver and served to Windows via
Samba and mapped drives.  We typically mount this filesystem as "K:".  This may
be reflected in some scripts.

If you want to figure out more automated scripts for building, you will need
cvs, and you will need to import all of the sources in the escrow into your cvs
repository.  You will probably also have to edit various of the scripts which
may have hardcoded pathnames in them.  Some scripts depend on our exact CVS
repository layout (e.g. that it is called "/gensym/ab-repos")

If you want to use the G2 moderated build system, called Supervisor and provided
in the super directory, you will have to change the names of machines and values
of variables etc.  Documenting Supervisor is beyond the scope of this readme.

We have a system in house to speed up the Solaris C compiles by having more than
one machine working on the list of files.  This is called the helper system.
The helper system has been stubbed out in the escrow; you will see references to
it in the makefiles, but the stubs should enable the existing makefiles to work
without modification.


MAKEFILES:

The makefiles for most of the platforms and products are automatically generated
from a lisp-based database located in gen/mfgen.  Edits will have to be made to
remove hard-coded pathnames from the gen/mfgen/generate-makefiles script before
this can be used, also as below.



DEVELOPMENT ENVIRONMENT:

Some development environment files are included; specifically Xemacs 19.13, our
enhancements to it (directory emacs), our shell configuration files (directory
config), and the Supervisor build shell (directory bin).

If you setenv the csh variable REF_SBOX to the location of the config directory
(e.g., /usr/escrow, if you have installed it as /usr/escrow/config), then you
can source config/base-cshrc.txt, and get the proper gensym environment.  You
may want to reference this file from ~/.cshrc.

The Solaris distribution of xemacs is provided as a tar file, which will unpack
to directory xemacs-19.13.  You can then run emacs directly by starting
xemacs-19.13/bin/xemacs.  Magically, it will get the proper paths so that it
finds all the pieces it needs.  Edit emacs/ab-boot.el to specify the location of
the extension files (e.g. /usr/escrow/emacs), and load that file.  You may want
to call that file ~/.emacs, so that these will be loaded automatically.

The bin directory contains directories naming each platform, and within those
are the contents of the /gensym/bin directory on that platform.  The main thing
it contains is binaries for the buildsh program, which is used by Supervisor to
actually launch commands on the individual platforms.  Some platforms also
contain additional scripts and programs useful on that particular platform.


PLATFORM REQUIREMENTS:

Solaris:Solaris 2.6 or higher
	Gnu C compiler GCC version 2.7.2.  Later will probably work.
	X window system (most any X server on a PC or the native one on the
		solaris box will work)
	To compile GSI we have a dependency on the GCC's _varargs.o, which has a
		hardcoded path.  This will have to be amended for your system.
		See gen/mfgen/commands-and-options.rel (makefile generator) and
		gen/mfiles/sparcsol-gsi-opt (makefile).
	Java 1.4

Microsoft Windows NT/2000:
	Any Windows 2000 version.  We have not compiled under 2003 yet.
	This can run on a surprisingly weak computer (e.g. Pentium Pro 200).
		Faster is, of course, better.
	Visual Studio C++ 6.0.  We use the Enterprise Edition.  We have not
		tested to see if a less expensive version would suffice.
		Command line functions available in the PATH and INCLUDE and LIB
		variables set up.  Note that Microsoft changed how things work
		with 7.0, and so we have not upgraded, due to the engineering
		effort involved. 
	Platform SDK February 2003 
	Intel C++ 8.0 or 9.0 Compiler
	Java 1.4
	Installshield 6.2


MORE DOCUMENTATION:

The module "trail" contains rather a lot of possibly outdated and irrelevant
information about Gensym products.  Of particular interest may be 

0179-building-javalink-t2.txt
	This contains many details about how to create javalink, and in
	particular, the javalink DLL.	

0040-single-regression-test-harness.txt
	This will explain how to run the regression tests using minivisor, the
	small version of our build/test harnesses, supervisor.

0282-supervisor.txt
	This talks more about supervisor.

0158-builds-and-promotion.html
	This document attempts to be a comprehensive overview of how to build
	the G2 and how it was promoted internally for shipment.  Many details of
	the gensym filesystem are necessarily included.  As with all of this
	documentation, it is somewhat out of date, but does contains useful
	background material.

Here are some of the tools which are included in some format in the escrow, and
their locations within the escrow: 

GPL Xemacs				xemacs-19.13.tar
Ilisp 5.6				xemacs-19.13.tar
Lucid Liquid Common Lisp 5.0.x		lisp-clos-50
Chestnut Lisp to C Translator		trans-32b3c
Perl (ActivePerl) 4.0  			specific/intelnt/perl4.exe
OpenSSL 0.9.7g				openssl/
XML toolkit 2.6.19			libxml2/
Scintilla 162				scintilla/
CodeJock XTP 10.2			xtp/
Rainbow spromps.lib (version unknown)	specific/intelnt/spromeps.lib
Gigasoft library: pegrp32d.dll		promote/bin/pegrp32d.dll 
		  pegrpapi.h		specific/intelnt/pegrpapi.h
Fonts (AGFA Monotype Corporation)	promote/fonts
