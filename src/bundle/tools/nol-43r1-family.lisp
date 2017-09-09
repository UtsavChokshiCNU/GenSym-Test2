;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; NOL-FAMILY - NOL Family Definitions.  Requires G2-FAMILY (with bundle.lisp loaded).

;; Mark H. David; yduJ; gchen

;;; The current shipping version of NOL is 4.3 Rev. 1 ("43r1").  

(defvar g2-shortcut-folder-name "Gensym NOL 4.3r1")
(defvar nol-shortcut-folder-name "Gensym NOL 4.3r1")

(require "g2-71r2-family")			; G2 7.1r2
(provide 'nol-43r1-family)


;;;; NOL Family (prototype)


;;;; Family: NOL

(def-family nol-43r1
    :index 39
    :file-syntax-version 20
    :bundles (nol-studio-evaluation
	       nol-studio-development
	       nol-premium-deployment
	       nol-studio-deployment
	       nol-premium-development)
    :print-name "NOL"
    :directory "nol-4.3r1"
    :guid "4d77835c-1a3a-4996-8a46-4a5dfc20db75" ; 4.3r1
    :compatible-previous-versions (
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
				(1 "-jun25-2005") (1 "-jul25-2005") (1 "-aug25-2005")
				(1 "-sep25-2005") (1 "-oct25-2005") (1 "-nov25-2005")
				(1 "-dec25-2005") (1 "-jan25-2006") (1 "-feb25-2006")
			  ))

(def-g2-ok-components (neuron-line-premium-deployment :obfuscate t) nol "NeurOnline Premium Deployment"
		      (4 8 12 16 20 24 28 32
				(1 "-jun25-2005") (1 "-jul25-2005") (1 "-aug25-2005")
				(1 "-sep25-2005") (1 "-oct25-2005") (1 "-nov25-2005")
				(1 "-dec25-2005") (1 "-jan25-2006") (1 "-feb25-2006")
			  ))


;;;; Bundles nol-studio-evaluation nol-studio-development nol-premium-deployment nol-studio-deployment nol-premium-development

;; Note: there is no longer a "bundle directory" used by the bundle installer.
;; Previously, NOL specified dev, premdep, dep, and premdev for the following,
;; respectively. (MHD 1/2/01)

(defvar nols-basic-components '(nolstudio-examples nolstudio-documentation nol-readme))

(def-bundle nol-studio-evaluation
    :version :43r1
    :components  (nolstudio-core-evaluation nols-basic-components nolstudio-gui nolstudio-dynamic-lib)
    :platforms ("nt")
    :print-name "NOL Studio Evaluation")

(def-bundle nol-studio-development
    :version :43r1										         
    :components  (nolstudio-core-development nols-basic-components nolstudio-gui nolstudio-dynamic-lib)
    :platforms ("nt" "hpux" "sparcsol")
    :print-name "NOL Studio Development")

(def-bundle nol-studio-deployment
    :version :43r1
    :components (nolstudio-core-development nols-basic-components nolstudio-window-deployment nolstudio-dynamic-lib)
    :platforms ("nt")
    :print-name "NOL Studio Deployment")

(def-bundle nol-premium-development
    :version :43r1
    :components (nolstudio-core-development nols-basic-components nolstudio-gui
				 nolstudio-g2-deployment nolstudio-window-deployment nolstudio-dynamic-lib
				 core-g2-components additional-g2-development-components
				 nol-classic nol-classic-documentation 
				 neuron-line-premium-development-family-ok-components
				 g2-gold-hp-fix-kbs	nol-classic-g2i
				 )
    :platforms ("nt" "hpux" "sparcsol")
    :print-name "NOL Premium Development")

(def-bundle nol-premium-deployment
    :version :43r1
    :components (nolstudio-core-development nols-basic-components
				 nolstudio-g2-deployment nolstudio-window-deployment nolstudio-dynamic-lib
				 core-g2-components additional-g2-deployment-components 
				 nol-classic nol-classic-documentation 
				 neuron-line-premium-deployment-family-ok-components
				 g2-gold-hp-fix-kbs	nol-classic-g2i
				) 
    :platforms ("nt" "hpux" "sparcsol")
    :print-name "NOL Premium Deployment")




;;;; Components


(def-component nolstudio-core-evaluation
    :parts (nolstudio-data-eva nolstudio-math-library jre
			   nolstudio-core-misc-demolicense)
    :print-name "NOL Studio Core Evaluation")


(def-component nolstudio-core-development
    :parts (nolstudio-data nolstudio-math-library jre
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
  :parts (nolstudio-deploy-library nolstudio-javalink-kbs
				   nolstudio-tw2-kbs nolstudio-tw2-kbs-intelnt 
				   nolstudio-deploy-misc nolstudio-deploy-script pi-bridge)
  :print-name "NolStudio G2 Deployment")

(def-component nol-classic
  :parts (nol-classic nol-classic-nt nol-classic-unix nol-total-demo nol-bakery-demo nol-bleach-demo gda-43r1 gda-jvl-43r1 gda-g2i-43r1 nol-jvl-43r1)
  :print-name "NOL Classic")

(def-component nol-classic-g2i
  :parts (nol-classic-gnne nol-g2i-modules g2i-core-modules odbc-bridge opclink-bridge jmail-part jmail-doc jms-part jms-doc jre)
  :print-name "Gensym Neural Network Engine")

(def-component nol-classic-documentation
  :parts (nol-classic-documentation)
  :print-name "NOL Classic Documentation")

;;;; Parts


(def-part nolstudio-data-eva
    :version :43r1-EVA 
    :print-name "Data Evaluation"
    :source nols
    :source-filename "NolStudioDataEva.jar"
    :destination-directory nolstudio
	:destination-filename NolStudioData.jar)

(def-part nolstudio-data
    :version :43r1 
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
    :version :43r1 
    :print-name "Math Library"
    :source nols
    :source-filename "NolStudioMath.jar"
    :destination-directory nolstudio)

(def-part nolstudio-core-misc-demolicense
    :version :43r1 
    :print-name "Core Misc"
    :source nols
    :source-filename ("demolicense.txt" "known-bugs.txt")
    :destination-directory nolstudio)

(def-part nolstudio-gui
    :version :43r1 
    :source-filename "NolStudioGUI.jar"
    :source nols
    :destination-directory nolstudio
    :print-name "NolStudio GUI")

(def-part nolstudio-gui-misc
    :version :43r1 
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
    :version :43r1 
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
    :version :43r1 
    :source nols
    :source-subdirectory examples
    :destination-directory nolstudio/examples)

(def-part nolstudio-documentation
    :version :43r1 
    :source nols
    :source-subdirectory doc
    :destination-directory nolstudio/doc
    :shortcuts (nolstudio-users-guide))

(def-shortcut nolstudio-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "NOL"
    :application-display-name "NOLStudio Users' Guide"
    :application-directory nolstudio/doc
    :target-name NOLStudioUsersGuide.pdf)

(def-part nolstudio-window-misc
    :source nols
    :version :43r1 
    :source-filename ("RegisterControls.bat" "UnRegisterControls.bat")
    :platforms ("nt")
	:destination-directory nolstudio)

(def-part nolstudio-ActiveX-control
    :source nols
    :version :43r1 
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
    :version :43r1 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "jnol.dll"
    :platforms ("nt"))

(def-part nolstudio-hp-classic-dll
    :source nols
    :version :43r1 
    :source-subdirectory bin
    :destination-directory nolstudio/bin
    :source-filename "libjnol.sl"
    :platforms ("hpux"))

(def-part nolstudio-sol-classic-dll
    :source nols
    :version :43r1 
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

(def-part nolstudio-javalink-kbs
	:version :12r8-GH13
    :source jvl
    :source-subdirectory kbs
    :source-filename "javalink.kb"
    :platforms ("nt" "hpux" "sparcsol")
    :destination-directory nol
	)

(def-part nolstudio-deploy-library
    :source nols
    :version :43r1
    :destination-directory nolstudio
    :source-filename "NolStudioDeploy.jar")

(def-part nolstudio-deploy-misc
    :source nols
    :version :43r1
    :source-filename "nolonline.bat"
    :platforms ("nt")
	:postinstall-code "replace_rootdir(\"nolstudio\", \"nolonline.bat\");"
	:destination-directory nolstudio
	)

(def-part nol-classic
    :source nol
    :version :43r1
    :indep t
    :destination-directory nol
    :source-filename ("nol.kb" "nolapps.bat" "nolapps" "gnne.bat" "gnne" "nolapps.kb" "noldemo.kb" "nolexten.kb" "nol.kb"  "nolx.kb" 
				"nolxapps.kb" "nolxapps.bat" "nolxapps"
		       "nolui.kb" "java-module.kb"  "nolspack.kb" "nolstudio.kb"))

(def-part nol-classic-gnne
    :source nol
    :version :43r1
    :indep t
    :destination-directory nol
    :source-filename ("gnne.kb"))

(def-part nol-classic-nt
    :source nol
    :version :43r1
    :indep t
    :destination-directory nol
    :platforms ("nt")
    :source-filename ("ntnol.exe")
    :shortcuts (noldemo-shortcut nolapp-shortcut nolbakerydemo-shortcut nolbleachdemo-shortcut))

	
(def-shortcut nolapp-shortcut
    :folder-name nol-shortcut-folder-name
    :subfolder-name "NeurOnLine"
    :application-display-name "NOL Application"
    :application-directory "nol"
    :target-name "nolapps.bat"
	)

(def-shortcut noldemo-shortcut
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "NOL"
    :application-display-name "NOL Total Demo"
    :application-directory nol/noldemo/total-demo
	:target-name "total-demo.bat"   
	)

(def-shortcut nolbakerydemo-shortcut
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "NOL"
    :application-display-name "NOL Bakery Demo"
    :application-directory nol/noldemo/bakery-demo
	:target-name "bakery-demo.bat"   
	)

(def-shortcut nolbleachdemo-shortcut
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "NOL"
    :application-display-name "NOL Bleach Demo"
    :application-directory nol/noldemo/bleach-demo
	:target-name "bleach-demo.bat"   
	)


(def-part nol-classic-unix
    :source nol
    :version :43r1
    :indep t
    :destination-directory nol
    :platforms ("hpux" "sparcsol")
    :source-filename ("solnol" "hpuxnol" "noldemounix"))


(def-part gda-43r1
    :source gda
    :version :43r1
    :indep t
    :destination-directory gda
    :source-filename ("gcc.kb" "gda.kb" "gdaapps.kb" "gdabasic.kb" "gdabsdlg.kb" "gdacerel.kb" "gdacore2.kb" "gdadlg.kb" "gdareact.kb" "gdasound.exe" "gdatank.kb" "gdl.kb" "gdluisup.kb" "gqm.kb" "gqmv.kb" "grl.kb"))

(def-part gda-jvl-43r1
    :source jvl
    :version :12r8-GH13
	:source-subdirectory kbs
	:platforms ("hpux" "sparcsol" "nt")
    :destination-directory gda
    :source-filename ("g2evliss.kb" "javalink.kb"))

(def-part gda-g2i-43r1
	:source g2i
    :version :12r1-GG14
	:indep t
	:source-subdirectory kbs
    :destination-directory gda
    :source-filename ("gens.kb" "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb"))

(def-part nol-jvl-43r1
    :source jvl
    :version :12r8-GH13
	:source-subdirectory kbs
	:platforms ("hpux" "sparcsol" "nt")
    :destination-directory javalink/kbs
    :source-filename ("g2evliss.kb" "javalink.kb" "jgidemo.kb"))

(def-part nol-classic-documentation
    :source nol
    :version :43r1
    :indep t
    :source-subdirectory noldoc
    :destination-directory nol/noldoc
	:shortcuts (nol-users-guide nol-reference-guide gnne-users-guide))

(def-part nol-total-demo
    :source nol
    :version :43r1
    :indep t
    :source-subdirectory noldemo/total-demo
    :destination-directory nol/noldemo/total-demo)

(def-part nol-bakery-demo
    :source nol
    :version :43r1
    :indep t
    :source-subdirectory noldemo/bakery-demo
    :destination-directory nol/noldemo/bakery-demo)

(def-part nol-bleach-demo
    :source nol
    :version :43r1
    :indep t
    :source-subdirectory noldemo/bleach-demo
    :destination-directory nol/noldemo/bleach-demo)

(def-shortcut nol-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "NOL"
    :application-display-name "NOL Users' Guide"
    :application-directory nol/noldoc
    :target-name nolusersguide.pdf)

(def-shortcut nol-reference-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "NOL"
    :application-display-name "NOL Reference Manual"
    :application-directory nol/noldoc
    :target-name nolrm.pdf)

(def-shortcut gnne-users-guide
    :folder-name nol-shortcut-folder-name
    :subfolder-name "Documentation"
    :subsubfolder-name "NOL"
    :application-display-name "GNNE Users' Guide"
    :application-directory nol/noldoc
    :target-name GNNEUsersGuide.pdf)

(def-part nol-readme
    :source nols
    :version :43r1
    :source-filename "readme-nol-bundle.html"
    :shortcuts (nol-readme))

(def-shortcut nol-readme
    :folder-name nol-shortcut-folder-name
    :application-display-name "Readme for NOL Bundle"
    :application-directory ""
    :target-name readme-nol-bundle.html)


(def-part nolstudio-script
    :version :43r1 
    :source nols
    :destination-directory nolstudio
    :platforms ("hpux" "sparcsol")
    :source-filename ("nolstudio"))

(def-part nolstudio-deploy-script
    :version :43r1 
    :source nols
    :destination-directory nolstudio
    :platforms ("hpux" "sparcsol")
    :source-filename ("nolonline"))

(def-part g2-gold-hp-fix-kbs
    :version :43r1-HP
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

;;;
;;;======= Begin G2i Modules =======
;;;

(def-part g2i-core-modules
  :source g2i
  :version :12r1-GG14
  :indep t
  :source-subdirectory kbs
  :source-filename ("gens.kb" "gerr.kb" "grtl.kb"  "glf.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb" "gqsdemo.kb" "resources-english.txt" "config.txt" "gevm.kb")
  :destination-directory "g2i/kbs")

(def-part nol-g2i-modules
  :source g2i
  :version :12r1-GG14
  :indep t
  :source-subdirectory kbs
  :source-filename ("gdpm.kb" "gdsm.kb")
  :destination-directory "g2i/kbs")

;;;
;;;======= End G2i Modules =======
;;;
;;;
;;;=== ODBC Bridge delivered with G2 7.1r2
(def-part odbc-bridge
    :version :60r11
    :source g2odbc
    :destination-directory odbc
    :platforms ("nt"))

;;;=== OPCLink Bridge delivered with G2 7.0r1
(def-part opclink-bridge
  :source opclink
  :version :21r1
  :platforms ("nt")
  :source-subdirectory "KBs"
  :source-filename ("launch.kb")
  :destination-directory "opclink/kbs")

;;;=== PI Bridge delivered with G2 7.0r1
(def-part pi-bridge
  :source g2pi
  :version :50r3
  :platforms ("nt")
  :source-filename ("g2-pi.kb" "gensym-raised-button.kb")
  :destination-directory "pi")


;;;======= Begin JMail =======
;;;
(def-part jmail-part
  :source jmail
  :version :12r0
  :platforms ("nt")
  :destination-directory jmail
  :postinstall-code "replace_rootdir(\"jmail\"^\"bin\", \"StartJMailBridge.bat\");"
  :shortcuts (jmail-shortcut jmail-demo-shortcut)
)

(def-part jmail-doc
  :source jmaildoc
  :version :10r0
  :platforms ("nt")
  :indep t
  :destination-directory "doc/bridges/jmail"
  :shortcuts (jmail-doc-shortcut)
)

(def-shortcut jmail-doc-shortcut
  :folder-name optegrity-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "JMail User's Guide"
  :application-directory "doc/bridges/jmail"
  :target-name "g2jmailbridge.pdf")

(def-shortcut jmail-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :application-display-name "JMail Bridge"
    :application-directory "jmail\\bin"
    :target-name "StartJMailBridge.bat")

(def-shortcut jmail-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "JMail"
    :application-display-name "JMail Tutorial"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\jmail\\examples\\jmail-demo.kb")

;;;
;;;======= End JMail =======
;;;
;;;
;;;======= Begin JMS =======
;;;

(def-part jms-doc
  :source jmsdoc
  :version :10r0
  :platforms ("nt")
  :indep t
  :destination-directory "doc/bridges/jms"
  :shortcuts (jms-doc-shortcut)
)

(def-shortcut jms-doc-shortcut
  :folder-name optegrity-shortcut-folder-name
  :subfolder-name "Documentation"
  :subsubfolder-name "Bridges"
  :application-display-name "JMS User's Guide"
  :application-directory "doc/bridges/jms"
  :target-name "g2jmslink.pdf")

(def-part jms-part
  :source jms
  :version :12r0
  :platforms ("nt")
  :destination-directory jms
  :postinstall-code "replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-j2ee.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-jboss.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-FioranoMQ.bat\");replace_rootdir(\"jms\"^\"bin\", \"StartJmsBridge-WebSphereMQ.bat\");"
  :shortcuts (jms-j2ee-shortcut jms-jboss-shortcut jms-FioranoMQ-shortcut jms-WebSphereMQ-shortcut jms-demo-shortcut)
)

(def-shortcut jms-demo-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Examples"
    :subsubfolder-name "JMS"
    :application-display-name "JMS Tutorial"
    :application-directory "optegrity\\bin"
    :target-name "StartServer.bat"
    :parameters "..\\..\\jms\\examples\\jms-demo.kb")

(def-shortcut jms-SonicMQ-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS Sonic MQ Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-SonicMQ.bat")

(def-shortcut jms-FioranoMQ-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS Fiorano MQ Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-FioranoMQ.bat")

(def-shortcut jms-WebSphereMQ-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS WebSphere MQ Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-WebSphereMQ.bat")

(def-shortcut jms-j2ee-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS J2EE Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-j2ee.bat")

(def-shortcut jms-jboss-shortcut
    :folder-name optegrity-shortcut-folder-name
    :subfolder-name "Bridges"
    :subsubfolder-name "JMS"
    :application-display-name "JMS JBoss Bridge"
    :application-directory "jms\\bin"
    :target-name "StartJmsBridge-jboss.bat")

;;;
;;;======= End JMS =======
;;;
;;;
;;;

