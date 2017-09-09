;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; INTEGRITY-FAMILY - Integrity Family Definitions.  Requires bundle.lisp and g2-family.lisp
;;
;; When a new bundle is to be made and after the promotes have been done, perform a global replace
;;   on the version and build number.  For the def-part definitions a :version specifies the version
;;   in which to look for in the promoted directories.  This is a combination of the version and
;;   build number.  The build number is the suffix appended to the promoted product and 
;;   version number.  For example, the promote of component INTREAS for version 4.0r0 and build
;;   number B03F16 will appear in the promoted directory as intereas-40b0-B03F16.  The def-part
;;   :version is specified as :version :40b0-B03F16.  This must be updated to indicate the current
;;   version and current build in order to pull the correct files for the bundle.
;; You can also do a global replace for the version number (i.e. "4.0r0").  This replace is for the
;;   shortcuts defined.
;; To find other items that needs to be updated will be marked with a ";; MODIFY" comment.  So, you can
;;   search for ";; MODIFY" and see what else has to be changed within this file.
;;

;; MODIFY
;; Renaming the shortcut defined in the G2 bundle.  This should show the version number
;;   of this bundle.
(defvar g2-shortcut-folder-name "Gensym Integrity 5.0a0")
;; MODIFY
;; Setting the shortcut for the Integrity bundle
(defvar integrity-shortcut-folder-name "Gensym Integrity 5.0a0")
;; MODIFY
;; Defining the module search path for Integrity.  This needs to be modified if the support
;;   KBs path changes.
(defvar integrity-search-path-and-ok-file "-module-search-path ..\\g2i\\kbs kbs\\utils ..\\integrity\\kbs ..\\integrity\\demos ..\\odbc ..\\opclink\\kbs ..\\protools\\kbs ..\\gw ..\\corbalink\\kbs ..\\javalink\\kbs ..\\tw2\\kbs ..\\gda ..\\activexlink ..\\oracle ..\\sybase -ok ..\\g2\\g2.ok")

;; MODIFY
;; Indicating that G2 will be a required bundle for Integrity.  This indicates which version of G2
;;   will be included in the Integrity bundle.
(require "g2-83a1-family")
;;(require "g2-70r1-family")              ; G2 7.0r1
;;(require "tw2-12r6-family")             ; G2 7.0r1
;;(require "g2-62r2-family")			; G2 6.2r2
;;(require "g2-62r0-family")			; G2 6.2r0
;;(require "g2-52r1-family")			; G2 6.0r1
;;; Use this for 3.4r0 version of Integrity (require "g2-family")			; G2 5.1r7

;; MODIFY
;; The name of the Integrity bundle so other bundles can include in their family files.
(provide "integrity-50a0-family")

;;; normally we refer to versions as something like :32r0, which the code
;;; automatically figures out what to do for pretty name etc.  However, with
;;; the version numbers that have a suffix, the code is stupid about case,
;;; and ends up lower casing it all.  So you have to define a version if you
;;; have an uppercase suffix.
;;;
;;; +++
;; MODIFY
;;; Change this when a new build is promoted to the e-ship directory.  This should be 
;;; changed according to the promote.
;;; To keep a history of the build numbers, I have been copying the def-part-version and
;;;   then pasting and modifying the new copy.  I don't know if we need to do this, but...
;;;(def-part-version :40r0-B03F16 :major 4 :minor 0 :revision 0 :suffix "-B03F16" :letter "r")
;;;(def-part-version :36r1-B02L16 :major 3 :minor 6 :revision 1 :suffix "-B02L16" :letter "r")
;;;(def-part-version :36r0-B02G10 :major 3 :minor 6 :revision 0 :suffix "-B02G10" :letter "r")
;;;(def-part-version :35r1-B02B20 :major 3 :minor 5 :revision 1 :suffix "-B02B20" :letter "r")
;;;(def-part-version :35r0-B01J02 :major 3 :minor 5 :revision 0 :suffix "-B01J02" :letter "r")
;;;(def-part-version :34r0-B01F22 :major 3 :minor 4 :revision 0 :suffix "-B01F22" :letter "r")
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
;;
;; MODIFY
;; The numbers in the parenthesis pertain to the number of users is authorized.  No
;;   need to change this.  There is one definition for each bundle.
;;
;; This needs to be updated only when new temporary codes are generated.  Be sure to update
;;   both Development and Deployment definitions.
(def-g2-ok-components (integrity-reasoner-development :obfuscate t) integrity "Integrity Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
			(1 "-apr25-2007") (1 "-nov25-2006") (1 "-dec25-2006")
			(1 "-jan25-2007") (1 "-feb25-2007") (1 "-mar25-2007")
))

(def-g2-ok-components (integrity-reasoner-deployment :obfuscate t) integrity "Integrity Deployment"
		      (4 8 16 20 24 28 32
			(1 "-apr25-2007") (1 "-nov25-2006") (1 "-dec25-2006")
			(1 "-jan25-2007") (1 "-feb25-2007") (1 "-mar25-2007")
))


;;the following list of components is in every bundle, so abstract it out here
;;
;;  This defines the components that are common to every Integrity bundle.  There is no
;;    need to change this unless we add another component to the common list.  If addition
;;    is required, then make sure the addition is within the parenthesis.
(defvar integrity-common
  '(javalink ping-manager remote-OS-agent
    integrity-jsnmp-bridge G2-snmp-hpov-bridge G2-SNMP-netview integrity-documentation
    mib-parser integrity-g2i-modules
    doc-pdf doc-html doc-chm
    protools activexlink weblink telewindows2-jars
    telewindows g2 gateway g2-readme gda jre cdg-import-export 
    integrity-readme gservice ))

(defvar int-g2-bridges-common
  '(corbalink opclink pibridge Oraclebridge Sybasebridge ODBCbridge))

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
;; MODIFY
;;  If a new GUID is created (indication of a new key for installation), then change the :guid to
;;    the new GUID that was generated.
(def-family integrity-50a0
    :index 76
    :file-syntax-version 10
    :print-name "Integrity"
    :bundles (integrity-reasoner-development
	       integrity-reasoner-deployment)
    :directory "integrity-5.0a0"
    :guid "90f277fc-b87b-44a6-aacd-24a6e4404d15"
;;
;; Previous GUID's:
;;    Integrity/Optegrity 3.3r0 - 3.6r1 ==> :guid "243D4BB3-9EE7-11D4-8111-00A02431D004"
;;    Integrity 4.0r0 -->    :guid "6EFADBB0-1B39-437e-BD35-6E52C3D3F79C"
;;
    :splash-screen "integrity-setup.bmp")

;;; There are now only two bundles that makde up the Integrity family: Development and Deployment.
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
    :version :40r0
    :print-name "Integrity Development"
    :components (integrity-common integrity-reasoner-kbs int-g2-bridges-common
              socket-manager jmail-component jms-component
		  integrity-reasoner-development-family-ok-components))

;;;   The deployment bundles include the exact same files as their development counterparts
;;;   with the exception of the ok files.  They are for deployment vs. development.
(def-bundle integrity-reasoner-deployment
    :version :40r0
    :print-name "Integrity Deployment"
    :components (integrity-common integrity-reasoner-kbs int-g2-bridges-common
              socket-manager jmail-component jms-component
		  integrity-reasoner-deployment-family-ok-components))


;;===========================================

;;; components and their parts below
;;;
;;;  Components will never change unless there is an addition to the component
;;;  being defined.  If a new part is to be added, it must appear within the
;;;  parenthesis of the parts attribute.  The structure for the component is
;;;  as follows:
;;;    print-name               the name to be displayed during installation
;;;    parts                    a list of parts that make up the component
;;;**********************************************************************************************
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
;;; the default value of an environment variable is the directory name of its
;;; associated part, as concatenated with the user install directory
;;; 3/4/02 WSM  removed ->(def-environment-variable integrity_home)

;;; This defines a shortcut for NT only platforms.  The structure of the definition
;;; is as follows:
;;;   folder-name              name of the folder to create under Programs
;;;   application-display-name name to display as the shortcut
;;;   application-directory    directory where the initiating file can be found
;;;   target-name              name of the file that initiates the application

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
    :version :40r0-FJ14
    :destination-directory "doc/integrity"
    :indep t
    :shortcuts (int-users-guide int-ref-man int-util-guide 
                int-snmp-users-guide int-jsnmp-users-guide int-dxi3db-primer
                int-demo-guide ))

(def-shortcut int-users-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Integrity"
    :application-display-name "Integrity User's Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityUsersGuide.pdf")

(def-shortcut int-ref-man
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Integrity"
    :application-display-name "Integrity Reference Manual"
    :application-directory "doc/integrity"
    :target-name "IntegrityReferenceManual.pdf")

(def-shortcut int-util-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Integrity"
    :application-display-name "Integrity Utilities Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityUtilitiesGuide.pdf")

(def-shortcut int-snmp-users-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Integrity"
    :application-display-name "Integrity G2-SNMP User's Guide"
    :application-directory "doc/integrity"
    :target-name "G2-SNMPBridges.pdf")

(def-shortcut int-jsnmp-users-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Integrity"
    :application-display-name "Integrity Java G2-SNMP User's Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityJavaSNMP.pdf")

(def-shortcut int-rel-notes
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Integrity"
    :application-display-name "Integrity 5.0a0 Release Notes"
    :application-directory "doc/integrity"
    :target-name "IntRelNotes.pdf")

(def-shortcut int-demo-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Integrity"
    :application-display-name "Integrity Demo Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityDemoGuide.pdf")

(def-shortcut int-dxi3db-primer
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Integrity"
    :application-display-name "Integrity DXI3DB Primer"
    :application-directory "doc/integrity"
    :target-name "DXI3DB-Primer.pdf")


;;;  Ping manager component
(def-component ping-manager
  :print-name "Ping Manager"
  :parts (ping-manager))

;;;  +++
;;;  Ping manager part.
(def-part ping-manager
    :source pingmgr
    :version :40r0-B03F16
    :platforms ("nt" "sparcsol" "hpux") 
    :destination-directory "integrity/bin")

;;;===================================
;;; Added for current Optegrity users (3.6r1 and before)
;;; to allow them to export and import their SymCure
;;; models.
(def-component cdg-import-export
  :print-name "Import/Export Utilities for SymCure Upgrade"
  :parts (cdg-import-export-kbs cdg-readme))

(def-part cdg-import-export-kbs
  :source intereas
  :source-subdirectory "kbs"
  :version :40r0-B03I24
  :indep t
  :source-filename ("cdg-import.kb" "cdg-export.kb")
  :destination-directory "integrity/kbs")

(def-part cdg-readme
  :source optegdoc
  :version :40r0
  :source-filename ("readme-symcure.html" "cdgimportutility3.gif" "cdgimportutility42.gif" "readme-symcure3.gif")
  :destination-directory "g2i"
  :indep t
  :shortcuts (cdg-readme))

(def-shortcut cdg-readme
  :folder-name integrity-shortcut-folder-name
  :application-display-name "Readme for SymCure"
  :application-directory "g2i"
  :target-name "readme-symcure.html")


;; G2i Modules (new for Integrity 5.0a0)
(def-component integrity-g2i-modules
  :print-name "Integrity G2i Modules"
  :parts (integrity-g2i-modules))
(def-part integrity-g2i-modules
  :source g2i
  :version :23a1-IK07
  :source-ship-type :internal
  :indep t
  :source-subdirectory kbs
  :source-filename ("gvad.kb" "gtad.kb" "gndo.kb" "gtrap.kb" "gmib.kb" "gerr.kb" "grtl.kb"  "symcure.kb" "cdg.kb" "cdggrlb.kb" "gens.kb" "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "grlb.kb" "resources-english.txt" "config.txt")
  :postinstall-code "replace_rootdir(\"g2i\"^\"kbs\", \"config.txt\");"
  :destination-directory "g2i/kbs")

;;; MIB Parser (new for Integrity 5.0a0)
(def-component mib-parser
  :print-name "MIB Parser"
  :parts (integrity-mib-parser))
(def-part integrity-mib-parser
  :source g2mibparser
  :version :40r0-IK07
  :source-ship-type :internal
  :platforms ("nt" "sparcsol")
  :destination-directory g2mibparser)




;;;  Remote OS Agent component
(def-component remote-OS-agent
  :print-name "Remote OS Agent"
  :parts (remote-OS-agent))

;;;  +++
;;;  Remote OS Agent part
(def-part remote-OS-agent
  :source rosa
  :version :40r0-B03F16
  :destination-directory remote-os
  :platforms ("nt" "sparcsol"))

;;;  Reasoner KB modules component
(def-component integrity-reasoner-kbs
  :print-name "Integrity KBs"
  :parts (integrity-reasoner-kbs integrity-examples))

;;;  +++
;;;  Reasoner KB modules part
(def-part integrity-reasoner-kbs
    :source intereas
    :source-subdirectory kbs
    :version :50a0
    :source-ship-type :internal
    :destination-directory "integrity/kbs"
;;;    :postinstall-code "replace_rootdir(\"integrity\"^\"bin\", \"StartServer.bat\");"
    :shortcuts (integrity-shortcut reasoner-sym-users-guide)
    :indep t) 

(def-shortcut integrity-shortcut
    :folder-name integrity-shortcut-folder-name
    :application-display-name "Start Integrity"
    :application-directory "g2"
    :parameters "-kb ..\\integrity\\kbs\\integrity-dev.kb -nowindow"
    :icon-file "Integrity.ico"
    :icon-index 0
    :target-name "StartServer.bat")

(def-shortcut reasoner-sym-users-guide
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Integrity"
    :application-display-name "SymCure Users Guide"
    :application-directory "doc/integrity"
    :target-name "SymCureUsersGuide.pdf")

;;;  Reasoner Examples KB modules part
(def-part integrity-examples
    :source intereas
    :source-subdirectory examples
    :version :50a0
    :source-ship-type :internal
    :destination-directory "integrity/examples"
    :shortcuts (
;;; not yet converted                doc-demo-shortcut 
                mpe-demo-shortcut 
                opac-demo-shortcut 
                opx-demo-shortcut
;;; need to modify for gsnmp-demo                oxsj-demo-shortcut 
;;; included in G2                sockman-demo-shortcut 
                svcm-demo-shortcut )
    :indep t) 

(def-shortcut doc-demo-shortcut
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Integrity"
    :application-display-name "Doc Tutorial"
    :application-directory "g2"    
    :parameters "-kb ..\\integrity\\examples\\doc_demo.kb -nowindow"
    :target-name "StartServer.bat"
)

(def-shortcut mpe-demo-shortcut
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Integrity"
    :application-display-name "Message Parsing Engine Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\integrity\\examples\\mpe-demo.kb -nowindow"
)

(def-shortcut opac-demo-shortcut
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Integrity"
    :application-display-name "OPerator ACtions Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\integrity\\examples\\opacdemo.kb -nowindow"
)

(def-shortcut opx-demo-shortcut
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Integrity"
    :application-display-name "Integrity Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\integrity\\examples\\opx_demo.kb -nowindow"
)

(def-shortcut oxsj-demo-shortcut
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Integrity"
    :application-display-name "SNMP Java Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\integrity\\examples\\gsnmp-demo.kb -nowindow"
)

(def-shortcut sockman-demo-shortcut
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Integrity"
    :application-display-name "Socket Manager Tutorial"
    :application-directory "integrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\demos\\sockdemo.kb")

(def-shortcut svcm-demo-shortcut
    :folder-name integrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Integrity"
    :application-display-name "SymCure Service Level Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\integrity\\examples\\svcmdemo.kb -nowindow"
)



;;;  HPOV SNMP Bridge component.  Note if the print-name must contain spaces,
;;;  double-quotes must be used.
(def-component G2-snmp-hpov-bridge
  :print-name "G2 SNMP HPOV Bridge"
  :platforms ("sparcsol" "hpux")
  :parts (G2-snmp-hpov-bridge))

;;;  +++
;;;  HPOV SNMP Bridge part
(def-part G2-snmp-hpov-bridge
    :version :40r0-B03F16
    :platforms ("hpux" "sparcsol")
    :source g2snmpov
    :destination-directory g2snmpov)

;;;  Generic Java SNMP Bridge component
(def-component integrity-jsnmp-bridge
  :print-name "Java Generic SNMP Bridge"
  :platforms ("nt" "sparcsol")
  :parts (jsnmp-intel jsnmp-unix jre-most basic-jvl-parts))

;;;  +++
;;;  Generic Java SNMP Bridge part
(def-part java-SNMP
    :source g2snmpgn
    :version :40r0-IK07
    :destination-directory jsnmp
    :postinstall-code "replace_rootdir(\"jsnmp\"^\"bin\", \"StartJsnmpBridge.bat\");"
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
    :version :40r0-B03F16
    :destination-directory g2snmpnv)

(def-component integrity-readme :parts (integrity-readme) :print-name "Integrity Readme")

(def-part integrity-readme
    :source opexdoc
    :version :40r0-FJ14
    :source-filename "readme-integrity.html"
    :indep t 
    :shortcuts (integrity-readme))

(def-shortcut integrity-readme
    :folder-name integrity-shortcut-folder-name
    :application-display-name "Readme for Integrity Bundle"
    :application-directory ""
    :target-name "readme-integrity.html")


