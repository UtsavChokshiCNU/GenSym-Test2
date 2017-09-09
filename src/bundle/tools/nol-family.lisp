;; -*- mode: lisp; package: bundle -*-
(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; NOL-FAMILY - NOL Family Definitions.  Requires G2-FAMILY (with bundle.lisp loaded).

;; Mark H. David; yduJ

(require 'g2-family)
(provide 'nol-family)


;;;; NOL Family (prototype)


;;; Note: through a misunderstanding, "NOLS" or "nols" sometimes refers to
;;; NeurOnLine (NOL), as opposed to NOL Studio. There have been several changes
;;; today to take this out of the users' view.  However, a few instances still
;;; remain.  Going forward, this naming error should be phased out.
;;; Incrementing bundle version from 22r0 to 22r0a.  A new GUID is being issued
;;; in accordance.  (MHD 2/14/01)



;;;; Family: NOL

(def-family nol
    :index 2
    :file-syntax-version 20
    :bundles (nol-studio-development
	       nol-premium-deployment
	       nol-studio-deployment
	       nol-premium-development)
    :print-name "NOL"
    :directory "nol"
    :platforms ("nt")
    :splash-screen "nol-setup.bmp"
    :readme-file "nol-readme.txt"
    :guid "243D4BB6-9EE7-11D4-8111-00A02431D004" ; "2.2r0b"
    :previous-versions (("2.2r0" "243D4BAD-9EE7-11D4-8111-00A02431D004")
			("2.2r0a" "243D4BB4-9EE7-11D4-8111-00A02431D004")
			;; add more here
			)
    :license-text "standard-license.txt")


;;;; ok file definitions
;; the following forms create variables containing parts and components for all of the
;; ok files, which variables will be referenced in the bundle's components. They are:
;; neuron-line-premium-development-family-ok-components,
;; neuron-line-premium-deployment-family-ok-components
(def-g2-ok-components neuron-line-premium-development nols "NeurOnline Premium Development"
		      (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))

(def-g2-ok-components neuron-line-premium-deployment nols "NeurOnline Premium Deployment"
		      (4 8 12 16 20 24 28 32))


;;;; Bundles nol-studio-development nol-premium-deployment nol-studio-deployment nol-premium-development

;; Note: there is no longer a "bundle directory" used by the bundle installer.
;; Previously, NOL specified dev, premdep, dep, and premdev for the following,
;; respectively. (MHD 1/2/01)

(defvar nol-basic-components '(nolstudio-examples nolstudio-documentation nolstudio-jre))

(def-bundle nol-studio-development
    :version :22r0b
    :components  (nolstudio-core-development nol-basic-components nolstudio-gui)
    :print-name "NOL Studio Development")



(def-bundle nol-premium-deployment
    :version :22r0b
    :components (nolstudio-core-deployment nol-basic-components
				 nolstudio-g2-deployment nolstudio-window-deployment
				 nol-classic nol-classic-documentation
				 core-g2-components additional-g2-deployment-components 
				 neuron-line-premium-deployment-family-ok-components) 
    :print-name "NOL Premium Deployment")

(def-bundle nol-studio-deployment
    :version :22r0b
    :components (nolstudio-core-deployment nol-basic-components nolstudio-window-deployment)
    :print-name "NOL Studio Deployment")

(def-bundle nol-premium-development
    :version :22r0b
    :components (nolstudio-core-deployment nol-basic-components nolstudio-gui-development
				 nolstudio-g2-deployment nolstudio-window-deployment
				 nol-classic nol-classic-documentation
				 core-g2-components additional-g2-development-components
				 neuron-line-premium-development-family-ok-components) 
    :print-name "NOL Premium Development")





;;;; Components



(def-component nolstudio-core-deployment
    :parts (nolstudio-deployment-data nolstudio-math-library
			   nolstudio-core-misc-demolicense)
    :print-name "NOL Studio Core")

(def-component nolstudio-core-development
    :parts (nolstudio-data nolstudio-math-library
			   nolstudio-core-misc-demolicense)
    :print-name "NOL Studio Core")

(def-component nolstudio-gui
    :parts (nolstudio-gui nolstudio-gui-misc)
    :print-name "NOL Studio GUI")

(def-component nolstudio-gui-development
    :parts (nolstudio-gui-development nolstudio-gui-misc)
    :print-name "NOL Studio GUI")

(def-component nolstudio-examples
  :parts (nolstudio-examples)
  :print-name "NolStudio Examples")

(def-component nolstudio-documentation
  :parts (nolstudio-documentation)
  :print-name "NolStudio Documentation")



(def-component nolstudio-jre
  :parts (nolstudio-jre)
  :print-name "JRE")

(def-component nolstudio-window-deployment
  :parts (nolstudio-window-misc nolstudio-ActiveX-control)
  :print-name "NolStudio Window Deployment")

(def-component nolstudio-g2-deployment
  :parts (nolstudio-deploy-library nolstudio-kbs nolstudio-G2-kbs nolstudio-javalink-kbs
				   nolstudio-tw2-kbs nolstudio-deploy-misc)
  :print-name "NolStudio G2 Deployment")

(def-component nol-classic
  :parts (nols-G2-kbs nols-gda-kbs nol-classic)
  :print-name "NOL Classic")

(def-component nol-classic-documentation
  :parts (nol-classic-documentation)
  :print-name "NOL Classic Documentation")

;;;; Parts



(def-part nolstudio-data
    :version :22r0 
    :print-name "Data"
    :source-subdirectory nolstudio
    :source nols
    :source-filename "NolStudioData.jar"
    :destination-directory nolstudio
    :environment-variables (nolstudio_home))

(def-environment-variable nolstudio_home
    :value "<TARGETDIR>\\\\nolstudio")

(def-part nolstudio-deployment-data
    :parent nolstudio-data
    :environment-variables (nolstudio_home nolstudio_classpath))

(def-environment-variable nolstudio_classpath
    :variable "CLASSPATH"
    :append-or-merge merge
    :value "%NOLSTUDIO_HOME%\\\\NolStudioData.jar;%NOLSTUDIO_HOME%\\\\NolStudioMath.jar")
    

(def-part nolstudio-math-library
    :version :22r0 
    :print-name "Math Library"
    :source nols
    :source-subdirectory nolstudio
    :source-filename "NolStudioMath.jar"
    :destination-directory nolstudio)

(def-part nolstudio-core-misc-demolicense
    :version :22r0 
    :print-name "Core Misc"
    :source nols
    :source-subdirectory nolstudio
    :source-filename ("demolicense.txt" "known-bugs.txt")
    :destination-directory nolstudio)

(def-part nolstudio-gui
    :version :22r0
    :source-filename "NolStudioGUI.jar"
    :source nols
    :source-subdirectory nolstudio
    :destination-directory nolstudio
    :print-name "NolStudio GUI")

(def-part nolstudio-gui-development
    :parent nolstudio-gui
    :environment-variables (nolstudio-gui))

(def-environment-variable nolstudio-gui
    :variable "CLASSPATH"
    :append-or-merge merge
    :value "%NOLSTUDIO_HOME%\\\\NolStudioGUI.jar")

(def-part nolstudio-gui-misc
    :version :22r0
    :source nols
    :source-subdirectory nolstudio
    :destination-directory nolstudio
    :source-filename ("NolMainFrame.properties" "NolStringResources.properties" "nolstudio.bat")
    :shortcuts (nolstudio-batch-file))

(def-shortcut nolstudio-batch-file
    :folder-name "Gensym NOLS"
    :application-display-name "Neur-Online Studio"
    :application-directory nolstudio
    :target-name nolstudio.bat
    :run-style minimized)

(def-part nolstudio-examples
    :version :22r0
    :source nols
    :source-subdirectory nolstudio/examples
    :destination-directory nolstudio/examples)

(def-part nolstudio-documentation
    :source nols
    :version :22r0
    :source-subdirectory nolstudio/doc
    :destination-directory nolstudio/doc)

(def-part nolstudio-jre
    :parent jre
    :destination-directory nolstudio/jre
    :environment-variables (nolstudio-jre))

(def-environment-variable nolstudio-jre
    :variable "PATH"
    :append-or-merge merge
    :value "%NOLSTUDIO_HOME%\\\\jre\\\\bin;%NOLSTUDIO_HOME%\\\\jre\\\\bin\\\\classic")


(def-part nolstudio-window-misc
    :source-subdirectory nolstudio
    :source nols
    :version :22r0
    :source-filename ("RegisterControls.bat" "UnRegisterControls.bat")
    :destination-directory nolstudio)

(def-part nolstudio-ActiveX-control
    :source nols
    :version :22r0
    :source-subdirectory nolstudio/bin
    :destination-directory nolstudio/bin
    :source-filename "NolOnline.dll"
    :shortcuts (nolstudio-install-control nolstudio-uninstall-control))

(def-shortcut nolstudio-install-control
    :folder-name "Gensym NOLS"
    :application-display-name "Install Control"
    :application-directory nolstudio
    :target-name "RegisterControls.bat"
    :run-style minimized)

(def-shortcut nolstudio-uninstall-control
    :folder-name "Gensym NOLS"
    :application-display-name "UnInstall Control"
    :application-directory nolstudio
    :target-name "UnRegisterControls.bat"
    :run-style minimized)


(def-part nols-G2-kbs
    :version :51r7
    :source kbs
    :source-filename ("g2uifile.kb" "gold.kb" "sys-mod.kb" "uildefs.kb" "uilsa.kb" "gfr.kb"
				    "goldui.kb" "uil.kb" "uillib.kb" "uilslide.kb" "gms.kb"
				    "gxl.kb" "uilcombo.kb" "uilroot.kb" "uiltdlg.kb")
    :source-subdirectory utils
    :destination-directory nol
    :indep t)

(def-part nols-gda-kbs
    :source gda
    :version :40r1
    :indep t
    :destination-directory nol
    :source-filename ("gcc.kb" "gdabasic.kb" "gdabsdlg.kb" "gdl.kb" "gens.kb"
	              "glf.kb" "gqm.kb" "gqmv.kb" "gqs.kb" "gqsui.kb" "gqsviews.kb"))

(def-part nolstudio-G2-kbs
    :version :51r7
    :source kbs
    :source-filename ("gfr.kb" "sys-mod.kb" "uilroot.kb")
    :source-subdirectory utils
    :destination-directory nolstudio/kbs
    :indep t)

(def-part nolstudio-kbs
    :source nols
    :version :22r0
    :source-subdirectory nolstudio/kbs
    :destination-directory nolstudio/kbs
    :source-filename ("java-module.kb"
		       "nolexten.kb" "nolspack.kb" "nolstudio.kb"))

(def-part nolstudio-tw2-kbs
    :version :11r0a
    :source tw2
    :source-subdirectory components/kbs
    :source-filename "jlintf.kb"
    :destination-directory nolstudio/kbs)

(def-part nolstudio-javalink-kbs
    :version :11r0a
    :source jvl
    :source-subdirectory components/kbs
    :source-filename "javalink.kb"
    :destination-directory nolstudio/kbs)

(def-part nolstudio-deploy-library
    :source nols
    :version :22r0
    :source-subdirectory nolstudio
    :destination-directory nolstudio
    :source-filename "NolStudioDeploy.jar"
    :environment-variables (nolstudio-deploy-classpath))

(def-environment-variable nolstudio-deploy-classpath
    :variable "CLASSPATH"
    :append-or-merge merge
    :value "%NOLSTUDIO_HOME%\\\\NolStudioDeploy.jar")

(def-part nolstudio-deploy-misc
    :source nols
    :version :22r0
    :source-subdirectory nolstudio
    :source-filename "nolonline.bat"
    :destination-directory nolstudio)

(def-part nol-classic
    :source nols
    :version :22r0
    :source-subdirectory nol
    :destination-directory nol
    :source-filename ("nol.kb" "nolapps.kb" "noldemo.kb"
		      "nolexten.kb" "nolstart.com" "nolui.kb" "ntnol.exe"
		      ;"appl_files.dat" "help_files.dat" "kitinstal.com"
		      ))

(def-part nol-classic-documentation
    :source nols
    :version :22r0
    :source-subdirectory nol/noldoc
    :destination-directory nol/noldoc)
