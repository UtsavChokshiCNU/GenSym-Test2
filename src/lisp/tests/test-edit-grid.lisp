(in-package :tests)

(define-test test-edit-grid-date
  (ab::with-system-variables ('ab::ab (make-symbol "CURRENT-PROCESS"))
    (let* ((g2-window (ab::make-gensym-window nil))
           (work-station (ab::make-workstation g2-window))
           (pg))
      (setf (ab::icp-output-port-for-window? g2-window) work-station)
      (setf pg (ab::g2-ui-create-property-grid
                #w"" nil
                (ab::allocate-evaluation-structure-inline
                  'ab::contents (ab::allocate-evaluation-sequence nil)
                  'ab::user-data (ab::package-internal-data-property
                                  nil g2-window 'ab::update-table-of-attributes-pane nil)
                  'ab::sort 'ab::none)
                g2-window
                'ab::prop-grid-invoke-callback))
      (assert-true (ab::prop-grid-invoke-callback pg 'ab::edit 0 "08/09/10" 0 10 10)))))


