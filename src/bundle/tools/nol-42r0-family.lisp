;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; NOL-FAMILY - NOL Family Definitions.  Requires G2-FAMILY (with bundle.lisp loaded).

;; Mark H. David; yduJ; gchen

;;; The current shipping version of NOL is 4.2 Rev. 0 ("42r0").  The
;;; symbol :42r0 should be used generally for NOL elements below.
;;; but temporally it is set to 42r0.

(defvar g2-shortcut-folder-name "Gensym NOL 4.2r0")
(defvar nol-shortcut-folder-name "Gensym NOL 4.2r0")

(require "g2-70r1-family")			; G2 7.0r1
(provide 'nol-42r0-family)


;;;; NOL Family (prototype)


;;;; Family: NOL

(def-family nol-42r0
    :index 24
    :file-syntax-version 20
    :bundles (nol-studio-development
	       nol-premium-deployment
	       nol-studio-deployment
	       nol-premium-development)
    :print-name "NOL"
    :directory "nol-4.2r0"
    :guid "EF7E0B02-1147-45d8-9B1F-D5A208FC57D9" ; 4.2r0
    :previous-versions (
			("2.2r0b" "243D4BB6-9EE7-11D4-8111-00A02431D004")
			("2.2r0" "243D4BAD-9EE7-11D4-8111-00A02431D004")
			("2.2r0a" "243D4BB4-9EE7-11D4-8111-00A02431D004")
			("4.1r1" "39C4AC65-75FF-4EA5-A105-A001BF1BD5E7")
			("4.1r2" "72840789-1558-4B87-876B-7889E282F256")
			("4.1r3" "9C4D66F9-B71E-4EB9-BB91-FA9BE1954B57")
			("4.2b0" "3FACB849-03C5-4d66-9887-EEEEB8F9A5B8")
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
				 (1 "-dec25-2003") (1 "-jan25-2004") (1 "-feb25-2004")
				 (1 "-mar25-2004") (1 "-apr25-2004") (1 "-may25-2004")
			  ))

(def-g2-ok-components (neuron-line-premium-deployment :obfuscate t) nol "NeurOnline Premium Deployment"
		      (4 8 12 16 20 24 28 32
				 (1 "-dec25-2003") (1 "-jan25-2004") (1 "-feb25-2004")
				 (1 "-mar25-2004") (1 "-apr25-2004") (1 "-may25-2004")
			  ))

;; need checking gchen

;;;; Bundles nol-studio-development nol-premium-deployment nol-studio-deployment nol-premium-development

;; Note: there is no longer a "bundle directory" used by the bundle installer.
;; Previously, NOL specified dev, premdep, dep, and premdev for the following,
;; respectively. (MHD 1/2/01)

(defvar nols-basic-components '(nolstudio-examples nolstudio-documentation jre nol-readme))

(def-bundle nol-studio-development
    :version :42r0										         
    :components  (nolstudio-core-development nols-basic-components nolstudio-gui nolstudio-dynamic-lib)
    :platforms ("nt" "hpux" "sparcsol")
    :print-name "NOL Studio Development")

(def-bundle nol-studio-deployment
    :version :42r0
    :components (nolstudio-core-development nols-basic-components nolstudio-window-deployment nolstudio-dynamic-lib)
    :platforms ("nt")
    :print-name "NOL Studio Deployment")

(def-bundle nol-premium-development
    :version :42r0
    :components (nolstudio-core-development nols-basic-components nolstudio-gui
				 nolstudio-g2-deployment nolstudio-window-deployment nolstudio-dynamic-lib
				 nol-classic nol-classic-documentation
				 core-g2-components additional-g2-development-components
				 neuron-line-premium-development-family-ok-components
				 g2-gold-hp-fix-kbs
				 )
    :platforms ("nt" "hpux" "sparcsol")
    :print-name "NOL Premium Development")

(def-bundle nol-premium-deployment
    :version :42r0
    :components (nolstudio-core-development nols-basic-components
				 nolstudio-g2-deployment nolstudio-window-deployment nolstudio-dynamic-lib
				 nol-classic nol-classic-documentation
				 core-g2-components additional-g2-deployment-components 
				 neuron-line-premium-deployment-family-ok-components
				 g2-gold-hp-fix-kbs
				) 
    :platforms ("nt" "hpux" "sparcsol")
    :print-name "NOL Premium Deployment")




;;;; Components


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


(def-component nol-readme
  :parts (nol-readme)
  :print-name "Readme for NOL Bundle")

(def-component nolstudio-window-deployment
  :parts (nolstudio-window-misc nolstudio-ActiveX-control)
  :platforms ("nt")
  :print-name "NolStudio Window Deployment")

(def-component nolstudio-dynamic-lib
  :parts (nolstudio-window-classic-dll nolstudio-hp-classic-dll nolstudio-sol-classic-dll)
  :print-name "NolStudio Window Classic DLL")

(def-component nolstudio-g2-deployment
  :parts (nolstudio-deploy-library nolstudio-javalink-kbs nolstudio-javalink-kbs-intelnt
				   nolstudio-tw2-kbs nolstudio-tw2-kbs-intelnt 
				   nolstudio-deploy-misc nolstudio-deploy-script)
  :print-name "NolStudio G2 Deployment")

(def-component nol-classic
  :parts (nol-classic nol-classic-nt nol-classic-unix nol-total-demo)
  :print-name "NOL Classic")

(def-component nol-classic-documentation
  :parts (nol-classic-documentation)
  :print-name "NOL Classic Documentation")

;;;; Parts


(def-part nolstudio-data
    :version :42r0 
    :print-name "Data"
    :source nols
    :source-filename "NolStudioData.jar"
    :destination-directory nolstudio)

(def-environment-variable nolstudio_home
    :value "<TARGETDIR>")

(def-environment-variable nolstudio-jre
    :variable "PATH"
    :append-or-merge merge
    :value "<TARGETDIR>\\\\jre\\\\bin;<TARGETDIR>\\\\jre\\\\bin\\\\hotspot")


(def-part nolstudio-math-library
    :version :42r0 
    :print-name "Math Library"
    :source nols
    :source-filename "NolStudioMath.jar"
    :destination-directory nolstudio)

(def-part nolstudio-core-misc-demolicense
    :version :42r0 
    :print-name "Core Misc"
    :source nols
    :source-filename ("demolicense.txt" "known-bugs.txt")
    :destination-directory nolstudio)

(def-part nolstudio-gui
    :version :42r0 
    :source-filename "NolStudioGUI.jar"
    :source nols
    :destination-directory nolstudio
    :print-name "NolStudio GUI")

(def-part nolstudio-gui-misc
    :version :42r0 
    :source nols
    :destination-directory nolstudio
    :source-filename ("NolMainFrame.properties" "NolStringResources.properties" "readme.html")
	:shortcuts (nolstudio-readme))

(def-shortcut nolstudio-readme
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "NOLStudio Readme"
    :application-directory nolstudio
    :target-name readme.html)

(def-part nolstudio-batch
    :version :42r0 
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
    :version :42r0 
    :source nols
    :source-subdirectory examples
    :destination-directory nolstudio/examples)

(def-part nolstudio-documentation
    :version :42r0 
    :source nols
    :source-subdirectory doc
    :destination-directory nolstudio/doc
    :shortcuts (nolstudio-users-guide))

(def-shortcut nolstudio-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "NOLStudio Users' Guide"
    :application-directory nolstudio/doc
    :target-name NOLStudioUsersGuide.pdf)

(def-part nolstudio-window-misc
    :source nols
    :version :42r0 
    :source-filename ("RegisterControls.bat" "UnRegisterControls.bat")
    :platforms ("nt")
	:destination-directory nolstudio)

(def-part nolstudio-ActiveX-control
    :source nols
    :version :42r0 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "NolOnline.dll"
    :platforms ("nt")
    :environment-variables (nolstudio_home nolstudio-jre)
    :shortcuts (nolstudio-install-control nolstudio-uninstall-control))

(def-shortcut nolstudio-install-control
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "Register NOLOnline Control"
    :application-directory nolstudio
    :target-name RegisterControls.bat
    :run-style minimized)

(def-shortcut nolstudio-uninstall-control
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "Unregister NOLOnline Control"
    :application-directory nolstudio
    :target-name UnRegisterControls.bat
    :run-style minimized)

(def-part nolstudio-window-classic-dll
    :source nols
    :version :42r0 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "jnol.dll"
    :platforms ("nt"))

(def-part nolstudio-hp-classic-dll
    :source nols
    :version :42r0 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "libjnol.sl"
    :platforms ("hpux"))

(def-part nolstudio-sol-classic-dll
    :source nols
    :version :42r0 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "libjnol.so"
    :platforms ("sparcsol"))

(def-part nolstudio-tw2-kbs-intelnt
    :version :12r4
    :source tw2
    :source-subdirectory components/kbs
    :source-filename "jlintf.kb"
    :platforms ("nt")
    :destination-directory nol)

(def-part nolstudio-tw2-kbs
    :version :12r4
    :source tw2
    :source-subdirectory kbs
    :source-filename "jlintf.kb"
    :platforms ("hpux" "sparcsol")
    :destination-directory nol)

(def-part nolstudio-javalink-kbs-intelnt
	:version :12r4
    :source jvl
    :source-subdirectory components/kbs
    :source-filename "javalink.kb"
    :platforms ("nt")
    :destination-directory nol
	)

(def-part nolstudio-javalink-kbs
	:version :12r4
    :source jvl
    :source-subdirectory kbs
    :source-filename "javalink.kb"
    :platforms ("hpux" "sparcsol")
    :destination-directory nol
	)

(def-part nolstudio-deploy-library
    :source nols
    :version :42r0
    :destination-directory nolstudio
    :source-filename "NolStudioDeploy.jar")

(def-part nolstudio-deploy-misc
    :source nols
    :version :42r0
    :source-filename "nolonline.bat"
    :platforms ("nt")
	:postinstall-code "replace_rootdir(\"nolstudio\", \"nolonline.bat\");"
	:destination-directory nolstudio
	)

(def-part nol-classic
    :source nol
    :version :42r0
    :indep t
    :destination-directory nol
    :source-filename ("nol.kb" "nolapps.kb" "noldemo.kb" "nolexten.kb"
		       "nolui.kb" "java-module.kb"  "nolspack.kb" "nolstudio.kb"))

(def-part nol-classic-nt
    :source nol
    :version :42r0
    :indep t
    :destination-directory nol
    :platforms ("nt")
    :source-filename ("ntnol.exe")
    :shortcuts (noldemo-shortcut nolapp-shortcut))

	
(def-shortcut nolapp-shortcut
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "NOL Application"
    :application-directory "nol"
    :target-name "..\\g2\\g2.exe"
    :parameters "-kb nolapps.kb -module-search-path \"'..\\g2\\kbs\\utils' '..\\nol' '..\\gda' '..\\protools\\kbs' '..\\activexlink' '..\\gsi' '..\\gw\\kbs' '..\\tw2\\kbs'\" -ok ..\\g2\\g2.ok")

(def-shortcut noldemo-shortcut
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "NOL Demo"
    :application-directory nol/noldemo
	:target-name "..\\..\\g2\\g2.exe"   
	:parameters "-kb noldemo.kb -module-search-path \"'.\\' '..\\..\\g2\\kbs\\utils' '..\\..\\gda' '..\\' '..\\..\\javalink\\KBs' '..\\..\\protools\\kbs' '..\\..\\activexlink' '..\\..\\gsi' '..\\..\gw\kbs' '..\\..\\tw2\\kbs' '..\\..\\odbc'\" -ok ..\\..\\g2\\g2.ok -start"
	)

(def-part nol-classic-unix
    :source nol
    :version :42r0
    :indep t
    :destination-directory nol
    :platforms ("hpux" "sparcsol")
    :source-filename ("solnol" "hpuxnol" "noldemounix"))


(def-part nol-classic-documentation
    :source nol
    :version :42r0
    :indep t
    :source-subdirectory noldoc
    :destination-directory nol/noldoc
	:shortcuts (nol-users-guide nol-reference-guide))

(def-part nol-total-demo
    :source nol
    :version :42r0
    :indep t
    :source-subdirectory noldemo
    :destination-directory nol/noldemo)

(def-shortcut nol-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "NOL Users' Guide"
    :application-directory nol/noldoc
    :target-name nolusersguide.pdf)

(def-shortcut nol-reference-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :application-display-name "NOL Reference Manual"
    :application-directory nol/noldoc
    :target-name nolrm.pdf)

(def-part nol-readme
    :source nols
    :version :42r0
    :source-filename "readme-nol-bundle.html"
    :shortcuts (nol-readme))

(def-shortcut nol-readme
    :folder-name nol-shortcut-folder-name
    :application-display-name "Readme for NOL Bundle"
    :application-directory ""
    :target-name readme-nol-bundle.html)


(def-part nolstudio-script
    :version :42r0 
    :source nols
    :destination-directory nolstudio
    :platforms ("hpux" "sparcsol")
    :source-filename ("nolstudio"))

(def-part nolstudio-deploy-script
    :version :42r0 
    :source nols
    :destination-directory nolstudio
    :platforms ("hpux" "sparcsol")
    :source-filename ("nolonline"))

(def-part g2-gold-hp-fix-kbs
    :version :42r0-HP
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
