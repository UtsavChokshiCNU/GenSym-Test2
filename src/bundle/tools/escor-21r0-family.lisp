;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; ESCOR-FAMILY - escor Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduj, mhd, and PPrintz


;;; The current shipping version of e-SCOR is 2.1 Rev. 0 ("21r0").  The
;;; symbol :21r0 should be used generally for e-SCOR elements below.

(require "g2-family")			; G2 5.1r7
(provide "escor-21r0-family")

(def-family escor-21r0
    :index 3
    :file-syntax-version 10
    :print-name "escor"			; was "e-SCOR"! (MHD 5/1/01)
    :bundles (escor)
    :directory "escor"
    :guid "243D4BB8-9EE7-11D4-8111-00A02431D004" ; "2.1r0"
    :previous-versions (("2.0r0" "243D4BAE-9EE7-11D4-8111-00A02431D004")
			;; add more here
			)
    :splash-screen "escor-setup.bmp"
    :platforms ("nt"))

(def-bundle escor
    :components (escor-client escor-documentation escor-standard escor-professional escor-professional-team-server escor-professional-team-client)
    :print-name "e-SCOR"
    :directory "escor"
    :version :21r0)


;;;
;;; client components and parts
;;;
(def-component escor-client
  :print-name "e-SCOR Core"
  :parts (escor-readme escor-DLL escor-reports
	escor-client-binaries ODBC-binaries axl-binaries GSI-binaries javalink-binaries
	jre escor-classes javalink-classes sequoia-classes))


(def-part escor-readme
    :version :21r0-DE17 :source-ship-type :internal
    :source-filename "readme.html"
    :source "escor"
    :print-name "e-SCOR README file"
    :shortcuts (readme))

(def-shortcut readme
    :folder-name "Gensym e-SCOR"
    :application-display-name "Readme"
    :application-directory ""
    :target-name "readme.html")

(def-part escor-DLL
    :parent axl-g2com-dll
    :destination-directory "Bin"
    :print-name "DLLs to register")


(def-part escor-reports
    :version :21r0-DE17 :source-ship-type :internal
    :destination-directory "Kbs"
    :source-subdirectory "Kbs"
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
    :version :21r0-DE17 :source-ship-type :internal
    :source-filename ("e-SCOR.ico"  "e-SCOR-Client.bat")
    :destination-directory "Bin"
    :source "escor"
    :source-subdirectory "Bin"
    :shortcuts (escor-client-shortcut)
    :environment-variables (escor_home_v2))

(def-shortcut escor-client-shortcut
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Client"
    :application-directory "Bin"
    :target-name "e-SCOR-Client.bat"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-environment-variable escor_home_v2 :value "<TARGETDIR>")


(def-part axl-binaries
    :version :10r1-CF05
    :source axl
    :source-filename ("regsvr32.exe" "G2Com.dll")
    :destination-directory "Bin")

(def-part ODBC-binaries
    :version :60r4
    :source g2odbc
    :source-filename "g2-odbc.exe"
    :destination-directory "Bin")

(def-part GSI-binaries
    :version :51r7
    :source gsi
    :source-filename "gsi.dll"
    :destination-directory "Bin")

(def-part javalink-binaries
    :version :11r0
    :source jvl
    :source-subdirectory "components/bin"
    :source-filename "JgiInterface.dll"
    :destination-directory "Bin")



(def-part escor-classes
    :version :21r0-DE17 :source-ship-type :internal
    :source "escor"
    :source-subdirectory "Classes"
    :source-filename ("escor.jar" "generic-uitools.jar" "jh.jar" "jhall.jar" "jhtools.jar" "jsearch.jar" "ntw-uitools.jar" "patches.jar" "rethink.jar")
    :destination-directory "Classes")


(def-part javalink-classes
    :version :11r0
    :source jvl
    :source-subdirectory "components/classes"
    :source-filename ("core.jar" "javalink.jar" "classtools.jar")
    :destination-directory "Classes")


(def-part sequoia-classes
    :version :11r0
    :source tw2
    :source-subdirectory "components/classes"
    :destination-directory "Classes"
    :source-filename ("coreui.jar" "sequoia.jar"))


;;;
;;; server parts
;;;

(def-part G2-database-KB
    :source g2odbc
    :version :60r4
    :source-filename "g2-database.kb"
    :destination-directory "Kbs")

(def-part G2-com-KB
    :source axl
    :version :10r1-CF05
    :source-filename "g2com.kb"
    :destination-directory "Kbs")

(def-part escor-kbs
    :version :21r0-DE17 :source-ship-type :internal
    :destination-directory "Kbs"
    :source-subdirectory "Kbs"
    :source-filename ("aero.kb" "bpr.kb" "bprui.kb" "chapter3.kb" "customiz.kb" "eSCOR.kb" "escor-bom.kb" "escor-customiz.kb" "escor-definitions.kb" "escor-demos.kb" "escor-examples-eto.kb" "escor-examples-misc.kb" "escor-examples-mto.kb" "escor-examples-pull.kb" "escor-examples-push.kb" "escor-upgrade.kb" "methods.kb" "menus.kb" "orderful.kb" "Tutorial-ACME.kb" "Tutorial-Simplest-Model.kb" "Tutorial-VMI.kb" "aeroscrt.txt") 
    :source "escor"
    :shortcuts (simplest-model-tutorial
		 acme-tutorial
		 vmi-tutorial))

(def-shortcut simplest-model-tutorial
    :folder-name "Gensym e-SCOR"
    :subfolder-name "Tutorial Solutions"
    :application-display-name "Simplest Model"
    :application-directory "Bin"
    :target-name "e-SCOR-Server.bat"
    :parameters "Tutorial-Simplest-Model.kb"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)


(def-shortcut acme-tutorial
    :folder-name "Gensym e-SCOR"
    :subfolder-name "Tutorial Solutions"
    :application-display-name "ACME"
    :application-directory "Bin"
    :target-name "e-SCOR-Server.bat"
    :parameters "Tutorial-ACME.kb"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)


(def-shortcut vmi-tutorial
    :folder-name "Gensym e-SCOR"
    :subfolder-name "Tutorial Solutions"
    :application-display-name "VMI"
    :application-directory "Bin"
    :target-name "e-SCOR-Server.bat"
    :parameters "Tutorial-VMI.kb"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)



(def-part escor-G2-kbs
    :version :51r7
    :source-filename ("g2uifile.kb" "gfr.kb" "gms.kb" "gold.kb" "goldui.kb" "gxl.kb" "sys-mod.kb"
				    "uil.kb" "uilcombo.kb" "uildefs.kb" "uillib.kb" "uilroot.kb" "uilsa.kb"
				    "uilslide.kb" "uiltdlg.kb"  "gbcodes.kl" "jiscodes.kl"
				    "kscodes.kl" "japanese.kl" "korean.kl" "language.kl")
    :source kbs
    :source-subdirectory "utils"
    :destination-directory "Kbs"
    :indep t)

(def-part world-gif
    :version :51r7
    :source-filename "world.gif"
    :source kbs
    :source-subdirectory "tutors"
    :destination-directory "Kbs/Images"
    :indep t)


(def-part g2-exe-intelnt-escor
    :parent g2-exe-intelnt
    :environment-variables :delete
    :shortcuts :delete)


(def-part escor-server-binaries
    :version :21r0-DE17 :source-ship-type :internal
    :source-filename ("e-SCOR-Server.bat")
    :destination-directory "Bin"
    :source "escor"
    :source-subdirectory "Bin"
    :shortcuts (escor-server-shortcut))


(def-shortcut escor-server-shortcut
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Server"
    :application-directory "Bin"
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
    :version :21r0-DE17 :source-ship-type :internal
    :destination-directory "Docs"
    :source-subdirectory "Docs"
    :source escor
    :shortcuts (escor-documentation-quick
		 escor-documentation-user
		 escor-documentation-scor
		 escor-tutorial))

(def-shortcut escor-documentation-quick
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Quick Reference"
    :application-directory "Docs"
    :target-name "e-SCOR-Quick-Reference.pdf")

(def-shortcut escor-documentation-user
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Users Guide"
    :application-directory "Docs"
    :target-name "e-SCOR-Users-Guide.pdf")

(def-shortcut escor-documentation-scor
    :folder-name "Gensym e-SCOR"
    :application-display-name "SCOR Version 4.0"
    :application-directory "Docs"
    :target-name "SCOR-Version-4.0.pdf")

(def-shortcut escor-tutorial
    :folder-name "Gensym e-SCOR"
    :application-display-name "e-SCOR Tutorials"
    :application-directory "Docs"
    :target-name "e-SCOR-Tutorials.pdf")




;;
;; licensed components. We are always installing the client
;; on a server
;;
(def-component escor-standard
  :print-name "e-SCOR Standard Authorization"
  :parts (escor-standard-ok
	g2-database-KB g2-com-KB escor-kbs escor-G2-Kbs world-gif 
	escor-server-binaries
	g2-exe-intelnt-escor g2passwd-exe-intelnt ext-directory
	g2-gen16ut-dll-intelnt g2-gen32-dll-intelnt g2-gen32ut-dll-intelnt)
  :watermark "g2/g2.ok"
  :radio-button-group-index 1)

(def-part escor-standard-ok
    :destination-directory "g2"
    :destination-filename "g2.ok"
    :indep t
    :source "/home/development/installers/release-files"
    :source-filename "e-scor-standard.ok")



(def-component escor-professional
  :print-name "e-SCOR Professional Authorization"
  :parts (escor-professional-ok
	g2-database-KB g2-com-KB escor-kbs escor-G2-Kbs world-gif 
	escor-server-binaries
	g2-exe-intelnt-escor g2passwd-exe-intelnt ext-directory
	g2-gen16ut-dll-intelnt g2-gen32-dll-intelnt g2-gen32ut-dll-intelnt)
  :watermark "g2/g2.ok"
  :radio-button-group-index 1)

(def-part escor-professional-ok
    :destination-directory "g2"
    :destination-filename "g2.ok"
    :indep t
    :source "/home/development/installers/release-files"
    :source-filename "e-scor-professional.ok")



(def-component escor-professional-team-server
  :print-name "e-SCOR Professional Team Server Authorization"
  :parts (escor-professional-ok
	g2-database-KB g2-com-KB escor-kbs escor-G2-Kbs world-gif 
	escor-server-binaries
	g2-exe-intelnt-escor g2passwd-exe-intelnt ext-directory
	g2-gen16ut-dll-intelnt g2-gen32-dll-intelnt g2-gen32ut-dll-intelnt)
  :watermark "g2/g2.ok"
  :radio-button-group-index 1)



(def-component escor-professional-team-client
  :print-name "e-SCOR Professional Team Client Authorization"
  :parts (escor-professional-ok)
  :watermark "g2/g2.ok"
  :radio-button-group-index 1)

