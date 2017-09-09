(in-package :ab)

(let ((statement) (optimized-statement))
  ((setq statement '(FOR-NUMERIC-STATEMENT (I TO 0 100) DO (ASSIGNMENT-STATEMENT X 1) (ASSIGNMENT-STATEMENT Z (+ X 3))))
  (setq optimized-statement (mutate-for-statement-body-if-possible statement))
  (assert-true (eq (car optimized-statement) 'FOR-NUMERIC-STATEMENT))))
