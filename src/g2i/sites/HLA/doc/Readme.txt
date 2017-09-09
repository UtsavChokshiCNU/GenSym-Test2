
				  GHLA TOOLKIT
				  Version 20b0



INTRODUCTION
------------

The formal definition of the Modeling and Simulation (M & S) High Level Architecture (HLA) comprises
three main components: the HLA rules, the HLA interface specification, and the HLA object model template
(OMT). It provides a language independent specification (LIS) and multiple language bindings to support
inter-simulation communication in a distributed simulation domain. To learn more about HLA please visit
the HLA web site. 

The High Level Architecture (HLA) is an integrated architecture which has been developed to provide a
common architecture for M&S. The HLA requires that inter-federate interactions use a standard API. The
specification defines the standard services and interfaces to be used by the federates in order to support
efficient information exchange when participating in a distributed federation execution and reuse of the
individual federates. 

The RTI provides services to federates in a way that is analogous to how a distributed operating system
provides services to applications. These interfaces are arranged into six basic RTI service groups: 
        a) federation management 
        b) declaration management 
        c) object management 
        d) ownership management 
        e) time management 
        f) data distribution management 

The six service groups describe the interface between the federates and the RTI, and the software services
provided by the RTI for use by HLA federates. The initial set of these services was carefully chosen to
provide those functions most likely to be required across multiple federations. As a result, federate
applications will require most of the services described. The RTI requires a set of services from the federate
that are referred to as 'RTI callbacks methods'. 

The G2 HLA toolkit is the communicate interface between the RTI and G2. It provides methods and
callback methods to any G2 application. The definition and basic implementation of these methods is
provided in the ghla.kb module. This module requires sys-mod.kb and uilroot.kb modules. You should
merge the ghla.kb module into your application and make it a required module. 

Before using this package, you should familiarize yourself with HLA and RTI. You should review the
documentation available from the HLA web site. In additional and since this implementation is based on the
C++ libraries of the RTI, the documentation of these libraries available from the HLA web site may be a
good resource for additional information. 



INSTALLATION
------------

Installation of the G2 HLA package


Before installing the G2-HLA package, ensure that you already installed RTI 1.3 NG V6. It contains.
the core technology and implementation of HLA. You may download a version from the  HLA
web site. In addition you will need the G2 Bundle V8.2r4 or later.

G2-HLA runs on Windows XP, 2000 and NT 4.0 SP6. Set the GHLA_HOME environment variable to point to
the location of HLA-20a0.  Set the RTI_HOME variable to point to the location of the installed
library and include files (for example C:\Program Files\RTI-NG-Pro-v4.0\Win32-VC6)

HISTORY
-------

Version 1.6 Changes
- Removed licensing, i.e. does not require an ok file to run
- Recompiled the bridge for "RTI-NG-Pro-v4.0" using VC6 libraries
- Updated gsi.dll library to G2 8.2r2 version

Version 1.5 Changes
- Recompiled with new Burlington phone numbers

Version 1.4r2 Changes
- support current RTI version and G2 6.x
- Updated/compiled bridge for RTI 1.3 NG V5: needed to switch RTI installation and undef MAX_NAME_LENGTH
  in GlbDef.h
- Updated bridge to support new Gensym site licenses
- Recompiled kbs for G2 6.x