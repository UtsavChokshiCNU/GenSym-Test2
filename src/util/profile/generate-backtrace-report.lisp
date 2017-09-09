
(in-package #-translator-is-loaded :user #+translator-is-loaded :tcl-user)

#-translator-is-loaded
(proclaim '(optimize (safety 1) (speed 3) #+lucid (compilation-speed 0)))

(defparameter tt (make-hash-table :test 'equal))

(defparameter cutoff-fraction 0.002)
(defvar cutoff)

(defun add-entry (list tail count)
  (let* ((prefix (ldiff list tail))
	 (entry (or (gethash prefix tt)
		    (setf (gethash prefix tt)
			  (cons (cons 0 0) nil)))))
    (incf (caar entry) count)
    (unless tail
      (incf (cdar entry) count))
    (when tail
      (pushnew (car tail) (cdr entry))
      (add-entry list (cdr tail) count))))

(defun write-num3 (i out)
  (format out "~a~a~a"
	  (if (>= i 100)
	      (digit-char (mod (floor i 100) 10))
	      #\space)
	  (if (>= i 10)
	      (digit-char (mod (floor i 10) 10))
	      #\space)
	  (digit-char (mod i 10))))

(defun generate-output (prefix out)
  (let ((entry (or (gethash prefix tt)
		   (return-from generate-output nil))))
    (when (<= cutoff (caar entry))
      (let* ((list (cons (cons (cdar entry) nil)
			 (loop for tail-sym in (cdr entry)
			       for entry = (gethash (append prefix (list tail-sym)) tt)
			       collect (cons (caar entry) tail-sym))))
	     (sorted-list (sort list #'> :key #'car))
	     (plength (length prefix)))
	(loop for i from 0 below plength
	      do (if (zerop (mod i 5))
		     (write-num3 i out)
		     (write-string "  |" out)))
	(if prefix
	    (format out "> ~A (~D)~%" (car (last prefix)) (caar entry))
	    (format out "(~D)~%" (caar entry)))
	(when (cdr sorted-list)
	  (loop for (count . tail-sym) in sorted-list
		do
	    (progn count)
	    (if tail-sym
		(generate-output (append prefix (list tail-sym)) out)
		(when (plusp (cdar entry))
		  (loop for i from 0 to plength
			do (if (zerop (mod i 5))
			       (write-num3 i out)
			       (write-string "  |" out)))
		  (format out "~D~%" (cdar entry))))))))))

(defun read-entries-and-generate-output (start-list end-list entry-list out)
  (setq cutoff (floor (* cutoff-fraction (length entry-list))))
  (loop for start in start-list
	do
    (format out "Backtrace Root: ~a~%" start)
    (clrhash tt)
    (loop for entry in entry-list
	  for tail = (member start (reverse entry))
	  when tail
	    do (add-entry tail tail 1))
    (generate-output nil out)
    (format out "~%~%~%"))
  (loop for end in end-list
	do
    (format out "Backtrace Target: ~a~%" end)
    (clrhash tt)
    (loop for entry in entry-list
	  for tail = (member end entry)
	  when tail
	    do (add-entry tail tail 1))
    (generate-output nil out)
    (format out "~%~%~%")))

(defun read-from-file ()
  (let ((input-file (read)))
    (when (probe-file input-file)
      (with-open-file (in input-file)
	(read in)))))

(let ((start-list (read-from-file))
      (end-list (read-from-file))
      (entry-list (read-from-file)))
  (when (and start-list entry-list)
    (with-open-file (out (read) :direction :output)
      (read-entries-and-generate-output start-list end-list entry-list out))))
