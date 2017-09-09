;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; OPTEGRITY-FAMILY - Optegrity Family Definitions.  Requires bundle.lisp and g2-family.lisp
;;
;; When a new bundle is to be made and after the promotes have been done, perform a global replace
;;   on the version and build number.  For the def-part definitions a :version specifies the version
;;   in which to look for in the promoted directories.  This is a combination of the version and
;;   build number.  The build number is the suffix appended to the promoted product and 
;;   version number.  For example, the promote of component INTREAS for version 3.7r0 and build
;;   number B03E12 will appear in the promoted directory as intereas-37r0-B03E12.  The def-part
;;   :version is specified as :version :37r0-B03E12.  This must be updated to indicate the current
;;   version and current build in order to pull the correct files for the bundle.
;; You can also do a global replace for the version number (i.e. "3.7r0").  This replace is for the
;;   shortcuts defined.
;; To find other items that needs to be updated will be marked with a ";; MODIFY" comment.  So, you can
;;   search for ";; MODIFY" and see what else has to be changed within this file.
;;

;; MODIFY
;; Renaming the shortcut defined in the G2 bundle.  This should show the version number
;;   of this bundle.
(defvar g2-shortcut-folder-name "Gensym Optegrity 4.2r1")
;; MODIFY
;; Setting the shortcut for the Optegrity bundle
(defvar optegrity-shortcut-folder-name "Gensym Optegrity 4.2r1")
;; MODIFY
;; Defining the module search path for Optegrity.  This needs to be modified if the support
;;   KBs path changes.
(defvar optegrity-search-path-and-ok-file "-module-search-path ..\\g2i\\kbs kbs\\utils ..\\optegrity\\kbs ..\\optegrity\\demos ..\\pi ..\\odbc ..\\opclink\\kbs ..\\protools\\kbs ..\\gw ..\\corbalink\\kbs ..\\javalink\\kbs ..\\gda ..\\activexlink ..\\oracle ..\\sybase ..\\sockman\\kbs -ok ..\\g2\\g2.ok")

;; MODIFY
;; Indicating that G2 will be a required bundle for Optegrity.  This indicates which version of G2
;;   will be included in the Optegrity bundle.
(require "g2-71r3-family")                ; Optegrity 4.2r1
;;(require "g2-71r2-family")              ; Optegrity 4.2r0
;;(require "g2-71r0-family")              ; Optegrity 4.1r0
;;(require "g2-70r1-family")              ; Optegrity 4.0r0
;;(require "g2-62r2-family")			; G2 6.2r2

;; MODIFY
;; The name of the Optegrity bundle so other bundles can include in their family files.
(provide "optegrity-42r1-family")

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
;;;(def-part-version :42r0 :major 4 :minor 2 :revision 0 :suffix "-B04G02" :letter "r")
;;;(def-part-version :42b0 :major 4 :minor 2 :revision 0 :suffix "-B04F09" :letter "b")
;;;(def-part-version :40b0-B03H05 :major 4 :minor 0 :revision 0 :suffix "-B03H05" :letter "b")
;;;(def-part-version :36r1-B02L16 :major 3 :minor 6 :revision 1 :suffix "-B02L16" :letter "r")

;;;; ok file definitions
;; the following forms create variables containing parts and components for all
;; of the ok files, which variables will be referenced in the bundle's
;; components. You would append -family-ok-components to the defining name to
;; get the variable name, e.g., optegrity-core-development turns into
;; optegrity-core-development-family-ok-components when referenced.
;;
;; MODIFY
;; The numbers in the parenthesis pertain to the number of users is authorized.  No
;;   need to change this.  There is one definition for each bundle.
;;
;; This needs to be updated only when new temporary codes are generated.  Be sure to update
;;   both Development and Deployment definitions.
(def-g2-ok-components (optegrity-reasoner-development :obfuscate t) optegrity "Optegrity Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
			(1 "-jan25-2005") (1 "-feb25-2005")
			(1 "-mar25-2005") (1 "-apr25-2005") (1 "-may25-2005")
			(1 "-jun25-2005") (1 "-jul25-2005") (1 "-dec25-2004")
))

(def-g2-ok-components (optegrity-reasoner-deployment :obfuscate t) optegrity "Optegrity Deployment"
		      (4 8 16 20 24 28 32
			(1 "-jan25-2005") (1 "-feb25-2005")
			(1 "-mar25-2005") (1 "-apr25-2005") (1 "-may25-2005")
			(1 "-jun25-2005") (1 "-jul25-2005") (1 "-dec25-2004")
))


;;the following list of components is in every bundle, so abstract it out here
;;
;;  This defines the components that are common to every Optegrity bundle.  There is no
;;    need to change this unless we add another component to the common list.  If addition
;;    is required, then make sure the addition is within the parenthesis.
(defvar optegrity-common
  '(javalink optegrity-documentation optegrity-win-documentation optegrity-release-notes-component 
    g2i-core-modules doc-pdf doc-html doc-chm protools activexlink weblink telewindows g2 gateway 
    g2-readme gda jre cdg-import-export optegrity-readme gservice io-modules gda-43r2-component))

(defvar opt-g2-bridges-common
  '(corbalink opclink pibridge Oraclebridge Sybasebridge ODBCbridge))

;;; finally, time to define the family file!
;;;
;;;  The break down is family, bundle, component, and finally part.  Here there is only one
;;;  family, Optegrity.  No changes should be made here unless another bundle is to be added
;;;  to the Optegrity family.
;;;
;;;  Below is a description of the structure for the family definiation:
;;;    index                   never change this, Optegrity is setup for index of 23
;;;    file-syntax-version     this is used by the parser of this file, do not change
;;;    print-name              the name to be displayed
;;;    bundles                 defines the bundles that make up the family
;;;    directory               the directory where the files will be placed once installed
;;;    guid                    a unique identifier, do not change
;;;    splash-screen           defines the splash screen file name
;; MODIFY
;;  If a new GUID is created (indication of a new key for installation), then change the :guid to
;;    the new GUID that was generated.
(def-family optegrity-42r1
    :index 46
    :file-syntax-version 10
    :print-name "Optegrity"
    :bundles (optegrity-development optegrity-deployment)
    :directory "optegrity-4.2r1"
    :guid "7a027366-779b-4ed2-8bc5-8b50fa67087a"
    :compatible-previous-versions (("40a0" "88fb5875-5df5-449c-87de-0cbd5263552f")
                                   ("42r0" "c9065ef2-5691-444d-b740-ae3bb4e39561"))

;;;
;; Optegrity 4.2a0    :guid "88fb5875-5df5-449c-87de-0cbd5263552f"
;;
;; Previous GUID's:
;;    Integrity/Optegrity 3.3r0 - 3.6r1 ==> :guid "243D4BB3-9EE7-11D4-8111-00A02431D004"
;;
    :splash-screen "optegrity-setup.bmp")

;;;
;;;  Notice that each bundle definition contains the optegrity-common component.  The 
;;;  optegrity-common was defined above; however, each of the parts in the optegrity-common
;;;  component must be defined.
;;;
;;;  The structure of the bundle definition are:
;;;     version                  the version in which this represents
;;;     components               the components that make up this bundle.
;;;
;;;   The reasoner components include:
;;;     optegrity-common          defined above
;;;     optegrity-kbs             core and reasoner KB modules
;;;     reasoner development oks  ok files for development
(def-bundle optegrity-development
    :version :42r1
    :print-name "Optegrity Development"
    :components (optegrity-common optegrity-kbs opt-g2-bridges-common socket-manager jmail-component jms-component
		  optegrity-reasoner-development-family-ok-components))

;;;   The deployment bundles include the exact same files as their development counterparts
;;;   with the exception of the ok files.  They are for deployment vs. development.
(def-bundle optegrity-deployment
    :version :42r1
    :print-name "Optegrity Deployment"
    :components (optegrity-common optegrity-kbs opt-g2-bridges-common jmail-component jms-component
		  optegrity-reasoner-deployment-family-ok-components))


;;===========================================
;; Redefining G2's shortcut to get the module search path correct
(def-shortcut g2-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "G2"
    :application-directory "g2"
    :target-name "g2.exe"
    :parameters "-module-search-path ..\\g2i\\kbs kbs\\utils ..\\optegrity\\kbs ..\\optegrity\\demos ..\\pi ..\\odbc ..\\opclink\\kbs ..\\protools\\kbs ..\\gw ..\\corbalink\\kbs ..\\javalink\\kbs ..\\gda ..\\activexlink ..\\oracle ..\\sybase ..\\sockman\\kbs -ok ..\\g2\\g2.ok")



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
;;;  A new attribute of the part structure is:
;;;    indep             this indicates that it is an independent part.  Independent
;;;                      with respect to the operating system.  Possible values are
;;;                      t for TRUE or f for FALSE.


;;; This defines a shortcut for NT only platforms.  The structure of the definition
;;; is as follows:
;;;   folder-name              name of the folder to create under Programs
;;;   application-display-name name to display as the shortcut
;;;   application-directory    directory where the initiating file can be found
;;;   target-name              name of the file that initiates the application

;;;  Documentation component
(def-component optegrity-win-documentation
    :print-name "Optegrity WinHelp"
    :parts (optegrity-win-doc))

(def-part optegrity-win-doc
    :source optwinhelp
    :version :42r1
;;;    :source-ship-type :internal
    :destination-directory "doc/optegrity/WinHelp"
    :indep t
    :shortcuts (opt-win-doc))

(def-shortcut opt-win-doc
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "Optegrity Help"
    :application-directory "doc/optegrity/WinHelp"
    :target-name "Master.chm")

(def-component optegrity-release-notes-component
    :print-name "Optegrity Release Notes"
    :parts (optegrity-release-notes))

(def-part optegrity-release-notes
    :source optegdoc
    :version :42r1
;;;    :source-ship-type :internal
    :source-filename ("OptegrityReleaseNotes.pdf")
    :destination-directory "doc"
    :indep t
    :shortcuts (opt-rel-notes))

(def-shortcut opt-rel-notes
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Optegrity Release Notes"
    :application-directory "doc"
    :target-name "OptegrityReleaseNotes.pdf")

(def-component optegrity-documentation
    :print-name "Optegrity Documentation"
    :parts (optegrity-doc))


;;;  +++
(def-part optegrity-doc
    :source optegdoc
    :version :42r1
;;;    :source-ship-type :internal
    :source-filename ("GEDPUsersGuide.pdf" "OptegrityUsersGuide.pdf" "OptegrityFurnaceTutorial.pdf" "SymCureUsersGuide.pdf" "IntelligentObjectsUsersGuide.pdf")
    :destination-directory "doc/optegrity"
    :indep t
    :shortcuts (opt-users-guide 
;;; leaving opt-rel-notes out of the Alpha release.
;;;                opt-rel-notes
                opt-demo-guide gedp-users-guide opt-io-users-guide ))

(def-shortcut opt-io-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "Intelligent Objects User's Guide"
    :application-directory "doc/optegrity"
    :target-name "IntelligentObjectsUsersGuide.pdf")

(def-shortcut gedp-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "GEDP User's Guide"
    :application-directory "doc/optegrity"
    :target-name "GEDPUsersGuide.pdf")

(def-shortcut opt-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "Optegrity User's Guide"
    :application-directory "doc/optegrity"
    :target-name "OptegrityUsersGuide.pdf")

(def-shortcut opt-ref-man
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "Optegrity Reference Manual"
    :application-directory "doc/optegrity"
    :target-name "OptRefManual.pdf")

(def-shortcut opt-util-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "Optegrity Utilities Guide"
    :application-directory "doc/optegrity"
    :target-name "OptUtilGuide.pdf")

(def-shortcut opt-demo-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "Optegrity Furnace Tutorial"
    :application-directory "doc/optegrity"
    :target-name "OptegrityFurnaceTutorial.pdf")


;;;===================================
;;; Added for current Optegrity users (3.6r1 and before)
;;; to allow them to export and import their SymCure
;;; models.
(def-component cdg-import-export
  :print-name "Import/Export Utilities for SymCure Upgrade"
  :parts (cdg-import-export-kbs cdg-readme )
  :include-in-contents (cdg-readme))

(def-part cdg-import-export-kbs
  :source intereas
  :source-subdirectory "kbs"
  :version :40b0-B03F16
  :indep t
  :source-filename ("cdg-import.kb" "cdg-export.kb")
  :destination-directory "optegrity/kbs")

(def-part cdg-readme
  :source optegdoc
  :version :42r1
;;;  :source-ship-type :internal
  :source-filename ("readme-symcure.html" "cdgimportutility3.gif" "cdgimportutility42.gif" "readme-symcure3.gif")
  :destination-directory "g2i"
  :indep t
  :shortcuts (cdg-readme))

(def-shortcut cdg-readme
  :folder-name optegrity-shortcut-folder-name
  :application-display-name "Readme for SymCure"
  :application-directory "g2i"
  :target-name "readme-symcure.html")

;;;
;;;======= Begin G2i Modules =======
;;;
(def-component g2i-core-modules
  :print-name "G2i Modules"
  :parts (g2i-core-modules g2i-examples g2i-datafiles))

(def-part g2i-core-modules
  :source g2i
  :version :12r2
;;;  :source-ship-type :internal
  :indep t
  :source-subdirectory kbs
  :source-filename ("gens.kb" "gerr.kb" "grtl.kb"  "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "gqsdemo.kb" "resources-english.txt" "config.txt" "gevm.kb" "geuc.kb")
  :destination-directory "g2i/kbs"
  :postinstall-code "replace_rootdir(\"g2i\"^\"kbs\", \"config.txt\");"
)

(def-part g2i-examples
  :source g2i
  :version :12r2
;;;  :source-ship-type :internal
  :indep t
  :source-subdirectory examples
  :source-filename ("gedp-demo.kb" "gdpm-demo.kb" "cdg-modguide.kb")
  :destination-directory "g2i/examples"
  :shortcuts (gedp-demo-shortcut gdpm-demo-shortcut ) )

(def-part g2i-datafiles
  :source g2i
  :version :12r2
;;;  :source-ship-type :internal
  :indep t
  :source-subdirectory data
  :source-filename ("custom-conversions.csv" "custom-synonyms.csv")
  :destination-directory "g2i/data")

(def-shortcut geuc-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2i"
    :application-display-name "Engineering Unit Conversion Example"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\g2i\\examples\\geuc-demo.kb")

(def-shortcut gedp-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2i"
    :application-display-name "GEDP Example"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\g2i\\examples\\gedp-demo.kb")

(def-shortcut gdpm-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2i"
    :application-display-name "GDPM Example"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\g2i\\examples\\gdpm-demo.kb")

;;;
;;;======= End G2i Modules =======
;;;
;;;
;;;======= Begin Intelligent Object Modules =======
;;;
(def-component io-modules
  :print-name "Intelligent Objects"
  :parts (opt-io-modules opt-io-data opt-io-examples opt-io-resources opt-f101-examples)
  :optional true
  :include-in-contents (opt-io-modules))

(def-part opt-io-modules
  :source optegrity
  :version :42r1
;;;  :source-ship-type :internal
  :indep t
  :source-subdirectory kbs
  :source-filename ("iato.kb" "icco.kb" "ico.kb"  "icso.kb" "idco.kb" "iedo.kb" "iffo.kb" "iho.kb" "ioc.kb" "ipo.kb" "irco.kb" "iso.kb" "ito.kb" "ivo.kb" "ixo.kb" "sdb.kb")
  :destination-directory "optegrity/kbs")

(def-part opt-io-data
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory data
    :source-filename ("io-external-datapoints-configuration.csv" "io-replay-to-external-datapoint.csv" "F-101-external-data.csv")
    :destination-directory "optegrity/data")

(def-part opt-io-resources
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory resources
    :source-filename ("IATO-EventNames.txt" "ICCO-EventNames.txt" "ICO-EventNames.txt" "IDCO-EventNames.txt" "IEDO-EventNames.txt" "IFFO-FB-EventNames.txt" "IFFO-FF-EventNames.txt" "IHO-EventNames.txt" "IPO-EventNames.txt" "IRCO-EventNames.txt" "ISO-EventNames.txt" "ITO-EventNames.txt" "IVO-EventNames.txt" "IXO-EventNames.txt")
    :destination-directory "optegrity/resources")

(def-part opt-io-examples
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory examples
    :source-filename ("io-examples.kb")
    :destination-directory "optegrity/examples"
    :shortcuts (io-demo-shortcut) )

(def-part opt-f101-examples
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory examples
    :source-filename ("f101demo.kb")
    :destination-directory "optegrity/examples"
    :shortcuts (f101-demo-shortcut) ) 

(def-shortcut io-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Intelligent Objects"
    :application-display-name "Heater Example"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\examples\\io-examples.kb")

(def-shortcut f101-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Intelligent Objects"
    :application-display-name "Furnace Example"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\examples\\f101demo.kb")

;;;
;;;======= End Intelligent Object Modules =======
;;;
;;;
;;;======= Begin Socket Manager =======
;;;
(def-component socket-manager
    :print-name "Socket Manager"
    :parts (socket-manager-bin socket-manager-classes socket-manager-kbs socket-manager-example socket-manager-doc jre basic-jvl-parts)
    :include-in-contents (socket-manager-bin))

(def-part socket-manager-bin
    :source sockman
    :version :42r1
;;;    :source-ship-type :internal
    :platforms ("nt" "sparcsol")
    :source-subdirectory bin
    :source-filename ("StartSockManBridge.bat" "SocketManager.sh")
    :postinstall-code "replace_rootdir(\"sockman\"^\"bin\", \"StartSockManBridge.bat\");"
    :destination-directory "sockman/bin"
    :shortcuts (sockman-shortcut sockman-demo-shortcut)
)

(def-shortcut sockman-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "Socket Manager Bridge"
    :application-directory "sockman\\bin"
    :target-name "StartSockManBridge.bat"
)

(def-shortcut sockman-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Socket Manager"
    :application-display-name "Socket Manager Example"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\sockman\\kbs\\sockdemo.kb"
)

(def-part socket-manager-classes
    :source sockman
    :version :42r1
;;;    :source-ship-type :internal
    :platforms ("nt" "sparcsol")
    :source-subdirectory classes
    :source-filename ("SocketManager.jar")
    :destination-directory "sockman/classes"
)

(def-part socket-manager-kbs
    :source sockman
    :version :42r1
;;;    :source-ship-type :internal
    :platforms ("nt" "sparcsol")
    :source-subdirectory kbs
    :source-filename ("gsockman.kb")
    :destination-directory "sockman/kbs"
)

(def-part socket-manager-example
    :source sockman
    :version :42r1
;;;    :source-ship-type :internal
    :platforms ("nt" "sparcsol")
    :source-subdirectory examples
    :source-filename ("gsockdemo.kb")
    :destination-directory "sockman/examples"
)

(def-part socket-manager-doc
    :source sockman
    :version :42r1
;;;    :source-ship-type :internal
    :platforms ("nt" "sparcsol")
    :source-subdirectory doc
    :source-filename ("JSockManUsersGuide.pdf")
    :destination-directory "doc/bridges/sockman"
    :shortcuts (sockman-doc-shortcut)
)

(def-shortcut sockman-doc-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "Socket Manager User's Guide"
    :application-directory "doc/bridges/sockman"
    :target-name "JSockManUsersGuide.pdf")
;;;
;;;======= End Socket Manager =======
;;;
;;;======= Begin JMail =======
;;;
(def-component jmail-component
  :print-name "JMail"
  :parts (jmail-part jmail-doc jre basic-jvl-parts)
  :include-in-contents (jmail-part))

(def-part jmail-part
  :source jmail
  :version :12r2
;;;  :source-ship-type :internal
  :platforms ("nt")
  :destination-directory jmail
  :postinstall-code "replace_rootdir(\"jmail\"^\"bin\", \"StartJMailBridge.bat\");"
  :shortcuts (jmail-shortcut jmail-demo-shortcut)
)

(def-part jmail-doc
  :source jmaildoc
  :version :10r0
  :platforms ("nt")
  :indep t
  :destination-directory "doc/bridges/jmail"
  :shortcuts (jmail-doc-shortcut)
)

(def-shortcut jmail-doc-shortcut
  :folder-name optegrity-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JMail Bridge User's Guide"
  :application-directory "doc/bridges/jmail"
  :target-name "g2jmailbridge.pdf")

(def-shortcut jmail-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 JMail Bridge"
    :application-directory "jmail\\bin"
    :target-name "StartJMailBridge.bat")

(def-shortcut jmail-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 JMail Bridge"
    :application-display-name "G2 JMail Bridge Tutorial"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\jmail\\examples\\jmail-demo.kb")

;;;
;;;======= End JMail =======
;;;
;;;
;;;======= Begin JMS =======
;;;
(def-component jms-component
  :print-name "JMS"
  :parts (jms-part jms-g2i-modules jms-doc jre basic-jvl-parts)
  :optional true
  :include-in-contents (jms-part))

(def-part jms-doc
  :source jmsdoc
  :version :10r0
  :platforms ("nt")
  :indep t
  :destination-directory "doc/bridges/jms"
  :shortcuts (jms-doc-shortcut)
)

(def-shortcut jms-doc-shortcut
  :folder-name optegrity-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JMSLink User's Guide"
  :application-directory "doc/bridges/jms"
  :target-name "g2jmslink.pdf")

(def-part jms-part
  :source jms
  :version :12r2
;;;  :source-ship-type :internal
  :platforms ("nt")
  :destination-directory jms
  :postinstall-code "replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-j2ee.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-jboss.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-FioranoMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-WebSphereMQ.bat\");"
  :shortcuts (jms-j2ee-shortcut jms-jboss-shortcut jms-FioranoMQ-shortcut jms-WebSphereMQ-shortcut jms-demo-shortcut)
)

(def-shortcut jms-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 JMSLink"
    :application-display-name "G2 JMSLink Tutorial"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\jms\\examples\\jms-demo.kb")

(def-shortcut jms-SonicMQ-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 JMSLink"
    :application-display-name "G2 JMSLink Sonic MQ Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-SonicMQ.bat")

(def-shortcut jms-FioranoMQ-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 JMSLink"
    :application-display-name "G2 JMSLink Fiorano MQ Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-FioranoMQ.bat")

(def-shortcut jms-WebSphereMQ-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 JMSLink"
    :application-display-name "G2 JMSLink WebSphere MQ Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-WebSphereMQ.bat")

(def-shortcut jms-j2ee-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 JMSLink"
    :application-display-name "G2 JMSLink J2EE Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-j2ee.bat")

(def-shortcut jms-jboss-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 JMSLink"
    :application-display-name "G2 JMSLink JBoss Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-jboss.bat")

(def-part jms-g2i-modules
  :source g2i
  :version 12r2
;;;  :source-ship-type :internal
  :destination-directory "g2i/kbs"
  :source-subdirectory kbs
  :source-filename ("grtl.kb" "gerr.kb")
  :indep t)
;;;
;;;======= End JMS =======
;;;
;;;
;;;======= Begin Optegrity Modules =======
;;;
(def-component optegrity-kbs
  :print-name "Optegrity KBs"
  :parts (opt-archive opt-bin opt-data opt-examples opt-kbs opt-g2i-modules g2i-core-modules opt-logs opt-resources opt-odbc-bridge opt-opclink opt-pi opt-jms)
  :include-in-contents (opt-bin))

;;;=== ODBC Bridge delivered with G2 7.1r0
(def-part opt-odbc-bridge
  :source g2odbc
  :version :60r11
  :platforms ("nt")
  :source-filename ("g2-database.kb")
  :destination-directory "odbc")

;;;=== OPCLink Bridge delivered with G2 7.0r1
(def-part opt-opclink
  :source opclink
  :version :21r1
  :platforms ("nt")
  :source-subdirectory "KBs"
  :source-filename ("launch.kb")
  :destination-directory "opclink/kbs")

;;;=== PI Bridge delivered with G2 7.0r1
(def-part opt-pi
  :source g2pi
  :version :50r3
  :platforms ("nt")
  :source-filename ("g2-pi.kb" "gensym-raised-button.kb")
  :destination-directory "pi")

(def-part opt-jms
  :source jms
  :version :12r2
;;;  :source-ship-type :internal
  :platforms ("nt")
  :source-subdirectory kbs
  :source-filename ("jms.kb")
  :destination-directory "jms/kbs"
)

(def-part opt-archive
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :source-subdirectory archives
    :source-filename ( )
    :destination-directory "optegrity/archives"
    :indep t
)

(def-part opt-bin
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :source-subdirectory bin
    :source-filename ("InstallServerAsNTService.bat" "Optegrity.ico" "StartServer.bat" "UninstallServerAsNTService.bat" "StartClient.bat")
    :destination-directory "optegrity/bin"
    :postinstall-code "replace_rootdir(\"optegrity\"^\"bin\", \"StartServer.bat\");replace_rootdir(\"optegrity\"^\"bin\", \"InstallServerAsNTService.bat\");replace_rootdir(\"optegrity\"^\"bin\", \"UninstallServerAsNTService.bat\");replace_rootdir(\"optegrity\"^\"bin\", \"StartClient.bat\");"
    :shortcuts (optegrity-shortcut optegrity-client-shortcut optegrity-sym-users-guide furnace-demo-shortcut symcure-demo-shortcut)
    :indep t
)

(def-part opt-data
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :source-subdirectory data
    :source-filename ("fo2-external-datapoint-configuration-OPC.csv" "fo2-external-datapoint-configuration-OPC.xls" "fo2-external-datapoint-configuration-PI.csv" "fo2-external-datapoint-configuration-PI.xls" "fo2-external-datapoints-configuration.csv" "fo2-external-datapoints-configuration.xls" "fo2-logging-data.csv" "fo2-replay-to-external-datapoint.csv" "fo2-replay-to-internal-datapoint.csv")
    :destination-directory "optegrity/data"
    :indep t
)

(def-part opt-examples
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :source-subdirectory examples
    :source-filename ("fo2demo.kb")
    :destination-directory "optegrity/examples"
    :indep t
)

(def-part opt-kbs
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :source-subdirectory kbs
    :source-filename ("equipmnt.kb" "optegrity.kb" "optegrity-core.kb")
    :destination-directory "optegrity/kbs"
    :indep t
)

(def-part opt-logs
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :source-subdirectory logs
    :source-filename ( )
    :destination-directory "optegrity/logs"
    :indep t
)

(def-part opt-resources
    :source optegrity
    :version :42r1
;;;    :source-ship-type :internal
    :source-subdirectory resources
    :source-filename ("optegrity-core-resources.txt")
    :destination-directory "optegrity/resources"
    :indep t
)

(def-shortcut optegrity-shortcut
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "Start Optegrity Server"
    :application-directory "optegrity\\bin"
    :icon-file "Optegrity.ico"
    :icon-index 0
    :target-name "StartServer.bat")

(def-shortcut optegrity-client-shortcut
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "Start Optegrity Client"
    :application-directory "optegrity\\bin"
    :icon-file "Optegrity.ico"
    :icon-index 0
    :target-name "StartClient.bat")

(def-shortcut optegrity-sym-users-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "SymCure User's Guide"
    :application-directory "doc/optegrity"
    :target-name "SymCureUsersGuide.pdf")

(def-shortcut furnace-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Optegrity"
    :application-display-name "Furnace Tutorial"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\examples\\fo2demo.kb")

(def-shortcut symcure-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Optegrity"
    :application-display-name "SymCure Modeling Guide"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\g2i\\examples\\cdg-modguide.kb")

(def-part opt-g2i-modules
  :source g2i
  :version 12r2
;;;  :source-ship-type :internal
  :destination-directory "g2i/kbs"
  :source-subdirectory kbs
  :source-filename ("cdg.kb" "cdggrlb.kb" "gdpm.kb" "grlb.kb" "gdsm.kb" "gedp.kb" "guif.kb" "guif-resources.txt" "geuc.kb")
  :indep t)
;;;
;;;======= End Optegrity Modules =======
;;;


;;;=================================================
;;; Currently not used for 4.0r0.
;;;
(def-shortcut optegrity-sym-modeling-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "SymCure Modeling Guide"
    :application-directory "doc/optegrity"
    :target-name "OptSymModelingGuide.pdf")


(def-component optegrity-readme :parts (optegrity-readme) :print-name "Optegrity Readme")

(def-part optegrity-readme
    :source optegdoc
    :version :42r1
;;;    :source-ship-type :internal
    :source-filename "readme-optegrity.html"
    :indep t 
    :shortcuts (optegrity-readme))

(def-shortcut optegrity-readme
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "Readme for Optegrity Bundle"
    :application-directory ""
    :target-name "readme-optegrity.html")

;;;==================================================
;;; Try to remove the shortcut for TW
;;;
(remprop 'tw-intelnt 'part-shortcuts)

;;;==================================================
;;; Updated GDA version
;;;
(def-component gda-43r2-component :parts (gda-43r2 gda-jvl-43r2 gda-g2i-43r2) :print-name "G2 Diagnostic Assistant (GDA)")

(def-part gda-43r2
  :source gda
  :version :43r2
  :indep t    
  :destination-directory gda    
  :source-filename ("gcc.kb" "gda.kb" "gdaapps.kb" "gdabasic.kb" "gdabsdlg.kb" "gdacerel.kb" "gdacore2.kb" "gdadlg.kb" "gdareact.kb" "gdasound.exe" "gdatank.kb" "gdl.kb" "gdluisup.kb" "gqm.kb" "gqmv.kb" "grl.kb"))  

(def-part gda-jvl-43r2     
  :source jvl     
  :version :12r9	
  :source-subdirectory kbs 	
  :platforms ("hpux" "sparcsol" "nt")     
  :destination-directory gda     
  :source-filename ("g2evliss.kb" "javalink.kb"))  

(def-part gda-g2i-43r2
  :source g2i     
  :version :12r1 	
  :indep t 	
  :source-subdirectory kbs     
  :destination-directory gda     
  :source-filename ("gens.kb" "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb"))
