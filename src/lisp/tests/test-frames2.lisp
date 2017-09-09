(in-package :tests)

(define-test test-make-method-table-for-system-class
  (assert-equal nil (svref (ab::make-method-table-for-system-class) 0)))

;; RETURN-HERE This test fails when g2 is running, 
;; even if we wrap it into (with-connection-test-environment () ...) 
;; what's wrong? 
(define-test test-method-table-of-the-class
 (with-connection-test-environment  ()
  (assert-true (svref (ab::method-table-of-class-description 
                       (ab::class-description 'ab::iconic-entity))
                      (ab::map-generic-method-name-to-id 
                       'ab::analyze-for-consistency)))
  ;; Without this eval, CCL executes def-class form at macroexpansion time (too early).
  (eval '(ab::def-class (ab::iconic-entity ab::entity)))
  (assert-true (svref (ab::method-table-of-class-description 
                       (ab::class-description 'ab::iconic-entity))
                      (ab::map-generic-method-name-to-id 
                       'ab::analyze-for-consistency)))))

(define-test test--class--call-for-instance--expect-reasonable-result
  (with-connection-test-environment ()
    (let ((c (ab::make-frame 'ab::block)))
      (assert-eq
       'ab::block
       (eval `(ab::class ,c))))))
