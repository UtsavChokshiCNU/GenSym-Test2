(in-package :tests)

(define-test test-g2-enterprise-p-is-equal-to-is-g2-enterprise
  (assert-equal (ab::g2-enterprise-p) ab::*is-g2-enterprise?*))

(define-test test-g2-enterprise-p-depends-on-is-g2-enterprise
  (let ((ab::*is-g2-enterprise?* (not ab::*is-g2-enterprise?*)))
    (assert-equal ab::*is-g2-enterprise?* (ab::g2-enterprise-p))))

(define-test test-is-g2-enterprise-equal-to-isG2Enterprise
  (assert-equal (if (ab::=f (ab::is-g2-enterprise-defined?) 0) nil t) 
                ab::*is-g2-enterprise?*))

