;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; INTEGRITY-FAMILY - Integrity Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduj and wmorris
(require "g2-52r1-family")			; G2 6.0r0
;;; Use this for 3.4r0 version of Integrity (require "g2-family")			; G2 5.1r7
(provide "integrity-35r0-family")

;;; normally we refer to versions as something like :32r0, which the code
;;; automatically figures out what to do for pretty name etc.  However, with
;;; the version numbers that have a suffix, the code is stupid about case,
;;; and ends up lower casing it all.  So you have to define a version if you
;;; have an uppercase suffix.
;;;
;;; +++
;;; Change this when a new build is promoted to the e-ship directory.  This should be 
;;; changed according to the promote.
(def-part-version :35r0-B01J02 :major 3 :minor 5 :revision 0 :suffix "-B01J02" :letter "r")
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
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))

(def-g2-ok-components (integrity-reasoner-deployment :obfuscate t) integrity "Integrity Reasoner Deployment"
		      (4 8 16 20 24 28 32))

;;; Optegrity bundle
(def-g2-ok-components (optegrity-reasoner-development :obfuscate t) optegrity "Optegrity Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))

(def-g2-ok-components (optegrity-reasoner-deployment :obfuscate t) optegrity "Optegrity Deployment"
		      (4 8 16 20 24 28 32))


;;;the following list of components is in every bundle, so abstract it out here
;;;
;;;  This defines the components that are common to every Integrity bundle.  There is no
;;;  need to change this unless we add another component to the common list.  If addition
;;;  is required, then make sure the addition is within the parenthesis.
(defvar integrity-common
  '(integrity-client integrity-G2 ping-manager remote-OS-agent
    java-SNMP G2-snmp-hpov-bridge G2-SNMP-netview integrity-documentation
    socket-manager))

(defvar optegrity-common
  '(optegrity-client integrity-g2 remote-OS-agent optegrity-documentation
    socket-manager))


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
(def-family integrity-35r0
    :index 4
    :file-syntax-version 10
    :print-name "Integrity"
    :bundles (integrity-reasoner-development
	       integrity-reasoner-deployment
             optegrity-reasoner-development
	       optegrity-reasoner-deployment)
    :directory "integrity"
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
    :version :35r0
    :components (integrity-common integrity-reasoner-kbs
		  integrity-reasoner-development-family-ok-components))

;;;   The deployment bundles include the exact same files as their development counterparts
;;;   with the exception of the ok files.  They are for deployment vs. development.
(def-bundle integrity-reasoner-deployment
    :version :35r0
    :components (integrity-common integrity-reasoner-kbs
		  integrity-reasoner-deployment-family-ok-components))

;;; *******************************************************************************
;;; Optegrity bundle definition
;;;
(def-bundle optegrity-reasoner-development
    :version :35r0
    :components (optegrity-common optegrity-reasoner-kbs
		  integrity-reasoner-development-family-ok-components))

;;;   The deployment bundles include the exact same files as their development counterparts
;;;   with the exception of the ok files.  They are for deployment vs. development.
(def-bundle optegrity-reasoner-deployment
    :version :35r0
    :components (optegrity-common optegrity-reasoner-kbs
		  integrity-reasoner-deployment-family-ok-components))


;;; components and their parts below
;;;
;;;  Components will never change unless there is an addition to the component
;;;  being defined.  If a new part is to be added, it must appear within the
;;;  parenthesis of the parts attribute.  The structure for the component is
;;;  as follows:
;;;    print-name               the name to be displayed during installation
;;;    parts                    a list of parts that make up the component
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
    :version :35r0-B01J02
    :source opex-client
    ;; this contains a self extracting installer.  This is no doubt wrong.
    ;; finishing later.
    :platforms ("nt")
    :environment-variables (integrity_home)
    :destination-directory client
    :source-ship-type :internal
    :shortcuts (integrity-client)
    :postinstall-code "integrityPostInstall(\"Integrity\");")

(def-part integrity-client-sparcsol
    :version :35r0-B01J02
    :source opex-client
    :platforms ("sparcsol")
    :destination-directory client
    :source-ship-type :internal)


;;; the default value of an environment variable is the directory name of its
;;; associated part, as concatenated with the user install directory
(def-environment-variable integrity_home)

;;; This defines a shortcut for NT only platforms.  The structure of the definition
;;; is as follows:
;;;   folder-name              name of the folder to create under Programs
;;;   application-display-name name to display as the shortcut
;;;   application-directory    directory where the initiating file can be found
;;;   target-name              name of the file that initiates the application
(def-shortcut integrity-client
    :folder-name "Integrity"
    :application-display-name "Integrity Client"
    :application-directory "client\\bin"
    :target-name "integrity.bat")

;;;  G2 component
(def-component integrity-G2
  :print-name "G2"
  :parts (integrity-g2-exe-intelnt g2-exe-unix g2-map-intelnt
			 g2passwd-exe-intelnt g2passwd-exe-unix
			 index-dic kojin-dic main-dic ext-directory
			 g2-blank-ok))

(def-part integrity-g2-exe-intelnt
    :parent g2-exe-intelnt
    :shortcuts :delete
    :environment-variables :delete)


;;;  Documentation component
(def-component integrity-documentation
    :print-name "Integrity Documentation"
    :parts (integrity-doc))

;;;  +++
;;;  A new attribute of the part structure is:
;;;    indep             this indicates that it is an independent part.  Independent
;;;                      with respect to the operating system.  Possible values are
;;;                      t for TRUE or f for FALSE.
(def-part integrity-doc
    :source opexdoc
    :version :35r0-B01J02
    :destination-directory doc
    :indep t
    :shortcuts (int-users-guide int-ref-man int-util-guide int-sockman-guide
                int-snmp-users-guide int-jsnmp-users-guide int-rel-notes
                int-demo-guide))

(def-shortcut int-users-guide
    :folder-name "Integrity\\Documentation"
    :application-display-name "Integrity User's Guide"
    :application-directory "doc"
    :target-name "IntUsersGuide.pdf")

(def-shortcut int-ref-man
    :folder-name "Integrity\\Documentation"
    :application-display-name "Integrity Reference Manual"
    :application-directory "doc"
    :target-name "IntRefManual.pdf")

(def-shortcut int-util-guide
    :folder-name "Integrity\\Documentation"
    :application-display-name "Integrity Utilities Guide"
    :application-directory "doc"
    :target-name "IntUtilGuide.pdf")

(def-shortcut int-sockman-guide
    :folder-name "Integrity\\Documentation"
    :application-display-name "Integrity Socket Manager User's Guide"
    :application-directory "doc"
    :target-name "IntJSockManGuide.pdf")

(def-shortcut int-snmp-users-guide
    :folder-name "Integrity\\Documentation"
    :application-display-name "Integrity G2-SNMP User's Guide"
    :application-directory "doc"
    :target-name "IntSNMPUsersGuide.pdf")

(def-shortcut int-jsnmp-users-guide
    :folder-name "Integrity\\Documentation"
    :application-display-name "Integrity Java G2-SNMP User's Guide"
    :application-directory "doc"
    :target-name "IntJSNMPUsersGuide.pdf")

(def-shortcut int-rel-notes
    :folder-name "Integrity\\Documentation"
    :application-display-name "Integrity 3.5r0 Release Notes"
    :application-directory "doc"
    :target-name "IntRelNotes.pdf")

(def-shortcut int-demo-guide
    :folder-name "Integrity\\Documentation"
    :application-display-name "Integrity Demo Guide"
    :application-directory "doc"
    :target-name "IntDemoGuide.pdf")


;;;  Ping manager component
(def-component ping-manager
  :print-name "Ping Manager"
  :parts (ping-manager))

;;;  +++
;;;  Ping manager part.
(def-part ping-manager
    :source pingmgr
    :version :35r0-B01J02
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
    :version :35r0-B01J02
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
  :version :35r0-B01J02
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
    :version :35r0-B01J02
    :destination-directory "integrity-kbs"
    :shortcuts (reasoner-shortcut reasoner-sym-dev-guide reasoner-sym-modeling-guide)
    :indep t) 

(def-shortcut reasoner-shortcut
    :folder-name "Integrity"
    :application-display-name "Integrity"
    :application-directory "integrity-kbs"
    :target-name "reasoner.bat")

(def-shortcut reasoner-sym-dev-guide
    :folder-name "Integrity\\Documentation"
    :application-display-name "SymCure Developers Guide"
    :application-directory "doc"
    :target-name "IntSymDevGuide.pdf")

(def-shortcut reasoner-sym-modeling-guide
    :folder-name "Integrity\\Documentation"
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
    :version :35r0-B01J02
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
    :version :35r0-B01J02
    :destination-directory jsnmp
    :shortcuts (java-SNMP-receiver java-SNMP-requests))

;;;  Shortcut definitions for the Generic Java SNMP bridge (NT only)
(def-shortcut java-SNMP-receiver
    :folder-name "Integrity"
    :application-display-name "SNMP Trap Receiver"
    :application-directory "jsnmp\\bin"
    :target-name "receiver.bat")

(def-shortcut java-SNMP-requests
    :folder-name "Integrity"
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
    :version :35r0-B01J02
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
    :source-filename "integrity-readme.txt"  ;;change this!
    :destination-filename "readme.txt")

|#

;;; **********************************************************************************
;;; Optegrity components
;;;
(def-component optegrity-client
  :print-name "Optegrity Client"
  :parts (optegrity-client-intelnt optegrity-client-sparcsol));optegrity-client-sparcsol

(def-part optegrity-client-intelnt
    :version :35r0-B01J02
    :source opteg-client
    :platforms ("nt")
    :environment-variables (optegrity_home)
    :destination-directory optclient
    :source-ship-type :internal
    :shortcuts (optegrity-client)
    :postinstall-code "integrityPostInstall(\"Optegrity\");")


(def-part optegrity-client-sparcsol
    :version :35r0-B01J02
    :source opteg-client
    :platforms ("sparcsol")
    :destination-directory optclient
    :source-ship-type :internal)

(def-environment-variable optegrity_home)

(def-shortcut optegrity-client
    :folder-name "Optegrity"
    :application-display-name "Optegrity Client"
    :application-directory "optclient\\bin"
    :target-name "optegrity.bat")

(def-component optegrity-documentation
    :print-name "Optegrity Documentation"
    :parts (optegrity-doc))


(def-part optegrity-doc
    :source optegdoc
    :version :35r0-B01J02
    :destination-directory optdoc
    :indep t
    :shortcuts (opt-users-guide opt-ref-man opt-util-guide opt-sockman-guide
                opt-sym-dev-guide opt-sym-modeling-guide opt-rel-notes
                opt-demo-guide))

(def-shortcut opt-users-guide
    :folder-name "Optegrity\\Documentation"
    :application-display-name "Optegrity User's Guide"
    :application-directory "optdoc"
    :target-name "OptUsersGuide.pdf")

(def-shortcut opt-ref-man
    :folder-name "Optegrity\\Documentation"
    :application-display-name "Optegrity Reference Manual"
    :application-directory "optdoc"
    :target-name "OptRefManual.pdf")

(def-shortcut opt-util-guide
    :folder-name "Optegrity\\Documentation"
    :application-display-name "Optegrity Utilities Guide"
    :application-directory "optdoc"
    :target-name "IntUtilGuide.pdf")

(def-shortcut opt-sockman-guide
    :folder-name "Optegrity\\Documentation"
    :application-display-name "Optegrity Socket Manager User's Guide"
    :application-directory "optdoc"
    :target-name "IntJSockManGuide.pdf")

(def-shortcut opt-sym-dev-guide
    :folder-name "Optegrity\\Documentation"
    :application-display-name "Optegrity SymCure Developers Guide"
    :application-directory "optdoc"
    :target-name "OptSymDevGuide.pdf")

(def-shortcut opt-sym-modeling-guide
    :folder-name "Optegrity\\Documentation"
    :application-display-name "Optegrity SymCure Modeling Guide"
    :application-directory "optdoc"
    :target-name "OptSymModelingGuide.pdf")

(def-shortcut opt-rel-notes
    :folder-name "Optegrity\\Documentation"
    :application-display-name "Optegrity 3.5r0 Release Notes"
    :application-directory "optdoc"
    :target-name "OptRelNotes.pdf")

(def-shortcut opt-demo-guide
    :folder-name "Optegrity\\Documentation"
    :application-display-name "Optegrity Demo Guide"
    :application-directory "optdoc"
    :target-name "IntDemoGuide.pdf")


(def-component optegrity-reasoner-kbs
  :print-name "Optegrity KBs"
  :parts (optegrity-reasoner-kbs))

(def-part optegrity-reasoner-kbs
    :source optegrity
    :version :35r0-B01J02
    :destination-directory "optegrity-kbs"
    :shortcuts (optegrity-shortcut)
    :indep t) 

(def-shortcut optegrity-shortcut
    :folder-name "Optegrity"
    :application-display-name "Optegrity"
    :application-directory "optegrity-kbs"
    :target-name "optegrity.bat")

