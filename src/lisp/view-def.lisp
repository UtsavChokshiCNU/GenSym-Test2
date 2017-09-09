;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module VIEW-DEF

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Joseph Devlin


;;; The Workspace Protocol
;;;   Issues
;;;      Handles to wses and items
;;;   Requests
;;;      All of the testp args say whether request is currently allowed
;;;      REPRESENT-WS (batch-mode-p, ref-no, test-p)
;;;      MOVE-WS-ITEM (ws,item,delta-x-ws,delta-y-ws, test-p)
;;;      CHANGE-WS-ITEM-LAYER (item, ..., test-p)
;;;      TRANSFER-WS-ITEM ( )
;;;      CLONE-WS-ITEM ( )
;;;      DELETE-WS-ITEM ( )
;;;      CHANGE-WS-ITEM-CHANGE-COLOR-LAYER
;;;   Notifications
;;;      START-WS-INITIAL-DATA: number-of-items 
;;;      WS-INITIAL-DATA-SEGMENT: (delivered in layer order)
;;;        n of { ws-item-rep-type - entity|tc|chart|graph|text-box 
;;;               class
;;;               handle
;;;               x,y
;;;               group-definition
;;;               group-membership
;;;               prefix-encoded-rep-type-particulars
;;;               prefix-encoded-input-connection-info
;;;             }
;;;      ICON-CLASS-CHANGE
;;;      ICON-INSTANCE-CHANGE
;;;      CONNECTION-CLASS-CHANGE
;;;      ITEM-MOVED
;;;      ITEM-TRANFSFERRED-OFF
;;;      ITEM-TRANSFERRED-ON
;;;      ITEM-CREATED
;;;      ITEM-DELETED
;;;      WS-EXTENT-CHANGE
;;;      CONNECTION-KINK-INTRODUCE object, connection, kink info
;;;      CONNECTION-OBJECT-CHANGE object, connection last-two-vertex info
;;;      TREND-CHART-LAYOUT-CHANGE
;;;      TREND-CHART-DATA-BURST
;;;      CHART-LAYOUT-CHANGE
;;;      CHART-DATA-BURST
;;;      TEXT-BOX-HIGHLIGHT
;;;      READOUT-TABLE-FORMAT-CHANGE
;;;      READOUT-TABLE-UPDATE

(declare-forward-reference send-rpc-start function)
(declare-forward-reference gather-affected-representations function)
(declare-forward-reference match-subscriptions function)
(declare-forward-reference make-attribute-denotation function)
(declare-forward-reference make-variable-value-denotation function)
(declare-forward-reference make-virtual-attribute-denotation function)
(declare-forward-reference denotation->denotation-sequence function)
(declare-forward-reference make-item-access-cache function)
(declare-forward-reference delete-item-access-cache function)
(declare-forward-reference remove-subscription function)
(declare-forward-reference get-denoted-evaluation-value function)
(declare-forward-reference ensure-registration-on-network function)
(declare-forward-reference start-procedure-invocation-in-place function)
(declare-forward-reference runnable-p-function function)
(declare-forward-reference reclaim-rpc-argument-list function)
(declare-forward-reference remote-procedure-item-info-kind-function function)
(declare-forward-reference register-all-items-in-value function) ;g2-rpc3.lisp
(declare-forward-reference get-or-make-connection-frame-and-activate-if-appropriate function) ;connect2
(declare-forward-reference make-remote-procedure-name-function function) ;rpc-common1

;; Chaining

(declare-forward-reference chain-forward-for-attribute-if-necessary function)

;; rpc-common1

(declare-forward-reference make-remote-procedure-item-info function)
(declare-forward-reference loose-end-connection-frame-p function);events-g2
(declare-forward-reference item-or-connection-being-deleted-p function);events-g2

(declare-forward-reference output-connection-p-function function)

(declare-forward-reference workspace-showing-on-ui-client-p function)

;; conclude
(declare-forward-reference reclaim-denotation-function function)
(declare-forward-reference make-item-color-pattern-change-denotation function)
(declare-forward-reference make-custom-event-denotation function)
(declare-forward-reference make-add-item-to-workspace-denotation function)
(declare-forward-reference make-remove-item-from-workspace-denotation function)
(declare-forward-reference make-item-event-denotation function)

;; view-g2
(declare-forward-reference export-color-pattern function)

;; proc-utils
(declare-forward-reference start-local-representation-callback function)

;; connect1
(declare-forward-reference connection-structures function)
(declare-forward-reference connection-p-function function)


;;;; Variable-value Components




(defmacro make-variable-value-component-particulars
    (further-particulars)
  `(slot-value-list 'variable-value ,further-particulars))

(defmacro variable-value-further-component (component-particulars)
  `(cadr ,component-particulars))

(defmacro component-typecase (component-particulars-exp &body body)
  `(let ((type-in-component ,component-particulars-exp))
     (cond
       ,@(loop for (type-or-types . consequents) in body
	       collect
	       (cond ((consp type-or-types)
		      `((or ,@(loop for type in type-or-types
				   collect
				    `(eq type-in-component ',type)))
			,@consequents))
		     (t
		      `((eq type-in-component ',type-or-types)
			,@consequents)))))))






;;;; Access Errors 

;;; This is exists to support internationalization of error reporting
;;; of the G2 API.

(def-structure (access-error
		 (:constructor make-access-error
			       (access-error-name
				 access-error-particulars)))
  (access-error-name nil)
  (access-error-particulars nil))

(defmacro access-error (name &body body)
  `(make-access-error
     ,name
     (gensym-list ,@body)))

(defun-simple make-default-text-string-for-access-error (access-error)
  (twith-output-to-text-string
    (let ((particulars? (access-error-particulars access-error)))
      (tformat "ACCESS-ERROR: ~(~a~)"
	       (access-error-name access-error))
      (when particulars?
	(tformat " where:~%" ))
      (loop for (name value) on particulars? by 'cddr
	    do
	(tformat "  ~a = ~NV~%" name value)))))


;;; Some standard errors





(defun-simple make-missing-implied-attribute-error-message (item new-value)
  (access-error
    'missing-implied-attribute
    'item (tformat-text-string "~NF" item)
    'symbolic-value new-value))

(defun-simple make-conclude-no-value-into-non-variable-error-message (place)
  (access-error
    'conclude-no-value-in-non-variable
    'item (tformat-text-string "~NF" place)))

(defun-simple make-no-such-class-error-message (class-name)
  (access-error
    'no-such-class-error
    'class-name class-name))

(defun-simple make-conclude-into-non-v-or-p-error-message (item)
  (access-error
    'conclude-into-non-variable-or-parameter
    'item (tformat-text-string "~NF" item)
    'item-class (class item)))

(defun-simple make-inactive-item-in-attribute-error-message
    (slot-description class-description item slot-value)
  (access-error
    'inactive-item-in-attribute
    'attribute (tformat-text-string "~NS" slot-description
				    class-description)
    'item (tformat-text-string "~NF" item)
    'item-in-attribute (tformat-text-string "~NF" slot-value)))

(defun really-general-twrite (x)
  (if (slot-constantp x)
      (get-slot-value-number-or-string-from-slot-constant x)
;      (twith-output-to-text-string
;	(write-slot-value 'attribute x nil))
      (tformat-text-string "~NA" x)))

(defun-simple make-attribute-access-on-non-frame-error
    (would-be-item slot-name class-qualifier?)
  (access-error
    'attribute-access-on-non-frame
    'attribute-name slot-name
    'class (or class-qualifier? '<none>)
    'attribute-or-structure
    (really-general-twrite would-be-item)))

(defun-simple make-no-such-virtual-attribute-error-message (item name)
  (access-error
    'no-such-virtual-attribute
    'virtual-attribute-name name
    'item (tformat-text-string "~NF" item)
    'item-class (class item)))





;;;; Subscriptions


(def-kb-specific-property-name class-subscriptions)

(def-structure class-subscriptions
  ;; hash table of point (not wildcarded) subscriptions
  ;; problem
  (class-subscriptions-specific-denotation-table nil)
  ;; just a list of (denotation last-item-index and rep-item)
  (class-subscriptions-wildcard-denotation-list nil))

(def-structure (class-subscription
		 (:constructor
		   make-class-subscription
		   (class-subscription-denotation
		     class-subscription-inner-item-index
		     class-subscription-representation)))
  (class-subscription-denotation nil)
  (class-subscription-inner-item-index nil)
  (class-subscription-representation nil))

(def-global-property-name representation-callback-remote-procedure-name)

(defun-simple demand-representation-callback-remote-procedure-name
    (remote-procedure-name-thing)
  (if (symbolp remote-procedure-name-thing)
      (or (representation-callback-remote-procedure-name remote-procedure-name-thing)
	  (setf (representation-callback-remote-procedure-name
		  remote-procedure-name-thing)
 		(make-remote-procedure-name-function remote-procedure-name-thing)))
      remote-procedure-name-thing))


;;;; Handle Management

;;; This section will probably go away at some point.

(defmacro connectionp (structure)
  (if (eval-feature :chestnut-trans)
      `(connection-p ,structure)
      `(connection-p-function ,structure)))

(defmacro representation-type-of-thing (thing)
  `(cond ((framep ,thing)
	  (funcall-method 'get-workspace-representation-type ,thing))
	 ((connectionp ,thing)
	  'connection)))

(defmacro class-of-thing (block-or-connection)
  `(cond ((framep ,block-or-connection)
	  (class ,block-or-connection))
	 ((connectionp ,block-or-connection)
	  (let ((connection-frame-or-class 
		  (connection-frame-or-class ,block-or-connection)))
	    (cond ((symbolp connection-frame-or-class)
		   connection-frame-or-class)
		  ((framep connection-frame-or-class)
		   (class connection-frame-or-class))
		  (t nil))))
	 (t 
	  (type-of-named-structure ,block-or-connection))))

(defmacro get-workspace-if-any-for-block-or-connection (block-or-connection)
  `(cond ((framep ,block-or-connection)
	  (cond ((frame-of-class-p ,block-or-connection 'connection)
		 (let ((connection? (connection-for-this-connection-frame ,block-or-connection)))
		   (workspace-of-connection? connection?)))
		(t	
		 (get-workspace-if-any ,block-or-connection))))
	 ((connectionp ,block-or-connection)
	  (workspace-of-connection? ,block-or-connection))))

(defun-substitution-macro collect-frames-of-class (frame-list class-name)
  (loop with new-list = '()
	for frame in frame-list
	do
    (when (frame-of-class-p frame class-name)
      (gensym-push frame new-list))
        finally
          (return new-list)))

;;;; Macros to support different protocol versions

(def-named-dynamic-extent javalink-notification-versions
  (module view-def))

(defvar-of-named-dynamic-extent notification-data-version-map
    javalink-notification-versions)

(defvar-of-named-dynamic-extent current-lookup-data
    javalink-notification-versions)

;;; tacks the subscription handle on the end of the arg list. This
;;; is currently only correct for some javalink/telewindows2 protocols (specifically,
;;; at the time of writing, only 'ws-representation callbacks have
;;; been using this function). It is known not to be correct of
;;; 'tc-representation callbacks. rpenny 2/19/1999

(defun-simple javalink-versioning-make-arg-list-copy (arg-list subscription-handle)
  (loop with return-list = nil
	for arg in arg-list
	do
	(eval-push (copy-if-evaluation-value arg) return-list)
    finally
	  (eval-push subscription-handle return-list)
	(return (nreverse return-list))))

(defun-simple reclaim-javalink-versioned-call-data-arg-lists (arg-lists)
  (loop for arg-list in arg-lists
	do
    (loop for arg in arg-list
	  do
      (reclaim-if-evaluation-value arg))
    (reclaim-eval-list arg-list)
    finally
	  (reclaim-eval-list arg-lists)))
	

(def-structure (javalink-versioned-call-data)
  javalink-versioned-call-data-version
  (javalink-versioned-call-data-arg-lists nil :reclaimer reclaim-javalink-versioned-call-data-arg-lists))

(defun-simple javalink-versioned-call-data-sendp (call-data)
  (javalink-versioned-call-data-arg-lists call-data))

(defun-simple make-javalink-versioned-data (version)
  (let ((data (make-javalink-versioned-call-data)))
    (setf (javalink-versioned-call-data-version data) version)
    data))

(defun-simple javalink-versioned-call-data-evaluated-p (call-data-or-primitive)
  (javalink-versioned-call-data-p call-data-or-primitive))

(defun-simple javalink-versioned-call-data-get-version (data-symbol-or-fixnum)
  (cond ((javalink-versioned-call-data-p data-symbol-or-fixnum)
	 (javalink-versioned-call-data-version data-symbol-or-fixnum))
	((or (eq t data-symbol-or-fixnum)
	     (fixnump data-symbol-or-fixnum))
	 data-symbol-or-fixnum)
	(t (cerror "shouldn't be here" "Bad version data in notification-data-version-map ~s~%" data-symbol-or-fixnum))))

(defun-for-macro javalink-versioning-make-version-case-clause (version-var body-for-version)
  (let ((version (eval (car body-for-version))))
    (cond ((or (eq version t)
	       (eq version 'default))
	   `(t ,@(cdr body-for-version)))
	  ((fixnump version)
	   `((and (fixnump ,version-var)
		  (<=f ,version-var ,version))
	     ,@(cdr body-for-version)))
	  (t (error "bad version ~s~%" version)))))

(defun-for-macro javalink-versioning-expand-version-case-clauses
    (version-var body)
  `(with-named-dynamic-extent javalink-notification-versions
       ((current-lookup-data (make-javalink-versioned-data ,version-var)))
     ,(if (eq (car body) 'javalink-version-case)
	  (loop for body-for-version in (cdr body)
	    collect (javalink-versioning-make-version-case-clause version-var body-for-version) into cond-clauses
	    finally
	      (return `(cond ,@cond-clauses)))
	  body)
     current-lookup-data))

(defmacro send-matching-data-to-javalink-representation (representation body)
  (let ((version-for-current (gensym "VERSION-FOR-CURRENT"))
	(evaluatedp (gensym "EVALUATEDP"))
	(address (gensym "ADDRESS"))
	(socket (gensym "SOCKET"))
	(representation-version (gensym "REPRESENTATION-VERSION"))
	(current-list (gensym "CURRENT-LIST"))
	(subscription-handle (gensym "SUBSCRIPTION-HANDLE"))
	(version-or-data (gensym "VERSION-OR-DATA")))
    `(loop with ,version-for-current = nil
	   with ,evaluatedp = nil
	   with ,address = (representation-address ,representation)
	   with ,socket = (getf ,address 'socket)
	   with ,representation-version = (remote-icp-protocol-version ,socket)
	   with ,subscription-handle = (callback-representation-callback-subscription-handle
					 ,representation)
	   for ,current-list = notification-data-version-map then (cdr ,current-list)
	   ;; could be a fixnum, symbol, or structure
	   for ,version-or-data = (car ,current-list)
	   do
       (when (null ,version-or-data)
	 (return nil))
       (setf ,version-for-current (javalink-versioned-call-data-get-version ,version-or-data)
	     ,evaluatedp (javalink-versioned-call-data-evaluated-p ,version-or-data))
       ;; notification-data-version-map is in descending
       ;; order of versions, with T applying to all older versions
       (when (or (eq ,version-for-current t)
		 (>=f ,representation-version ,version-for-current))
	 (unless ,evaluatedp
	   (setf ,version-or-data ,(javalink-versioning-expand-version-case-clauses
				     version-or-data body)
		 (car ,current-list) ,version-or-data))
	 (when (javalink-versioned-call-data-sendp ,version-or-data)
	   (let ((arg-lists (javalink-versioned-call-data-arg-lists ,version-or-data)))
	     (loop for arg-list in arg-lists
		   for arg-list-to-send = (javalink-versioning-make-arg-list-copy arg-list ,subscription-handle)
		   do
	       (callback-representation-fire-callback
		 ,representation ,socket arg-list-to-send))))
	 (return t)))))

;;; Simply builds a list containing the version numbers embedded inside
;;; an javalink-version-case statement. This list will be modified as necessary
;;; by send-matching-data-to-javalink-representation

(defun-for-macro javalink-versioning-build-version-map (body)
  (cond ((and (consp (car body))
	      (eq (caar body) 'javalink-version-case))
	 `(gensym-list ,@(loop for version-form in (cdar body)
			     for version = (car version-form)
			     collect version)))
	(t `(gensym-list t))))

;;; This is a special symbol that behaves *somewhat* like CASE when it
;;; occurs as the car of the body in DO-JAVALINK-NOTIFICATION. It *must*
;;; be followed by a list of lists, the car of each list being an expression
;;; that *must* evaluate at compile-time to either a fixnum, the symbol T,
;;; or the symbol DEFAULT (enforced by JAVALINK-VERSIONING-MAKE-VERSION-CASE-CLAUSE).
;;; The cdr of each list is a body of code to be executed when there is a
;;; CALLBACK-REPRESENTATION whose version is higher than the car of the list.
;;;
;;; The lists *must* be in descending order, with T as the last (this
;;; ensures correct enforcement of which code-bodies cause messages to
;;; be sent to which versions of javalink. See
;;; SEND-WS-REPRESENTATIONS-ITEM-LAYER-CHANGE for an example.

(def-concept javalink-version-case)

;;; A macro designed for sending notifications to javalink. There are some
;;; very special things about the body of this macro:
;;; 1. For anything to be actually sent to a representation of the
;;;    class specified by REPRESENTATION-CLASS, something in the
;;;    body must set the JAVALINK-VERSIONED-CALL-DATA-ARG-LISTS of the
;;;    variable CURRENT-LOOKUP-DATA (bound for you by the DO-JAVALINK-NOTIFICATION
;;;    in the named-dynamic-extent of JAVALINK-NOTIFICATION-VERSIONS).
;;;    The only current example of this is SEND-VERSIONED-WS-NOTIFICATION-INTERNAL.
;;;    - The arg-lists are modified by JAVALINK-VERSIONING-MAKE-ARG-LIST-COPY,
;;;      then passed as the last argument to CALLBACK-REPRESENTATION-FIRE-CALLBACK.
;;; 2. If you wish to make distinctions between what needs to be sent
;;;    to different versions of javalink, the car of the body can be
;;;    JAVALINK-VERSION-CASE (see above).
;;; 3. currently (2/19/1999) this macro is only known to work for the
;;;    "workspace protocol" (ws-representation). See
;;;    JAVALINK-VERSIONING-MAKE-ARG-LIST-COPY.

(defmacro do-javalink-notification
    ((represented-item? representation-class) &body body)
  (let ((any-body-evaluated-p (gensym "ANY-BODY-EVALUATED-P"))
	(representations (gensym "REPRESENTATIONS"))
	(representation (gensym "REPRESENTATION"))
	(current-frame-serial-number-on-entry (gensym "CURRENT-FRAME-SERIAL-NUMBER-ON-ENTRY")))
    `(with-named-dynamic-extent javalink-notification-versions
	 ((notification-data-version-map nil))
       (when (and ,represented-item? (v5-tw-item-like-p ,represented-item?))
	 (loop with ,any-body-evaluated-p = nil
	       with ,representations = (collect-frames-of-class
					 (frame-representations ,represented-item?)
					 ,representation-class)
	       with ,current-frame-serial-number-on-entry = (copy-frame-serial-number (current-frame-serial-number))
	       for ,representation in ,representations
	       do
	   (when (and (not (frame-has-been-reprocessed-p ,representation
							 ,current-frame-serial-number-on-entry))
		      (representation-address-valid-p ,representation))
	     (when (null notification-data-version-map) ; only build when necessary
	       (setf notification-data-version-map ,(javalink-versioning-build-version-map body)))
	     (send-matching-data-to-javalink-representation ,representation ,@body))
	       finally
		 (reclaim-gensym-list ,representations)
	         (reclaim-frame-serial-number ,current-frame-serial-number-on-entry)
		 (javalink-versioning-reclaim-evaluated-version-bodies notification-data-version-map)
		 (return ,any-body-evaluated-p))))))

(defun-simple javalink-versioning-reclaim-evaluated-version-bodies
    (notification-data-version-map)
  (loop for data in notification-data-version-map
	do
    (when (javalink-versioned-call-data-p data)
      (reclaim-javalink-versioned-call-data data))
    finally
	  (reclaim-gensym-list notification-data-version-map)))

(defun-void send-versioned-ws-notification-internal (notification-type item data)
  (when (v5-tw-item-like-p item)
    ;; maybe I should force the callers to do this, but this is safer
    (when (connectionp item)
      (setf item (get-or-make-connection-frame-and-activate-if-appropriate item)))
    (let* ((arg-lists (javalink-versioned-call-data-arg-lists current-lookup-data))
	   (new-arg-lists-end (eval-list (eval-list (make-evaluation-symbol notification-type)
						    item
						    data))))
      (setf arg-lists (if arg-lists
			  (nconc arg-lists new-arg-lists-end)
			  new-arg-lists-end))
      (setf (javalink-versioned-call-data-arg-lists current-lookup-data) arg-lists))))

;;; Conditionally evaluates(reclaiming if so) update-info.
;;; Returns t if update-info has been reclaimed.
(defmacro send-ws-representations-item-change-macro
    (item update-info)
  `(do-javalink-notification ((get-workspace-if-any-for-block-or-connection ,item)
			      'ws-representation)
     (send-versioned-ws-notification-internal
       'item-change
       ,item
       ,update-info)))

;;;; Representation classes





(def-class (representation system-item define-predicate)
  (representation-address nil vector-slot)
  (represented-frame nil vector-slot))

(def-slot-value-reclaimer representation-address (address)
  (loop for (name value) on address by 'cddr
	do
    (unless (eq name 'socket)
      (reclaim-slot-value value))
	finally
	  (reclaim-slot-value-list address)))


(def-slot-value-reclaimer represented-frame (frame representation)
  frame
  representation
  nil)

(def-class (object-definition-representation
	     representation define-predicate)
  (object-definition-representation-reference-count nil vector-slot))

(defparameter local-pseudo-socket '(local-pseudo-socket))

(defun make-representation (icp-socket represented-frame
				       representation-class)
  (let ((representation (make-frame representation-class)))
    (slot-value-push representation
		     (frame-representations represented-frame))
    (setf (represented-frame representation) represented-frame)
    (unless (eq icp-socket local-pseudo-socket)
      (gensym-push representation
		   (icp-socket-representations icp-socket)))
    representation))

(def-substitution-macro representation-handle-hash (x)
  x)

(def-hash-table representation-handle
  :constructor make-representation-handle-table
  :hash-function-or-macro representation-handle-hash
  :entry-reclaimer identity
  :accessor     get-representation-handle-internal 
  :key-deleter  delete-representation-handle
  :size 109)

(def-system-variable the-representation-handle-hashtable VIEW-DEF
  (:funcall make-representation-handle-table))
  
(defun representation-handle-gethash (handle)
  (get-representation-handle-internal handle the-representation-handle-hashtable))

(defun representation-handle-puthash (handle representation)
  (setf (get-representation-handle-internal handle the-representation-handle-hashtable)
	representation))

(defun representation-handle-remhash (handle)
  (when (get-representation-handle-internal handle the-representation-handle-hashtable)
    (delete-representation-handle handle the-representation-handle-hashtable)))


(defvar current-callback-representation-subscription-handle 0)

(defun new-callback-representation-subscription-handle ()
  (prog1
      current-callback-representation-subscription-handle
    (incff current-callback-representation-subscription-handle)))

;;;; Item/Attribute Representation Code


(def-class (callback-representation
	     representation define-predicate)
  (callback-representation-callback-procedure nil vector-slot)
  (callback-representation-callback-serial-number nil vector-slot)
  (callback-representation-callback-subscription-handle nil vector-slot))

(def-slot-value-reclaimer callback-representation-callback-serial-number (serial-number callback-representation)
    (reclaim-frame-serial-number serial-number)
    (setf (callback-representation-callback-serial-number callback-representation) nil))
  
(defun-simple assign-callback-representation-subscription-handle (callback-representation)
  (setf (callback-representation-callback-subscription-handle callback-representation)
	(new-callback-representation-subscription-handle)))

(defun-simple store-callback-representation (callback-representation)
  (let ((handle (or (callback-representation-callback-subscription-handle
		      callback-representation)
		    (assign-callback-representation-subscription-handle
		      callback-representation))))
    (representation-handle-puthash handle callback-representation)
    handle))

(defun-void callback-representation-fire-callback (representation socket argument-list)
  ;; this function may be missing some copying or reclaiming
  (cond
    ((eq socket local-pseudo-socket)
     (start-local-representation-callback
       representation
       argument-list))
    (t
     (start-remote-representation-callback
       socket
       (callback-representation-callback-procedure representation)
       argument-list))))

(def-class (item-representation
	     callback-representation define-predicate)
  (item-representation-denotation nil vector-slot)
  ;;
  ;; It's really ugly that we are jamming "user-model" data (i.e. possibly
  ;; evaluation-values) into a system-defined attribute. -dkuznick, 5/13/04
  ;;
  (item-representation-user-data-value t vector-slot)
  (item-representation-subscriptions nil vector-slot))

(def-slot-value-reclaimer item-representation-denotation (denotation frame)
  (when denotation
    (reclaim-denotation-function denotation)
    (setf (item-representation-denotation frame) nil)))

(def-slot-value-reclaimer item-representation-user-data-value (user-data frame)
  (reclaim-if-evaluation-value user-data)
  (setf (item-representation-user-data-value frame) nil))

(defun delete-representation (representation &optional (remove-from-socket-p t))
  (let ((represented-frame (represented-frame representation))
	(icp-socket (getf (representation-address representation)
			  'socket)))
    (setf (frame-representations represented-frame)
	  (delete-slot-value-element representation
				     (frame-representations represented-frame)))
    (when (and remove-from-socket-p
	       (not (eq icp-socket local-pseudo-socket)))
      (setf (icp-socket-representations icp-socket)
	    (delete-gensym-element representation
				   (icp-socket-representations icp-socket))))
    ;; the following to "when" clauses are hacks that await a better
    ;; abstraction of how to clean up a representation (i.e. unsubsribe)
    ;; and how to have that happen for all representations owned by
    ;; a connection automatically go away as part of icp-socket shutdown.
    ;; Right now we are doing all cleanup inside delete representation,
    ;; we should probably have a method on representations that allows them
    ;; before any of the above unwinding takes place.  jed 9/21/97
    (when (and (frame-of-class-p representation 'item-representation)
	       (item-representation-subscriptions representation))
      (remove-subscription 
	(item-representation-subscriptions representation)
	representation))
    (when (frame-of-class-p representation 'ws-representation)
      (cleanup-ws-representation representation))
    (progn
      (representation-handle-remhash
	(callback-representation-callback-subscription-handle representation))
      (delete-frame representation))))

(defun delete-all-representations-for-icp-socket (icp-socket)
  (loop with representations
	  = (copy-list-using-gensym-conses
	      (icp-socket-representations icp-socket))
	for representation in representations
	do (delete-representation representation nil)
	finally
	  ;; Now delete top-level conses of representations, a copy of the
	  ;; top-level conses of the slot, and then delete the list in the slot
	  ;; itself.  Working on the copy makes this safe from any side effects
	  ;; of delete-representation, i.e., removal from the list in the slot
	  ;; while we're traversing it.
	  (reclaim-gensym-list representations)
	  (reclaim-gensym-list (icp-socket-representations icp-socket))
	  (setf (icp-socket-representations icp-socket) nil)))

(defun-simple get-interface-from-representation (representation)
  (let ((socket? (getf (representation-address representation) 'socket)))
    (and socket?
	 (enclosing-interface-frame? socket?))))

;;; `send-representation-deletion-notification' should be a method.

(defun-void send-representation-deletion-notification (representation)
  (frame-class-case representation
    (item-representation
      (send-item-representation-deletion-notification
	representation))))

(defun-void send-item-representation-deletion-notification
    (representation)
  (let* ((denotation
	   (item-representation-denotation representation))
	 (argument-list
	   (eval-list
	     (make-evaluation-symbol 'delete)
	     nil ; no frame
	     (denotation->denotation-sequence denotation)
	     nil ; no attribute-value
	     (copy-if-evaluation-value
	       (item-representation-user-data-value representation))
	     (callback-representation-callback-subscription-handle representation))) ; the "subscription handle"
	 (address (representation-address representation))
	 (socket (getfq address 'socket)))
    (callback-representation-fire-callback
      representation socket argument-list)))

;; This is somewhat copied from the deletion fuctions above.
(defun-void send-item-representation-item-color-pattern-change-notification
    (representation color-or-pattern specific-region?)
  (let* ((denotation (item-representation-denotation representation))
	 (argument-list
	   (eval-list
	     (make-evaluation-symbol 'item-color-pattern-change)
	     (represented-frame representation)
	     (denotation->denotation-sequence denotation)
	     (if (symbolp color-or-pattern)
		 (allocate-evaluation-structure-inline
		   specific-region?
		   color-or-pattern)
		 (export-color-pattern color-or-pattern))
	     (copy-if-evaluation-value
	       (item-representation-user-data-value
		 representation))
	     (callback-representation-callback-subscription-handle
	       representation)))
	 (socket (getfq (representation-address representation) 'socket)))
    (callback-representation-fire-callback
      representation socket argument-list)))

(defun-void send-item-representation-custom-event-notification
    (representation event-info)
  (callback-representation-fire-callback
    representation
    (getfq (representation-address representation) 'socket)
    (eval-list
      (make-evaluation-symbol 'custom-event)
      (represented-frame representation)
      (denotation->denotation-sequence (item-representation-denotation
					 representation))
      (copy-if-evaluation-value event-info)
      (copy-if-evaluation-value (item-representation-user-data-value
				  representation))
      (callback-representation-callback-subscription-handle representation))))

;;; GENSYMCID-1406: Item deleted event
(defun-void send-item-representation-item-event-notification
    (representation)
  (callback-representation-fire-callback
    representation
    (getfq (representation-address representation) 'socket)
    (eval-list
      (make-evaluation-symbol 'delete)
      nil
      (denotation->denotation-sequence (item-representation-denotation
					 representation))
      nil
      (copy-if-evaluation-value (item-representation-user-data-value
				  representation))
      (callback-representation-callback-subscription-handle representation))))

(defun-void send-item-representation-add-item-to-workspace-notification
    (representation item)
  (send-item-representation-add-or-remove-item-from-workspace-notification
    representation item 'add-item-to-workspace))

(defun-void send-item-representation-remove-item-from-workspace-notification
    (representation item)
  (send-item-representation-add-or-remove-item-from-workspace-notification
    representation item 'remove-item-from-workspace))

(defun-void send-item-representation-add-or-remove-item-from-workspace-notification
    (representation item event-name)
  (callback-representation-fire-callback
    representation
    (getfq (representation-address representation) 'socket)
    (eval-list
      ;; Was thinking of making the name of the event ADD-ITEM or REMOVE-ITEM
      ;; (while keeping the denotation as-is, so that we could have different
      ;; types of add-item events later, but PP thought it would be better to
      ;; do it this way -dkuznick, 3/17/04
      (make-evaluation-symbol event-name)
      (represented-frame representation)
      (denotation->denotation-sequence (item-representation-denotation
					 representation))
      item
      (copy-if-evaluation-value (item-representation-user-data-value
				  representation))
      (callback-representation-callback-subscription-handle representation))))

(defun-void update-represented-item-denotation-value
    (representation frame denotation)
  (let* ((attribute-evaluation-value
	   (get-denoted-evaluation-value frame denotation))
	 (argument-list
	   (eval-list
	     (make-evaluation-symbol 'modify)
	     frame
	     (denotation->denotation-sequence denotation)
	     attribute-evaluation-value
	     (copy-if-evaluation-value
	       (item-representation-user-data-value representation))
	     (callback-representation-callback-subscription-handle representation))) ; the "subscription handle"
	 (address (representation-address representation))
	 (socket (getfq address 'socket)))
    (callback-representation-fire-callback
      representation socket argument-list)))

;; Moved start-local-representation-callback to proc-utils.lisp -dkuznick,
;; 6/29/04  


(defun-simple transform-system-rpc-arguments (icp-socket argument-list info-list
					      remote-representation-callback-p
					      varargs-p)
  (loop with current-computation-flags = current-computation-flags
	initially (setf (role-serve-inactive-objects?)
			(icp-socket-runs-while-inactive icp-socket))
	for info-list-tail = info-list
			   then (if (and (null (cdr info-list-tail))
					 varargs-p)
				    info-list-tail				    
				    (cdr info-list-tail))
	for kind = (if remote-representation-callback-p
		       'handle
		       (remote-procedure-item-info-kind-function
			 (car info-list-tail)))
	for argument-tail on argument-list
	as argument = (car argument-tail)
	do
    ;; kind is one of: by-copy-with-handle handle reference nil
    (setf (car argument-tail)
	  (if (framep argument)
	      (case kind
		(by-copy-with-handle
		 (icp-list
 		   'copy argument
 		   (make-remote-procedure-item-info nil nil nil nil nil kind)
 		   (ensure-registration-on-network
 		     argument
 		     (enclosing-interface-frame? icp-socket))))
		(handle
		 (ensure-registration-on-network
		   argument
		   (enclosing-interface-frame? icp-socket))
		 (icp-cons 'handle argument))
		;;(reference ...)
		(t
		 (icp-list
 		   'copy argument
 		   (make-remote-procedure-item-info nil nil nil nil nil kind))))
	      (case kind
		(handle 
		 (register-all-items-in-value
		   argument
		   (enclosing-interface-frame? icp-socket))
		 (icp-cons 'handle argument))
		(t
		 (icp-cons 'value argument)))))))

(defun-allowing-unwind start-remote-representation-callback
    (icp-socket callback-procedure argument-list)
  (cond
    ((symbolp callback-procedure)
     (funcall callback-procedure argument-list))
    ((or (not (icp-connection-open-p icp-socket))
	 (icp-connection-being-shutdown? icp-socket))
     ;; (format t "should warn about bad icp socket for system-rpc callback")
     (reclaim-rpc-argument-list argument-list nil))
    (t
     (transform-system-rpc-arguments icp-socket argument-list nil t nil)
     (send-rpc-start (icp-output-port icp-socket)
		     6 ; execution-priority
		     callback-procedure ; a remote-procedure
		     argument-list
		     nil))))

(defun-void update-subscriptions-from-virtual-attribute-change
  (frame virtual-attribute defining-class?)
  (let ((subscriptions (class-subscriptions-macro (class frame)))
	(attribute-name (virtual-attribute-name virtual-attribute)))
    ;; First, run the subscribed updates.
    (when subscriptions
      (update-subscriptions
       frame
       (make-virtual-attribute-denotation virtual-attribute nil)
       subscriptions))
    ;; Next, invoke rules for forward chaining, and trigger event detectors.
    (chain-forward-for-attribute-if-necessary
      frame attribute-name defining-class?)))

(defun-void update-subscriptions-from-variable-change (frame)
  (let ((subscriptions (class-subscriptions-macro (class frame))))
    (when subscriptions
      (update-subscriptions
	frame
	(make-variable-value-denotation nil)
	subscriptions))))

(defun-substitution-macro update-subscriptions-from-slot-change-with-description
  (frame slot-description)
  ;; Only do the updates when the slot is exported for reading (true of
  ;; all user-defined slots and of some system-defined slots).
  (cond
   ((user-defined-slot-description-p slot-description)
    (let ((subscriptions (class-subscriptions-macro (class frame))))
      (when subscriptions
	(update-subscriptions
	 frame
	 (make-attribute-denotation
	  (pretty-slot-name slot-description)
	  (class-qualifier-of-slot-description frame slot-description)
	  nil)
	 subscriptions))))
   ((evaluator-slot-info-category-getter
     (get-slot-description-evaluator-info slot-description))
    (let* ((subscriptions (class-subscriptions (class frame)))
	   (slot-name (pretty-slot-name slot-description))
	   (attribute-name
	    (or (get-alias-for-slot-name-if-any slot-name frame) slot-name))
	   (defining-class? nil))
    (when subscriptions
      (update-subscriptions
       frame
       (make-attribute-denotation attribute-name defining-class? nil)
       subscriptions))
    ;; Next, invoke forward chaining and trigger event-detectors when the
    ;; attribute is gettable.  For non-user-defined slots; see note.
    (chain-forward-for-attribute-if-necessary
     frame attribute-name defining-class?)))))

(defun-void update-subscriptions-from-slot-change
    (frame slot-description slot-name defining-class?)
  (declare (ignore slot-name defining-class?))
  (update-subscriptions-from-slot-change-with-description frame slot-description))

;; N.B.    invoke-rules-for-attribute-change-chaining is called
;; for user-defined attribtes in put-attribute-description-value.
;; We should get rid of that call and remove the unless here, but there
;; are currently too many callers of put-attribute-description-value
;; to do this for 5.0r1.  jed 10/28/97
;;
;; -- NOTE: put-attribute-description-value is not called when the value is set
;; EQ to the previous value.  Consider the efficiency issues carefully!
;; Also consider the difficulty users coping with the EQ case, which is not
;; really part of their model!  (MHD 5/4/00)
;;
;; Note: soon flush update-subscriptions-from-slot-change; it's obsolete.
;; (MHD 5/12/00)

(defun update-representation-dispatch
     (representation frame attribute-description)
  (frame-class-case representation
    (item-representation
      ;; this does not happen directly anymore
      ;; this case goes through update-subscriptions-from-slot-change
      representation frame attribute-description)))

(defun update-representation-with-denotation
    (representation frame denotation)
  (frame-class-case representation
    (item-representation
      (update-represented-item-denotation-value
	representation frame denotation))))

;;; `do-matching-item-representations' is used to find "matching"
;;; item-representations, and to evaluate the body once for each one found with
;;; the representation-var bound each iteration to one of the matching
;;; representations.  The macro returns no values.

(defmacro do-matching-item-representations
    ((representation-var frame denotation subscriptions) &body body)
  (avoiding-variable-capture
      (frame denotation subscriptions &aux matching-subscriptions cache representations reference)
    `(let ((,matching-subscriptions (match-subscriptions ,subscriptions
							 ,denotation
							 0)))
       (when ,matching-subscriptions
	 (let* ((,cache (make-item-access-cache))
		(,representations (gather-affected-representations
				    ,cache ,matching-subscriptions ,frame)))
	   (when ,representations
	     (loop with ,reference = (copy-frame-serial-number
				       (current-frame-serial-number))
		   ;; Here is where we are binding the variable for the caller
		   for ,representation-var in ,representations
		   unless (or (frame-has-been-reprocessed-p ,representation-var
							    ,reference)
			      (not (frame-of-class-p ,representation-var
						     'item-representation)))
		     do (progn ,@body)
		   finally (reclaim-frame-serial-number ,reference))
	     (reclaim-gensym-list ,representations))
	   (delete-item-access-cache ,cache)
	   (reclaim-gensym-list ,matching-subscriptions))))))

(defun-void update-subscriptions (frame denotation subscriptions)
  (do-matching-item-representations
      (representation frame denotation subscriptions)
    (update-represented-item-denotation-value
      representation
      (represented-frame representation)  ; could frame just be used?!
      denotation)))

(defun-void update-subscriptions-for-color-change
    (frame color-or-pattern region?)
  (let ((subscriptions? (class-subscriptions-macro (class frame))))
    (when subscriptions?
      ;; The below is not actually a leak.  The denotation gets cached
      ;; permanently and re-used.
      (let ((denotation (make-item-color-pattern-change-denotation)))
	(do-matching-item-representations
	    (representation frame denotation subscriptions?)
	  (send-item-representation-item-color-pattern-change-notification
	    representation color-or-pattern region?))))))

(defun-void update-subscriptions-for-custom-event (frame event-name event-info)
  (let ((subscriptions? (class-subscriptions-macro (class frame))))
    (when subscriptions?
      ;; Ditto re: not being a leak.
      (let ((denotation (make-custom-event-denotation event-name)))
	(do-matching-item-representations
	    (representation frame denotation subscriptions?)
	  (send-item-representation-custom-event-notification
	    representation event-info))))))

(defun-void update-subscriptions-for-item-event (frame event-name)
  (let ((subscriptions? (class-subscriptions-macro (class frame))))
    (when subscriptions?
      (let ((denotation (make-item-event-denotation event-name)))
	(do-matching-item-representations
	    (representation frame denotation subscriptions?)
	  (send-item-representation-item-event-notification
	    representation))))))

(defun-void update-subscriptions-for-add-item-to-workspace (ws item)
  (let ((subscriptions? (class-subscriptions-macro (class ws))))
    (when subscriptions?
      (let ((denotation (make-add-item-to-workspace-denotation)))
	(do-matching-item-representations
	    (representation ws denotation subscriptions?)
	  (send-item-representation-add-or-remove-item-from-workspace-notification
	    representation item 'add-item-to-workspace))))))


(defun-void update-subscriptions-for-remove-item-from-workspace (ws item)
  (let ((subscriptions? (class-subscriptions-macro (class ws))))
    (when subscriptions?
      (let ((denotation (make-remove-item-from-workspace-denotation)))
	(do-matching-item-representations
	    (representation ws denotation subscriptions?)
	  (send-item-representation-add-or-remove-item-from-workspace-notification
	    representation item 'remove-item-from-workspace))))))


;;;; Deferred Notification

(def-structure deferred-update
  (deferred-update-frame nil)
  (deferred-update-frame-serial-number nil)
  (deferred-update-attribute-description nil) ; how do we protect against user attribute-change
  (deferred-update-user-class-definition nil)  ; used only if user defined slot
  (deferred-update-user-class-definition-frame-serial-number nil)) ; ditto
;; unused? -dkuznick, 8/2/01

;;; fix this:  Should be subclassed from item-representation. However,
;;; the unsubscribe code makes assumptions that are only valid
;;; if the subscription occured through g2-subscribe-to-item,
;;; which in turn expects a non-null denotation.

(def-class (tc-representation
	     callback-representation define-predicate)
  )

;;;; WS Representation Code


(def-class (ws-representation
	     callback-representation define-predicate)
  )

(defun cleanup-ws-representation (ws-representation)
  (let ((workspace (represented-frame ws-representation)))
    (unless (workspace-showing-p workspace nil) ;; by definition it WAS showing
      (event-update-status-of-block-showing workspace nil nil))))

(defun-simple ws-has-ws-representation-p (frame)
  (and g2-has-v5-mode-windows-p
       (loop for representation in (frame-representations frame)
	     thereis (frame-of-class-p representation
				       'ws-representation))))
    

(defun make-structure-from-dimensions (left top right bottom)
  (allocate-evaluation-structure-inline
    'left left
    'top top
    'right right
    'bottom bottom))

(defmacro copy-subblocks-using-slot-value-conses (subblocks)
  #-subblocks-v2
  `(copy-list-using-slot-value-conses ,subblocks)
  #+subblocks-v2
  (let ((subblock (gensym)))
    (avoiding-variable-capture (subblocks)
      `(when ,subblocks
	 (loop for ,subblock being each constant-queue-element of ,subblocks
	       collect ,subblock using slot-value-cons)))))

;;; This is a more generic version of create-ws-representation-initial-state
;;; but I decided to leave the old one in the code to prevent
;;; destabilization at this late stage of the release cycle.

(defun create-ws-representation-updated-state (ws slots-to-update)
  (loop with subblocks = (copy-subblocks-using-slot-value-conses
			   (subblocks ws))
	with items = (reverse-item-like-children subblocks)
	with first-item = (car items)
	with workspace-dimensions
	  =  (make-structure-from-dimensions
	       (left-edge-of-block ws)
	       (top-edge-of-block ws)
	       (right-edge-of-block ws)
	       (bottom-edge-of-block ws))
	with workspace-background-color
	= (workspace-background-color? ws)
	with workspace-foreground-color
	= (workspace-foreground-color? ws)
	with first-item-info
	  = (if first-item
		(get-thing-updated-info-with-all-children
		  first-item nil
		  slots-to-update))
     	with item-info-list
	  =  first-item-info
	with items-to-export = nil
	with item-datas-to-export = nil
	for (item1 item2) on items
	do
    (when item2
      (setf item-info-list
	    (nconc
	      (get-thing-updated-info-with-all-children
		item2 nil
		slots-to-update)
	      item-info-list)))
	finally
	  (loop for (item-data item) on item-info-list by 'cddr
		do
	    (eval-push item-data item-datas-to-export)
	    (eval-push item items-to-export))
	  (reclaim-gensym-list item-info-list)
	  (reclaim-gensym-list items)
	  (reclaim-slot-value-list subblocks)
	  (return
	    (allocate-evaluation-structure-inline
	      'workspace-dimensions workspace-dimensions
	      'workspace-background-color workspace-background-color
	      'workspace-foreground-color workspace-foreground-color
	      'item-info-list (allocate-evaluation-sequence items-to-export)
	      'item-data-list (allocate-evaluation-sequence item-datas-to-export)))))

(defun create-ws-representation-initial-state (ws)
  (loop with subblocks = (copy-subblocks-using-slot-value-conses
			   (subblocks ws))
	with items = (nreverse (copy-list-using-gensym-conses subblocks))
	with first-item = (car items)
	with workspace-dimensions
	  =  (make-structure-from-dimensions
	       (left-edge-of-block ws)
	       (top-edge-of-block ws)
	       (right-edge-of-block ws)
	       (bottom-edge-of-block ws))
	with workspace-background-color
	= (workspace-background-color? ws)
	with workspace-foreground-color
	= (workspace-foreground-color? ws)
	with first-item-info
	  = (if first-item
		(get-thing-initial-info-with-all-children
		  first-item nil))
     	with item-info-list
	  =  first-item-info
	with items-to-export = nil
	with item-datas-to-export = nil
	for (item1 item2) on items
	do
    (when item2
      (setf item-info-list
	    (nconc
	      (get-thing-initial-info-with-all-children
		item2 nil)
	      item-info-list)))
	finally
	  (loop for (item-data item) on item-info-list by 'cddr
		do
	    (eval-push item-data item-datas-to-export)
	    (eval-push item items-to-export))
	  (reclaim-gensym-list item-info-list)
	  (reclaim-gensym-list items)
	  (reclaim-slot-value-list subblocks)
	  (return
	    (allocate-evaluation-structure-inline
	      'workspace-dimensions workspace-dimensions
	      'workspace-background-color workspace-background-color
	      'workspace-foreground-color workspace-foreground-color
	      'item-info-list (allocate-evaluation-sequence items-to-export)
	      'item-data-list (allocate-evaluation-sequence item-datas-to-export)))))

(defun get-first-item-like-child (block)
  (loop with children = (nreverse (children-of-thing block t))
	for child in children
	thereis (when (and (v5-tw-item-like-p child)
			   (not (item-or-connection-being-deleted-p child)))
		  child)
	finally
	  (reclaim-gensym-list children)))
	
(defun get-topmost-child-of-block (block)
  (when block
    (let ((topmost-child (get-first-item-like-child block)))
      (cond (topmost-child
	     (get-topmost-child-of-block topmost-child))
	    (t
	     block)))))

(defun v5-tw-item-like-p (block-or-connection)
  (cond ((framep block-or-connection)
	 (and (not (frame-of-class-p block-or-connection 'bounding-box))
	      (not (frame-of-class-p block-or-connection 'non-kb-workspace))
	      (frame-of-class-p block-or-connection 'item)))
	((connectionp block-or-connection))
	(t nil)))
	 	
	 

(defun reverse-item-like-children (children)
  (loop with result = 'nil
	for child in children
	do
    (when (v5-tw-item-like-p child)
      (gensym-push child result))
	finally
	  (return result)))

(defun item-like-children (children)
  (nreverse (reverse-item-like-children children)))

(defun input-end-connections-and-output-stubs (item exclude-output-stubs-p)
    (loop with result = nil
	  with connections
	    = (connection-structures item)
	  for connection in connections
	  as connection-frame
	     = (get-or-make-connection-frame-and-activate-if-appropriate
		 connection)
	  do
      (when (or (output-connection-p-function item connection)
		(and (null exclude-output-stubs-p)
		     (loose-end-connection-frame-p connection-frame)))
	(gensym-push
	  connection-frame
	  result))
	  finally
	    (reclaim-gensym-list connections)
	    (return (nreverse result))))

(defmacro copy-subblocks-using-gensym-conses (subblocks)
  #-subblocks-v2
  `(copy-list-using-gensym-conses ,subblocks)
  #+subblocks-v2
  (let ((subblock (gensym)))
    (avoiding-variable-capture (subblocks)
      `(when ,subblocks
	 (loop for ,subblock being each constant-queue-element of ,subblocks
	       collect ,subblock using gensym-cons)))))

(defun children-of-thing (thing &optional exclude-output-stubs)
  (cond ((framep thing)
	 (let* ((connections
		  (input-end-connections-and-output-stubs thing exclude-output-stubs))
		(subblocks
		  (copy-subblocks-using-gensym-conses
		    (subblocks thing)))
		(all-subblocks
		  (nconc subblocks connections)))
	   all-subblocks))
	((connectionp thing)
	 nil)
	(t nil)))

;;; This is a more generic version of get-thing-initial-info
;;; but I decided to leave the old one in the code to prevent
;;; destabilization at this late stage of the release cycle.

(defun get-thing-updated-info (thing slots-to-update)
  (when (connectionp thing)
    (setq thing (get-or-make-connection-frame-and-activate-if-appropriate
		  thing)))
 (unless (and (framep thing)
	      (frame-of-class-p thing 'kb-workspace))
   (let ((structure (allocate-evaluation-structure-inline)))
     (macrolet ((add-slot-if-needed (name)
		  `(let* ((attribute-description?
			    (get-attribute-description-of-frame
			      thing ,name nil))
			  (val
			    (and attribute-description?
				 (get-attribute-description-evaluation-value
				   thing
				   attribute-description?))))
		     (when attribute-description? 
		       (setf (evaluation-structure-slot
			       structure ,name)
			       val)))))
       (loop for slot in slots-to-update
	     do
	 (add-slot-if-needed slot)))
     structure)))

(defun get-thing-initial-info (thing)
  (when (connectionp thing)
    (setq thing (get-or-make-connection-frame-and-activate-if-appropriate
		  thing)))
 (unless (and (framep thing)
	      (frame-of-class-p thing 'kb-workspace))
   (let ((structure (allocate-evaluation-structure-inline)))
     (macrolet ((add-slot-if-needed (name)
		  `(let* ((attribute-description?
			    (get-attribute-description-of-frame
			      thing ,name nil))
			  (val
			    (and attribute-description?
				 (get-attribute-description-evaluation-value
				   thing
				   attribute-description?))))
		     (when attribute-description? 
		       (setf (evaluation-structure-slot
			       structure ,name)
			       val)))))
       (add-slot-if-needed 'representation-type)
       (add-slot-if-needed 'item-color-pattern)
       (add-slot-if-needed 'connection-style)
       (add-slot-if-needed 'connection-is-directed)
       (add-slot-if-needed 'connection-position-sequence)
       (add-slot-if-needed 'represented-item)
       (add-slot-if-needed 'format-type)
       (add-slot-if-needed 'table-rows)
       (add-slot-if-needed 'table-cells)
       (add-slot-if-needed 'default-cell-format)
       (add-slot-if-needed 'table-font-size)
       (add-slot-if-needed 'item-configuration)
       (add-slot-if-needed 'manually-disabled?)
       (add-slot-if-needed 'text-x-magnification)
       (add-slot-if-needed 'text-y-magnification)
       (unless (frame-of-class-p thing 'connection)
	 (add-slot-if-needed 'item-x-position)
	 (add-slot-if-needed 'item-y-position)
	 (add-slot-if-needed 'item-width)
	 (add-slot-if-needed 'item-height)
	 (add-slot-if-needed 'icon-heading)
	 (add-slot-if-needed 'icon-reflection))
       (add-slot-if-needed 'icon-variables))
     structure)))

;;; This is a more generic version of get-thing-updated-info-with-all-children
;;; but I decided to leave the old one in the code to prevent
;;; destabilization at this late stage of the release cycle.

(defun get-thing-updated-info-with-all-children
    (thing result slots-to-update)
  (let* ((children-of-thing?
	   (children-of-thing thing))
	 (item-like-children?
	   (item-like-children children-of-thing?))
	 (first-child? (car item-like-children?)))
    (gensym-push
      thing
      result)
    (gensym-push
      (get-thing-updated-info thing slots-to-update)
      result)
    (when (and first-child?
	       (v5-tw-item-like-p first-child?))
      (setf result
	    (get-thing-updated-info-with-all-children
	      first-child? result slots-to-update)))
    (loop for (child1 child2) on item-like-children?
	  do
      (when (and child2
		 (v5-tw-item-like-p child2))
	(setf result
	      (get-thing-updated-info-with-all-children
		child2 result slots-to-update))))
    (reclaim-gensym-list children-of-thing?)
    (reclaim-gensym-list item-like-children?)
    result))

(defun get-thing-initial-info-with-all-children
    (thing result)
  (let* ((children-of-thing?
	   (children-of-thing thing t))
	 (item-like-children?
	   (item-like-children children-of-thing?))
	 (first-child? (car item-like-children?)))
    (when (v5-tw-item-like-p thing)
      (gensym-push
	thing
	result)
      (gensym-push
	(get-thing-initial-info thing)
	result))
    (when (and first-child?
	       (v5-tw-item-like-p first-child?))
      (setf result
	    (get-thing-initial-info-with-all-children
	      first-child? result)))
    (loop for (child1 child2) on item-like-children?
	  do
      (when (and child2
		 (v5-tw-item-like-p child2))
	(setf result
	      (get-thing-initial-info-with-all-children
		child2 result))))
    (reclaim-gensym-list children-of-thing?)
    (reclaim-gensym-list item-like-children?)
    result))




