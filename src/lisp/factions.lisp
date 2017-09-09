
;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FACTIONS
; I can get no G2 faction (c)

;;; Copyright (c) 2017 Ignite 
;;; All Rights Reserved.

;;; Dmitri Hrapof


;;; FACTIONS cons pool
(defconser factions)

(declare-forward-reference get-pond-lock function)
(declare-forward-reference get-pond-queue-cv function)

;;; A `faction' is a sort of a lightweight thread/task.
;;; During runtime, it gets mapped to a CPU thread, but, that relationship is dynamic.
(def-class (faction object (foundation-class faction) define-predicate)
  (icon-description
    (:funcall-at-load-time
      create-icon-description ; (|)
      20 20 ((outline (0 0) (0 20) (20 20) (20 0))
             (circle (1 10) (10 1) (19 10))
             (lines (10 1) (10 19))
             )))
  (faction-members nil system vector-slot)
  (faction-running-p t system vector-slot))

;;; Dctor for `faction-members' slot
(def-slot-value-reclaimer faction-members (faction-members faction)
  (when faction-members (reclaim-constant-queue faction-members))
  (set-slot-value faction 'faction-members nil))
    
;;; Makes item a member of faction and returns item.
(defun-simple add-faction-member (item faction)
  (setf (faction? item) faction)
  (when faction
    (unless (faction-members faction)
      (setf (faction-members faction) (make-empty-constant-queue)))
    (constant-queue-filo-enqueue (faction-members faction) item))
  item)

;;; Removes item from its faction
(defun-simple remove-as-faction-member (item)
  (when (and (faction? item) (faction-members (faction? item)))
    (constant-queue-search-and-delete (faction-members (faction? item)) item))
  (setf (faction? item) nil)
  item)

;;; A loop path for faction members

(defun-for-macro faction-members-path
    (path-name variable data-type prep-phrases inclusive?
               allowed-preposistions data)
  (declare (ignore data-type data allowed-preposistions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S." path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~s path of ~s ~
            (prep-phrase = ~s)" path-name variable prep-phrases))
  (let* ((block-form-entry (assq 'of prep-phrases))
         (block-form (second block-form-entry))
         (queue-form (loop-gentemp 'queue-form-))
         (next-queue-element (loop-gentemp 'next-queue-element-))
         (init-bindings
           `((,queue-form (faction-members ,block-form))
             (,next-queue-element nil)
             (,variable nil)))
	 (prologue-forms
           `((when ,queue-form
               (setq ,next-queue-element
                   (constant-queue-head ,queue-form)
                   ))))
         (pre-step-tests `(eq ,next-queue-element ,queue-form))
         (steppings nil)
         (post-step-tests nil)
         (post-step-settings
           `(,variable (queue-datum ,next-queue-element)
             ,next-queue-element
             (constant-queue-next ,next-queue-element ,queue-form))))
    `(,init-bindings
      ,prologue-forms ,pre-step-tests ,steppings ,post-step-tests ,post-step-settings)))

(define-loop-path (faction-members faction-member)
                  faction-members-path (of))

;;; Propagates faction recursively
(defun propagate-faction-recursively (block)
  (loop for subblock being each subblock of block
     do (when (and (framep subblock) (block-p subblock))
	  (add-faction-member subblock (faction? block))
	  (unless (eq 'faction (class subblock))
	    (propagate-faction-recursively subblock))))
  (when (frame-of-class-p block 'entity)
    (loop for subblock in (subworkspaces block)
       do (when (and (framep subblock) (block-p subblock))
	    (add-faction-member subblock (faction? block))
	    (propagate-faction-recursively subblock)))))

;;; Unpropagates faction recursively
(defun unpropagate-faction-recursively (block)
  (loop for subblock being each subblock of block
     do (when (and (framep subblock) (block-p subblock))
	  (remove-as-faction-member subblock)
	  (unless (eq 'faction (class subblock))
	    (unpropagate-faction-recursively subblock))))
  (when (frame-of-class-p block 'entity)
    (loop for subblock in (subworkspaces block)
       do (when (and (framep subblock) (block-p subblock))
	    (remove-as-faction-member subblock)
	    (unpropagate-faction-recursively subblock)))))

;;; The stack of factions, the head being the faction the interpreter runs in
(defvar current-faction-global (factions-list nil))

;;; A thread pool for factions
(defvar other-factions-thread-pool)

;;; Adds the faction to the list of currently running factions
(defun add-faction-to-executing-list (faction)
  (add-unique-elem-to-payload faction other-factions-thread-pool))

;;; Removes the faction from the list of currently running factions
(defun remove-faction-from-executing-list (faction)
  (remove-unique-elem-from-payload faction other-factions-thread-pool))

;;; Starts a faction
(defun-for-system-procedure start-faction-lisp-side (faction)
  (when faction
    (tx:with-lock-held ((get-pond-lock other-factions-thread-pool))
      (setf (faction-running-p faction) t)
      (tx:condition-variable-signal
       (get-pond-queue-cv other-factions-thread-pool))))
  evaluation-true-value)

;;; Stops a faction
(defun-for-system-procedure stop-faction-lisp-side (faction)
  (when faction
    (tx:with-lock-held ((get-pond-lock other-factions-thread-pool))
      (setf (faction-running-p faction) nil)))
  evaluation-false-value)

;;; Is the faction running?
(defun-for-system-procedure faction-is-running-lisp-side (faction)
  (if (null faction)
      evaluation-true-value
      (tx:with-lock-held ((get-pond-lock other-factions-thread-pool))
	(if (faction-running-p faction)
	    evaluation-true-value
	    evaluation-false-value))))

      
  
