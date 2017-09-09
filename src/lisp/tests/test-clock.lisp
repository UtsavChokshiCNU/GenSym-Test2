(in-package :tests)

;;; This isn't really a unit test, it's more of a functional test for
;;; the "native tick counter"
(defun c-native-clock-ticks-or-cache-ab-test ()
  #+(and :unix (not :linux) :vanilla-time)
  (assert-eql internal-time-units-per-second
              ab::fixnum-time-units-per-second)
  #-(and :unix (not :linux) :vanilla-time)
  (assert-eql (ab::c-native-clock-ticks-per-second)
              ab::fixnum-time-units-per-second)
  ;; Read the tick counter, then wait until it changes, read it again,
  ;; calculate how many ticks have "passed" and do sanity checks
  (let* ((tick1 (ab::c-native-clock-ticks-or-cache nil nil))
         (tickcount 
          (loop for i from 1 until 
               (/= tick1 
                   (ab::c-native-clock-ticks-or-cache nil nil)) 
               finally (return i)))
         (tick2 (ab::c-native-clock-ticks-or-cache nil nil))
         (ticktime (if (> tick2 tick1) (- tick2 tick1) 
                       (- #.most-positive-fixnum (- tick1 tick2)))))
    (format t "tick test result [~D ~D] ~D ~D~%" tick1 tick2 ticktime tickcount)
    ;; sanity check "time can't go backwards"
    (assert-true (> ticktime 0))
    ;; this (sanity) check is dubious, as we don't have any control over
    ;; how much time will pass between `tick1` and `tick2`, so we don't
    ;; have a good threshold, thus we use a "really big threshold"
    (assert-true (< ticktime (* 200 (ab::fixnum-time-milliseconds-of-graininess))))))

(defun c-native-clock-ticks-or-cache-test () 
  (c-native-clock-ticks-or-cache-ab-test))

(define-test test-z-clock-0
  (format t "load clock test SUCCESS~%")
  (assert-true t))

(define-test test-z-clock-c-native-clock-ticks-or-cache-func
  (format t "test c-native-clock-ticks-or-cache-func~%")
  (c-native-clock-ticks-or-cache-test)
  (format t "test c-native-clock-ticks-or-cache-func SUCCESS~%")
  (assert-true t))
