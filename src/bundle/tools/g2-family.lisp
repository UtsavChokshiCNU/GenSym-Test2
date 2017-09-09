;; -*- mode: lisp; package: bundle -*-

(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; G2-FAMILY - G2 Family Definitions.  Requires bundle.lisp.

;; Mark H. David


(provide "g2-family")





;;;; Families



(def-family G2 :index 1 :file-syntax-version 10
	    :bundles (G2-Deployment G2-Development)
	    ;; Changing this, e.g., to "G2 Classic", impacts (i.e., may break)
	    ;; some scripts & generators currently in use.  "G2 Classic" is the
	    ;; official name, but defer for now. (MHD 9/13/00)
	    :print-name "G2"
	    :directory "g2classic"
	    :guid "243D4BB1-9EE7-11D4-8111-00A02431D004"
	    :previous-versions (("5.1r6a" "243D4BAA-9EE7-11D4-8111-00A02431D004")
				;; add more here
				)
	    :splash-screen "g2-setup.bmp"
	    :license-text "standard-license.txt")





;;; Family G2 OK Files


;;; For g2-deployment, 4 is the standard number of clients.  For g2-development
;;; 1 is the standard number of clients.  For development, we supply this in
;;; increments of 1 up to 10, thereafter in increments of 4.  Deployment only
;;; has increments of 4.

(def-g2-ok-components g2-development g2 "Development"
  (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
     (1 "-jul1-dec25-2000") (1 "-oct1-mar25-2001") (1 "-jan1-jun25-2001") 
     (1 "-apr1-sep25-2001") (1 "-jul1-dec25-2001") (1 "-oct1-mar25-2002")))

;; => (defvar g2-development-family-ok-components '(g2-development g2-development-4 ...))

(def-g2-ok-components g2-deployment g2 "Deployment"
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
    :version :51r7
    :print-name "G2 Deployment"
    :directory "deployment")

(def-bundle g2-development
    :components (core-g2-components
		  additional-g2-development-components
		  g2-development-family-ok-components)
    :version :51r7
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
(def-component telewindows2 :parts (tw2 tw2-intelnt tw2-AIX) :print-name "Telewindows2 Toolkit")

(def-component gateway :parts (gsi) :print-name "G2 Gateway (GSI)")
(def-component gda :parts (gda) :print-name "GDA")
(def-component weblink :parts (gw gsi-gw-ok gsi-gw-blank-ok) :print-name "G2 Weblink")
(def-component javalink
  :parts (jvl jvl-intelnt jvl-AIX jvl-com-gensym-properties-intelnt)
  :print-name "G2 JavaLink")


(def-component activexlink
  :parts (axl-g2com-dll axl-gsi-dll axl-readme axl-g2com-kb axl-demos axl-runme-bat)
  :platforms ("nt")
  :print-name "G2 ActiveXlink")

(def-component documentation
  :parts (g2stkdoc g2doc g2utldoc jvldoc tw2doc axldoc corbalinkdoc
		   g2stkpdf g2ps g2utlps
		   g2oradoc g2sybdoc opclinkdoc g2odbcdoc)
  :print-name "G2 Documentation"
  :typical false)			; consider making false, especially if an 
					;   HTML component gets split off


(def-component g2-readme :parts (g2-readme g2-blank-readme) :print-name "G2 Readme")

(def-component protools :parts (protools) :print-name "G2 ProTools")




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

(def-component corbalink :parts (corbalink corbalink-AIX-version)
	       :print-name "G2 CORBALink"
	       :optional true)
(def-component opclink :parts (opclink gsi-opclink-ok gsi-opclink-blank-ok) :platforms ("nt")
	       :print-name "OPCLink"
	       :optional true)
(def-component Oraclebridge :parts (Oraclebridge Oraclebridge-AIX-version gsi-Oracle-ok gsi-Oracle-blank-ok)
	       :print-name "Oracle Bridge"
	       :optional true)
(def-component Sybasebridge :parts (Sybasebridge gsi-Sybase-ok gsi-Sybase-blank-ok)
	       :print-name "Sybase Bridge"
	       :optional true)
(def-component ODBCbridge :parts (ODBCbridge gsi-ODBC-ok gsi-ODBC-blank-ok) :platforms ("nt")
	       :print-name "ODBC Bridge"
	       :optional true)





;;;; Parts



(def-part g2-exe-intelnt
    :version :51r7
    :print-name "G2 Windows Executable"
    :source g2
    :source-filename "g2.exe"
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (g2-shortcut)
    :environment-variables (sequoia_g2 g2v51_ok))

(def-shortcut g2-shortcut
    :folder-name "Gensym G2 Classic"
    :application-display-name "G2"
    :application-directory "g2"
    :target-name "g2.exe")

(def-part g2-exe-unix
    :version :51r7
    :print-name "G2 Unix Executable"
    :source g2
    :source-filename "g2"
    :destination-directory "g2"
    :platforms ("sparcsol" "aix" "hpux" "linux"))


(def-part g2passwd-exe-intelnt
    :version :51r7
    :print-name "G2PASSWD Windows Executable"
    :source g2
    :source-filename "g2passwd.exe"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2passwd-exe-unix
    :version :51r7
    :print-name "G2PASSWD Unix Executable"
    :source g2
    :source-filename "g2passwd"
    :destination-directory "g2"
    :platforms ("sparcsol" "aix" "hpux" "linux"))

(def-part g2-gen16ut-dll-intelnt
    :version :51r7
    :print-name "G2 Gen16UT DLL"
    :source g2
    :source-filename "gen16ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-gen32-dll-intelnt
    :version :51r7
    :print-name "G2 Gen32 DLL"
    :source g2
    :source-filename "gen32.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-gen32ut-dll-intelnt
    :version :51r7
    :print-name "G2 Gen32UT DLL"
    :source g2
    :source-filename "gen32ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-map-intelnt
    :version :51r7
    :print-name "G2 Map"
    :source g2
    :source-filename "g2.map"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part g2-blank-ok
    :version :51r7
    :print-name "Sample G2 OK file"
    :source g2
    :source-filename "g2.ok"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part index-dic
    :version :51r7
    :print-name "Kanji index dictionary"
    :source g2
    :source-filename "index.dic"
    :destination-directory "g2")

(def-part kojin-dic
    :version :51r7
    :print-name "Kanji kojin dictionary"
    :source g2
    :source-filename "kojin.dic"
    :destination-directory "g2")

(def-part main-dic
    :version :51r7
    :print-name "Kanji main dictionary"
    :source g2
    :source-filename "main.dic"
    :destination-directory "g2")

(def-part ext-directory
    :version :51r7
    :print-name "G2 EXT Directory"
    :source g2
    :source-subdirectory "ext"
    :destination-directory "g2/ext")



(def-part tw-exe-intelnt
    :version :51r7
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
    :version :51r7
    :print-name "TW Unix Executable"
    :source tw
    :source-filename "tw"
    :destination-directory "g2"
    :platforms ("sparcsol" "aix" "hpux" "linux"))



(def-part tw-nptwplug-dll-intelnt
    :version :51r7
    :print-name "TW NPTWPlug DLL"
    :source tw
    :source-filename "nptwplug.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-gen16ut-dll-intelnt
    :version :51r7
    :print-name "TW Gen16UT DLL"
    :source tw
    :source-filename "gen16ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-gen32-dll-intelnt
    :version :51r7
    :print-name "TW Gen32 DLL"
    :source tw
    :source-filename "gen32.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-gen32ut-dll-intelnt
    :version :51r7
    :print-name "TW Gen32UT DLL"
    :source tw
    :source-filename "gen32ut.dll"
    :destination-directory "g2"
    :platforms ("nt"))

(def-part tw-map-intelnt
    :version :51r7
    :print-name "TW Map"
    :source tw
    :source-filename "tw.map"
    :destination-directory "g2"
    :platforms ("nt"))







(def-part kbs :version :51r7 :destination-directory g2/kbs :indep t
	  ;; KBs are read-only, which is not terribly bad by itself, but causes
	  ;; a problem: doing uninstall on Windows.
	  :make-not-read-only t)
(def-part fonts :version :51r7 :destination-directory g2/fonts :indep t
	  ;; fonts are read-only, which is not terribly bad by itself, but
	  ;; causes these problems: using this part from both g2 and telewindow
	  ;; components, and doing uninstall on Windows.
	  :make-not-read-only t)
(def-part tw2 :version :11r0-exec :destination-directory tw2 :non-platforms ("nt" "aix"))
(def-part tw2-AIX :version :11b0-exec :source tw2 :destination-directory tw2 :platforms ("aix"))
(def-part tw2-intelnt :version :11r0b
	  :source tw2
	  :source-subdirectory "components"
	  ;; for building tree:  handled by bundle.lisp, not in family file. -mhd
	  :remove-from-source ("bin/unInstall.bat" "bin/unInstaller.bat") ; remove component installer stuff
	  :destination-directory tw2
	  :platforms ("nt")	  
	  :environment-variables (sequoia_home sequoia-classpath sequoia-path)
	  :shortcuts (tw2-toolkit-demo
		       tw2-demo
		       tw2-component-editor
		       tw2-readme

		       ;; ActiveX:
		       tw2-activex-install-controls
		       tw2-activex-uninstall-controls
		       tw2-activex-mill-demo
		       tw2-activex-shell-demo))

;; the b version of Telewindows 2 contains changes to the readme files, and the
;; demo batch files.  it does not include the installer changes from a, or the
;; readme information that would go with them.

;; About the -EXEC version of tw2/jvl: the -EXEC version is fixed so that
;; executables have their executable bit set.  This is needed, and done, for the
;; unix versions only. -mhd, 9/7/00

;; For Windows we don't care about the "exec"-suffix version, since that just
;; includes chmod'd executables.  And we don't want the "a"-suffix version,
;; since that just has the old installer's issues addressed, e.g., the old (1H,
;; 2000) approach to system environment variable lossage. (MHD and yduJ,
;; 12/8/00)


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

(def-shortcut tw2-component-editor
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Component Editor"
    :application-directory "tw2\\bin"
    :target-name "beaneditor.bat")

(def-shortcut tw2-readme
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "Readme"
    :application-directory "tw2"
    :target-name "readme.html")


;; TW2 Tooklit ActiveX Shortcuts:

(def-shortcut tw2-activex-install-controls
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :subsubfolder-name "ActiveX"
    :application-display-name "Install Controls"
    :application-directory "tw2\\bin"
    :target-name "InstallControls.bat")

(def-shortcut tw2-activex-uninstall-controls
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :subsubfolder-name "ActiveX"
    :application-display-name "Uninstall Controls"
    :application-directory "tw2\\bin"
    :target-name "unInstallControls.bat")

(def-shortcut tw2-activex-mill-demo
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :subsubfolder-name "ActiveX"
    :application-display-name "Visual Basic Mill Demo"
    :application-directory "tw2\\ActiveX\\vbdemo"
    :target-name "VbDemo.bat")

(def-shortcut tw2-activex-shell-demo
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :subsubfolder-name "ActiveX"
    :application-display-name "Visual Basic Telewindows2 Shell"
    :application-directory "tw2\\ActiveX\\vbShell"
    :target-name "Tw2Prj.exe")

(def-shortcut tw2-activex-help
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Telewindows2 Toolkit"
    :subsubfolder-name "ActiveX"
    :application-display-name "Telewindows2 Toolkit for ActiveX Reference Manual"
    :application-directory "tw2\\ActiveX"
    :target-name "AXClient.hlp")

;; Documentation Shortcuts

(def-shortcut g2-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2 Reference Manual"
    :application-directory "doc\\g2\\g2\\html\\g2rm"
    :target-name "titlepag.htm")

(def-shortcut g2-release-notes-update
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2 Release Notes Update"
    :application-directory "doc\\g2\\starterkit\\html\\g2rnupd"
    :target-name "titlepag.htm")

(def-shortcut g2-system-procedures-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2 System Procedures Reference Manual"
    :application-directory "doc\\g2\\g2\\html\\g2sprm"
    :target-name "titlepag.htm")

(def-shortcut g2-class-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2 Class Reference Manual"
    :application-directory "doc\\g2\\g2\\html\\g2crm"
    :target-name "titlepag.htm")

(def-shortcut g2-developers-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2 Developer's Guide"
    :application-directory "doc\\g2\\g2\\html\\g2dvg"
    :target-name "titlepag.htm")

(def-shortcut g2-dynamic-displays-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Dynamic Displays User's Guide"
    :application-directory "doc\\g2\\utilities\\html\\gddug"
    :target-name "titlepag.htm")

(def-shortcut g2-developers-interface-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Developer's Interface User's Guide"
    :application-directory "doc\\g2\\utilities\\html\\gdiug"
    :target-name "titlepag.htm")

(def-shortcut g2-foundation-resources-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Foundation Resources User's Guide"
    :application-directory "doc\\g2\\utilities\\html\\gfrug"
    :target-name "titlepag.htm")

(def-shortcut g2-menu-system-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Menu System User's Guide"
    :application-directory "doc\\g2\\utilities\\html\\gmsug"
    :target-name "titlepag.htm")

(def-shortcut g2-online-documentation-developers-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation Developer's Guide"
    :application-directory "doc\\g2\\utilities\\html\\golddg"
    :target-name "titlepag.htm")

(def-shortcut g2-guide-uil-procedures-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE UIL Procedures Reference Manual"
    :application-directory "doc\\g2\\utilities\\html\\guideprm"
    :target-name "titlepag.htm")

(def-shortcut g2-guide-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE User's Guide"
    :application-directory "doc\\g2\\utilities\\html\\guideug"
    :target-name "titlepag.htm")

(def-shortcut g2-xl-spreadsheet-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 XL Spreadsheet User's Guide"
    :application-directory "doc\\g2\\utilities\\html\\gxlsug"
    :target-name "titlepag.htm")



;; GDA

(def-shortcut gda-users-guide-and-reference-manual
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA User's Guide and Reference Manual"
    :application-directory "gda\\gdadoc"
    :target-name "titlepag.htm")

(def-shortcut gda-queues-api-reference-section
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA Queues API Reference Section"
    :application-directory "gda\\gdadoc\\queueapi"
    :target-name "titlepag.htm")


;; G2 ProTools

(def-shortcut g2-protools-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2ProTools User's Guide"
    :application-directory "protools\\doc"
    :target-name "titlepag.htm")

;; G2 Gateway (GSI)

(def-shortcut gsi-bridge-developers-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2 Gateway Bridge Developer's Guide"
    :application-directory "doc\\g2\\g2\\html\\gsibdg"
    :target-name "titlepag.htm")

;; Bridges

(def-shortcut g2-opclink-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 OPCLink User's Guide"
    :application-directory "doc\\bridges\\opclink\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-corba-link-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 CORBALink User's Guide"
    :application-directory "doc\\bridges\\corbalink\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-odbc-bridge-release-notes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-ODBC Bridge Release Notes"
    :application-directory "doc\\bridges\\odbc\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-oracle-bridge-release-notes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Oracle Bridge Release Notes"
    :application-directory "doc\\bridges\\oracle\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-sybase-bridge-release-notes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Sybase Bridge Release Notes"
    :application-directory "doc\\bridges\\sybase\\html"
    :target-name "titlepag.htm")


;; Telewindows

(def-shortcut telewindows-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "Telewindows User's Guide"
    :application-directory "doc\\g2\\starterkit\\html\\twug"
    :target-name "titlepag.htm")



;; Telewindows2 Toolkit
			   
(def-shortcut tw2-release-notes
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Release Notes"
    :application-directory "doc\\tw2\\java\\docs\\guides\\ReleaseNotes"
    :target-name "titlepag.htm")

(def-shortcut telewindows2-toolkit-online-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Online Guide"
    :application-directory "doc\\tw2\\java\\docs\\guides"
    :target-name "index.html")

(def-shortcut telewindows2-toolkit-activex-developers-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit ActiveX Developer's Guide"
    :application-directory "doc\\tw2\\ActiveX\\docs\\guides\\ActiveXDevelopersGuide"
    :target-name "titlepag.htm")
			                 

;; Javalink

(def-shortcut g2-javalink-gateway-online-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "JavaLink Online Guide"
    :application-directory "doc\\javalink\\docs\\guides"
    :target-name "index.html")


;; G2 ActiveXLink

(def-shortcut g2-activexlink-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2 ActiveXLink User's Guide"
    :application-directory "doc\\bridges\\activexlink"
    :target-name "titlepag.htm")

;; G2 WebLink

(def-shortcut g2-weblink-users-guide
    :folder-name "Gensym G2 Classic"
    :subfolder-name "Documentation"
    :application-display-name "G2 WebLink User's Guide"
    :application-directory "gw"
    ;; We don't use titlepag.htm because its main image and link is an image it
    ;; refers to that's not present in the directory. Instead, we go straight to
    ;; the main page, which they would have gone to anyhow if they clicked on
    ;; this one main link.  Fix the bug in the release directory! (MHD 12/10/00)
    :target-name "booktoc.htm")

(def-part gsi :version :51r7 :destination-directory gsi)
(def-part gda :version :40r1 :destination-directory gda :indep t)
(def-part gw :version :10r2-CG21 :destination-directory gw)



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

(def-part jvl-intelnt :version :11r0 :source jvl :destination-directory javalink
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
    :application-display-name "Readme"
    :application-directory "javalink"
    :target-name "readme.html")




;; personally, yduj is not willing to call the AIX version other than beta, since it has had
;; zero testing.
(def-part jvl-AIX :version :11b0-exec :source jvl :destination-directory javalink :platforms ("aix"))
(def-part jvl :version :11r0-exec :destination-directory javalink :non-platforms ("nt" "aix"))

; should this be in a bridges directory?  Or should all the bridges be in the G2 directory?
(def-part corbalink-AIX-version :version :10r1-cj12 :destination-directory corbalink
	  :source corbalink :platforms ("aix"))
(def-part corbalink :version :10r1-cd24 :destination-directory corbalink
	  :non-platforms ("aix" "alphaosf"))

;;; The :10r1-cj12 version of corbalink has the KBs compiled for 5.1r7.  It
;;; is not known at this if this brings it enough up-to-date to be usable.



;; ActiveXLink Parts:

(def-part axl-g2com-dll
    :version :10r1-CF05
    :source axl
    :source-filename "G2Com.dll"
    :register true			; Active X Control
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-gsi-dll
    :version :10r1-CF05
    :source axl
    :source-filename "gsi.dll"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-readme
    :version :10r1-CF05
    :source axl
    :source-filename "ReadMe.htm"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-g2com-kb
    :version :10r1-CF05
    :source axl
    :source-filename "g2com.kb"
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-demos
    :version :10r1-CF05
    :source axl
    :source-subdirectory "demos"
    :destination-directory activexlink/demos
    :platforms ("nt"))

(def-part axl-runme-bat
    :version :10r1-CF05
    :source axl
    :source-filename "runme.bat"
    :destination-directory activexlink
    :platforms ("nt"))

;; Doc is now its own part, axldoc, and goes with doc/bridges, q.v., below.


;; starter kit:

;; Off of the part G2STKDOC hang all the doc shortcuts.  Some of them could hang
;; off of their real parts, but (a) it's a lot more work; (b) some of them use
;; doc in parts that are not of the DOC component.  I don't want to hang off of
;; those parts because then you could get doc shortcuts without being authorized
;; for the doc component, which seems strange.  (Of course, it's strange to give
;; the doc in the first place, but that's another story.) (MHD 12/8/00)

(def-part g2stkdoc :version :51r7 :destination-directory doc/g2/starterkit/html :indep t
	  :shortcuts
	  (
	   ;; Note: there seem to be bugs in InstallShield and/or
	   ;; InstallGenerator and/or the commented out shortcuts here.  For
	   ;; now, leave them uncommented; this set was carefully determined by
	   ;; expirimentation to work, whereas with some or all of the commented
	   ;; out shortcuts, there was failure: "unknown error". (MHD 12/11/00)
	   g2-reference-manual
	    g2-release-notes-update
	    g2-system-procedures-reference-manual
	    g2-class-reference-manual	    
	    g2-developers-guide
	    ;; G2 Utilities
	    g2-dynamic-displays-users-guide	    
	    g2-developers-interface-users-guide
	    g2-foundation-resources-users-guide	    
	    g2-menu-system-users-guide
	    g2-online-documentation-developers-guide	    
	    g2-guide-uil-procedures-reference-manual
	    g2-guide-users-guide	    
	    g2-xl-spreadsheet-users-guide
	    ;; GDA:
	    gda-users-guide-and-reference-manual
	    gda-queues-api-reference-section
	    ;; Protools
	    g2-protools-users-guide
	    ;; GSI
	    gsi-bridge-developers-guide
	    ;; Bridges:
	    g2-opclink-users-guide
	    g2-corba-link-users-guide	   
	    g2-odbc-bridge-release-notes
	    g2-oracle-bridge-release-notes	    
	    g2-sybase-bridge-release-notes
	    ;; TW
	    telewindows-users-guide
	    ;; TW2
	    tw2-activex-help		; NOTE: Shortcut in TW2/ActiveX Folder
	    tw2-release-notes
	    telewindows2-toolkit-online-guide
	    telewindows2-toolkit-activex-developers-guide
	    ;; Javalink
	    g2-javalink-gateway-online-guide
	    ;; ActiveXLink
	    g2-activexlink-users-guide
	    ;; Weblink
	    g2-weblink-users-guide
	    )) 

(def-part g2stkpdf :version :51r7 :destination-directory doc/g2/starterkit :indep t)
;; utilities
(def-part g2utldoc :version :50r1 :destination-directory doc/g2/utilities/html :indep t)
(def-part g2utlps :version :|50r1-pdf| :destination-directory doc/g2/utilities :indep t)
;; reference manual
(def-part g2doc :version :50r3 :destination-directory doc/g2/g2/html :indep t)
(def-part g2ps :version :|50r3-pdf| :destination-directory doc/g2/g2 :indep t)


;; Documentation for bridges - Javalink, ActiveXLink, TW2, Corbalink, Oracle, Sybase, OPCLink, ODBC:

(def-part jvldoc :version :11r0 :destination-directory doc/javalink :indep t)
(def-part axldoc
    :version :10r1-CF05 :source axl :source-subdirectory "docs"
    :destination-directory doc/bridges/activexlink
    :platforms ("nt"))
(def-part tw2doc :version :11r0 :destination-directory doc/tw2 :indep t)

(def-part corbalinkdoc :version :10r1 :destination-directory doc/bridges/corbalink :indep t)
(def-part g2oradoc :version :60r4 :destination-directory doc/bridges/oracle :indep t)
(def-part g2sybdoc :version :60r4 :destination-directory doc/bridges/sybase :indep t)
(def-part opclinkdoc :version :10r0 :destination-directory doc/bridges/opclink :indep t)
(def-part g2odbcdoc :version :60r4 :destination-directory doc/bridges/odbc :indep t)

(def-part protools :version :51r0 :destination-directory protools :indep t)

(def-gsi-bridge-ok-parts gw opclink odbc oracle sybase)


(def-part g2-readme
    :destination-filename "readme.txt"
    :indep t 
    :source "/home/development/installers/release-files"
    :source-filename "g2-package-readme.txt"
    :shortcuts (g2-readme))

;;; this is a kluge to deal with the fact that the whole rename situation
;;; doesn't really work on NT
(def-part g2-blank-readme
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "readme.txt")

(def-shortcut g2-readme
    :folder-name "Gensym G2 Classic"
    :application-display-name "Readme for G2 Classic"
    :application-directory ""
    :target-name "readme.txt")

(def-part opclink :version :10r0 :destination-directory opclink)
(def-part Sybasebridge :version :60r4 :source g2sybase :destination-directory Sybase)
(def-part ODBCbridge :version :60r4 :source g2odbc :destination-directory ODBC)
(def-part Oraclebridge-AIX-version :version :60r4 :source g2oracle
	  :destination-directory Oracle :platforms ("aix"))
(def-part Oraclebridge :version :60r4-N23-8 :source g2oracle
	  :destination-directory Oracle :non-platforms ("aix"))



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


;;; The environment variables sequoia_g2 and g2v51_ok are useful, but are mostly
;;; needed in order to get the T2 Demo that runs mill to work.  At least that's
;;; the only place we currently depend on them.

(def-environment-variable sequoia_g2 :value "<TARGETDIR>\\\\g2")
(def-environment-variable g2v51_ok :value "<TARGETDIR>\\\\g2\\\\g2.ok")

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
