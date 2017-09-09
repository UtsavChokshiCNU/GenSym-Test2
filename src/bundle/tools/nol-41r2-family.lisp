;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; NOL-FAMILY - NOL Family Definitions.  Requires G2-FAMILY (with bundle.lisp loaded).

;; Mark H. David; yduJ; gchen

;;; The current shipping version of NOL is 4.1 Rev. 2 ("41r2").  The
;;; symbol :41r2 should be used generally for NOL elements below.

(defvar g2-shortcut-folder-name "Gensym NOL")
(defvar nol-shortcut-folder-name "Gensym NOL")

(require "g2-62r0-family")			; G2 6.2r0
(provide 'nol-41r2-family)


;;;; NOL Family (prototype)


;;;; Family: NOL

(def-family nol-41r2
    :index 14
    :file-syntax-version 20
    :bundles (nol-studio-development
	       nol-premium-deployment
	       nol-studio-deployment
	       nol-premium-development)
    :print-name "NOL"
    :directory "nol"
    :readme-file "nol-readme.txt"
    :guid "72840789-1558-4B87-876B-7889E282F256" ; 4.1r2
    :previous-versions (
			("2.2r0b" "243D4BB6-9EE7-11D4-8111-00A02431D004")
			("2.2r0" "243D4BAD-9EE7-11D4-8111-00A02431D004")
			("2.2r0a" "243D4BB4-9EE7-11D4-8111-00A02431D004")
			("4.1r1" "39C4AC65-75FF-4EA5-A105-A001BF1BD5E7")
			;; add more here
			)
	:splash-screen "nol-setup.bmp"
    :license-text "standard-license.txt")


;;;; ok file definitions
;; the following forms create variables containing parts and components for all of the
;; ok files, which variables will be referenced in the bundle's components. They are:
;; neuron-line-premium-development-family-ok-components,
;; neuron-line-premium-deployment-family-ok-components


(def-g2-ok-components (neuron-line-premium-development :obfuscate t) nol "NeurOnline Premium Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32
				 (1 "-mar25-2002") (1 "-apr25-2002") (1 "-may25-2002")
				 (1 "-jun25-2002") (1 "-jul25-2002") (1 "-aug25-2002")
				 (1 "-sep25-2002") (1 "-oct25-2002") (1 "-nov25-2002")
				 (1 "-dec25-2002") (1 "-jan25-2003") (1 "-feb25-2003")
			  ))

(def-g2-ok-components (neuron-line-premium-deployment :obfuscate t) nol "NeurOnline Premium Deployment"
		      (4 8 12 16 20 24 28 32
				 (1 "-mar25-2002") (1 "-apr25-2002") (1 "-may25-2002")
				 (1 "-jun25-2002") (1 "-jul25-2002") (1 "-aug25-2002")
				 (1 "-sep25-2002") (1 "-oct25-2002") (1 "-nov25-2002")
				 (1 "-dec25-2002") (1 "-jan25-2003") (1 "-feb25-2003")
			  ))

;; need checking gchen

;;;; Bundles nol-studio-development nol-premium-deployment nol-studio-deployment nol-premium-development

;; Note: there is no longer a "bundle directory" used by the bundle installer.
;; Previously, NOL specified dev, premdep, dep, and premdev for the following,
;; respectively. (MHD 1/2/01)

(defvar nols-basic-components '(nolstudio-examples nolstudio-documentation nolstudio-jre nol-readme))

(def-bundle nol-studio-development
    :version :41r2										         
    :components  (nolstudio-core-development nols-basic-components nolstudio-gui)
    :platforms ("nt" "hpux" "sparcsol")
    :print-name "NOL Studio Development")

(def-bundle nol-studio-deployment
    :version :41r2
    :components (nolstudio-core-deployment nols-basic-components nolstudio-window-deployment)
    :platforms ("nt")
    :print-name "NOL Studio Deployment")

(def-bundle nol-premium-development
    :version :41r2
    :components (nolstudio-core-deployment nols-basic-components nolstudio-gui
				 nolstudio-g2-deployment nolstudio-window-deployment
				 nol-classic nol-classic-documentation
				 core-g2-components additional-g2-development-components
				 neuron-line-premium-development-family-ok-components
				 g2-gold-hp-fix-kbs
				 )
    :platforms ("nt" "hpux" "sparcsol")
    :print-name "NOL Premium Development")

(def-bundle nol-premium-deployment
    :version :41r2
    :components (nolstudio-core-deployment nols-basic-components
				 nolstudio-g2-deployment nolstudio-window-deployment
				 nol-classic nol-classic-documentation
				 core-g2-components additional-g2-deployment-components 
				 neuron-line-premium-deployment-family-ok-components
				 g2-gold-hp-fix-kbs
				) 
    :platforms ("nt" "hpux" "sparcsol")
    :print-name "NOL Premium Deployment")




;;;; Components



(def-component nolstudio-core-deployment
    :parts (nolstudio-deployment-data-nt nolstudio-deployment-data-unix nolstudio-math-library
			   nolstudio-core-misc-demolicense)
    :print-name "NOL Studio Core")

(def-component nolstudio-core-development
    :parts (nolstudio-data nolstudio-math-library
			   nolstudio-core-misc-demolicense)
    :print-name "NOL Studio Core")

(def-component nolstudio-gui
    :parts (nolstudio-gui nolstudio-gui-misc nolstudio-batch nolstudio-script)
    :print-name "NOL Studio GUI")

(def-component nolstudio-examples
  :parts (nolstudio-examples)
  :print-name "NolStudio Examples")

(def-component nolstudio-documentation
  :parts (nolstudio-documentation)
  :print-name "NolStudio Documentation")


(def-component nolstudio-jre
  :parts (nolstudio-jre)
  :platforms ("nt")
  :print-name "Java Runtime Environment for NOLStudio")

(def-component nol-readme
  :parts (nol-readme)
  :print-name "Readme for NOL Bundle")

(def-component nolstudio-window-deployment
  :parts (nolstudio-window-misc nolstudio-ActiveX-control)
  :platforms ("nt")
  :print-name "NolStudio Window Deployment")

(def-component nolstudio-g2-deployment
  :parts (nolstudio-deploy-library nolstudio-javalink-kbs nolstudio-javalink-kbs-intelnt
				   nolstudio-tw2-kbs nolstudio-tw2-kbs-intelnt 
				   nolstudio-deploy-misc nolstudio-deploy-script)
  :print-name "NolStudio G2 Deployment")

(def-component nol-classic
  :parts (nol-G2-kbs nol-gold-nonhp-kbs nol-gold-hp-kbs nols-gda-kbs nol-classic nol-classic-nt nol-classic-unix)
  :print-name "NOL Classic")

(def-component nol-classic-documentation
  :parts (nol-classic-documentation)
  :print-name "NOL Classic Documentation")

;;;; Parts


(def-part nolstudio-data
    :version :41r2 
    :print-name "Data"
    :source nols
    :source-filename "NolStudioData.jar"
    :destination-directory nolstudio)

(def-environment-variable nolstudio_home
    :value "<TARGETDIR>\\\\nolstudio")

(def-environment-variable nolstudio-jre
    :variable "PATH"
    :append-or-merge merge
    :value "%NOLSTUDIO_HOME%\\\\jre\\\\bin;%NOLSTUDIO_HOME%\\\\jre\\\\bin\\\\hotspot")


(def-part nolstudio-deployment-data-nt
    :parent nolstudio-data
    :platforms ("nt")
    :environment-variables (nolstudio_home nolstudio-jre))

(def-part nolstudio-deployment-data-unix
    :parent nolstudio-data
    :platforms ("hpux" "sparcsol"))

(def-part nolstudio-math-library
    :version :41r2 
    :print-name "Math Library"
    :source nols
    :source-filename "NolStudioMath.jar"
    :destination-directory nolstudio)

(def-part nolstudio-core-misc-demolicense
    :version :41r2 
    :print-name "Core Misc"
    :source nols
    :source-filename ("demolicense.txt" "known-bugs.txt")
    :destination-directory nolstudio)

(def-part nolstudio-gui
    :version :41r2 
    :source-filename "NolStudioGUI.jar"
    :source nols
    :destination-directory nolstudio
    :print-name "NolStudio GUI")

(def-part nolstudio-gui-misc
    :version :41r2 
    :source nols
    :destination-directory nolstudio
    :source-filename ("NolMainFrame.properties" "NolStringResources.properties" "readme.html")
	:shortcuts (nolstudio-readme))

(def-part nolstudio-batch
    :version :41r2 
    :source nols
    :destination-directory nolstudio
    :platforms ("nt")
    :source-filename ("nolstudio.bat")
	:shortcuts (nolstudio-batch-file))

(def-shortcut nolstudio-batch-file
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "Neur-Online Studio"
    :application-directory nolstudio
    :target-name nolstudio.bat
    :run-style minimized)

(def-part nolstudio-examples
    :version :41r2 
    :source nols
    :source-subdirectory examples
    :destination-directory nolstudio/examples)

(def-part nolstudio-documentation
    :version :41r2 
    :source nols
    :source-subdirectory doc
    :destination-directory nolstudio/doc
    :shortcuts (nolstudio-users-guide))

(def-part nolstudio-jre
    :parent jre
    :destination-directory nolstudio/jre)

(def-part nolstudio-window-misc
    :source nols
    :version :41r2 
    :source-filename ("RegisterControls.bat" "UnRegisterControls.bat")
    :platforms ("nt")
	:destination-directory nolstudio)

(def-part nolstudio-ActiveX-control
    :source nols
    :version :41r2 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "NolOnline.dll"
    :platforms ("nt")
    :shortcuts (nolstudio-install-control nolstudio-uninstall-control))

(def-shortcut nolstudio-install-control
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "Register NOLOnline Control"
    :application-directory nolstudio
    :target-name "RegisterControls.bat"
    :run-style minimized)

(def-shortcut nolstudio-uninstall-control
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "Unregister NOLOnline Control"
    :application-directory nolstudio
    :target-name "UnRegisterControls.bat"
    :run-style minimized)

(def-shortcut nolstudio-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "NOLStudio Users' Guide"
    :application-directory nolstudio/doc
    :target-name "NOLStudioUsersGuide.pdf")

(def-shortcut nolstudio-readme
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "NOLStudio Readme"
    :application-directory nolstudio
    :target-name "readme.html")

(def-shortcut nol-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "NOL Users' Guide"
    :application-directory nol/noldoc
    :target-name "titlepag.htm")


(def-part nol-G2-kbs
    :version :62r0
    :source kbs
    :source-filename ("g2uifile.kb" "sys-mod.kb" "uildefs.kb" "uilsa.kb" "gfr.kb"
				    "uil.kb" "uillib.kb" "uilslide.kb" "gms.kb"
				    "gxl.kb" "uilcombo.kb" "uilroot.kb" "uiltdlg.kb")
    :source-subdirectory utils
    :destination-directory nol
    :indep t)

(def-part nol-gold-nonhp-kbs
    :version :62r0
    :source kbs
    :source-filename ("gold.kb" "goldui.kb")
    :source-subdirectory utils
    :destination-directory nol
    :platforms ("nt" "sparcsol")
    :indep t)

(def-part nol-gold-hp-kbs
    :version :41r2-HP
    :source gda
    :source-filename ("goldui-hp.kb")
    :destination-directory nol
	:destination-filename goldui.kb
    :platforms ("hpux")
    :indep t)

(def-part nols-gda-kbs
    :source gda
    :version :41r2
    :indep t
    :destination-directory nol
    :source-filename ("gcc.kb" "gdabasic.kb" "gdabsdlg.kb" "gdl.kb" "gens.kb"
	              "glf.kb" "gqm.kb" "gqmv.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb"))


(def-part nolstudio-tw2-kbs-intelnt
    :version :12r3
    :source tw2
    :source-subdirectory components/kbs
    :source-filename "jlintf.kb"
    :platforms ("nt")
    :destination-directory nol)

(def-part nolstudio-tw2-kbs
    :version :12r3
    :source tw2
    :source-subdirectory kbs
    :source-filename "jlintf.kb"
    :platforms ("hpux" "sparcsol")
    :destination-directory nol)

(def-part nolstudio-javalink-kbs-intelnt
	:version :12r3
    :source jvl
    :source-subdirectory components/kbs
    :source-filename "javalink.kb"
    :platforms ("nt")
    :destination-directory nol
	)

(def-part nolstudio-javalink-kbs
	:version :12r3
    :source jvl
    :source-subdirectory kbs
    :source-filename "javalink.kb"
    :platforms ("hpux" "sparcsol")
    :destination-directory nol
	)

(def-part nolstudio-deploy-library
    :source nols
    :version :41r2
    :destination-directory nolstudio
    :source-filename "NolStudioDeploy.jar")

(def-part nolstudio-deploy-misc
    :source nols
    :version :41r2
    :source-filename "nolonline.bat"
    :platforms ("nt")
	:postinstall-code "replace_rootdir(\"nolstudio\", \"nolonline.bat\");"
	:destination-directory nolstudio
	)

(def-part nol-classic
    :source nol
    :version :41r2
    :indep t
    :destination-directory nol
    :source-filename ("nol.kb" "nolapps.kb" "noldemo.kb" "nolexten.kb"
		       "nolui.kb" "java-module.kb"  "nolspack.kb" "nolstudio.kb"))

(def-part nol-classic-nt
    :source nol
    :version :41r2
    :indep t
    :destination-directory nol
    :platforms ("nt")
    :source-filename ("ntnol.exe")
    :shortcuts (noldemo-shortcut nolapp-shortcut))

(def-part nol-classic-unix
    :source nol
    :version :41r2
    :indep t
    :destination-directory nol
    :platforms ("hpux" "sparcsol")
    :source-filename ("solnol" "hp700nol" "noldemo"))


(def-part nol-classic-documentation
    :source nol
    :version :41r2
    :indep t
    :source-subdirectory noldoc
    :destination-directory nol/noldoc
	:shortcuts (nol-users-guide))

(def-part nol-readme
    :source nols
    :version :41r2
    :source-filename "readme-nol-bundle.html"
    :shortcuts (nol-readme))

(def-shortcut nol-readme
    :folder-name nol-shortcut-folder-name
    :application-display-name "Readme for NOL Bundle"
    :application-directory ""
    :target-name readme-nol-bundle.html)

(def-shortcut noldemo-shortcut
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "NOL Classic Demo"
    :application-directory "nol"
    :target-name "..\\g2\\g2.exe"
    :parameters "-kb ..\\nol\\noldemo.kb -module-search-path kbs\\utils -ok ..\\g2\\g2.ok -start")

(def-shortcut nolapp-shortcut
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "NOL Application"
    :application-directory "nol"
    :target-name "..\\g2\\g2.exe"
    :parameters "-module-search-path \"'..\\g2\\kbs\\utils' '..\\nol' '..\\gda' '..\\protools\\kbs' '..\\activexlink' '..\\gsi' '..\\gw\\kbs' '..\\tw2\\kbs'\" -ok ..\\g2\\g2.ok")


(def-part nolstudio-script
    :version :41r2 
    :source nols
    :destination-directory nolstudio
    :platforms ("hpux" "sparcsol")
    :source-filename ("nolstudio"))

(def-part nolstudio-deploy-script
    :version :41r2 
    :source nols
    :destination-directory nolstudio
    :platforms ("hpux" "sparcsol")
    :source-filename ("nolonline"))

(def-part g2-gold-hp-fix-kbs
    :version :41r2-HP
    :source gda
    :source-filename ("goldui-hp.kb")
    :destination-directory g2/kbs/utils
	:destination-filename goldui.kb
    :platforms ("hpux")
    :indep t)

(def-component g2-gold-hp-fix-kbs
  :parts (g2-gold-hp-fix-kbs)
  :platforms ("hpux")
  :print-name "Gold Fix for HP-UX B-11-00")
