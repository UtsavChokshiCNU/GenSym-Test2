 ;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module RG-REPORT

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author: Ben Hyde



;;; This module reads *.rg from <sandbox>/logs.
;;; These are the regression testing logs.
;;; What is read in is loaded into a list of tuples
;;; These tuples are of the form:
;;;  <machine> <test> <subtest-index> <subtest> <info-1> <info-2> <test-time>
;;; for example
;;;  (rwanda arraycpm 0 change-length ok nil 1234534)
;;; This list is stored into the global rg-info

;;; This module is loaded only in development.

;;; To use this, see the section Main Driver


;;;; Running reports standalone

;; This module was written to take advantage of code which was already
;; written for G2.  That is, it is in-package "AB", and it uses
;; functions defined in other modules of G2.  Therefore, you need to
;; run Lucid and load and compile G2 in order to use it.  (It is also
;; possible to set up a "system" for rg-report, so only the necessary
;; files are loaded; but a great deal of the code in the "necessary"
;; files is completely unnecessary for running regression reports.)
;; I often want to run regression reports without having to load G2
;; (like when I run them from home).  It turns out that this module
;; only called three external functions: `with-faster-standard-output',
;; `terminal-write-universal-time', and `gensym-copy-file'.  These
;; functions are very simple to redefine without using ab's stuff,
;; if you make the assumption that you are only running in Lucid on
;; a Unix machine.  I think this is a fair assumption for running
;; regression reports.  The first thing I did was to four new macros
;; to serve as wrappers around the functions.  Now, rg-report calls
;; `rg-with-faster-standard-output', `rg-write-current-universal-time', 
;; `rg-write-universal-time', and `rg-copy-file'.
;;
;; The alternate definitions will only be used if :simple-unix-rg is
;; in *features* list.  I added it to mine in my lisp-init file.
;; So when I run the regression reports, I get the simple, non-G2
;; implementation.  For anyone else (who doesn't copy my lisp-init
;; file or otherwise add :simple-unix-rg), the implementation should
;; be exactly the same.  And if it isn't, I'll fix it.  - jv 5/24/96

;(pushnew :simple-unix-rg *features*)
;(compile-file "rg-report.lisp")
;(load "rg-report")
;(in-package 'ab)
;(setq sandbox "<sandbox>") ;; e.g., "/bt/ab"
;(reps) ;; shorthand for (progn (collect-reports) (show-reports))


;;; `rg-with-faster-standard-output' - "with-faster-standard-output",
;;; defined in BOOTSTRAP, is a very simple macro, so I just duplicated
;;; it here with a different name.

(defmacro rg-with-faster-standard-output (&body forms)
  #+(and lucid (not translator))
  `(lcl:with-buffered-terminal-output (*standard-output*)
     ,@forms)
  #-(and lucid (not translator))
  `(progn ,@forms))



;;; `rg-copy-file' - "gensym-copy-file" is fairly complex, due to the
;;; variety of platforms on which G2 runs, and also due to the fact
;;; that it has to translate to C well.  When we just want to run
;;; regression reports, we needn't worry about these concerns.
;;; Under those circumstances, I will use Lucid's ability to fork
;;; a Unix process to use the "cp" command to copy the file.

(defmacro rg-copy-file (source destination)
  #+simple-unix-rg
  `(progn
     #+lucid
     (lcl::run-program
       "/bin/cp"
       :wait t
       :arguments (list ,source ,destination))
     #+allegro
     (let ((copy-command
            (format nil "/bin/cp ~A ~A" ,source ,destination)))
       (excl:run-shell-command copy-command :wait t))
     (values))
  #-simple-unix-rg
  `(gensym-copy-file ,source ,destination))

;;; similarly for deleting files...
(defmacro rg-delete-file (filename)
  #+simple-unix-rg
  `(progn
     #+lucid
     (lcl::run-program
       "/bin/rm"
       :wait t
       :arguments (list ,filename))
     #+allegro
     (let ((delete-command
            (format nil "/bin/rm ~A" ,filename)))
       (excl:run-shell-command delete-command :wait t))
     (values))
  #-simple-unix-rg
  `(gensym-delete-file ,filename))

(defmacro rg-commit-file (filename log-message)
;; #+simple-unix-rg
  `(progn
     #+lucid
     (lcl::run-program
       "cvs"
       :wait t
       :arguments (list "commit" "-m" ,log-message ,filename))
     #+allegro
     (let ((commit-command
            (format nil "/usr/local/bin/cvs commit -m ~s ~a"
                    ,log-message ,filename)))
       (excl:run-shell-command commit-command :wait t))
     (values))
  #-simple-unix-rg
  `(let ((commit-command
           (format nil "/usr/local/bin/cvs commit -m ~s ~a"
                    ,log-message ,filename)))
     ;; not sure why we are continuing to pretend that we will use this inside normal G2
     ;; anyway, leaking the command.  yduj, 4/14/00
     (unix-command-output-as-string commit-command)))

;;; `rg-write-universal-time'

(defun rg-write-universal-time (universal-time)
  (multiple-value-bind (second minute hour date month year
                               day-of-the-week daylight-savings-time-p time-zone)
      (decode-universal-time universal-time)
    (declare (ignore day-of-the-week daylight-savings-time-p time-zone))
    (format t "~2,'0d ~a ~d  ~d:~2,'0d:~2,'0d"
            ;; e.g. "10 Dec 1986  8:03:16"
            date
            (nth (- month 1)
                 '("Jan" "Feb" "Mar" "Apr" "May" "Jun"
                   "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))
            year
            hour minute second)))

;;; 

(defmacro rg-environment-variable (variable)
 #+simple-unix-rg
  `(progn
     #+lucid
     (lcl:environment-variable ,variable)
     #+allegro
     (system:getenv ,variable))  
#-simple-unix-rg
  `(get-gensym-environment-variable ,variable))


;;;; RG-REPORT


;;; sandbox is the name of the directory to snarf testing out of.
(defvar sandbox)

;;; srcbox is where the source files live, which may be exactly the same as
;;; the sandbox, or (in theory) might be completely different, but is likely
;;; going to be <sandbox>/src
(defvar srcbox)

;;; commit-report is a flag which is set by the calling script which specifies
;;; whether we wish to commit the results of this regression report to cvs
(defvar commit-report nil)


;;; supress-multiple-line-troubles-reporting-p

(defparameter supress-multiple-line-troubles-reporting-p t)


;;; as per above functions, get-delta-ID has a definition for being run within
;;; the context of a G2, vs. being run stand-alone.  its purpose is to extract
;;; the build ID from delta.lisp with the get-build-ID script, getting
;;; delta.lisp from the current spin id location.
(defmacro get-delta-ID ()
;;
  #+simple-unix-rg
  `(progn
     #+lucid
     (let ((stream (lcl::run-program
                     (format nil "~a/build/get-build-id" srcbox)
                     :arguments (format nil "~a/lisp" srcbox)
                     :output :stream
                     :wait nil)))
       (read-line stream))
     #+allegro
     (let ((command (format nil "~a/build/get-build-id ~a/lisp"
                            srcbox srcbox))
           ;; need to find out how to return a stream or string from the command
           (excl:run-shell-command command :wait t))))
  #-simple-unix-rg
  `(let* ((command (format nil "~a/build/get-build-id ~a/lisp"
                           srcbox srcbox)))
     (unix-command-output-as-string command)))


;;;; Data Recording Known Troubles with the Regression Testing.

;;; This data is used to annotate the report.  The list looks like
;;; ( (<TRBL/trouble-list> <NOTE/string>*)* )
;;; Any trouble that exactly matches TRBL will have each NOTE printed
;;; following it.

;;; The "known-troubles-list" contained lots of troubles which were
;;; unknown to me, so I'm removing them.  If they come up again, we
;;; should diagnose them from scratch.  - jv 3/8/96

(defparameter known-troubles-list
  '((nil ;; I.e. passed
     "Oh happy day!")
    ((:no-subtest-records)
     "Presumably the test aborted when an attempt was made to run it.")
    ((:logfile-is-old)
     "Presumably some stuff is lagging behind.")
    ((:platform-is-disabled
       :no-log-found)
     "Probably defer this.")))



;; (:bad-log-status failed-to-establish-connection)
;; This means that ESTABLISH-CONNECTION-AND-MONITOR-TEST  got false back
;; from ESTABLISH-G2-TO-G2-CONNECTION after waiting the length of time
;; given in the test's time out period.

;; (:bad-log-status starting)
;; This means that the test informed the master that he was starting if we
;; have some subtest records that's good, but otherwise the test failed
;; during the the subtest just after the one we last got a record for.

;; (:bad-log-status failed-to-complete)
;; This means that the ESTABLISH-CONNECTION-AND-MONITOR-TEST's
;; do-in-parallel exited without the local ran-ok to true.  That happens
;; for one of the following reasons:
;;  a. watch-for-kill-task-signal returned
;;  b. the test timed out.
;;  c. watch-for-g2-abort returned.
;;  d. the test failed to "start ok" i.e.
;;     set-testing-slaves-name-and-masters-name-and-port-number failed to
;;     return true.
;; I rewrote ESTABLISH-CONNECTION-AND-MONITOR-TEST to be more specific.






;;;; Parsing Utilities I

;;; Break-line-to-lisp-fields reads a line of lisp atoms and returns a 
;;; list.  I.e. "foo bar 123 1.2" -> (foo bar 123 1.2)

(defun break-line-to-lisp-fields (text-line)
  (loop with start = 0 
        with field
        with result = nil
        do
    (multiple-value-setq (field start)
      (read-from-string text-line nil :eof :start start))
    (when (eql field :eof)
      (return (nreverse result)))
    (push field result)))

(defun rg-assq (key pseudo-alist)
  (loop for element in pseudo-alist
        when (and (consp element)
                  (eql key (car element)))
          return element))

;;;; Long Term Knowledge

;;; `platform-info' is a list of lists, each in the form of the
;;; lines in "bt-machines.dat", i.e.
;;;  (bt-platform alphant   hy          nt active none      1200)
;;;     name      platform  machine     os status password  speed
;;;  The os is: nt unix vms mswindows
;;;  The status is: active disabled
;;;  Speed is relative to a basic 1000 being about rule/second.

(defun read-platform-info ()
  (let ((machine-file
          (format nil "~A/build/bt-machines.dat" srcbox)))
    (when (probe-file machine-file)
      ;; (format t "reading machines from ~A~%" machine-file)
      (with-open-file (f machine-file)
        (loop for line = (read-line f nil nil)
              while line
              for field-list = (break-line-to-lisp-fields line)
              when (and (eq (fifth field-list) 'active)
                        (not (eq (fourth field-list) 'mswindows)))
                collect field-list)))))

(defvar platform-info)

(defun build-machine-name-to-platform-name ()
  (loop as (nil platform machine-name) in platform-info
        nconc (list machine-name platform)))

(defvar machine-name-to-platform-name?)



(defparameter rg-test-info
              ;;   Name    Subtests
              '(
                (null-test       1)
                (func-30        69)
                (arraycpm        6)
                (stk-act        22)
                (stk-form       22)
                (stk-3-0        21)
                (conn-agh       32)
                (simulate        8)        
                (jh-eval       473)
                (text-func      30)
                (cpm-list       16)
                (cpm-gfi         6)
                (low-price       1)
                (mi-tests       19)
                (motor-maint     1)
                (mill-test       1)
                (batch-fill      1)
                (vinyl-3.0       1)
                (chrt01          1)
                (chgtxt          8)
                (snap-1          1)
                (draw01-test     5)
                (player-test     1)
                (opt-test        4)
                (qa-test        77)
                (change-attribute 8)
                (guide-player-test 4)
                (itempass       49)
                (history         2)
                (file-io        33)
                (g2-bench       26)
                (structs        24)
                (qa-itemx        99)
                (qa-subcl        51)
                (telewindow      1)
                (ng-telewindows  1 (intelnt))
                (gsi-regress   182 show-gsi-grid) ;; See Note
                ))

;; GSI-regress has 7*6  tests, i.e.
;;  - Seven individual tests.
;;  - Six platforms.

;; It is currently a problem that if one platform is corrupt, then
;; all platforms will report failures in their attempt to use that
;; platform.  As a result the report can look awful.  It is tempting
;; to have the report, or the test force such failures to OK, since
;; they are already refected in the total failure of the individual
;; platform. 

;; NG-TELEWINDOWS is a platform specific test that only runs on one platform.
;; In order to support this, we use the third element in rg-test-info as does
;; GSI-regress, but this time it is a list of platforms for which the test must
;; pass.  --yduJ, 4/6/05


(defparameter truncated-test-name-to-test-name
              (loop for (test-name) in rg-test-info
                    nconc
                      (list
                        (if (> (length (symbol-name test-name)) 6)
                            (intern (subseq (symbol-name test-name) 0 6))
                            test-name)
                        test-name)))





;;;; Parsing Utilities II

;;; Parse-rg-subtest-record reads the lines found in the .rg files
;;; and returns a list.  I.e.
;;; "Player-test,OK," --> (player-test ok)
;;; "my-test,Trouble,Gee this didn't work" ->
;;;                          (my-test trouble "Gee this didn't work")

(defun parse-rg-subtest-record (line stream)
  (cond
    ((zerop (length line))
     nil)
    (t
     (let ((start 0)
           end
           (result nil))
       (setf end (position #\, line :start start))
       (push (read-from-string line nil nil :start start :end end) result)
       (setf start (1+ end))
       (setf end (position #\, line :start start))
       (push (read-from-string line nil nil :start start :end end) result)
       (unless end (setf end 0))
       (setf start (1+ end))
       (push 
         (cond
           ((and (search "<<<" line)
                 (not (search ">>>" line)))
            (apply #'concatenate
                   'string
                   (loop with newline = (concatenate 'string '(#\newline))
                         for line = (read-line stream)
                         until (search ">>>" line)
                         collect line
                         collect newline)))
           (t
            (subseq line start)))
         result)
       (nreverse result)))))

(defun parse-rg-header (line)
  line)

(defun parse-rg-footer (line)
  ;; "end-of-file, bk, SETTING-UP-FOR-RUN, 13 Apr 92  11:11:08 a.m."
  ;;                                             -- new style
  ;; "end-of-file, bk, 13 Apr 92  11:11:08 a.m." -- old style
  (list
    (or
      (loop with count = 0
            with status-start
            with status-end
            for i from 0 below (length line) 
            for c = (char line i)
            when (eql #\, c) do (incf count)
            when (= 1 count) do (setf status-start (+ 3 i))
            when (= 2 count) do (setf status-end (1+ i))
            finally
              (when (and (= count 3)
                         status-start
                         status-end)
                (return (read-from-string (subseq line status-start
                                                  status-end)))))
      'unknown-test-run-status)
    line))
;; status:  
;;   unknown-test-run-status -- old style footer.
;;   not-yet-run
;;   passed
;;   failed-to-complete
;;   setting-up-for-run
;;   failed-to-establish-connection


;;; Get-platform-and-test-from i.e.: hoarrayc.rg --> (sgi arraycpm)

(defun get-platform-and-test-from (pathname)
  (unless machine-name-to-platform-name?
    (setq machine-name-to-platform-name?
          (build-machine-name-to-platform-name)))
  (loop with filename = (pathname-name pathname)
        with len = (length filename)
        for i from (max len 8) downto 4
        as machine-name = (intern (string-upcase
                                    (subseq filename 0 (- len i))))
        as truncated-test-name = (intern (string-upcase
                                          (subseq filename (- len i))))
        as platform-name? = (getf machine-name-to-platform-name?
                                  machine-name nil)
        as test-name? = (getf truncated-test-name-to-test-name
                              truncated-test-name nil)
        when (and platform-name?
                  test-name?)
          return (list platform-name?
                       test-name?)
        finally
          (warn "Unable to break apart log file name ~S ~
                into a known test and platform."
                filename)
          (return '(nil nil))))







;;;; Knowledge about the Recent Testing Results

(defvar test-results)

(defun clear-test-results ()
  (setf test-results
        (make-array (list
                      (length platform-info)
                      (length rg-test-info)))))

(defparameter current-troubles-list ())

(defparameter current-delta-ID nil)

(defun initialize-rg-reports (new-sandbox)
  (setq sandbox new-sandbox)
  (setq srcbox (format nil "~A/src" new-sandbox))
  (setq platform-info (read-platform-info))
  (setq machine-name-to-platform-name?
        (build-machine-name-to-platform-name))
  (clear-test-results)
  (setq current-delta-ID (get-delta-ID))
  sandbox)






;;;; Standard Report Generator


(defun do-grid-report
    (function
      &optional (end-of-line-function
                  #'(lambda (test-id special-report-flag?)
                      (declare (ignore test-id special-report-flag?)))))
  (let ((*print-case* :downcase))
    (loop initially (format t "~&~10T")
          for platform-index from 1 to (length platform-info)
          do (format t "~3D " platform-index))
    (loop initially (format t "~&~10T")
          for (nil nil machine-id) in platform-info
          do (format t " ~3A" (prefix-of-string machine-id 3)))
    (loop for (test . etc) in rg-test-info
          for test-index from 0
          do
      (format t "~&~2D ~6A " (1+ test-index) (prefix-of-string test 6))
      (loop for platform-index from 0 below (length platform-info) do
        (format t "~A"
                (let ((test-data (aref test-results platform-index
                                       test-index)))
                  (apply function
                         :test-data test-data
                         :expected-subtest-count (first etc)
                         :special-info? (second etc)
                         :real-platform (second (nth platform-index platform-info))
                         test-data))))
      (funcall
        end-of-line-function
        test
        (second etc)))))

;; new keyword real-platform gets passed to reporting functions.  Prior
;; assumption was that that the test data will contain the keyword :platform,
;; but if there's no log, test data is nil, and there's no platform keyword.
;; This is needed with a platform-specific tests such as ng-telewindows.  Can't
;; use :platform though, because then we'd be sending it twice in the case where
;; we have a test log.  yduJ 4/6/05


(defun prefix-of-string (string-or-symbol prefix-maximum-length)
  (let ((string (string (string string-or-symbol))))
    (nstring-downcase
     (subseq string 0
             (min prefix-maximum-length
                  (length string))))))

(defun report-key ()
  (let ((*print-case* :downcase))
    (loop for (nil platform machine-id) in platform-info
          as index from 1
          as beat from 0
          when (= 4 beat)
            do (setf beat 0)
          when (zerop beat)
            do (format t "~&")
          do (format t "  ~2D. ~15A" index (format nil "~A/~A"
                                                   platform machine-id)))
    (format t "~2%")
    (loop for (test) in rg-test-info
          as index from 1
          as beat from 0
          when (= 4 beat)
            do (setf beat 0)
          when (zerop beat)
            do (format t "~&")
          do (format t "  ~2D. ~12A" index test))))



;;;; I/O on the regression reports


;;; Two stages
;;;  1. read-rg-directory:
;;;     Do a *.rg and then get the write date of each file, creating
;;;     and initial plist values for the elements in the test-results
;;;     array.
;;;  2. read-rg-logs
;;;     Read each of the files and fill in the header, footer, and
;;;     subtest-records of the plists.
;;; 

(defun read-rg-directory ()
  (let ((g2-translate-log
          (format nil "~A/logs/g2-trans-tc.log" sandbox))
        (gsi-translate-log
          (format nil "~A/logs/gsi-trans-tc.log" sandbox))
        (glob-pattern (format nil "~A/logs/*.rg" sandbox)))
    (format t "~%")
    ;; (format t "g2-translate-log = ~A~%" g2-translate-log)
    ;; (format t "gsi-translate-log = ~A~%" gsi-translate-log)
    ;; (format t "glob-pattern = ~A~%" glob-pattern)
    (loop with translate-log-write-date = (file-write-date g2-translate-log)
          for pathname in (directory glob-pattern)
          as (platform test) = (get-platform-and-test-from pathname)
          as platform-index = (position platform platform-info :key #'second)
          as test-index = (position test rg-test-info :key #'first)
          as old-record = (aref test-results platform-index test-index)
          as write-date? = (file-write-date pathname)
          as new-file-write-date = (if (and write-date?
                                            (> write-date?
                                               translate-log-write-date))
                                       write-date?
                                       nil)
          as old-file-write-date = (getf old-record :logfile-write-date)
          if (eql old-file-write-date
                  new-file-write-date)
            do (format t ".")
          else
            (format t "x")
            (setf (aref test-results platform-index test-index)
                  (list
                    :platform platform 
                    :test test
                    :logfile-pathname pathname
                    :logfile-write-date new-file-write-date
                    :header nil
                    :footer nil
                    :subtest-records :not-read-yet)))
    (loop with translate-log-write-date = (file-write-date g2-translate-log)
          for (nil platform-id) in platform-info
          as pathname = (format nil "~A/logs/gsi-regress-~A/*.rg"
                               sandbox platform-id)
          as platform-index = (position platform-id platform-info
                                        :key #'second)
          as test-index = (position 'gsi-regress rg-test-info :key #'first)
          as write-date? = (file-write-date gsi-translate-log)
          as new-file-write-date = (if (and write-date?
                                            (> write-date?
                                               translate-log-write-date))
                                       write-date?
                                       nil)
          do
      (format t "x")
      (setf (aref test-results platform-index test-index)
            (list
              :platform platform-id
              :test 'gsi-regress
              :logfile-pathname (string-downcase pathname)
              :logfile-write-date new-file-write-date
              :header nil
            :footer nil
            :subtest-records :not-read-yet)))
  (report-run-dates)))

(defun read-rg-logs ()
  (do-grid-report 
      #'(lambda (&key logfile-pathname test-data subtest-records
                      &allow-other-keys)
          (cond
            ((not logfile-pathname)
             "  . ")
            ((eql subtest-records :not-read-yet)
             (read-rg-log logfile-pathname test-data))
            (T
           "  , ")))))

(defun read-rg-log (logfile-pathname
                    &optional
                    (test-data 
                      (apply #'get-log (get-platform-and-test-from
                                         logfile-pathname))))
  (if (eql (getf test-data :test) 'gsi-regress)
      (progn (setf (getf test-data :subtest-records) nil)
             (loop with translate-log-write-date
                     = (file-write-date
                         (format nil "~A/logs/g2-trans-tc.log" sandbox))
                   for pathname in (directory
                                     (getf test-data :logfile-pathname))
                   for logfile-write-date = (file-write-date pathname)
                   do
               (when (> logfile-write-date translate-log-write-date)
                 (with-open-file (f pathname)
                   (let ((header
                           (parse-rg-header (prog1 (read-line f nil nil)
                                              (read-line f nil nil))))
                         (subtest-records
                           (loop for subtest-record?
                                     = (parse-rg-subtest-record
                                         (read-line f nil nil) f)
                                 while subtest-record?
                                 collect subtest-record?))
                         (footer
                           (parse-rg-footer (read-line f nil nil)))
                         (logfile-write-date (file-write-date pathname)))
                     (setf (getf test-data :subtest-records)
                           (append (getf test-data :subtest-records)
                                   subtest-records))
                     (setf (getf test-data :header) header)
                     (setf (getf test-data :footer) footer)
                     (unless (and (getf test-data :logfile-write-date)
                                  (> (getf test-data :logfile-write-date)
                                     logfile-write-date))
                       (setf (getf test-data :logfile-write-date)
                             logfile-write-date))))))
             (format nil " ~3D" (length (getf test-data :subtest-records))))
      (with-open-file (logfile-stream logfile-pathname)
        (let ((header (parse-rg-header
                        (prog1 (read-line logfile-stream nil nil)
                           (read-line logfile-stream nil nil))))
              (subtest-records
                (loop for subtest-record? = (parse-rg-subtest-record 
                                          (read-line logfile-stream nil nil)
                                          logfile-stream)
                  while subtest-record?
                  collect subtest-record?))
              (footer (parse-rg-footer
                    (read-line logfile-stream nil nil))))
          (setf (getf test-data :subtest-records) subtest-records)
          (setf (getf test-data :header) header)
          (setf (getf test-data :footer) footer)
          (format nil " ~3D" (length subtest-records))))))

;;;; Report for how old the testing files are.

(defun report-run-dates ()
  (let ((now (get-universal-time)))
    (do-grid-report
        #'(lambda (&key logfile-write-date &allow-other-keys)
            (cond
              ((not logfile-write-date)
               "    ")
              ((< now logfile-write-date)
               " fut")
              (T
               (let ((hours-old (round
                                  (- now logfile-write-date)
                                  (* 60 60))))
                 (if (< 72 hours-old)
                     (format nil "~3Dd" (round hours-old 24))
                     (format nil "~3Dh" hours-old)))))))))



;;;; Report of how many subtests are in each log file.

(defun report-subtest-counts ()
  (do-grid-report 
      #'(lambda (&key test-data subtest-records
                      &allow-other-keys)
          (cond
            (subtest-records
             (format nil " ~3D" (length subtest-records)))
            ((not test-data)
             "   .")
            (t
             "   e"))))
  (format t "~& . : No log file")
  (format t "~& e : Log file had no entries"))




;;;; Create a list of troubles with a log file.

;;; `rg-log-troubles' takes a log as obtained from get-log and returns a
;;; list that attempts to characterize what is wrong with this log.  If
;;; the log seems fine then it returns NIL. The elements in this list may
;;;  include:
;;;   :no-log-found
;;;   :malformed-header
;;;   :malformed-footer
;;;   :no-subtest-records
;;;   (:too-few-subtest-records <number-missing> <test>)
;;;   (:too-many-subtest-records <number-found>)
;;;   :logfile-is-old           -- Older than G2's translate log
;;;   (:failed-subtest <subtest-id/symbol> <status/symbol> <info/text>)
;;;   :platform-is-disabled
;;;   (:percentage-subtest-that-passed <number>)
;;;          -- does not appear if exactly the right number
;;;             of subtests passed.

(defun rg-log-troubles (log &optional platform-id)
  (block :this
    (let ((result ()))
      (when (null log)
        (push :no-log-found result)
        (when platform-id
          (let* ((platform-info (find platform-id platform-info :key #'second))
                 (platform-is-active  (eql 'active (fifth platform-info))))
            (unless platform-is-active
              (push :platform-is-disabled result))))
        (return-from :this result))
       (let* ((this-is-old
               (file-write-date
                 (format nil "~A/logs/g2-trans-tc.log" sandbox)))
              (test (getf log :test))
              (platform (getf log :platform))
              (logfile-write-date (getf log :logfile-write-date))
              (header (getf log :header))
              (footer (getf log :footer))
              (subtest-records (getf log :subtest-records))
              (length-of-subtest-records (length subtest-records))
              (this-test-info (assq test rg-test-info))
              (expected-length-of-subtest-records (second this-test-info))
              (platform-info (find platform platform-info :key #'second))
              (platform-is-active (eql 'active (fifth platform-info))))
         (unless (= length-of-subtest-records
                    expected-length-of-subtest-records )
           (push (cond
                   ((zerop length-of-subtest-records)
                    :no-subtest-records)
                   ((or (null expected-length-of-subtest-records)
                        (null length-of-subtest-records))
                    (error "Null value"))
                   ((< length-of-subtest-records expected-length-of-subtest-records)
                    (list :too-few-subtest-records (- expected-length-of-subtest-records length-of-subtest-records) test))
                   (t
                    (list :too-many-subtest-records length-of-subtest-records)))
                 result))
         (unless platform-is-active
           (push :platform-is-disabled result))
         (unless (search "written" header)
           (push :malformed-header result))
         (cond
           ((not (search "end-of-file" (if (consp footer)
                                           (second footer)
                                           footer)))
            (push :malformed-footer result))
           ((and (consp footer)
                 (not (memq (car footer)
                            '(passed
                               unknown-test-run-status))))
            (let ((status (car footer)))
              (list :bad-log-status status)
              ;; Recognize some end of file status as being top level troubles.
              (case status
                (failed-to-establish-connection
                 (push
                   :launched-test-but-failed-to-establish-g2-to-g2-connection 
                   result))
                (monitor-test-timed-out
                 (push :timeout-while-monitoring-the-test-running result))
                (starting
                 (if (zerop length-of-subtest-records)
                     (push :test-started-but-we-lost-it-after-that result)
                     (push :test-started-but-we-do-not-know-how-it-finished
                           result)))
                ))))
         (when (or (null logfile-write-date)
                   (null this-is-old))
           (error "Null logfile write date"))
         (when (< logfile-write-date this-is-old)
           (push :logfile-is-old result))
         (loop with pass-count = 0
               finally 
                 (unless (= pass-count expected-length-of-subtest-records)
                   (push 
                     (list :percentage-subtest-that-passed
                           (truncate (* 100 pass-count)
                                     expected-length-of-subtest-records))
                     result))
               for (subtest-id status info) in subtest-records
               if (memq status '(OK PASSED))
                 do (incf pass-count)
               else
                 (setf info (simplify-failure-info info))
                 (push
                   (list :failed-subtest subtest-id status info)
                   result)
                 ;; Recognize some subtest status as being top level problems.
                 (case status
                   (player-script-timed-out
                    (push :player-script-timed-out result))))
         (return-from :this result)))))


;;; `simplify-failure-info' is used to discard some of the
;;; information returned in failure reports so that when
;;; grouping similar failures together using equal we will
;;; get the a useful result.

;; The messages we're searching for are of the form:
;; "\'the collection time of variable-with-collection-time-1' is 24.0 but
;;    should be 23""
;; and
;; "Failed ('the rate of change during the last 10.0000000 seconds' is
;;  0.2335766, but expected 1.0000000 within tolerance factor 5.0e-7)"

(defun simplify-failure-info (info)
  (cond
    ;; Discard the numbers that are much too volatile.
    ((and (search "is " info)
          (search " but should be " info))
     (concatenate 'string
                  (subseq info 0 (search "is " info))
                  "is ...##too volatile, hidden## "))
    ((search "the rate of change" info)
     (concatenate 'string
                  (subseq info 0 (search "the rate of change" info))
                  "the rate of change ... ##too volatile, hidden##"))
    (t
     info)))



(defun show-trouble-list (troubles)
  (cond
    ((null troubles)
     (format t "~&~15TPassed"))
    (t
     (loop for trouble in troubles
           do
       (cond
         ((consp trouble)
          (case (car trouble)
            (:failed-subtest
             (let ((failure-description (fourth trouble)))
               (cond
                 ((find #\newline failure-description)
                  (format t "~&~15T~S ~S"
                          (second trouble)
                          (third trouble))
                  (if supress-multiple-line-troubles-reporting-p
                      (format t " --- excessive detail suppressed ---")
                      (format t "~&~A" failure-description)))
                 (t
                  (format t "~&~15T~S ~S ~S" 
                          (second trouble)
                          (third trouble)
                          failure-description)))))
            (:too-few-subtest-records
             (let* ((test (third trouble))
                    (this-test-info (assq test rg-test-info))
                    (expected-length-of-subtest-records
                      (second this-test-info)))
               (format t "~&~15T~D missing subtest records of ~D in ~A." 
                       (second trouble)
                       expected-length-of-subtest-records
                       (third trouble))))
            (:too-many-subtest-records
             (format t "~&~15T~D subtest records seen, more than expected."
                     (second trouble)))
            (otherwise
             (format t "~&~15T~S" trouble))))
         (t
          (format t "~&~15T~S" trouble)))))))

(defun real-trouble (trouble-list)
  (not
    (or
      (null trouble-list)
      (memq :platform-is-disabled trouble-list))))







;;;; The Main Report

(defun report-summary ()
  (collect-current-troubles t)
  (do-grid-report 
      #'(lambda (&key
                 platform
                 test
                 test-data
                 subtest-records
                 special-info?
                 real-platform
                 &allow-other-keys)
          (cond
            ((and special-info? (symbolp special-info?))
             "")
            (t
             (let* ((log (and platform (get-log platform test)))
                    ;;pretend there are no troubles if this platform is not in
                    ;;the list of required platforms for this test
                    (trouble-list (when (or (null special-info?)
                                            (memq real-platform special-info?))
                                    (rg-log-troubles log)))
                    (character-label
                      (if trouble-list
                          (character-label-for-current-trouble trouble-list)
                          #\-)))
               (cond
                 ((and special-info?
                       (not (memq real-platform special-info?)))
                  ;;and return an empty string to demonstrate that it's OK
                  "    ")
                 ((not test-data)
                  "  . ")
                 ((not subtest-records)
                  (format nil "  E~C" character-label))
                 (t
                  (cond
                    ((null trouble-list)
                     " -- ")
                    (t
                     (loop with (nil nil)
                             = (assq test rg-test-info)
                           with passing-count = 0
                           with records-count = 0
                           for (nil status) in subtest-records
                           when (eql status 'ok)
                             do (incf passing-count)
                           do (incf records-count)
                           finally
                             (let* ((trouble-percentage-subtest-that-passed 
                                      (rg-assq :percentage-subtest-that-passed
                                               trouble-list))
                                    (percent (second
                                               (or trouble-percentage-subtest-that-passed
                                                   '(:percentage-subtest-that-passed 100)))))
                               (return
                                 (cond
                                   ((not trouble-percentage-subtest-that-passed)
                                    (format nil " --~C" character-label))
                                   ((<= 100 percent)
                                    (format nil " ??~C" character-label))
                                   (t
                                    (format nil " ~2D~C" percent character-label)
                                    )))))))))))))
    #'(lambda (test-id special-info?)
        (cond
          ((and special-info? (symbolp special-info?))
           (format t " ...Z"))
          (t
           (loop initially (format t "  ")
                 for (trouble . victims) in current-troubles-list
                 as trouble-index from 0
                 when (and (real-trouble trouble)
                           (find test-id victims :key #'first))
                   do (format t "~C" (character-label trouble-index)))))))
  (format t  "~&   --   : Expected number of subtests passed.")
  (format t  "~&   ??   : More than 100% passed?")
  (format t  "~&   .    : No log file")
  (format t  "~&   E    : No entries in log file")
  (format t  "~&   Z    : See special report below")
  (key-line-for-trouble-kind :player-script-timed-out
                             "Player script timed out.")
  (key-line-for-trouble-kind :too-many-subtest-records 
                             "Too many subtest reports")
  (key-line-for-trouble-kind :too-few-subtest-records 
                             "Too few subtest reports")
  (key-line-for-trouble-kind :test-started-but-we-do-not-know-how-it-finished 
                             "Test started but we do not know how it finished.")
  (key-line-for-trouble-kind :test-started-but-we-lost-it-after-that
                             "Test started but we lost it after that.")
  (key-line-for-trouble-kind
    :launched-test-but-failed-to-establish-g2-to-g2-connection
    "Launched test but failed to establish g2 to g2 connection.")
  (key-line-for-trouble-kind :timeout-while-monitoring-the-test-running
                             "Timeout while monitoring the test running.")
  (key-line-for-trouble-kind :logfile-is-old
                             "Old logfile, i.e. older than the translate log."
                             )
  (format t  "~&        : Other problem see below~%~%"))

(defun key-line-for-trouble-kind (kind text)
  (let ((troubles-of-kind
          (loop for (trouble-list) in current-troubles-list
                as i from 0
                when (loop for trouble in trouble-list
                               thereis
                                 (or (eq kind trouble)
                                     (and (consp trouble)
                                          (eq kind (car trouble)))))
                  collect i)))
    (when troubles-of-kind
      (loop initially (format t "~&   ")
            finally (format t "~8T: ~A" text)
            for i in troubles-of-kind
            as char = (character-label i)
            do (format t "~C" char)))))



;;;; Main Driver


;;; The routine `Collect-reports' is used to read the log file
;;; info into your process.  If run repeatedly it will read in
;;; the logs that are newer, according to their write dates. 
;;; The function `Clear-test-results' will cause it to forget
;;; all the reports logs info previously loaded.
;;;
;;; The routine `Show-reports' will write a report file into:
;;;   <sandbox>/logs/regression-summary.log

;;; Don't get confused into thinking that the report-like output
;;; that appears in your background stream is the actual report,
;;; it's isn't.  It is more like a progress indicator.

;;; A typical usage pattern is:
;;;      ` (progn (collect-reports) (show-reports)) '
;;;
;;; ... which is fine when your in emacs and you can just type
;;; it once and then do meta-p to re-run them.  But I am trying
;;; to save memory, and for regression testing I run Lucid as
;;; a shell process in an xterm, in which case, I would like to
;;; have a nice, short abbreviation:

(defun reps ()
  (collect-reports)
  (show-reports))


;;; `Collect-reports' does the file I/O necessary to load the full set of
;;; regression report logs into lisp.  These are stored in the 
;;; variable test-results.

(defun collect-reports ()
  ;; (clear-test-results)
  (initialize-rg-reports sandbox)
  (rg-with-faster-standard-output
    (format t "~3& ---- How old the log files are ---")
    (read-rg-directory)
    (format t "~3& ---- How many subtests results are in each log file. ---")
    (read-rg-logs)
    (format t "~3& ---- Testing Scores. ---")
    (report-summary)))



;;; `Show-reports' creates the standard set of reports.  These are placed
;;; in <sandbox>/logs/regression-summary.log

(defun show-reports ()
  (rg-with-faster-standard-output 
    (with-open-file (xxx  "/tmp/regression-summary.log"
                          :direction :output)
      (let ((*standard-output*
              (make-broadcast-stream *standard-output* xxx)))
        (format t "~&Build (~A) started: ~A"
                current-delta-ID
                (let* ((build-prep-log
                         (format nil "~A/logs/build-prep-trans-tc.log" sandbox))
                       (line
                         (with-open-file (in build-prep-log)
                           (read-line in))))
                  (subseq (string line) (+ 6 (search "start" line)))))
        (format t "~&G2 translate finished: ")
        (rg-write-universal-time
          (file-write-date
            (format nil "~A/logs/g2-trans-tc.log" sandbox)))
        (format t "~&Regression testing report generated: ")
        (rg-write-universal-time (get-universal-time))
        (format t "~%")
        (report-summary)
        (format t "~2&")
        (report-key)
        (format t "~3& ---- How old the log files are ---")
        (report-run-dates) 
        (format t "~3& ---- How many subtests results are in each ~
                            log file. ---")
        (report-subtest-counts)
        (format t "~5&")
        (show-collected-troubles t)
        (show-gsi-grid))))
  (print "Moving the file around..")
  (let ((logfilename (format nil "~A/logs/regression-summary.log" sandbox))
        (cvsfilename (format nil "~A/tests/regression-summary.log" srcbox))
        (log-message (format nil "Automatic commit of regression summary for build ~a"
                             current-delta-ID)))
    (rg-copy-file "/tmp/regression-summary.log" logfilename)
    ;;Only do the copy if we are logged in as "ab", so that the copy likely succeeds.
    (when (and commit-report (equal (rg-environment-variable "USER") "ab"))
      (print "committing the resulting log file to CVS.")
      (rg-copy-file "/tmp/regression-summary.log" cvsfilename)
      (rg-commit-file cvsfilename log-message))
    (rg-delete-file "/tmp/regression-summary.log")))


;;; Get-log <platform> <test>
;;; returns the list structure used to store the parse of a log file.
;;; <platform> may be an integer, platform-id, or host-id
;;;       e.g.           3      hp9000s700      tibet
;;; <test> may be an integer, test-name, or the first 6 chars of the test name
;;;       e.g.           2      batch-3-0     batch-

(defun get-log (platform-index-or-id test-index-or-id)
  (let ((platform-index (if (integerp platform-index-or-id)
                            (1- platform-index-or-id)
                            (or (position platform-index-or-id platform-info
                                          :key #'second)
                                (position platform-index-or-id platform-info
                                          :key #'third))))
        (test-index (if (integerp test-index-or-id)
                        (1- test-index-or-id)
                        (or (position test-index-or-id rg-test-info :key #'first)
                            (loop for (short-name real-name) on
                                  truncated-test-name-to-test-name by #'cddr
                                  when (eql short-name test-index-or-id)
                                    return (position real-name rg-test-info
                                                     :key #'first))))))
    (assert (integerp platform-index) ()
            "Unknown platform.~S " platform-index-or-id)
    (assert (integerp test-index) () "Unknown test. ~S" test-index-or-id) 
    (aref test-results platform-index test-index)))


;;; `show-troubles' does rg-log-troubles on every possible get-log and
;;; reports all that are in trouble.  Anything that these patterns of
;;; trouble:  '(:no-log-found)
;;;           '( ... :logfile-is-old ... )

(defun show-troubles (&optional show-all)
  (loop with *print-case* = :downcase
        for (test-id) in rg-test-info
        do
    (loop for (nil platform-id) in platform-info
          as troubles = (rg-log-troubles (get-log platform-id test-id)
                                         platform-id)
      when (or show-all
               (and troubles
                    (not (equal troubles '(:no-log-found)))
                    (not (equal troubles '(:logfile-is-old)))
                    (not (memq :logfile-is-old troubles))
                    ))
        do
          (format t "~&~10A ~15A" test-id platform-id)
          (show-trouble-list troubles))))



(defun collect-current-troubles (show-all)
  (let ((table (make-hash-table :test #'equal)))
    
    ;; Collect all the kinds of trouble, and who has them.
    (loop for (test-id nil platform-list) in rg-test-info
          do
      (unless (eq test-id 'gsi-regress)
        (loop for (nil platform-id) in platform-info
              as troubles = (rg-log-troubles (get-log platform-id test-id)
                                             platform-id)
              when (and
                     (or show-all
                         (and troubles
                              (not (equal troubles '(:no-log-found)))
                              (not (equal troubles '(:logfile-is-old)))
                              (not (memq :logfile-is-old troubles))
                              ))
                     ;;don't include a trouble if it's not supposed to have a
                     ;;log file for this platform
                     (or (null platform-list)
                         (memq platform-id platform-list)))
                do
                  (push (list test-id platform-id)
                        (gethash troubles table '())))))

    (let ((collected-troubles nil))
      (maphash
        #'(lambda (troubles victims)
            (push (cons troubles victims) collected-troubles))
        table)
      (setf collected-troubles
            (sort collected-troubles #'string< 
                  :key #'(lambda (x)
                           ;; Put this common failure at the front.
                           ;; otherwise sort by test name.
                           (if (equal '(:logfile-is-old) (car x))
                               "AAAAAAAAAAA"
                               (symbol-name (car (car (cdr x))))))))
      (setf current-troubles-list collected-troubles))))


;;; `character-label` ...

(defun character-label (integer)
  (code-char (+ (char-code #\a)
                (min 25
                     integer))))

;;; `character-label-for-current-trouble' ...

(defun character-label-for-current-trouble (trouble-list)
  (character-label
    (position trouble-list
              current-troubles-list
              :key #'car :test #'equal)))



;;; `show-collected-troubles' is like show-troubles but it sorts the
;;; report so that things with the same trouble appear together.

(defun show-collected-troubles (&optional show-all)
  (collect-current-troubles show-all)
  ;;; Print a Report
  (let ((*print-case* :downcase)
        (known-troubles (make-hash-table :test #'equal)))
    ;; Index the set of known troubles.
    (loop for (trouble . comments) in known-troubles-list
          do (setf (gethash trouble known-troubles)
                   comments))
    (loop for (troubles . victims) in current-troubles-list
          as count from 1
          as character-label-for-current-trouble 
             = (character-label (1- count))
          do
      (loop with previous-test = nil
            for (test platform) in (reverse victims)
            do
        (unless (eql previous-test test)
          (format t "~&")
          (unless previous-test
            (format t "~C. #~D" character-label-for-current-trouble count))
          (format t "~4T~11S on" test)
          (setf previous-test test))
        (format t " ~S" platform))
      (show-trouble-list troubles)
      (let ((comments? (gethash troubles known-troubles nil)))
        (when comments?
          (loop for comment in comments?
                do (format t "~&~15T>~A" comment)))))))














;;;; GSI Report


;;; `gsi-test-names' is were we accumulate all known GSI tests from the logs.

(defvar gsi-test-names ())



;; The subtests names look like this:
;;  LISP-BASED-GSI---FLOAT_1_ON_INTELNT_OVER_TCP-IP
;;   <implementation>-GSI---<test>_ON_<platform>_OVER_<transport>
;; <implementation> : LISP C

(defun pick-apart-gsi-test-name (test-name)
  (let* ((name (symbol-name test-name))
         (start 0))
    (flet ((eat (delim)
             (let ((end? (search delim name :start2 start)))
               (unless end?
                 (return-from pick-apart-gsi-test-name nil))
               (prog1
                   (intern (subseq name start end?))
                 (setf start (+ end? (length delim)))))))
      (values
        (let ((test (eat "_ON_")))
          (pushnew test gsi-test-names)
          test)
        (eat "_OVER_")
        (intern (subseq name start))))))


(defvar gsi-troubles ())
(defvar gsi-host-data nil)
(defvar gsi-trouble-data nil)





(defun set-host-data-from-gsi-log (subtests)
  (loop with initial-value = (if subtests -1 -2)
        for platform-index from 0 below (length platform-info) do
    (setf (aref gsi-host-data platform-index tcpip-protocol) initial-value))
  (when subtests
    (let ((troubles gsi-trouble-data))
      (loop for (name status info) in subtests
            do
        (multiple-value-bind (test-name host-name transport-name)
            (pick-apart-gsi-test-name name)
          (declare (ignore transport-name))
          (let ((platform-index
                  (position host-name platform-info :key #'second))
                (not-enabled-p (search "Platform not enabled" info))
                (not-supported-p (search "not supported" info)))
            (when (= -1 (aref gsi-host-data platform-index tcpip-protocol))
              (setf (aref gsi-host-data platform-index tcpip-protocol) 0))
            (cond
              ((member status '(ok passed))
               (cond
                 (not-supported-p
                  (setf (aref gsi-host-data platform-index tcpip-protocol) -20))
                 (not-enabled-p
                  (setf (aref gsi-host-data platform-index tcpip-protocol) -30))
                 (t
                  (incf (aref gsi-host-data platform-index tcpip-protocol)))))
              ((not not-supported-p)
               ;; Real failure, add to the failure signature.
               (push (list test-name);  info)
                     (aref troubles platform-index tcpip-protocol)))))))
      (loop for platform-index from 0 below (length platform-info)
            as trouble? = (aref troubles platform-index tcpip-protocol)
            when (and trouble?
                      (not (member trouble? gsi-troubles :test #'equal)))
              do
                (setf gsi-troubles
                      (nconc
                        gsi-troubles
                        (list trouble?)))))))





(defun gsi-report-result-character (protocol platform)
  (let ((count (aref gsi-host-data platform protocol)))
    (cond
      ((= count number-of-gsi-subtests) "-")
      ((= count -2) "!")
      ((= count -1) "?")
      ((<= -20 count -11) "~")
      ((<= -30 count -21) "D")
      (t
       (let ((trouble?
               (aref gsi-trouble-data platform protocol)))
         (if trouble?
             (character-label
               (position trouble? gsi-troubles
                         :test #'equal))
             count))))))


(defun print-line-of-gsi-report ()
  (loop for platform-index from 0 below (length platform-info) do
    (format t " ~1A  "
            (gsi-report-result-character
              tcpip-protocol platform-index))))



(defun print-explanation-of-gsi-reports ()
  (format t "~%")
  (format t "~%  E -- no log file found.")
  (format t "~%  x -- log file older than last gsi translation.")
  (format t "~%  X -- log file even four days older than that.")
  (format t "~%  L -- less than expected number of subtest reports.")
  (format t "~%  M -- more than    \"       \"          \"       \"   .")
  (format t "~%  - -- is ~d passing, i.e. perfect." number-of-gsi-subtests)
  (format t "~%  ~~ -- reported as not supported.")
  (format t "~%  D -- column's host was disabled when test was run.")
  (format t "~%  ! -- no file, or no data in file. ")
  (format t "~%  ? -- is no data in log for this.")
  (format t "~%  # -- is number of tests that passed. <unused code>"))
  


(defun show-gsi-grid ()
  (setf gsi-test-names nil)
  (setf gsi-troubles nil)
  (format t "~5&Report for gsi-regress: G2 vs. GSI,  Rows vs. Columns")
  (format t "~&~6t")
  (loop
    for (nil nil host-id) in platform-info
    do (format t "~3a "
               (nstring-downcase (subseq (symbol-name host-id)
                                         0
                                         (min 3
                                              (length
                                                (symbol-name host-id)))))))
  (loop
    with this-is-old 
      = (file-write-date
          (format nil "~A/logs/gsi-trans-tc.log" sandbox))
    with this-is-very-old = (- this-is-old (* 4 60 60 24))
    with gsi-host-data = (make-array (list (length platform-info)
                                       number-of-protocols)
                                     :element-type 'fixnum)
    with expected-count-of-results = (second (assq 'gsi-regress rg-test-info))
    for gsi-trouble-data = (make-array (list (length platform-info)
                                       number-of-protocols)
                                   :initial-element nil)
    for (nil platform-id host-id) in platform-info
    as log = (get-log platform-id 'gsi-regress)
    as logfile-write-date?
       = (getf log :logfile-write-date)
    as subtests = (getf log :SUBTEST-RECORDS)
    do
    (set-host-data-from-gsi-log subtests)
    (format t "~&~3a ~A~A"
            (nstring-downcase (subseq (symbol-name host-id)
                                      0
                                      (min 3
                                           (length
                                             (symbol-name host-id)))))
            (cond
              ((not logfile-write-date?) "E")              
              ((= expected-count-of-results (length subtests)) " ")
              ((< expected-count-of-results (length subtests)) "?")
              (t                         "L"))
            (cond
              ((not logfile-write-date?)           " ")
              ((< logfile-write-date? this-is-very-old) "X")
              ((< logfile-write-date? this-is-old) "x")
              (t                                   " ")))
    (print-line-of-gsi-report))
  (print-explanation-of-gsi-reports)
  (when gsi-troubles
    (setf gsi-test-names (sort gsi-test-names #'string<))
    (loop for i in gsi-test-names
          initially (format t "~2&    ")
          do (format t "~10A" i))
    (loop
      for trouble in gsi-troubles
      for i from 0 do
      (format t "~&  ~A " (character-label i))
      (loop for test-name in gsi-test-names
            do (format t "~10A"
                       (if (member test-name trouble :key #'first)
                           "  X" "  -"))))))





;;; `Show-log' prints the log (as obtained with get-log).  The show-all
;;; flag requests that all subtest records be shown, usually the OK ones
;;; are suppressed.

(defun show-log (log &optional show-all)
  (assert (consp log) () "Bad log, should be the return value of get-log")
  (loop
       with platform = (getf log :platform)
       with test = (getf log :test)
       with logfile-pathname = (getf log :logfile-pathname)
       with logfile-write-date = (getf log :logfile-write-date)
       with header = (getf log :header)
       with footer = (getf log :footer)
       with subtest-records = (getf log :subtest-records)
       with this-test-info = (assq test rg-test-info)
       with (nil nil) = this-test-info
       with troubles = (rg-log-troubles log)
       initially
       (format t "~&~A on ~A with ~D subtests"
               test
               platform
               (length subtest-records))
       (if (consp troubles)
           (format t " ~D TROUBLES" (length troubles))
           (format t " seems ok."))
       (format t "~&Header: ~A" header)
       (format t "~&Footer: ~A" footer)
       (format t "~&Log File: ~A" (namestring logfile-pathname))
       (format t "~&Log Date: ~A" (namestring logfile-pathname))
       (rg-write-universal-time logfile-write-date)
       (unless show-all
         (format t "~&Showing only those records that are not OK."))
       for subtest-info in subtest-records
       as (subtest status info) = subtest-info
       do
       (when (or show-all
                 (not (eql 'OK status)))
         (format t "~&~20A ~20A ~A" subtest status info)))
  (values))



;;; `show-logs' will print a slice of the logs using get-log and show-log.
;;; The tests and platforms can be specified with a pattern.
;;;  a number
;;;  a symbol
;;;  a list of number or symbol
;;;  the symbol T 
;;; For example
;;; (show-logs t '(4 5 8)) -- shows 3 tests on all platforms
;;; (show-logs 7 t) -- shows all tests on platforms 7.
;;; The platform name maybe either the host-id or the platform-id
;;; The test name maybe either the full test name of the 6 character name.

(defun show-logs (platforms tests &optional show-all)
  (loop for test in (cond
                      ((consp tests)
                       tests)
                      ((eql t tests)
                       (loop for (test) in rg-test-info 
                             collect test))
                      (t
                       (list tests)))
        do
    (loop for platform in (cond
                            ((consp platforms)
                             tests)
                            ((eql t platforms)
                             (loop for (nil p nil nil active?) in platform-info 
                                   when (eql active? 'active)  collect p))
                            (t
                             (list platforms)))
          as log = (get-log platform test)
          when log 
            do
              (format t "~2&")
              (show-log log show-all)))
  (values))

