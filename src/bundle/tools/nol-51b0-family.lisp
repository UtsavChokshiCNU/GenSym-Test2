;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; NOL-FAMILY - NOL Family Definitions.  Requires G2-FAMILY (with bundle.lisp loaded).

;; Mark H. David; yduJ; gchen

;;; The current shipping version of NOL is 5.0 Rev. 1 ("50r1").  

(defvar g2-shortcut-folder-name "Gensym G2 NOL 5.0r1")
(defvar nol-shortcut-folder-name "Gensym G2 NOL 5.0r1")

(require "g2-83a1-family")        ; g2-83a1-family       
(provide 'nol-51b0-family)	; NOL 5.1b0



;;;; NOL Family (prototype)


;;;; Family: NOL
;; MODIFY
;;  If a new GUID is created (indication of a new key for installation), then change the :guid to
;;    the new GUID that was generated.

(def-family nol-51b0
    :index 74
    :file-syntax-version 20
    :bundles (nol-studio-evaluation
	       nol-studio-development
	       nol-premium-deployment
	       nol-studio-deployment
	       nol-premium-development)
    :print-name "NOL"
    :directory "nol-5.0r1"
    :guid "6e4d81e7-b111-4154-8eb9-4e3011637ab6" ; 5.0r1
    :compatible-previous-versions (
			("5.0r0" "b598691f-ea2a-4e0d-8946-561b9aa0287d")
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
			  (1 "-nov25-2006") (1 "-dec25-2006")
			  (1 "-jan25-2007") (1 "-feb25-2007") (1 "-mar25-2007") (1 "-apr25-2007") 
			  ))

(def-g2-ok-components (neuron-line-premium-deployment :obfuscate t) nol "NeurOnline Premium Deployment"
		      (4 8 12 16 20 24 28 32
			  (1 "-nov25-2006") (1 "-dec25-2006")
			  (1 "-jan25-2007") (1 "-feb25-2007") (1 "-mar25-2007")	(1 "-apr25-2007") 
			  ))


;;;; Bundles nol-studio-evaluation nol-studio-development nol-premium-deployment nol-studio-deployment nol-premium-development

;; Note: there is no longer a "bundle directory" used by the bundle installer.
;; Previously, NOL specified dev, premdep, dep, and premdev for the following,
;; respectively. (MHD 1/2/01)

(defvar nols-basic-components '(nolstudio-examples nolstudio-documentation nol-readme))

(def-bundle nol-studio-evaluation
    :version :50r1
    :components  (nolstudio-core-evaluation nols-basic-components nolstudio-gui nolstudio-dynamic-lib)
    :platforms ("nt")
    :print-name "G2 NOL Studio Evaluation")

(def-bundle nol-studio-development
    :version :50r1										         
    :components  (nolstudio-core-development nols-basic-components nolstudio-gui nolstudio-dynamic-lib)
    :platforms ("nt")
    :print-name "G2 NOL Studio Development")

(def-bundle nol-studio-deployment
    :version :50r1
    :components (nolstudio-core-development nols-basic-components nolstudio-window-deployment nolstudio-dynamic-lib)
    :platforms ("nt")
    :print-name "G2 NOL Studio Deployment")

(def-bundle nol-premium-development
    :version :50r1
    :components (nolstudio-core-development nols-basic-components nolstudio-gui
				 nolstudio-g2-deployment nolstudio-window-deployment nolstudio-dynamic-lib
				 core-g2-components additional-g2-components additional-g2-development-components
				 nol-classic nol-classic-documentation 
				 neuron-line-premium-development-family-ok-components
				 nol-classic-g2i
				 )
    :platforms ("nt")
    :print-name "G2 NOL Premium Development")

(def-bundle nol-premium-deployment
    :version :50r1
    :components (nolstudio-core-development nols-basic-components
				 nolstudio-g2-deployment nolstudio-window-deployment nolstudio-dynamic-lib
				 core-g2-components additional-g2-components additional-g2-deployment-components 
				 nol-classic nol-classic-documentation 
				 neuron-line-premium-deployment-family-ok-components
				 nol-classic-g2i
				) 
    :platforms ("nt")
    :print-name "G2 NOL Premium Deployment")




;;;; Components


(def-component nolstudio-core-evaluation
    :parts (nolstudio-data-eva nolstudio-math-library jre-most
			   nolstudio-core-misc-demolicense)
    :print-name "G2 NOL Studio Core Evaluation"
	:include-in-contents (nolstudio-math-library))

(def-component nolstudio-core-development
    :parts (nolstudio-data nolstudio-math-library jre-most
			   nolstudio-core-misc-demolicense)
    :print-name "G2 NOL Studio Core"
	:include-in-contents (nolstudio-math-library))

(def-component nolstudio-gui
    :parts (nolstudio-gui nolstudio-gui-misc nolstudio-batch nolstudio-online-batch)
    :print-name "G2 NOL Studio GUI"
	:include-in-contents (nolstudio-gui))

(def-component nolstudio-examples
  :parts (nolstudio-examples)
  :print-name "G2 NOL Studio Examples"
  :include-in-contents (nolstudio-examples))

(def-component nolstudio-documentation
  :parts (nolstudio-documentation)
  :print-name "G2 NOL Studio Documentation"
  :include-in-contents (nolstudio-documentation))

(def-component nol-readme
  :parts (nol-readme)
  :print-name "Readme for G2 NOL Bundle"
  :include-in-contents (nol-readme))

(def-component nolstudio-window-deployment
  :parts (nolstudio-window-misc nolstudio-ActiveX-control)
  :platforms ("nt")
  :print-name "G2 NOL Studio Window Deployment"
  :include-in-contents (nolstudio-window-misc))

(def-component nolstudio-dynamic-lib
  :parts (nolstudio-window-classic-dll)
  :print-name "G2 NOL Studio Window Classic DLL"
  :include-in-contents (nolstudio-window-classic-dll))

(def-component nolstudio-g2-deployment
  :parts (nolstudio-deploy-library 
				   nolstudio-deploy-misc pikbs)
  :print-name "G2 NOL Studio G2 Deployment"
  :include-in-contents (nolstudio-deploy-library))

(def-component nol-classic
  :parts (nol-classic-kb nol-classic-nt gnne-demo gnne-demo-config nol-total-demo nol-bakery-demo nol-bleach-demo gda-50r1p)
  :print-name "G2 NOL Classic"
  :include-in-contents (gnne-demo))

(def-component nol-classic-g2i
  :parts (nol-classic-gnne nol-g2i-modules g2i-core-modules ODBCbridge opclink jmail-intel jmail-doc basic-jvl-parts jms-intel jms-g2i-modules jms-doc jre-most)
  :print-name "G2 Neural Network Engine"
  :include-in-contents (nol-classic-gnne))

(def-component nol-classic-documentation
  :parts (nol-classic-documentation)
  :print-name "G2 NOL Classic Documentation"
  :include-in-contents (nol-classic-documentation))

;;;; Parts


(def-part nolstudio-data-eva
    :version :50r1-EVA 
    :print-name "G2 NOL Studio Data Evaluation"
    :source nols
    :source-filename "NolStudioDataEva.jar"
    :destination-directory nolstudio
	:destination-filename NolStudioData.jar)

(def-part nolstudio-data
    :version :50r1 
    :print-name "G2 NOL Studio Data"
    :source nols
    :source-filename "NolStudioData.jar"
    :destination-directory nolstudio)

(def-part nolstudio-math-library
    :version :50r1 
    :print-name "G2 NOL Studio Math Library"
    :source nols
    :source-filename "NolStudioMath.jar"
    :destination-directory nolstudio)

(def-part nolstudio-core-misc-demolicense
    :version :50r1 
    :print-name "G2 NOL Studio Core Misc"
    :source nols
    :source-filename ("demolicense.txt" "known-bugs.txt")
    :destination-directory nolstudio)

(def-part nolstudio-gui
    :version :50r1 
    :source-filename "NolStudioGUI.jar"
    :source nols
    :destination-directory nolstudio
    :print-name "G2 NOL Studio GUI")

(def-part nolstudio-gui-misc
    :version :50r1 
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
    :version :50r1 
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
    :version :50r1 
    :source nols
    :source-subdirectory projects
    :destination-directory nolstudio/projects)

(def-part nolstudio-documentation
    :version :50r1 
    :source nols
    :source-subdirectory doc
    :destination-directory doc/nol/nolstudio
    :shortcuts (nolstudio-users-guide))

(def-shortcut nolstudio-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "NeurOn-Line"
    :application-display-name "NeurOn-Line Studio Users' Guide"
    :application-directory doc/nol/nolstudio
    :target-name NOLStudioUsersGuide.pdf)

(def-part nolstudio-window-misc
    :source nols
    :version :50r1 
    :source-filename ("RegisterControls.bat" "UnRegisterControls.bat")
    :platforms ("nt")
	:destination-directory nolstudio)

(def-part nolstudio-ActiveX-control
    :source nols
    :version :50r1 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "NolOnline.dll"
    :platforms ("nt")
    :shortcuts (nolstudio-install-control nolstudio-uninstall-control))

(def-shortcut nolstudio-install-control
    :folder-name nol-shortcut-folder-name
    :application-display-name "Register NeurOn-Line Control"
    :application-directory nolstudio
    :target-name RegisterControls.bat
    :run-style minimized)

(def-shortcut nolstudio-uninstall-control
    :folder-name nol-shortcut-folder-name
    :application-display-name "Unregister NeurOn-Line Control"
    :application-directory nolstudio
    :target-name UnRegisterControls.bat
    :run-style minimized)

(def-part nolstudio-window-classic-dll
    :source nols
    :version :50r1 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "jnol.dll"
    :platforms ("nt"))

(def-part nolstudio-deploy-library
    :source nols
    :version :50r1
    :destination-directory nolstudio
    :source-filename "NolStudioDeploy.jar")

(def-part nolstudio-online-batch
    :source nols
    :version :50r1
    :source-filename "onlinenolstudio.bat"
    :platforms ("nt")
	:postinstall-code "replace_rootdir(\"nolstudio\", \"onlinenolstudio.bat\");"
	:destination-directory nolstudio
	)

(def-part nolstudio-deploy-misc
    :source nols
    :version :50r1
    :source-filename "nolonline.bat"
    :platforms ("nt")
	:postinstall-code "replace_rootdir(\"nolstudio\", \"nolonline.bat\");"
	:destination-directory nolstudio
	)

(def-part nol-classic-kb
    :source nol
    :version :50r1
    :source-subdirectory kbs
    :indep t
    :destination-directory "nol/kbs"
    :source-filename ("nol.kb" "nolapps.kb" "gnneapps.kb" "noldemo.kb" "nolexten.kb" "nolx.kb" 
				"nolxapps.kb" "nolui.kb" "java-module.kb"  "nolspack.kb" "nolstudio.kb"))

(def-part nol-classic-gnne
    :source nol
    :version :50r1
    :source-subdirectory kbs
    :indep t
    :destination-directory "nol/kbs"
    :source-filename ("gnne.kb"))

(def-part nol-classic-nt
    :source nol
    :version :50r1
    :source-subdirectory bin
    :indep t
    :destination-directory "nol/bin"
    :platforms ("nt")
    :source-filename ("ntnol.exe" "nol.ico")
    :shortcuts (nolapps-shortcut gnneapps-shortcut gnnedemo-shortcut noldemo-shortcut nolbakerydemo-shortcut nolbleachdemo-shortcut))

(def-shortcut nolapps-shortcut
     :folder-name nol-shortcut-folder-name
     :application-display-name "NeurOn-Line Application"
     :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\kbs\\nolapps.kb -start"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut gnneapps-shortcut
     :folder-name nol-shortcut-folder-name
     :application-display-name "Neural Network Engine Application"
     :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\kbs\\gnneapps.kb -start"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut gnnedemo-shortcut
     :folder-name nol-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "NeurOn-Line"
     :application-display-name "Neural Network Engine Demo"
	 :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\projects\\examples\\gnne-demo\\gnne-demo.kb -configfile ..\\nol\\projects\\examples\\gnne-demo\\config.txt"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut noldemo-shortcut
     :folder-name nol-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "NeurOn-Line"
     :application-display-name "NeurOn-Line Total Demo"
	 :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\projects\\examples\\total-demo\\total-demo.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut nolbakerydemo-shortcut
     :folder-name nol-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "NeurOn-Line"
;;    :subsubfolder-name "GNNE"
     :application-display-name "NeurOn-Line Bakery Demo"
	 :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\projects\\examples\\bakery-demo\\bakery.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-shortcut nolbleachdemo-shortcut
     :folder-name nol-shortcut-folder-name
     :subfolder-name "Examples"
     :subsubfolder-name "NeurOn-Line"
;;    :subsubfolder-name "GNNE"
     :application-display-name "NeurOn-Line Bleach Demo"
	 :application-directory g2
     :target-name "StartServer.bat"
     :parameters "-kb ..\\nol\\projects\\examples\\bleach-demo\\bleach-plant.kb"
     :icon-file "../nol/bin/nol.ico"
     :icon-index 0
     :run-style minimized)

(def-part nol-classic-documentation
    :source nol
    :version :50r1
    :indep t
    :source-subdirectory noldoc
    :destination-directory doc/nol
	:shortcuts (nol-users-guide nol-reference-guide gnne-users-guide))


(def-part gda-50r1p
    :source gda
    :version :50r1-P
    :indep t
    :destination-directory gda/kbs
    :source-filename ("gdl.kb"))

(def-part gnne-demo
    :source nol
    :version :50r1
    :indep t
    :source-subdirectory projects/examples/gnne-demo
    :destination-directory nol/projects/examples/gnne-demo)

(def-part gnne-demo-config
    :source nol
    :version :50r1
    :indep t
    :source-subdirectory projects/examples/gnne-demo
    :destination-directory nol/projects/examples/gnne-demo
    :source-filename ("config.txt")
    :postinstall-code "replace_rootdir(\"nol\"^\"projects\"^\"examples\"^\"gnne-demo\", \"config.txt\");"
	)

(def-part nol-total-demo
    :source nol
    :version :50r1
    :indep t
    :source-subdirectory projects/examples/total-demo
    :destination-directory nol/projects/examples/total-demo)

(def-part nol-bakery-demo
    :source nol
    :version :50r1
    :indep t
    :source-subdirectory projects/examples/bakery-demo
    :destination-directory nol/projects/examples/bakery-demo)

(def-part nol-bleach-demo
    :source nol
    :version :50r1
    :indep t
    :source-subdirectory projects/examples/bleach-demo
    :destination-directory nol/projects/examples/bleach-demo)

(def-shortcut nol-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "NeurOn-Line"
    :application-display-name "NeurOn-Line Users' Guide"
    :application-directory doc/nol/nolugrm
    :target-name nolusersguide.pdf)

(def-shortcut nol-reference-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "NeurOn-Line"
    :application-display-name "NeurOn-Line Reference Manual"
    :application-directory doc/nol/nolugrm
    :target-name nolrm.pdf)

(def-shortcut gnne-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "NeurOn-Line"
    :application-display-name "Neural Net Engine Users' Guide"
    :application-directory doc/nol/gnne
    :target-name GNNEUsersGuide.pdf)

(def-part nol-readme
    :source nols
    :version :50r1
    :source-filename "readme-nol-bundle.html"
    :shortcuts (nol-readme))

(def-shortcut nol-readme
    :folder-name nol-shortcut-folder-name
    :application-display-name "Readme for NeurOn-Line Bundle"
    :application-directory ""
    :target-name readme-nol-bundle.html)

;;;
;;;======= Begin G2i Modules =======
;;;

(def-part nol-g2i-modules
  :source g2i
  :version :22r2
  :indep t
  :source-subdirectory kbs
  :postinstall-code "replace_rootdir(\"g2i\"^\"kbs\", \"config.txt\");"
  :source-filename ("gdpm.kb" "gedp.kb")
  :destination-directory "g2i/kbs")

;;;
;;;======= End G2i Modules =======
;;;
;;;

