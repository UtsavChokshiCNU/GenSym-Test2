;; -*- mode: lisp; package: bundle -*-

(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; G2-FAMILY - G2 Family Definitions.  Requires bundle.lisp.

;; Mark H. David


(provide 'g2-83b0-family)




;;;; Families



(def-family G2-83b0
    :index 79			; per tools/datafiles/families/family-id.dat
    :file-syntax-version 11
    :bundles (G2-Deployment G2-Development TW-Client)
    :print-name "G2"		; "G2" => "G2 Classic" (MHD 12/13/01)
				; "G2 Classic" => "G2" (yduJ 1/28/02)
    
    :directory "g2-8.3b0"
    ;; per tools/datafiles/families/guid.dat:
    :guid "93f4944a-2607-4b88-a977-44ef51b0cff9"
    :compatible-previous-versions (("8.3a1" "7e2afbe3-f71a-4c50-90a6-269814d09516")
				   ("8.3a0" "119575e2-3b3e-4158-9e34-fe3a31320d41")
 				   ("8.2r4" "fcc3a967-d7c7-4dd1-bc53-39f61afcefe5")
				   ("8.2r3" "7e98adb1-7abc-4415-a822-cb6e676eeb67")
				   ("8.2r2" "67545f8b-1c2a-4d7d-bffb-f7ef063dcd10")
				   ("8.2r1" "1b16e687-98f4-478c-bb0f-d775eb0d1a46")
				   ("8.2r0" "d71bceeb-1631-491c-91a7-1a0d9a5c2e26")
				   ("8.2a0" "845b6aad-861d-44b5-a36e-2eab7524f82f")
				   ("8.1r1" "e1417885-cf39-4385-8c10-3e843e35c1ec")
				   ("8.1r0" "17d47941-887f-48e1-86eb-7eff3e5a9224")
				   ("8.1b0" "c4664f9c-db38-4afe-b5d6-992a046c7d99")
				   ("8.1a0" "3a6d5b1d-08e5-42fa-973e-518ccd5c2b9e")
				   ("8.0r1" "9bce1969-7fbf-45a4-91cc-f54d294a7531")
				   ("8.0r0" "c5192361-2347-4ec2-827c-a9af41ddc6c9")
				   ("8.0b0" "74ee5cc5-de60-4cd0-8012-c8da127d35b8")
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



(defvar g2-shortcut-folder-name "Gensym G2 8.3b0")

;;; Family G2 OK Files


;;; For g2-deployment, 4 is the standard number of clients.  For g2-development
;;; 1 is the standard number of clients.  For development, we supply this in
;;; increments of 1 up to 10, thereafter in increments of 4.  Deployment only
;;; has increments of 4.

;;; We also supply 2-G2-process OK files in a number of specific increments, as
;;; suggested by Customer Support; these are the items with a "2" as the second
;;; element.  The ones with dates are temporary OK files.

(setq prevailing-ok-version-suffix "-v8")

#|
(def-g2-ok-components (g2-development :obfuscate :from-sandbox)
    g2 "Development"
  (1 2 3 4 5 6 7 8 9 10 12 16
     (1 2) (2 2) (3 2) (4 2) (5 2) (6 2) (7 2) (8 2) (9 2) (10 2) 
     (1 "-oct25-2006") (1 "-nov25-2006") (1 "-dec25-2006")
     (1 "-jan25-2007") (1 "-feb25-2007") (1 "-mar25-2007")
     (1 "-apr25-2007") (1 "-may25-2007") (1 "-jun25-2007")
     (1 "-jul25-2007") (1 "-aug25-2007") (1 "-sep25-2007")          
     (1 "-oct25-2007") (1 "-nov25-2007") (1 "-dec25-2007")
     (1 "-jan25-2008") (1 "-feb25-2008") (1 "-mar25-2008")))
;; => (defvar g2-development-family-ok-components '(g2-development g2-development-4 ...))

(def-g2-ok-components (g2-deployment :obfuscate :from-sandbox) g2 "Deployment"
  (4 8 12 16
     (4 2) (5 2) (8 2) (12 2) (16 2) ))
|#

(defvar g2-development-family-ok-components '(g2-megabundle-ok-file))

(defvar g2-deployment-family-ok-components '(g2-megabundle-ok-file))

(def-component g2-megabundle-ok-file
  :print-name "G2 83b0 OK file"
  :radio-button-group-index 1
  :parts (g2-megabundle-ok-file)
  :watermark "g2/g2.ok")

(def-part g2-megabundle-ok-file
    :destination-directory g2
    :destination-filename g2.ok
    :indep t
    :source "$SRCBOX/bundle/ok"
    :source-filename "g2-83b0-megabundle.obf"
    :obfuscate :from-sandbox)




;;;; Bundles


(defvar core-g2-components
  '(g2 telewindows gateway gateway-itanium gda g2i-core-modules weblink javalink
    activexlink
    corbalink opclink pibridge Oraclebridge Sybasebridge ODBCbridge gservice
    g2-readme protools))

(defvar additional-g2-components '(jmail-component jms-component socket-manager jsnmp-bridge hla-bridge))

(defvar additional-g2-deployment-components '(jre))

(defvar additional-g2-development-components '(jre doc-pdf doc-html doc-chm))


(def-bundle g2-deployment
    :components (core-g2-components
		  additional-g2-components
		  additional-g2-deployment-components 
		  g2-deployment-family-ok-components
		  g2-blank-ok-component
		  rethink escor nol integrity optegrity symcure
		  )
    :version :83b0
    :print-name "G2 Deployment"
    :directory "deployment")

(def-bundle g2-development
    :components (core-g2-components
		  additional-g2-components
		  additional-g2-development-components
		  g2-development-family-ok-components
		  g2-blank-ok-component
		  rethink escor nol integrity optegrity symcure
		  )
    :version :83b0
    :print-name "G2 Development"
    :directory "development")


(def-bundle tw-client
    :components (telewindows doc-chm)
    :version :83b0
    :print-name "Telewindows Client"
    :directory "client"
    :platforms ("nt"))


;;;; Components



(def-component g2
  :parts
  (g2-intelnt g2-unix
	      kanji-dic ext-directory
	      g2-blank-ok
	      kbs fonts mill-demo startserver-bat-file startserver-sh-file registerControls
	      ;;The following kbs are requested by the application products to
	      ;;be available even when the bridge itself is not authorized.
	      ;;Suggestion HQ-4795626.
	      jmskbs odbckbs oraclekbs sybasekbs pikbs opclinkkbs socket-manager-kbs 
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
	   tw-unix twng tw-win2000
	   twax twax-examples workspace-view
	   ;; same in G2, OK to specify twice, may be overwritten:
	   fonts)
  :include-in-contents (tw-intelnt tw-unix)
  :print-name "Telewindows")

(def-component gateway
  :parts (gsi gsi-intc gsi-msvc)
  :print-name "G2 Gateway (GSI)"
  :include-in-contents (gsi gsi-msvc))
(def-component gateway-itanium
  :parts (gsi-itanium)
  :print-name "G2 Gateway (GSI) for HP-UX Itanium"
  :optional true
  :platforms ("hpux"))

(def-component gda :parts (gda) :print-name "G2 Diagnostic Assistant (GDA)")
(def-component gda-45r1 :parts (gda-45r1)
	       :print-name "G2 Diagnostic Assistant (GDA) Version 4-5 Rev 1"
	       :optional true)
(def-component weblink :parts (gw gsi-gw-ok run-gw-template-batfile gsi-gw-blank-ok) :print-name "G2 WebLink")
(defvar basic-jvl-parts
  '(jvl-unix jvl-intelnt jvl-com-gensym-properties-intelnt jvl-javadoc))
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
	   g2doc-g2sysprocrefcard-pdf
	   g2utldoc-gdi-pdf g2utldoc-gms-pdf g2utldoc-goldui-pdf
	   g2utldoc-guideuserguide-pdf g2utldoc-gdd-pdf g2utldoc-gfr-pdf
	   g2utldoc-golddev-pdf g2utldoc-guideprocref-pdf g2utldoc-gxl-pdf
	   g2idoc-gdsm-pdf g2idoc-gdu-pdf g2idoc-gerr-pdf
	   g2idoc-gevm-pdf g2idoc-grlb-pdf g2idoc-grtl-pdf g2idoc-gdpm-pdf 
	   g2idoc-gedp-pdf g2idoc-grpe-pdf g2idoc-gweb-pdf g2idoc-bpms-pdf g2idoc-brms-pdf
	   g2idoc-geuc-pdf hladoc-pdf
	   jvldoc-javalink-pdf jvldoc-di-pdf jvldoc-bb-pdf axldoc corbalinkdoc
		 g2classicrn 
		   g2oradoc g2sybdoc opclinkdoc g2pidoc g2odbcdoc
		   g2dbdoc protoolsdoc weblinkdoc gdadoc-api-pdf gdadoc-ug-pdf
		   snmpdoc-pdf)
  :print-name "G2 Full Documentation (PDF)"
  :include-in-contents (g2doc-g2refman-pdf)
  :typical false)

(def-component doc-html
  :parts (;g2classicrn-html
	  g2doc-g2refman-html g2doc-g2tutorials-html g2doc-g2gateway-html
	  g2doc-g2classref-html g2doc-telewindows-html g2doc-g2sysprocs-html
	  g2doc-g2langrefcard-html g2doc-g2sysprocsrefcard-html g2doc-g2devguide-html
	  g2utldoc-gdi-html g2utldoc-gms-html g2utldoc-goldui-html
	  g2utldoc-guideuserguide-html g2utldoc-gdd-html g2utldoc-gfr-html
	  g2utldoc-golddev-html g2utldoc-guideprocref-html g2utldoc-gxl-html
	  g2idoc-gdsm-html g2idoc-gdu-html g2idoc-gerr-html
	  g2idoc-gevm-html g2idoc-grlb-html g2idoc-grtl-html g2idoc-gdpm-html
	  g2idoc-gedp-html g2idoc-grpe-html g2idoc-gweb-html g2idoc-bpms-html g2idoc-brms-html
	  g2idoc-geuc-html hladoc-html
	  jvldoc-javalink-html jvldoc-di-html jvldoc-bb-html axldoc-html corbalinkdoc-html 
	  g2oradoc-html g2sybdoc-html opclinkdoc-html g2pidoc-html g2odbcdoc-html
	  g2dbdoc-html protoolsdoc-html weblinkdoc-html gdadoc-api-html gdadoc-ug-html
	  snmpdoc-html)
  :print-name "G2 Full Documentation (HTML/Gold)"
  :include-in-contents (g2doc-g2refman-html)
  :typical false)

(def-component doc-chm
  :platforms ("nt")
  :parts (doc-chm)
  :print-name "G2 Core Documentation (Windows Help)"
  :typical true)


(def-component g2-readme :parts (g2-readme) :print-name "G2 Readme")

(def-component protools :parts (protools profiler profiler-demo) :print-name "G2 ProTools")




;;; Optional Bridges in G2: Two bridges are standard (picked by the customer at
;;; order time), and others may be optionally chosen, i.e., at order time.
;;;
;;; Optional Bridges: (1) corbalink (2) opclink (3) Oraclebridge (4)
;;; Sybasebridge (5) ODBCbridge (6) Pi Bridge (7) JMS (8) Socket Manager
;;; (9) HLA Bridge
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
	       :print-name "G2 OPCLink Bridge"
	       :optional true)

(def-component pibridge :parts (g2pi gsi-pi-ok
				 run-g2-pi-template-batfile gsi-pi-blank-ok) :platforms ("nt")
	       :print-name "G2 PI Bridge"
	       :optional true)

(def-component Oraclebridge :parts (Oraclebridge gsi-Oracle-ok run-g2-ora7-template-batfile run-g2-ora80-template-batfile run-g2-ora81-template-batfile run-g2-ora90-template-batfile run-g2-ora92-template-batfile run-g2-ora10-template-batfile gsi-Oracle-blank-ok)
	       :print-name "G2 Oracle Bridge"
	       :optional true)
(def-component Sybasebridge :parts (Sybasebridge gsi-Sybase-ok run-g2-sybase11-template-batfile run-g2-sybase125-template-batfile gsi-Sybase-blank-ok)
	       :print-name "G2 Sybase Bridge"
	       :non-platforms ("linux")
	       :optional true)
(def-component ODBCbridge :parts (ODBCbridge gsi-ODBC-ok run-g2-odbc-template-batfile gsi-ODBC-blank-ok) :platforms ("nt")
	       :print-name "G2 ODBC Bridge"
	       :optional true)





;;;; Parts



(def-part g2-intelnt
    :version :83b0
    :print-name "G2 Windows Executable"
    :source g2
    :source-filename ("g2.exe" "g2passwd.exe")
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (g2-shortcut))

(def-shortcut startserver-shortcut
    :folder-name g2-shortcut-folder-name
    :application-directory "g2"
    :target-name "StartServer.bat"
    :icon-file "g2.exe"
    :icon-index 0)
    

(def-shortcut g2-shortcut
    :parent startserver-shortcut
    :application-display-name "Start G2 Server"
    :parameters "-netinfo")

(def-part g2-unix
    :version :83b0
    :print-name "G2 Unix Executable"
    :source g2
    :source-filename ("g2" "g2passwd")
    :destination-directory "g2"
    :non-platforms ("nt"))

(def-part g2-blank-ok
    :version :83b0
    :print-name "Sample G2 OK file"
    :source g2
    :source-filename "g2.ok"
    :destination-directory "g2")

(def-part kanji-dic
    :version :83b0
    :print-name "Kanji dictionary files"
    :source g2
    :source-filename ("index.dic" "kojin.dic" "main.dic")
    :destination-directory "g2")

(def-part ext-directory
    :version :83b0
    :print-name "G2 EXT Directory"
    :source g2
    :source-subdirectory "ext"
    :destination-directory "g2/ext")

(def-part tw-intelnt
    :version :83b0
    :print-name "TW Windows Executable"
    :source tw
    :source-filename ("tw.exe" "nptwplug.dll" "pegrp32g.dll")
    :destination-directory "g2"
    :platforms ("nt")
    :shortcuts (tw-shortcut)
    :postinstall-code "LaunchAppAndWait(TARGETDIR ^ \"g2\"^\"tw.exe\", \"/regserver /s\", WAIT);"
    :uninstall-code "LaunchAppAndWait(TARGETDIR ^ \"g2\"^\"tw.exe\", \"/unregserver /s\", WAIT);")

(def-part tw-win2000
    :version :83b0
    :print-name "TW Windows Support DLL"
    :source tw
    :source-subdirectory win2000
    :source-filename ("gdiplus.dll")
    :destination-directory "g2"
    :postinstall-code "DeleteDLLIfNotNeeded(\"gdiplus.dll\",5,1,\"g2\");"
    :platforms ("nt"))

(def-part twng
    ;;This kluge brought to you by the wonders of the bundle version number decomposer.
    :version :83b0-NG
    :print-name "TW Next Generation"
    :source tw
    :source-filename ("twng.exe")
    :destination-directory "g2"
    :preinstall-code "VerifyDLLVersion(\"comctl32.dll\",4,71,\"\",\"Telewindows\");VerifyDLLVersion(\"shell32.dll\",4,71,\"shfolder.dll\",\"Telewindows\");"
    :postinstall-code "LaunchAppAndWait(TARGETDIR ^ \"g2\"^\"twng.exe\", \"/regserver /s\", WAIT);"
    :uninstall-code "LaunchAppAndWait(TARGETDIR ^ \"g2\"^\"twng.exe\", \"/unregserver /s\", WAIT);"
    :platforms ("nt")
    :shortcuts (twng-shortcut))

(def-shortcut tw-shortcut-multiwindow
    :folder-name g2-shortcut-folder-name
    :application-display-name "Telewindows (Multiwindow)"
    :application-directory "g2"
    :target-name "tw.exe"
    :parameters "-ui multiwindow")

(def-shortcut tw-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "Telewindows"
    :application-directory "g2"
    :target-name "tw.exe")

(def-shortcut twng-shortcut
    :folder-name g2-shortcut-folder-name
    :application-display-name "Telewindows Next Generation"
    :application-directory "g2"
    :target-name "twng.exe")

(def-part tw-unix
    :version :83b0
    :print-name "TW Unix Executable"
    :source tw
    :source-filename ("tw" "nptwplug.so")
    :destination-directory "g2"
    :non-platforms ("nt"))


(def-part twax
    :version :83b0
    :source-filename ("TwControl.cab" "unregisterTwControl.bat" "TwControl.ocx"
		      "install.html" "registerTwControl.bat")
    :destination-directory "g2"
    :platforms ("nt"))

(def-part twax-examples
    :version :83b0
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
    :version :83b0
    :destination-directory "g2"
    :source-filename ("WSView.frm" "WSView.frx" "WorkspaceView.ocx" "WorkspaceViewDemo.exe" "WorkspaceViewDemo.vbp" "WorkspaceViewDemo.vbw" "registerWSV.bat" "unregisterWSV.bat" "wsvdemo.kb" "wsview.html")
    :platforms ("nt")
    :shortcuts (WorkspaceViewDemo WorkspaceViewDemoExe workspace-view wsview-html))

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
    :parent startserver-shortcut
    :application-display-name "G2 for Workspace View Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "Workspace View"
    :parameters "-kb wsvdemo.kb -tcpport 1112 -tcpipexact")

(def-shortcut wsview-html
    :folder-name g2-shortcut-folder-name
    :application-display-name "HTML Page"
    :subfolder-name "Examples"
    :subsubfolder-name "Workspace View"
    :application-directory "g2"
    :target-name "wsview.html")


(def-part kbs
  :version :83b0
  :destination-directory g2/kbs
  :indep t
  ;; KBs are read-only, which is not terribly bad by itself, but causes
  ;; a problem: doing uninstall on Windows.
  :make-not-read-only t
  :shortcuts (g2-80r0-doc-examples dialogs-demo gms-native-language-demo
              gms-native-large-menu-demo gms-native-multiple-menubar-demo
	      gms-native-popup-demo nmsdemo publish-subscribe-doc-ex
	      publish-subscribe-remote-doc-ex space business explnfac
	      g2gl-demo charts-demo g2web-demo))

(def-part mill-demo
    :source demos
    :version :83b0
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
    :target-name "start-mill.bat"
    :icon-file "../../g2.exe"
    :icon-index 0)

(def-shortcut g2-80r0-doc-examples
    :parent startserver-shortcut
    :application-display-name "G2 8.0 Documentation"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\g2-80r0-doc-examples.kb")

(def-shortcut dialogs-demo
    :parent startserver-shortcut
    :application-display-name "Windows Dialogs"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\dialogs-demo.kb")

(def-shortcut g2gl-demo
    :parent startserver-shortcut
    :application-display-name "G2GL Credit Rating Example"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\g2gl-credit-rating-example.kb")

(def-shortcut charts-demo
    :parent startserver-shortcut
    :application-display-name "Charts Example"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\samples\\charts.kb")

(def-shortcut gms-native-language-demo
    :parent startserver-shortcut
    :application-display-name "Windows GMS Menus"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\gms-native-language-demo.kb")


(def-shortcut gms-native-large-menu-demo
    :parent startserver-shortcut
    :application-display-name "Windows Large GMS Menus"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\gms-native-large-menu-demo.kb")


(def-shortcut gms-native-multiple-menubar-demo
    :parent startserver-shortcut
    :application-display-name "Windows Multiple GMS Menubar"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\gms-native-multiple-menubar-demo.kb")

(def-shortcut gms-native-popup-demo
    :parent startserver-shortcut
    :application-display-name "Windows GMS Menubar"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\gms-native-popup-demo.kb")

(def-shortcut nmsdemo
    :parent startserver-shortcut
    :application-display-name "NMS Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\nmsdemo.kb")

(def-shortcut publish-subscribe-doc-ex
    :parent startserver-shortcut
    :application-display-name "Publish Subscribe"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\publish-subscribe-doc-ex.kb")

(def-shortcut publish-subscribe-remote-doc-ex
    :parent startserver-shortcut
    :application-display-name "Remote Publish Subscribe"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\publish-subscribe-remote-doc-ex.kb")

(def-shortcut space
    :parent startserver-shortcut
    :application-display-name "Space Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\space.kb")

(def-shortcut business
    :parent startserver-shortcut
    :application-display-name "Business Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\business.kb")

(def-shortcut explnfac
    :parent startserver-shortcut
    :application-display-name "Rules Explanation"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\explnfac.kb")

(def-shortcut g2web-demo
    :parent startserver-shortcut
    :application-display-name "Web Services"
    :subfolder-name "Examples"
    :subsubfolder-name "G2"
    :parameters "-kb kbs\\demos\\g2web-demo.kb")

(def-part startserver-bat-file
    :source demos
    :version :83b0
    :source-filename ("StartServer.bat")
    :destination-directory g2
    :platforms ("nt")
    :postinstall-code "replace_rootdir(\"g2\", \"StartServer.bat\");"
    :indep t ;; it's on indep even though it's really not independent.
             ;;Other demos were that way, just piggybacked on existing product.
    )


(def-part startserver-sh-file
    :source demos
    :version :83b0
    :source-filename ("startserver")
    :destination-directory g2
    :non-platforms ("nt")
    :postinstall-code "replace_rootdir(\"g2\", \"startserver\");"
    :indep t ;; it's on indep even though it's really not independent.
             ;;Other demos were that way, just piggybacked on existing product.
    )

(def-part registerControls
    :source demos
    :version :83b0
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
    :version :83b0
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

(def-shortcut g2-release-notes-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :application-display-name "G2 Bundle Release Notes"
    :application-directory "doc\\g2\\g2relnotes\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Reference Manual"
    :application-directory "doc\\g2\\g2refman"
    :target-name "g2refman.pdf")

(def-shortcut g2-reference-manual-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "G2 Reference Manual"
    :application-directory "doc\\g2\\g2refman\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-reference-card
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Language Reference Card"
    :application-directory "doc\\g2\\g2langrefcard"
    :target-name "g2langrefcard.pdf")

(def-shortcut g2-reference-card-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "G2 Language Reference Card"
    :application-directory "doc\\g2\\g2langrefcard\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-sysproc-refcard
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 System Procedures Reference Card"
    :application-directory "doc\\g2\\g2sysprocsrefcard"
    :target-name "g2sysprocsrefcard.pdf")

(def-shortcut g2-sysproc-refcard-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "G2 System Procedures Reference Card"
    :application-directory "doc\\g2\\g2sysprocsrefcard\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-system-procedures-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 System Procedures Reference Manual"
    :application-directory "doc\\g2\\g2sysprocs"
    :target-name "g2sysprocs.pdf")

(def-shortcut g2-system-procedures-reference-manual-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "G2 System Procedures Reference Manual"
    :application-directory "doc\\g2\\g2sysprocs\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Getting Started with G2 Tutorials"
    :application-directory "doc\\g2\\g2tutorials"
    :target-name "g2tutorials.pdf")

(def-shortcut g2-tutorial-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "Getting Started with G2 Tutorials"
    :application-directory "doc\\g2\\g2tutorials\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-class-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Class Reference Manual"
    :application-directory "doc\\g2\\g2classref"
    :target-name "g2classref.pdf")

(def-shortcut g2-class-reference-manual-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "G2 Class Reference Manual"
    :application-directory "doc\\g2\\g2classref\\html"
    :target-name "titlepag.htm")

;; not included in 5.2r0 bundle
(def-shortcut g2-developers-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Developers' Guide"
    :application-directory "doc\\g2\\g2devguide"
    :target-name "g2devguide.pdf")

(def-shortcut g2-developers-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "G2 Developers' Guide"
    :application-directory "doc\\g2\\g2devguide\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-dynamic-displays-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Dynamic Displays User's Guide (GDD)"
    :application-directory "doc\\utilities\\gdd"
    :target-name "gdd.pdf")

(def-shortcut g2-dynamic-displays-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Dynamic Displays User's Guide (GDD)"
    :application-directory "doc\\utilities\\gdd\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-developers-interface-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Developers' Interface User's Guide (GDI)"
    :application-directory "doc\\utilities\\gdi"
    :target-name "gdi.pdf")

(def-shortcut g2-developers-interface-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Developers' Interface User's Guide (GDI)"
    :application-directory "doc\\utilities\\gdi\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-foundation-resources-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Foundation Resources User's Guide (GFR)"
    :application-directory "doc\\utilities\\gfr"
    :target-name "gfr.pdf")

(def-shortcut g2-foundation-resources-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Foundation Resources User's Guide (GFR)"
    :application-directory "doc\\utilities\\gfr\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-menu-system-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Menu System User's Guide (GMS)"
    :application-directory "doc\\utilities\\gms"
    :target-name "gms.pdf")

(def-shortcut g2-menu-system-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Menu System User's Guide (GMS)"
    :application-directory "doc\\utilities\\gms\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-online-documentation-developers-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation Developers' Guide (GOLD)"
    :application-directory "doc\\utilities\\golddev"
    :target-name "golddev.pdf")

(def-shortcut g2-online-documentation-developers-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation Developers' Guide (GOLD)"
    :application-directory "doc\\utilities\\golddev\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-online-documentation-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation User's Guide (GOLD)"
    :application-directory "doc\\utilities\\goldui"
    :target-name "goldui.pdf")

(def-shortcut g2-online-documentation-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation User's Guide (GOLD)"
    :application-directory "doc\\utilities\\goldui\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-guide-uil-procedures-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE UIL Procedures Reference Manual"
    :application-directory "doc\\utilities\\guideprocref"
    :target-name "guideprocref.pdf")

(def-shortcut g2-guide-uil-procedures-reference-manual-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE UIL Procedures Reference Manual"
    :application-directory "doc\\utilities\\guideprocref\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-guide-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE User's Guide"
    :application-directory "doc\\utilities\\guideuserguide"
    :target-name "guideuserguide.pdf")

(def-shortcut g2-guide-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 GUIDE User's Guide"
    :application-directory "doc\\utilities\\guideuserguide\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-xl-spreadsheet-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 XL Spreadsheet User's Guide (GXL)"
    :application-directory "doc\\utilities\\gxl"
    :target-name "gxl.pdf")

(def-shortcut g2-xl-spreadsheet-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 XL Spreadsheet User's Guide (GXL)"
    :application-directory "doc\\utilities\\gxl\\html"
    :target-name "titlepag.htm")

;; G2i

(def-shortcut g2idoc-gdsm
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Data Source Manager User's Guide (GDSM)"
    :application-directory "doc\\g2i\\gdsm"
    :target-name "gdsm.pdf")

(def-shortcut g2idoc-gdsm-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Data Source Manager User's Guide (GDSM)"
    :application-directory "doc\\g2i\\gdsm\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-gdu
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Dialog Utility User's Guide (GDU)"
    :application-directory "doc\\g2i\\gdu"
    :target-name "gdu.pdf")

(def-shortcut g2idoc-gdu-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Dialog Utility User's Guide (GDU)"
    :application-directory "doc\\g2i\\gdu\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-gerr
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Error Handling Foundation User's Guide (GERR)"
    :application-directory "doc\\g2i\\gerr"
    :target-name "gerr.pdf")

(def-shortcut g2idoc-gerr-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Error Handling Foundation User's Guide (GERR)"
    :application-directory "doc\\g2i\\gerr\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-gevm
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Event Manager User's Guide (GEVM)"
    :application-directory "doc\\g2i\\gevm"
    :target-name "gevm.pdf")

(def-shortcut g2idoc-gevm-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Event Manager User's Guide (GEVM)"
    :application-directory "doc\\g2i\\gevm\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-grlb
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Relation Browser User's Guide (GRLB)"
    :application-directory "doc\\g2i\\grlb"
    :target-name "grlb.pdf")

(def-shortcut g2idoc-grlb-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Relation Browser User's Guide (GRLB)"
    :application-directory "doc\\g2i\\grlb\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-grtl
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Run-Time Library User's Guide (GRTL)"
    :application-directory "doc\\g2i\\grtl"
    :target-name "grtl.pdf")

(def-shortcut g2idoc-grtl-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Run-Time Library User's Guide (GRTL)"
    :application-directory "doc\\g2i\\grtl\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-gdpm
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Data Point Manager User's Guide (GDPM)"
    :application-directory "doc\\g2i\\gdpm"
    :target-name "gdpm.pdf")

(def-shortcut g2idoc-gdpm-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Data Point Manager User's Guide (GDPM)"
    :application-directory "doc\\g2i\\gdpm\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-grpe
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Reporting Engine User's Guide (GRPE)"
    :application-directory "doc\\g2i\\grpe"
    :target-name "grpe.pdf")

(def-shortcut g2idoc-grpe-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Reporting Engine User's Guide (GRPE)"
    :application-directory "doc\\g2i\\grpe\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-brms
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "Business Rules Management System User's Guide (BRMS)"
    :application-directory "doc\\g2i\\brms"
    :target-name "brms.pdf")

(def-shortcut g2idoc-brms-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "Business Rules Management System User's Guide (BRMS)"
    :application-directory "doc\\g2i\\brms\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-bpms
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "Business Process Management System User's Guide (BPMS)"
    :application-directory "doc\\g2i\\bpms"
    :target-name "bpms.pdf")

(def-shortcut g2idoc-bpms-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "Business Process Management System User's Guide (BPMS)"
    :application-directory "doc\\g2i\\bpms\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-gedp
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Event and Data Processing User's Guide (GEDP)"
    :application-directory "doc\\g2i\\gedp"
    :target-name "gedp.pdf")

(def-shortcut g2idoc-gedp-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Event and Data Processing User's Guide (GEDP)"
    :application-directory "doc\\g2i\\gedp\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-geuc
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Engineering Unit Conversion User's Guide (GEUC)"
    :application-directory "doc\\g2i\\geuc"
    :target-name "geuc.pdf")

(def-shortcut g2idoc-geuc-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Engineering Unit Conversion User's Guide (GEUC)"
    :application-directory "doc\\g2i\\geuc\\html"
    :target-name "titlepag.htm")

(def-shortcut g2idoc-gweb
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Web User's Guide (GWEB)"
    :application-directory "doc\\g2i\\gweb"
    :target-name "gweb.pdf")

(def-shortcut g2idoc-gweb-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Web User's Guide (GWEB)"
    :application-directory "doc\\g2i\\gweb\\html"
    :target-name "titlepag.htm")

(def-part hladoc-pdf
    :source hladoc
    :version :20b0
    :destination-directory doc/bridges/hla
    :source-filename ("g2hla.pdf")    
    :shortcuts (hladoc-pdf)
    :indep t)

(def-part hladoc-html
    :source hladoc
    :version :20b0
    :destination-directory doc/bridges/hla/html
    :source-subdirectory html
    :shortcuts (hladoc-html)
    :indep t)

(def-shortcut hladoc-pdf
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 HLA User's Guide"
    :application-directory "doc\\bridges\\hla"
    :target-name "g2hla.pdf")

(def-shortcut hladoc-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 HLA User's Guide"
    :application-directory "doc\\bridges\\hla\\html"
    :target-name "titlepag.htm")


;; GDA

(def-shortcut gda-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA User's Guide"
    :application-directory "doc\\gda\\gdaugrm"
    :target-name "gdaug.pdf")

(def-shortcut gda-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "GDA"
    :application-display-name "GDA User's Guide"
    :application-directory "doc\\gda\\gdaugrm\\html"
    :target-name "titlepag.htm")

(def-shortcut gda-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA Reference Manual"
    :application-directory "doc\\gda\\gdaugrm"
    :target-name "gdarefman.pdf")

(def-shortcut gda-reference-manual-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "GDA"
    :application-display-name "GDA Reference Manual"
    :application-directory "doc\\gda\\gdaugrm\\html"
    :target-name "titlepag.htm")

(def-shortcut gda-api-reference-manual
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "GDA"
    :application-display-name "GDA API Reference Manual"
    :application-directory "doc\\gda\\gdaapi"
    :target-name "gdaapi.pdf")

(def-shortcut gda-api-reference-manual-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "GDA"
    :application-display-name "GDA API Reference Manual"
    :application-directory "doc\\gda\\gdaapi\\html"
    :target-name "titlepag.htm")


;; G2 ProTools

(def-shortcut g2-protools-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 ProTools User's Guide"
    :application-directory "doc\\utilities\\g2protools"
    :target-name "g2protools.pdf")

(def-shortcut g2-protools-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 ProTools User's Guide"
    :application-directory "doc\\utilities\\g2protools\\html"
    :target-name "titlepag.htm")

;; G2 Gateway (GSI)

(def-shortcut gsi-bridge-developers-guide
    ;; "Everyone knows this informally as 'the GSI manual'". --peter k.
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "G2 Gateway Bridge Developers' Guide"
    :application-directory "doc\\g2\\g2gateway"
    :target-name "g2gateway.pdf")

(def-shortcut gsi-bridge-developers-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "G2 Gateway Bridge Developers' Guide"
    :application-directory "doc\\g2\\g2gateway\\html"
    :target-name "titlepag.htm")

;; Bridges

(def-shortcut g2-database-bridge-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 Database Bridge User's Guide"
    :application-directory "doc\\bridges\\db"
    :target-name "g2databasebridge.pdf")

(def-shortcut g2-database-bridge-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 Database Bridge User's Guide"
    :application-directory "doc\\bridges\\db\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-opclink-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 OPCLink User's Guide"
    :application-directory "doc\\bridges\\opclink"
    :target-name "g2opclink.pdf")

(def-shortcut g2-opclink-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 OPCLink User's Guide"
    :application-directory "doc\\bridges\\opclink\\html"
    :target-name "titlepag.htm")


(def-shortcut g2-corba-link-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 CORBALink User's Guide"
    :application-directory "doc\\bridges\\corbalink"
    :target-name "g2corbalink.pdf")

(def-shortcut g2-corba-link-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 CORBALink User's Guide"
    :application-directory "doc\\bridges\\corbalink\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-odbc-bridge-release-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-ODBC Bridge Release Notes"
    :application-directory "doc\\bridges\\odbc"
    :target-name "g2odbcbridge.pdf")

(def-shortcut g2-odbc-bridge-release-notes-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-ODBC Bridge Release Notes"
    :application-directory "doc\\bridges\\odbc\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-pi-bridge-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-PI Bridge User's Guide"
    :application-directory "doc\\bridges\\pi"
    :target-name "g2pibridge.pdf")

(def-shortcut g2-pi-bridge-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-PI Bridge User's Guide"
    :application-directory "doc\\bridges\\pi\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-oracle-bridge-release-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Oracle Bridge Release Notes"
    :application-directory "doc\\bridges\\oracle"
    :target-name "g2oraclebridge.pdf")

(def-shortcut g2-oracle-bridge-release-notes-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Oracle Bridge Release Notes"
    :application-directory "doc\\bridges\\oracle\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-sybase-bridge-release-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Sybase Bridge Release Notes"
    :application-directory "doc\\bridges\\sybase"
    :target-name "g2sybasebridge.pdf")

(def-shortcut g2-sybase-bridge-release-notes-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-Sybase Bridge Release Notes"
    :application-directory "doc\\bridges\\sybase\\html"
    :target-name "titlepag.htm")


;; Telewindows

(def-shortcut telewindows-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2"
    :application-display-name "Telewindows User's Guide"
    :application-directory "doc\\g2\\telewindows"
    :target-name "telewindows.pdf")

(def-shortcut telewindows-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "Telewindows User's Guide"
    :application-directory "doc\\g2\\telewindows\\html"
    :target-name "titlepag.htm")



;; Javalink

(def-shortcut g2-download-interfaces-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 DownloadInterfaces User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2downloadinterfaces"
    :target-name "g2downloadinterfaces.pdf")

(def-shortcut g2-download-interfaces-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 DownloadInterfaces User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2downloadinterfaces\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-beanbuilder-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 Bean Builder User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2beanbuilder"
    :target-name "g2beanbuilder.pdf")

(def-shortcut g2-beanbuilder-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 Bean Builder User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2beanbuilder\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-javalink-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 JavaLink User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2javalink"
    :target-name "g2javalink.pdf")

(def-shortcut g2-javalink-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 JavaLink"
    :application-display-name "G2 JavaLink User's Guide"
    :application-directory "doc\\javalink\\docs\\guides\\g2javalink\\html"
    :target-name "titlepag.htm")




;; G2 ActiveXLink

(def-shortcut g2-activexlink-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 ActiveXLink User's Guide"
    :application-directory "doc\\bridges\\activexlink"
    :target-name "g2activexlink.pdf")

(def-shortcut g2-activexlink-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 ActiveXLink User's Guide"
    :application-directory "doc\\bridges\\activexlink\\html"
    :target-name "titlepag.htm")

;; G2 WebLink

(def-shortcut g2-weblink-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 WebLink User's Guide"
    :application-directory "doc\\bridges\\weblink"
    :target-name "g2weblink.pdf")

(def-shortcut g2-weblink-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 WebLink User's Guide"
    :application-directory "doc\\bridges\\weblink\\html"
    :target-name "titlepag.htm")

;; SNMP bridge

(def-shortcut snmpdoc-pdf
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-SNMP Bridge User's Guide"
    :application-directory "doc\\bridges\\snmp"
    :target-name "g2snmp.pdf")

(def-shortcut snmpdoc-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-SNMP Bridge User's Guide"
    :application-directory "doc\\bridges\\snmp\\html"
    :target-name "titlepag.htm")

(def-part gsi
    :version :83b0
    :destination-directory gsi
    :non-platforms ("nt"))

(def-part gsi-msvc
    :version :83b0
    :source gsi
    :destination-directory gsi-msvc
    :platforms ("nt"))

(def-part gsi-INTC
    :version :83b0-INTC 
    :source gsi
    :destination-directory gsi-intc
    :platforms ("nt"))

(def-part gsi-itanium
    :source gsi
    :version :83b0-HP64
    :destination-directory gsi-itanium
    :platforms ("hpux"))

(def-part gservice
    :version :83b0
    :source gservice
    :source-filename "gservice.exe"
    :destination-directory g2
    :platforms ("nt"))
    

(def-part gda
    :version :51b0
    :destination-directory gda
    :indep t
    :shortcuts (gdacerl gdareact gdatank)
    )

(def-shortcut gdacerl
    :parent startserver-shortcut
    :application-display-name "Cereal Box Example"
    :subfolder-name "Examples"
    :subsubfolder-name "GDA"
    :parameters "-kb ..\\gda\\examples\\gdacerel.kb")

(def-shortcut gdareact
    :parent startserver-shortcut
    :application-display-name "Reactor Example"
    :subfolder-name "Examples"
    :subsubfolder-name "GDA"
    :parameters "-kb ..\\gda\\examples\\gdareact.kb")

(def-shortcut gdatank
    :parent startserver-shortcut
    :application-display-name "Tank Level Example"
    :subfolder-name "Examples"
    :subsubfolder-name "GDA"
    :parameters "-kb ..\\gda\\examples\\gdatank.kb")


;;;
;;;======= Begin G2i Modules =======
;;;
(def-component g2i-core-modules
  :print-name "G2 Developers' Utilities (G2i)"
  :parts (g2i-core-modules g2i-examples g2i-data g2i-g2agent))

(def-part g2i-core-modules
  :source g2i
  :version :23b0
  :indep t
  :source-subdirectory kbs
  :source-filename ("gens.kb" "gerr.kb" "grtl.kb" "grtl-icons.kb" "grtl-utils.kb" "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "resources-english.txt" "config.txt" "gevm.kb" "grlb.kb" "gdu.kb" "gduc.kb" "gdue.kb" "gdpm.kb" "geuc.kb" "gedp.kb" "grpe.kb" "gweb.kb" "brms.kb" "bpms.kb"
	"gdsm.kb" "gdsm-agent.kb" "gdsm-db.kb" "gdsm-jmail.kb" "gdsm-jms.kb" "gdsm-opc.kb" "gdsm-pi.kb" "gdsm-web.kb" "gdsm-snmp.kb")
  :make-not-read-only t
  :postinstall-code "replace_rootdir(\"g2i\"^\"kbs\", \"config.txt\");"
  :destination-directory "g2i/kbs")

(def-part g2i-data
  :source g2i
  :version :23b0
  :indep t
  :source-subdirectory data
  :destination-directory "g2i/data")

(def-part g2i-g2agent
    :source g2i
    :version :23b0
    :platforms ("nt")
    :source-subdirectory "G2Agent"
    :destination-directory "g2i/g2agent"
    :shortcuts (g2agent-shortcut)
    :postinstall-code "replace_rootdir(\"g2i\"^\"g2agent\"^\"intelnt\"^\"bin\", \"StartG2Agent.bat\");"
    :indep t)

(def-shortcut g2agent-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Agent Bridge"
    :application-directory "g2i\\g2agent\\intelnt\\bin"
    :target-name "StartG2Agent.bat")

(def-part g2i-examples
  :source g2i
  :version :23b0
  :indep t
  :source-subdirectory examples
  :source-filename ("gqsdemo.kb" "gevm-demo.kb" "gdu-demo.kb" "g2i-ui-demo.kb"
		    "g2i-ui-demo-resource-english.txt" "g2i-ui-demo.html" "gdpm-demo.kb"
		    "gedp-demo.kb" "grpe-demo.kb" "brms-demo.kb" "bpms-demo.kb" "gdsm-demo.kb")
  :shortcuts (g2i-gqsdemo-shortcut g2i-gevm-demo-shortcut g2i-gdu-demo-shortcut g2i-ui-demo-shortcut g2i-gedp-demo-shortcut g2i-gdpm-demo-shortcut g2i-brms-demo-shortcut g2i-bpms-demo-shortcut g2i-grpe-demo-shortcut g2i-gdsm-demo-shortcut)
  :destination-directory "g2i/examples")

(def-shortcut g2i-gqsdemo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Queue System (GQS) Example"
    :parameters "-kb ..\\g2i\\examples\\gqsdemo.kb")

(def-shortcut g2i-gevm-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Event Manager (GEVM) Example"
    :parameters "-kb ..\\g2i\\examples\\gevm-demo.kb")

(def-shortcut g2i-gdu-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Dialog Utility (GDU) Example"
    :parameters "-kb ..\\g2i\\examples\\gdu-demo.kb")

(def-shortcut g2i-ui-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "User Interface Demo"
    :parameters "-kb ..\\g2i\\examples\\g2i-ui-demo.kb")

(def-shortcut g2i-gedp-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Event and Data Processing (GEDP) Example"
    :parameters "-kb ..\\g2i\\examples\\gedp-demo.kb")

(def-shortcut g2i-gdpm-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Data Point Manager (GDPM) Example"
    :parameters "-kb ..\\g2i\\examples\\gdpm-demo.kb")

(def-shortcut g2i-grpe-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Reporting Engine (GRPE) Example"
    :parameters "-kb ..\\g2i\\examples\\grpe-demo.kb")

(def-shortcut g2i-brms-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "Business Rules Management System (BRMS) Example"
    :parameters "-kb ..\\g2i\\examples\\brms-demo.kb")

(def-shortcut g2i-bpms-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "Business Process Management System (BPMS) Example"
    :parameters "-kb ..\\g2i\\examples\\bpms-demo.kb")

(def-shortcut g2i-gdsm-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Data Source Manager (GDSM) Example"
    :parameters "-kb ..\\g2i\\examples\\gdsm-demo.kb")

;;;
;;;======= End G2i Modules =======
;;;

;;;
;;;======= Begin Socket Manager =======
;;;
(def-component socket-manager
    :print-name "Socket Manager"
    :parts (socket-manager-intel socket-manager-unix socket-manager-doc socket-manager-kbs jre-most basic-jvl-parts)
    :optional true
    :include-in-contents (socket-manager-unix socket-manager-intel))

(def-part socket-manager-intel
    :source sockman
    :version :42b0
    :platforms ("nt")
    :destination-directory "sockman"
    :postinstall-code "replace_rootdir(\"sockman\"^\"bin\", \"SocketManager.bat\");"
    :shortcuts (sockman-shortcut sockman-demo-shortcut))

(def-part socket-manager-unix
    :source sockman
    :version :42b0
    :non-platforms ("nt")
    :postinstall-code "replace_rootdir(\"sockman\"^\"bin\", \"socketmanager\");"
    :destination-directory "sockman")

(def-part socket-manager-kbs
    :source sockman
    :version :42b0
    :source-subdirectory kbs
    :destination-directory "sockman/kbs"
    :make-not-read-only t
    :indep "nt")

(def-part socket-manager-doc
    :source sockmandoc
    :version :41r2
    :source-subdirectory "sockman"
    :indep t
    :platforms ("nt" "sparcsol")
    :destination-directory "doc/bridges/sockman"
    :shortcuts (sockman-doc-shortcut sockman-doc-shortcut-html))

(def-shortcut sockman-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "Socket Manager Bridge"
    :application-directory "sockman\\bin"
    :target-name "SocketManager.bat"
)

(def-shortcut sockman-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "Socket Manager"
    :application-display-name "Socket Manager Example"
    :parameters "-kb ..\\sockman\\examples\\gsockdemo.kb"
)

(def-shortcut sockman-doc-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 Java Socket Manager User's Guide"
    :application-directory "doc/bridges/sockman"
    :target-name "g2javasocketmanager.pdf")

(def-shortcut sockman-doc-shortcut-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 Java Socket Manager User's Guide"
    :application-directory "doc/bridges/sockman/html"
    :target-name "titlepag.htm")


;;;
;;;======= End Socket Manager =======
;;;
;;;======= Begin JMail =======
;;;
(def-component jmail-component
  :print-name "JMail"
  :parts (jmail-intel jmail-unix jmail-doc jre-most jre-aix basic-jvl-parts)
  :include-in-contents (jmail-intel jmail-unix))

(def-part jmail-intel
  :source jmail
  :version :23b0
  :platforms ("nt")
  :destination-directory jmail
  :postinstall-code "replace_rootdir(\"jmail\"^\"bin\", \"StartJMailBridge.bat\");"
  :shortcuts (jmail-shortcut jmail-demo-shortcut))


(def-part jmail-unix
  :source jmail
  :version :23b0
  :non-platforms ("nt")
  :destination-directory jmail
  :postinstall-code "replace_rootdir(\"jmail\"^\"bin\", \"startjmailbridge\");")

(def-part jmailkbs
  :source jmail
  :version :23b0
  :source-subdirectory kbs
  :destination-directory jmail/kbs
  :indep "nt")  

(def-part jmail-doc
  :source jmaildoc
  :source-subdirectory jmail
  :version :22r0-HL13
  :indep t
  :destination-directory "doc/bridges/jmail"
  :shortcuts (jmail-doc-shortcut jmail-doc-shortcut-html))

(def-shortcut jmail-doc-shortcut
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JMail User's Guide"
  :application-directory "doc/bridges/jmail"
  :target-name "g2jmailbridge.pdf")

(def-shortcut jmail-doc-shortcut-html
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation (HTML)"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JMail User's Guide"
  :application-directory "doc/bridges/jmail/html"
  :target-name "titlepag.htm")

(def-shortcut jmail-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "JMail Bridge"
    :application-directory "jmail\\bin"
    :target-name "StartJMailBridge.bat")

(def-shortcut jmail-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "JMail"
    :application-display-name "JMail Tutorial"
    :parameters "-kb ..\\jmail\\examples\\jmail-demo.kb")

;;;
;;;======= End JMail =======
;;;

;;; Begin HLA

(def-component hla-bridge
  :print-name "G2 HLA"
  :parts (hla)
  :optional true
  :platforms ("nt"))


(def-part hla
    :source hla
    :version 20b0
    :destination-directory hla
    :postinstall-code "replace_rootdir(\"hla\"^\"bin\", \"StartG2HLA.bat\");replace_rootdir(\"hla\"^\"examples\"^\"G2Demo_Federate\", \"StartG2Demo.bat\");replace_rootdir(\"hla\"^\"examples\"^\"G2HelloWorld_Federate\", \"StartG2HelloWorld.bat\");"
    :shortcuts (start-g2hla-exe hla-demo hla-helloworld start-g2hla-kb))

(def-shortcut start-g2hla-exe
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Bridges"
  :application-display-name "G2 HLA Bridge"
  :application-directory "hla\\bin"
  :target-name "StartG2HLA.bat")


(def-shortcut start-g2hla-kb
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "G2 HLA"
    :application-display-name "G2 HLA Demo KB"
    :parameters "-kb ..\\hla\\examples\\ghla-demo.kb")

(def-shortcut hla-demo
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Examples"
  :subsubfolder-name "G2 HLA"
  :application-display-name "G2 HLA Demo"
  :application-directory "hla\\examples\\G2Demo_Federate"
  :target-name "StartG2Demo.bat")

(def-shortcut hla-helloworld
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Examples"
  :subsubfolder-name "G2 HLA"
  :application-display-name "G2 HLA HelloWorld"
  :application-directory "hla\\examples\\G2HelloWorld_Federate"
  :target-name "StartG2HelloWorld.bat")



;;;
;;;======= Begin JMS =======
;;;
(def-component jms-component
  :print-name "JMS"
  :parts (jms-intel jms-linux jms-hpux jms-g2i-modules jms-doc jre-most basic-jvl-parts)
  :optional true
  :include-in-contents (jms-intel jms-linux jms-hpux))

(def-part jms-doc
  :source jmsdoc
  :version :22r0
  :source-subdirectory jms
  :platforms ("nt" "hpux" "linux")
  :indep t
  :destination-directory "doc/bridges/jms"
  :shortcuts (jms-doc-shortcut jms-doc-shortcut-html)) 

(def-shortcut jms-doc-shortcut
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JMSLink User's Guide"
  :application-directory "doc/bridges/jms"
  :target-name "g2jmslink.pdf")

(def-shortcut jms-doc-shortcut-html
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation (HTML)"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JMSLink User's Guide"
  :application-directory "doc/bridges/jms/html"
  :target-name "titlepag.htm")

(def-part jms-intel
  :source jms
  :version :23b0
  :platforms ("nt")
  :destination-directory jms
  :postinstall-code "replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-j2ee.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-jboss.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-FioranoMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-WebSphereMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-SonicMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-OpenJMS.bat\");"
  :shortcuts (jms-j2ee-shortcut jms-jboss-shortcut jms-FioranoMQ-shortcut jms-WebSphereMQ-shortcut jms-openjms-shortcut jms-demo-shortcut))

(def-part jms-linux
  :source jms
  :version :23b0
  :platforms ("linux")
  :destination-directory jms
  :postinstall-code "replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-j2ee\");replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-jboss\");replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-openjms\");")

(def-part jms-hpux
  :source jms
  :version :23b0
  :platforms ("hpux")
  :destination-directory jms
  :postinstall-code "replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-jboss\");replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-openjms\");")

(def-part jmskbs
  :source jms
  :version :23b0
  :source-subdirectory kbs
  :destination-directory jms/kbs
  :indep "nt")  

(def-shortcut jms-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "JMS"
    :application-display-name "JMS Tutorial"
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

(def-shortcut jms-openjms-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS OpenJMS Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-OpenJMS.bat")

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
  :version :23b0
  :destination-directory "g2i/kbs"
  :source-subdirectory kbs
  :source-filename ("grtl.kb" "gerr.kb")
  :make-not-read-only t
  :indep t)
;;;
;;;======= End JMS =======
;;;
;;;
;;;======= Begin JsnmpBridge =======
;;;
(def-component jsnmp-bridge
  :print-name "Java SNMP Bridge"
  :parts (jsnmp-intel jsnmp-unix jre-most basic-jvl-parts)
  :optional true
  :include-in-contents (jsnmp-intel jsnmp-unix))

(def-part jsnmp-intel
    :source g2snmpgn
    :version :40r0-JC07
    :platforms ("nt")
    :destination-directory jsnmp
    :postinstall-code "replace_rootdir(\"jsnmp\"^\"bin\", \"StartJsnmpBridge.bat\");"
    :shortcuts (jsnmp-shortcut))

(def-part jsnmp-unix
  :source g2snmpgn
  :version :40r0-JC07
  :platforms ("sparcsol")
  :destination-directory jsnmp
  :postinstall-code "replace_rootdir(\"jsnmp\"^\"bin\", \"startjsnmpbridge.sh\");")

(def-shortcut jsnmp-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "Java SNMP Bridge"
    :application-directory "jsnmp\\bin"
    :target-name "StartJsnmpBridge.bat")
;;;
;;;======= End JsnmpBridge =======
;;;


(def-part gw
  :version :83b0
  :source gw
  :destination-directory gw)

(def-part gwkbs
  :version :83b0
  :source gw
  :source-subdirectory kbs
  :source-filename ("gwex2.kb" "gwex1.kb" "gwlow.kb")
  :destination-directory gw/kbs)

(def-part run-gw-template-batfile
    :platforms ("nt") 
    :version :83b0
    :source gw
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


(def-part jvl-unix
  :version :83b0
  :source jvl
  :destination-directory javalink
  :postinstall-code "replace_rootdir(\"javalink\"^\"bin\", \"set-envvars\");"
  :platforms ("sparcsol" "hpux" "aix" "linux" "alphaosf"))

(def-part jvl-intelnt
  :version :83b0
  :source jvl
  :destination-directory javalink
  :postinstall-code "replace_rootdir(\"javalink\"^\"bin\", \"envvars.bat\");"
  :platforms ("nt")
  :shortcuts (jvl-interface-downloader
	      jvl-install-properties
	      jvl-bean-builder
	      jvl-example-readme
	      jvl-readme))

;;; The part jvl-com-gensym-properties-intelnt sets up a template
;;; .com.gensym.properties file in the classes, and also arranges through
;;; postinstall code to have that file overwritten with substitutions from the
;;; template file that normally lives in the bin directory.  Having the template
;;; file preexist just ensures that uninstalling will remove that file, so it
;;; can clean up everything.  (I had to copy the current 11r0
;;; .com.gensym.properties to
;;; /development/installers/release-files/.com.gensym.properties to make this
;;; work. --mhd, 12/11/00)

;;; yduJ, 9/27/05: Now specifying from eship; rather than using a potentially
;;; out of date version in release-files.

(def-part jvl-com-gensym-properties-intelnt
  :version :83b0
  :source jvl
  :source-subdirectory "bin"
  :source-filename ".com.gensym.properties"
  :destination-directory "javalink/classes"
  :platforms ("nt")
  :postinstall-code
  "FixupPropertiesFile(TARGETDIR^\"javalink\"^\"bin\", \".com.gensym.properties\", TARGETDIR^\"javalink\", \"classes\", \".com.gensym.properties\");")

(def-part jvlkbs
  :source jvl
  :version :83b0
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

(def-shortcut jvl-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 JavaLink"
    :application-display-name "Readme for G2 JavaLink"
    :application-directory "javalink"
    :target-name "readme-javalink.html")




(def-part jvl-javadoc
    :version :83b0
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
  :version :83b0
  :destination-directory corbalink
  :non-platforms ("alphaosf"))

;; ActiveXLink Parts:

(def-part axl
    :version :83b0
    :source axl
    :destination-directory activexlink
    :platforms ("nt")
    :shortcuts (axldemo axlhtmldemo axlvbdemo axlvbdemoproj axlc++demo
			axlc++proj axlexceldemo axlvbnetdemo axlvbnetproj
			))
(def-part axl-g2com-dll
    :version :83b0
    :source axl
    :source-subdirectory bin
    :source-filename "G2Com.dll"
    :register true			; Active X Control
    :destination-directory activexlink/bin
    :platforms ("nt"))

(def-shortcut axldemo
    :parent startserver-shortcut
    :application-display-name "ActiveX Link Demo KB"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :parameters "-kb kbs\\demos\\axldemo.kb")

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

(def-shortcut axlvbnetdemo
    :folder-name g2-shortcut-folder-name
    :application-display-name "VB .NET Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "activexlink\\demos\\vbnetdemo\\bin"
    :target-name "VBNetDemo.exe")

(def-shortcut axlvbnetproj
    :folder-name g2-shortcut-folder-name
    :application-display-name "VB .NET Demo Project"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "activexlink\\demos\\vbnetdemo"
    :target-name "VBNetDemo.sln")

(def-shortcut axlc++demo
    :folder-name g2-shortcut-folder-name
    :application-display-name "C++ Demo"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "activexlink\\demos\\vcppdemo"
    :target-name "VCppDemo.exe")

(def-shortcut axlc++proj
    :folder-name g2-shortcut-folder-name
    :application-display-name "C++ Demo Project"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "activexlink\\demos\\vcppdemo"
    :target-name "VCppDemo.dsw")

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
    :version 82r0
    :destination-directory doc/utilities/gdi
    :indep t
    :source-filename ("gdi.pdf")
    :source-subdirectory gdi)

(def-part g2utldoc-gms-pdf
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/gms
    :indep t
    :source-filename ("gms.pdf")
    :source-subdirectory gms)

(def-part g2utldoc-goldui-pdf
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/goldui
    :indep t
    :source-filename ("goldui.pdf")
    :source-subdirectory goldui)

(def-part g2utldoc-guideuserguide-pdf
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/guideuserguide
    :indep t
    :source-filename ("guideuserguide.pdf")
    :source-subdirectory guideuserguide)

(def-part g2utldoc-gdd-pdf
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/gdd
    :indep t
    :source-filename ("gdd.pdf")
    :source-subdirectory gdd)

(def-part g2utldoc-gfr-pdf
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/gfr
    :indep t
    :source-filename ("gfr.pdf")
    :source-subdirectory gfr)

(def-part g2utldoc-golddev-pdf
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/golddev
    :indep t
    :source-filename ("golddev.pdf")
    :source-subdirectory golddev)

(def-part g2utldoc-guideprocref-pdf
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/guideprocref
    :indep t
    :source-filename ("guideprocref.pdf")
    :source-subdirectory guideprocref)

(def-part g2utldoc-gxl-pdf
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/gxl
    :indep t
    :source-filename ("gxl.pdf")
    :source-subdirectory gxl)

(def-part g2utldoc-gdi-html
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/gdi/html
    :indep t
    :source-subdirectory gdi/html)

(def-part g2utldoc-gms-html
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/gms/html
    :indep t
    :source-subdirectory gms/html)

(def-part g2utldoc-goldui-html
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/goldui/html
    :indep t
    :source-subdirectory goldui/html)

(def-part g2utldoc-guideuserguide-html
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/guideuserguide/html
    :indep t
    :source-subdirectory guideuserguide/html)

(def-part g2utldoc-gdd-html
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/gdd/html
    :indep t
    :source-subdirectory gdd/html)

(def-part g2utldoc-gfr-html
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/gfr/html
    :indep t
    :source-subdirectory gfr/html)

(def-part g2utldoc-golddev-html
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/golddev/html
    :indep t
    :source-subdirectory golddev/html)

(def-part g2utldoc-guideprocref-html
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/guideprocref/html
    :indep t
    :source-subdirectory guideprocref/html)

(def-part g2utldoc-gxl-html
    :source g2utldoc
    :version 82r0
    :destination-directory doc/utilities/gxl/html
    :indep t
    :source-subdirectory gxl/html)


(def-part g2idoc-gdsm-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gdsm
    :indep t
    :source-subdirectory gdsm
    :source-filename ("gdsm.pdf"))

(def-part g2idoc-gdsm-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gdsm/html
    :indep t
    :source-subdirectory gdsm/html)

(def-part g2idoc-gdu-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gdu
    :indep t
    :source-subdirectory gdu
    :source-filename ("gdu.pdf"))

(def-part g2idoc-gdu-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gdu/html
    :indep t
    :source-subdirectory gdu/html)

(def-part g2idoc-gerr-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gerr
    :indep t
    :source-subdirectory gerr
    :source-filename ("gerr.pdf"))

(def-part g2idoc-gerr-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gerr/html
    :indep t
    :source-subdirectory gerr/html)

(def-part g2idoc-gevm-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gevm
    :indep t
    :source-subdirectory gevm
    :source-filename ("gevm.pdf"))

(def-part g2idoc-gevm-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gevm/html
    :indep t
    :source-subdirectory gevm/html)

(def-part g2idoc-grlb-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/grlb
    :indep t
    :source-subdirectory grlb
    :source-filename ("grlb.pdf"))

(def-part g2idoc-grlb-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/grlb/html
    :indep t
    :source-subdirectory grlb/html)

(def-part g2idoc-grtl-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/grtl
    :indep t
    :source-subdirectory grtl
    :source-filename ("grtl.pdf"))

(def-part g2idoc-grtl-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/grtl/html
    :indep t
    :source-subdirectory grtl/html)

(def-part g2idoc-gdpm-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gdpm
    :indep t
    :source-subdirectory gdpm
    :source-filename ("gdpm.pdf"))

(def-part g2idoc-gdpm-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gdpm/html
    :indep t
    :source-subdirectory gdpm/html)

(def-part g2idoc-grpe-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/grpe
    :indep t
    :source-subdirectory grpe
    :source-filename ("grpe.pdf"))

(def-part g2idoc-grpe-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/grpe/html
    :indep t
    :source-subdirectory grpe/html)

(def-part g2idoc-brms-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/brms
    :indep t
    :source-subdirectory brms
    :source-filename ("brms.pdf"))

(def-part g2idoc-brms-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/brms/html
    :indep t
    :source-subdirectory brms/html)

(def-part g2idoc-bpms-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/bpms
    :indep t
    :source-subdirectory bpms
    :source-filename ("bpms.pdf"))

(def-part g2idoc-bpms-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/bpms/html
    :indep t
    :source-subdirectory bpms/html)

(def-part g2idoc-gedp-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gedp
    :indep t
    :source-subdirectory gedp
    :source-filename ("gedp.pdf"))

(def-part g2idoc-gedp-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gedp/html
    :indep t
    :source-subdirectory gedp/html)

(def-part g2idoc-gweb-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gweb
    :indep t
    :source-subdirectory gweb
    :source-filename ("gweb.pdf"))

(def-part g2idoc-gweb-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/gweb/html
    :indep t
    :source-subdirectory gweb/html)

(def-part g2idoc-geuc-pdf
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/geuc
    :indep t
    :source-subdirectory geuc
    :source-filename ("geuc.pdf"))

(def-part g2idoc-geuc-html
    :source g2idoc
    :version :23b0
    :destination-directory doc/g2i/geuc/html
    :indep t
    :source-subdirectory geuc/html)

(def-part protoolsdoc
    :version :82r0
    :destination-directory doc/utilities/g2protools
    :source-subdirectory g2protools
    :indep t :source-filename ("g2protools.pdf"))

(def-part protoolsdoc-html
    :source protoolsdoc
    :version :82r0
    :destination-directory doc/utilities/g2protools/html
    :indep t :source-subdirectory g2protools/html)

(def-part gdadoc-api-pdf
    :source gdadoc
    :version :44r0
    :destination-directory doc/gda/gdaapi
    :source-filename ("gdaapi.pdf")
    :indep t :source-subdirectory gda/gdaapi)

(def-part gdadoc-ug-pdf
    :source gdadoc
    :version :44r0
    :destination-directory doc/gda/gdaugrm
    :source-filename ("gdarefman.pdf" "gdaug.pdf")
    :indep t :source-subdirectory gda/gdaugrm)

(def-part gdadoc-api-html
    :source gdadoc
    :version :44r0
    :destination-directory doc/gda/gdaapi/html
    :indep t :source-subdirectory gda/gdaapi/html)

(def-part gdadoc-ug-html
    :source gdadoc
    :version :44r0
    :destination-directory doc/gda/gdaugrm/html
    :indep t :source-subdirectory gda/gdaugrm/html)

(def-part snmpdoc-pdf
    :source snmpdoc
    :version :40r0
    :source-subdirectory snmp
    :destination-directory doc/bridges/snmp
    :source-filename ("g2snmp.pdf")    
    :shortcuts (snmpdoc-pdf)
    :indep t)

(def-part snmpdoc-html
    :source snmpdoc
    :version :40r0
    :destination-directory doc/bridges/snmp/html
    :source-subdirectory snmp/html
    :shortcuts (snmpdoc-html)
    :indep t)

(def-part weblinkdoc
    :version 82r0
    :destination-directory doc/bridges/weblink
    :indep t
    :source-subdirectory weblink
    :source-filename ("g2weblink.pdf")
    :shortcuts (g2-weblink-users-guide g2-weblink-users-guide-html))

(def-part weblinkdoc-html
    :source weblinkdoc
    :version 82r0
    :destination-directory doc/bridges/weblink/html
    :indep t :source-subdirectory weblink/html)

(def-part g2classicrn
    :version :83b0
;    :source-subdirectory g2relnotes
    :source-filename "g2relnotes.pdf"
    :indep t
    :destination-directory doc)

(def-part g2classicrn-html
    :source g2classicrn
    :version :83b0
    :source-subdirectory g2relnotes/html
    :destination-directory doc/g2/g2relnotes/html
    :indep t
    :destination-directory doc)

;; reference manual

(def-part g2doc-g2refman-pdf
    :source g2doc
    :version :82r0-ID06
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
		 g2-sysproc-refcard
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
		 g2idoc-bpms
		 g2idoc-brms
		 g2idoc-gdsm
		 g2idoc-gdu
		 g2idoc-gerr
		 g2idoc-gevm
		 g2idoc-grlb
		 g2idoc-grtl
		 g2idoc-gdpm
		 g2idoc-grpe
		 g2idoc-gedp
		 g2idoc-geuc
		 g2idoc-gweb
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
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2tutorials
    :source-subdirectory g2tutorials
    :indep t
    :source-filename ("g2tutorials.pdf"))

(def-part g2doc-g2gateway-pdf
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2gateway
    :source-subdirectory g2gateway
    :indep t
    :source-filename ("g2gateway.pdf"))

(def-part g2doc-g2classref-pdf
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2classref
    :source-subdirectory g2classref
    :indep t
    :source-filename ("g2classref.pdf"))

(def-part g2doc-telewindows-pdf
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/telewindows
    :source-subdirectory telewindows
    :indep t
    :source-filename ("telewindows.pdf"))

(def-part g2doc-g2sysprocs-pdf
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2sysprocs
    :source-subdirectory g2sysprocs
    :indep t
    :source-filename ("g2sysprocs.pdf"))

(def-part g2doc-g2langrefcard-pdf
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2langrefcard
    :source-subdirectory g2langrefcard
    :indep t
    :source-filename ("g2langrefcard.pdf"))

(def-part g2doc-g2sysprocrefcard-pdf
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2sysprocsrefcard
    :source-subdirectory g2sysprocsrefcard
    :indep t
    :source-filename ("g2sysprocsrefcard.pdf"))

(def-part g2doc-g2devguide-pdf
    :source g2doc
    :version :82r0-ID06
    :source-subdirectory g2devguide
    :source g2doc
    :destination-directory doc/g2/g2devguide
    :indep t
    :source-filename ("g2devguide.pdf"))



(def-part g2doc-g2tutorials-html
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2tutorials/html
    :source-subdirectory g2tutorials/html
    :indep t)

(def-part g2doc-g2refman-html
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2refman/html
    :source-subdirectory g2refman/html
    :indep t
    :shortcuts (
		 ;g2-release-notes-html
		 g2-reference-manual-html
		 g2-reference-card-html
		 g2-sysproc-refcard-html
		 ;;g2-release-notes-update;;not included in 6.0b1
		 g2-system-procedures-reference-manual-html
		 g2-tutorial-html
		 g2-class-reference-manual-html
		 g2-developers-guide-html	    ;;not included in 6.0b1
		 ;; G2 Utilities
		 g2-dynamic-displays-users-guide-html
		 g2-developers-interface-users-guide-html
		 g2-foundation-resources-users-guide-html
		 g2-menu-system-users-guide-html
		 g2-online-documentation-developers-guide-html
		 g2-online-documentation-users-guide-html
		 g2-guide-uil-procedures-reference-manual-html
		 g2-guide-users-guide-html
		 g2-xl-spreadsheet-users-guide-html
		 ;; G2i
		 g2idoc-bpms-html
		 g2idoc-brms-html
		 g2idoc-gdsm-html
		 g2idoc-gdu-html
		 g2idoc-gerr-html
		 g2idoc-gevm-html
		 g2idoc-grlb-html
		 g2idoc-grtl-html
		 g2idoc-gdpm-html
		 g2idoc-grpe-html
		 g2idoc-gedp-html
		 g2idoc-geuc-html
		 g2idoc-gweb-html
		 ;; GDA:
		 gda-users-guide-html
		 gda-reference-manual-html
		 gda-api-reference-manual-html
		 ;; Protools
		 g2-protools-users-guide-html
		 ;; GSI
		 gsi-bridge-developers-guide-html
		 ;; Bridges:
		 g2-database-bridge-guide-html
		 g2-opclink-users-guide-html
		 g2-corba-link-users-guide-html
		 g2-odbc-bridge-release-notes-html
		 g2-oracle-bridge-release-notes-html
		 g2-sybase-bridge-release-notes-html
		 g2-pi-bridge-users-guide-html
		 ;; TW
		 telewindows-users-guide-html
		 )
    )

(def-part g2doc-g2gateway-html
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2gateway/html
    :source-subdirectory g2gateway/html
    :indep t)

(def-part g2doc-g2classref-html
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2classref/html
    :source-subdirectory g2classref/html
    :indep t)

(def-part g2doc-telewindows-html
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/telewindows/html
    :source-subdirectory telewindows/html
    :indep t)

(def-part g2doc-g2sysprocs-html
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2sysprocs/html
    :source-subdirectory g2sysprocs/html
    :indep t)

(def-part g2doc-g2langrefcard-html
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2langrefcard/html
    :source-subdirectory g2langrefcard/html
    :indep t)

(def-part g2doc-g2sysprocsrefcard-html
    :source g2doc
    :version :82r0-ID06
    :source g2doc
    :destination-directory doc/g2/g2sysprocsrefcard/html
    :source-subdirectory g2sysprocsrefcard/html
    :indep t)

(def-part g2doc-g2devguide-html
    :source g2doc
    :version :82r0-ID06
    :source-subdirectory g2devguide/html
    :source g2doc
    :destination-directory doc/g2/g2devguide/html
    :indep t)

 
(def-part doc-chm
    :version :83b0
    :source g2winhelp
    :source-filename ("ActiveXLinkHelp.chm"
		       "BPMSHelp.chm"
		       "BRMSHelp.chm"
		       "DownloadInterfacesHelp.chm"
		       "G2-CORBALinkHelp.chm"
		       "G2-DatabaseBridgeHelp.chm"
		       "G2-JMSBridgeHelp.chm"
		       "G2-JMailBridgeHelp.chm"
		       "G2-JSockManHelp.chm"
		       "G2-ODBCBridgeHelp.chm"
		       "G2-OPCLinkHelp.chm"
		       "G2-OracleBridgeHelp.chm"
		       "G2-PIBridgeHelp.chm"
		       "G2-SNMPBridgeHelp.chm"
		       "G2-SybaseBridgeHelp.chm"
		       "G2-WebLinkHelp.chm"
		       "G2BeanBuilderHelp.chm"
		       "G2Bridges.html"
		       "G2BundleReleaseNotesHelp.chm"
		       "G2ClassReferenceHelp.chm"
		       "G2Core.html"
		       "G2DevUtilities.html"
		       "G2DevelopersGuideHelp.chm"
		       "G2GatewayHelp.chm"
		       "G2JavaLink.html"
		       "G2JavaLinkHelp.chm"
		       "G2LanguageReferenceHelp.chm"
		       "G2ProToolsHelp.chm"
		       "G2ReferenceManualHelp.chm"
		       "G2SystemProceduresHelp.chm"
		       "G2SystemProceduresReferenceCardHelp.chm"
		       "G2Utilities.html"
		       "GDDHelp.chm"
		       "GDIHelp.chm"
		       "GDPMHelp.chm"
		       "GDSMHelp.chm"
		       "GDUHelp.chm"
		       "GEDPHelp.chm"
		       "GERRHelp.chm"
		       "GEUCHelp.chm"
		       "GEVMHelp.chm"
		       "GFRHelp.chm"
		       "GMSHelp.chm"
		       "GOLDDevelopersGuideHelp.chm"
		       "GOLDHelp.chm"
		       "GRLBHelp.chm"
		       "GRPEHelp.chm"
		       "GRTLHelp.chm"
		       "GUIDEHelp.chm"
		       "GUIDEUILHelp.chm"
		       "GWEBHelp.chm"
		       "GXLHelp.chm"
		       "GettingStarted.html"
		       "GettingStartedWithG2Help.chm"
		       "Master.chm"
		       "Master.html"
		       "Master2.html"
		       "Master3.html"
		       "TelewindowsHelp.chm"
		       )
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
    :version :82r0
    :destination-directory doc/javalink/docs/guides/g2javalink
    :indep t
    :source-filename ("g2javalink.pdf")
    :source-subdirectory docs/guides/g2javalink
    :shortcuts (
		 ;; Javalink
		 g2-download-interfaces-guide g2-download-interfaces-guide-html
		 g2-beanbuilder-guide g2-beanbuilder-guide-html
		 g2-javalink-guide g2-javalink-guide-html
		 )
    )

(def-part jvldoc-di-pdf
    :source jvldoc
    :version :82r0
    :destination-directory doc/javalink/docs/guides/g2downloadinterfaces
    :indep t
    :source-filename ("g2downloadinterfaces.pdf")
    :source-subdirectory docs/guides/g2downloadinterfaces
    )

(def-part jvldoc-bb-pdf
    :source jvldoc
    :version :82r0
    :destination-directory doc/javalink/docs/guides/g2beanbuilder
    :indep t
    :source-filename ("g2beanbuilder.pdf")
    :source-subdirectory docs/guides/g2beanbuilder
    )

(def-part jvldoc-javalink-html
    :source jvldoc
    :version :82r0
    :destination-directory doc/javalink/docs/guides/g2javalink/html
    :indep t
    :source-subdirectory docs/guides/g2javalink/html
    )

(def-part jvldoc-di-html
    :source jvldoc
    :version :82r0
    :destination-directory doc/javalink/docs/guides/g2downloadinterfaces/html
    :indep t
    :source-subdirectory docs/guides/g2downloadinterfaces/html
    )

(def-part jvldoc-bb-html
    :source jvldoc
    :version :82r0
    :destination-directory doc/javalink/docs/guides/g2beanbuilder/html
    :indep t
    :source-subdirectory docs/guides/g2beanbuilder/html
    )

(def-part axldoc
    :version :82r0
    :destination-directory doc/bridges/activexlink
    :platforms ("nt")
    :indep t :source-filename "g2activexlink.pdf"
    :source-subdirectory activexlink
    :shortcuts (g2-activexlink-users-guide g2-activexlink-users-guide-html))
(def-part axldoc-html
    :source axldoc
    :version :82r0
    :destination-directory doc/bridges/activexlink/html
    :platforms ("nt")
    :indep t
    :source-subdirectory activexlink/html)

(def-part corbalinkdoc
    :version :82r0
    :destination-directory doc/bridges/corbalink
    :indep t
    :source-filename ("g2corbalink.pdf")
    :source-subdirectory corbalink)

(def-part corbalinkdoc-html
    :source corbalinkdoc
    :version :82r0
    :destination-directory doc/bridges/corbalink/html
    :indep t
    :source-subdirectory corbalink/html)
(def-part g2oradoc
    :version :82r0
    :destination-directory doc/bridges/oracle
    :indep t :source-filename ("g2oraclebridge.pdf")
    :source-subdirectory oracle)


(def-part g2oradoc-html
    :source g2oradoc
    :version :82r0
    :destination-directory doc/bridges/oracle/html
    :indep t
    :source-subdirectory oracle/html)
(def-part g2sybdoc
    :version :82r0
    :destination-directory doc/bridges/sybase
    :indep t
    :source-filename ("g2sybasebridge.pdf")
    :source-subdirectory sybase)
(def-part g2sybdoc-html
    :source g2sybdoc
    :version :82r0
    :destination-directory doc/bridges/sybase/html
    :indep t
    :source-subdirectory sybase/html)
(def-part opclinkdoc
    :version :30r2
    :destination-directory doc/bridges/opclink
    :indep t
    :source-filename ("g2opclink.pdf")
    :source-subdirectory opclink
    )
(def-part opclinkdoc-html
    :source opclinkdoc
    :version :30r2
    :destination-directory doc/bridges/opclink/html
    :indep t
    :source-subdirectory opclink/html)
(def-part g2odbcdoc
    :version :82r0
    :destination-directory doc/bridges/odbc
    :indep t
    :source-filename ("g2odbcbridge.pdf")
    :source-subdirectory odbc
    )
(def-part g2odbcdoc-html
    :source g2odbcdoc
    :version :82r0
    :destination-directory doc/bridges/odbc/html
    :indep t
    :source-subdirectory odbc/html)
(def-part g2pidoc
    :version :82r0
    :destination-directory doc/bridges/pi
    :source-subdirectory pi
    :indep t
    :source-filename ("g2pibridge.pdf")
    )
(def-part g2pidoc-html
    :source g2pidoc
    :version :82r0
    :destination-directory doc/bridges/pi/html
    :indep t
    :source-subdirectory pi/html)

(def-part g2dbdoc
    :version :82r0
    :destination-directory doc/bridges/db
    :source-subdirectory db
    :indep t :source-filename ("g2databasebridge.pdf"))

(def-part g2dbdoc-html :source g2dbdoc
    :version :82r0
    :destination-directory doc/bridges/db/html
    :indep t :source-subdirectory db/html)

(def-part protools
    :version :83b0
    :source protools
    :destination-directory protools/kbs
    :source-filename ("protools.kb" "ptroot.kb")
    :indep t)

(def-part profiler
    :version :83b0
    :source protools
    :source-filename ("profiler.kb" "profroot.kb")
    :destination-directory g2/kbs/utils
    :indep t)

(def-part profiler-demo
    :version :83b0
    :source protools
    :source-filename ("profile-demo.kb")
    :destination-directory g2/kbs/samples
    :indep t)

(def-gsi-bridge-ok-parts (:obfuscate :from-sandbox :version 8)
    gw)

(def-gsi-bridge-ok-parts (:obfuscate :from-sandbox :version 8)
    odbc)

(def-gsi-bridge-ok-parts (:obfuscate :from-sandbox :version 8)
    oracle)

(def-gsi-bridge-ok-parts (:obfuscate :from-sandbox :version 8 :non-platforms ("linux"))
    sybase)

(def-gsi-bridge-ok-parts (:obfuscate :from-sandbox :version 8)
    pi)

(def-gsi-bridge-ok-parts (:obfuscate :from-sandbox :version 8)
    opclink)

(def-part g2-readme
    :source g2pkgreadme
    :version :83b0
    :source-filename "readme-g2.html"
    :indep t 
    :shortcuts (g2-readme))

(def-shortcut g2-readme
    :folder-name g2-shortcut-folder-name
    :application-display-name "Readme for G2 Bundle"
    :application-directory ""
    :target-name "readme-g2.html")


(def-part opclink
    :platforms ("nt") 
    :version :83b0
    :destination-directory opclink
    :postinstall-code "replace_rootdir(\"opclink\", \"run-g2opc.bat\");"
    :shortcuts (opclink-shortcut))

(def-part opclinkkbs
    :source opclink
    :version :83b0
    :destination-directory "opclink/kbs"
    :source-subdirectory "kbs"
    :indep "nt")

(def-shortcut opclink-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 OPCLink Bridge"
    :application-directory "opclink"
    :target-name "run-g2opc.bat")

(def-part g2pi
    :version :83b0
    :destination-directory pi)

(def-part pikbs
    :source g2pi
    :version :83b0
    :source-subdirectory kbs
    :source-filename ("g2-pi.kb")
    :destination-directory pi/kbs
    :indep "nt")

(def-part run-g2-pi-template-batfile
    :platforms ("nt") 
    :version :83b0
    :source g2pi
    :source-subdirectory bin
    :source-filename "run-g2-pi.bat"
    :destination-directory pi/bin
    :postinstall-code "replace_rootdir(\"pi\"^\"bin\", \"run-g2-pi.bat\");"
    :shortcuts (pi-shortcut))

(def-shortcut pi-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 PI Bridge"
    :application-directory "pi\\bin"
    :target-name "run-g2-pi.bat")


(def-part Sybasebridge
    :version :83b0
    :source g2sybase
    :destination-directory sybase
    :non-platforms ("linux"))

(def-part sybasekbs
    :version :83b0
    :source g2sybase
    :source-subdirectory kbs
    :source-filename ("g2-database.kb")
    :destination-directory sybase/kbs
    :indep "nt")

(def-part run-g2-sybase11-template-batfile
    :platforms ("nt") 
    :source g2sybase
    :source-subdirectory bin
    :version :83b0
    :source-filename "run-g2-syb11.bat"
    :destination-directory sybase/bin
    :postinstall-code "replace_rootdir(\"sybase\"^\"bin\", \"run-g2-syb11.bat\");"
    :shortcuts (sybase11-shortcut))

(def-shortcut sybase11-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Sybase 11 Bridge"
    :application-directory "sybase\\bin"
    :target-name "run-g2-syb11.bat")

(def-part run-g2-sybase125-template-batfile
    :platforms ("nt") 
    :source g2sybase
    :source-subdirectory bin
    :version :83b0
    :source-filename "run-g2-syb125.bat"
    :destination-directory sybase/bin
    :postinstall-code "replace_rootdir(\"sybase\"^\"bin\", \"run-g2-syb125.bat\");"
    :shortcuts (sybase125-shortcut))

(def-shortcut sybase125-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Sybase 12.5 Bridge"
    :application-directory "sybase\\bin"
    :target-name "run-g2-syb125.bat")



(def-part ODBCbridge
    :version :83b0
    :source g2odbc
    :destination-directory odbc
    :platforms ("nt"))

(def-part run-g2-odbc-template-batfile
    :platforms ("nt") 
    :source g2odbc
    :source-subdirectory bin
    :version :83b0
    :source-filename "run-g2-odbc.bat"
    :destination-directory odbc/bin
    :postinstall-code "replace_rootdir(\"odbc\"^\"bin\", \"run-g2-odbc.bat\");"
    :shortcuts (odbc-shortcut))

(def-shortcut odbc-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 ODBC Bridge"
    :application-directory "odbc\\bin"
    :target-name "run-g2-odbc.bat")

(def-part odbckbs
    :version :83b0
    :source g2odbc
    :source-subdirectory kbs
    :source-filename ("g2-database.kb")
    :destination-directory odbc/kbs
    :indep "nt")


(def-part Oraclebridge
    :version :83b0
    :source g2oracle
    :destination-directory oracle)

(def-part oraclekbs
    :version :83b0
    :source g2oracle
    :source-subdirectory kbs
    :source-filename ("g2-database.kb")
    :destination-directory oracle/kbs)

(def-part run-g2-ora7-template-batfile
    :platforms ("nt") 
    :source g2oracle
    :source-subdirectory bin
    :version :83b0
    :source-filename "run-g2-ora7.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora7.bat\");"
    :shortcuts (ora7-shortcut))

(def-part run-g2-ora80-template-batfile
    :platforms ("nt") 
    :source g2oracle
    :source-subdirectory bin
    :version :83b0
    :source-filename "run-g2-ora80.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora80.bat\");"
    :shortcuts (ora80-shortcut))

(def-part run-g2-ora81-template-batfile
    :platforms ("nt") 
    :source g2oracle
    :source-subdirectory bin
    :version :83b0
    :source-filename "run-g2-ora81.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora81.bat\");"
    :shortcuts (ora81-shortcut))

(def-part run-g2-ora90-template-batfile
    :platforms ("nt") 
    :source g2oracle
    :source-subdirectory bin
    :version :83b0
    :source-filename "run-g2-ora90.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora90.bat\");"
    :shortcuts (ora90-shortcut))

(def-part run-g2-ora92-template-batfile
    :platforms ("nt") 
    :source g2oracle
    :source-subdirectory bin
    :version :83b0
    :source-filename "run-g2-ora92.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora92.bat\");"
    :shortcuts (ora92-shortcut))

(def-part run-g2-ora10-template-batfile
    :platforms ("nt") 
    :source g2oracle
    :source-subdirectory bin
    :version :83b0
    :source-filename "run-g2-ora10.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora10.bat\");"
    :shortcuts (ora10-shortcut))

(def-shortcut ora7-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 7 Bridge"
    :application-directory "oracle\\bin"
    :target-name "run-g2-ora7.bat")

(def-shortcut ora80-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 8.0 Bridge"
    :application-directory "oracle\\bin"
    :target-name "run-g2-ora80.bat")

(def-shortcut ora81-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 8.1 Bridge"
    :application-directory "oracle\\bin"
    :target-name "run-g2-ora81.bat")

(def-shortcut ora90-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 9.0 Bridge"
    :application-directory "oracle\\bin"
    :target-name "run-g2-ora90.bat")

(def-shortcut ora92-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 9.2 Bridge"
    :application-directory "oracle\\bin"
    :target-name "run-g2-ora92.bat")

(def-shortcut ora10-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 10 Bridge"
    :application-directory "oracle\\bin"
    :target-name "run-g2-ora10.bat")



;;;Unfortunately in the version on the java run-time environment that is
;;;available on aix and alphaosf are not the same as the version for most of the
;;;other platforms.  So we are forced to have separate parts for the JRE.  This
;;;means that any other components which wish to include jre separately (jmail,
;;;jms, sockman) need to know which version(s) they will require.
(def-component jre
    :print-name "Java Runtime Environment"
    :parts (jre-most jre-aix jre-alphaosf))

(def-part jre-most
    :version :14r2_03
    :source "jre"
    :platforms ("nt" "sparcsol" "hpux" "linux")
    :destination-directory "jre")

(def-part jre-aix
    :version :14r1
    :source "jre"
    :platforms ("aix")
    :destination-directory "jre")

(def-part jre-alphaosf
    :version :|14r2-4p2|
    :source "jre"
    :platforms ("alphaosf")
    :destination-directory "jre")

;;;  Now comes the MEGABUNDLE parts.

;;; rethink:

(def-component rethink
  :print-name "G2 ReThink"
  :parts ( rethink-client-binaries rethink-readme rethink-online-server-binaries rethink-online-kbs images rethink-online-examples log-part rethink-resources  rethink-reports rethink-databases rethink-documentation )
  :optional true
  :platforms ("nt")
  :include-in-contents (rethink-online-kbs))

(def-part rethink-client-binaries
    :version :51b0
;;;    :source-ship-type :internal
    :source-filename ("ReThink.ico")
    :destination-directory "rethink/bin"
    :source "rethink"
    :indep t
    :source-subdirectory "bin")

(def-part log-part
  :version :51b0
;;;  :source-ship-type :internal
  :destination-directory "rethink/logs"
  :source-subdirectory "logs"
  :source "rethink"
  :indep t
)

(def-part archives-part
  :version :51b0
;;;  :source-ship-type :internal
  :destination-directory "rethink/archives"
  :source-subdirectory "archives"
  :source "rethink"
  :indep t
)
(def-part rethink-resources
  :version :51b0
;;;  :source-ship-type :internal
  :destination-directory "rethink/resources"
  :source-subdirectory "resources"
  :source "rethink"
  :indep t
)

(def-part rethink-online-kbs
    :version :51b0
;;;    :source-ship-type :internal
    :destination-directory "rethink/kbs"
    :source-subdirectory "kbs"
    :source-filename ("rethink.kb" "rethink-online.kb" "rethink-online-core.kb" "rethink-core.kb" "bpr.kb" "bprui.kb" "customiz.kb" "methods.kb" "menus.kb" "methods-online.kb") 
    :source "rethink"
    :indep t
;;;    :shortcuts (rethink-online-server-shortcut)
)

(def-part rethink-online-examples
  :version :51b0
;;;  :source-ship-type :internal
  :destination-directory "rethink/examples"
  :source-subdirectory "examples"
  :source-filename ("aero.kb" "chapter3.kb" "orderful.kb" "rethink-40-doc-examples.kb" "rethink-40-online-examples.kb")
  :source "rethink"
  :indep t
  :shortcuts (aero-tutorial orderful-tutorial chapter3-tutorial rethink-40-tutorial rethink-40-online-tutorial)
)

(def-shortcut rethink-40-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "ReThink 4.0 Examples"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\rethink-40-doc-examples.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)


(def-shortcut aero-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "Aero Model"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\aero.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut chapter3-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "Chapter3 Model"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\chapter3.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut orderful-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "Orderful Model"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\orderful.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut rethink-40-online-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "ReThink 4.0 Online Example"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\examples\\rethink-40-online-examples.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)

(def-part images
    :version :51b0
;;;    :source-ship-type :internal
    :destination-directory "rethink/kbs/images"
    :source-subdirectory "kbs/images"
    :source "rethink"
    :indep t
)

(def-part rethink-online-server-binaries
    :version :51b0
;;;    :source-ship-type :internal
    :source-filename ("ReThink.ico")
    :destination-directory "rethink/bin"
    :source "rethink"
    :indep t
    :source-subdirectory "bin"
    :shortcuts (rethink-online-server-shortcut)
)

(def-shortcut rethink-online-server-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 ReThink"
    :application-display-name "Start G2 ReThink Server"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\rethink\\kbs\\rethink-online.kb -nowindow"
    :icon-file "../rethink/bin/ReThink.ico"
    :icon-index 0
    :run-style minimized)

(def-part rethink-reports
    :version :51b0
;;;    :source-ship-type :internal
    :destination-directory "rethink/data"
    :source-subdirectory "data"
    :source-filename ("ReThink-Summary-Reports.xls")
    :source "rethink"
    :indep t
;;;    :platforms ("nt")
    :shortcuts (rethink-default-summary-reports))

(def-shortcut rethink-default-summary-reports
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "ReThink Default Summary Reports"
    :application-directory "rethink/data"
    :target-name "ReThink-Summary-Reports.xls")

(def-part rethink-databases
    :version :51b0
;;;    :source-ship-type :internal
    :destination-directory "rethink/data"
    :source-subdirectory "data"
    :source-filename ("orders.mdb")
    :source "rethink"
    :indep t)

(def-part rethink-readme
    :source g2pkgreadme
    :version :83b0
    :source-filename "ReThink-readme.html"
    :destination-directory "doc/rethink"
    :indep t
    :shortcuts (rethink-readme-shortcut))

(def-shortcut rethink-readme-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 ReThink"
    :application-display-name "Readme for G2 ReThink"
    :application-directory "doc/rethink"
    :target-name "ReThink-readme.html")


(def-part rethink-documentation
    :version :50r0
;;;    :source-ship-type :internal
    :destination-directory "doc/rethink"
    :source rethinkdoc
    :indep t
    :shortcuts (rethink-getting-started-documentation rethink-documentation-user rethink-documentation-customization 
         rethink-documentation-winhelp))

(def-shortcut rethink-getting-started-documentation
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "Getting Started with ReThink"
    :application-directory "doc/rethink"
    :target-name "ReThinkTutorials.pdf")

(def-shortcut rethink-documentation-user
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "ReThink Users Guide"
    :application-directory "doc/rethink"
    :target-name "ReThinkUsersGuide.pdf")

(def-shortcut rethink-documentation-customization
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "Customizing ReThink Users Guide"
    :application-directory "doc/rethink"
    :target-name "CustomizingReThinkUsersGuide.pdf")

(def-shortcut rethink-documentation-winhelp
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "ReThink Documentation (Windows Help)"
    :application-directory "doc/rethink/WinHelp"
    :target-name "Master.chm")


;;; ESCOR

(def-component ESCOR
  :print-name "G2 e-SCOR"
  :parts (escor-client-binaries escor-xls-reports escor-kbs escor-server-binaries escor-images escor-examples   escor-documentation escor-readme escor-log-part )
  :optional true
  :platforms ("nt")
  :include-in-contents (escor-kbs))


(def-part escor-client-binaries
    :version :51b0
;;    :source-ship-type :internal
    :source-filename ("e-SCOR.ico") ;;"StartClient.bat" -- Doesn't seem to exist.
    :destination-directory "escor/bin"
    :source "escor"
    :source-subdirectory "bin"
    :platforms ("nt")
;;;    :shortcuts (escor-client-shortcut)
;;;    :environment-variables (ESCOR_RETHINK_HOME)   
;;;    :postinstall-code "replace_rootdir(\"escor\"^\"bin\", \"StartClient.bat\");"
    )

(def-shortcut escor-client-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 e-SCOR"
    :application-display-name "Start e-SCOR Client"
    :application-directory "escor/bin"
    :target-name "StartClient.bat"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-part escor-readme
    :version :83b0
;;    :source-ship-type :internal
    :source-filename ("e-SCOR-readme.html")
    :source "g2pkgreadme"
    :indep t 
    :destination-directory "doc/escor"
    :platforms ("nt")
    :print-name "e-SCOR README file"
    :shortcuts (escor-readme-shortcut))

(def-shortcut escor-readme-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 e-SCOR"
    :application-display-name "Readme for G2 e-SCOR"
    :application-directory "doc/escor"
    :target-name "e-SCOR-readme.html")


(def-part escor-xls-reports
    :version :51b0
    :source "escor"
    :platforms ("nt")
;;    :source-ship-type :internal
    :destination-directory "escor/data"
    :source-subdirectory "data"
    :source-filename ("e-SCOR-Summary-Reports.xls" "Tutorial-Simplest-Model-Summary-Reports.xls" "Tutorial-ACME-Summary-Reports.xls" "Tutorial-VMI-Summary-Reports.xls")
    :shortcuts (escor-default-summary-reports
		 simplest-model-summary-reports-tutorial
		 escor-simplest-tutorial
		 acme-summary-report-tutorial
		 vmi-summary-report-tutorial))

(def-shortcut escor-default-summary-reports
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "e-SCOR Default Summary Reports"
    :application-directory "escor/data"
    :target-name "e-SCOR-Summary-Reports.xls")

(def-shortcut simplest-model-summary-reports-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "Simplest Model Summary Reports"
    :application-directory "escor/data"
    :target-name "Tutorial-Simplest-Model-Summary-Reports.xls")

(def-shortcut acme-summary-report-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "ACME Summary Reports"
    :application-directory "escor/data"
    :target-name "Tutorial-ACME-Summary-Reports.xls")

(def-shortcut vmi-summary-report-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "VMI Summary Reports"
    :application-directory "escor/data"
    :target-name "Tutorial-VMI-Summary-Reports.xls")

(def-part escor-log-part
  :version :51b0
  :platforms ("nt")
;;  :source-ship-type :internal
  :destination-directory "escor/logs"
  :source-subdirectory "logs"
  :source "escor"
)

(def-part escor-archives-part
  :version :51b0
  :platforms ("nt")
;;  :source-ship-type :internal
  :destination-directory "escor/archives"
  :source-subdirectory "archives"
  :source "escor"
)

(def-part escor-resources
  :version :51b0
  :platforms ("nt")
;;  :source-ship-type :internal
  :destination-directory "escor/resources"
  :source-subdirectory "resources"
  :source "escor"
)

(def-part escor-kbs
    :version :51b0
    :platforms ("nt")
  ;;  :source-ship-type :internal
    :destination-directory "escor/kbs"
    :source-subdirectory "kbs"
    :source-filename ("escor-customiz.kb" "e-scor.kb") 
    :source "escor"
)

(def-part escor-examples
  :version :51b0
  :platforms ("nt")
;;  :source-ship-type :internal
  :destination-directory "escor/examples"
  :source-subdirectory "examples"
  :source-filename ("escor-demo.kb" "escor-tutorial-acme.kb" "escor-tutorial-vmi.kb" "escor-tutorial-simplest.kb")
  :source "escor"
  :shortcuts (demo-tutorial acme-tutorial vmi-tutorial)
)

(def-shortcut demo-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "e-SCOR Examples"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\escor\\examples\\escor-demo.kb -nowindow"
    :icon-file "../escor/bin/e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut acme-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "ACME Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\escor\\examples\\escor-tutorial-acme.kb -nowindow"
    :icon-file "../escor/bin/e-SCOR.ico"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut vmi-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "VMI Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\escor\\examples\\escor-tutorial-vmi.kb -nowindow"
    :icon-file "../escor/bin/e-SCOR.ico"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

(def-part escor-images
    :version :51b0
    :platforms ("nt")
  ;;  :source-ship-type :internal
    :destination-directory "escor/kbs/images"
    :source-subdirectory "kbs/images"
    :source "escor"
)

(def-part escor-server-binaries
    :version :51b0
    :platforms ("nt")
  ;;  :source-ship-type :internal
    :source-filename ("e-SCOR.ico")
    :destination-directory "escor/bin"
    :source "escor"
    :source-subdirectory "bin"
    :shortcuts (escor-server-shortcut))


(def-shortcut escor-server-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 e-SCOR"
    :application-display-name "Start G2 e-SCOR Server"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\escor\\kbs\\e-scor.kb -nowindow"
    :icon-file "../escor/bin/e-SCOR.ico"
    :icon-index 0
    :run-style minimized)

;;;
;;; Documentation components for ReThink, e-SCOR, and core G2
;;;


(def-part escor-documentation
    :version :50r0
    :platforms ("nt")
;;    :source-ship-type :internal
    :destination-directory "doc/escor"
    :source escordoc
    :indep t
    :shortcuts (escor-documentation-quick escor-documentation-user escor-tutorial))

(def-shortcut escor-documentation-quick
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "e-SCOR Quick Reference"
    :application-directory "doc/escor"
    :target-name "webSCORQuickReference.pdf")

(def-shortcut escor-documentation-user
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "e-SCOR Users Guide"
    :application-directory "doc/escor"
    :target-name "webSCORUsersGuide.pdf")

(def-shortcut escor-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "e-SCOR Tutorial"
    :application-directory "doc/escor"
    :target-name "webSCORTutorials.pdf")

(def-shortcut escor-simplest-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "Simplest Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\escor\\examples\\escor-tutorial-simplest.kb -nowindow"
    :icon-file "../escor/bin/e-SCOR.ico"
    :icon-file "e-SCOR.ico"
    :icon-index 0
    :run-style minimized) 
;;; NOL

(def-component NOL
  :print-name "G2 NeurOn-Line"

  :parts (nolstudio-data nolstudio-math-library   nolstudio-window-classic-dll nolstudio-deploy-library
	  nolstudio-gui nolstudio-gui-misc nolstudio-batch nolstudio-online-batch 
nolstudio-examples nolstudio-deploy-misc nol-classic-kb nol-classic-nt gnne-demo gnne-demo-config nol-total-demo nol-bakery-demo nol-bleach-demo nol-classic-gnne nol-g2i-modules  nol-classic-documentation nol-readme nols-readme nolstudio-window-misc nolstudio-ActiveX-control)

  :optional true
  :platforms ("nt")
  :include-in-contents (gnne-demo))


(def-part nolstudio-data-eva
    :version :51b0
    :print-name "G2 NOL Studio Data Evaluation"
    :source nols
    :platforms ("nt")
    :source-filename "NolStudioDataEva.jar"
    :destination-directory nolstudio
	:destination-filename NolStudioData.jar)

(def-part nolstudio-data
    :version :51b0 
    :print-name "G2 NOL Studio Data"
    :source nols
    :platforms ("nt")
    :source-filename "NolStudioData.jar"
    :destination-directory nolstudio)

(def-environment-variable nolstudio_home
    :value "<TARGETDIR>")

(def-environment-variable nolstudio-jre
    :variable "PATH"
    :append-or-merge merge
    :value "<TARGETDIR>\\\\jre\\\\bin;<TARGETDIR>\\\\jre\\\\bin\\\\client")


(def-part nolstudio-math-library
    :version :51b0 
    :print-name "G2 NOL Studio Math Library"
    :platforms ("nt")
    :source nols
    :source-filename "NolStudioMath.jar"
    :destination-directory nolstudio)

(def-part nolstudio-core-misc-demolicense
    :version :51b0 
    :print-name "G2 NOL Studio Core Misc"
    :source nols
    :platforms ("nt")
    :source-filename ("demolicense.txt" "known-bugs.txt")
    :destination-directory nolstudio)

(def-part nolstudio-gui
    :version :51b0 
    :source-filename "NolStudioGUI.jar"
    :source nols
    :platforms ("nt")
    :destination-directory nolstudio
    :print-name "G2 NOL Studio GUI")

(def-part nolstudio-gui-misc
    :version :51b0 
    :source nols
    :platforms ("nt")
    :destination-directory nolstudio
    :source-filename ("readme.html")
	:shortcuts (nolstudio-readme))

(def-shortcut nolstudio-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 NeurOn-Line"
    :application-display-name "G2 NeurOn-Line Studio Readme"
    :application-directory nolstudio
    :target-name readme.html)

(def-part nolstudio-batch
    :version :51b0 
    :source nols
    :platforms ("nt")
    :destination-directory nolstudio/bin
    :platforms ("nt")
    :source-filename ("nolstudio.bat")
	:postinstall-code "replace_rootdir(\"nolstudio\"^\"bin\", \"nolstudio.bat\");"
	:shortcuts (nolstudio-batch-file))

(def-shortcut nolstudio-batch-file
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 NeurOn-Line"
    :application-display-name "G2 NeurOn-Line Studio"
    :application-directory nolstudio/bin
    :target-name nolstudio.bat
	:icon-file "../nol/bin/nol.ico"
	:icon-index 0
    :run-style minimized)

(def-part nolstudio-examples
    :version :51b0 
    :source nols
    :platforms ("nt")
    :source-subdirectory projects
    :destination-directory nolstudio/projects)

#|
(def-part nolstudio-documentation
    :version :43r1 :source-ship-type :internal 
    :source noldoc
    :destination-directory doc/nol/nolstudio
    :shortcuts (nolstudio-users-guide))
|#

(def-part nolstudio-window-misc
    :source nols
    :platforms ("nt")
    :version :51b0 
    :source-filename ("RegisterControls.bat" "UnRegisterControls.bat")
    :platforms ("nt")
	:destination-directory nolstudio/bin)

(def-part nolstudio-ActiveX-control
    :source nols
    :platforms ("nt")
    :version :51b0 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "NolOnline.dll"
    :platforms ("nt")
;;    :environment-variables (nolstudio_home nolstudio-jre)
    :shortcuts (nolstudio-install-control nolstudio-uninstall-control))

(def-shortcut nolstudio-install-control
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 NeurOn-Line"
    :application-display-name "Register G2 NeurOn-Line Control"
    :application-directory nolstudio/bin
    :target-name RegisterControls.bat
    :run-style minimized)

(def-shortcut nolstudio-uninstall-control
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 NeurOn-Line"
    :application-display-name "Unregister G2 NeurOn-Line Control"
    :application-directory nolstudio/bin
    :target-name UnRegisterControls.bat
    :run-style minimized)

(def-part nolstudio-window-classic-dll
    :source nols
    :platforms ("nt")
    :version :51b0 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "jnol.dll"
    :platforms ("nt"))

(def-part nolstudio-deploy-library
    :source nols
    :platforms ("nt")
    :version :51b0
    :destination-directory nolstudio
    :source-filename "NolStudioDeploy.jar")

(def-part nolstudio-online-batch
    :source nols
    :platforms ("nt")
    :version :51b0
    :source-filename "onlinenolstudio.bat"
    :platforms ("nt")
	:postinstall-code "replace_rootdir(\"nolstudio\"^\"bin\", \"onlinenolstudio.bat\");"
	:destination-directory nolstudio/bin
	)

(def-part nolstudio-deploy-misc
    :source nols
    :platforms ("nt")
    :version :51b0
    :source-filename "nolonline.bat"
    :platforms ("nt")
	:postinstall-code "replace_rootdir(\"nolstudio\"^\"bin\", \"nolonline.bat\");"
	:destination-directory nolstudio/bin
	)

(def-part nol-classic-kb
    :source nol
    :version :51b0
    :source-subdirectory kbs
    :indep t
    :destination-directory "nol/kbs"
    :source-filename ("nol.kb" "nolapps.kb" "gnneapps.kb" "noldemo.kb" "nolexten.kb" "nolx.kb" 
				"nolxapps.kb" "nolui.kb" "java-module.kb"  "nolspack.kb" "nolstudio.kb"))

(def-part nol-classic-gnne
    :source nol
    :version :51b0
    :source-subdirectory kbs
    :indep t
    :destination-directory "nol/kbs"
    :source-filename ("gnne.kb"))

(def-part nol-classic-nt
    :source nol
    :version :51b0
    :source-subdirectory bin
    :indep t
    :destination-directory "nol/bin"
    :platforms ("nt")
    :source-filename ("ntnol.exe" "nol.ico")
    :shortcuts (nolapps-shortcut gnneapps-shortcut gnnedemo-shortcut noldemo-shortcut nolbakerydemo-shortcut nolbleachdemo-shortcut))

(def-shortcut nolapps-shortcut
     :folder-name g2-shortcut-folder-name
     :subfolder-name "G2 NeurOn-Line"
     :application-display-name "G2 NeurOn-Line Application"
     :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\kbs\\nolapps.kb -start"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut gnneapps-shortcut
     :folder-name g2-shortcut-folder-name
     :subfolder-name "G2 NeurOn-Line"
     :application-display-name "G2 Neural Network Engine Application"
     :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\kbs\\gnneapps.kb -start"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut gnnedemo-shortcut
     :folder-name g2-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "G2 NeurOn-Line"
     :application-display-name "G2 Neural Network Engine Demo"
	 :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\projects\\examples\\gnne-demo\\gnne-demo.kb -configfile ..\\nol\\projects\\examples\\gnne-demo\\config.txt"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut noldemo-shortcut
     :folder-name g2-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "G2 NeurOn-Line"
     :application-display-name "G2 NeurOn-Line Total Demo"
	 :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\projects\\examples\\total-demo\\total-demo.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut nolbakerydemo-shortcut
     :folder-name g2-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "G2 NeurOn-Line"
;;    :subsubfolder-name "GNNE"
     :application-display-name "G2 NeurOn-Line Bakery Demo"
	 :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\projects\\examples\\bakery-demo\\bakery.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut nolbleachdemo-shortcut
     :folder-name g2-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "G2 NeurOn-Line"
;;    :subsubfolder-name "GNNE"
     :application-display-name "G2 NeurOn-Line Bleach Demo"
	 :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\projects\\examples\\bleach-demo\\bleach-plant.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-part nol-classic-documentation
    :source noldoc
    :version :50r0
    :indep t
    :destination-directory doc/nol
    :shortcuts (nol-users-guide nol-reference-guide gnne-users-guide nolstudio-users-guide))


(def-shortcut nolstudio-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "G2 NeurOn-Line Studio Users' Guide"
    :application-directory doc/nol
    :target-name nolstudioug.pdf)

(def-part gnne-demo
    :source nol
    :version :51b0
    :indep t
    :source-subdirectory projects/examples/gnne-demo
    :destination-directory nol/projects/examples/gnne-demo)

(def-part gnne-demo-config
    :source nol
    :version :51b0
    :indep t
    :source-subdirectory projects/examples/gnne-demo
    :destination-directory nol/projects/examples/gnne-demo
    :source-filename ("config.txt")
    :postinstall-code "replace_rootdir(\"nol\"^\"projects\"^\"examples\"^\"gnne-demo\", \"config.txt\");"
	)

(def-part nol-total-demo
    :source nol
    :version :51b0
    :indep t
    :source-subdirectory projects/examples/total-demo
    :destination-directory nol/projects/examples/total-demo)

(def-part nol-bakery-demo
    :source nol
    :version :51b0
    :indep t
    :source-subdirectory projects/examples/bakery-demo
    :destination-directory nol/projects/examples/bakery-demo)

(def-part nol-bleach-demo
    :source nol
    :version :51b0
    :indep t
    :source-subdirectory projects/examples/bleach-demo
    :destination-directory nol/projects/examples/bleach-demo)

(def-shortcut nol-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "G2 NeurOn-Line Users' Guide"
    :application-directory doc/nol
    :target-name nolusersguide.pdf)

(def-shortcut nol-reference-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "G2 NeurOn-Line Reference Manual"
    :application-directory doc/nol
    :target-name nolrm.pdf)

(def-shortcut gnne-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "Neural Network Engine Users' Guide"
    :application-directory doc/nol
    :target-name "GNNEUsersGuide.pdf")

(def-part nol-readme
    :source g2pkgreadme
    :version :83b0
    :destination-directory doc/nol
    :source-filename "readme-nol-bundle.html"
    :indep t
    :shortcuts (nol-readme))

(def-shortcut nol-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 NeurOn-Line"
    :application-display-name "Readme for G2 NeurOn-Line"
    :application-directory "doc/nol"
    :target-name readme-nol-bundle.html)


(def-part nols-readme
    :source g2pkgreadme
    :version :83b0
    :destination-directory doc/nol
    :source-filename "readme-nolstudio.html"
    :indep t
    :shortcuts (nols-readme))

(def-shortcut nols-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 NeurOn-Line"
    :application-display-name "Readme for G2 NeurOn-Line Studio"
    :application-directory "doc/nol"
    :target-name readme-nolstudio.html)

(def-part nol-g2i-modules
  :source g2i
  :version :23b0
  :indep t
  :source-subdirectory kbs
  :source-filename ("gdpm.kb" "gedp.kb")
  :destination-directory "g2i/kbs")

;;;Integrity

(def-component integrity
  :print-name "G2 Integrity"
  :optional true
  :parts (integrity-doc ping-manager integrity-g2i-modules integrity-mib-parser remote-OS-agent integrity-readme integrity-reasoner-kbs)
  ;;cdg-import-export-kbs
  :platforms ("nt" "hpux" "sparcsol")
  :include-in-contents (integrity-reasoner-kbs))

(def-part integrity-client-intelnt
    :version :40r0-B03F16
    :source opex-client
    ;; this contains a self extracting installer.  This is no doubt wrong.
    ;; finishing later.
    :platforms ("nt")
    ;;;:environment-variables (integrity_home)
    :destination-directory client
    ;;;  :source-ship-type :internal
;;    :shortcuts (integrity-client)
    :postinstall-code "integrityPostInstall(\"Integrity\");")

(def-shortcut integrity-client
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 Integrity"
    :application-display-name "Integrity Client"
    :application-directory "client\\bin"
    :icon-file "../integrity/bin/integrity.ico"
    :icon-index 0
    :target-name "integrity.bat")

(def-part integrity-doc
    :source opexdoc
    :version :40r0-FJ14
    :destination-directory "doc/integrity"
    :indep t
    :shortcuts (int-users-guide int-ref-man int-util-guide 
                int-snmp-users-guide int-jsnmp-users-guide int-dxi3db-primer
                int-demo-guide ))

(def-shortcut int-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity User's Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityUsersGuide.pdf")

(def-shortcut int-ref-man
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity Reference Manual"
    :application-directory "doc/integrity"
    :target-name "IntegrityReferenceManual.pdf")

(def-shortcut int-util-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity Utilities Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityUtilitiesGuide.pdf")

(def-shortcut int-snmp-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity G2-SNMP User's Guide"
    :application-directory "doc/integrity"
    :target-name "G2-SNMPBridges.pdf")

(def-shortcut int-jsnmp-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity Java G2-SNMP User's Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityJavaSNMP.pdf")

(def-shortcut int-rel-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity 4.0r0 Release Notes"
    :application-directory "doc/integrity"
    :target-name "IntRelNotes.pdf")

(def-shortcut int-demo-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity Demo Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityDemoGuide.pdf")

(def-shortcut int-dxi3db-primer
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity DXI3DB Primer"
    :application-directory "doc/integrity"
    :target-name "DXI3DB-Primer.pdf")



;;;  +++
;;;  Ping manager part.
(def-part ping-manager
    :source pingmgr
    :version :40r0-B03F16
    :platforms ("nt" "sparcsol" "hpux") 
    :destination-directory "integrity/bin")

(def-part cdg-import-export-kbs
  :source intereas
  :source-subdirectory "kbs"
  :version :50b0
  :indep t
  :source-filename ("cdg-import.kb" "cdg-export.kb")
  :destination-directory "integrity/kbs")

(def-part integrity-g2i-modules
  :source g2i
  :version :23b0
  :indep t
  :source-subdirectory kbs
  :source-filename ("gvad.kb" "gtad.kb" "gndo.kb" "gtrap.kb" "gmib.kb" "gerr.kb" "grtl.kb"  "cdg.kb" "cdggrlb.kb" "gens.kb" "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "grlb.kb" "symcure.kb" "resources-english.txt")
  :destination-directory "g2i/kbs")


(def-part integrity-mib-parser
  :source g2mibparser
  :version :40r0
  :platforms ("nt" ) ;"sparcsol"
  :destination-directory g2mibparser
  :postinstall-code "replace_rootdir(\"g2mibparser\"^\"bin\", \"StartJMibParser.bat\");"
  :shortcuts (mib-parser-shortcut))


(def-shortcut mib-parser-shortcut
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Bridges"
  :application-display-name "MIB Parser Bridge"
  :application-directory "g2mibparser/bin"
  :target-name "StartJMibParser.bat")


(def-part remote-OS-agent
  :source rosa
  :version :40r0-B03F16
  :destination-directory remote-os
  :platforms ("nt" "sparcsol"))


;;;  +++
;;;  Reasoner KB modules part
(def-part integrity-reasoner-kbs
    :source intereas
    :version :50b0
    :destination-directory "integrity"
;;    :postinstall-code "replace_rootdir(\"integrity\"^\"bin\", \"StartServer.bat\");"
    :shortcuts (integrity-shortcut 
                 mpe-demo-shortcut opac-demo-shortcut opx-demo-shortcut scvm-demo-shortcut)
    :indep t) 

(def-shortcut integrity-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 Integrity"
    :application-display-name "Start G2 Integrity Server"
    :application-directory "g2"
    :parameters "-kb ..\\integrity\\kbs\\integrity.kb -nowindow"
    :icon-file "../integrity/bin/integrity.ico"
    :icon-index 0
    :target-name "StartServer.bat")


(def-shortcut doc-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Doc Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :icon-file "../integrity/bin/integrity.ico"
    :icon-index 0
    :parameters "-kb ..\\integrity\\examples\\doc_demo.kb -nowindow")

(def-shortcut mpe-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Message Parsing Engine Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :icon-file "../integrity/bin/integrity.ico"
    :icon-index 0
    :parameters "-kb ..\\integrity\\examples\\mpe-demo.kb -nowindow")

(def-shortcut opac-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "OPerator ACtions Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :icon-file "../integrity/bin/integrity.ico"
    :icon-index 0
    :parameters "-kb ..\\integrity\\examples\\opacdemo.kb -nowindow")

(def-shortcut opx-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :icon-file "../integrity/bin/integrity.ico"
    :icon-index 0
    :parameters "-kb ..\\integrity\\examples\\opx_demo.kb -nowindow")

(def-shortcut oxsj-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "OXS Java Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :icon-file "../integrity/bin/integrity.ico"
    :icon-index 0
    :parameters "-kb ..\\integrity\\examples\\oxsjdemo.kb")

(def-shortcut integrity-sockman-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Socket Manager Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :icon-file "../integrity/bin/integrity.ico"
    :icon-index 0
    :parameters "-kb ..\\integrity\\examples\\sockdemo.kb")


(def-part integrity-resources
    :source intereas
    :version :50b0
    :destination-directory "resources"
    :indep t
    :source-filename ("resources/symcure") )

(def-part integrity-readme
    :source g2pkgreadme
    :version :83b0
    :destination-directory doc/integrity
    :source-filename "readme-integrity.html"
    :indep t 
    :shortcuts (integrity-readme))

(def-shortcut integrity-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 Integrity"
    :application-display-name "Readme for G2 Integrity"
    :application-directory "doc/integrity"
    :target-name "readme-integrity.html")



;;; Optegrity

(def-component optegrity
  :print-name "G2 Optegrity"
  :optional true
  :parts (optegrity-win-doc optegrity-release-notes optegrity-doc opt-io-modules opt-io-data    optegrity-readme opt-bin  opt-kbs  opt-g2i-modules
          ;opt-io-resources opt-resources
          opt-io-examples 
          opt-io-modules opt-io-data opt-archive)
  :platforms ("nt")
  :include-in-contents (opt-bin opt-io-modules))


(def-part optegrity-win-doc
    :source optwinhelp
    :version :50r0
;;;    :source-ship-type :internal
    :destination-directory "doc/optegrity/WinHelp"
    :indep t
    :shortcuts (opt-win-doc))

(def-shortcut opt-win-doc
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity Help"
    :application-directory "doc/optegrity/WinHelp"
    :target-name "Master.chm")

(def-part optegrity-release-notes
    :source optegdoc
    :version :50r0
;;;    :source-ship-type :internal
    :source-filename ("OptegrityReleaseNotes.pdf")
    :destination-directory "doc"
    :indep t
    :shortcuts (opt-rel-notes))

(def-shortcut opt-rel-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity Release Notes"
    :application-directory "doc"
    :target-name "OptegrityReleaseNotes.pdf")


(def-part optegrity-doc
    :source optegdoc
    :version :50r0
;;;    :source-ship-type :internal
    :source-filename ("OptegrityUsersGuide.pdf" "OptegrityHeaterTutorial.pdf")
    :destination-directory "doc/optegrity"
    :indep t
    :shortcuts (opt-users-guide 
;;; leaving opt-rel-notes out of the Alpha release.
;;;                opt-rel-notes
;;; WSM 3.23.2006 opt-io-users-guide 
                opt-intelligent-demo-guide))

(def-shortcut opt-io-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Intelligent Objects User's Guide"
    :application-directory "doc/optegrity"
    :target-name "IntelligentObjectsUsersGuide.pdf")

(def-shortcut opt-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity User's Guide"
    :application-directory "doc/optegrity"
    :target-name "OptegrityUsersGuide.pdf")

(def-shortcut opt-ref-man
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity Reference Manual"
    :application-directory "doc/optegrity"
    :target-name "OptRefManual.pdf")

(def-shortcut opt-util-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity Utilities Guide"
    :application-directory "doc/optegrity"
    :target-name "OptUtilGuide.pdf")

(def-shortcut opt-intelligent-demo-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity Heater Tutorial"
    :application-directory "doc/optegrity"
    :target-name "OptegrityHeaterTutorial.pdf")

(def-shortcut opt-demo-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity Furnace Tutorial"
    :application-directory "doc/optegrity"
    :target-name "OptegrityFurnaceTutorial.pdf")

(def-part opt-io-modules
  :source optegrity
  :version :51b0
;;;  :source-ship-type :internal
  :indep t
  :source-subdirectory kbs
  :source-filename ("iato.kb" "icco.kb" "ico.kb"  "icso.kb" "idco.kb" "iedo.kb" "iffo.kb" "iho.kb" "ioc.kb" "ipo.kb" "irco.kb" "iso.kb" "ito.kb" "ivo.kb" "ixo.kb" "sdb.kb" "opt-event.kb")
  :destination-directory "optegrity/kbs")

(def-part opt-io-data
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory data
    :source-filename ("F102-replay-to-external-datapoint.csv" "F102-external-datapoint-configuration-OPC.csv")
    :destination-directory "optegrity/data")

(def-part opt-io-resources
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory resources
    :source-filename ("IATO-EventNames.txt" "ICCO-EventNames.txt" "ICO-EventNames.txt" "IDCO-EventNames.txt" "IEDO-EventNames.txt" "IFFO-FB-EventNames.txt" "IFFO-FF-EventNames.txt" "IHO-EventNames.txt" "IPO-EventNames.txt" "IRCO-EventNames.txt" "ISO-EventNames.txt" "ITO-EventNames.txt" "IVO-EventNames.txt" "IXO-EventNames.txt")
    :destination-directory "optegrity/resources")

(def-part opt-io-examples
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory examples
    :source-filename ("f102demo.kb")
    :destination-directory "optegrity/examples"
    :shortcuts (io-demo-shortcut) )

(def-part opt-f101-examples
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :indep t
    :source-subdirectory examples
    :source-filename ("f101demo.kb" "f102demo.kb")
    :destination-directory "optegrity/examples"
    :shortcuts (f101-demo-shortcut f102-demo-shortcut) ) 

(def-shortcut io-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Heater Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\examples\\f102demo.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut f101-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Intelligent Objects"
    :application-display-name "Furnace Example"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\examples\\f101demo.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)

(def-shortcut f102-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Intelligent Objects"
    :application-display-name "Furnace Example"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\examples\\f102demo.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)

(def-part opt-archive
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :source-subdirectory archives
    :source-filename ( )
    :destination-directory "optegrity/archives"
    :indep t
)

(def-part opt-project
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :source-subdirectory projects
    :source-filename ( )
    :destination-directory "optegrity/projects"
    :indep t
)

(def-part opt-bin
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :source-subdirectory bin
    :source-filename ("InstallServerAsNTService.bat" "Optegrity.ico" "UninstallServerAsNTService.bat")
    :destination-directory "optegrity/bin"
    :postinstall-code "replace_rootdir(\"optegrity\"^\"bin\", \"InstallServerAsNTService.bat\");replace_rootdir(\"optegrity\"^\"bin\", \"UninstallServerAsNTService.bat\");"
    :shortcuts (optegrity-shortcut )
    :indep t
)

(def-part opt-data
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :source-subdirectory data
    :source-filename ("fo2-external-datapoint-configuration-OPC.csv" "fo2-external-datapoint-configuration-OPC.xls" "fo2-external-datapoint-configuration-PI.csv" "fo2-external-datapoint-configuration-PI.xls" "fo2-external-datapoints-configuration.csv" "fo2-external-datapoints-configuration.xls" "fo2-logging-data.csv" "fo2-replay-to-external-datapoint.csv" "fo2-replay-to-internal-datapoint.csv")
    :destination-directory "optegrity/data"
    :indep t
)

(def-part opt-examples
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :source-subdirectory examples
    :source-filename ("fo2demo.kb")
    :destination-directory "optegrity/examples"
    :indep t
)

(def-part opt-kbs
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :source-subdirectory kbs
    :source-filename ("equipmnt.kb" "optegrity.kb" "optegrity-core.kb")
    :destination-directory "optegrity/kbs"
    :indep t
)


(def-part opt-logs
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :source-subdirectory logs
    :source-filename ( )
    :destination-directory "optegrity/logs"
    :indep t
)

(def-part opt-resources
    :source optegrity
    :version :51b0
;;;    :source-ship-type :internal
    :source-subdirectory resources
    :source-filename ("optegrity-core-resources.txt")
    :destination-directory "optegrity/resources"
    :indep t
)

(def-shortcut optegrity-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 Optegrity"
    :application-display-name "Start G2 Optegrity Server"
    :application-directory "g2"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\kbs\\optegrity.kb -nowindow"
    :run-style minimized)

(def-shortcut optegrity-client-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 Optegrity"
    :application-display-name "Start G2 Optegrity Client"
    :application-directory "g2"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :target-name "twng.exe")

(def-shortcut furnace-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Furnace Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\optegrity\\examples\\fo2demo.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
    :icon-index 0
    :run-style minimized)

(def-part opt-g2i-modules
  :source g2i
  :version :23b0
;;  :source-ship-type :internal
  :destination-directory "g2i/kbs"
  :source-subdirectory kbs
  :source-filename ("cdg.kb" "cdggrlb.kb" "gdpm.kb" "gedp.kb" "guif.kb" "guif-resources.txt" "geuc.kb" "symcure.kb" "grtl.kb" "gevm.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "grlb.kb" "gdsm.kb" "gdu.kb" "gduc.kb" "gdue.kb" "gens.kb" "gerr.kb" "glf.kb" "resources-english.txt")
  :indep t)

(def-part optegrity-readme
    :source g2pkgreadme
    :version :83b0
    :source-filename ("readme-optegrity.html")
    :destination-directory "doc/optegrity"
    :indep t 
    :shortcuts (optegrity-readme))

(def-shortcut optegrity-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 Optegrity"
    :application-display-name "Readme for G2 Optegrity"
    :application-directory "doc/optegrity"
    :target-name "readme-optegrity.html")

;;; SymCure
 
(def-component symcure
  :print-name "G2 SymCure"
  :optional true
  :parts (
    symcure-doc 
    symcure-readme 
;    symcure-bin  
    symcure-kbs  
    jmskbs jmailkbs
    symcure-examples)
  :include-in-contents (????)
)
 
;;; Pulling the User's Guide from the Optegrity documentation
(def-part symcure-doc
    :source optegdoc
    :version :50r0
;;;    :source-ship-type :internal
    :source-filename "SymCureUsersGuide.pdf"
    :destination-directory "doc/symcure"
    :indep t
    :platforms ("nt")
    :shortcuts (symcure-users-guide)
)
 
(def-shortcut symcure-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 SymCure"
    :application-display-name "SymCure User's Guide"
    :application-directory "doc/symcure"
    :target-name "SymCureUsersGuide.pdf")
 
 
;;; Where should the SymCure.ico reside, g2i?
(def-part symcure-bin
    :source symcure
    :version :51b0
;;;    :source-ship-type :internal
    :source-subdirectory bin
    :source-filename "SymCure.ico"
    :destination-directory "symcure/bin"
    :platforms ("nt")
    :shortcuts (symcure-shortcut)
    :indep t
)
 
(def-shortcut symcure-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 SymCure"
    :application-display-name "Start G2 SymCure Server"
    :application-directory "g2"
    :icon-file "../optegrity/bin/Optegrity.ico"
;;    :icon-file "../symcure/bin/SymCure.ico" -- when available
    :icon-index 0
    :target-name "StartServer.bat"
    :parameters "-kb ..\\symcure\\kbs\\symcure.kb -nowindow"
    :run-style minimized
)
 
(def-part symcure-readme
    :source g2pkgreadme
    :version :83b0
    :source-filename ("readme-symcure.html")
    :platforms ("nt")
    :destination-directory "doc/symcure"
    :indep t 
    :shortcuts (symcure-readme)
)
 
(def-shortcut symcure-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 SymCure"
    :application-display-name "Readme for G2 SymCure"
    :application-directory "doc/symcure"
    :target-name "readme-symcure.html"
)
 
(def-part symcure-kbs
  :source g2i
  :version :23b0
;;  :source-ship-type :internal
  :destination-directory "g2i/kbs"
  :platforms ("nt")
  :source-subdirectory kbs
  :source-filename ("cdg.kb" "cdggrlb.kb" "symcure.kb" "grtl.kb" "gevm.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "grlb.kb" "gdsm.kb" "gdu.kb"  "gerr.kb" "glf.kb" "resources-english.txt" "grtl-utils.kb" "grtl-icons.kb" "grpe.kb" "gdsm-jmail.kb" "gdsm-jms.kb" "gdsm-db.kb" "gdsm-web.kb" "gweb.kb")
  :indep t)
 
(def-part symcure-examples
    :source g2i
    :version :23b0
    :source-subdirectory examples
    :source-filename ("cdg-modguide.kb")
    :destination-directory "g2i/examples"
    :platforms ("nt")
    :indep t
    :shortcuts (symcure-demo-shortcut)
)
 
(def-shortcut symcure-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 SymCure"
    :application-display-name "SymCure Modeling Guide"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :parameters "-kb ..\\g2i\\examples\\cdg-modguide.kb -nowindow"
    :icon-file "../optegrity/bin/Optegrity.ico"
;;    :icon-file "../symcure/bin/SymCure.ico"
    :icon-index 0
    :run-style minimized)
 
 
(def-shortcut scvm-demo-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity SymCure Tutorial"
    :application-directory "g2"
    :target-name "StartServer.bat"
    :icon-file "../integrity/bin/integrity.ico"
    :icon-index 0
    :parameters "-kb ..\\integrity\\examples\\svcmdemo.kb -nowindow")
