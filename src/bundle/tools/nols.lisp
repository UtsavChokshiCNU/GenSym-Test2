;; -*- mode: lisp; package: bundle -*-

(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; NOLS - neuron line definitions.  Requires bundle.lisp , g2-family.lisp.

;; yduJ

;; loading this file in addition to g2-family.lisp will create the G2 bundle
;; components with the right index (note that *component-counters* has to be
;; edited if NOLS creates another component).  You then must do the handwork of
;; taking the parts from "component: G2" down to the beginning of the next
;; bundle or the end of the file and copying it into the nols.fam file.
;; Later, we might try to put all of NOLS into this format.

(setq *default-folder-name* "Gensym NOLS")

;; sadly, the above needs to be executed before g2-family.lisp is loaded.
;; this is all a kluge anyway, let's go ahead and be klugy!
(load (merge-pathnames "g2-family" *load-pathname*))

(def-g2-ok-components neuron-line-premium-development nols "Development NOLS Premium"
  (1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))


(def-g2-ok-components neuron-line-premium-deployment nols "Deployment NOLS Premium"
  (4 8 12 16 20 24 28 32))

(setq *component-counters* '(9 10))

(setf core-g2-components (remove 'g2-readme core-g2-components))

(def-bundle g2-deployment
    :evaluated-components (append core-g2-components
				  additional-g2-deployment-components 
				  neuron-line-premium-deployment-family-ok-components)
    :version :51r6
    :print-name "G2 Deployment"
    :directory "deployment")

(def-bundle g2-development
    :evaluated-components (append core-g2-components
				  additional-g2-development-components
				  neuron-line-premium-development-family-ok-components)
    :version :51r6
    :print-name "G2 Development"
    :directory "development")


#+test
(progn
  (load (compile-file "/bt/yduj/bundle/tools/bundle.lisp"))
  (compile-file "/bt/yduj/bundle/tools/g2-family.lisp")
  (load (compile-file "/bt/yduj/bundle/tools/nols.lisp"))
  (funcall (intern "MAKE-G2-FAM" "BUNDLE") "/bt/yduj/tools/datafiles/families/nols-G2.fam"))
