;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; ESCOR-FAMILY - escor Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduj, mhd, and PPrintz


;;; The current shipping version of e-SCOR is 4.0 Beta Rev. 1 ("40b1").  The
;;; symbol :40b1-DK30 should be used generally for e-SCOR / ReThink elements below.

(require "g2-52r1-family")			; G2 6.0r1
(provide "escor-40b1-family")

(def-family escor-40b1
    :index 10
    :file-syntax-version 10
    :print-name "eSCOR_ReThink"
    :bundles (escor-offline escor-online escor-online-client
		  rethink-offline rethink-online rethink-online-client)
    :directory "escor_rethink"
    :guid "3BFDD0B2-F895-489B-A51C-9C44F6BB4405" ; "2.1b2"
    :previous-versions (("2.1r1" "243D4BBB-9EE7-11D4-8111-00A02431D004")
			("2.1r0" "243D4BB8-9EE7-11D4-8111-00A02431D004")
			("2.0r0" "243D4BAE-9EE7-11D4-8111-00A02431D004")
			;; add more here
			)
    :splash-screen "escor-rethink-setup.bmp"
    :license-text "escor-rethink-license.txt"
    :platforms ("nt"))



;;; Evaluation OK Components

;;; NOTE: escor and ReThink ok files.  Note, too, that
;;; this form must preceed the def-bundle form, so it interacts with certain
;;; bundle dwimification (MHD). 

(def-g2-ok-components (rethink-offline :obfuscate t) rethink-offline "ReThink Offline"
  (1
     (1 "-dec25-2001") (1 "-jan25-2002") (1 "-feb25-2002")
     (1 "-mar25-2002") (1 "-apr25-2002") (1 "-may25-2002")
     (1 "-jun25-2002") (1 "-jul25-2002") (1 "-aug25-2002")
     (1 "-sep25-2002") (1 "-oct25-2002") (1 "-nov25-2002")
     (1 "-dec25-2002") (1 "-jan25-2003") (1 "-feb25-2003")))

(def-g2-ok-components (rethink-online :obfuscate t) rethink-online "ReThink Online"
  (1 2 3 4 5 6 7 8
     (1 "-dec25-2001") (1 "-jan25-2002") (1 "-feb25-2002")
     (1 "-mar25-2002") (1 "-apr25-2002") (1 "-may25-2002")
     (1 "-jun25-2002") (1 "-jul25-2002") (1 "-aug25-2002")
     (1 "-sep25-2002") (1 "-oct25-2002") (1 "-nov25-2002")
     (1 "-dec25-2002") (1 "-jan25-2003") (1 "-feb25-2003")))


(def-g2-ok-components (escor-offline :obfuscate t) escor-offline "e-SCOR Offline"
  (1
     (1 "-dec25-2001") (1 "-jan25-2002") (1 "-feb25-2002")
     (1 "-mar25-2002") (1 "-apr25-2002") (1 "-may25-2002")
     (1 "-jun25-2002") (1 "-jul25-2002") (1 "-aug25-2002")
     (1 "-sep25-2002") (1 "-oct25-2002") (1 "-nov25-2002")
     (1 "-dec25-2002") (1 "-jan25-2003") (1 "-feb25-2003")))

(def-g2-ok-components (escor-online :obfuscate t) escor-online "e-SCOR Online"
  (1 2 3 4 5 6 7 8
     (1 "-dec25-2001") (1 "-jan25-2002") (1 "-feb25-2002")
     (1 "-mar25-2002") (1 "-apr25-2002") (1 "-may25-2002")
     (1 "-jun25-2002") (1 "-jul25-2002") (1 "-aug25-2002")
     (1 "-sep25-2002") (1 "-oct25-2002") (1 "-nov25-2002")
     (1 "-dec25-2002") (1 "-jan25-2003") (1 "-feb25-2003")))





;;;
;;; Specifications of the different bundles
;;;

(def-bundle escor-offline
    :components (core-runtime-client rethink-client escor-client escor-offline-client
			escor-documentation rethink-documentation
			core-runtime-server rethink-server escor-server
			;; These are the OK components:
			escor-offline-family-ok-components)
    :print-name "e-SCOR Offline"
    :directory "escor"
    :version :40b1-DK30)


(def-bundle escor-online
    :components (core-runtime-client rethink-client escor-client escor-online-client
			escor-documentation rethink-documentation development-documentation
			core-runtime-server rethink-server rethink-online-server escor-server
			dev-g2-server dev-telewindows dev-telewindows2 dev-javalink dev-gateway
			dev-weblink dev-activexlink dev-protools
			dev-corbalink dev-opclink dev-Oraclebridge dev-Sybasebridge dev-ODBCbridge
			dev-g2-readme
			;; These are the OK components:
			escor-online-family-ok-components)
    :print-name "e-SCOR Online"
    :directory "escor"
    :version :40b1-DK30)

(def-bundle escor-online-client
    :components (core-runtime-client rethink-client escor-client escor-online-client 
			escor-documentation rethink-documentation)
    :print-name "e-SCOR Online Client Only"
    :directory "escor"
    :version :40b1-DK30)




(def-bundle rethink-offline
    :components (core-runtime-client rethink-client rethink-offline-client
			rethink-documentation 
			core-runtime-server rethink-server
			;; These are the OK components:
			rethink-offline-family-ok-components)
    :print-name "ReThink Offline"
    :directory "escor"
    :version :40b1-DK30)


(def-bundle rethink-online
    :components (core-runtime-client rethink-client rethink-online-client
			rethink-documentation development-documentation
			core-runtime-server rethink-server rethink-online-server
			dev-g2-server dev-telewindows dev-telewindows2 dev-javalink dev-gateway
			dev-weblink dev-activexlink dev-protools
			dev-corbalink dev-opclink dev-Oraclebridge dev-Sybasebridge dev-ODBCbridge
			dev-g2-readme
			;; These are the OK components:
			rethink-online-family-ok-components)
    :print-name "ReThink Online"
    :directory "escor"
    :version :40b1-DK30)

(def-bundle rethink-online-client
    :components (core-runtime-client rethink-client rethink-online-client 
			rethink-documentation)
    :print-name "ReThink Online Client Only"
    :directory "escor"
    :version :40b1-DK30)



;;;
;;; ReThink client components and parts
;;;
(def-component rethink-client
  :print-name "ReThink Client"
  :parts (rethink-readme rethink-client-binaries core-client-classes rethink-reports)
  :optional false)


(def-part rethink-readme
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename "ReThink-readme.html"
    :source "escor"
    :print-name "ReThink README file"
    :shortcuts (rethink-readme-shortcut))

(def-shortcut rethink-readme-shortcut
    :folder-name "Gensym e-SCOR & ReThink"
    :application-display-name "Readme for ReThink"
    :application-directory ""
    :target-name "ReThink-readme.html")



(def-part rethink-client-binaries
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename ("Client.bat")
    :destination-directory "bin"
    :source "escor"
    :source-subdirectory "bin"
    :shortcuts (rethink-client-shortcut)
    :environment-variables (ESCOR_RETHINK_HOME))

(def-shortcut rethink-client-shortcut
    :folder-name "Gensym e-SCOR & ReThink"
    :application-display-name "Client"
    :application-directory "bin"
    :target-name "Client.bat"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)

(def-environment-variable ESCOR_RETHINK_HOME :value "<TARGETDIR>")



(def-part core-client-classes
    :version :40b1-DK30 :source-ship-type :internal
    :source "escor"
    :source-subdirectory "classes"
    :source-filename ("escor-rethink.jar" "generic-uitools.jar" "jh.jar" "jhall.jar" "jhtools.jar" "jsearch.jar" "ntw-uitools.jar")
    :destination-directory "classes")



(def-part rethink-reports
    :version :40b1-DK30 :source-ship-type :internal
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("ReThink-Summary-Reports.xls")
    :source "escor"
    :shortcuts (rethink-default-summary-reports))

(def-shortcut rethink-default-summary-reports
    :folder-name "Gensym e-SCOR & ReThink"
    :application-display-name "ReThink Default Summary Reports"
    :application-directory "kbs"
    :target-name "ReThink-Summary-Reports.xls")




(def-component rethink-offline-client
  :print-name "ReThink Offline Client"
  :parts (rethink-offline-splash rethink-product-icon rethink-product-logo)
  :optional false)


(def-component rethink-online-client
  :print-name "ReThink Online Client"
  :parts (rethink-online-splash rethink-product-icon rethink-product-logo)
  :optional false)



(def-part rethink-offline-splash
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename "rethink_offline_splash.jpg"
    :source-subdirectory "bin"
    :destination-filename "splash.jpg"
    :destination-directory "bin"
    :source "escor"
    :print-name "ReThink Offline Splash Screen")


(def-part rethink-online-splash
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename "rethink_online_splash.jpg"
    :source-subdirectory "bin"
    :destination-filename "splash.jpg"
    :destination-directory "bin"
    :source "escor"
    :print-name "ReThink Online Splash Screen")

(def-part rethink-product-icon
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename "ReThink.ico"
    :source-subdirectory "bin"
    :destination-filename "logo.ico"
    :destination-directory "bin"
    :source "escor"
    :print-name "ReThink Product Icon")

(def-part rethink-product-logo
    :version :40b1-DK30 :source-ship-type :internal
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
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename "e-SCOR-readme.html"
    :source "escor"
    :print-name "e-SCOR README file"
    :shortcuts (escor-readme-shortcut))

(def-shortcut escor-readme-shortcut
    :folder-name "Gensym e-SCOR & ReThink"
    :application-display-name "Readme for e-SCOR"
    :application-directory ""
    :target-name "e-SCOR-readme.html")



(def-part escor-reports
    :version :40b1-DK30 :source-ship-type :internal
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("Default-Summary-Reports.xls"  "Tutorial-Simplest-Model-Summary-Reports.xls" "Tutorial-ACME-Summary-Reports.xls" "Tutorial-VMI-Summary-Reports.xls")
    :source "escor"
    :shortcuts (escor-default-summary-reports
		 simplest-model-summary-reports-tutorial
		 acme-summary-report-tutorial
		 vmi-summary-report-tutorial))

(def-shortcut escor-default-summary-reports
    :folder-name "Gensym e-SCOR & ReThink"
    :application-display-name "e-SCOR Default Summary Reports"
    :application-directory "kbs"
    :target-name "Default-Summary-Reports.xls")

(def-shortcut simplest-model-summary-reports-tutorial
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "Simplest Model Summary Reports"
    :application-directory "kbs"
    :target-name "Tutorial-Simplest-Model-Summary-Reports.xls")

(def-shortcut acme-summary-report-tutorial
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Examples"
    :subsubfolder-name "e-SCOR"
    :application-display-name "ACME Summary Reports"
    :application-directory "kbs"
    :target-name "Tutorial-ACME-Summary-Reports.xls")

(def-shortcut vmi-summary-report-tutorial
    :folder-name "Gensym e-SCOR & ReThink"
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
  :parts (escor-online-splash escor-product-icon escor-product-logo)
  :optional false)



(def-part escor-offline-splash
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename "escor_offline_splash.jpg"
    :source-subdirectory "bin"
    :destination-filename "splash.jpg"
    :destination-directory "bin"
    :source "escor"
    :print-name "e-SCOR Offline Splash Screen")

(def-part escor-online-splash
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename "escor_online_splash.jpg"
    :source-subdirectory "bin"
    :destination-filename "splash.jpg"
    :destination-directory "bin"
    :source "escor"
    :print-name "e-SCOR Online Splash Screen")

(def-part escor-product-icon
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename "e-SCOR.ico"
    :source-subdirectory "bin"
    :destination-filename "logo.ico"
    :destination-directory "bin"
    :source "escor"
    :print-name "e-SCOR Product Icon")

(def-part escor-product-logo
    :version :40b1-DK30 :source-ship-type :internal
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
  :parts (runtime-axl-dll runtime-axl-binaries runtime-GSI-binaries runtime-javalink-binaries 
	runtime-javalink-classes runtime-sequoia-classes jre)
  :optional false)


(def-part runtime-axl-dll
    :parent axl-g2com-dll
    :destination-directory "activexlink"
    :print-name "DLLs to register")

(def-part runtime-axl-binaries
    :version :10r1-DF12
    :source axl
    :source-ship-type :external
    :source-filename ("regsvr32.exe" "G2Com.dll" "gsi.dll")
    :destination-directory "activexlink")


(def-part runtime-GSI-binaries
    :version :60r1
    :source gsi
    :source-ship-type :external
    :source-filename "gsi.dll"
    :destination-directory "gsi")


(def-part runtime-javalink-binaries
    :version :12r1
    :source jvl
    :source-ship-type :external
    :source-subdirectory "components/bin"
    :source-filename "JgiInterface.dll"
    :destination-directory "javalink/bin")


(def-part runtime-javalink-classes
    :version :12r1
    :source jvl
    :source-ship-type :external
    :source-subdirectory "components/classes"
    :source-filename ("core.jar" "javalink.jar" "classtools.jar")
    :destination-directory "javalink/classes")


(def-part runtime-sequoia-classes
    :version :12r1
    :source tw2
    :source-ship-type :external
    :source-subdirectory "components/classes"
    :destination-directory "tw2/classes"
    :source-filename ("coreui.jar" "sequoia.jar"))




(def-component core-online-client
  :print-name "Core Online Client"
  :parts (odbc-binaries)
  :optional false)


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
    :version :40b1-DK30 :source-ship-type :internal
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("rethink.kb" "aero.kb" "bpr.kb" "bprui.kb" "chapter3.kb" "customiz.kb" "methods.kb" "menus.kb" "orderful.kb" "aeroscrt.txt" "rethink-40-doc-examples.kb" "customizing-rethink-examples.kb") 
    :source "escor"
    :shortcuts (aero-tutorial aero-script-tutorial orderful-tutorial chapter3-tutorial rethink-40-tutorial rethink-customization-tutorial))

(def-shortcut rethink-customization-tutorial
    :folder-name "Gensym e-SCOR & ReThink"
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
    :folder-name "Gensym e-SCOR & ReThink"
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
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "Aero Model"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "aero.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut aero-script-tutorial
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "Aero Script"
    :application-directory "kbs"
    :target-name "aeroscrt.txt")

(def-shortcut chapter3-tutorial
    :folder-name "Gensym e-SCOR & ReThink"
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
    :folder-name "Gensym e-SCOR & ReThink"
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
    :version :40b1-DK30 :source-ship-type :internal
    :destination-directory "kbs/images"
    :source-subdirectory "kbs/images"
    :source "escor")


(def-part rethink-server-binaries
    :version :40b1-DK30 :source-ship-type :internal
    :source-filename ("Server.bat")
    :destination-directory "bin"
    :source "escor"
    :source-subdirectory "bin"
    :shortcuts (rethink-server-shortcut))


(def-shortcut rethink-server-shortcut
    :folder-name "Gensym e-SCOR & ReThink"
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
    :version :40b1-DK30 :source-ship-type :internal
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("rethink-online.kb" "methods-online.kb" "rethink-40-online-examples.kb" "orders.mdb")
    :source "escor"
    :shortcuts (rethink-online-examples runtime-odbc-shortcut)
    :environment-variables (gsi_root))


(def-shortcut rethink-online-examples
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Examples"
    :subsubfolder-name "ReThink"
    :application-display-name "ReThink 4.0 Online Examples"
    :application-directory "bin"
    :target-name "Server.bat"
    :parameters "rethink-40-online-examples.kb"
    :icon-file "logo.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut runtime-odbc-shortcut
    :folder-name "Gensym e-SCOR & ReThink"
    :application-display-name "ODBC Bridge "
    :application-directory "odbc"
    :target-name "g2-odbc.exe"
    :parameters "22042"
    :icon-index 0
    :run-style minimized)

(def-environment-variable gsi_root :value "<TARGETDIR>\\\\odbc")




;;
;; e-SCOR server
;;
(def-component escor-server
  :print-name "e-SCOR Server"
  :parts (escor-kbs)
  :optional false)



(def-part escor-kbs
    :version :40b1-DK30 :source-ship-type :internal
    :destination-directory "kbs"
    :source-subdirectory "kbs"
    :source-filename ("eSCOR.kb" "escor-bom.kb" "escor-customiz.kb" "escor-definitions.kb" "escor-demos.kb" "escor-examples-eto.kb" "escor-examples-misc.kb" "escor-examples-mto.kb" "escor-examples-pull.kb" "escor-examples-push.kb" "escor-upgrade.kb" "Tutorial-ACME.kb" "Tutorial-Simplest-Model.kb" "Tutorial-VMI.kb") 
    :source "escor"
    :shortcuts (simplest-model-tutorial acme-tutorial vmi-tutorial))

(def-shortcut simplest-model-tutorial
    :folder-name "Gensym e-SCOR & ReThink"
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
    :folder-name "Gensym e-SCOR & ReThink"
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
    :folder-name "Gensym e-SCOR & ReThink"
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
	runtime-g2-com-kbs runtime-g2-database-kbs runtime-g2-kbs
	g2-exe-intelnt-escor g2passwd-exe-intelnt ext-directory
	g2-gen16ut-dll-intelnt g2-gen32-dll-intelnt g2-gen32ut-dll-intelnt)
  :optional false)



(def-part runtime-G2-database-kbs
    :source g2odbc
    :version :60r5
    :source-ship-type :external
    :source-filename "g2-database.kb"
    :destination-directory "odbc")

(def-part runtime-G2-com-kbs
    :source axl
    :version :10r1-DF12
    :source-ship-type :external
    :source-filename "g2com.kb"
    :destination-directory "activexlink")

(def-part runtime-g2-kbs
    :version :60r1    :source-ship-type :external
    :source-filename ("g2uifile.kb" "gfr.kb" "gms.kb" "gold.kb" "goldui.kb" "gxl.kb" "sys-mod.kb"
				    "uil.kb" "uilcombo.kb" "uildefs.kb" "uillib.kb" "uilroot.kb" "uilsa.kb"
				    "uilslide.kb" "uiltdlg.kb" "jiscodes.kl"
				    "kscodes.kl" "japanese.kl" "korean.kl" "language.kl")
    :source kbs
    :source-subdirectory "utils"
    :destination-directory "g2/kbs/utils"
    :indep t)


(def-part g2-exe-intelnt-escor
   :version :60r1   :source-ship-type :external
   :parent g2-exe-intelnt
   :environment-variables :delete
   :shortcuts :delete)



;;
;; core G2, TW2, etc components for basic versions
;;
(def-component dev-g2-readme
  :parts (dev-g2-readme)
  :print-name "G2 Readme")

(def-part dev-g2-readme
    :source g2pkgreadme
    :version :52r1
    :source-filename "readme.htm"
    :destination-filename "g2-readme.htm"
    :indep t 
    :shortcuts (dev-g2-readme))

(def-shortcut dev-g2-readme
    :folder-name "Gensym e-SCOR & ReThink"
    :application-display-name "Readme for G2 Classic"
    :application-directory ""
    :target-name "g2-readme.htm")

(def-component dev-g2-server
  :parts (g2-exe-intelnt g2passwd-exe-intelnt
		index-dic kojin-dic main-dic ext-directory

		;; note: same files as for TW, may overwrite:
		g2-gen16ut-dll-intelnt
		g2-gen32-dll-intelnt
		g2-gen32ut-dll-intelnt

		g2-blank-ok

		kbs fonts)
  :print-name "G2 (and utilities)"
  :optional true)


(def-component dev-telewindows
  :parts (dev-tw-exe-intelnt
	   tw-nptwplug-dll-intelnt

	   ;; note: same files as for G2, may overwrite:
	   tw-gen16ut-dll-intelnt
	   tw-gen32-dll-intelnt
	   tw-gen32ut-dll-intelnt

	   ;; same in G2, OK to specify twice, may be overwritten:
	   fonts)
  :print-name "Telewindows"
  :optional true)

(def-part dev-tw-exe-intelnt
    :version :60r1
    :print-name "TW Windows Executable"
    :source tw
    :source-filename "tw.exe"
    :destination-directory "g2"
    :platforms ("nt"))


(def-component dev-telewindows2
  :parts (tw2 dev-tw2-intelnt dev-tw2-javadoc)
  :print-name "Telewindows2 Toolkit"
  :optional true)

(def-part dev-tw2-javadoc
    :version :12r1
    :source tw2-javadoc
    :destination-directory "doc/tw2/Java"
    :shortcuts (dev-tw2-javadoc)
    :indep t)

(def-shortcut dev-tw2-javadoc
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "API Documentation"
    :application-directory "doc\\tw2\\Java\\docs\\api"
    :target-name "index.html")

(def-part dev-tw2-intelnt
    :version :12r1
	  :source tw2
	  :source-subdirectory "components"
	  ;; for building tree:  handled by bundle.lisp, not in family file. -mhd
	  :remove-from-source ("bin/unInstall.bat" "bin/unInstaller.bat") ; remove component installer stuff
	  :destination-directory tw2
	  :platforms ("nt")	  
	  :environment-variables (sequoia_home sequoia-classpath sequoia-path)
	  :shortcuts (
;;dev-tw2-toolkit-demo
		       dev-tw2-readme))

;;(def-shortcut dev-tw2-toolkit-demo
;;    :folder-name "Gensym e-SCOR & ReThink"
;;    :subfolder-name "Documentation"
;;    :subsubfolder-name "Telewindows2 Toolkit"
;;    :application-display-name "Default Application Shell"
;;    :application-directory "tw2\\bin"
;;    :target-name "shell.bat")

(def-shortcut dev-tw2-readme
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Readme for Telewindows2 Toolkit"
    :application-directory "tw2"
    :target-name "readme.html")





(def-component dev-javalink
  :parts (jvl dev-jvl-intelnt jvl-com-gensym-properties-intelnt dev-jvl-javadoc)
  :print-name "G2 JavaLink"
  :optional true)

(def-part dev-jvl-intelnt
  :version :12r1
  :source jvl
  :destination-directory javalink
  :environment-variables (javalink_home javalink-classpath javalink-path)

  ;; the semantics of the special source directive is to only copy those files
  :platforms ("nt") :source-subdirectory "components"
  :shortcuts (dev-jvl-example-readme
	      dev-jvl-known-problems
	      dev-jvl-readme)
  )

(def-shortcut dev-jvl-example-readme
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "Examples Readme"
    :application-directory "javalink"
    :target-name "ExamplesReadme.html")

(def-shortcut dev-jvl-known-problems
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "Known Problems"
    :application-directory "javalink"
    :target-name "KnownProblems.html")

(def-shortcut dev-jvl-readme
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "Readme for Javalink"
    :application-directory "javalink"
    :target-name "readme.html")


(def-part dev-jvl-javadoc
    :version :12r1
    :source jvl-javadoc
    :destination-directory doc/javalink
    :shortcuts (dev-jvl-javadoc)
    :indep t)

(def-shortcut dev-jvl-javadoc
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "API Documentation"
    :application-directory "doc\\javalink\\docs\\api"
    :target-name "index.html")



(def-component dev-gateway
  :parts (gsi)
  :print-name "G2 Gateway (GSI)"
  :optional true)


(def-component dev-weblink
  :parts (gw gsi-gw-ok gsi-gw-blank-ok)
  :print-name "G2 WebLink"
  :optional true)


(def-component dev-activexlink
  :parts (axl-g2com-dll axl-gsi-dll axl-readme axl-g2com-kb axl-demos axl-runme-bat axl-regsvr axl-kbs-5)
  :platforms ("nt")
  :print-name "G2 ActiveXLink"
  :optional true)


(def-component dev-protools
  :parts (protools-5 protools-6)
  :print-name "G2 ProTools"
  :optional true)


(def-component dev-corbalink
  :parts (corbalink)
  :print-name "G2 CORBALink"
  :non-platforms ("alphaosf")
  :optional true)

(def-component dev-opclink
  :parts (opclink gsi-opclink-ok gsi-opclink-blank-ok)
  :platforms ("nt")
  :print-name "G2 OPCLink Bridge"
  :optional true)

(def-component dev-Oraclebridge
  :parts (Oraclebridge gsi-Oracle-ok gsi-Oracle-blank-ok)
  :print-name "G2 Oracle Bridge"
  :optional true)

(def-component dev-Sybasebridge
  :parts (Sybasebridge gsi-Sybase-ok gsi-Sybase-blank-ok)
  :print-name "G2 Sybase Bridge"
  :non-platforms ("linux")
  :optional true)

(def-component dev-ODBCbridge
  :parts (ODBCbridge gsi-ODBC-ok gsi-ODBC-blank-ok)
  :platforms ("nt")
  :print-name "G2 ODBC Bridge"
  :optional true)



;;;
;;; Documentation components for ReThink, e-SCOR, and core G2
;;;
(def-component escor-documentation
  :parts (escor-documentation)
  :print-name "e-SCOR Documentation"
  :optional true)



(def-part escor-documentation
    :version :40b1-DK30 :source-ship-type :internal
    :destination-directory "doc/escor"
    :source-subdirectory "doc/escor"
    :source escor
    :shortcuts (escor-documentation-quick escor-documentation-user escor-documentation-scor escor-tutorial))

(def-shortcut escor-documentation-quick
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "e-SCOR"
    :application-display-name "e-SCOR Quick Reference"
    :application-directory "doc/escor"
    :target-name "e-SCOR-Quick-Reference.pdf")

(def-shortcut escor-documentation-user
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "e-SCOR"
    :application-display-name "e-SCOR Users Guide"
    :application-directory "doc/escor"
    :target-name "e-SCOR-Users-Guide.pdf")

(def-shortcut escor-documentation-scor
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "e-SCOR"
    :application-display-name "SCOR Version 4.0"
    :application-directory "doc/escor"
    :target-name "SCOR-Version-4.0.pdf")

(def-shortcut escor-tutorial
    :folder-name "Gensym e-SCOR & ReThink"
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
    :version :40b1-DK30 :source-ship-type :internal
    :destination-directory "doc/rethink"
    :source-subdirectory "doc/rethink"
    :source escor
    :shortcuts (rethink-documentation-user rethink-documentation-customization))

(def-shortcut rethink-documentation-user
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "ReThink"
    :application-display-name "ReThink Users Guide"
    :application-directory "doc/rethink"
    :target-name "ReThink-Users-Guide.pdf")

(def-shortcut rethink-documentation-customization
    :folder-name "Gensym e-SCOR & ReThink"
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
  :include-in-contents (g2pdf)
  :optional true)

(def-part dev-g2pdf
    :version :60r0
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
		 dev-g2-release-notes
		 dev-g2-reference-manual
		 dev-g2-reference-card

		 dev-g2-system-procedures-reference-manual
		 dev-g2-tutorial
		 dev-g2-class-reference-manual

		 ;; G2 Utilities
		 dev-g2-dynamic-displays-users-guide	    
		 dev-g2-developers-interface-users-guide
		 dev-g2-foundation-resources-users-guide	    
		 dev-g2-menu-system-users-guide
		 dev-g2-online-documentation-developers-guide
		 dev-g2-online-documentation-users-guide
		 dev-g2-guide-uil-procedures-reference-manual
		 dev-g2-guide-users-guide	    
		 dev-g2-xl-spreadsheet-users-guide
		 ;; Protools
		 dev-g2-protools-users-guide
		 ;; GSI
		 dev-gsi-bridge-developers-guide
		 ;; Bridges:
		 dev-g2-database-bridge-guide
		 dev-g2-opclink-users-guide
		 dev-g2-corba-link-users-guide	   
		 dev-g2-odbc-bridge-release-notes
		 dev-g2-oracle-bridge-release-notes	    
		 dev-g2-sybase-bridge-release-notes
		 ;; TW
		 dev-telewindows-users-guide

		 ;; TW2

		 ;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
		 ;;	    tw2-activex-help		; NOTE: Shortcut in TW2/ActiveX Folder

		 dev-tw2-release-notes
		 dev-bean-exporter-guide
		 dev-tw2-components-guide
		 dev-tw2-demos-guide
		 dev-tw2-application-classes

		 ;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
		 ;; 	    telewindows2-toolkit-activex-developers-guide

		 ;; Javalink
		 dev-g2-download-interfaces-guide
		 dev-g2-beanbuilder-guide
		 dev-g2-javalink-guide
		 ;; ActiveXLink
		 dev-g2-activexlink-users-guide
		 ;; Weblink
		 dev-g2-weblink-users-guide
		 ))


;; Documentation Shortcuts
(def-shortcut dev-g2-release-notes
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Classic Release Notes"
    :application-directory "doc"
    :target-name "g2classicrelnotes.pdf")

(def-shortcut dev-g2-reference-manual
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Reference Manual"
    :application-directory "doc\\g2"
    :target-name "g2refman.pdf")

(def-shortcut dev-g2-reference-card
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Language Reference Card"
    :application-directory "doc\\g2"
    :target-name "g2langrefcard.pdf")

(def-shortcut dev-g2-system-procedures-reference-manual
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 System Procedures Reference Manual"
    :application-directory "doc\\g2"
    :target-name "g2sysprocs.pdf")

(def-shortcut dev-g2-tutorial
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Getting Started with G2 Tutorial"
    :application-directory "doc\\g2"
    :target-name "g2tutorials.pdf")

(def-shortcut dev-g2-class-reference-manual
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Class Reference Manual"
    :application-directory "doc\\g2"
    :target-name "g2classref.pdf")

;; not included in 5.2r0 bundle
(def-shortcut dev-g2-developers-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Developer's Guide"
    :application-directory "doc\\g2\\html\\g2dvg"
    :target-name "titlepag.htm")

(def-shortcut dev-g2-dynamic-displays-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Dynamic Displays User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gdd.pdf")

(def-shortcut dev-g2-developers-interface-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Developer's Interface User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gdi.pdf")

(def-shortcut dev-g2-foundation-resources-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Foundation Resources User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gfr.pdf")

(def-shortcut dev-g2-menu-system-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Menu System User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gms.pdf")

(def-shortcut dev-g2-online-documentation-developers-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation Developer's Guide"
    :application-directory "doc\\utilities"
    :target-name "golddev.pdf")

(def-shortcut dev-g2-online-documentation-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation User's Guide"
    :application-directory "doc\\utilities"
    :target-name "goldui.pdf")

(def-shortcut dev-g2-guide-uil-procedures-reference-manual
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE UIL Procedures Reference Manual"
    :application-directory "doc\\utilities"
    :target-name "guideprocref.pdf")

(def-shortcut dev-g2-guide-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE User's Guide"
    :application-directory "doc\\utilities"
    :target-name "guideuserguide.pdf")

(def-shortcut dev-g2-xl-spreadsheet-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 XL Spreadsheet User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gxl.pdf")


;; G2 ProTools

(def-shortcut dev-g2-protools-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 ProTools User's Guide"
    :application-directory "protools\\kbs"
    :target-name "g2protools.pdf")

;; G2 Gateway (GSI)

(def-shortcut dev-gsi-bridge-developers-guide
    ;; "Everyone knows this informally as 'the GSI manual'". --peter k.
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Gateway Bridge Developer's Guide"
    :application-directory "doc\\g2"
    :target-name "g2gateway.pdf")

;; Bridges

(def-shortcut dev-g2-database-bridge-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 Database Installation and Operations Manual"
    ;; About the name above: would prefer & instead of "and", but I'm afraid &'s
    ;; won't work?! -mhd
    ;;
    ;; (from our part g2dbdoc)
    ;;
    ;; Actually the cover title page says G2-Database Bridge Installation &
    ;; operations Manual Version 6.0
    ;;
    ;; Part number: DOC047-601.
    ;;
    ;; The "r4" was added because it originally shipped with Oracle Bridge
    ;; 6.0r4, and they wanted the version to match that.  However, per Peter
    ;; Keville, this is really "r1" (which he can tell from the part number's
    ;; -601 tag. (MHD 4/26/01)
    :application-directory "doc\\bridges\\db"
    :target-name "g2dbinstalloper.pdf")

(def-shortcut dev-g2-opclink-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 OPCLink User's Guide"
    :application-directory "doc\\bridges\\opclink"
    :target-name "g2opclink.pdf")


(def-shortcut dev-g2-corba-link-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 CORBALink User's Guide"
    :application-directory "doc\\bridges\\corbalink"
    :target-name "g2corbalink.pdf")

(def-shortcut dev-g2-odbc-bridge-release-notes
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-ODBC Bridge Release Notes"
    :application-directory "doc\\bridges\\odbc"
    :target-name "g2odbcbridge.pdf")

(def-shortcut dev-g2-oracle-bridge-release-notes
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Oracle Bridge Release Notes"
    :application-directory "doc\\bridges\\oracle"
    :target-name "g2oraclebridge.pdf")

(def-shortcut dev-g2-sybase-bridge-release-notes
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Sybase Bridge Release Notes"
    :application-directory "doc\\bridges\\sybase"
    :target-name "g2sybasebridge.pdf")


;; Telewindows

(def-shortcut dev-telewindows-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Telewindows User's Guide"
    :application-directory "doc\\g2"
    :target-name "telewindows.pdf")



;; Telewindows2 Toolkit
			   
(def-shortcut dev-tw2-release-notes
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Release Notes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "t2relnotes.pdf")

(def-shortcut dev-bean-exporter-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "BeanXporter User's Guide"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "beanXporter.pdf")

(def-shortcut dev-tw2-components-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Components and Core Classes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "t2components.pdf")

(def-shortcut dev-tw2-application-classes
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Application Classes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "t2javadevguide.pdf")

(def-shortcut dev-tw2-demos-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Java Demos Guide"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "t2javademos.pdf")



;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
;; (def-shortcut telewindows2-toolkit-activex-developers-guide
;;     :folder-name "Gensym e-SCOR & ReThink"
;;     :subfolder-name "Documentation"
;;     :subsubfolder-name "Telewindows2 Toolkit"
;;     :application-display-name "Telewindows2 Toolkit ActiveX Developer's Guide"
;;     :application-directory "doc\\tw2\\ActiveX\\docs\\guides\\ActiveXDevelopersGuide"
;;     :target-name "titlepag.htm")
			                 

;; Javalink

(def-shortcut dev-g2-download-interfaces-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 Download Interfaces User's Guide"
    :application-directory "doc\\javalink\\docs\\guides"
    :target-name "g2downloadinterfaces.pdf")

(def-shortcut dev-g2-beanbuilder-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 Bean Builder User's Guide"
    :application-directory "doc\\javalink\\docs\\guides"
    :target-name "g2beanbuilder.pdf")

(def-shortcut dev-g2-javalink-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 JavaLink User's Guide"
    :application-directory "doc\\javalink\\docs\\guides"
    :target-name "g2javalink.pdf")




;; G2 ActiveXLink

(def-shortcut dev-g2-activexlink-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 ActiveXLink User's Guide"
    :application-directory "doc\\bridges\\activexlink"
    :target-name "g2activexlink.pdf")

;; G2 WebLink

(def-shortcut dev-g2-weblink-users-guide
    :folder-name "Gensym e-SCOR & ReThink"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 WebLink User's Guide"
    :application-directory "gw"
    :target-name "g2weblink.pdf")
