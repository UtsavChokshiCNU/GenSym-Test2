(in-package :tests)

(define-test test-char-code-encrypt-or-decrypt-speed
  (let ((base))
    (assert-equal 0 (ab::char-code-encrypt-or-decrypt 0 base nil))
    (assert-equal nil base)))
