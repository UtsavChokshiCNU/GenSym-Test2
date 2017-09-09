;; -*- mode: lisp; package: bundle -*-

(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; G2-FAMILY - G2 Family Definitions.  Requires bundle.lisp.

;; Mark H. David


(provide 'g2-70b0-family)





;;;; Families



(def-family G2-70b0
    :index 19			; per tools/datafiles/families/family-id.dat
    :file-syntax-version 10
    :bundles (G2-Deployment G2-Development TW-Client TW2-Client)
    :print-name "G2"		; "G2" => "G2 Classic" (MHD 12/13/01)
				; "G2 Classic" => "G2" (yduJ 1/28/02)
    
    :directory "g2-7.0b0"
    ;; per tools/datafiles/families/guid.dat:
    :guid "69999187-41FE-4390-B149-33765323882F" ; 7.0b0
    :compatible-previous-versions (("6.2r2" "B496D6B3-B00D-43A9-96A2-267F01395A64")
				   ("6.2r0" "C88050F2-F316-4099-816C-A37D11D62831")
				   ("6.1r0" "5127F127-9E61-4E5C-B7F6-F34B20EC8F34"))
    :previous-versions (("5.2r1" "243D4BC0-9EE7-11D4-8111-00A02431D004")
			("5.2r0" "243D4BBC-9EE7-11D4-8111-00A02431D004")
			("5.2b1" "243D4BB9-9EE7-11D4-8111-00A02431D004")
			("5.1r7" "243D4BB1-9EE7-11D4-8111-00A02431D004")
			("5.1r6a" "243D4BAA-9EE7-11D4-8111-00A02431D004")
			)
    :splash-screen "g2-setup.bmp"
    :license-text "standard-license.txt")



(defvar g2-shortcut-folder-name "Gensym G2 7.0b0")

;;; Family G2 OK Files


;;; For g2-deployment, 4 is the standard number of clients.  For g2-development
;;; 1 is the standard number of clients.  For development, we supply this in
;;; increments of 1 up to 10, thereafter in increments of 4.  Deployment only
;;; has increments of 4.

(def-g2-ok-components (g2-development :obfuscate t)
    g2 "Development"
  (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
     (1 "-nov25-2002")
     (1 "-dec25-2002") (1 "-jan25-2003") (1 "-feb25-2003")
     (1 "-mar25-2003") (1 "-apr25-2003") (1 "-may25-2003")
     (1 "-jun25-2003") (1 "-jul25-2003") (1 "-aug25-2003")
     (1 "-sep25-2003") (1 "-oct25-2003") (1 "-nov25-2003")
     (1 "-dec25-2003") (1 "-jan25-2004") (1 "-feb25-2004")
     (1 "-mar25-2004") (1 "-apr25-2004") (1 "-may25-2004")
     ))

;; => (defvar g2-development-family-ok-components '(g2-development g2-development-4 ...))

(def-g2-ok-components (g2-deployment :obfuscate t) g2 "Deployment"
  (4 8 12 16 20 24 28 32))





;;;; Bundles


(defvar core-g2-components
  '(g2 telewindows gateway gda weblink javalink
    activexlink 
    corbalink opclink pibridge Oraclebridge Sybasebridge ODBCbridge gservice
    g2-readme))

(defvar additional-g2-deployment-components '(jre))

(defvar additional-g2-development-components '(jre doc-pdf doc-html doc-chm protools))


(def-bundle g2-deployment
    :components (core-g2-components
		  additional-g2-deployment-components 
		  g2-deployment-family-ok-components)
    :version :70b0
    :print-name "G2 Deployment"
    :directory "deployment")

(def-bundle g2-development
    :components (core-g2-components
		  additional-g2-development-components
		  g2-development-family-ok-components)
    :version :70b0
    :print-name "G2 Development"
    :directory "development")


(def-bundle tw-client
    :components (telewindows doc-chm)
    :version :70b0
    :print-name "Telewindows Client"
    :directory "client")


(def-bundle tw2-client
    :components (telewindows2)
    :version :12r5
    :print-name "Telewindows 2 Toolkit"
    :directory "tw2")

;;;; Components



(def-component g2
  :parts
  (g2-exe-intelnt g2-exe-unix
		  g2passwd-exe-intelnt g2passwd-exe-unix
		  index-dic kojin-dic main-dic ext-directory

		  ;; note: same files as for TW, may overwrite:
;;		  g2-gen16ut-dll-intelnt
;;		  g2-gen32-dll-intelnt
;;		  g2-gen32ut-dll-intelnt

		  g2-blank-ok

		  kbs fonts)
  :print-name "G2 (and utilities)")

(def-component telewindows
  :parts (tw-exe-intelnt
	   tw-exe-unix

	   tw-nptwplug-dll-intelnt
	   tw-nptwplug-dll-unix
	   twax twax-examples

	   ;; note: same files as for G2, may overwrite:
;;	   tw-gen16ut-dll-intelnt
;;	   tw-gen32-dll-intelnt
;;	   tw-gen32ut-dll-intelnt

	   ;; same in G2, OK to specify twice, may be overwritten:
	   fonts)
  :print-name "Telewindows")
(def-component telewindows2 :parts (tw2 tw2-intelnt tw2-javadoc tw2doc)
	       :include-in-contents :none
	       :print-name "Telewindows2 Toolkit")

(def-component gateway :parts (gsi) :print-name "G2 Gateway (GSI)")
(def-component gda :parts (gda) :print-name "G2 Diagnostic Assistant (GDA)")
(def-component weblink :parts (gw gsi-gw-ok run-gw-template-batfile gsi-gw-blank-ok) :print-name "G2 WebLink")
(def-component javalink
  :parts (jvl jvl-intelnt jvl-com-gensym-properties-intelnt jvl-javadoc)
  :print-name "G2 JavaLink")


(def-component activexlink
  :parts (axl-g2com-dll axl-gsi-dll axl-readme axl-g2com-kb axl-demos axl-runme-bat axl-regsvr)
  :platforms ("nt")
  :print-name "G2 ActiveXLink")

(def-component gservice
  :parts (gservice)
  :print-name "GService Startup Service"
  :platforms ("nt"))

(def-component doc-pdf
  :parts (g2doc-g2tutorials-pdf g2doc-g2refman-pdf g2doc-g2gateway-pdf
	   g2doc-g2classref-pdf g2doc-telewindows-pdf g2doc-g2sysprocs-pdf
	   g2doc-g2langrefcard-pdf g2doc-g2devguide-pdf
	   g2utldoc-gdi-pdf g2utldoc-gms-pdf g2utldoc-goldui-pdf
	   g2utldoc-guideuserguide-pdf g2utldoc-gdd-pdf g2utldoc-gfr-pdf
	   g2utldoc-golddev-pdf g2utldoc-guideprocref-pdf g2utldoc-gxl-pdf
	   jvldoc-javalink-pdf jvldoc-di-pdf jvldoc-bb-pdf axldoc corbalinkdoc
		 g2classicrn
		   g2oradoc g2sybdoc opclinkdoc g2pidoc g2odbcdoc
		   g2dbdoc protoolsdoc weblinkdoc gdadoc-api-pdf gdadoc-ug-pdf)
  :print-name "G2 Full Documentation (PDF)"
  :include-in-contents (g2doc-pdf)
  :typical false)

(def-component doc-html
  :parts (g2doc-g2refman-html g2doc-g2tutorials-html g2doc-g2gateway-html
	  g2doc-g2classref-html g2doc-telewindows-html g2doc-g2sysprocs-html
	  g2doc-g2langrefcard-html g2doc-g2devguide-html 
	  g2utldoc-gdi-html g2utldoc-gms-html g2utldoc-goldui-html
	  g2utldoc-guideuserguide-html g2utldoc-gdd-html g2utldoc-gfr-html
	  g2utldoc-golddev-html g2utldoc-guideprocref-html g2utldoc-gxl-html
	  jvldoc-javalink-html jvldoc-di-html jvldoc-bb-html axldoc-html corbalinkdoc-html 
	  g2oradoc-html g2sybdoc-html opclinkdoc-html g2pidoc-html g2odbcdoc-html
	  g2dbdoc-html protoolsdoc-html weblinkdoc-html gdadoc-api-html gdadoc-ug-html)
  :print-name "G2 Full Documentation (HTML/Gold)"
  :include-in-contents (g2doc-g2refman-html)
  :typical false)

(def-component doc-chm
  :platforms ("nt")
  :parts (doc-chm)
  :print-name "G2 Core Documentation (Windows Help)"
  :typical true)


(def-component g2-readme :parts (g2-readme) :print-name "G2 Readme")

(def-component protools :parts (protools profiler) :print-name "G2 ProTools")




;;; Optional Bridges in G2: Two bridges are standard (picked by the customer at
;;; order time), and others may be optionally chosen, i.e., at order time.
;;;
;;; Optional Bridges: (1) corbalink (2) opclink (3) Oraclebridge (4)
;;; Sybasebridge (5) ODBCbridge (6) Pi Bridge
;;;
;;; Note that there may be other components, e.g., Gateway (GW) and perhaps
;;; other components, that are technically bridges, but they're not necessarily
;;; marketed that way to customers.
;;;
;;; All of the optional bridges, those bridges marketed as such, are here,
;;; below, and bear the :optional=true flag.

(def-component corbalink :parts (corbalink)
	       :print-name "G2 CORBALink"
	       :non-platforms ("alphaosf")
	       :optional true)
(def-component opclink :parts (opclink gsi-opclink-ok run-G2Opc-template-batfile gsi-opclink-blank-ok) :platforms ("nt")
	       :print-name "G2 OPCLink Bridge"
	       :optional true)

(def-component pibridge :parts (g2pi gsi-pi-ok
				 run-g2-pi-template-batfile gsi-pi-blank-ok) :platforms ("nt")
	       :print-name "G2 PI Bridge"
	       :optional true)

(def-component Oraclebridge :parts (Oraclebridge gsi-Oracle-ok run-g2-ora7-template-batfile run-g2-ora80-template-batfile run-g2-ora81-template-batfile run-g2-ora9i-template-batfile gsi-Oracle-blank-ok)
	       :print-name "G2 Oracle Bridge"
	       :optional true)
(def-component Sybasebridge :parts (Sybasebridge gsi-Sybase-ok run-g2-sybase-template-batfile gsi-Sybase-blank-ok)
	       :print-name "G2 Sybase Bridge"
	       :non-platforms ("linux")
	       :optional true)
(def-component ODBCbridge :parts (ODBCbridge gsi-ODBC-ok run-g2-odbc-template-batfile gsi-ODBC-blank-ok) :platforms ("nt")
	       :print-name "G2 ODBC Bridge"
	       :optional true)





;;;; Parts



(def-part g2-exe-intelnt
    :version :70b0
    :print-name "G2 Windows Executable"
    :source g2
    :source-filename "g2.exe"
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (g2-shortcut))

(def-shortcut g2-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "G2"
    :application-directory "g2"
    :target-name "g2.exe"
    :parameters "-module-search-path kbs\\utils")

(def-part g2-exe-unix
    :version :70b0
    :print-name "G2 Unix Executable"
    :source g2
    :source-filename "g2"
    :destination-directory "g2"
    :non-platforms ("nt"))


(def-part g2passwd-exe-intelnt
    :version :70b0
    :print-name "G2PASSWD Windows Executable"
    :source g2
    :source-filename "g2passwd.exe"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2passwd-exe-unix
    :version :70b0
    :print-name "G2PASSWD Unix Executable"
    :source g2
    :source-filename "g2passwd"
    :destination-directory "g2"
    :non-platforms ("nt"))

(def-part g2-gen16ut-dll-intelnt
    :version :70b0
    :print-name "G2 Gen16UT DLL"
    :source g2
    :source-filename "gen16ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-gen32-dll-intelnt
    :version :70b0
    :print-name "G2 Gen32 DLL"
    :source g2
    :source-filename "gen32.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-gen32ut-dll-intelnt
    :version :70b0
    :print-name "G2 Gen32UT DLL"
    :source g2
    :source-filename "gen32ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-map-intelnt
    :version :70b0
    :print-name "G2 Map"
    :source g2
    :source-filename "g2.map"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-blank-ok
    :version :70b0
    :print-name "Sample G2 OK file"
    :source g2
    :source-filename "g2.ok"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part index-dic
    :version :70b0
    :print-name "Kanji index dictionary"
    :source g2
    :source-filename "index.dic"
    :destination-directory "g2")

(def-part kojin-dic
    :version :70b0
    :print-name "Kanji kojin dictionary"
    :source g2
    :source-filename "kojin.dic"
    :destination-directory "g2")

(def-part main-dic
    :version :70b0
    :print-name "Kanji main dictionary"
    :source g2
    :source-filename "main.dic"
    :destination-directory "g2")

(def-part ext-directory
    :version :70b0
    :print-name "G2 EXT Directory"
    :source g2
    :source-subdirectory "ext"
    :destination-directory "g2/ext")



(def-part tw-exe-intelnt
    :version :70b0
    :print-name "TW Windows Executable"
    :source tw
    :source-filename "tw.exe"
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (tw-shortcut))

(def-shortcut tw-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "Telewindows"
    :application-directory "g2"
    :target-name "tw.exe")

(def-part tw-exe-unix
    :version :70b0
    :print-name "TW Unix Executable"
    :source tw
    :source-filename "tw"
    :destination-directory "g2"
    :non-platforms ("nt"))

(def-part tw-nptwplug-dll-unix
    :version :70b0
    :print-name "TW Extensions"
    :source tw
    :source-filename ("nptwplug.so")
    :destination-directory "g2"
    :non-platforms ("nt"))

(def-part tw-nptwplug-dll-intelnt
    :version :70b0
    :print-name "TW Extensions"
    :source tw
    :source-filename ("nptwplug.dll")
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-gen16ut-dll-intelnt
    :version :70b0
    :print-name "TW Gen16UT DLL"
    :source tw
    :source-filename "gen16ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-gen32-dll-intelnt
    :version :70b0
    :print-name "TW Gen32 DLL"
    :source tw
    :source-filename "gen32.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-gen32ut-dll-intelnt
    :version :70b0
    :print-name "TW Gen32UT DLL"
    :source tw
    :source-filename "gen32ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-map-intelnt
    :version :70b0
    :print-name "TW Map"
    :source tw
    :source-filename "tw.map"
    :destination-directory "g2"
    :platforms ("nt"))


(def-part twax
    :version :70b0
    :source-filename ("TwControl.cab" "unregisterTwControl.bat" "TwControl.ocx"
		      "install.html" "registerTwControl.bat")
    :destination-directory "g2"
    :platforms ("nt"))

(def-part twax-examples
    :version :70b0
    :source twax
    :source-subdirectory examples
    :destination-directory "g2/examples"
    :platforms ("nt"))


(def-part kbs
  :version :70b0
  :destination-directory g2/kbs
  :indep t
  ;; KBs are read-only, which is not terribly bad by itself, but causes
  ;; a problem: doing uninstall on Windows.
  :make-not-read-only t)
(def-part fonts
    :version :70b0
    :destination-directory g2/fonts :indep t
    ;; fonts are read-only, which is not terribly bad by itself, but
    ;; causes these problems: using this part from both g2 and telewindow
    ;; components, and doing uninstall on Windows.
    :make-not-read-only t)
(def-part tw2
    :version :12r5
    :destination-directory tw2
    :non-platforms ("nt"		; has its own part
		     ))

(def-part tw2-javadoc
    :version :12r5
    :destination-directory "doc/tw2/Java"
    :shortcuts (tw2-javadoc)
    :indep t)

(def-shortcut tw2-javadoc
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "API Documentation"
    :application-directory "doc\\tw2\\Java\\docs\\api"
    :target-name "index.html")

(def-part tw2-intelnt
    :version :12r5
    :source tw2
    :source-subdirectory "components"
    ;; for building tree:  handled by bundle.lisp, not in family file. -mhd
    :remove-from-source ("bin/unInstall.bat" "bin/unInstaller.bat") ; remove component installer stuff
    :destination-directory tw2
    :platforms ("nt")
    :postinstall-code "replace_rootdir(\"tw2\"^\"bin\", \"envvars.bat\");"
    :shortcuts (tw2-toolkit-demo
		 tw2-demo
		 ;;		       tw2-component-editor
		 tw2-readme
		 tw2-itemaccessdemo
		 tw2-internationalizationdemo
		 tw2-palettedemo

		 ;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
		 ;; 		       ;; ActiveX:
		 ;; 		       tw2-activex-install-controls
		 ;; 		       tw2-activex-uninstall-controls
		 ;; 		       tw2-activex-mill-demo
		 ;; 		       tw2-activex-shell-demo
		 ))

(def-shortcut tw2-toolkit-demo
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Default Application Shell"
    :application-directory "tw2\\bin"
    :target-name "shell.bat")

(def-shortcut tw2-demo
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Demo"
    :application-directory "tw2\\bin"
    :target-name "t2demo.bat")

(def-shortcut tw2-itemaccessdemo
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Item Access Demo"
    :application-directory "tw2\\classes\\com\\gensym\\demos\\itemaccessdemo"
    :target-name "rundemo.bat")

(def-shortcut tw2-internationalizationdemo
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Internationalization Demo"
    :application-directory "tw2\\classes\\com\\gensym\\demos\\internationalizationdemo"
    :target-name "rundemo.bat")

(def-shortcut tw2-palettedemo
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Palette Demo"
    :application-directory "tw2\\classes\\com\\gensym\\demos\\palettedemo"
    :target-name "rundemo.bat")

;; Removed from G2 Classic product:
;; (def-shortcut tw2-component-editor
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :application-display-name "Component Editor"
;;     :application-directory "tw2\\bin"
;;     :target-name "beaneditor.bat")

(def-shortcut tw2-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Readme for Telewindows2 Toolkit"
    :application-directory "tw2"
    :target-name "readme-tw2.html")


;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
;;
;; ;; TW2 Tooklit ActiveX Shortcuts:
;; 
;; (def-shortcut tw2-activex-install-controls
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Install Controls"
;;     :application-directory "tw2\\bin"
;;     :target-name "InstallControls.bat")
;; 
;; (def-shortcut tw2-activex-uninstall-controls
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Uninstall Controls"
;;     :application-directory "tw2\\bin"
;;     :target-name "unInstallControls.bat")
;; 
;; (def-shortcut tw2-activex-mill-demo
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Visual Basic Mill Demo"
;;     :application-directory "tw2\\ActiveX\\vbdemo"
;;     :target-name "VbDemo.bat")
;; 
;; (def-shortcut tw2-activex-shell-demo
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Visual Basic Telewindows2 Shell"
;;     :application-directory "tw2\\ActiveX\\vbShell"
;;     :target-name "Tw2Prj.exe")
;; 
;; (def-shortcut tw2-activex-help
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Telewindows2 Toolkit for ActiveX Reference Manual"
;;     :application-directory "tw2\\ActiveX"
;;     :target-name "AXClient.hlp")

;; Documentation Shortcuts
(def-shortcut g2-release-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "G2 Bundle Release Notes"
    :application-directory "doc"
    :target-name "g2relnotes.pdf")

(def-shortcut g2-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Reference Manual"
    :application-directory "doc\\g2\\g2refman"
    :target-name "g2refman.pdf")

(def-shortcut g2-reference-card
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Language Reference Card"
    :application-directory "doc\\g2\\g2langrefcard"
    :target-name "g2langrefcard.pdf")

(def-shortcut g2-system-procedures-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 System Procedures Reference Manual"
    :application-directory "doc\\g2\\g2sysprocs"
    :target-name "g2sysprocs.pdf")

(def-shortcut g2-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Getting Started with G2 Tutorials"
    :application-directory "doc\\g2\\g2tutorials"
    :target-name "g2tutorials.pdf")

(def-shortcut g2-class-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Class Reference Manual"
    :application-directory "doc\\g2\\g2classref"
    :target-name "g2classref.pdf")

;; not included in 5.2r0 bundle
(def-shortcut g2-developers-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Developer's Guide"
    :application-directory "doc\\g2\\g2devguide"
    :target-name "g2devguide.pdf")

(def-shortcut g2-dynamic-displays-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Dynamic Displays User's Guide"
    :application-directory "doc\\utilities\\gdd"
    :target-name "gdd.pdf")

(def-shortcut g2-developers-interface-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Developer's Interface User's Guide"
    :application-directory "doc\\utilities\\gdi"
    :target-name "gdi.pdf")

(def-shortcut g2-foundation-resources-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Foundation Resources User's Guide"
    :application-directory "doc\\utilities\\gfr"
    :target-name "gfr.pdf")

(def-shortcut g2-menu-system-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Menu System User's Guide"
    :application-directory "doc\\utilities\\gms"
    :target-name "gms.pdf")

(def-shortcut g2-online-documentation-developers-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation Developer's Guide"
    :application-directory "doc\\utilities\\golddev"
    :target-name "golddev.pdf")

(def-shortcut g2-online-documentation-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation User's Guide"
    :application-directory "doc\\utilities\\goldui"
    :target-name "goldui.pdf")

(def-shortcut g2-guide-uil-procedures-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE UIL Procedures Reference Manual"
    :application-directory "doc\\utilities\\guideprocref"
    :target-name "guideprocref.pdf")

(def-shortcut g2-guide-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE User's Guide"
    :application-directory "doc\\utilities\\guideuserguide"
    :target-name "guideuserguide.pdf")

(def-shortcut g2-xl-spreadsheet-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 XL Spreadsheet User's Guide"
    :application-directory "doc\\utilities\\gxl"
    :target-name "gxl.pdf")



;; GDA

(def-shortcut gda-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA User's Guide"
    :application-directory "doc\\gda\\gdaugrm"
    :target-name "gdaug.pdf")

(def-shortcut gda-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA Reference Manual"
    :application-directory "doc\\gda\\gdaugrm"
    :target-name "gdarefman.pdf")

(def-shortcut gda-api-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA API Reference Manual"
    :application-directory "doc\\gda\\gdaapi"
    :target-name "gdaapi.pdf")


;; G2 ProTools

(def-shortcut g2-protools-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 ProTools User's Guide"
    :application-directory "doc\\utilities\\g2protools"
    :target-name "g2protools.pdf")

;; G2 Gateway (GSI)

(def-shortcut gsi-bridge-developers-guide
    ;; "Everyone knows this informally as 'the GSI manual'". --peter k.
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Gateway Bridge Developer's Guide"
    :application-directory "doc\\g2\\g2gateway"
    :target-name "g2gateway.pdf")

;; Bridges

(def-shortcut g2-database-bridge-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 Database Bridge User's Guide"
    :application-directory "doc\\bridges\\db"
    :target-name "g2databasebridge.pdf")

(def-shortcut g2-opclink-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 OPCLink User's Guide"
;;review for final!
;;    :application-directory "opclink"
;;    :target-name "G2-OPCLink-Client-for-Gensym-G2-Manual.pdf"
    :application-directory "doc\\bridges\\opclink"
    :target-name "g2opclink.pdf")


(def-shortcut g2-corba-link-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 CORBALink User's Guide"
    :application-directory "doc\\bridges\\corbalink"
    :target-name "g2corbalink.pdf")

(def-shortcut g2-odbc-bridge-release-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-ODBC Bridge Release Notes"
    :application-directory "doc\\bridges\\odbc"
    :target-name "g2odbcbridge.pdf")

(def-shortcut g2-oracle-bridge-release-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Oracle Bridge Release Notes"
    :application-directory "doc\\bridges\\oracle"
    :target-name "g2oraclebridge.pdf")

(def-shortcut g2-sybase-bridge-release-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Sybase Bridge Release Notes"
    :application-directory "doc\\bridges\\sybase"
    :target-name "g2sybasebridge.pdf")


;; Telewindows

(def-shortcut telewindows-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Telewindows User's Guide"
    :application-directory "doc\\g2\\telewindows"
    :target-name "telewindows.pdf")



;; Telewindows2 Toolkit
			   
(def-shortcut tw2-release-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Release Notes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\t2relnotes"
    :target-name "t2relnotes.pdf")

(def-shortcut bean-exporter-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "BeanXporter User's Guide"
    :application-directory "doc\\tw2\\java\\docs\\guides\\beanxporter"
    :target-name "beanXporter.pdf")

(def-shortcut tw2-components-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Components and Core Classes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\t2components"
    :target-name "t2components.pdf")

(def-shortcut tw2-application-classes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Application Classes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\t2javadevguide"
    :target-name "t2javadevguide.pdf")

(def-shortcut tw2-demos-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Demos Guide"
    :application-directory "doc\\tw2\\java\\docs\\guides\\t2javademos"
    :target-name "t2javademos.pdf")



;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
;; (def-shortcut telewindows2-toolkit-activex-developers-guide
;;     :folder-name g2-shortcut-folder-name
;;     :subfolder-name "Documentation"
;;     :subsubfolder-name "Telewindows2 Toolkit"
;;     :application-display-name "Telewindows2 Toolkit ActiveX Developer's Guide"
;;     :application-directory "doc\\tw2\\ActiveX\\docs\\guides\\ActiveXDevelopersGuide"
;;     :target-name "titlepag.htm")
			                 

;; Javalink

(def-shortcut g2-download-interfaces-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 DownloadInterfaces User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2downloadinterfaces"
    :target-name "g2downloadinterfaces.pdf")

(def-shortcut g2-beanbuilder-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 Bean Builder User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2beanbuilder"
    :target-name "g2beanbuilder.pdf")

(def-shortcut g2-javalink-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 JavaLink User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2javalink"
    :target-name "g2javalink.pdf")




;; G2 ActiveXLink

(def-shortcut g2-activexlink-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 ActiveXLink User's Guide"
    :application-directory "doc\\bridges\\activexlink"
    :target-name "g2activexlink.pdf")

;; G2 WebLink

(def-shortcut g2-weblink-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 WebLink User's Guide"
    :application-directory "doc\\bridges\\weblink"
    :target-name "g2weblink.pdf")

(def-part gsi
    :version :70b0
    :destination-directory gsi)

(def-part gservice
    :version :70b0
    :source gservice
    :source-filename "gservice.exe"
    :destination-directory g2
    :platforms ("nt"))
    

(def-part gda
    :version :42r0
    :destination-directory gda
    :indep t)


(def-part gw
  :version :10r5
  :source gw
  :destination-directory gw)

(def-part run-gw-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-gw.bat"
    :destination-directory gw
    :postinstall-code "replace_rootdir(\"gw\", \"run-gw.bat\");"
    :shortcuts (gw-shortcut))

(def-shortcut gw-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "G2 WebLink"
    :application-directory "gw"
    :target-name "run-gw.bat")



;;; The part jvl-com-gensym-properties-intelnt sets up a template
;;; .com.gensym.properties file in the classes, and also arranges through
;;; postinstall code to have that file overwritten with substitutions from the
;;; template file that normally lives in the bin directory.  Having the template
;;; file preexist just ensures that uninstalling will remove that file, so it
;;; can clean up everything.  (I had to copy the current 11r0
;;; .com.gensym.properties to
;;; /development/installers/release-files/.com.gensym.properties to make this
;;; work. --mhd, 12/11/00)

(def-part jvl-com-gensym-properties-intelnt
    :destination-directory "javalink/classes"
    :source "/home/development/installers/release-files"
    :source-filename ".com.gensym.properties"
    :platforms ("nt")
    :postinstall-code
    "FixupPropertiesFile(TARGETDIR^\"javalink\"^\"bin\", \".com.gensym.properties\", TARGETDIR^\"javalink\", \"classes\", \".com.gensym.properties\");")

(def-part jvl-intelnt
  :version :12r5
  :source jvl
  :destination-directory javalink
  :postinstall-code "replace_rootdir(\"javalink\"^\"bin\", \"envvars.bat\");"

  ;; the semantics of the special source directive is to only copy those files
  :platforms ("nt") :source-subdirectory "components"
  :shortcuts (jvl-interface-downloader
	      jvl-install-properties
	      jvl-bean-builder
	      jvl-example-readme
	      jvl-known-problems
	      jvl-readme))

(def-shortcut jvl-interface-downloader
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Download Interfaces"
    :application-directory "javalink\\bin"
    :target-name "Downloadinterfaces.bat")

;; Note: Downloadinterfaces can be considered the main application for the
;; Javalink component.

(def-shortcut jvl-bean-builder
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "G2 Bean Builder"
    :application-directory "javalink\\bin"
    :target-name "G2BeanBuilder.bat")

(def-shortcut jvl-install-properties
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Install Properties"
    :application-directory "javalink\\bin"
    :target-name "InstallProperties.bat")

(def-shortcut jvl-example-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Examples Readme"
    :application-directory "javalink"
    :target-name "ExamplesReadme.html")

(def-shortcut jvl-known-problems
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Known Problems"
    :application-directory "javalink"
    :target-name "KnownProblems.html")

(def-shortcut jvl-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Readme for G2 JavaLink"
    :application-directory "javalink"
    :target-name "readme-javalink.html")




(def-part jvl
  :version :12r5
  :destination-directory javalink
  :non-platforms ("nt"			; has its own part
		  ))

(def-part jvl-javadoc
    :version :12r5
    :destination-directory doc/javalink
    :shortcuts (jvl-javadoc)
    :indep t)

(def-shortcut jvl-javadoc
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "API Documentation"
    :application-directory "doc\\javalink\\docs\\api"
    :target-name "index.html")

; should this be in a bridges directory?  Or should all the bridges be in the G2 directory?
(def-part corbalink
  :version :10r2
  :destination-directory corbalink
  :non-platforms ("alphaosf" "linux" "aix"))

;; ActiveXLink Parts:

(def-part axl-g2com-dll
    :version :10r5
    :source axl
    :source-filename "G2Com.dll"
    :register true			; Active X Control
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-gsi-dll
    :version :10r5
    :source axl
    :source-filename "gsi.dll"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-readme
    :version :10r5
    :source axl
    :source-filename "ReadMe.htm"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-g2com-kb
    :version :10r5
    :source axl
    :source-filename "g2com.kb"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-demos
    :version :10r5
    :source axl
    :source-subdirectory "demos"
    :destination-directory activexlink/demos
    :platforms ("nt"))

(def-part axl-runme-bat
    :version :10r5
    :source axl
    :source-filename "runme.bat"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-regsvr
    :version :10r5
    :source axl
    :source-filename "regsvr32.exe"
    :destination-directory activexlink
    :platforms ("nt"))

;; Doc is now its own part, axldoc, and goes with doc/bridges, q.v., below.


;; utilities

(def-part g2utldoc-gdi-pdf
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gdi
    :indep t
    :source-filename ("gdi.pdf")
    :source-subdirectory gdi)

(def-part g2utldoc-gms-pdf
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gms
    :indep t
    :source-filename ("gms.pdf")
    :source-subdirectory gms)

(def-part g2utldoc-goldui-pdf
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/goldui
    :indep t
    :source-filename ("goldui.pdf")
    :source-subdirectory goldui)

(def-part g2utldoc-guideuserguide-pdf
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/guideuserguide
    :indep t
    :source-filename ("guideuserguide.pdf")
    :source-subdirectory guideuserguide)

(def-part g2utldoc-gdd-pdf
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gdd
    :indep t
    :source-filename ("gdd.pdf")
    :source-subdirectory gdd)

(def-part g2utldoc-gfr-pdf
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gfr
    :indep t
    :source-filename ("gfr.pdf")
    :source-subdirectory gfr)

(def-part g2utldoc-golddev-pdf
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/golddev
    :indep t
    :source-filename ("golddev.pdf")
    :source-subdirectory golddev)

(def-part g2utldoc-guideprocref-pdf
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/guideprocref
    :indep t
    :source-filename ("guideprocref.pdf")
    :source-subdirectory guideprocref)

(def-part g2utldoc-gxl-pdf
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gxl
    :indep t
    :source-filename ("gxl.pdf")
    :source-subdirectory gxl)

(def-part g2utldoc-gdi-html
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gdi/html
    :indep t
    :source-subdirectory gdi/html)

(def-part g2utldoc-gms-html
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gms/html
    :indep t
    :source-subdirectory gms/html)

(def-part g2utldoc-goldui-html
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/goldui/html
    :indep t
    :source-subdirectory goldui/html)

(def-part g2utldoc-guideuserguide-html
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/guideuserguide/html
    :indep t
    :source-subdirectory guideuserguide/html)

(def-part g2utldoc-gdd-html
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gdd/html
    :indep t
    :source-subdirectory gdd/html)

(def-part g2utldoc-gfr-html
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gfr/html
    :indep t
    :source-subdirectory gfr/html)

(def-part g2utldoc-golddev-html
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/golddev/html
    :indep t
    :source-subdirectory golddev/html)

(def-part g2utldoc-guideprocref-html
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/guideprocref/html
    :indep t
    :source-subdirectory guideprocref/html)

(def-part g2utldoc-gxl-html
    :source g2utldoc
    :version :70b0
    :destination-directory doc/utilities/gxl/html
    :indep t
    :source-subdirectory gxl/html)



(def-part protoolsdoc
    :version :70b0
    :destination-directory doc/utilities/g2protools
    :source-subdirectory g2protools
    :indep t :source-filename ("g2protools.pdf"))

(def-part protoolsdoc-html
    :source protoolsdoc
    :version :70b0
    :destination-directory doc/utilities/g2protools/html
    :indep t :source-subdirectory g2protools/html)

(def-part gdadoc-api-pdf
    :source gdadoc
    :version :42r0
    :destination-directory doc/gda/gdaapi
    :source-filename ("gdaapi.pdf")
    :indep t :source-subdirectory gda/gdaapi)

(def-part gdadoc-ug-pdf
    :source gdadoc
    :version :42r0
    :destination-directory doc/gda/gdaugrm
    :source-filename ("gdarefman.pdf" "gdaug.pdf")
    :indep t :source-subdirectory gda/gdaugrm)

(def-part gdadoc-api-html
    :source gdadoc
    :version :42r0
    :destination-directory doc/gda/gdaapi/html
    :indep t :source-subdirectory gda/gdaapi/html)

(def-part gdadoc-ug-html
    :source gdadoc
    :version :42r0
    :destination-directory doc/gda/gdaugrm/html
    :indep t :source-subdirectory gda/gdaugrm/html)

(def-part weblinkdoc
    :version :10r5
    :destination-directory doc/bridges/weblink
    :indep t
    :source-subdirectory weblink
    :source-filename ("g2weblink.pdf"))

(def-part weblinkdoc-html
    :source weblinkdoc
    :version :10r5
    :destination-directory doc/bridges/weblink/html
    :indep t :source-subdirectory weblink/html)

(def-part g2classicrn
    :version :70b0
    :source-filename "g2relnotes.pdf"
    :indep t
    :destination-directory doc)

;; reference manual

(def-part g2doc-g2refman-pdf
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2refman
    :source-subdirectory g2refman
    :indep t
    :source-filename ("g2refman.pdf")
        ;; Off of this part hang all the doc shortcuts.  Some of them could hang off
    ;; of their real parts, but (a) it's a lot more work; (b) some of them use
    ;; doc in parts that are not of the DOC component.  I don't want to hang off
    ;; of those parts because then you could get doc shortcuts without being
    ;; authorized for the doc component, which seems strange.  (Of course, it's
    ;; strange to give the doc in the first place, but that's another story.)
    ;; (MHD 12/8/00) 

    ;;yduJ 6/24/02: there are many fewer of these components that contain
    ;;documentation within them then there used to be, so it is less strange.
        :shortcuts (
		;; Note: there seem to be bugs in InstallShield and/or
		;; InstallGenerator and/or the commented out shortcuts here.  For
		;; now, leave them uncommented; this set was carefully determined by
		;; expirimentation to work, whereas with some or all of the commented
		;; out shortcuts, there was failure: "unknown error". (MHD 12/11/00)
		g2-release-notes
		g2-reference-manual
		 g2-reference-card
		 ;;g2-release-notes-update;;not included in 6.0b1
		 g2-system-procedures-reference-manual
		 g2-tutorial
		 g2-class-reference-manual
		 g2-developers-guide	    ;;not included in 6.0b1
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
		 ;; GDA:
		 gda-users-guide
		 gda-reference-manual
		 gda-api-reference-manual
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

		 ;; Javalink
		 g2-download-interfaces-guide
		 g2-beanbuilder-guide
		 g2-javalink-guide
		 ;; ActiveXLink
		 g2-activexlink-users-guide
		 ;; Weblink
		 g2-weblink-users-guide))

(def-part g2doc-g2tutorials-pdf
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2tutorials
    :source-subdirectory g2tutorials
    :indep t
    :source-filename ("g2tutorials.pdf"))

(def-part g2doc-g2gateway-pdf
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2gateway
    :source-subdirectory g2gateway
    :indep t
    :source-filename ("g2gateway.pdf"))

(def-part g2doc-g2classref-pdf
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2classref
    :source-subdirectory g2classref
    :indep t
    :source-filename ("g2classref.pdf"))

(def-part g2doc-telewindows-pdf
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/telewindows
    :source-subdirectory telewindows
    :indep t
    :source-filename ("telewindows.pdf"))

(def-part g2doc-g2sysprocs-pdf
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2sysprocs
    :source-subdirectory g2sysprocs
    :indep t
    :source-filename ("g2sysprocs.pdf"))

(def-part g2doc-g2langrefcard-pdf
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2langrefcard
    :source-subdirectory g2langrefcard
    :indep t
    :source-filename ("g2langrefcard.pdf"))

(def-part g2doc-g2devguide-pdf
    :source g2doc
    :version :70b0
    :source-subdirectory g2devguide
    :source g2doc
    :destination-directory doc/g2/g2devguide
    :indep t
    :source-filename ("g2devguide.pdf"))



(def-part g2doc-g2tutorials-html
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2tutorials/html
    :source-subdirectory g2tutorials/html
    :indep t)

(def-part g2doc-g2refman-html
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2refman/html
    :source-subdirectory g2refman/html
    :indep t)

(def-part g2doc-g2gateway-html
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2gateway/html
    :source-subdirectory g2gateway/html
    :indep t)

(def-part g2doc-g2classref-html
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2classref/html
    :source-subdirectory g2classref/html
    :indep t)

(def-part g2doc-telewindows-html
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/telewindows/html
    :source-subdirectory telewindows/html
    :indep t)

(def-part g2doc-g2sysprocs-html
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2sysprocs/html
    :source-subdirectory g2sysprocs/html
    :indep t)

(def-part g2doc-g2langrefcard-html
    :source g2doc
    :version :70b0
    :source g2doc
    :destination-directory doc/g2/g2langrefcard/html
    :source-subdirectory g2langrefcard/html
    :indep t)

(def-part g2doc-g2devguide-html
    :source g2doc
    :version :70b0
    :source-subdirectory g2devguide/html
    :source g2doc
    :destination-directory doc/g2/g2devguide/html
    :indep t)


(def-part doc-chm
    :version :70b0
    :source-filename ("G2BundleReleaseNotesHelp.chm" "G2ClassReferenceHelp.chm" "G2Core.html"
		       "G2DevelopersGuideHelp.chm" "G2LanguageReferenceHelp.chm" "G2ProToolsHelp.chm"
		       "G2ReferenceManualHelp.chm" "G2SystemProceduresHelp.chm" "G2Utilities.html"
		       "GDDHelp.chm" "GDIHelp.chm" "GFRHelp.chm" "GMSHelp.chm"
		       "GOLDDevelopersGuideHelp.chm" "GOLDHelp.chm" "GUIDEHelp.chm"
		       "GUIDEUILHelp.chm" "GXLHelp.chm" "GettingStarted.html"
		       "GettingStartedWithG2Help.chm" "Master.CHM" "Master.html"
		       "Master2.html" "Master3.html" "TelewindowsHelp.chm")
    :source g2winhelp
    :destination-directory g2
    :indep t)

;; Documentation for bridges - Javalink, ActiveXLink, TW2, Corbalink, Oracle, Sybase, OPCLink, ODBC:

(def-part jvldoc-javalink-pdf
    :source jvldoc
    :version :12r5
    :destination-directory doc/javalink/docs/guides/g2javalink
    :indep t
    :source-filename ("g2javalink.pdf")
    :source-subdirectory docs/guides/g2javalink
    )

(def-part jvldoc-di-pdf
    :source jvldoc
    :version :12r5
    :destination-directory doc/javalink/docs/guides/g2downloadinterfaces
    :indep t
    :source-filename ("g2downloadinterfaces.pdf")
    :source-subdirectory docs/guides/g2downloadinterfaces
    )

(def-part jvldoc-bb-pdf
    :source jvldoc
    :version :12r5
    :destination-directory doc/javalink/docs/guides/g2beanbuilder
    :indep t
    :source-filename ("g2beanbuilder.pdf")
    :source-subdirectory docs/guides/g2beanbuilder
    )

(def-part jvldoc-javalink-html
    :source jvldoc
    :version :12r5
    :destination-directory doc/javalink/docs/guides/g2javalink/html
    :indep t
    :source-subdirectory docs/guides/g2javalink/html
    )

(def-part jvldoc-di-html
    :source jvldoc
    :version :12r5
    :destination-directory doc/javalink/docs/guides/g2downloadinterfaces/html
    :indep t
    :source-subdirectory docs/guides/g2downloadinterfaces/html
    )

(def-part jvldoc-bb-html
    :source jvldoc
    :version :12r5
    :destination-directory doc/javalink/docs/guides/g2beanbuilder/html
    :indep t
    :source-subdirectory docs/guides/g2beanbuilder/html
    )

(def-part axldoc
    :version :10r5
    :destination-directory doc/bridges/activexlink
    :platforms ("nt")
    :indep t :source-filename "g2activexlink.pdf"
    :source-subdirectory activexlink)

(def-part axldoc-html
    :source axldoc
    :version :10r5
    :destination-directory doc/bridges/activexlink/html
    :platforms ("nt")
    :indep t
    :source-subdirectory activexlink/html)

(def-part tw2doc
    :version :12r2
    :destination-directory doc/tw2
    :indep t
    :shortcuts (
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
		 ))

(def-part corbalinkdoc
    :version :10r2
    :destination-directory doc/bridges/corbalink
    :indep t
    :source-filename ("g2corbalink.pdf")
    :source-subdirectory corbalink)

(def-part corbalinkdoc-html
    :source corbalinkdoc
    :version :10r2
    :destination-directory doc/bridges/corbalink/html
    :indep t
    :source-subdirectory corbalink/html)
(def-part g2oradoc
    :version :60r9
    :destination-directory doc/bridges/oracle
    :indep t :source-filename ("g2oraclebridge.pdf")
    :source-subdirectory oracle)


(def-part g2oradoc-html
    :source g2oradoc
    :version :60r9
    :destination-directory doc/bridges/oracle/html
    :indep t
    :source-subdirectory oracle/html)
(def-part g2sybdoc
    :version :60r9
    :destination-directory doc/bridges/sybase
    :indep t
    :source-filename ("g2sybasebridge.pdf")
    :source-subdirectory sybase)
(def-part g2sybdoc-html
    :source g2sybdoc
    :version :60r9
    :destination-directory doc/bridges/sybase/html
    :indep t
    :source-subdirectory sybase/html)
(def-part opclinkdoc
    :version :21r0
    :destination-directory doc/bridges/opclink
    :indep t
    :source-filename ("g2opclink.pdf")
    :source-subdirectory opclink
    )
(def-part opclinkdoc-html
    :source opclinkdoc
    :version :21r0
    :destination-directory doc/bridges/opclink/html
    :indep t
    :source-subdirectory opclink/html)
(def-part g2odbcdoc
    :version :60r9
    :destination-directory doc/bridges/odbc
    :indep t
    :source-filename ("g2odbcbridge.pdf")
    :source-subdirectory odbc
    )
(def-part g2odbcdoc-html
    :source g2odbcdoc
    :version :60r9
    :destination-directory doc/bridges/odbc/html
    :indep t
    :source-subdirectory odbc/html)
(def-part g2pidoc
    :version :50b0
    :destination-directory doc/bridges/pi
    :source-subdirectory pi
    :indep t
    :source-filename ("g2pibridge.pdf")
    )
(def-part g2pidoc-html
    :source g2pidoc
    :version :50b0
    :destination-directory doc/bridges/pi/html
    :indep t
    :source-subdirectory pi/html)

(def-part g2dbdoc
    :version :60r9
    :destination-directory doc/bridges/db
    :source-subdirectory db
    :indep t :source-filename ("g2databasebridge.pdf"))

(def-part g2dbdoc-html :source g2dbdoc
    :version :60r9
    :destination-directory doc/bridges/db/html
    :indep t :source-subdirectory db/html)

(def-part protools
    :version :70b0
    :source protools
    :destination-directory protools/kbs
    :source-filename ("protools.kb" "ptroot.kb")
    :indep t)

(def-part profiler
    :version :70b0
    :source protools
    :source-filename ("profiler.kb" "profroot.kb")
    :destination-directory g2/kbs/utils
    :indep t)

(def-gsi-bridge-ok-parts (:obfuscate t)
    gw pi opclink odbc oracle sybase)


(def-part g2-readme
    :source g2pkgreadme
    :version :70b0
    :source-filename "readme-g2.html"
    :indep t 
    :shortcuts (g2-readme))

(def-shortcut g2-readme
    :folder-name g2-shortcut-folder-name
    :application-display-name "Readme for G2 Bundle"
    :application-directory ""
    :target-name "readme-g2.html")


(def-part opclink
    :version :21r0
    :destination-directory opclink)

(def-part run-G2Opc-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-G2Opc.bat"
    :destination-directory opclink
    :postinstall-code "replace_rootdir(\"opclink\", \"run-G2Opc.bat\");"
    :shortcuts (opclink-shortcut))

(def-shortcut opclink-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 OPCLink Bridge"
    :application-directory "opclink"
    :target-name "run-G2Opc.bat")

(def-part g2pi
    :version :50b0
    :destination-directory pi)

(def-part run-g2-pi-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-pi.bat"
    :destination-directory pi
    :postinstall-code "replace_rootdir(\"pi\", \"run-g2-pi.bat\");"
    :shortcuts (pi-shortcut))

(def-shortcut pi-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 PI Bridge"
    :application-directory "pi"
    :target-name "run-g2-pi.bat")


(def-part Sybasebridge
    :version :60r9
    :source g2sybase
    :destination-directory sybase
    :non-platforms ("linux")) ; "linux" does not exist for sybase

(def-part run-g2-sybase-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-sybase.bat"
    :destination-directory sybase
    :postinstall-code "replace_rootdir(\"sybase\", \"run-g2-sybase.bat\");"
    :shortcuts (sybase-shortcut))

(def-shortcut sybase-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Sybase Bridge"
    :application-directory "sybase"
    :target-name "run-g2-sybase.bat")



(def-part ODBCbridge
    :version :60r9
    :source g2odbc
    :destination-directory odbc
    :platforms ("nt"))

(def-part run-g2-odbc-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-odbc.bat"
    :destination-directory odbc
    :postinstall-code "replace_rootdir(\"odbc\", \"run-g2-odbc.bat\");"
    :shortcuts (odbc-shortcut))

(def-shortcut odbc-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 ODBC Bridge"
    :application-directory "odbc"
    :target-name "run-g2-odbc.bat")


(def-part Oraclebridge
    :version :60r9
    :source g2oracle
    :destination-directory oracle)

(def-part run-g2-ora7-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora7.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora7.bat\");"
    :shortcuts (ora7-shortcut))

(def-part run-g2-ora80-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora80.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora80.bat\");"
    :shortcuts (ora80-shortcut))

(def-part run-g2-ora81-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora81.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora81.bat\");"
    :shortcuts (ora81-shortcut))

(def-part run-g2-ora9i-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora9i.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora9i.bat\");"
    :shortcuts (ora9i-shortcut))

(def-shortcut ora7-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Oracle 7 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora7.bat")

(def-shortcut ora80-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Oracle 8.0 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora80.bat")

(def-shortcut ora81-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Oracle 8.1 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora81.bat")

(def-shortcut ora9i-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Oracle 9i Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora9i.bat")



;; currently jre is only on Intel NT.  We should be downloading jre on
;; other platforms and providing it on them as well.

(def-component jre
    :print-name "Java Runtime Environment"
    :parts (jre)
    :platforms ("nt"))

(def-part jre
    :version :13r1_01
    :source "jre"
    :platforms ("nt")
    :destination-directory "jre")
