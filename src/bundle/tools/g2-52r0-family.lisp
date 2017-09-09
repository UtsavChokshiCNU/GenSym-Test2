;; -*- mode: lisp; package: bundle -*-

(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; G2-FAMILY - G2 Family Definitions.  Requires bundle.lisp.

;; Mark H. David


(provide 'g2-52r0-family)





;;;; Families



(def-family G2-52r0
    :index 7
    :file-syntax-version 10
    :bundles (G2-Deployment G2-Development)
    :print-name "G2"
    :directory "g2classic"
    :guid "243D4BBC-9EE7-11D4-8111-00A02431D004" ; 5.2r0
    :previous-versions (("5.2b1" "243D4BB9-9EE7-11D4-8111-00A02431D004")
			("5.1r7" "243D4BB1-9EE7-11D4-8111-00A02431D004")
			("5.1r6a" "243D4BAA-9EE7-11D4-8111-00A02431D004")
			;; add more here
			)
    :splash-screen "g2-setup.bmp"
    :license-text "standard-license.txt")





;;; Family G2 OK Files


;;; For g2-deployment, 4 is the standard number of clients.  For g2-development
;;; 1 is the standard number of clients.  For development, we supply this in
;;; increments of 1 up to 10, thereafter in increments of 4.  Deployment only
;;; has increments of 4.

(def-g2-ok-components (g2-development :obfuscate t)
    g2 "Development"
  (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
     (1 "-jun25-2001") (1 "-jul25-2001") (1 "-aug25-2001")
     (1 "-sep25-2001") (1 "-oct25-2001") (1 "-nov25-2001")
     (1 "-dec25-2001") (1 "-jan25-2002") (1 "-feb25-2002")
     (1 "-mar25-2002") (1 "-apr25-2002") (1 "-may25-2002")
     (1 "-jun25-2002") (1 "-jul25-2002") (1 "-aug25-2002")))

;; => (defvar g2-development-family-ok-components '(g2-development g2-development-4 ...))

(def-g2-ok-components (g2-deployment :obfuscate t) g2 "Deployment"
  (4 8 12 16 20 24 28 32))





;;;; Bundles


(defvar core-g2-components
  '(g2 telewindows telewindows2 gateway gda weblink javalink 
    activexlink
    corbalink opclink Oraclebridge Sybasebridge ODBCbridge
    g2-readme))

(defvar additional-g2-deployment-components '())

(defvar additional-g2-development-components '(documentation protools))


(def-bundle g2-deployment
    :components (core-g2-components
		  additional-g2-deployment-components 
		  g2-deployment-family-ok-components)
    :version :52r0
    :print-name "G2 Deployment"
    :directory "deployment")

(def-bundle g2-development
    :components (core-g2-components
		  additional-g2-development-components
		  g2-development-family-ok-components)
    :version :52r0
    :print-name "G2 Development"
    :directory "development")





;;;; Components



(def-component g2
  :parts
  (g2-exe-intelnt g2-exe-unix
		  g2passwd-exe-intelnt g2passwd-exe-unix
		  index-dic kojin-dic main-dic ext-directory

		  ;; note: same files as for TW, may overwrite:
		  g2-gen16ut-dll-intelnt
		  g2-gen32-dll-intelnt
		  g2-gen32ut-dll-intelnt

		  g2-blank-ok

		  kbs fonts)
  :print-name "G2")

(def-component telewindows
  :parts (tw-exe-intelnt
	   tw-exe-unix

	   tw-nptwplug-dll-intelnt

	   ;; note: same files as for G2, may overwrite:
	   tw-gen16ut-dll-intelnt
	   tw-gen32-dll-intelnt
	   tw-gen32ut-dll-intelnt

	   ;; same in G2, OK to specify twice, may be overwritten:
	   fonts)
  :print-name "Telewindows")
(def-component telewindows2 :parts (tw2 tw2-intelnt tw2-javadoc)
	       :non-platforms ("linux" "alphaosf")
	       :print-name "Telewindows2 Toolkit")

(def-component gateway :parts (gsi) :print-name "G2 Gateway (GSI)")
(def-component gda :parts (gda) :print-name "GDA")
(def-component weblink :parts (gw gsi-gw-ok gsi-gw-blank-ok) :print-name "G2 Weblink")
(def-component javalink
  :parts (jvl jvl-intelnt jvl-com-gensym-properties-intelnt jvl-javadoc)
  :non-platforms ("linux" "alphaosf")
  :print-name "G2 JavaLink")


(def-component activexlink
  :parts (axl-g2com-dll axl-gsi-dll axl-readme axl-g2com-kb axl-demos axl-runme-bat axl-regsvr axl-kbs-5)
  :platforms ("nt")
  :print-name "G2 ActiveXlink")

(def-component documentation
  :parts (g2pdf g2utlpdf jvldoc tw2doc axldoc corbalinkdoc
		 g2classicrn
		   g2oradoc g2sybdoc opclinkdoc g2odbcdoc
		   g2dbdoc)
  :print-name "G2 Documentation"
  :typical false)			; consider making false, especially if an 
					;   HTML component gets split off


(def-component g2-readme :parts (g2-readme) :print-name "G2 Readme")

(def-component protools :parts (protools-5 protools-6) :print-name "G2 ProTools")




;;; Optional Bridges in G2: Two bridges are standard (picked by the customer at
;;; order time), and others may be optionally chosen, i.e., at order time.
;;;
;;; Optional Bridges: (1) corbalink (2) opclink (3) Oraclebridge (4)
;;; Sybasebridge (5) ODBCbridge
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
(def-component opclink :parts (opclink gsi-opclink-ok gsi-opclink-blank-ok) :platforms ("nt")
	       :print-name "OPCLink"
	       :optional true)
(def-component Oraclebridge :parts (Oraclebridge gsi-Oracle-ok gsi-Oracle-blank-ok)
	       :non-platforms ("linux")
	       :print-name "Oracle Bridge"
	       :optional true)
(def-component Sybasebridge :parts (Sybasebridge gsi-Sybase-ok gsi-Sybase-blank-ok)
	       :print-name "Sybase Bridge"
	       :non-platforms ("linux")
	       :optional true)
(def-component ODBCbridge :parts (ODBCbridge gsi-ODBC-ok gsi-ODBC-blank-ok) :platforms ("nt")
	       :print-name "ODBC Bridge"
	       :optional true)





;;;; Parts



(def-part g2-exe-intelnt
    :version :60r0
    :print-name "G2 Windows Executable"
    :source g2
    :source-filename "g2.exe"
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (g2-shortcut)
    :environment-variables (sequoia_g2 g2v6_ok))

(def-shortcut g2-shortcut
    :folder-name "Gensym G2 Classic"
    :application-display-name "G2"
    :application-directory "g2"
    :target-name "g2.exe")

(def-part g2-exe-unix
    :version :60r0
    :print-name "G2 Unix Executable"
    :source g2
    :source-filename "g2"
    :destination-directory "g2"
    :non-platforms ("nt"))


(def-part g2passwd-exe-intelnt
    :version :60r0
    :print-name "G2PASSWD Windows Executable"
    :source g2
    :source-filename "g2passwd.exe"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2passwd-exe-unix
    :version :60r0
    :print-name "G2PASSWD Unix Executable"
    :source g2
    :source-filename "g2passwd"
    :destination-directory "g2"
    :non-platforms ("nt"))

(def-part g2-gen16ut-dll-intelnt
    :version :60r0
    :print-name "G2 Gen16UT DLL"
    :source g2
    :source-filename "gen16ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-gen32-dll-intelnt
    :version :60r0
    :print-name "G2 Gen32 DLL"
    :source g2
    :source-filename "gen32.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-gen32ut-dll-intelnt
    :version :60r0
    :print-name "G2 Gen32UT DLL"
    :source g2
    :source-filename "gen32ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-map-intelnt
    :version :60r0
    :print-name "G2 Map"
    :source g2
    :source-filename "g2.map"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-blank-ok
    :version :60r0
    :print-name "Sample G2 OK file"
    :source g2
    :source-filename "g2.ok"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part index-dic
    :version :60r0
    :print-name "Kanji index dictionary"
    :source g2
    :source-filename "index.dic"
    :destination-directory "g2")

(def-part kojin-dic
    :version :60r0
    :print-name "Kanji kojin dictionary"
    :source g2
    :source-filename "kojin.dic"
    :destination-directory "g2")

(def-part main-dic
    :version :60r0
    :print-name "Kanji main dictionary"
    :source g2
    :source-filename "main.dic"
    :destination-directory "g2")

(def-part ext-directory
    :version :60r0
    :print-name "G2 EXT Directory"
    :source g2
    :source-subdirectory "ext"
    :destination-directory "g2/ext")



(def-part tw-exe-intelnt
    :version :60r0
    :print-name "TW Windows Executable"
    :source tw
    :source-filename "tw.exe"
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (tw-shortcut))

(def-shortcut tw-shortcut
    :folder-name "Gensym G2 Classic"
    :application-display-name "Telewindows"
    :application-directory "g2"
    :target-name "tw.exe")

(def-part tw-exe-unix
    :version :60r0
    :print-name "TW Unix Executable"
    :source tw
    :source-filename "tw"
    :destination-directory "g2"
    :non-platforms ("nt"))



(def-part tw-nptwplug-dll-intelnt
    :version :60r0
    :print-name "TW NPTWPlug DLL"
    :source tw
    :source-filename "nptwplug.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-gen16ut-dll-intelnt
    :version :60r0
    :print-name "TW Gen16UT DLL"
    :source tw
    :source-filename "gen16ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-gen32-dll-intelnt
    :version :60r0
    :print-name "TW Gen32 DLL"
    :source tw
    :source-filename "gen32.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-gen32ut-dll-intelnt
    :version :60r0
    :print-name "TW Gen32UT DLL"
    :source tw
    :source-filename "gen32ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-map-intelnt
    :version :60r0
    :print-name "TW Map"
    :source tw
    :source-filename "tw.map"
    :destination-directory "g2"
    :platforms ("nt"))







(def-part kbs
  :version :60r0
  :destination-directory g2/kbs
  :indep t
  ;; KBs are read-only, which is not terribly bad by itself, but causes
  ;; a problem: doing uninstall on Windows.
  :make-not-read-only t)
(def-part fonts
    :version :60r0
    :destination-directory g2/fonts :indep t
    ;; fonts are read-only, which is not terribly bad by itself, but
    ;; causes these problems: using this part from both g2 and telewindow
    ;; components, and doing uninstall on Windows.
    :make-not-read-only t)
(def-part tw2
    :version :12r0
    :destination-directory tw2
    :non-platforms ("nt"		; has its own part
		     "alphaosf"		; not ready yet
		     "linux"		; ditto.
		     ))

(def-part tw2-javadoc
    :version :12r0
    :destination-directory "doc/tw2/Java"
    :shortcuts (tw2-javadoc)
    :indep t)

(def-shortcut tw2-javadoc
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "API Documentation"
    :application-directory "doc\\tw2\\Java\\docs\\api"
    :target-name "index.html")

(def-part tw2-intelnt
    :version :12r0
	  :source tw2
	  :source-subdirectory "components"
	  ;; for building tree:  handled by bundle.lisp, not in family file. -mhd
	  :remove-from-source ("bin/unInstall.bat" "bin/unInstaller.bat") ; remove component installer stuff
	  :destination-directory tw2
	  :platforms ("nt")	  
	  :environment-variables (sequoia_home sequoia-classpath sequoia-path)
	  :shortcuts (tw2-toolkit-demo
		       tw2-demo
;;		       tw2-component-editor
		       tw2-readme

;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
;; 		       ;; ActiveX:
;; 		       tw2-activex-install-controls
;; 		       tw2-activex-uninstall-controls
;; 		       tw2-activex-mill-demo
;; 		       tw2-activex-shell-demo
		       ))

;; We still have no TW2 for Linux and Alphaosf.  (MHD 4/18/01)


(def-shortcut tw2-toolkit-demo
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Default Application Shell"
    :application-directory "tw2\\bin"
    :target-name "shell.bat")

(def-shortcut tw2-demo
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Demo"
    :application-directory "tw2\\bin"
    :target-name "t2demo.bat")

;; Removed from G2 Classic product:
;; (def-shortcut tw2-component-editor
;;     :folder-name "Gensym G2 Classic"
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :application-display-name "Component Editor"
;;     :application-directory "tw2\\bin"
;;     :target-name "beaneditor.bat")

(def-shortcut tw2-readme
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Readme for Telewindows2 Toolkit"
    :application-directory "tw2"
    :target-name "readme.html")


;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
;;
;; ;; TW2 Tooklit ActiveX Shortcuts:
;; 
;; (def-shortcut tw2-activex-install-controls
;;     :folder-name "Gensym G2 Classic"
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Install Controls"
;;     :application-directory "tw2\\bin"
;;     :target-name "InstallControls.bat")
;; 
;; (def-shortcut tw2-activex-uninstall-controls
;;     :folder-name "Gensym G2 Classic"
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Uninstall Controls"
;;     :application-directory "tw2\\bin"
;;     :target-name "unInstallControls.bat")
;; 
;; (def-shortcut tw2-activex-mill-demo
;;     :folder-name "Gensym G2 Classic"
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Visual Basic Mill Demo"
;;     :application-directory "tw2\\ActiveX\\vbdemo"
;;     :target-name "VbDemo.bat")
;; 
;; (def-shortcut tw2-activex-shell-demo
;;     :folder-name "Gensym G2 Classic"
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Visual Basic Telewindows2 Shell"
;;     :application-directory "tw2\\ActiveX\\vbShell"
;;     :target-name "Tw2Prj.exe")
;; 
;; (def-shortcut tw2-activex-help
;;     :folder-name "Gensym G2 Classic"
;;     :subfolder-name "Telewindows2 Toolkit"
;;     :subsubfolder-name "ActiveX"
;;     :application-display-name "Telewindows2 Toolkit for ActiveX Reference Manual"
;;     :application-directory "tw2\\ActiveX"
;;     :target-name "AXClient.hlp")

;; Documentation Shortcuts
(def-shortcut g2-release-notes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2 Classic Release Notes"
    :application-directory "doc"
    :target-name "g2classicrelnotes.pdf")

(def-shortcut g2-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Reference Manual"
    :application-directory "doc\\g2"
    :target-name "g2refman.pdf")

(def-shortcut g2-reference-card
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Language Reference Card"
    :application-directory "doc\\g2"
    :target-name "g2langrefcard.pdf")

(def-shortcut g2-system-procedures-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 System Procedures Reference Manual"
    :application-directory "doc\\g2"
    :target-name "g2sysprocs.pdf")

(def-shortcut g2-tutorial
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Getting Started with G2 Tutorial"
    :application-directory "doc\\g2"
    :target-name "g2tutorials.pdf")

(def-shortcut g2-class-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Class Reference Manual"
    :application-directory "doc\\g2"
    :target-name "g2classref.pdf")

;; not included in 5.2r0 bundle
(def-shortcut g2-developers-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Developer's Guide"
    :application-directory "doc\\g2\\html\\g2dvg"
    :target-name "titlepag.htm")

(def-shortcut g2-dynamic-displays-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Dynamic Displays User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gdd.pdf")

(def-shortcut g2-developers-interface-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Developer's Interface User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gdi.pdf")

(def-shortcut g2-foundation-resources-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Foundation Resources User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gfr.pdf")

(def-shortcut g2-menu-system-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Menu System User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gms.pdf")

(def-shortcut g2-online-documentation-developers-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation Developer's Guide"
    :application-directory "doc\\utilities"
    :target-name "golddev.pdf")

(def-shortcut g2-online-documentation-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation User's Guide"
    :application-directory "doc\\utilities"
    :target-name "goldui.pdf")

(def-shortcut g2-guide-uil-procedures-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE UIL Procedures Reference Manual"
    :application-directory "doc\\utilities"
    :target-name "guideprocref.pdf")

(def-shortcut g2-guide-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE User's Guide"
    :application-directory "doc\\utilities"
    :target-name "guideuserguide.pdf")

(def-shortcut g2-xl-spreadsheet-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 XL Spreadsheet User's Guide"
    :application-directory "doc\\utilities"
    :target-name "gxl.pdf")



;; GDA

(def-shortcut gda-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA User's Guide"
    :application-directory "gda\\gdadoc"
    :target-name "gdaug.pdf")

(def-shortcut gda-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA Reference Manual"
    :application-directory "gda\\gdadoc"
    :target-name "gdarefman.pdf")

(def-shortcut gda-api-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA API Reference Manual"
    :application-directory "gda\\gdadoc"
    :target-name "gdaapi.pdf")


;; G2 ProTools

(def-shortcut g2-protools-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 ProTools User's Guide"
    :application-directory "protools\\kbs"
    :target-name "g2protools.pdf")

;; G2 Gateway (GSI)

(def-shortcut gsi-bridge-developers-guide
    ;; "Everyone knows this informally as 'the GSI manual'". --peter k.
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Gateway Bridge Developer's Guide"
    :application-directory "doc\\g2"
    :target-name "g2gateway.pdf")

;; Bridges

(def-shortcut g2-database-bridge-guide
    :folder-name "Gensym G2 Classic"
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

(def-shortcut g2-opclink-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 OPCLink User's Guide"
;;review for final!
;;    :application-directory "opclink"
;;    :target-name "G2-OPCLink-Client-for-Gensym-G2-Manual.pdf"
    :application-directory "doc\\bridges\\opclink"
    :target-name "g2opclink.pdf")


(def-shortcut g2-corba-link-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 CORBALink User's Guide"
    :application-directory "doc\\bridges\\corbalink"
    :target-name "g2corbalink.pdf")

(def-shortcut g2-odbc-bridge-release-notes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-ODBC Bridge Release Notes"
    :application-directory "doc\\bridges\\odbc"
    :target-name "g2odbcbridge.pdf")

(def-shortcut g2-oracle-bridge-release-notes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Oracle Bridge Release Notes"
    :application-directory "doc\\bridges\\oracle"
    :target-name "g2oraclebridge.pdf")

(def-shortcut g2-sybase-bridge-release-notes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Sybase Bridge Release Notes"
    :application-directory "doc\\bridges\\sybase"
    :target-name "g2sybasebridge.pdf")


;; Telewindows

(def-shortcut telewindows-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Telewindows User's Guide"
    :application-directory "doc\\g2"
    :target-name "telewindows.pdf")



;; Telewindows2 Toolkit
			   
(def-shortcut tw2-release-notes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Release Notes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "t2relnotes.pdf")

(def-shortcut bean-exporter-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "BeanXporter User's Guide"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "beanXporter.pdf")

(def-shortcut tw2-components-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Components and Core Classes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "t2components.pdf")

(def-shortcut tw2-application-classes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Application Classes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "t2javadevguide.pdf")

(def-shortcut tw2-demos-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Java Demos Guide"
    :application-directory "doc\\tw2\\java\\docs\\guides\\"
    :target-name "t2javademos.pdf")



;; T2A (TW2 Tooklit ActiveX) removed form G2 Classic product:  (6/10/01)
;; (def-shortcut telewindows2-toolkit-activex-developers-guide
;;     :folder-name "Gensym G2 Classic"
;;     :subfolder-name "Documentation"
;;     :subsubfolder-name "Telewindows2 Toolkit"
;;     :application-display-name "Telewindows2 Toolkit ActiveX Developer's Guide"
;;     :application-directory "doc\\tw2\\ActiveX\\docs\\guides\\ActiveXDevelopersGuide"
;;     :target-name "titlepag.htm")
			                 

;; Javalink

(def-shortcut g2-download-interfaces-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 Download Interfaces User's Guide"
    :application-directory "doc\\javalink\\docs\\guides"
    :target-name "g2downloadinterfaces.pdf")

(def-shortcut g2-beanbuilder-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 Bean Builder User's Guide"
    :application-directory "doc\\javalink\\docs\\guides"
    :target-name "g2beanbuilder.pdf")

(def-shortcut g2-javalink-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 JavaLink User's Guide"
    :application-directory "doc\\javalink\\docs\\guides"
    :target-name "g2javalink.pdf")




;; G2 ActiveXLink

(def-shortcut g2-activexlink-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 ActiveXLink User's Guide"
    :application-directory "doc\\bridges\\activexlink"
    :target-name "g2activexlink.pdf")

;; G2 WebLink

(def-shortcut g2-weblink-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 WebLink User's Guide"
    :application-directory "gw"
    :target-name "g2weblink.pdf")

(def-part gsi
    :version :60r0
    :destination-directory gsi)

(def-part gda
    :version :41r0
    :destination-directory gda
    :indep t)

(def-part gw
  :version :10r3-DF04
  :source gw
  :destination-directory gw)



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
  :version :12r0
  :source jvl
  :destination-directory javalink
  :environment-variables (javalink_home javalink-classpath javalink-path)

  ;; the semantics of the special source directive is to only copy those files
  :platforms ("nt") :source-subdirectory "components"
  :shortcuts (jvl-interface-downloader
	      jvl-bean-builder
	      jvl-example-readme
	      jvl-known-problems
	      jvl-readme)
  )

(def-shortcut jvl-interface-downloader
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Javalink"
    :application-display-name "Download Interfaces"
    :application-directory "javalink\\bin"
    :target-name "Downloadinterfaces.bat")

;; Note: Downloadinterfaces can be considered the main application for the
;; Javalink component.

(def-shortcut jvl-bean-builder
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Javalink"
    :application-display-name "G2 Bean Builder"
    :application-directory "javalink\\bin"
    :target-name "G2BeanBuilder.bat")

(def-shortcut jvl-example-readme
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Javalink"
    :application-display-name "Examples Readme"
    :application-directory "javalink"
    :target-name "ExamplesReadme.html")

(def-shortcut jvl-known-problems
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Javalink"
    :application-display-name "Known Problems"
    :application-directory "javalink"
    :target-name "KnownProblems.html")

(def-shortcut jvl-readme
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Javalink"
    :application-display-name "Readme for Javalink"
    :application-directory "javalink"
    :target-name "readme.html")




(def-part jvl
  :version :12r0
  :destination-directory javalink
  :non-platforms ("nt"			; has its own part
		  "alphaosf"		; not ready yet
		  "linux"		; ditto.
		  ))

(def-part jvl-javadoc
    :version :12r0
    :destination-directory doc/javalink
    :shortcuts (jvl-javadoc)
    :indep t)

(def-shortcut jvl-javadoc
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Javalink"
    :application-display-name "API Documentation"
    :application-directory "doc\\javalink\\docs\\api"
    :target-name "index.html")

; should this be in a bridges directory?  Or should all the bridges be in the G2 directory?
(def-part corbalink
  :version :10r1-dd19
  :destination-directory corbalink
  :non-platforms ("alphaosf"))



;; ActiveXLink Parts:

(def-part axl-g2com-dll
    :version :10r1-DF12
    :source axl
    :source-filename "G2Com.dll"
    :register true			; Active X Control
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-gsi-dll
    :version :10r1-DF12
    :source axl
    :source-filename "gsi.dll"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-readme
    :version :10r1-DF12
    :source axl
    :source-filename "ReadMe.htm"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-g2com-kb
    :version :10r1-DF12
    :source axl
    :source-filename "g2com.kb"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-demos
    :version :10r1-DF12
    :source axl
    :source-subdirectory "demos"
    :destination-directory activexlink/demos
    :platforms ("nt"))

(def-part axl-runme-bat
    :version :10r1-DF12
    :source axl
    :source-filename "runme.bat"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-regsvr
    :version :10r1-DF12
    :source axl
    :source-filename "regsvr32.exe"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-kbs-5
    :version :10r1-DF12
    :source axl
    :source-subdirectory "kbs-5"
    :destination-directory activexlink/kbs-5
    :platforms ("nt"))

;; Doc is now its own part, axldoc, and goes with doc/bridges, q.v., below.


;; utilities

(def-part g2utlpdf
    :version :60r0
    :destination-directory doc/utilities
    :indep t)

(def-part g2classicrn
    :version :60r0
    :indep t
    :destination-directory doc)

;; reference manual
(def-part g2pdf
    :version :60r0
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
		 ;;g2-release-notes-update;;not included in 6.0b1
		 g2-system-procedures-reference-manual
		 g2-tutorial
		 g2-class-reference-manual
		 ;;g2-developers-guide	    ;;not included in 6.0b1
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


;; Documentation for bridges - Javalink, ActiveXLink, TW2, Corbalink, Oracle, Sybase, OPCLink, ODBC:

(def-part jvldoc
    :version :12r0
    :destination-directory doc/javalink
    :indep t)

(def-part axldoc
    :version :10r1-DF12
    :source axl
    :source-subdirectory "docs"
    :destination-directory doc/bridges/activexlink
    :platforms ("nt"))

(def-part tw2doc
    :version :12r0
    :destination-directory doc/tw2
    :indep t)

(def-part corbalinkdoc :version :10r1-DF18 :destination-directory doc/bridges/corbalink :indep t)
(def-part g2oradoc :version :60r4-DE18 :destination-directory doc/bridges/oracle :indep t)
(def-part g2sybdoc :version :60r4-DE18 :destination-directory doc/bridges/sybase :indep t)
(def-part opclinkdoc :version :10r0-DD24 :destination-directory doc/bridges/opclink :indep t) ; check for 5.2r0 final!
(def-part g2odbcdoc :version :60r4-DE18 :destination-directory doc/bridges/odbc :indep t)
(def-part g2dbdoc
    :version :60r4-DE18			; see note at shortcut for g2-database-bridge-guide
    :destination-directory doc/bridges/db
    :indep t)

(def-part protools-5
    :version :51r8-DF11
    :source protools
    :destination-directory protools/kbs-5
    :indep t)
(def-part protools-6
    :version :60r0
    :source protools
    :destination-directory protools/kbs
    :indep t)

(def-gsi-bridge-ok-parts (:obfuscate t)
    gw opclink odbc oracle sybase)


(def-part g2-readme
    :source g2pkgreadme
    :version :60r0
    :source-filename "readme.htm"
    :indep t 
    :shortcuts (g2-readme))

(def-shortcut g2-readme
    :folder-name "Gensym G2 Classic"
    :application-display-name "Readme for G2 Classic"
    :application-directory ""
    :target-name "readme.htm")


(def-part opclink
    :version :10r0-dd24			; includes their new doc; review after beta!! (MHD 4/24/01)
    :destination-directory opclink)

(def-part Sybasebridge
    :version :60r4-DE18
    :source g2sybase
    :destination-directory Sybase
    :non-platforms ("linux" "hpux"  "alphaosf")) ; "hpux" "alphaosf" only because they are later

(def-part ODBCbridge
    :version :60r4-DE18
    :source g2odbc
    :destination-directory ODBC
    :platforms ("nt"))

(def-part Oraclebridge
    :version :60r4-DE18
    :source g2oracle
    :destination-directory Oracle
    :non-platforms ("linux"))





;;; the default value of an environment variable is the directory name of its
;;; associated part, as concatenated with the user install directory

(def-environment-variable javalink_home)

(def-environment-variable javalink-classpath :variable "CLASSPATH" :append-or-merge merge
			  :value "%JAVA_HOME%\\\\lib\\\\tools.jar;%JAVALINK_HOME%\\\\classes;%JAVALINK_HOME%\\\\classes\\\\core.jar;%JAVALINK_HOME%\\\\classes\\\\classtools.jar;%JAVALINK_HOME%\\\\classes\\\\javalink.jar;%JAVALINK_HOME%\\\\classes\\\\beanbuilder.jar")
(def-environment-variable javalink-path :variable "PATH" :append-or-merge merge
			  :value "%JAVALINK_HOME%\\\\bin")

(def-environment-variable sequoia_home)

(def-environment-variable sequoia-classpath :variable "CLASSPATH" :append-or-merge merge
			  :value "%SWING_HOME%\\\\windows.jar;%SWING_HOME%\\\\swing.jar;%SEQUOIA_HOME%\\\\classes;%SEQUOIA_HOME%\\\\classes\\\\coreui.jar;%SEQUOIA_HOME%\\\\classes\\\\sequoia.jar;%SEQUOIA_HOME%\\\\classes\\\\antlr.jar;%SEQUOIA_HOME%\\\\classes\\\\ax2jbeans.jar")

(def-environment-variable sequoia-path :variable "PATH" :append-or-merge merge
			  :value "%SEQUOIA_HOME%\\\\bin")

;;; [Rosanne Bogan:] I should point out a few things about the JavaLink demo
;;; launcher idea:
;;; 
;;; 1.  In addition to changing the readme file to document the new scheme,
;;; there is an ExamplesReadme.html file that ships with the product that will
;;; need to be modified.  Like the readme file, it describes how to run the
;;; example from the command line.
;;; 
;;; 2.  Some of the demos require that the host or port be included using
;;; -g2host or -g2port on the command line and so in some instances, it's not
;;; enough to simply give the name of the .java file you want to launch.
;;; 
;;; Also, it struck me later that I *might* have heard a suggestion to revert
;;; to one .jar file in the future.  If that's true, you should know that we
;;; just broke everything up into several jar files in 1.1r0.  I think the
;;; chief reason was to reduce the size of deployed applications.  Customers
;;; didn't want to waste space including a bunch of unused files.
;;;
;;; [Robert Penny:] I'd like to reinforce what rosanne said about the jar
;;; unification idea. The smallest number of useful jars is two for Javalink and
;;; three for Tw2. The jars could be
;;;
;;; for javalink:
;;;
;;; 1. javalink.jar (contains current core.jar, classtools.jar, javalink.jar)
;;;
;;; 2. beanbuilder.jar (contains current beanbuilder.jar)
;;; 
;;; for Tw2:
;;;
;;; 1. sequoia.jar (contains current sequoia.jar, coreui.jar, for Tw2 1.2 may
;;; need to contain stuff like uitools, or whatever stuff was mixed in during
;;; all the G2Studio development).
;;;
;;; 2. ax2jbeans.jar (contains current ax2jbeans.jar aka BeanXporter)
;;;
;;; 3. antlr.jar (contains current antlr.jar)
;;; 
;;; Note that 2. and 3. of the Tw2 jars would go away once the ComponentEditor
;;; is no longer supported. I wouldn't combine 2. and 3. since antlr.jar is
;;; provided by another vendor.


;;; The environment variables sequoia_g2 and g2v6_ok are useful, but are mostly
;;; needed in order to get the T2 Demo that runs mill to work.  At least that's
;;; the only place we currently depend on them.

(def-environment-variable sequoia_g2 :value "<TARGETDIR>\\\\g2")
(def-environment-variable g2v6_ok :value "<TARGETDIR>\\\\g2\\\\g2.ok")

;; Consider adding FONTS at a later time.  It would be nicer to have this be relative
;; to SEQUOIA_G2.  It would also be nicer if G2_HOME was the name used instead of
;; SEQUOIA_G2.
;;
;; (def-environment-variable fonts :value "<TARGETDIR>\\\\g2\\\\fonts")

;; although currently none of the above the G2 components use of this part,
;; escor and NeurOnline both do, and eventually G2 studio will also
(def-part jre
    :version :13r0
    :source "jre"
    :destination-directory "jre")
