;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; INTEGRITY-FAMILY - Integrity Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduj and wmorris
(defvar g2-shortcut-folder-name "Gensym Integrity 3.6r1")
(defvar integrity-shortcut-folder-name "Gensym Integrity 3.6r1")
(defvar optegrity-shortcut-folder-name "Gensym Optegrity 3.6r1")
(defvar integrity-search-path-and-ok-file "-module-search-path kbs\\utils ..\\integrity-kbs ..\\optegrity-kbs ..\\protools\\kbs ..\\gw\\kbs ..\\javalink\\kbs ..\\tw2\\kbs ..\\gda ..\\activexlink -ok ..\\g2\\g2.ok")

(require "g2-62r2-family")			; G2 6.2r2
;;(require "g2-62r0-family")			; G2 6.2r0
;;(require "g2-52r1-family")			; G2 6.0r1
;;; Use this for 3.4r0 version of Integrity (require "g2-family")			; G2 5.1r7
(provide "integrity-36r1-family")

;;; normally we refer to versions as something like :32r0, which the code
;;; automatically figures out what to do for pretty name etc.  However, with
;;; the version numbers that have a suffix, the code is stupid about case,
;;; and ends up lower casing it all.  So you have to define a version if you
;;; have an uppercase suffix.
;;;
;;; +++
;;; Change this when a new build is promoted to the e-ship directory.  This should be 
;;; changed according to the promote.
(def-part-version :36r1-B02L16 :major 3 :minor 6 :revision 1 :suffix "-B02L16" :letter "r")
;;;(def-part-version :36r0-B02G10 :major 3 :minor 6 :revision 0 :suffix "-B02G10" :letter "r")
;;; (def-part-version :35r1-B02B20 :major 3 :minor 5 :revision 1 :suffix "-B02B20" :letter "r")
;;; (def-part-version :35r0-B01J02 :major 3 :minor 5 :revision 0 :suffix "-B01J02" :letter "r")
;;; (def-part-version :34r0-B01F22 :major 3 :minor 4 :revision 0 :suffix "-B01F22" :letter "r")

;;;(def-part-version :33r0-B01B15 :major 3 :minor 3 :revision 0 :suffix "-B01B15" :letter "r")

;;;(def-part-version :32r0-B00L15 :major 3 :minor 2 :revision 0 :suffix "-B00L15" :letter "r")

;;;(def-part-version :33r0-B01A15 :major 3 :minor 3 :revision 0 :suffix "-B01A15" :letter "r")

;;;(def-part-version :33r0-B01A24 :major 3 :minor 3 :revision 0 :suffix "-B01A24" :letter "r")



;;;; ok file definitions
;; the following forms create variables containing parts and components for all
;; of the ok files, which variables will be referenced in the bundle's
;; components. You would append -family-ok-components to the defining name to
;; get the variable name, e.g., integrity-core-development turns into
;; integrity-core-development-family-ok-components when referenced.
;;;
;;; The numbers in the parenthesis pertain to the number of users is authorized.  No
;;; need to change this.  There is one definition for each bundle.
(def-g2-ok-components (integrity-reasoner-development :obfuscate t) integrity "Integrity Reasoner Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
                  (1 "-dec25-2002")
			(1 "-jan25-2003") (1 "-feb25-2003") (1 "-mar25-2003")
			(1 "-apr25-2003") (1 "-may25-2003") (1 "-jun25-2003")
			(1 "-jul25-2003") (1 "-aug25-2003") (1 "-sep25-2003")
			(1 "-oct25-2003") (1 "-nov25-2003") (1 "-dec25-2003")
))

(def-g2-ok-components (integrity-reasoner-deployment :obfuscate t) integrity "Integrity Reasoner Deployment"
		      (4 8 16 20 24 28 32
                  (1 "-dec25-2002")
			(1 "-jan25-2003") (1 "-feb25-2003") (1 "-mar25-2003")
			(1 "-apr25-2003") (1 "-may25-2003") (1 "-jun25-2003")
			(1 "-jul25-2003") (1 "-aug25-2003") (1 "-sep25-2003")
			(1 "-oct25-2003") (1 "-nov25-2003") (1 "-dec25-2003")
))

;;; Optegrity bundle
(def-g2-ok-components (optegrity-reasoner-development :obfuscate t) optegrity "Optegrity Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
                  (1 "-dec25-2002")
			(1 "-jan25-2003") (1 "-feb25-2003") (1 "-mar25-2003")
			(1 "-apr25-2003") (1 "-may25-2003") (1 "-jun25-2003")
			(1 "-jul25-2003") (1 "-aug25-2003") (1 "-sep25-2003")
			(1 "-oct25-2003") (1 "-nov25-2003") (1 "-dec25-2003")
))

(def-g2-ok-components (optegrity-reasoner-deployment :obfuscate t) optegrity "Optegrity Deployment"
		      (4 8 16 20 24 28 32
                  (1 "-dec25-2002")
			(1 "-jan25-2003") (1 "-feb25-2003") (1 "-mar25-2003")
			(1 "-apr25-2003") (1 "-may25-2003") (1 "-jun25-2003")
			(1 "-jul25-2003") (1 "-aug25-2003") (1 "-sep25-2003")
			(1 "-oct25-2003") (1 "-nov25-2003") (1 "-dec25-2003")
))


;;;the following list of components is in every bundle, so abstract it out here
;;;
;;;  This defines the components that are common to every Integrity bundle.  There is no
;;;  need to change this unless we add another component to the common list.  If addition
;;;  is required, then make sure the addition is within the parenthesis.
(defvar integrity-common
  '(javalink integrity-client ping-manager remote-OS-agent
    java-SNMP G2-snmp-hpov-bridge G2-SNMP-netview integrity-documentation
    socket-manager
    g2-for-integrity-documentation
    protools activexlink weblink telewindows2
    telewindows g2 gateway g2-readme gda ))

(defvar optegrity-common
  '(opt-javalink optegrity-client remote-OS-agent optegrity-documentation
    socket-manager opt-documentation opt-protools opt-activexlink opt-weblink opt-telewindows2
    opt-telewindows opt-g2 opt-gateway opt-gda opt-g2-readme ))

(defvar int-g2-bridges-common
  '(corbalink opclink Oraclebridge Sybasebridge ODBCbridge gservice))

(defvar opt-g2-bridges-common
  '(opt-corbalink opt-opclink opt-Oraclebridge opt-Sybasebridge opt-ODBCbridge opt-gservice))


;;; finally, time to define the family file!
;;;
;;;  The break down is family, bundle, component, and finally part.  Here there is only one
;;;  family, Integrity.  No changes should be made here unless another bundle is to be added
;;;  to the Integrity family.
;;;
;;;  Below is a description of the structure for the family definiation:
;;;    index                   never change this, Integrity is setup for index of 4
;;;    file-syntax-version     this is used by the parser of this file, do not change
;;;    print-name              the name to be displayed
;;;    bundles                 defines the bundles that make up the family
;;;    directory               the directory where the files will be placed once installed
;;;    guid                    a unique identifier, do not change
;;;    splash-screen           defines the splash screen file name
(def-family integrity-36r1
    :index 15
    :file-syntax-version 10
    :print-name "Integrity"
    :bundles (integrity-reasoner-development
	       integrity-reasoner-deployment
             optegrity-reasoner-development
	       optegrity-reasoner-deployment)
    :directory "integrity36r1"
    :guid "243D4BB3-9EE7-11D4-8111-00A02431D004"
    :splash-screen "integrity-setup.bmp")

;;; the eight bundles that make up the Integrity family
;;;
;;;  Notice that each bundle definition contains the integrity-common component.  The 
;;;  integrity-common was defined above; however, each of the parts in the integrity-common
;;;  component must be defined.
;;;
;;;  The structure of the bundle definition are:
;;;     version                  the version in which this represents
;;;     components               the components that make up this bundle.
;;;
;;;   The reasoner components include:
;;;     integrity-common          defined above
;;;     integrity-resoner-kbs     core and reasoner KB modules
;;;     reasoner development oks  ok files for development
(def-bundle integrity-reasoner-development
    :version :36r1
    :components (integrity-common integrity-reasoner-kbs int-g2-bridges-common
		  integrity-reasoner-development-family-ok-components))

;;;   The deployment bundles include the exact same files as their development counterparts
;;;   with the exception of the ok files.  They are for deployment vs. development.
(def-bundle integrity-reasoner-deployment
    :version :36r1
    :components (integrity-common integrity-reasoner-kbs int-g2-bridges-common
		  integrity-reasoner-deployment-family-ok-components))

;;; *******************************************************************************
;;; Optegrity bundle definition
;;;
(def-bundle optegrity-reasoner-development
    :version :36r1
    :components (optegrity-common optegrity-reasoner-kbs opt-g2-bridges-common
		  integrity-reasoner-development-family-ok-components))

;;;   The deployment bundles include the exact same files as their development counterparts
;;;   with the exception of the ok files.  They are for deployment vs. development.
(def-bundle optegrity-reasoner-deployment
    :version :36r1
    :components (optegrity-common optegrity-reasoner-kbs opt-g2-bridges-common
		  integrity-reasoner-deployment-family-ok-components))


;;; components and their parts below
;;;
;;;  Components will never change unless there is an addition to the component
;;;  being defined.  If a new part is to be added, it must appear within the
;;;  parenthesis of the parts attribute.  The structure for the component is
;;;  as follows:
;;;    print-name               the name to be displayed during installation
;;;    parts                    a list of parts that make up the component


;;;**********************************************************************************************
;;; Integrity Client

(def-component integrity-client
  :print-name "Integrity Client"
  :parts (integrity-client-intelnt integrity-client-sparcsol));integrity-client-sparcsol

;;;  +++
;;;  Parts give the most detail for the software.  Most of the changes will be 
;;;  made here pertaining to the version attribute of the part structure.
;;;  The part structure is as follows:
;;;    version                  this must match the version supplied when the
;;;                             promotion was done.  
;;;    source                   defines the part that was promoted.  When promotion
;;;                             is done you will see a directory comprised of
;;;                             the source and version (i.e.  opex-client-33r0-B01B15)
;;;    platforms                a list of supported platforms enclosed in double-quotes
;;;    environment-variables    used by the installer to create an entry in the 
;;;                             registry file for an environment variable
;;;    destination-directory    the directory in which to place the files on the
;;;                             installed system
;;;    source-ship-type         don't know, leave alone
;;;    shortcuts                used by the installer to create a shortcut to start
;;;                             the defined part, in this case the Client
(def-part integrity-client-intelnt
    :version :36r1-B02L16
    :source opex-client
    ;; this contains a self extracting installer.  This is no doubt wrong.
    ;; finishing later.
    :platforms ("nt")
    ;;;:environment-variables (integrity_home)
    :destination-directory client
    :source-ship-type :internal
    :shortcuts (integrity-client)
    :postinstall-code "integrityPostInstall(\"Integrity\");")

(def-part integrity-client-sparcsol
    :version :36r1-B02L16
    :source opex-client
    :platforms ("sparcsol")
    :destination-directory client
    :source-ship-type :internal)


;;; the default value of an environment variable is the directory name of its
;;; associated part, as concatenated with the user install directory
;;; 3/4/02 WSM  removed ->(def-environment-variable integrity_home)

;;; This defines a shortcut for NT only platforms.  The structure of the definition
;;; is as follows:
;;;   folder-name              name of the folder to create under Programs
;;;   application-display-name name to display as the shortcut
;;;   application-directory    directory where the initiating file can be found
;;;   target-name              name of the file that initiates the application
(def-shortcut integrity-client
    :folder-name integrity-shortcut-folder-name
    :application-display-name "Integrity Client"
    :application-directory "client\\bin"
    :target-name "integrity.bat")

;;;  Documentation component
(def-component integrity-documentation
    :print-name "Integrity Documentation"
    :parts (integrity-doc))

;;; The special component g2-for-integrity-documentation is based on the
;;; component DOCUMENTATION, but excludes the Solaris platform. This component
;;; has G2's documentation, defined by the required g2-<ver>-family.lisp module.
;;; But it turns out the documenation can't fit on the CD for this platform.
;;; This is just being done now to save space: we hope later to rearrange things
;;; and do some compression so this is not necessary. (MHD 7/26/02)

(def-component g2-for-integrity-documentation
  :parent documentation
  :non-platforms ("sparcsol"))
  
  

;;;  +++
;;;  A new attribute of the part structure is:
;;;    indep             this indicates that it is an independent part.  Independent
;;;                      with respect to the operating system.  Possible values are
;;;                      t for TRUE or f for FALSE.
(def-part integrity-doc
    :source opexdoc
    :version :36r1-B02L16
    :destination-directory doc
    :indep t
    :shortcuts (int-users-guide int-ref-man int-util-guide int-sockman-guide
                int-snmp-users-guide int-jsnmp-users-guide int-rel-notes
                int-demo-guide int-dxi3db-primer))

(def-shortcut int-users-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Integrity User's Guide"
    :application-directory "doc"
    :target-name "IntUsersGuide.pdf")

(def-shortcut int-ref-man
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Integrity Reference Manual"
    :application-directory "doc"
    :target-name "IntRefManual.pdf")

(def-shortcut int-util-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Integrity Utilities Guide"
    :application-directory "doc"
    :target-name "IntUtilGuide.pdf")

(def-shortcut int-sockman-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Integrity Socket Manager User's Guide"
    :application-directory "doc"
    :target-name "IntJSockManGuide.pdf")

(def-shortcut int-snmp-users-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Integrity G2-SNMP User's Guide"
    :application-directory "doc"
    :target-name "IntSNMPUsersGuide.pdf")

(def-shortcut int-jsnmp-users-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Integrity Java G2-SNMP User's Guide"
    :application-directory "doc"
    :target-name "IntJSNMPUsersGuide.pdf")

(def-shortcut int-rel-notes
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Integrity 3.6r1 Release Notes"
    :application-directory "doc"
    :target-name "IntRelNotes.pdf")

(def-shortcut int-demo-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Integrity Demo Guide"
    :application-directory "doc"
    :target-name "IntDemoGuide.pdf")

(def-shortcut int-dxi3db-primer
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Integrity DXI3DB Primer"
    :application-directory "doc"
    :target-name "DXI3DB-Primer.pdf")


;;;  Ping manager component
(def-component ping-manager
  :print-name "Ping Manager"
  :parts (ping-manager))

;;;  +++
;;;  Ping manager part.
(def-part ping-manager
    :source pingmgr
    :version :36r1-B02L16
    :platforms ("nt" "sparcsol" "hpux") 
    :destination-directory bin)

;;;  Socket Manager component
(def-component socket-manager
    :print-name "Socket Manager"
    :parts (socket-manager))

;;;  +++
;;;  Socket Manager part
(def-part socket-manager
    :source sockman
    :version :36r1-B02L16
    :platforms ("nt" "sparcsol")
    :destination-directory sockman)

;;;  Discovery component (NetSleuth and ODG java class files)
(def-component integrity-discovery
    :print-name "Auto Discovery"
    :parts (integrity-discovery))

;;;  Remote OS Agent component
(def-component remote-OS-agent
  :print-name "Remote OS Agent"
  :parts (remote-OS-agent))

;;;  +++
;;;  Remote OS Agent part
(def-part remote-OS-agent
  :source rosa
  :version :36r1-B02L16
  :source-ship-type :internal
  :destination-directory remote-os
  :platforms ("nt" "sparcsol"))

;;;  Reasoner KB modules component
(def-component integrity-reasoner-kbs
  :print-name "Integrity KBs"
  :parts (integrity-reasoner-kbs))

;;;  +++
;;;  Reasoner KB modules part
(def-part integrity-reasoner-kbs
    :source intereas
    :version :36r1-B02L16
    :destination-directory "integrity-kbs"
    :shortcuts (reasoner-shortcut reasoner-sym-dev-guide reasoner-sym-modeling-guide)
    :indep t) 

(def-shortcut reasoner-shortcut
    :folder-name integrity-shortcut-folder-name
    :application-display-name "Integrity"
    :application-directory "integrity-kbs"
    :target-name "reasoner.bat")

(def-shortcut reasoner-sym-dev-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "SymCure Developers Guide"
    :application-directory "doc"
    :target-name "IntSymDevGuide.pdf")

(def-shortcut reasoner-sym-modeling-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "SymCure Modeling Guide"
    :application-directory "doc"
    :target-name "IntSymModelingGuide.pdf")

;;;  HPOV SNMP Bridge component.  Note if the print-name must contain spaces,
;;;  double-quotes must be used.
(def-component G2-snmp-hpov-bridge
  :print-name "G2 SNMP HPOV Bridge"
  :platforms ("sparcsol" "hpux")
  :parts (G2-snmp-hpov-bridge))

;;;  +++
;;;  HPOV SNMP Bridge part
(def-part G2-snmp-hpov-bridge
    :version :36r1-B02L16
    :platforms ("hpux" "sparcsol")
    :source g2snmpov
    :destination-directory g2snmpov)

;;;  Generic Java SNMP Bridge component
(def-component java-SNMP
  :print-name "Java Generic SNMP Bridge"
  :platforms ("nt" "sparcsol")
  :parts (java-SNMP))

;;;  +++
;;;  Generic Java SNMP Bridge part
(def-part java-SNMP
    :source g2snmpgn
    :version :36r1-B02L16
    :destination-directory jsnmp
    :shortcuts (java-SNMP-receiver java-SNMP-requests))

;;;  Shortcut definitions for the Generic Java SNMP bridge (NT only)
(def-shortcut java-SNMP-receiver
    :folder-name integrity-shortcut-folder-name
    :application-display-name "SNMP Trap Receiver"
    :application-directory "jsnmp\\bin"
    :target-name "receiver.bat")

(def-shortcut java-SNMP-requests
    :folder-name integrity-shortcut-folder-name
    :application-display-name "SNMP Set Requests"
    :application-directory "jsnmp\\bin"
    :target-name "requests.bat")

;;;  NetView SNMP Bridge component
(def-component G2-SNMP-netview
  :platforms ("aix")
  :parts (G2-SNMP-netview))

;;;  +++
;;;  NetView SNMP Bridge part
(def-part G2-SNMP-netview
    :platforms ("aix")
    :source g2snmpnv
    :version :36r1-B02L16
    :destination-directory g2snmpnv)

#| ;; commenting this out.  Currently there is only the readme first component, and
   ;; there is no separate readme file.  It is changes, reinstate as appropriate,
   ;; and reinstate component usage in bundle definitions above.  yduj, 6/28/01
;;;  Integrity Readme component
(def-component integrity-readme
  :print-name "Readme"
  :parts (integrity-readme))

;;;  +++
;;;  Integrity Readme part.  Note the source is a directory listing and a new attribute:
;;;    source-filename          defines the name of the file to pick up from the source.
(def-part integrity-readme
    :indep t
    :source "/home/development/installers/release-files"
    :source-filename "integrity-readme-first-36r1.txt"  ;;change this for each release!
    :destination-filename "readme.txt")

|#

;;; **********************************************************************************
;;; Optegrity components
;;;
(def-component optegrity-client
  :print-name "Optegrity Client"
  :parts (optegrity-client-intelnt optegrity-client-sparcsol));optegrity-client-sparcsol

(def-part optegrity-client-intelnt
    :version :36r1-B02L16
    :source opteg-client
    :platforms ("nt")
    ;;;:environment-variables (optegrity_home)
    :destination-directory optclient
    :source-ship-type :internal
    :shortcuts (optegrity-client)
    :postinstall-code "integrityPostInstall(\"Optegrity\");")


(def-part optegrity-client-sparcsol
    :version :36r1-B02L16
    :source opteg-client
    :platforms ("sparcsol")
    :destination-directory optclient
    :source-ship-type :internal)

(def-environment-variable optegrity_home)

(def-shortcut optegrity-client
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "Optegrity Client"
    :application-directory "optclient\\bin"
    :target-name "optegrity.bat")

(def-component optegrity-documentation
    :print-name "Optegrity Documentation"
    :parts (optegrity-doc))


(def-part optegrity-doc
    :source optegdoc
    :version :36r1-B02L16
    :destination-directory optdoc
    :indep t
    :shortcuts (opt-users-guide opt-ref-man opt-util-guide opt-sockman-guide
                opt-sym-dev-guide opt-sym-modeling-guide opt-rel-notes
                opt-demo-guide opt-dxi3db-primer))

(def-shortcut opt-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity User's Guide"
    :application-directory "optdoc"
    :target-name "OptUsersGuide.pdf")

(def-shortcut opt-ref-man
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity Reference Manual"
    :application-directory "optdoc"
    :target-name "OptRefManual.pdf")

(def-shortcut opt-util-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity Utilities Guide"
    :application-directory "optdoc"
    :target-name "IntUtilGuide.pdf")

(def-shortcut opt-sockman-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity Socket Manager User's Guide"
    :application-directory "optdoc"
    :target-name "IntJSockManGuide.pdf")

(def-shortcut opt-sym-dev-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity SymCure Developers Guide"
    :application-directory "optdoc"
    :target-name "OptSymDevGuide.pdf")

(def-shortcut opt-sym-modeling-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity SymCure Modeling Guide"
    :application-directory "optdoc"
    :target-name "OptSymModelingGuide.pdf")

(def-shortcut opt-rel-notes
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity 3.6r1 Release Notes"
    :application-directory "optdoc"
    :target-name "OptRelNotes.pdf")

(def-shortcut opt-demo-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity Demo Guide"
    :application-directory "optdoc"
    :target-name "IntDemoGuide.pdf")

(def-shortcut opt-dxi3db-primer
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity DXI3DB Primer"
    :application-directory "optdoc"
    :target-name "DXI3DB-Primer.doc")


(def-component optegrity-reasoner-kbs
  :print-name "Optegrity KBs"
  :parts (optegrity-reasoner-kbs))

(def-part optegrity-reasoner-kbs
    :source optegrity
    :version :36r1-B02L16
    :destination-directory "optegrity-kbs"
    :shortcuts (optegrity-shortcut)
    :indep t) 

(def-shortcut optegrity-shortcut
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "Optegrity"
    :application-directory "optegrity-kbs"
    :target-name "optegrity.bat")

;;;==========================================================================================================
;;;; Components



(def-component opt-g2
  :parts
  (opt-g2-exe-intelnt opt-g2-exe-unix
		  opt-g2passwd-exe-intelnt opt-g2passwd-exe-unix
		  opt-index-dic opt-kojin-dic opt-main-dic opt-ext-directory

		  ;; note: same files as for TW, may overwrite:
		  opt-g2-gen16ut-dll-intelnt
		  opt-g2-gen32-dll-intelnt
		  opt-g2-gen32ut-dll-intelnt

		  opt-g2-blank-ok

		  opt-kbs opt-fonts)
  :print-name "G2 (and utilities)")

(def-component opt-telewindows
  :parts (opt-tw-exe-intelnt
	   opt-tw-exe-unix

	   opt-tw-nptwplug-dll-intelnt

	   ;; note: same files as for G2, may overwrite:
	   opt-tw-gen16ut-dll-intelnt
	   opt-tw-gen32-dll-intelnt
	   opt-tw-gen32ut-dll-intelnt

	   ;; same in G2, OK to specify twice, may be overwritten:
	   opt-fonts)
  :print-name "Telewindows")
(def-component opt-telewindows2 :parts (opt-tw2 opt-tw2-intelnt opt-tw2-javadoc)
	       
	       ;; important: the extra space in the middle of the following
	       ;; string is a kludge to make a string compare fail in order to
	       ;; keep the shared env. var. dialog from appearing. We don't want
	       ;; that now that we've gotten rid of all the env. var.'s! Fix
	       ;; this right later!  Reference the code
	       ;;
	       ;;  #define TW2_NAME "Telewindows2 Toolkit"
	       ;;
	       ;; in bundle/ishield/Setup.rul. (MHD 12/11/01)
	       :print-name "Telewindows2 Toolkit")

(def-component opt-gateway :parts (opt-gsi) :print-name "G2 Gateway (GSI)")
(def-component opt-gda :parts (opt-gda) :print-name "G2 Diagnostic Assistant (GDA)")
(def-component opt-weblink :parts (opt-gw gsi-gw-ok opt-run-gw-template-batfile gsi-gw-blank-ok) :print-name "G2 WebLink")
(def-component opt-javalink
  :parts (opt-jvl opt-jvl-intelnt opt-jvl-com-gensym-properties-intelnt opt-jvl-javadoc)
  :print-name "G2 JavaLink")


(def-component opt-activexlink
  :parts (opt-axl-g2com-dll opt-axl-gsi-dll opt-axl-readme opt-axl-g2com-kb opt-axl-demos 
          opt-axl-runme-bat opt-axl-regsvr opt-axl-kbs-5)
  :platforms ("nt")
  :print-name "G2 ActiveXLink")

(def-component opt-gservice
  :parts (opt-gservice)
  :print-name "GService Startup Service"
  :platforms ("nt"))

(def-component opt-documentation
  :parts (opt-g2pdf opt-g2doc opt-g2utlpdf opt-g2utldoc opt-jvldoc opt-tw2doc opt-axldoc opt-corbalinkdoc
		 opt-g2classicrn
		   opt-g2oradoc opt-g2sybdoc opt-opclinkdoc opt-g2odbcdoc
		   opt-g2dbdoc opt-protoolsdoc opt-weblinkdoc opt-gdadoc)
  :print-name "G2 Documentation"
  :include-in-contents (opt-g2pdf)
  :typical false)			; consider making false, especially if an 
					;   HTML component gets split off


(def-component opt-g2-readme :parts (opt-g2-readme) :print-name "G2 Readme")

(def-component opt-protools :parts (opt-protools-5 opt-protools-6) :print-name "G2 ProTools")




;;; Optional Bridges in G2: Two bridges are standard (picked by the customer at
;;; order time), and others may be optionally chosen, i.e., at order time.
;;;
;;; Optional Bridges: (1) corbalink (2) opclink (3) Oraclebridge (4)
;;; Sybasebridge (5) ODBCbridge
;;;
;;; Note that there may be other components, e.g., Gateway (GW) and perhaps
;;; other components, that are technically bridges, but they're not necessarily
;;; marketed that way to customers.
;;;
;;; All of the optional bridges, those bridges marketed as such, are here,
;;; below, and bear the :optional=true flag.

(def-component opt-corbalink :parts (opt-corbalink)
	       :print-name "G2 CORBALink"
	       :non-platforms ("alphaosf")
	       :optional true)
(def-component opt-opclink 
             :parts (opt-opclink gsi-opclink-ok opt-run-G2Opc-template-batfile gsi-opclink-blank-ok)
             :platforms ("nt")
	       :print-name "G2 OPCLink Bridge"
	       :optional true)
(def-component opt-Oraclebridge
             :parts (opt-Oraclebridge gsi-Oracle-ok opt-run-g2-ora7-template-batfile 
                     opt-run-g2-ora80-template-batfile opt-run-g2-ora81-template-batfile 
                     opt-run-g2-ora9i-template-batfile gsi-Oracle-blank-ok)
	       :print-name "G2 Oracle Bridge"
	       :optional true)
(def-component opt-Sybasebridge
             :parts (opt-Sybasebridge gsi-Sybase-ok opt-run-g2-sybase-template-batfile gsi-Sybase-blank-ok)
	       :print-name "G2 Sybase Bridge"
	       :non-platforms ("linux")
	       :optional true)
(def-component opt-ODBCbridge 
             :parts (opt-ODBCbridge gsi-ODBC-ok opt-run-g2-odbc-template-batfile gsi-ODBC-blank-ok)
             :platforms ("nt")
	       :print-name "G2 ODBC Bridge"
	       :optional true)

;;;; Parts
(def-part opt-g2-exe-intelnt
    :version :62r2
    :print-name "G2 Windows Executable Optegrity"
    :source g2
    :source-filename "g2.exe"
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (opt-g2-shortcut))

(def-shortcut opt-g2-shortcut
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "G2"
    :application-directory "g2"
    :target-name "g2.exe"
    :parameters "-module-search-path kbs\\utils ..\\integrity-kbs ..\\optegrity-kbs ..\\protools\\kbs ..\\gw\\kbs ..\\javalink\\kbs ..\\tw2\\kbs ..\\gda ..\\activexlink -ok ..\\g2\\g2.ok")

;;;Redefining G2 Shortcut to allow for Integrity/Optegrity module search path and ok file
(def-shortcut g2-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "G2"
    :application-directory "g2"
    :target-name "g2.exe"
    :parameters "-module-search-path kbs\\utils ..\\integrity-kbs ..\\optegrity-kbs ..\\protools\\kbs ..\\gw\\kbs ..\\javalink\\kbs ..\\tw2\\kbs ..\\gda ..\\activexlink -ok ..\\g2\\g2.ok")

(def-part opt-g2-exe-unix
    :version :62r2
    :print-name "G2 Unix Executable"
    :source g2
    :source-filename "g2"
    :destination-directory "g2"
    :non-platforms ("nt"))


(def-part opt-g2passwd-exe-intelnt
    :version :62r2
    :print-name "G2PASSWD Windows Executable Optegrity"
    :source g2
    :source-filename "g2passwd.exe"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-g2passwd-exe-unix
    :version :62r2
    :print-name "G2PASSWD Unix Executable"
    :source g2
    :source-filename "g2passwd"
    :destination-directory "g2"
    :non-platforms ("nt"))

(def-part opt-g2-gen16ut-dll-intelnt
    :version :62r2
    :print-name "G2 Gen16UT DLL"
    :source g2
    :source-filename "gen16ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-g2-gen32-dll-intelnt
    :version :62r2
    :print-name "G2 Gen32 DLL"
    :source g2
    :source-filename "gen32.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-g2-gen32ut-dll-intelnt
    :version :62r2
    :print-name "G2 Gen32UT DLL"
    :source g2
    :source-filename "gen32ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-g2-map-intelnt
    :version :62r2
    :print-name "G2 Map"
    :source g2
    :source-filename "g2.map"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-g2-blank-ok
    :version :62r2
    :print-name "Sample G2 OK file"
    :source g2
    :source-filename "g2.ok"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-index-dic
    :version :62r2
    :print-name "Kanji index dictionary"
    :source g2
    :source-filename "index.dic"
    :destination-directory "g2")

(def-part opt-kojin-dic
    :version :62r2
    :print-name "Kanji kojin dictionary"
    :source g2
    :source-filename "kojin.dic"
    :destination-directory "g2")

(def-part opt-main-dic
    :version :62r2
    :print-name "Kanji main dictionary"
    :source g2
    :source-filename "main.dic"
    :destination-directory "g2")

(def-part opt-ext-directory
    :version :62r2
    :print-name "G2 EXT Directory"
    :source g2
    :source-subdirectory "ext"
    :destination-directory "g2/ext")



(def-part opt-tw-exe-intelnt
    :version :62r2
    :print-name "TW Windows Executable Optegrity"
    :source tw
    :source-filename "tw.exe"
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (opt-tw-shortcut))

(def-shortcut opt-tw-shortcut
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "Telewindows"
    :application-directory "g2"
    :target-name "tw.exe")

(def-part opt-tw-exe-unix
    :version :62r2
    :print-name "TW Unix Executable"
    :source tw
    :source-filename "tw"
    :destination-directory "g2"
    :non-platforms ("nt"))



(def-part opt-tw-nptwplug-dll-intelnt
    :version :62r2
;;;    :source-ship-type :internal
    :print-name "TW Extensions"
    :source tw
    :source-filename ("nptwplug.dll" "TwControl.ocx" "registerTwControl.bat")
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-tw-gen16ut-dll-intelnt
    :version :62r2
    :print-name "TW Gen16UT DLL"
    :source tw
    :source-filename "gen16ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-tw-gen32-dll-intelnt
    :version :62r2
    :print-name "TW Gen32 DLL"
    :source tw
    :source-filename "gen32.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-tw-gen32ut-dll-intelnt
    :version :62r2
    :print-name "TW Gen32UT DLL"
    :source tw
    :source-filename "gen32ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part opt-tw-map-intelnt
    :version :62r2
    :print-name "TW Map"
    :source tw
    :source-filename "tw.map"
    :destination-directory "g2"
    :platforms ("nt"))







(def-part opt-kbs
  :version :62r2
  :source kbs
  :destination-directory g2/kbs
  :indep t
  ;; KBs are read-only, which is not terribly bad by itself, but causes
  ;; a problem: doing uninstall on Windows.
  :make-not-read-only t)
(def-part opt-fonts
    :version :62r2
    :source fonts
    :destination-directory g2/fonts :indep t
    ;; fonts are read-only, which is not terribly bad by itself, but
    ;; causes these problems: using this part from both g2 and telewindow
    ;; components, and doing uninstall on Windows.
    :make-not-read-only t)
(def-part opt-tw2
    :version :12r4
    :source tw2
    :destination-directory tw2
    :non-platforms ("nt"		; has its own part
		     ))

(def-part opt-tw2-javadoc
    :version :12r4
    :source tw2-javadoc
    :destination-directory "doc/tw2/Java"
    :shortcuts (opt-tw2-javadoc)
    :indep t)

(def-shortcut opt-tw2-javadoc
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "API Documentation"
    :application-directory "doc\\tw2\\Java\\docs\\api"
    :target-name "index.html")

(def-part opt-tw2-intelnt
    :version :12r4
    :source tw2
    :source-subdirectory "components"
    ;; for building tree:  handled by bundle.lisp, not in family file. -mhd
    :remove-from-source ("bin/unInstall.bat" "bin/unInstaller.bat") ; remove component installer stuff
    :destination-directory tw2
    :platforms ("nt")
    :postinstall-code "replace_rootdir(\"tw2\"^\"bin\", \"envvars.bat\");"
    :shortcuts (opt-tw2-toolkit-demo
		 opt-tw2-demo
		 ;;		       tw2-component-editor
		 opt-tw2-readme
		 opt-tw2-itemaccessdemo
		 opt-tw2-internationalizationdemo
		 opt-tw2-palettedemo

		 ;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
		 ;; 		       ;; ActiveX:
		 ;; 		       tw2-activex-install-controls
		 ;; 		       tw2-activex-uninstall-controls
		 ;; 		       tw2-activex-mill-demo
		 ;; 		       tw2-activex-shell-demo
		 ))

(def-shortcut opt-tw2-toolkit-demo
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Default Application Shell"
    :application-directory "tw2\\bin"
    :target-name "shell.bat")

(def-shortcut opt-tw2-demo
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Demo"
    :application-directory "tw2\\bin"
    :target-name "t2demo.bat")

(def-shortcut opt-tw2-itemaccessdemo
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Item Access Demo"
    :application-directory "tw2\\classes\\com\\gensym\\demos\\itemaccessdemo"
    :target-name "rundemo.bat")

(def-shortcut opt-tw2-internationalizationdemo
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Internationalization Demo"
    :application-directory "tw2\\classes\\com\\gensym\\demos\\internationalizationdemo"
    :target-name "rundemo.bat")

(def-shortcut opt-tw2-palettedemo
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Palette Demo"
    :application-directory "tw2\\classes\\com\\gensym\\demos\\palettedemo"
    :target-name "rundemo.bat")

;; Removed from G2 Classic product:
;; (def-shortcut tw2-component-editor
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :application-display-name "Component Editor"
;;     :application-directory "tw2\\bin"
;;     :target-name "beaneditor.bat")

(def-shortcut opt-tw2-readme
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Readme for Telewindows2 Toolkit"
    :application-directory "tw2"
    :target-name "readme-tw2.html")


;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
;;
;; ;; TW2 Tooklit ActiveX Shortcuts:
;; 
;; (def-shortcut tw2-activex-install-controls
;;     :folder-name optegrity-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Install Controls"
;;     :application-directory "tw2\\bin"
;;     :target-name "InstallControls.bat")
;; 
;; (def-shortcut tw2-activex-uninstall-controls
;;     :folder-name optegrity-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Uninstall Controls"
;;     :application-directory "tw2\\bin"
;;     :target-name "unInstallControls.bat")
;; 
;; (def-shortcut tw2-activex-mill-demo
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Visual Basic Mill Demo"
;;     :application-directory "tw2\\ActiveX\\vbdemo"
;;     :target-name "VbDemo.bat")
;; 
;; (def-shortcut tw2-activex-shell-demo
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Visual Basic Telewindows2 Shell"
;;     :application-directory "tw2\\ActiveX\\vbShell"
;;     :target-name "Tw2Prj.exe")
;; 
;; (def-shortcut tw2-activex-help
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Telewindows2 Toolkit for ActiveX Reference Manual"
;;     :application-directory "tw2\\ActiveX"
;;     :target-name "AXClient.hlp")

;; Documentation Shortcuts
(def-shortcut opt-g2-release-notes
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "G2 Bundle Release Notes"
    :application-directory "doc"
    :target-name "g2relnotes.pdf")

(def-shortcut opt-g2-reference-manual
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Reference Manual"
    :application-directory "doc\\g2\\g2refman"
    :target-name "g2refman.pdf")

(def-shortcut opt-g2-reference-card
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Language Reference Card"
    :application-directory "doc\\g2\\g2langrefcard"
    :target-name "g2langrefcard.pdf")

(def-shortcut opt-g2-system-procedures-reference-manual
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 System Procedures Reference Manual"
    :application-directory "doc\\g2\\g2sysprocs"
    :target-name "g2sysprocs.pdf")

(def-shortcut opt-g2-tutorial
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Getting Started with G2 Tutorial"
    :application-directory "doc\\g2\\g2tutorials"
    :target-name "g2tutorials.pdf")

(def-shortcut opt-g2-class-reference-manual
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Class Reference Manual"
    :application-directory "doc\\g2\\g2classref"
    :target-name "g2classref.pdf")

;; not included in 5.2r0 bundle
(def-shortcut opt-g2-developers-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Developer's Guide"
    :application-directory "doc\\g2\\g2devguide"
    :target-name "g2devguide.pdf")

(def-shortcut opt-g2-dynamic-displays-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Dynamic Displays User's Guide"
    :application-directory "doc\\utilities\\gdd"
    :target-name "gdd.pdf")

(def-shortcut opt-g2-developers-interface-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Developer's Interface User's Guide"
    :application-directory "doc\\utilities\\gdi"
    :target-name "gdi.pdf")

(def-shortcut opt-g2-foundation-resources-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Foundation Resources User's Guide"
    :application-directory "doc\\utilities\\gfr"
    :target-name "gfr.pdf")

(def-shortcut opt-g2-menu-system-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Menu System User's Guide"
    :application-directory "doc\\utilities\\gms"
    :target-name "gms.pdf")

(def-shortcut opt-g2-online-documentation-developers-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation Developer's Guide"
    :application-directory "doc\\utilities\\golddev"
    :target-name "golddev.pdf")

(def-shortcut opt-g2-online-documentation-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation User's Guide"
    :application-directory "doc\\utilities\\goldui"
    :target-name "goldui.pdf")

(def-shortcut opt-g2-guide-uil-procedures-reference-manual
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE UIL Procedures Reference Manual"
    :application-directory "doc\\utilities\\guideprocref"
    :target-name "guideprocref.pdf")

(def-shortcut opt-g2-guide-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE User's Guide"
    :application-directory "doc\\utilities\\guideuserguide"
    :target-name "guideuserguide.pdf")

(def-shortcut opt-g2-xl-spreadsheet-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 XL Spreadsheet User's Guide"
    :application-directory "doc\\utilities\\gxl"
    :target-name "gxl.pdf")



;; GDA

(def-shortcut opt-gda-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA User's Guide"
    :application-directory "doc\\gda\\gdaugrm"
    :target-name "gdaug.pdf")

(def-shortcut opt-gda-reference-manual
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA Reference Manual"
    :application-directory "doc\\gda\\gdaugrm"
    :target-name "gdarefman.pdf")

(def-shortcut opt-gda-api-reference-manual
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA API Reference Manual"
    :application-directory "doc\\gda\\gdaapi"
    :target-name "gdaapi.pdf")


;; G2 ProTools

(def-shortcut opt-g2-protools-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 ProTools User's Guide"
    :application-directory "doc\\utilities\\g2protools"
    :target-name "g2protools.pdf")

;; G2 Gateway (GSI)

(def-shortcut opt-gsi-bridge-developers-guide
    ;; "Everyone knows this informally as 'the GSI manual'". --peter k.
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Gateway Bridge Developer's Guide"
    :application-directory "doc\\g2\\g2gateway"
    :target-name "g2gateway.pdf")

;; Bridges

(def-shortcut opt-g2-database-bridge-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 Database Bridge User's Guide"
    :application-directory "doc\\bridges\\db"
    :target-name "g2databasebridge.pdf")

(def-shortcut opt-g2-opclink-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 OPCLink User's Guide"
;;review for final!
;;    :application-directory "opclink"
;;    :target-name "G2-OPCLink-Client-for-Gensym-G2-Manual.pdf"
    :application-directory "doc\\bridges\\opclink"
    :target-name "g2opclink.pdf")


(def-shortcut opt-g2-corba-link-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 CORBALink User's Guide"
    :application-directory "doc\\bridges\\corbalink"
    :target-name "g2corbalink.pdf")

(def-shortcut opt-g2-odbc-bridge-release-notes
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-ODBC Bridge Release Notes"
    :application-directory "doc\\bridges\\odbc"
    :target-name "g2odbcbridge.pdf")

(def-shortcut opt-g2-oracle-bridge-release-notes
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Oracle Bridge Release Notes"
    :application-directory "doc\\bridges\\oracle"
    :target-name "g2oraclebridge.pdf")

(def-shortcut opt-g2-sybase-bridge-release-notes
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Sybase Bridge Release Notes"
    :application-directory "doc\\bridges\\sybase"
    :target-name "g2sybasebridge.pdf")


;; Telewindows

(def-shortcut opt-telewindows-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Telewindows User's Guide"
    :application-directory "doc\\g2\\telewindows"
    :target-name "telewindows.pdf")



;; Telewindows2 Toolkit
			   
(def-shortcut opt-tw2-release-notes
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Release Notes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\t2relnotes"
    :target-name "t2relnotes.pdf")

(def-shortcut opt-bean-exporter-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "BeanXporter User's Guide"
    :application-directory "doc\\tw2\\java\\docs\\guides\\beanxporter"
    :target-name "beanXporter.pdf")

(def-shortcut opt-tw2-components-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Components and Core Classes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\t2components"
    :target-name "t2components.pdf")

(def-shortcut opt-tw2-application-classes
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Application Classes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\t2javadevguide"
    :target-name "t2javadevguide.pdf")

(def-shortcut opt-tw2-demos-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Java Demos Guide"
    :application-directory "doc\\tw2\\java\\docs\\guides\\t2javademos"
    :target-name "t2javademos.pdf")



;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
;; (def-shortcut telewindows2-toolkit-activex-developers-guide
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Documentation"
;;     :subsubfolder-name "Telewindows2 Toolkit"
;;     :application-display-name "Telewindows2 Toolkit ActiveX Developer's Guide"
;;     :application-directory "doc\\tw2\\ActiveX\\docs\\guides\\ActiveXDevelopersGuide"
;;     :target-name "titlepag.htm")
			                 

;; Javalink

(def-shortcut opt-g2-download-interfaces-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 Download Interfaces User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2downloadinterfaces"
    :target-name "g2downloadinterfaces.pdf")

(def-shortcut opt-g2-beanbuilder-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 Bean Builder User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2beanbuilder"
    :target-name "g2beanbuilder.pdf")

(def-shortcut opt-g2-javalink-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 JavaLink User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2javalink"
    :target-name "g2javalink.pdf")




;; G2 ActiveXLink

(def-shortcut opt-g2-activexlink-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 ActiveXLink User's Guide"
    :application-directory "doc\\bridges\\activexlink"
    :target-name "g2activexlink.pdf")

;; G2 WebLink

(def-shortcut opt-g2-weblink-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 WebLink User's Guide"
    :application-directory "doc\\bridges\\weblink"
    :target-name "g2weblink.pdf")

(def-part opt-gsi
    :version :62r2
    :source gsi
    :destination-directory gsi)

(def-part opt-gservice
  :version :62r0
  :source gservice
  :source-filename "gservice.exe"
  :destination-directory g2
  :platforms ("nt"))

(def-part opt-gda
    :version :41r2
    :source gda
    :destination-directory gda
    :indep t)


(def-part opt-gw
  :version :10r4
  :source gw
  :destination-directory gw)

(def-part opt-run-gw-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-gw.bat"
    :destination-directory gw
    :postinstall-code "replace_rootdir(\"gw\", \"run-gw.bat\");"
    :shortcuts (opt-gw-shortcut))

(def-shortcut opt-gw-shortcut
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "G2 WebLink"
    :application-directory "gw"
    :target-name "run-gw.bat")



;;; The part jvl-com-gensym-properties-intelnt sets up a template
;;; .com.gensym.properties file in the classes, and also arranges through
;;; postinstall code to have that file overwritten with substitutions from the
;;; template file that normally lives in the bin directory.  Having the template
;;; file preexist just ensures that uninstalling will remove that file, so it
;;; can clean up everything.  (I had to copy the current 11r0
;;; .com.gensym.properties to
;;; /development/installers/release-files/.com.gensym.properties to make this
;;; work. --mhd, 12/11/00)

(def-part opt-jvl-com-gensym-properties-intelnt
    :destination-directory "javalink/classes"
    :source "/home/development/installers/release-files"
    :source-filename ".com.gensym.properties"
    :platforms ("nt")
    :postinstall-code
    "FixupPropertiesFile(TARGETDIR^\"javalink\"^\"bin\", \".com.gensym.properties\", TARGETDIR^\"javalink\", \"classes\", \".com.gensym.properties\");")

(def-part opt-jvl-intelnt
  :version :12r4
  :source jvl
  :destination-directory javalink
  :postinstall-code "replace_rootdir(\"javalink\"^\"bin\", \"envvars.bat\");"

  ;; the semantics of the special source directive is to only copy those files
  :platforms ("nt") :source-subdirectory "components"
  :shortcuts (opt-jvl-interface-downloader
	      opt-jvl-install-properties
	      opt-jvl-bean-builder
	      opt-jvl-example-readme
	      opt-jvl-known-problems
	      opt-jvl-readme))

(def-shortcut opt-jvl-interface-downloader
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Download Interfaces"
    :application-directory "javalink\\bin"
    :target-name "Downloadinterfaces.bat")

;; Note: Downloadinterfaces can be considered the main application for the
;; Javalink component.

(def-shortcut opt-jvl-bean-builder
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "G2 Bean Builder"
    :application-directory "javalink\\bin"
    :target-name "G2BeanBuilder.bat")

(def-shortcut opt-jvl-install-properties
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Install Properties"
    :application-directory "javalink\\bin"
    :target-name "InstallProperties.bat")

(def-shortcut opt-jvl-example-readme
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Examples Readme"
    :application-directory "javalink"
    :target-name "ExamplesReadme.html")

(def-shortcut opt-jvl-known-problems
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Known Problems"
    :application-directory "javalink"
    :target-name "KnownProblems.html")

(def-shortcut opt-jvl-readme
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Readme for G2 JavaLink"
    :application-directory "javalink"
    :target-name "readme-javalink.html")




(def-part opt-jvl
  :version :12r4
  :source jvl
  :destination-directory javalink
  :non-platforms ("nt"			; has its own part
		  ))

(def-part opt-jvl-javadoc
    :version :12r4
    :source jvl-javadoc
    :destination-directory doc/javalink
    :shortcuts (opt-jvl-javadoc)
    :indep t)

(def-shortcut opt-jvl-javadoc
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "API Documentation"
    :application-directory "doc\\javalink\\docs\\api"
    :target-name "index.html")

; should this be in a bridges directory?  Or should all the bridges be in the G2 directory?
(def-part opt-corbalink
  :version :10r1-dd19
  :source corbalink
  :destination-directory corbalink
  :non-platforms ("alphaosf"))



;; ActiveXLink Parts:

(def-part opt-axl-g2com-dll
    :version :10r4
    :source axl
    :source-filename "G2Com.dll"
    :register true			; Active X Control
    :destination-directory activexlink
    :platforms ("nt"))

(def-part opt-axl-gsi-dll
    :version :10r4
    :source axl
    :source-filename "gsi.dll"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part opt-axl-readme
    :version :10r4
    :source axl
    :source-filename "ReadMe.htm"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part opt-axl-g2com-kb
    :version :10r4
    :source axl
    :source-filename "g2com.kb"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part opt-axl-demos
    :version :10r4
    :source axl
    :source-subdirectory "demos"
    :destination-directory activexlink/demos
    :platforms ("nt"))

(def-part opt-axl-runme-bat
    :version :10r4
    :source axl
    :source-filename "runme.bat"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part opt-axl-regsvr
    :version :10r4
    :source axl
    :source-filename "regsvr32.exe"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part opt-axl-kbs-5
    :version :10r4
    :source axl
    :source-subdirectory "kbs-5"
    :destination-directory activexlink/kbs-5
    :platforms ("nt"))

;; Doc is now its own part, axldoc, and goes with doc/bridges, q.v., below.


;; utilities

(def-part opt-g2utlpdf
    :version :61r0
    :source g2utlpdf
    :destination-directory doc/utilities
    :indep t)

(def-part opt-g2utldoc
  :version :61r0
  :source g2utldoc
  :destination-directory doc/utilities
  :indep t)

(def-part opt-protoolsdoc
  :version :61r0
  :source protoolsdoc
  :destination-directory doc/utilities
  :indep t)

(def-part opt-gdadoc
  :version :41r1
  :source gdadoc
  :destination-directory doc
  :indep t)

(def-part opt-weblinkdoc
  :version :10r3
  :source weblinkdoc
  :destination-directory doc/bridges
  :indep t)

(def-part opt-g2classicrn
    :version :62r2
    :source g2classicrn
    :source-filename "g2relnotes.pdf"
    :indep t
    :destination-directory doc)

;; reference manual
(def-part opt-g2pdf
    :version :61r0
    :source g2pdf
    :destination-directory doc/g2
    :indep t
    ;; Off of this part hang all the doc shortcuts.  Some of them could hang off
    ;; of their real parts, but (a) it's a lot more work; (b) some of them use
    ;; doc in parts that are not of the DOC component.  I don't want to hang off
    ;; of those parts because then you could get doc shortcuts without being
    ;; authorized for the doc component, which seems strange.  (Of course, it's
    ;; strange to give the doc in the first place, but that's another story.)
    ;; (MHD 12/8/00)
    :shortcuts (
		;; Note: there seem to be bugs in InstallShield and/or
		;; InstallGenerator and/or the commented out shortcuts here.  For
		;; now, leave them uncommented; this set was carefully determined by
		;; expirimentation to work, whereas with some or all of the commented
		;; out shortcuts, there was failure: "unknown error". (MHD 12/11/00)
		opt-g2-release-notes
		opt-g2-reference-manual
		 opt-g2-reference-card
		 ;;g2-release-notes-update;;not included in 6.0b1
		 opt-g2-system-procedures-reference-manual
		 opt-g2-tutorial
		 opt-g2-class-reference-manual
		 opt-g2-developers-guide	    ;;not included in 6.0b1
		 ;; G2 Utilities
		 opt-g2-dynamic-displays-users-guide	    
		 opt-g2-developers-interface-users-guide
		 opt-g2-foundation-resources-users-guide	    
		 opt-g2-menu-system-users-guide
		 opt-g2-online-documentation-developers-guide
		 opt-g2-online-documentation-users-guide
		 opt-g2-guide-uil-procedures-reference-manual
		 opt-g2-guide-users-guide	    
		 opt-g2-xl-spreadsheet-users-guide
		 ;; GDA:
		 opt-gda-users-guide
		 opt-gda-reference-manual
		 opt-gda-api-reference-manual
		 ;; Protools
		 opt-g2-protools-users-guide
		 ;; GSI
		 opt-gsi-bridge-developers-guide
		 ;; Bridges:
		 opt-g2-database-bridge-guide
		 opt-g2-opclink-users-guide
		 opt-g2-corba-link-users-guide	   
		 opt-g2-odbc-bridge-release-notes
		 opt-g2-oracle-bridge-release-notes	    
		 opt-g2-sybase-bridge-release-notes
		 ;; TW
		 opt-telewindows-users-guide

		 ;; TW2

		 ;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
		 ;;	    tw2-activex-help		; NOTE: Shortcut in TW2/ActiveX Folder

		 opt-tw2-release-notes
		 opt-bean-exporter-guide
		 opt-tw2-components-guide
		 opt-tw2-demos-guide
		 opt-tw2-application-classes

		 ;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
		 ;; 	    telewindows2-toolkit-activex-developers-guide

		 ;; Javalink
		 opt-g2-download-interfaces-guide
		 opt-g2-beanbuilder-guide
		 opt-g2-javalink-guide
		 ;; ActiveXLink
		 opt-g2-activexlink-users-guide
		 ;; Weblink
		 opt-g2-weblink-users-guide
		 ))
(def-part opt-g2doc
  :version :61r0
  :source g2doc
  :destination-directory doc/g2
  :indep t)


;; Documentation for bridges - Javalink, ActiveXLink, TW2, Corbalink, Oracle, Sybase, OPCLink, ODBC:

(def-part opt-jvldoc
    :version :12r2
    :source jvldoc
    :destination-directory doc/javalink
    :indep t)

(def-part opt-axldoc
    :version :10r2
    :source axldoc
    :source-subdirectory "docs"
    :destination-directory doc/bridges
    :platforms ("nt")
    :indep t)

(def-part opt-tw2doc
    :version :12r2
    :source tw2doc
    :destination-directory doc/tw2
    :indep t)

(def-part opt-corbalinkdoc :version :10r2 :source corbalinkdoc :destination-directory doc/bridges :indep t)
(def-part opt-g2oradoc :version :60r6 :source g2oradoc :destination-directory doc/bridges :indep t)
(def-part opt-g2sybdoc :version :60r6 :source g2sybdoc :destination-directory doc/bridges :indep t)
(def-part opt-opclinkdoc :version :20r0 :source opclinkdoc :destination-directory doc/bridges :indep t) ; check for 5.2r0 final!
(def-part opt-g2odbcdoc :version :60r6 :source g2odbcdoc :destination-directory doc/bridges :indep t)
(def-part opt-g2dbdoc
    :version :60r6			; see note at shortcut for g2-database-bridge-guide
    :source g2dbdoc
    :destination-directory doc/bridges
    :indep t)

(def-part opt-protools-5
    :version :51r9
    :source protools
    :destination-directory protools/kbs-5
    :indep t)
(def-part opt-protools-6
    :version :62r0
    :source protools
    :destination-directory protools/kbs
    :source-filename ("protools.kb" "ptroot.kb")
    :indep t)

(def-part opt-profiler
    :version :62r0
;;;    :source-ship-type :internal
    :source protools
    :source-filename ("profiler.kb" "profroot.kb")
    :destination-directory g2/kbs/utils
    :indep t)

(def-gsi-bridge-ok-parts (:obfuscate t)
    opt-gw opt-opclink opt-odbc opt-oracle opt-sybase)


(def-part opt-g2-readme
    :source g2pkgreadme
    :version :62r2
    :source-filename "readme-g2.html"
    :indep t 
    :shortcuts (opt-g2-readme))

(def-shortcut opt-g2-readme
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "Readme for G2 Bundle"
    :application-directory ""
    :target-name "readme-g2.html")


(def-part opt-opclink
    :version :20r0			; includes their new doc; review after beta!! (MHD 4/24/01)
    :source opclink
    :destination-directory opclink)

(def-part opt-run-G2Opc-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-G2Opc.bat"
    :destination-directory opclink
    :postinstall-code "replace_rootdir(\"opclink\", \"run-G2Opc.bat\");"
    :shortcuts (opt-opclink-shortcut))

(def-shortcut opt-opclink-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 OPCLink Bridge"
    :application-directory "opclink"
    :target-name "run-G2Opc.bat")


(def-part opt-Sybasebridge
    :version :60r8
    :source g2sybase
    :destination-directory sybase
    :non-platforms ("linux")) ; "linux" does not exist for sybase

(def-part opt-run-g2-sybase-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-sybase.bat"
    :destination-directory sybase
    :postinstall-code "replace_rootdir(\"sybase\", \"run-g2-sybase.bat\");"
    :shortcuts (opt-sybase-shortcut))

(def-shortcut opt-sybase-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Sybase Bridge"
    :application-directory "sybase"
    :target-name "run-g2-sybase.bat")



(def-part opt-ODBCbridge
    :version :60r8
    :source g2odbc
    :destination-directory odbc
    :platforms ("nt"))

(def-part opt-run-g2-odbc-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-odbc.bat"
    :destination-directory odbc
    :postinstall-code "replace_rootdir(\"odbc\", \"run-g2-odbc.bat\");"
    :shortcuts (opt-odbc-shortcut))

(def-shortcut opt-odbc-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 ODBC Bridge"
    :application-directory "odbc"
    :target-name "run-g2-odbc.bat")


(def-part opt-Oraclebridge
    :version :60r8
    :source g2oracle
    :destination-directory oracle)

(def-part opt-run-g2-ora7-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora7.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora7.bat\");"
    :shortcuts (opt-ora7-shortcut))

(def-part opt-run-g2-ora80-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora80.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora80.bat\");"
    :shortcuts (opt-ora80-shortcut))

(def-part opt-run-g2-ora81-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora81.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora81.bat\");"
    :shortcuts (opt-ora81-shortcut))

(def-part opt-run-g2-ora9i-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora9i.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora9i.bat\");"
    :shortcuts (opt-ora9i-shortcut))

(def-shortcut opt-ora7-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Oracle 7 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora7.bat")

(def-shortcut opt-ora80-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Oracle 8.0 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora80.bat")

(def-shortcut opt-ora81-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Oracle 8.1 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora81.bat")

(def-shortcut opt-ora9i-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Oracle 9i Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora9i.bat")

(def-component opt-jre
  :print-name "Java Runtime Environment"
  :parts (opt-jre)
  :platforms ("ny"))

(def-part opt-jre
  :version :13r1_01
  :source "jre"
  :platforms ("nt")
  :destination-directory "jre")




