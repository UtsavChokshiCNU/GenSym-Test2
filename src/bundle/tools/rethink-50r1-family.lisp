;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; ReThink-FAMILY - rethink Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduj, mhd, and PPrintz


;;; The configuration file is for ReThink is 5.0 Rev 1. 

(defvar g2-shortcut-folder-name "Gensym G2 ReThink 5.0r1")
(defvar rethink-shortcut-folder-name "Gensym G2 ReThink 5.0r1")
;;; (defvar rethink-example-subsub-folder-name "ReThink")

(require "g2-82r3-family")
(provide "rethink-50r1-family")

(def-family rethink-50r1
    :index 71
    :file-syntax-version 10
    :print-name "G2 ReThink"
    :bundles (rethink-offline rethink-online rethink-client-only)
    :directory "rethink-5.0r1"
    :guid "4db7e66b-b4e4-475e-bf8b-bf7b55e6a802"
    :compatible-previous-versions (("5.0r0" "f0853dda-11aa-47d5-abe4-3342ff2ea2f8")
				   ("4.0r4" "045E9660-BBF8-445c-9D54-4F677C054F23"))
    :previous-versions (("4.0r3" "83B0DEEF-70A4-4339-82C9-290058CA0E29")
			("4.0r2" "CCD24411-CF01-4661-BAA0-90E52E487142")
			("4.0r1" "3BFDD0B2-F895-489B-A51C-9C44F6BB4405")
			("2.1r1" "243D4BBB-9EE7-11D4-8111-00A02431D004")
			("2.1r0" "243D4BB8-9EE7-11D4-8111-00A02431D004")
			("2.0r0" "243D4BAE-9EE7-11D4-8111-00A02431D004")
			;; add more here
			)
    :splash-screen "rethink-setup.bmp"
    :license-text "rethink-license.txt"
    :platforms ("nt"))




;;; Evaluation OK Components

;;; NOTE: escor and ReThink ok files.  Note, too, that
;;; this form must preceed the def-bundle form, so it interacts with certain
;;; bundle dwimification (MHD). 

(def-g2-ok-components (rethink-offline :obfuscate :from-sandbox) rethink-offline "ReThink Offline"
  (1
     (1 "-jan25-2007") (1 "-feb25-2007") (1 "-mar25-2007")
     (1 "-apr25-2007") (1 "-may25-2007") (1 "-jun25-2007")
     (1 "-jul25-2007") (1 "-aug25-2007") (1 "-sep25-2006")
     (1 "-oct25-2006") (1 "-nov25-2006") (1 "-dec25-2006")))

(def-g2-ok-components (rethink-online :obfuscate :from-sandbox) rethink-online "ReThink Online"
  (1 2 3 4 5 6 7 8
     (1 "-jan25-2007") (1 "-feb25-2007") (1 "-mar25-2007")
     (1 "-apr25-2007") (1 "-may25-2007") (1 "-jun25-2007")
     (1 "-jul25-2007") (1 "-aug25-2007") (1 "-sep25-2006")
     (1 "-oct25-2006") (1 "-nov25-2006") (1 "-dec25-2006")))



(defvar rethink-common
  '(javalink rethink-documentation rethink-reports-and-databases
    g2i-core-modules doc-pdf doc-html doc-chm protools activexlink weblink telewindows g2 gateway 
    g2-readme gda jre gservice ))

(defvar rethink-g2-bridges-common
  '(corbalink opclink Oraclebridge Sybasebridge ODBCbridge jmail-component jms-component socket-manager))


;;;
;;; Specifications of the different bundles
;;;

(def-bundle rethink-offline
    :components (rethink-common rethink-offline-component rethink-offline-server
			;; These are the OK components:
			rethink-offline-family-ok-components)
    :print-name "G2 ReThink Offline"
    :directory "ReThink"
    :version :50r1)


(def-bundle rethink-online
    :components (rethink-common rethink-online-component rethink-online-server
                  rethink-g2-bridges-common
			;; These are the OK components:
			rethink-online-family-ok-components)
    :print-name "G2 ReThink Online"
    :directory "ReThink"
    :version :50r1)


(def-bundle rethink-client-only
    :components (rethink-client
	    rethink-documentation rethink-reports-and-databases
	    doc-pdf doc-html doc-chm protools activexlink telewindows
	    g2-readme)
    :print-name "G2 ReThink Online Client Only"
    :directory "ReThink"
    :version :50r1)


;;;
;;; ReThink client components and parts
;;;
(def-component rethink-client
  :print-name "G2 ReThink Client"
  :parts (rethink-client-binaries)
  :optional false)


(def-part rethink-client-binaries
    :version :50r1
;;;    :source-ship-type :internal
    :source-filename ("ReThink.ico")
    :destination-directory "rethink/bin"
    :source "rethink"
    :indep t
    :source-subdirectory "bin")
;;;    :environment-variables (ESCOR_RETHINK_HOME))


;;
;; rethink server
;;
(def-component rethink-offline-server
  :print-name "G2 ReThink Offline Server"
  :parts (rethink-offline-server-binaries)
  :optional false
)

(def-component rethink-online-server
  :print-name "G2 ReThink Online Server"
  :parts (rethink-online-server-binaries)
  :optional false
)

(def-component rethink-offline-component
  :print-name "G2 Rethink Offline"
  :parts (rethink-offline-kbs images rethink-offline-examples rethink-resources log-part archives-part jms-g2i-modules )
  :include-in-contents (rethink-offline-kbs)
  :optional false
)

(def-component rethink-online-component
  :print-name "G2 Rethink Online"
  :parts (rethink-online-kbs images rethink-online-examples rethink-resources log-part archives-part jms-g2i-modules )
  :include-in-contents (rethink-online-kbs)
  :optional false
)

(def-part log-part
  :version :50r1
;;;  :source-ship-type :internal
  :destination-directory "rethink/logs"
  :source-subdirectory "logs"
  :source "rethink"
  :indep t
)

(def-part archives-part
  :version :50r1
;;;  :source-ship-type :internal
  :destination-directory "rethink/archives"
  :source-subdirectory "archives"
  :source "rethink"
  :indep t
)

(def-part rethink-resources
  :version :50r1
;;;  :source-ship-type :internal
  :destination-directory "rethink/resources"
  :source-subdirectory "resources"
  :source "rethink"
  :indep t
)

(def-part rethink-offline-kbs
    :version :50r1
;;;    :source-ship-type :internal
    :destination-directory "rethink/kbs"
    :source-subdirectory "kbs"
    :source-filename ("rethink.kb" "bpr.kb" "bprui.kb" "customiz.kb" "methods.kb" "menus.kb" "rethink-core.kb") 
    :source "rethink"
    :indep t
;;;    :shortcuts (rethink-offline-server-shortcut)
)

(def-part rethink-online-kbs
    :version :50r1
;;;    :source-ship-type :internal
    :destination-directory "rethink/kbs"
    :source-subdirectory "kbs"
    :source-filename ("rethink.kb" "rethink-online.kb" "rethink-online-core.kb" "rethink-core.kb" "bpr.kb" "bprui.kb" "customiz.kb" "methods.kb" "menus.kb" "methods-online.kb") 
    :source "rethink"
    :indep t
;;;    :shortcuts (rethink-online-server-shortcut)
)

(def-part rethink-offline-examples
  :version :50r1
;;;  :source-ship-type :internal
  :destination-directory "rethink/examples"
  :source-subdirectory "examples"
  :source-filename ("aero.kb" "chapter3.kb" "orderful.kb" "rethink-40-doc-examples.kb")
  :source "rethink"
  :indep t
  :shortcuts (aero-tutorial orderful-tutorial chapter3-tutorial rethink-40-tutorial)
)

(def-part rethink-online-examples
  :version :50r1
;;;  :source-ship-type :internal
  :destination-directory "rethink/examples"
  :source-subdirectory "examples"
  :source-filename ("aero.kb" "chapter3.kb" "orderful.kb" "rethink-40-doc-examples.kb" "rethink-40-online-examples.kb")
  :source "rethink"
  :indep t
  :shortcuts (aero-tutorial orderful-tutorial chapter3-tutorial rethink-40-tutorial rethink-40-online-tutorial)
)

(def-shortcut rethink-40-tutorial
    :folder-name rethink-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "ReThink 4.0 Examples"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\rethink-40-doc-examples.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)


(def-shortcut aero-tutorial
    :folder-name rethink-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "Aero Model"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\aero.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut chapter3-tutorial
    :folder-name rethink-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "Chapter3 Model"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\chapter3.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut orderful-tutorial
    :folder-name rethink-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "Orderful Model"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\orderful.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut rethink-40-online-tutorial
    :folder-name rethink-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "ReThink 4.0 Online Example"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\rethink-40-online-examples.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)



(def-part images
    :version :50r1
;;;    :source-ship-type :internal
    :destination-directory "rethink/kbs/images"
    :source-subdirectory "kbs/images"
    :source "rethink"
    :indep t
)

(def-part rethink-offline-server-binaries
    :version :50r1
;;;    :source-ship-type :internal
    :source-filename ("ReThink.ico")
    :destination-directory "rethink/bin"
    :source "rethink"
    :indep t
    :source-subdirectory "bin"
    :shortcuts (rethink-offline-server-shortcut)
)

(def-shortcut rethink-offline-server-shortcut
    :folder-name rethink-shortcut-folder-name
    :application-display-name "Start ReThink Offline Server"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\kbs\\rethink.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)


(def-part rethink-online-server-binaries
    :version :50r1
;;;    :source-ship-type :internal
    :source-filename ("ReThink.ico")
    :destination-directory "rethink/bin"
    :source "rethink"
    :indep t
    :source-subdirectory "bin"
    :shortcuts (rethink-online-server-shortcut)
)

(def-shortcut rethink-online-server-shortcut
    :folder-name rethink-shortcut-folder-name
    :application-display-name "Start ReThink Online Server"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\kbs\\rethink-online.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)


;;;
;;; Excel reports and Access Databases for ReThink
;;;
(def-component rethink-reports-and-databases
  :print-name "ReThink reports and databases"
  :parts (rethink-reports rethink-databases)
  :optional false)


(def-part rethink-reports
    :version :50r1
;;;    :source-ship-type :internal
    :destination-directory "rethink/data"
    :source-subdirectory "data"
    :source-filename ("ReThink-Summary-Reports.xls")
    :source "rethink"
    :indep t
;;;    :platforms ("nt")
    :shortcuts (rethink-default-summary-reports))

(def-shortcut rethink-default-summary-reports
    :folder-name rethink-shortcut-folder-name
    :application-display-name "ReThink Default Summary Reports"
    :application-directory "rethink/data"
    :target-name "ReThink-Summary-Reports.xls")

(def-part rethink-databases
    :version :50r1
;;;    :source-ship-type :internal
    :destination-directory "rethink/data"
    :source-subdirectory "data"
    :source-filename ("orders.mdb")
    :source "rethink"
    :indep t)

;;;    :platforms ("nt"))

;;;
;;; Documentation components for ReThink
;;;
(def-component rethink-documentation
  :parts (rethink-documentation rethink-readme)
  :print-name "ReThink Documentation"
  :optional true)


(def-part rethink-readme
    :version :50r1
;;;    :source-ship-type :internal
    :source-filename "ReThink-readme.html"
    :source "rethink"
    :indep t
    :print-name "ReThink README file"
    :shortcuts (rethink-readme-shortcut))

(def-shortcut rethink-readme-shortcut
    :folder-name rethink-shortcut-folder-name
    :application-display-name "Readme for ReThink"
    :application-directory ""
    :target-name "ReThink-readme.html")


(def-part rethink-documentation
    :version :50r1
;;;    :source-ship-type :internal
    :destination-directory "doc/rethink"
    :source-subdirectory "doc"
    :source rethink
    :indep t
    :shortcuts (rethink-getting-started-documentation rethink-documentation-user rethink-documentation-customization 
         rethink-documentation-winhelp))

(def-shortcut rethink-getting-started-documentation
    :folder-name rethink-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "ReThink"
    :application-display-name "Getting Started with ReThink"
    :application-directory "doc/rethink"
    :target-name "ReThinkTutorials.pdf")

(def-shortcut rethink-documentation-user
    :folder-name rethink-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "ReThink"
    :application-display-name "ReThink Users Guide"
    :application-directory "doc/rethink"
    :target-name "ReThinkUsersGuide.pdf")

(def-shortcut rethink-documentation-customization
    :folder-name rethink-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "ReThink"
    :application-display-name "Customizing ReThink Users Guide"
    :application-directory "doc/rethink"
    :target-name "CustomizingReThinkUsersGuide.pdf")

(def-shortcut rethink-documentation-winhelp
    :folder-name rethink-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "ReThink"
    :application-display-name "Windows Help ReThink Documentation"
    :application-directory "doc/rethink/WinHelp"
    :target-name "Master.chm")


;;;======= Begin G2i Modules =======
;;;
(def-component g2i-core-modules
  :print-name "G2i Modules"
  :parts (g2i-examples rethink-g2i-core-modules))
;;;  :parts (g2i-core-modules g2i-examples rethink-g2i-core-modules))


(def-part rethink-g2i-core-modules
  :source g2i
  :version :22r2
;;;  :source-ship-type :internal
  :indep t
  :source-subdirectory kbs
  :source-filename ("grpe.kb" "gdsm.kb" "gdu.kb" "gduc.kb" "gdue.kb" "gens.kb" "gerr.kb" "gevm.kb" "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "grlb.kb" "grtl.kb" "resources-english.txt" "config.txt")
  :destination-directory "g2i/kbs"
  :make-not-read-only t
  :postinstall-code "replace_rootdir(\"g2i\"^\"kbs\", \"config.txt\");"
)

;;;
;;;======= End G2i Modules =======

(def-part jms-g2i-modules
  :source g2i
  :version :22r2
  :destination-directory "g2i/kbs"
;;;  :source-ship-type :internal
  :source-subdirectory kbs
  :source-filename ("grtl.kb" "gerr.kb")
  :indep t)


