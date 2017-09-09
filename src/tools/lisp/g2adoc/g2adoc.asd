;;; -*- Lisp -*-
(defpackage :g2adoc-system (:use #:asdf #:cl))
(in-package :g2adoc-system)

(defsystem :g2adoc
    :name "g2adoc"
    :depends-on (:cxml)
    :author "Dmitri Hrapof <dmitri.hrapof@aurea.com>"
    :maintainer "Dmitri Hrapof <dmitri.hrapof@aurea.com>"
    :description "AsciiDoc generator for G2 plain-text KBs"
    :components
    ((:file "g2adoc")))
