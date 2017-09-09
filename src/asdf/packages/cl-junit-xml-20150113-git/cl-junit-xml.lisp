;;;; cl-junit-xml.lisp

(in-package #:cl-junit-xml)

;;; "cl-junit-xml" goes here. Hacks and glory await!

(defclass junit-xml ()
  ((testsuites :accessor testsuites :initarg :testsuites)))

(defclass junit-testsuite ()
  ((testcases :accessor testcases :initarg :testcases)
   (name :reader name :initarg :name)
   (pkg :reader pkg :initarg :package)
   (timestamp :reader timestamp :initarg :timestamp)))

(defclass junit-testcase ()
  ((name :reader name :initarg :name)
   (duration :reader duration :initarg :duration)
   (class-name :reader class-name :initarg :class-name)
   (error-text :reader error-text :initarg :error-text)
   (failure-text :reader failure-text :initarg :failure-text)))


(defgeneric write-xml (junit-xml sink &key pretty-p &allow-other-keys)
  (:documentation "write the junit to the given sink (string, pathname, T, nil)")
  (:method (junit-xml (sink string) &key pretty-p &allow-other-keys)
    (write-xml junit-xml (pathname sink) :pretty-p pretty-p))
  (:method (junit-xml (sink T) &key pretty-p &allow-other-keys)
    (format T (write-xml junit-xml nil :pretty-p pretty-p)))
  (:method (junit-xml (sink pathname) &key pretty-p &allow-other-keys)
    (ensure-directories-exist sink)
    (with-open-file (stream sink :direction :output :if-exists :supersede
                                 :element-type '(unsigned-byte 8))
      (%write-xml junit-xml
                  :sink (cxml:make-octet-stream-sink
                         stream :encoding :utf-8 :indentation (when pretty-p 2))))
    (truename sink))
  (:method (junit-xml (sink null) &key pretty-p &allow-other-keys)
    (with-output-to-string (s)
      (%write-xml junit-xml
                  :sink
                  (cxml:make-character-stream-sink
                   s :encoding :utf-8 :indentation (when pretty-p 2))))))

(defgeneric %write-xml (thing &key &allow-other-keys)
  (:method ((junit-xml junit-xml) &key sink &allow-other-keys)
    (with-xml-output sink
      (if (alexandria:sequence-of-length-p (testsuites junit-xml) 1)
          (%write-xml (first (testsuites junit-xml)))
          (with-element "testsuites"
            (iter (for id from 0)
              (for suite in (reverse (testsuites junit-xml)))
              (%write-xml suite :id id))))))

  (:method ((suite junit-testsuite) &key (id 0) &allow-other-keys)
    (with-element "testsuite"
      (attribute "name" (name suite))
      (when-let (pkg (pkg suite))
        (attribute "package" pkg))
      (when-let (ts (timestamp suite))
        (attribute "timestamp" ts))
      (attribute "id" id)
      (attribute "tests" (length (testcases suite)))
      (attribute "errors" (count-if #'error-text (testcases suite)))
      (attribute "failures" (count-if #'failure-text (testcases suite)))
      (attribute "time" (format nil "~,1f"
                                (reduce #'+ (testcases suite)
                                        :key #'duration)))
      (mapcar #'%write-xml (testcases suite))))

  (:method ((testcase junit-testcase) &key &allow-other-keys)
    (with-element "testcase"
      (attribute "name" (name testcase))
      (attribute "classname" (class-name testcase))
      (attribute "time" (format nil "~,1f"
                                (duration testcase)))
      (when-let ((text (error-text testcase)))
        (with-element "error" (cdata text)))
      (when-let ((text (failure-text testcase)))
        (with-element "failure" (cdata text))))))

(defun make-junit (&key testsuites)
  (make-instance 'junit-xml :testsuites testsuites))

(defun make-testsuite (name &key testcases timestamp package)
  (make-instance 'junit-testsuite
                 :name (princ-to-string name)
                 :package (unless (alexandria:emptyp package) package)
                 :testcases testcases :timestamp timestamp))

(defun make-testcase (name class-name duration &key error failure)
  (make-instance 'junit-testcase
                 :name (princ-to-string name)
                 :duration duration
                 :class-name (princ-to-string class-name)
                 :error-text (unless (alexandria:emptyp error) error)
                 :failure-text (unless (alexandria:emptyp failure) failure)))

(defgeneric add-child (parent child)
  (:method ((p junit-xml) (c junit-testsuite))
    (push c (testsuites p))
    c)
  (:method ((p junit-testsuite) (c junit-testcase))
    (push c (testcases p))
    c))
