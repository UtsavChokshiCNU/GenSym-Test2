;;;; -*- Mode: Common-Lisp; -*-
;;;;
;;;; Lisp Unit Tests for the new #+connections-v2 feature
;;;;
;;;; Author: Chun Tian (binghe) <tian.chun@gensym.com>
;;;;   Date: May 31, 2016.

(in-package :tests)

;;; `create-random-graph' creates a graph (block + connections) with n nodes and
;;; connection probability p. This is the Erdos-Renyi random graph model, with
;;; self-connections (a node may connects to itself).
;;; It returns a node array of lenth n, and the number of created connections.

#|
TESTS 32 > (create-random-graph 5 0)
#<Simple-Vector T 5 @1037>
0

TESTS 33 > (create-random-graph 5 1)
#<Simple-Vector T 5 @1038>
25

TESTS 34 > (create-random-graph 5 0.5)
#<Simple-Vector T 5 @1039>
12
|#

;; To reproduce GENSYMCID-1959, set connection matrix as follows:
;; #2A(((ab::top 1 ab::bottom 1) (ab::top 1 ab::right 1))(nil nil))
;; and create 2 nodes

#+connections-v2 ; only this function depends on data structure in #+connections-v2
(defun create-random-graph (n p &optional connection-matrix)
  (declare (type (integer 0 *) n) ; number of nodes in graph
	   (type (real 0 1) p))   ; connection probability
  ;; 1. create all nodes.
  (let ( ;; the following line disables printing in this fn!
        (*standard-output* (make-broadcast-stream))
        (node-array (make-array n))
        (num-of-conn 0)) ; a counter for created connections
    (loop for i from 0 below n
	  as node = (ab::make-frame 'ab::block) do
      (setf (ab::name-or-names-for-frame node)
	    (intern (format nil "NODE-~D" i)))
      (setf (ab::connections node) (ab::make-connection-item-table))
      (setf (svref node-array i) node))
    ;; 2. create random connections
    (loop for i from 0 below n
	  as node-i = (svref node-array i) do
      (loop for j from 0 below n
	    as node-j = (svref node-array j) do
	;; 2.1 make a connection from i to j on probability
	(when (or (and connection-matrix (aref connection-matrix i j))
                  (and (not connection-matrix) (<= (random 1.0) p)))
          ;; note that printing is normally disabled in this fn
          (print `((connection-matrix ,i ,j) = 1))
	  (incf num-of-conn)
	  (let ((connection (ab::make-connection)))
	    (setf (ab::connection-frame-or-class connection)
		  'ab::connection)
	    ;; 2.2 setup connection end objects
	    (setf (ab::input-end-object connection) node-i)
	    (setf (ab::output-end-object connection) node-j)
	    ;; 2.3 setup random connection positions
	    (setf (ab::input-end-position connection)
		  (ab::combine-side-and-position-on-side-for-end-position
                    ;; note that printing is normally disabled in this fn                    
                   (print
                    (if connection-matrix
                        (first (aref connection-matrix i j))
                      (nth (random 4) '(ab::top ab::left ab::bottom ab::right))))
                    ;; note that printing is normally disabled in this fn                    
                   (print
                    (if connection-matrix
                        (second (aref connection-matrix i j))
                        (random n)))))
	    (setf (ab::output-end-position connection)
		  (ab::combine-side-and-position-on-side-for-end-position
                    ;; note that printing is normally disabled in this fn                    
                   (print
                    (if connection-matrix
                        (third (aref connection-matrix i j))
                      (nth (random 4) '(ab::top ab::left ab::bottom ab::right))))
                    ;; note that printing is normally disabled in this fn                    
                   (print
                    (if connection-matrix
                        (fourth (aref connection-matrix i j))
                      (random n)))))
	    ;; 2.4 attach connection into blocks with port name "in" or "out"
	    (let ((connection-item-i (ab::make-connection-item connection)))
	      (setf (ab::connection-item-output-names connection-item-i) (list 'out))
	      (setf (ab::get-connection-item connection (ab::connections node-i))
		    connection-item-i)
	      ;; 2.5 handle self-connections
	      (cond ((/= i j)
		     (let ((connection-item-j (ab::make-connection-item connection)))
		       (setf (ab::connection-item-input-names connection-item-j) (list 'in))
		       (setf (ab::get-connection-item connection (ab::connections node-j))
			     connection-item-j)))
		    (t
		     (setf (ab::connection-item-input-names connection-item-i) (list 'in))
		     (setf (ab::connection-item-duplicated? connection-item-i) t))))))))
    (format t "Created ~D connections.~%" num-of-conn)
    (values node-array num-of-conn)))


;;; `blocks-are-connected?' test if there's a output connection from block-1 to block-2.

(defun blocks-are-connected? (block-1 block-2)
  (and (ab::loop for connection being each ab::output-connection ab::of block-1
		 as block-at-other-end
		  = (ab::get-block-at-other-end-of-connection connection block-1)
		 thereis (eq block-at-other-end block-2))
       ;; double confirm from the other side
       (ab::loop for connection being each ab::input-connection ab::of block-2
		 as block-at-other-end
		  = (ab::get-block-at-other-end-of-connection connection block-2)
		 thereis (eq block-at-other-end block-1))))


;;; `connected-blocks-of' returns a list of all output connected blocks
;;; `connected-names-of' returns a list names for all output connected blocks.

(defun connected-blocks-of (node)
  (ab::loop for connection being each ab::output-connection ab::of node
	    collect (ab::get-block-at-other-end-of-connection connection node)))

(defun connected-names-of (node)
  (ab::loop for connection being each ab::output-connection ab::of node
	    collect (ab::name-or-names-for-frame
		      (ab::get-block-at-other-end-of-connection connection node))))

(defun describe-connections (node-array)
  (declare (type simple-vector node-array))
  (declare (ignorable node-array))
  ;; uncomment for debug printing
  #|
  (let ((length (length node-array)))
    (loop for i from 0 below length
	  as node = (svref node-array i)
	  as names = (connected-names-of node)
	  do
      (format t "NODE-~D connects to ~A~%" i names))) |#
  node-array)

;; The function can be used for debugging purposes
(defun describe-connection-plus (connection)
  (print "Connection: ")
  (ab::d connection)
  (let ((o (ab::output-end-object-internal connection)))
    (print "Output-end-object: ")
    (print o)
    (print "Connection-table of output-end-object")
    (print (ab::connections o))
    (print "Connection-items of output-end-object")
    (ab::loop ab::for c ab::being ab::each ab::connection ab::of o
              ab::for ci = (ab::get-connection-item c (ab::connections o))
              do (ab::p c) (ab::d ci)))
  (let ((i (ab::input-end-object-internal connection)))
    (print "Input-end-object: ")
    (print i)
    (print "Connection-table of input-end-object")
    (print (ab::connections i))
    (print "Connection-items of input-end-object")
    (ab::loop ab::for c ab::being ab::each ab::connection ab::of i
              ab::for ci = (ab::get-connection-item c (ab::connections i))
              do (ab::p c) (ab::d ci))))


;;; `create-random-graph-with-clones' first call `create-random-graph' to create a
;;; random graph ER(n,p), then call CLONE-CONNECTIONS-SLOT to clone all their connection
;;; slots into stubs. It return the old and new graph as node arrays.

(defun create-random-graph-with-clones (n p)
  (declare (type (integer 0 *) n) ; number of nodes in graph
	   (type (real 0 1) p))   ; connection probability
  (let ((old-node-array (create-random-graph n p))
	(new-node-array (make-array n)))
    ;; 1. create cloned nodes
    (loop for i from 0 below n
	  as node = (ab::make-frame 'ab::block) do
      (setf (ab::name-or-names-for-frame node)
	    (intern (format nil "NODE-~D" i)))
      (setf (svref new-node-array i) node))
    ;; 2. generate blocks-in-bounding-box?
    (let ((blocks-in-bounding-box?
	   (loop for i from 0 below n collect (svref old-node-array i))))
      ;; 3. clone the connections (partially)
      (loop for i from 0 below n
	    as old-node = (svref old-node-array i)
	    as new-node = (svref new-node-array i)
	    do
	(ab::clone-connections-slot (ab::connections old-node)
				    old-node new-node blocks-in-bounding-box?)))
    (values old-node-array new-node-array)))

;;; `test-clone-connections-slot' check if `clone-connections-slot' correctly
;;; cloned a group of connections with the same number of connection stubs for
;;; all output connections.

(defun test-clone-connections-slot (n p)
  (declare (type (integer 0 *) n) ; number of nodes in graph
	   (type (real 0 1) p))   ; connection probability
  ;; 1. generate ER random graph and its clone
  (multiple-value-bind (old new)
      (create-random-graph-with-clones n p)
    ;; 2. verify if the two graphs have the same node degrees.
    (let ((test-result
	   (loop for i from 0 below n
		 as old-node = (svref old i)
		 as new-node = (svref new i)
		 always (= (length (connected-blocks-of old-node))
			   (length (connected-blocks-of new-node))))))
      (or test-result
	  (progn
	    (format t "WARN: test-clone-connections-slot failed!~%")
	    (describe-connections old)
	    (values nil new old))))))


;;; `test-clone-connections-for-block' check if the a cloned random graph
;;; is isomorphismo with the original one.  `clone-connections-for-block' is the
;;; most complicated function in the whole #+connections-v2 system.

(defun test-clone-connections-for-block (n p)
  (declare (type (integer 0 *) n) ; number of nodes in graph
	   (type (real 0 1) p))   ; connection probability
  ;; 1. generate ER random graph and its clone
  (multiple-value-bind (old new)
      (create-random-graph-with-clones n p)
    (declare (type simple-vector old new))
    (describe-connections old) ; debug purpose
    ;; 2. prepare environments for `clone-connections-for-block'
    (let ((plist-of-blocks-and-corresponding-clones
	   (loop for i from 0 below n
		 nconc (list (svref old i) (svref new i)))))
      ;; 3. call `clone-connections-for-block' on each cloned block.
      (loop for i from 0 below n
	    as block = (svref old i)
	    as cloned-block = (svref new i)
	    do
	(ab::clone-connections-for-block block cloned-block
					 plist-of-blocks-and-corresponding-clones))
      ;; 4. verify if the two graphs are isomorphismo
      (let ((test-result
	     (loop for i from 0 below n
		   as old-node = (svref old i)
		   as new-node = (svref new i)
		   as old-names = (connected-names-of old-node)
		   as new-names = (connected-names-of new-node)
		   always (and (null (set-difference old-names new-names))
			       (null (set-difference new-names old-names))))))
	(or test-result
	    (progn
	      (format t "~%WARN: test-clone-connections-for-block failed!~%")
	      (describe-connections new)
	      (values nil new old)))))))

;; NOTE: some large tests were SBCL only, because it may reach heap limits.

(define-test unit-test-clone-connections-slot
  (with-connection-test-environment ()
    (assert-true (test-clone-connections-slot 5 0.5))
    (assert-true (test-clone-connections-slot 10 0.4))
    (assert-true (test-clone-connections-slot 15 0.3))))

(define-test unit-test-clone-connections-for-block
  (with-connection-test-environment ()
    (macrolet ((test-one-configuration (number-of-repetitions number-of-blocks probability-of-connectedness)
                 (let ((expression `(test-clone-connections-for-block ,number-of-blocks ,probability-of-connectedness)))
                   `(let ((success t))
                      (dotimes (i ,number-of-repetitions)
                        (unless ,expression
                          (setf success nil)
                          (show-expr `("failed" ,',expression)) 
                          (return)))
                      (assert-true success)))))
      (test-one-configuration 1000 2 0.5)
      (test-one-configuration 100 10 0.4)
      (test-one-configuration 30 15 0.3))))

