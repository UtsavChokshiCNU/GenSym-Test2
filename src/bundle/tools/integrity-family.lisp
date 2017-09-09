;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; INTEGRITY-FAMILY - Integrity Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduj and wmorris

;;; normally we refer to versions as something like :32r0, which the code
;;; automatically figures out what to do for pretty name etc.  However, with
;;; the version numbers that have a suffix, the code is stupid about case,
;;; and ends up lower casing it all.  So you have to define a version if you
;;; have an uppercase suffix.
;;;
;;; +++
;;; Change this when a new build is promoted to the e-ship directory.  This should be 
;;; changed according to the promote.
(def-part-version :33r0-B01B15 :major 3 :minor 3 :revision 0 :suffix "-B01B15" :letter "r")

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
(def-g2-ok-components integrity-core-development integrity "Integrity Core Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))

(def-g2-ok-components integrity-discovery-development integrity "Integrity Discovery Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))

(def-g2-ok-components integrity-premium-development integrity "Integrity Premium Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))

(def-g2-ok-components integrity-reasoner-development integrity "Integrity Reasoner Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))

(def-g2-ok-components integrity-core-deployment integrity "Integrity Core Deployment"
		      (4 8 16 20 24 28 32))

(def-g2-ok-components integrity-discovery-deployment integrity "Integrity Discovery Deployment"
		      (4 8 16 20 24 28 32))

(def-g2-ok-components integrity-premium-deployment integrity "Integrity Premium Deployment"
		      (4 8 16 20 24 28 32))

(def-g2-ok-components integrity-reasoner-deployment integrity "Integrity Reasoner Deployment"
		      (4 8 16 20 24 28 32))

;;;the following list of components is in every bundle, so abstract it out here
;;;
;;;  This defines the components that are common to every Integrity bundle.  There is no
;;;  need to change this unless we add another component to the common list.  If addition
;;;  is required, then make sure the addition is within the parenthesis.
(defvar integrity-common
  '(integrity-client integrity-G2 ping-manager remote-OS-agent
    java-SNMP G2-snmp-hpov-bridge G2-SNMP-netview integrity-readme integrity-documentation
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
(def-family integrity
    :index 4
    :file-syntax-version 10
    :print-name "Integrity"
    :bundles (integrity-core-development
	       integrity-discovery-development
	       integrity-premium-development
	       integrity-reasoner-development
	       integrity-core-deployment
	       integrity-discovery-deployment
	       integrity-premium-deployment
	       integrity-reasoner-deployment)
    :directory "integrity"
    :guid "243D4BB3-9EE7-11D4-8111-00A02431D004"
    :splash-screen "need a splash screen")

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
;;;  The core development components include:
;;;     integrity-common         defined above
;;;     integrity-core-kbs       mainly core-services and OPAC KB modules
;;;     core development oks      ok files for development
(def-bundle integrity-core-development
    :version :33r0
    :components (integrity-common integrity-core-kbs
		  integrity-core-development-family-ok-components
		  ))

;;;  The discovery components include:
;;;     integrity-common           defined above
;;;     integrity-discovery-kbs    core KBs plus discovery KB modules
;;;     integrity-discovery        NetSleuth and ODG java class files
;;;     discovery development oks  ok files for development
(def-bundle integrity-discovery-development
    :version :33r0
    :components (integrity-common integrity-discovery-kbs integrity-discovery
		  integrity-discovery-development-family-ok-components
		  ))

;;;  The premium components include:
;;;     integrity-common           defined above
;;;     integrity-premium-kbs      core, discovery, and reasoner KB modules
;;;     integrity-discovery        NetSleuth and ODG java class files
;;;     premium development oks    ok files for development
(def-bundle integrity-premium-development
    :version :33r0
    :components (integrity-common integrity-premium-kbs integrity-discovery
		  integrity-premium-development-family-ok-components))

;;;   The reasoner components include:
;;;     integrity-common          defined above
;;;     integrity-resoner-kbs     core and reasoner KB modules
;;;     reasoner development oks  ok files for development
(def-bundle integrity-reasoner-development
    :version :33r0
    :components (integrity-common integrity-reasoner-kbs
		  integrity-reasoner-development-family-ok-components))

;;;   The deployment bundles include the exact same files as their development counterparts
;;;   with the exception of the ok files.  They are for deployment vs. development.
(def-bundle integrity-core-deployment
    :version :33r0
    :components (integrity-common integrity-core-kbs
		  integrity-core-deployment-family-ok-components))

(def-bundle integrity-discovery-deployment
    :version :33r0
    :components (integrity-common integrity-discovery-kbs integrity-discovery
		  integrity-discovery-deployment-family-ok-components))

(def-bundle integrity-premium-deployment
    :version :33r0
    :components (integrity-common integrity-premium-kbs integrity-discovery
		  integrity-premium-deployment-family-ok-components))

(def-bundle integrity-reasoner-deployment
    :version :33r0
    :components (integrity-common integrity-reasoner-kbs
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
  :parts (integrity-client-intelnt ));integrity-client-sparcsol

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
    :version :33r0-B01B15
    :source opex-client
    ;; this contains a self extracting installer.  This is no doubt wrong.
    ;; finishing later.
    :platforms ("nt")
    :environment-variables (integrity_home)
    :destination-directory client
    :source-ship-type :internal
    :shortcuts (integrity-client))

(def-part integrity-client-sparcsol)


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
    :version :33r0-B01B15
    :destination-directory doc
    :indep t)

;;;  Ping manager component
(def-component ping-manager
  :print-name "Ping Manager"
  :parts (ping-manager))

;;;  +++
;;;  Ping manager part.
(def-part ping-manager
    :source pingmgr
    :version :33r0-B01B15
    :platforms ("nt" "sparcsol" "hp") 
    :destination-directory bin)

;;;  Socket Manager component
(def-component socket-manager
    :print-name "Socket Manager"
    :parts (socket-manager))

;;;  +++
;;;  Socket Manager part
(def-part socket-manager
    :source sockman
    :version :33r0-B01B15
    :platforms ("nt")
    :destination-directory sockman)

;;;  Discovery component (NetSleuth and ODG java class files)
(def-component integrity-discovery
    :print-name "Auto Discovery"
    :parts (integrity-discovery))

;;;  +++
;;;  Discvoery part
(def-part integrity-discovery
    :source integad
    :version :33r0-B01B15
    :platforms ("nt")
    :destination-directory discovery
    :shortcuts (ad-dhns-startup ad-server-startup ad-client-startup))

(def-shortcut ad-dhns-startup
    :folder-name "Integrity"
    :application-display-name "AutoDiscovery DHNS Startup"
    :application-directory "discovery\\bin"
    :target-name "startup_dhns.bat")

(def-shortcut ad-server-startup
    :folder-name "Integrity"
    :application-display-name "AutoDiscovery Server Startup"
    :application-directory "discovery\\bin"
    :target-name "startup_server.bat")

(def-shortcut ad-client-startup
    :folder-name "Integrity"
    :application-display-name "AutoDiscovery Client Startup"
    :application-directory "discovery\\bin"
    :target-name "startup_client.bat")

;;;  Remote OS Agent component
(def-component remote-OS-agent
  :print-name "Remote OS Agent"
  :parts (remote-OS-agent))

;;;  +++
;;;  Remote OS Agent part
(def-part remote-OS-agent
  :source rosa
  :version :33r0-B01B15
  :source-ship-type :internal
  :destination-directory remote-os
  :platforms ("nt" "sparcsol"))

;;;  Core KB modules component
(def-component integrity-core-kbs
  :print-name "Integrity KBs"
  :parts (integrity-core-kbs))

;;;  +++
;;;  Core KB modules part
(def-part integrity-core-kbs
    :source intecore
    :version :33r0-B01B15
    :destination-directory "core-kbs"
    :indep t)

;;;  Discovery KB modules component
(def-component integrity-discovery-kbs
  :print-name "Integrity KBs"
  :parts (integrity-discovery-kbs))

;;;  +++
;;;  Discovery KB modules part
(def-part integrity-discovery-kbs
    :source intedisc
    :version :33r0-B01B15
    :destination-directory "discovery-kbs"
    :indep t)

;;;  Premium KB modules component
(def-component integrity-premium-kbs
  :print-name "Integrity KBs"
  :parts (integrity-premium-kbs))

;;;  +++
;;;  Premium KB modules part
(def-part integrity-premium-kbs
    :source inteprem
    :version :33r0-B01B15
    :destination-directory "premium-kbs"
    :indep t)

;;;  Reasoner KB modules component
(def-component integrity-reasoner-kbs
  :print-name "Integrity KBs"
  :parts (integrity-reasoner-kbs))

;;;  +++
;;;  Reasoner KB modules part
(def-part integrity-reasoner-kbs
    :source intereas
    :version :33r0-B01B15
    :destination-directory "reasoner-kbs"
    :indep t) 

;;;  HPOV SNMP Bridge component.  Note if the print-name must contain spaces,
;;;  double-quotes must be used.
(def-component G2-snmp-hpov-bridge
  :print-name "G2 SNMP HPOV Bridge"
  :platforms ("sparcsol" "hp")
  :parts (G2-snmp-hpov-bridge))

;;;  +++
;;;  HPOV SNMP Bridge part
(def-part G2-snmp-hpov-bridge
    :version :33r0-B01B15
    :platforms ("hp" "sparcsol")
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
    :version :33r0-B01B15
    :destination-directory jsnmp
    :shortcuts (java-SNMP-receiver java-SNMP-requests))

;;;  Shortcut definitions for the Generic Java SNMP bridge (NT only)
(def-shortcut java-SNMP-receiver
    :folder-name "Integrity"
    :application-display-name "SNMP Trap Receiver"
    :application-directory "jsnmp\\bin"
    :target-name "jsnmp.bat -listenerport 22041")

(def-shortcut java-SNMP-requests
    :folder-name "Integrity"
    :application-display-name "SNMP Set Requests"
    :application-directory "jsnmp\\bin"
    :target-name "jsnmp.bat -listenerport 22044")

;;;  NetView SNMP Bridge component
(def-component G2-SNMP-netview
  :platforms ("aix")
  :parts (G2-SNMP-netview))

;;;  +++
;;;  NetView SNMP Bridge part
(def-part G2-SNMP-netview
    :platforms ("aix")
    :source g2snmpnv
    :version :33r0-B01B15
    :destination-directory g2snmpnv)

;;;  Integrity Readme component
(def-component integrity-readme
  :print-name "Integrity Readme"
  :parts (integrity-readme))

;;;  +++
;;;  Integrity Readme part.  Note the source is a directory listing and a new attribute:
;;;    source-filename          defines the name of the file to pick up from the source.
(def-part integrity-readme
    :indep t
    :source "/home/development/installers/release-files"
    :source-filename "g2-package-readme.txt"  ;;change this!
    :destination-filename "readme.txt")
