(in-package :tests)

#|
;; Get-port-names-for-connection returns a list of eval-conses of
;; the port names for a connection.

(defun-simple get-port-names-for-connection (block connection)
  #-connections-v2
  (let ((connections-sublist
	  (get-connections-sublist-for-connection
	    block connection))
	(port-name-list nil))
    (loop for port-name? in connections-sublist
	  while (not (connection-p port-name?))
	  do
      (setq port-name-list
	    (nconc port-name-list
		   (eval-cons port-name? nil))))
    port-name-list)
  ;; GENSYMCID-1834: G2 2015 Aborts when loading some of our applications
  ;;
  ;; In connection-v1, if `block' and `connection' are not connected, this function returns
  ;; NIL. But in connection-v2, the function will crash, now we've fixed it to return NIL.
  #+connections-v2
  (when-let (connection-item
	     (get-connection-item connection (connections block)))
    (copy-list-using-eval-conses
      (case (get-direction-of-connection connection block)
	(input
	 (connection-item-input-names connection-item))
	(t ; output or undirected
	 (connection-item-output-names connection-item))))))
|#

;;; this test fails in connections-v2 before GENSYMCID-1834 and passes after.

(define-test test-get-port-names-for-connection
  (with-connection-test-environment ()
    (let ((block-1 (ab::make-frame 'ab::block))
	  (conne-1 (ab::make-connection)))
      (setf (ab::name-or-names-for-frame block-1) 'node)
      (setf (ab::connections block-1) (ab::make-connection-item-table))
      (setf (ab::connection-frame-or-class conne-1) 'ab::connection)
      (let ((port-names
	     (handler-case (ab::get-port-names-for-connection block-1 conne-1)
	       (error () 'error))))
	(assert-eq port-names nil)))))
