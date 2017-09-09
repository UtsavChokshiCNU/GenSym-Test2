;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CTEST

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Valente



;;;; Explicit Stubs

;;; These functions get called by run-system-process.  They could just as easily
;;; get stubbed out in ctest-patches, but I think of that file as being more for
;;; functions which are merely referenced inside of files which are part of this
;;; system, rather than things that actually get called by code which makes up
;;; this system.  -jv, 7/24/07


;;; `shift-rule-ordering-heuristics' aka license-close-listener -- the CTEST
;;; system does not do authorization.

(defun shift-rule-ordering-heuristics ()
  1)


;;; `establish-g2-network-listeners' is a no-op for anything but G2.  Not sure
;;; why it is set up so every system calls it.

(defun establish-g2-network-listeners ()
  )


;;; `close-and-disconnect-all-sockets' - CTEST does not use ICP

(defun-void close-and-disconnect-all-sockets ()
  )


;;; Establish the `streams' cons pool

(defconser streams CTEST)

;;; `copy-list-using-streams-conses-function'

(defun copy-list-using-streams-conses-function (streams-list)
  (copy-list-using-streams-conses streams-list))

;;; `reclaim-streams-list-function'

(defun reclaim-streams-list-function (streams-list)
  (reclaim-streams-list streams-list))



;;; `Run-ctest' is the top-level run loop for Ctest.

(defun-allowing-unwind run-ctest (ignore-me)
  (declare (ignore ignore-me))
  (catch-abort (0)
    ;; (initialize-scheduler)
    ;; (initialize-gensym-time)
    #+development
    (show-foreign-functions)
    (shutdown-or-exit)))


;;;; System Access Definition for Ctest


;;; Definition of the Ctest System.

(define-system-access ctest)
