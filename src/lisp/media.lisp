;; -*- Mode:Lisp; Package: AB; Base: 10; Syntax: Common-lisp -*-
(in-package "AB")

;;;; Module MEDIA

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Joe Devlin
 

(def-class (media-bin (entity item) define-predicate)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((polychrome (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (icon-color . foreground)
		   (g2-icon-specialty-region-1 . black)
		   (g2-icon-specialty-region-2 . gray))
       g2-icon-background
       (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading
       (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
		       ((0 0) (50 0) (47 3)) ((3 3) (3 47) (0 50))
		       ((0 0) (47 3) (3 3)) ((3 3) (0 50) (0 0)))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50))
		       ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50))
		       ((50 50) (3 47) (47 47)))
       icon-color
       (outline (0 0) (0 50) (50 50) (50 0))
       (text "MEDIA" (8 21) small)
       (text "-BIN" (9 40) small)
       (lines (44 5) (5 5) (5 45))
       g2-icon-light-shading
       (lines (5 45) (44 45) (44 5)))))
  (media-bin-data nil system save vector-slot)
  (media-bin-streams nil system vector-slot)
  (media-bin-highest-file-descriptor 0 system vector-slot)
  (media-bin-owner? nil system vector-slot)
  (media-bin-owner-serial nil system vector-slot))

(def-class-method cleanup (media-bin)
  (let ((owner? (media-bin-owner? media-bin)))
    (when (and owner?
	       (not (frame-has-been-reprocessed-p
		      owner? (media-bin-owner-serial media-bin))))
      (frame-class-case owner?
	(image-definition
	  (setf (image-definition-media-bin owner?) nil))))))

(def-class-method initialize (media-bin)
  (setf (media-bin-data media-bin)
	(make-media-file 'directory (make-wide-string 0))))

(def-slot-value-reclaimer media-bin-owner? (owner media-bin)
  (declare (ignore owner))
  (setf (media-bin-owner? media-bin) nil)
  (reclaim-frame-serial-number (media-bin-owner-serial media-bin))
  (setf (media-bin-owner-serial media-bin) nil))

(def-slot-value-reclaimer media-bin-owner-serial (serial-number)
  ;; already reclaimed above
  (declare (ignore serial-number))
  nil)

(defmacro media-file-type (x)
  `(managed-svref ,x 0))

(defmacro media-file-name (x)
  `(managed-svref ,x 1))

(defmacro media-file-status (x)
  `(managed-svref ,x 2))

(defmacro media-file-size (x)
  `(managed-svref ,x 3))

(defmacro media-file-contents (x)
  `(managed-svref ,x 4))

(defmacro media-file-streams (x)
  `(managed-svref ,x 5))

(defmacro media-file-create-date (x)
  `(managed-svref ,x 6))

(defmacro media-file-binary-odd-p (x)
  `(managed-svref ,x 7))

(defun make-media-file-1 (type name status size contents binary-odd-p create-date)
  (let ((file (allocate-managed-array 8)))
    (setf (media-file-type file) type)
    (setf (media-file-name file) name)
    (setf (media-file-status file) status)
    (setf (media-file-size file) size)
    (setf (media-file-contents file) contents)
    (setf (media-file-binary-odd-p file) binary-odd-p)
    (setf (media-file-create-date file) create-date)
    file))

(defun make-media-file (type name)
  (make-media-file-1
    type name (if (eq type 'directory) 'normal 'new)
    0 nil nil (allocate-managed-float (gensym-get-unix-time))))

(def-structure (media-stream
	          (:constructor make-media-stream
		     (media-stream-file-descriptor
		       media-stream-location
		       media-stream-file
		       media-stream-direction)))
  (media-stream-file-descriptor nil)
  (media-stream-location nil
			 :reclaimer reclaim-media-file-location)
  (media-stream-file nil)
  (media-stream-direction nil)
  (media-stream-file-pointer nil)
  (media-stream-current-block nil))

(defun-simple media-stream-p-function (thing)
  (media-stream-p thing))

(defparameter media-block-size 1024)

(def-class-method initialize-after-reading (media-bin)
  (funcall-superior-method media-bin)
  (remove-dead-media-streams (media-bin-data media-bin)))

(defun-void remove-dead-media-streams (media-file)
  (cond
    ((eq (media-file-type media-file) 'directory)
     (loop for file in (media-file-contents media-file)
	   do
       (remove-dead-media-streams file)))
    (t
     (reclaim-slot-value (media-file-streams media-file))
     (setf (media-file-streams media-file) nil))))

(defun-for-system-procedure g2-media-bin-open-stream
    (media-bin location-sequence name direction data-type mode)
  (let* ((location (make-location-from-sequence location-sequence t))
	 (file? (locate-media-file-node
		  (media-bin-data media-bin) location)))
    (cond
      ((null file?)
       (media-bin-file-not-found-error media-bin location))
      ((not (eq (media-file-type file?) 'directory))
       (media-bin-non-directory-error media-bin location))
      ((eq direction 'input)
       (media-bin-open-input-stream
	 media-bin file? location name data-type mode))
      ((eq direction 'output)
       (media-bin-open-output-stream
	 media-bin file? location name data-type mode))
      (t
       (media-bin-unknown-io-direction-error media-bin location direction)))))

(define-system-rpc-access (g2-media-bin-open-stream (integer))
    ((media-bin (class media-bin))
     (location-sequence (sequence))
     (name text)
     (direction symbol)
     (data-type symbol)
     (mode symbol))
  (g2-media-bin-open-stream
    media-bin location-sequence name direction data-type mode))
		

;;; Memory notes:
;;;  location is consumed

(defun-simple media-bin-open-output-stream
    (media-bin directory location name data-type mode)
  (let ((existing-file?
	  (find-media-file-in-directory directory name)))
    (cond
      ((not (memq data-type '(binary text)))
       (media-bin-unsupported-file-type-error media-bin location data-type))
      ((eq mode 'create-or-overwrite)
       (when existing-file?
	 (remove-media-file-from-directory
	   directory existing-file?)
	 (reclaim-media-file media-bin existing-file?))
       (let* ((new-file (make-media-file
			  data-type (copy-text-string name)))
	      (new-stream
	       (make-media-stream
		 (incff (media-bin-highest-file-descriptor media-bin))
		 (extend-media-file-location
		   (copy-media-file-location location) name)
		 new-file
		 'output)))
	 (setf (media-file-status new-file) 'writing)
	 (add-media-file-to-directory directory new-file)
	 (add-stream-to-media-file new-file new-stream)
	 (add-stream-to-media-bin media-bin new-stream)
	 (setf (media-stream-file-pointer new-stream) 0)
	 (media-stream-file-descriptor new-stream)))
      (t
       (media-bin-unsupported-mode-error media-bin location mode)))))

(defun media-bin-open-input-stream
    (media-bin directory location name data-type mode)
  (let ((existing-file?
	  (find-media-file-in-directory directory name)))
    (cond
      ((not (memq data-type '(binary text)))
       (media-bin-unsupported-file-type-error media-bin location data-type))
      ((not existing-file?)
       (media-bin-file-not-found-error
	 media-bin
	 (extend-media-file-location location name)))
      ((not (eq (media-file-type existing-file?) data-type))
       (media-bin-incompatible-file-type-error
	 media-bin location (media-file-type existing-file?) data-type))
      ((eq mode 'read-shared)
       (unless (memq (media-file-status existing-file?)
		     '(normal reading))
	 (media-bin-file-locked-error media-bin location))
       (let ((new-stream
	       (make-media-stream
		 (incff (media-bin-highest-file-descriptor media-bin))
		 (extend-media-file-location
		   (copy-media-file-location location) name)
		 existing-file?
		 'input)))
	 (setf (media-file-status existing-file?) 'reading)
	 (add-stream-to-media-file existing-file? new-stream)
	 (add-stream-to-media-bin media-bin new-stream)
	 (setf (media-stream-file-pointer new-stream) 0)
	 (setf (media-stream-current-block new-stream)
	       (media-file-contents existing-file?))
	 (media-stream-file-descriptor new-stream)))
      (t
       (media-bin-unsupported-mode-error media-bin location mode)))))
       

(defun-for-system-procedure g2-media-bin-close-stream
    (media-bin file-descriptor abort-ev)
  (let ((stream (get-media-stream-or-error media-bin file-descriptor nil)))
    abort-ev ; silence compiler
    (unless stream
      (cond ((eq abort-ev evaluation-true-value)
	     (return-from g2-media-bin-close-stream
	       evaluation-true-value))
	    (t
	     (return-from g2-media-bin-close-stream
	       evaluation-false-value))))
    (unless (media-stream-file stream)
      (cond ((eq abort-ev evaluation-true-value)
	     (return-from g2-media-bin-close-stream
	       evaluation-true-value))
	    (t
	     (media-bin-stream-file-deleted-error
	       media-bin
	       (copy-media-file-location (media-stream-location stream))))))
    (case (media-stream-direction stream)
      (output
       (let ((file (media-stream-file stream)))
	 (setf (media-file-status file) 'normal)
	 (setf (media-file-size file)
	       (media-stream-file-pointer stream))
	 (remove-stream-from-media-file file stream)
	 (remove-stream-from-media-bin media-bin stream)
	 (reclaim-media-stream stream)))
      (input
       (let ((file (media-stream-file stream)))
	 (remove-stream-from-media-file file stream)
	 (remove-stream-from-media-bin media-bin stream)
	 (if (loop for stream in (media-bin-streams media-bin)
		   as stream-file = (media-stream-file stream)
		   thereis (eq stream-file file))
	     (setf (media-file-status file) 'reading)
	     (setf (media-file-status file) 'normal))
	 (reclaim-media-stream stream))))
    evaluation-true-value))

(define-system-rpc-access (g2-media-bin-close-stream (truth-value))
    ((media-bin (class media-bin))
     (file-descriptor integer)
     (abort-ev datum))
  (g2-media-bin-close-stream media-bin file-descriptor abort-ev))

(defun-for-system-procedure g2-media-bin-set-ignore-last-byte
    (media-bin file-descriptor)
  (let ((stream (get-media-stream-or-error media-bin file-descriptor t)))
    (unless (eq (media-stream-direction stream) 'output)
      (media-bin-io-direction-error
	media-bin
	(copy-media-file-location (media-stream-location stream))
	'output (media-stream-direction stream)))
    (let ((file (media-stream-file stream)))
      (unless (eq (media-file-type file) 'binary)
	(media-bin-stream-must-be-binary-error
	  media-bin
	  (copy-media-file-location (media-stream-location stream))))
      (setf (media-file-binary-odd-p file) t))
    evaluation-true-value))

(define-system-rpc-access (g2-media-bin-set-ignore-last-byte (truth-value))
    ((media-bin (class media-bin))
     (file-descriptor integer))
  (g2-media-bin-set-ignore-last-byte media-bin file-descriptor))

(defun-for-system-procedure g2-media-bin-ignore-last-byte
    (media-bin file-descriptor)
  (let ((stream (get-media-stream-or-error media-bin file-descriptor t)))
    (unless (eq (media-stream-direction stream) 'input)
      (media-bin-io-direction-error
	media-bin
	(copy-media-file-location (media-stream-location stream))
	'output (media-stream-direction stream)))
    (let ((file (media-stream-file stream)))
      (unless (eq (media-file-type file) 'binary)
	(media-bin-stream-must-be-binary-error
	  media-bin
	  (copy-media-file-location (media-stream-location stream))))
      (if (media-file-binary-odd-p file)
	  evaluation-true-value
	  evaluation-false-value))))

(define-system-rpc-access (g2-media-bin-ignore-last-byte (truth-value))
    ((media-bin (class media-bin))
     (file-descriptor integer))
  (g2-media-bin-ignore-last-byte media-bin file-descriptor))

(defun-for-system-procedure g2-media-bin-write
    (media-bin file-descriptor data)
  (let ((stream (get-media-stream-or-error media-bin file-descriptor t)))
    (unless (eq (media-stream-direction stream) 'output)
      (media-bin-io-direction-error
	media-bin
	(copy-media-file-location (media-stream-location stream))
	'output (media-stream-direction stream)))
    (let* ((file (media-stream-file stream))
	   (data-pointer 0)
	   (data-length (text-string-length data))
	   (file-pointer (media-stream-file-pointer stream))
	   (pointer-in-block (modf file-pointer media-block-size))
	   (space-in-first-segment (-f media-block-size pointer-in-block))
	   (current-block (media-stream-current-block stream))
	   (current-block-data (car current-block)))
      ;; (format t "START data-len ~s file-pointer ~s current-block ~s"
      ;;      data-length file-pointer current-block)
      (when (>f data-length 0)
	(when (/=f space-in-first-segment media-block-size)
	  ;; write first segment, may be partial or last
	  #+development
	  (unless current-block
	    (error "logic error in media-bin-write"))
	  (let ((source-length (minf space-in-first-segment data-length)))
	    (media-block-copy data 0 source-length
			      current-block-data pointer-in-block)
	    (incff file-pointer source-length)
	    (incff data-pointer source-length)))
	(when (>f data-length space-in-first-segment)
	  ;; write "middle" full segments and tail
	  (loop for i from 0 below (floorf (-f data-length data-pointer)
					   media-block-size)
		do
	    (setf current-block (extend-media-file file current-block))
	    (setf current-block-data (car current-block))
	    (media-block-copy data data-pointer media-block-size
			      current-block-data 0)
	    (incff file-pointer media-block-size)
	    (incff data-pointer media-block-size)))
	(when (<f data-pointer data-length)
	  (let ((source-length (-f data-length data-pointer)))
	    (setf current-block (extend-media-file file current-block))
	    (setf current-block-data (car current-block))
	    (media-block-copy data data-pointer source-length
			      current-block-data 0)
	    (incff file-pointer source-length)
	    (incff data-pointer source-length)))
	(setf (media-stream-current-block stream) current-block)
	(setf (media-stream-file-pointer stream) file-pointer)))
    evaluation-true-value))

(define-system-rpc-access (g2-media-bin-write (truth-value))
    ((media-bin (class media-bin))
     (file-descriptor integer)
     (data (or text (unsigned-vector-16))))
  (g2-media-bin-write
    media-bin
    file-descriptor
    (if (evaluation-text-p data)
	data
	(prog1
	    (evaluation-unsigned-vector-16-value data)
	  (reclaim-eval-cons data)))))

;; test saving and loading
;; getting context from Item (or any G2Stub)
;; usv considerations (binary type)
;; test across network

(defun-for-system-procedure g2-media-bin-read
    (media-bin file-descriptor max-length)
  (let ((stream (get-media-stream-or-error media-bin file-descriptor t)))
    (unless (eq (media-stream-direction stream) 'input)
      (media-bin-io-direction-error
	media-bin
	(copy-media-file-location (media-stream-location stream))
	'output (media-stream-direction stream)))
    (unless (>=f max-length 0)
      (media-bin-negative-length-error
	media-bin
	(copy-media-file-location (media-stream-location stream))
	max-length))
    (let* ((file (media-stream-file stream))
	   (file-pointer (media-stream-file-pointer stream))
	   (file-size (media-file-size file))
	   (data-pointer 0)
	   (data-length (minf max-length (-f file-size file-pointer)))
	   (data (mark-wide-string-as-binary (make-wide-string data-length)))
	   (pointer-in-block (modf file-pointer media-block-size))
	   (space-in-first-segment (-f media-block-size pointer-in-block))
	   (current-block (media-stream-current-block stream))
	   (current-block-data (car current-block)))
      (cond
	((=f file-pointer file-size)
	 evaluation-false-value)
	((>f data-length 0)
	 (when (/=f space-in-first-segment media-block-size)
	   (let ((source-length (minf space-in-first-segment data-length)))
;	     (format t "slen = ~s sifs=~s p-in-b =~s fp =~s dp=~s~%"
;		     source-length space-in-first-segment
;		     pointer-in-block file-pointer data-pointer)
	     (media-block-copy current-block-data
			       pointer-in-block source-length
			       data 0)
	     (incff file-pointer source-length)
	     (incff data-pointer source-length)
	     (when (=f source-length space-in-first-segment)
	       (setf current-block (cdr current-block))
	       (setf current-block-data (car current-block)))))
	 (when (<f data-pointer data-length)
;	   (format t "num whole blocks = ~s~%"
;		   (floorf (-f data-length data-pointer)
;					    media-block-size))
	   (loop for i from 0 below (floorf (-f data-length data-pointer)
					    media-block-size)
		 do
	     (media-block-copy current-block-data 0 media-block-size
			       data data-pointer)
	     (incff file-pointer media-block-size)
	     (incff data-pointer media-block-size)
	     (setf current-block (cdr current-block))
	     (setf current-block-data (car current-block))))
	 (when (<f data-pointer data-length)
	   (let ((source-length (-f data-length data-pointer)))
	     (media-block-copy current-block-data 0 source-length
			       data data-pointer)
	     (incff file-pointer source-length)
	     (incff data-pointer source-length)))
	 (setf (media-stream-current-block stream) current-block)
	 (setf (media-stream-file-pointer stream) file-pointer)
	 data)
	(t
	 #+development
	 (unless (=f (wide-string-length data) 0)
	   (cerror "go on" "logical error - call Joe"))
	 data)))))

(define-system-rpc-access (g2-media-bin-read ((unsigned-vector-16)))
    ((media-bin (class media-bin))
     (file-descriptor integer)
     (max-length integer))
  (let ((result
	  (g2-media-bin-read media-bin file-descriptor max-length)))
    (cond ((wide-string-p result)
	   (maybe-make-evaluation-unsigned-vector-16 result))
	  (t
	   result))))

(defun-for-system-procedure g2-media-bin-describe
    (media-bin location-sequence-or-file-descriptor)
  ;; returns struct type, size contents, date as double
  (let ((file?
	  (if (fixnump location-sequence-or-file-descriptor)
	      (media-stream-file
		(get-media-stream-or-error
		  media-bin location-sequence-or-file-descriptor nil))
	      (locate-media-file-node
		(media-bin-data media-bin)
		(make-location-from-sequence
		  location-sequence-or-file-descriptor t)))))
    (cond (file?
	   (with-temporary-gensym-float-creation i-hate-gl-memory-management
	     (let* ((type (media-file-type file?))
		    (size (media-file-size file?))
		    (binary-size (if (media-file-binary-odd-p file?)
				     (-f (*f 2 size) 1)
				     (*f 2 size)))
		    (info (allocate-evaluation-structure-inline
			    'type type
			    'size size
			    'size-in-bytes binary-size
			    'create-date (make-evaluation-float
					   (managed-float-value
					     (media-file-create-date file?))))))
	     (when (eq type 'directory)
	       (setf (evaluation-structure-slot info 'contents)
		     (allocate-evaluation-sequence
		       (loop for file in (media-file-contents file?)
			     collect
			     (make-evaluation-text (media-file-name file))
			       using eval-cons))))
	     info)))
	  (t
	   evaluation-false-value))))

(define-system-rpc-access (g2-media-bin-describe (datum)) ; false or structure
    ((media-bin (class media-bin))
     (location-sequence-or-file-descriptor datum))
  (g2-media-bin-describe
    media-bin location-sequence-or-file-descriptor))

(defun-for-system-procedure g2-media-bin-make-directory
    (media-bin location-sequence name)
  (let* ((location (make-location-from-sequence location-sequence t))
	 (file? (locate-media-file-node
		  (media-bin-data media-bin) location)))
    (cond
      ((null file?)
       (media-bin-file-not-found-error media-bin location))
      ((not (eq (media-file-type file?) 'directory))
       (media-bin-non-directory-error media-bin location))
      ((find-media-file-in-directory file? name)
       (media-bin-already-exists-error media-bin location))
      (t
       (let ((new-directory (make-media-file
			      'directory
			      (copy-text-string (evaluation-text-value name)))))
	 (add-media-file-to-directory file? new-directory))))
    evaluation-true-value))

(define-system-rpc-access (g2-media-bin-make-directory (truth-value))
    ((media-bin (class media-bin))
     (location-sequence (sequence))
     (name text))
  (g2-media-bin-make-directory
    media-bin location-sequence name))

(defun-for-system-procedure g2-media-bin-delete
    (media-bin location-sequence)
  (let* ((location (make-location-from-sequence location-sequence t))
	 (file? (locate-media-file-node
		  (media-bin-data media-bin) location))
	 (parent-file? (locate-media-file-parent-node
			 (media-bin-data media-bin) location)))
    (cond (file?
	   (delete-media-file-or-directory media-bin file? parent-file?)
	   (when (null location) ; i.e. deleting root
	     (setf (media-bin-data media-bin)
		   (make-media-file 'directory (make-wide-string 0)))))
	  (t
	   (media-bin-file-not-found-error
	     media-bin location)))
    evaluation-true-value))

(define-system-rpc-access (g2-media-bin-delete (truth-value))
    ((media-bin (class media-bin))
     (location-sequence (sequence)))
  (g2-media-bin-delete media-bin location-sequence))

(defun-void delete-media-file-or-directory (media-bin file parent-file?)
  ; (format t "deleting ~s name=~s~%" file (media-file-name file))
  (cond
    ((eq (media-file-type file) 'directory)
     (loop for sub-file in (media-file-contents file)
	   do
       (delete-media-file-or-directory media-bin sub-file file))
     (reclaim-slot-value-list (media-file-contents file))
     (setf (media-file-contents file) nil)
     (when parent-file?
       (remove-media-file-from-directory parent-file? file))
     (reclaim-slot-value file))
    (t
     (when parent-file?
       (remove-media-file-from-directory parent-file? file))
     (reclaim-media-file media-bin file))))

(defun get-media-stream-or-error (media-bin file-descriptor throw-error-p)
  (loop for stream in (media-bin-streams media-bin)
	when (=f file-descriptor (media-stream-file-descriptor stream))
	  do
	    (unless (media-stream-file stream)
	      (cond
		(throw-error-p
		 (media-bin-stream-file-deleted-error
		   media-bin
		   (copy-media-file-location (media-stream-location stream))))
		(t
		 (return nil))))
	    (return stream)
	finally
	  (cond
	    (throw-error-p
	     (media-bin-no-such-stream-error media-bin file-descriptor))
	    (t
	     (return nil)))))
	     

(defun-simple locate-media-file-node (root location)
  (loop for level-name in location
	do
    (cond ((eq (media-file-type root) 'directory)
	   (unless (loop for media-file in (media-file-contents root)
			 do
		     (when (string=w (media-file-name media-file) level-name)
		       (setf root media-file)
		       (return t)))
	     (return nil)))
	  (t
	   (return nil)))
	finally
	  (return root)))

(defun-simple locate-media-file-parent-node (root location)
  (loop with parent? = nil
	for level-name in location
	do
    (cond ((eq (media-file-type root) 'directory)
	   (unless (loop for media-file in (media-file-contents root)
			 do
		     (when (string=w (media-file-name media-file) level-name)
		       (setf parent? root)
		       (setf root media-file)
		       (return t)))
	     (return nil)))
	  (t
	   (return parent?)))
	finally
	  (return parent?)))

(defun-simple find-media-file-in-directory (directory filename)
  (loop for media-file in (media-file-contents directory)
	do
    (when (string=w (media-file-name media-file) filename)
      (return media-file))))

(defun-simple extend-media-file (file end-block)
  #+development
  (when (cdr end-block)
    (cerror "go on" "Um, that's not an end block -> ~s" end-block))
  (let ((result (slot-value-list (make-wide-string media-block-size))))
    (cond ((media-file-contents file)
	   (setf (cdr end-block) result)
	   result)
	  (t
	   (setf (media-file-contents file) result)
	   result))))

(defun-void media-block-copy (source source-start source-length
				     destination destination-start)
  (memcpy-portion-of-wide-string-into-wide-string
    source source-start (+f source-start source-length)
    destination destination-start))

(defun-void add-media-file-to-directory (directory file)
  (slot-value-push file (media-file-contents directory))
  (incff (media-file-size directory)))

(defun-void remove-media-file-from-directory (directory file)
  (setf (media-file-contents directory)
	(delete-slot-value-element
	  file
	  (media-file-contents directory)))
  (decff (media-file-size directory)))

(defun-void add-stream-to-media-file (file stream)
  (slot-value-push stream
		   (media-file-streams file)))

(defun-void remove-stream-from-media-file (file stream)
  (setf (media-file-streams file)
	(delete-slot-value-element
	  stream
	  (media-file-streams file))))

(defun-void add-stream-to-media-bin (media-bin stream)
  (slot-value-push stream (media-bin-streams media-bin)))

(defun-void remove-stream-from-media-bin (media-bin stream)
  (setf (media-bin-streams media-bin)
	(delete-slot-value-element
	  stream
	  (media-bin-streams media-bin))))

(defun-simple make-location-from-sequence (sequence reclaim-p)
  (loop with location = '()
        for elt being each evaluation-sequence-element of sequence
	do
    (cond ((evaluation-text-p elt)
	   (slot-value-push
	     (copy-text-string (evaluation-text-value elt))
	     location))
	  (t
	   (stack-error cached-top-of-stack "~NV is not a sequence of text")))
	finally
	  (when reclaim-p
	    (reclaim-evaluation-value sequence)
	    (return (nreverse location)))))
	   
(defun-void reclaim-media-file (media-bin media-file)
  (cond
    ((eq (media-file-type media-file) 'directory)
     (cerror "go on" "write me"))
    (t
     (loop for stream in (media-bin-streams media-bin)
	   when (eq (media-stream-file stream) media-file)
	     do
	       (setf (media-stream-file stream) nil))
     (reclaim-slot-value media-file))))
     
(defun extend-media-file-location (location extension)
  (nconc location (if (text-string-p extension)
		      (slot-value-list extension)
		      extension)))

(defun copy-media-file-location (location)
  (copy-for-slot-value location))

(defun-void reclaim-media-file-location (location)
  (reclaim-slot-value location))





;;;; Convenience Procedure

;;; finish and test this baby standalone
;;; see if results look good in nevada
;;; put in logic for image-definition to media bin

(defun-for-system-procedure g2-media-bin-upload-binary-file
    (media-bin location-sequence name local-file-name)
  (g2-media-bin-upload-binary-file-1
    media-bin location-sequence name local-file-name))

(defun-allowing-unwind g2-media-bin-upload-binary-file-1
    (media-bin location-sequence name local-file-name)
  (g2-stream-with-open-stream
      (binary-file-stream local-file-name
			  :direction :input
			  :element-type (unsigned-byte 8))
    (cond
      ((null binary-file-stream)
       (media-bin-no-local-file-error media-bin local-file-name))
      (t
       (g2-media-bin-upload-binary-file-2
	 binary-file-stream media-bin location-sequence name)))))

(defun g2-media-bin-upload-binary-file-2
    (binary-file-stream media-bin location-sequence name)
  (let ((media-stream
	  (g2-media-bin-open-stream
	    media-bin location-sequence name 'output 'binary 'create-or-overwrite)))
    ;; here, load that data
    (loop with buffer = (make-wide-string media-block-size)
	  with last-byte? = 0
	  with i = 0
	  for ch? = (g2-stream-read-ascii-byte binary-file-stream)
	  as count from 0 by 1
	  until (null ch?)
	  do
      (cond ((=f (logandf count 1) 0) ; evenp
	     (setf last-byte? ch?))
	    (t
	     (setf (charw buffer i)
		   (code-charw (+f (ashf ch? 8) last-byte?)))
	     (incff i)
	     (setf last-byte? nil)))
      (when (=f i media-block-size)
	(g2-media-bin-write media-bin media-stream buffer)
	(setf i 0)
	(setf last-byte? nil))
	  finally
	    (when last-byte?
	      (setf (charw buffer i) (code-charw last-byte?))
	      (incff i))
	    (when (>f i 0)
	      (let ((last-buffer (make-wide-string i)))
		(media-block-copy buffer 0 i last-buffer 0)
		(g2-media-bin-write media-bin media-stream last-buffer)
		(reclaim-wide-string last-buffer)))
	    (when (=f (logandf count 1) 1)
	      (g2-media-bin-set-ignore-last-byte media-bin media-stream))
	    (reclaim-wide-string buffer))
    (g2-media-bin-close-stream media-bin media-stream evaluation-false-value)))


;;;; Support for Describe 


(def-class-method describe-frame (media-bin)
  (nconc
    (if (media-bin-data media-bin)
	(describe-media-bin media-bin (media-bin-data media-bin) 0)
	(eval-list (copy-constant-wide-string #w"Media Bin is Empty")))
    (funcall-superior-method media-bin)))
    

(defun describe-media-bin (media-bin file depth)
  (cond
    ((eq (media-file-type file) 'directory)
     (loop with result
	     = (eval-list
		 (twith-output-to-text-string
		   (loop for i from 0 below depth do (twrite " "))
		   (tformat "~A:" (if (=f depth 0)
				      #w"Top-Level Directory"
				      (media-file-name file)))))
           for sub-file in (media-file-contents file)
	   as sub-description
	      = (describe-media-bin media-bin sub-file (+f 2 depth))
	   do
       (setf result (nconc sub-description result))
	   finally
	     (return result)))
    (t
     (eval-list
       (twith-output-to-text-string
	 (loop for i from 0 below depth do (twrite " "))
	 (tformat "~A size = ~s"
		  (media-file-name file)
		  (-f (*f 2 (media-file-size file))
		      (if (media-file-binary-odd-p file)
			  1 0))))))))
		      
		  




;;;; Backward Compatibility with Image Definitions



(def-virtual-attribute cached-media-bin
    ((class image-definition) (or (class media-bin) (no-item)) ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((image-definition)
	   (cache-media-bin-if-possible image-definition nil)
	   (image-definition-media-bin image-definition)))

(defun cache-media-bin-if-possible (image-definition decache-p)
  (let* ((pathname? (full-pathname-of-image? image-definition))
	 (cacheable-p (and pathname?
			   (file-exists-p pathname?)))
	 (existing-bin? (image-definition-media-bin image-definition)))
    (cond
      (cacheable-p
       (let ((media-bin (image-definition-media-bin image-definition)))
	 (unless media-bin
	   (setf media-bin (make-transient-item 'media-bin))
	   (unless (transient-p image-definition)
	     (clear-transient media-bin)
	     (set-permanent-block media-bin))
	   (setf (image-definition-media-bin image-definition) media-bin)
	   (setf (media-bin-owner? media-bin) image-definition)
	   (frame-serial-number-setf (media-bin-owner-serial media-bin)
				     (frame-serial-number image-definition)))
	 (let ((file-description?
		 (let ((structure-or-false
			 (g2-media-bin-describe
			   media-bin
			   (allocate-evaluation-sequence
			     (eval-list
			       (copy-constant-wide-string #w"image"))))))
		   (cond ((eq structure-or-false evaluation-false-value)
			  nil)
			 (t
			  structure-or-false)))))
	   (when (or (null file-description?) decache-p)
	     (let ((namestring (gensym-namestring pathname?)))
	       (g2-media-bin-upload-binary-file
		 media-bin
		 (allocate-evaluation-sequence nil)
		 ; (copy-text-string (file-name-of-image? image-definition))
		 (copy-constant-wide-string #w"image")
		 namestring)
	       (reclaim-text-string namestring)))
	   (when file-description?
	     (reclaim-evaluation-structure file-description?)))))
      ((and existing-bin? decache-p)
       (delete-frame existing-bin?)
       (setf (image-definition-media-bin image-definition) nil))
      (t
       nil))
    (when pathname?
      (reclaim-gensym-pathname pathname?))))
  

(defun-void make-media-bin-for-g2-java-bean (g2-java-bean)
  (let ((media-bin nil))
    (setf media-bin (make-transient-item 'media-bin))
    (unless (transient-p g2-java-bean)
      (clear-transient media-bin)
      (set-permanent-block media-bin))
    (setf (g2-java-bean-media-bin g2-java-bean) media-bin)
    (setf (media-bin-owner? media-bin) g2-java-bean)
    (frame-serial-number-setf (media-bin-owner-serial media-bin)
			      (frame-serial-number g2-java-bean))))

;;;; Media Bin Errors

;; all of these functions consume their location argument

(defun media-bin-file-not-found-error (media-bin location)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error cached-top-of-stack
		 "Media file ~A not found in media bin ~NF"
		 location-string media-bin)))

(defun media-bin-file-locked-error (media-bin location)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error cached-top-of-stack
		 "file ~A in ~NF is locked"
		 location-string media-bin)))

(defun media-bin-non-directory-error (media-bin location)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error cached-top-of-stack
		 "~a in media bin ~NF is not a directory"
		 location-string media-bin)))

(defun media-bin-stream-must-be-binary-error (media-bin location)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error cached-top-of-stack
		 "~a in media bin ~NF must be BINARY"
		 location-string media-bin)))

(defun media-bin-unknown-io-direction-error (media-bin location direction)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error
      cached-top-of-stack
      "opening file, ~a, in media bin ~NF with unknown directionn ~A"
      location-string media-bin direction)))

(defun media-bin-unsupported-file-type-error (media-bin location file-type)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error
      cached-top-of-stack
      "opening file, ~a, in media bin ~NF with unsupported file type, ~A"
      location-string media-bin file-type)))

(defun media-bin-unsupported-mode-error (media-bin location mode)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error
      cached-top-of-stack
      "opening file, ~a, in media bin ~NF with unsupported mode, ~A"
      location-string media-bin mode)))

(defun media-bin-io-direction-error (media-bin location
					       stream-direction operation)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error
      cached-top-of-stack
      "attempting to ~a file, ~a, in media bin ~NF, open for ~a"
      operation location-string media-bin stream-direction)))

(defun media-bin-negative-length-error (media-bin location length)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error
      cached-top-of-stack
      "reading negative (~s) number of bytes or characters from ~a in ~NF"
      length location-string media-bin)))

(defun media-bin-already-exists-error (media-bin location)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error cached-top-of-stack
		 "attempting to create ~a in ~NF, which already exists"
		 location-string media-bin)))

(defun media-bin-stream-file-deleted-error (media-bin location)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error cached-top-of-stack
		 "attempting to use ~a in ~NF, which was deleted"
		 location-string media-bin)))

(defun media-bin-incompatible-file-type-error (media-bin location
					       file-type open-type)
  (let ((location-string (media-file-location-to-string location)))
    (stack-error cached-top-of-stack
		 "cannot open ~a in ~NF, a ~a file, as ~a"
		 location-string media-bin file-type open-type)))

(defun media-bin-no-such-stream-error (media-bin file-descriptor)
  (stack-error cached-top-of-stack
	       "No stream in ~NF known for file descriptor ~s"
	       media-bin file-descriptor))

(defun media-bin-no-local-file-error (media-bin local-file-name)
  (stack-error cached-top-of-stack
	       "Cannot open for ~a for uploading into ~NF"
	       local-file-name media-bin))

(defun media-file-location-to-string (location)
  (prog1
      (twith-output-to-text-string
	(loop for name in location
	      do
	  (twrite-string "/")
	  (twrite-string name)))
    (reclaim-slot-value location)))



;;;; Testing

#+development
(defun make-test-media-file (mb location name text-string)
  (let* ((name-copy (copy-text-string name))
	 (fd (g2-media-bin-open-stream mb
				      (allocate-evaluation-sequence 
					(loop for x in  location
					      collect
					      (copy-evaluation-value x)
					      using eval-cons))
				      name-copy
				      'output
				      'text
				      'create-or-overwrite)))
    (g2-media-bin-write mb fd (copy-text-string text-string))
    (g2-media-bin-close-stream mb fd evaluation-false-value)))

#+development
(defun make-test-binary-file (mb location name text-string)
  (let* ((name-copy (copy-text-string name))
	 (fd (g2-media-bin-open-stream mb
				      (allocate-evaluation-sequence 
					(loop for x in  location
					      collect
					      (copy-evaluation-value x)
					      using eval-cons))
				      name-copy
				      'output
				      'binary
				      'create-or-overwrite)))
    (g2-media-bin-write mb fd (copy-text-string text-string))
    (g2-media-bin-close-stream mb fd evaluation-false-value)))

#+development
(defun test-media-upload (mb filename local-filename)
  (g2-media-bin-upload-binary-file
    mb
    (allocate-evaluation-sequence nil)
    (copy-text-string filename)
    (copy-text-string local-filename)))
    

#+development
(defun pprint-media-buffer-bytes (string)
  (loop for i from 0 below (wide-string-length string)
	as code = (wide-character-code (charw string i))
	do
    (format t "~2,'0x~2,'0x" (logandf code 255) (ashf code -8))
    (when (=f 0 (modf (+f i 1) 4))
      (format t " "))
    (when (=f 0 (modf (+f i 1) 16))
      (format t "~%")))
  (format t "~%"))


(defun media-file-evaluation-value (file owner?)
  (allocate-evaluation-structure
    (nconc
      (when owner?
	(eval-list 'owner owner?))
      (eval-list 'type (media-file-type file)
		 'name (copy-text-string (media-file-name file))
		 'status (media-file-status file)
		 'contents (case (media-file-type file)
			     (directory
			      (allocate-evaluation-sequence
				(loop for element in (media-file-contents file)
				      collect (media-file-evaluation-value element nil)
					using eval-cons)))
			     (text
			      (allocate-evaluation-sequence
				(loop for element in (media-file-contents file)
				      collect (copy-text-string element)
					using eval-cons)))
			     (binary
			      (allocate-evaluation-sequence
				(loop for element in (media-file-contents file)
				      collect (mark-wide-string-as-binary (copy-text-string element))
					using eval-cons))))
		 'create-date (copy-evaluation-float
				(media-file-create-date file)))
      (unless (eq (media-file-type file) 'directory)
	(eval-list 'size-in-bytes (+f (*f 2 (media-file-size file))
				      (if (media-file-binary-odd-p file)
					  1 0)))))))

(defun evaluation-value-media-bin (evaluation-value)
  (unless (evaluation-structure-p evaluation-value)
    (return-from evaluation-value-media-bin
      (tformat-text-string "~S is not a structure" evaluation-value)))
  (let ((owner (evaluation-structure-slot evaluation-value 'owner))
	(type (evaluation-structure-slot evaluation-value 'type))
	(name (evaluation-structure-slot evaluation-value 'name))
	(status (evaluation-structure-slot evaluation-value 'status))
	(contents (evaluation-structure-slot evaluation-value 'contents))
	(create-date (evaluation-structure-slot evaluation-value 'create-date))
	(size-in-bytes (evaluation-structure-slot evaluation-value 'size-in-bytes)))
    (unless (or (null owner)
		(of-class-p owner 'image-definition)
		(of-class-p owner 'g2-java-bean))
      (return-from evaluation-value-media-bin
	(tformat-text-string "bad owner")))
    (unless (memq type '(directory text binary))
      (return-from evaluation-value-media-bin
	(tformat-text-string "media-bin type error")))
    (unless (text-string-p name)
      (return-from evaluation-value-media-bin
	(tformat-text-string "media-bin name error")))
    (unless (memq status '(normal new writing reading))
      (return-from evaluation-value-media-bin
	(tformat-text-string "media-bin status error")))
    (unless (or (null size-in-bytes)
		(and (fixnump size-in-bytes)
		     (<=f 0 size-in-bytes)))
      (return-from evaluation-value-media-bin
	(tformat-text-string "media-bin size-in-bytes error")))
    (unless (evaluation-float-p create-date)
      (return-from evaluation-value-media-bin
	(tformat-text-string "media-bin create-date error")))
    (unless (evaluation-sequence-p contents)
      (return-from evaluation-value-media-bin
	(tformat-text-string "media-bin contents error")))
    (setq contents
	  (loop for element being each evaluation-sequence-element of contents
		for value-or-error
		    = (if (eq type 'directory)
			  (if (evaluation-structure-p element)
			      (evaluation-value-media-bin element)
			      (tformat-text-string "media-bin contents error"))
			  (if (text-string-p element)
			      nil
			      (tformat-text-string "media-bin contents error")))
		do (when (text-string-p value-or-error)
		     (return-from evaluation-value-media-bin value-or-error))
		collect (or value-or-error
			    (copy-text-string element))
		  using slot-value-cons))
    (make-media-file-1
      type (copy-if-evaluation-value name)
      status
      (if size-in-bytes (ashf size-in-bytes -1) (length contents))
      contents
      (if size-in-bytes (=f 1 (logandf size-in-bytes 1)) nil)
      (copy-if-evaluation-value create-date))))

(def-virtual-attribute media-bin-data
    ((class media-bin)
     datum
     (exclude-from-wildcard-denotation t))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   nil)
  :getter
  ((media-bin)
   (media-file-evaluation-value
     (media-bin-data media-bin)
     (let ((owner? (media-bin-owner? media-bin)))
       (when (and owner?
		  (not (frame-has-been-reprocessed-p
			 owner? (media-bin-owner-serial media-bin))))
	 owner?))))
  :setter
  ((media-bin new-value)
   ;; this used to call evaluation-value-media-bin inside
   ;; a multiple-value-bind, but 
   ;; a second value is never returned, so I killed all
   ;; of that code. -alatto, 1/15/03
   (let ((media-data
	   (evaluation-value-media-bin new-value)))
     (cond ((text-string-p media-data)
	    media-data)
	   (t
	    (setf (media-bin-data media-bin) media-data)
	    nil)))))




;;;; Stubs for "new UI" features now deprecated

;;; What follows below this point are definitions that we no longer want used
;;; in G2, but can't simply be removed, because there may be instances dependent
;;; on them.

;;; `g2-new-secret-entity' - at some point in early T2 (Bristol) development,
;;; this was used extensively to create objects such as media bins and external
;;; java classes.  This is a pretty dangerous system procedure, because it
;;; circumvents the normal code that may run when items are created, it lets
;;; users create items that are normally not user-instantiable, and is just
;;; generally unhygienic.  We don't think it's actually being used any more, but
;;; it was contained in the kb sequoia-support.kb, which was shipped with T2.
;;; Given that this was part of the product for over five years, we should not
;;; remove it entirely, even though G2 handles that situation relatively well.
;;; We should instead throw a stack-error with a relatively informative message.
;;; I'm keeping the text of the implementation around, protected by a #+obsolete
;;; reader macro, simply for reference.  - jv, 4/23/02

(defun-for-system-procedure g2-new-secret-entity (workspace g2-window class-name)
  #+obsolete
  (let ((image-plane (map-to-image-plane-or-stack-error
		       workspace g2-window))
	;; guarded by previous form
	(workstation (workstation-for-g2-window? g2-window)))
    (for-workstation (workstation)
      (manifest-item-creation
	(make-entity class-name)
	image-plane
	(x-in-window-for-image-plane
	  (item-x-position workspace) image-plane)
	(y-in-window-for-image-plane
	  (item-y-position workspace) image-plane))))
  #-obsolete
  (progn
    workspace
    g2-window
    class-name
    (ui-stack-error
      "This kb has called an unsupported system procedure which is no longer ~
       present in G2.")))


;;; `tw-resource' - note that there is no "not-user-instantiable" flag here...
;;; users have been able to instantiate this class, and although there's
;;; very little point to doing so, it did appear in the directory of names
;;; and so was even prompted for.  Therefore I really think it's likely that
;;; people messed around and saved kbs with tw-resources in them, so we
;;; should be very careful about ever trying to fully remove it.  - jv, 4/02

(def-class (tw-resource (item entity)
			define-predicate
			(foundation-class tw-resource))
  
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (name-or-names-for-frame
    nil system (type nil) save)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (icon-color . foreground)
		   (g2-icon-specialty-region-1 . black)
		   (g2-icon-specialty-region-2 . gray))
       g2-icon-background
       (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading
       (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
		       ((0 0) (50 0) (47 3)) ((3 3) (3 47) (0 50))
		       ((0 0) (47 3) (3 3)) ((3 3) (0 50) (0 0)))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50))
		       ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50))
		       ((50 50) (3 47) (47 47)))
       icon-color
       (outline (0 0) (0 50) (50 50) (50 0))
       (text "TW-" (8 21) small)
       (text "RSRC" (9 40) small)
       (lines (44 5) (5 5) (5 45))
       g2-icon-light-shading
       (lines (5 45) (44 45) (44 5)))))

  #+res-g2-facilities			; grammar, slot putter, and compiler in
  (resource-definition			;    RES-G2, featured out (MHD 8/17/02)
    nil (type resource-definition text) vector-slot
    system save do-not-identify-in-attribute-tables
    do-not-clone)
  (resource-compilation
    nil vector-slot system)
  )


;;; `external-java-class' - class definition for Java syntax parsing.  This
;;; class is *NOT* user-instantiable, but of course it was instantiable in
;;; various other ways, and it's really not the best idea to remove this
;;; from the product altogether.

(def-class (external-java-class (item entity)
            not-user-instantiable define-predicate)
  (name-or-names-for-frame
    nil system (type name-or-names) save)
  (derive-names-automatically?
    nil vector-slot system (type yes-or-no) save)
  (java-class-and-interface-names
    nil
    (type java-class-and-interface-names)
    vector-slot system save not-user-editable)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-background . light-gray)
		   (g2-icon-dark-shading . dark-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-color . foreground)
		   (java-text-highlights . white)
		   (java-text . dark-slate-blue))
       (variables)
       (background-layer)
       g2-icon-background
         (solid-rectangle (0 0) (50 50))
       g2-icon-dark-shading
         (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
			 ((47 3) (50 0) (50 50)) ((50 50) (0 50) (3 47))
			 ((47 47) (47 3) (50 50))
			 ((50 50) (3 47) (47 47)))
       g2-icon-light-shading
         (lines (5 45) (44 45) (44 5))
       g2-icon-light-shading
         (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
			 ((0 0) (50 0) (47 3)) ((3 3) (3 47) (0 50))
			 ((0 0) (47 3) (3 3))
			 ((3 3) (0 50) (0 0)))
       g2-icon-color
         (outline (0 0) (0 50) (50 50) (50 0)) (lines (44 5) (5 5) (5 45))
       java-text-highlights (text #w"Java" (9 28) small)
       java-text (text #w"Java" (9 27) small) (text #w"Java" (8 27) small))))
  (java-syntax-version #w"1.1" system (type attribute) not-user-editable save)
  (package-declaration
    nil
    (type java-read-only-package-declaration)
    vector-slot system save not-user-editable)
  (import-declarations
    nil
    (type java-read-only-import-declarations)
    vector-slot system save not-user-editable)
  (compilation-unit
    nil (type java-compilation-unit-or-none text) vector-slot
    system save do-not-identify-in-attribute-tables)
  )
