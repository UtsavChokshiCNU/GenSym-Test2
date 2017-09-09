;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module VIEW-MSG1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Joe Devlin

;;;; View Messages

;;; View messages are messages that define the conversation
;;; between G2 and TW in versions 5 and later.  They live
;;; in the space of ICP messages currently (#'s 400-799)
;;; and use standard icp argument types.  See documentation
;;; in INTn for details.

;;; This interface is abstracted away from ICP and provides
;;; a more perspicuous interface around asymmetric messages.
;;; View message definitions are in this file which is present
;;; in both TW and G2.  The implementations of the messages
;;; handled by G2 are in view-g2.  The implementations of those
;;; handled in TW are defined in view-tw.  If any symmetric messages
;;; crop up def-view-messsage will be extended to provide
;;; a means for definition and a third file of handlers
;;; will be introduced, called view-common.

;; 2do
;; get some part of the workspace message to work
;;  (like having format message come up in the tw buffer)
;; object handle management
;; make ill-behaved frame-rep handling code respect non-TABLE classes

(def-global-property-name view-message-receiver)
(def-global-property-name view-message-sender)
(def-global-property-name object-definition-message-receiver)
(def-global-property-name object-definition-message-sender)




;;;;  WS-represntation-types

;;; WS-represntation-types are a set of reduced complexity classes/types
;;; describing a user interface perspective on what an object (on a kb-workspace)
;;; can be.  The canonical examples is that pumps and tanks are both
;;; classes that are drawn with icons and can accept connections.  Telewindows,
;;; or any other UI, does not need to know any further details.

(def-global-property-name ws-representation-type)

(def-structure ws-representation-type
  ws-representation-type-name 
  ws-representation-type-needs-instance-representation-p 
  ws-representation-type-property-spec
  ws-representation-type-property-getter)
  
(defmacro def-workspace-representation-type
    (name &key needs-instance-representation-p 
	  property-spec property-getter)
  `(let ((ws-rep-type (make-ws-representation-type)))
     (setf (ws-representation-type ',name) ws-rep-type)
     (setf (ws-representation-type-name ws-rep-type) ',name)
     (setf (ws-representation-type-needs-instance-representation-p
	     ws-rep-type) ,needs-instance-representation-p)
     (setf (ws-representation-type-property-spec ws-rep-type)
	   ',property-spec)
     (setf (ws-representation-type-property-getter ws-rep-type)
	   ',property-getter)))



;; Entities

(def-workspace-representation-type icon-with-connections)

(def-workspace-representation-type icon-without-connections)

(def-workspace-representation-type loose-end)

(def-workspace-representation-type connection
    :property-spec (structure style symbol
			   stub-length integer)
    :property-getter connection-property-getter)


			   
;; Text-boxes
;; with-border or without-border

(def-workspace-representation-type text-box
    :property-spec     (structure text-lines sequence
				  text-box-format structure)
    :property-getter   text-box-property-getter)

;; edit-box??
;; dialog-buttons???

;; Displays

(def-workspace-representation-type readout-table
    :property-spec   ((row-label row-info))
    :property-getter table-property-getter)

(def-workspace-representation-type dial
    :property-spec   (low-value high-value increment)   
    :property-getter dial-property-getter)

(def-workspace-representation-type meter
    :property-spec   (low-value high-value increment)    
    :property-getter meter-property-getter)

(def-workspace-representation-type trend-chart
    :needs-instance-representation-p t
    :property-spec   trend-chart-property-spec     
    :property-getter trend-chart-property-getter)

(def-workspace-representation-type graph 
  ;; old graphs are represented as gray rectangles in 5.0!
  )

(def-workspace-representation-type chart
    :property-spec   chart-property-spec     
    :property-getter chart-property-getter)

(def-workspace-representation-type freeform-table
    :property-spec    ((row-label row-info)(row-label row-info))
    :property-getter   table-property-getter)


;; Buttons

(def-workspace-representation-type action-button
    :property-spec   (label button-state)
    :property-getter action-button-property-getter)

(def-workspace-representation-type radio-button
    :property-spec   (label button-state)
    :property-getter radio-button-property-getter)


(def-workspace-representation-type check-box
    :property-spec   (label button-state)
    :property-getter check-box-property-getter)

(def-workspace-representation-type slider
    :property-spec   (label readout-value min max)
    :property-getter slider-property-getter)


(def-workspace-representation-type type-in-box
    :property-spec   (label last-value-displayed)
    :property-getter type-in-box-property-getter)


;; Tables/attribute-displays

(def-workspace-representation-type attribute-display
    :property-spec    ((row-label row-info)(row-label row-info))
    :property-getter   table-property-getter)
  
; kind-of-display-p
; kind-of-cell-based-display-p

(def-workspace-representation-type attribute-table
    :property-spec    ((row-label row-info)(row-label row-info))
    :property-getter   table-property-getter)

(def-workspace-representation-type short-representation
    :property-spec ((row-label row-info)(row-label row-info))
    :property-getter table-property-getter)

(def-workspace-representation-type classic-attribute-table
    :property-spec ((row-label row-info)(row-label row-info))
    :property-getter table-property-getter)

(def-workspace-representation-type attribute-table-with-header
    :property-spec ((row-label row-info)(row-label row-info))
    :property-getter table-property-getter)

;make-text-for-cell-identifying-attribute-in-table
;make-string-that-identifies-attribute



;;; New Method: `get-workspace-representation-type'
;;; Everything that can be represented on a workspace is 
;;; a member of '(text-box entity button table display)


;;;; Message Sending

 
(defmacro def-view-message ((name number direction-spec)
			    args)
   (let ((arg-names (loop
		     for arg in args
			collect (if (consp arg) (cadr arg) arg)))
	 (handler-function-name
	   (build-ab-symbol name 'view-message-handler))
	(sender (car direction-spec))
	(receiver (caddr direction-spec)))
     `(progn
	#-development
	(current-system-case
	  (,sender
	     nil)
	  (,receiver
	     (declare-forward-references (,handler-function-name function))))
	#+development
	(declare-forward-references (,handler-function-name function))
	(eval-when (:compile-toplevel :load-toplevel :execute)
	  (def-icp-message-type-code ,name ,number)
	  (setf (view-message-sender ',name) ',sender)
	  (setf (view-message-receiver ',name) ',receiver))
	(def-icp-message-type ,name ,args
	  #-development                         ; this bit of cleverness
	  (current-system-case                  ; accomodates the vastly
	    (,sender                            ; different expansions
	       (declare-ignorable-icp-arguments
		 ,@arg-names))                  ; that current-system-case
	    (,receiver                          ; has versus the
	       nil))                            ; :development *feature*
	  (current-system-case
	    (,sender
	       (error "~s is a message that this system sends, not receives"
		      ',sender))
	    (,receiver
	       (,handler-function-name ,@arg-names)))))))

(defmacro def-view-message-handler (name args &body body)
  (let ((handler-function-name
	  (build-ab-symbol name 'view-message-handler)))
    (unless (view-message-receiver name)
      (error "must define view message before handler"))
    `(defun ,handler-function-name ,args
       ,@body)))

(defmacro with-view-message-sending ((icp-port) &body body)
  (avoiding-variable-capture (&aux icp-output-port?)
    `(let ((,icp-output-port? ,icp-port))
       (when (and ,icp-output-port?
		  (icp-connection-open-p
		    (parent-icp-socket ,icp-output-port?)))
	 (writing-icp-message-group (,icp-output-port?)
	   ,@body)))))
    
(defmacro send-view-message (icp-port (message &rest args)
				      &optional completion-function+arguments)
  (let ((sender-function-name
	  (build-ab-symbol 'send-icp message)))
    (unless (view-message-sender message)
      (error "must define view message before callers of it"))
    (avoiding-variable-capture (&aux icp-output-port?)
      `(current-system-case
	 (,(view-message-sender message)
	   (let ((,icp-output-port? ,icp-port))
	     (when (and ,icp-output-port?
			(icp-connection-open-p
			  (parent-icp-socket ,icp-output-port?)))
	       (send-or-enqueue-icp-write-task
		 ,icp-output-port?
		 6 ;priority
		 #',sender-function-name
		 (icp-list ,@args)
		 ,@(if (null completion-function+arguments)
		       '(nil nil)
		       `(#',(car completion-function+arguments)
			 (icp-list ,@(cdr completion-function+arguments))))))))
	 (t
	   (error "This message is not defined to be sent by this system"))))))

(defmacro send-view-message-to-socket (icp-socket &rest args)
  `(send-view-message (icp-output-port ,icp-socket)
		      ,@args))

(defmacro send-view-message-for-window (gensym-window &rest args)
  `(send-view-message (icp-output-port-for-window? ,gensym-window)
		      ,@args))

(defmacro send-view-message-to-master-for-window (gensym-window &rest args)
  `(send-view-message (icp-output-port-to-master-for-window? ,gensym-window)
		      ,@args))


