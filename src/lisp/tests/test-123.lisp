(in-package :tests)

#+sbcl
(progn

  (load "../123")
  
  (define-test test-get-native-command-line-argument
    (let ((cmd-arg-1 "3rpm"))
      (push cmd-arg-1 sb-ext:*posix-argv*)
      (assert-equal cmd-arg-1 (cl-user::get-native-command-line-argument 0))
      (pop sb-ext:*posix-argv*)))

  (define-test test-get-command-line-option-and-switches
    (let ((cmd-arg-1 "3rpm") (cmd-arg-2 "3pm"))
      (push cmd-arg-2 sb-ext:*posix-argv*)
      (push cmd-arg-1 sb-ext:*posix-argv*)
      (assert-equal cmd-arg-2 (cl-user::get-command-line-option-and-switches))
      (pop sb-ext:*posix-argv*)
      (pop sb-ext:*posix-argv*))))

