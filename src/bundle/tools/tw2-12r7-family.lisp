;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; TW2-FAMILY - TW2 Family Definitions.  Requires bundle.lisp and g2-family.lisp

;; yduJ

;;; This is the version of tw2 that would have been shipped with the g2 7.0r1
;;; bundle had we not stopped bundling it.

(require "g2-71r0-family")
(provide "tw2-12r7-family")

(def-family tw2-12r7
    :index 28			; per tools/datafiles/families/family-id.dat
    :file-syntax-version 10
    :bundles (tw2-client)
    :print-name "Telewindows2 Toolkit"    
    :directory "g2-7.1r0"
    ;; per tools/datafiles/families/guid.dat:
    :guid "45735011-ac08-4399-8fed-3e8624792542"
    :compatible-previous-versions (("1.2r6" "BF1B2B68-73E4-4691-BCB9-F780C5CAE906"))
    :splash-screen "tw2-setup.bmp"
    :license-text "standard-license.txt")


(def-bundle tw2-client
    :components (telewindows2 tw2-doc javalink javalink-doc jre)
    :version :12r7
    :print-name "Telewindows 2 Toolkit"
    :directory "tw2")

(def-component javalink-doc
  :parts (jvldoc-javalink-pdf jvldoc-di-pdf jvldoc-bb-pdf jvldoc-javalink-html jvldoc-di-html jvldoc-bb-html)
  :print-name "G2 Javalink Documentation")


(def-component telewindows2 :parts (tw2-unix tw2-3tier tw2-intelnt-with-shortcuts tw2-javadoc-with-shortcuts )
	       :print-name "Telewindows2 Toolkit")

(def-component telewindows2-no-shortcuts :parts (tw2-unix tw2-3tier tw2-intelnt tw2-javadoc)
	       :print-name "Telewindows2 Toolkit")

(def-component telewindows2-jars :parts (tw2-jars-only)
	       :print-name "Telewindows2 Toolkit Runtime")

(def-component tw2-doc :parts (tw2doc)
	       :print-name "Telewindows2 Toolkit Documentation")

(def-part tw2-unix
    :source tw2
    :version :12r7
    :destination-directory tw2
    :postinstall-code "replace_rootdir(\"tw2\"^\"bin\", \"set-envvars\");"
    :platforms ("sparcsol" "hpux" "aix"))

(def-part tw2-3tier
    :source tw2
    :version :12r7
    :destination-directory tw2
    :platforms ("alphaosf" "linux"))

(def-part tw2-intelnt
    :version :12r7
    :source tw2
    ;; for building tree:  handled by bundle.lisp, not in family file. -mhd
    :remove-from-source ("bin/unInstall.bat" "bin/unInstaller.bat") ; remove component installer stuff
    :destination-directory tw2
    :platforms ("nt")
    :postinstall-code "replace_rootdir(\"tw2\"^\"bin\", \"envvars.bat\");")

(def-part tw2-javadoc
    :source tw2-javadoc
    :version :12r7
    :destination-directory "doc/tw2/Java"
    :indep t)

(def-part tw2-javadoc-with-shortcuts
    :parent tw2-javadoc
    :shortcuts (tw2-javadoc))


(def-shortcut tw2-javadoc
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Telewindows2 Toolkit"
    :application-display-name "API Documentation"
    :application-directory "doc\\tw2\\Java\\docs\\api"
    :target-name "index.html")

(def-part tw2-jars-only
    :version :12r7
    :source tw2
    :source-subdirectory "classes"
    :destination-directory tw2/classes
    :source-filename ("antlr.jar" "ax2jbeans.jar" "coreui.jar" "sequoia.jar"))

(def-part tw2-intelnt-with-shortcuts
    :parent tw2-intelnt
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
    :subfolder-name "Examples"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Telewindows2 Toolkit Demo"
    :application-directory "tw2\\bin"
    :target-name "t2demo.bat")

(def-shortcut tw2-itemaccessdemo
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Item Access Demo"
    :application-directory "tw2\\classes\\com\\gensym\\demos\\itemaccessdemo"
    :target-name "rundemo.bat")

(def-shortcut tw2-internationalizationdemo
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Telewindows2 Toolkit"
    :application-display-name "Internationalization Demo"
    :application-directory "tw2\\classes\\com\\gensym\\demos\\internationalizationdemo"
    :target-name "rundemo.bat")



(def-shortcut tw2-palettedemo
    :folder-name g2-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "Telewindows2 Toolkit"
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

