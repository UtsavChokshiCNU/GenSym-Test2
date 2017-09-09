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
(defvar g2-shortcut-folder-name "Gensym G2 Optegrity 5.0r0")
(defvar nol-shortcut-folder-name "Gensym G2 Optegrity 5.0r0")  
;; MODIFY
;; Setting the shortcut for the Optegrity bundle
(defvar optegrity-shortcut-folder-name "Gensym G2 Optegrity 5.0r0")
;; MODIFY
;; Defining the module search path for Optegrity.  This needs to be modified if the support
;;   KBs path changes.
(defvar optegrity-search-path-and-ok-file "-module-search-path ..\\g2i\\kbs kbs\\utils ..\\optegrity\\kbs ..\\optegrity\\demos ..\\pi ..\\odbc ..\\opclink\\kbs ..\\protools\\kbs ..\\gw ..\\corbalink\\kbs ..\\javalink\\kbs ..\\gda ..\\activexlink ..\\oracle ..\\sybase ..\\sockman\\kbs -ok ..\\g2\\g2.ok")

;; MODIFY
;; Indicating that G2 will be a required bundle for Optegrity.  This indicates which version of G2
;;   will be included in the Optegrity bundle.
(require "g2-82r2-family")                ; Optegrity 5.0r0
(require "nol-50r0-family")               ; To include NOL capability
;;(require "g2-71r3-family")                ; Optegrity 4.2r1
;;(require "g2-71r2-family")              ; Optegrity 4.2r0
;;(require "g2-71r0-family")              ; Optegrity 4.1r0
;;(require "g2-70r1-family")              ; Optegrity 4.0r0
;;(require "g2-62r2-family")			; G2 6.2r2

;; MODIFY
;; The name of the Optegrity bundle so other bundles can include in their family files.
(provide "optegrity-50r0-family")

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
(def-g2-ok-components (optegrity-reasoner-development :obfuscate :from-sandbox) optegrity "G2 Optegrity Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
			(1 "-aug25-2006")
			(1 "-sep25-2006") (1 "-oct25-2006") (1 "-nov25-2006")
                  (1 "-dec25-2006") (1 "-jan25-2007") (1 "-feb25-2007")
))

(def-g2-ok-components (optegrity-reasoner-deployment :obfuscate :from-sandbox) optegrity "G2 Optegrity Deployment"
		      (4 8 16 20 24 28 32
			(1 "-aug25-2006")
			(1 "-sep25-2006") (1 "-oct25-2006") (1 "-nov25-2006")
                  (1 "-dec25-2006") (1 "-jan25-2007") (1 "-feb25-2007")
))


;;the following list of components is in every bundle, so abstract it out here
;;
;;  This defines the components that are common to every Optegrity bundle.  There is no
;;    need to change this unless we add another component to the common list.  If addition
;;    is required, then make sure the addition is within the parenthesis.
(defvar optegrity-common
  '(javalink optegrity-documentation optegrity-win-documentation optegrity-release-notes-component 
    g2i-core-modules doc-pdf doc-html doc-chm protools activexlink weblink telewindows g2 gateway 
    g2-readme gda gda-45r1 jre cdg-import-export optegrity-readme gservice ))

(defvar opt-g2-bridges-common
  '(corbalink opclink pibridge Oraclebridge Sybasebridge ODBCbridge ))

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
(def-family optegrity-50r0
    :index 43
    :file-syntax-version 10
    :print-name "G2 Optegrity"
    :bundles (optegrity-development optegrity-deployment)
    :directory "optegrity-5.0r0"
    :guid "ba89ab5b-ea60-4c99-87e0-e3f41c80a540"
    :compatible-previous-versions (("40a0" "88fb5875-5df5-449c-87de-0cbd5263552f")
                                   ("42r0" "c9065ef2-5691-444d-b740-ae3bb4e39561")
                                   ("42r1" "7a027366-779b-4ed2-8bc5-8b50fa67087a")
                                   ("50b0" "fdf14328-4a21-40fa-bc3b-418e1b312b40"))

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
    :version :50r0
    :print-name "G2 Optegrity Development"
    :components (optegrity-common optegrity-kbs opt-g2-bridges-common socket-manager jmail-component jms-component
                 ;;; nol-component
                 nol-premium-component
		  optegrity-reasoner-development-family-ok-components))

;;;   The deployment bundles include the exact same files as their development counterparts
;;;   with the exception of the ok files.  They are for deployment vs. development.
(def-bundle optegrity-deployment
    :version :50r0
    :print-name "G2 Optegrity Deployment"
    :components (optegrity-common optegrity-kbs opt-g2-bridges-common socket-manager jmail-component jms-component 
                 nol-premium-component
		  optegrity-reasoner-deployment-family-ok-components))


;;===========================================
;; Redefining G2's shortcut to get the module search path correct
;;;(def-shortcut g2-shortcut
;;;    :folder-name g2-shortcut-folder-name
;;;    :application-display-name "G2"
;;;    :application-directory "g2"
;;;    :target-name "g2.exe"
;;;    :parameters "-module-search-path ..\\g2i\\kbs kbs\\utils ..\\optegrity\\kbs ..\\optegrity\\demos ..\\pi ..\\odbc ..\\opclink\\kbs ..\\protools\\kbs ..\\gw ..\\corbalink\\kbs ..\\javalink\\kbs ..\\gda ..\\activexlink ..\\oracle ..\\sybase ..\\sockman\\kbs -ok ..\\g2\\g2.ok")



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
    :print-name "G2 Optegrity WinHelp"
    :parts (optegrity-win-doc))

(def-part optegrity-win-doc
    :source optwinhelp
    :version :50r0
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
    :print-name "G2 Optegrity Release Notes"
    :parts (optegrity-release-notes))

(def-part optegrity-release-notes
    :source optegdoc
    :version :50r0
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
    :print-name "G2 Optegrity Documentation"
    :parts (optegrity-doc))


;;;  +++
(def-part optegrity-doc
    :source optegdoc
    :version :50r0
;;;    :source-ship-type :internal
    :source-filename ("GEDPUsersGuide.pdf" "OptegrityUsersGuide.pdf" "SymCureUsersGuide.pdf" "OptegrityHeaterTutorial.pdf")
    :destination-directory "doc/optegrity"
    :indep t
    :shortcuts (opt-users-guide 
;;; leaving opt-rel-notes out of the Alpha release.
;;;                opt-rel-notes
                gedp-users-guide 
;;; WSM 3.23.2006 opt-io-users-guide 
                opt-intelligent-demo-guide))

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

(def-shortcut opt-intelligent-demo-guide
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Optegrity"
    :application-display-name "Optegrity Heater Tutorial"
    :application-directory "doc/optegrity"
    :target-name "OptegrityHeaterTutorial.pdf")

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
  :version :50r0
;;;  :source-ship-type :internal
  :source-filename ("readme-symcure.html" "readme-symcure3.gif")
  :destination-directory "g2i"
  :indep t
  :shortcuts (cdg-readme))

(def-shortcut cdg-readme
  :folder-name optegrity-shortcut-folder-name
  :application-display-name "Readme for SymCure"
  :application-directory "g2i"
  :target-name "readme-symcure.html")

;;;
;;;======= Begin NOL Component =======
;;;
(def-component nol-premium-component
  :print-name "Neural Network Engine and NeurOn-Line Studio"
  :optional true
  :parts (nolstudio-data nolstudio-math-library nolstudio-gui opt-nolstudio-batch nolstudio-window-classic-dll
          nolstudio-deploy-library nolstudio-online-batch nol-classic-gnne opt-nol-classic-kb opt-nol-classic-nt gnne-demo
          gnne-demo-config nol-g2i-modules nolstudio-gui-misc nolstudio-examples nol-classic-documentation nol-opt-winhelp)
)
;;; I want to get everything from nolstudio-batch, but not include the shortcuts
(def-part opt-nolstudio-batch
     :version :50r0
      :source nols
     :destination-directory nolstudio
     :platforms ("nt")
     :source-filename ("nolstudio.bat")
 	:postinstall-code "replace_rootdir(\"nolstudio\", \"nolstudio.bat\");"
)

(def-part opt-nol-classic-kb
     :source nol
     :version :50r0
     :source-subdirectory kbs
     :indep t
     :destination-directory "nol/kbs"
     :source-filename ("gnneapps.kb" "java-module.kb"  "nolspack.kb" "nolstudio.kb"))

(def-part opt-nol-classic-nt
     :source nol
     :version :50r0
     :source-subdirectory bin
     :indep t
     :destination-directory "nol/bin"
     :platforms ("nt")
     :source-filename ("ntnol.exe" "nol.ico")
;;;     :shortcuts (gnneapps-shortcut gnnedemo-shortcut)
     :shortcuts (gnnedemo-shortcut)
)
  (def-shortcut gnneapps-shortcut
      :folder-name nol-shortcut-folder-name
      :application-display-name "Neural Network Engine Application"
      :application-directory g2
      :target-name "StartServer.bat"
      :parameters "-kb ..\\nol\\kbs\\gnneapps.kb -start"
      :icon-file "../nol/bin/nol.ico"
      :icon-index 0
      :run-style minimized)
  (def-shortcut gnnedemo-shortcut
      :folder-name nol-shortcut-folder-name
      :subfolder-name "Examples"
      :subsubfolder-name "NeurOn-Line"
      :application-display-name "Neural Network Engine Demo"
 	 :application-directory g2
      :target-name "StartServer.bat"
      :parameters "-kb ..\\nol\\projects\\examples\\gnne-demo\\gnne-demo.kb -configfile ..\\nol\\projects\\examples\\gnne-demo\\config.txt"
      :icon-file "../nol/bin/nol.ico"
      :icon-index 0
      :run-style minimized)

(def-part nol-opt-winhelp
	:source nol
	:version :50r0
	:source-subdirectory "noldoc/WinHelp"
	:destination-directory "doc/nol"
	:indep t
	:shortcuts (gnne-nol-winhelp-shortcut)
)
  (def-shortcut gnne-nol-winhelp-shortcut
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "NeurOn-Line"
    :application-display-name "Neural Network Engine and NeurOn-Line Studio Help"
    :application-directory "doc/nol/WinHelp"
    :target-name "Master.chm")
;;;
;;;======= End NOL Component =======

;;;
;;;======= Begin G2i Modules =======
;;;
;;;;(def-component opt-g2i-core-modules
;;;;  :print-name "G2i Modules"
;;;;  :parts (g2i-core-modules g2i-examples opt-g2i-datafiles))

;;;;(def-part opt-g2i-core-modules
;;;;  :source g2i
;;;;  :version :22r2
;;;;;;;  :source-ship-type :internal
;;;;  :indep t
;;;;  :source-subdirectory kbs
;;;;  :source-filename ("grtl.kb" "gedp.kb" "gdpm.kb" "config.txt")
;;;;  :destination-directory "g2i/kbs"
;;;;  :postinstall-code "replace_rootdir(\"g2i\"^\"kbs\", \"config.txt\");"
;;;;)


(def-part opt-g2i-examples
  :source g2i
  :version :22r2
;;;  :source-ship-type :internal
  :indep t
  :source-subdirectory examples
  :source-filename ("cdg-modguide.kb" "gdpm-demo.kb")
  :destination-directory "g2i/examples"
  :shortcuts (symcure-demo-shortcut gdpm-demo-shortcut) )

(def-part opt-g2i-datafiles
  :source g2i
  :version :22r2
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
    :subsubfolder-name "Optegrity"
    :application-display-name "GDPM Example"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\g2i\\examples\\gdpm-demo.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)


(def-shortcut gdu-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2i"
    :application-display-name "GDU Example"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\g2i\\examples\\gdu-demo.kb")

;;;
;;;======= End G2i Modules =======
;;;
;;;
;;;======= Begin Intelligent Object Modules =======
;;;
;;; 6/14/2006 WSM
;;; Adding opt-io-modules, opt-io-data, opt-io-resources, and opt-io-examples to the optegrity-kbs component.
;;; By doing this it will force the IO modules to be installed without having to select the option to
;;; install them.
;;;
(def-component io-modules
  :print-name "Intelligent Objects"
  :parts (opt-io-modules opt-io-data opt-io-resources opt-io-examples)
;;;  :optional true
  :include-in-contents (opt-io-modules))

(def-part opt-io-modules
  :source optegrity
  :version :50r0
;;;  :source-ship-type :internal
  :indep t
  :source-subdirectory kbs
  :source-filename ("iato.kb" "icco.kb" "ico.kb"  "icso.kb" "idco.kb" "iedo.kb" "iffo.kb" "iho.kb" "ioc.kb" "ipo.kb" "irco.kb" "iso.kb" "ito.kb" "ivo.kb" "ixo.kb" "sdb.kb" "opt-event.kb")
  :destination-directory "optegrity/kbs")

(def-part opt-io-data
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory data
    :source-filename ("F102-replay-to-external-datapoint.csv" "F102-external-datapoint-configuration-OPC.csv")
    :destination-directory "optegrity/data")

(def-part opt-io-resources
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory resources
    :source-filename ("IATO-EventNames.txt" "ICCO-EventNames.txt" "ICO-EventNames.txt" "IDCO-EventNames.txt" "IEDO-EventNames.txt" "IFFO-FB-EventNames.txt" "IFFO-FF-EventNames.txt" "IHO-EventNames.txt" "IPO-EventNames.txt" "IRCO-EventNames.txt" "ISO-EventNames.txt" "ITO-EventNames.txt" "IVO-EventNames.txt" "IXO-EventNames.txt")
    :destination-directory "optegrity/resources")

(def-part opt-io-examples
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory examples
    :source-filename ("f102demo.kb")
    :destination-directory "optegrity/examples"
    :shortcuts (io-demo-shortcut) )

(def-part opt-f101-examples
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory examples
    :source-filename ("f101demo.kb" "f102demo.kb")
    :destination-directory "optegrity/examples"
    :shortcuts (f101-demo-shortcut f102-demo-shortcut) ) 

(def-shortcut io-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Optegrity"
    :application-display-name "Heater Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\examples\\f102demo.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut f101-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Intelligent Objects"
    :application-display-name "Furnace Example"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\examples\\f101demo.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut f102-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Intelligent Objects"
    :application-display-name "Furnace Example"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\examples\\f102demo.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)

;;;
;;;======= End Intelligent Object Modules =======
;;;
;;;
;;;======= Begin Optegrity Modules =======
;;; 2.22.2006 WSM: removed opt-data to remove the fo2demo data files from the bundle.
;;;
(def-component optegrity-kbs
  :print-name "G2 Optegrity and Intelligent Object KBs"
  :parts (opt-archive opt-bin opt-kbs opt-g2i-modules opt-logs opt-resources odbckbs opclinkkbs 
          pikbs opt-jms jms-g2i-modules opt-project opt-g2i-examples opt-g2i-datafiles
          opt-io-modules opt-io-data opt-io-resources opt-io-examples)
  :include-in-contents (opt-bin opt-io-modules))

;;;=== ODBC Bridge delivered with G2 7.1r0
;;;===  Now using odbckbs provided by the G2 family file
(def-part opt-odbc-bridge
  :source g2odbc
  :version :82r0
  :platforms ("nt")
  :source-subdirectory "kbs"
  :source-filename ("g2-database.kb")
  :destination-directory "odbc")

;;;=== OPCLink Bridge delivered with G2 7.0r1
;;;===  Now using opclinkkbs provided by the G2 family file
(def-part opt-opclink
  :source opclink
  :version :30r2
  :platforms ("nt")
  :source-subdirectory "KBs"
  :source-filename ("launch.kb")
  :destination-directory "opclink/kbs")

;;;=== PI Bridge delivered with G2 7.0r1
;;;===  Now using pikbs defined in the G2 family file
(def-part opt-pi
  :source g2pi
  :version :82r0
  :platforms ("nt")
  :source-filename ("g2-pi.kb" "gensym-raised-button.kb")
  :destination-directory "pi")

(def-part opt-jms
  :source jms
  :version :22r2
;;;  :source-ship-type :internal
  :platforms ("nt")
  :source-subdirectory kbs
  :source-filename ("jms.kb")
  :destination-directory "jms/kbs"
)

(def-part jms-g2i-modules
  :source g2i
  :version :22r2
  :destination-directory "g2i/kbs"
;;;  :source-ship-type :internal
  :source-subdirectory kbs
  :source-filename ("grtl.kb" "gerr.kb")
  :indep t)

(def-part opt-archive
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :source-subdirectory archives
    :source-filename ( )
    :destination-directory "optegrity/archives"
    :indep t
)

(def-part opt-project
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :source-subdirectory projects
    :source-filename ( )
    :destination-directory "optegrity/projects"
    :indep t
)

(def-part opt-bin
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :source-subdirectory bin
    :source-filename ("InstallServerAsNTService.bat" "Optegrity.ico" "UninstallServerAsNTService.bat")
    :destination-directory "optegrity/bin"
    :postinstall-code "replace_rootdir(\"optegrity\"^\"bin\", \"InstallServerAsNTService.bat\");replace_rootdir(\"optegrity\"^\"bin\", \"UninstallServerAsNTService.bat\");"
    :shortcuts (optegrity-shortcut optegrity-sym-users-guide)
    :indep t
)

(def-part opt-data
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :source-subdirectory data
    :source-filename ("fo2-external-datapoint-configuration-OPC.csv" "fo2-external-datapoint-configuration-OPC.xls" "fo2-external-datapoint-configuration-PI.csv" "fo2-external-datapoint-configuration-PI.xls" "fo2-external-datapoints-configuration.csv" "fo2-external-datapoints-configuration.xls" "fo2-logging-data.csv" "fo2-replay-to-external-datapoint.csv" "fo2-replay-to-internal-datapoint.csv")
    :destination-directory "optegrity/data"
    :indep t
)

(def-part opt-examples
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :source-subdirectory examples
    :source-filename ("fo2demo.kb")
    :destination-directory "optegrity/examples"
    :indep t
)

(def-part opt-kbs
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :source-subdirectory kbs
    :source-filename ("equipmnt.kb" "optegrity.kb" "optegrity-core.kb")
    :destination-directory "optegrity/kbs"
    :indep t
)

(def-part opt-logs
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :source-subdirectory logs
    :source-filename ( )
    :destination-directory "optegrity/logs"
    :indep t
)

(def-part opt-resources
    :source optegrity
    :version :50r0
;;;    :source-ship-type :internal
    :source-subdirectory resources
    :source-filename ("optegrity-core-resources.txt")
    :destination-directory "optegrity/resources"
    :indep t
)

(def-shortcut optegrity-shortcut
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "Start Optegrity Server"
    :application-directory "g2"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\kbs\\optegrity.kb -nowindow"
    :run-style minimized)

(def-shortcut optegrity-client-shortcut
    :folder-name optegrity-shortcut-folder-name
    :application-display-name "Start Optegrity Client"
    :application-directory "g2"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :target-name "twng.exe")

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
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\examples\\fo2demo.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut symcure-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Optegrity"
    :application-display-name "SymCure Modeling Guide"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\g2i\\examples\\cdg-modguide.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)


(def-part opt-g2i-modules
  :source g2i
  :version 22r2
;;;  :source-ship-type :internal
  :destination-directory "g2i/kbs"
;;;;
;;;; 6/9/2006
;;;; Removed for 50r0, causing a write error during installation
;;;;  Also removed "config.txt" from the source-filename directive
  :postinstall-code "replace_rootdir(\"g2i\"^\"kbs\", \"config.txt\");"
;;;;
  :source-subdirectory kbs
  :source-filename ("cdg.kb" "cdggrlb.kb" "gdpm.kb" "gedp.kb" "guif.kb" "guif-resources.txt" "geuc.kb" "symcure.kb" "grtl.kb" "gevm.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "grlb.kb" "gdsm.kb" "gdu.kb" "gduc.kb" "gdue.kb" "gens.kb" "gerr.kb" "glf.kb" "resources-english.txt")
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


(def-component optegrity-readme :parts (optegrity-readme) :print-name "G2 Optegrity Readme")

(def-part optegrity-readme
    :source optegdoc
    :version :50r0
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

