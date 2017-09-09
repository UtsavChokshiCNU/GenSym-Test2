
;; -*- mode: lisp; package: bundle -*-

(in-package "BUNDLE")

;; Copyright (c) 2012-2014 DevFactory, Inc.
;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; G2-FAMILY - G2 Family Definitions.  Requires bundle.lisp.

;; Mark H. David and Chun Tian (binghe)

(provide 'g2-2015-family)

;;;; Families

(def-family G2-2015
    :index 220			; per tools/datafiles/families/family-id.dat
    :file-syntax-version 11
    :bundles (G2-Deployment G2-Development TW-Client)
    :print-name "G2"		; "G2" => "G2 Classic" (MHD 12/13/01)
				; "G2 Classic" => "G2" (yduJ 1/28/02)
    :directory #-Enterprise "g2-2015"
               #+Enterprise "g2-2015e"
    ;; per tools/datafiles/families/guid.dat:
    :guid #-Enterprise "dfbbb4c1-d0ff-484f-8184-3b2a47ed7bf3"
          #+Enterprise "b7ccfea3-3a19-43bb-b9ad-fa85be2da7fe"
    :compatible-previous-versions (("2011"  "f5c990cb-f7cb-48b6-9cee-3e7db4afb021")
				   ("8.3r1" "3973967d-6c2a-4703-a287-be1a50ab5a02")
				   ("8.3r0" "db696946-2d97-44c2-b5f5-7971488fcab4")
				   ("8.3b1" "9d76a758-e820-4223-b011-9472a0a5ee2b")
				   ("8.3b0" "93f4944a-2607-4b88-a977-44ef51b0cff9")
				   ("8.3a1" "7e2afbe3-f71a-4c50-90a6-269814d09516")
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
			("5.1r6a" "243D4BAA-9EE7-11D4-8111-00A02431D004"))
    :splash-screen "g2-setup.bmp"
    :license-text "standard-license.txt")

(defvar g2-shortcut-folder-name
  #-Enterprise "Gensym G2 2015"
  #+Enterprise "Gensym G2 2015 (Enterprise)")

;;; Family G2 OK Files

;;; For the megabundle, we define a large number of OK file family groups,
;;; and then include them all in the def-bundles.

;;; Format: single numbers give you a <n> client unexpiring OK file.
;;; List of (n 2) gives you a <n> client 2-process unexpiring OK file.
;;; list of (1 date) gives you a 1 client expriing OK file.

(setq prevailing-ok-version-suffix "-v12")

(def-g2-ok-components (g2-development :obfuscate :from-sandbox)
    g2 "Development"
    (1 2 3 (1 2)
       ;; NOTE: do not add more items here, it's fixed 10 items.
       (1 "-dec25-2015")
       (1 "-jan25-2016") (1 "-feb25-2016") (1 "-mar25-2016")
       (1 "-apr25-2016") (1 "-may25-2016") (1 "-jun25-2016")
       (1 "-jul25-2016") (1 "-aug25-2016") (1 "-sep25-2016")))

(def-g2-ok-components (rethink-online :obfuscate :from-sandbox) rethink-online "ReThink Online"
  (1 2 3))

(def-g2-ok-components (escor-online :obfuscate :from-sandbox) escor-online "e-SCOR Online"
  (1 2 3))

(def-g2-ok-components (neuron-line-premium-development :obfuscate :from-sandbox) nol "NeurOnline Premium Development"
  (1 2 3))

(def-g2-ok-components (integrity-reasoner-development :obfuscate :from-sandbox) integrity "Integrity Development"
  (1 2 3))

(def-g2-ok-components (optegrity-reasoner-development :obfuscate :from-sandbox) optegrity "G2 Optegrity Development"
  (1 2 3))

(def-g2-ok-components (g2-deployment :obfuscate :from-sandbox) g2 "Deployment"
  (4 8 12))

(def-g2-ok-components (neuron-line-premium-deployment :obfuscate :from-sandbox) nol "NeurOnline Premium Deployment"
  (4 8 12))

(def-g2-ok-components (optegrity-reasoner-deployment :obfuscate :from-sandbox) optegrity "G2 Optegrity Deployment"
  (4 8 16))

(def-g2-ok-components (integrity-reasoner-deployment :obfuscate :from-sandbox) integrity "Integrity Deployment"
  (4 8 16))

(def-component g2-megabundle-ok-file
  :print-name "G2 2011 Megabundle OK file (internal use only)"
  :radio-button-group-index 1
  :parts (g2-megabundle-ok-file)
  :watermark "g2/g2.ok")

(def-part g2-megabundle-ok-file
    :destination-directory g2
    :destination-filename g2.ok
    :indep t
    :source "$SRCBOX/bundle/ok"
    :source-filename "g2-2011-megabundle.obf"
    :obfuscate :from-sandbox)

;;;; Bundles

;; IMPORTANT: do not touch this list, or component IDs will shift.
(defvar core-g2-components
  ; component         | ID
  ;-------------------+----
  '(g2                ; 1
    telewindows       ; 2
    gateway           ; 3
    gda               ; 4
    g2i-core-modules  ; 5
    weblink           ; 6
    javalink          ; 7
    debug-symbols     ; 8
    activexlink       ; 9
    corbalink         ; 10
    opcclient         ; 11
    pibridge          ; 12
    g2-oracle         ; 13
    Sybasebridge      ; 14
    ODBCbridge        ; 15
    ODBCUnicodebridge ; 16
    SymScale          ; 17
    jdbc-component    ; 18
    gservice          ; 19
    g2-readme         ; 20
    protools))        ; 21

;; IMPORTANT: do not touch these lists.
(defvar additional-g2-components ; component id: 22-26
  '(jmail-component jms-component socket-manager jsnmp-bridge hla-bridge))
(defvar additional-g2-deployment-components '(jre)) ; 27
(defvar additional-g2-development-components '(jre doc-pdf doc-html)) ; 27 28 29

(def-bundle g2-deployment ; id :1
    :components (core-g2-components ; 1-21
		 additional-g2-components ; 22-26
		 additional-g2-deployment-components ; 27
		 g2-deployment-family-ok-components ; 28-30
		 neuron-line-premium-deployment-family-ok-components ; 31-33
		 optegrity-reasoner-deployment-family-ok-components ; 34-36
		 integrity-reasoner-deployment-family-ok-components ; 37-39
		 g2-blank-ok-component ; 40
		 rethink   ; 41
		 escor     ; 42
		 nol       ; 43
		 integrity ; 44
		 optegrity ; 45
		 symcure   ; 46
		 ;; IMPORTANT: append new components here
		 )
    :version :2015
    :print-name #-Enterprise "G2 Deployment"
                #+Enterprise "G2 Deployment Enterprise"
    :directory "deployment")

(def-bundle g2-development ; id: 2
    :components (core-g2-components ; 1-21
		 additional-g2-components ; 22-26
		 additional-g2-development-components ; 27-29
		 g2-development-family-ok-components ; 30-43
		 neuron-line-premium-development-family-ok-components ; 44-46
		 escor-online-family-ok-components ; 47-49
		 optegrity-reasoner-development-family-ok-components ; 50-52
		 integrity-reasoner-development-family-ok-components ; 53-55
		 rethink-online-family-ok-components ; 56-58
		 g2-megabundle-ok-file ; 59
		 g2-blank-ok-component ; 60
		 rethink   ; 61
		 escor     ; 62
		 nol       ; 63
		 integrity ; 64
		 optegrity ; 65
		 symcure   ; 66
		 ) ; 67 is the last possible value
    :version :2015
    :print-name #-Enterprise "G2 Development"
                #+Enterprise "G2 Development Enterprise"
    :directory "development")

(def-bundle tw-client ; id: 3
    :components (telewindows doc-html)
    :version :2015
    :print-name "Telewindows Client"
    :directory "client"
    :platforms ("nt" "win64"))

;;; IMPORTANT: Add new bundle here.

;;;; Components

(def-component g2
  :parts
  (g2-intelnt g2-unix
	      kanji-dic ext-directory
	      g2-blank-ok
	      kbs fonts g2-x64
	      mill-demo startserver-bat-file startserver-sh-file registerControls
	      ;;The following kbs are requested by the application products to
	      ;;be available even when the bridge itself is not authorized.
	      ;;Suggestion HQ-4795626.
	      jmskbs odbckbs odbckbsunicode jdbckbs
	      oraclekbs sybasekbs pikbs opcclientkbs socket-manager-kbs
	      jvlkbs gwkbs jmailkbs
	      #+ignore startsymscale-bat-file
	      )
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
  :parts (gsi gsi-sample)
  :print-name "G2 Gateway (GSI)"
  :include-in-contents (gsi))

(def-component debug-symbols
  :parts (symbols-intelnt symbols-linux)
  :print-name "Debug Symbols (PDB)"
  :optional true
  :platforms ("nt" "win64" "linux" "linux64"))

(def-component gda :parts (gda) :print-name "G2 Diagnostic Assistant (GDA)")

(def-component weblink
  :parts (gw run-gw-template-batfile)
  :print-name "G2 WebLink")

(defvar basic-jvl-parts
  '(jvl-unix jvl-intelnt jvl-readme jvl-com-gensym-properties-intelnt jvl-javadoc
    jvl-classes))

(def-component javalink
  :parts (basic-jvl-parts)
  :include-in-contents (jvl-unix jvl-intelnt)
  :print-name "G2 JavaLink")

(def-component activexlink
  ;;note order: put the individual file part first and the "everything" part
  ;;last, and then when uninstall happens everything will be uninstalled.
  :parts (axl-g2com-dll axl)
  :platforms ("nt" "win64")
  :print-name "G2 ActiveXLink")

(def-component gservice
  :parts (gservice)
  :print-name "GService Startup Service"
  :platforms ("nt" "win64"))

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
	   #+nil g2classicrn 
	   g2oradoc g2sybdoc opcclientdoc g2pidoc g2odbcdoc
	   g2dbdoc protoolsdoc weblinkdoc gdadoc-api-pdf gdadoc-ug-pdf
	   snmpdoc-pdf
	   )
  :print-name "G2 Full Documentation (PDF)"
  :include-in-contents (g2doc-g2refman-pdf)
  :typical false)

(def-component doc-html
  :parts ()
  :print-name "G2 Full Documentation (HTML/Gold)"
  :include-in-contents ()
  :typical false)

(def-component doc-chm ; leave for future use
  :platforms ("nt" "win64")
  :parts ()
  :print-name "G2 Core Help"
  :typical true)

(def-component g2-readme
  :parts (g2-readme)
  :print-name "G2 Readme")

(def-component protools
  :parts (protools profiler profiler-demo)
  :print-name "G2 ProTools"
  :platforms ("nt" "win64"))

;;; Optional Bridges in G2: Two bridges are standard (picked by the customer at
;;; order time), and others may be optionally chosen, i.e., at order time.
;;;
;;; Optional Bridges: (1) corbalink (2) opcclient (3) Oraclebridge (4)
;;; Sybasebridge (5) ODBCbridge (6) Pi Bridge (7) JMS (8) Socket Manager
;;; (9) HLA Bridge (10) Old OPClink Bridge
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

(def-component opcclient :parts (opcclient) :platforms ("nt" "win64")
	       :print-name "G2 OPC Client Bridge"
	       :optional true)

(def-component opclink :parts (opclink) :platforms ("nt" "win64")
	       :print-name "G2 OPCLink Bridge"
	       :optional true)

(def-component pibridge :parts (g2pi
				run-g2-pi-template-batfile) :platforms ("nt" "win64")
	       :print-name "G2 PI Bridge"
	       :optional true)

(def-component g2-oracle
    :parts (oraclebridge oraclebin
#|
	    run-g2-ora7-template-batfile
	    run-g2-ora80-template-batfile
	    run-g2-ora81-template-batfile
	    run-g2-ora90-template-batfile
	    run-g2-ora92-template-batfile
|#
	    run-g2-ora10-template-batfile
	    #+Enterprise run-g2-ora10-x64-template-batfile
	    run-g2-ora11-template-batfile
	    #+Enterprise run-g2-ora11-x64-template-batfile
	    run-g2-ora12-template-batfile
	    #+Enterprise run-g2-ora12-x64-template-batfile
	    oraclekbs)
    :print-name "G2 Oracle Bridge"
    :optional true)

(def-component Sybasebridge
    :parts (Sybasebridge
#|
	    run-g2-sybase11-template-batfile
	    run-g2-sybase125-template-batfile
|#
	    run-g2-sybase150-template-batfile
	    #+Enterprise run-g2-sybase150-x64-template-batfile)
    :print-name "G2 Sybase Bridge"
    :non-platforms ("linux" "linux64")
    :optional true)

(def-component ODBCbridge
    :parts (ODBCbridge
	    run-g2-odbc-template-batfile
	    #+Enterprise run-g2-odbc-x64-template-batfile
	    run-g2-odbc-sh-file)
    :print-name "G2 ODBC Bridge"
    :optional true)

(def-component ODBCUnicodebridge
    :parts (odbcunicodebridge
	    run-g2-odbc-unicode-template-batfile
	    #+Enterprise run-g2-odbc-unicode-x64-template-batfile)
    :platforms ("nt" "win64")
    :print-name "G2 ODBC UNICODE Bridge"
    :optional true)

(def-component SymScale ; wait for reuse
    :parts (#+ignore symscale-intelnt
	    #+ignore symscale-unix) ; #+Enterprise when ready
    :platforms ("win64" "linux64")
    :print-name "SymScale"
    :optional true)

;;;; Parts

(def-part g2-intelnt
    :version :2015
    :print-name "G2 Windows Executable"
    :source g2
    :source-filename ("g2.exe" "libiconv.dll"
		      "g2passwd.exe" "machine-id.exe" "hostlookup.exe")
    :destination-directory "g2"
    :platforms ("nt" "win64")
    :shortcuts (g2-shortcut))

(def-shortcut startserver-shortcut
    :folder-name g2-shortcut-folder-name
    :application-directory "g2"
    :target-name "StartServer.bat"
    :icon-file "g2.exe"
    :icon-index 0)

(def-part symscale-intelnt
    :version :2015
    :print-name "SymScale Windows Executable"
    :source g2
    :source-filename ("SymScale.exe")
    :destination-directory "g2"
    :platforms ("win64")
    :shortcuts (symscale-shortcut))

(def-shortcut startsymscale-shortcut
    :folder-name g2-shortcut-folder-name
    :application-directory "g2"
    :target-name "SymScale.bat"
    :icon-file "SymScale.exe"
    :icon-index 0)

(def-shortcut g2-shortcut
    :parent startserver-shortcut
    :application-display-name "Start G2 Server"
    :parameters "-netinfo")

(def-shortcut symscale-shortcut
    :parent startsymscale-shortcut
    :application-display-name "Start SymScale"
    :parameters "-netinfo")

(def-part g2-unix
    :version :2015
    :print-name "G2 Unix Executable"
    :source g2
    :source-filename ("g2"
		      "g2passwd" "hostlookup" "machine-id")
    :destination-directory "g2"
    :non-platforms ("nt" "win64"))

(def-part symscale-unix
    :version :2015
    :print-name "G2 Unix Executable"
    :source g2
    :source-filename ("SymScale")
    :destination-directory "g2"
    :platforms ("linux64"))

(def-part g2-blank-ok
    :version :2015
    :print-name "Sample G2 OK file"
    :source g2
    :source-filename "g2.ok"
    :destination-directory "g2")

(def-part kanji-dic
    :version :2015
    :print-name "Kanji dictionary files"
    :source g2
    :source-filename ("index.dic" "kojin.dic" "main.dic")
    :destination-directory "g2")

(def-part ext-directory
    :version :2015
    :print-name "G2 EXT Directory"
    :source g2
    :source-subdirectory "ext"
    :destination-directory "g2/ext")

(def-part tw-intelnt
    :version :2015
    :print-name "TW Windows Executable"
    :source tw
    :source-filename ("tw.exe" "nptwplug.dll" "pegrp32f.dll")
    :destination-directory "g2"
    :platforms ("nt" "win64")
    :shortcuts (tw-shortcut tw-shortcut-multiwindow)
    :postinstall-code "LaunchAppAndWait(TARGETDIR ^ \"g2\"^\"tw.exe\", \"/regserver /s\", WAIT);"
    :uninstall-code "LaunchAppAndWait(TARGETDIR ^ \"g2\"^\"tw.exe\", \"/unregserver /s\", WAIT);")

(def-part tw-win2000
    :version :2015
    :print-name "TW Windows Support DLL"
    :source tw
    :source-subdirectory win2000
    :source-filename ("gdiplus.dll")
    :destination-directory "g2"
    :postinstall-code "DeleteDLLIfNotNeeded(\"gdiplus.dll\",5,1,\"g2\");"
    :platforms ("nt" "win64"))

(def-part twng
    ;;This kluge brought to you by the wonders of the bundle version number decomposer.
    :version :2015-NG
    :print-name "TW Next Generation"
    :source tw
    :source-filename ("twng.exe")
    :destination-directory "g2"
    :preinstall-code "VerifyDLLVersion(\"comctl32.dll\",4,71,\"\",\"Telewindows\");VerifyDLLVersion(\"shell32.dll\",4,71,\"shfolder.dll\",\"Telewindows\");"
    :postinstall-code "LaunchAppAndWait(TARGETDIR ^ \"g2\"^\"twng.exe\", \"/regserver /s\", WAIT);"
    :uninstall-code "LaunchAppAndWait(TARGETDIR ^ \"g2\"^\"twng.exe\", \"/unregserver /s\", WAIT);"
    :platforms ("nt" "win64")
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
    :version :2015
    :print-name "TW Unix Executable"
    :source tw
    :source-filename ("tw" #+nil "nptwplug.so")
    :destination-directory "g2"
    :non-platforms ("nt" "win64"))

(def-part twax
    :version :2015
    :source-filename ("TwControl.cab" "unregisterTwControl.bat" "TwControl.ocx"
		      "install.html" "registerTwControl.bat")
    :destination-directory "g2"
    :platforms ("nt" "win64"))

(def-part twax-examples
    :version :2015
    :source twax
    :source-subdirectory examples
    :destination-directory "g2/examples"
    :platforms ("nt" "win64"))


;;It is an extremely sad fact that we must specify all the files in the
;;directory here.  The problem is we need to specify individual filenames from
;;every component that goes into the G2 directory or it chooses *.* from the
;;whole concatenated mess, rather than just *.* from the individual component.
;;Then you end up with all possible OK files with their ugly names!  Oops.
(def-part workspace-view
    :version :2015
    :source wsv
    :destination-directory "g2"
    :source-filename ("WSView.frm" "WSView.frx" "WorkspaceView.ocx" "WorkspaceViewDemo.exe" "WorkspaceViewDemo.vbp" "WorkspaceViewDemo.vbw" "registerWSV.bat" "unregisterWSV.bat" "wsvdemo.kb" "wsview.html")
    :platforms ("nt" "win64")
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
    :parameters "-kb wsvdemo.kb -tcpport 1111 -tcpipexact")

(def-shortcut wsview-html
    :folder-name g2-shortcut-folder-name
    :application-display-name "HTML Page"
    :subfolder-name "Examples"
    :subsubfolder-name "Workspace View"
    :application-directory "g2"
    :target-name "wsview.html")

(def-part kbs
  :version :2015
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
    :version :2015
    :destination-directory g2/kbs/demos
    :source-filename ("start-mill.bat" "sleep.exe")
    :postinstall-code "replace_rootdir(\"g2\"^\"kbs\"^\"demos\", \"start-mill.bat\");"
    :platforms ("nt" "win64")
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
    :version :2015
    :source-filename ("StartServer.bat")
    :destination-directory g2
    :platforms ("nt" "win64")
    :postinstall-code "replace_rootdir(\"g2\", \"StartServer.bat\");"
    :indep t ;; it's on indep even though it's really not independent.
             ;;Other demos were that way, just piggybacked on existing product.
    )

(def-part startsymscale-bat-file
    :source demos
    :version :2015
    :source-filename ("SymScale.bat")
    :destination-directory g2
    :platforms ("win64")
    :postinstall-code "replace_rootdir(\"g2\", \"SymScale.bat\");"
    :indep t ;; it's on indep even though it's really not independent.
             ;;Other demos were that way, just piggybacked on existing product.
    )

(def-part startserver-sh-file
    :source demos
    :version :2015
    :source-filename ("startserver")
    :destination-directory g2
    :non-platforms ("nt" "win64")
    :postinstall-code "replace_rootdir(\"g2\", \"startserver\");"
    :indep t ;; it's on indep even though it's really not independent.
             ;;Other demos were that way, just piggybacked on existing product.
    )

(def-part registerControls
    :source demos
    :version :2015
    :source-filename ("registerControls.bat" "unregisterControls.bat")
    :destination-directory g2
    :platforms ("nt" "win64")
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
    :version :2015
    :destination-directory g2/fonts :indep t
    ;; fonts are read-only, which is not terribly bad by itself, but
    ;; causes these problems: using this part from both g2 and telewindow
    ;; components, and doing uninstall on Windows.
    :make-not-read-only t)

(def-part g2-x64
    :version :2015
    :print-name "G2 x64 Directory"
    :source g2
    :source-subdirectory "x64"
    :destination-directory "g2/x64")


;; Documentation Shortcuts
(def-shortcut g2-release-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "G2 Bundle Release Notes"
    :application-directory "doc"
    :target-name "g2relnotes.pdf")

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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
    :application-display-name "G2 Developer's Guide"
    :application-directory "doc\\g2\\g2devguide"
    :target-name "g2devguide.pdf")

#+nil
(def-shortcut g2-developers-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "G2 Developer's Guide"
    :application-directory "doc\\g2\\g2devguide\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-dynamic-displays-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Dynamic Displays User's Guide (GDD)"
    :application-directory "doc\\utilities\\gdd"
    :target-name "gdd.pdf")

#+nil
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
    :application-display-name "G2 Developer's Interface User's Guide (GDI)"
    :application-directory "doc\\utilities\\gdi"
    :target-name "gdi.pdf")

#+nil
(def-shortcut g2-developers-interface-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Developer's Interface User's Guide (GDI)"
    :application-directory "doc\\utilities\\gdi\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-foundation-resources-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Foundation Resources User's Guide (GFR)"
    :application-directory "doc\\utilities\\gfr"
    :target-name "gfr.pdf")

#+nil
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

#+nil
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
    :application-display-name "G2 Online Documentation Developer's Guide (GOLD)"
    :application-directory "doc\\utilities\\golddev"
    :target-name "golddev.pdf")

#+nil
(def-shortcut g2-online-documentation-developers-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation Developer's Guide (GOLD)"
    :application-directory "doc\\utilities\\golddev\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-online-documentation-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Utilities"
    :application-display-name "G2 Online Documentation User's Guide (GOLD)"
    :application-directory "doc\\utilities\\goldui"
    :target-name "goldui.pdf")

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
(def-shortcut g2idoc-gweb-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Web User's Guide (GWEB)"
    :application-directory "doc\\g2i\\gweb\\html"
    :target-name "titlepag.htm")

(def-part hladoc-pdf
    :source hladoc
    :version :20r0
    :source-subdirectory hla
    :destination-directory doc/bridges/hla
    :source-filename ("g2hla.pdf")    
    :platforms ("nt" "win64")
    :shortcuts (hladoc-pdf)
    :indep t)

#+nil
(def-part hladoc-html
    :source hladoc
    :version :20r0
    :destination-directory doc/bridges/hla/html
    :source-subdirectory hla/html
    :shortcuts (hladoc-html)
    :indep t)

(def-shortcut hladoc-pdf
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 HLA User's Guide"
    :application-directory "doc\\bridges\\hla"
    :target-name "g2hla.pdf")

#+nil
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

#+nil
(def-shortcut gda-users-guide-and-rm-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "GDA"
    :application-display-name "GDA User's Guide and Reference Manual"
    :application-directory "doc\\gda\\gdaugrm\\html"
    :target-name "titlepag.htm")

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

#+nil
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

#+nil
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
    :application-display-name "G2 Gateway Bridge Developer's Guide"
    :application-directory "doc\\g2\\g2gateway"
    :target-name "g2gateway.pdf")

#+nil
(def-shortcut gsi-bridge-developers-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2"
    :application-display-name "G2 Gateway Bridge Developer's Guide"
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

#+nil
(def-shortcut g2-database-bridge-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 Database Bridge User's Guide"
    :application-directory "doc\\bridges\\db\\html"
    :target-name "titlepag.htm")

(def-shortcut g2-opcclient-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-OPC Client User's Guide"
    :application-directory "doc\\bridges\\opcclient"
    :target-name "g2opcclient.pdf")

#+nil
(def-shortcut g2-opcclient-users-guide-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-OPC Client User's Guide"
    :application-directory "doc\\bridges\\opcclient\\html"
    :target-name "titlepag.htm")


(def-shortcut g2-corba-link-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "Bridges"
    :application-display-name "G2 CORBALink User's Guide"
    :application-directory "doc\\bridges\\corbalink"
    :target-name "g2corbalink.pdf")

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
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

#+nil
(def-shortcut snmpdoc-html
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "Bridges"
    :application-display-name "G2-SNMP Bridge User's Guide"
    :application-directory "doc\\bridges\\snmp\\html"
    :target-name "titlepag.htm")

(def-part gsi
    :version :2015
    :destination-directory gsi)

(def-part gsi-sample
    :version :2015
    :source gsi
    :destination-directory gsi)

(def-part gservice
    :version :2015
    :source gservice
    :source-filename "gservice.exe"
    :destination-directory g2
    :platforms ("nt" "win64"))
    
(def-part gda
    :version :51r1
    :destination-directory gda
    :indep t
    :shortcuts (gdacerl gdareact gdatank))

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
  :version :23r1
  :indep t
  :source-subdirectory kbs
  :source-filename ("gens.kb" "gerr.kb" "grtl.kb" "grtl-icons.kb" "grtl-utils.kb" "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "resources-english.txt" "cdg-resources-english.txt" "gevm-resources-english.txt" "gdpm-resources-english.txt" "config.txt" "gevm.kb" "grlb.kb" "gdu.kb" "gduc.kb" "gdue.kb" "gdpm.kb" "geuc.kb" "gedp.kb" "grpe.kb" "gweb.kb" "brms.kb" "bpms.kb"
	"gdsm.kb" "gdsm-agent.kb" "gdsm-db.kb" "gdsm-jmail.kb" "gdsm-jms.kb" "gdsm-opc.kb" "gdsm-pi.kb" "gdsm-web.kb" "gdsm-snmp.kb")
  :make-not-read-only t
  :postinstall-code "replace_rootdir(\"g2i\"^\"kbs\", \"config.txt\");"
  :destination-directory "g2i/kbs")

(def-part g2i-data
  :source g2i
  :version :23r1
  :indep t
  :source-subdirectory data
  :destination-directory "g2i/data")

(def-part g2i-g2agent
    :source g2i
    :version :23r1
    :platforms ("nt" "win64")
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
  :version :23r1
  :indep t
  :source-subdirectory examples
  :source-filename ("gqsdemo.kb" "gevm-demo.kb" "gdu-demo.kb" "g2i-ui-demo.kb"
		    "g2i-ui-demo-resource-english.txt" "g2i-ui-demo.html" "gdpm-demo.kb"
		    "gedp-demo.kb" "grpe-demo.kb" "brms-demo.kb" "bpms-demo.kb" "gdsm-demo.kb")
  :shortcuts (g2i-gqsdemo-shortcut g2i-gevm-demo-shortcut g2i-gdu-demo-shortcut g2i-ui-demo-shortcut g2i-gedp-demo-shortcut g2i-gdpm-demo-shortcut g2i-brms-demo-shortcut g2i-bpms-demo-shortcut g2i-grpe-demo-shortcut g2i-gdsm-demo-shortcut g2i-server-console)
  :destination-directory "g2i/examples")

(def-shortcut g2i-server-console
    :folder-name g2-shortcut-folder-name
    :application-directory "g2"
    :target-name "http://localhost:8085/login"
    :subfolder-name "Examples"
    :subsubfolder-name "G2 Developers' Utilities"
    :application-display-name "G2 Server Console")

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
    :version :42r1
    :platforms ("nt" "win64")
    :destination-directory "sockman"
    :postinstall-code "replace_rootdir(\"sockman\"^\"bin\", \"SocketManager.bat\");"
    :shortcuts (sockman-shortcut sockman-demo-shortcut))

(def-part socket-manager-unix
    :source sockman
    :version :42r1
    :non-platforms ("nt" "win64")
    :postinstall-code "replace_rootdir(\"sockman\"^\"bin\", \"socketmanager\");"
    :destination-directory "sockman")

(def-part socket-manager-kbs
    :source sockman
    :version :42r1
    :source-subdirectory kbs
    :destination-directory "sockman/kbs"
    :platforms ("nt" "win64")
    :make-not-read-only t)

(def-part socket-manager-doc
    :source sockmandoc
    :version :42r0
    :indep t
    :destination-directory "doc/bridges/sockman"
    :shortcuts (sockman-doc-shortcut))

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

#+nil
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
;;;======= Begin JDBC =======
;;;
(def-component jdbc-component
  :print-name "G2 JDBC Bridge"
  :parts (jdbc-intel jdbc-unix
          jre-most jre-aix jre-hpia64 basic-jvl-parts)
  :include-in-contents (jdbc-intel jdbc-unix))

(def-part jdbc-intel
  :source g2jdbc
  :version :2015
  :platforms ("nt" "win64")
  :destination-directory jdbc
  :postinstall-code "replace_rootdir(\"jdbc\"^\"bin\", \"envvars.bat\");"
  :shortcuts (jdbc-shortcut))

(def-part jdbc-unix
  :source jdbc
  :version :2015
  :non-platforms ("nt" "win64")
  :destination-directory jdbc
  :postinstall-code "replace_rootdir(\"jdbc\"^\"bin\", \"set-envvars\");replace_rootdir(\"jdbc\"^\"bin\", \"run-g2jdbc.sh\");")

(def-part jdbckbs
    :source jdbc
    :version :2015
    :source-subdirectory kbs
    :destination-directory jdbc/kbs
    :source-filename ("g2-database.kb"))

(def-part jdbc-doc
  :source jdbcdoc
  :version :2015
  :indep t
  :destination-directory "doc/bridges/jdbc"
  :shortcuts (jdbc-doc-shortcut jdbc-doc-shortcut-html))

(def-shortcut jdbc-doc-shortcut
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JDBC User's Guide"
  :application-directory "doc/bridges/jdbc"
  :target-name "g2jdbcbridge.pdf")

#+nil
(def-shortcut jdbc-doc-shortcut-html
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation (HTML)"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JDBC User's Guide"
  :application-directory "doc/bridges/jdbc/html"
  :target-name "titlepag.htm")

(def-shortcut jdbc-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 JDBC Bridge"
    :application-directory "jdbc\\bin"
    :target-name "g2jdbc.bat")

(def-shortcut jdbc-demo-shortcut
    :parent startserver-shortcut
    :subfolder-name "Examples"
    :subsubfolder-name "JDBC"
    :application-display-name "JDBC Tutorial"
    :parameters "-kb ..\\jdbc\\examples\\jdbc-demo.kb")

;;;
;;;======= End JDBC =======
;;;
;;;======= Begin JMail =======
;;;
(def-component jmail-component
  :print-name "JMail"
  :parts (jmail-intel jmail-unix jmail-doc jre-most jre-aix jre-hpia64 basic-jvl-parts)
  :include-in-contents (jmail-intel jmail-unix))

(def-part jmail-intel
  :source jmail
  :version :23r1
  :platforms ("nt" "win64")
  :destination-directory jmail
  :postinstall-code "replace_rootdir(\"jmail\"^\"bin\", \"StartJMailBridge.bat\");"
  :shortcuts (jmail-shortcut jmail-demo-shortcut))


(def-part jmail-unix
  :source jmail
  :version :23r1
  :non-platforms ("nt" "win64")
  :destination-directory jmail
  :postinstall-code "replace_rootdir(\"jmail\"^\"bin\", \"startjmailbridge\");")

(def-part jmailkbs
  :source jmail
  :version :23r1
  :source-subdirectory kbs
  :destination-directory "jmail/kbs")

(def-part jmail-doc
  :source jmaildoc
  :version :23r0
  :indep t
  :destination-directory "doc/bridges/jmail"
  :shortcuts (jmail-doc-shortcut #+nil jmail-doc-shortcut-html))

(def-shortcut jmail-doc-shortcut
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JMail User's Guide"
  :application-directory "doc/bridges/jmail"
  :target-name "g2jmailbridge.pdf")

#+nil
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
  :parts (hla hla-linux)
  :optional true)

(def-part hla-linux
    :source hla
    :version 20r1
    :destination-directory hla
    :postinstall-code "replace_rootdir(\"hla\"^\"bin\", \"startHLADemo\");"
    :platforms ("linux" "linux64"))

(def-part hla
    :source hla
    :version 20r1
    :destination-directory hla
    :postinstall-code "replace_rootdir(\"hla\"^\"bin\", \"StartG2HLA.bat\");replace_rootdir(\"hla\"^\"examples\"^\"G2Demo_Federate\", \"StartG2Demo.bat\");replace_rootdir(\"hla\"^\"examples\"^\"G2HelloWorld_Federate\", \"StartG2HelloWorld.bat\");"
    :platforms ("nt" "win64")
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
  :version :23r0
  :platforms ("nt" "hpux" "hpia64" "linux" "linux64")
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

#+nil
(def-shortcut jms-doc-shortcut-html
  :folder-name g2-shortcut-folder-name
  :subfolder-name "Documentation (HTML)"
  :subsubfolder-name "Bridges"
  :application-display-name "G2 JMSLink User's Guide"
  :application-directory "doc/bridges/jms/html"
  :target-name "titlepag.htm")

(def-part jms-intel
  :source jms
  :version :23r1
  :platforms ("nt" "win64")
  :destination-directory jms
  :postinstall-code "replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-j2ee.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-jboss.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-FioranoMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-WebSphereMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-SonicMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-OpenJMS.bat\");"
  :shortcuts (jms-j2ee-shortcut jms-jboss-shortcut jms-FioranoMQ-shortcut jms-WebSphereMQ-shortcut jms-openjms-shortcut jms-demo-shortcut))

(def-part jms-linux
  :source jms
  :version :23r1
  :platforms ("linux" "linux64")
  :destination-directory jms
  :postinstall-code "replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-j2ee\");replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-jboss\");replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-openjms\");")

(def-part jms-hpux
  :source jms
  :version :23r1
  :platforms ("hpux" "hpia64")
  :destination-directory jms
  :postinstall-code "replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-jboss\");replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-openjms\");")

(def-part jmskbs
  :source jms
  :version :23r1
  :source-subdirectory kbs
  :destination-directory jms/kbs)

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
  :version :23r1
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
  :parts (jsnmp-intel jsnmp-unix jsnmp-linux jsnmp-g2i-modules jre-most basic-jvl-parts)
  :optional true
  :include-in-contents (jsnmp-intel jsnmp-unix))

(def-part jsnmp-intel
    :source g2snmpgn
    :version :40r0
    :platforms ("nt" "win64")
    :destination-directory jsnmp
    :postinstall-code "replace_rootdir(\"jsnmp\"^\"bin\", \"StartJsnmpBridge.bat\");"
    :shortcuts (jsnmp-shortcut))

(def-part jsnmp-unix
  :source g2snmpgn
  :version :40r0
  :platforms ("sparcsol" "hpux" "hpia64")
  :destination-directory jsnmp
  :postinstall-code "replace_rootdir(\"jsnmp\"^\"bin\", \"startjsnmpbridge.sh\");")

(def-part jsnmp-linux
  :source g2snmpgn
  :version :40r0
  :platforms ("linux" "linux64")
  :destination-directory jsnmp
  :postinstall-code "replace_rootdir(\"jsnmp\"^\"bin\", \"startjsnmpbridge\");")

(def-shortcut jsnmp-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "Java SNMP Bridge"
    :application-directory "jsnmp\\bin"
    :target-name "StartJsnmpBridge.bat")

(def-part jsnmp-g2i-modules
  :source g2i
  :version :23r1
  :indep t
  :source-subdirectory kbs
  :source-filename ("gmib.kb")
  :destination-directory "g2i/kbs")
;;;
;;;======= End JsnmpBridge =======
;;;


(def-part gw
  :version :2015
  :source gw
  :destination-directory gw)

(def-part gwkbs
  :version :2015
  :source gw
  :source-subdirectory kbs
  :source-filename ("gwex3.kb" "gwex2.kb" "gwex1.kb" "gwlow.kb")
  :destination-directory gw/kbs)

(def-part run-gw-template-batfile
    :platforms ("nt" "win64") 
    :version :2015
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
  :version :2015
  :source jvl
  :destination-directory javalink
  :postinstall-code "replace_rootdir(\"javalink\"^\"bin\", \"set-envvars\");"
  :non-platforms ("nt" "win64"))

(def-part jvl-intelnt
  :version :2015
  :source jvl
  :destination-directory javalink
  :postinstall-code "replace_rootdir(\"javalink\"^\"bin\", \"envvars.bat\"); replace_rootdir(\"javalink\"^\"bin\"^\"x64\", \"envvars.bat\");"
  :platforms ("nt" "win64")
  :shortcuts (jvl-interface-downloader
	      jvl-install-properties
	      jvl-bean-builder
	      jvl-example-readme
	      jvl-readme))

(def-part jvl-readme
    :source g2pkgreadme
    :version :2015
    :indep t 
    :source-filename "readme-javalink.html"
    :destination-directory "javalink")

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

(def-part jvl-classes
  :source jvl
  :version :2015
  :source-subdirectory classes
  :destination-directory javalink/classes)

(def-part jvl-com-gensym-properties-intelnt
  :version :2015
  :source jvl
  :source-subdirectory "bin"
  :source-filename ".com.gensym.properties"
  :destination-directory "javalink/classes"
  :platforms ("nt" "win64")
  :postinstall-code
  "FixupPropertiesFile(TARGETDIR^\"javalink\"^\"bin\", \".com.gensym.properties\", TARGETDIR^\"javalink\", \"classes\", \".com.gensym.properties\");")

(def-part jvlkbs
  :source jvl
  :version :2015
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
    :version :2015
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
  :version :2015
  :destination-directory corbalink
  :non-platforms ("alphaosf"))

;; ActiveXLink Parts:
(def-part axl
    :version :2015
    :source axl
    :destination-directory activexlink
    :platforms ("nt" "win64")
    :shortcuts (axldemo axlhtmldemo axlvbdemo axlvbdemoproj axlc++demo
			axlc++proj axlexceldemo axlvbnetdemo axlvbnetproj
			))

(def-part axl-g2com-dll
    :version :2015
    :source axl
    :source-subdirectory bin
    :source-filename "G2Com.dll"
    ;; :register true			; Active X Control
    :destination-directory activexlink/bin
    :platforms ("nt" "win64"))

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
    :target-name "VCppDemo_32bit.exe")

(def-shortcut axlc++proj
    :folder-name g2-shortcut-folder-name
    :application-display-name "C++ Demo Project"
    :subfolder-name "Examples"
    :subsubfolder-name "ActiveX Link"
    :application-directory "activexlink\\demos\\vcppdemo"
    :target-name "VCppDemo.sln")

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
    :version :2015
    :destination-directory doc/utilities/gdi
    :indep t
    :source-filename ("gdi.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory gdi)

(def-part g2utldoc-gms-pdf
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/gms
    :indep t
    :source-filename ("gms.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory gms)

(def-part g2utldoc-goldui-pdf
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/goldui
    :indep t
    :source-filename ("goldui.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory goldui)

(def-part g2utldoc-guideuserguide-pdf
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/guideuserguide
    :indep t
    :source-filename ("guideuserguide.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory guideuserguide)

(def-part g2utldoc-gdd-pdf
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/gdd
    :indep t
    :source-filename ("gdd.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory gdd)

(def-part g2utldoc-gfr-pdf
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/gfr
    :indep t
    :source-filename ("gfr.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory gfr)

(def-part g2utldoc-golddev-pdf
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/golddev
    :indep t
    :source-filename ("golddev.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory golddev)

(def-part g2utldoc-guideprocref-pdf
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/guideprocref
    :indep t
    :source-filename ("guideprocref.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory guideprocref)

(def-part g2utldoc-gxl-pdf
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/gxl
    :indep t
    :source-filename ("gxl.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory gxl)

(def-part g2utldoc-gdi-html
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/gdi/html
    :indep t
    :source-subdirectory gdi/html)

(def-part g2utldoc-gms-html
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/gms/html
    :indep t
    :source-subdirectory gms/html)

(def-part g2utldoc-goldui-html
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/goldui/html
    :indep t
    :source-subdirectory goldui/html)

(def-part g2utldoc-guideuserguide-html
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/guideuserguide/html
    :indep t
    :source-subdirectory guideuserguide/html)

(def-part g2utldoc-gdd-html
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/gdd/html
    :indep t
    :source-subdirectory gdd/html)

(def-part g2utldoc-gfr-html
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/gfr/html
    :indep t
    :source-subdirectory gfr/html)

(def-part g2utldoc-golddev-html
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/golddev/html
    :indep t
    :source-subdirectory golddev/html)

(def-part g2utldoc-guideprocref-html
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/guideprocref/html
    :indep t
    :source-subdirectory guideprocref/html)

(def-part g2utldoc-gxl-html
    :source g2utldoc
    :version :2015
    :destination-directory doc/utilities/gxl/html
    :indep t
    :source-subdirectory gxl/html)


(def-part g2idoc-gdsm-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gdsm
    :indep t
    :source-subdirectory gdsm
    :platforms ("nt" "win64")
    :source-filename ("gdsm.pdf"))

(def-part g2idoc-gdsm-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gdsm/html
    :indep t
    :source-subdirectory gdsm/html)

(def-part g2idoc-gdu-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gdu
    :indep t
    :source-subdirectory gdu
    :platforms ("nt" "win64")
    :source-filename ("gdu.pdf"))

(def-part g2idoc-gdu-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gdu/html
    :indep t
    :source-subdirectory gdu/html)

(def-part g2idoc-gerr-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gerr
    :indep t
    :source-subdirectory gerr
    :platforms ("nt" "win64")
    :source-filename ("gerr.pdf"))

(def-part g2idoc-gerr-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gerr/html
    :indep t
    :source-subdirectory gerr/html)

(def-part g2idoc-gevm-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gevm
    :indep t
    :source-subdirectory gevm
    :platforms ("nt" "win64")
    :source-filename ("gevm.pdf"))

(def-part g2idoc-gevm-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gevm/html
    :indep t
    :source-subdirectory gevm/html)

(def-part g2idoc-grlb-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/grlb
    :indep t
    :source-subdirectory grlb
    :platforms ("nt" "win64")
    :source-filename ("grlb.pdf"))

(def-part g2idoc-grlb-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/grlb/html
    :indep t
    :platforms ("nt" "win64")
    :source-subdirectory grlb/html)

(def-part g2idoc-grtl-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/grtl
    :indep t
    :source-subdirectory grtl
    :platforms ("nt" "win64")
    :source-filename ("grtl.pdf"))

(def-part g2idoc-grtl-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/grtl/html
    :indep t
    :source-subdirectory grtl/html)

(def-part g2idoc-gdpm-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gdpm
    :indep t
    :source-subdirectory gdpm
    :platforms ("nt" "win64")
    :source-filename ("gdpm.pdf"))

(def-part g2idoc-gdpm-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gdpm/html
    :indep t
    :source-subdirectory gdpm/html)

(def-part g2idoc-grpe-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/grpe
    :indep t
    :source-subdirectory grpe
    :platforms ("nt" "win64")
    :source-filename ("grpe.pdf"))

(def-part g2idoc-grpe-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/grpe/html
    :indep t
    :source-subdirectory grpe/html)

(def-part g2idoc-brms-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/brms
    :indep t
    :source-subdirectory brms
    :platforms ("nt" "win64")
    :source-filename ("brms.pdf"))

(def-part g2idoc-brms-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/brms/html
    :indep t
    :source-subdirectory brms/html)

(def-part g2idoc-bpms-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/bpms
    :indep t
    :source-subdirectory bpms
    :platforms ("nt" "win64")
    :source-filename ("bpms.pdf"))

(def-part g2idoc-bpms-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/bpms/html
    :indep t
    :source-subdirectory bpms/html)

(def-part g2idoc-gedp-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gedp
    :indep t
    :source-subdirectory gedp
    :platforms ("nt" "win64")
    :source-filename ("gedp.pdf"))

(def-part g2idoc-gedp-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gedp/html
    :indep t
    :source-subdirectory gedp/html)

(def-part g2idoc-gweb-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gweb
    :indep t
    :source-subdirectory gweb
    :platforms ("nt" "win64")
    :source-filename ("gweb.pdf"))

(def-part g2idoc-gweb-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/gweb/html
    :indep t
    :source-subdirectory gweb/html)

(def-part g2idoc-geuc-pdf
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/geuc
    :indep t
    :source-subdirectory geuc
    :platforms ("nt" "win64")
    :source-filename ("geuc.pdf"))

(def-part g2idoc-geuc-html
    :source g2idoc
    :version :23r0
    :destination-directory doc/g2i/geuc/html
    :indep t
    :source-subdirectory geuc/html)

(def-part protoolsdoc
    :version :2015
    :destination-directory doc/utilities/g2protools
    :source-subdirectory g2protools
    :platforms ("nt" "win64")
    :indep t
    :source-filename ("g2protools.pdf"))

(def-part protoolsdoc-html
    :source protoolsdoc
    :version :2015
    :destination-directory doc/utilities/g2protools/html
    :indep t
    :source-subdirectory g2protools/html)

(def-part gdadoc-api-pdf
    :source gdadoc
    :version :51r0
    :destination-directory doc/gda/gdaapi
    :source-filename ("gdaapi.pdf")
    :indep t
    :source-subdirectory gda/gdaapi)

(def-part gdadoc-ug-pdf
    :source gdadoc
    :version :51r0
    :destination-directory doc/gda/gdaugrm
    :source-filename ("gdarefman.pdf" "gdaug.pdf")
    :indep t
    :source-subdirectory gda/gdaugrm)

#+nil
(def-part gdadoc-api-html
    :source gdadoc
    :version :51r0
    :destination-directory doc/gda/gdaapi/html
    :indep t
    :source-subdirectory gda/gdaapi/html)

#+nil
(def-part gdadoc-ug-html
    :source gdadoc
    :version :51r0
    :destination-directory doc/gda/gdaugrm/html
    :indep t
    :source-subdirectory gda/gdaugrm/html)

(def-part snmpdoc-pdf
    :source snmpdoc
    :version :40r1-JH03
    :source-subdirectory snmp
    :destination-directory doc/bridges/snmp
    :source-filename ("g2snmp.pdf")
    :shortcuts (snmpdoc-pdf)
    :platforms ("nt" "win64")
    :indep t)

#+nil
(def-part snmpdoc-html
    :source snmpdoc
    :version :40r1-JH03
    :destination-directory doc/bridges/snmp/html
    :source-subdirectory snmp/html
    :shortcuts (snmpdoc-html)
    :indep t)

(def-part weblinkdoc
    :version :2015
    :destination-directory doc/bridges/weblink
    :indep t
    :source-subdirectory weblink
    :source-filename ("g2weblink.pdf")
    :platforms ("nt" "win64")
    :shortcuts (g2-weblink-users-guide #+nil g2-weblink-users-guide-html))

(def-part weblinkdoc-html
    :source weblinkdoc
    :version :2015
    :destination-directory doc/bridges/weblink/html
    :indep t :source-subdirectory weblink/html)

(def-part g2classicrn
    :version :2015
;    :source-subdirectory g2relnotes
    :source-filename "g2relnotes.pdf"
    :indep t
    :destination-directory doc)

#+nil
(def-part g2classicrn-html
    :source g2classicrn
    :version :2015
    :source-subdirectory html
    :destination-directory doc/g2/g2relnotes/html
    :indep t
    :destination-directory doc)

;; reference manual

(def-part g2doc-g2refman-pdf
    :source g2doc
    :version :2015
    :destination-directory doc/g2/g2refman
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
		#+nil g2-release-notes
		g2-reference-manual
		 g2-reference-card
		 g2-sysproc-refcard
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
		 g2-opcclient-users-guide
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
    :version :2015
    :destination-directory doc/g2/g2tutorials
    :indep t
    :source-filename ("g2tutorials.pdf"))

(def-part g2doc-g2gateway-pdf
    :source g2doc
    :version :2015
    :destination-directory doc/g2/g2gateway
    ;; :source-subdirectory g2gateway
    :indep t
    :source-filename ("g2gateway.pdf"))

(def-part g2doc-g2classref-pdf
    :source g2doc
    :version :2015
    :destination-directory doc/g2/g2classref
    :indep t
    :source-filename ("g2classref.pdf"))

(def-part g2doc-telewindows-pdf
    :source g2doc
    :version :2015
    :destination-directory doc/g2/telewindows
    :indep t
    :source-filename ("telewindows.pdf"))

(def-part g2doc-g2sysprocs-pdf
    :source g2doc
    :version :2015
    :destination-directory doc/g2/g2sysprocs
    :indep t
    :source-filename ("g2sysprocs.pdf"))

(def-part g2doc-g2langrefcard-pdf
    :source g2doc
    :version :2015
    :destination-directory doc/g2/g2langrefcard
    :indep t
    :source-filename ("g2langrefcard.pdf"))

(def-part g2doc-g2sysprocrefcard-pdf
    :source g2doc
    :version :2015
    :destination-directory doc/g2/g2sysprocsrefcard
    :indep t
    :source-filename ("g2sysprocsrefcard.pdf"))

(def-part g2doc-g2devguide-pdf
    :source g2doc
    :version :2015
    :destination-directory doc/g2/g2devguide
    :indep t
    :source-filename ("g2devguide.pdf"))

;; Documentation for bridges - Javalink, ActiveXLink, Corbalink, Oracle, Sybase, Opcclient, ODBC:

(def-part jvldoc-javalink-pdf
    :source jvldoc
    :version :2015
    :destination-directory doc/javalink/docs/guides/g2javalink
    :indep t
    :source-filename ("g2javalink.pdf")
    :source-subdirectory docs/guides/g2javalink
    :platforms ("nt" "win64")
    :shortcuts ( ;; Javalink
		 g2-download-interfaces-guide #+nil g2-download-interfaces-guide-html
		 g2-beanbuilder-guide #+nil g2-beanbuilder-guide-html
		 g2-javalink-guide #+nil g2-javalink-guide-html
		 )
    )

(def-part jvldoc-di-pdf
    :source jvldoc
    :version :2015
    :destination-directory doc/javalink/docs/guides/g2downloadinterfaces
    :indep t
    :source-filename ("g2downloadinterfaces.pdf")
    :source-subdirectory docs/guides/g2downloadinterfaces
    :platforms ("nt" "win64")
    )

(def-part jvldoc-bb-pdf
    :source jvldoc
    :version :2015
    :destination-directory doc/javalink/docs/guides/g2beanbuilder
    :indep t
    :source-filename ("g2beanbuilder.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory docs/guides/g2beanbuilder
    )

(def-part jvldoc-javalink-html
    :source jvldoc
    :version :2015
    :destination-directory doc/javalink/docs/guides/g2javalink/html
    :indep t
    :source-subdirectory docs/guides/g2javalink/html
    )

(def-part jvldoc-di-html
    :source jvldoc
    :version :2015
    :destination-directory doc/javalink/docs/guides/g2downloadinterfaces/html
    :indep t
    :source-subdirectory docs/guides/g2downloadinterfaces/html
    )

(def-part jvldoc-bb-html
    :source jvldoc
    :version :2015
    :destination-directory doc/javalink/docs/guides/g2beanbuilder/html
    :indep t
    :source-subdirectory docs/guides/g2beanbuilder/html
    )

(def-part axldoc
    :version :2015
    :destination-directory doc/bridges/activexlink
    :platforms ("nt" "win64")
    :indep t :source-filename "g2activexlink.pdf"
    :source-subdirectory activexlink
    :shortcuts (g2-activexlink-users-guide #+nil g2-activexlink-users-guide-html))

(def-part axldoc-html
    :source axldoc
    :version :2015
    :destination-directory doc/bridges/activexlink/html
    :platforms ("nt" "win64")
    :indep t
    :source-subdirectory activexlink/html)

(def-part corbalinkdoc
    :version :2015
    :destination-directory doc/bridges/corbalink
    :indep t
    :source-filename ("g2corbalink.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory corbalink)

(def-part g2oradoc
    :version :2015
    :destination-directory doc/bridges/oracle
    :indep t :source-filename ("g2oraclebridge.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory oracle)

(def-part g2sybdoc
    :version :2015
    :destination-directory doc/bridges/sybase
    :indep t
    :source-filename ("g2sybasebridge.pdf")
    :platforms ("nt" "win64")
    :source-subdirectory sybase)

(def-part opcclientdoc
    :source opclinkdoc
    :version :2015-JG18
    :destination-directory doc/bridges/opcclient
    :indep t
    :source-filename ("g2opcclient.pdf")
    :source-subdirectory opcclient
    :platforms ("nt" "win64")
    )

(def-part g2odbcdoc
    :version :2015
    :destination-directory doc/bridges/odbc
    :indep t
    :source-filename ("g2odbcbridge.pdf")
    :source-subdirectory odbc
    :platforms ("nt" "win64")
    )

(def-part g2pidoc
    :version :2015
    :destination-directory doc/bridges/pi
    :source-subdirectory pi
    :indep t
    :source-filename ("g2pibridge.pdf")
    :platforms ("nt" "win64")
    )

(def-part g2dbdoc
    :version :2015
    :destination-directory doc/bridges/db
    :source-subdirectory db
    :platforms ("nt" "win64")
    :indep t :source-filename ("g2databasebridge.pdf"))

(def-part protools
    :version :2015
    :source protools
    :destination-directory protools/kbs
    :source-filename ("protools.kb" "ptroot.kb")
    :indep t)

(def-part profiler
    :version :2015
    :source protools
    :source-filename ("profiler.kb" "profroot.kb")
    :destination-directory g2/kbs/utils
    :indep t)

(def-part profiler-demo
    :version :2015
    :source protools
    :source-filename ("profile-demo.kb")
    :destination-directory g2/kbs/samples
    :indep t)

(def-part g2-readme
    :source g2pkgreadme
    :version :2015
    :source-filename "readme-g2.html"
    :indep t)

(def-part opcclient
    :source opclink
    :platforms ("nt" "win64") 
    :version :2015
    :destination-directory opcclient
    :postinstall-code "replace_rootdir(\"opcclient\", \"run-g2opc.bat\");"
    :shortcuts (opcclient-shortcut))

(def-part opcclientkbs
    :source opclink
    :version :2015
    :destination-directory "opcclient/kbs"
    :source-subdirectory "kbs"
    :platforms ("nt" "win64")
    :indep t)

(def-shortcut opcclient-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 OPC Client Bridge"
    :application-directory "opcclient"
    :target-name "run-g2opc.bat")

;;We also are including the old OPCLINK in addition to the new rewrite.
;;No shortcuts here though.
(def-part opclink
    :source opclink
    :platforms ("nt" "win64") 
    :version :30r2
    :destination-directory opclink
    :postinstall-code "replace_rootdir(\"opclink\", \"run-g2opc.bat\");")

(def-part g2pi
    :version :2015
    :destination-directory pi)

(def-part pikbs
    :source g2pi
    :version :2015
    :source-subdirectory kbs
    :source-filename ("g2-pi.kb")
    :destination-directory pi/kbs
    :platforms ("nt" "win64")
    :indep t)

(def-part run-g2-pi-template-batfile
    :platforms ("nt" "win64") 
    :version :2015
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
    :version :2015
    :source g2sybase
    :destination-directory sybase
    :non-platforms ("linux" "linux64"))

(def-part sybasekbs
    :version :2015
    :source g2sybase
    :source-subdirectory kbs
    :source-filename ("g2-database.kb")
    :destination-directory sybase/kbs
    :platforms ("nt" "win64")
    :indep t)

(def-part run-g2-sybase11-template-batfile
    :platforms ("nt" "win64") 
    :source g2sybase
    :source-subdirectory bin
    :version :2015
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
    :platforms ("nt" "win64") 
    :source g2sybase
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-syb125.bat"
    :destination-directory sybase/bin
    :postinstall-code "replace_rootdir(\"sybase\"^\"bin\", \"run-g2-syb125.bat\");"
    :shortcuts (sybase125-shortcut))

(def-part run-g2-sybase150-template-batfile
    :platforms ("nt" "win64") 
    :source g2sybase
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-syb150.bat"
    :destination-directory sybase/bin
    :postinstall-code "replace_rootdir(\"sybase\"^\"bin\", \"run-g2-syb150.bat\");"
    :shortcuts (sybase150-shortcut))

(def-part run-g2-sybase150-x64-template-batfile
    :platforms ("win64") 
    :source g2sybase
    :source-subdirectory "bin/x64"
    :version :2015
    :source-filename "run-g2-syb150.bat"
    :destination-directory sybase/bin
    :postinstall-code "replace_rootdir(\"sybase\"^\"bin\"^\"x64\", \"run-g2-syb150.bat\");"
    :shortcuts (sybase150-x64-shortcut))

(def-shortcut sybase125-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Sybase 12.5 Bridge"
    :application-directory "sybase\\bin"
    :target-name "run-g2-syb125.bat")

(def-shortcut sybase150-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Sybase 15.7 Bridge"
    :application-directory "sybase\\bin"
    :target-name "run-g2-syb150.bat")

(def-shortcut sybase150-x64-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 Sybase 15.7 Bridge (64-bit)"
    :application-directory "sybase\\bin\\x64"
    :target-name "run-g2-syb150.bat")

(def-part ODBCbridge
    :version :2015
    :source g2odbc
    :destination-directory odbc)

(def-part run-g2-odbc-template-batfile
    :platforms ("nt" "win64") 
    :source g2odbc
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-odbc.bat"
    :destination-directory odbc/bin
    :postinstall-code "replace_rootdir(\"odbc\"^\"bin\", \"run-g2-odbc.bat\");"
    :shortcuts (odbc-shortcut))

(def-part run-g2-odbc-x64-template-batfile
    :platforms ("win64") 
    :source g2odbc
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-odbc.bat"
    :destination-directory odbc/bin/x64
    :postinstall-code "replace_rootdir(\"odbc\"^\"bin\"^\"x64\", \"run-g2-odbc.bat\");"
    :shortcuts (odbc-x64-shortcut))

(def-part run-g2-odbc-sh-file
    :platforms ("linux" "linux64") 
    :source g2odbc
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-odbc"
    :destination-directory odbc/bin
    :postinstall-code "replace_rootdir(\"odbc\", \"bin\", \"run-g2-odbc\");")

(def-shortcut odbc-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 ODBC Bridge"
    :application-directory "odbc\\bin"
    :target-name "run-g2-odbc.bat")

(def-shortcut odbc-x64-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 ODBC Bridge (64-bit)"
    :application-directory "odbc\\bin\\x64"
    :target-name "run-g2-odbc.bat")

(def-part odbckbs
    :version :2015
    :source g2odbc
    :source-subdirectory kbs
    :source-filename ("g2-database.kb")
    :destination-directory odbc/kbs)

(def-part odbckbsunicode
    :version :2015
    :source g2odbc_unicode
    :source-subdirectory kbs
    :source-filename ("g2-database.kb")
    :platforms ("nt" "win64")
    :destination-directory odbc_unicode/kbs)

(def-part oraclebridge
    :version :2015
    :source g2oracle
    :platforms ("nt" "win64")
    :destination-directory "oracle")

(def-part oraclebin
    :version :2015
    :source g2oracle
    :source-subdirectory bin
    :destination-directory oracle/bin)

(def-part oraclekbs
    :version :2015
    :source g2oracle
    :source-subdirectory kbs
    :source-filename ("g2-database.kb")
    :destination-directory oracle/kbs)

(def-part run-g2-ora7-template-batfile
    :platforms ("nt" "win64") 
    :source g2oracle
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-ora7.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora7.bat\");"
    :shortcuts (ora7-shortcut))

(def-part run-g2-ora80-template-batfile
    :platforms ("nt" "win64") 
    :source g2oracle
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-ora80.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora80.bat\");"
    :shortcuts (ora80-shortcut))

(def-part run-g2-ora81-template-batfile
    :platforms ("nt" "win64") 
    :source g2oracle
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-ora81.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora81.bat\");"
    :shortcuts (ora81-shortcut))

(def-part run-g2-ora90-template-batfile
    :platforms ("nt" "win64") 
    :source g2oracle
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-ora90.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora90.bat\");"
    :shortcuts (ora90-shortcut))

(def-part run-g2-ora92-template-batfile
    :platforms ("nt" "win64") 
    :source g2oracle
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-ora92.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora92.bat\");"
    :shortcuts (ora92-shortcut))

(def-part run-g2-ora7-template-batfile
    :platforms ("nt" "win64") 
    :source g2oracle
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-ora7.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora7.bat\");"
    :shortcuts (ora7-shortcut))

(def-part run-g2-ora10-template-batfile
    :platforms ("nt" "win64") 
    :source g2oracle
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-ora10.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora10.bat\");"
    :shortcuts (ora10-shortcut))

(def-part run-g2-ora10-x64-template-batfile
    :platforms ("win64")
    :source g2oracle
    :source-subdirectory "bin/x64"
    :version :2015
    :source-filename "run-g2-ora10.bat"
    :destination-directory oracle/bin/x64
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\"^\"x64\", \"run-g2-ora10.bat\");"
    :shortcuts (ora10-x64-shortcut))

(def-part run-g2-ora11-template-batfile
    :platforms ("nt" "win64") 
    :source g2oracle
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-ora11.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora11.bat\");"
    :shortcuts (ora11-shortcut))

(def-part run-g2-ora11-x64-template-batfile
    :platforms ("win64")
    :source g2oracle
    :source-subdirectory "bin/x64"
    :version :2015
    :source-filename "run-g2-ora11.bat"
    :destination-directory oracle/bin/x64
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\"^\"x64\", \"run-g2-ora11.bat\");"
    :shortcuts (ora11-x64-shortcut))

(def-part run-g2-ora12-template-batfile
    :platforms ("nt" "win64") 
    :source g2oracle
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-ora12.bat"
    :destination-directory oracle/bin
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\", \"run-g2-ora12.bat\");"
    :shortcuts (ora12-shortcut))

(def-part run-g2-ora12-x64-template-batfile
    :platforms ("win64")
    :source g2oracle
    :source-subdirectory "bin/x64"
    :version :2015
    :source-filename "run-g2-ora12.bat"
    :destination-directory oracle/bin/x64
    :postinstall-code "replace_rootdir(\"oracle\"^\"bin\"^\"x64\", \"run-g2-ora12.bat\");"
    :shortcuts (ora12-x64-shortcut))

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

(def-shortcut ora10-x64-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 10 Bridge (64-bit)"
    :application-directory "oracle\\bin\\x64"
    :target-name "run-g2-ora10.bat")

(def-shortcut ora11-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 11 Bridge"
    :application-directory "oracle\\bin"
    :target-name "run-g2-ora11.bat")

(def-shortcut ora11-x64-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 11 Bridge (64-bit)"
    :application-directory "oracle\\bin\\x64"
    :target-name "run-g2-ora11.bat")

(def-shortcut ora12-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 12 Bridge"
    :application-directory "oracle\\bin"
    :target-name "run-g2-ora12.bat")

(def-shortcut ora12-x64-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "G2 Oracle"
    :application-display-name "G2 Oracle 12 Bridge (64-bit)"
    :application-directory "oracle\\bin\\x64"
    :target-name "run-g2-ora12.bat")

(def-part odbcunicodebridge
    :version :2015
    :source g2odbc_unicode
    :destination-directory odbc_unicode
    :platforms ("nt" "win64"))

(def-part run-g2-odbc-unicode-template-batfile
    :source g2odbc_unicode
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-odbc-unicode.bat"
    :destination-directory odbc_unicode/bin
    :platforms ("nt" "win64")
    :postinstall-code "replace_rootdir(\"odbc_unicode\"^\"bin\", \"run-g2-odbc-unicode.bat\");"
    :shortcuts (odbc-unicode-shortcut))

(def-part run-g2-odbc-unicode-x64-template-batfile
    :source g2odbc_unicode
    :source-subdirectory bin
    :version :2015
    :source-filename "run-g2-odbc-unicode.bat"
    :destination-directory odbc_unicode/bin/x64
    :platforms ("win64")
    :postinstall-code " replace_rootdir(\"odbc_unicode\"^\"bin\"^\"x64\", \"run-g2-odbc-unicode.bat\");"
    :shortcuts (odbc-unicode-x64-shortcut))

(def-shortcut odbc-unicode-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 ODBC UNICODE Bridge"
    :application-directory "odbc_unicode\\bin"
    :target-name "run-g2-odbc-unicode.bat")

(def-shortcut odbc-unicode-x64-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "G2 ODBC UNICODE Bridge (64-bit)"
    :application-directory "odbc_unicode\\bin\\x64"
    :target-name "run-g2-odbc-unicode.bat")

;;;Unfortunately in the version on the java run-time environment that is
;;;available on aix and alphaosf are not the same as the version for most of the
;;;other platforms.  So we are forced to have separate parts for the JRE.  This
;;;means that any other components which wish to include jre separately (jmail,
;;;jms, sockman) need to know which version(s) they will require.

(def-component jre
    :print-name "Java Runtime Environment"
    :parts (jre-most jre-aix jre-alphaosf jre-hpia64))

(def-part jre-most
    :version :16r45
    :source "jre"
    :platforms ("nt" "sparcsol" "hpux" "linux" "linux64")
    :destination-directory "jre")

(def-part jre-hpia64
    :version :14r2_09
    :source "jre"
    :platforms ("hpia64")
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
  :parts ( rethink-client-binaries rethink-readme rethink-online-server-binaries rethink-online-kbs images rethink-online-examples log-part rethink-resources  rethink-reports rethink-databases rethink-documentation rethink-linux-sh)
  :optional true
  :include-in-contents (rethink-online-kbs))

(def-part rethink-client-binaries
    :version :51r1
    :source-filename ("ReThink.ico")
    :destination-directory "rethink/bin"
    :source "rethink"
    :indep t
    :platforms ("nt" "win64")
    :source-subdirectory "bin")

(def-part rethink-linux-sh
    :version :51r1
    :source-filename ("startReThink" "startAeroModel" "startOrderfulModel" "startChapter3Model" "start4.0OnlineExamples" "start4.0Examples")
    :destination-directory "rethink/bin"
    :source "rethink"
    :indep t
    :platforms ("linux" "linux64")
    :postinstall-code "replace_rootdir(\"rethink\"^\"bin\", \"startReThink\");replace_rootdir(\"rethink\"^\"bin\", \"startAeroModel\");replace_rootdir(\"rethink\"^\"bin\", \"startOrderfulModel\");replace_rootdir(\"rethink\"^\"bin\", \"startChapter3Model\");replace_rootdir(\"rethink\"^\"bin\", \"start4.0Examples\");replace_rootdir(\"rethink\"^\"bin\", \"start4.0OnlineExamples\");"
    :source-subdirectory "bin")

(def-part log-part
  :version :51r1
  :destination-directory "rethink/logs"
  :source-subdirectory "logs"
  :source "rethink"
  :indep t)

(def-part archives-part
  :version :51r1
  :destination-directory "rethink/archives"
  :source-subdirectory "archives"
  :source "rethink"
  :indep t)

(def-part rethink-resources
  :version :51r1
  :destination-directory "rethink/resources"
  :source-subdirectory "resources"
  :source "rethink"
  :indep t)

(def-part rethink-online-kbs
    :version :51r1
    :destination-directory "rethink/kbs"
    :source-subdirectory "kbs"
    :source-filename ("rethink.kb" "rethink-online.kb" "rethink-online-core.kb" "rethink-core.kb" "bpr.kb" "bprui.kb" "customiz.kb" "methods.kb" "menus.kb" "methods-online.kb") 
    :source "rethink"
    :indep t
;;;    :shortcuts (rethink-online-server-shortcut)
)

(def-part rethink-online-examples
  :version :51r1
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
    :version :51r1
    :destination-directory "rethink/kbs/images"
    :source-subdirectory "kbs/images"
    :source "rethink"
    :indep t)

(def-part rethink-online-server-binaries
    :version :51r1
    :source-filename ("ReThink.ico")
    :destination-directory "rethink/bin"
    :source "rethink"
    :indep t
    :source-subdirectory "bin"
    :platforms ("nt" "win64")
    :shortcuts (rethink-online-server-shortcut))

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
    :version :51r1
    :destination-directory "rethink/data"
    :source-subdirectory "data"
    :source-filename ("ReThink-Summary-Reports.xls")
    :source "rethink"
    :indep t
;;;    :platforms ("nt" "win64")
    :shortcuts (rethink-default-summary-reports))

(def-shortcut rethink-default-summary-reports
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "ReThink Default Summary Reports"
    :application-directory "rethink/data"
    :target-name "ReThink-Summary-Reports.xls")

(def-part rethink-databases
    :version :51r1
    :destination-directory "rethink/data"
    :source-subdirectory "data"
    :source-filename ("orders.mdb")
    :source "rethink"
    :indep t)

(def-part rethink-readme
    :source g2pkgreadme
    :version :2015
    :source-filename "readme-rethink.html"
    :destination-directory "doc/rethink"
    :indep t
    :shortcuts (rethink-readme-shortcut))

(def-shortcut rethink-readme-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 ReThink"
    :application-display-name "Readme for G2 ReThink"
    :application-directory "doc/rethink"
    :target-name "readme-rethink.html")

(def-part rethink-documentation
    :version :51r0
    :destination-directory "doc/rethink"
    :source rethinkdoc
    :indep t
    :shortcuts (rethink-getting-started-documentation rethink-documentation-user rethink-documentation-customization))

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
    :application-display-name "ReThink User's Guide"
    :application-directory "doc/rethink"
    :target-name "ReThinkUsersGuide.pdf")

(def-shortcut rethink-documentation-customization
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 ReThink"
    :application-display-name "Customizing ReThink User's Guide"
    :application-directory "doc/rethink"
    :target-name "CustomizingReThinkUsersGuide.pdf")


;;; ESCOR

(def-component ESCOR
  :print-name "G2 e-SCOR"
  :parts (escor-client-binaries escor-sh-file escor-xls-reports escor-kbs escor-server-binaries escor-images escor-examples   escor-documentation escor-readme escor-log-part )
  :optional true
  :include-in-contents (escor-kbs))


(def-part escor-client-binaries
    :version :51r1
    :source-filename ("e-SCOR.ico") ;;"StartClient.bat" -- Doesn't seem to exist.
    :destination-directory "escor/bin"
    :source "escor"
    :source-subdirectory "bin"
    :platforms ("nt" "win64")
;;;    :shortcuts (escor-client-shortcut)
;;;    :environment-variables (ESCOR_RETHINK_HOME)   
;;;    :postinstall-code "replace_rootdir(\"escor\"^\"bin\", \"StartClient.bat\");"
    )

(def-part escor-sh-file
    :version :51r1
    :source-filename ("startescor" "startACMETutorial" "startEscorExamples" "startSimplestTutorial" "startVMITutorial")
    :destination-directory "escor/bin"
    :source "escor"
    :source-subdirectory "bin"
    :postinstall-code "replace_rootdir(\"escor\"^\"bin\", \"startescor\");replace_rootdir(\"escor\"^\"bin\", \"startACMETutorial\");replace_rootdir(\"escor\"^\"bin\", \"startEscorExamples\");replace_rootdir(\"escor\"^\"bin\", \"startSimplestTutorial\");replace_rootdir(\"escor\"^\"bin\", \"startVMITutorial\");"
    :platforms ("linux" "linux64"))

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
    :source-filename ("readme-escor.html")
    :source "g2pkgreadme"
    :version :2015
    :indep t 
    :destination-directory "doc/escor"
    :platforms ("nt" "win64")
    :print-name "e-SCOR README file"
    :shortcuts (escor-readme-shortcut))

(def-shortcut escor-readme-shortcut
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 e-SCOR"
    :application-display-name "Readme for G2 e-SCOR"
    :application-directory "doc/escor"
    :target-name "readme-escor.html")


(def-part escor-xls-reports
    :version :51r1
    :source "escor"
    :platforms ("nt" "win64")
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
  :version :51r1
  :platforms ("nt" "win64")
  :destination-directory "escor/logs"
  :source-subdirectory "logs"
  :source "escor")

(def-part escor-archives-part
  :version :51r1
  :platforms ("nt" "win64")
  :destination-directory "escor/archives"
  :source-subdirectory "archives"
  :source "escor")

(def-part escor-resources
  :version :51r1
  :platforms ("nt" "win64")
  :destination-directory "escor/resources"
  :source-subdirectory "resources"
  :source "escor")

(def-part escor-kbs
    :version :51r1
    :destination-directory "escor/kbs"
    :source-subdirectory "kbs"
    :source-filename ("escor-customiz.kb" "e-scor.kb") 
    :source "escor")

(def-part escor-examples
  :version :51r1
  :destination-directory "escor/examples"
  :source-subdirectory "examples"
  :source-filename ("escor-demo.kb" "escor-tutorial-acme.kb" "escor-tutorial-vmi.kb" "escor-tutorial-simplest.kb")
  :source "escor"
  :shortcuts (demo-tutorial acme-tutorial vmi-tutorial))

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
    :version :51r1
    :destination-directory "escor/kbs/images"
    :source-subdirectory "kbs/images"
    :source "escor")

(def-part escor-server-binaries
    :version :51r1
    :platforms ("nt" "win64")
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
    :version :51r0
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
    :target-name "e-SCORQuickReference.pdf")

(def-shortcut escor-documentation-user
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "e-SCOR User's Guide"
    :application-directory "doc/escor"
    :target-name "e-SCORUsersGuide.pdf")

(def-shortcut escor-tutorial
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 e-SCOR"
    :application-display-name "e-SCOR Tutorial"
    :application-directory "doc/escor"
    :target-name "e-SCORTutorials.pdf")

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
  :parts (nolstudio-data nolstudio-math-library nolstudio-window-classic-dll nolstudio-deploy-library
	  nolstudio-gui nolstudio-batch nolstudio-sh-file nolstudio-online-batch 
	  nolstudio-examples nolstudio-deploy-misc nol-classic-kb nol-classic-nt nol-classic-win64
	  nol-classic-linux gnne-demo gnne-demo-config nol-total-demo nol-bakery-demo
	  nol-bleach-demo nol-classic-gnne nol-g2i-modules nol-classic-documentation nol-readme
	  nolstudio-window-misc nolstudio-ActiveX-control)
  :optional true
  :include-in-contents (gnne-demo))

(def-part nolstudio-data-eva
    :version :51r1
    :print-name "G2 NOL Studio Data Evaluation"
    :source nols
    :platforms ("nt" "win64")
    :source-filename "NolStudioDataEva.jar"
    :destination-directory nolstudio
    :destination-filename NolStudioData.jar)

(def-part nolstudio-data
    :version :51r1 
    :print-name "G2 NOL Studio Data"
    :source nols
    :source-filename "NolStudioData.jar"
    :destination-directory nolstudio)

(def-environment-variable nolstudio_home
    :value "<TARGETDIR>")

(def-environment-variable nolstudio-jre
    :variable "PATH"
    :append-or-merge merge
    :value "<TARGETDIR>\\\\jre\\\\bin;<TARGETDIR>\\\\jre\\\\bin\\\\client")

(def-part nolstudio-math-library
    :version :51r1 
    :print-name "G2 NOL Studio Math Library"
    :source nols
    :source-filename "NolStudioMath.jar"
    :destination-directory nolstudio)

(def-part nolstudio-core-misc-demolicense
    :version :51r1 
    :print-name "G2 NOL Studio Core Misc"
    :source nols
    :platforms ("nt" "win64")
    :source-filename ("demolicense.txt" "known-bugs.txt")
    :destination-directory nolstudio)

(def-part nolstudio-gui
    :version :51r1 
    :source-filename "NolStudioGUI.jar"
    :source nols
    :destination-directory nolstudio
    :print-name "G2 NOL Studio GUI")

(def-part nolstudio-gui-misc
    :version :51r1 
    :source nols
    :platforms ("nt" "win64")
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
    :version :51r1 
    :source nols
    :platforms ("nt" "win64")
    :destination-directory nolstudio/bin
    :source-filename ("nolstudio.bat")
	:postinstall-code "replace_rootdir(\"nolstudio\"^\"bin\", \"nolstudio.bat\");"
	:shortcuts (nolstudio-batch-file))

(def-part nolstudio-sh-file
    :version :51r1 
    :source nols
    :platforms ("linux" "linux64")
    :destination-directory nolstudio
    :source-filename ("nolstudio"))

(def-shortcut nolstudio-batch-file
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 NeurOn-Line"
    :application-display-name "G2 NeurOn-Line Studio"
    :application-directory nolstudio/bin
    :target-name nolstudio.bat
	:icon-file "../../nol/bin/nol.ico"
	:icon-index 0
    :run-style minimized)

(def-part nolstudio-examples
    :version :51r1 
    :source nols
    :platforms ("nt" "win64")
    :source-subdirectory projects
    :destination-directory nolstudio/projects)

(def-part nolstudio-window-misc
    :source nols
    :platforms ("nt" "win64")
    :version :51r1 
    :source-filename ("RegisterControls.bat" "UnRegisterControls.bat")
    :platforms ("nt" "win64")
    :destination-directory nolstudio/bin)

(def-part nolstudio-ActiveX-control
    :source nols
    :platforms ("nt" "win64")
    :version :51r1 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "NolOnline.dll"
    :platforms ("nt" "win64")
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
    :platforms ("nt" "win64")
    :version :51r1 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "jnol.dll"
    :platforms ("nt" "win64"))

(def-part nolstudio-deploy-library
    :source nols
    :version :51r1
    :destination-directory nolstudio
    :source-filename "NolStudioDeploy.jar")

(def-part nolstudio-online-batch
    :source nols
    :platforms ("nt" "win64")
    :version :51r1
    :source-filename "onlinenolstudio.bat"
    :platforms ("nt" "win64")
	:postinstall-code "replace_rootdir(\"nolstudio\"^\"bin\", \"onlinenolstudio.bat\");"
	:destination-directory nolstudio/bin
	)

(def-part nolstudio-deploy-misc
    :source nols
    :platforms ("nt" "win64")
    :version :51r1
    :source-filename "nolonline.bat"
    :platforms ("nt" "win64")
	:postinstall-code "replace_rootdir(\"nolstudio\"^\"bin\", \"nolonline.bat\");"
	:destination-directory nolstudio/bin
	)

(def-part nol-classic-kb
    :source nol
    :version :51r1
    :source-subdirectory kbs
    :indep t
    :destination-directory "nol/kbs"
    :source-filename ("nol.kb" "nolapps.kb" "gnneapps.kb" "noldemo.kb" "nolexten.kb" "nolx.kb" 
				"nolxapps.kb" "nolui.kb" "java-module.kb"  "nolspack.kb" "nolstudio.kb"))

(def-part nol-classic-gnne
    :source nol
    :version :51r1
    :source-subdirectory kbs
    :indep t
    :destination-directory "nol/kbs"
    :source-filename ("gnne.kb"))

(def-part nol-classic-nt
    :source nol
    :version :51r1
    :source-subdirectory bin
    :indep t
    :destination-directory "nol/bin"
    :platforms ("nt" "win64")
    :source-filename ("ntnol.exe" "nol.ico")
    :shortcuts (nolapps-shortcut gnneapps-shortcut gnnedemo-shortcut noldemo-shortcut nolbakerydemo-shortcut nolbleachdemo-shortcut))

(def-part nol-classic-win64
    :source nol
    :version :51r1
    :source-subdirectory "bin/x64"
    :indep t
    :destination-directory "nol/bin/x64"
    :platforms ("win64")
    :source-filename ("ntnol.exe")
    :shortcuts ())

(def-part nol-classic-linux
    :source nol
    :version :51r1
    :source-subdirectory bin
    :indep t
    :destination-directory "nol/bin"
    :platforms ("linux" "linux64")
    :source-filename ("linuxnol" "startnolapps" "startbakery-demo" "startbleach-demo" "starttotal-demo")
    :postinstall-code "replace_rootdir(\"nol\"^\"bin\", \"startnolapps\");replace_rootdir(\"nol\"^\"bin\", \"startbakery-demo\");replace_rootdir(\"nol\"^\"bin\", \"startbleach-demo\");replace_rootdir(\"nol\"^\"bin\", \"starttotal-demo\");")

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
     :parameters "-kb ..\\nol\\projects\\examples\\gnne-demo\\gnne-demo.kb -configfile ..\\..\\g2i\\kbs\\config.txt"
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
    :version :51r0-JG20
    :source-filename ("nolrm.pdf" "nolstudioug.pdf" "nolusersguide.pdf" "GNNEUsersGuide.pdf")
    :indep t
    :destination-directory "doc/nol"
    :shortcuts (nol-users-guide nol-reference-guide gnne-users-guide nolstudio-users-guide
		#|nol-html-doc nol-win-doc|#)
    )

(def-shortcut nolstudio-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "G2 NeurOn-Line Studio User's Guide"
    :application-directory doc/nol
    :target-name nolstudioug.pdf)

#+nil
(def-shortcut nol-html-doc
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation (HTML)"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "G2 NeurOn-Line User's Guide and Reference Manual"
    :application-directory doc/nol/nolugrm/html
    :target-name titlepag.htm)

(def-part gnne-demo
    :source nol
    :version :51r1
    :indep t
    :source-subdirectory projects/examples/gnne-demo
    :destination-directory nol/projects/examples/gnne-demo)

(def-part gnne-demo-config
    :source nol
    :version :51r1
    :indep t
    :source-subdirectory projects/examples/gnne-demo
    :destination-directory nol/projects/examples/gnne-demo
    :source-filename ("config.txt")
    :postinstall-code "replace_rootdir(\"nol\"^\"projects\"^\"examples\"^\"gnne-demo\", \"config.txt\");"
	)

(def-part nol-total-demo
    :source nol
    :version :51r1
    :indep t
    :source-subdirectory projects/examples/total-demo
    :destination-directory nol/projects/examples/total-demo)

(def-part nol-bakery-demo
    :source nol
    :version :51r1
    :indep t
    :source-subdirectory projects/examples/bakery-demo
    :destination-directory nol/projects/examples/bakery-demo)

(def-part nol-bleach-demo
    :source nol
    :version :51r1
    :indep t
    :source-subdirectory projects/examples/bleach-demo
    :destination-directory nol/projects/examples/bleach-demo)

(def-shortcut nol-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "G2 NeurOn-Line User's Guide"
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
    :application-display-name "Neural Network Engine User's Guide"
    :application-directory doc/nol
    :target-name "GNNEUsersGuide.pdf")

(def-part nol-readme
    :source g2pkgreadme
    :version :2015
    :destination-directory doc/nol
    :source-filename "readme-nol.html"
    :indep t
    :shortcuts (nol-readme))

(def-shortcut nol-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 NeurOn-Line"
    :application-display-name "Readme for G2 NeurOn-Line"
    :application-directory "doc/nol"
    :target-name readme-nol.html)

(def-part nol-g2i-modules
  :source g2i
  :version :23r1
  :indep t
  :source-subdirectory kbs
  :source-filename ("gdpm.kb" "gedp.kb")
  :destination-directory "g2i/kbs")

;;;Integrity

(def-component integrity
  :print-name "G2 Integrity"
  :optional true
  :parts (integrity-doc ping-manager integrity-g2i-modules integrity-mib-parser integrity-readme integrity-reasoner-kbs
          integrity-client-sh-file integrity-mib-parser-unix)
  ;;cdg-import-export-kbs
  :platforms ("nt" "hpux" "sparcsol" "hpia64" "linux" "linux64")
  :include-in-contents (integrity-reasoner-kbs))

(def-part integrity-client-intelnt
    :version :40r0-B03F16
    :source opex-client
    ;; this contains a self extracting installer.  This is no doubt wrong.
    ;; finishing later.
    :platforms ("nt" "win64")
    ;;;:environment-variables (integrity_home)
    :destination-directory client
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
    :version :50r1
    :destination-directory "doc/integrity"
    :indep t
    :shortcuts (int-users-guide int-util-guide 
                ;;int-snmp-users-guide int-jsnmp-users-guide 
                ;;int-demo-guide int-ref-man int-dxi3db-primer
		))

(def-shortcut int-users-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity User's Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityUsersGuide.pdf")

#+nil
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

#+nil
(def-shortcut int-rel-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity 4.0r0 Release Notes"
    :application-directory "doc/integrity"
    :target-name "IntRelNotes.pdf")

#+nil
(def-shortcut int-demo-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Integrity"
    :application-display-name "Integrity Demo Guide"
    :application-directory "doc/integrity"
    :target-name "IntegrityDemoGuide.pdf")

#+nil
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
    :platforms ("nt" "sparcsol" "hpux" "hpia64") 
    :destination-directory "integrity/bin")

(def-part integrity-client-sh-file
  :source intereas
  :source-subdirectory "bin"
  :version :50r1
  :indep t
  :source-filename ("startintegrity")
  :non-platforms ("nt" "win64")
  :postinstall-code "replace_rootdir(\"integrity\"^\"bin\", \"startintegrity\");"
  :destination-directory "integrity/bin")

(def-part integrity-g2i-modules
  :source g2i
  :version :23r1
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

(def-part integrity-mib-parser-unix
  :source g2mibparser
  :version :40r0
  :non-platforms ("nt" )
  :postinstall-code "replace_rootdir(\"g2mibparser\"^\"bin\", \"startjmibparser\");"
  :destination-directory g2mibparser)

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
    :version :50r1
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
    :version :50r1
    :destination-directory "resources"
    :indep t
    :source-filename ("resources/symcure") )

(def-part integrity-readme
    :source g2pkgreadme
    :version :2015
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
  :parts (optegrity-doc
	  opt-io-modules opt-io-data
	  optegrity-readme
	  opt-win-bin opt-linux-bin
	  opt-kbs opt-g2i-modules 
	  ;; opt-io-resources opt-resources optegrity-release-notes
	  opt-io-examples 
	  opt-archive)
  :include-in-contents (opt-win-bin opt-io-modules))

#+nil
(def-part optegrity-release-notes
    :source optegdoc
    :version :51r0-JG18
    :source-filename ("OptegrityReleaseNotes.pdf")
    :destination-directory "doc/optegrity"
    :indep t
    :platforms ("nt" "win64")
    :shortcuts (opt-rel-notes))

#+nil
(def-shortcut opt-rel-notes
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity Release Notes"
    :application-directory "doc/optegrity"
    :target-name "OptegrityReleaseNotes.pdf")

(def-part optegrity-doc
    :source optegdoc
    :version :51r0-JG18
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

#+nil
(def-shortcut opt-ref-man
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity Reference Manual"
    :application-directory "doc/optegrity"
    :target-name "OptRefManual.pdf")

#+nil
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

#+nil
(def-shortcut opt-demo-guide
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 Optegrity"
    :application-display-name "Optegrity Furnace Tutorial"
    :application-directory "doc/optegrity"
    :target-name "OptegrityFurnaceTutorial.pdf")

(def-part opt-io-modules
  :source optegrity
  :version :51r1
  :indep t
  :source-subdirectory kbs
  :source-filename ("iato.kb" "icco.kb" "ico.kb"  "icso.kb" "idco.kb" "iedo.kb" "iffo.kb" "iho.kb" "ioc.kb" "ipo.kb" "irco.kb" "iso.kb" "ito.kb" "ivo.kb" "ixo.kb" "sdb.kb" "opt-event.kb")
  :destination-directory "optegrity/kbs")

(def-part opt-io-data
    :source optegrity
    :version :51r1
    :indep t
    :source-subdirectory data
    :source-filename ("F102-replay-to-external-datapoint.csv" "F102-external-datapoint-configuration-OPC.csv")
    :destination-directory "optegrity/data")

(def-part opt-io-resources
    :source optegrity
    :version :51r1
    :indep t
    :source-subdirectory resources
    :source-filename ("IATO-EventNames.txt" "ICCO-EventNames.txt" "ICO-EventNames.txt" "IDCO-EventNames.txt" "IEDO-EventNames.txt" "IFFO-FB-EventNames.txt" "IFFO-FF-EventNames.txt" "IHO-EventNames.txt" "IPO-EventNames.txt" "IRCO-EventNames.txt" "ISO-EventNames.txt" "ITO-EventNames.txt" "IVO-EventNames.txt" "IXO-EventNames.txt")
    :destination-directory "optegrity/resources")

(def-part opt-io-examples
    :source optegrity
    :version :51r1
    :indep t
    :source-subdirectory examples
    :source-filename ("f102demo.kb")
    :destination-directory "optegrity/examples"
    :shortcuts (io-demo-shortcut) )

(def-part opt-f101-examples
    :source optegrity
    :version :51r1
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
    :version :51r1
    :source-subdirectory archives
    :source-filename ( )
    :destination-directory "optegrity/archives"
    :indep t)

(def-part opt-project
    :source optegrity
    :version :51r1
    :source-subdirectory projects
    :source-filename ( )
    :destination-directory "optegrity/projects"
    :indep t)

(def-part opt-win-bin
    :source optegrity
    :version :51r1
    :source-subdirectory bin
    :source-filename ("InstallServerAsNTService.bat" "Optegrity.ico" "UninstallServerAsNTService.bat")
    :destination-directory "optegrity/bin"
    :postinstall-code "replace_rootdir(\"optegrity\"^\"bin\", \"InstallServerAsNTService.bat\");replace_rootdir(\"optegrity\"^\"bin\", \"UninstallServerAsNTService.bat\");"
    :shortcuts (optegrity-shortcut )
    :platforms ("nt" "win64")
    :indep t)

(def-part opt-linux-bin
    :source optegrity
    :version :51r1
    :source-subdirectory bin
    :source-filename ("startoptegrity" "startHeaterTutorial")
    :destination-directory "optegrity/bin"
    :platforms ("linux" "linux64")
    :postinstall-code "replace_rootdir(\"optegrity\"^\"bin\", \"startoptegrity\");replace_rootdir(\"optegrity\"^\"bin\", \"startHeaterTutorial\");"
    :indep t)

(def-part opt-data
    :source optegrity
    :version :51r1
    :source-subdirectory data
    :source-filename ("fo2-external-datapoint-configuration-OPC.csv" "fo2-external-datapoint-configuration-OPC.xls" "fo2-external-datapoint-configuration-PI.csv" "fo2-external-datapoint-configuration-PI.xls" "fo2-external-datapoints-configuration.csv" "fo2-external-datapoints-configuration.xls" "fo2-logging-data.csv" "fo2-replay-to-external-datapoint.csv" "fo2-replay-to-internal-datapoint.csv")
    :destination-directory "optegrity/data"
    :indep t)

(def-part opt-examples
    :source optegrity
    :version :51r1
    :source-subdirectory examples
    :source-filename ("fo2demo.kb")
    :destination-directory "optegrity/examples"
    :indep t)

(def-part opt-kbs
    :source optegrity
    :version :51r1
    :source-subdirectory kbs
    :source-filename ("equipmnt.kb" "optegrity.kb" "optegrity-core.kb")
    :destination-directory "optegrity/kbs"
    :indep t)

(def-part opt-logs
    :source optegrity
    :version :51r1
    :source-subdirectory logs
    :source-filename ( )
    :destination-directory "optegrity/logs"
    :indep t)

(def-part opt-resources
    :source optegrity
    :version :51r1
    :source-subdirectory resources
    :source-filename ("optegrity-core-resources.txt")
    :destination-directory "optegrity/resources"
    :indep t)

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
  :version :23r1
  :destination-directory "g2i/kbs"
  :source-subdirectory kbs
  :source-filename ("cdg.kb" "cdggrlb.kb" "gdpm.kb" "gedp.kb" "guif.kb" "guif-resources.txt" "geuc.kb" "symcure.kb" "grtl.kb" "gevm.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "grlb.kb" "gdsm.kb" "gdu.kb" "gduc.kb" "gdue.kb" "gens.kb" "gerr.kb" "glf.kb" "resources-english.txt")
  :indep t)

(def-part optegrity-readme
    :source g2pkgreadme
    :version :2015
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
    symcure-fake-icon
    symcure-examples)
  :platforms ("nt" "win64")
  :include-in-contents (symcure-fake-icon))

;;;The purpose of this kluge is to get Symcure to have the same version as Optegrity.
;;;There aren't any components that ACTUALLY COME from something with the right version.
;;;So duplicate the optegrity icon file.

(def-part symcure-fake-icon
    :source optegrity
    :version :51r1
    :source-subdirectory bin
    :source-filename ("Optegrity.ico")
    :destination-directory "optegrity/bin"
    :indep t)

;;; Pulling the User's Guide from the Optegrity documentation
(def-part symcure-doc
    :source optegdoc
    :version :51r0-JG18
    :source-filename "SymCureUsersGuide.pdf"
    :destination-directory "doc/symcure"
    :indep t
    :platforms ("nt" "win64")
    :shortcuts (symcure-users-guide))

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
    :version :51r1
    :source-subdirectory bin
    :source-filename "SymCure.ico"
    :destination-directory "symcure/bin"
    :platforms ("nt" "win64")
    :shortcuts (symcure-shortcut)
    :indep t)

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
    :run-style minimized)
 
(def-part symcure-readme
    :source g2pkgreadme
    :version :2015
    :source-filename ("readme-symcure.html")
    :platforms ("nt" "win64")
    :destination-directory "doc/symcure"
    :indep t 
    :shortcuts (symcure-readme))

(def-shortcut symcure-readme
    :folder-name g2-shortcut-folder-name
    :subfolder-name "G2 SymCure"
    :application-display-name "Readme for G2 SymCure"
    :application-directory "doc/symcure"
    :target-name "readme-symcure.html")
 
(def-part symcure-kbs
  :source g2i
  :version :23r1
  :destination-directory "g2i/kbs"
  :platforms ("nt" "win64")
  :source-subdirectory kbs
  :source-filename ("cdg.kb" "cdggrlb.kb" "symcure.kb" "grtl.kb" "gevm.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "grlb.kb" "gdsm.kb" "gdu.kb"  "gerr.kb" "glf.kb" "resources-english.txt" "cdg-resources-english.txt" "gevm-resources-english.txt" "grtl-utils.kb" "grtl-icons.kb" "grpe.kb" "gdsm-jmail.kb" "gdsm-jms.kb" "gdsm-db.kb" "gdsm-web.kb" "gweb.kb")
  :indep t)
 
(def-part symcure-examples
    :source g2i
    :version :23r1
    :source-subdirectory examples
    :source-filename ("cdg-modguide.kb")
    :destination-directory "g2i/examples"
    :platforms ("nt" "win64")
    :indep t
    :shortcuts (symcure-demo-shortcut))

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

(def-part symbols-intelnt
  :source symbols
  :version :2015
  :platforms ("nt" "win64")
  :destination-directory symbols)

(def-part symbols-linux
  :source symbols
  :version :2015
  :platforms ("linux" "linux64")
  :destination-directory symbols)
