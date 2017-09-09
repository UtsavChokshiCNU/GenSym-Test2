(in-package :tests)

(defun char-code-decrypt-ab-test ()
  (let ((base 0) r)
    (setq r (ab::char-code-decrypt 50 base))
    (assert-eql r 51)
    (assert-eql base 3947)
    (setq r (ab::char-code-decrypt 51 base))
    (assert-eql r 61)
    (assert-eql base 460)
    (setq r (ab::char-code-decrypt 52 base))
    (assert-eql r 57)
    (assert-eql base 841)))

(defun char-code-decrypt-test ()
  (char-code-decrypt-ab-test))

(define-test test-z-char-code-decrypt
  (char-code-decrypt-test)
  (format t "test char-code-decrypt-test SUCCESS~%")
  (assert-true t))
