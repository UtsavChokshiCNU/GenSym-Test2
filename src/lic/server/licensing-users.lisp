;;;; -*- Mode: Lisp; Package: USER; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")



;;;; Module LICENSING-USERS: The /etc/passwd file of the licensing server.







;;;; Introduction

;;; This module contains only three forms.  An in-package, a setf of
;;; *user-records*, and a check that things are well formed.  A copy of this is
;;; placed in where the licensing server can load it, requests to the licensing
;;; server may trigger the reading of it.  Note that we take care in that reader
;;; to preclude using this as a back door.







;;;; Database

(setf *user-records*
  '((:name guest
     :encrypted-password "67160tgv6pZ" ;; i.e. anonymous
     :permissions (basic login))
    (:name ddm
     :encrypted-password "6qr@tknsc" ;; Mumble-95b
     :permissions (root basic any-license temporary-license))
    (:name corpdb
     :encrypted-password "648s#xyC"
     :permissions (basic list-products any-license temporary-license))
    (:name orderserv
     :encrypted-password "6pdu4q5J"
     :permissions (root basic list-products any-license temporary-license))
    (:name binghe ; for test, ask for password from me ..
     :encrypted-password "62@s8M"
     :permissions (root basic list-products any-license temporary-license))))

;; (encrypt-licensing-password "example")







;;;; Load Time Checking

(let ((troubled-user? (find-troubled-user *user-records*)))
  (when troubled-user?
    (warn "Malformed User Info: ~S" troubled-user?)))
