(defpackage :lisp-unit2-tests
  (:use :lisp-unit2-asserts :common-lisp :iter)
  (:import-from :lisp-unit2 :define-test :undefine-test :run-tests :with-summary
                #:get-tests #:%norm
                #:errors #:len
                #:failed #:failed-assertions
                #:passed #:passed-assertions
                #:warnings #:missing #:empty))

(defpackage :lisp-unit2-test-2)
