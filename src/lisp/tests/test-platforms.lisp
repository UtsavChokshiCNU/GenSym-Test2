(in-package :tests)

(defun load-foreign-library (dll-name)
  #+sbcl (sb-alien:load-shared-object dll-name)
  #+lispworks (fli:register-module dll-name)
  #+ccl (ccl:open-shared-library dll-name))

(defun unload-foreign-library (dll-handle)
  #+sbcl (sb-alien:unload-shared-object dll-handle)
  #+lispworks (fli:register-module dll-handle)
  ;; CCL doesn't have close-shared-library defined under Windows
  #+(and ccl (not windows)) (ccl:close-shared-library dll-handle))

#+(and (or sbcl ccl) (or windows win32))
(defun get-desktop-window ()
  #+sbcl (eval '(sb-alien:alien-funcall 
                 (sb-alien:extern-alien 
                  "GetDesktopWindow" (sb-alien:function sb-alien:integer))))
  #+ccl (ccl:%ptr-to-int (ccl:external-call "GetDesktopWindow" :integer)))

#+(and lispworks mswindows)
(fli:define-foreign-function (get-desktop-window "GetDesktopWindow") ()
  :result-type :long)

#+(and lispworks mswindows)
(define-test test-c-x11-get-pixel-value
  (ab::c-x11-preinitialize 0 "")
  (let* 
      ((dll-handle (load-foreign-library "user32.dll"))
       (hwnd (get-desktop-window))
       (g2-pointer (ab::c-cache-c-pointer hwnd)))
    (assert-equal 0 (ab::c-x11-get-pixel-value g2-pointer "black" 0))
    (ab::c-decache-g2-pointer g2-pointer)
    (unload-foreign-library dll-handle)))
