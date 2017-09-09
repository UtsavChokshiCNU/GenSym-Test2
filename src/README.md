# Gensym G2

This is the code repository for Gensym G2. Here's a quick overview of
"what's where", by directories:

- `Symscale` - not used (a defunct project to introduce multi-threading)
- `activex` - ActiveX control support ("Activex Link")
- `ant` - Master Ant scripts for building G2. Works fully on Windows, only partially on Linux
- `asdf` - The ASDF packages we use (only in development)
- `build` - not used (some ancient build scripts)
- `bundle` - for installers, files used to build the bundle. Currently, has a lot of files that are actually built and copied here automatically. In the long run, should be phased out.
- `chestnut` - Our Lisp -> C compiler
- `common` - A few common C headers for Gensym runtime
- `config` - not used (some ancient configurations)
- `corba` - The G2 - CORBA bridge ("CORBA Link")
- `cpplink` - not used (C++ support for making bridges). Originally built by Siemens to fix a threading bug in ActiveX Link, which has since been fixed.
- `cppunit-1.13.2` - CppUnit unit test framework we use for C/C++
- `documentation` - User documentation in PDF and some sources in Asciidoc (most sources are in Adobe FrameMaker in a different branch)
- `dyndialogs` - not used (development/test version of Dynamic Dialogs support)
- `emacs` - stuff for using EMacs to develop G2 Lisp
- `ext` - G2 subsystem for interfacing with the platform (files, graphics...)
- `fnt` - Fonts libraries
- `fonts` - Fonts themselves and some libraries
- `freetype` - The FreeType library
- `g2` - The G2 (server) itself. `g2/c` has the Lisp compiled sources
- `g2db` - The G2 database bridges
- `g2fasth` - G2 Functional And Stress Test Harness (in development)
- `g2i` - G2 "Layered products" - SymCure, EScor, ReThink, Optegrity/integrity, part of NeurOnline, HLA bridge
- `g2opc` - G2 - OPC bridge (only classic, no OPC UA yet)
- `g2pi` - G2 - PI bridge
- `gdanol` - GDA (G2 Diagnostic Assistant) and parts of NOL
- `gen` - Makefiles for Linux and makefile generator (which is not used). There are also Makefiles for some other platforms, which are not used and will be phased out.
- `gservice` - Support for running G2 (server) as a service
- `gsi` - LibGSI, for building bridges, `gsi/c` has Lisp->C code
- `gw` - The GWEB bridge, `gw/c` has Lisp->C code
- `java` - Java code - JavaLink and some stuff which is largely unused (Telewindows 2 "toolkit", "G2 studio"...)
- `javalink` - placeholder for JavaLink
- `jpeg` - The JPEG library
- `kbs` - System KBs, in their "primary" KB source form, and, to the extent possible, in XML form. In general, we try to keep their XML representations up-to-date for grepping and such.
- `libiconv` - Libiconv library for character set conversions
- `libpng` - libpng library for PNG format
- `libxml2` - The XML library we use in G2
- `lic` - Code for licensing server and client(s)
- `license` - Has the license files and bundle keys for development
- `lisp` - The (Common) Lisp source code of G2 ("the kernel")
- `mtg2` - Multi-threading G2 (in development)
- `nolstudio` - Java source code for NOL Studio, a user interface for NOL, a "neural network designer" of sorts.
- `opcfoundation` - Library for OPC
- `openssl-0.9.8zh` - The OpenSSL we use
- `promote` - Some scripts used in buidling installer on Linux. Designed to be files which are directly copied to the user installation, rather than needing special building. In addition, there are some files which do need building, primarily customer makefiles.
- `pthreads-w32` - PThreads on Windows library
- `rtl` - Chestnut runtime support (low level C routines that work with Chestnut generated code)
- `scintilla` - Editor library used in TWNG
- `scripts` - Scripts to run G2 in development and build on Linux
- `specific` - "not regularly" built object files. We aim to remove this directory. Initially designed to be architecture specific files, primarily binaries which are built by us in some other fashion, such as SSL and XML libraries, but also header files and libraries/programs we acquired prebuilt. These are used in the build, rather than distributed directly (contrast the promote module).
- `sunstudio` - For using Sun Studio (not maintained)
- `super` - some ancient scripts (for building and such) - not used
- `tests` - The Regression Tests
- `tools` - various tools, some of which are not used at this time
- `tw` - Telewindows client, `tw/c` has Lisp->C code
- `twng` - Telewindows NG client (using MFC), Windows only
- `util` - various utilities
- `vstudio` - The VisualStudio 2010 solutions and projects for use on Windows
- `vstudio2015` - not used - VS2015 solutions/projects ("preparing for upgrade")
- `widgets` - Widgets for TWNG
- `xanalys` - Support for running G2 under Lispworks and other lisps
- `xml` - Wrapper to use libxml2 from Lisp
- `xtp` - The XTP Widget library for MFC from Codejock

At the time of this writing, the G2 applications are stored in another
Git repository, at: https://github.com/trilogy-group/ignite-gensym-kbs

The `Updater`, Java project for automatically updating G2 on customer site,
which was not used at the time of this writing, is stored in another Git
repository, at: https://github.com/trilogy-group/ignite-gensym-updater
