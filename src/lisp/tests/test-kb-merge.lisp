(in-package :tests)

;; TODO: this test makes LispWorks go into Infinite LOOPs. -- Chun Tian (binghe), July 16, 2016.

(defun aux-fn-get-slot-value-function-for-test--make-new-top-level-kb-workspace--returns-workspace
    (fn frame slot-name &optional ab::class-if-specific?)
  (cond
   ((and (null frame) (eq slot-name 'ab::initial-margin-for-workspaces))
    30)
   (t
    (funcall fn frame slot-name ab::class-if-specific?))))

(defun aux-fn-test--make-new-top-level-kb-workspace--returns-workspace ()
  (ab::with-system-variables ('ab::ab (make-symbol "CURRENT-PROCESS"))
    (setq ab::classes-visited-byte-vector
          (ab::initialize-classes-visited-byte-vector))
    (ab::assign-class-bit-numbers-and-vectors-to-system-classes)
    (let ((ab::miscellaneous-parameters nil))
      (mock:with-wrapped-functions*
          ((ab::get-slot-value-function
            'aux-fn-get-slot-value-function-for-test--make-new-top-level-kb-workspace--returns-workspace)
           (ab::mutate-kb-specific-property-value 'ignore-all)
           (ab::put-module-this-is-part-of? 'ignore-all)
           (ab::recompute-selection-highlights 'ignore-all)
           (ab::|AB::FRAME-STATUS-AND-NOTES -Mock-function| 'ignore-all)
           (ab::|AB::TOP-LEVEL-KB-MODULE? -Mock-function| 'ignore-all)
           )
        (with-mocked-macros (ab::frame-status-and-notes
                             ab::module-system-table-belongs-to?
                             ab::top-level-kb-module?)
          (mock:expect
           (
            (:call (AB::|AB::MODULE-SYSTEM-TABLE-BELONGS-TO? -Mock-function| nil) :return (nil))
            )
           :for
           (ab::make-new-top-level-kb-workspace 'ab::kb-workspace t)))))))

(define-test test--make-new-top-level-kb-workspace--returns-workspace
  (let ((ws (aux-fn-test--make-new-top-level-kb-workspace--returns-workspace)))
    (assert-eq
     (simplified-g2-type-of ws)
     'ab::kb-workspace)))
