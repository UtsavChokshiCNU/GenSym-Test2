;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; ESCOR-FAMILY - escor Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduj, mhd, and PPrintz


;;; The current shipping version of e-SCOR is 4.0 Rev. 4("40r4").  The
;;; symbol :40r4 should be used generally for e-SCOR / ReThink elements below.

(defvar g2-shortcut-folder-name "Gensym e-SCOR & ReThink 5.0r0")
(defvar escor-shortcut-folder-name "Gensym e-SCOR & ReThink 5.0r0")

(require "g2-81r1-family")
(require "rethink-50r0-family")
(provide "escor-50r0-family")

(def-family escor-50r0
    :index 52
    :file-syntax-version 10
    :print-name "eSCOR_ReThink"
    :bundles (escor-offline escor-online)
    :directory "escor_rethink-5.0r0"
    :guid "6c10f73d-11d6-4fb0-b814-ab96c5063440"
    :previous-versions (("4.0r4" "045E9660-BBF8-445c-9D54-4F677C054F23")
                  ("4.0r3" "83B0DEEF-70A4-4339-82C9-290058CA0E29")
			("4.0r2" "CCD24411-CF01-4661-BAA0-90E52E487142")
			("4.0r1" "3BFDD0B2-F895-489B-A51C-9C44F6BB4405")
			("2.1r1" "243D4BBB-9EE7-11D4-8111-00A02431D004")
			("2.1r0" "243D4BB8-9EE7-11D4-8111-00A02431D004")
			("2.0r0" "243D4BAE-9EE7-11D4-8111-00A02431D004")
			;; add more here
			)
    :splash-screen "escor-setup.bmp"
    :license-text "escor-license.txt"
    :platforms ("nt"))




;;; Evaluation OK Components

;;; NOTE: escor and ReThink ok files.  Note, too, that
;;; this form must preceed the def-bundle form, so it interacts with certain
;;; bundle dwimification (MHD). 

(def-g2-ok-components (escor-offline :obfuscate t) escor-offline "e-SCOR Offline"
  (1
     (1 "-may25-2005") (1 "-jun25-2005")
     (1 "-jul25-2005") (1 "-aug25-2005") (1 "-sep25-2005")
     (1 "-oct25-2005") (1 "-nov25-2005") (1 "-dec25-2005")
     (1 "-jan25-2006") (1 "-feb25-2006") (1 "-mar25-2006")
     (1 "-apr25-2006") (1 "-may25-2006") (1 "-jun25-2006")
     (1 "-jul25-2006") (1 "-aug25-2006")))

(def-g2-ok-components (escor-online :obfuscate t) escor-online "e-SCOR Online"
  (1 2 3 4 5 6 7 8
     (1 "-may25-2005") (1 "-jun25-2005")
     (1 "-jul25-2005") (1 "-aug25-2005") (1 "-sep25-2005")
     (1 "-oct25-2005") (1 "-nov25-2005") (1 "-dec25-2005")
     (1 "-jan25-2006") (1 "-feb25-2006") (1 "-mar25-2006")
     (1 "-apr25-2006") (1 "-may25-2006") (1 "-jun25-2006")
     (1 "-jul25-2006") (1 "-aug25-2006")))





;;;
;;; Specifications of the different bundles
;;;

(def-bundle escor-offline
    :components (rethink-common rethink-offline-component escor-server
			escor-documentation rethink-documentation
			;; These are the OK components:
			escor-offline-family-ok-components)
    :print-name "e-SCOR Offline"
    :directory "escor"
    :version :50r0)


(def-bundle escor-online
    :components (rethink-common rethink-online-component escor-server
			rethink-g2-bridges-common 
			escor-documentation rethink-documentation 
			;; These are the OK components:
			escor-online-family-ok-components)
    :print-name "e-SCOR Online"
    :directory "escor"
    :version :50r0)

;;;(def-bundle escor-online-client
;;;    :components (escor-client
;;;			escor-documentation rethink-documentation)
;;;    :print-name "e-SCOR Online Client Only"
;;;    :directory "escor"
;;;    :version :50r0)

;;;
;;; e-SCOR client components and parts
;;;
(def-component escor-client
  :print-name "e-SCOR Client"
  :parts (escor-client-binaries escor-readme escor-xls-reports)
  :optional false)

(def-part escor-client-binaries
    :version :50r0
    :source-ship-type :internal
    :source-filename ("StartClient.bat" "e-SCOR.ico")
    :destination-directory "escor/bin"
    :source "escor"
    :source-subdirectory "bin"
    :platforms ("nt")
    :shortcuts (escor-client-shortcut)
;;;    :environment-variables (ESCOR_RETHINK_HOME)   
    :postinstall-code "replace_rootdir(\"escor\"^\"bin\", \"StartClient.bat\");")

(def-shortcut escor-client-shortcut
    :folder-name escor-shortcut-folder-name
    :application-display-name "Start e-SCOR Client"
    :application-directory "escor/bin"
    :target-name "StartClient.bat"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-part escor-readme
    :version :50r0
    :source-ship-type :internal
    :source-filename ("e-SCOR-readme.html")
    :source "escor"
    :platforms ("nt")
    :print-name "e-SCOR README file"
    :shortcuts (escor-readme-shortcut))

(def-shortcut escor-readme-shortcut
    :folder-name escor-shortcut-folder-name
    :application-display-name "Readme for e-SCOR"
    :application-directory ""
    :target-name "e-SCOR-readme.html")


(def-part escor-xls-reports
    :version :50r0
    :source "escor"
    :platforms ("nt")
    :source-ship-type :internal
    :destination-directory "escor/data"
    :source-subdirectory "data"
    :source-filename ("e-SCOR-Summary-Reports.xls" "Tutorial-Simplest-Model-Summary-Reports.xls" "Tutorial-ACME-Summary-Reports.xls" "Tutorial-VMI-Summary-Reports.xls")
    :shortcuts (escor-default-summary-reports
		 simplest-model-summary-reports-tutorial
		 acme-summary-report-tutorial
		 vmi-summary-report-tutorial))

(def-shortcut escor-default-summary-reports
    :folder-name escor-shortcut-folder-name
    :application-display-name "e-SCOR Default Summary Reports"
    :application-directory "escor/data"
    :target-name "e-SCOR-Summary-Reports.xls")

(def-shortcut simplest-model-summary-reports-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "Simplest Model Summary Reports"
    :application-directory "escor/data"
    :target-name "Tutorial-Simplest-Model-Summary-Reports.xls")

(def-shortcut acme-summary-report-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "ACME Summary Reports"
    :application-directory "escor/data"
    :target-name "Tutorial-ACME-Summary-Reports.xls")

(def-shortcut vmi-summary-report-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "VMI Summary Reports"
    :application-directory "escor/data"
    :target-name "Tutorial-VMI-Summary-Reports.xls")

(def-component escor-server
  :print-name "e-SCOR Server"
  :parts (escor-kbs escor-server-binaries escor-images escor-examples escor-resources escor-log-part escor-archives-part)
  :optional false
)

(def-part escor-log-part
  :version :50r0
  :platforms ("nt")
  :source-ship-type :internal
  :destination-directory "escor/logs"
  :source-subdirectory "logs"
  :source "escor"
)

(def-part escor-archives-part
  :version :50r0
  :platforms ("nt")
  :source-ship-type :internal
  :destination-directory "escor/archives"
  :source-subdirectory "archives"
  :source "escor"
)

(def-part escor-resources
  :version :50r0
  :platforms ("nt")
  :source-ship-type :internal
  :destination-directory "escor/resources"
  :source-subdirectory "resources"
  :source "escor"
)

(def-part escor-kbs
    :version :50r0
    :platforms ("nt")
    :source-ship-type :internal
    :destination-directory "escor/kbs"
    :source-subdirectory "kbs"
    :source-filename ("escor-customiz.kb" "e-scor.kb") 
    :source "escor"
)

(def-part escor-examples
  :version :50r0
  :platforms ("nt")
  :source-ship-type :internal
  :destination-directory "escor/examples"
  :source-subdirectory "examples"
  :source-filename ("escor-demo.kb" "escor-tutorial-acme.kb" "escor-tutorial-vmi.kb")
  :source "escor"
  :shortcuts (demo-tutorial acme-tutorial vmi-tutorial)
)

(def-shortcut demo-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "e-SCOR 5.0 Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\escor\\kbs\\escor-demo.kb -nowindow"
    :icon-file "../escor/bin/e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut acme-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "ACME Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\escor\\kbs\\escor-tutorial-acme.kb -nowindow"
    :icon-file "../escor/bin/e-SCOR.ico"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut vmi-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "VMI Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\escor\\kbs\\escor-tutorial-vmi.kb -nowindow"
    :icon-file "../escor/bin/e-SCOR.ico"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)


(def-part escor-images
    :version :50r0
    :platforms ("nt")
    :source-ship-type :internal
    :destination-directory "escor/kbs/images"
    :source-subdirectory "kbs/images"
    :source "escor"
)


(def-part escor-server-binaries
    :version :50r0
    :platforms ("nt")
    :source-ship-type :internal
    :source-filename ("StartServer.bat" "e-SCOR.ico")
    :destination-directory "escor/bin"
    :source "escor"
    :source-subdirectory "bin"
    :postinstall-code "replace_rootdir(\"escor\"^\"bin\", \"StartServer.bat\");"
    :shortcuts (escor-server-shortcut))


(def-shortcut escor-server-shortcut
    :folder-name escor-shortcut-folder-name
    :application-display-name "Start e-SCOR Server"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\escor\\kbs\\e-scor.kb -nowindow"
    :icon-file "../escor/bin/e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

;;;
;;; Documentation components for ReThink, e-SCOR, and core G2
;;;
(def-component escor-documentation
  :parts (escor-documentation)
  :print-name "e-SCOR Documentation"
  :optional true)



(def-part escor-documentation
    :version :50r0
    :platforms ("nt")
    :source-ship-type :internal
    :destination-directory "doc/escor"
    :source-subdirectory "doc"
    :source escor
    :shortcuts (escor-documentation-quick escor-documentation-user escor-documentation-scor escor-tutorial))

(def-shortcut escor-documentation-quick
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "e-SCOR"
    :application-display-name "e-SCOR Quick Reference"
    :application-directory "doc/escor"
    :target-name "e-SCOR-Quick-Reference.pdf")

(def-shortcut escor-documentation-user
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "e-SCOR"
    :application-display-name "e-SCOR Users Guide"
    :application-directory "doc/escor"
    :target-name "e-SCOR-Users-Guide.pdf")

(def-shortcut escor-documentation-scor
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "e-SCOR"
    :application-display-name "SCOR Version 4.0"
    :application-directory "doc/escor"
    :target-name "SCOR-Version-4.0.pdf")

(def-shortcut escor-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "e-SCOR"
    :application-display-name "e-SCOR Tutorials"
    :application-directory "doc/escor"
    :target-name "e-SCOR-Tutorials.pdf")


