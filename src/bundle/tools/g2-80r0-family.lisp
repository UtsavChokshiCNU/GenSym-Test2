;; -*- mode: lisp; package: bundle -*-

(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; G2-FAMILY - G2 Family Definitions.  Requires bundle.lisp.

;; Mark H. David


(provide 'g2-80r0-family)




;;;; Families



(def-family G2-80r0
    :index 35			; per tools/datafiles/families/family-id.dat
    :file-syntax-version 10
    :bundles (G2-Deployment G2-Development TW-Client)
    :print-name "G2"		; "G2" => "G2 Classic" (MHD 12/13/01)
				; "G2 Classic" => "G2" (yduJ 1/28/02)
    
    :directory "g2-8.0r0"
    ;; per tools/datafiles/families/guid.dat:
    :guid "c5192361-2347-4ec2-827c-a9af41ddc6c9" ;8.0r0
    :compatible-previous-versions (("8.0b0" "74ee5cc5-de60-4cd0-8012-c8da127d35b8")
				   ("8.0a1" "162d35e4-346d-426a-b840-b3495f4c51a4")
				   ("8.0a0" "49D6E4C9-C17A-41f4-AAD1-CC92F9575A15")
				   ("7.1r0" "55F37F88-60D2-466e-BA95-517719158B18")
				   ("7.0r1" "23961651-4FCF-4fec-BC84-2DE2E5679818")
				   ("7.0r0" "487E5A3E-E452-4048-802B-3FCF81C4E4AF")
				   ("6.2r2" "B496D6B3-B00D-43A9-96A2-267F01395A64")
				   ("6.2r0" "C88050F2-F316-4099-816C-A37D11D62831")
				   ("6.1r0" "5127F127-9E61-4E5C-B7F6-F34B20EC8F34"))
    :previous-versions (("7.0b0" "69999187-41FE-4390-B149-33765323882F")
			("5.2r1" "243D4BC0-9EE7-11D4-8111-00A02431D004")
			("5.2r0" "243D4BBC-9EE7-11D4-8111-00A02431D004")
			("5.2b1" "243D4BB9-9EE7-11D4-8111-00A02431D004")
			("5.1r7" "243D4BB1-9EE7-11D4-8111-00A02431D004")
			("5.1r6a" "243D4BAA-9EE7-11D4-8111-00A02431D004")
			)
    :splash-screen "g2-setup.bmp"
    :license-text "standard-license.txt")



(defvar g2-shortcut-folder-name "Gensym G2 8.0r0")

;;; Family G2 OK Files


;;; For g2-deployment, 4 is the standard number of clients.  For g2-development
;;; 1 is the standard number of clients.  For development, we supply this in
;;; increments of 1 up to 10, thereafter in increments of 4.  Deployment only
;;; has increments of 4.

(setq prevailing-ok-version-suffix "-v8")

(def-g2-ok-components (g2-development :obfuscate t)
    g2 "Development"
  (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
     (1 "-jul25-2004") (1 "-aug25-2004")
     (1 "-sep25-2004") (1 "-oct25-2004") (1 "-nov25-2004")
     (1 "-dec25-2004") (1 "-jan25-2005") (1 "-feb25-2005")
     (1 "-mar25-2005") (1 "-apr25-2005") (1 "-may25-2005")
     (1 "-jun25-2005") (1 "-jul25-2005") (1 "-aug25-2005")
     (1 "-sep25-2005") (1 "-oct25-2005") (1 "-nov25-2005")
     (1 "-dec25-2005") ))

;; => (defvar g2-development-family-ok-components '(g2-development g2-development-4 ...))

(def-g2-ok-components (g2-deployment :obfuscate t) g2 "Deployment"
  (4 8 12 16 20 24 28 32))





;;;; Bundles


(defvar core-g2-components
  '(g2 telewindows gateway gda g2i-core-modules weblink javalink
    activexlink
    corbalink opclink pibridge Oraclebridge Sybasebridge ODBCbridge gservice
    g2-readme))

(defvar additional-g2-components '(jmail-component jms-component socket-manager))

(defvar additional-g2-deployment-components '(jre))

(defvar additional-g2-development-components '(jre doc-pdf doc-html doc-chm protools))


(def-bundle g2-deployment
    :components (core-g2-components
		  additional-g2-components
		  additional-g2-deployment-components 
		  g2-deployment-family-ok-components
		  g2-blank-ok-component)
    :version :80r0
    :print-name "G2 Deployment"
    :directory "deployment")

(def-bundle g2-development
    :components (core-g2-components
		  additional-g2-components
		  additional-g2-development-components
		  g2-development-family-ok-components
		  g2-blank-ok-component)
    :version :80r0
    :print-name "G2 Development"
    :directory "development")


(def-bundle tw-client
    :components (telewindows doc-chm)
    :version :80r0
    :print-name "Telewindows Client"
    :directory "client"
    :platforms ("nt"))


;;;; Components



(def-component g2
  :parts
  (g2-intelnt g2-unix
	      kanji-dic ext-directory
	      g2-blank-ok
	      kbs fonts mill-demo startserver-bat-file registerControls
	      ;;The following kbs are requested by the application products to
	      ;;be available even when the bridge itself is not authorized.
	      ;;Suggestion HQ-4795626.
	      axlkbs jmskbs odbckbs oraclekbs sybasekbs pikbs opclinkkbs socket-manager-kbs
	      jvlkbs gwkbs jmailkbs)
  :include-in-contents (g2-intelnt g2-unix)
  :print-name "G2 (and utilities)")

(def-component g2-blank-ok-component
  :print-name "No Authorization File for G2"
  :parts (g2-blank-ok)
  :watermark "g2/g2.ok"
  :include-in-contents :none
  :radio-button-group-index 1)

(def-component telewindows
  :parts (tw-intelnt
	   tw-unix twng
	   twax twax-examples workspace-view workspace-view-g2com
	   ;; same in G2, OK to specify twice, may be overwritten:
	   fonts)
  :include-in-contents (tw-intelnt tw-unix)
  :print-name "Telewindows")

(def-component gateway :parts (gsi) :print-name "G2 Gateway (GSI)")
(def-component gda :parts (gda) :print-name "G2 Diagnostic Assistant (GDA)")
(def-component weblink :parts (gw gsi-gw-ok run-gw-template-batfile gsi-gw-blank-ok) :print-name "G2 WebLink")
(defvar basic-jvl-parts
  '(jvl-unix jvl-intelnt jvl-3tier jvl-com-gensym-properties-intelnt jvl-javadoc))
(def-component javalink
  :parts (basic-jvl-parts)
  :print-name "G2 JavaLink")


(def-component activexlink
  ;;note order: put the individual file part first and the "everything" part
  ;;last, and then when uninstall happens everything will be uninstalled.
  :parts (axl-g2com-dll axl)
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
	   g2idoc-ug-pdf g2idoc-runtime-pdf 
	   jvldoc-javalink-pdf jvldoc-di-pdf jvldoc-bb-pdf axldoc corbalinkdoc
		 g2classicrn
		   g2oradoc g2sybdoc opclinkdoc g2pidoc g2odbcdoc
		   g2dbdoc protoolsdoc weblinkdoc gdadoc-api-pdf gdadoc-ug-pdf)
  :print-name "G2 Full Documentation (PDF)"
  :include-in-contents (g2doc-g2refman-pdf)
  :typical false)

(def-component doc-html
  :parts (g2doc-g2refman-html g2doc-g2tutorials-html g2doc-g2gateway-html
	  g2doc-g2classref-html g2doc-telewindows-html g2doc-g2sysprocs-html
	  g2doc-g2langrefcard-html g2doc-g2devguide-html 
	  g2utldoc-gdi-html g2utldoc-gms-html g2utldoc-goldui-html
	  g2utldoc-guideuserguide-html g2utldoc-gdd-html g2utldoc-gfr-html
	  g2utldoc-golddev-html g2utldoc-guideprocref-html g2utldoc-gxl-html
	  ;;g2idoc-ug-html g2idoc-runtime-html
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
;;; Sybasebridge (5) ODBCbridge (6) Pi Bridge (7) JMS (8) Socket Manager
;;;
;;; Note that there may be other components, e.g., Gateway (GW) and perhaps
;;; other components, that are technically bridges, but they're not necessarily
;;; marketed that way to customers.
;;;
;;; All of the optional bridges, those bridges marketed as such, are here,
;;; below, and bear the :optional=true flag.

(def-component corbalink :parts (corbalink)
	       :print-name "G2 CORBALink"
	       :non-platforms ("alphaosf" "linux")
	       :optional true)
(def-component opclink :parts (opclink gsi-opclink-ok run-G2Opc-template-batfile gsi-opclink-blank-ok) :platforms ("nt")
	       :print-name "G2 OPCLink Bridge"
	       :optional true)

(def-component pibridge :parts (g2pi gsi-pi-ok
				 run-g2-pi-template-batfile gsi-pi-blank-ok) :platforms ("nt")
	       :print-name "G2 PI Bridge"
	       :optional true)

(def-component Oraclebridge :parts (Oraclebridge gsi-Oracle-ok run-g2-ora7-template-batfile run-g2-ora80-template-batfile run-g2-ora81-template-batfile run-g2-ora90-template-batfile run-g2-ora92-template-batfile gsi-Oracle-blank-ok)
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



(def-part g2-intelnt
    :version :80r0
    :print-name "G2 Windows Executable"
    :source g2
    :source-filename ("g2.exe" "g2passwd.exe" "g2.map")
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (g2-shortcut))

(def-shortcut g2-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-netinfo")

(def-part g2-unix
    :version :80r0
    :print-name "G2 Unix Executable"
    :source g2
    :source-filename ("g2" "g2passwd")
    :destination-directory "g2"
    :non-platforms ("nt"))

(def-part g2-blank-ok
    :version :80r0
    :print-name "Sample G2 OK file"
    :source g2
    :source-filename "g2.ok"
    :destination-directory "g2")

(def-part kanji-dic
    :version :80r0
    :print-name "Kanji dictionary files"
    :source g2
    :source-filename ("index.dic" "kojin.dic" "main.dic")
    :destination-directory "g2")

(def-part ext-directory
    :version :80r0
    :print-name "G2 EXT Directory"
    :source g2
    :source-subdirectory "ext"
    :destination-directory "g2/ext")

(def-part tw-intelnt
    :version :80r0
    :print-name "TW Windows Executable"
    :source tw
    :source-filename ("tw.exe" "nptwplug.dll" "tw.map")
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (tw-shortcut tw-shortcut-classic)
    :registry-entries (tw-registry-entry)
    )

(def-registry-entry tw-registry-entry
    :path  "HKEY_LOCAL_MACHINE\\SOFTWARE\\Gensym\\Telewindows\\8.0 Rev. 0" 
    :key-name "installDir"
    :value "%ROOTDIR%\\g2")

(def-part twng
    ;;This kluge brought to you by the wonders of the bundle version number decomposer.
    :version :80r0-NG
    :print-name "TW Next Generation"
    :source tw
    :source-filename ("twng.exe")
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (twng-shortcut))

(def-shortcut tw-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "Telewindows (Multiwindow)"
    :application-directory "g2"
    :target-name "tw.exe"
    :parameters "-ui multiwindow")

(def-shortcut tw-shortcut-classic
    :folder-name g2-shortcut-folder-name
    :application-display-name "Telewindows (Standard)"
    :application-directory "g2"
    :target-name "tw.exe")

(def-shortcut twng-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "Telewindows Next Generation"
    :application-directory "g2"
    :target-name "twng.exe")

(def-part tw-unix
    :version :80r0
    :print-name "TW Unix Executable"
    :source tw
    :source-filename ("tw" "nptwplug.so")
    :destination-directory "g2"
    :non-platforms ("nt"))


(def-part twax
    :version :80r0
    :source-filename ("TwControl.cab" "unregisterTwControl.bat" "TwControl.ocx"
		      "install.html" "registerTwControl.bat")
    :destination-directory "g2"
    :platforms ("nt"))

(def-part twax-examples
    :version :80r0
    :source twax
    :source-subdirectory examples
    :destination-directory "g2/examples"
    :platforms ("nt"))


;;It is an extremely sad fact that we must specify all the files in the
;;directory here.  The problem is we need to specify individual filenames from
;;every component that goes into the G2 directory or it chooses *.* from the
;;whole concatenated mess, rather than just *.* from the individual component.
;;Then you end up with all possible OK files with their ugly names!  Oops.
(def-part workspace-view
    :version :80r0
    :destination-directory "g2"
    :source-filename ("WSView.frm" "WSView.frx" "WorkspaceViewDemo.exe" "WorkspaceView.ocx" "WorkspaceViewDemo.vbp" "WorkspaceViewDemo.vbw" "registerWSV.bat" "unregisterWSV.bat" "workspace-views.kb" "wsvdemo.kb" "wsview.html")
    :platforms ("nt")
    :shortcuts (WorkspaceViewDemo WorkspaceViewDemoExe workspace-view wsview-html))

(def-part workspace-view-g2com
    :version :11r0
    :destination-directory "g2"
    :source axl
    :source-filename ("g2com.kb")
    :platforms ("nt"))

(def-shortcut WorkspaceViewDemo
    :folder-name g2-shortcut-folder-name
    :application-display-name "VB Project"
    :subfolder-name "Examples"
    :subsubfolder-name "Workspace View"
    :application-directory "g2"
    :target-name "WorkspaceViewDemo.vbp")

(def-shortcut WorkspaceViewDemoExe
    :folder-name g2-shortcut-folder-name
    :application-display-name "VB Executable"
    :subfolder-name "Examples"
    :subsubfolder-name "Workspace View"
    :application-directory "g2"
    :target-name "WorkspaceViewDemo.exe")

(def-shortcut workspace-view
    :folder-name g2-shortcut-folder-name
    :application-display-name "Workspace View Demo KB"
    :subfolder-name "Examples"
    :subsubfolder-name "Workspace View"
    :application-directory "g2"
    :target-name "Startserver.bat"
    :parameters "-kb wsvdemo.kb -tcpport 1112 -tcpipexact")

(def-shortcut wsview-html
    :folder-name g2-shortcut-folder-name
    :application-display-name "HTML Page"
    :subfolder-name "Examples"
    :subsubfolder-name "Workspace View"
    :application-directory "g2"
    :target-name "wsview.html")


(def-part kbs
  :version :80r0
  :destination-directory g2/kbs
  :indep t
  ;; KBs are read-only, which is not terribly bad by itself, but causes
  ;; a problem: doing uninstall on Windows.
  :make-not-read-only t
  :shortcuts (g2-80r0-doc-examples dialogs-demo gms-native-language-demo
              gms-native-large-menu-demo gms-native-multiple-menubar-demo
	      gms-native-popup-demo nmsdemo publish-subscribe-doc-ex
	      publish-subscribe-remote-doc-ex space business explnfac))

(def-part mill-demo
    :source demos
    :version :80r0
    :destination-directory g2/kbs/demos
    :source-filename ("start-mill.bat" "sleep.exe")
    :postinstall-code "replace_rootdir(\"g2\"^\"kbs\"^\"demos\", \"start-mill.bat\");"
    :platforms ("nt")
    :indep t ;; it's on indep even though it's really not independent.
    ;;Other demos were that way, just piggybacked on existing product.
    :shortcuts (mill-demo))

    
(def-shortcut mill-demo
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-display-name "Mill Demo"
    :application-directory "g2\\kbs\\demos"
    :target-name "start-mill.bat")

(def-shortcut g2-80r0-doc-examples
    :folder-name g2-shortcut-folder-name
    :application-display-name "G2 8.0 Documentation"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\g2-80r0-doc-examples.kb")

(def-shortcut dialogs-demo
    :folder-name g2-shortcut-folder-name
    :application-display-name "Windows Dialogs"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\dialogs-demo.kb")


(def-shortcut gms-native-language-demo
    :folder-name g2-shortcut-folder-name
    :application-display-name "Windows GMS Menus"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\gms-native-language-demo.kb")


(def-shortcut gms-native-large-menu-demo
    :folder-name g2-shortcut-folder-name
    :application-display-name "Windows Large GMS Menus"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\gms-native-large-menu-demo.kb")


(def-shortcut gms-native-multiple-menubar-demo
    :folder-name g2-shortcut-folder-name
    :application-display-name "Windows Multiple GMS Menubar"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\gms-native-multiple-menubar-demo.kb")

(def-shortcut gms-native-popup-demo
    :folder-name g2-shortcut-folder-name
    :application-display-name "Windows GMS Menubar"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\gms-native-popup-demo.kb")

(def-shortcut nmsdemo
    :folder-name g2-shortcut-folder-name
    :application-display-name "NMS Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\nmsdemo.kb")

(def-shortcut publish-subscribe-doc-ex
    :folder-name g2-shortcut-folder-name
    :application-display-name "Publish Subscribe"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\publish-subscribe-doc-ex.kb")

(def-shortcut publish-subscribe-remote-doc-ex
    :folder-name g2-shortcut-folder-name
    :application-display-name "Remote Publish Subscribe"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\publish-subscribe-remote-doc-ex.kb")

(def-shortcut space
    :folder-name g2-shortcut-folder-name
    :application-display-name "Space Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\space.kb")

(def-shortcut business
    :folder-name g2-shortcut-folder-name
    :application-display-name "Business Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\business.kb")

(def-shortcut explnfac
    :folder-name g2-shortcut-folder-name
    :application-display-name "Rules Explanation"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb kbs\\demos\\explnfac.kb")


(def-part startserver-bat-file
    :source demos
    :version :80r0
    :source-filename ("StartServer.bat")
    :destination-directory g2
    :platforms ("nt")
    :postinstall-code "replace_rootdir(\"g2\", \"StartServer.bat\");"
    :indep t ;; it's on indep even though it's really not independent.
             ;;Other demos were that way, just piggybacked on existing product.
    )

(def-part registerControls
    :source demos
    :version :80r0
    :source-filename ("registerControls.bat" "unregisterControls.bat")
    :destination-directory g2
    :platforms ("nt")
    :postinstall-code "replace_rootdir(\"g2\", \"registerControls.bat\");replace_rootdir(\"g2\", \"unregisterControls.bat\");"
    :indep t
    :shortcuts (registerControls unregisterControls)
    )

(def-shortcut registerControls
    :folder-name g2-shortcut-folder-name
    :application-display-name "Register G2 ActiveX Controls"
    :application-directory "g2"
    :target-name "registerControls.bat")

(def-shortcut unregisterControls
    :folder-name g2-shortcut-folder-name
    :application-display-name "Unregister G2 ActiveX Controls"
    :application-directory "g2"
    :target-name "unregisterControls.bat")

(def-part fonts
    :version :80r0
    :destination-directory g2/fonts :indep t
    ;; fonts are read-only, which is not terribly bad by itself, but
    ;; causes these problems: using this part from both g2 and telewindow
    ;; components, and doing uninstall on Windows.
    :make-not-read-only t)

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

;; G2i

(def-shortcut g2idoc-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Developers' Utilities User's Guide"
    :application-directory "doc\\g2i\\g2developersutilities"
    :target-name "g2developersutilities.pdf")

(def-shortcut g2idoc-runtime
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Developer's Utilities Runtime Library User's Guide"
    :application-directory "doc\\g2i\\g2runtimelibrary"
    :target-name "g2runtimelibrary.pdf")

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

(def-shortcut g2-pi-bridge-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-PI Bridge User's Guide"
    :application-directory "doc\\bridges\\pi"
    :target-name "g2pibridge.pdf")

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
    :version :80r0
    :destination-directory gsi)

(def-part gservice
    :version :80r0
    :source gservice
    :source-filename "gservice.exe"
    :destination-directory g2
    :platforms ("nt"))
    

(def-part gda
    :version :44r0
    :destination-directory gda
    :indep t)


;;;
;;;======= Begin G2i Modules =======
;;;
(def-component g2i-core-modules
  :print-name "G2 Developers' Utilities (G2i)"
  :parts (g2i-core-modules))

(def-part g2i-core-modules
  :source g2i
  :version :20r0
  :indep t
  :source-subdirectory kbs
  :source-filename ("gens.kb" "gerr.kb" "grtl.kb"  "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "gqsdemo.kb" "resources-english.txt" "config.txt" "gevm.kb" "gdsm.kb" "grlb.kb")
  :destination-directory "g2i/kbs")
;;;
;;;======= End G2i Modules =======
;;;

;;;
;;;======= Begin Socket Manager =======
;;;
(def-component socket-manager
    :print-name "Socket Manager"
    :parts (socket-manager-bin socket-manager-classes socket-manager-kbs socket-manager-examples socket-manager-doc jre basic-jvl-parts)
    :optional true
    :include-in-contents (socket-manager-bin))

(def-part socket-manager-bin
    :source sockman
    :version :41r0
    :platforms ("nt" "sparcsol")
    :source-subdirectory bin
    :source-filename ("StartSockManBridge.bat" "SocketManager.sh")
    :postinstall-code "replace_rootdir(\"sockman\"^\"bin\", \"StartSockManBridge.bat\");"
    :destination-directory "sockman/bin"
    :shortcuts (sockman-shortcut sockman-demo-shortcut))

(def-part socket-manager-classes
    :source sockman
    :version :41r0
    :platforms ("nt" "sparcsol")
    :source-subdirectory classes
    :source-filename ("SocketManager.jar")
    :destination-directory "sockman/classes")

(def-part socket-manager-examples
    :source sockman
    :version :41r0
    :platforms ("nt" "sparcsol")
    :source-subdirectory examples
    :source-filename ("gsockdemo.kb") ;;"jsockman.kb"
    :destination-directory "sockman/examples")

(def-part socket-manager-kbs
    :source sockman
    :version :41r0
    :platforms ("nt" "sparcsol")
    :source-subdirectory kbs
    :source-filename ("gsockman.kb")
    :destination-directory "sockman/kbs")

(def-part socket-manager-doc
    :source sockmandoc
    :version :41r0
    :indep t
    :platforms ("nt" "sparcsol")
    :source-filename ("g2javasocketmanager.pdf")
    :destination-directory "doc/bridges/sockman"
    :shortcuts (sockman-doc-shortcut))

(def-shortcut sockman-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "Socket Manager Bridge"
    :application-directory "sockman\\bin"
    :target-name "StartSockManBridge.bat"
)

(def-shortcut sockman-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Socket Manager"
    :application-display-name "Socket Manager Example"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\sockman\\examples\\sockdemo.kb"
)

(def-shortcut sockman-doc-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "Socket Manager User's Guide"
    :application-directory "doc/bridges/sockman"
    :target-name "JSockManUsersGuide.pdf")
;;;
;;;======= End Socket Manager =======
;;;
;;;======= Begin JMail =======
;;;
(def-component jmail-component
  :print-name "JMail"
  :parts (jmail-part jmail-doc jre basic-jvl-parts)
  :include-in-contents (jmail-part))

(def-part jmail-part
  :source jmail
  :version :20r0
  :platforms ("nt")
  :destination-directory jmail
  :postinstall-code "replace_rootdir(\"jmail\"^\"bin\", \"StartJMailBridge.bat\");"
  :shortcuts (jmail-shortcut jmail-demo-shortcut))

(def-part jmailkbs
  :source jmail
  :version :20r0
  :platforms ("nt")
  :source-subdirectory kbs
  :destination-directory jmail/kbs)  

(def-part jmail-doc
  :source jmaildoc
  :version :20r0
  :platforms ("nt")
  :indep t
  :destination-directory "doc/bridges/jmail"
  :shortcuts (jmail-doc-shortcut))

(def-shortcut jmail-doc-shortcut
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "JMail User's Guide"
  :application-directory "doc/bridges/jmail"
  :target-name "g2jmailbridge.pdf")

(def-shortcut jmail-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "JMail Bridge"
    :application-directory "jmail\\bin"
    :target-name "StartJMailBridge.bat")

(def-shortcut jmail-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "JMail"
    :application-display-name "JMail Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\jmail\\examples\\jmail-demo.kb")

;;;
;;;======= End JMail =======
;;;
;;;
;;;======= Begin JMS =======
;;;
(def-component jms-component
  :print-name "JMS"
  :parts (jms-part jms-g2i-modules jms-doc jre basic-jvl-parts)
  :optional true
  :include-in-contents (jms-part))

(def-part jms-doc
  :source jmsdoc
  :version :20r0
  :platforms ("nt")
  :indep t
  :destination-directory "doc/bridges/jms"
  :shortcuts (jms-doc-shortcut))

(def-shortcut jms-doc-shortcut
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "JMS User's Guide"
  :application-directory "doc/bridges/jms"
  :target-name "g2jmslink.pdf")

(def-part jms-part
  :source jms
  :version :20r0
  :platforms ("nt")
  :destination-directory jms
  :postinstall-code "replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-j2ee.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-jboss.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-FioranoMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-WebSphereMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-SonicMQ.bat\");"
  :shortcuts (jms-j2ee-shortcut jms-jboss-shortcut jms-FioranoMQ-shortcut jms-WebSphereMQ-shortcut jms-demo-shortcut))

(def-part jmskbs
  :source jms
  :version :20r0
  :platforms ("nt")
  :source-subdirectory kbs
  :destination-directory jms/kbs)  

(def-shortcut jms-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "JMS"
    :application-display-name "JMS Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\jms\\examples\\jms-demo.kb")

(def-shortcut jms-SonicMQ-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS Sonic MQ Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-SonicMQ.bat")

(def-shortcut jms-FioranoMQ-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS Fiorano MQ Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-FioranoMQ.bat")

(def-shortcut jms-WebSphereMQ-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS WebSphere MQ Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-WebSphereMQ.bat")

(def-shortcut jms-j2ee-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS J2EE Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-j2ee.bat")

(def-shortcut jms-jboss-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS JBoss Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-jboss.bat")

(def-part jms-g2i-modules
  :source g2i
  :version :20r0
  :destination-directory "g2i/kbs"
  :source-subdirectory kbs
  :source-filename ("grtl.kb" "gerr.kb")
  :indep t)
;;;
;;;======= End JMS =======
;;;


(def-part gw
  :version :80r0
  :source gw
  :destination-directory gw)

(def-part gwkbs
  :version :80r0
  :source gw
  :source-filename ("gwex2.kb" "gwex1.kb" "gwlow.kb")
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
    :subfolder-name "Bridges"
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

(def-part jvl-unix
  :version :13r0
  :source jvl
  :destination-directory javalink
  :postinstall-code "replace_rootdir(\"javalink\"^\"bin\", \"set-envvars\");"
  :platforms ("sparcsol" "hpux" "aix" "linux"))

(def-part jvl-3tier
  :version :13r0
  :source jvl
  :destination-directory javalink
  :platforms ("alphaosf"))

(def-part jvl-intelnt
  :version :13r0
  :source jvl
  :destination-directory javalink
  :postinstall-code "replace_rootdir(\"javalink\"^\"bin\", \"envvars.bat\");"
  :platforms ("nt")
  :shortcuts (jvl-interface-downloader
	      jvl-install-properties
	      jvl-bean-builder
	      jvl-example-readme
	      jvl-known-problems
	      jvl-readme))

(def-part jvlkbs
  :source jvl
  :version :13r0
  :platforms ("nt")
  :source-subdirectory kbs
  :destination-directory javalink/kbs)

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




(def-part jvl-javadoc
    :version :13r0
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
  :version :11r0
  :destination-directory corbalink
  :non-platforms ("alphaosf"))

;; ActiveXLink Parts:

(def-part axl
    :version :11r0
    :source axl
    ;;:source-filename ("gsi.dll" "g2com.kb" "runme.bat" "regsvr32.exe" "G2Com.oca")
    :destination-directory activexlink
    :platforms ("nt")
    :shortcuts (axldemo axlhtmldemo axlvbdemo axlvbdemoproj ;axlexceldemo
			))

(def-part axl-g2com-dll
    :version :11r0
    :source axl
    :source-filename "G2Com.dll"
    :register true			; Active X Control
    :destination-directory activexlink
    :platforms ("nt"))

(def-part axl-demos
    :version :11r0
    :source axl
    :source-subdirectory "demos"
    :destination-directory activexlink/demos
    :platforms ("nt"))

(def-part axlkbs
    :version :11r0
    :source axl
    :destination-directory activexlink
    :source-filename ("g2com.kb")
    :platforms ("nt"))

(def-shortcut axldemo
    :folder-name g2-shortcut-folder-name
    :application-display-name "ActiveX Link Demo KB"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\activexlink\\demos\\axldemo.kb")

(def-shortcut axlhtmldemo
    :folder-name g2-shortcut-folder-name
    :application-display-name "HTML Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "activexlink\\demos\\iedemo"
    :target-name "Gateway.htm")

(def-shortcut axlvbdemo
    :folder-name g2-shortcut-folder-name
    :application-display-name "VB Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "activexlink\\demos\\vbdemo"
    :target-name "VBDemo.exe")

(def-shortcut axlvbdemoproj
    :folder-name g2-shortcut-folder-name
    :application-display-name "VB Demo Project"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "activexlink\\demos\\vbdemo"
    :target-name "VBDemo.vbp")

(def-shortcut axlexceldemo
    :folder-name g2-shortcut-folder-name
    :application-display-name "Excel Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "activexlink\\demos\\exceldemo"
    :target-name "Gateway.xls")



;; Doc is now its own part, axldoc, and goes with doc/bridges, q.v., below.


;; utilities

(def-part g2utldoc-gdi-pdf
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gdi
    :indep t
    :source-filename ("gdi.pdf")
    :source-subdirectory gdi)

(def-part g2utldoc-gms-pdf
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gms
    :indep t
    :source-filename ("gms.pdf")
    :source-subdirectory gms)

(def-part g2utldoc-goldui-pdf
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/goldui
    :indep t
    :source-filename ("goldui.pdf")
    :source-subdirectory goldui)

(def-part g2utldoc-guideuserguide-pdf
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/guideuserguide
    :indep t
    :source-filename ("guideuserguide.pdf")
    :source-subdirectory guideuserguide)

(def-part g2utldoc-gdd-pdf
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gdd
    :indep t
    :source-filename ("gdd.pdf")
    :source-subdirectory gdd)

(def-part g2utldoc-gfr-pdf
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gfr
    :indep t
    :source-filename ("gfr.pdf")
    :source-subdirectory gfr)

(def-part g2utldoc-golddev-pdf
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/golddev
    :indep t
    :source-filename ("golddev.pdf")
    :source-subdirectory golddev)

(def-part g2utldoc-guideprocref-pdf
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/guideprocref
    :indep t
    :source-filename ("guideprocref.pdf")
    :source-subdirectory guideprocref)

(def-part g2utldoc-gxl-pdf
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gxl
    :indep t
    :source-filename ("gxl.pdf")
    :source-subdirectory gxl)

(def-part g2utldoc-gdi-html
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gdi/html
    :indep t
    :source-subdirectory gdi/html)

(def-part g2utldoc-gms-html
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gms/html
    :indep t
    :source-subdirectory gms/html)

(def-part g2utldoc-goldui-html
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/goldui/html
    :indep t
    :source-subdirectory goldui/html)

(def-part g2utldoc-guideuserguide-html
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/guideuserguide/html
    :indep t
    :source-subdirectory guideuserguide/html)

(def-part g2utldoc-gdd-html
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gdd/html
    :indep t
    :source-subdirectory gdd/html)

(def-part g2utldoc-gfr-html
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gfr/html
    :indep t
    :source-subdirectory gfr/html)

(def-part g2utldoc-golddev-html
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/golddev/html
    :indep t
    :source-subdirectory golddev/html)

(def-part g2utldoc-guideprocref-html
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/guideprocref/html
    :indep t
    :source-subdirectory guideprocref/html)

(def-part g2utldoc-gxl-html
    :source g2utldoc
    :version :80r0
    :destination-directory doc/utilities/gxl/html
    :indep t
    :source-subdirectory gxl/html)


(def-part g2idoc-ug-pdf
    :source g2idoc
    :version :20r0
    :destination-directory doc/g2i/g2developersutilities
    :indep t
    :source-subdirectory g2developersutilities
    :source-filename ("g2developersutilities.pdf"))

(def-part g2idoc-runtime-pdf
    :source g2idoc
    :version :20r0
    :destination-directory doc/g2i/g2runtimelibrary
    :indep t
    :source-subdirectory g2runtimelibrary
    :source-filename ("g2runtimelibrary.pdf"))

(def-part g2idoc-ug-html
    :source g2idoc
    :version :20r0
    :destination-directory doc/g2i/g2developersutilities/html
    :indep t
    :source-subdirectory g2developersutilities/html)

(def-part g2idoc-runtime-html
    :source g2idoc
    :version :20r0
    :destination-directory doc/g2i/g2runtimelibrary/html
    :indep t
    :source-subdirectory g2runtimelibrary/html)



(def-part protoolsdoc
    :version :80r0
    :destination-directory doc/utilities/g2protools
    :source-subdirectory g2protools
    :indep t :source-filename ("g2protools.pdf"))

(def-part protoolsdoc-html
    :source protoolsdoc
    :version :80r0
    :destination-directory doc/utilities/g2protools/html
    :indep t :source-subdirectory g2protools/html)

(def-part gdadoc-api-pdf
    :source gdadoc
    :version :43r0
    :destination-directory doc/gda/gdaapi
    :source-filename ("gdaapi.pdf")
    :indep t :source-subdirectory gda/gdaapi)

(def-part gdadoc-ug-pdf
    :source gdadoc
    :version :43r0
    :destination-directory doc/gda/gdaugrm
    :source-filename ("gdarefman.pdf" "gdaug.pdf")
    :indep t :source-subdirectory gda/gdaugrm)

(def-part gdadoc-api-html
    :source gdadoc
    :version :43r0
    :destination-directory doc/gda/gdaapi/html
    :indep t :source-subdirectory gda/gdaapi/html)

(def-part gdadoc-ug-html
    :source gdadoc
    :version :43r0
    :destination-directory doc/gda/gdaugrm/html
    :indep t :source-subdirectory gda/gdaugrm/html)

(def-part weblinkdoc
    :version :80r0
    :destination-directory doc/bridges/weblink
    :indep t
    :source-subdirectory weblink
    :source-filename ("g2weblink.pdf")
    :shortcuts(g2-weblink-users-guide))

(def-part weblinkdoc-html
    :source weblinkdoc
    :version :80r0
    :destination-directory doc/bridges/weblink/html
    :indep t :source-subdirectory weblink/html)

(def-part g2classicrn
    :version :80r0
    :source-filename "g2relnotes.pdf"
    :indep t
    :destination-directory doc)

;; reference manual

(def-part g2doc-g2refman-pdf
    :source g2doc
    :version :80r0
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
		 ;; G2i
		 g2idoc-users-guide
		 g2idoc-runtime
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
		 g2-pi-bridge-users-guide
		 ;; TW
		 telewindows-users-guide
		 ))

(def-part g2doc-g2tutorials-pdf
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2tutorials
    :source-subdirectory g2tutorials
    :indep t
    :source-filename ("g2tutorials.pdf"))

(def-part g2doc-g2gateway-pdf
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2gateway
    :source-subdirectory g2gateway
    :indep t
    :source-filename ("g2gateway.pdf"))

(def-part g2doc-g2classref-pdf
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2classref
    :source-subdirectory g2classref
    :indep t
    :source-filename ("g2classref.pdf"))

(def-part g2doc-telewindows-pdf
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/telewindows
    :source-subdirectory telewindows
    :indep t
    :source-filename ("telewindows.pdf"))

(def-part g2doc-g2sysprocs-pdf
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2sysprocs
    :source-subdirectory g2sysprocs
    :indep t
    :source-filename ("g2sysprocs.pdf"))

(def-part g2doc-g2langrefcard-pdf
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2langrefcard
    :source-subdirectory g2langrefcard
    :indep t
    :source-filename ("g2langrefcard.pdf"))

(def-part g2doc-g2devguide-pdf
    :source g2doc
    :version :80r0
    :source-subdirectory g2devguide
    :source g2doc
    :destination-directory doc/g2/g2devguide
    :indep t
    :source-filename ("g2devguide.pdf"))



(def-part g2doc-g2tutorials-html
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2tutorials/html
    :source-subdirectory g2tutorials/html
    :indep t)

(def-part g2doc-g2refman-html
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2refman/html
    :source-subdirectory g2refman/html
    :indep t)

(def-part g2doc-g2gateway-html
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2gateway/html
    :source-subdirectory g2gateway/html
    :indep t)

(def-part g2doc-g2classref-html
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2classref/html
    :source-subdirectory g2classref/html
    :indep t)

(def-part g2doc-telewindows-html
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/telewindows/html
    :source-subdirectory telewindows/html
    :indep t)

(def-part g2doc-g2sysprocs-html
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2sysprocs/html
    :source-subdirectory g2sysprocs/html
    :indep t)

(def-part g2doc-g2langrefcard-html
    :source g2doc
    :version :80r0
    :source g2doc
    :destination-directory doc/g2/g2langrefcard/html
    :source-subdirectory g2langrefcard/html
    :indep t)

(def-part g2doc-g2devguide-html
    :source g2doc
    :version :80r0
    :source-subdirectory g2devguide/html
    :source g2doc
    :destination-directory doc/g2/g2devguide/html
    :indep t)


(def-part doc-chm
    :version :80r0
    :source-filename ("G2BundleReleaseNotesHelp.chm" "G2ClassReferenceHelp.chm" "G2Core.html"
		       "G2DevelopersGuideHelp.chm" "G2LanguageReferenceHelp.chm" "G2ProToolsHelp.chm"
		       "G2ReferenceManualHelp.chm" "G2SystemProceduresHelp.chm" "G2Utilities.html"
		       "GDDHelp.chm" "GDIHelp.chm" "GFRHelp.chm" "GMSHelp.chm"
		       "GOLDDevelopersGuideHelp.chm" "GOLDHelp.chm" "GUIDEHelp.chm"
		       "GUIDEUILHelp.chm" "GXLHelp.chm" "GettingStarted.html"
		       "GettingStartedWithG2Help.chm" "Master.chm" "Master.html"
		       "Master2.html" "Master3.html" "TelewindowsHelp.chm")
    :source g2winhelp
    :destination-directory g2
    :shortcuts (doc-chm-shortcut)
    :indep t)

(def-shortcut doc-chm-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "Windows Help G2 Documentation"
    :application-directory "g2"
    :target-name "Master.CHM")


;; Documentation for bridges - Javalink, ActiveXLink, Corbalink, Oracle, Sybase, OPCLink, ODBC:

(def-part jvldoc-javalink-pdf
    :source jvldoc
    :version :13r0
    :destination-directory doc/javalink/docs/guides/g2javalink
    :indep t
    :source-filename ("g2javalink.pdf")
    :source-subdirectory docs/guides/g2javalink
    :shortcuts (
		 ;; Javalink
		 g2-download-interfaces-guide
		 g2-beanbuilder-guide
		 g2-javalink-guide
		 )
    )

(def-part jvldoc-di-pdf
    :source jvldoc
    :version :13r0
    :destination-directory doc/javalink/docs/guides/g2downloadinterfaces
    :indep t
    :source-filename ("g2downloadinterfaces.pdf")
    :source-subdirectory docs/guides/g2downloadinterfaces
    )

(def-part jvldoc-bb-pdf
    :source jvldoc
    :version :13r0
    :destination-directory doc/javalink/docs/guides/g2beanbuilder
    :indep t
    :source-filename ("g2beanbuilder.pdf")
    :source-subdirectory docs/guides/g2beanbuilder
    )

(def-part jvldoc-javalink-html
    :source jvldoc
    :version :13r0
    :destination-directory doc/javalink/docs/guides/g2javalink/html
    :indep t
    :source-subdirectory docs/guides/g2javalink/html
    )

(def-part jvldoc-di-html
    :source jvldoc
    :version :13r0
    :destination-directory doc/javalink/docs/guides/g2downloadinterfaces/html
    :indep t
    :source-subdirectory docs/guides/g2downloadinterfaces/html
    )

(def-part jvldoc-bb-html
    :source jvldoc
    :version :13r0
    :destination-directory doc/javalink/docs/guides/g2beanbuilder/html
    :indep t
    :source-subdirectory docs/guides/g2beanbuilder/html
    )

(def-part axldoc
    :version :11r0
    :destination-directory doc/bridges/activexlink
    :platforms ("nt")
    :indep t :source-filename "g2activexlink.pdf"
    :source-subdirectory activexlink
    :shortcuts (g2-activexlink-users-guide))
(def-part axldoc-html
    :source axldoc
    :version :11r0
    :destination-directory doc/bridges/activexlink/html
    :platforms ("nt")
    :indep t
    :source-subdirectory activexlink/html)

(def-part corbalinkdoc
    :version :10r4
    :destination-directory doc/bridges/corbalink
    :indep t
    :source-filename ("g2corbalink.pdf")
    :source-subdirectory corbalink)

(def-part corbalinkdoc-html
    :source corbalinkdoc
    :version :10r4
    :destination-directory doc/bridges/corbalink/html
    :indep t
    :source-subdirectory corbalink/html)
(def-part g2oradoc
    :version :70r0
    :destination-directory doc/bridges/oracle
    :indep t :source-filename ("g2oraclebridge.pdf")
    :source-subdirectory oracle)


(def-part g2oradoc-html
    :source g2oradoc
    :version :70r0
    :destination-directory doc/bridges/oracle/html
    :indep t
    :source-subdirectory oracle/html)
(def-part g2sybdoc
    :version :70r0
    :destination-directory doc/bridges/sybase
    :indep t
    :source-filename ("g2sybasebridge.pdf")
    :source-subdirectory sybase)
(def-part g2sybdoc-html
    :source g2sybdoc
    :version :70r0
    :destination-directory doc/bridges/sybase/html
    :indep t
    :source-subdirectory sybase/html)
(def-part opclinkdoc
    :version :30r0
    :destination-directory doc/bridges/opclink
    :indep t
    :source-filename ("g2opclink.pdf")
    :source-subdirectory opclink
    )
(def-part opclinkdoc-html
    :source opclinkdoc
    :version :30r0
    :destination-directory doc/bridges/opclink/html
    :indep t
    :source-subdirectory opclink/html)
(def-part g2odbcdoc
    :version :70r0
    :destination-directory doc/bridges/odbc
    :indep t
    :source-filename ("g2odbcbridge.pdf")
    :source-subdirectory odbc
    )
(def-part g2odbcdoc-html
    :source g2odbcdoc
    :version :70r0
    :destination-directory doc/bridges/odbc/html
    :indep t
    :source-subdirectory odbc/html)
(def-part g2pidoc
    :version :60r0
    :destination-directory doc/bridges/pi
    :source-subdirectory pi
    :indep t
    :source-filename ("g2pibridge.pdf")
    )
(def-part g2pidoc-html
    :source g2pidoc
    :version :60r0
    :destination-directory doc/bridges/pi/html
    :indep t
    :source-subdirectory pi/html)

(def-part g2dbdoc
    :version :70r0
    :destination-directory doc/bridges/db
    :source-subdirectory db
    :indep t :source-filename ("g2databasebridge.pdf"))

(def-part g2dbdoc-html :source g2dbdoc
    :version :70r0
    :destination-directory doc/bridges/db/html
    :indep t :source-subdirectory db/html)

(def-part protools
    :version :80r0
    :source protools
    :destination-directory protools/kbs
    :source-filename ("protools.kb" "ptroot.kb")
    :indep t)

(def-part profiler
    :version :80r0
    :source protools
    :source-filename ("profiler.kb" "profroot.kb")
    :destination-directory g2/kbs/utils
    :indep t)

(def-gsi-bridge-ok-parts (:obfuscate t :version 8)
    gw)

(def-gsi-bridge-ok-parts (:obfuscate t :version 7)
    odbc)

(def-gsi-bridge-ok-parts (:obfuscate t :version 7)
    oracle)

(def-gsi-bridge-ok-parts (:obfuscate t :version 7 :non-platforms ("linux"))
    sybase)

(def-gsi-bridge-ok-parts (:obfuscate t :version 6)
    pi)

(def-gsi-bridge-ok-parts (:obfuscate t :version 3)
    opclink)

(def-part g2-readme
    :source g2pkgreadme
    :version :80r0
    :source-filename "readme-g2.html"
    :indep t 
    :shortcuts (g2-readme))

(def-shortcut g2-readme
    :folder-name g2-shortcut-folder-name
    :application-display-name "Readme for G2 Bundle"
    :application-directory ""
    :target-name "readme-g2.html")


(def-part opclink
    :version :30r0
    :destination-directory opclink)

(def-part opclinkkbs
    :source opclink
    :version :30r0
    :destination-directory "opclink/KBs"
    :platforms ("nt")
    :source-subdirectory "KBs")

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
    :version :60r0
    :destination-directory pi)

(def-part pikbs
    :source g2pi
    :version :60r0
    :platforms ("nt")
    :source-filename ("g2-pi.kb gensym-raised-button.kb")
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
    :version :70r0
    :source g2sybase
    :destination-directory sybase
    :non-platforms ("linux"))

(def-part sybasekbs
    :version :70r0
    :source g2sybase
    :source-filename ("g2-database.kb")
    :destination-directory sybase
    :platforms ("nt"))

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
    :version :70r0
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

(def-part odbckbs
    :version :70r0
    :source g2odbc
    :source-filename ("g2-database.kb")
    :destination-directory odbc
    :platforms ("nt"))


(def-part Oraclebridge
    :version :70r0
    :source g2oracle
    :destination-directory oracle)

(def-part oraclekbs
    :version :70r0
    :source g2oracle
    :source-filename ("g2-database.kb")
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

(def-part run-g2-ora90-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora90.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora90.bat\");"
    :shortcuts (ora90-shortcut))

(def-part run-g2-ora92-template-batfile
    :platforms ("nt") 
    :source "/home/development/installers/release-files"
    :source-filename "run-g2-ora92.bat"
    :destination-directory oracle
    :postinstall-code "replace_rootdir(\"oracle\", \"run-g2-ora92.bat\");"
    :shortcuts (ora92-shortcut))

(def-shortcut ora7-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 7 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora7.bat")

(def-shortcut ora80-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 8.0 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora80.bat")

(def-shortcut ora81-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 8.1 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora81.bat")

(def-shortcut ora90-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 9.0 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora90.bat")

(def-shortcut ora92-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 9.2 Bridge"
    :application-directory "oracle"
    :target-name "run-g2-ora92.bat")



;; currently jre is only on Intel NT.  We should be downloading jre on
;; other platforms and providing it on them as well.

(def-component jre
    :print-name "Java Runtime Environment"
    :parts (jre)
    :platforms ("nt"))

(def-part jre
    :version :14r2_03
    :source "jre"
    :platforms ("nt")
    :destination-directory "jre")
