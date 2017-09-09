(in-package :tests)

(define-test test-proprietary-package-slot-value-writer
  ;;; not while xml kb saving
  (with-connection-test-environment ()
      (let ((value-in-string
             (ab::twith-output-to-text-string
               (ab::write-proprietary-package-from-slot 'private nil))))
        (assert-true (ab::string=w (ab::string-to-wide-string "private") value-in-string)))
      ;;; while xml kb saving
      (let* ((ab::write-proprietary-package-while-saving-xml-kb t)
             (value-in-string
              (ab::twith-output-to-text-string
                (ab::write-proprietary-package-from-slot 'private nil))))
        (assert-true (ab::string=w (ab::string-to-wide-string "potentially private") value-in-string)))))
