;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module GSI-RPC1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Peter Fandel, Nick Caruso, and John Hodgkinson.

;;; This module contains the machinery for remote-procedure execution that is
;;; specific to GSI and involves passing values as arguments and results.
;;; (Module GSI-RPC2 contains the GSI-specific machinery for passing items as
;;; arguments and results.)

;; jh, 3/16/94.  Created this module.

;;;; Forward references

;; To GSI-RPC2

(declare-forward-reference flush-outgoing-item-list function)
(declare-forward-reference establish-new-object-indices-as-required function)



;;;; GSI-specific Message Handlers

(defun-simple lookup-or-create-gsi-local-function (name create-p)
  (let ((application (current-gsi-application)))
    (or (loop for local-function in (gsi-local-functions application)
	      when (eq name (gsi-function-name-in-g2 local-function))
		return local-function)
	(when create-p
	  (let ((local-function (make-gsi-local-function)))
	    (setf (gsi-function-name-in-g2 local-function) name)
	    (setf (gsi-function-user-data local-function) nil)
	    (gsi-push local-function (gsi-local-functions application))
	    local-function)))))

(defun-void reclaim-list-of-local-functions (list)
  (loop while list
	for lf = (gsi-pop list)
	do (reclaim-gsi-local-function lf)))

(defun-simple gsi-lookup-new-remote-procedure-name (new-remote-procedure-name)
  (let ((local-function (lookup-or-create-gsi-local-function
			  (remote-procedure-name-symbol new-remote-procedure-name)
			  nil)))
    (when local-function
      (setf (gsi-local-function new-remote-procedure-name) local-function))
    local-function))

(defun-void gsi-call-missing-procedure-handler (new-remote-procedure-name)
  (let* ((name-string
	   (symbol-name-text-string
	     (remote-procedure-name-symbol new-remote-procedure-name)))
	 (name-for-callback
	   (if (using-wide-gsi-api-p)
	       name-string
	       (wide-string-to-gensym-string-for-gsi name-string))))
    (call-gsi-callback gsi-missing-procedure-handler name-for-callback)
    (unless (text-string-p name-for-callback) ; a copy
      (reclaim-gensym-string name-for-callback))))

(defun-simple gsi-handle-define-remote-procedure-name (new-remote-procedure-name)
  (or (gsi-lookup-new-remote-procedure-name new-remote-procedure-name)
      (progn
	(gsi-call-missing-procedure-handler new-remote-procedure-name)
	(gsi-lookup-new-remote-procedure-name new-remote-procedure-name))
      (progn
	(gsi-warning 'handle_icp_define_remote_proc gsi-local-function-undefined
		     (remote-procedure-name-symbol new-remote-procedure-name))
	nil)))





;;;;  API FUNCTIONS

;; error handling mechanism:
;;
;;    1. all API functions will return a result, or nothing; routines which used
;;    to return status, now return null.
;;
;;    2. all API functions set a global (hidden from the user, and eventually
;;    will be a per-connection item) analogous to unix' errno, which users read
;;    back with a function gsi_last_error().
;;
;;    3. In addition, all API functions will call a user error handling
;;    function, if the user has defined one.  If none is defined, or if the user
;;    function returns, control is returned to the caller of the erroring API
;;    function _UNLESS_ the error which occurred is fatal, in which case control
;;    passes back out of the gsi_run_loop call in the user's main program.
;;    CURRENTLY, only network errors and ICP protocol-out-of-sync errors are
;;    considered fatal. (9 Mar 1994 ncc)
;;      The body of the user error handler function executes outside any GSI
;;    context; the value of gsi_current_context() muat be (at least temporarily)
;;    set to -1.
;;
;;    4. Inside the user error handler, the user has two options for dealing
;;    with the error: a. call gsi_continue() {by analogy to the c "continue"
;;    stmt} or b. return.  Returning is dealt with above.  gsi_continue should
;;    throw to the run loop, remaining in or falling out as determined by the
;;    setting of one-cycle mode, unless the error was fatal.  For a fatal error,
;;    gsi_continue should throw out of the run loop.


;;; gsi-local-function contains a pointer to a C function and a string
;;; containing the name of the function as it is known in G2.  Each
;;; time gsi-rpc-declare-local is called from GSI user code, a
;;; gsi-local-function is added to gsi-local-functions, a global list 
;;; (one serves all contexts).

(def-gsi-api-function (gsi-rpc-declare-local-plain (:return-type :null)) 
                      ((function            :object) 
		       (function-name-in-g2 gsi-symbol))
  (let ((local-function (lookup-or-create-gsi-local-function
			  function-name-in-g2 t)))
    (setf (gsi-function-pointer local-function) function)))

(def-gsi-api-function (gsi-rpc-declare-local-w-u-d (:return-type :null))
                      ((function            :object)
		       (user-data           :object)
		       (function-name-in-g2 gsi-symbol))
  (let ((local-function (lookup-or-create-gsi-local-function
			  function-name-in-g2 t)))
    (setf (gsi-function-pointer local-function) function)
    (setf (gsi-function-user-data local-function) user-data)))

(defun-simple gsi-add-new-remote-procedure
    (remote-function-name receiver-function error-receiver-function user-data
     argument-count return-count gsi-extension-data?)
  (let ((gsi-remote-procedure
	  (or (loop for remote-procedure
			in (gsi-remote-procedures gsi-extension-data?)
		    when (eq (procedure-name-in-g2 remote-procedure)
			     remote-function-name)
		      return remote-procedure)
	      (let ((remote-procedure (make-gsi-remote-procedure)))
		(gsi-push remote-procedure
			  (gsi-remote-procedures gsi-extension-data?))
		remote-procedure))))
    (setf (procedure-name-in-g2 gsi-remote-procedure) remote-function-name)
    (setf (gsi-return-function gsi-remote-procedure) receiver-function)
    (setf (gsi-error-return-function gsi-remote-procedure) error-receiver-function)
    (setf (gsi-return-function-user-data gsi-remote-procedure) user-data)
    (setf (gsi-rpc-argument-count gsi-remote-procedure) argument-count)
    (setf (gsi-rpc-return-count gsi-remote-procedure) return-count)
    gsi-remote-procedure))

(def-gsi-api-function (gsi-rpc-declare-remote-plain (:return-type :null))
                      ((local-handle_result  (gsi-return-value :object))
		       (remote-function-name gsi-symbol)
		       (receiver-function    :object)
		       (argument-count       gsi-fixnum-long)
		       (return-count         gsi-fixnum-long)
		       (context              gsi-fixnum-long))
  (let ((gsi-remote-procedure
	  (gsi-add-new-remote-procedure
	    remote-function-name receiver-function nil nil
	    argument-count return-count
	    (or (gsi-extension-data? (resolve-gsi-context context))
		(gsi-api-error gsi-malformed-socket)))))
    (return-gsi-values gsi-remote-procedure)))

(def-gsi-api-function (gsi-rpc-declare-remote-w-u-d (:return-type :null))
                      ((local-handle_result  (gsi-return-value :object))
		       (remote-function-name gsi-symbol)
		       (receiver-function    :object)
		       (user-data            :object)
		       (argument-count       gsi-fixnum-long)
		       (return-count         gsi-fixnum-long)
		       (context              gsi-fixnum-long))
  (let ((gsi-remote-procedure
	  (gsi-add-new-remote-procedure
	    remote-function-name receiver-function nil user-data
	    argument-count return-count
	    (or (gsi-extension-data? (resolve-gsi-context context))
		(gsi-api-error gsi-malformed-socket)))))
    (return-gsi-values gsi-remote-procedure)))

(def-gsi-api-function (gsi-rpc-declare-remote-w-e-u-d (:return-type :null))
                      ((local-handle_result  (gsi-return-value :object))
		       (remote-function-name gsi-symbol)
		       (receiver-function    :object)
		       (error-receiver-function :object)
		       (user-data            :object)
		       (argument-count       gsi-fixnum-long)
		       (return-count         gsi-fixnum-long)
		       (context              gsi-fixnum-long))
  (let ((gsi-remote-procedure
	  (gsi-add-new-remote-procedure
	    remote-function-name receiver-function error-receiver-function user-data
	    argument-count return-count
	    (or (gsi-extension-data? (resolve-gsi-context context))
		(gsi-api-error gsi-malformed-socket)))))
    (return-gsi-values gsi-remote-procedure)))

;;; gsi-set-rpc-remote-return-value-kind
(def-gsi-api-function (gsi-set-rpc-remote-return-v-k (:return-type :null))
                      ((local-handle       :object)
		       (return-value-index gsi-fixnum-long)
		       (kind               gsi-symbol))
  (unless (gsi-remote-procedure-p local-handle)
    (gsi-api-error gsi-remote-declaration-not-found))
  ;; change "kind" values into those recognized by transform-rpc-argument-or-result-list.
  (case kind
    (by-copy-with-handle)
    (handle)
    (reference)
    (copy  (setq kind nil))
    (value (setq kind nil))
    (t
     (gsi-api-error gsi-invalid-return-value-kind)))
  (cond ((and (=f return-value-index -1)
	      (=f (gsi-rpc-return-count local-handle) -1))
	 (setf (gsi-rpc-return-kind-list local-handle) (gsi-list kind)))
	((or (<f return-value-index 0)
	     (>=f return-value-index (gsi-rpc-return-count local-handle)))
	 (gsi-api-error gsi-invalid-return-value-index))
	(t
	 (let ((kind-list
		 (or (gsi-rpc-return-kind-list local-handle)
		     (setf (gsi-rpc-return-kind-list local-handle)
			   (loop for i from 0 below (gsi-rpc-return-count local-handle)
				 collect nil using gsi-cons)))))
	   (setf (car (nthcdr return-value-index kind-list)) kind)))))

;;; gsi-set-rpc-remote-return-exclude-user-attrs
(def-gsi-api-function (gsi-set-rpc-remote-return-e-u-a (:return-type :null))
                      ((local-handle       :object)
		       (attrs gsi-managed-array-with-unspecified-length)) 
  (let ((exclude-user-attrs nil))
    (when attrs
      (loop for i from gsi-magic-offset below (gsi-managed-array-length attrs)
	    for item = (gsi-managed-svref attrs i)
	    for type = (gsi-instance-value-type item)
	    for value = (gsi-instance-value item)
	    do (cond ((=f type gsi-symbol-type-tag)
		      (gsi-push value exclude-user-attrs))
		     (t (gsi-api-error gsi-incompatible-type type)))))      
    (setf (gsi-rpc-return-excluded-attributes local-handle)
	  exclude-user-attrs)))

;;; gsi-set-rpc-remote-return-include-system-attrs
(def-gsi-api-function (gsi-set-rpc-remote-return-i-s-a (:return-type :null))
                      ((local-handle       :object)
		       (attrs gsi-managed-array-with-unspecified-length)) 
  (let ((include-system-attrs nil))
      (when attrs
	(loop for i from gsi-magic-offset below (gsi-managed-array-length attrs)
	      for item = (gsi-managed-svref attrs i)
	      for type = (gsi-instance-value-type item)
	      for value = (gsi-instance-value item)
	      do (cond ((=f type gsi-symbol-type-tag)
			(gsi-push value include-system-attrs))
		       (t (gsi-api-error gsi-incompatible-type type)))))      
      (setf (gsi-rpc-return-included-system-attributes local-handle)
	    include-system-attrs)))

;;; gsi-set-rpc-remote-return-include-all-system-attrs-except
(def-gsi-api-function (gsi-set-rpc-remote-r-i-a-s-a-e (:return-type :null))
                      ((local-handle       :object)
		       (attrs gsi-managed-array-with-unspecified-length))
  (let ((include-system-attrs-except nil)
	(include-system-attrs nil))
    (when attrs
      (loop for i from gsi-magic-offset below (gsi-managed-array-length attrs)
	    for item = (gsi-managed-svref attrs i)
	    for type = (gsi-instance-value-type item)
	    for value = (gsi-instance-value item)
	    do (cond ((=f type gsi-symbol-type-tag)
		      (gsi-push value include-system-attrs-except)
		      (gsi-push value include-system-attrs))
		     (t (gsi-api-error gsi-incompatible-type type)))))
    (setf (gsi-rpc-return-include-all-system-attributes-except local-handle)
	  include-system-attrs-except)
    (setf (gsi-rpc-return-include-all-system-attributes local-handle)
	  include-system-attrs)))

(defmacro gsi-get-rpc-argument-count (local-handle)
  `(progn
     (unless (gsi-remote-procedure-p ,local-handle)
       (gsi-api-error gsi-remote-declaration-not-found))
     (gsi-rpc-argument-count ,local-handle)))

(defun-void gsi-rpc-start-internal (local-handle argument-array context)
  (let ((remote-procedure-name
	  (or (gsi-remote-procedure-name-structure local-handle)
	      (gsi-define-new-remote-procedure local-handle)))
	(derived-socket (get-icp-socket-from-context context t)))
    (with-bifurcated-version (resumable-icp-version derived-socket)
      (progn
	(writing-icp-message-group ((icp-output-port derived-socket))
	  (let ((use-new-message-group-for-send-icp-enlarge-index-space-p nil))
	    (establish-new-object-indices-as-required argument-array)
	    (send-icp-rpc-start remote-procedure-name argument-array)))
	(flush-outgoing-item-list derived-socket))
      (send-or-enqueue-icp-write-task
	(icp-output-port derived-socket)
	resumable-priority-of-gsi-rpc-service
	#'send-icp-resumable-rpc-start
	(icp-list remote-procedure-name argument-array)
	nil   ; #'reclaim-rpc-argument-list {currently reclaimed by the api function}
	nil)) ;(icp-list argument-array)
    (gsi-flush-internal)))

(defun build-procedure-identifier-icp-list (list varargs-p)
  (let ((result (if list
		    (copy-tree-using-icp-conses list)
		    nil)))
    (if (or varargs-p (consp list))
      (icp-list result)
      result)))

(defun-simple gsi-rpc-call-internal (local-handle argument-array context user-data user-data-p)
  (let* ((remote-procedure-name
	   (or (gsi-remote-procedure-name-structure local-handle)
	       (gsi-define-new-remote-procedure local-handle)))
	 (kind-list (gsi-rpc-return-kind-list local-handle))
	 (varargs-p (=f (gsi-rpc-return-count local-handle) -1))	 
	 (incl
	   (when varargs-p (icp-list nil)))  
	 (excl
	   (build-procedure-identifier-icp-list
	     (gsi-rpc-return-excluded-attributes local-handle) 
	     varargs-p))
	 (incl-sys
	   (build-procedure-identifier-icp-list
	     (gsi-rpc-return-included-system-attributes local-handle) 
	     varargs-p))
	 (incl-all-sys
	   (build-procedure-identifier-icp-list
	     (gsi-rpc-return-include-all-system-attributes local-handle) 
	     varargs-p))
	 (incl-all-sys-except
	   (build-procedure-identifier-icp-list
	     (gsi-rpc-return-include-all-system-attributes-except local-handle) 
	     varargs-p)) 
	 (remote-procedure-identifier
	   (make-outgoing-remote-procedure-identifier-with-info
	     incl
 	     excl
 	     incl-sys
 	     incl-all-sys
 	     incl-all-sys-except
	     kind-list
	     varargs-p))
	 (derived-socket (get-icp-socket-from-context context t))
	 (user-data (if user-data-p
			user-data
			(inline-get-long-from-fixnum
			  (remote-procedure-identifier-tag remote-procedure-identifier))))) 
    (when incl (reclaim-icp-tree incl))
    (when excl (reclaim-icp-tree excl))
    (when incl-sys (reclaim-icp-tree incl-sys))
    (when incl-all-sys (reclaim-icp-tree incl-all-sys))
    (when incl-all-sys-except (reclaim-icp-tree incl-all-sys-except))  
    (setf (remote-procedure-identifier-caller remote-procedure-identifier)
	  local-handle)
    (setf (remote-procedure-identifier-gsi-user-data remote-procedure-identifier)
	  user-data)
    (with-bifurcated-version (resumable-icp-version derived-socket)
      (progn
	(writing-icp-message-group ((icp-output-port derived-socket))
	  (let ((use-new-message-group-for-send-icp-enlarge-index-space-p nil))
	    (establish-new-object-indices-as-required argument-array)
	    (send-icp-rpc-call remote-procedure-name remote-procedure-identifier
			       argument-array)))
	(flush-outgoing-item-list derived-socket))
      (send-or-enqueue-icp-write-task
	(icp-output-port derived-socket)
	resumable-priority-of-gsi-rpc-service
	#'send-icp-resumable-rpc-call
	(icp-list remote-procedure-name
		  remote-procedure-identifier
		  argument-array)
	nil   ; #'reclaim-rpc-argument-list {currently reclaimed by the api function}
	nil)) ; (icp-list argument-array)
    (gsi-flush-internal)
    user-data))

(def-gsi-api-function (gsi-rpc-start     (:return-type :null))
                      ((local-handle   :object)
		       (argument-array (gsi-temporary-displaced-array
					 (gsi-get-rpc-argument-count
					   local-handle)))
		       (context        gsi-fixnum-long))
  (check-gsi-context context t)
  (gsi-rpc-start-internal local-handle argument-array context))

(def-gsi-api-function (gsi-rpc-start-with-count     (:return-type :null))
                      ((local-handle   :object)
		       (argument-array (gsi-temporary-displaced-array count))
		       (count          gsi-fixnum-long)
		       (context        gsi-fixnum-long))
  (unless (gsi-remote-procedure-p local-handle)
    (gsi-api-error gsi-remote-declaration-not-found))
  (check-gsi-context context t)
  (gsi-rpc-start-internal local-handle argument-array context))

(def-gsi-api-function (gsi-rpc-call    (:return-type :object))
                      ((local-handle   :object)      
		       (argument-array (gsi-temporary-displaced-array
					 (gsi-get-rpc-argument-count
					   local-handle)))
		       (context        gsi-fixnum-long))
  (check-gsi-context context t)
  (gsi-rpc-call-internal local-handle argument-array context nil nil))

(def-gsi-api-function (gsi-rpc-call-with-count    (:return-type :object))
                      ((local-handle   :object)      
		       (argument-array (gsi-temporary-displaced-array count))
		       (count          gsi-fixnum-long)
		       (context        gsi-fixnum-long))
  (unless (gsi-remote-procedure-p local-handle)
    (gsi-api-error gsi-remote-declaration-not-found))
  (check-gsi-context context t)
  (gsi-rpc-call-internal local-handle argument-array context nil nil))

(def-gsi-api-function (gsi-rpc-call-with-u-d    (:return-type :object))
                      ((local-handle   :object)      
		       (argument-array (gsi-temporary-displaced-array
					 (gsi-get-rpc-argument-count
					   local-handle)))
		       (user-data      :object)
		       (context        gsi-fixnum-long))
  (check-gsi-context context t)
  (gsi-rpc-call-internal local-handle argument-array context user-data t))

(def-gsi-api-function (gsi-rpc-call-with-count-u-d    (:return-type :object))
                      ((local-handle   :object)
		       (argument-array (gsi-temporary-displaced-array count))
		       (count          gsi-fixnum-long)
		       (user-data      :object)
		       (context        gsi-fixnum-long))
  (unless (gsi-remote-procedure-p local-handle)
    (gsi-api-error gsi-remote-declaration-not-found))
  (check-gsi-context context t)
  (gsi-rpc-call-internal local-handle argument-array context user-data t))

(defun-void gsi-rpc-return-values-internal (argument-array remote-procedure-identifier context errorp)
  (let* ((rpid-tag (if remote-procedure-identifier
		       (remote-procedure-identifier-tag remote-procedure-identifier)
		       0))
	 (derived-socket (get-icp-socket-from-context context t))
	 (output-port (icp-output-port derived-socket))
	 error-name error-level error-message error-message-for-reclaim)
    (when errorp
      (let ((error-in-arguments (check-gsi-error-argument-list argument-array)))
	(when error-in-arguments
	  (gsi-error 'gsi_rpc_return_values_internal gsi-illegal-error-arguments
		     error-in-arguments)))
      (setq error-level 1)
      (cond ((=f 2 (1-f (gsi-managed-array-length argument-array)))
	     (setq error-name (gsi-instance-value (gsi-managed-svref argument-array 1)))
	     (setq error-message (gsi-instance-value (gsi-managed-svref argument-array 2))))
	    (t
	     (setq error-name (gsi-instance-class (gsi-managed-svref argument-array 1)))
	     (setq error-message (gsi-instance-value (gsi-get-item-of-attribute-named
						       (gsi-managed-svref argument-array 1)
						       'error-description)))))
      (unless (text-string-p error-message)
	(setq error-message (convert-gsi-value-to-value error-message))
	(setq error-message-for-reclaim error-message)))
    (case (if remote-procedure-identifier
	      (remote-procedure-identifier-state remote-procedure-identifier)
	      (if errorp
		  'outstanding
		  nil))
      (outstanding
       (if errorp
	   (with-bifurcated-version (resumable-icp-version derived-socket)
	     (writing-icp-message-group (output-port)
	       (if (<f 0 rpid-tag)
		   (send-icp-rpc-error-to-caller
		     rpid-tag nil
		     error-name error-level error-message nil)
		   (send-icp-rpc-error
		     error-name error-level error-message nil))
	       (reclaim-if-text-string-function error-message-for-reclaim))
	     (send-or-enqueue-icp-write-task
	       output-port
	       resumable-priority-of-gsi-rpc-service
	       #'send-icp-resumable-rpc-error-to-caller
	       (icp-list rpid-tag nil error-name error-level error-message argument-array)
	       #'reclaim-if-text-string-function
	       (icp-list error-message-for-reclaim)))
	   (with-bifurcated-version (resumable-icp-version derived-socket)
	     (progn
	       (writing-icp-message-group (output-port)
		 (let ((use-new-message-group-for-send-icp-enlarge-index-space-p nil))
		   (establish-new-object-indices-as-required argument-array)
		   (send-icp-rpc-return-values rpid-tag argument-array)))
	       (flush-outgoing-item-list derived-socket))
	     (send-or-enqueue-icp-write-task
	       output-port
	       resumable-priority-of-gsi-rpc-service
	       #'send-icp-resumable-rpc-return-values
	       (icp-list rpid-tag argument-array)
	       nil   ; #'reclaim-rpc-argument-list {currently reclaimed by the api function}
	       nil))) ; (icp-list argument-array)
       (gsi-flush-internal)
       (when remote-procedure-identifier
	 (setf (remote-procedure-identifier-state remote-procedure-identifier) 'returned)))
      (async-abort
       (writing-icp-message-group (output-port)
	 (send-icp-rpc-acknowledge-abort rpid-tag)
	 (gsi-flush-internal)))
      (otherwise
       (gsi-error 'gsi_rpc_return_values_internal gsi-bad-rpc-state)))))
  
(def-gsi-api-function (gsi-rpc-return-values (:return-type :null)) 
                      ((argument-array (gsi-temporary-displaced-array count))
                       (count          gsi-fixnum-long)
		       (call-handle    :object)
		       (context        gsi-fixnum-long))
  (unless (remote-procedure-identifier-p call-handle)
    (gsi-api-error gsi-invalid-call-handle))
  (check-gsi-context context t)
  (gsi-rpc-return-values-internal argument-array call-handle context nil))

(def-gsi-api-function (gsi-rpc-return-error-values (:return-type :null)) 
                      ((argument-array (gsi-temporary-displaced-array count))
                       (count          gsi-fixnum-long)
		       (call-handle    :object)
		       (context        gsi-fixnum-long))
  (unless (or (null call-handle)
	      (remote-procedure-identifier-p call-handle))
    (gsi-api-error gsi-invalid-call-handle))
  (check-gsi-context context t)
  (gsi-rpc-return-values-internal argument-array call-handle context t))

(defun-void gsi-start-or-call-local-function-or-handle-return-values
    (invocation-type
      remote-procedure-name remote-procedure-identifier rpc-argument-list)
  (case invocation-type
    (start (setq current-invocation-remotely-started-p t))
    (call  (setq current-invocation-remotely-started-p nil)))
  (let* ((current-remote-procedure-identifier
	   (when (eq invocation-type 'call)
	     remote-procedure-identifier))
	 (argument-list-length
	   (-f (gsi-managed-array-length rpc-argument-list)
	       gsi-magic-offset))
	 (local-function
	   (case invocation-type
	     ((start call)
	      (or (gsi-local-function remote-procedure-name)
		  (gsi-handle-define-remote-procedure-name remote-procedure-name)))
	     (return
	      (remote-procedure-identifier-caller remote-procedure-identifier))
	     (error-return
	      (remote-procedure-identifier-caller remote-procedure-identifier))))
	 (function
	   (when local-function
	     (case invocation-type
		 ((start call)
		  (gsi-function-pointer local-function))
		 ((return)
		  (gsi-return-function local-function))
		 ((error-return)
		  (gsi-error-return-function local-function)))))
	 (remote-procedure-name-symbol
	   (remote-procedure-name-symbol remote-procedure-name)))
    (when (and (memq invocation-type '(start call))
	       local-function
	       remote-procedure-identifier)
      (setf (remote-procedure-identifier-caller remote-procedure-identifier)
	    local-function))
    (if (null function)
	(case invocation-type
	  ((error-return)
	   (multiple-value-bind (error-name error-message)
	       (case argument-list-length
		 (2 (values (gsi-instance-value (gsi-managed-svref rpc-argument-list 1))
			    (gsi-instance-value (gsi-managed-svref rpc-argument-list 2))))
		 (1 (values (gsi-instance-class (gsi-managed-svref rpc-argument-list 1))
			    (gsi-instance-value (gsi-get-item-of-attribute-named
						  (gsi-managed-svref rpc-argument-list 1)
						  'error-description)))))
	     
	     (gsi-warning 'rpc_error_handler_2
			  gsi-rpc-error-from-g2-procedure
			  remote-procedure-name-symbol
			  error-name error-message))))
	(let ((user-data
		(case invocation-type
		  ((start call)
		   (gsi-function-user-data local-function))
		  ((return error-return)
		   (gsi-return-function-user-data local-function))))
	      (info-string
		(case invocation-type
		  (start "rpc_start")
		  (call "rpc_call")
		  (return "rpc_return")
		  (error-return "rpc_error_return"))))
	  (with-backtrace-for-internal-error
	      (rpc-callback
		(push-backtrace-information remote-procedure-name-symbol)
		twrite-gsi-rpc-backtrace-info)
	    (calling-gsi-callback-callback info-string)
	    (case invocation-type
	      ((start call)
	       (if (gsi-option-is-set-p gsi-user-data-for-callbacks)
		   (gsi-funcall-with-user-data
		     function
		     user-data ; procedure user data
		     (gsi-extract-c-array rpc-argument-list)
		     argument-list-length
		     remote-procedure-identifier)
		   (gsi-funcall
		     function
		     (gsi-extract-c-array rpc-argument-list)
		     argument-list-length
		     remote-procedure-identifier)))
	      ((return error-return)
		(if (gsi-option-is-set-p gsi-user-data-for-callbacks)
		    (gsi-return-funcall-with-user-data
		      function
		      user-data ; procedure user data
		      (gsi-extract-c-array rpc-argument-list)
		      argument-list-length
		      (remote-procedure-identifier-gsi-user-data ; call user data
			remote-procedure-identifier))
		    (gsi-return-funcall
		      function
		      (gsi-extract-c-array rpc-argument-list)
		      argument-list-length
		      (remote-procedure-identifier-gsi-user-data ; call user data
			remote-procedure-identifier)))))
	(returning-from-gsi-callback-callback info-string))))
    (case invocation-type
      ((return error-return)
       (setq gsi-most-recent-error-remote-procedure-identifier nil)
       (reclaim-outgoing-remote-procedure-identifier-and-index
	 remote-procedure-identifier)))))

;; End file with [CR]

