;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; ESCOR-FAMILY - escor Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduj, mhd, and PPrintz


;;; The current shipping version of e-SCOR is 4.0 Rev. 3("40r3").  The
;;; symbol :40r3 should be used generally for e-SCOR / ReThink elements below.

(defvar g2-shortcut-folder-name "Gensym e-SCOR & ReThink 4.0r3")
(defvar escor-shortcut-folder-name "Gensym e-SCOR & ReThink 4.0r3")

(require "g2-62r2-family")
(provide "escor-40r3-family")

(def-family escor-40r3
    :index 18
    :file-syntax-version 10
    :print-name "eSCOR_ReThink"
    :bundles (escor-offline escor-online escor-online-client
		  rethink-offline rethink-online rethink-online-client)
    :directory "escor_rethink-4.0r3"
    :guid "83B0DEEF-70A4-4339-82C9-290058CA0E29"
    :previous-versions (("4.0r2" "CCD24411-CF01-4661-BAA0-90E52E487142")
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

(def-g2-ok-components (rethink-offline :obfuscate t) rethink-offline "ReThink Offline"
  (1
     (1 "-dec25-2002")
     (1 "-jan25-2003") (1 "-feb25-2003") (1 "-mar25-2003")
     (1 "-apr25-2003") (1 "-may25-2003") (1 "-jun25-2003")
     (1 "-jul25-2003") (1 "-aug25-2003") (1 "-sep25-2003")
     (1 "-oct25-2003") (1 "-nov25-2003") (1 "-dec25-2003")
     (1 "-jan25-2004") (1 "-feb25-2004") (1 "-mar25-2004")
     (1 "-apr25-2004") (1 "-may25-2004")))

(def-g2-ok-components (rethink-online :obfuscate t) rethink-online "ReThink Online"
  (1 2 3 4 5 6 7 8
     (1 "-dec25-2002")
     (1 "-jan25-2003") (1 "-feb25-2003") (1 "-mar25-2003")
     (1 "-apr25-2003") (1 "-may25-2003") (1 "-jun25-2003")
     (1 "-jul25-2003") (1 "-aug25-2003") (1 "-sep25-2003")
     (1 "-oct25-2003") (1 "-nov25-2003") (1 "-dec25-2003")
     (1 "-jan25-2004") (1 "-feb25-2004") (1 "-mar25-2004")
     (1 "-apr25-2004") (1 "-may25-2004")))


(def-g2-ok-components (escor-offline :obfuscate t) escor-offline "e-SCOR Offline"
  (1
     (1 "-dec25-2002")
     (1 "-jan25-2003") (1 "-feb25-2003") (1 "-mar25-2003")
     (1 "-apr25-2003") (1 "-may25-2003") (1 "-jun25-2003")
     (1 "-jul25-2003") (1 "-aug25-2003") (1 "-sep25-2003")
     (1 "-oct25-2003") (1 "-nov25-2003") (1 "-dec25-2003")
     (1 "-jan25-2004") (1 "-feb25-2004") (1 "-mar25-2004")
     (1 "-apr25-2004") (1 "-may25-2004")))

(def-g2-ok-components (escor-online :obfuscate t) escor-online "e-SCOR Online"
  (1 2 3 4 5 6 7 8
     (1 "-dec25-2002")
     (1 "-jan25-2003") (1 "-feb25-2003") (1 "-mar25-2003")
     (1 "-apr25-2003") (1 "-may25-2003") (1 "-jun25-2003")
     (1 "-jul25-2003") (1 "-aug25-2003") (1 "-sep25-2003")
     (1 "-oct25-2003") (1 "-nov25-2003") (1 "-dec25-2003")
     (1 "-jan25-2004") (1 "-feb25-2004") (1 "-mar25-2004")
     (1 "-apr25-2004") (1 "-may25-2004")))





;;;
;;; Specifications of the different bundles
;;;

(def-bundle escor-offline
    :components (core-runtime-client rethink-client escor-client escor-offline-client jre
			core-runtime-server rethink-server escor-server gservice
			escor-documentation rethink-documentation
			;; These are the OK components:
			escor-offline-family-ok-components)
    :print-name "e-SCOR Offline"
    :directory "escor"
    :version :40r3)


(def-bundle escor-online
    :components (core-runtime-client rethink-client escor-client escor-online-client jre
			core-runtime-server rethink-server rethink-online-server escor-server
			g2-escor telewindows telewindows2 javalink gateway protools 
			weblink escor-activexlink corbalink opclink Oraclebridge Sybasebridge ODBCbridge gservice
			escor-documentation rethink-documentation development-documentation
			dev-g2-readme
			;; These are the OK components:
			escor-online-family-ok-components)
    :print-name "e-SCOR Online"
    :directory "escor"
    :version :40r3)

(def-bundle escor-online-client
    :components (core-runtime-client rethink-client escor-client escor-online-client jre
			escor-documentation rethink-documentation)
    :print-name "e-SCOR Online Client Only"
    :directory "escor"
    :version :40r3)




(def-bundle rethink-offline
    :components (core-runtime-client rethink-client rethink-offline-client jre
			core-runtime-server rethink-server gservice
			rethink-documentation 
			;; These are the OK components:
			rethink-offline-family-ok-components)
    :print-name "ReThink Offline"
    :directory "escor"
    :version :40r3)


(def-bundle rethink-online
    :components (core-runtime-client rethink-client rethink-online-client jre
			core-runtime-server rethink-server rethink-online-server
			g2-escor telewindows telewindows2 javalink gateway protools 
			weblink escor-activexlink corbalink opclink Oraclebridge Sybasebridge ODBCbridge gservice
			rethink-documentation development-documentation
			dev-g2-readme
			;; These are the OK components:
			rethink-online-family-ok-components)
    :print-name "ReThink Online"
    :directory "escor"
    :version :40r3)

(def-bundle rethink-online-client
    :components (core-runtime-client rethink-client rethink-online-client jre
			rethink-documentation)
    :print-name "ReThink Online Client Only"
    :directory "escor"
    :version :40r3)



;;;
;;; ReThink client components and parts
;;;
(def-component rethink-client
  :print-name "ReThink Client"
  :parts (rethink-readme rethink-client-binaries core-client-classes rethink-reports)
  :optional false)


(def-part rethink-readme
    :version :40r3
    :source-ship-type :external
    :source-filename "ReThink-readme.html"
    :source "escor"
    :print-name "ReThink README file"
    :shortcuts (rethink-readme-shortcut))

(def-shortcut rethink-readme-shortcut
    :folder-name escor-shortcut-folder-name
    :application-display-name "Readme for ReThink"
    :application-directory ""
    :target-name "ReThink-readme.html")



(def-part rethink-client-binaries
    :version :40r3
    :source-ship-type :external
    :source-filename ("Client.bat")
    :destination-directory "bin"
    :source "escor"
    :source-subdirectory "bin"
    :shortcuts (rethink-client-shortcut)
;;;    :environment-variables (ESCOR_RETHINK_HOME)
    :postinstall-code "replace_rootdir(\"bin\", \"Client.bat\");")

(def-shortcut rethink-client-shortcut
    :folder-name escor-shortcut-folder-name
    :application-display-name "Client"
    :application-directory "bin"
    :target-name "Client.bat"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)


;;;(def-environment-variable ESCOR_RETHINK_HOME :value "<TARGETDIR>")

(def-part jmail-binaries
    :version :40r3
    :source-ship-type :external
    :source-filename ("StartJMailBridge.bat")
    :destination-directory "bin"
    :source "escor"
    :source-subdirectory "bin"
    :shortcuts (jmail-client-shortcut)
    :postinstall-code "replace_rootdir(\"bin\", \"StartJMailBridge.bat\");")

(def-shortcut jmail-client-shortcut
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 JMail Bridge"
    :application-directory "bin"
    :target-name "StartJMailBridge.bat"
    :icon-index 0
    :run-style minimized)


(def-part online-client-classes
    :version :40r3
    :source-ship-type :external
    :source "escor"
    :source-subdirectory "classes"
    :source-filename ("activation.jar" "mail.jar" "jmail.jar")
    :destination-directory "classes")



(def-part core-client-classes
    :version :40r3
    :source-ship-type :external
    :source "escor"
    :source-subdirectory "classes"
    :source-filename ("escor-rethink.jar" "generic-uitools.jar" "jh.jar" "jhall.jar" "jsearch.jar" "ntw-uitools.jar")
    :destination-directory "classes")

(def-part rethink-reports
    :version :40r3
    :source-ship-type :external
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("ReThink-Summary-Reports.xls")
    :source "escor"
    :shortcuts (rethink-default-summary-reports))

(def-shortcut rethink-default-summary-reports
    :folder-name escor-shortcut-folder-name
    :application-display-name "ReThink Default Summary Reports"
    :application-directory "kbs"
    :target-name "ReThink-Summary-Reports.xls")



(def-part default-icons
    :version :40r3
    :source-ship-type :external
    :source-filename ("splash.jpg" "logo.gif" "logo.ico")
    :source-subdirectory "bin"
    :destination-directory "bin"
    :source "escor"
    :print-name "Icons")

(def-component rethink-offline-client
  :print-name "ReThink Offline Client"
  :parts (rethink-offline-splash rethink-product-icon rethink-product-logo)
  :optional false)


(def-component rethink-online-client
  :print-name "ReThink Online Client"
  :parts (rethink-online-splash rethink-product-icon rethink-product-logo online-client-classes jmail-binaries)
  :optional false)


(def-part rethink-offline-splash
    :version :40r3
    :source-ship-type :external
    :source-filename "rethink_offline_splash.jpg"
    :source-subdirectory "bin"
    :destination-filename "splash.jpg"
    :destination-directory "bin"
    :source "escor"
    :print-name "ReThink Offline Splash Screen")


(def-part rethink-online-splash
    :version :40r3
    :source-ship-type :external
    :source-filename "rethink_online_splash.jpg"
    :source-subdirectory "bin"
    :destination-filename "splash.jpg"
    :destination-directory "bin"
    :source "escor"
    :print-name "ReThink Online Splash Screen")

(def-part rethink-product-icon
    :version :40r3
    :source-ship-type :external
    :source-filename "ReThink.ico"
    :source-subdirectory "bin"
    :destination-filename "logo.ico"
    :destination-directory "bin"
    :source "escor"
    :print-name "ReThink Product Icon")

(def-part rethink-product-logo
    :version :40r3
    :source-ship-type :external
    :source-filename "rethink_logo.gif"
    :source-subdirectory "bin"
    :destination-filename "logo.gif"
    :destination-directory "bin"
    :source "escor"
    :print-name "ReThink Product Logo")




;;;
;;; e-SCOR client components and parts
;;;
(def-component escor-client
  :print-name "e-SCOR Client"
  :parts (escor-readme escor-reports)
  :optional false)



(def-part escor-readme
    :version :40r3
    :source-ship-type :external
    :source-filename "e-SCOR-readme.html"
    :source "escor"
    :print-name "e-SCOR README file"
    :shortcuts (escor-readme-shortcut))

(def-shortcut escor-readme-shortcut
    :folder-name escor-shortcut-folder-name
    :application-display-name "Readme for e-SCOR"
    :application-directory ""
    :target-name "e-SCOR-readme.html")



(def-part escor-reports
    :version :40r3
    :source-ship-type :external
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("Default-Summary-Reports.xls"  "Tutorial-Simplest-Model-Summary-Reports.xls" "Tutorial-ACME-Summary-Reports.xls" "Tutorial-VMI-Summary-Reports.xls")
    :source "escor"
    :shortcuts (escor-default-summary-reports
		 simplest-model-summary-reports-tutorial
		 acme-summary-report-tutorial
		 vmi-summary-report-tutorial))

(def-shortcut escor-default-summary-reports
    :folder-name escor-shortcut-folder-name
    :application-display-name "e-SCOR Default Summary Reports"
    :application-directory "kbs"
    :target-name "Default-Summary-Reports.xls")

(def-shortcut simplest-model-summary-reports-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "Simplest Model Summary Reports"
    :application-directory "kbs"
    :target-name "Tutorial-Simplest-Model-Summary-Reports.xls")

(def-shortcut acme-summary-report-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "ACME Summary Reports"
    :application-directory "kbs"
    :target-name "Tutorial-ACME-Summary-Reports.xls")

(def-shortcut vmi-summary-report-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "VMI Summary Reports"
    :application-directory "kbs"
    :target-name "Tutorial-VMI-Summary-Reports.xls")




(def-component escor-offline-client
  :print-name "e-SCOR Offline Client"
  :parts (escor-offline-splash escor-product-icon escor-product-logo)
  :optional false)


(def-component escor-online-client
  :print-name "e-SCOR Online Client"
  :parts (escor-online-splash escor-product-icon escor-product-logo online-client-classes jmail-binaries)
  :optional false)



(def-part escor-offline-splash
    :version :40r3
    :source-ship-type :external
    :source-filename "escor_offline_splash.jpg"
    :source-subdirectory "bin"
    :destination-filename "splash.jpg"
    :destination-directory "bin"
    :source "escor"
    :print-name "e-SCOR Offline Splash Screen")

(def-part escor-online-splash
    :version :40r3
    :source-ship-type :external
    :source-filename "escor_online_splash.jpg"
    :source-subdirectory "bin"
    :destination-filename "splash.jpg"
    :destination-directory "bin"
    :source "escor"
    :print-name "e-SCOR Online Splash Screen")

(def-part escor-product-icon
    :version :40r3
    :source-ship-type :external
    :source-filename "e-SCOR.ico"
    :source-subdirectory "bin"
    :destination-filename "logo.ico"
    :destination-directory "bin"
    :source "escor"
    :print-name "e-SCOR Product Icon")

(def-part escor-product-logo
    :version :40r3
    :source-ship-type :external
    :source-filename "escor_logo.gif"
    :source-subdirectory "bin"
    :destination-filename "logo.gif"
    :destination-directory "bin"
    :source "escor"
    :print-name "e-SCOR Product Logo")



;;
;; core G2, TW2, etc components for basic versions
;;
(def-component core-runtime-client
  :print-name "Core Runtime Client"
  :parts (default-icons 
	axl-g2com-dll axl-gsi-dll axl-runme-bat axl-regsvr
	runtime-GSI-binaries
	runtime-javalink-binaries runtime-javalink-classes
	runtime-sequoia-classes jre)
  :optional false)




(def-part runtime-GSI-binaries
    :version :62r2
    :source-ship-type :external
    :source gsi
    :source-filename "gsi.dll"
    :destination-directory "gsi")


(def-part runtime-javalink-binaries
    :version :12r4
    :source jvl
    :source-ship-type :external
    :source-subdirectory "components/bin"
    :source-filename "JgiInterface.dll"
    :destination-directory "javalink/bin")


(def-part runtime-javalink-classes
    :version :12r4
    :source jvl
    :source-ship-type :external
    :source-subdirectory "components/classes"
    :source-filename ("core.jar" "javalink.jar" "classtools.jar")
    :destination-directory "javalink/classes")


(def-part runtime-sequoia-classes
    :version :12r4
    :source tw2
    :source-ship-type :external
    :source-subdirectory "components/classes"
    :destination-directory "tw2/classes"
    :source-filename ("coreui.jar" "sequoia.jar"))



;;;
;;; server parts
;;;

;;
;; rethink server
;;
(def-component rethink-server
  :print-name "ReThink Server"
  :parts (rethink-kbs rethink-server-binaries images)
  :optional false)




(def-part rethink-kbs
    :version :40r3
    :source-ship-type :external
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("rethink.kb" "aero.kb" "bpr.kb" "bprui.kb" "chapter3.kb" "customiz.kb" "methods.kb" "menus.kb" "orderful.kb" "rethink-40-doc-examples.kb" "customizing-rethink-examples.kb") 
    :source "escor"
    :shortcuts (aero-tutorial orderful-tutorial chapter3-tutorial rethink-40-tutorial rethink-customization-tutorial))

(def-shortcut rethink-customization-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "Customizing ReThink Examples"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "customizing-rethink-examples.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut rethink-40-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "ReThink 4.0 Examples"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "rethink-40-doc-examples.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut aero-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "Aero Model"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "aero.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut chapter3-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "Chapter3 Model"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "chapter3.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut orderful-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "Orderful Model"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "orderful.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)



(def-part images
    :version :40r3
    :source-ship-type :external
    :destination-directory "kbs/images"
    :source-subdirectory "kbs/images"
    :source "escor")


(def-part rethink-server-binaries
    :version :40r3
    :source-ship-type :external
    :source-filename ("Server.bat")
    :destination-directory "bin"
    :source "escor"
    :source-subdirectory "bin"
    :postinstall-code "replace_rootdir(\"bin\", \"Server.bat\");"
    :shortcuts (rethink-server-shortcut))


(def-shortcut rethink-server-shortcut
    :folder-name escor-shortcut-folder-name
    :application-display-name "Server"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "rethink.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)



(def-component rethink-online-server
  :print-name "ReThink Online Server"
  :parts ( rethink-online-kbs )
  :optional false)



(def-part rethink-online-kbs
    :version :40r3
    :source-ship-type :external
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("rethink-online.kb" "methods-online.kb" "jmail.kb" "rethink-40-online-examples.kb" "orders.mdb")
    :source "escor"
    :shortcuts (rethink-online-examples))


(def-shortcut rethink-online-examples
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "ReThink 4.0 Online Examples"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "rethink-40-online-examples.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)



;;
;; e-SCOR server
;;
(def-component escor-server
  :print-name "e-SCOR Server"
  :parts (escor-kbs)
  :optional false)



(def-part escor-kbs
    :version :40r3
    :source-ship-type :external
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("eSCOR.kb" "escor-bom.kb" "escor-customiz.kb" "escor-definitions.kb" "escor-demos.kb" "escor-examples-eto.kb" "escor-examples-misc.kb" "escor-examples-mto.kb" "escor-examples-pull.kb" "escor-examples-push.kb" "escor-upgrade.kb" "Tutorial-ACME.kb" "Tutorial-Simplest-Model.kb" "Tutorial-VMI.kb") 
    :source "escor"
    :shortcuts (simplest-model-tutorial acme-tutorial vmi-tutorial))

(def-shortcut simplest-model-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "Simplest Model"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "Tutorial-Simplest-Model.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut acme-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "ACME"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "Tutorial-ACME.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut vmi-tutorial
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "VMI"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "Tutorial-VMI.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)



;;
;; core G2, TW2, etc components for basic versions
;;
(def-component core-runtime-server
  :print-name "Core Runtime Server"
  :parts (
	axl-g2com-kb runtime-g2-database-kbs runtime-g2-kbs
	g2-exe-intelnt-escor g2passwd-exe-intelnt-escor ext-directory-escor
	g2-gen16ut-dll-intelnt-escor g2-gen32-dll-intelnt-escor g2-gen32ut-dll-intelnt-escor
	g2-blank-ok-escor)
  :optional false)



(def-part runtime-G2-database-kbs
    :version :60r8
    :source-ship-type :external
    :source g2odbc
    :destination-directory "odbc"
    :platforms ("nt")
    :make-not-read-only t
    :source-filename "g2-database.kb")


(def-part runtime-g2-kbs
    :version :62r2
    :source-ship-type :external
    :source-filename ("g2uifile.kb" "gfr.kb" "gms.kb" "gold.kb" "goldui.kb" "gxl.kb" "sys-mod.kb"
				    "uil.kb" "uilcombo.kb" "uildefs.kb" "uillib.kb" "uilroot.kb" "uilsa.kb"
				    "uilslide.kb" "uiltdlg.kb" "jiscodes.kl"
				    "kscodes.kl" "japanese.kl" "korean.kl" "language.kl")
    :source kbs
    :source-subdirectory "utils"
    :destination-directory "g2/kbs/utils"
    :make-not-read-only t
    :indep t)

;;
;;	For e-SCOR/ReThink 4.0r1 we are using a 62r1
;;	that fixes a specific G2 bug (z ordering of
;;	objects in TW2 workspace views).
;;
(def-component g2-escor
  :parts
  (	g2-exe-intelnt-escor
	g2passwd-exe-intelnt-escor
	index-dic-escor
	kojin-dic-escor
	main-dic-escor
	ext-directory-escor
	g2-gen16ut-dll-intelnt-escor
	g2-gen32-dll-intelnt-escor
	g2-gen32ut-dll-intelnt-escor
	g2-blank-ok-escor
	kbs
	fonts)
  :print-name "G2 (and utilities)")


(def-part index-dic-escor
    :version :62r2
    :print-name "Kanji index dictionary"
    :source g2
    :source-filename "index.dic"
    :destination-directory "g2")

(def-part kojin-dic-escor
    :version :62r2
    :print-name "Kanji kojin dictionary"
    :source g2
    :source-filename "kojin.dic"
    :destination-directory "g2")

(def-part main-dic-escor
    :version :62r2
    :print-name "Kanji main dictionary"
    :source g2
    :source-filename "main.dic"
    :destination-directory "g2")

(def-part ext-directory-escor
    :version :62r2
    :print-name "G2 EXT Directory"
    :source g2
    :source-subdirectory "ext"
    :destination-directory "g2/ext")

(def-part g2-exe-intelnt-escor
    :version :62r2
    :print-name "G2 Windows Executable"
    :source g2
    :source-filename "g2.exe"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2passwd-exe-intelnt-escor
    :version :62r2
    :print-name "G2PASSWD Windows Executable"
    :source g2
    :source-filename "g2passwd.exe"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-gen16ut-dll-intelnt-escor
    :version :62r2
    :print-name "G2 Gen16UT DLL"
    :source g2
    :source-filename "gen16ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-gen32-dll-intelnt-escor
    :version :62r2
    :print-name "G2 Gen32 DLL"
    :source g2
    :source-filename "gen32.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-gen32ut-dll-intelnt-escor
    :version :62r2
    :print-name "G2 Gen32UT DLL"
    :source g2
    :source-filename "gen32ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-blank-ok-escor
    :version :62r2
    :print-name "Sample G2 OK file"
    :source g2
    :source-filename "g2.ok"
    :destination-directory "g2"
    :platforms ("nt"))


;;
;;	Following parts already installed as part of core server installation
;;	therefore not duplicating them here.
;;		axl-g2com-dll axl-gsi-dll axl-runme-bat axl-regsvr 

(def-component escor-activexlink
  :parts (axl-readme axl-g2com-kb axl-demos axl-kbs-5)
  :platforms ("nt")
  :print-name "G2 ActiveXLink")

;;
;; core G2, TW2, etc components for basic versions
;;
(def-component dev-g2-readme
  :parts (dev-g2-readme)
  :print-name "G2 Readme")

(def-part dev-g2-readme
    :source g2pkgreadme
    :version :62r2
    :source-ship-type :external
    :source-filename "readme-g2.html"
    :indep t 
    :shortcuts (dev-g2-readme))

(def-shortcut dev-g2-readme
    :folder-name escor-shortcut-folder-name
    :application-display-name "Readme for G2 Bundle"
    :application-directory ""
    :target-name "readme-g2.html")


;;;
;;; Documentation components for ReThink, e-SCOR, and core G2
;;;
(def-component escor-documentation
  :parts (escor-documentation)
  :print-name "e-SCOR Documentation"
  :optional true)



(def-part escor-documentation
    :version :40r3
    :source-ship-type :external
    :destination-directory "doc/escor"
    :source-subdirectory "doc/escor"
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



(def-component rethink-documentation
  :parts (rethink-documentation)
  :print-name "ReThink Documentation"
  :optional true)

(def-part rethink-documentation
    :version :40r3
    :source-ship-type :external
    :destination-directory "doc/rethink"
    :source-subdirectory "doc/rethink"
    :source escor
    :shortcuts (rethink-getting-started-documentation rethink-documentation-user rethink-documentation-customization))

(def-shortcut rethink-getting-started-documentation
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "ReThink"
    :application-display-name "Getting Started With ReThink"
    :application-directory "doc/rethink"
    :target-name "Getting-Started-With-ReThink.pdf")

(def-shortcut rethink-documentation-user
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "ReThink"
    :application-display-name "ReThink Users Guide"
    :application-directory "doc/rethink"
    :target-name "ReThink-Users-Guide.pdf")

(def-shortcut rethink-documentation-customization
    :folder-name escor-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "ReThink"
    :application-display-name "Customizing ReThink Users Guide"
    :application-directory "doc/rethink"
    :target-name "Customizing-ReThink-Users-Guide.pdf")



(def-component development-documentation
  :print-name "G2 Development Documentation"
  :parts (dev-g2pdf g2utlpdf jvldoc tw2doc axldoc corbalinkdoc
		g2classicrn
		g2oradoc g2sybdoc opclinkdoc g2odbcdoc
		g2dbdoc)
  :include-in-contents (dev-g2pdf)
  :optional true)

(def-part dev-g2pdf
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
		 g2-release-notes
		 g2-reference-manual
		 g2-reference-card

		 g2-system-procedures-reference-manual
		 g2-tutorial
		 g2-class-reference-manual
		 g2-developers-guide

		 ;; G2 Utilities
		 g2-dynamic-displays-users-guide	    
		 g2-developers-interface-users-guide
		 g2-foundation-resources-users-guide	    
		 g2-menu-system-users-guide
		 g2-online-documentation-developers-guide
		 g2-online-documentation-users-guide
		 g2-guide-uil-procedures-reference-manual
		 g2-guide-users-guide	    
		 g2-xl-spreadsheet-users-guide
		 ;; Protools
		 g2-protools-users-guide
		 ;; GSI
		 gsi-bridge-developers-guide
		 ;; Bridges:
		 g2-database-bridge-guide
		 g2-opclink-users-guide
		 g2-corba-link-users-guide	   
		 g2-odbc-bridge-release-notes
		 g2-oracle-bridge-release-notes	    
		 g2-sybase-bridge-release-notes
		 ;; TW
		 telewindows-users-guide

		 ;; TW2

		 ;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
		 ;;	    tw2-activex-help		; NOTE: Shortcut in TW2/ActiveX Folder

		 tw2-release-notes
		 bean-exporter-guide
		 tw2-components-guide
		 tw2-demos-guide
		 tw2-application-classes

		 ;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
		 ;; 	    telewindows2-toolkit-activex-developers-guide

		 ;; Javalink
		 g2-download-interfaces-guide
		 g2-beanbuilder-guide
		 g2-javalink-guide
		 ;; ActiveXLink
		 g2-activexlink-users-guide
		 ;; Weblink
		 g2-weblink-users-guide
		 ))

