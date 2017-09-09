;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; ESCOR-FAMILY - escor Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduj, mhd, and PPrintz


;;; The current shipping version of e-SCOR is 2.1 Rev. 1 ("21r1").  The
;;; symbol :21r1 should be used generally for e-SCOR elements below.

(require "g2-52r0-family")			; G2 6.0r0
(provide "escor-21r1-family")

(def-family escor-21r1
    :index 9
    :file-syntax-version 10
    :print-name "escor"			; was "e-SCOR"! (MHD 5/1/01)
    :bundles (escor-standard escor-professional escor-professional-team-server escor-professional-team-client)
    :directory "escor"
    :guid "243D4BBB-9EE7-11D4-8111-00A02431D004" ; "2.1r1"
    :previous-versions (("2.1r0" "243D4BB8-9EE7-11D4-8111-00A02431D004")
			("2.0r0" "243D4BAE-9EE7-11D4-8111-00A02431D004")
			;; add more here
			)
    :splash-screen "escor-setup.bmp"
    :license-text "escor-license.txt"
    :platforms ("nt"))


;;; Evaluation OK Components

;;; NOTE: Only the evaluation OK is handled by the following form. The other
;;; OK components are done by hand for now.  Note that this differs slightly
;;; in terms of capabilities from e-SCOR professional: declared embedded
;;; (no local window) and has zero (0) floating Telewindows.  Note, too, that
;;; this form must preceed the def-bundle form, so it interacts with certain
;;; bundle dwimification (MHD). 

(def-g2-ok-components (escor :obfuscate t)
    escor "e-SCOR Professional"
  ((1 "-jun25-2001") (1 "-jul25-2001") (1 "-aug25-2001")
   (1 "-sep25-2001") (1 "-oct25-2001") (1 "-nov25-2001")
   (1 "-dec25-2001") (1 "-jan25-2002") (1 "-feb25-2002")
   (1 "-mar25-2002") (1 "-apr25-2002") (1 "-may25-2002")
   (1 "-jun25-2002") (1 "-jul25-2002") (1 "-aug25-2002")))


(def-bundle escor-standard
    :components (escor-client escor-server escor-documentation 
			      ;; These are the permanent OK components:
			      escor-standard-license)
    :print-name "e-SCOR Standard"
    :directory "escor"
    :version :21r1)


(def-bundle escor-professional
    :components (escor-client escor-server escor-documentation 
			      ;; These are the permanent OK components:
			      escor-professional-license
			      ;; This is the generated set of e-scor
			      ;; professional eval OK components:
			      escor-family-ok-components)
    :print-name "e-SCOR Professional"
    :directory "escor"
    :version :21r1)


(def-bundle escor-professional-team-server
    :components (escor-client escor-server escor-odbc escor-documentation 
			      ;; These are the permanent OK components:
				escor-odbc-license
			      escor-professional-team-server-license)
    :print-name "e-SCOR Professional Team Server"
    :directory "escor"
    :version :21r1)

(def-bundle escor-professional-team-client
    :components (escor-client escor-odbc escor-documentation 
			      ;; These are the permanent OK components:
				escor-odbc-license)
    :print-name "e-SCOR Professional Team Client"
    :directory "escor"
    :version :21r1)



;;;
;;; client components and parts
;;;
(def-component escor-client
  :print-name "e-SCOR Client"
  :parts (escor-readme escor-license escor-DLL escor-reports
	escor-client-binaries axl-binaries GSI-binaries javalink-binaries
	jre escor-classes javalink-classes sequoia-classes))

(def-component escor-odbc
  :print-name "e-SCOR ODBC Bridge"
  :parts (ODBC-binaries))


(def-part escor-readme
    :version :21r1 :source-ship-type :external
    :source-filename "readme.html"
    :source "escor"
    :print-name "e-SCOR README file"
    :shortcuts (readme))

(def-shortcut readme
    :folder-name "Gensym e-SCOR"
    :application-display-name "Readme"
    :application-directory ""
    :target-name "readme.html")

(def-part escor-license
    :version :21r1 :source-ship-type :external
    :source-filename "e-SCOR-license.doc"
    :source "escor")

(def-part escor-DLL
    :parent axl-g2com-dll
    :destination-directory "bin"
    :print-name "DLLs to register")


(def-part escor-reports
    :version :21r1 :source-ship-type :external
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("Default-Summary-Reports.xls"  "Tutorial-Simplest-Model-Summary-Reports.xls" "Tutorial-ACME-Summary-Reports.xls" "Tutorial-VMI-Summary-Reports.xls")
    :source "escor"
    :shortcuts (default-summary-reports-tutorial
		simplest-model-summary-reports-tutorial
		 acme-summary-report-tutorial
		 vmi-summary-report-tutorial))

(def-shortcut default-summary-reports-tutorial
    :folder-name "Gensym e-SCOR"
    :application-display-name "Default Summary Reports"
    :application-directory "kbs"
    :target-name "Default-Summary-Reports.xls")

(def-shortcut simplest-model-summary-reports-tutorial
    :folder-name "Gensym e-SCOR"
    :subfolder-name "Tutorial Solutions"
    :application-display-name "Simplest Model Summary Reports"
    :application-directory "kbs"
    :target-name "Tutorial-Simplest-Model-Summary-Reports.xls")

(def-shortcut acme-summary-report-tutorial
    :folder-name "Gensym e-SCOR"
    :subfolder-name "Tutorial Solutions"
    :application-display-name "ACME Summary Reports"
    :application-directory "kbs"
    :target-name "Tutorial-ACME-Summary-Reports.xls")

(def-shortcut vmi-summary-report-tutorial
    :folder-name "Gensym e-SCOR"
    :subfolder-name "Tutorial Solutions"
    :application-display-name "VMI Summary Reports"
    :application-directory "kbs"
    :target-name "Tutorial-VMI-Summary-Reports.xls")



(def-part escor-client-binaries
    :version :21r1 :source-ship-type :external
    :source-filename ("e-SCOR.ico"  "e-SCOR-Client.bat")
    :destination-directory "bin"
    :source "escor"
    :source-subdirectory "bin"
    :shortcuts (escor-client-shortcut)
    :environment-variables (escor_home_v2))

(def-shortcut escor-client-shortcut
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Client"
    :application-directory "bin"
    :target-name "e-SCOR-Client.bat"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-environment-variable escor_home_v2 :value "<TARGETDIR>")


(def-part axl-binaries
    :version :10r1-DF12
    :source axl
    :source-filename ("regsvr32.exe" "G2Com.dll")
    :destination-directory "bin")

(def-part ODBC-binaries
    :version :60r4-DE18
    :source g2odbc
    :source-filename ("g2-odbc.exe" "inst_g2odbc_trigs.sql" "deinst_g2odbc_trigs.sql" "inst_mssql7_trigs.sql")
    :shortcuts (odbc-shortcut)
    :destination-directory "bin"
    :environment-variables (gsi_root))

(def-environment-variable gsi_root :value "<TARGETDIR>\\\\odbc")


(def-shortcut odbc-shortcut
    :folder-name "Gensym e-SCOR"
    :application-display-name "ODBC Bridge"
    :application-directory "bin"
    :target-name "g2-odbc.exe"
    :icon-index 0
    :run-style minimized)

(def-part GSI-binaries
    :version :60r0
    :source gsi
    :source-filename "gsi.dll"
    :destination-directory "bin")

(def-part javalink-binaries
    :version :12r0
    :source jvl
    :source-subdirectory "components/bin"
    :source-filename "JgiInterface.dll"
    :destination-directory "bin")



(def-part escor-classes
    :version :21r1 :source-ship-type :external
    :source "escor"
    :source-subdirectory "classes"
    :source-filename ("escor.jar" "generic-uitools.jar" "jh.jar" "jhall.jar" "jhtools.jar" "jsearch.jar" "ntw-uitools.jar")
    :destination-directory "classes")


(def-part javalink-classes
    :version :12r0
    :source jvl
    :source-subdirectory "components/classes"
    :source-filename ("core.jar" "javalink.jar" "classtools.jar")
    :destination-directory "classes")


(def-part sequoia-classes
    :version :12r0
    :source tw2
    :source-subdirectory "components/classes"
    :destination-directory "classes"
    :source-filename ("coreui.jar" "sequoia.jar"))


;;;
;;; server parts
;;;
;;; NOTE: removed g2-database-KB for now and made it part of escor promote
;;; The reason is that the promoted kb has a revision mismatch compared to
;;; the bridges. Therefore the bridges will abort immediatly when started.
;;;
(def-component escor-server
  :print-name "e-SCOR Server"
  :parts (
	g2-com-KB escor-kbs escor-G2-Kbs images
	escor-server-binaries
	g2-exe-intelnt-escor g2passwd-exe-intelnt ext-directory
	g2-gen16ut-dll-intelnt g2-gen32-dll-intelnt g2-gen32ut-dll-intelnt))


(def-part G2-database-KB
    :source g2odbc
    :version :60r4-DE18
    :source-filename "g2-database.kb"
    :destination-directory "kbs")

(def-part G2-com-KB
    :source axl
    :version :10r1-DF12
    :source-filename "g2com.kb"
    :destination-directory "kbs")

(def-part escor-kbs
    :version :21r1 :source-ship-type :external
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("g2-database.kb" "aero.kb" "bpr.kb" "bprui.kb" "chapter3.kb" "customiz.kb" "eSCOR.kb" "escor-bom.kb" "escor-customiz.kb" "escor-definitions.kb" "escor-demos.kb" "escor-examples-eto.kb" "escor-examples-misc.kb" "escor-examples-mto.kb" "escor-examples-pull.kb" "escor-examples-push.kb" "escor-upgrade.kb" "methods.kb" "menus.kb" "orderful.kb" "Tutorial-ACME.kb" "Tutorial-Simplest-Model.kb" "Tutorial-VMI.kb" "aeroscrt.txt") 
    :source "escor"
    :shortcuts (simplest-model-tutorial
		 acme-tutorial
		 vmi-tutorial))

(def-shortcut simplest-model-tutorial
    :folder-name "Gensym e-SCOR"
    :subfolder-name "Tutorial Solutions"
    :application-display-name "Simplest Model"
    :application-directory "bin"
    :target-name "e-SCOR-Server.bat"
    :parameters "Tutorial-Simplest-Model.kb"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)


(def-shortcut acme-tutorial
    :folder-name "Gensym e-SCOR"
    :subfolder-name "Tutorial Solutions"
    :application-display-name "ACME"
    :application-directory "bin"
    :target-name "e-SCOR-Server.bat"
    :parameters "Tutorial-ACME.kb"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)


(def-shortcut vmi-tutorial
    :folder-name "Gensym e-SCOR"
    :subfolder-name "Tutorial Solutions"
    :application-display-name "VMI"
    :application-directory "bin"
    :target-name "e-SCOR-Server.bat"
    :parameters "Tutorial-VMI.kb"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-part images
    :version :21r1 :source-ship-type :external
    :destination-directory "kbs/images"
    :source-subdirectory "kbs/images"
    :source "escor")

(def-part escor-G2-kbs
    :version :60r0
    :source-filename ("g2uifile.kb" "gfr.kb" "gms.kb" "gold.kb" "goldui.kb" "gxl.kb" "sys-mod.kb"
				    "uil.kb" "uilcombo.kb" "uildefs.kb" "uillib.kb" "uilroot.kb" "uilsa.kb"
				    "uilslide.kb" "uiltdlg.kb" "jiscodes.kl"
				    "kscodes.kl" "japanese.kl" "korean.kl" "language.kl")
    :source kbs
    :source-subdirectory "utils"
    :destination-directory "kbs"
    :indep t)

(def-part g2-exe-intelnt-escor
    :version :21r1 :source-ship-type :external
    :destination-directory "g2"
    :source-subdirectory "g2"
    :source-filename ("g2.exe") 
    :source "escor")
;;; removed for 2.1r1 to use G2 6.0r0 patch with memory leak fix in sys proc for animation
;;;    :parent g2-exe-intelnt
;;;    :environment-variables :delete
;;    :shortcuts :delete)


(def-part escor-server-binaries
    :version :21r1 :source-ship-type :external
    :source-filename ("e-SCOR-Server.bat")
    :destination-directory "bin"
    :source "escor"
    :source-subdirectory "bin"
    :shortcuts (escor-server-shortcut))


(def-shortcut escor-server-shortcut
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Server"
    :application-directory "bin"
    :target-name "e-SCOR-Server.bat"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)



;;;
;;; Documentation component
;;;
(def-component escor-documentation
  :parts (escor-documentation)
  :print-name "e-SCOR Documentation"
  :optional true)

(def-part escor-documentation
    :version :21r1 :source-ship-type :external
    :destination-directory "docs"
    :source-subdirectory "docs"
    :source escor
    :shortcuts (escor-documentation-quick
		 escor-documentation-user
		 escor-documentation-scor
		 escor-tutorial))

(def-shortcut escor-documentation-quick
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Quick Reference"
    :application-directory "docs"
    :target-name "e-SCOR-Quick-Reference.pdf")

(def-shortcut escor-documentation-user
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Users Guide"
    :application-directory "docs"
    :target-name "e-SCOR-Users-Guide.pdf")

(def-shortcut escor-documentation-scor
    :folder-name "Gensym e-SCOR"
    :application-display-name "SCOR Version 4.0"
    :application-directory "docs"
    :target-name "SCOR-Version-4.0.pdf")

(def-shortcut escor-tutorial
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Tutorials"
    :application-directory "docs"
    :target-name "e-SCOR-Tutorials.pdf")



;;;; OK Files

;;
;; licensed components. We are always installing the client
;; on a server
;;


;; Standard.

(def-component escor-standard-license
  :print-name "e-SCOR Standard Authorization"
  :parts (escor-standard-ok)
  :watermark "g2/g2.ok"
  :radio-button-group-index 1)

(def-part escor-standard-ok
    :destination-directory "g2"
    :destination-filename "g2.ok"
    :indep t
    :source "/home/development/installers/release-files"
    :source-filename "e-scor-standard.ok"
    :obfuscate t)




;; Professional.

(def-component escor-professional-license
  :print-name "e-SCOR Professional Authorization"
  :parts (escor-professional-ok)
  :watermark "g2/g2.ok"
  :radio-button-group-index 1)

(def-part escor-professional-ok
    :destination-directory "g2"
    :destination-filename "g2.ok"
    :indep t
    :source "/home/development/installers/release-files"
    :source-filename "e-scor-professional.ok"
    :obfuscate t)



;; Professional Team Server.

(def-component escor-professional-team-server-license
  :print-name "e-SCOR Professional Team Server Authorization"
  :parts (escor-professional-team-ok)
  :watermark "g2/g2.ok"
  :radio-button-group-index 1
  :optional false)


(def-part escor-professional-team-ok
    :destination-directory "g2"
    :destination-filename "g2.ok"
    :indep t
    :source "/home/development/installers/release-files"
    :source-filename "e-scor-professional-team.ok"
    :obfuscate t)

(def-component escor-odbc-license
  :print-name "e-SCOR ODBC Bridge Authorization"
  :parts (gsi-ODBC-ok gsi-ODBC-blank-ok) :platforms ("nt")
  :optional false)
