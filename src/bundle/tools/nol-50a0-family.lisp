;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; NOL-FAMILY - NOL Family Definitions.  Requires G2-FAMILY (with bundle.lisp loaded).

;; Mark H. David; yduJ; gchen

;;; The current shipping version of NOL is 4.3 Rev. 1 ("50a0").  

(defvar g2-shortcut-folder-name "Gensym G2 NOL 5.0a0")
(defvar nol-shortcut-folder-name "Gensym G2 NOL 5.0a0")

(require "g2-82r1-family")        ; g2-82r1-family       
(provide 'nol-50a0-family)	; NOL 5.0a0



;;;; NOL Family (prototype)


;;;; Family: NOL
;; MODIFY
;;  If a new GUID is created (indication of a new key for installation), then change the :guid to
;;    the new GUID that was generated.

(def-family nol-50a0
    :index 58
    :file-syntax-version 20
    :bundles (nol-studio-evaluation
	       nol-studio-development
	       nol-premium-deployment
	       nol-studio-deployment
	       nol-premium-development)
    :print-name "NOL"
    :directory "nol-5.0a0"
    :guid "9145e84f-7ea6-46aa-9892-a652dd60a4f9" ; 5.0a0
    :compatible-previous-versions (
			("4.3r1" "4d77835c-1a3a-4996-8a46-4a5dfc20db75")
			("4.2r0" "EF7E0B02-1147-45d8-9B1F-D5A208FC57D9")
			("4.3r0" "6ebdaab3-894f-4a65-82ce-e8296fee7d76")
	)
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
			  (1 "-apr25-2006") (1 "-may25-2006") (1 "-jun25-2006")
			  (1 "-jul25-2006") (1 "-aug25-2006") (1 "-sep25-2006")
			  (1 "-oct25-2006") (1 "-nov25-2006") (1 "-dec25-2006")
			  ))

(def-g2-ok-components (neuron-line-premium-deployment :obfuscate t) nol "NeurOnline Premium Deployment"
		      (4 8 12 16 20 24 28 32
			  (1 "-apr25-2006") (1 "-may25-2006") (1 "-jun25-2006")
			  (1 "-jul25-2006") (1 "-aug25-2006") (1 "-sep25-2006")
			  (1 "-oct25-2006") (1 "-nov25-2006") (1 "-dec25-2006")
			  ))


;;;; Bundles nol-studio-evaluation nol-studio-development nol-premium-deployment nol-studio-deployment nol-premium-development

;; Note: there is no longer a "bundle directory" used by the bundle installer.
;; Previously, NOL specified dev, premdep, dep, and premdev for the following,
;; respectively. (MHD 1/2/01)

(defvar nols-basic-components '(nolstudio-examples nolstudio-documentation nol-readme))

(def-bundle nol-studio-evaluation
    :version :50a0
    :components  (nolstudio-core-evaluation nols-basic-components nolstudio-gui nolstudio-dynamic-lib)
    :platforms ("nt")
    :print-name "NOL Studio Evaluation")

(def-bundle nol-studio-development
    :version :50a0										         
    :components  (nolstudio-core-development nols-basic-components nolstudio-gui nolstudio-dynamic-lib)
    :platforms ("nt")
    :print-name "NOL Studio Development")

(def-bundle nol-studio-deployment
    :version :50a0
    :components (nolstudio-core-development nols-basic-components nolstudio-window-deployment nolstudio-dynamic-lib)
    :platforms ("nt")
    :print-name "NOL Studio Deployment")

(def-bundle nol-premium-development
    :version :50a0
    :components (nolstudio-core-development nols-basic-components nolstudio-gui
				 nolstudio-g2-deployment nolstudio-window-deployment nolstudio-dynamic-lib
				 core-g2-components additional-g2-components additional-g2-development-components
				 nol-classic nol-classic-documentation 
				 neuron-line-premium-development-family-ok-components
				 nol-classic-g2i
				 )
    :platforms ("nt")
    :print-name "NOL Premium Development")

(def-bundle nol-premium-deployment
    :version :50a0
    :components (nolstudio-core-development nols-basic-components
				 nolstudio-g2-deployment nolstudio-window-deployment nolstudio-dynamic-lib
				 core-g2-components additional-g2-components additional-g2-deployment-components 
				 nol-classic nol-classic-documentation 
				 neuron-line-premium-deployment-family-ok-components
				 nol-classic-g2i
				) 
    :platforms ("nt")
    :print-name "NOL Premium Deployment")




;;;; Components


(def-component nolstudio-core-evaluation
    :parts (nolstudio-data-eva nolstudio-math-library jre-most
			   nolstudio-core-misc-demolicense)
    :print-name "G2 NOL Studio Core Evaluation")


(def-component nolstudio-core-development
    :parts (nolstudio-data nolstudio-math-library jre-most
			   nolstudio-core-misc-demolicense)
    :print-name "G2 NOL Studio Core")

(def-component nolstudio-gui
    :parts (nolstudio-gui nolstudio-gui-misc nolstudio-batch nolstudio-online-batch)
    :print-name "G2 NOL Studio GUI")

(def-component nolstudio-examples
  :parts (nolstudio-examples)
  :print-name "G2 NOL Studio Examples")

(def-component nolstudio-documentation
  :parts (nolstudio-documentation)
  :print-name "G2 NOL Studio Documentation")


(def-component nol-readme
  :parts (nol-readme)
  :print-name "Readme for G2 NOL Bundle")

(def-component nolstudio-window-deployment
  :parts (nolstudio-window-misc nolstudio-ActiveX-control)
  :platforms ("nt")
  :print-name "G2 NOL Studio Window Deployment")

(def-component nolstudio-dynamic-lib
  :parts (nolstudio-window-classic-dll)
  :print-name "G2 NOL Studio Window Classic DLL")

(def-component nolstudio-g2-deployment
  :parts (nolstudio-deploy-library 
  				   nolstudio-tw2-kbs-intelnt 
				   nolstudio-deploy-misc pikbs)
  :print-name "G2 NOL Studio G2 Deployment")

(def-component nol-classic
  :parts (nol-classic-kb nol-classic-nt gnne-demo gnne-demo-config nol-total-demo nol-bakery-demo nol-bleach-demo)
  :print-name "G2 NOL Classic")

(def-component nol-classic-g2i
  :parts (nol-classic-gnne nol-g2i-modules g2i-core-modules ODBCbridge opclink jmail-intel jmail-doc basic-jvl-parts jms-intel jms-g2i-modules jms-doc jre-most)
  :print-name "G2 Neural Network Engine")

(def-component nol-classic-documentation
  :parts (nol-classic-documentation)
  :print-name "G2 NOL Classic Documentation")

;;;; Parts


(def-part nolstudio-data-eva
    :version :50r0-EVA 
    :print-name "G2 NOL Studio Data Evaluation"
    :source nols
    :source-filename "NolStudioDataEva.jar"
    :destination-directory nolstudio
	:destination-filename NolStudioData.jar)

(def-part nolstudio-data
    :version :50r0 
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
    :version :50r0 
    :print-name "G2 NOL Studio Math Library"
    :source nols
    :source-filename "NolStudioMath.jar"
    :destination-directory nolstudio)

(def-part nolstudio-core-misc-demolicense
    :version :50r0 
    :print-name "G2 NOL Studio Core Misc"
    :source nols
    :source-filename ("demolicense.txt" "known-bugs.txt")
    :destination-directory nolstudio)

(def-part nolstudio-gui
    :version :50r0 
    :source-filename "NolStudioGUI.jar"
    :source nols
    :destination-directory nolstudio
    :print-name "G2 NOL Studio GUI")

(def-part nolstudio-gui-misc
    :version :50r0 
    :source nols
    :destination-directory nolstudio
    :source-filename ("readme.html")
	:shortcuts (nolstudio-readme))

(def-shortcut nolstudio-readme
    :folder-name nol-shortcut-folder-name
    :application-display-name "NeurOn-Line Studio Readme"
    :application-directory nolstudio
    :target-name readme.html)

(def-part nolstudio-batch
    :version :50r0 
    :source nols
    :destination-directory nolstudio
    :platforms ("nt")
    :source-filename ("nolstudio.bat")
	:postinstall-code "replace_rootdir(\"nolstudio\", \"nolstudio.bat\");"
	:shortcuts (nolstudio-batch-file))

(def-shortcut nolstudio-batch-file
    :folder-name nol-shortcut-folder-name
    :application-display-name "NeurOn-Line Studio"
    :application-directory nolstudio
    :target-name nolstudio.bat
	:icon-file "../nol/bin/nol.ico"
	:icon-index 0
    :run-style minimized)

(def-part nolstudio-examples
    :version :50r0 
    :source nols
    :source-subdirectory project
    :destination-directory nolstudio/project)

(def-part nolstudio-documentation
    :version :50r0 
    :source nols
    :source-subdirectory doc
    :destination-directory doc/nolstudio
    :shortcuts (nolstudio-users-guide))

(def-shortcut nolstudio-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "NeurOn-Line Studio Users' Guide"
    :application-directory doc/nolstudio
    :target-name NOLStudioUsersGuide.pdf)

(def-part nolstudio-window-misc
    :source nols
    :version :50r0 
    :source-filename ("RegisterControls.bat" "UnRegisterControls.bat")
    :platforms ("nt")
	:destination-directory nolstudio)

(def-part nolstudio-ActiveX-control
    :source nols
    :version :50r0 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "NolOnline.dll"
    :platforms ("nt")
    :environment-variables (nolstudio_home nolstudio-jre)
    :shortcuts (nolstudio-install-control nolstudio-uninstall-control))

(def-shortcut nolstudio-install-control
    :folder-name nol-shortcut-folder-name
    :application-display-name "Register G2 NeurOn-Line Control"
    :application-directory nolstudio
    :target-name RegisterControls.bat
    :run-style minimized)

(def-shortcut nolstudio-uninstall-control
    :folder-name nol-shortcut-folder-name
    :application-display-name "Unregister G2 NeurOn-Line Control"
    :application-directory nolstudio
    :target-name UnRegisterControls.bat
    :run-style minimized)

(def-part nolstudio-window-classic-dll
    :source nols
    :version :50r0 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "jnol.dll"
    :platforms ("nt"))

(def-part nolstudio-tw2-kbs-intelnt
    :version :12r4
    :source tw2
    :source-subdirectory components/kbs
    :source-filename "jlintf.kb"
    :platforms ("nt")
    :destination-directory "nol/kbs")

(def-part nolstudio-deploy-library
    :source nols
    :version :50r0
    :destination-directory nolstudio
    :source-filename "NolStudioDeploy.jar")

(def-part nolstudio-online-batch
    :source nols
    :version :50r0
    :source-filename "onlinenolstudio.bat"
    :platforms ("nt")
	:postinstall-code "replace_rootdir(\"nolstudio\", \"onlinenolstudio.bat\");"
	:destination-directory nolstudio
	)

(def-part nolstudio-deploy-misc
    :source nols
    :version :50r0
    :source-filename "nolonline.bat"
    :platforms ("nt")
	:postinstall-code "replace_rootdir(\"nolstudio\", \"nolonline.bat\");"
	:destination-directory nolstudio
	)

(def-part nol-classic-kb
    :source nol
    :version :50r0
    :source-subdirectory kbs
    :indep t
    :destination-directory "nol/kbs"
    :source-filename ("nol.kb" "nolapps.kb" "gnneapps.kb" "noldemo.kb" "nolexten.kb" "nolx.kb" 
				"nolxapps.kb" "nolui.kb" "java-module.kb"  "nolspack.kb" "nolstudio.kb"))

(def-part nol-classic-gnne
    :source nol
    :version :50r0
    :source-subdirectory kbs
    :indep t
    :destination-directory "nol/kbs"
    :source-filename ("gnne.kb"))

(def-part nol-classic-nt
    :source nol
    :version :50r0
    :source-subdirectory bin
    :indep t
    :destination-directory "nol/bin"
    :platforms ("nt")
    :source-filename ("ntnol.exe" "nol.ico")
    :shortcuts (nolapps-shortcut gnneapps-shortcut gnnedemo-shortcut noldemo-shortcut nolbakerydemo-shortcut nolbleachdemo-shortcut))

(def-shortcut nolapps-shortcut
     :folder-name nol-shortcut-folder-name
     :application-display-name "NeurOn-Line Application"
     :application-directory nol
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\kbs\\nolapps.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut gnneapps-shortcut
     :folder-name nol-shortcut-folder-name
     :application-display-name "Neural Network Engine Application"
     :application-directory nol
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\kbs\\gnneapps.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut gnnedemo-shortcut
     :folder-name nol-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "G2 NeurOn-Line"
     :application-display-name "Neural Network Engine Demo"
	 :application-directory nol/examples/gnne-demo
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\examples\\gnne-demo\\gnne-demo.kb -configfile ..\\nol\\examples\\gnne-demo\\config.txt"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut noldemo-shortcut
     :folder-name nol-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "G2 NeurOn-Line"
     :application-display-name "NeurOn-Line Total Demo"
	 :application-directory nol/examples/total-demo
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\examples\\total-demo\\total-demo.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut nolbakerydemo-shortcut
     :folder-name nol-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "G2 NeurOn-Line"
;;    :subsubfolder-name "GNNE"
     :application-display-name "NeurOn-Line Bakery Demo"
	 :application-directory nol/examples/bakery-demo
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\examples\\bakery-demo\\bakery.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut nolbleachdemo-shortcut
     :folder-name nol-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "G2 NeurOn-Line"
;;    :subsubfolder-name "GNNE"
     :application-display-name "NeurOn-Line Bleach Demo"
	 :application-directory nol/examples/bleach-demo
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\examples\\bleach-demo\\bleach-plant.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-part nol-classic-documentation
    :source nol
    :version :50r0
    :indep t
    :source-subdirectory noldoc
    :destination-directory doc/nol
	:shortcuts (nol-users-guide nol-reference-guide gnne-users-guide))

(def-part gnne-demo
    :source nol
    :version :50r0
    :indep t
    :source-subdirectory examples/gnne-demo
    :destination-directory nol/examples/gnne-demo)

(def-part gnne-demo-config
    :source nol
    :version :50r0
    :indep t
    :source-subdirectory examples/gnne-demo
    :destination-directory nol/examples/gnne-demo
    :source-filename ("config.txt")
    :postinstall-code "replace_rootdir(\"nol\examples\gnne-demo\", \"config.txt\");"
	)

(def-part nol-total-demo
    :source nol
    :version :50r0
    :indep t
    :source-subdirectory examples/total-demo
    :destination-directory nol/examples/total-demo)

(def-part nol-bakery-demo
    :source nol
    :version :50r0
    :indep t
    :source-subdirectory examples/bakery-demo
    :destination-directory nol/examples/bakery-demo)

(def-part nol-bleach-demo
    :source nol
    :version :50r0
    :indep t
    :source-subdirectory examples/bleach-demo
    :destination-directory nol/examples/bleach-demo)

(def-shortcut nol-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "NeurOn-Line Users' Guide"
    :application-directory doc/nol
    :target-name nolusersguide.pdf)

(def-shortcut nol-reference-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "NeurOn-Line Reference Manual"
    :application-directory doc/nol
    :target-name nolrm.pdf)

(def-shortcut gnne-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "G2 NeurOn-Line"
    :application-display-name "Neural Net Engine Users' Guide"
    :application-directory doc/nol
    :target-name GNNEUsersGuide.pdf)

(def-part nol-readme
    :source nols
    :version :50r0
    :source-filename "readme-nol-bundle.html"
    :shortcuts (nol-readme))

(def-shortcut nol-readme
    :folder-name nol-shortcut-folder-name
    :application-display-name "Readme for G2 NeurOn-Line Bundle"
    :application-directory ""
    :target-name readme-nol-bundle.html)

;;;
;;;======= Begin G2i Modules =======
;;;

(def-part nol-g2i-modules
  :source g2i
  :version :22b2
  :indep t
  :source-subdirectory kbs
  :source-filename ("grtl.kb" "gdpm.kb" "gdsm.kb" "gedp.kb")
  :destination-directory "g2i/kbs")

;;;
;;;======= End G2i Modules =======
;;;
;;;

