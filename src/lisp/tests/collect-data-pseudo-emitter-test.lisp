(in-package :ab)

(defun collect-data-pseudo-emitter-test ()
	(let ((instruction '(0 1 2 3 5 6)) (byte-code-stream nil))
		(COLLECT-DATA-PSEUDO-EMITTER byte-code-stream instruction)))

(in-package :tests)

(collect-data-pseudo-emitter-test)